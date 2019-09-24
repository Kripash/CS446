
/** @file PCBTimer.cpp
@author Kripash Shrestha
@version 1.0
@brief This program will implement a timer to test multiple sort, searches, constructor and increment tests.
@details The specifications of the program are instructed and documented on Lab 13 Performance Evaluation of C++ Data Structures: A Laboratory Course Third Edition by Brandle, Geisler, Roberge and Whittington
@date Wednesday, September 26, 2017
*/

/**
@mainpage
This program contains the necessary functions to implement
-the timer to test the multiple sort, search, constructor and increment tests. 

When mentioning a timer, one has to think about the start time and stop time to get the elapsed time. 
Timers have different accuracy and in terms of this one, we will implement one up to microseconds. 
We will have to evaluate the difference in the seconds and the difference in the microseconds measured. 
this can be solved with the structs of timeval of beginTime and duration. 
We will have a timerWasStarted boolean to tell us if the timer was ever started and if it was stopped. 

*/

/*
Author self-assessment statement:
This program is complete and working according to specifications,
according to the best of my knowledge.
*/


//
// Header Files ///////////////////////////////////////////////////
//


#include <iostream>
#include "PCBTimer.h"
#include <chrono>
#include <stdlib.h>
#include <istream>

//
// Supporting Function Implementations //////////////////////////////
//

/**
 * This function will create a timer class using the constructor. This function is the default constructor of the Timer class.
 *
 * This function will be used specifically to initialize a Timer class with all of the private struct values to be set to and the boolean timerWasStarted to false since it was never
 * started.
 * 
 * @param none.
 * @return This function does not return anything.
 *
 * @pre none.
 * @post The object is intialized.
 *
 */
PCBTimer::PCBTimer(){

   
	processState = 0;
	begin = 0;
	ready = 0;
	running = 0;
	wait = 0;
	exit = 0;

    timerWasStarted = false;
	exitStat = false;

}

/**
 * This function will create setBegin to be true for the PCBTimer class.
 *
 * This function will be used specifically to intialize the processState to 1 and set begin to 1. All other states will be set to 0.
 * 
 * @param none.
 * @return This function does not return anything.
 *
 * @pre none.
 * @post processState and begin will be set to 1.
 *
 */
void PCBTimer::setBegin()
{
	processState = 1;
	begin = 1;
	ready = 0;
	running = 0;
	wait = 0;
	exit = 0;

	timerWasStarted = false;
}

/**
 * This function will setReady to be true for the PCBTimer class.
 *
 * This function will be used specifically to intialize the processState to 2 and set ready to 1. All other states will be set to 0.
 * 
 * @param none.
 * @return This function does not return anything.
 *
 * @pre none.
 * @post processState will be set to 2 and ready will be set to 1.
 *
 */
void PCBTimer::setReady()
{
	processState = 2;
	begin = 0;
	ready = 1;
	running = 0;
	wait = 0;
	exit = 0;

	timerWasStarted = false;

}


/**
 * This function will setRunning to be true for the PCBTimer class.
 *
 * This function will be used specifically to intialize the processState to 3 and set running to 1. All other states will be set to 0.
 * 
 * @param none.
 * @return This function does not return anything.
 *
 * @pre none.
 * @post processState will be set to 3 and running will be set to 1.
 *
 */
void PCBTimer::setRunning()
{
	processState = 3;
	begin = 0;
	ready = 0;
	running = 1;
	wait = 0;
	exit = 0;

	timerWasStarted = true;

}

/**
 * This function will setWait to be true for the PCBTimer class.
 *
 * This function will be used specifically to intialize the processState to 4 and set wait to 1. All other states will be set to 0.
 * 
 * @param none.
 * @return This function does not return anything.
 *
 * @pre none.
 * @post processState will be set to 4 and wait will be set to 1.
 *
 */
void PCBTimer::setWait()
{
	processState = 4;
	begin = 0;
	ready = 0;
	running = 0;
	wait = 1;
	exit = 0;

	timerWasStarted = false;

}

