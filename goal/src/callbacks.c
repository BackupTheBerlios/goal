#include <config.h>
#include "callbacks.h"
#include "game.h"
#include "property.h"
#include "helpers.h"


/**
 * goal_exit:
 * 
 * function description:
 *
 * return values: gint
 */
gint
goal_exit(gpointer data)
{
	GoalApp *app;
	gint ret;

	
	app = (GoalApp *) data;

	if(app->game.GameIsRunning)
	{
		app->gui.ExitMsgBox = gtk_message_dialog_new(GTK_WINDOW(app->gui.MainWindow),
				GTK_DIALOG_MODAL,
				GTK_MESSAGE_QUESTION,
				GTK_BUTTONS_YES_NO,
				_("Do you really want to quit this game?"));

		ret = gtk_dialog_run(GTK_DIALOG(app->gui.ExitMsgBox));
		
		gtk_widget_destroy(app->gui.ExitMsgBox);

		if(ret == GTK_RESPONSE_NO) return TRUE;
	}
	
	save_settings(app);
	
	gtk_main_quit();
	
	return TRUE;
		
}

/**
 * menubar_game_menu_exit_item_cb: 
 * @widget: 
 * @data:
 * 
 * function description: call goal_exit
 *
 * return values: gint
 */
gint 
menubar_game_menu_exit_item_cb(GtkWidget *widget, gpointer data)
{

	return goal_exit(data);
	
}


/**
 * mainwindow_destroy_cb: 
 * @widget:
 * @data:
 * 
 * function description: call goal_exit
 *
 * return values: gint 
 */
gint 
mainwindow_destroy_cb(GtkWidget *widget, gpointer data)
{

	return goal_exit(data);
	
}


	
/**
 * mainwindow_delete_event_cb: 
 * @widget:
 * @event: 
 * @data:
 * 
 * function description: call goal_exit
 *
 * return values: gint 
 */
gint
mainwindow_delete_event_cb(GtkWidget *widget, GdkEvent *event, gpointer data)
{


	return goal_exit(data);

}

/**
 * menubar_help_menu_about_cb: 
 * @widget:
 * @data:
 * 
 * function description: shows the about dialog
 *
 * return values: nothing 
 */
void 
menubar_help_menu_about_item_cb(GtkWidget *widget, gpointer data)
{
	GoalApp *app;
	const gchar *authors[] = 
	{
		"Dietze Sebastian <sdietze@freemail.hu>",
		NULL
	};
	const gchar *documenters[] = 
	{
		NULL
	};		
	gchar *translator_credits = _("translator_credits");
	
	app = (GoalApp *) data;

	/* if the AboutDiloag already exists, we get it in the foreground */
	if (app->gui.AboutDlg != NULL)
	{
		gdk_window_raise(app->gui.AboutDlg->window);
	        gdk_window_show (app->gui.AboutDlg->window);
		return;
	}

	/* else creat a new one */
	app->gui.AboutDlg = gnome_about_new("Goal",
			VERSION,
			"(c) 2001,2002 Dietze Sebastian",
			_("A Solitaire game for Gnome."),
			(const char **) authors,
			(const char **)documenters,
			strcmp (translator_credits, "translator_credits") != 0 ? translator_credits : NULL,
			NULL/* we need a very nice logo */);

	g_signal_connect(GTK_OBJECT(app->gui.AboutDlg), "destroy", GTK_SIGNAL_FUNC
		                        (gtk_widget_destroyed), &app->gui.AboutDlg);
	
	gtk_widget_show(app->gui.AboutDlg);
	
}

/**
 * set_game_type_to_cross_cb: 
 * 
 * function description: set game type to cross 
 *
 * return values: nothing 
 */
void
set_game_type_to_cross_cb(GtkWidget *widget, gpointer data)
{
	GoalApp *app;

	app = (GoalApp *) data;


	if(app->game.GameType == CROSS) return;
	
	if(app->game.GameIsRunning)
		if(ask_finish_game(app) == GTK_RESPONSE_NO) return ;

	app->game.GameType = CROSS;
	init_new_game(app);
	app->game.GameIsRunning = TRUE;
	app->game.FirstPieceRemoved = TRUE;
	app->game.JumpStarted = FALSE;

}
/**
 * set_game_type_to_plus_cb: 
 * 
 * function description: set game type to plus
 *
 * return values: nothing 
 */
