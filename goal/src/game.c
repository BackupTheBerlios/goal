#include <config.h>
#include "game.h"


/**
 * clear_board: 
 * @app: the application struct
 * 
 * function description: mark the fields 
 *
 * return values: nothing 
 */
void
clear_board(GoalApp *app)
{

	gint x, y;

	if(app == NULL) return;

	for (x=0; x<=1; x++)
		for(y=0; y<=1; y++)
			app->game.CellStatus[x][y]       = UNKOWN;
	for (x=5; x<=6; x++)
		for(y=0; y<=1; y++)
			app->game.CellStatus[x][y]       = UNKOWN;

	for (x=0; x<=1; x++)
		for(y=5; y<=6; y++)
			app->game.CellStatus[x][y]       = UNKOWN;
	for (x=5; x<=6; x++)
		for(y=5; y<=6; y++)
			app->game.CellStatus[x][y]       = UNKOWN;

				
	for (x=2; x<=4; x++)
		for(y=0; y<=1; y++)
			app->game.CellStatus[x][y]       = EMPTY;
	for (x=0; x<=6; x++)
		for(y=2; y<=4; y++)
			app->game.CellStatus[x][y]       = EMPTY;
	for (x=2; x<=4; x++)
		for(y=5; y<=6; y++)
			app->game.CellStatus[x][y]       = EMPTY;


}

/**
 * init_new_game: 
 * @app: the application struct
 * 
 * function description: set standart values for each game type
 *
 * return values: nothing 
 */
