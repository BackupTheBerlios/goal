#ifndef __GOAL_CALLBACKS_H__
#define __GOAL_CALLBACKS_H__


#include <gnome.h>
#include "typedefs.h"

gint goal_exit(gpointer data);
gint menubar_game_menu_exit_item_cb(GtkWidget *widget, gpointer data);
void menubar_help_menu_about_item_cb(GtkWidget *widget, gpointer data);
void new_game_cb(GtkWidget *widget, gpointer data);
gint mainwindow_delete_event_cb(GtkWidget *widget, GdkEvent *event, gpointer data);
gint mainwindow_destroy_cb(GtkWidget *widget, gpointer data);
void board_event_cb(GnomeCanvasItem *item, GdkEvent *event, gpointer data);
void set_game_type_to_cross_cb(GtkWidget *widget, gpointer data);
void set_game_type_to_plus_cb(GtkWidget *widget, gpointer data);
void set_game_type_to_chimney_cb(GtkWidget *widget, gpointer data);
void set_game_type_to_pyramid_cb(GtkWidget *widget, gpointer data);
void set_game_type_to_arrow_cb(GtkWidget *widget, gpointer data);
void set_game_type_to_rubin_cb(GtkWidget *widget, gpointer data);
void set_game_type_to_diamond_cb(GtkWidget *widget, gpointer data);
void set_game_type_to_solitaire_cb(GtkWidget *widget, gpointer data);
gint ask_finish_game(GoalApp *app);
void toggle_show_board_hints_cb(GtkWidget *widget, gpointer data);
void menubar_help_menu_properties_item_cb(GtkWidget *widget, gpointer data);
/*
void property_left_arrow_button_press_event_cb(GtkWidget *widget, gpointer data);
void property_right_arrow_button_press_event_cb(GtkWidget *widget, gpointer data);
void property_box_apply_event_cb(GtkWidget *widget, gint page_number, gpointer data);
void property_box_destroy_event_cb(GnomeDialog *property_box, gpointer data);
*/
void property_box_destroy_event_cb(GtkObject *object, gpointer data);
void property_left_arrow_button_clicked_event_cb(GtkButton *button, gpointer data);
void property_right_arrow_button_clicked_event_cb(GtkButton *button, gpointer data);
void property_cancel_button_clicked_event_cb(GtkButton *button, gpointer data);
void property_apply_button_clicked_event_cb(GtkButton *button, gpointer data);
void property_ok_button_clicked_event_cb(GtkButton *button, gpointer data);

#endif /* __GOAL_CALLBACKS_H__ */
