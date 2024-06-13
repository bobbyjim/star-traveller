#ifndef _UWP_H_
#define _UWP_H_

#define		UWP_BANK			1
#define		WORLD_ZNAME_BANK	2

//
// 8 bytes per world name = 1024 entries in an 8K bank.
//
typedef struct {

    // Up to 12 chars.  Should be plenty.
	unsigned int zname[4];

} WorldZName;

//
//  8 bytes per entry = 1024 entries in an 8K bank.
//
typedef struct {

    // 0000 - 8192
	int  location  :13;
	int  belt      :1;
	int  gg        :1;
    int  satellite :1;

    int  alleg     :5;
	int  ancients  :1;
    int  capital   :1;
    int  hellworld :1;
    int  icecapped :1;
    int  military  :1;
    int  reserve   :1;
    int  research  :1;
	int  starport_and_bases :4;
	/*
		11 11	A + NS
		11 10	A + N
		11 01	A + S
		11 00	A
		10 11	B + NS
		10 10	B + N
		10 01	B + S
		10 00	B
		01 11	C + S
		01 10	C
		01 01	D + S
		01 00	D
		00 11	E
		00 10   X
		00 01	Corsair Base
		00 00	?
	 */
	
	int  siz :4;
	int  atm :4;
	int  hyd :4;
	int  pop :4;

	int  gov :4;
	int  law :4;
	int  tl  :5;
	int  surveyed  :1;
	int  zone      :2;

} UWP;

#endif