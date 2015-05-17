//Practica 3 Karina Robledo Hernández

#include <stdio.h>
#include <string.h>

unsigned invert(unsigned x,int p,int n)
{ 
	return (((~(~0 << p + n) & (~0 << p)) & ~x) | ((( ~0 << p+n) | ~(~0 <<p)) & x) ); 
} 

int analizarLLC(unsigned char t[], int tam)
{
	//Espacio para invertir bytes
	
	//Uniendo el byte de control
	short control[2];
	short pf, ns, nr;
//	printf("Bit 17: %x \n", t[17]);
	if(t[17] == 0x00)
	{
		control[0] = t[16];
		pf = (t[16] >> 3) & 1;
		printf("Control de 8 bits \t control: %x \t pf: %x\n", control[0], pf);
		//Ver el tipo
		if(control[0] <= 0x7f){
		printf("Tipo I \n");
		ns = (control[0] >> 4) & 7;
		nr = control[0] & 7;
		printf("Ns: %d \t Nr: %d\n", ns, nr);
		}
		else if(control[0] <= 0xbf){
		printf("Tipo S \n");
		ns = (control[0] >> 4) & 3;
		nr = control[0] & 7;
		printf("Cod: %d \t Nr: %d\n", ns, nr);
			switch(ns)
			{
			case 0:
				printf("RR - Listo para recibir\n");
			break;
			case 1:
				printf("REJ - Rechazo\n");
			break;
			break;
			case 2:
				printf("RNR - No listo para recibir \n");
			break;
			case 3:
				printf("SREJ - Rechazo selectivo \n");
			break;
			default:
				printf("Error \n");
			break;
			}
		}
		else {
		printf("Tipo U\n");
		ns = (control[0] >> 4) & 3;
		nr = control[0] & 7;
		printf("Cod: %d \t Nr: %d\n", ns, nr);
		}

	}
	else{
		control[0] = t[16];
		control[1] = t[17];
		pf = t[17] >> 7;
		printf("Control de 16 bits \t control: %x  %x\t pf: %x\n", control[0], control[1], pf);
		//Ver el tipo
		if(control[0] <= 0x7f){
		printf("Tipo I \n");
		ns = control[0] & 127;
		nr = control[1] & 127;
		printf("Ns: %d \t Nr: %d\n", ns, nr);
		}
		else if(control[0] <= 0xbf){
		printf("Tipo S \n");
		ns = (control[0] >> 4) & 3;
		nr = control[1] & 127;
		printf("Cod: %d \t Nr: %d\n", ns, nr);
		}
		else {
		printf("Tipo U\n");
		ns = (control[0] >> 4) & 3;
		nr = control[0] & 7;
		printf("Cod: %d \t Nr: %d\n", ns, nr);
		}

	}
	

}

int analizarTrama(unsigned char t[], int tam)
{
	short tipo;
	tipo = (t[12] << 8) + t[13];
//	printf("%x\t %x\t%d\n", t[12], t[13], tipo);
	if(tipo < 1500){
        printf("Tipo: LLC\n");
        analizarLLC(t, tam);
    }
    else{
	
        if(tipo == 2048){
        printf("Tipo: IP\n");
		}
		else if(tipo == 2054){
        printf("Tipo: ARP\n");
    	}else{
    		printf("Ninguna\n");
		}
   }
   return 0;
}

int main(void){

	int tam;
	unsigned char tram[] = {0x00, 0x02, 0xb3, 0x9c, 0xae, 0xba, 0x00, 0x02, 0xb3, 0x9c, 0xdf, 0x1b, 0x00, 0x03, 0xf0, 0xf0,
0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x43, 0x05, 0x90, 0x6d};

	tam = sizeof(tram)/sizeof(char);
	printf("Trama \n");
	analizarTrama(tram, tam);

}
