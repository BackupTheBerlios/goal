#ifndef __GOAL_GAME_H__
#define __GOAL_GAME_H__

#include <gnome.h>
#include "typedefs.h"


void clear_board(GoalApp *app);
void init_new_game(GoalApp *app);
gboolean valid_move(GoalApp *app, gint from_x, gint from_y, gint to_x, gint to_y);
void play(GoalApp *app, gint x, gint y);
void remove_piece(GoalApp *app, gint x, gint y);
gboolean one_move_possible(GoalApp *app);
void make_move(GoalApp *app, gint from_x, gint from_y, gint to_x, gint to_y);
void show_board_hints(GoalApp *app, gint x, gint y);	


#endif /* __GOAL_GAME_H__ */