void 
set_game_type_to_plus_cb(GtkWidget *widget, gpointer data)
{
	GoalApp *app;

	app = (GoalApp *) data;
	

	if(app->game.GameType == PLUS) return;
	
	if(app->game.GameIsRunning)
		if(ask_finish_game(app) == GTK_RESPONSE_NO) return ;
	
	app->game.GameType = PLUS;	
	init_new_game(app);
	app->game.GameIsRunning = TRUE;
	app->game.FirstPieceRemoved = TRUE;
	app->game.JumpStarted = FALSE;

}
/**
 * set_game_type_to_chimney_cb: 
 * 
 * function description: set game type to chimney 
 *
 * return values: nothing 
 */
void 
set_game_type_to_chimney_cb(GtkWidget *widget, gpointer data)
{
	GoalApp *app;

	app = (GoalApp *) data;


	if(app->game.GameType == CHIMNEY) return;
	
	if(app->game.GameIsRunning)
		if(ask_finish_game(app) == GTK_RESPONSE_NO) return ;
	
	app->game.GameType = CHIMNEY;
	init_new_game(app);
	app->game.GameIsRunning = TRUE;
	app->game.FirstPieceRemoved = TRUE;
	app->game.JumpStarted = FALSE;

}
/**
 * set_game_type_to_pyramid_cb: 
 * 
 * function description: set game type to pyramid 
 *
 * return values: nothing 
 */
void set_game_type_to_pyramid_cb(GtkWidget *widget, gpointer data)
{
	GoalApp *app;

	app = (GoalApp *) data;


	if(app->game.GameType == PYRAMID) return;
	
	if(app->game.GameIsRunning)
		if(ask_finish_game(app) == GTK_RESPONSE_NO) return ;

	app->game.GameType = PYRAMID;
	init_new_game(app);
	app->game.GameIsRunning = TRUE;
	app->game.FirstPieceRemoved = TRUE;
	app->game.JumpStarted = FALSE;

}
/**
 * set_game_type_to_arrow_cb: 
 * 
 * function description: set game type to arrow 
 *
 * return values: nothing 
 */
void set_game_type_to_arrow_cb(GtkWidget *widget, gpointer data)
{
	GoalApp *app;

	app = (GoalApp *) data;
	
	
	if(app->game.GameType == ARROW) return;
	
	if(app->game.GameIsRunning)
		if(ask_finish_game(app) == GTK_RESPONSE_NO) return ;
	
	app->game.GameType = ARROW;	
	init_new_game(app);	
	app->game.GameIsRunning = TRUE;
	app->game.FirstPieceRemoved = TRUE;
	app->game.JumpStarted = FALSE;

}
/**
 * set_game_type_to_rubin_cb: 
 * 
 * function description: set game type to rubin 
 *
 * return values: nothing 
 */
void set_game_type_to_rubin_cb(GtkWidget *widget, gpointer data)
{
	GoalApp *app;

	app = (GoalApp *) data;

	if(app->game.GameType == RUBIN) return;
	
	if(app->game.GameIsRunning)
		if(ask_finish_game(app) == GTK_RESPONSE_NO) return ;
	
	app->game.GameType = RUBIN;
	init_new_game(app);
	app->game.GameIsRunning = TRUE;
	app->game.FirstPieceRemoved = TRUE;
	app->game.JumpStarted = FALSE;

}
/**
 * set_game_type_to_diamond_cb: 
 * 
 * function description: set game type to diamond
 *
 * return values: nothing 
 */
void set_game_type_to_diamond_cb(GtkWidget *widget, gpointer data)
{
	GoalApp *app;

	app = (GoalApp *) data;


	if(app->game.GameType == DIAMOND) return;
	
	if(app->game.GameIsRunning)
		if(ask_finish_game(app) == GTK_RESPONSE_NO) return ;
	
	app->game.GameType = DIAMOND;
	init_new_game(app);
	app->game.GameIsRunning = TRUE;
	app->game.FirstPieceRemoved = TRUE;
	app->game.JumpStarted = FALSE;

}
/**
 * set_game_type_to_solitaire_cb:
 * @widget:
 * @data: 
 * 
 * function description: set game type to solitaire
 *
 * return values: nothing 
 */
