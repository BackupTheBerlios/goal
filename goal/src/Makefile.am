## Goal

INCLUDES = -I. -I$(srcdir) -I$(srcdir)/../pixmaps			\
	-DGNOMELOCALEDIR=\""$(datadir)/locale"\" \
	-I$(includedir) $(GNOME_INCLUDEDIR)

bin_PROGRAMS = goal 

goal_SOURCES = 		\
	main.c          \
	helpers.c       \
	callbacks.c      

goal_LDADD = $(GNOME_LIBDIR) $(GNOMEUI_LIBS) $(INTLLIBS)

#pixmapdir = $(datadir)/pixmaps

#EXTRA_DIST = pharmacy.desktop agent.h checkout.h preferences.h console.h\

