/**
 ** This file is part of BoneOS.
 **
 **   BoneOS is free software: you can redistribute it and/or modify
 **   it under the terms of the GNU General Public License as published by
 **   the Free Software Foundation, either version 3 of the License, or
 **   (at your option) any later version.

 **   BoneOS is distributed in the hope that it will be useful,
 **   but WITHOUT ANY WARRANTY; without even the implied warranty of
 **   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 **   GNU General Public License for more details.

 **   You should have received a copy of the GNU General Public License
 **   along with BoneOS.  If not, see <http://www.gnu.org/licenses/>.
 **
 **  @main_author : Amanuel Bogale
 **  
 **  @contributors:

 **     Amanuel Bogale <amanuel2> : start
 **/ 


#include <drv/video/VGA/textmode/80x25/putch/putch.h>
#include <libc/string/memset/memset.h>
#include <drv/video/VGA/textmode/80x25/utils.h>


extern size_t terminal_column;
extern size_t terminal_row;
extern uint8_t FG; // Foreground - White
extern uint8_t BG; // Background - BLACK 
extern const size_t VGA_WIDTH;
extern const size_t VGA_HEIGHT; 

void term_zero()
{
  terminal_row=0;
  terminal_column=0;
}

/*
 * @function cls:
 *    Function for clearing
 *    the screen in normal text
 *    mode 80x25 VGA.
 */


void clear_vga_80_x_25()    
{
  term_zero();
  for(int i=0; i<80; i++)
  {
    for(int j=0; j<25; j++)
    {
        const size_t index =  (terminal_row * 80 +  terminal_column);
        uint16_t* VideoMemory = (uint16_t*)0xB8000;
        uint8_t terminal_color = make_color(FG,BG);
        
        VideoMemory[index] = make_vgaentry(' ', terminal_color);
        VideoMemory[index+1] = make_vgaentry(' ', terminal_color);

        VideoMemory[index]= (VideoMemory[index] & 0xFF00)|(char)0;
        terminal_column++;
    }
  }
  term_zero();
}