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


/* */
typedef struct
{
	gchar *ThemeName,
		*PathToPixmapWallpaper,
		*PathToPixmapPieceNormal,
		*PathToPixmapPieceEmpty,
		*PathToPixmapPieceMarked,
		*PathToPixmapPieceTouched,
		*PathToPixmapPieceNegativ,
		*PathToPixmapPieceEmptyPositiv,
		*PathToPixmapPieceEmptyNegativ;

}GoalTheme;



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
			*ExitMsgBox,
			*GameFinishedMsgBox,
			*PropertyBox,
			*PropertyBoxButtonLeft,
			*PropertyBoxButtonRight,
			*PropertyBoxCanvas,
			*PropertyBoxLabelThemeName;

		GnomeCanvasItem *Wallpaper,
			*PieceNormal[NUMBER_CELLS][NUMBER_CELLS], /* the "normal" piece */
			*PieceEmpty,
			*PieceMarked,         /* the selected piece, with this piece you will jump */
			*PieceTouched,        /* only cosmetic, highlight the piece if no move is selectet */
			*PieceNegativ,        /* you can not jump onto this place */
			*PieceEmptyPositiv,   /* found an empty place, jump !!!!!!! */
			*PieceEmptyNegativ,   /* found an empty place, but you can not jump */
			*PropertyBoxWallpaper /* */,
			*PropertyBoxPieceNormal,
			*PropertyBoxPieceEmpty,
			*PropertyBoxPieceMarked,
			*PropertyBoxPieceTouched,
			*PropertyBoxPieceNegativ,
			*PropertyBoxPieceEmptyPositiv,
			*PropertyBoxPieceEmptyNegativ;
			
			
		gint WallpaperHeight, WallpaperWidth;
		gint PieceHeight, PieceWidth;
	
	} gui;
	
	
	
	/* the game management */
	struct
	{
		gint DefaultThemeNumber;
		gboolean GameIsRunning,
			FirstPieceRemoved,
			JumpStarted,
			ShowBoardHints;
		gint GameType;
		gint MovePosX,
			MovePosY;
		gint JumpStartPosX,
			JumpStartPosY;
		gint CellStatus[NUMBER_CELLS][NUMBER_CELLS];

	} game;


	
	/*  */
	GList *ThemeList;
	gint NumberOfThemes,
		PropertyBoxCurrentThemeNumber;

	
	
} GoalApp;


#endif /* __GOAL_TYPEDEFS_H__ */


