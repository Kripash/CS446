//
// Header Files ///////////////////////////////////////////////////
//

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>
#include <map>
#include "PCBTimer.cpp"




using namespace std;




/* IMPORTANT NOTICE */

/*
	I had to define my classes in one header file and implement by class functions in one cpp because of makefile errors. This was the only way for me to make it work like it was intended.
	I was getting redefinition errors so thats something i need to work on for the next project. 
 
  Assignment 2: 

	I do all the calculations and simulations first. All the outputs will be sent to a vector and then they will all be printed out at once for ease of access to output.

*/


/**
 * This function is the myTimerThread routine function call.
 *
 * The function runs with mains, but if the PCB is "destroyed" as it exits, the thread will be exited by showing that the simulation is ending. 
 * This function takes a pointer given my the thread creation. That pointer points to the PCBTimer object that is using to simulate the time. 
 * This essentially acts as a timer count down as the system clock goes until that time is reached. 
 * The timer only starts when timerWasStarted variable in the PCB object is set to true and it counts down from the timeAlloted to until it is equal to or lower than 0.
 * 
 * 
 * @param void * param, which will be used to point to the object that was passed in pthread_create.
 * @return This function does not return anything.
 *
 * @pre none.
 * @post will be used simulate a hardware timer.
 *
 */
void* myTimerThread(void* param)
{

	PCBTimer * timer = (PCBTimer *) param;

	while(true)
	{
		if(timer -> exitStat == true)
		{
			pthread_exit(0);
		}

		if((timer -> timerWasStarted == true))
		{
			timer -> time_passed = (getSystemTime() - timer -> startTime);
			while(((timer -> timeAlloted) - (timer -> time_passed)) > 0)
			{
				timer -> time_passed = (getSystemTime() - (timer -> startTime));
				timer -> timerCount = (timer -> timeAlloted) - (timer -> time_passed);
			}
		}
	}
}


//
// Main Function Implementation ///////////////////////////////////
//
int main(int argc, char *argv[]){

	
	Config OS_Config;	//My ADT for the config file reading, storing data and error checking.
	MetaData OS_Meta;	//My ADT for the Meta file reading, storing data and error checking.
	PCBTimer PCB_Timer; //My ADT PCB timer 

	

	pthread_t timerthread;
	pthread_t tid;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	

	pthread_create(&tid, &attr, myTimerThread, &PCB_Timer);



	if(argc != 2)	//if there are too many or few arguments, call error_handle.
	{
		error_handle("Invalid amount of command line arguments!");
		
	}
	
	vector <string> check;	//vector of strings used to check for errors in the files
	vector <int> ConfigData; //Vector of ints to hold the data of the integer datas of the config file
	vector <string> StringData; //vector of strings to hold the strings of data of the config file
	vector <string> MetaFile;  //vector of strings to hold the strings of data of the Meta file


	readConfigFile(argv[1], check);	//read the data from the config file to vector check.
	OS_Config.separateConfig(check, ConfigData, StringData);	//separate the config file for error check

	OS_Config.DataStorage(ConfigData, StringData);	//store the data from the config file.
	OS_Config.ConfigErrorCheck(check, ConfigData);	//check to see if there are errors within the config file that wasn't detected previously 

	check.clear();						//clear the check vector for Meta file use


	OS_Meta.readMetaFile(OS_Config.File_path, check);	//read the data from the meta file to vector check
	OS_Meta.separateMeta(check, MetaFile);				//separate the config file for error check
	
	OS_Meta.MetaCheck(check, MetaFile);		//check to see if there are errors within the meta file that wasn't detected previously
	OS_Meta.calculateMetaData(MetaFile, OS_Config);	//calcualte the data for the instructions provided in the Meta Data file 

	PCB_Timer.log_to = OS_Config.Log_to;
	PCB_Timer.log_path = OS_Config.Log_file_path;

	Schedule(MetaFile, OS_Config);
	//call PCBTimer.simulate to simulate the OS processes.
	PCB_Timer.simulate(MetaFile, OS_Config, OS_Meta);

	//free the memory for the global variable processes
	free(processes);
	
	
	//cout << OS_Config.sys_memory << endl;
	//cout << OS_Config.memory_block << endl;

	return 0;
}



