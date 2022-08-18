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


#define MONEDA_25 PORTCbits.RC0 
#define MONEDA_50 PORTCbits.RC1
#define MONEDA_100 PORTCbits.RC2
#define MONEDA_200 PORTEbits.RE0 

unsigned char estado=0,cafe=0, boton=0,pulsador=0,tiempo_lectura_adc=0,decena=0,centena=0,unidad=0,valor_pote=0,contador=0,aux25=0,aux50=0,aux100=0,aux200=0;
unsigned int monto=0,tiempo1=0,tiempouno=0,tiempo=0,numero=0;
int precio=0;

/*variables globales ********************************************************/
/*Nombro casos de maquina de estado *****************************************/
enum{
    MENU_PRINCIPAL,
    MOSTRAR_CAFE_UNO,
    MOSTRAR_CAFE_DOS,
    MOSTRAR_CAFE_TRES,
    MOSTRAR_CAFE_CUATRO,
    MOSTRAR_CAFE_CINCO,
    MOSTRAR_CAFE_SEIS,
    MOSTRAR_CAFE_SIETE,
    MONEDERO,
    PREPARANDO_CAFE,
    RETIRE_CAFE,
    ERROR,
            
            

};
void main(void) {
    
   //PIC EN SIMULIDE A 48MHz
   PicIni13();
   TIMER0_INI();
    {                           //inicio TIMER0
        INTCONbits.TMR0IF = 0; //desactivo TMR0IF
        INTCONbits.GIE = 1;    //activo la interrupcion general
        T0CONbits.TMR0ON = 1;  //activo TMR0
    }        
   LCD_init(); 
   tecladoIni13();



    while(1){
        boton = tecla();
        pulsador=Botones13();

        
        switch(estado){
            /*INICIO MENU PRINCIPAL PARA QUE EL CLIENTE ELIJA CAFE **********/
            case MENU_PRINCIPAL:
                S1 = 0; //LD3
                S2 = 0; //LC6
                S3 = 0; //LC7
                LED1 = 0;  //DESACTIVO MONEDERO
                set_CURSOR(0x00);
                msg2LCD("ELIJA SU CAFE:");
                set_CURSOR(0x40);
                msg2LCD("<1-2-3-4-5-6-7->");
                
                /*PREGUNTO POR LOS ESTADOS DE LOS BOTONES. 
                 * POR BOTON HAY UN CAFE ASIGNADO **********/
                if(boton == 1){
                    LED1=1;
                    clear_LCD();
                    estado=MOSTRAR_CAFE_UNO;  /*EN EL CASO DE QUE BOTON ESTE PRESIONADO           *  PASO AL SIGUIENTE ESTADO*/                   
                }
                
                /*HAGO LO MISMO CON TODOS LOS OTRO BOTONES**********/
                if(boton == 2){
                    LED1=1;
                    clear_LCD();
                    estado=MOSTRAR_CAFE_DOS;
                }
                
                if(boton == 3){
                    LED1=1;
                    clear_LCD();
                    estado=MOSTRAR_CAFE_TRES;
                }

                if(boton == 4){
                    LED1=1;
                    clear_LCD();
                    estado=MOSTRAR_CAFE_CUATRO;
                }
                
                if(boton == 5){
                    LED1=1;
                    clear_LCD();
                    estado=MOSTRAR_CAFE_CINCO;
                }
                
                if(boton == 6){
                    LED1=1;
                    clear_LCD();
                    estado=MOSTRAR_CAFE_SEIS;
                }
                
                if(boton == 7){
                    LED1=1;
                    clear_LCD();
                    estado=MOSTRAR_CAFE_SIETE;
                }
            break; 
            
            case MOSTRAR_CAFE_UNO:
                cafe=1;
                set_CURSOR(0x00);
                msg2LCD("CAFE AMARGO");//MUESTRO EL CAFE QUE ESCOGIÓ EL CLIENTE
                set_CURSOR(0x40);
                msg2LCD("Precio >> $2,50");
                precio=250;  
                estado=MONEDERO;
                LED1 = 1;  //ACTIVO MONEDERO
                tiempo=5000;
            break;
            case MOSTRAR_CAFE_DOS:
                cafe=2;
                set_CURSOR(0x00);
                msg2LCD("CAFE DULCE");//MUESTRO EL CAFE QUE ESCOGIÓ EL CLIENTE
                set_CURSOR(0x40);
                msg2LCD("Precio >> $3,50");
                precio=350;  
                estado=MONEDERO;
                LED1 = 1;  //ACTIVO MONEDERO
                tiempo=5000;
            break;            
            case MOSTRAR_CAFE_TRES:
                cafe=3;
                set_CURSOR(0x00);
                msg2LCD("LECHE AMARGO");//MUESTRO EL CAFE QUE ESCOGIÓ EL CLIENTE
                set_CURSOR(0x40);
                msg2LCD("Precio >> $2,75");
                precio=275;  
                estado=MONEDERO;
                LED1 = 1;  //ACTIVO MONEDERO
                tiempo=5000;
            break;
            case MOSTRAR_CAFE_CUATRO:
                cafe=4;
                set_CURSOR(0x00);
                msg2LCD("LECHE DULCE");//MUESTRO EL CAFE QUE ESCOGIÓ EL CLIENTE
                set_CURSOR(0x40);
                msg2LCD("Precio >> $3,25");
                precio=325; 
                estado=MONEDERO;
                LED1 = 1;  //ACTIVO MONEDERO
                tiempo=5000;
            break;            
            case MOSTRAR_CAFE_CINCO:
                cafe=5;
                set_CURSOR(0x00);
                msg2LCD("LECHE MUY DULCE");//MUESTRO EL CAFE QUE ESCOGIÓ EL CLIENTE
                set_CURSOR(0x40);
                msg2LCD("Precio >> $3,50");
                precio=350;  
                estado=MONEDERO;
                LED1 = 1;  //ACTIVO MONEDERO
                tiempo=5000;                
            break;
            case MOSTRAR_CAFE_SEIS:
                cafe=6;
                set_CURSOR(0x00);
                msg2LCD("CAPUCHINO AMARGO");//MUESTRO EL CAFE QUE ESCOGIÓ EL CLIENTE
                set_CURSOR(0x40);
                msg2LCD("Precio >> $4,00");
                precio=400 ;
                estado=MONEDERO;
                LED1 = 1;  //ACTIVO MONEDERO
                tiempo=5000;

            break;            
            case MOSTRAR_CAFE_SIETE:
                cafe=7;
                set_CURSOR(0x00);
                msg2LCD("CAPUCHINO DULCE");//MUESTRO EL CAFE QUE ESCOGIÓ EL CLIENTE
                set_CURSOR(0x40);
                msg2LCD("Precio >> $4,25");
                precio=425;  
                estado=MONEDERO;
                LED1 = 1;  //ACTIVO MONEDERO
                tiempo=5000;
            break;
            
            
            case MONEDERO:
                
                centena = precio/100;
                decena = (precio%100)/10;
                unidad = (precio%100)%10;
                
                set_CURSOR(0x4B);
                char2LCD(centena+48);
                set_CURSOR(0x4C);
                char2LCD(',');
                set_CURSOR(0x4D);
                char2LCD(decena+48); 
                set_CURSOR(0x4E);
                char2LCD(unidad+48);   


                    if(aux25==0){
                        if(MONEDA_25==0){
                                precio=precio-25;
                                aux25=1;
                                contador++;
                        }
                    }

                    if(MONEDA_25==1){
                        aux25=0;
                    }
                
                    if(aux25==0){
                        if(MONEDA_50==0){
                                precio=precio-50;
                                aux50=1;
                                contador++;
                        }
                    }

                    if(MONEDA_50==1){
                        aux50=0;
                    }
                    if(aux200==0){
                        if(MONEDA_200==0){
                                precio=precio-200;
                                aux200=1;
                                contador++;
                        }
                    }

                    if(MONEDA_200==1){
                        aux200=0;
                    }
                    if(aux100==0){
                        if(MONEDA_100==0){
                                precio=precio-100;
                                aux100=1;
                                contador++;
                        }
                    }

                    if(MONEDA_100==1){
                        aux100=0;
                    }
                

                
                if(precio<=0){
                    LED1 = 0;  //apago MONEDERO
                    clear_LCD();
                    estado = PREPARANDO_CAFE;
                    
                    
                    if(cafe==1||cafe==2||cafe==6)tiempo=15000;
                    if(cafe==3||cafe==4||cafe==5||cafe==7)tiempo=25000;
                }
                
                
                if(tiempo==0){//time out
                    LED1 = 0;  //apago MONEDERO
                    clear_LCD();
                    estado = ERROR;
                    tiempouno = 5000;
                }
                
                
            break;  //PASO AL SIGUENTE ESTADO
            
            case PREPARANDO_CAFE:
                set_CURSOR(0x00);
                msg2LCD("PREPARANDO...");
                
                if(cafe==1){
                    S1 = 0; //LD3
                    S2 = 0; //LC6
                    S3 = 1;
                    
                }
                if(cafe==2){
                    S1 = 0; //LD3
                    S2 = 1; //LC6
                    S3 = 0;         
                }
                if(cafe==3){
                    S1 = 0; //LD3
                    S2 = 1; //LC6
                    S3 = 1;
                    
                }
                if(cafe==4){
                    S1 = 1; //LD3
                    S2 = 0; //LC6
                    S3 = 0;         
                }
                if(cafe==5){
                    S1 = 1; //LD3
                    S2 = 0; //LC6
                    S3 = 1;         
                }
                if(cafe==6){
                    S1 = 0; //LD3
                    S2 = 1; //LC6
                    S3 = 0;
                    
                }
                if(cafe==7){
                    S1 = 1; //LD3
                    S2 = 1; //LC6
                    S3 = 0;         
                }
                
                
                
                if(tiempo==0){
                    estado=RETIRE_CAFE;
                    tiempo=25000;
                    tiempouno=5000;
                    S1 = 0; //LD3
                    S2 = 0; //LC6
                    S3 = 0;
                }
                
            break;
            case RETIRE_CAFE:
                set_CURSOR(0x00);
                msg2LCD("Sirviendo...");
                
                if(tiempouno == 0){
                    msg2LCD("Disfrute su cafe");
                }

                if(tiempo == 0){
                    estado = MENU_PRINCIPAL;
                }
                break;
            case ERROR:
                set_CURSOR(0x00);
                msg2LCD("ERROR!!");
                clear_LCD();

                if(tiempouno == 0){
                    estado = MENU_PRINCIPAL;
                }
                break;                
            
            /*HAGO LO MISMO EN CON CADA CAFE. CAMBIO EL IMPORTE, EL TIEMPO
             * Y ACTIVO SALIDAS CORRESPONDIENTES A CADA CAFE */
            
         
                
                
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
        if(tiempouno!=0){
            tiempouno--;
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