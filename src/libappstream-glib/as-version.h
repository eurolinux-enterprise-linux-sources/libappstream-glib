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

/**
 * SECTION:as-version
 * @short_description: Preprocessor macros for the libappstream-glib version
 * @include: appstream-glib.h
 * @stability: Stable
 *
 * These functions are used in client code to conditionalize compilation
 * depending on the version of libappstream-glib headers installed.
 */

#if !defined (__APPSTREAM_GLIB_H) && !defined (AS_COMPILATION)
#error "Only <appstream_glib.h> can be included directly."
#endif

#ifndef __AS_VERSION_H
#define __AS_VERSION_H

/* compile time version
 */
#define AS_MAJOR_VERSION				(0)
#define AS_MINOR_VERSION				(3)
#define AS_MICRO_VERSION				(6)

/* check whether a As version equal to or greater than
 * major.minor.micro.
 */
#define AS_CHECK_VERSION(major,minor,micro)    \
    (AS_MAJOR_VERSION > (major) || \
     (AS_MAJOR_VERSION == (major) && AS_MINOR_VERSION > (minor)) || \
     (AS_MAJOR_VERSION == (major) && AS_MINOR_VERSION == (minor) && \
      AS_MICRO_VERSION >= (micro)))

#endif /* __AS_VERSION_H */
