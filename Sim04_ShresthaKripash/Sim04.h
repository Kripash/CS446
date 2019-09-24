
//
// Header Files ///////////////////////////////////////////////////
//


#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>
#include <map>

using namespace std;

//
// Supporting Function and Object Declarations ///////////////////////////////////////////////////
//

//struct Processes 
struct Processes{

	int tasks;	//holds the number of tasks in process
	int start; //holds the start index in original vector
	int end;   //holds the end index in original vector
	int IO;    //holds the number of IO tasks in process
	int process_number; //process number based on MetaData file
};


//global variable// 
Processes * processes;

void swapProcess(Processes * S1, Processes * S2);
void Schedule(vector<string> &MetaFile, Config& OS_Config);
void readConfigFile(char * file_Name, vector <string> &check);	//need to change for now
void error_handle(string error);
void position_check(size_t position, string Type);
string stringify(string hold);
double getSystemTime();
void Schedule(vector<string> &MetaFile, Config& OS_Config);

//
// Supporting Function Implementations ///////////////////////////////////////////////////
//

/*
* This is the swapProcess function
*
* The function takes a pointer to 2 processes and swaps them. This is done for my bubble sorting of the processes.
*
* @Parameters:
* Processes * S1, process 1 to be swapped
* Processes * S2, process 2 to be swapped 
*
* @Return: None 
*
*/
void swapProcess(Processes * S1, Processes * S2)
{
	Processes temp = *S1;
	*S1 = *S2;
	*S2 = temp;
}

/*
* This is the Schedule function
*
* The function first determines the amount of processes the MetaData file has. It then allocates an array of processes based on the amount of processes it found.
* The function then loops through the original array again and counts the amount of tasks and Input/Output tasks for each process and stores them in the respective process. 
* The function keeps track of the original start and end index for the processes. The function then bubble sorts the array of processes based on the scheduling we need to do.
* The function will then appropriately fill a vector of strings with the correct order needed for the simulation. 
*
* @Parameters:
* vector<string> &MetaFile, which contains the processes and tasks from the MetaDatafile
* Config& OS_Config, which is the Config object that is passed to determine what kind of scheduling we need to do
*
* @Return: None 
*
*/
void Schedule(vector<string> &MetaFile, Config& OS_Config)
{

	int i = 0, processors = 0, tracker = 0, offset = 0, IO = 0; 
	string temp;
	char code;
	vector<string> hold;
	int processNumber = 1; 
	int PBegin = 0, PEnd = 0;

	//Used to find the amount of processes in the MetaData file
	for(i = 0; i < MetaFile.size(); i++)
	{
		if(MetaFile[i] == "A{begin}0;")
		{
			processors++;
			PBegin++;
		}
		else if(MetaFile[i] == "A{finish}0;")
		{
			PEnd++;
		}
	}

	if(PBegin < PEnd)
	{
		error_handle("Error: There are less A{begin}0; than A{finish}0;");
	}
	else if(PEnd < PBegin)
	{
		error_handle("Error: There are less A{finish}0; than A{begin}0;");
	}
	
	//allocate an array of processes based on the number of processes found
	processes = new Processes[processors];

	for(i = 1; i < MetaFile.size() - 1; i++)
	{
		temp = MetaFile[i];
		code = temp[0];
		if(temp == "A{begin}0;")	
		{
			processes[offset].start = i;	//mark start index for each process
			processes[offset].IO = 0;
			
		}
		if(code == 'I' || code == 'O')
		{
			processes[offset].IO++;							//increment the amount of IO in each process.
		}
		if(temp == "A{finish}0;")	
		{
			processes[offset].end = i;	//mark end index for each process
			processes[offset].tasks = i - processes[offset].start - 1;	//subtract current index - the starting index - 1 to find number of tasks.
			 //store the IO value in the struct
			processes[offset].process_number = processNumber;
			processNumber++;						//reset IO back to 0 
			offset++;					//increment process number
		}
	}

	
	
	if(OS_Config.Scheduler == "FIFO")	
	{
			
		return;
	}
	else if(OS_Config.Scheduler == "SJF")	//bubble sort the processes array based on the amount of tasks per process
	{
		for(int j = 0; j < processors - 1; j++)
		{
			for(int k = 0; k < processors - j - 1; k++)
			{
				if(processes[k].tasks > processes[k+1].tasks)
				{
					swapProcess(&processes[k], &processes[k+1]);
				}
			}	
		}
	}
	else if(OS_Config.Scheduler == "PS")	//bubble sort the processes array based on the amount of IO per process
	{
		for(int j = 0; j < processors - 1; j++)
		{
			for(int k = 0; k < processors - j - 1; k++)
			{
				if(processes[k].IO < processes[k + 1].IO)
				{
						swapProcess(&processes[k], &processes[k+1]);
				}
			}	
		}
	}
	else	//if the scheduler has a wrong scheduler string, throw error
	{
		error_handle("Error: Config File (Scheduling) does not match specifications!");
	}


	//put this to mark start of simulation
	hold.push_back("S{begin}0;");

	//create the new vector with the scheduler ordered properly
	for(i = 0; i < processors; i++)
	{
		for(int l = processes[i].start; l < (processes[i].end + 1); l++)
		{
			temp = MetaFile[l];
			hold.push_back(temp);
		}
	}
	hold.push_back("S{finish}0."); //mark the end of simulation

	//clear oroginal Metafile vector
	MetaFile.clear();
	//set it equal to the new one for simulation
	MetaFile = hold;
	
}




