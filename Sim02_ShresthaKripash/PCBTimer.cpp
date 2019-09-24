
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
 * This essentially acts as a timer count down as the system clock goes until that time is reached. 
 * Then the thread exits.
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
	

	timer -> time_passed = (getSystemTime() - timer -> startTime);
	while(((timer -> timeAlloted) - (timer -> time_passed)) > 0)
	{
		timer -> time_passed = (getSystemTime() - (timer -> startTime));
		timer -> timerCount = (timer -> timeAlloted) - (timer -> time_passed);			
	}

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
void PCBTimer::ApplicationChange(string temp)
{
	if(temp == "A{begin}0;")
	{

		timeAlloted = 0;
		process_counter++;
		setRunning();
		time_data.push_back(getSystemTime());
		string_data.push_back(" - OS: preparing process " + to_string(process_counter));
		
		setRunning();
		time_data.push_back(getSystemTime());
		string_data.push_back(" - OS: starting process " + to_string(process_counter));
		
		setBegin();
	}
	else if(temp == "A{finish}0;")
	{
		timeAlloted = 0;
		setRunning();
		time_data.push_back(getSystemTime());
		string_data.push_back(" - OS: removing process " + to_string(process_counter));
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

		setBegin();

		process_counter = 1;

		timeAlloted = 0;

		setRunning();
		time_data.push_back(getSystemTime());
		string_data.push_back(" - Simulator program starting");
		
		
		setRunning();
		time_data.push_back(getSystemTime());
		string_data.push_back(" - OS: preparing process " + to_string(process_counter));
		
		setRunning();
		time_data.push_back(getSystemTime());
		string_data.push_back(" - OS: starting process " + to_string(process_counter));
		
		setReady();
		

		for(int i = 2; i < (MetaFile.size() - 1); i = i + 1)
		{
			temp = MetaFile[i];
	
			//if another application has begun or finished, increment i++ to move to the next instruction
			while((temp == "A{begin}0;") || (temp =="A{finish}0;"))
			{	
				ApplicationChange(temp);
				i++;
				temp = MetaFile[i];
				if(i == MetaFile.size() - 1 )
				{

					timeAlloted = 0;
					setRunning();
					time_data.push_back(getSystemTime());
					string_data.push_back(" - Simulator program ending");
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

			setReady();


			if(processState == 2)
			{
			
				switch(code)
				{	
			//if the char instructions are as exists, call the compute function. Since we already verified for process and application in config check we do not have to check here
					case 'P':
							myProcessDelay(OS_Meta, data_counter);
							break;
					case 'M':
							myMemoryDelay(instruction,OS_Config, OS_Meta, data_counter);
							break;			
					case 'I':
					case 'O':
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
void PCBTimer::myProcessDelay(MetaData& OS_Meta, int counter)
{

	
	timeAlloted = OS_Meta.Meta_Data[counter] / 1000.0;
	

	startTime = getSystemTime();
	time_data.push_back(startTime);
	string_data.push_back(" - Process " + to_string(process_counter) + " : start processing action");
	setRunning();
	checkTimer();
	time_data.push_back(finishTime);
	string_data.push_back(" - Process " + to_string(process_counter) + " : end processing action");
	
	setReady();

}

/**
 * This function is the myMemoryDelay function for the PCBTimer class.
 *
 * This function sets the timeAllote to the respective value based on the Meta_Data vector divided by 1000.0 to convert to MS. 
 * The function then sets the startTime by calling getSystemTime(). The function saves that time and sets the processState to running. 
 * This allows the timer thread to start the countdown with the timeAlloted to 0. The function also calls checkTimer() to check to see if the timer has run out.
 * Then after checkTimer() returns, the finishTime is saved and the function allocates time up to the system memory based on the time seed that is has received. 
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

	if(instruction == "block")
	{
		string_data.push_back(" - Process " + to_string(process_counter) + " : start memory blocking");
		time_data.push_back(finishTime);
		string_data.push_back(" - Process " + to_string(process_counter) + " : end memory blocking ");
	}
	else if(instruction == "allocate")
	{
		stringstream stream;
		srand(time(NULL));
		unsigned int i = rand() % OS_Config.sys_memory;
		stream << hex << i;
		string c = stream.str();
		int x = c.size();
		for(int z = 0; z < 8 - x; z++)
		{
			c = "0" + c;
		}
		string_data.push_back(" - Process " + to_string(process_counter) + " : allocating memory");
		time_data.push_back(finishTime);
		string_data.push_back(" - Process " + to_string(process_counter) + " : memory allocated at 0x" + c);
	}

	setReady();
	
}

/**
 * This function is the myIODelay function for the PCBTimer class.
 *
 * This function sets the timeAllote to the respective value based on the Meta_Data vector divided by 1000.0 to convert to MS. 
 * The function then sets the startTime by calling getSystemTime().The function saves that time and sets the process state of Wait as the IOthread is created by calling callPThread() as *this as the parameter.
 * The function creates the IOthread and calls checkTimer() to wait for the function to return the finishTime. The function saves that and then sets the PCB to ready to use again.
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
	
	timeAlloted = OS_Meta.Meta_Data[counter] / 1000.0;
	
	
	startTime = getSystemTime();
	time_data.push_back(startTime);
	if(code == 'I')
	{
		string_data.push_back(" - Process " + to_string(process_counter) + " : start " + instruction + " input");
		string_data.push_back(" - Process " + to_string(process_counter) + " : end " + instruction + " input");
	}
	else if(code == 'O')
	{
		string_data.push_back(" - Process " + to_string(process_counter) + " : start " + instruction + " output");
		string_data.push_back(" - Process " + to_string(process_counter) + " : end " + instruction + " output");
	}

	setWait();
	callPThread(*this);
	checkTimer();
	
	finishTime = getSystemTime();
	time_data.push_back(finishTime);
	
	
	setReady();
	
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
		for(int i = 0; i < string_data.size(); i++)
			out << fixed << setprecision (6) << time_data[i] << string_data[i] << endl;
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