void init_new_game(GoalApp *app)
{
	
	gint x, y;
	
	switch(app->game.GameType)
	{
		case CROSS :
			clear_board(app); /* clear all */
			app->game.CellStatus[3][1] = OCCUPIED;
			app->game.CellStatus[2][2] = OCCUPIED;
			app->game.CellStatus[3][2] = OCCUPIED;
			app->game.CellStatus[4][2] = OCCUPIED;
			app->game.CellStatus[3][3] = OCCUPIED;
			app->game.CellStatus[3][4] = OCCUPIED;

			gtk_window_set_title(GTK_WINDOW(app->gui.MainWindow), _("Goal - Cross"));
			break;
		
		case PLUS :
			clear_board(app); /* clear all */
			app->game.CellStatus[3][1] = OCCUPIED;
			app->game.CellStatus[1][3] = OCCUPIED;
			app->game.CellStatus[3][2] = OCCUPIED;
			app->game.CellStatus[2][3] = OCCUPIED;
			app->game.CellStatus[3][3] = OCCUPIED;
			app->game.CellStatus[4][3] = OCCUPIED;
			app->game.CellStatus[5][3] = OCCUPIED;
			app->game.CellStatus[3][4] = OCCUPIED;
			app->game.CellStatus[3][5] = OCCUPIED;

			gtk_window_set_title(GTK_WINDOW(app->gui.MainWindow), _("Goal - Plus"));
			break;
			
		case CHIMNEY :
			clear_board(app);/* clear all */
			app->game.CellStatus[2][0] = OCCUPIED;
			app->game.CellStatus[2][1] = OCCUPIED;
			app->game.CellStatus[3][0] = OCCUPIED;
			app->game.CellStatus[3][1] = OCCUPIED;
			app->game.CellStatus[4][0] = OCCUPIED;
			app->game.CellStatus[4][1] = OCCUPIED;
			app->game.CellStatus[2][2] = OCCUPIED;
			app->game.CellStatus[2][3] = OCCUPIED;
			app->game.CellStatus[3][2] = OCCUPIED;
			app->game.CellStatus[4][3] = OCCUPIED;
			app->game.CellStatus[4][2] = OCCUPIED;
			
			gtk_window_set_title(GTK_WINDOW(app->gui.MainWindow), _("Goal - Chimney"));
			break;
			
		case PYRAMID :
			clear_board(app);/* clear all */
			app->game.CellStatus[3][1] = OCCUPIED;
			app->game.CellStatus[2][2] = OCCUPIED;
			app->game.CellStatus[3][2] = OCCUPIED;
			app->game.CellStatus[4][2] = OCCUPIED;
			app->game.CellStatus[1][3] = OCCUPIED;
			app->game.CellStatus[2][3] = OCCUPIED;
			app->game.CellStatus[3][3] = OCCUPIED;
			app->game.CellStatus[0][4] = OCCUPIED;
			app->game.CellStatus[1][4] = OCCUPIED;
			app->game.CellStatus[2][4] = OCCUPIED;
			app->game.CellStatus[3][4] = OCCUPIED;
			app->game.CellStatus[4][4] = OCCUPIED;
			app->game.CellStatus[5][4] = OCCUPIED;
			app->game.CellStatus[6][4] = OCCUPIED;
			app->game.CellStatus[4][3] = OCCUPIED;
			app->game.CellStatus[5][3] = OCCUPIED;
			
			gtk_window_set_title(GTK_WINDOW(app->gui.MainWindow), _("Goal - Pyramid"));
			break;
			
		case ARROW :
			clear_board(app);/* clear all */
			app->game.CellStatus[3][0] = OCCUPIED;
			app->game.CellStatus[2][1] = OCCUPIED;
			app->game.CellStatus[3][1] = OCCUPIED;
			app->game.CellStatus[4][1] = OCCUPIED;
			app->game.CellStatus[1][2] = OCCUPIED;
			app->game.CellStatus[2][2] = OCCUPIED;
			app->game.CellStatus[3][2] = OCCUPIED;
			app->game.CellStatus[4][2] = OCCUPIED;
			app->game.CellStatus[5][2] = OCCUPIED;
			app->game.CellStatus[3][3] = OCCUPIED;
			app->game.CellStatus[3][4] = OCCUPIED;
			app->game.CellStatus[2][5] = OCCUPIED;
			app->game.CellStatus[3][5] = OCCUPIED;
			app->game.CellStatus[4][5] = OCCUPIED;
			app->game.CellStatus[2][6] = OCCUPIED;
			app->game.CellStatus[3][6] = OCCUPIED;
			app->game.CellStatus[4][6] = OCCUPIED;
			
			gtk_window_set_title(GTK_WINDOW(app->gui.MainWindow), _("Goal - Arrow"));
			break;
			
		case RUBIN :
			clear_board(app);/* clear all */
			app->game.CellStatus[3][0] = OCCUPIED;
			app->game.CellStatus[2][1] = OCCUPIED;
			app->game.CellStatus[3][1] = OCCUPIED;
			app->game.CellStatus[4][1] = OCCUPIED;
			app->game.CellStatus[1][2] = OCCUPIED;
			app->game.CellStatus[2][2] = OCCUPIED;
			app->game.CellStatus[3][2] = OCCUPIED;
			app->game.CellStatus[4][2] = OCCUPIED;
			app->game.CellStatus[5][2] = OCCUPIED;
			app->game.CellStatus[2][3] = OCCUPIED;
			app->game.CellStatus[3][3] = OCCUPIED;
			app->game.CellStatus[4][3] = OCCUPIED;
			app->game.CellStatus[1][4] = OCCUPIED;
			app->game.CellStatus[2][4] = OCCUPIED;
			app->game.CellStatus[3][4] = OCCUPIED;
			app->game.CellStatus[4][4] = OCCUPIED;
			app->game.CellStatus[5][4] = OCCUPIED;
			app->game.CellStatus[2][5] = OCCUPIED;
			app->game.CellStatus[3][5] = OCCUPIED;
			app->game.CellStatus[4][5] = OCCUPIED;
			app->game.CellStatus[3][6] = OCCUPIED;

			gtk_window_set_title(GTK_WINDOW(app->gui.MainWindow), _("Goal - Rubin"));
			break;
			
		case DIAMOND :
			clear_board(app);/* clear all */
			app->game.CellStatus[3][0] = OCCUPIED;
			app->game.CellStatus[2][1] = OCCUPIED;
			app->game.CellStatus[3][1] = OCCUPIED;
			app->game.CellStatus[4][1] = OCCUPIED;
			app->game.CellStatus[1][2] = OCCUPIED;
			app->game.CellStatus[2][2] = OCCUPIED;
			app->game.CellStatus[3][2] = OCCUPIED;
			app->game.CellStatus[4][2] = OCCUPIED;
			app->game.CellStatus[5][2] = OCCUPIED;
			app->game.CellStatus[0][3] = OCCUPIED;
			app->game.CellStatus[1][3] = OCCUPIED;
			app->game.CellStatus[2][3] = OCCUPIED;
			app->game.CellStatus[3][3] = OCCUPIED;
			app->game.CellStatus[4][3] = OCCUPIED;
			app->game.CellStatus[5][3] = OCCUPIED;
			app->game.CellStatus[6][3] = OCCUPIED;
			app->game.CellStatus[1][4] = OCCUPIED;
			app->game.CellStatus[2][4] = OCCUPIED;
			app->game.CellStatus[3][4] = OCCUPIED;
			app->game.CellStatus[4][4] = OCCUPIED;
			app->game.CellStatus[5][4] = OCCUPIED;
			app->game.CellStatus[2][5] = OCCUPIED;
			app->game.CellStatus[3][5] = OCCUPIED;
			app->game.CellStatus[4][5] = OCCUPIED;
			app->game.CellStatus[3][6] = OCCUPIED;

			gtk_window_set_title(GTK_WINDOW(app->gui.MainWindow), _("Goal - Diamond"));
			break;
			
		case SOLITAIRE :
			for (x=2; x<=4; x++)
				for(y=0; y<=1; y++)
					app->game.CellStatus[x][y] = OCCUPIED;
			for (x=0; x<=6; x++)
				for(y=2; y<=4; y++)
					app->game.CellStatus[x][y] = OCCUPIED;
			for (x=2; x<=4; x++)
				for(y=5; y<=6; y++)
					app->game.CellStatus[x][y] = OCCUPIED;
			
			gtk_window_set_title(GTK_WINDOW(app->gui.MainWindow), _("Goal - Solitaire"));
			break;

		default:
			g_error(":: PACKAGE: %s :: FILE: %s :: LINE: %i :: unkown game type\n" , PACKAGE, __FILE__, __LINE__);

	}

	/* show pieces */
	for(x = 0; x < NUMBER_CELLS; x++)
		for(y = 0; y < NUMBER_CELLS; y++)
			switch(app->game.CellStatus[x][y])
			{
				case UNKOWN :
					/* with this value we mark not used fields */
				       break;	
				case EMPTY :
					gnome_canvas_item_hide(app->gui.PieceNormal[x][y]);
					break;
				case OCCUPIED :
					gnome_canvas_item_show(app->gui.PieceNormal[x][y]);
					break;
				default:
					g_error(":: PACKAGE: %s :: FILE: %s :: LINE: %i :: wrong status type (x=%i :: y=%i)\n" , PACKAGE, __FILE__, __LINE__, x, y);
			
			}

	/* hide the "helper" pieces */
	gnome_canvas_item_hide(app->gui.PieceMarked);
	gnome_canvas_item_hide(app->gui.PieceTouched);
	gnome_canvas_item_hide(app->gui.PieceNegativ);
	gnome_canvas_item_hide(app->gui.PieceEmptyPositiv);
	gnome_canvas_item_hide(app->gui.PieceEmptyNegativ);

	/* set important variables */
	app->game.JumpStartPosX = 0;
	app->game.JumpStartPosY = 0;
	app->game.MovePosX = 0;
	app->game.MovePosY = 0;

}


