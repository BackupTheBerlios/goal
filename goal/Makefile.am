SUBDIRS = pixmaps src po

schemadir   = @GCONF_SCHEMA_FILE_DIR@
schema_DATA = goal.schemas


EXTRA_DIST = \
    goal.desktop \
    README \
    AUTHORS \
    TODO \
    COPYING \
    $(schema_DATA)
    
Applicationsdir = $(datadir)/gnome/apps/Games
Applications_DATA = goal.desktop

install-data-local:
	GCONF_CONFIG_SOURCE=$(GCONF_SCHEMA_CONFIG_SOURCE) $(GCONFTOOL) --makefile-install-rule $(srcdir)/$(schema_DATA)
	
