#include <config.h>
#include <gnome.h>
#include "typedefs.h"
#include "helpers.h"


gint
main(gint argc, gchar **argv)
{
	static GoalApp *app;


	/* i18n */
	/*bindtextdomain(PACKAGE, GNOMELOCALEDIR);
	textdomain(PACKAGE);*/
#ifdef ENABLE_NLS
	bindtextdomain(PACKAGE, EXTRA_GNOME_LOCALE_DIR);
	bind_textdomain_codeset(PACKAGE, "UTF-8");
	textdomain(PACKAGE);
#endif


	app = goal_init_and_create(argc, argv);

	gtk_main();
	
	return 0;

}


