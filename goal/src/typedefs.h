#ifndef __GOAL_TYPEDEFS_H__
#define __GOAL_TYPEDEFS_H__


#include <gnome.h>


typedef struct
{
	/* the gui objects */
	struct
	{
		GtkWidget *MainWindow,
			*Appbar,
			*AboutDialog,
			*Canvas;
	} gui;

	/* flags */
	gboolean GameIsRunning;


	/* setting variables */
	struct
	{
		gchar *PathToPixmapWallpaper,
			*PathToPixmapPiece;	
	} settings;

	
} GoalApp;


/* which kind of games we have */
enum GameType
{
	CROSS = 0,
	PLUS,
	CHIMNEY,
	PYRAMID,
	ARROW,
	RUBIN,
	DIAMOND,
	SOLITAIRE
};


#endif /* __GOAL_TYPEDEFS_H__ */
