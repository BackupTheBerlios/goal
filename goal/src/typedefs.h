#ifndef __GOAL_TYPEDEFS_H__
#define __GOAL_TYPEDEFS_H__


#include <gnome.h>
#include <gdk-pixbuf/gdk-pixbuf.h>


#define NUMBER_CELLS 7


enum Status
{
	UNKOWN = 0,
	EMPTY,
	OCCUPIED
};

/* which kind of games we have */
enum GameTypes
{
	NOTDEFINED = 0,
	CROSS,
	PLUS,
	CHIMNEY,
	PYRAMID,
	ARROW,
	RUBIN,
	DIAMOND,
	SOLITAIRE
};

/* this struct holds the app */
typedef struct
{


	
	/* the gui objects */
	struct
	{
		GtkWidget *MainWindow,
			*Appbar,
			*AboutDlg,
			*NewGameDlg,
			*Canvas,
			*ExitMsgBox;

		GnomeCanvasItem *Wallpaper,
			*PieceNormal[NUMBER_CELLS][NUMBER_CELLS], /* the "normal" piece */
			*PieceMarked,         /* the selected piece, with this piece you will jump */
			*PieceTouched,        /* only cosmetic, highlight the piece if no move is selectet */
			*PieceNegativ,        /* you can not jump onto this place */
			*PieceEmptyPositiv,   /* found an empty place, jump !!!!!!! */
			*PieceEmptyNegativ;   /* found an empty place, but you can not jump */
			
			
		gint WallpaperHeight, WallpaperWidth;
		gint PieceHeight, PieceWidth;
	
	} gui;
	
	
	
	/* the game management */
	struct
	{
		gboolean GameIsRunning,
			FirstPieceRemoved,
			JumpStarted;
		gint GameType,
			JumpStartPosX,
			JumpStartPosY;
		gint CellStatus[NUMBER_CELLS][NUMBER_CELLS];

	} game;


	
	/* setting variables */
	struct
	{
		gchar *PathToPixmapWallpaper,
			*PathToPixmapPieceNormal,
			*PathToPixmapPieceMarked,
			*PathToPixmapPieceTouched,
			*PathToPixmapPieceNegativ,
			*PathToPixmapPieceEmptyPositiv,
			*PathToPixmapPieceEmptyNegativ;
	} settings;

	
	
} GoalApp;


#endif /* __GOAL_TYPEDEFS_H__ */


