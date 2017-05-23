#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include <unistd.h>
#include <time.h>


pthread_t tid[2];

//Aus Blatt 1
struct FluxCapacitor {
	unsigned char *c_string;
	unsigned int value;
};

struct FluxCapacitor *createFluxCapacitor() {

	struct FluxCapacitor *zeiger = malloc(sizeof(struct FluxCapacitor));

	//itoa(rand(), *(zeiger).c_string, 10);

	(*zeiger).c_string = malloc(sizeof(char) * 4 + 1);
	(*zeiger).c_string[0] = rand() % (126 - 33 + 1) + 33;
	(*zeiger).c_string[1] = rand() % (126 - 33 + 1) + 33;
	(*zeiger).c_string[2] = rand() % (126 - 33 + 1) + 33;
	(*zeiger).c_string[3] = rand() % (126 - 33 + 1) + 33;
	(*zeiger).c_string[4] = rand() % (126 - 33 + 1) + 33;
	(*zeiger).c_string[5] = 0;

	//Zufallszahl fuer member "value" generieren und zuweisen
	zeiger->value = 10;


	return zeiger;

}


struct FluxCapacitor** createFluxCapacitorArray(unsigned int n) {

	struct FluxCapacitor** zeiger = calloc(n, sizeof(struct FluxCapacitor));

	for (int i = 0; i < n; i++) {
		zeiger[i] = createFluxCapacitor();
	}



	return zeiger;

}

void printFluxCapacitorArray(struct FluxCapacitor** array, unsigned int n) {

	for (int i = 0; i < n; i++) {
		printf("FluxCapacitor %d \tChar: %s  \t Value: %d \n", i, array[i]->c_string, array[i]->value);
	}
}

struct DeLorean
{
	double speed_in_kmh;
	double current_power_level_in_mega_watts;
};

struct IndexContainer
{
	unsigned int* cap_indices;
	unsigned int array_length;
};


//Aufgabe 1
struct DeLorean* delorean__;
struct FluxCapacitor** capacitors__;


//Aufgabe 2
int sum = 0;

void* assembleDeLorean(void* indices_)
{

    //Cast für IC
    struct IndexContainer* ic = (struct IndexContainer*)indices_;


    //Auslesen der Elemente aus dem globalen FC Array aus IC
    int fcc;
    for(fcc = 0; fcc < ic->array_length; fcc++){
            sum += capacitors__[ic->cap_indices[fcc]]->value;
    }

    //Addieren der Summe zum Attribut current_power_level_in_mega_watts
    delorean__->current_power_level_in_mega_watts = (double)sum;




    return NULL;
}

void waitForSeonds(unsigned int secs){

    unsigned int retTime = time(0) + secs;
    while(time(0) < retTime);
}


//pid_t fork(void);

int main()
{
	//Aufgabe 1
	delorean__ = malloc(sizeof(struct DeLorean));
	capacitors__ = createFluxCapacitorArray(121);
	printFluxCapacitorArray(capacitors__, 121);

	struct IndexContainer ic1;
	ic1.cap_indices = calloc(21, sizeof(struct IndexContainer));
    ic1.array_length = 21;

    //Aufgabe 3
	//Kleiner IC
	int x;
	for(x = 0; x < 21; x++){
        ic1.cap_indices[x] = x;
	}

	struct IndexContainer ic2;
	ic2.cap_indices = calloc(100, sizeof(struct IndexContainer));
	ic2.array_length = 100;

	//Großer IC
	int y;
	for(y = 21; y < 120; y++){
       ic2.cap_indices[y] = y;
	}

	//Aufgabe 4
	pthread_t thread1, thread2;
	int rc;
	rc = pthread_create(&thread1,NULL, &assembleDeLorean, &ic1);
	if(rc != 0){
        printf("Konnte Thread 1 nicht erzeugen!\n");
        return EXIT_FAILURE;
	}

	//Warten
	pthread_join(thread1, NULL);

	rc = pthread_create(&thread2,NULL, &assembleDeLorean, &ic2);
	if(rc != 0){
        printf("Konnte Thread 2 nicht erzeugen!\n");
        return EXIT_FAILURE;
	}

	//Warten
	pthread_join(thread2, NULL);


	//Aufgabe 6
	/*pid_t pid;

	switch(pid = fork()){

    case -1:
        printf("Fehler beim fork()\n");
        break;

    case 0:
        printf("Kindprozess\n");
        if(delorean__->current_power_level_in_mega_watts == 1210){
            delorean__->speed_in_kmh = 144.1;
        }
        break;

    default:
        printf("elternprozess\n");
        //waitForSeonds(5);
        wait(pid); //warten
        break;
	}






	*/

	printf("Speed:\t\t%f Km/h!\n", delorean__->speed_in_kmh);
    printf("CPL per watt\t%d\n",(int)delorean__->current_power_level_in_mega_watts);
	printf("Wait");waitForSeonds(1);printf("#");waitForSeonds(1);printf("#");waitForSeonds(1);printf(".");waitForSeonds(1);printf(".");


	//Speicher freigeben

	free(sum);
	free(delorean__);

	//Ic1
    free(ic1.cap_indices);

	//Ic2free
    free(ic2.cap_indices);

    for(int i = 0; i < 121; i++){
        free(capacitors__[i]->c_string);
        capacitors__[i]->c_string = NULL;
        free(capacitors__[i]->value);
    }

    free(capacitors__);




	return 0;
}
