## Goal

INCLUDES = \
	-DEXTRA_GNOME_DATA_DIR=\""$(datadir)"\" \
	-DEXTRA_GNOME_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	@EXTRA_GNOME_CFLAGS@


bin_PROGRAMS = goal 

goal_SOURCES = 		\
	main.c          \
	helpers.c       \
	helpers.h	\
	callbacks.c     \
	callbacks.h	\
	property.c 	\
	property.h	\
	game.c		\
	game.h		\
	typedefs.h

goal_LDADD = $(INTLLIBS) @EXTRA_GNOME_LIBS@

