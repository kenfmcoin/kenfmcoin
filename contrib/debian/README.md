
Debian
====================
This directory contains files used to package kenfmcoind/kenfmcoin-qt
for Debian-based Linux systems. If you compile kenfmcoind/kenfmcoin-qt yourself, there are some useful files here.

## kenfmcoin: URI support ##


kenfmcoin-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install kenfmcoin-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your kenfmcoin-qt binary to `/usr/bin`
and the `../../share/pixmaps/kenfmcoin128.png` to `/usr/share/pixmaps`

kenfmcoin-qt.protocol (KDE)