void 
set_game_type_to_solitaire_cb(GtkWidget *widget, gpointer data)
{
	GoalApp *app;
	
	app = (GoalApp *) data;

	
	if(app->game.GameType == SOLITAIRE) return;
	
	if(app->game.GameIsRunning)
		if(ask_finish_game(app) == GTK_RESPONSE_NO) return ;
	
	app->game.GameType = SOLITAIRE;
	init_new_game(app);	
	app->game.GameIsRunning = TRUE;
	app->game.FirstPieceRemoved = FALSE;
	app->game.JumpStarted = FALSE;

}

/**
 * ask_finish_game:
 * @app: 
 * 
 * function description: set game type to solitaire
 *
 * return values: nothing 
 */
gint
ask_finish_game(GoalApp *app)
{
	
	gint ret;


	app->gui.NewGameDlg = gtk_message_dialog_new(GTK_WINDOW(app->gui.MainWindow),
			GTK_DIALOG_MODAL,
			GTK_MESSAGE_QUESTION,
			GTK_BUTTONS_YES_NO,
			_("Start a new game?"));

	ret = gtk_dialog_run(GTK_DIALOG(app->gui.NewGameDlg));
	gtk_widget_destroy(app->gui.NewGameDlg);

	return ret;
}


/**
 * new_game_cb: 
 * @widget:
 * @data:
 * 
 * function description: start a new game 
 *
 * return values: nothing 
 */
void 
new_game_cb(GtkWidget *widget, gpointer data)
{
	GoalApp *app;

	app = (GoalApp *) data;

	if(app->game.GameIsRunning)
		if(ask_finish_game(app) == GTK_RESPONSE_NO)
			return;
	
	init_new_game(app);
	app->game.GameIsRunning = TRUE;
	app->game.JumpStarted = FALSE;

	if(app->game.GameType == SOLITAIRE)
		app->game.FirstPieceRemoved = FALSE;
	else
		app->game.FirstPieceRemoved = TRUE;


	/* set text to appbar */
	gnome_appbar_set_status(GNOME_APPBAR(app->gui.Appbar), _("New game started."));

	
/*	g_print("new game startet\n");*/
}

/**
 * board_event_cb: 
 * @item:
 * @event:
 * @data:
 * 
 * function description: 
 *
 * return values: nothing 
 */
void
board_event_cb(GnomeCanvasItem *item, GdkEvent *event, gpointer data)
{

	GoalApp *app;
	gint x, y;

	app = (GoalApp *) data;
	
	if(!app->game.GameIsRunning) return;
	
	switch(event->type)
	{

	case GDK_BUTTON_PRESS:
		x = event->button.x / app->gui.PieceWidth; 
		y = event->button.y / app->gui.PieceHeight;
		
		if(app->game.CellStatus[x][y] == UNKOWN) return;
		
		play(app, x, y);
		break;

	case GDK_MOTION_NOTIFY:
		x = event->motion.x / app->gui.PieceWidth; 
		y = event->motion.y / app->gui.PieceHeight;
		
		if(app->game.CellStatus[x][y] == UNKOWN) return;
	
		show_board_hints(app, x, y);

		/*
		 * g_print("motion (X:%i-Y:%i)\n", x, y);
		 */
		break;
	
	default:
		/*
		 * g_print("--==##  OTHER EVENT  ##==--\n");
		 */
		break;
	}
}
	
	
/**
 * toggle_show_board_hints_cb: 
 * @widget:
 * @data:
 * 
 * function description: 
 *
 * return values: nothing 
 */
void 
toggle_show_board_hints_cb(GtkWidget *widget, gpointer data)
{

	GoalApp *app;

	app = (GoalApp *) data;

	app->game.ShowBoardHints = !app->game.ShowBoardHints;

	if(app->game.GameIsRunning)
	{
		if(!app->game.ShowBoardHints)
		{
			gnome_canvas_item_hide(app->gui.PieceNegativ);
			gnome_canvas_item_hide(app->gui.PieceEmptyPositiv);
			gnome_canvas_item_hide(app->gui.PieceEmptyNegativ);
		}
		else
		{
			gnome_canvas_item_hide(app->gui.PieceTouched);
			gnome_canvas_item_hide(app->gui.PieceEmpty);
		}
	}
}