/**
 * valid_move:
 * @app:
 * @from_x:
 * @from_y:
 * @to_x:
 * @to_y:
 *
 * function description:
 *
 * return values:
 */
gboolean 
valid_move(GoalApp *app, gint from_x, gint from_y, gint to_x, gint to_y)
{
	
	gint diff;
    

   /* preconditions */
    if((/*on_board(from_x, from_y)*/app->game.CellStatus[from_x][from_y] != UNKOWN) &&
       (/*on_board(to_x, to_y)*/ app->game.CellStatus[to_x][to_y] != UNKOWN) &&
       (/**/app->game.CellStatus[to_x][to_y] == EMPTY) &&
       (/**/app->game.CellStatus[from_x][from_y] == OCCUPIED) &&
       ((from_x == to_x) || (from_y == to_y)))
    {
	if(from_x == to_x)
	{/* here check horizontal move */
	    diff = from_y - to_y;
	    if((diff == 2) || (diff == -2))
	    {
		if(diff == -2) 
			diff = from_y + 1;
		else 
			diff= from_y - 1;
		if(/*board[from_x][diff].status == OCCUPIED*/app->game.CellStatus[from_x][diff] == OCCUPIED) 
			return TRUE;
		else 
			return FALSE;
	    }
	    else 
		    return FALSE;
	}
	else
	{/* here check vertical move */
	    diff = from_x - to_x;
	    if((diff == 2) || (diff == -2))
	    {
		if(diff == -2) 
			diff = from_x + 1;
		else 
			diff= from_x - 1;
		if(/*board[diff][from_y].status == OCCUPIED*/app->game.CellStatus[diff][from_y] == OCCUPIED) 
			return TRUE;
		else 
			return FALSE;
	    }
	    else 
		    return FALSE;
	}
    }
    else
	return FALSE;
}




