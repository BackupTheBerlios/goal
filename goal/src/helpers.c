#include <config.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include <gdk-pixbuf/gnome-canvas-pixbuf.h>
#include "typedefs.h"
#include "helpers.h"
#include "callbacks.h"
#include "property.h"
#include "game.h"


/**
 * make_menus: 
 * @app: the application struct
 * 
 * function description: for internal use only( goal_init_and_create() ), creates the main menu(bar)
 *
 * return values: nothing 
 */
void
make_menus(GoalApp *app)
{

	GnomeUIInfo game_type_subtree [] =
	{
		GNOMEUIINFO_ITEM_DATA(_("Cross"), _("create cross board"), set_game_type_to_cross_cb, app, NULL),
		GNOMEUIINFO_ITEM_DATA(_("Plus"), _("create plus board"), set_game_type_to_plus_cb, app, NULL),
		GNOMEUIINFO_ITEM_DATA(_("Chimney"), _("create chimney board"), set_game_type_to_chimney_cb, app, NULL),
		GNOMEUIINFO_ITEM_DATA(_("Pyramid"), _("create pyramid board"), set_game_type_to_pyramid_cb, app, NULL),
		GNOMEUIINFO_ITEM_DATA(_("Arrow"), _("create arrow board"), set_game_type_to_arrow_cb, app, NULL),
		GNOMEUIINFO_ITEM_DATA(_("Rubin"), _("create rubin board"), set_game_type_to_rubin_cb, app, NULL),
		GNOMEUIINFO_ITEM_DATA(_("Diamond"), _("create diamond board"), set_game_type_to_diamond_cb, app, NULL),
		GNOMEUIINFO_ITEM_DATA(_("Solitaire"), _("create solitaire board"), set_game_type_to_solitaire_cb, app, NULL),
		GNOMEUIINFO_END
	};
	
	GnomeUIInfo menubar_game_menu[] = 
	{
		GNOMEUIINFO_MENU_NEW_GAME_ITEM(new_game_cb, app),
		GNOMEUIINFO_MENU_GAME_TREE(game_type_subtree),
		GNOMEUIINFO_SEPARATOR,
		GNOMEUIINFO_MENU_EXIT_ITEM(menubar_game_menu_exit_item_cb, app),
		GNOMEUIINFO_END
	};
	
	GnomeUIInfo menubar_help_menu[] =
	{
		GNOMEUIINFO_MENU_ABOUT_ITEM(menubar_help_menu_about_item_cb, app),
		GNOMEUIINFO_END
	};

	GnomeUIInfo menubar[] = 
	{
	        GNOMEUIINFO_MENU_GAME_TREE(menubar_game_menu),
		GNOMEUIINFO_MENU_HELP_TREE(menubar_help_menu),
		GNOMEUIINFO_END
	};

	/* install the menus+hints for the application */
	gnome_app_create_menus(GNOME_APP(app->gui.MainWindow), menubar);
	gnome_app_install_menu_hints(GNOME_APP(app->gui.MainWindow), menubar);   
}


/**
 * load_pixmaps:
 * @app: the GoalApp struct, holds the game information 
 * 
 * function description: load the pixmaps into a temp variables (pixbuf)
 *
 * return values: 0 no error happends, NOT 0 error code
 */
