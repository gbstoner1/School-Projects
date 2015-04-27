// ***********************************************************************
//
// (c) Copyright 2013 Dr. Thomas Fernandez
//
//  All rights reserved.
//
//  thomas@cse.fau.edu
//
// ***********************************************************************

#pragma once
#include <string>
#include <vector>
#include "Word.h"
using namespace std;

class filenamesNode
{

private:
	string data;
	filenamesNode * pNext;
	filenamesNode * pPrev;
	friend class filenames;
	friend class XYZ_Database;
};

class filenames
{
public:
	filenames();
	~filenames();
	bool fileexists(const std::string& filename);
	bool checkduplicates(string filename);
	void clear();
	void add(string s);
	string remove();
	void writedata();
	void readdata();
	bool isEmpty() {return pTop == NULL;};
	friend class XYZ_Database;
private:
	filenamesNode * pTop;
	filenamesNode * pBottom;
};

class filelinesNode
{
private:
	string data;
	int linenumber;
	string filename;
	filelinesNode * pNext;
	filelinesNode * pPrev;
	friend class filelines;
	friend class XYZ_Database;
};

class filelines
{
public:
	filelines();
	filelines(filenames & orig);
	string sanitize(string wordresult);
	~filelines();
	void clear();
	void process(string s);
	string remove();
	bool isEmpty() {return pTop == NULL;}
	friend class XYZ_Database;
private:
	filelinesNode * pTop;
	filelinesNode * pBottom;
};

class BSTOffilesNode
{
	BSTOffilesNode() {pLeft=NULL;pRight=NULL;}
	BSTOffilesNode(Word * pS) {pLeft=NULL;pRight=NULL;pData=pS;}
	friend class BSTOfWords;
private:
	Word * pData;
	BSTOffilesNode * pLeft;
	BSTOffilesNode * pRight;
};

class BSTOfWords
{
public:
	static BSTOffilesNode * notFound;
	BSTOfWords(){pRoot=NULL;}
	BSTOfWords(const BSTOfWords & src);
	BSTOfWords & operator = (const BSTOfWords & src);
	~BSTOfWords();
	void add(Word * pStu);
	string displayAll();
	bool isEmpty(){return pRoot==NULL;}
	Word * find(string key);
	vector<Word *> findMulti(string key);
//	int count();
//	int countStartsWithLetter(char c);
	void clear();
	bool remove(string key);
	friend class filelines;
	friend class XYZ_Database;

private:

	void copy(BSTOfWords & destBST,  BSTOffilesNode * ptrRoot);

	BSTOffilesNode * & findNode(string key, BSTOffilesNode * & ptrRoot);
	BSTOffilesNode * & leftMostNode(BSTOffilesNode * & ptrRoot);

	void clear(BSTOffilesNode * & ptrCurRoot);

//	int countStartsWithLetter(char c, BSTOffilesNode * & ptrCurRoot);
	int height(BSTOffilesNode * & ptrCurRoot);


//	int count(BSTOffilesNode * & ptrCurRoot);
//	double totalGPA(BSTOffilesNode * & ptrCurRoot);

	void add(Word * pStu,BSTOffilesNode * & ptrRoot);
	string displayAll(BSTOffilesNode * & ptrRoot);
	BSTOffilesNode * pRoot;
};