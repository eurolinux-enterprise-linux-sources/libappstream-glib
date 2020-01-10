Summary:   Library for AppStream metadata
Name:      libappstream-glib
Version:   0.3.6
Release:   1%{?dist}
License:   LGPLv2+
URL:       http://people.freedesktop.org/~hughsient/appstream-glib/
Source0:   http://people.freedesktop.org/~hughsient/appstream-glib/releases/appstream-glib-%{version}.tar.xz

BuildRequires: glib2-devel >= 2.16.1
BuildRequires: libtool
BuildRequires: docbook-utils
BuildRequires: gtk-doc
BuildRequires: gobject-introspection-devel
BuildRequires: gperf
BuildRequires: libarchive-devel
BuildRequires: libsoup-devel
BuildRequires: gdk-pixbuf2-devel
BuildRequires: gtk3-devel
BuildRequires: gettext
BuildRequires: intltool

# for the builder component
BuildRequires: fontconfig-devel
BuildRequires: freetype-devel
BuildRequires: pango-devel
BuildRequires: rpm-devel
BuildRequires: sqlite-devel

# for the manpages
BuildRequires: libxslt
BuildRequires: docbook-style-xsl

# no longer required
Obsoletes: appdata-tools < 0.1.9
Provides: appdata-tools

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

%prep
%setup -q -n appstream-glib-%{version}

%build
%configure \
        --enable-gtk-doc \
        --disable-builder \
        --disable-dep11 \
        --disable-static \
        --disable-silent-rules \
        --disable-dependency-tracking

make %{?_smp_mflags}

%install
make install DESTDIR=$RPM_BUILD_ROOT

%__rm -f %{buildroot}%{_libdir}/libappstream*.la
%__rm -f %{buildroot}%{_libdir}/asb-plugins/*.la

%find_lang appstream-glib

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig

%files -f appstream-glib.lang
%doc README.md AUTHORS NEWS COPYING
%{_libdir}/libappstream-glib.so.7*
%{_libdir}/girepository-1.0/*.typelib
%{_bindir}/appstream-util
%{_bindir}/appdata-validate
%dir %{_datadir}/bash-completion/completions/
%{_datadir}/bash-completion/completions/appstream-util
%{_mandir}/man1/appstream-util.1.gz

%files devel
%{_libdir}/libappstream-glib.so
%{_libdir}/pkgconfig/appstream-glib.pc
%dir %{_includedir}/libappstream-glib
%{_includedir}/libappstream-glib/*.h
%{_datadir}/gtk-doc/html/appstream-glib
%{_datadir}/gir-1.0/AppStreamGlib-1.0.gir
%{_datadir}/aclocal/*.m4
%{_datadir}/installed-tests/appstream-glib/*.test

%changelog
* Sat Nov 01 2014 Richard Hughes <richard@hughsie.com> 0.3.6-1
- Initial import
- Resolves: #1184201