/**
 * This function will setExit to be true for the PCBTimer class.
 *
 * This function will be used specifically to intialize the processState to 5 and set exit to 1. All other states will be set to 0.
 * 
 * @param none.
 * @return This function does not return anything.
 *
 * @pre none.
 * @post processState will be set to 5 and exit will be set to 1.
 *
 */
void PCBTimer::setExit()
{
	processState = 5;
	begin = 0;
	ready = 0;
	running = 0;
	wait = 0;
	exit = 1;

	timerWasStarted = false;
	exitStat = true;

}

/**
 * This function is the resetPCB function for the PCBTimer class to reset the PCBTimer.
 *
 * This function will be used specifically to reset a Timer class with all of the private struct values to be set to and the boolean timerWasStarted to false.
 * 
 * @param none.
 * @return This function does not return anything.
 *
 * @pre none.
 * @post The object is reset for the next Process.
 *
 */
void PCBTimer::resetPCB()
{
	processState = 0;
	begin = 0;
	ready = 0;
	running = 0;
	wait = 0;
	exit = 0;

	timerWasStarted = false;
}

/**
 * This function is the IOtimerThread routine function call.
 *
 * This function takes a pointer given my the thread creation. That pointer points to the PCBTimer object that is using to simulate the time. 
 * The function locks a pthread mutex based on the instruction passed in to the function, which of input and output based. 
 * The function gets the values ( by calling sem_getvalue) of the harddrive and projector semaphores for later use.If the mutex values need to be reset, the function will do so by calling sem_init.
 * This function sets the timeAllote to the respective value based on the Meta_Data vector divided by 1000.0 to convert to MS. 
 * The function then sets the startTime by calling getSystemTime().The function saves that time and sets the process state of Wait as the IOthread is created by calling callPThread() 
 * as *this as the parameter.
 * The function creates the IOthread and calls checkTimer() to wait for the function to return the finishTime. The function saves that and then sets the PCB to ready to use again.
 * The function performs simple arithmetic, based on the current value of the respective harddrive/projector semaphore and the max possible size. 
 * The function then calls wait on the respective semaphore to decrement it by 1. 
 * The function then unlocks a pthread mutex based on the instruction passed in to the function, which of input and output based. 
 * 
 * @param void * param, which will be used to point to the object that was passed in pthread_create.
 * @return This function does not return anything.
 *
 * @pre none.
 * @post will be used as a delay thread to put the thread to sleep for a certain time.
 *
 */
