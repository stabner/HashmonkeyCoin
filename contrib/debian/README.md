
Debian
====================
This directory contains files used to package hashmonkeycoind/hashmonkeycoin-qt
for Debian-based Linux systems. If you compile hashmonkeycoind/hashmonkeycoin-qt yourself, there are some useful files here.

## raptoreum: URI support ##


hashmonkeycoin-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install hashmonkeycoin-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your hashmonkeycoin-qt binary to `/usr/bin`
and the `../../share/pixmaps/raptoreum128.png` to `/usr/share/pixmaps`

hashmonkeycoin-qt.protocol (KDE)