gint
load_pixmaps(GoalApp *app)
{	

	gint PNoH, PNoW,
		PMH, PMW,
		PTH, PTW,
		PNeH, PNeW,
		PEPH, PEPW,
		PENH, PENW,
		x,
		y;

	GdkPixbuf *buff;


	/* --- Wallpaper --- */	
	if((buff = gdk_pixbuf_new_from_file(app->settings.PathToPixmapWallpaper)) == NULL)
	{
		return 1;
	};
	/* get height and width, with this info we set the main windows heigth and width */
	app->gui.WallpaperHeight = gdk_pixbuf_get_height(buff);
	app->gui.WallpaperWidth = gdk_pixbuf_get_width(buff);
	
	if(app->gui.Wallpaper) 
		gtk_object_destroy(GTK_OBJECT(app->gui.Wallpaper));
	app->gui.Wallpaper = gnome_canvas_item_new(gnome_canvas_root(GNOME_CANVAS(app->gui.Canvas)),
			gnome_canvas_pixbuf_get_type(),
			"pixbuf", buff,
			"x",0.0,
			"y",0.0,
			NULL);
	/* connect to signal */
	gtk_signal_connect(GTK_OBJECT(app->gui.Wallpaper), "event",
			(GtkSignalFunc)board_event_cb, app);
	
	gdk_pixbuf_unref(buff);	 
	
	/* --- Piece --- */
	if((buff = gdk_pixbuf_new_from_file(app->settings.PathToPixmapPieceNormal)) == NULL)
	{
		return 2;
	}
	app->gui.PieceHeight = gdk_pixbuf_get_height(buff);
	app->gui.PieceWidth = gdk_pixbuf_get_width(buff);

	for(x = 0; x < NUMBER_CELLS; x++)
		for(y = 0; y < NUMBER_CELLS; y++)
			if(app->game.CellStatus[x][y] != UNKOWN)
			{
				/* destroy canvas item if exists */
				if(app->gui.PieceNormal[x][y]) 
					gtk_object_destroy(GTK_OBJECT(app->gui.PieceNormal[x][y]));
				/* create new canvas item*/
				app->gui.PieceNormal[x][y] = gnome_canvas_item_new(gnome_canvas_root(GNOME_CANVAS(app->gui.Canvas)),
					gnome_canvas_pixbuf_get_type(),
					"pixbuf", buff,
					"x",(double)(x * app->gui.PieceWidth),
					"y",(double)(y * app->gui.PieceHeight),
					NULL);
				/* connect canvas item to signal */
				gtk_signal_connect(GTK_OBJECT(app->gui.PieceNormal[x][y]), "event",
					(GtkSignalFunc)board_event_cb, app);
			}
	PNoH = app->gui.PieceHeight;
	PNoW = app->gui.PieceWidth;
	gdk_pixbuf_unref(buff);
	
	/* --- Piece (marked) --- */
	if((buff = gdk_pixbuf_new_from_file(app->settings.PathToPixmapPieceMarked)) == NULL)
	{
		return 3;
	}
	
	if(app->gui.PieceMarked)
		gtk_object_destroy(GTK_OBJECT(app->gui.PieceMarked));
	app->gui.PieceMarked = gnome_canvas_item_new(gnome_canvas_root(GNOME_CANVAS(app->gui.Canvas)),
					gnome_canvas_pixbuf_get_type(),
					"pixbuf", buff,
					"x", 0.0,
					"y", 0.0,
					NULL);
	/* connect canvas item to signal */
	gtk_signal_connect(GTK_OBJECT(app->gui.PieceMarked), "event",
		(GtkSignalFunc)board_event_cb, app);

	gnome_canvas_item_hide(app->gui.PieceMarked);
	
	PMH = gdk_pixbuf_get_height(buff);
	PMW = gdk_pixbuf_get_width(buff);
	gdk_pixbuf_unref(buff);

	/* --- Piece (touched) --- */
	if((buff = gdk_pixbuf_new_from_file(app->settings.PathToPixmapPieceTouched)) == NULL)
	{
		return 4;
	}

	if(app->gui.PieceTouched)
		gtk_object_destroy(GTK_OBJECT(app->gui.PieceTouched));
	app->gui.PieceTouched = gnome_canvas_item_new(gnome_canvas_root(GNOME_CANVAS(app->gui.Canvas)),
			gnome_canvas_pixbuf_get_type(),
			"pixbuf", buff,
			"x", 0.0,
			"y", 0.0,
			NULL);
	gnome_canvas_item_hide(app->gui.PieceTouched);
			
	
	PTH = gdk_pixbuf_get_height(buff);
	PTW = gdk_pixbuf_get_width(buff);
	gdk_pixbuf_unref(buff);

	/* --- Piece (negativ) --- */
	if((buff = gdk_pixbuf_new_from_file(app->settings.PathToPixmapPieceNegativ)) == NULL)
	{
		return 5;
	}
	
	if(app->gui.PieceNegativ)
		gtk_object_destroy(GTK_OBJECT(app->gui.PieceNegativ));
	app->gui.PieceNegativ = gnome_canvas_item_new(gnome_canvas_root(GNOME_CANVAS(app->gui.Canvas)),
			gnome_canvas_pixbuf_get_type(),
			"pixbuf", buff,
			"x", 0.0,
			"y", 0.0,
			NULL);
	gnome_canvas_item_hide(app->gui.PieceNegativ);
					
	PNeH = gdk_pixbuf_get_height(buff);
	PNeW = gdk_pixbuf_get_width(buff);
	gdk_pixbuf_unref(buff);

	
	/* --- Piece (positiv) --- */
	if((buff = gdk_pixbuf_new_from_file(app->settings.PathToPixmapPieceEmptyPositiv)) == NULL)
	{
		return 6;
	}

	if(app->gui.PieceEmptyPositiv)
		gtk_object_destroy(GTK_OBJECT(app->gui.PieceEmptyPositiv));
	app->gui.PieceEmptyPositiv = gnome_canvas_item_new(gnome_canvas_root(GNOME_CANVAS(app->gui.Canvas)),
			gnome_canvas_pixbuf_get_type(),
			"pixbuf", buff,
			"x", 0.0,
			"y", 0.0,
			NULL);
	gnome_canvas_item_hide(app->gui.PieceEmptyPositiv);
			
	PEPH = gdk_pixbuf_get_height(buff);
	PEPW = gdk_pixbuf_get_width(buff);
	gdk_pixbuf_unref(buff);

	
	/* --- */
	if((buff = gdk_pixbuf_new_from_file(app->settings.PathToPixmapPieceEmptyNegativ)) == NULL)
	{
		return 7;
	}

	if(app->gui.PieceEmptyNegativ)
		gtk_object_destroy(GTK_OBJECT(app->gui.PieceEmptyNegativ));
	app->gui.PieceEmptyNegativ = gnome_canvas_item_new(gnome_canvas_root(GNOME_CANVAS(app->gui.Canvas)),
			gnome_canvas_pixbuf_get_type(),
			"pixbuf", buff,
			"x", 0.0,
			"y", 0.0,
			NULL);
	gnome_canvas_item_hide(app->gui.PieceEmptyNegativ);

	
	PENH = gdk_pixbuf_get_height(buff);
	PENW = gdk_pixbuf_get_width(buff);
	gdk_pixbuf_unref(buff);

	
	/* check some important things and give an warning message */
	/* have the other pieces the same width and height like the "normal" piece ?? */
	if((PNoW != PMW) || (PNoW != PTW) || (PNoW != PNeW) || (PNoW != PEPW) || (PNoW != PENW))
		g_warning(":: PACKAGE: %s :: FILE: %s :: LINE: %i :: pieces have not the same width\n" , PACKAGE, __FILE__, __LINE__);
	if((PNoH != PMH) || (PNoH != PTH) || (PNoH != PNeH) || (PNoH != PEPH) || (PNoH != PENH))
		g_warning(":: PACKAGE: %s :: FILE: %s :: LINE: %i :: pieces have not the same height\n" , PACKAGE, __FILE__, __LINE__);
	/* check relations */
	if(app->gui.WallpaperWidth != (NUMBER_CELLS * PNoW))
		g_warning(":: PACKAGE: %s :: FILE: %s :: LINE: %i :: wrong relation between wallpaper width and piece width\n" , PACKAGE, __FILE__, __LINE__);
	if(app->gui.WallpaperHeight != (NUMBER_CELLS * PNoH))
		g_warning(":: PACKAGE: %s :: FILE: %s :: LINE: %i :: wrong relation between wallpaper height and piece height\n" , PACKAGE, __FILE__, __LINE__);

	
	gnome_canvas_set_scroll_region(GNOME_CANVAS(app->gui.Canvas),
		0.0, 0.0,
		app->gui.WallpaperWidth,
		app->gui.WallpaperHeight);
/* FIXME: change to gtk_widget_set_size_request	*/
	gtk_widget_set_usize(app->gui.Canvas,
		app->gui.WallpaperWidth,
		app->gui.WallpaperHeight);
/* FIXME: change gtk_window_set_policy to  gtk_window_set_resizable() */
 	gtk_widget_realize(app->gui.MainWindow);


	
	/* great, no error happends */
	return 0;

}