/**
 * one_move_possible:
 * @app:
 *
 * function description:
 *
 * return values: TRUE if one move is possible, otherwise FALSE
 */
gboolean
one_move_possible(GoalApp *app)
{
	gint x, y;
	
	for(x = 0; x < NUMBER_CELLS; x++)
	{
		for(y = 0; y < NUMBER_CELLS; y++)
		{
			if(valid_move(app, x,y,x+2,y)) return TRUE;
			if(valid_move(app, x,y,x-2,y)) return TRUE;
			if(valid_move(app, x,y,x,y+2)) return TRUE;
			if(valid_move(app, x,y,x,y-2)) return TRUE;
		}
	}
	
	return FALSE;
}



/**
 * remove_piece:
 * @app:
 * @x:
 * @y:
 *
 * function description:
 *
 * return values:
 */
void
remove_piece(GoalApp *app, gint x, gint y)
{
	app->game.CellStatus[x][y] = EMPTY;
	gnome_canvas_item_hide(app->gui.PieceNormal[x][y]);
}



/**
 * make_move:
 * @app:
 * @from_x:
 * @from_y:
 * @to_x:
 * @to_y:
 *
 * function description:
 *
 * return values:
 */
void 
make_move(GoalApp *app, gint from_x, gint from_y, gint to_x, gint to_y){
    gint diff;
    
    /* */
    remove_piece(app, from_x, from_y);
  
    /* */
    app->game.CellStatus[to_x][to_y] = OCCUPIED;
    gnome_canvas_item_show(app->gui.PieceNormal[to_x][to_y]);
    
    if(from_x == to_x)
    {/* horizontal jump */
	diff = from_y - to_y;
	if(diff == -2) diff = from_y + 1;
	else diff = from_y - 1;
	remove_piece(app, from_x, diff);
    }
    else
    {/* vertical jump */
	diff = from_x - to_x;
	if(diff == -2) diff = from_x + 1;
	else diff= from_x - 1;
	remove_piece(app, diff, from_y);
    } 
}



/**
 * valid_move:
 * @app:
 * @x:
 * @y:
 *
 * function description:
 *
 * return values:
 */
void
play(GoalApp *app, gint x, gint y)
{
	
	/* check if app is running in board_event_cb */
	
	if(app->game.FirstPieceRemoved)
	{/* ------------------------------->>>>>>>>>>>>>>>>> on this branch is the real game management */
		if(app->game.JumpStarted)
		{/* we have select a piece, an would like jump now */
			if(valid_move(app, app->game.JumpStartPosX, app->game.JumpStartPosY, x, y))
			{/* great, this is an valid move */
				make_move(app, app->game.JumpStartPosX, app->game.JumpStartPosY, x, y);
			}
			else
			{/* failure */

				gnome_canvas_item_show(app->gui.PieceNormal[app->game.JumpStartPosX][app->game.JumpStartPosY]);
			}
			
			app->game.JumpStarted = FALSE;
			app->game.JumpStartPosX = 0;
			app->game.JumpStartPosY = 0;
			gnome_canvas_item_hide(app->gui.PieceMarked);
					}
		else
		{/* begin a new jump */
			if(app->game.CellStatus[x][y] == OCCUPIED)
			{/* start jump but only if there is an piece */	
				app->game.JumpStarted = TRUE;
				app->game.JumpStartPosX = x;
				app->game.JumpStartPosY = y;			
				gnome_canvas_item_set(app->gui.PieceMarked, 
						"x", (double)(x * app->gui.PieceWidth),
						"y", (double)(y * app->gui.PieceHeight),
						NULL);
				gnome_canvas_item_hide(app->gui.PieceNormal[x][y]);
				gnome_canvas_item_show(app->gui.PieceMarked);
				gnome_canvas_item_hide(app->gui.PieceTouched);

			}
		}

		if(app->game.ShowBoardHints)
		{	
			gnome_canvas_item_hide(app->gui.PieceNegativ);
			gnome_canvas_item_hide(app->gui.PieceEmptyPositiv);
			gnome_canvas_item_hide(app->gui.PieceEmptyNegativ);
		}
	}
	else
	{/* --------------------------------->>>>>>>>>>>>>>>>> only used for "solitaire" game type */
		remove_piece(app, x, y);
		app->game.FirstPieceRemoved = TRUE;
		gnome_canvas_item_hide(app->gui.PieceTouched);
	}


	if(!one_move_possible(app))
	{/* no jump possible, finish this game */
		g_print("game finished\n");
		app->game.GameIsRunning = FALSE;
		app->game.JumpStarted = FALSE;
		app->game.FirstPieceRemoved = FALSE;
	}
}



