//HW2

#include <iostream>
#include <pthread.h>
#include <string>

using namespace std;

//prototypes
void *reader(void *arg);
void *converter(void *arg);
void *writer(void *arg);

//global vars
int NUM_THREADS = 3;


int main(){

	string BufferA[50];
	string BufferB[50];	

	pthread_t Rid[NUM_THREADS];
	pthread_t Cid[NUM_THREADS];
	pthread_t Wid[NUM_THREADS];

	for(int i = 0; i < NUM_THREADS; i++){
		pthread_create(&Rid[i], NULL, reader,NULL);
		//cout << Rid[i] <<"\n";
		pthread_create(&Cid[i], NULL, converter,NULL);
		//cout << Cid[i] <<"\n";
		pthread_create(&Wid[i], NULL, writer,NULL);
		//cout << Wid[i] <<"\n";
	}

	for(int i = 0; i < NUM_THREADS; i++){
		pthread_join(Rid[i], NULL);
		pthread_join(Cid[i], NULL);
		pthread_join(Wid[i], NULL);
	}

	return 0;
}

//**********************
//
//
//**********************
void *reader(void *arg){

	cout << "reader\n";

}

//**********************
//
//
//**********************
void *converter(void *arg){

	cout << "converter\n";

}

//**********************
//
//
//**********************
void *writer(void *arg){

	cout << "writer\n";

}