void * IOtimerThread(void* param)
{
	
	PCBTimer * timer = (PCBTimer *) param;
	
	int value, value1;

	//lock a mutex for the thread, based on theinstruction passed in the function.
	if(timer -> instruction_set == "hard drive")
	{
		pthread_mutex_lock(&hard_drive);
	}
	else if(timer -> instruction_set == "keyboard")
	{
		pthread_mutex_lock(&keyboard);
	}
	else if(timer -> instruction_set == "scanner")
	{
		pthread_mutex_lock(&scanner);
	}
	else if(timer -> instruction_set == "monitor")
	{
		pthread_mutex_lock(&monitor);
	}
	else if(timer -> instruction_set == "projector")	
	{
		pthread_mutex_lock(&projector);
	}

	//get the values of the semaphores and assign them to variables
	sem_getvalue(&hard_drive_sem, &value);
	sem_getvalue(&projector_sem, &value1);

	//reset the semaphore values if all resources are used up
	if(value == 0)
	{
		sem_init(&hard_drive_sem, 0, timer-> hard_drive_set);	
		sem_getvalue(&hard_drive_sem, &value);
	}

	if(value1 == 0)
	{
		sem_init(&projector_sem, 0, timer -> projector_set);
		sem_getvalue(&projector_sem, &value1);
	}

	//initial timer start
	timer -> timeAlloted = timer -> timeAlloted / 1000.0;

	timer -> startTime = getSystemTime();
	timer -> time_data.push_back(timer -> startTime);


	//determine the output based on the instruction set and the code given 
	if(timer -> code_set == 'I')
	{
	
		if(timer -> instruction_set == "hard drive")
		{
			timer -> string_data.push_back(" - Process " + to_string(timer -> process_counter) + " : start " + timer -> instruction_set + " input " + "HDD " + to_string(timer -> hard_drive_set - value));
			timer -> PrintData();
			timer -> string_data.push_back(" - Process " + to_string(timer ->process_counter) + " : end " + timer -> instruction_set + " input");
			sem_wait(&hard_drive_sem);
		}	
		else
		{
			timer -> string_data.push_back(" - Process " + to_string(timer -> process_counter) + " : start " + timer -> instruction_set + " input");
			timer -> PrintData();
			timer -> string_data.push_back(" - Process " + to_string(timer -> process_counter) + " : end " + timer -> instruction_set + " input");
		}
	}
	else if(timer -> code_set == 'O')
	{
		if(timer -> instruction_set == "hard drive")
		{
			timer -> string_data.push_back(" - Process " + to_string(timer -> process_counter) + " : start " + timer -> instruction_set + " input " + "HDD " + to_string(timer -> hard_drive_set - value));
			timer -> PrintData();
			timer -> string_data.push_back(" - Process " + to_string(timer -> process_counter) + " : end " + timer -> instruction_set + " output ");
			sem_wait(&hard_drive_sem);
		}	
		else if(timer -> instruction_set == "projector")
		{
			timer -> string_data.push_back(" - Process " + to_string(timer -> process_counter) + " : start " + timer -> instruction_set + " output " + "PROJ " + to_string(timer -> projector_set - value1));
			timer -> PrintData();
			timer -> string_data.push_back(" - Process " + to_string(timer -> process_counter) + " : end " + timer -> instruction_set + " output ");
			sem_wait(&projector_sem);
		}	
		else
		{	
			timer -> string_data.push_back(" - Process " + to_string(timer -> process_counter) + " : start " + timer -> instruction_set + " output");
			timer -> PrintData();
			timer -> string_data.push_back(" - Process " + to_string(timer -> process_counter) + " : end " + timer -> instruction_set + " output");
		}
	}

	//set the thread creating wait since the system must wait for the I/O to complete
	timer -> setWait();
	timer -> time_passed = (getSystemTime() - timer -> startTime);
	while(((timer -> timeAlloted) - (timer -> time_passed)) > 0)
	{
		timer -> time_passed = (getSystemTime() - (timer -> startTime));
		timer -> timerCount = (timer -> timeAlloted) - (timer -> time_passed);			
	}

	timer -> finishTime = getSystemTime();
	timer -> time_data.push_back(timer -> finishTime);
	timer -> PrintData();;
	
	//unlock a mutex for the thread, based on theinstruction passed in the function.
	if(timer -> instruction_set == "hard drive")
	{
		pthread_mutex_unlock(&hard_drive);
	}
	else if(timer -> instruction_set == "keyboard")
	{
		pthread_mutex_unlock(&keyboard);
	}
	else if(timer -> instruction_set == "scanner")
	{
		pthread_mutex_unlock(&scanner);
	}
	else if(timer -> instruction_set == "monitor")
	{
		pthread_mutex_unlock(&monitor);
	}
	else if(timer -> instruction_set == "projector")	
	{
		pthread_mutex_unlock(&projector);
	}

	timer -> setReady();
	pthread_exit(0);
}

/**
 * This function is the checkTimer function for the PCBtimer class.
 *
 * This function checks to see if the timer was started. If the timer was started, the function will check to see if the timer was stopped every 15 milliseconds.
 * AUTHOR IMPORTANT NOTICE: 
 * Dr.Siming Liu mentioned to me in office hours that it was okay to change the time we poll to increase accuracy. If it is neeed to go back to 100 milliseconds, you can change .015 to .1. 
 *
 * @param None
 * @return This function does not return anything.
 *
 * @pre none.
 * @post will be used to check to see if the timer has stopped. 
 *
 */
void PCBTimer::checkTimer()
{
	
	double waitTime = startTime;

	while(timerWasStarted == true)
	{
		while((getSystemTime() - waitTime) < (.015));
		waitTime = getSystemTime();

		if(timerCount <= 0)
		{
			finishTime = getSystemTime();
			setReady();
		}
	} 
}

