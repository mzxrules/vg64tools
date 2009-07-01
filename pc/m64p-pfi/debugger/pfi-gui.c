#include <stdio.h>
#include <gtk/gtk.h>
#include <stdint.h>
#include <glib.h>

struct spec_t
{
    char       * symname;
    GtkWidget ** stor;
};

/* Widgets */
GtkWidget * pfi_gui_window;
GtkWidget * pfi_gui_b_enable;
GtkWidget * pfi_gui_b_disable;
GtkWidget * pfi_gui_b_close;
GtkWidget * pfi_gui_e_file;
GtkWidget * pfi_gui_e_arg_start;
GtkWidget * pfi_gui_e_address;
GtkWidget * pfi_gui_c_append;
GtkWidget * pfi_gui_c_logra;

/* Options */
int        pfi_enabled;
uint32_t   pfi_address;
int        pfi_argstart;
FILE     * pfi_logfile;
int        pfi_append;
int        pfi_logra;

/* Mutal exclusion for fucking around with settings */
GMutex * pfi_mutex;


struct spec_t
syms[] = 
{
    { "m64pd-PrintfIntercept", &pfi_gui_window      },
    { "b-enable",              &pfi_gui_b_enable    },
    { "b-disable",             &pfi_gui_b_disable   },
    { "b-close",               &pfi_gui_b_close     },
    { "e-file",                &pfi_gui_e_file      },
    { "e-arg-start",           &pfi_gui_e_arg_start },
    { "e-address",             &pfi_gui_e_address   },
    { "c-append",              &pfi_gui_c_append    },
    { "c-logra",               &pfi_gui_c_logra     },
    { NULL }
};


static void
close ( GtkButton * b, gpointer udata )
{
    gtk_widget_hide( pfi_gui_window );
}

static gboolean
delete_event ( GtkWidget * w, GdkEvent * event, gpointer udata )
{
    close( NULL, NULL );
    
    return TRUE;
}

static void
enable ( GtkButton * b, gpointer udata )
{
    char * fname;
    
    g_mutex_lock( pfi_mutex );
    
    gtk_widget_set_sensitive( pfi_gui_b_enable, FALSE );
    gtk_widget_set_sensitive( pfi_gui_b_disable, TRUE );
    
    /* Read values */
    pfi_argstart = gtk_spin_button_get_value_as_int( GTK_SPIN_BUTTON(pfi_gui_e_arg_start) );
    sscanf( gtk_entry_get_text(GTK_ENTRY(pfi_gui_e_address)), "%X", &pfi_address );
    pfi_append = gtk_toggle_button_get_active( GTK_TOGGLE_BUTTON(pfi_gui_c_append) );
    pfi_logra = gtk_toggle_button_get_active( GTK_TOGGLE_BUTTON(pfi_gui_c_logra) );
    fname = gtk_file_chooser_get_filename( GTK_FILE_CHOOSER(pfi_gui_e_file) );
    if( pfi_logfile )
        fclose( pfi_logfile );
    
    if( fname )
    {
        pfi_logfile = fopen( fname, (pfi_append ? "ab" : "wb") );
    }
    else
    {
        pfi_logfile = NULL;/*fopen( "/dev/null", "w" );*/
    }
    
    g_free( fname );
    pfi_enabled = TRUE;
    
    g_mutex_unlock( pfi_mutex );
}

static void
disable ( GtkButton * b, gpointer udata )
{
    g_mutex_lock( pfi_mutex );
    
    gtk_widget_set_sensitive( pfi_gui_b_enable, TRUE );
    gtk_widget_set_sensitive( pfi_gui_b_disable, FALSE );
    
    pfi_enabled = FALSE;
    fclose( pfi_logfile );
    pfi_logfile = NULL;
    
    g_mutex_unlock( pfi_mutex );
}

