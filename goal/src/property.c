#include "property.h"

/**
 * load_settings: 
 * @app: the application struct
 * 
 * function description: load the settings
 *
 * return values: nothing 
 */
void
load_settings(GoalApp *app)
{
	gchar *tmp1,
		*tmp2,
		*filename;
		
		
	/* piece pixmap (normal) */	
	tmp1 = g_strconcat("goal/", "piece.png", NULL);
	filename = gnome_unconditional_pixmap_file(tmp1);
	tmp2 = g_strconcat("/goal/pieceicon/filename=", filename, NULL);
	app->settings.PathToPixmapPieceNormal = "../pixmaps/piece_normal.png";/*gnome_config_get_string(tmp2); */
	g_free(tmp1);
	g_free(tmp2);
	g_free(filename);

	/* piece pixmap (marked) */
	app->settings.PathToPixmapPieceMarked = "../pixmaps/piece_marked.png";

	/* piece pixmap (touched) */	
	app->settings.PathToPixmapPieceTouched = "../pixmaps/piece_touched.png";


	/* piece pixmap (negativ) */	
	app->settings.PathToPixmapPieceNegativ = "../pixmaps/piece_negativ.png";
	
	/* piece pixmap (empty positiv) */	
	app->settings.PathToPixmapPieceEmptyPositiv = "../pixmaps/piece_empty_positiv.png";

	/* piece pixmap (emptiy negativ) */	
	app->settings.PathToPixmapPieceEmptyNegativ = "../pixmaps/piece_empty_negativ.png";

	
	/* wallpaper pixmap */	
	tmp1 = g_strconcat("goal/", "wallpaper.png", NULL);
	filename = gnome_unconditional_pixmap_file(tmp1);
	tmp2 = g_strconcat("/goal/wallpaper/filename=", filename, NULL);
	app->settings.PathToPixmapWallpaper = "../pixmaps/wallpaper.png";/*gnome_config_get_string(tmp2);*/ 
	g_free(tmp1);
	g_free(tmp2);
	g_free(filename);
	
	/* gametype */
	tmp1 = g_malloc(sizeof(gint) + sizeof("/goal/gametype="));
	sprintf(tmp1,"/goal/gametype=%i", SOLITAIRE);
	app->game.GameType = gnome_config_get_int(tmp1);
	g_free(tmp1);
	
	g_print("Goal :: load_seetings\n");
	g_print("PathToPixmapWallpaper: %s\n", app->settings.PathToPixmapWallpaper);
	g_print("PathToPixmapPieceNormal: %s\n", app->settings.PathToPixmapPieceNormal);
	g_print("PathToPixmapPieceMarked: %s\n", app->settings.PathToPixmapPieceMarked);
	g_print("PathToPixmapPieceTouched: %s\n", app->settings.PathToPixmapPieceTouched);
	g_print("PathToPixmapPieceNegativ: %s\n", app->settings.PathToPixmapPieceNegativ);
	g_print("PathToPixmapPieceEmptyPositiv: %s\n", app->settings.PathToPixmapPieceEmptyPositiv);
	g_print("PathToPixmapPieceEmptyNegativ: %s\n", app->settings.PathToPixmapPieceEmptyNegativ);
	g_print("GameType: %i\n", app->game.GameType);
	
}


