#include <config.h>
#include "typedefs.h"
#include "helpers.h"
#include "callbacks.h"


/**
 * make_menus: 
 * @app: the application struct
 *
 * 
 * function description: for internal use only( goal_init_and_create() ), creates the main menu(bar)
 *
 * return values: nothing 
 */
void
make_menus(GoalApp *app)
{

	GnomeUIInfo menubar_game_menu[] = 
	{
		GNOMEUIINFO_MENU_NEW_GAME_ITEM(new_game_cb, app), 
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
 * load_settings: 
 * @app: the application struct
 * 
 * function description: load the settings
 *
 * return values: nothing 
 */
void
load_settings(GoalApp *app)
{
	gchar *tmp1,
		*tmp2,
		*filename;
		
		
	/* piece pixmap (normal) */	
	tmp1 = g_strconcat("goal/", "piece.png", NULL);
	filename = gnome_unconditional_pixmap_file(tmp1);
	tmp2 = g_strconcat("/goal/pieceicon/filename=", filename, NULL);
	app->settings.PathToPixmapPieceNormal = "/home/sebastian/projects/goal/pixmaps/piece_normal.png";/*gnome_config_get_string(tmp2); */
	g_free(tmp1);
	g_free(tmp2);
	g_free(filename);

	/* piece pixmap (marked) */
	app->settings.PathToPixmapPieceMarked = "/home/sebastian/projects/goal/pixmaps/piece_marked.png";

	/* piece pixmap (touched) */	
	app->settings.PathToPixmapPieceTouched = "/home/sebastian/projects/goal/pixmaps/piece_touched.png";


	/* piece pixmap (negativ) */	
	app->settings.PathToPixmapPieceNegativ = "/home/sebastian/projects/goal/pixmaps/piece_negativ.png";
	
	/* piece pixmap (empty positiv) */	
	app->settings.PathToPixmapPieceEmptyPositiv = "/home/sebastian/projects/goal/pixmaps/piece_empty_positiv.png";

	/* piece pixmap (emptiy negativ) */	
	app->settings.PathToPixmapPieceEmptyNegativ = "/home/sebastian/projects/goal/pixmaps/piece_empty_negativ.png";

	
	/* wallpaper pixmap */	
	tmp1 = g_strconcat("goal/", "wallpaper.png", NULL);
	filename = gnome_unconditional_pixmap_file(tmp1);
	tmp2 = g_strconcat("/goal/wallpaper/filename=", filename, NULL);
	app->settings.PathToPixmapWallpaper = "/home/sebastian/projects/goal/pixmaps/wallpaper.png";/*gnome_config_get_string(tmp2);*/ 
	g_free(tmp1);
	g_free(tmp2);
	g_free(filename);
	
	/* gametype */
	tmp1 = g_malloc(sizeof(gint) + sizeof("/goal/gametype="));
	sprintf(tmp1,"/goal/gametype=%i", SOLITAIRE);
	app->game.GameType = gnome_config_get_int(tmp1);
	g_free(tmp1);
	
	g_print("Goal :: load_seetings\n");
	g_print("PathToPixmapWallpaper: %s\n", app->settings.PathToPixmapWallpaper);
	g_print("PathToPixmapPieceNormal: %s\n", app->settings.PathToPixmapPieceNormal);
	g_print("PathToPixmapPieceMarked: %s\n", app->settings.PathToPixmapPieceMarked);
	g_print("PathToPixmapPieceTouched: %s\n", app->settings.PathToPixmapPieceTouched);
	g_print("PathToPixmapPieceNegativ: %s\n", app->settings.PathToPixmapPieceNegativ);
	g_print("PathToPixmapPieceEmptyPositiv: %s\n", app->settings.PathToPixmapPieceEmptyPositiv);
	g_print("PathToPixmapPieceEmptyNegativ: %s\n", app->settings.PathToPixmapPieceEmptyNegativ);
	g_print("GameType: %i\n", app->game.GameType);
	
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


	/* request memory for app */
	if((app = g_malloc(sizeof(GoalApp))) == NULL)
		g_error(":: PACKAGE: %s :: FILE: %s :: LINE: %i :: not enough memory for goal\n" , PACKAGE, __FILE__, __LINE__);

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


	/* create the canvas and put it into the main window */
	gtk_widget_push_visual(gdk_rgb_get_visual());
	gtk_widget_push_colormap(gdk_rgb_get_cmap());
    	if((app->gui.Canvas = gnome_canvas_new()) == NULL)
		g_error(":: PACKAGE: %s :: FILE: %s :: LINE: %i :: could not create canvas\n" , PACKAGE, __FILE__, __LINE__);
	gtk_widget_pop_colormap();
        gtk_widget_pop_visual();
	gnome_canvas_set_scroll_region(GNOME_CANVAS(app->gui.Canvas), 0.0, 0.0, 300.0, 300.0);
	gnome_app_set_contents(GNOME_APP(app->gui.MainWindow), app->gui.Canvas);

	/* create the main menu */
	make_menus(app);


	/* init the game status to not running */
	app->game.GameIsRunning = FALSE;
	
	return app;
	
}



