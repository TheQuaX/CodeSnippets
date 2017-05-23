#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>


struct FluxCapacitor{
    unsigned char *c_string;
    unsigned int value;
};

//AUFGABE 1
struct FluxCapacitor *createFluxCapacitor(){

    struct FluxCapacitor *zeiger = malloc(sizeof(struct FluxCapacitor));

    //(*zeiger).c_string = malloc(sizeof(int)*8+1);
    //itoa(rand(), *(zeiger).c_string, 10);

    (*zeiger).c_string = malloc(sizeof(char)*4+1);
    (*zeiger).c_string[0] = rand() % (126 - 33 + 1) + 33;
    (*zeiger).c_string[1] = rand() % (126 - 33 + 1) + 33;
    (*zeiger).c_string[2] = rand() % (126 - 33 + 1) + 33;
    (*zeiger).c_string[3] = rand() % (126 - 33 + 1) + 33;
    (*zeiger).c_string[4] = rand() % (126 - 33 + 1) + 33;
    (*zeiger).c_string[5] = 0;

    //Zufallszahl fr member "value" generieren und zuweisen
    zeiger->value = rand();


    return zeiger;

}



//AUFGABE 2
struct FluxCapacitor** createFluxCapacitorArray(unsigned int n){

    struct FluxCapacitor** zeiger = calloc(n, sizeof(struct FluxCapacitor));

    int i; //C89
    for(i = 0; i < n; i++){
            zeiger[i] = createFluxCapacitor();
    }



    return zeiger;

}

//AUFGABE 3
void printFluxCapacitorArray(struct FluxCapacitor** array, unsigned int n){

    int i;
    for(i = 0; i < n; i++){
        printf("Flux %d: s\tChar: %s\t  Value: %d \n", i+1, array[i]->c_string,array[i]->value);
    }
}

//AUFGABE 4
void bubbleSortFluxCapacitorArray(struct FluxCapacitor** array, unsigned int n){

    int i, j; //Zhlindizes
    struct FluxCapacitor* tmp; //Hilfsvariable

    //Durch das ganze array gehen
    for(i = 0; i < n; i++){
            //am Ende beginnen das kleinste Element zu suchen
            for(j = n - 1; j > i; j--){
                //prfen ob das Element kleiner als der Vorgnger ist
                if(array[j]->value < array[j -1]->value){
                    //Werte vertauschen
                    tmp = array[j];
                    array[j]= array[j-1];
                    array[j - 1] = tmp;
                }
            }
    }

}



int main(){
    srand(time(NULL));
    printf("Programmstart!\n");

    //AUFGABE 5
    struct FluxCapacitor **Fcapas = malloc(10 * sizeof(struct FluxCapacitor));
    Fcapas = createFluxCapacitorArray(10);
    printf("\nunsorted:\n");
    printFluxCapacitorArray(Fcapas,10);
    bubbleSortFluxCapacitorArray(Fcapas, 10);
    printf("\nSorted:\n");
    printFluxCapacitorArray(Fcapas,10);

    //Speicher freigeben
    free(Fcapas);



    return 0;
}
