#ifndef __GOAL_HELPERS_H__
#define __GOAL_HELPERS_H__


#include <gnome.h>


GoalApp* goal_init_and_create(gint argc, gchar **argv);
gint load_pixmaps(GoalApp *app);
void load_settings(GoalApp *app);
GoalTheme* load_theme(gchar *theme_name);
gint create_theme_list(GoalApp *app);
void delete_theme_list(GoalApp *app);


#endif /* __GOAL_HELPERS_H__ */
