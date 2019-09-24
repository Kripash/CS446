//
// Header Files ///////////////////////////////////////////////////
//

#include "ConfigMeta.h"
#include "Sim01.h"
#include <string>

using namespace std;

/* IMPORTANT NOTICE */

/*
	I had to define my classes in one header file and implement by class functions in one cpp because of makefile errors. This was the only way for me to make it work like it was intended.
	I was getting redefinition errors so thats something i need to work on for the next project.

*/



/*
* This is the default constructor for the Config class.
*
* This function intializes the Config_check vector in the config class so that the program can compare the config file to the skeleton of the  expected config file to make sure that there are no errors. 
* It does this by constantly adding a string to the Config_check vector. The string is determined by the programmer as it is made to the skeletonof the config file.
*
*
* @Parameters: None 
* @Return: None 
*
*/
Config::Config()
{

	Config_check.push_back("Start Simulator Configuration File");
	Config_check.push_back("Version/Phase:");
	Config_check.push_back("File Path:");
	Config_check.push_back("Monitor display time {msec}:");
	Config_check.push_back("Processor cycle time {msec}:");
	Config_check.push_back("Scanner cycle time {msec}:");
	Config_check.push_back("Hard drive cycle time {msec}:");
	Config_check.push_back("Keyboard cycle time {msec}:");
	Config_check.push_back("Memory cycle time {msec}:");
	Config_check.push_back("Projector cycle time {msec}:");
	Config_check.push_back("Log:");
	Config_check.push_back("Log File Path:");
	Config_check.push_back("End Simulator Configuration File");

}

/*
* This is the separateConfig function for the Config class.
*
* This function takes in the strings that were taken from the config file and separates them. 
* The function ignores the first and last element of the check vector as those do not need to be separated.
* The function then loops for every vector element besides the two mentioned above. 
* The function takes the string from the vector element and assings it to the variable temp.
* After that, the function searches for the character ":" in the temp string and marks the position + 1.
* The string is then separated into two halves, the first and second, front of the colon and after the colon.
* The function then checks to make sure that the position exists and if it doesn't the function logs the two types of error.
* Since we have special cases to separate the data, strings, floats and ints, the function separates them based on a counter
* which is used to monitor what to use based on the example config file given
*
* @Parameters: 
* vector <string> &check, which is the vector of strings that is taken from the config file to separate. 
* vector <int> &data, which is the vector of ints to hold the data that is taken from the config file. 
* vector <string> &stringdata, which is the vector of strings to hold the data that is taken from the config file.
*
* @Return: None 
*
*/
void Config::separateConfig(vector <string> &check, vector <int> &data, vector <string> &StringData)
{
	string temp, first_half, second_half;
	char hold;
	float version = 0;
	size_t convert = 0;
	int data_hold = 0, position = 0, counter = 0;
	
	//loop to go through the vector minus the first and last element
	for(counter = 1; counter < check.size() - 1; counter++)
	{
		//set the temp variable to the current "line" 
		temp = check[counter];

		//search for the colon in the string and mark it
		position = temp.find(":") + 1;

		//substract first half of the string from start to the position and store it.
		first_half = temp.substr(0, position);
		
		//make sure that the data is availabe to get the value of second half
		if((position + 1) < temp.length())
		{
			second_half = temp.substr(position + 1);
		}
		//if it isn't then there is data missing and we log the error by calling error handle
		else
		{
			error_handle("Error: Empty data in Config file");
		}
		
		//check to make sure the position is valid and the config file matches specifications

		position_check(position, "Config");

		//We have different types to convert, so we separate it into three statements, the first being the version as it is a float
		if(counter == 1)
		{
			version = stof(second_half, &convert);
			version_number = version;
			check[counter] = first_half;
		}
		//the second being the strings, which can be pushed easily
		else if(counter == 2 || counter == 10 || counter == 11)
		{
			check[counter] = first_half; 
			StringData.push_back(second_half);
		}	
		//and the last being ints, which is converted using string to int function in the c++ library
		else if( counter >= 3 && counter <= 9)
		{
			data_hold = stoi(second_half, &convert);
			data.push_back(data_hold);
			check[counter] = first_half;
		}
	}
}

