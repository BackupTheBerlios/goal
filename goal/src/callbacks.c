#include <config.h>
#include "callbacks.h"
#include "typedefs.h"



/**
 * gaol_exit:
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
		app->gui.ExitMsgBox = gnome_message_box_new(_("Do you really want to end this game?"),
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
		"Dietze Sebastian <jaques@freemail.hu>",
		NULL
	};
	
	
	app = (GoalApp *) data;

	app->gui.AboutDialog = gnome_about_new("Goal",
			VERSION,
			"(c) 2001 Dietze Sebastian",
			authors,
			_("A Solitaire game for gnome."),
			NULL);

	gtk_window_set_modal(GTK_WINDOW(app->gui.AboutDialog), TRUE);
	
	gtk_widget_show(app->gui.AboutDialog);
	
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
	{
		g_print("Game is running\n");
	}
	else
	{
		app->game.GameIsRunning = TRUE;
		g_print("start an new game\n");
	}


	
}

	
	
