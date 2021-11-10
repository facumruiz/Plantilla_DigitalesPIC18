/****************************************************************************
 * File:   main.c                                                           *
 * Author: Esteban Lemos                                                    *
 * Created on 5 de febrero de 2014, 20:49                                   *
 * En caso de necesitar el proyecto completo ingresar en                    *
 * https://github.com/EEST1/Plantilla_6to                                   *
 ****************************************************************************/

#include <xc.h>
#include "confbits.h"       //no se debe de modificar este archivo para
                            //garantizar el funcionamiento del BOOTLOADER

#include "Tecnica1.h"       //segun el shield habilita distintas librerias
#include "ConfShield1_3.h"
#include "lcd.h"
#include "teclado.h"

unsigned char boton=0,pulsador=0,tiempo_lectura_adc=0,dec=0,cent=0,uni=0,valor_pote=0;
unsigned int tiempo=0,numero=0;
/*variables globales ********************************************************/
void main(void) {
    
   //IMPORTANTE CAMBIAR FRECUENCIA PIC EN SIMULIDE A 48MHz
   PicIni13();
   TIMER0_INI();
    {                                                                           //inicio TIMER0
        INTCONbits.TMR0IF = 0;                                              //desactivo TMR0IF
        INTCONbits.GIE = 1;                                                //activo la interrupcion general
        T0CONbits.TMR0ON = 1;                                              //activo TMR0
    }        
   LCD_init(); 
   tecladoIni13();
   msg2LCD("Tecla: ");
   set_CURSOR(0x40);
   msg2LCD("Adc: ");
   set_CURSOR(0x4A);
   msg2LCD("Puls:");
    while(1){
        
        boton = tecla(); //TECLADO MATRICIAL
        if(boton!=0xFF){
            set_CURSOR(0x07);// Pone el cursor donde quiero (0x00 a 0x0F el 1er renglón, 0x40 a 0x4F el 2do)
            char2LCD(boton+48);
        }
        
        
        /*-----ESTO LEE LOS PULSADORES-----*/
        
        pulsador=Botones13();
        if(pulsador==1){
            set_CURSOR(0x4F);// Pone el cursor donde quiero (0x00 a 0x0F el 1er renglón, 0x40 a 0x4F el 2do)
            char2LCD('1');         
        }
        if(pulsador==2){
            set_CURSOR(0x4F);// Pone el cursor donde quiero (0x00 a 0x0F el 1er renglón, 0x40 a 0x4F el 2do)
            char2LCD('2');         
        }
        if(pulsador==3){
            set_CURSOR(0x4F);// Pone el cursor donde quiero (0x00 a 0x0F el 1er renglón, 0x40 a 0x4F el 2do)
            char2LCD('3');         
        }
        if(pulsador==4){
            set_CURSOR(0x4F);// Pone el cursor donde quiero (0x00 a 0x0F el 1er renglón, 0x40 a 0x4F el 2do)
            char2LCD('4');         
        }   
        
        
        /*-------------------*/
        
        
        //MUESTRO UN NUMERITO QUE SE INCREMENTA AL COSTADO
        if(tiempo==0){
            tiempo=500;
            LED9=~LED9;
            
            if(numero<9)numero++;
            else numero=0;
            
            set_CURSOR(0x0F);// Pone el cursor donde quiero (0x00 a 0x0F el 1er renglón, 0x40 a 0x4F el 2do)
            char2LCD(numero+48);
            
        }
        
        
        
        //LEO Y MUESTRO ADC
        if(tiempo_lectura_adc==0){
            tiempo_lectura_adc=20;
            valor_pote=obtener_ADC8();
            
            cent=valor_pote/100;
            dec=(valor_pote%100)/10;
            uni=(valor_pote%100)%10;
            
            set_CURSOR(0x45);
            char2LCD(cent+48);
            set_CURSOR(0x46);
            char2LCD(dec+48);
            set_CURSOR(0x47);
            char2LCD(uni+48);
            
        }
 
    }    
}


void __interrupt () my_isr_routine (void){  
    if (TMR0IF ==1)
    {   
        TMR0IF=0;
        TMR0L = 209;                    //el timer contará 47 fosc/4 * 256 = 12032 * 0,0833us
        TMR0H = 0xFF; 
        //tic_LCD(); 
        tic_teclado();
        tic_bot();
        if(tiempo!=0){
            tiempo--;
        }
        if(tiempo_lectura_adc!=0){
            tiempo_lectura_adc--;
        }
    }
    if (RBIF) {                                                                 //si RBIF es 1
        marca_tecla(); 
        RBIF=0;
    }
}