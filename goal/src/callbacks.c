#include <config.h>
#include "callbacks.h"
#include "typedefs.h"

/**
 * menubar_game_menu_exit_item_cb: 
 * @widget: 
 * @data:
 * 
 * function description: call gtk_main_quit() to exit goal
 *
 * return values: gint 
 */
gint 
menubar_game_menu_exit_item_cb(GtkWidget *widget, gpointer data)
{

	gtk_main_quit();

	return TRUE;
}


/**
 * mainwindow_delete_event_cb: 
 * @widget:
 * @event: 
 * @data:
 * 
 * function description: call gtk_main_quit() to exit goal (  like menubar_game_menu_exit_item_cb()  )
 *
 * return values: gint 
 */
gint 
mainwindow_delete_event_cb(GtkWidget *widget, GdkEvent *event, gpointer data)
{


	gtk_main_quit();

	return TRUE;

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


	
