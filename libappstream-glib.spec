%global glib2_version 2.45.8
%global libsoup_version 2.51.92
%global json_glib_version 1.1.1
%global gdk_pixbuf_version 2.31.5

Summary:   Library for AppStream metadata
Name:      libappstream-glib
Version:   0.6.10
Release:   1%{?dist}
License:   LGPLv2+
URL:       http://people.freedesktop.org/~hughsient/appstream-glib/
Source0:   http://people.freedesktop.org/~hughsient/appstream-glib/releases/appstream-glib-%{version}.tar.xz

BuildRequires: glib2-devel >= %{glib2_version}
BuildRequires: libtool
BuildRequires: docbook-utils
BuildRequires: gtk-doc
BuildRequires: gobject-introspection-devel
BuildRequires: gperf
BuildRequires: libarchive-devel
BuildRequires: libsoup-devel >= %{libsoup_version}
BuildRequires: gdk-pixbuf2-devel >= %{gdk_pixbuf_version}
BuildRequires: gtk3-devel
BuildRequires: gettext
BuildRequires: libgcab1-devel
BuildRequires: libuuid-devel
BuildRequires: json-glib-devel >= %{json_glib_version}

# for the builder component
BuildRequires: fontconfig-devel
BuildRequires: freetype-devel
BuildRequires: pango-devel
BuildRequires: rpm-devel
BuildRequires: sqlite-devel
BuildRequires: gcab

# for the manpages
BuildRequires: libxslt
BuildRequires: docbook-style-xsl

# Make sure we pull in the minimum required versions
Requires: gdk-pixbuf2%{?_isa} >= %{gdk_pixbuf_version}
Requires: glib2%{?_isa} >= %{glib2_version}
Requires: json-glib%{?_isa} >= %{json_glib_version}
Requires: libsoup%{?_isa} >= %{libsoup_version}

# no longer required
Obsoletes: appdata-tools < 0.1.9
Provides: appdata-tools

# this is not a library version
%define as_plugin_version               5

%description
This library provides GObjects and helper methods to make it easy to read and
write AppStream metadata. It also provides a simple DOM implementation that
makes it easy to edit nodes and convert to and from the standardized XML
representation.

%package devel
Summary: GLib Libraries and headers for appstream-glib
Requires: %{name}%{?_isa} = %{version}-%{release}

%description devel
GLib headers and libraries for appstream-glib.

%package builder
Summary: Library and command line tools for building AppStream metadata
Requires: %{name}%{?_isa} = %{version}-%{release}

%description builder
This library and command line tool is used for building AppStream metadata
from a directory of packages.

%package builder-devel
Summary: GLib Libraries and headers for appstream-builder
Requires: %{name}-builder%{?_isa} = %{version}-%{release}

%description builder-devel
GLib headers and libraries for appstream-builder.

%prep
%setup -q -n appstream-glib-%{version}

%build
%configure \
        --enable-gtk-doc \
        --disable-stemmer \
        --disable-dep11 \
        --disable-static \
        --disable-silent-rules \
        --disable-dependency-tracking

make %{?_smp_mflags}

%install
make install DESTDIR=$RPM_BUILD_ROOT

%__rm -f %{buildroot}%{_libdir}/libappstream-glib*.la
%__rm -f %{buildroot}%{_libdir}/libappstream-builder*.la
%__rm -f %{buildroot}%{_libdir}/asb-plugins-%{as_plugin_version}/*.la

%find_lang appstream-glib

%post -p /sbin/ldconfig
%post builder -p /sbin/ldconfig

%postun -p /sbin/ldconfig
%postun builder -p /sbin/ldconfig

%files -f appstream-glib.lang
%license COPYING
%doc README.md AUTHORS NEWS
%{_libdir}/libappstream-glib.so.8*
%{_libdir}/girepository-1.0/*.typelib
%{_bindir}/appstream-util
%{_bindir}/appstream-compose
%dir %{_datadir}/bash-completion/completions/
%{_datadir}/bash-completion/completions/appstream-util
%{_mandir}/man1/appstream-util.1.gz
%{_mandir}/man1/appstream-compose.1.gz

%files devel
%{_libdir}/libappstream-glib.so
%{_libdir}/pkgconfig/appstream-glib.pc
%dir %{_includedir}/libappstream-glib
%{_includedir}/libappstream-glib/*.h
%{_datadir}/gtk-doc/html/appstream-glib
%{_datadir}/gir-1.0/AppStreamGlib-1.0.gir
%{_datadir}/aclocal/*.m4
%{_datadir}/installed-tests/appstream-glib/*.test
%{_datadir}/gettext/its/appdata.its
%{_datadir}/gettext/its/appdata.loc

%files builder
%license COPYING
%{_bindir}/appstream-builder
%{_datadir}/bash-completion/completions/appstream-builder
%{_libdir}/asb-plugins-%{as_plugin_version}/*.so
%{_libdir}/libappstream-builder.so.8*
%{_mandir}/man1/appstream-builder.1.gz

%files builder-devel
%license COPYING
%{_libdir}/libappstream-builder.so
%{_libdir}/pkgconfig/appstream-builder.pc
%dir %{_includedir}/libappstream-builder
%{_includedir}/libappstream-builder/*.h
%{_datadir}/gir-1.0/AppStreamBuilder-1.0.gir

%changelog
* Mon Mar 06 2017 Richard Hughes <richard@hughsie.com> 0.6.10-1
- New upstream release
- Resolves: #1386997

* Thu Feb 02 2017 Kalev Lember <klember@redhat.com> 0.6.8-1
- New upstream release
- Resolves: #1386997

* Sat Nov 01 2014 Richard Hughes <richard@hughsie.com> 0.3.6-1
- Initial import
- Resolves: #1184201

