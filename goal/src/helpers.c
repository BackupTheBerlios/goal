#include <config.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include <gdk-pixbuf/gnome-canvas-pixbuf.h>
#include "typedefs.h"
#include "helpers.h"
#include "callbacks.h"
#include "property.h"
#include "game.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>


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
	
	gboolean dummy;

	GnomeUIInfo game_type_subtree [] =
	{
		GNOMEUIINFO_ITEM_DATA(N_("Cross"), N_("create cross board"), set_game_type_to_cross_cb, app, NULL),
		GNOMEUIINFO_ITEM_DATA(N_("Plus"), N_("create plus board"), set_game_type_to_plus_cb, app, NULL),
		GNOMEUIINFO_ITEM_DATA(N_("Chimney"), N_("create chimney board"), set_game_type_to_chimney_cb, app, NULL),
		GNOMEUIINFO_ITEM_DATA(N_("Pyramid"), N_("create pyramid board"), set_game_type_to_pyramid_cb, app, NULL),
		GNOMEUIINFO_ITEM_DATA(N_("Arrow"), N_("create arrow board"), set_game_type_to_arrow_cb, app, NULL),
		GNOMEUIINFO_ITEM_DATA(N_("Rubin"), N_("create rubin board"), set_game_type_to_rubin_cb, app, NULL),
		GNOMEUIINFO_ITEM_DATA(N_("Diamond"), N_("create diamond board"), set_game_type_to_diamond_cb, app, NULL),
		GNOMEUIINFO_ITEM_DATA(N_("Solitaire"), N_("create solitaire board"), set_game_type_to_solitaire_cb, app, NULL),
		GNOMEUIINFO_END
	};
	
	GnomeUIInfo menubar_game_menu[] = 
	{
		GNOMEUIINFO_MENU_NEW_GAME_ITEM(new_game_cb, app),
		GNOMEUIINFO_MENU_GAME_TREE(game_type_subtree),
		GNOMEUIINFO_TOGGLEITEM_DATA(N_("Hints"), N_("Show board hints"), toggle_show_board_hints_cb, app, NULL),
		GNOMEUIINFO_SEPARATOR,
		GNOMEUIINFO_MENU_EXIT_ITEM(menubar_game_menu_exit_item_cb, app),
		GNOMEUIINFO_END
	};
	
	GnomeUIInfo menubar_edit_menu[] =
	{
		GNOMEUIINFO_MENU_PROPERTIES_ITEM(menubar_help_menu_properties_item_cb, app),
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
		GNOMEUIINFO_MENU_EDIT_TREE(menubar_edit_menu),
		GNOMEUIINFO_MENU_HELP_TREE(menubar_help_menu),
		GNOMEUIINFO_END
	};

	/* install the menus+hints for the application */
	gnome_app_create_menus(GNOME_APP(app->gui.MainWindow), menubar);
	gnome_app_install_menu_hints(GNOME_APP(app->gui.MainWindow), menubar);   


	/* FIXME: gtk_check_menu_item_set_active call toggle_show_board_hints_cb if state is changed */
	/* set menupoint "hints" */
	dummy = app->game.ShowBoardHints; 
	gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(menubar_game_menu[2].widget), app->game.ShowBoardHints);
	app->game.ShowBoardHints = dummy;
 
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
		PEH, PEW,
		PMH, PMW,
		PTH, PTW,
		PNeH, PNeW,
		PEPH, PEPW,
		PENH, PENW,
		x,
		y;
	GdkPixbuf *buff;
	GoalTheme *theme;

	/* get the given theme (the list ist counting from 0, but we count from 1 thats why -1)*/
	theme = (GoalTheme *) g_list_nth_data(app->ThemeList, app->game.DefaultThemeNumber - 1);

	if(theme == NULL)
	{
		g_warning(":: PACKAGE: %s :: FILE: %s :: LINE: %i :: error getting theme from list\n" , PACKAGE, __FILE__, __LINE__);
		return 2;
	}

	
	/* ---===---===---   load pixmaps into canvas   ---===---===--- */
	/* --- Wallpaper --- */	
	if((buff = gdk_pixbuf_new_from_file(/*app->*/theme->PathToPixmapWallpaper)) == NULL)
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
	if((buff = gdk_pixbuf_new_from_file(/*app->*/theme->PathToPixmapPieceNormal)) == NULL)
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
	

	/* --- Piece (empty) --- */
	if((buff = gdk_pixbuf_new_from_file(theme->PathToPixmapPieceEmpty)) == NULL)
	{
		return 3;
	}
	
	if(app->gui.PieceEmpty)
		gtk_object_destroy(GTK_OBJECT(app->gui.PieceEmpty));
	app->gui.PieceEmpty = gnome_canvas_item_new(gnome_canvas_root(GNOME_CANVAS(app->gui.Canvas)),
					gnome_canvas_pixbuf_get_type(),
					"pixbuf", buff,
					"x", 0.0,
					"y", 0.0,
					NULL);
	/* connect canvas item to signal */
	gtk_signal_connect(GTK_OBJECT(app->gui.PieceEmpty), "event",
		(GtkSignalFunc)board_event_cb, app);

	gnome_canvas_item_hide(app->gui.PieceEmpty);
	
	PEH = gdk_pixbuf_get_height(buff);
	PEW = gdk_pixbuf_get_width(buff);
	gdk_pixbuf_unref(buff);


	/* --- Piece (marked) --- */
	if((buff = gdk_pixbuf_new_from_file(/*app->*/theme->PathToPixmapPieceMarked)) == NULL)
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
	if((buff = gdk_pixbuf_new_from_file(/*app->*/theme->PathToPixmapPieceTouched)) == NULL)
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
	/* connect canvas item to signal */
	gtk_signal_connect(GTK_OBJECT(app->gui.PieceTouched), "event",
		(GtkSignalFunc)board_event_cb, app);

	gnome_canvas_item_hide(app->gui.PieceTouched);
			
	PTH = gdk_pixbuf_get_height(buff);
	PTW = gdk_pixbuf_get_width(buff);
	gdk_pixbuf_unref(buff);

	/* --- Piece (negativ) --- */
	if((buff = gdk_pixbuf_new_from_file(/*app->*/theme->PathToPixmapPieceNegativ)) == NULL)
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
	/* connect canvas item to signal */
	gtk_signal_connect(GTK_OBJECT(app->gui.PieceNegativ), "event",
		(GtkSignalFunc)board_event_cb, app);


	gnome_canvas_item_hide(app->gui.PieceNegativ);
					
	PNeH = gdk_pixbuf_get_height(buff);
	PNeW = gdk_pixbuf_get_width(buff);
	gdk_pixbuf_unref(buff);

	
	/* --- Piece (positiv) --- */
	if((buff = gdk_pixbuf_new_from_file(/*app->*/theme->PathToPixmapPieceEmptyPositiv)) == NULL)
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
	/* connect canvas item to signal */
	gtk_signal_connect(GTK_OBJECT(app->gui.PieceEmptyPositiv), "event",
		(GtkSignalFunc)board_event_cb, app);


	gnome_canvas_item_hide(app->gui.PieceEmptyPositiv);
			
	PEPH = gdk_pixbuf_get_height(buff);
	PEPW = gdk_pixbuf_get_width(buff);
	gdk_pixbuf_unref(buff);

	
	/* --- */
	if((buff = gdk_pixbuf_new_from_file(/*app->*/theme->PathToPixmapPieceEmptyNegativ)) == NULL)
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
	/* connect canvas item to signal */
	gtk_signal_connect(GTK_OBJECT(app->gui.PieceEmptyNegativ), "event",
		(GtkSignalFunc)board_event_cb, app);


	gnome_canvas_item_hide(app->gui.PieceEmptyNegativ);

	
	PENH = gdk_pixbuf_get_height(buff);
	PENW = gdk_pixbuf_get_width(buff);
	gdk_pixbuf_unref(buff);

	
	/* check some important things and give an warning message */
	/* have the other pieces the same width and height like the "normal" piece ?? */
	if((PNoW != PMW) || (PNoW != PTW) || (PNoW != PEW) || (PNoW != PNeW) || (PNoW != PEPW) || (PNoW != PENW))
		g_warning(":: PACKAGE: %s :: FILE: %s :: LINE: %i :: pieces have not the same width\n" , PACKAGE, __FILE__, __LINE__);
	if((PNoH != PMH) || (PNoH != PTH) || (PNoH != PEH) || (PNoH != PNeH) || (PNoH != PEPH) || (PNoH != PENH))
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
/* FIXME: deprecated (change to gtk_widget_set_size_request) */
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
	/* initialize the empty list. */
	app->ThemeList = NULL;

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


	/* --- load the pixmaps and put they into the gnomecanvas --- */
	/* first lad theme list */
	if((ret = create_theme_list(app)) != 0)
		g_error(":: PACKAGE: %s :: FILE: %s :: LINE: %i :: error loading theme (ERROR:%i)\n" , PACKAGE, __FILE__, __LINE__, ret);
	
	/* check the default theme number, if is lesser than 1 or greater than our number of themes then set it to 1 */
	if((app->game.DefaultThemeNumber > app->NumberOfThemes) || (app->game.DefaultThemeNumber < 1))
	{
		g_warning(":: PACKAGE: %s :: FILE: %s :: LINE: %i :: wrong theme number, set theme number to 1\n" , PACKAGE, __FILE__, __LINE__);
		app->game.DefaultThemeNumber = 1;
	}	
	
	if((ret = load_pixmaps(app)) != 0)
		g_error(":: PACKAGE: %s :: FILE: %s :: LINE: %i :: error loading pixmaps (ERROR:%i)\n" , PACKAGE, __FILE__, __LINE__, ret);
	delete_theme_list(app);


	/* appbar hint */
	gnome_appbar_set_status(GNOME_APPBAR(app->gui.Appbar), _("Welcome to Goal"));
	
	/* update the gui but don't start a new one */
	init_new_game(app);
		
	
	/* init the game status to not running */
	app->game.GameIsRunning = FALSE;
	app->game.JumpStarted = FALSE;
	app->game.FirstPieceRemoved = FALSE;

	return app;
	
}


