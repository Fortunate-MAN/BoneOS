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

#include <stdio/stdio.h>
#include <misc/status_codes.h>
#include <term/terminal.h>
#include <unistd/unistd.h>
#include <boneshell/boneshell.h>
#include <string/string.h>
#include <term/terminal.h>
#include <term/values.h>
#include <term/utils.h>
#include <drv/video/VGA/vga.h>

struct cmd_opt_t* cmd_boneshell_opts[] = 
{
  0
};


int __found = 0;

void loop_terminal()
{
  while(1)
  {
    int FG__ = video_drivers[VGA_VIDEO_DRIVER_INDEX]->fg;
    int BG__ = video_drivers[VGA_VIDEO_DRIVER_INDEX]->bg;
    if(video_drivers[VGA_VIDEO_DRIVER_INDEX]->fg==0x7 && video_drivers[VGA_VIDEO_DRIVER_INDEX]->bg==0x0)
    {
      printck(2,0,"%s@boneos:",VAR_USER);
      printck(1,0,"%s",VAR_PWD);
      printck(0x0,0x7,"");
      printck(0x7,0x0," $ ");
    }
    else
    {
      printk("%s@boneos:",VAR_USER);
      printk("%s",VAR_PWD);
      printk(" $ ");
    }
    video_drivers[VGA_VIDEO_DRIVER_INDEX]->fg = FG__;
    video_drivers[VGA_VIDEO_DRIVER_INDEX]->bg = BG__;
    
    scank(true,true, "%s" , cmd_active.value);
 
    for(int i=0; cmds[i]; i++)
    {
      if(termcmp(cmds[i]->name, cmd_active.value)==0)
      {
        cmds[i]->handler(cmd_active.value);
        __found = 1;
      }
    }
    
    if(__found == 0)
    {
      printk("Invalid Command '%s' \n", cmd_active.value);
      printk("Try 'help' for more information.\n");
    }
      
    __found = 0;  
    cmd_active_index++;
  }
}

int boneshell_handler(char* cmd)
{
    size_t num_opts = get_opt_count(cmd);
    str_t opts[num_opts];
    get_opt(cmd,opts);
    
    if(strcmp(opts[1].str,"--help")==0)
        printk(cmd_boneshell.help);
    else if(num_opts==1)
       loop_terminal();
    else
        printk(cmd_boneshell.invalid_use_msg);
   
    return STATUS_OK;
}

struct cmd_t cmd_boneshell = 
{
  .name = "boneshell",
  .usage = "boneshell [--help] ",
  .help = "boneshell(1) \t\t\t\t BoneOS Terminal Manual \n"
                "NAME : \n "
                "\tboneshell\n"
                "SYNOPSIS : \n "
                "\tboneshell [--help]\n"
                "DESCRIPTION : \n "
                "\tThe General Shell For BoneOS \n "
                "\tOperating System.\n",
  .cmd_opts =  cmd_boneshell_opts,
  .handler = &boneshell_handler,
  .invalid_use_msg = "Invalid use of boneshell command.\n"
                     "Type in boneshell --help for more help.\n",
  .privilege = USER
};


