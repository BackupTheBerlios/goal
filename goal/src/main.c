#include <config.h>
#include <gnome.h>
#include "typedefs.h"
#include "helpers.h"


gint
main(gint argc, gchar **argv)
{
	static GoalApp *app;


	/* i18n */
	bindtextdomain(PACKAGE, GNOMELOCALEDIR);
	textdomain(PACKAGE);

	app = goal_init_and_create(argc, argv);

	gtk_main();
	
	return 0;

}


