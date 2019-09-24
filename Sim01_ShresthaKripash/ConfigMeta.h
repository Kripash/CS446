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
// Class Declaration ///////////////////////////////////////////////////
//

/* IMPORTANT NOTICE */

/*
	I had to define my classes in one header file and implement by class functions in one cpp because of makefile errors. This was the only way for me to make it work like it was intended.
	I was getting redefinition errors so thats something i need to work on for the next project.

*/


class Config
{
	public: 

		Config();
		void insertString();
		void separateConfig(vector <string> &check, vector <int> &data, vector <string> &StringData);
		void ConfigErrorCheck(vector <string> &check, vector <int> &data);
		void DataStorage(vector <int> &data, vector <string> &StringData);
		void PrintConfigData(ostream& out);
		
		/*
		data that is given in the config file that must be stored.
        stored as public members for ease of access since, without having to make a get and set for each variable
		*/

		float version_number;
		string File_path;
		int Monitor_display_time;
		int Processor_cycle_time;
		int Scanner_cycle_time;
		int Hard_drive_cycle_time;
		int Keyboard_cycle_time;
		int Memory_cycle_time;
		int Project_cycle_time; 
		string Log_to;
		string Log_file_path;
	
		/*
		map with the keys as strings which hold the value ints
		The strings are the types of instructions that the Meta Data file can have and the ints are the values for the instructions 	
		*/
		map <string, int> Config_Data;

	private:
		/*
		private member to check the config file to make sure that the file is proper and does not have errors
		the user should not be able to edit this, the programmer should since the programmer is responsible
		to know what the config file consists of 
		This is done as a vector of strings to contain the skeleton of the config file
		*/
		vector <string> Config_check;
};


//
// Class Declaration ///////////////////////////////////////////////////
//

class MetaData
{
	public: 

		MetaData();
		void readMetaFile(string file_Name, vector <string> &check);
		void separateMeta(vector <string> &check, vector <string> &MetaFile);
		void MetaCheck(vector <string> &check, vector <string> &MetaFile);
		void calculateMetaData(vector <string> &Metafile, Config &OS_Config);
		void compute(string instruction, int data, Config &OS_Config);  
		void printMetrics(vector <string> &MetaFile, ostream& out);
		void printToBoth(Config &OS_Config,vector <string> &MetaFile, ostream& out);

	public: 
	
		/*
		private member to check the Meta Data file to make sure that the file is proper and does not have errors
		the user should not be able to edit this, the programmer should since the programmer is responsible
		to know what the Meta Datafile consists of 
		This is done as a vector of strings to contain the skeleton of the Meta Data file
		*/
		vector <string> Meta_Check;

		/*
		Vector of ints which is used to contain the computed values of each instruction provided in the Meta Data file. 
		This is in order of the Meta Data File to make it easier to print out the data.
		*/
		vector <int> Meta_Data;
};