/**
 * menubar_help_menu_properties_item_cb: 
 * @widget:
 * @data:
 * 
 * function description: 
 *
 * return values: nothing 
 */
void
menubar_help_menu_properties_item_cb(GtkWidget *widget, gpointer data)
{
	GoalApp *app;
	gint ret;

	app = (GoalApp *) data;


	app->PropertyBoxCurrentThemeNumber = app->game.DefaultThemeNumber;

	app->PropertyBoxTmpThemeNumber = app->game.DefaultThemeNumber;
	
	/* load the pixmaps and put they into the gnomecanvas */
	if((ret = create_theme_list(app)) != 0)
		g_error(":: PACKAGE: %s :: FILE: %s :: LINE: %i :: error loading theme (ERROR:%i)\n" , PACKAGE, __FILE__, __LINE__, ret);


	create_PropertyBox(app);

	set_arrow_buttons(app);

	/* draw the board in the preview canvas */
	put_theme_to_preview_canvas(app, app->PropertyBoxCurrentThemeNumber);

	gtk_widget_show_all(app->gui.PropertyBox);

}


/**
 * property_left_arrow_button_press_event_cb: 
 * @widget:
 * @data:
 * 
 * function description: 
 *
 * return values: nothing 
 */
/*void
property_left_arrow_button_press_event_cb(GtkWidget *widget, gpointer data)
{

	GoalApp *app;


	app = (GoalApp *) data;

	app->PropertyBoxCurrentThemeNumber--;

	set_arrow_buttons(app);

*/	/* destroy the property box canvas items */
/*	destroy_property_box_canvas_items(app);
*/	
	/*  */ 
/*	put_theme_to_preview_canvas(app, app->PropertyBoxCurrentThemeNumber);
*/

	/* */
/*	gnome_property_box_changed(GNOME_PROPERTY_BOX(app->gui.PropertyBox));
}
*/




/**
 * property_rightt_arrow_button_press_event_cb: 
 * @widget:
 * @data:
 * 
 * function description: 
 *
 * return values: nothing 
 */
/*void
property_right_arrow_button_press_event_cb(GtkWidget *widget, gpointer data)
{
	GoalApp *app;


	app = (GoalApp *) data;

	app->PropertyBoxCurrentThemeNumber++;

	set_arrow_buttons(app);
*/	
	/* destroy the property box canvas items */
/*	destroy_property_box_canvas_items(app);
*/	
	/*  */ 
/*	put_theme_to_preview_canvas(app, app->PropertyBoxCurrentThemeNumber);
*/
	/* */
/*	gnome_property_box_changed(GNOME_PROPERTY_BOX(app->gui.PropertyBox));
}
*/


/**
 * property_box_apply_event_cb:
 * @widget:
 * @page_number:
 * @data:
 *
 * function description:
 *
 * return values:
 */
/*
void 
property_box_apply_event_cb(GtkWidget *widget, gint page_number, gpointer data)
{
	GoalApp *app;
	gint x, y;

	app = (GoalApp *) data;

*/
	/* we have only one property page, thats why we recieve page number 0 and -1, but we only react at -1 */
/*
	if(page_number != -1) return;

*/
	/* update theme number */
/*
	app->game.DefaultThemeNumber = app->PropertyBoxCurrentThemeNumber;
*/
	/* load the pixmaps */	
/*	if(load_pixmaps(app))
	{
			g_warning(":: PACKAGE: %s :: FILE: %s :: LINE: %i :: error loading themes\n" , PACKAGE, __FILE__, __LINE__);
	}

*/	
	/* --- update the gui --- */
	/* hide the "helper" pieces */
/*	gnome_canvas_item_hide(app->gui.PieceEmpty);
	gnome_canvas_item_hide(app->gui.PieceMarked);
	gnome_canvas_item_hide(app->gui.PieceTouched);
	gnome_canvas_item_hide(app->gui.PieceNegativ);
	gnome_canvas_item_hide(app->gui.PieceEmptyPositiv);
	gnome_canvas_item_hide(app->gui.PieceEmptyNegativ);
*/
	/* set important variables */
