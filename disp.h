/*_ disp.h   Fri Aug 18 1989   Modified by: Walter Bright */
/* Copyright (C) 1985-1989 by Walter Bright	*/
/* All rights reserved					*/
/* Written by Walter Bright				*/

#ifndef __DISP_H
#define __DISP_H	1	/* prevent multiple #include's		*/

#include <ncurses.h>
#include <stdarg.h>

class simWindow {

public:
	simWindow() { initscr(); raw(); keypad(stdscr,TRUE); noecho(); refresh();  } ;
	~simWindow() { endwin(); } ;
	
	
   void disp_open() { erase(); refresh(); };               // Initialize display package
   void disp_move(int y, int x) { move( y, x ); refresh(); };           // Move to "home" position
	
   void disp_eeop() { erase(); refresh(); };               // Clear the display
   void disp_hidecursor() {  curs_set(0); refresh(); };         // Make cursor invisible
   void disp_puts(const char *str)  { printw( str ) ;refresh();  };
   void disp_putc(char ch)  { addch(ch); refresh(); };

   int  disp_printf( const char *fmt , ...  ) { va_list args; va_start(args,fmt); int i = vw_printw( stdscr, fmt, args) ; va_end(args); refresh(); return(i); };	
	
   // attrset(),attron(),attroff().auto
   /* 
    A_NORMAL        Normal display (no highlight)
    A_STANDOUT      Best highlighting mode of the terminal.
    A_UNDERLINE     Underlining
    A_REVERSE       Reverse video
    A_BLINK         Blinking
    A_DIM           Half bright
    A_BOLD          Extra bright or bold
    A_PROTECT       Protected mode
    A_INVIS         Invisible or blank mode
    A_ALTCHARSET    Alternate character set
    A_CHARTEXT      Bit-mask to extract a character
    COLOR_PAIR(n)   Color-pair number n 
    */	

   void disp_startstand()  { attrset(A_REVERSE); } ;         // Begin reversed-video display
   void disp_endstand()  { standend(); };           // End reversed-video display
 
   		  
};
	   
#endif /* __DISP_H */
