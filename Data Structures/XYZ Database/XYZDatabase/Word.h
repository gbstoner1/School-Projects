#pragma once

#include <string>
#include "filenames.h"
using namespace std;




class Word
{
public:
	string getName(){return name;};
	void setName(string s){name=s;};
	/*double getGPA(){return gpa;}
	void setGPA(double d){if(d>4.0)d=4.0;gpa=d;}*/
	friend class XYZ_Database;
	friend class filelinesNode;
private:
	string name;
	filelinesNode * pLine;
};