/**
 * load_settings: 
 * @app: the application struct
 * 
 * function description: load the settings
 *
 * return values: void 
 */
void
load_settings(GoalApp *app)
{
	gchar *tmp1;
	

	/* default theme name */
	tmp1 = g_malloc(sizeof(gint) + sizeof("/goal/setting/defaultthemenumber="));
	sprintf(tmp1, "/goal/setting/defaultthemenumber=%i", 1);
	app->game.DefaultThemeNumber = gnome_config_get_int(tmp1);
	g_free(tmp1);
	
	/* gametype */
	tmp1 = g_malloc(sizeof(gint) + sizeof("/goal/setting/gametype="));
	sprintf(tmp1,"/goal/setting/gametype=%i", SOLITAIRE);
	app->game.GameType = gnome_config_get_int(tmp1);
	g_free(tmp1);			
	
	/* board hints */
	tmp1 = g_malloc(sizeof(gint) + sizeof("/goal/setting/showboardhints="));
	sprintf(tmp1,"/goal/setting/showboardhints=%i", FALSE);
	app->game.ShowBoardHints = gnome_config_get_bool(tmp1);
	g_free(tmp1);
	
	/*
	g_print("Goal :: load_seetings\n");
	g_print("DefaultTheme: %i\n", app->game.DefaultThemeNumber);
	g_print("GameType: %i\n", app->game.GameType);
	g_print("ShowBoardHints: %i\n", app->game.ShowBoardHints);
	*/	
}



