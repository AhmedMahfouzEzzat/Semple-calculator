/*
 * calc.c
 *
 * Created: 18/12/2018 04:21:46 م
 *  Author: AHMED
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define control_word 0x81	//1000 0001 ,out (portA,portB,portC_up) , in (portC_low)
#define calc_data_mode DDRD 
#define calc_addr_mode DDRB
#define calc_ctrl_mode DDRC
#define calc_data_out_port PORTD 
#define calc_data_in_port PIND
#define calc_addr_port PORTB
#define calc_ctrl_port PORTC
#define OUTPUT 0xff
#define INPUT 0x00
#define lcd_data_port 0x00
#define lcd_ctrl_port 0x01
#define keypad_port 0x02
#define calc_ctrl_reg 0x03
#define READ ~1
#define WRITE ~2
#define IDLE 0xff
#define DATA 1
#define CMD 0
#define Error "Error"
//lcd commands 
#define clr 0x01
#define display_on 0x0E
#define set_size 0x38
#define start_1st_line 0x80
#define start_2nd_line 0xC0
#define shift_cutsor_lift 0x10
#define shift_cutsor_right 0x14
		
char MyKeypad[4][4]={{'7','4','1','N'},
					{'8','5','2','0'},
					{'9','6','3','='},
					{'/','x','-','+'}};
uint8_t key_presed = 0;

void write_to_calc(uint8_t addr, uint8_t source){	
	calc_data_mode = OUTPUT; 
	calc_addr_port = addr ; 
	calc_data_out_port = source ; 
	calc_ctrl_port = IDLE; 
	calc_ctrl_port = WRITE ; 
	_delay_us(1); 
	calc_ctrl_port = IDLE;	
}			
			
void init_calc(){ 
	calc_addr_mode = OUTPUT;
	calc_ctrl_mode = OUTPUT;
	write_to_calc( calc_ctrl_reg , control_word );
}

void SEND_TO_LCD(char data , uint8_t mode )
{
	uint8_t control_lcd = 0 ;
	write_to_calc(lcd_data_port,data);
	control_lcd = mode ;			//CMD => RS=0 ,DATA =>RS =1 
	control_lcd |= 2;				// EN = 1
	write_to_calc(lcd_ctrl_port,control_lcd);
	_delay_ms(1);
	control_lcd &= ~2 ;				// EN =0
	write_to_calc(lcd_ctrl_port,control_lcd);
}

void INIT_LCD()
{
	SEND_TO_LCD(set_size,CMD);
	SEND_TO_LCD(clr,CMD);
	SEND_TO_LCD(display_on,CMD)	;
}

void write_to_LCD(char ch){
	SEND_TO_LCD(ch,DATA);
}

void print_to_LCD(char *str){
	while(*str != '\0')
	{
		write_to_LCD(*str);
		str++;
	}
}

void write_to_keypad(uint8_t source){
	calc_data_mode = 0XF0; 
	calc_addr_port = keypad_port ; 
	calc_data_out_port = source ; 
	calc_ctrl_port = IDLE; 
	calc_ctrl_port = WRITE ; 
	_delay_ms(10); 
	calc_ctrl_port = IDLE;
}
uint8_t read_from_keypad()
{
	uint8_t temp;
	calc_data_mode = 0X00; 
	calc_addr_port = keypad_port ; 
	calc_ctrl_port = IDLE; 
	calc_ctrl_port = READ ;
	temp = calc_data_in_port ;
	_delay_ms(10);
	calc_ctrl_port = IDLE; 
	return temp ;
}

char get_key_presed(){
	uint8_t OUT_VAL[4] ={0XEF,0XDF,0XBF,0X7F};
	while (1)
	{
		for (uint8_t i=0;i<4;i++)
		{
			uint8_t tmp;
			write_to_keypad(OUT_VAL[i]);
			tmp = read_from_keypad();
			tmp &= 0X0F;
			switch (tmp) {
				case 0X0E :	_delay_ms(300) ; return MyKeypad[i][0]; break;
				case 0X0D : _delay_ms(300) ; return MyKeypad[i][1]; break;
				case 0X0B : _delay_ms(300) ; return MyKeypad[i][2]; break;
				case 0X07 :	_delay_ms(300) ; return MyKeypad[i][3]; break;
			}					
		}		
	}
}

int Sign_to_Unsign(char *sign,int Num ,int x){
	/*int mul=1;
	if (sign[Num]=='-') Num++,mul=-1;
	int ret=0;
	while(Num<=x){
		ret+=sign[Num]-'0';
		ret*=10;
		Num++;
	}
	return (ret/10)*mul;*/
}
 
int res(int firNum ,int SecNum,char op){
		/*if (op=='+') return firNum+SecNum;
		if (op=='-') return firNum-SecNum;
		if (op=='x') return firNum*SecNum;
		if (op=='/'){
			if(SecNum=0)
			  write_to_LCD(Error);
			else
			  return firNum/SecNum;  
		} */			
}

void operate(){
	/*while (1)
	{
		memset(arr,0,sizeof(arr));
		for (int i=0;i<pixels;i++)
		{
			arr[i]= Read_from_keypad();
			LCD_cmd(arr[i],0);
			if (arr[i]=='o')
			{
				LCD_cmd(0X01,1);
				LCD_cmd(0X0E,1);
				
				break;
			}
			if (arr[i]=='=') return ;
		}
	}*/
}

void to_string(int in){ 
	/*memset(arr,0,sizeof(arr));
	if (in==0) {
		arr[0]='0';
		return;
	}
	char tarr[10];
	memset(tarr,0,sizeof(tarr));
	int ptr=0,tmp=in;
	if (in<0)in*=-1;
	while (in)
	{
		tarr[ptr++]=(in%10)+'0';
		in/=10;
	}
	if (tmp<0) tarr[ptr++]='-';
	for (int i=0;i<ptr;i++) arr[i]=tarr[ptr-1-i];*/
}

int calculate(){
	/*int pos=-1,sz=strlen(arr),f,s,mid;
	char op,nop;
	for (int i=sz-2;i>=0;i--)
	{
		if (arr[i]>'9'||arr[i]<'0')
		{
			op=arr[i];
			pos=i;
			break;
		}
	}
	int numpos=-1;
	for (int i = pos-1; i >0 ; i--)
	{
		if (arr[i]>'9'||arr[i]<'0')
		{
			nop=arr[i];
			numpos=i;
			break;
		}
	}
	if (numpos!=-1) {
		f=Sign_to_Unsign(arr,0,numpos-1);
		mid=Sign_to_Unsign(arr,numpos+1,pos-1);
		s=Sign_to_Unsign(arr,pos+1,sz-2);
		int t=res(f,mid,nop);
		return res(t,s,op);
	}else{
		f=Sign_to_Unsign(arr,0,pos-1);
		s=Sign_to_Unsign(arr,pos+1,sz-2);
		return res(f,s,op);
	}
*/
}

int main(void)
{
	init_calc();
	INIT_LCD();
	print_to_LCD("hello");
	_delay_ms(1000);
	SEND_TO_LCD(clr,CMD);
	SEND_TO_LCD(start_1st_line,CMD);
	while(1)
	{
		char ch = get_key_presed();
		write_to_LCD(ch);
	}
	return 0;
}