#ifndef __GOAL_CALLBACKS_H__
#define __GOAL_CALLBACKS_H__


#include <gnome.h>


gint goal_exit(gpointer data);
gint menubar_game_menu_exit_item_cb(GtkWidget *widget, gpointer data);
void menubar_help_menu_about_item_cb(GtkWidget *widget, gpointer data);
void new_game_cb(GtkWidget *widget, gpointer data);
gint mainwindow_delete_event_cb(GtkWidget *widget, GdkEvent *event, gpointer data);
gint mainwindow_destroy_cb(GtkWidget *widget, gpointer data);


#endif /* __GOAL_CALLBACKS_H__ */
