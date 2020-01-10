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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#ifndef ASB_PACKAGE_RPM_H
#define ASB_PACKAGE_RPM_H

#include <glib-object.h>

#include <stdarg.h>
#include <appstream-glib.h>

#include "asb-package.h"

#define ASB_TYPE_PACKAGE_RPM		(asb_package_rpm_get_type())
#define ASB_PACKAGE_RPM(obj)		(G_TYPE_CHECK_INSTANCE_CAST((obj), ASB_TYPE_PACKAGE_RPM, AsbPackageRpm))
#define ASB_PACKAGE_RPM_CLASS(cls)	(G_TYPE_CHECK_CLASS_CAST((cls), ASB_TYPE_PACKAGE_RPM, AsbPackageRpmClass))
#define ASB_IS_PACKAGE_RPM(obj)		(G_TYPE_CHECK_INSTANCE_TYPE((obj), ASB_TYPE_PACKAGE_RPM))
#define ASB_IS_PACKAGE_RPM_CLASS(cls)	(G_TYPE_CHECK_CLASS_TYPE((cls), ASB_TYPE_PACKAGE_RPM))
#define ASB_PACKAGE_RPM_GET_CLASS(obj)	(G_TYPE_INSTANCE_GET_CLASS((obj), ASB_TYPE_PACKAGE_RPM, AsbPackageRpmClass))

G_BEGIN_DECLS

typedef struct _AsbPackageRpm		AsbPackageRpm;
typedef struct _AsbPackageRpmClass	AsbPackageRpmClass;

struct _AsbPackageRpm
{
	AsbPackage			parent;
};

struct _AsbPackageRpmClass
{
	AsbPackageClass			parent_class;
};

GType		 asb_package_rpm_get_type	(void);

AsbPackage	*asb_package_rpm_new		(void);

G_END_DECLS

#endif /* ASB_PACKAGE_RPM_H */