/*
* This is the ConfigErrorCheck function for the Config class.
*
* This function takes the check vector as the passed parameter and makes sure to check that the size of that vector is the size of the Config_check vector in the class. 
* If the vector sizes are not equal to each other, the function calls error_hangle to produce an error.
* The function then iterates for the size of either, since they are equal and comapres the string of each element within the vector. 
* If the strings in each element are the same, the function does not produce an error, otherwise it calls error_handle to produce an error.
* The function also iterates through the size of the data vector and checks to see if any element is 0 to check for 0 data cycle time to handle errors.
*
*
* @Parameters: 
* vector<string> &check, which is the vector containing data from the config file to check for comparison to check for file error
* vector<int> &data, which is the vector of data from the config file, to check for 0 cycle times.
*
* @Return: None 
*
*/
void Config::ConfigErrorCheck(vector <string> &check, vector <int> &data)
{
	if (check.size() != Config_check.size() )
	{
		error_handle("Error: Config File size does not match specifications!");
		
	}
	else if(check.size() == Config_check.size())
	{
		for(int i = 0; i < Config_check.size(); i++)
		{	
			if(check[i] != Config_check[i])
			{
				error_handle("Error: Config File does not match specifications!");
			}
		}
	}
	for(int i = 0; i < data.size(); i++)
	{
		if(data[i] == 0)
			{
				error_handle("Error: 0 cycle time appears in Config File");
			}
	}
}

/*
* This is the DataStorage function for the Config class.
*
* This function takes in the vectors of data presented, both strings and ints, and then stores them in the respective variables in the class and stores it into a map for easy acces. 
* They are stored into variables for each access when priting out the data and then stored into a map with string and int for easy access when performing calculations.
* 
* @Parameters: 
* vector<int> &data, which consists of the cycle times from the config file. 
* vector<string> &StringData, which consists of the string data from the config file, such as the file path, where to log to and the file path.
*
* @Return: None 
*
*/
void Config::DataStorage(vector <int> &data, vector <string> &StringData)
{
	File_path =  StringData[0];
	Log_to = StringData[1];
	Log_file_path = StringData[2];

	Monitor_display_time = data[0];
	Config_Data.insert(pair<string,int>("monitor",data[0]));

	Processor_cycle_time = data[1];
	Config_Data.insert(pair<string,int>("run",data[1]));

	Scanner_cycle_time = data[2];
	Config_Data.insert(pair<string,int>("scanner",data[2]));

	Hard_drive_cycle_time = data[3];
	Config_Data.insert(pair<string,int>("hard drive",data[3]));

	Keyboard_cycle_time = data[4];
	Config_Data.insert(pair<string,int>("keyboard",data[4]));

	Memory_cycle_time = data[5];
	Config_Data.insert(pair<string,int>("block",data[5]));
	Config_Data.insert(pair<string,int>("allocate",data[5]));

	Project_cycle_time = data[6];
	Config_Data.insert(pair<string,int>("projector",data[6]));
}

/*
* This is the PrintConfigData function for the Config class.
*
* The function prints out the data of the config file in the respective order given in the example output of the assignment file.
* The function is able to handle, ostream so that it can print to the file and terminal.
*
* @Parameters:
* ostream& out, which determines where the stream of the cahracters will be printed to. 
*
* @Return: None 
*
*/
void Config::PrintConfigData(ostream& out)
{
	out << "Configuration File Data" << endl;
	out << "Monitor = " << Monitor_display_time << " ms/cycle" << endl;
	out << "Processor = " << Processor_cycle_time << " ms/cycle" << endl;
	out << "Scanner = " << Scanner_cycle_time << " ms/cycle" << endl;
	out << "Hard Drive = " << Hard_drive_cycle_time << " ms/cycle" << endl;
	out << "Keyboard = " << Keyboard_cycle_time << " ms/cycle" << endl;
	out << "Memory = " << Memory_cycle_time << " ms/cycle" << endl;
	out << "Projector = " << Project_cycle_time << " ms/cycle" << endl;
	
	if(Log_to == "Log to Both")
	{
		out << "Logged to: monitor and " << Log_file_path << endl << endl;
	}
	else if(Log_to == "Log to Monitor")
	{
		out << "Logged to: monitor" << endl << endl;
	}
	else if(Log_to == "Log to File")
	{
		out << "Logged to: file" << endl << endl;
	}
}

