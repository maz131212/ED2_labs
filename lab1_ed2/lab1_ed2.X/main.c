//******************************************************************************
// Archivo: main.c
// Autor: Axel Mazariegos
// Fecha: 15 - julio - 2021
// Laboratorio 1 - Interrupciones y librerias
//******************************************************************************


//******************************************************************************
// Importación de Librerías
//******************************************************************************
#include <xc.h>
#include <stdint.h>
#include "ADC.h"


//******************************************************************************
// Palabra de configuración
//******************************************************************************

// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT    // Oscillator Selection bits#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator: Crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
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
uint8_t v_tmr0;      //banderas para el anti rebote de cada una de los botones
uint8_t count;       //contador de pulsos de cada boton
uint8_t b_inc;
uint8_t b_dec;


uint8_t VAR;

uint8_t banderaT0;




//******************************************************************************
// Prototipos de funciones
//******************************************************************************
void setup(void);       //Funcion para definir la configuracion inicial


//******************************************************************************
// Vector de interrupción
//******************************************************************************
void __interrupt() ISR(void){
    
    // INTERRUPT ON CHANGE 
    if (INTCONbits.RBIF)   
    {
        if (PORTBbits.RB0 == 1) {b_inc = 1;}
        if (PORTBbits.RB0 == 0 && b_inc == 1) 
            { 
                b_inc = 0;      
                PORTC++;        
            }                   

        if (PORTBbits.RB1 == 1){b_dec = 1;}
        if (PORTBbits.RB1 == 0 && b_dec == 1) 
            {
                b_dec = 0;       
                PORTC--;          
            }  

        INTCONbits.RBIF = 0;   
    }
    
    // INTERRUPCION DEL ADC
    if (PIR1bits.ADIF)
    {   
        VAR = readADC();
        PORTD = VAR;
    }
    
    
}

//******************************************************************************
// Ciclo Principal
//******************************************************************************

void main(void) 
{

    setup();    //CONFIGURACION

    //**************************************************************************
    // Loop Principal
    //**************************************************************************

    while (1) 
    {
        
    ADCON0bits.GO_DONE = 1;
    __delay_us(50);
    
    }
}

//******************************************************************************
// Configuración
//******************************************************************************

void setup(void) {
    
    
    // ENTRADAS Y SALIDAS
    TRISA=0x01; // A01 INPUT
    PORTA = 0;  // TODA A APAGADO 
    TRISB=0xFF; // TODO B INPUT
    PORTB = 0;  // TODA B APAGADO
    TRISC = 0;  // TODO C OUTPUT
    PORTC = 0;  // TODA C APAGADO
    TRISD = 0;  // TODO D OUTPUT
    PORTD = 0;  // TODO D APAGADO
    TRISE = 0;  // TODO E OUTPUT
    PORTE = 0;  // TODA E APAGADO
    ANSEL=0x01; // PARA USAR PORTA0 COMO ANALOGICO
    ANSELH = 0; // PARA NO USARLO COMO ANALOGICO
    
  
    // OSCILADOR
    OSCCONbits.IRCF = 0b0110; //8MHz
    OSCCONbits.SCS = 1;
    
    
    // INTERRUPCIONES
    PIR1bits.ADIF = 0;  //Limpiar la bandera de interrupcion ADC
    PIE1bits.ADIE = 1;  //Habilitar la interrupcion ADC
    
    INTCONbits.PEIE = 1; //Habilitar interrupciones Perifericas
    INTCONbits.GIE = 1;  //Habilitar Interrupciones Globales
    INTCONbits.RBIE = 1; //Habilitar IOC
   
    IOCBbits.IOCB0 = 1; //Interrupt-on-change enabled PB0
    IOCBbits.IOCB1 = 1; //Interrupt-on-change enabled PB1
    
    
    
    // CONFIGURACION MODULO ADC
    ADCON0bits.ADCS1 = 0;
    ADCON0bits.ADCS0 = 1;    
    
    ADCON1bits.VCFG0 = 0;
    ADCON1bits.VCFG1 = 0;

    ADCON1bits.ADFM = 0; //Justificado a la izquierda
    
    ADCON0bits.ADON = 1;
    
    ADCON0bits.CHS = 0; //AN0 en el PORTA0
    __delay_us(50);
    
    ADCON0bits.GO_DONE = 1;
    __delay_ms(5);
   
            
}

//******************************************************************************
// Funciones
//******************************************************************************



