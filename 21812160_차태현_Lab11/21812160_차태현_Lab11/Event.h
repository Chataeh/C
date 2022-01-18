#ifndef E_H
#define E_H

#define NUM_PRIORITY 100
#define EVENT_PER_LINE 5

typedef struct {
	int event_no;//�̺�Ʈ��ȣ
	int event_gen_addr;//�̺�Ʈ�� �߻���Ų��
	int event_handler_addr;//�̺�Ʈ�� ó���Ѱ�
	int event_pri;//�̺�Ʈ�� �켱����
}Event;

void printEvent(Event* pEv);
void fprintEvent(FILE* fout, Event* pEv);
Event* genEvent(Event* pEvent, int event_Gen_ID, int event_no, int event_pri);



#endif 