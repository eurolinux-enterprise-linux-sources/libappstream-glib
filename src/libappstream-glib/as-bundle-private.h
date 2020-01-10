/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*-
 *
 * Copyright (C) 2014 Richard Hughes <richard@hughsie.com>
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

#if !defined (__APPSTREAM_GLIB_PRIVATE_H) && !defined (AS_COMPILATION)
#error "Only <appstream-glib.h> can be included directly."
#endif

#ifndef __AS_BUNDLE_PRIVATE_H
#define __AS_BUNDLE_PRIVATE_H

#include "as-bundle.h"
#include "as-node-private.h"

G_BEGIN_DECLS

GNode		*as_bundle_node_insert		(AsBundle	*bundle,
						 GNode		*parent,
						 AsNodeContext	*ctx);
gboolean	 as_bundle_node_parse		(AsBundle	*bundle,
						 GNode		*node,
						 AsNodeContext	*ctx,
						 GError		**error);
gboolean	 as_bundle_node_parse_dep11	(AsBundle	*bundle,
						 GNode		*node,
						 AsNodeContext	*ctx,
						 GError		**error);

G_END_DECLS

#endif /* __AS_BUNDLE_PRIVATE_H */
