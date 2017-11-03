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
string BufferA[50] = {"def"};
int bufferAIndex = 0;
string BufferB[50];	
int bufferBIndex = 0;
pthread_mutex_t mutex1 =
PTHREAD_MUTEX_INITIALIZER;


int main(){

	
	pthread_t Rid[NUM_THREADS];
	pthread_t Cid[NUM_THREADS];
	pthread_t Wid[NUM_THREADS];

	for(int i = 0; i < NUM_THREADS; i++){
		pthread_create(&Rid[i], NULL, reader, NULL);
		//pthread_join(Rid[i], NULL);
		//cout << Rid[i] <<"\n";
		pthread_create(&Cid[i], NULL, converter,NULL);
		//pthread_join(Cid[i], NULL);
		//cout << Cid[i] <<"\n";
		pthread_create(&Wid[i], NULL, writer,NULL);
		//pthread_join(Wid[i], NULL);
		//cout << Wid[i] <<"\n";
	}

	for(int i = 0; i < NUM_THREADS; i++){
		pthread_join(Rid[i], NULL);
		pthread_join(Cid[i], NULL);
		pthread_join(Wid[i], NULL);
	}
cout << bufferAIndex <<"\n";
	return 0;
}

//**********************
//
//
//**********************
void *reader(void *arg){
pthread_mutex_lock(&mutex1);
cout << "reader\n";
getline(cin,BufferA[bufferAIndex]);
bufferAIndex++;

pthread_mutex_unlock(&mutex1);
}

//**********************
//
//
//**********************
void *converter(void *arg){

pthread_mutex_lock(&mutex1);
cout << "converter\n";
if(bufferAIndex != 0){
	bufferAIndex--;
}
int x = 0;
while(BufferA[bufferAIndex][x] != '\0'){

if(BufferA[bufferAIndex][x] == ' '){
BufferA[bufferAIndex][x] = '%';
}
x++;
}
BufferB[bufferBIndex] = BufferA[bufferAIndex];
bufferBIndex++;

pthread_mutex_unlock(&mutex1);
}

//**********************
//
//
//**********************
void *writer(void *arg){

pthread_mutex_lock(&mutex1);
cout << "writer\n";
if(bufferBIndex != 0){
	bufferBIndex--;
}
cout << BufferB[bufferBIndex] << ": ";
cout << bufferBIndex <<"\n";
pthread_mutex_unlock(&mutex1);


}
