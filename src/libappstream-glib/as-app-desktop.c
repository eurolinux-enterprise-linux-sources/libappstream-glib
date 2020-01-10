/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*-
 *
 * Copyright (C) 2013-2015 Richard Hughes <richard@hughsie.com>
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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA
 */

#include <fnmatch.h>
#include <string.h>

#include "as-app-private.h"
#include "as-cleanup.h"
#include "as-utils.h"

/**
 * as_app_desktop_key_get_locale:
 */
static gchar *
as_app_desktop_key_get_locale (const gchar *key)
{
	gchar *tmp1;
	gchar *tmp2;
	gchar *locale = NULL;

	tmp1 = g_strstr_len (key, -1, "[");
	if (tmp1 == NULL)
		return NULL;
	tmp2 = g_strstr_len (tmp1, -1, "]");
	if (tmp1 == NULL)
		return NULL;
	locale = g_strdup (tmp1 + 1);
	locale[tmp2 - tmp1 - 1] = '\0';
	return locale;
}

/**
 * as_app_infer_file_key:
 **/
static gboolean
as_app_infer_file_key (AsApp *app,
		       GKeyFile *kf,
		       const gchar *key,
		       GError **error)
{
	_cleanup_free_ gchar *tmp = NULL;

	if (g_strcmp0 (key, "X-GNOME-UsesNotifications") == 0) {
		as_app_add_kudo_kind (AS_APP (app),
				      AS_KUDO_KIND_NOTIFICATIONS);

	} else if (g_strcmp0 (key, "X-GNOME-Bugzilla-Bugzilla") == 0) {
		tmp = g_key_file_get_string (kf,
					     G_KEY_FILE_DESKTOP_GROUP,
					     key,
					     NULL);
		if (g_strcmp0 (tmp, "GNOME") == 0)
			as_app_set_project_group (app, "GNOME", -1);

	} else if (g_strcmp0 (key, "X-MATE-Bugzilla-Product") == 0) {
		as_app_set_project_group (app, "MATE", -1);

	} else if (g_strcmp0 (key, "X-KDE-StartupNotify") == 0) {
		as_app_set_project_group (app, "KDE", -1);

	} else if (g_strcmp0 (key, "X-DocPath") == 0) {
		tmp = g_key_file_get_string (kf,
					     G_KEY_FILE_DESKTOP_GROUP,
					     key,
					     NULL);
		if (g_str_has_prefix (tmp, "http://userbase.kde.org/"))
			as_app_set_project_group (app, "KDE", -1);

	/* Exec */
	} else if (g_strcmp0 (key, G_KEY_FILE_DESKTOP_KEY_EXEC) == 0) {
		tmp = g_key_file_get_string (kf,
					     G_KEY_FILE_DESKTOP_GROUP,
					     key,
					     NULL);
		if (g_str_has_prefix (tmp, "xfce4-"))
			as_app_set_project_group (app, "XFCE", -1);
	}

	return TRUE;
}

/**
 * as_app_parse_file_key:
 **/
