#ifndef __GOAL_HELPERS_H__
#define __GOAL_HELPERS_H__


#include <gnome.h>


GoalApp* goal_init_and_create(gint argc, gchar **argv);
gboolean load_pixmaps(GoalApp *app);

#endif /* __GOAL_HELPERS_H__ */
