#include <gdk-pixbuf/gdk-pixbuf.h>
#include <gdk-pixbuf/gnome-canvas-pixbuf.h>
#include "property.h"
#include "callbacks.h"





/**
 * create_PropertyBox: 
 * @app: the application struct
 * 
 * function description: 
 *
 * return values: nothing 
 */
void
create_PropertyBox(GoalApp *app)
{
  
	
	GtkWidget *NotebookTheme;
	GtkWidget *hbox1;
	GtkWidget *vbox1;
	GtkWidget *hbox2;
	GtkWidget *ArrowLeft;
	/*GtkWidget *LabelThemeName;*/
	GtkWidget *ArrowRight;
	GtkWidget *scrolledwindow1;
	GtkWidget *LabelTheme;


	/* --- property box --- */
	app->gui.PropertyBox = gnome_property_box_new ();
	gtk_widget_set_name (app->gui.PropertyBox, "PropertyBox");
	gtk_object_set_data (GTK_OBJECT (app->gui.PropertyBox), "PropertyBox", app->gui.PropertyBox);
	gtk_window_set_title (GTK_WINDOW (app->gui.PropertyBox), _("Goal - theme selector"));
	gtk_window_set_modal (GTK_WINDOW (app->gui.PropertyBox), TRUE);
	
	NotebookTheme = GNOME_PROPERTY_BOX (app->gui.PropertyBox)->notebook;
	gtk_widget_set_name (NotebookTheme, "NotebookTheme");
	gtk_object_set_data (GTK_OBJECT (app->gui.PropertyBox), "NotebookTheme", NotebookTheme);
	gtk_widget_show (NotebookTheme);
	
	hbox1 = gtk_hbox_new (FALSE, 0);
	gtk_widget_set_name (hbox1, "hbox1");
	gtk_widget_ref (hbox1);
	gtk_object_set_data_full (GTK_OBJECT (app->gui.PropertyBox), "hbox1", hbox1,
			(GtkDestroyNotify) gtk_widget_unref);
	gtk_widget_show (hbox1);
	gtk_container_add (GTK_CONTAINER (NotebookTheme), hbox1);

	vbox1 = gtk_vbox_new (FALSE, 0);
	gtk_widget_set_name (vbox1, "vbox1");
	gtk_widget_ref (vbox1);
  gtk_object_set_data_full (GTK_OBJECT (app->gui.PropertyBox), "vbox1", vbox1,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (vbox1);
  gtk_box_pack_start (GTK_BOX (hbox1), vbox1, TRUE, TRUE, 0);

  hbox2 = gtk_hbox_new (FALSE, 0);
  gtk_widget_set_name (hbox2, "hbox2");
  gtk_widget_ref (hbox2);
  gtk_object_set_data_full (GTK_OBJECT (app->gui.PropertyBox), "hbox2", hbox2,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (hbox2);
  gtk_box_pack_start (GTK_BOX (vbox1), hbox2, FALSE, FALSE, GOAL_PROP_BOX_PAD);

  /* --- button left --- */
  app->gui.PropertyBoxButtonLeft= gtk_button_new();
  gtk_widget_set_name (app->gui.PropertyBoxButtonLeft, "button_left");
  gtk_widget_ref(app->gui.PropertyBoxButtonLeft);
  gtk_object_set_data_full (GTK_OBJECT (app->gui.PropertyBox), "button_left", app->gui.PropertyBoxButtonLeft,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (app->gui.PropertyBoxButtonLeft);
  gtk_box_pack_start (GTK_BOX (hbox2), app->gui.PropertyBoxButtonLeft, FALSE, TRUE, 0);
  /*gtk_button_set_relief (GTK_BUTTON (app->gui.PropertyBoxButtonLeft), GTK_RELIEF_NONE);*/

  ArrowLeft = gtk_arrow_new (GTK_ARROW_LEFT, GTK_SHADOW_NONE);
  gtk_widget_set_name (ArrowLeft, "ArrowLeft");
  gtk_widget_ref (ArrowLeft);
  gtk_object_set_data_full (GTK_OBJECT (app->gui.PropertyBox), "ArrowLeft", ArrowLeft,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_container_add (GTK_CONTAINER (app->gui.PropertyBoxButtonLeft), ArrowLeft);


  /* --- theme name label --- */
  app->gui.PropertyBoxLabelThemeName = gtk_label_new (_("theme name"));
  gtk_widget_set_name (app->gui.PropertyBoxLabelThemeName, "LabelThemeName");
  gtk_widget_ref(app->gui.PropertyBoxLabelThemeName);
  gtk_object_set_data_full (GTK_OBJECT (app->gui.PropertyBox), "LabelThemeName", app->gui.PropertyBoxLabelThemeName,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (app->gui.PropertyBoxLabelThemeName);
  gtk_box_pack_start (GTK_BOX (hbox2), app->gui.PropertyBoxLabelThemeName, TRUE, TRUE, 0);

  /* --- button right --- */
  app->gui.PropertyBoxButtonRight = gtk_button_new ();
  gtk_widget_set_name (app->gui.PropertyBoxButtonRight, "button_right");
  gtk_widget_ref (app->gui.PropertyBoxButtonRight);
  gtk_object_set_data_full (GTK_OBJECT (app->gui.PropertyBox), "button_right", app->gui.PropertyBoxButtonRight,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (app->gui.PropertyBoxButtonRight);
  gtk_box_pack_start (GTK_BOX (hbox2), app->gui.PropertyBoxButtonRight, FALSE, TRUE, 0);
  /*gtk_button_set_relief (GTK_BUTTON (app->gui.PropertyBoxButtonRight), GTK_RELIEF_NONE);*/

  ArrowRight = gtk_arrow_new (GTK_ARROW_RIGHT, GTK_SHADOW_NONE);
  gtk_widget_set_name (ArrowRight, "ArrowRight");
  gtk_widget_ref (ArrowRight);
  gtk_object_set_data_full (GTK_OBJECT (app->gui.PropertyBox), "ArrowRight", ArrowRight,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_container_add (GTK_CONTAINER (app->gui.PropertyBoxButtonRight), ArrowRight);

  scrolledwindow1 = gtk_scrolled_window_new (NULL, NULL);
  gtk_widget_set_name (scrolledwindow1, "scrolledwindow1");
  gtk_widget_ref (scrolledwindow1);
  gtk_object_set_data_full (GTK_OBJECT (app->gui.PropertyBox), "scrolledwindow1", scrolledwindow1,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (scrolledwindow1);
  gtk_box_pack_start (GTK_BOX (vbox1), scrolledwindow1, TRUE, TRUE, GOAL_PROP_BOX_PAD);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolledwindow1), GTK_POLICY_NEVER, GTK_POLICY_NEVER);

  /* --- canvas --- */
  gtk_widget_push_visual(gdk_rgb_get_visual());
  gtk_widget_push_colormap(gdk_rgb_get_cmap());
  app->gui.PropertyBoxCanvas = gnome_canvas_new ();
  gtk_widget_pop_colormap ();
  gtk_widget_pop_visual ();
  gtk_widget_set_name(app->gui.PropertyBoxCanvas, "CanvasTheme");
  gtk_widget_ref(app->gui.PropertyBoxCanvas);
  gtk_object_set_data_full (GTK_OBJECT (app->gui.PropertyBox), "CanvasTheme", app->gui.PropertyBoxCanvas,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (app->gui.PropertyBoxCanvas);
  gtk_container_add (GTK_CONTAINER (scrolledwindow1), app->gui.PropertyBoxCanvas);
  GTK_WIDGET_UNSET_FLAGS(app->gui.PropertyBoxCanvas, GTK_CAN_FOCUS);
  gnome_canvas_set_scroll_region(GNOME_CANVAS(app->gui.PropertyBoxCanvas), 0, 0, 100, 100);
  /* FIXME: deprecated */
  gtk_widget_set_usize(app->gui.PropertyBoxCanvas, 100, 100);


  LabelTheme = gtk_label_new (_("Theme"));
  gtk_widget_set_name (LabelTheme, "LabelTheme");
  gtk_widget_ref (LabelTheme);
  gtk_object_set_data_full (GTK_OBJECT (app->gui.PropertyBox), "LabelTheme", LabelTheme,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (LabelTheme);
  gtk_notebook_set_tab_label (GTK_NOTEBOOK (NotebookTheme), gtk_notebook_get_nth_page (GTK_NOTEBOOK (NotebookTheme), 0), LabelTheme);

  /* --- connect to signal handlers --- */
	gtk_signal_connect (GTK_OBJECT(app->gui.PropertyBoxButtonLeft), "clicked", 
			GTK_SIGNAL_FUNC (property_left_arrow_button_press_event_cb),
			app);
	gtk_signal_connect (GTK_OBJECT (app->gui.PropertyBoxButtonRight), "clicked",
			GTK_SIGNAL_FUNC (property_right_arrow_button_press_event_cb),
                      	app);
	gtk_signal_connect(GTK_OBJECT(app->gui.PropertyBox), "apply",
			GTK_SIGNAL_FUNC(property_box_apply_event_cb),
			app);
	/* we need this only to know when this property box is destroyed */
	gtk_signal_connect(GTK_OBJECT(app->gui.PropertyBox), "destroy",
			GTK_SIGNAL_FUNC(property_box_destroy_event_cb),
			app);
  /* --- set sensitiv --- */
  gtk_widget_set_sensitive(app->gui.PropertyBoxButtonRight, FALSE);
  gtk_widget_set_sensitive(app->gui.PropertyBoxButtonLeft, FALSE);


}