/**
 * This function is the ApplicationChange function for the PCBTimer class.
 *
 * The function has two states, when the string is with begin or with finish.
 * If the string contains the begin application state, the timeAlloted is put to 0 and the process counter is indicator.  
 * The function then sets the process to run for 0 ms, and then pushes it back. This is to prepare the process. The function does this again to start the process.
 * The function then sets the process to begin.
 * 
 * If the string is finish. the time Alloted to set to 0. The function runs that process for 0ms and then pushes it back. This simulates the removing process and then resets the PCB.
 *
 * @param 
 * string temp, which is used to determine what state of application of the function receives, begin or finish.
 * @return None
 *
 * @pre none.
 * @post will be used to simulate a process running.
 *
 */
void PCBTimer::ApplicationChange(string temp, Config& OS_Config)
{
	if(temp == "A{begin}0;")
	{

		timeAlloted = 0;
		process_cont++;
		process_counter = processes[process_cont].process_number;
		setRunning();
		time_data.push_back(getSystemTime());
		string_data.push_back(" - OS: preparing process " + to_string(process_counter));
		PrintData();		

		setRunning();
		time_data.push_back(getSystemTime());
		string_data.push_back(" - OS: starting process " + to_string(process_counter));
		PrintData();
		
		setBegin();
	}
	else if(temp == "A{finish}0;")
	{
		timeAlloted = 0;
		setRunning();
		time_data.push_back(getSystemTime());
		string_data.push_back(" - OS: removing process " + to_string(process_counter));
		PrintData();
		resetPCB();
	}

}