/**
 * save_settings: 
 * @app: the application struct
 * 
 * function description: load the settings
 *
 * return values: void 
 */
void
save_settings(GoalApp *app)
{
	
	gnome_config_set_int("/goal/setting/defaultthemenumber", app->game.DefaultThemeNumber);

	gnome_config_set_int("/goal/setting/gametype", app->game.GameType);

	gnome_config_set_int("/goal/setting/showboardhints", app->game.ShowBoardHints);
	
	/* write to disk */
	gnome_config_sync();
	
	/*	
	g_print("Goal :: save_seetings\n");
	g_print("DefaultTheme: %i\n", app->game.DefaultThemeNumber);
	g_print("GameType: %i\n", app->game.GameType);
	g_print("ShowBoardHints: %i\n", app->game.ShowBoardHints);	
	*/
}



/**
 * load_theme: 
 * @theme_name:
 * 
 * function description:
 *
 * return values: GoalTheme
 */
GoalTheme* 
load_theme(gchar *path)
{
	GoalTheme *theme = NULL;
	gchar *wallpaper,
		*piece_normal,
		*piece_empty,
		*piece_marked,
		*piece_touched,
		*piece_negativ,
		*piece_empty_positiv,
		*piece_empty_negativ;


	/* concat */
	wallpaper = g_concat_dir_and_file(path, "wallpaper.png");
	piece_normal = g_concat_dir_and_file(path, "piece_normal.png");
	piece_empty = g_concat_dir_and_file(path, "piece_empty.png");
	piece_marked = g_concat_dir_and_file(path, "piece_marked.png");
	piece_touched = g_concat_dir_and_file(path, "piece_touched.png");
	piece_negativ = g_concat_dir_and_file(path, "piece_negativ.png");
	piece_empty_positiv = g_concat_dir_and_file(path, "piece_empty_positiv.png");
	piece_empty_negativ = g_concat_dir_and_file(path, "piece_empty_negativ.png");

	
	
	if(g_file_exists(wallpaper) && g_file_exists(piece_normal)&&
		g_file_exists(piece_marked) && g_file_exists(piece_touched)&&
		g_file_exists(piece_negativ) && g_file_exists(piece_empty_positiv) && 
		g_file_exists(piece_empty_negativ) && g_file_exists(piece_empty))
	{
		theme = g_malloc(sizeof(GoalTheme));
		theme->PathToPixmapWallpaper = wallpaper;
		theme->PathToPixmapPieceNormal = piece_normal;
		theme->PathToPixmapPieceEmpty = piece_empty;
		theme->PathToPixmapPieceMarked = piece_marked;
		theme->PathToPixmapPieceTouched = piece_touched;
		theme->PathToPixmapPieceNegativ = piece_negativ;
		theme->PathToPixmapPieceEmptyPositiv = piece_empty_positiv;
		theme->PathToPixmapPieceEmptyNegativ = piece_empty_negativ;
		/*g_print("--->>> %s\n", path);*/
	}
	else
	{
		g_free(wallpaper);
		g_free(piece_normal);
		g_free(piece_empty);
		g_free(piece_marked);
		g_free(piece_touched);
		g_free(piece_negativ);
		g_free(piece_empty_positiv);
		g_free(piece_empty_negativ);
		g_warning(":: PACKAGE: %s :: FILE: %s :: LINE: %i :: error loading theme :: theme not found in %s\n" , PACKAGE, __FILE__, __LINE__, path);
	}

	
	return theme;
}


