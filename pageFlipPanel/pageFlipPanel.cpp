#include "pageFlipPanel.hpp"
#include <gtkmm.h>
#include <gtk/gtk.h>
#include <gdk/gdk.h>

int main (int argc, char* argv[])
{
    Gtk::Main kit(argc, argv);
    
    PageFlipPanel panel;

    Gtk::Main::run(panel);

    return 0;
}

PageFlipPanel::~PageFlipPanel()
{
}

PageFlipPanel::PageFlipPanel()
    : up_button("U"), down_button("D")
{
    int width = 50;

    up_button.signal_clicked().connect(
	sigc::mem_fun(*this, &PageFlipPanel::up_button_pressed));
    down_button.signal_clicked().connect(
	sigc::mem_fun(*this, &PageFlipPanel::down_button_pressed));


    vbox.pack_start(up_button, Gtk::PACK_EXPAND_WIDGET);
    vbox.pack_start(down_button);
    add(vbox);
    up_button.show();
    down_button.show();
    vbox.show();

    set_default_size(width, Gdk::screen_height());
    move(Gdk::screen_width()-width, 0);
    set_type_hint(Gdk::WINDOW_TYPE_HINT_DOCK);
    show();

    gulong val[12];
    val[0] = 0;
    val[1] = width;
    val[2] = 0;
    val[3] = 0;
    val[4] = 0;
    val[5] = 0;
    val[6] = 0;
    val[7] = 200;
    val[8] = 0;
    val[9] = 0;
    val[10] = 0;
    val[11] = 0;

    GtkWindow* gtkWindow = gobj();

    gdk_property_change(
	GTK_WIDGET(gtkWindow)->window,
	gdk_atom_intern("_NET_WM_STRUT_PARTIAL", FALSE),
	gdk_atom_intern ("CARDINAL", FALSE),
	32,
	GDK_PROP_MODE_REPLACE,
	(unsigned char *)val, 12);


}

void PageFlipPanel::up_button_pressed()
{
    int keyPress = XK_Page_Up;
    cheese(keyPress);
}

void PageFlipPanel::down_button_pressed()
{
    int keyPress = XK_Page_Down;
    cheese(keyPress);
}

XKeyEvent createKeyEvent(Display *display, Window &win,
                           Window &winRoot, bool press,
                           int keycode, int modifiers)
{
   XKeyEvent event;

   event.display     = display;
   event.window      = win;
   event.root        = winRoot;
   event.subwindow   = None;
   event.time        = CurrentTime;
   event.x           = 1;
   event.y           = 1;
   event.x_root      = 1;
   event.y_root      = 1;
   event.same_screen = True;
   event.keycode     = XKeysymToKeycode(display, keycode);
   event.state       = modifiers;

   if(press)
      event.type = KeyPress;
   else
      event.type = KeyRelease;

   return event;
}

int cheese(int keyPress)
{
   // Obtain the X11 display.
   Display *display = XOpenDisplay(0);
   if(display == NULL)
      return -1;

   // Get the root window for the current display.
   Window winRoot = XDefaultRootWindow(display);

   // Find the window which has the current keyboard focus.
   Window winFocus;
   int    revert;
   XGetInputFocus(display, &winFocus, &revert);


   // Send a fake key press event to the window.
   XKeyEvent event = createKeyEvent(display, winFocus, winRoot, true, keyPress, 0);
   XSendEvent(event.display, event.window, True, KeyPressMask, (XEvent *)&event);

   // Send a fake key release event to the window.
   event = createKeyEvent(display, winFocus, winRoot, false, keyPress, 0);
   XSendEvent(event.display, event.window, True, KeyPressMask, (XEvent *)&event);

   // Done.
   XCloseDisplay(display);

    return 0;
}
