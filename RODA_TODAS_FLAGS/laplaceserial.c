#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <sys/time.h>

#define J 10000
#define I 10000
#define tolerance 0.001
double V[I+2][J+2]; 
double W[I+2][J+2]; 
int inter=1; // contador de iterações
int numero_interacoes=12500; // total de iterações
int aux=0;
double delta_t=1.0; 


void inicializa_W(){  

// Aqui inicializamos a placa e as condições de contorno, 
//onde W é usado como a primeira iteração.


 	int i,j;
 	for(i = 0; i <= I+1; i++){
 		for (j = 0; j <= J+1; j++){
 			W[i][j] = 0.0;
 		}	
 	}
 	for(i = 0; i <= I+1; i++) {
 		W[i][0] = 0.0;
 		W[i][J+1] = (100.0/I)*i;
 	}
 	for(j = 0; j <= J+1; j++) {
 		W[0][j] = 0.0;
 		W[I+1][j] = (100.0/J)*j;
 	}
}



void evolucao(int inter) {
 	int it;
 	printf("----------- Número de iterações: %d -------------\n", inter);
 	for(it = I-5; it <= I; it++) printf("[%d,%d]: %5.2f ", it, it, V[it][it]);
 	printf("\n");
}


void novo_V(double Vmp[I+2][J+2], double Wmp_fim[I+2][J+2]){

	int i, j;
	delta_t = 0.0; 
	for(i = 1; i <= I; i++) {
 		for(j = 1; j <= J; j++) {
 			Vmp[i][j] = 0.25*(Wmp_fim[i+1][j] + Wmp_fim[i-1][j] +
 			Wmp_fim[i][j+1] + Wmp_fim[i][j-1]);
 		}
		for(j = 1; j <= J; j++){
 			delta_t = fmax( fabs(Vmp[i][j]-Wmp_fim[i][j]), delta_t);
 			Wmp_fim[i][j] = Vmp[i][j];
 		}
 	}

 
}

double calcula_laplace(double Vmp[I+2][J+2], double Wmp_fim[I+2][J+2]){

	novo_V(Vmp, Wmp_fim);
	if((inter % 100) == 0) evolucao(inter);
 	inter++;
	if(delta_t > tolerance && inter <= numero_interacoes) calcula_laplace(Vmp, Wmp_fim);
	return delta_t;
}



int main(int argc, char *argv[]) {
 	 
	int i, j;
 	struct timeval ini_temp, para_temp, andamento_temp;
	FILE *p; 
	//tempo incial
 	gettimeofday(&ini_temp,NULL); 
	//inicializações
 	inicializa_W(); 
	//Execução
	delta_t=calcula_laplace(V,W);
	//tempo de parada 
 	gettimeofday(&para_temp,NULL);
	//tempos
 	timersub(&para_temp, &ini_temp, &andamento_temp); 
	//imprime resultados
	printf("\nNúmero de iterações: %d ", inter-1);
 	printf("\nErro máximo: %f",delta_t);
 	printf("\nTempo total do programa: %f segundos\n", andamento_temp.tv_sec+andamento_temp.tv_usec/1000000.0);
	//Grava o resultado
	p = fopen("VserialOXYX.txt", "w");
	for(i=1;i<=I;i++)
	{
		for(j=1;j<=J;j++) fprintf(p, "%f ", V[i][j]);
		fprintf(p, "\n");
	}
	fclose(p);
}