/*
* This is the simulate function for the PCBTimer class.
*
* The function sets out by setting the process to begin an setting process counter to 1. The timeAlloted is set to 0 so it can simulate the program starting, preparing process
* and starting process with the timer thread. The function then sets the process to ready simulating. 
*
* This function starts off by iterating through the MetaFile data vector. It starts at the 3rd element and ends at the second to last since those are the application and process instructions 
* that have already been verified at the metaCheck function.
* The function stores the string of the element in a temp string. The function dissects the strings into a char, which represents the Meta Code. 
* The function then gets the instruction from the string and stores it into the string instruction.
* The function then gets the integer data from the string and stores it into data_hold and converts it into an int using stoi and stores it into data.
* If the process state is set to 2 the function goes into an if statement.
* The function then goes into a switch statement to switch based on the char code, which is the Meta code, that the function dissected from the string.
* If an application change state is reached, the function calls ApplicationChange() with temp passed in as the parameters. The program will simulate the end if the last element is reached.
*
* The switch statement changes the simulation to process, memory and IO based on the state that is given by the char code. 
* P, calls myProcessDelay, M, calls myMemoryDelay and I an O call myIODelay. Otherwise, the function throws an error. 
* If the last element was not reached the function will simulate the termination of the simulation and exit.
* 
*
* @Parameters: 
* vector<string> &MetaFile, which is the vector containing the data of separated strings from the MetaFile.
* Config &OS_Config, which is the Config object to retrieve the map from so we can do the computations.
* MetaData& OS_Meta, which is the MetaData object that contain data about the Meta File to simulate the OS.
*
* @Return: None 
*
*/
void PCBTimer::simulate(vector<string> &MetaFile, Config& OS_Config, MetaData& OS_Meta)
{
	
		//we know our meta data file is correct so we can run S{start}0; and A{start}0; to simulate the start of the process without checking for it.

		char code;
		string temp, instruction, data_hold;
		int position = 0, position_2 = 0, position_3, data = 0, counter = 0, data_counter = 0;
		size_t convert = 0;
		process_cont = 0;

		setBegin();

		process_counter = processes[process_cont].process_number;
		
		ofstream openOutputFile;
		openOutputFile.open(log_path.c_str(), std::ofstream::out | std::ofstream::trunc);
		openOutputFile.close();


		//intialize the semaphores, the default values for keyboard, monitor and scanner are 1 while hard drive and projector are taken in from the config file
		sem_init(&keyboard_sem, 0, 1);
		sem_init(&monitor_sem, 0, 1);
		sem_init(&scanner_sem, 0, 1);
		sem_init(&hard_drive_sem, 0, OS_Config.Hard_drive_quantity);
		sem_init(&projector_sem, 0, OS_Config.Project_quantity);


		projector_set = OS_Config.curr_proj = OS_Config.Project_quantity; 
		hard_drive_set = OS_Config.curr_hard_drive = OS_Config.Hard_drive_quantity;
		OS_Config.current_mem = 0;
		timeAlloted = 0;

		setRunning();
		time_data.push_back(getSystemTime());
		string_data.push_back(" - Simulator program starting");
		PrintData();
		
		setRunning();
		time_data.push_back(getSystemTime());
		string_data.push_back(" - OS: preparing process " + to_string(process_counter));
		PrintData();
		
		setRunning();
		time_data.push_back(getSystemTime());
		string_data.push_back(" - OS: starting process " + to_string(process_counter));
		PrintData();
		
		setReady();
		

		for(int i = 2; i < (MetaFile.size() - 1); i = i + 1)
		{
			temp = MetaFile[i];
	
			//if another application has begun or finished, increment i++ to move to the next instruction
			while((temp == "A{begin}0;") || (temp =="A{finish}0;"))
			{	
				sem_init(&hard_drive_sem, 0, projector_set);
				sem_init(&projector_sem, 0, hard_drive_set);
				OS_Config.current_mem = 0;
				ApplicationChange(temp, OS_Config);
				i++;
				temp = MetaFile[i];
				if(i == MetaFile.size() - 1 )
				{

					timeAlloted = 0;
					setRunning();
					time_data.push_back(getSystemTime());
					string_data.push_back(" - Simulator program ending");
					PrintData();
					setExit();
								
					return;
				}
				
			}
		
			//gets the Meta code, so for example either P, I , O or M as the valid code.
			code = temp[0];
			//If the next character is not a { , the code is invalid and has more than one character
			if(temp[1] != '{' )
			{
				error_handle("Error: Invalid Meta Code, more than 1 character for the Meta Data Code!");
			}

			//find the { in the string and make sure it exists
			position = temp.find("{") + 1;
			position_check(position, "Meta");
		
			//find the } in the string and make sure it exists. Get the string instruction from the code for map access to the cycle per time.
			position_2 = temp.find("}");
			position_check(position_2, "Meta");
			instruction = temp.substr(position, position_2-position);
		
			//find the semi colon in the string and make sure it exists
			position_3 = temp.find(";");
			position_check(position_3, "Meta");

			//if the following statement is true, then there is no data for the code and it ends with a }; In that case, send an error.
			if((position_3 - position_2 - 1) == 0)
			{
				error_handle("Error: Missing Data in Meta File");
			}
			//Other wise get the value of the data and convert that to string using stoi.
			data_hold = temp.substr(position_2 + 1, position_3 - position_2 - 1);
			data = stoi(data_hold, &convert);

			instruction_set = instruction;
			code_set = code;
			setReady();
		

			if(processState == 2)
			{
			timeAlloted = OS_Meta.Meta_Data[data_counter];
				switch(code)
				{	
			//if the char instructions are as exists, call the compute function. Since we already verified for process and application in config check we do not have to check here
					case 'P':
							myProcessDelay(OS_Meta, data_counter, OS_Config);
							break;
					case 'M':
							myMemoryDelay(instruction,OS_Config, OS_Meta, data_counter);
							break;			
					case 'I':
					case 'O':
							
							//this function is used to call PThread to create my I/O thread creation
							myIODelay(code, instruction, OS_Config, OS_Meta, data_counter);
							break;
				
					default:
						error_handle("Error: Invalid Meta Data Code!");	//otherwise call error handle with invalid meta data code as the string passed
						break;
				}
			data_counter++;
		}
	}

	timeAlloted = 0;	

	setRunning();
	time_data.push_back(getSystemTime());
	string_data.push_back(" - Simulator program ending");
	PrintData();

	setExit();

}


/**
 * This function is the myProcessDelay function for the PCBTimer class.
 *
 * This function sets the timeAllote to the respective value based on the Meta_Data vector divided by 1000.0 to convert to MS. 
 * The function then sets the startTime by calling getSystemTime(). The function saves that time and sets the processState to running. 
 * This allows the timer thread to start the countdown with the timeAlloted to 0. The function also calls checkTimer() to check to see if the timer has run out.
 * Then after checkTimer() returns, the finishTime is save and the PCB is set to ready for the next task.
 *
 * @param 
 * MetaData& OS_Meta, which is the MetaData object which holds the calculations for the times to simulate the processes.
 * int counter, which is the task that needs to be simulated. 
 * @return None
 *
 * @pre none.
 * @post will be used to simulate a process running.
 *
 */