/**
 * create_theme_list: 
 * @app:
 * 
 * function description:
 *
 * return values: gint
 */
gint
create_theme_list(GoalApp *app)
{
	DIR *dirp;             /* */
	struct dirent *direntp;/* */
	struct stat stat_buff; /* file attributes */
	gchar *theme_path,
		*tmp_path;
	GoalTheme *theme;
		

	theme_path = gnome_unconditional_datadir_file("goal");
	
	
	if((dirp = opendir(theme_path)) == NULL)
	{
		closedir(dirp);
		g_warning(":: PACKAGE: %s :: FILE: %s :: LINE: %i :: opendir failure\n" , PACKAGE, __FILE__, __LINE__);
		return 1;
	}
	
	
	while((direntp = readdir(dirp)) != NULL)
	{
		tmp_path = g_strconcat(theme_path, "/", direntp->d_name, NULL);

		/* get file attributes */
		if(stat(tmp_path, &stat_buff) == -1)
		{
			g_free(tmp_path);
			g_warning(":: PACKAGE: %s :: FILE: %s :: LINE: %i :: stat failure\n" , PACKAGE, __FILE__, __LINE__);
			return 2;
		}
		/* is it an directory ??? */	
		if(S_ISDIR(stat_buff.st_mode))
		{/* found a directory */
			/* ignore "." and ".." */
			if(strcmp(direntp->d_name, ".") && strcmp(direntp->d_name, ".."))
			{
				/* try to load theme */
				if((theme = load_theme(tmp_path)) != NULL)
				{
					theme->ThemeName = g_strdup(direntp->d_name);
					app->ThemeList = g_list_append(app->ThemeList, (gpointer) theme);
				}
			}
		}
	
		g_free(tmp_path);
		
	}
	
	if(closedir(dirp) == -1)
		g_warning(":: PACKAGE: %s :: FILE: %s :: LINE: %i :: closedir failure\n" , PACKAGE, __FILE__, __LINE__);


	g_print("theme list contains %i elements\n", g_list_length(app->ThemeList));

	/* no theme found */
	if(app->ThemeList == NULL)
	{
		g_warning(":: PACKAGE: %s :: FILE: %s :: LINE: %i :: no theme found\n" , PACKAGE, __FILE__, __LINE__);
		return 3;
	}
	else
	{
		app->NumberOfThemes = g_list_length(app->ThemeList);
	}
	
	
	return 0;
}


