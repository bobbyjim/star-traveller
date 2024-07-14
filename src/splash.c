#include <conio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

void splash(char* name) 
{
   textcolor(COLOR_GRAY2);
   gotoxy(60,1);
   cprintf("%u k free\n\n", _heapmemavail());

   gotoxy(22,5);
   cputs("map: www.travellermap.com/?p=-95!70!8");

   sleep(1);

   textcolor(COLOR_WHITE);
   gotoxy(0,8);
   cputs("               __                __                        ____            \r\n");
   cputs("         _____/ /_____ ______   / /__________ __   _____  / / /__  _____   \r\n");
   cputs("        / ___/ __/ __ `/ ___/  / __/ ___/ __ `/ | / / _ \xcd/ / / _ \xcd/ ___/   \r\n");
   cputs("       (__  ) /_/ /_/ / /     / /_/ /  / /_/ /| |/ /  __/ / /  __/ /       \r\n");
   cputs("      /____/\xcd__/\xcd__,_/_/      \xcd__/_/   \xcd__,_/ |___/\xcd___/_/_/\xcd___/_/ 0.1 \r\n");
   cputs("\r\n");
   
   textcolor(COLOR_RED);
   chline(80);

   textcolor(COLOR_WHITE);
   gotoxy(50 - strlen(name)/2, 16);
   cprintf("current player: %s", name);
}