//******************************************************************************
// Archivo: main.c
// Autor: Axel Mazariegos
// Fecha: 12 - julio - 2021
// Laboratorio 0 - Juego de carreras
//******************************************************************************


//******************************************************************************
// Importación de Librerías
//******************************************************************************
#include <xc.h>
#include <stdint.h>


//******************************************************************************
// Palabra de configuración
//******************************************************************************

// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT    // Oscillator Selection bits
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

#define _XTAL_FREQ 4000000

//******************************************************************************
// Variables
//******************************************************************************

uint8_t numero;
uint8_t ganador;


//******************************************************************************
// Prototipos de funciones
//******************************************************************************
void setup(void);       //Funcion para definir la configuracion inicial
void semaforo(void);
uint8_t Config_7(uint8_t numero7);
void jugador1(void);
void jugador2(void);
void revisarGanador(void);

//******************************************************************************
// Vector de interrupción
//******************************************************************************


//******************************************************************************
// Ciclo Principal
//******************************************************************************

void main(void) 
{

    setup();    //configuracion

    //**************************************************************************
    // Loop Principal
    //**************************************************************************

    while (1) 
    {
        
    while(PORTBbits.RB0 == 0);
    semaforo();
    
 
    
    
    
    
    }
}

//******************************************************************************
// Configuración
//******************************************************************************

void setup(void) {
    
    
    
    // ENTRADAS Y SALIDAS
    TRISA = 0;  // TODO A OUTPUT
    PORTA = 0;  // TODA A APAGADO 
    TRISB=0xFF; // TODO B INPUT
    PORTB = 0;  // TODA B APAGADO
    TRISC = 0;  // TODO C OUTPUT
    PORTC = 0;  // TODA C APAGADO
    TRISD = 0;  // TODO D OUTPUT
    PORTD = 0;  // TODO D APAGADO
    TRISE = 0;  // TODO E OUTPUT
    PORTE = 0;  // TODA E APAGADO
    ANSEL = 0;  // PARA NO USARLO COMO ANALOGICO
    ANSELH = 0; // PARA NO USARLO COMO ANALOGICO
    
    // OSCILADOR
    OSCCONbits.IRCF = 0b0111; //8MHz
    OSCCONbits.SCS = 1;
    
    // INTERRUPCIONES
    /*INTCONbits.GIE = 1;  //Habilitar Interrupciones Globales
    INTCONbits.RBIE = 1; //Habilitar IOC
    INTCONbits.T0IE = 1; //Habilitar Interrupciones Timer0
    
    INTCONbits.RBIF = 0; //Apagar bandera IOC
    INTCONbits.T0IF = 0; //Apagar bandera Timer0
   
    IOCBbits.IOCB0 = 1; //Interrupt-on-change enabled PB0
    IOCBbits.IOCB1 = 1; //Interrupt-on-change enabled PB1*/
    
    
            
}

//******************************************************************************
// Funciones
//******************************************************************************

uint8_t Config_7(uint8_t numero7)
{
    //recibe un valor de 8 bits que se desea ver en el 7 segmentos
    //devulve el valor apropiado para usar en un 7 segmentos
    
    uint8_t valor, seg;
    seg = numero7;
    
    switch(seg)
    {
        case 0:
            valor= 0b00111111;
            break;
        case 1:
            valor= 0b00000110;
            break;
        case 2:
            valor= 0b01011011;
            break;
        case 3:
            valor= 0b01001111;
            break;
        case 4:
            valor= 0b01100110;
            break;
        case 5:
            valor= 0b01101101;
            break;
        case 6:
            valor= 0b01111101;
            break;
        case 7:
            valor= 0b00000111;
            break;
        case 8:
            valor= 0b01111111;
            break;
        case 9:
            valor= 0b01101111;
            break;
        case 10:
            valor= 0b01110111;
            break;
        case 11:
            valor= 0b01111100;
            break;
        case 12:
            valor= 0b00111001;
            break;
        case 13:
            valor= 0b01011110;
            break;
        case 14:
            valor= 0b01111001;
            break;
        case 15:
            valor= 0b01110001;
            break;     
    }
    return valor;
}

void semaforo(void)
{
    PORTE = 0b111;
    
    PORTD = 0;      //Borrar el Puerto D
    numero = Config_7(3);  //buscar el valor del 7seg
    PORTD = numero;   //Mostrar el valor en el 7seg
    
    __delay_ms(1500);
    PORTE = 0b110;
    
    PORTD = 0;      //Borrar el Puerto D
    numero = Config_7(2);  //buscar el valor del 7seg
    PORTD = numero;   //Mostrar el valor en el 7seg
    
    __delay_ms(1500);
    PORTE = 0b100;
    
    PORTD = 0;      //Borrar el Puerto D
    numero = Config_7(1);  //buscar el valor del 7seg
    PORTD = numero;   //Mostrar el valor en el 7seg
    
    __delay_ms(1500);
    PORTE = 0b000;
    
    PORTD = 0;      //Borrar el Puerto D
    numero = Config_7(0);  //buscar el valor del 7seg
    PORTD = numero;   //Mostrar el valor en el 7seg

    
}




void jugador1(void){

    

}

void jugador2(void){

}
    

void revisarGanador(void){


}