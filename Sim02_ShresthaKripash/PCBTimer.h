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



using namespace std;


//thread IO function delcaration

void * IOtimerThread(void* param); 




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
	
	//function delcarations for my simulator
    void ApplicationChange(string temp);
	void callPThread(PCBTimer convert);
	void PrintTimer(ostream& out);
	void simulate(vector<string> &MetaFile, Config& OS_Config, MetaData& OS_Meta);
	void myProcessDelay( MetaData& OS_Meta, int counter);
	void myMemoryDelay(string instruction,Config& OS_Config, MetaData& OS_Meta, int counter);
	void myIODelay(char code, string instruction, Config& OS_Config, MetaData& OS_Meta, int counter);


  private:
    
  	//used to hold the data
	vector<string> string_data;
	vector<double> time_data;

	//PCB states

	int processState;

	int begin;
	int ready;
	int running;
	int wait;
	int exit;

};