void
pfi_gui_make ( void )
{
    extern const char pfi_gtk_gui[];
    GtkBuilder * b;
    int i;
    
    pfi_mutex = g_mutex_new();
    
    /* Create the interface builder */
    b = gtk_builder_new();
    
    /* Load spec */
    gtk_builder_add_from_string( b, pfi_gtk_gui, -1, NULL );
    
    /* Grab symbols */
    for( i = 0; syms[i].symname; i++ )
        *syms[i].stor = (GtkWidget*)gtk_builder_get_object( b, syms[i].symname );
    
    system( "touch pfilog.txt" );
    
    gtk_file_chooser_set_filename( GTK_FILE_CHOOSER(pfi_gui_e_file), "pfilog.txt" );
    gtk_spin_button_set_range( GTK_SPIN_BUTTON(pfi_gui_e_arg_start), 0.0, 3.0 ); 
    
    gtk_widget_set_sensitive( pfi_gui_b_disable, FALSE );
    
    g_signal_connect( G_OBJECT(pfi_gui_window), "delete-event", (GCallback)delete_event, NULL );
    g_signal_connect( G_OBJECT(pfi_gui_b_close), "clicked", (GCallback)close, NULL );
    g_signal_connect( G_OBJECT(pfi_gui_b_enable), "clicked", (GCallback)enable, NULL );
    g_signal_connect( G_OBJECT(pfi_gui_b_disable), "clicked", (GCallback)disable, NULL );
}

void pfi_gui_show ( void )
{
    if( !pfi_gui_window )
    {
        pfi_gui_make();
    }
    gtk_widget_show_all( pfi_gui_window );
}



const char 
pfi_gtk_gui[] =