static gboolean
as_app_parse_file_key (AsApp *app,
		       GKeyFile *kf,
		       const gchar *key,
		       GError **error)
{
	gchar *dot = NULL;
	guint i;
	guint j;
	_cleanup_free_ gchar *locale = NULL;
	_cleanup_free_ gchar *tmp = NULL;
	_cleanup_strv_free_ gchar **list = NULL;

	/* NoDisplay */
	if (g_strcmp0 (key, G_KEY_FILE_DESKTOP_KEY_NO_DISPLAY) == 0) {
		tmp = g_key_file_get_string (kf,
					     G_KEY_FILE_DESKTOP_GROUP,
					     key,
					     NULL);
		if (tmp != NULL && strcasecmp (tmp, "True") == 0)
			as_app_add_veto (app, "NoDisplay=true");

	/* Type */
	} else if (g_strcmp0 (key, G_KEY_FILE_DESKTOP_KEY_TYPE) == 0) {
		tmp = g_key_file_get_string (kf,
					     G_KEY_FILE_DESKTOP_GROUP,
					     key,
					     NULL);
		if (g_strcmp0 (tmp, G_KEY_FILE_DESKTOP_TYPE_APPLICATION) != 0) {
			g_set_error_literal (error,
					     AS_APP_ERROR,
					     AS_APP_ERROR_INVALID_TYPE,
					     "not an application");
			return FALSE;
		}

	/* Icon */
	} else if (g_strcmp0 (key, G_KEY_FILE_DESKTOP_KEY_ICON) == 0) {
		tmp = g_key_file_get_string (kf,
					     G_KEY_FILE_DESKTOP_GROUP,
					     key,
					     NULL);
		if (tmp != NULL && tmp[0] != '\0') {
			_cleanup_object_unref_ AsIcon *icon = NULL;
			icon = as_icon_new ();
			as_icon_set_name (icon, tmp, -1);
			dot = g_strstr_len (tmp, -1, ".");
			if (dot != NULL)
				*dot = '\0';
			if (as_utils_is_stock_icon_name (tmp)) {
				as_icon_set_name (icon, tmp, -1);
				as_icon_set_kind (icon, AS_ICON_KIND_STOCK);
			} else {
				as_icon_set_kind (icon, AS_ICON_KIND_LOCAL);
			}
			as_app_add_icon (app, icon);
		}

	/* Categories */
	} else if (g_strcmp0 (key, G_KEY_FILE_DESKTOP_KEY_CATEGORIES) == 0) {
		list = g_key_file_get_string_list (kf,
						   G_KEY_FILE_DESKTOP_GROUP,
						   key,
						   NULL, NULL);
		for (i = 0; list[i] != NULL; i++) {

			/* check categories that if present would blacklist
			 * the application */
			if (fnmatch ("X-*-Settings-Panel", list[i], 0) == 0 ||
			    fnmatch ("X-*-Settings", list[i], 0) == 0 ||
			    fnmatch ("X-*-SettingsDialog", list[i], 0) == 0) {
				as_app_add_veto (app, "category '%s' blacklisted", list[i]);
				continue;
			}

			/* not a standard category */
			if (g_str_has_prefix (list[i], "X-"))
				continue;

			/* check the category is valid */
			if (!as_utils_is_category_id (list[i]))
				continue;

			/* ignore some useless keys */
			if (g_strcmp0 (list[i], "GTK") == 0)
				continue;
			if (g_strcmp0 (list[i], "Qt") == 0)
				continue;
			if (g_strcmp0 (list[i], "KDE") == 0)
				continue;
			if (g_strcmp0 (list[i], "GNOME") == 0)
				continue;
			as_app_add_category (app, list[i], -1);
		}

	} else if (g_strcmp0 (key, "Keywords") == 0) {
		list = g_key_file_get_string_list (kf,
						   G_KEY_FILE_DESKTOP_GROUP,
						   key,
						   NULL, NULL);
		for (i = 0; list[i] != NULL; i++) {
			_cleanup_strv_free_ gchar **kw_split = NULL;
			kw_split = g_strsplit (list[i], ",", -1);
			for (j = 0; kw_split[j] != NULL; j++) {
				if (kw_split[j][0] == '\0')
					continue;
				as_app_add_keyword (app, "C",
						    kw_split[j], -1);
			}
		}

	} else if (g_str_has_prefix (key, "Keywords")) {
		locale = as_app_desktop_key_get_locale (key);
		list = g_key_file_get_locale_string_list (kf,
							  G_KEY_FILE_DESKTOP_GROUP,
							  key,
							  locale,
							  NULL, NULL);
		for (i = 0; list[i] != NULL; i++) {
			_cleanup_strv_free_ gchar **kw_split = NULL;
			kw_split = g_strsplit (list[i], ",", -1);
			for (j = 0; kw_split[j] != NULL; j++) {
				if (kw_split[j][0] == '\0')
					continue;
				as_app_add_keyword (app, locale,
						    kw_split[j], -1);
			}
		}

	} else if (g_strcmp0 (key, "MimeType") == 0) {
		list = g_key_file_get_string_list (kf,
						   G_KEY_FILE_DESKTOP_GROUP,
						   key,
						   NULL, NULL);
		for (i = 0; list[i] != NULL; i++)
			as_app_add_mimetype (app, list[i], -1);

	} else if (g_strcmp0 (key, "X-AppInstall-Package") == 0) {
		tmp = g_key_file_get_string (kf,
					     G_KEY_FILE_DESKTOP_GROUP,
					     key,
					     NULL);
		if (tmp != NULL && tmp[0] != '\0')
			as_app_add_pkgname (app, tmp, -1);

	/* OnlyShowIn */
	} else if (g_strcmp0 (key, G_KEY_FILE_DESKTOP_KEY_ONLY_SHOW_IN) == 0) {
		/* if an app has only one entry, it's that desktop */
		list = g_key_file_get_string_list (kf,
						   G_KEY_FILE_DESKTOP_GROUP,
						   key,
						   NULL, NULL);
		if (g_strv_length (list) == 1)
			as_app_set_project_group (app, list[0], -1);

	/* Name */
	} else if (g_strcmp0 (key, G_KEY_FILE_DESKTOP_KEY_NAME) == 0 ||
	           g_strcmp0 (key, "_Name") == 0) {
		tmp = g_key_file_get_string (kf,
					     G_KEY_FILE_DESKTOP_GROUP,
					     key,
					     NULL);
		if (tmp != NULL && tmp[0] != '\0')
			as_app_set_name (app, "C", tmp, -1);

	/* Name[] */
	} else if (g_str_has_prefix (key, G_KEY_FILE_DESKTOP_KEY_NAME)) {
		locale = as_app_desktop_key_get_locale (key);
		tmp = g_key_file_get_locale_string (kf,
						    G_KEY_FILE_DESKTOP_GROUP,
						    G_KEY_FILE_DESKTOP_KEY_NAME,
						    locale,
						    NULL);
		if (tmp != NULL && tmp[0] != '\0')
			as_app_set_name (app, locale, tmp, -1);

	/* Comment */
	} else if (g_strcmp0 (key, G_KEY_FILE_DESKTOP_KEY_COMMENT) == 0 ||
	           g_strcmp0 (key, "_Comment") == 0) {
		tmp = g_key_file_get_string (kf,
					     G_KEY_FILE_DESKTOP_GROUP,
					     key,
					     NULL);
		if (tmp != NULL && tmp[0] != '\0')
			as_app_set_comment (app, "C", tmp, -1);

	/* Comment[] */
	} else if (g_str_has_prefix (key, G_KEY_FILE_DESKTOP_KEY_COMMENT)) {
		locale = as_app_desktop_key_get_locale (key);
		tmp = g_key_file_get_locale_string (kf,
						    G_KEY_FILE_DESKTOP_GROUP,
						    G_KEY_FILE_DESKTOP_KEY_COMMENT,
						    locale,
						    NULL);
		if (tmp != NULL && tmp[0] != '\0')
			as_app_set_comment (app, locale, tmp, -1);

	/* non-standard */
	} else if (g_strcmp0 (key, "X-Ubuntu-Software-Center-Name") == 0) {
		tmp = g_key_file_get_string (kf,
					     G_KEY_FILE_DESKTOP_GROUP,
					     key,
					     NULL);
		if (tmp != NULL && tmp[0] != '\0')
			as_app_set_name (app, "C", tmp, -1);
	} else if (g_str_has_prefix (key, "X-Ubuntu-Software-Center-Name")) {
		locale = as_app_desktop_key_get_locale (key);
		tmp = g_key_file_get_locale_string (kf,
						    G_KEY_FILE_DESKTOP_GROUP,
						    "X-Ubuntu-Software-Center-Name",
						    locale,
						    NULL);
		if (tmp != NULL && tmp[0] != '\0')
			as_app_set_name (app, locale, tmp, -1);
	}

	return TRUE;
}

