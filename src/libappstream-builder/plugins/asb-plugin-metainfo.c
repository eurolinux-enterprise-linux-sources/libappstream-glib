/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*-
 *
 * Copyright (C) 2014-2015 Richard Hughes <richard@hughsie.com>
 *
 * Licensed under the GNU Lesser General Public License Version 2.1
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#include <config.h>
#include <fnmatch.h>

#include <asb-plugin.h>

/**
 * asb_plugin_get_name:
 */
const gchar *
asb_plugin_get_name (void)
{
	return "metainfo";
}

/**
 * asb_plugin_add_globs:
 */
void
asb_plugin_add_globs (AsbPlugin *plugin, GPtrArray *globs)
{
	asb_plugin_add_glob (globs, "/usr/share/appdata/*.metainfo.xml");
}

/**
 * _asb_plugin_check_filename:
 */
static gboolean
_asb_plugin_check_filename (const gchar *filename)
{
	if (asb_plugin_match_glob ("/usr/share/appdata/*.metainfo.xml", filename))
		return TRUE;
	return FALSE;
}

/**
 * asb_plugin_check_filename:
 */
gboolean
asb_plugin_check_filename (AsbPlugin *plugin, const gchar *filename)
{
	return _asb_plugin_check_filename (filename);
}

/**
 * asb_plugin_process_filename:
 */
static gboolean
asb_plugin_process_filename (AsbPlugin *plugin,
			     AsbPackage *pkg,
			     const gchar *filename,
			     GList **apps,
			     GError **error)
{
	_cleanup_object_unref_ AsbApp *app = NULL;

	app = asb_app_new (pkg, NULL);
	if (!as_app_parse_file (AS_APP (app), filename,
				AS_APP_PARSE_FLAG_APPEND_DATA,
				error))
		return FALSE;
	if (as_app_get_id_kind (AS_APP (app)) != AS_ID_KIND_ADDON &&
	    as_app_get_id_kind (AS_APP (app)) != AS_ID_KIND_FONT) {
		g_set_error (error,
			     ASB_PLUGIN_ERROR,
			     ASB_PLUGIN_ERROR_FAILED,
			     "%s is not an addon or font",
			     as_app_get_id (AS_APP (app)));
		return FALSE;
	}
	asb_app_set_requires_appdata (app, FALSE);
	asb_app_set_hidpi_enabled (app, asb_context_get_flag (plugin->ctx, ASB_CONTEXT_FLAG_HIDPI_ICONS));
	asb_plugin_add_app (apps, AS_APP (app));
	return TRUE;
}

/**
 * asb_plugin_process:
 */
GList *
asb_plugin_process (AsbPlugin *plugin,
		    AsbPackage *pkg,
		    const gchar *tmpdir,
		    GError **error)
{
	gboolean ret;
	GList *apps = NULL;
	guint i;
	gchar **filelist;

	filelist = asb_package_get_filelist (pkg);
	for (i = 0; filelist[i] != NULL; i++) {
		_cleanup_free_ gchar *filename_tmp = NULL;
		if (!_asb_plugin_check_filename (filelist[i]))
			continue;
		filename_tmp = g_build_filename (tmpdir, filelist[i], NULL);
		ret = asb_plugin_process_filename (plugin,
						   pkg,
						   filename_tmp,
						   &apps,
						   error);
		if (!ret) {
			g_list_free_full (apps, (GDestroyNotify) g_object_unref);
			return NULL;
		}
	}

	/* no desktop files we care about */
	if (apps == NULL) {
		g_set_error (error,
			     ASB_PLUGIN_ERROR,
			     ASB_PLUGIN_ERROR_FAILED,
			     "nothing interesting in %s",
			     asb_package_get_basename (pkg));
		return NULL;
	}
	return apps;
}

/**
 * asb_plugin_merge:
 */
void
asb_plugin_merge (AsbPlugin *plugin, GList *list)
{
	AsApp *app;
	AsApp *found;
	GList *l;
	_cleanup_hashtable_unref_ GHashTable *hash = NULL;

	/* make a hash table of ID->AsApp */
	hash = g_hash_table_new_full (g_str_hash, g_str_equal,
				      g_free, (GDestroyNotify) g_object_unref);
	for (l = list; l != NULL; l = l->next) {
		app = AS_APP (l->data);
		if (as_app_get_id_kind (app) != AS_ID_KIND_DESKTOP)
			continue;
		g_hash_table_insert (hash,
				     g_strdup (as_app_get_id (app)),
				     g_object_ref (app));
	}

	/* add addons where the pkgname is different from the
	 * main package */
	for (l = list; l != NULL; l = l->next) {
		if (!ASB_IS_APP (l->data))
			continue;
		app = AS_APP (l->data);
		if (as_app_get_id_kind (app) != AS_ID_KIND_ADDON)
			continue;
		found = g_hash_table_lookup (hash, as_app_get_id (app));
		if (found == NULL)
			continue;
		if (g_strcmp0 (as_app_get_pkgname_default (app),
			       as_app_get_pkgname_default (found)) != 0)
			continue;
		as_app_add_veto (app,
				 "absorbing addon %s shipped in "
				 "main package %s",
				 as_app_get_id (app),
				 as_app_get_pkgname_default (app));
		as_app_subsume_full (found, app, AS_APP_SUBSUME_FLAG_PARTIAL);
	}
}