"<?xml version=\"1.0\"?>"
"<interface>"
"  <requires lib=\"gtk+\" version=\"2.16\"/>"
"  <!-- interface-naming-policy toplevel-contextual -->"
"  <object class=\"GtkWindow\" id=\"m64pd-PrintfIntercept\">"
"    <property name=\"border_width\">8</property>"
"    <property name=\"title\" translatable=\"yes\">Print Format Interceptor</property>"
"    <property name=\"type_hint\">dialog</property>"
"    <child>"
"      <object class=\"GtkVBox\" id=\"Organizer\">"
"        <property name=\"visible\">True</property>"
"        <property name=\"spacing\">10</property>"
"        <child>"
"          <object class=\"GtkVBox\" id=\"FuncOpts\">"
"            <property name=\"visible\">True</property>"
"            <property name=\"spacing\">8</property>"
"            <child>"
"              <object class=\"GtkFrame\" id=\"frame2\">"
"                <property name=\"visible\">True</property>"
"                <property name=\"label_xalign\">0</property>"
"                <child>"
"                  <object class=\"GtkAlignment\" id=\"alignment1\">"
"                    <property name=\"visible\">True</property>"
"                    <property name=\"top_padding\">8</property>"
"                    <property name=\"bottom_padding\">8</property>"
"                    <property name=\"left_padding\">8</property>"
"                    <property name=\"right_padding\">8</property>"
"                    <child>"
"                      <object class=\"GtkTable\" id=\"table1\">"
"                        <property name=\"visible\">True</property>"
"                        <property name=\"n_rows\">2</property>"
"                        <property name=\"n_columns\">2</property>"
"                        <property name=\"column_spacing\">8</property>"
"                        <property name=\"row_spacing\">8</property>"
"                        <child>"
"                          <object class=\"GtkSpinButton\" id=\"e-arg-start\">"
"                            <property name=\"visible\">True</property>"
"                            <property name=\"can_focus\">True</property>"
"                            <property name=\"invisible_char\">&#x25CF;</property>"
"                            <property name=\"adjustment\">adjustment1</property>"
"                          </object>"
"                          <packing>"
"                            <property name=\"left_attach\">1</property>"
"                            <property name=\"right_attach\">2</property>"
"                            <property name=\"top_attach\">1</property>"
"                            <property name=\"bottom_attach\">2</property>"
"                          </packing>"
"                        </child>"
"                        <child>"
"                          <object class=\"GtkLabel\" id=\"label3\">"
"                            <property name=\"visible\">True</property>"
"                            <property name=\"has_tooltip\">True</property>"
"                            <property name=\"tooltip_markup\">Argument # of the format string</property>"
"                            <property name=\"tooltip_text\" translatable=\"yes\">Argument # of the format string.                            Arguments must come immediately afterwards.</property>"
"                            <property name=\"xalign\">0</property>"
"                            <property name=\"label\" translatable=\"yes\">Arg start:</property>"
"                          </object>"
"                          <packing>"
"                            <property name=\"top_attach\">1</property>"
"                            <property name=\"bottom_attach\">2</property>"
"                            <property name=\"x_options\">GTK_SHRINK | GTK_FILL</property>"
"                            <property name=\"y_options\">GTK_SHRINK | GTK_FILL</property>"
"                          </packing>"
"                        </child>"
"                        <child>"
"                          <object class=\"GtkLabel\" id=\"label6\">"
"                            <property name=\"visible\">True</property>"
"                            <property name=\"has_tooltip\">True</property>"
"                            <property name=\"tooltip_markup\">Address of the function to intercept</property>"
"                            <property name=\"tooltip_text\" translatable=\"yes\">Address of the function to intercept.</property>"
"                            <property name=\"xalign\">0</property>"
"                            <property name=\"label\" translatable=\"yes\">Address:</property>"
"                          </object>"
"                          <packing>"
"                            <property name=\"x_options\">GTK_SHRINK | GTK_FILL</property>"
"                            <property name=\"y_options\">GTK_SHRINK | GTK_FILL</property>"
"                          </packing>"
"                        </child>"
"                        <child>"
"                          <object class=\"GtkEntry\" id=\"e-address\">"
"                            <property name=\"visible\">True</property>"
"                            <property name=\"can_focus\">True</property>"
"                            <property name=\"invisible_char\">&#x25CF;</property>"
"                          </object>"
"                          <packing>"
"                            <property name=\"left_attach\">1</property>"
"                            <property name=\"right_attach\">2</property>"
"                          </packing>"
"                        </child>"
"                      </object>"
"                    </child>"
"                  </object>"
"                </child>"
"                <child type=\"label\">"
"                  <object class=\"GtkLabel\" id=\"label2\">"
"                    <property name=\"visible\">True</property>"
"                    <property name=\"label\" translatable=\"yes\">&lt;b&gt;Function options&lt;/b&gt;</property>"
"                    <property name=\"use_markup\">True</property>"
"                  </object>"
"                </child>"
"              </object>"
"              <packing>"
"                <property name=\"position\">0</property>"
"              </packing>"
"            </child>"
"          </object>"
"          <packing>"
"            <property name=\"expand\">False</property>"
"            <property name=\"fill\">False</property>"
"            <property name=\"position\">0</property>"
"          </packing>"
"        </child>"
"        <child>"
"          <object class=\"GtkVBox\" id=\"LogOpts\">"
"            <property name=\"visible\">True</property>"
"            <property name=\"spacing\">8</property>"
"            <child>"
"              <object class=\"GtkFrame\" id=\"frame1\">"
"                <property name=\"visible\">True</property>"
"                <property name=\"label_xalign\">0</property>"
"                <child>"
"                  <object class=\"GtkAlignment\" id=\"LogOpts-Align\">"
"                    <property name=\"visible\">True</property>"
"                    <property name=\"top_padding\">8</property>"
"                    <property name=\"bottom_padding\">8</property>"
"                    <property name=\"left_padding\">8</property>"
"                    <property name=\"right_padding\">8</property>"
"                    <child>"
"                      <object class=\"GtkVBox\" id=\"LogOpts-MainOrganizer\">"
"                        <property name=\"visible\">True</property>"
"                        <property name=\"orientation\">vertical</property>"
"                        <property name=\"spacing\">4</property>"
"                        <child>"
"                          <object class=\"GtkVBox\" id=\"vbox1\">"
"                            <property name=\"visible\">True</property>"
"                            <property name=\"orientation\">vertical</property>"
"                            <property name=\"spacing\">4</property>"
"                            <child>"
"                              <object class=\"GtkTable\" id=\"LogOpts-EntryTable\">"
"                                <property name=\"visible\">True</property>"
"                                <property name=\"n_columns\">2</property>"
"                                <property name=\"column_spacing\">8</property>"
"                                <property name=\"row_spacing\">8</property>"
"                                <child>"
"                                  <object class=\"GtkLabel\" id=\"label5\">"
"                                    <property name=\"visible\">True</property>"
"                                    <property name=\"has_tooltip\">True</property>"
"                                    <property name=\"tooltip_markup\">Where to write the output</property>"
"                                    <property name=\"tooltip_text\" translatable=\"yes\">An optional log file.</property>"
"                                    <property name=\"label\" translatable=\"yes\">Log file:</property>"
"                                  </object>"
"                                  <packing>"
"                                    <property name=\"x_options\">GTK_FILL</property>"
"                                    <property name=\"y_options\">GTK_FILL</property>"
"                                  </packing>"
"                                </child>"
"                                <child>"
"                                  <object class=\"GtkFileChooserButton\" id=\"e-file\">"
"                                    <property name=\"visible\">True</property>"
"                                  </object>"
"                                  <packing>"
"                                    <property name=\"left_attach\">1</property>"
"                                    <property name=\"right_attach\">2</property>"
"                                  </packing>"
"                                </child>"
"                              </object>"
"                              <packing>"
"                                <property name=\"position\">0</property>"
"                              </packing>"
"                            </child>"
"                            <child>"
"                              <object class=\"GtkTable\" id=\"table2\">"
"                                <property name=\"visible\">True</property>"
"                                <property name=\"n_columns\">2</property>"
"                                <property name=\"column_spacing\">4</property>"
"                                <property name=\"row_spacing\">4</property>"
"                                <property name=\"homogeneous\">True</property>"
"                                <child>"
"                                  <object class=\"GtkCheckButton\" id=\"c-append\">"
"                                    <property name=\"label\" translatable=\"yes\">Append</property>"
"                                    <property name=\"visible\">True</property>"
"                                    <property name=\"can_focus\">True</property>"
"                                    <property name=\"receives_default\">False</property>"
"                                    <property name=\"draw_indicator\">True</property>"
"                                  </object>"
"                                </child>"
"                                <child>"
"                                  <object class=\"GtkCheckButton\" id=\"c-logra\">"
"                                    <property name=\"label\" translatable=\"yes\">Log $ra</property>"
"                                    <property name=\"visible\">True</property>"
"                                    <property name=\"can_focus\">True</property>"
"                                    <property name=\"receives_default\">False</property>"
"                                    <property name=\"draw_indicator\">True</property>"
"                                  </object>"
"                                  <packing>"
"                                    <property name=\"left_attach\">1</property>"
"                                    <property name=\"right_attach\">2</property>"
"                                  </packing>"
"                                </child>"
"                              </object>"
"                              <packing>"
"                                <property name=\"position\">1</property>"
"                              </packing>"
"                            </child>"
"                          </object>"
"                          <packing>"
"                            <property name=\"position\">0</property>"
"                          </packing>"
"                        </child>"
"                      </object>"
"                    </child>"
"                  </object>"
"                </child>"
"                <child type=\"label\">"
"                  <object class=\"GtkLabel\" id=\"label4\">"
"                    <property name=\"visible\">True</property>"
"                    <property name=\"label\" translatable=\"yes\">&lt;b&gt;Logging options&lt;/b&gt;</property>"
"                    <property name=\"use_markup\">True</property>"
"                  </object>"
"                </child>"
"              </object>"
"              <packing>"
"                <property name=\"position\">0</property>"
"              </packing>"
"            </child>"
"          </object>"
"          <packing>"
"            <property name=\"expand\">False</property>"
"            <property name=\"fill\">False</property>"
"            <property name=\"position\">1</property>"
"          </packing>"
"        </child>"
"        <child>"
"          <object class=\"GtkAlignment\" id=\"ButtonsAlign\">"
"            <property name=\"visible\">True</property>"
"            <property name=\"yalign\">1</property>"
"            <property name=\"yscale\">0</property>"
"            <child>"
"              <object class=\"GtkVBox\" id=\"vbox2\">"
"                <property name=\"visible\">True</property>"
"                <property name=\"spacing\">4</property>"
"                <child>"
"                  <object class=\"GtkHSeparator\" id=\"hseparator1\">"
"                    <property name=\"visible\">True</property>"
"                  </object>"
"                  <packing>"
"                    <property name=\"expand\">False</property>"
"                    <property name=\"position\">0</property>"
"                  </packing>"
"                </child>"
"                <child>"
"                  <object class=\"GtkAlignment\" id=\"alignment3\">"
"                    <property name=\"visible\">True</property>"
"                    <property name=\"xalign\">0</property>"
"                    <property name=\"xscale\">0</property>"
"                    <child>"
"                      <object class=\"GtkHBox\" id=\"hbox3\">"
"                        <property name=\"visible\">True</property>"
"                        <property name=\"spacing\">4</property>"
"                        <property name=\"homogeneous\">True</property>"
"                        <child>"
"                          <object class=\"GtkButton\" id=\"b-enable\">"
"                            <property name=\"label\" translatable=\"yes\">Enable</property>"
"                            <property name=\"visible\">True</property>"
"                            <property name=\"can_focus\">True</property>"
"                            <property name=\"receives_default\">True</property>"
"                          </object>"
"                          <packing>"
"                            <property name=\"position\">0</property>"
"                          </packing>"
"                        </child>"
"                        <child>"
"                          <object class=\"GtkButton\" id=\"b-disable\">"
"                            <property name=\"label\" translatable=\"yes\">Disable</property>"
"                            <property name=\"visible\">True</property>"
"                            <property name=\"can_focus\">True</property>"
"                            <property name=\"receives_default\">True</property>"
"                          </object>"
"                          <packing>"
"                            <property name=\"position\">1</property>"
"                          </packing>"
"                        </child>"
"                        <child>"
"                          <object class=\"GtkButton\" id=\"b-close\">"
"                            <property name=\"label\" translatable=\"yes\">Close</property>"
"                            <property name=\"visible\">True</property>"
"                            <property name=\"can_focus\">True</property>"
"                            <property name=\"receives_default\">True</property>"
"                          </object>"
"                          <packing>"
"                            <property name=\"position\">2</property>"
"                          </packing>"
"                        </child>"
"                      </object>"
"                    </child>"
"                  </object>"
"                  <packing>"
"                    <property name=\"expand\">False</property>"
"                    <property name=\"fill\">False</property>"
"                    <property name=\"position\">1</property>"
"                  </packing>"
"                </child>"
"              </object>"
"            </child>"
"          </object>"
"          <packing>"
"            <property name=\"position\">2</property>"
"          </packing>"
"        </child>"
"      </object>"
"    </child>"
"  </object>"
"  <object class=\"GtkAdjustment\" id=\"adjustment1\">"
"    <property name=\"value\">1</property>"
"    <property name=\"lower\">1</property>"
"    <property name=\"upper\">100</property>"
"    <property name=\"step_increment\">1</property>"
"    <property name=\"page_increment\">10</property>"
"    <property name=\"page_size\">10</property>"
"  </object>"
"</interface>";