/**
 * delete_theme_list: 
 * @app:
 * 
 * function description:
 *
 * return values: void
 */
void
delete_theme_list(GoalApp *app)
{
	gboolean found_last = FALSE;
	GoalTheme *theme;
	GList *tmp_tlist;

	
	tmp_tlist = app->ThemeList;
	if(tmp_tlist != NULL) /* e.g. not empty */
	{
		/* free list items */
		while(!found_last)
		{
			theme = (GoalTheme *) tmp_tlist->data;
			g_free(theme->PathToPixmapWallpaper);
			g_free(theme->PathToPixmapPieceNormal);
			g_free(theme->PathToPixmapPieceEmpty);
			g_free(theme->PathToPixmapPieceMarked);
			g_free(theme->PathToPixmapPieceTouched);
			g_free(theme->PathToPixmapPieceNegativ);
			g_free(theme->PathToPixmapPieceEmptyPositiv);
			g_free(theme->PathToPixmapPieceEmptyNegativ);
		
			g_free(theme);
			
			tmp_tlist = g_list_next(tmp_tlist);
			if(tmp_tlist == NULL) found_last = TRUE;
		}


		/* free the list */

		g_list_free(app->ThemeList);
	}


	app->ThemeList = NULL;
}


/**
 * put_theme_to_preview_canvas: 
 * @app:
 * @theme_number:
 * 
 * function description:
 *
 * return values: gint
 */