/**
 * as_app_parse_desktop_file:
 **/
gboolean
as_app_parse_desktop_file (AsApp *app,
			   const gchar *desktop_file,
			   AsAppParseFlags flags,
			   GError **error)
{
	GKeyFileFlags kf_flags = G_KEY_FILE_KEEP_TRANSLATIONS;
	gchar *tmp;
	guint i;
	_cleanup_error_free_ GError *error_local = NULL;
	_cleanup_free_ gchar *app_id = NULL;
	_cleanup_keyfile_unref_ GKeyFile *kf = NULL;
	_cleanup_strv_free_ gchar **keys = NULL;

	/* load file */
	kf = g_key_file_new ();
	if (flags & AS_APP_PARSE_FLAG_KEEP_COMMENTS)
		kf_flags |= G_KEY_FILE_KEEP_COMMENTS;
	if (!g_key_file_load_from_file (kf, desktop_file, kf_flags, &error_local)) {
		g_set_error (error,
			     AS_APP_ERROR,
			     AS_APP_ERROR_INVALID_TYPE,
			     "Failed to parse %s: %s",
			     desktop_file, error_local->message);
		return FALSE;
	}

	/* create app */
	app_id = g_path_get_basename (desktop_file);
	as_app_set_id_kind (app, AS_ID_KIND_DESKTOP);

	/* is blacklisted */
	if (as_utils_is_blacklisted_id (app_id))
		as_app_add_veto (app, "%s is not an application", app_id);

	/* Ubuntu helpfully put the package name in the desktop file name */
	tmp = g_strstr_len (app_id, -1, ":");
	if (tmp != NULL)
		as_app_set_id (app, tmp + 1, -1);
	else
		as_app_set_id (app, app_id, -1);

	/* look at all the keys */
	keys = g_key_file_get_keys (kf, G_KEY_FILE_DESKTOP_GROUP, NULL, error);
	if (keys == NULL)
		return FALSE;
	for (i = 0; keys[i] != NULL; i++) {
		if (!as_app_parse_file_key (app, kf, keys[i], error))
			return FALSE;
		if ((flags & AS_APP_PARSE_FLAG_USE_HEURISTICS) > 0) {
			if (!as_app_infer_file_key (app, kf, keys[i], error))
				return FALSE;
		}
	}

	/* all applications require icons */
	if (as_app_get_icons(app)->len == 0)
		as_app_add_veto (app, "%s has no icon", app_id);

	return TRUE;
}
