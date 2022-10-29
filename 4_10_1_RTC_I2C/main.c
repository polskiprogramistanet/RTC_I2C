/*
 * 4_10_1_RTC_I2C.c
 *
 * Created: 2022-10-28 17:43:58
 * Author : polskiprogramista.net
 */ 

#include <avr/io.h>
#define MASK_FLAG 3
uint8_t ctrl_reg = (1<<MASK_FLAG);

void TWI_start(void);
void TWI_stop(void);
void TWI_write(uint8_t bajt);
void TWI_read(uint8_t ack);
void TWI_write_buf(uint8_t SLA, uint8_t adr, uint8_t len, uint8_t *buf);

int main(void)
{
	TWI_write_buf(0xA0, 0, 1, &ctrl_reg);   
    while (1) 
    {
		

    }
}

void TWI_start(void){
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTA);
	while(!(TWCR&(1<<TWINT)));
}

void TWI_stop(void){
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
	while((TWCR&(1<<TWSTO)));
}

void TWI_write(uint8_t bajt){
	TWDR = bajt;
	TWCR = (1<<TWINT)|(1<<TWEN);
	while(!(TWCR&(1<<TWINT)));
}

void TWI_read(uint8_t ack){
	TWCR = (1<<TWINT)|(ack<<TWEA)|(1<<TWEN);
	while(!(TWCR&(1<<TWINT)));
	return TWDR;
}

void TWI_write_buf(uint8_t SLA, uint8_t adr, uint8_t len, uint8_t *buf){
	TWI_start();
	TWI_write(SLA);
	TWI_write(adr);
	while(len--) TWI_write((*buf++));
	TWI_stop();
}