
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
// Supporting Function Declarations ///////////////////////////////////////////////////
//

void readConfigFile(char * file_Name, vector <string> &check);
void error_handle(string error);
void position_check(size_t position, string Type);
string stringify(string hold);
double getSystemTime();


//
// Supporting Function Implementations ///////////////////////////////////////////////////
//


/*
* This is the readConfigFile function.
*
* The takes in a char pointer which will be the file name to open and then takes in a vector of strings to take the file inputs and put it in there.
* The function makes sure that the file is open. If it isn't, then the function closes the file just to be sure and then calls error_handle to produce an error.
* If the file is open, the function reads the data of the files as a line of strings and puts it in the check vector. This is done until end of file is reached.
* Once end of file is reached, the function closes the file.
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
	string temp, log;
	float version = 0.0;
	int holder = 0;
	

	if(!openFile.is_open())
	{
		openFile.close();
		error_handle("The file you have entered could not be opened or found!");
	}

	else if(openFile.is_open())
	{
		while(!openFile.eof())
		{
			getline(openFile, temp);
			if(openFile.eof())
			{
				return;
			}
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

