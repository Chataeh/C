#ifndef E_H
#define E_H

#define NUM_PRIORITY 100
#define EVENT_PER_LINE 5

typedef struct {
	int event_no;//이벤트번호
	int event_gen_addr;//이벤트를 발생시킨것
	int event_handler_addr;//이벤트를 처리한것
	int event_pri;//이벤트의 우선순위
}Event;

void printEvent(Event* pEv);
void fprintEvent(FILE* fout, Event* pEv);
Event* genEvent(Event* pEvent, int event_Gen_ID, int event_no, int event_pri);



#endif 