void PCBTimer::myProcessDelay(MetaData& OS_Meta, int counter, Config& OS_Config)
{

	
	timeAlloted = OS_Meta.Meta_Data[counter] / 1000.0;
	

	startTime = getSystemTime();
	time_data.push_back(startTime);
	string_data.push_back(" - Process " + to_string(process_counter) + " : start processing action");
	PrintData();
	setRunning();
	checkTimer();
	time_data.push_back(finishTime);
	string_data.push_back(" - Process " + to_string(process_counter) + " : end processing action");
	PrintData();
	
	setReady();

}

/**
 * This function is the myMemoryDelay function for the PCBTimer class.
 *
 * This function sets the timeAllote to the respective value based on the Meta_Data vector divided by 1000.0 to convert to MS. 
 * The function then sets the startTime by calling getSystemTime(). The function saves that time and sets the processState to running. 
 * This allows the timer thread to start the countdown with the timeAlloted to 0. The function also calls checkTimer() to check to see if the timer has run out.
 * Then after checkTimer() returns, the finishTime is saved and the function allocates time up to the system memory based on the time seed that is has received. 
 * The function starts the allocation memory block at 0 and increments by the memory block size each time. However, when the memory block reaches the sys memory size, the memory resets to 0.
 * The memory values are converted into hex values for the output.
 * The function then sets the PCB to ready for the next task.
 *
 * @param 
 * MetaData& OS_Meta, which is the MetaData object which holds the calculations for the times to simulate the processes.
 * int counter, which is the task that needs to be simulated. 
 * string instruction, which is the instruction to the modify the output for the task
 * Config& OS_Config, which is the Config object which holds the system memory value
 * @return None
 *
 * @pre none.
 * @post will be used to simulate a process running.
 *
 */
void PCBTimer::myMemoryDelay(string instruction, Config& OS_Config, MetaData& OS_Meta, int counter)
{
	timeAlloted = OS_Meta.Meta_Data[counter] / 1000.0;
	

	startTime = getSystemTime();
	time_data.push_back(startTime);
	
	setRunning();
	checkTimer();

	//since block has nothing special going on righ tnow
	if(instruction == "block")
	{
		string_data.push_back(" - Process " + to_string(process_counter) + " : start memory blocking");
		PrintData();
		time_data.push_back(finishTime);
		string_data.push_back(" - Process " + to_string(process_counter) + " : end memory blocking ");
		PrintData();
	}
	else if(instruction == "allocate")	//allocate memory 
	{
		stringstream stream;

		stream << hex << OS_Config.current_mem; //start off with 0

		OS_Config.current_mem = OS_Config.current_mem + OS_Config.memory_block;	//increment by the block size.

		if(OS_Config.current_mem > OS_Config.sys_memory) //since the stream is already taken in, we can reset the block size to 0, if the size becomes larger than the system memory
		{
			OS_Config.current_mem = 0;
		}
		
		//convert the memory value to hex to print out 
		string c = stream.str();
		int x = c.size();
		for(int z = 0; z < 8 - x; z++)
		{
			c = "0" + c;
		}
		string_data.push_back(" - Process " + to_string(process_counter) + " : allocating memory");
		PrintData();
		time_data.push_back(finishTime);
		string_data.push_back(" - Process " + to_string(process_counter) + " : memory allocated at 0x" + c);
		PrintData();
	}

	setReady();
	
}

/**
 * This function is the myIODelay function for the PCBTimer class.
 *
 * The function creates the IO thread by calling callPThread with a *this as the parameter for the thread creation.
 *
 * @param 
 * char code, which is used to determine if the outputs will match output or input.
 * MetaData& OS_Meta, which is the MetaData object which holds the calculations for the times to simulate the processes.
 * int counter, which is the task that needs to be simulated. 
 * string instruction, which is the instruction to the modify the output for the task
 * Config& OS_Config, which is the Config object which holds the system memory value
 * @return None
 *
 * @pre none.
 * @post will be used to simulate a process running.
 *
 */