/*
*
* This is the default constructor for the MetaData class.
*
* This function intializes the Meta_check vector in the MetaData class so that the program can compare the Meta file to the skeleton of the expected Meta file to make sure that there are no errors. 
* It does this by constantly adding a string to the Meta_Data vector. The string is determined by the programmer as it is made to the skeleton of the Meta file.
*
*
* @Parameters: None 
* @Return: None 
*
*/
MetaData::MetaData()
{
	Meta_Check.push_back("Start Program Meta-Data Code:");
	Meta_Check.push_back("S{begin}0;");
	Meta_Check.push_back("A{begin}0;");
	Meta_Check.push_back("A{finish}0;");
	Meta_Check.push_back("S{finish}0.");
	Meta_Check.push_back("End Program Meta-Data Code.");
	
}

/*
* This is the readMetaFile function for the Meta Data class.
*
* The function takes in a string for the file name as it is obtained from the config file. This file is to be opened so that data can be read from the Meta File.
* The function makes sure that the file is open. If it isn't, then the function closes the file just to be sure and then calls error_handle to produce an error.
* If the file is open, the function reads the data of the files as a line of strings and puts it in the check vector. This is done until end of file is reached.
* Once end of file is reached, the function closes the file.
* 
* @Parameters:
* string file_Name, which is the string which contains the file name of the Meta Data File.
* vector <string> &check, which is the vector of strings that will contain the line by line data from the file. 
*
* @Return: None 
*
*/
void MetaData::readMetaFile(string file_Name, vector <string> &check)
{

	ifstream openFile;
	openFile.open(file_Name);
	string temp, log;
	
	if(!openFile.is_open())
	{
		openFile.close();
		error_handle("Error: The file you have entered could not be opened or found!");
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
* This is the separateMeta function for the Config class.
*
* This function starts off by making a loop that iterates from the second element of the vector the second to last since the first and last element are a line of string.
* The function then stores the string into a temp variable. the function does a while loop check to make sure the size of the string is not zero and its not the second to last element of the array, 
* because that string has a special command with a period on it.
* The function then increments remove_space so that we can remove the white space in the string to separate them into strings without white space. 
* The function then separates the strings into multiple other strings by finding the semi-colon and substracting strings and pushing them MetaFile vector.
* The function repeats this for each element except for the second to last element within the check vector. 
* This is because that string ends with a period and we have to keep going until we find a semi colon or a period. After doing so, the function the strings into the MetaFile vector.
*
* @Parameters: 
* vector<string> &check, which is the vector containing line by line data from the Metae Data File
* vector<string> &MetaFile, which is the vector that will hold the string data from the MetaFile.
*
* @Return: None 
*
*/
void MetaData::separateMeta(vector <string> &check, vector<string> &MetaFile)
{
	string temp, hold, end;
	size_t position;
	int counter = 0, remove_space = 0;
	
	for(counter = 1; counter < check.size() - 1; counter++)
	{
		temp = check[counter];
		remove_space = 0;
		while(temp.size()!= 0 && (counter != check.size() - 2))
		{
			//increment remove_space to determine which string we are on the line
			remove_space++;
			//search for the semi colon to separate the strings and verify it does exist, else parse an error.
			position = temp.find(";") + 1;
			position_check(position, "Meta");

			//if this is the second or higher string, we will use this to remove the white space at the end of the string.
			if(remove_space >= 2)
			{
				hold = temp.substr(1, position);
				hold = stringify(hold);
				temp = temp.substr(position);
				MetaFile.push_back(hold);
			}
			//if this is the first string of the line, use this, since we will not have to remove the white space at the end of the string.
			else
			{
				hold = temp.substr(0, position);
				temp = temp.substr(position);
				MetaFile.push_back(hold);
			}
		}
		//if this is the second to last element of the check vector, we have a special case since it ends with a period.
		if(counter == check.size() - 2)
		{
			//store the last string instruction into end since it ends with a period.
			temp = check[counter];
			position = temp.rfind(" ") + 1;
			position_check(position, "Meta");
			end = temp.substr(position, (temp.size()));

			//run until the size of the string is not zero
			while(temp.size() != 0)
			{
				remove_space++;
				//compare the end string to the temp string to make sure that we are not at the last string to end the loop
				if(end == temp)
				{
					MetaFile.push_back(end);
					return;
				}
				
				//search for the semi colon to separate the strings and verify it does exist, else parse an error.
				position = temp.find(";") + 1;
				position_check(position, "Meta");

				//if this is the second or higher string, we will use this to remove the white space at the end of the string.
				if(remove_space >= 2)
				{
					hold = temp.substr(0, position);
					temp = temp.substr(position + 1);
					MetaFile.push_back(hold);
				}
				//if this is the first string of the line, use this, since we will not have to remove the white space at the end of the string.
				else
				{
					hold = temp.substr(0, position);
					temp = temp.substr(position + 1);
					MetaFile.push_back(hold);
				}
			}
		}
	}
}


/*
* This is the MetaCheck function for the Config class.
*
* This function ultimately validates the MetaFile to make sure that it is proper and ready for use and computations. 
* The function erases all the data from the check string except for the first and last element.
* The function loops through the MetaFile separated strings of instructions. Then at the first, second, last and second last element which are the process and application instructions
* This function takes the check vector and compares it with the Meta_check vector.
* If the vector sizes are not equal to each other, the function calls error_hangle to produce an error.
* The function then iterates for the size of either, since they are equal and comapres the string of each element within the vector. 
* If the strings in each element are the same, the function does not produce an error, otherwise it calls error_handle to produce an error.
*
* @Parameters: 
* vector<string> &check, which is the vector containing data from the MetaFile to check for comparison to check for file error
* vector<string> &MetaFile, which is the vector containing the data of separated strings from the MetaFile.
*
* @Return: None 
*
*/
void MetaData::MetaCheck(vector <string> &check, vector <string> &MetaFile)
{
	int i = 0;
	string temp;
	string hold = check[check.size() - 1];	//holds the last element of the vector.
	while(check.size() != 1)	
	{	
		check.erase(check.begin() + 1);	//removes all elements besides the first element.
	}

	for(i = 0; i < MetaFile.size(); i++)	//loops though the MetaFile string of separated instructions
	{
		if( (i == 0) || (i == 1) || (i == (MetaFile.size() - 1)) || (i == (MetaFile.size() - 2)))	//if this is the first, second, or last and second last element store those in the check string.
		{
			temp = MetaFile[i];
			check.push_back(temp);	//pushes the process and apllication begin and finish into the check vector.
		}
	}
	check.push_back(hold); //push the last string of the file to the check vector
	
	if (check.size() != Meta_Check.size() )
	{
		error_handle("Error: Meta File size does not match specifications!");
	}
	else if(check.size() == Meta_Check.size())
	{
		for(int i = 0; i < Meta_Check.size(); i++)
		{	
			if(check[i] != Meta_Check[i])
			{
				error_handle("Error: Meta File does not match specifications!");
			}
		}
	}
}

/*
* This is the MetaCheck function for the Config class.
*
* This function starts off by iterating through the MetaFile data vector. It starts at the 3rd element and ends at the second to last since those are the application and process instructions 
* that have already been verified at the metaCheck function.
* The function stores the string of the element in a temp string. The function dissects the strings into a char, which represents the Meta Code. 
* The function then gets the instruction from the string and stores it into the string instruction.
* The function then gets the integer data from the string and stores it into data_hold and converts it into an int using stoi and stores it into data.
* The function then goes into a switch statement to switch based on the char code, which is the Meta code, that the function dissected from the string.
*
* @Parameters: 
* vector<string> &MetaFile, which is the vector containing the data of separated strings from the MetaFile.
* Config &OS_Config, which is the Config object to retrieve the map from so we can do the computations.
*
* @Return: None 
*
*/
void MetaData::calculateMetaData(vector <string> &MetaFile, Config &OS_Config)
{
	char code;
	string temp, instruction, data_hold;
	int position = 0, position_2 = 0, position_3, data = 0, counter = 0;
	size_t convert = 0;


	for(int i = 2; i < (MetaFile.size() - 2); i++)
	{
		temp = MetaFile[i];
	
		//if another application has begun or finished, increment i++ to move to the next instruction
		while((temp == "A{begin}0;") || (temp =="A{finish}0;"))
		{
			i++;
			temp = MetaFile[i];
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
		if((position_3 - position_2 - 1) == 0){
			error_handle("Error: Missing Data in Meta File");
		}
		//Other wise get the value of the data and convert that to string using stoi.
		data_hold = temp.substr(position_2 + 1, position_3 - position_2 - 1);
		data = stoi(data_hold, &convert);

		
		switch(code)
		{
			//if the char instructions are as exists, call the compute function. Since we already verified for process and application in config check we do not have to check here
			case 'P':			
			case 'I':
			case 'O':
			case 'M':
					compute(instruction, data, OS_Config);
					break;
			default:
					error_handle("Error: Invalid Meta Data Code!");	//otherwise call error handle with invalid meta data code as the string passed
					break;
		}
	}
}


/*
* This is the compute function for for the MetaData class.
*
* This function makes sure that the instruction string actually exists and is valid. It does this by comparing it to the keys in the map.
* If the instruction is not valid, the function creates an error message and generates it by calling error_handle with that string.
* If the instruction does exist. The function finds that instruction and gets the value of that instruction, which is acquired from the config file. 
* The function multiples the data passed into the function by the value of the instruction and pushes that into the Meta_Data vector.
*
*
* @Parameters:
* string instruction, which is the instruction string the function searches for in the map.
* int data, which is the amount of times that the cycle for the instruction is run for.
* Config &OS_Config, which is the Config object to retrieve the map from so we can do the computations.
*
* @Return: None 
*
*/
void MetaData::compute(string instruction, int data, Config &OS_Config)
{
	int compute;
	
	if(OS_Config.Config_Data.count(instruction) == 0)
	{
		string pass = "Error: The instruction: '" + instruction + "' does not exist.";
		error_handle(pass);
	}
	else
	{
		compute = OS_Config.Config_Data.find(instruction) -> second;
		compute = data * compute;
		Meta_Data.push_back(compute);
	}
}


/*
* This is the printMetrics function for for the MetaData class.
*
* This prints the Meta Data Metrics as specified by the example in the assignment instructions. 
* The function starts off with the 3rd element of the MetaFile vector since the first two are intializiation for process and application.
* The function then finds all semicolons and removes them from the string so that it may be printed to the screen.
* The function then prints out that string which displays the instruction from the MetaFile and then prints out the data associate with the computation for that instruction.
* Since we start the loop at 2, the offset for the Data is -2.
*
* @Parameters:
* vector <string> &MetaFile, which is the string of instructions from the MetaFile to print.
* ofstream &out, which is the ostream that the function will print out to, either file or monitor.
*
* @Return: None 
*
*/
void MetaData::printMetrics(vector <string> &MetaFile, ostream& out)
{
	string temp;
	int position = 0;
	int counter  = 0;

	out << "Meta-Data Metrics" << endl;
	for(int i = 2; i < (MetaFile.size() - 2); i++)	
	{	
		temp = MetaFile[i];
		while((temp == "A{begin}0;") || (temp =="A{finish}0;"))
		{
			i++;
			counter++;
			temp = MetaFile[i];
		}
		
		position = temp.find(";");
		position_check(position, "Meta Data");
		temp = temp.substr(0, position);
		out << temp << " - " << Meta_Data[i - counter -2] << " ms " << endl;
	}
}


/*
* This is the printToBoth function for for the MetaData class.
*
* This function calls the PrintConfigData function twice with cout and then with ostream out as the parameters passed to print the data to the monitor and file specified.
* This function then calls printMetrics function twice with MetaFile and cout and then with Metafile and out as the parameters passed  to print the data to the monitor and file specified.
*
*
* @Parameters:
* Config &OS_Config, which is the Config object to print the data from.
* ofstream &out, which is the file stream that the function will print the data to.
*
* @Return: None 
*
*/
void MetaData::printToBoth(Config &OS_Config,vector <string> &MetaFile, ostream& out)
{
	OS_Config.PrintConfigData(cout);
	printMetrics(MetaFile,cout);

	OS_Config.PrintConfigData(out);
	printMetrics(MetaFile,out);
}










