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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA
 */

/**
 * SECTION:as-bundle
 * @short_description: Object representing a single bundle used in a screenshot.
 * @include: appstream-glib.h
 * @stability: Stable
 *
 * Screenshot may have multiple versions of an bundle in different resolutions
 * or aspect ratios. This object allows access to the location and size of a
 * single bundle.
 *
 * See also: #AsScreenshot
 */

#include "config.h"

#include "as-cleanup.h"
#include "as-bundle-private.h"
#include "as-node-private.h"
#include "as-utils-private.h"
#include "as-yaml.h"

typedef struct _AsBundlePrivate	AsBundlePrivate;
struct _AsBundlePrivate
{
	AsBundleKind		 kind;
	gchar			*id;
};

G_DEFINE_TYPE_WITH_PRIVATE (AsBundle, as_bundle, G_TYPE_OBJECT)

#define GET_PRIVATE(o) (as_bundle_get_instance_private (o))

/**
 * as_bundle_finalize:
 **/
static void
as_bundle_finalize (GObject *object)
{
	AsBundle *bundle = AS_BUNDLE (object);
	AsBundlePrivate *priv = GET_PRIVATE (bundle);

	g_free (priv->id);

	G_OBJECT_CLASS (as_bundle_parent_class)->finalize (object);
}

/**
 * as_bundle_init:
 **/
static void
as_bundle_init (AsBundle *bundle)
{
}

/**
 * as_bundle_class_init:
 **/
static void
as_bundle_class_init (AsBundleClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS (klass);
	object_class->finalize = as_bundle_finalize;
}


/**
 * as_bundle_kind_from_string:
 * @kind: the string.
 *
 * Converts the text representation to an enumerated value.
 *
 * Returns: (transfer full): a #AsBundleKind, or %AS_BUNDLE_KIND_UNKNOWN for unknown.
 *
 * Since: 0.3.5
 **/
AsBundleKind
as_bundle_kind_from_string (const gchar *kind)
{
	if (g_strcmp0 (kind, "limba") == 0)
		return AS_BUNDLE_KIND_LIMBA;
	if (g_strcmp0 (kind, "xdg-app") == 0)
		return AS_BUNDLE_KIND_XDG_APP;
	return AS_BUNDLE_KIND_UNKNOWN;
}

/**
 * as_bundle_kind_to_string:
 * @kind: the #AsBundleKind.
 *
 * Converts the enumerated value to an text representation.
 *
 * Returns: string version of @kind
 *
 * Since: 0.3.5
 **/
const gchar *
as_bundle_kind_to_string (AsBundleKind kind)
{
	if (kind == AS_BUNDLE_KIND_LIMBA)
		return "limba";
	if (kind == AS_BUNDLE_KIND_XDG_APP)
		return "xdg-app";
	return NULL;
}

/**
 * as_bundle_get_id:
 * @bundle: a #AsBundle instance.
 *
 * Gets the ID for this bundle.
 *
 * Returns: ID, e.g. "foobar-1.0.2"
 *
 * Since: 0.3.5
 **/
const gchar *
as_bundle_get_id (AsBundle *bundle)
{
	AsBundlePrivate *priv = GET_PRIVATE (bundle);
	return priv->id;
}

/**
 * as_bundle_get_kind:
 * @bundle: a #AsBundle instance.
 *
 * Gets the bundle kind.
 *
 * Returns: the #AsBundleKind
 *
 * Since: 0.3.5
 **/
AsBundleKind
as_bundle_get_kind (AsBundle *bundle)
{
	AsBundlePrivate *priv = GET_PRIVATE (bundle);
	return priv->kind;
}

/**
 * as_bundle_set_id:
 * @bundle: a #AsBundle instance.
 * @id: the URL.
 * @id_len: the size of @id, or -1 if %NULL-terminated.
 *
 * Sets the ID for this bundle.
 *
 * Since: 0.3.5
 **/
void
as_bundle_set_id (AsBundle *bundle, const gchar *id, gssize id_len)
{
	AsBundlePrivate *priv = GET_PRIVATE (bundle);
	g_free (priv->id);
	priv->id = as_strndup (id, id_len);
}

/**
 * as_bundle_set_kind:
 * @bundle: a #AsBundle instance.
 * @kind: the #AsBundleKind, e.g. %AS_BUNDLE_KIND_THUMBNAIL.
 *
 * Sets the bundle kind.
 *
 * Since: 0.3.5
 **/
void
as_bundle_set_kind (AsBundle *bundle, AsBundleKind kind)
{
	AsBundlePrivate *priv = GET_PRIVATE (bundle);
	priv->kind = kind;
}

/**
 * as_bundle_node_insert: (skip)
 * @bundle: a #AsBundle instance.
 * @parent: the parent #GNode to use..
 * @ctx: the #AsNodeContext
 *
 * Inserts the bundle into the DOM tree.
 *
 * Returns: (transfer none): A populated #GNode
 *
 * Since: 0.3.5
 **/
GNode *
as_bundle_node_insert (AsBundle *bundle, GNode *parent, AsNodeContext *ctx)
{
	AsBundlePrivate *priv = GET_PRIVATE (bundle);
	GNode *n;

	n = as_node_insert (parent, "bundle", priv->id,
			    AS_NODE_INSERT_FLAG_NONE,
			    "type", as_bundle_kind_to_string (priv->kind),
			    NULL);
	return n;
}

/**
 * as_bundle_node_parse:
 * @bundle: a #AsBundle instance.
 * @node: a #GNode.
 * @ctx: a #AsNodeContext.
 * @error: A #GError or %NULL.
 *
 * Populates the object from a DOM node.
 *
 * Returns: %TRUE for success
 *
 * Since: 0.3.5
 **/
gboolean
as_bundle_node_parse (AsBundle *bundle, GNode *node,
		      AsNodeContext *ctx, GError **error)
{
	AsBundlePrivate *priv = GET_PRIVATE (bundle);
	const gchar *tmp;
	gchar *taken;

	tmp = as_node_get_attribute (node, "type");
	as_bundle_set_kind (bundle, as_bundle_kind_from_string (tmp));
	taken = as_node_take_data (node);
	if (taken != NULL) {
		g_free (priv->id);
		priv->id = taken;
	}
	return TRUE;
}

/**
 * as_bundle_node_parse_dep11:
 * @bundle: a #AsBundle instance.
 * @node: a #GNode.
 * @ctx: a #AsNodeContext.
 * @error: A #GError or %NULL.
 *
 * Populates the object from a DEP-11 node.
 *
 * Returns: %TRUE for success
 *
 * Since: 0.3.5
 **/
gboolean
as_bundle_node_parse_dep11 (AsBundle *im, GNode *node,
			    AsNodeContext *ctx, GError **error)
{
	GNode *n;
	const gchar *tmp;

	for (n = node->children; n != NULL; n = n->next) {
		tmp = as_yaml_node_get_key (n);
		if (g_strcmp0 (tmp, "id") == 0)
			as_bundle_set_id (im, as_yaml_node_get_value (n), -1);
	}
	return TRUE;
}

/**
 * as_bundle_new:
 *
 * Creates a new #AsBundle.
 *
 * Returns: (transfer full): a #AsBundle
 *
 * Since: 0.3.5
 **/
AsBundle *
as_bundle_new (void)
{
	AsBundle *bundle;
	bundle = g_object_new (AS_TYPE_BUNDLE, NULL);
	return AS_BUNDLE (bundle);
}
