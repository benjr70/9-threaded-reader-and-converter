#include <iostream>
#include <pthread.h>
#include <string>

using namespace std;

//prototypes
void *reader(void *arg);
void *converter(void *arg);
void *writer(void *arg);

//global vars
int NUM_THREADS = 3;// about of threads you would like. should work with any amount
string BufferA[50];
int bufferAIndex = 0;
string BufferB[50];	
int bufferBIndex = 0;
pthread_mutex_t mutex1 =
PTHREAD_MUTEX_INITIALIZER;


int main(){

	// thread id arrays
	pthread_t Rid[NUM_THREADS];
	pthread_t Cid[NUM_THREADS];
	pthread_t Wid[NUM_THREADS];

	for(int i = 0; i < NUM_THREADS; i++){ //loops three times
		pthread_create(&Rid[i], NULL, reader, NULL); //creates reader thread
		pthread_create(&Cid[i], NULL, converter,NULL); // creates converter thread 
		pthread_create(&Wid[i], NULL, writer,NULL); // creates writers thread

	}

	for(int i = 0; i < NUM_THREADS; i++){ //loop three times
		pthread_join(Rid[i], NULL); // joins reader thread back to main
		pthread_join(Cid[i], NULL); // joins converter thread back to main
		pthread_join(Wid[i], NULL); // joins writer thread back to main
	}
	return 0;
}

//**********************
// reader threads
// locks varibles the reads in from use and pushes line into buffer A
//**********************
void *reader(void *arg){

	pthread_mutex_lock(&mutex1); // mutex lock
	cout << "Enter Line: ";
	getline(cin,BufferA[bufferAIndex]);
	bufferAIndex++;
	pthread_mutex_unlock(&mutex1); // mutex unlock
}

//**********************
// coverter theads
// waits till theres data in buffer A then locks variable and covverts the data 
// in buffer A moves it to buffer B the pops data off of buffer A
//**********************
void *converter(void *arg){

	while(bufferAIndex == 0){
	// do nothing until there is data in buffer A
	}
		if(bufferAIndex != 0){ 
		
			pthread_mutex_lock(&mutex1); // mutex lock
			//cout << "converter\n";
			bufferAIndex--;
			int x = 0;
			while(BufferA[bufferAIndex][x] != '\0'){
				if(BufferA[bufferAIndex][x] == ' '){
					BufferA[bufferAIndex][x] = '%';
				}
				x++;
			}
			BufferB[bufferBIndex] = BufferA[bufferAIndex];
			bufferBIndex++;
		
			pthread_mutex_unlock(&mutex1); //mutex unlock
		}

}

//**********************
// writer threads
// waits till theres data in buffer B then locks the varables 
//while it prints from the buffer and pops that data from buffer stack
//**********************
void *writer(void *arg){
	while(bufferBIndex ==0){
	 // do nothing until there is data in buffer B
	}

	if(bufferBIndex != 0){
		pthread_mutex_lock(&mutex1); //mutex lock
		//cout << "writer\n";
		bufferBIndex--;
		cout << BufferB[bufferBIndex];// << ": ";
		cout <<"\n";
		pthread_mutex_unlock(&mutex1); //mutex unlock
	}

}
