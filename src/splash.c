#include <conio.h>
#include <string.h>
#include <unistd.h>

void splash(char* name) 
{
   textcolor(COLOR_YELLOW);
   gotoxy(18,10);
   cputs("www.travellermap.com/api/poster?sector=spin");

   sleep(1);

   textcolor(COLOR_WHITE);
   gotoxy(0,16);
   cputs("               __                __                        ____            \r\n");
   cputs("         _____/ /_____ ______   / /__________ __   _____  / / /__  _____   \r\n");
   cputs("        / ___/ __/ __ `/ ___/  / __/ ___/ __ `/ | / / _ \xcd/ / / _ \xcd/ ___/   \r\n");
   cputs("       (__  ) /_/ /_/ / /     / /_/ /  / /_/ /| |/ /  __/ / /  __/ /       \r\n");
   cputs("      /____/\xcd__/\xcd__,_/_/      \xcd__/_/   \xcd__,_/ |___/\xcd___/_/_/\xcd___/_/ 0.1 \r\n");
   cputs("\r\n");
   
   textcolor(COLOR_RED);
   chline(80);

   textcolor(COLOR_GRAY2);
   gotoxy(32 - strlen(name)/2, 26);
   cprintf("current player: %s", name);

}