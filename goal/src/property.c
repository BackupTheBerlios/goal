#include <gdk-pixbuf/gdk-pixbuf.h>
#include <libgnomecanvas/gnome-canvas-pixbuf.h>
#include "property.h"
#include "callbacks.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

/*
#define GLADE_HOOKUP_OBJECT(component,widget,name) \
  g_object_set_data_full (G_OBJECT (component), name, \
    gtk_widget_ref (widget), (GDestroyNotify) gtk_widget_unref)

#define GLADE_HOOKUP_OBJECT_NO_REF(component,widget,name) \
  g_object_set_data (G_OBJECT (component), name, widget)
*/


/*
void
create_PropertyBox(GoalApp *app)
{
  
	
	GtkWidget *NotebookTheme;
	GtkWidget *hbox1;
	GtkWidget *vbox1;
	GtkWidget *hbox2;
	GtkWidget *ArrowLeft;
*/	/*GtkWidget *LabelThemeName;*/
/*	GtkWidget *ArrowRight;
	GtkWidget *scrolledwindow1;
	GtkWidget *LabelTheme;


*/	/* --- property box --- */
/*	app->gui.PropertyBox = gnome_property_box_new ();
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

*/  /* --- button left --- */
/*  app->gui.PropertyBoxButtonLeft= gtk_button_new();
  gtk_widget_set_name (app->gui.PropertyBoxButtonLeft, "button_left");
  gtk_widget_ref(app->gui.PropertyBoxButtonLeft);
  gtk_object_set_data_full (GTK_OBJECT (app->gui.PropertyBox), "button_left", app->gui.PropertyBoxButtonLeft,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (app->gui.PropertyBoxButtonLeft);
  gtk_box_pack_start (GTK_BOX (hbox2), app->gui.PropertyBoxButtonLeft, FALSE, TRUE, 0);
*/  /*gtk_button_set_relief (GTK_BUTTON (app->gui.PropertyBoxButtonLeft), GTK_RELIEF_NONE);*/

/*  ArrowLeft = gtk_arrow_new (GTK_ARROW_LEFT, GTK_SHADOW_NONE);
  gtk_widget_set_name (ArrowLeft, "ArrowLeft");
  gtk_widget_ref (ArrowLeft);
  gtk_object_set_data_full (GTK_OBJECT (app->gui.PropertyBox), "ArrowLeft", ArrowLeft,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_container_add (GTK_CONTAINER (app->gui.PropertyBoxButtonLeft), ArrowLeft);


*/  /* --- theme name label --- */
/*  app->gui.PropertyBoxLabelThemeName = gtk_label_new (_("theme name"));
  gtk_widget_set_name (app->gui.PropertyBoxLabelThemeName, "LabelThemeName");
  gtk_widget_ref(app->gui.PropertyBoxLabelThemeName);
  gtk_object_set_data_full (GTK_OBJECT (app->gui.PropertyBox), "LabelThemeName", app->gui.PropertyBoxLabelThemeName,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (app->gui.PropertyBoxLabelThemeName);
  gtk_box_pack_start (GTK_BOX (hbox2), app->gui.PropertyBoxLabelThemeName, TRUE, TRUE, 0);

*/  /* --- button right --- */
/*  app->gui.PropertyBoxButtonRight = gtk_button_new ();
  gtk_widget_set_name (app->gui.PropertyBoxButtonRight, "button_right");
  gtk_widget_ref (app->gui.PropertyBoxButtonRight);
  gtk_object_set_data_full (GTK_OBJECT (app->gui.PropertyBox), "button_right", app->gui.PropertyBoxButtonRight,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (app->gui.PropertyBoxButtonRight);
  gtk_box_pack_start (GTK_BOX (hbox2), app->gui.PropertyBoxButtonRight, FALSE, TRUE, 0);
*/  /*gtk_button_set_relief (GTK_BUTTON (app->gui.PropertyBoxButtonRight), GTK_RELIEF_NONE);*/