/**
 * goal_init_and_create: 
 * @argc: like in the main function
 * @argv: like in the main function
 * 
 * function description: create the main window, init some important stuff
 *
 * return values: the created app, holding in GoalApp struct
 */
GoalApp*
goal_init_and_create(gint argc, gchar **argv)
{
GoalApp *app;
gint ret;


	/* request memory for app */
	app = g_malloc(sizeof(GoalApp));

	/* init gnome */
	if(gnome_init(PACKAGE, VERSION, argc, argv) != 0)
		g_error(":: PACKAGE: %s :: FILE: %s :: LINE: %i :: could not init gnome\n" , PACKAGE, __FILE__, __LINE__);


	/* load the settings */
	load_settings(app);
	
	/* create the main window and concect it to signals */
	if((app->gui.MainWindow = gnome_app_new(PACKAGE, "Goal")) == NULL)
		g_error(":: PACKAGE: %s :: FILE: %s :: LINE: %i :: could not create main window\n" , PACKAGE, __FILE__, __LINE__);
	gtk_signal_connect(GTK_OBJECT(app->gui.MainWindow),
			"delete_event",
			GTK_SIGNAL_FUNC(mainwindow_delete_event_cb),
			app);
	gtk_signal_connect(GTK_OBJECT(app->gui.MainWindow),
			"destroy",
			GTK_SIGNAL_FUNC(mainwindow_destroy_cb),
			app);

	/* install the appbar */
	if((app->gui.Appbar = gnome_appbar_new(FALSE, TRUE, GNOME_PREFERENCES_USER)) == NULL)
		g_error(":: PACKAGE: %s :: FILE: %s :: LINE: %i :: could not create appbar\n" , PACKAGE, __FILE__, __LINE__);
	gnome_app_set_statusbar(GNOME_APP(app->gui.MainWindow), app->gui.Appbar);
	
	gtk_widget_show(app->gui.MainWindow);


	/* init the board */
	clear_board(app);

	/* create the canvas and put it into the main window */
	gtk_widget_push_visual(gdk_rgb_get_visual());
	gtk_widget_push_colormap(gdk_rgb_get_cmap());
    	if((app->gui.Canvas = gnome_canvas_new()) == NULL)
		g_error(":: PACKAGE: %s :: FILE: %s :: LINE: %i :: could not create canvas\n" , PACKAGE, __FILE__, __LINE__);
	gtk_widget_pop_colormap();
        gtk_widget_pop_visual();

	gnome_app_set_contents(GNOME_APP(app->gui.MainWindow), app->gui.Canvas);
	gtk_widget_show(app->gui.Canvas);

 	gtk_window_set_policy(GTK_WINDOW(app->gui.MainWindow), FALSE, FALSE, TRUE);

	/* create the main menu */
	make_menus(app);


	/* load the pixmaps and put they into the gnomecanvas */
	if((ret = load_pixmaps(app)) != 0)
		g_error(":: PACKAGE: %s :: FILE: %s :: LINE: %i :: error loading pixmaps (ERROR:%i)\n" , PACKAGE, __FILE__, __LINE__, ret);
	
	/* init the game status to not running */
	app->game.GameIsRunning = FALSE;
	
	return app;
	
}