/*	app->game.JumpStartPosX = 0;
	app->game.JumpStartPosY = 0;
	app->game.MovePosX = 0;
	app->game.MovePosY = 0;
	app->game.JumpStarted = FALSE;
	
	for(x = 0; x < NUMBER_CELLS; x++)
	{
		for(y = 0; y < NUMBER_CELLS; y++)
		{
			if((app->game.CellStatus[x][y] != OCCUPIED) && (app->game.CellStatus[x][y] != UNKOWN))
			{
				gnome_canvas_item_hide(app->gui.PieceNormal[x][y]);
*/				/*g_print("gui update x=%i-y=%i\n",x,y);*/
/*			}

		}
	}


	save_settings(app);
	
}
*/

/**
 * property_box_destroy_event_cb:
 * @property_box:
 * @data:
 *
 * function description:
 *
 * return values: nothing
 */
/*
void 
property_box_destroy_event_cb(GnomeDialog *property_box, gpointer data)
{
	GoalApp *app;

	app = (GoalApp *) data;

*/
	/* destroy theme list */
/*
	delete_theme_list(app);
}
*/



void 
property_box_destroy_event_cb(GtkObject *object, gpointer data)
{
	GoalApp *app;

	app = (GoalApp *) data;

	
	/*g_print("property_box_destroy_event_cb - 0\n");*/
	/* destroy theme list */
	delete_theme_list(app);
}


void 
property_left_arrow_button_clicked_event_cb(GtkButton *button, gpointer data)
{
	GoalApp *app;

	app = (GoalApp *) data;

	
	app->PropertyBoxCurrentThemeNumber--;
	set_arrow_buttons(app);

	/* destroy the property box canvas items */
	destroy_property_box_canvas_items(app);
	/*  */ 
	put_theme_to_preview_canvas(app, app->PropertyBoxCurrentThemeNumber);


	/*g_print("property_left_arrow_button_clicked_event_cb\n");*/
}


void 
property_right_arrow_button_clicked_event_cb(GtkButton *button, gpointer data)
{
	GoalApp *app;

	app = (GoalApp *) data;

	
	app->PropertyBoxCurrentThemeNumber++;
	set_arrow_buttons(app);

	/* destroy the property box canvas items */
	destroy_property_box_canvas_items(app);	
	/*  */ 
	put_theme_to_preview_canvas(app, app->PropertyBoxCurrentThemeNumber);


	/*g_print("property_right_arrow_button_clicked_event_cb\n");*/
}


void 
property_cancel_button_clicked_event_cb(GtkButton *button, gpointer data)
{
	GoalApp *app;

	app = (GoalApp *) data;

	
	/* undo changes */
	if(app->game.DefaultThemeNumber != app->PropertyBoxTmpThemeNumber)
	{
		app->game.DefaultThemeNumber = app->PropertyBoxTmpThemeNumber;
		update_gui(app);		
		save_settings(app);

	}
	

	/* destroy theme list */
	delete_theme_list(app);
	gtk_widget_destroy(app->gui.PropertyBox);
	
	/*g_print("property_cancel_button_clicked_event_cb\n");*/

	
}


void 
property_apply_button_clicked_event_cb(GtkButton *button, gpointer data)
{
	GoalApp *app;

	app = (GoalApp *) data;

	/* update theme number */
	app->game.DefaultThemeNumber = app->PropertyBoxCurrentThemeNumber;
	update_gui(app);
	save_settings(app);

	/*g_print("property_apply_button_clicked_event_cb\n");*/

}


void 
property_ok_button_clicked_event_cb(GtkButton *button, gpointer data)
{
	GoalApp *app;

	app = (GoalApp *) data;

	/* update theme number */
	app->game.DefaultThemeNumber = app->PropertyBoxCurrentThemeNumber;
	update_gui(app);
	save_settings(app);

	/* destroy theme list */
	delete_theme_list(app);
	gtk_widget_destroy(app->gui.PropertyBox);


	/*g_print("property_ok_button_clicked_event_cb\n");*/
}