/*  ArrowRight = gtk_arrow_new (GTK_ARROW_RIGHT, GTK_SHADOW_NONE);
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

*/  /* --- canvas --- */
/*  gtk_widget_push_visual(gdk_rgb_get_visual());
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
*/  /* FIXME: deprecated */
/*  gtk_widget_set_usize(app->gui.PropertyBoxCanvas, 100, 100);


  LabelTheme = gtk_label_new (_("Theme"));
  gtk_widget_set_name (LabelTheme, "LabelTheme");
  gtk_widget_ref (LabelTheme);
  gtk_object_set_data_full (GTK_OBJECT (app->gui.PropertyBox), "LabelTheme", LabelTheme,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (LabelTheme);
  gtk_notebook_set_tab_label (GTK_NOTEBOOK (NotebookTheme), gtk_notebook_get_nth_page (GTK_NOTEBOOK (NotebookTheme), 0), LabelTheme);

*/  /* --- connect to signal handlers --- */
/*	gtk_signal_connect (GTK_OBJECT(app->gui.PropertyBoxButtonLeft), "clicked", 
			GTK_SIGNAL_FUNC (property_left_arrow_button_press_event_cb),
			app);
	gtk_signal_connect (GTK_OBJECT (app->gui.PropertyBoxButtonRight), "clicked",
			GTK_SIGNAL_FUNC (property_right_arrow_button_press_event_cb),
                      	app);
	gtk_signal_connect(GTK_OBJECT(app->gui.PropertyBox), "apply",
			GTK_SIGNAL_FUNC(property_box_apply_event_cb),
			app);
*/	/* we need this only to know when this property box is destroyed */
/*	gtk_signal_connect(GTK_OBJECT(app->gui.PropertyBox), "destroy",
			GTK_SIGNAL_FUNC(property_box_destroy_event_cb),
			app);
*/  /* --- set sensitiv --- */
/*  gtk_widget_set_sensitive(app->gui.PropertyBoxButtonRight, FALSE);
  gtk_widget_set_sensitive(app->gui.PropertyBoxButtonLeft, FALSE);


}
*/



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
  /*GtkWidget *PropertyBox;*/
  GtkWidget *dialog_vbox1;
  GtkWidget *vbox1;
  GtkWidget *hbox1;
  /*GtkWidget *PropertyBoxButtonLeft;*/
  GtkWidget *alignment1;
  GtkWidget *hbox2;
  GtkWidget *image1;
  GtkWidget *label2;
  /*GtkWidget *PropertyBoxLabelThemeName;
  GtkWidget *PropertyBoxButtonRight;*/
  GtkWidget *alignment2;
  GtkWidget *hbox3;
  GtkWidget *button2;
  GtkWidget *image2;
  GtkWidget *scrolledwindow1;
  /*GtkWidget *PropertyBoxCanvas;*/
  GtkWidget *dialog_action_area1;
  /*GtkWidget *PropertyBoxButtonCancel;
  GtkWidget *PropertyBoxButtonApply;
  GtkWidget *PropertyBoxButtonOK;*/

  app->gui.PropertyBox = gtk_dialog_new ();
  gtk_window_set_title (GTK_WINDOW (app->gui.PropertyBox), _("Goal - theme selector"));
  gtk_window_set_modal (GTK_WINDOW (app->gui.PropertyBox), TRUE);

  dialog_vbox1 = GTK_DIALOG (app->gui.PropertyBox)->vbox;
  gtk_widget_show (dialog_vbox1);

  vbox1 = gtk_vbox_new (FALSE, 0);
  gtk_widget_show (vbox1);
  gtk_box_pack_start (GTK_BOX (dialog_vbox1), vbox1, TRUE, TRUE, 0);

  hbox1 = gtk_hbox_new (FALSE, 0);
  gtk_widget_show (hbox1);
  gtk_box_pack_start (GTK_BOX (vbox1), hbox1, FALSE, FALSE, 0);

  app->gui.PropertyBoxButtonLeft = gtk_button_new ();
  gtk_widget_show (app->gui.PropertyBoxButtonLeft);
  gtk_box_pack_start (GTK_BOX (hbox1), app->gui.PropertyBoxButtonLeft, FALSE, TRUE, 0);

  alignment1 = gtk_alignment_new (0.5, 0.5, 0, 0);
  gtk_widget_show (alignment1);
  gtk_container_add (GTK_CONTAINER (app->gui.PropertyBoxButtonLeft), alignment1);

  hbox2 = gtk_hbox_new (FALSE, 2);
  gtk_widget_show (hbox2);
  gtk_container_add (GTK_CONTAINER (alignment1), hbox2);

  image1 = gtk_image_new_from_stock ("gtk-go-back", GTK_ICON_SIZE_BUTTON);
  gtk_widget_show (image1);
  gtk_box_pack_start (GTK_BOX (hbox2), image1, FALSE, FALSE, 0);

  label2 = gtk_label_new_with_mnemonic (_("Back"));
  gtk_widget_show (label2);
  gtk_box_pack_start (GTK_BOX (hbox2), label2, FALSE, FALSE, 0);
  gtk_label_set_justify (GTK_LABEL (label2), GTK_JUSTIFY_LEFT);

  app->gui.PropertyBoxLabelThemeName = gtk_label_new (_("theme name"));
  gtk_widget_show (app->gui.PropertyBoxLabelThemeName);
  gtk_box_pack_start (GTK_BOX (hbox1), app->gui.PropertyBoxLabelThemeName, TRUE, TRUE, 0);

  app->gui.PropertyBoxButtonRight = gtk_button_new ();
  gtk_widget_show (app->gui.PropertyBoxButtonRight);
  gtk_box_pack_start (GTK_BOX (hbox1), app->gui.PropertyBoxButtonRight, FALSE, TRUE, 0);

  alignment2 = gtk_alignment_new (0.5, 0.5, 0, 0);
  gtk_widget_show (alignment2);
  gtk_container_add (GTK_CONTAINER (app->gui.PropertyBoxButtonRight), alignment2);

  hbox3 = gtk_hbox_new (FALSE, 2);
  gtk_widget_show (hbox3);
  gtk_container_add (GTK_CONTAINER (alignment2), hbox3);

  button2 = gtk_label_new (_("Forward"));
  gtk_widget_show (button2);
  gtk_box_pack_start (GTK_BOX (hbox3), button2, FALSE, FALSE, 0);
  gtk_label_set_justify (GTK_LABEL (button2), GTK_JUSTIFY_RIGHT);

  image2 = gtk_image_new_from_stock ("gtk-go-forward", GTK_ICON_SIZE_BUTTON);
  gtk_widget_show (image2);
  gtk_box_pack_start (GTK_BOX (hbox3), image2, FALSE, FALSE, 0);

  scrolledwindow1 = gtk_scrolled_window_new (NULL, NULL);
  gtk_widget_show (scrolledwindow1);
  gtk_box_pack_start (GTK_BOX (vbox1), scrolledwindow1, TRUE, TRUE, 0);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolledwindow1), GTK_POLICY_NEVER, GTK_POLICY_NEVER);

  app->gui.PropertyBoxCanvas = gnome_canvas_new_aa ();
  gtk_widget_show (app->gui.PropertyBoxCanvas);
  gtk_container_add (GTK_CONTAINER (scrolledwindow1), app->gui.PropertyBoxCanvas);
  gtk_widget_set_sensitive (app->gui.PropertyBoxCanvas, FALSE);
  gnome_canvas_set_scroll_region (GNOME_CANVAS (app->gui.PropertyBoxCanvas), 0, 0, 100, 100);

  dialog_action_area1 = GTK_DIALOG(app->gui.PropertyBox)->action_area;
  gtk_widget_show (dialog_action_area1);
  gtk_button_box_set_layout (GTK_BUTTON_BOX (dialog_action_area1), GTK_BUTTONBOX_END);

  app->gui.PropertyBoxButtonCancel = gtk_button_new_from_stock ("gtk-cancel");
  gtk_widget_show (app->gui.PropertyBoxButtonCancel);
  gtk_dialog_add_action_widget (GTK_DIALOG(app->gui.PropertyBox), app->gui.PropertyBoxButtonCancel, GTK_RESPONSE_CANCEL);
  GTK_WIDGET_SET_FLAGS (app->gui.PropertyBoxButtonCancel, GTK_CAN_DEFAULT);

  app->gui.PropertyBoxButtonApply = gtk_button_new_from_stock ("gtk-apply");
  gtk_widget_show (app->gui.PropertyBoxButtonApply);
  gtk_dialog_add_action_widget (GTK_DIALOG(app->gui.PropertyBox), app->gui.PropertyBoxButtonApply, GTK_RESPONSE_APPLY);
  GTK_WIDGET_SET_FLAGS (app->gui.PropertyBoxButtonApply, GTK_CAN_DEFAULT);

  app->gui.PropertyBoxButtonOK = gtk_button_new_from_stock ("gtk-ok");
  gtk_widget_show (app->gui.PropertyBoxButtonOK);
  gtk_dialog_add_action_widget (GTK_DIALOG(app->gui.PropertyBox), app->gui.PropertyBoxButtonOK, GTK_RESPONSE_OK);
  GTK_WIDGET_SET_FLAGS (app->gui.PropertyBoxButtonOK, GTK_CAN_DEFAULT);

  g_signal_connect ((gpointer) app->gui.PropertyBox, "destroy",
                    G_CALLBACK (property_box_destroy_event_cb),
                    app);
  g_signal_connect ((gpointer) app->gui.PropertyBoxButtonLeft, "clicked",
                    G_CALLBACK (property_left_arrow_button_clicked_event_cb),
                    app);
  g_signal_connect ((gpointer) app->gui.PropertyBoxButtonRight, "clicked",
                    G_CALLBACK (property_right_arrow_button_clicked_event_cb),
                    app);
  g_signal_connect ((gpointer) app->gui.PropertyBoxButtonCancel, "clicked",
                    G_CALLBACK (property_cancel_button_clicked_event_cb),
                    app);
  g_signal_connect ((gpointer) app->gui.PropertyBoxButtonApply, "clicked",
                    G_CALLBACK (property_apply_button_clicked_event_cb),
                    app);
  g_signal_connect ((gpointer) app->gui.PropertyBoxButtonOK, "clicked",
                    G_CALLBACK (property_ok_button_clicked_event_cb),
                    app);

  
  /* Store pointers to all widgets, for use by lookup_widget(). */
  /*
  GLADE_HOOKUP_OBJECT_NO_REF (app->gui.PropertyBox, app->gui.PropertyBox, "PropertyBox");
  GLADE_HOOKUP_OBJECT_NO_REF (app->gui.PropertyBox, dialog_vbox1, "dialog_vbox1");
  GLADE_HOOKUP_OBJECT (app->gui.PropertyBox, vbox1, "vbox1");
  GLADE_HOOKUP_OBJECT (app->gui.PropertyBox, hbox1, "hbox1");
  GLADE_HOOKUP_OBJECT (app->gui.PropertyBox, app->gui.PropertyBoxButtonLeft, "PropertyBoxButtonLeft");
  GLADE_HOOKUP_OBJECT (app->gui.PropertyBox, alignment1, "alignment1");
  GLADE_HOOKUP_OBJECT (app->gui.PropertyBox, hbox2, "hbox2");
  GLADE_HOOKUP_OBJECT (app->gui.PropertyBox, image1, "image1");
  GLADE_HOOKUP_OBJECT (app->gui.PropertyBox, label2, "label2");
  GLADE_HOOKUP_OBJECT (app->gui.PropertyBox, app->gui.PropertyBoxLabelThemeName, "PropertyBoxLabelThemeName");
  GLADE_HOOKUP_OBJECT (app->gui.PropertyBox, app->gui.PropertyBoxButtonRight, "PropertyBoxButtonRight");
  GLADE_HOOKUP_OBJECT (app->gui.PropertyBox, alignment2, "alignment2");
  GLADE_HOOKUP_OBJECT (app->gui.PropertyBox, hbox3, "hbox3");
  GLADE_HOOKUP_OBJECT (app->gui.PropertyBox, button2, "button2");
  GLADE_HOOKUP_OBJECT (app->gui.PropertyBox, image2, "image2");
  GLADE_HOOKUP_OBJECT (app->gui.PropertyBox, scrolledwindow1, "scrolledwindow1");
  GLADE_HOOKUP_OBJECT (app->gui.PropertyBox, app->gui.PropertyBoxCanvas, "PropertyBoxCanvas");
  GLADE_HOOKUP_OBJECT_NO_REF (app->gui.PropertyBox, dialog_action_area1, "dialog_action_area1");
  GLADE_HOOKUP_OBJECT (app->gui.PropertyBox, app->gui.PropertyBoxButtonCancel, "PropertyBoxButtonCancel");
  GLADE_HOOKUP_OBJECT (app->gui.PropertyBox, app->gui.PropertyBoxButtonApply, "PropertyBoxButtonApply");
  GLADE_HOOKUP_OBJECT (app->gui.PropertyBox, app->gui.PropertyBoxButtonOK, "PropertyBoxButtonOK");
  */

 /* --- set sensitiv --- */
  gtk_widget_set_sensitive(app->gui.PropertyBoxButtonRight, FALSE);
  gtk_widget_set_sensitive(app->gui.PropertyBoxButtonLeft, FALSE);

}

