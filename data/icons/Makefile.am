icon_DATA = hextor.png
icondir = $(datadir)/icons/hicolor/48x48/apps

hicolor_DATA = hextor.svg
hicolordir = $(datadir)/icons/hicolor/scalable/apps

UPDATE_ICON_CACHE = gtk-update-icon-cache -f -t $(datadir)/icons/hicolor || :

install-data-hook:
	$(UPDATE_ICON_CACHE);

uninstall-hook:
	$(UPDATE_ICON_CACHE);
