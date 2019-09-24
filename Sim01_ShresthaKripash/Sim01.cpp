//
// Header Files ///////////////////////////////////////////////////
//

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>
#include <map>
#include "ConfigMeta.cpp"



using namespace std;




/* IMPORTANT NOTICE */

/*
	I had to define my classes in one header file and implement by class functions in one cpp because of makefile errors. This was the only way for me to make it work like it was intended.
	I was getting redefinition errors so thats something i need to work on for the next project.

*/


//
// Main Function Implementation ///////////////////////////////////
//


int main(int argc, char *argv[]){

	Config OS_Config;	//My ADT for the config file reading, storing data and error checking.
	MetaData OS_Meta;	//My ADT for the Meta file reading, storing data and error checking.

	if(argc != 2)	//if there are too many or few arguments, call error_handle.
	{
		error_handle("Invalid amount of command line arguments!");
		
	}
	
	vector <string> check;	//vector of strings used to check for errors in the files
	vector <int> ConfigData; //Vector of ints to hold the data of the integer datas of the config file
	vector<string> StringData; //vector of strings to hold the strings of data of the config file
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

	string Log_to = OS_Config.Log_to;	//contain the string to decide where to print

	if(Log_to == "Log to Both")	//If the log is to both, print out to file and the terminal by calling printToBoth function
	{
		ofstream openOutputFile;
		openOutputFile.open(OS_Config.Log_file_path.c_str());
		OS_Meta.printToBoth(OS_Config, MetaFile, openOutputFile);
		openOutputFile.close();
	}
	else if(Log_to == "Log to Monitor")	//If the log is to monitor, call PrintConfigData and printMetrics with cout as the parameter for ostream
	{
		OS_Config.PrintConfigData(cout);
		OS_Meta.printMetrics(MetaFile,cout);
	}
	else if(Log_to == "Log to File")	//If the log is to file, call PrintConfigData and printMetrics with the ofstream as the parameter for ostream
	{
		ofstream openOutputFile;
		openOutputFile.open(OS_Config.Log_file_path.c_str());
		OS_Config.PrintConfigData(openOutputFile);
		OS_Meta.printMetrics(MetaFile,openOutputFile);
		openOutputFile.close();
	}
	else	//else if the string does not match any of those, produce error by calling error_handle for the instruction for log
	{
		error_handle("Can't log to the instruction provided!");
	}

	return 0;
}