int 
put_theme_to_preview_canvas(GoalApp *app, gint theme_number)
{
	GdkPixbuf *buff,
		*buff_scal;
	GoalTheme *theme = NULL;
	gint height,
		width,
		height_bg,
		width_bg,
		prev_h = 350,
		prev_w = 350;
	gfloat height_scale = 2.0,
		width_scale = 2.0;
	gchar *theme_name;
	
	
	/* */
	if((theme_number < 1) || (theme_number > app->NumberOfThemes))
	{
		g_warning(":: PACKAGE: %s :: FILE: %s :: LINE: %i :: unkown theme number\n" , PACKAGE, __FILE__, __LINE__);
		return 1;
	}
	

	/* get the given theme (the list ist counting from 0, but we count from 1 thats why -1)*/
	theme = (GoalTheme *) g_list_nth_data(app->ThemeList, theme_number - 1);

	if(theme == NULL)
	{
		g_warning(":: PACKAGE: %s :: FILE: %s :: LINE: %i :: error getting theme from list\n" , PACKAGE, __FILE__, __LINE__);
		return 2;
	}


	/* ---===---===---   load pixmaps into canvas   ---===---===--- */
	/* --- Wallpaper --- */	
	if((buff = gdk_pixbuf_new_from_file(theme->PathToPixmapWallpaper)) == NULL)
	{
		return 1;
	};
	
	/* get scale factor */
	height_scale = (gfloat) prev_h / gdk_pixbuf_get_height(buff);
	width_scale = (gfloat) prev_w / gdk_pixbuf_get_width(buff);
	
	/* get height and width */
	height_bg = (gint) gdk_pixbuf_get_height(buff) * height_scale;
	width_bg = (gint) gdk_pixbuf_get_width(buff) * width_scale;
	
	/* scalling */
	buff_scal = gdk_pixbuf_scale_simple(buff, width_bg, height_bg, GDK_INTERP_NEAREST);

	/* */
	app->gui.PropertyBoxWallpaper = gnome_canvas_item_new(gnome_canvas_root(GNOME_CANVAS(app->gui.PropertyBoxCanvas)),
			gnome_canvas_pixbuf_get_type(),
			"pixbuf", buff_scal,
			"x",0.0,
			"y",0.0,
			NULL);
	/* connect to signal */
/*	gtk_signal_connect(GTK_OBJECT(app->gui.Wallpaper), "event",
			(GtkSignalFunc)board_event_cb, app);*/
	
	gdk_pixbuf_unref(buff);	 
	gdk_pixbuf_unref(buff_scal);	 
	
	/* --- Piece (normal) --- */
	if((buff = gdk_pixbuf_new_from_file(theme->PathToPixmapPieceNormal)) == NULL)
	{
		return 3;
	}
	
	/* get height and width */
	height = (gint) gdk_pixbuf_get_height(buff) * height_scale;
	width = (gint) gdk_pixbuf_get_width(buff) * width_scale;

	/* scalling */
	buff_scal = gdk_pixbuf_scale_simple(buff, width, height, GDK_INTERP_NEAREST);
	
	app->gui.PropertyBoxPieceNormal = gnome_canvas_item_new(gnome_canvas_root(GNOME_CANVAS(app->gui.PropertyBoxCanvas)),
			gnome_canvas_pixbuf_get_type(),
			"pixbuf", buff_scal,
			"x", (double) 0 * width,
			"y", (double) 3 * height,
			NULL);
	
	gdk_pixbuf_unref(buff);
	gdk_pixbuf_unref(buff_scal);


	/* --- Piece (empty) --- */
	if((buff = gdk_pixbuf_new_from_file(theme->PathToPixmapPieceEmpty)) == NULL)
	{
		return 3;
	}
	
	/* get height and width */
	height = (gint) gdk_pixbuf_get_height(buff) * height_scale;
	width = (gint) gdk_pixbuf_get_width(buff) * width_scale;

	/* scalling */
	buff_scal = gdk_pixbuf_scale_simple(buff, width, height, GDK_INTERP_NEAREST);
	
	app->gui.PropertyBoxPieceEmpty = gnome_canvas_item_new(gnome_canvas_root(GNOME_CANVAS(app->gui.PropertyBoxCanvas)),
			gnome_canvas_pixbuf_get_type(),
			"pixbuf", buff_scal,
			"x", (double) 1 * width,
			"y", (double) 3 * height,
			NULL);
	
	gdk_pixbuf_unref(buff);
	gdk_pixbuf_unref(buff_scal);


	
	/* --- Piece (marked) --- */
	if((buff = gdk_pixbuf_new_from_file(theme->PathToPixmapPieceMarked)) == NULL)
	{
		return 3;
	}
	
	/* get height and width */
	height = (gint) gdk_pixbuf_get_height(buff) * height_scale;
	width = (gint) gdk_pixbuf_get_width(buff) * width_scale;

	/* scalling */
	buff_scal = gdk_pixbuf_scale_simple(buff, width, height, GDK_INTERP_NEAREST);
	
	app->gui.PropertyBoxPieceMarked = gnome_canvas_item_new(gnome_canvas_root(GNOME_CANVAS(app->gui.PropertyBoxCanvas)),
			gnome_canvas_pixbuf_get_type(),
			"pixbuf", buff_scal,
			"x", (double) 2 * width,
			"y", (double) 3 * height,
			NULL);
	
	gdk_pixbuf_unref(buff);
	gdk_pixbuf_unref(buff_scal);

	/* --- Piece (touched) --- */
	if((buff = gdk_pixbuf_new_from_file(theme->PathToPixmapPieceTouched)) == NULL)
	{
		return 3;
	}
	
	/* get height and width */
	height = (gint) gdk_pixbuf_get_height(buff) * height_scale;
	width = (gint) gdk_pixbuf_get_width(buff) * width_scale;

	/* scalling */
	buff_scal = gdk_pixbuf_scale_simple(buff, width, height, GDK_INTERP_NEAREST);
	
	app->gui.PropertyBoxPieceTouched = gnome_canvas_item_new(gnome_canvas_root(GNOME_CANVAS(app->gui.PropertyBoxCanvas)),
			gnome_canvas_pixbuf_get_type(),
			"pixbuf", buff_scal,
			"x", (double) 3 * width,
			"y", (double) 3 * height,
			NULL);
	
	gdk_pixbuf_unref(buff);
	gdk_pixbuf_unref(buff_scal);

	/* --- Piece (negativ) --- */
	if((buff = gdk_pixbuf_new_from_file(theme->PathToPixmapPieceNegativ)) == NULL)
	{
		return 3;
	}
	
	/* get height and width */
	height = (gint) gdk_pixbuf_get_height(buff) * height_scale;
	width = (gint) gdk_pixbuf_get_width(buff) * width_scale;

	/* scalling */
	buff_scal = gdk_pixbuf_scale_simple(buff, width, height, GDK_INTERP_NEAREST);
	
	app->gui.PropertyBoxPieceNegativ = gnome_canvas_item_new(gnome_canvas_root(GNOME_CANVAS(app->gui.PropertyBoxCanvas)),
			gnome_canvas_pixbuf_get_type(),
			"pixbuf", buff_scal,
			"x", (double) 4 * width,
			"y", (double) 3 * height,
			NULL);
	
	gdk_pixbuf_unref(buff);
	gdk_pixbuf_unref(buff_scal);


	/* --- Piece (empty positiv) --- */
	if((buff = gdk_pixbuf_new_from_file(theme->PathToPixmapPieceEmptyPositiv)) == NULL)
	{
		return 3;
	}
	
	/* get height and width */
	height = (gint) gdk_pixbuf_get_height(buff) * height_scale;
	width = (gint) gdk_pixbuf_get_width(buff) * width_scale;

	/* scalling */
	buff_scal = gdk_pixbuf_scale_simple(buff, width, height, GDK_INTERP_NEAREST);
	
	app->gui.PropertyBoxPieceEmptyPositiv = gnome_canvas_item_new(gnome_canvas_root(GNOME_CANVAS(app->gui.PropertyBoxCanvas)),
			gnome_canvas_pixbuf_get_type(),
			"pixbuf", buff_scal,
			"x", (double) 5 * width,
			"y", (double) 3 * height,
			NULL);
	
	gdk_pixbuf_unref(buff);
	gdk_pixbuf_unref(buff_scal);

	/* --- Piece (empty negativ) --- */
	if((buff = gdk_pixbuf_new_from_file(theme->PathToPixmapPieceEmptyNegativ)) == NULL)
	{
		return 3;
	}
	
	/* get height and width */
	height = (gint) gdk_pixbuf_get_height(buff) * height_scale;
	width = (gint) gdk_pixbuf_get_width(buff) * width_scale;

	/* scalling */
	buff_scal = gdk_pixbuf_scale_simple(buff, width, height, GDK_INTERP_NEAREST);
	
	app->gui.PropertyBoxPieceEmptyNegativ = gnome_canvas_item_new(gnome_canvas_root(GNOME_CANVAS(app->gui.PropertyBoxCanvas)),
			gnome_canvas_pixbuf_get_type(),
			"pixbuf", buff_scal,
			"x", (double) 6 * width,
			"y", (double) 3 * height,
			NULL);
	
	gdk_pixbuf_unref(buff);
	gdk_pixbuf_unref(buff_scal);


	/* ------ put the theme name in the theme name label ------ */
	theme_name = g_strdup_printf("%s - (%i/%i)", theme->ThemeName, app->PropertyBoxCurrentThemeNumber, app->NumberOfThemes);
	gtk_label_set_text(GTK_LABEL(app->gui.PropertyBoxLabelThemeName), theme_name);
	g_free(theme_name);
	
	/* finisching touches */
	gnome_canvas_set_scroll_region(GNOME_CANVAS(app->gui.PropertyBoxCanvas),
		0.0, 0.0,
		width_bg,
		height_bg);
	/* FIXME: deprecated (change to gtk_widget_set_size_request) */
	gtk_widget_set_usize(app->gui.PropertyBoxCanvas,
		width_bg,
		height_bg);
	/* FIXME: change gtk_window_set_policy to  gtk_window_set_resizable() */
 	gtk_widget_realize(app->gui.PropertyBox);


	
	/* great, no error happends */
	return 0;


}


