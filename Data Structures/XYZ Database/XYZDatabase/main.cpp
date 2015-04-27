// ***********************************************************************
//
// (c) Copyright 2013 Dr. Thomas Fernandez
//
//  All rights reserved.
//
//  thomas@cse.fau.edu
//
// ***********************************************************************

#include "XYZ_Database.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <time.h>

using namespace std;

string getCommandFrom(ifstream & fin)
{
	string com;
	if(fin.eof())
	{
		com="ENDBATCH";
	}
	else
	{
		getline(fin,com);
	}
	if( fin.eof() && com=="" )
	{
		com="ENDBATCH";
	}
	return com;
}

string metaHelp()
{
	string result;
	result += "Meta Commands:\n" ;
	result += "--------------\n" ;
	result += "BATCH <filename>\n"; 
	result += "ENDBATCH\n" ;
	result += "REDIRECT <filename>\n"; 
	result += "DIRECT\n" ;
	result += "TON\n" ;
	result += "TOFF\n" ;
	result += "METAHELP\n\n" ;
	return result;
}

void advancedCommandLineInterface(XYZ_Database & XYZ_Database)
{
	ifstream fin;
	ofstream fout;
	bool batchActive=false;
	bool redirectActive = false;
	bool timerOn=false;
	string com;
	cout<<metaHelp();
	cout<<XYZ_Database.transducer((string)"HELP")<<endl;
	do
	{
		if(!batchActive)
		{
			cout<<">";
			getline(cin,com);
		}
		else
		{
			com=getCommandFrom(fin);
		}


		//META COMMANDS
		if(com.substr(0,5)=="BATCH")
		{
			string filename=com.substr(6,9999);
			fin.open(filename.c_str());
			batchActive=true;
		}
		else if(com=="ENDBATCH")
		{
			fin.close();
			fin.clear();
			batchActive=false;
		}
		else if(com.substr(0,8)=="REDIRECT")
		{
			string filename=com.substr(9,9999);
			fout.open(filename.c_str());
			redirectActive=true;
		}
		else if(com=="DIRECT")
		{
			fout.close();
			fout.clear();
			redirectActive=false;
		}
		else if(com=="TON")
		{
			timerOn=true;
		}
		else if(com=="TOFF")
		{
			timerOn=false;
		}
		else if(com=="METAHELP")
		{
			if(redirectActive)
			{
				fout<<metaHelp();
			}
			else
			{
				cout<<metaHelp();
			}
		}
		else
		{
			string transducerResults;
			clock_t startTime=clock();
			transducerResults=XYZ_Database.transducer(com);
			clock_t endTime=clock();
			clock_t elapsedTime=endTime-startTime;
			if(!redirectActive)
			{
				cout<<transducerResults<<endl;
				if(timerOn) cout<<"["<<elapsedTime<<"ms]"<<endl;
			}
			else
			{
				fout<<transducerResults<<endl;
				if(timerOn) fout<<"["<<elapsedTime<<"ms]"<<endl;
			}
		}
	} while ((com != "QUIT")&&(com != "quit")&&(com != "Q")&&(com != "q"));
}

void commandLineInterface(XYZ_Database & XYZ_Database)
{
	string com;
	cout<<XYZ_Database.transducer("HELP")<<endl;
	do
	{
		cout<<">";
		getline(cin,com);
		cout<<XYZ_Database.transducer(com)<<endl;
	} while ((com!="QUIT")&&(com!="Q")&&(com!="quit")&&(com!="q"));
}

int main()
{
	XYZ_Database trialrun;
	advancedCommandLineInterface(trialrun);
	return 0;
}
