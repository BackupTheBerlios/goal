#include <config.h>
#include "callbacks.h"
#include "typedefs.h"
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
		app->gui.ExitMsgBox = gnome_message_box_new(_("Do you really want to quit this game?"),
				GNOME_MESSAGE_BOX_QUESTION,
				GNOME_STOCK_BUTTON_YES,
				GNOME_STOCK_BUTTON_NO,
				NULL);	
		
		gtk_window_set_modal(GTK_WINDOW(app->gui.ExitMsgBox), TRUE);

		gtk_widget_show(app->gui.ExitMsgBox);

		ret = gnome_dialog_run(GNOME_DIALOG(app->gui.ExitMsgBox));

		if(ret) return TRUE;
	}
	
	
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
 * function description: show the about dialog
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
	
	
	app = (GoalApp *) data;

	app->gui.AboutDlg = gnome_about_new("Goal",
			VERSION,
			"(c) 2001 Dietze Sebastian",
			authors,
			_("A Solitaire game for gnome."),
			NULL);

	gtk_window_set_modal(GTK_WINDOW(app->gui.AboutDlg), TRUE);
	
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
		if(ask_finish_game(app)) return ;

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
		if(ask_finish_game(app)) return ;
	
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
		if(ask_finish_game(app)) return ;
	
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
		if(ask_finish_game(app)) return ;

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
		if(ask_finish_game(app)) return ;
	
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
		if(ask_finish_game(app)) return ;
	
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
		if(ask_finish_game(app)) return ;
	
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
		if(ask_finish_game(app)) return ;
	
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

	app->gui.NewGameDlg = gnome_message_box_new("Start a new game?",
			GNOME_MESSAGE_BOX_QUESTION,
			GNOME_STOCK_BUTTON_YES,
			GNOME_STOCK_BUTTON_NO,
			NULL);

	gtk_window_set_modal(GTK_WINDOW(app->gui.NewGameDlg), TRUE);

	gtk_widget_show(app->gui.NewGameDlg);

	ret = gnome_dialog_run(GNOME_DIALOG(app->gui.NewGameDlg));

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
		if(ask_finish_game(app))
			return;
	
	init_new_game(app);
	app->game.GameIsRunning = TRUE;
	app->game.JumpStarted = FALSE;

	if(app->game.GameType == SOLITAIRE)
		app->game.FirstPieceRemoved = FALSE;
	else
		app->game.FirstPieceRemoved = TRUE;

	g_print("new game startet\n");
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
	
	ret = create_theme_list(app);
	
	create_PropertyBox(app);

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
void
property_left_arrow_button_press_event_cb(GtkWidget *widget, gpointer data)
{
	g_print("left\n");
}





/**
 * property_rightt_arrow_button_press_event_cb: 
 * @widget:
 * @data:
 * 
 * function description: 
 *
 * return values: nothing 
 */
void
property_right_arrow_button_press_event_cb(GtkWidget *widget, gpointer data)
{
	g_print("right\n");
}
