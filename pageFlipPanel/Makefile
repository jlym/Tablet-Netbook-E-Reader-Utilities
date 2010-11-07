# ----- Make Macros -----                                                                                                             

CXXFLAGS = 	-g -Wall -Wextra -pedantic 
CXX      =	g++
#LDFLAGS     =	`pkg-config gtkmm-2.4 --cflags --libs`
#LIBS	 =	`pkg-config gtkmm-2.4 --cflags --libs`

TARGETS =	pageFlipPanel
OBJECTS =	pageFlipPanel.o

all:	$(TARGETS)

pageFlipPanel:	$(OBJECTS)
	$(CXX) $(LDFLAGS) $(CXXFLAGS) -o  $(OBJECTS) #$(LIBS) #`pkg-config gtkmm-2.4 --cflags --libs`

pageFlipPanel.o: pageFlipPanel.cpp pageFlipPanel.hpp
