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
	
	/* piece pixmap */	
	tmp1 = g_strconcat("goal/", "piece.png", NULL);
	filename = gnome_unconditional_pixmap_file(tmp1);
	tmp2 = g_strconcat("/goal/pieceicon/filename=", filename, NULL);
	app->settings.PathToPixmapPiece = gnome_config_get_string(tmp2); 
	g_free(tmp1);
	g_free(tmp2);
	g_free(filename);
	/* wallpaper pixmap */	
	tmp1 = g_strconcat("goal/", "wallpaper.png", NULL);
	filename = gnome_unconditional_pixmap_file(tmp1);
	tmp2 = g_strconcat("/goal/wallpaper/filename=", filename, NULL);
	app->settings.PathToPixmapWallpaper = gnome_config_get_string(tmp2); 
	g_free(tmp1);
	g_free(tmp2);
	g_free(filename);

	
	g_print("load: %s\n", app->settings.PathToPixmapPiece);
	g_print("load: %s\n", app->settings.PathToPixmapWallpaper);
	
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
	
	return app;
	
}