void PCBTimer::myIODelay(char code, string instruction, Config& OS_Config, MetaData& OS_Meta, int counter)
{
	callPThread(*this);
}

/**
 * This function is the PrintData function.
 *
 * This function takes an ostream reference and print out the data and strings based on the vectors that were pushed back. This is done in real time as it prints the last pushed in vector and is 
 * constantly called through out the program.
 * 
 * @param none
 * @return This function does not return anything.
 *
 * @pre none.
 * @post prints out the output to the ostream.
 *
 */
void PCBTimer::PrintData()
{

	string Log_to = log_to;	//contain the string to decide where to print

	if(Log_to == "Log to Both")	//If the log is to both, print out to file and the terminal by calling printToBoth function
	{
		ofstream openOutputFile;
		openOutputFile.open(log_path.c_str(), std::ios::app);
		PrintTimer(cout);
		//openOutputfile.seekg(end);
		//PrintTimer(openOutputFile);
		openOutputFile << fixed << setprecision (6) << time_data[time_data.size() - 1] << string_data[string_data.size() - 1] << endl;
		openOutputFile.close();
	}
	else if(Log_to == "Log to Monitor")	//If the log is to monitor, call PrintConfigData and printMetrics with cout as the parameter for ostream
	{
		PrintTimer(cout);

	}
	else if(Log_to == "Log to File")	//If the log is to file, call PrintConfigData and printMetrics with the ofstream as the parameter for ostream
	{
		ofstream openOutputFile;
		openOutputFile.open(log_path.c_str(), std::ios::app);
		//openOutputFile.seekg(end);
		//PrintTimer(openOutputFile);
		openOutputFile << fixed << setprecision (6) << time_data[time_data.size() - 1] << string_data[string_data.size() - 1] << endl;
		openOutputFile.close();
	}
	else	//else if the string does not match any of those, produce error by calling error_handle for the instruction for log
	{
		error_handle("Can't log to the instruction provided!");
	}

}


/**
 * This function is the Print timer function.
 *
 * This function takes an ostream reference and print out the data of the two given vectors, which contain the data of the time and strings 
 * to print the outputs based on the ostream.
 * 
 * @param ostream& out, which is the ostream where the output will be displayed.
 * @return This function does not return anything.
 *
 * @pre none.
 * @post prints out the output to the ostream.
 *
 */
void PCBTimer::PrintTimer(ostream& out)
{
	if(string_data.size() == time_data.size())
	{
			out << fixed << setprecision (6) << time_data[time_data.size() - 1] << string_data[string_data.size() - 1] << endl;
	}

}

/**
 * This function is the CallPThread function, which allows it to create a IOTimerthread.
 *
 * This function creates a thread with the convert value being passed as the PCBtimer object being passed to create a delay.
 * 
 * @param PCBTimer convert, which is the PCBTimer object to base the time delay off of
 * @return This function does not return anything.
 *
 * @pre none.
 * @post Creates a thread with the given PCBTimer to be treated as the value to act as the time delay.
 *
 */
void PCBTimer::callPThread(PCBTimer convert)
{
	pthread_t timerthread;
	pthread_t tid;
	pthread_attr_t attr;
	pthread_attr_init(&attr);

	pthread_create(&tid, &attr, IOtimerThread, &convert);
	pthread_join(tid,NULL);

}

/**
 * This function is the PrintAll function.
 *
 * This function takes an ostream reference and print out the data of the two given vectors, which contain the data of the time and strings 
 * to print the outputs based on the ostream.
 * 
 * @param ostream& out, which is the ostream where the output will be displayed.
 * @return This function does not return anything.
 *
 * @pre none.
 * @post prints out the output to the ostream.
 *
 */
void PCBTimer::PrintAll(ostream& out)
{
	if(string_data.size() == time_data.size())
	{
		for(int i = 0; i < string_data.size(); i++)
		{
			out << fixed << setprecision (6) << time_data[i] << string_data[i] << endl;
		}
	}
}






