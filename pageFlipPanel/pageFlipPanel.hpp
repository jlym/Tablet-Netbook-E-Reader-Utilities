#ifndef PAGE_FLIP_PANEL_H
#define PAGE_FLIP_PANEL_H

#include <gtkmm/window.h>
#include <gtkmm/button.h>
#include <gtkmm.h>
#include <X11/Xlib.h>                                                     

#include <X11/keysym.h>                                                  
#include <stdio.h>                                                          
#include <string.h>                                                        
#include <iostream>   


class PageFlipPanel : public Gtk::Window
{

public:
    PageFlipPanel();
    virtual ~PageFlipPanel();

protected:
    void up_button_pressed();
    void down_button_pressed();


    Gtk::Button up_button;
    Gtk::Button down_button;
    Gtk::VBox vbox;
};

int cheese(int key);

#endif
