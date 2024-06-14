#include <6502.h>
#include <cx16.h>
#include <conio.h>

void set_PET_font()
{
   struct regs fontregs;

   cbm_k_bsout(CH_BLACK);
   cbm_k_bsout(0x01);  // #define TO_BACKGROUND	0x01
   textcolor(COLOR_GREEN);
   clrscr();
   gotoy(2);

   fontregs.a = 4; // PET-like
   fontregs.pc = 0xff62;
   _sys(&fontregs);
}

void setPetFont()
{
   struct regs fontregs;
   fontregs.a = 4; // PET-like
   fontregs.pc = 0xff62;
   _sys(&fontregs);
}
