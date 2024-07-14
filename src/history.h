#ifndef _HISTORY_H_
#define _HISTORY_H_

typedef struct {

	int 	date : 16;
	char 	event[78];

} HistoryItem;

void history_add(char* msg);
void history_show();

#endif
