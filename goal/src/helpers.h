#ifndef __GOAL_HELPERS_H__
#define __GOAL_HELPERS_H__


#include <gnome.h>


GoalApp* goal_init_and_create(gint argc, gchar **argv);
gint load_pixmaps(GoalApp *app);
void load_settings(GoalApp *app);
void save_settings(GoalApp *app);
GoalTheme* load_theme(gchar *theme_name);
gint create_theme_list(GoalApp *app);
void delete_theme_list(GoalApp *app);
int put_theme_to_preview_canvas(GoalApp *app, gint theme_number);
void set_arrow_buttons(GoalApp *app);
void destroy_property_box_canvas_items(GoalApp *app);
void update_gui(GoalApp *app);

#endif /* __GOAL_HELPERS_H__ */