/**
 * set_arrow_buttons:
 * @app:
 *
 * function description:
 *
 * return values: nothing
 */
void
set_arrow_buttons(GoalApp *app)
{

	/* set the left arrow button */	
	if((app->PropertyBoxCurrentThemeNumber > 1) && (app->NumberOfThemes > 1))
		gtk_widget_set_sensitive(app->gui.PropertyBoxButtonLeft, TRUE);
	else
		gtk_widget_set_sensitive(app->gui.PropertyBoxButtonLeft, FALSE);
	
	
	/* set the right arrow sensitive */
	if((app->PropertyBoxCurrentThemeNumber < app->NumberOfThemes) && (app->NumberOfThemes > 1))
		gtk_widget_set_sensitive(app->gui.PropertyBoxButtonRight, TRUE);
	else
		gtk_widget_set_sensitive(app->gui.PropertyBoxButtonRight, FALSE);

	
}

/**
 * destroy_property_box_canvas_items:
 * @app:
 * 
 * function description:
 *
 * return values: nothing
 */
void
destroy_property_box_canvas_items(GoalApp *app)
{

	gtk_object_destroy(GTK_OBJECT(app->gui.PropertyBoxWallpaper));
	gtk_object_destroy(GTK_OBJECT(app->gui.PropertyBoxPieceNormal));
	gtk_object_destroy(GTK_OBJECT(app->gui.PropertyBoxPieceEmpty));
	gtk_object_destroy(GTK_OBJECT(app->gui.PropertyBoxPieceMarked));
	gtk_object_destroy(GTK_OBJECT(app->gui.PropertyBoxPieceTouched));
	gtk_object_destroy(GTK_OBJECT(app->gui.PropertyBoxPieceNegativ));
	gtk_object_destroy(GTK_OBJECT(app->gui.PropertyBoxPieceEmptyNegativ));
	gtk_object_destroy(GTK_OBJECT(app->gui.PropertyBoxPieceEmptyPositiv));

				
}


