// PCBTimer.h

//
// Header Files ///////////////////////////////////////////////////
//


#include <ctime>
#include <stdexcept>
#include <iostream>
#include <sys/time.h>
#include <chrono>
#include <pthread.h>
#include <iomanip>
#include <vector>
#include "ConfigMeta.cpp"
#include <sstream>
#include <math.h>
#include <semaphore.h>



using namespace std;


//thread IO function delcaration

void * IOtimerThread(void* param); 


//respective mutex for the input and output possibilities
pthread_mutex_t keyboard = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t hard_drive = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t scanner = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t monitor = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t projector = PTHREAD_MUTEX_INITIALIZER;

//respective sempahores for the input and output possibilities, all will be intialized but not all are needed to be used for this project
sem_t keyboard_sem;
sem_t hard_drive_sem;
sem_t scanner_sem;
sem_t monitor_sem;
sem_t projector_sem;



//
// Class Declaration ///////////////////////////////////////////////////
//

class PCBTimer {
  public:
    PCBTimer();
	  
	//set functions for the PCB State
	void setBegin();
	void setReady();
	void setRunning();
	void setWait();
	void setExit();
	void resetPCB();

	//checkTimer function which is essentially the wait function
	void checkTimer();

	//Timer variables for my Timer thread
	bool timerWasStarted;
	double time_passed;
	double startTime;
	double finishTime;
	double timeAlloted;
	double timerCount;
	bool exitStat;
	int process_counter;
	int projector_set;
	int hard_drive_set;
	string instruction_set;
	char code_set;
	string log_to;
	string log_path;

	//used to hold the data
	vector<string> string_data;
	vector<double> time_data;
	
	//function delcarations for my simulator
    void ApplicationChange(string temp, Config& OS_Config);
	void callPThread(PCBTimer convert);
	void PrintAll(ostream& out);
	void PrintData();
	void PrintTimer(ostream& out);
	void simulate(vector<string> &MetaFile, Config& OS_Config, MetaData& OS_Meta);
	void myProcessDelay( MetaData& OS_Meta, int counter, Config& OS_Config);
	void myMemoryDelay(string instruction,Config& OS_Config, MetaData& OS_Meta, int counter);
	void myIODelay(char code, string instruction, Config& OS_Config, MetaData& OS_Meta, int counter);


  private:
    
  	
	

	//PCB states

	int processState;

	int begin;
	int ready;
	int running;
	int wait;
	int exit;

};