/**
 * show_board_hints:
 * @app:
 * @x:
 * @y:
 *
 * function description:
 *
 * return values:
 */
void 
show_board_hints(GoalApp *app, gint x, gint y)
{
	if((app->game.MovePosX == x) && (app->game.MovePosY == y)) return;

	
	if(app->game.FirstPieceRemoved)
	{
		if(app->game.JumpStarted)
		{
			if(app->game.ShowBoardHints)
			{
				gnome_canvas_item_hide(app->gui.PieceNegativ);
				gnome_canvas_item_hide(app->gui.PieceEmptyPositiv);
				gnome_canvas_item_hide(app->gui.PieceEmptyNegativ);
			}
		
			if((app->game.JumpStartPosX != x) || (app->game.JumpStartPosY != y))
			{/* else do nothing */g_print("##\n");
				if(app->game.CellStatus[x][y] == OCCUPIED)
				{
					if(app->game.ShowBoardHints)
		  			{
						gnome_canvas_item_set(app->gui.PieceNegativ,
								"x", (double)(x * app->gui.PieceWidth),
						      		"y", (double)(y * app->gui.PieceHeight),
					      			NULL);
						gnome_canvas_item_show(app->gui.PieceNegativ);
					}
					else
					{
						gnome_canvas_item_set(app->gui.PieceTouched, 
							"x", (double)(x * app->gui.PieceWidth),
							"y", (double)(y * app->gui.PieceHeight),
							NULL);
						gnome_canvas_item_show(app->gui.PieceTouched);

					}
				}
				else
				{/* or app->game.CellStatus[x][y] == EMPTY state */
					if(valid_move(app, app->game.JumpStartPosX, app->game.JumpStartPosY, x, y))
			  		{
			  			if(app->game.ShowBoardHints)
		      				{
				  			gnome_canvas_item_set(app->gui.PieceEmptyPositiv, 
						  		"x", (double)(x * app->gui.PieceWidth),
								"y", (double)(y * app->gui.PieceHeight),
						  		NULL);
			    				gnome_canvas_item_show(app->gui.PieceEmptyPositiv);
						}
						else
						{
							gnome_canvas_item_hide(app->gui.PieceTouched);
						}
					}
					else
					{
						if(app->game.ShowBoardHints)
		      				{
			    				gnome_canvas_item_set(app->gui.PieceEmptyNegativ, 
						  		"x", (double)(x * app->gui.PieceWidth),
							  	"y", (double)(y * app->gui.PieceHeight),
						  		NULL);
					    		gnome_canvas_item_show(app->gui.PieceEmptyNegativ);
						}
						else
						{
							gnome_canvas_item_hide(app->gui.PieceTouched);
						}

					}
				}
			}
		}
		else
	      	{/* app->game.JumpStarted */
			if(app->game.CellStatus[x][y] == OCCUPIED)
		  	{
		    		gnome_canvas_item_set(app->gui.PieceTouched, 
					"x", (double)(x * app->gui.PieceWidth),
					"y", (double)(y * app->gui.PieceHeight),
					NULL);
				gnome_canvas_item_show(app->gui.PieceTouched);
			}
			else
		  	{
		    		gnome_canvas_item_hide(app->gui.PieceTouched);
		  	}
		}
	}
	else
	{/* app->game.FirstPieceRemoved */
		gnome_canvas_item_set(app->gui.PieceTouched, 
			"x", (double)(x * app->gui.PieceWidth),
			"y", (double)(y * app->gui.PieceHeight),
			NULL);
		gnome_canvas_item_show(app->gui.PieceTouched);
	}
	
	
	/* store x and y */
	app->game.MovePosX = x;
	app->game.MovePosY = y;
}



