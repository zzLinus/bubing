//

#include "com.h"

char COM_value[512];
typedef struct COM_back{
	UART_HandleTypeDef *Ins;
	void (*fun)(const char *);
	char back[10];
} COM_back;


COM_back COM_data[3];
int COM_tot = 0;

char cgetc(void *p){
	char ch = -1;
	HAL_UART_Receive(p, (uint8_t*)&ch, 1, 0xffff);
	return ch;
}

void cgets(void *p, char *str, char end){
	char ch = cgetc(p);
	while(isspace(ch))
		ch = cgetc(p);
	while(ch != end){
		*(str++) = ch;
		ch = cgetc(p);
	}
	*str = '\0';
}

void cgets_s(void *p, char *str, int s){
	if(s-- > 0)
		*(str++) = cgetc(p);
	*str = '\0';
}

int cprintf(void *p, const char *format, ...){
	
	va_list ap;
	va_start(ap, format);
	
	int res = vsprintf(COM_value, format, ap);
	HAL_UART_Transmit(p, (uint8_t *)COM_value, res, 0xffff);
	
	return res;
}

void receiveInit(UART_HandleTypeDef *p, void (*f)(const char *)){
	COM_back *t = &COM_data[COM_tot++];
	t->Ins = p;
	t->fun = f;
}

void receiveSet(UART_HandleTypeDef *p, void (*f)(const char *)){
	for(int i = 0; i < COM_tot; i++){
		if(COM_data[i].Ins->Instance == COM_data[i].Ins->Instance){
			COM_back *t = &COM_data[i];
			t->Ins = p;
			t->fun = f;
		}
	}
}

void receiveStart(UART_HandleTypeDef *huart, int sz){
	for(int i = 0; i < COM_tot; i++){
		if(COM_data[i].Ins->Instance == COM_data[i].Ins->Instance){
			HAL_UART_Receive_IT(COM_data[i].Ins, (uint8_t *)COM_data[i].back, sz);
			return;
		}
	}
}