/*
* This is the readConfigFile function.
*
* The takes in a char pointer which will be the file name to open and then takes in a vector of strings to take the file inputs and put it in there.
* The function makes sure that the file is open. If it isn't, then the function closes the file just to be sure and then calls error_handle to produce an error.
* If the file is open, the function reads the data of the files as a line of strings and puts it in the check vector. 
* The function closes the file once all of that is done.
* 
* @Parameters:
* char * file_Name, which is the pointer to the file_Name that will be opened.
* vector <string> &check, which is the vector of strings that will contain the line by line data from the file. 
*
* @Return: None 
*
*/
void readConfigFile(char * file_Name, vector <string> &check)
{
	ifstream openFile;
	openFile.open(file_Name);
	string temp, log, temp2;
	float version = 0.0;
	

	if(!openFile.is_open())
	{
		openFile.close();
		error_handle("The file you have entered could not be opened or found!");
	}

	else if(openFile.is_open())
	{
		for(int i = 0; i < 19; i++)
		{
			getline(openFile, temp);
			check.push_back(temp);
		}
	}
	openFile.close();
}

/*
*
* This is the error_handle function to cout errors to the terminal and exit the program.
*
* This function takes the string error and cout's it to the terminal. The function then exits the program.
*
* @Parameters: string error, which is the string to cout
* @Return: None 
* 
*/
void error_handle(string error)
{
	cout << error << endl;
	exit(0);
}

/*
* This is the position_check function to make sure that the position of data to be searched exists
*
* This function compares the position to 0 to make sure that the character searched for exists. If it doesn't then there is an error in formatting in the file. 
* If the position is set to 0, then the function concatenates the Type with a predetermined string. The function calls error_handle with the new string error to display the error and exit the program.
*
* @Parameters: 
* size_t position, which is the integer type to compare to 0 to make sure that the position exists
* string Type, the string to modify the error message to print out to the terminal
*
* @Return: None 
*
*/
void position_check(size_t position, string Type)
{
	if(position == 0)
	{
		string pass = "Error: " + Type + " file does not match specifications!";
		error_handle(pass);
	}
}	

/*
* This is the stringify function to fix whitespace at the end of a string.
*
* This function takes in a string and checks to see if there is a whitespace at the end and beginning of it. If there is, the function creates a new string that has everything but the whitespace before and at the end of it.
* The function then returns the string. The purpose of this is so that I can properly read the data and implement my error checking and computations without parsing issues.
*
* @Parameters: 
* string hold, which is the string to modify so that the white space is gone.
*
* @Return:
* The function returns the modified version of the string hold without the whitespace at the end.
*
*/
string stringify(string hold)
{
	while(hold[hold.length() - 1] == ' ')
	{
		int stringify = hold.length() - 1;
		hold = hold.substr(0,stringify);
	}
	while(hold[0] == ' ')
	{
		hold = hold.substr(1, hold.length());
	}
	
	return hold;
}



/*
* This is the getSystemTime function to check the current system time in millseconds.
*
* @Parameters: 
* None
*
* @Return:
* The function returns the current system time in millseconds.
*
*/
double getSystemTime()
{

	return (clock() / 1000000.0);

}

/*
* This is the checkWhiteSpaces function.
*
* The function checks to see if the entire string is filled with white spaces.
*
* @Parameters: 
* string temp, which is the string to check if it is entirely whitespaces.
*
* @Return:
* The function returns true if the entire string is fille with white spaces.
*
*/
bool checkWhiteSpaces(string temp)
{
	for(int i = 0; i < temp.length(); i++)
	{
		if(temp[i] != ' ')
		{
			return false;
		}
	}
	return true;
}

