// ***********************************************************************
//
// (c) Copyright 2014 Geoffrey Stoner
//
//  All rights reserved.
//
//  thomas@cse.fau.edu
//
// ***********************************************************************

#include "filenames.h"
#include "fstream"
#include "iostream"
#include "Word.h"
#include <algorithm>
#include <sys/stat.h>


filenames::filenames()
{
	pTop = NULL;
	pBottom=NULL;
}


filenames::~filenames()
{
	clear();
}

void filenames::clear()
{
	while(!isEmpty())
	{
		remove();
	}
}

void filenames::add(string s)
{
	filenamesNode * pNewNode = new filenamesNode;
	if(!pNewNode) // pNewNode==NULL
	{
		//out of memory???
		//exit(99);
		throw(99);
	}
	else
	{
		if(isEmpty())
		{
			(*pNewNode).data=s;
			(*pNewNode).pPrev=NULL;
			(*pNewNode).pNext=NULL;
			pTop=pNewNode;
			pBottom=pNewNode;
		}
		else
		{
			(*pNewNode).data=s;
			(*pNewNode).pPrev=NULL;
			(*pNewNode).pNext=pTop;
			(*pTop).pPrev=pNewNode;
			pTop=pNewNode;
		}
	}
}

string filenames::remove()
{
	if(isEmpty())
	{
		throw(98);
	}
	string result;
	if(pBottom==pTop)
	{
		//special case for removing last item
		result=(*pBottom).data;
		delete pBottom;
		pBottom=NULL;
		pTop=NULL;
	}
	else
	{
		result=(*pBottom).data;
		filenamesNode * pTemp = pBottom;
		pBottom=(*pBottom).pPrev;
		(*pBottom).pNext=NULL;
		delete pTemp;
	}
	return result;
}

void filenames::readdata()
{
	ifstream infile;
	infile.open("savednames.txt");
	string line;
	while(infile.good())
	{
		getline(infile, line);
		if(line.size() == 0)
		{
			infile.close();
			break;
		}
		else
		{
			add(line);
		}
	}
	infile.close();
}

bool filenames::fileexists(const std::string& filename)
{
    struct stat buf;
    if (stat(filename.c_str(), &buf) != -1)
    {
        return true;
    }
    return false;
}	

bool filenames::checkduplicates(string filename)
{
	filenamesNode * pCurrent = pTop;
		while(pCurrent!=NULL)
		{
		if(filename==pCurrent->data)
		{
			return true;
		}
		pCurrent=(*pCurrent).pNext;
		}
		return false;
}

void filenames::writedata()
{
		filenamesNode * pCurrent = pTop;
		ofstream outfile;
		outfile.open("savednames.txt", ios::trunc);
		while(pCurrent!=NULL)
		{
		outfile << pCurrent->data << "\n" ;
		pCurrent=(*pCurrent).pNext;
		}
		outfile.close();
}

filelines::filelines()
{
	pTop = NULL;
	pBottom=NULL;
}


filelines::~filelines()
{
	clear();
}

void filelines::clear()
{
	while(!isEmpty())
	{
		remove();
	}
}

string filelines::sanitize(string wordresult)
{
	 int lengthofword;
	lengthofword = wordresult.length();
	char ch = wordresult[lengthofword-1];
	if(((ch <= 'z' && ch >= 'a') || (ch <= 'Z' && ch >= 'A')))
	{

					 return wordresult;
	}
	else
	{
	if (wordresult.size () > 0)  wordresult.resize (wordresult.size () - 1);
		return wordresult;
	}
}

void filelines::process(string s)
{
	ifstream myfile;
	int counter=1;
	string line;
	myfile.open(s);
	while(myfile.good())
	{
		filelinesNode * pNewNode = new filelinesNode;
		getline (myfile,line);
		if(!pNewNode) // pNewNode==NULL
	{
		//out of memory???
		//exit(99);
		throw(99);
	}
	else
	{
		if(isEmpty())
		{
			
			(*pNewNode).data=line;
			(*pNewNode).linenumber=counter;
			(*pNewNode).filename=s;
			(*pNewNode).pPrev=NULL;
			(*pNewNode).pNext=NULL;
			pTop=pNewNode;
			pBottom=pNewNode;
		}
		else
		{
			(*pNewNode).data=line;
			(*pNewNode).linenumber=counter;
			(*pNewNode).filename=s;
			(*pNewNode).pPrev=NULL;
			(*pNewNode).pNext=pTop;
			(*pTop).pPrev=pNewNode;
			pTop=pNewNode;
		}
	}
		counter+=1;
	}
	myfile.close();
	
}

string filelines::remove()
{
	if(isEmpty())
	{
		throw(98);
	}
	string result;
	if(pBottom==pTop)
	{
		//special case for removing last item
		result=(*pBottom).data;
		delete pBottom;
		pBottom=NULL;
		pTop=NULL;
	}
	else
	{
		result=(*pBottom).data;
		filelinesNode * pTemp = pBottom;
		pBottom=(*pBottom).pPrev;
		(*pBottom).pNext=NULL;
		delete pTemp;
	}
	return result;
}

BSTOffilesNode * BSTOfWords::notFound = NULL;

BSTOfWords::BSTOfWords(const BSTOfWords & src)
{
	pRoot=NULL;
	(*this)=src;
}

BSTOfWords & BSTOfWords::operator = (const BSTOfWords & src)
{
	clear();
	copy((*this),src.pRoot);
	return (*this);
}

void BSTOfWords::copy(BSTOfWords & destBST,BSTOffilesNode * ptrRoot)
{
	if(ptrRoot==NULL)return;
	destBST.add( ptrRoot->pData);
	copy(destBST,ptrRoot->pLeft);
	copy(destBST,ptrRoot->pRight);
}



BSTOfWords::~BSTOfWords()
{
	clear();
}


/*int BSTOfWords::height()
{
	return height(pRoot);
}*/

int BSTOfWords::height(BSTOffilesNode * & ptrCurRoot)
{
	if(ptrCurRoot==NULL)
	{
		return 0;
	}
	return max(height(ptrCurRoot->pLeft),height(ptrCurRoot->pRight))+1;
	
}

void BSTOfWords::clear()
{
	clear(pRoot);
}

void BSTOfWords::clear(BSTOffilesNode * & ptrCurRoot)
{
	if(ptrCurRoot==NULL)return;	
	clear(ptrCurRoot->pLeft);
	clear(ptrCurRoot->pRight);
	_ASSERT((ptrCurRoot->pLeft==NULL)&&(ptrCurRoot->pRight==NULL));
	delete ptrCurRoot;
	ptrCurRoot=NULL;
}


void BSTOfWords::add(Word * pStu)
{
	add(pStu,pRoot);
}


void BSTOfWords::add(Word * pStu,BSTOffilesNode * & ptrRoot)
{
	//Do we add it to the Root Node?
	if(ptrRoot==NULL)
	{
		//Yes!
		BSTOffilesNode * pNewNode = new BSTOffilesNode(pStu);
		ptrRoot=pNewNode;
		return;
	}
	//Do we add it to the Left Sub BST?
	if( pStu->getName() <= ptrRoot->pData->getName() )
	{
		//Yes!
		add(pStu,ptrRoot->pLeft);
	}
	//Do we add it to the Right Sub BST?
	else
	{
		//Yes!
		add(pStu,ptrRoot->pRight);
	}
}

bool BSTOfWords::remove(string key)
{
	BSTOffilesNode * & pNodeFound = findNode(key,pRoot);
	if(pNodeFound==NULL) return false;
	if((pNodeFound->pLeft == NULL) && (pNodeFound->pRight == NULL))
	{
		delete pNodeFound;
		pNodeFound = NULL;
		return true;
	}
	else if((pNodeFound->pLeft != NULL) && (pNodeFound->pRight == NULL))
	{
		BSTOffilesNode * pTemp = pNodeFound;
		pNodeFound=pNodeFound->pLeft;
		delete pTemp;
		return true;
	}
	else if((pNodeFound->pLeft == NULL) && (pNodeFound->pRight != NULL))
	{
		BSTOffilesNode * pTemp = pNodeFound;
		pNodeFound=pNodeFound->pRight;
		delete pTemp;
		return true;
	}
	else //if((pNodeFound->pLeft != NULL) && (pNodeFound->pRight != NULL))
	{
		BSTOffilesNode * & pLeftMost = leftMostNode(pNodeFound->pRight);
		//do we really need to swap?
		Word * pTemp =pLeftMost->pData;
		pLeftMost->pData=pNodeFound->pData;
		pNodeFound->pData = pTemp;
		if((pLeftMost->pLeft == NULL) && (pLeftMost->pRight == NULL))
		{
			delete pLeftMost;
			pLeftMost = NULL;
			return true;
		}
		else //if((pLeftMost->pLeft == NULL) && (pLeftMost->pRight != NULL))
		{
			BSTOffilesNode * pTemp = pLeftMost;
			pLeftMost=pLeftMost->pRight;
			delete pTemp;
			return true;
		}
	}
}

BSTOffilesNode * & BSTOfWords::leftMostNode(BSTOffilesNode * & ptrRoot)
{

	if(ptrRoot->pLeft==NULL)
	{
		return ptrRoot;
	}
	return leftMostNode(ptrRoot->pLeft);
}


vector<Word *> BSTOfWords::findMulti(string key)
{
	vector<Word *> result;
	BSTOffilesNode * pNodeFound = findNode(key,pRoot);
	while(pNodeFound!=NULL)
	{
		result.push_back(pNodeFound->pData);
		pNodeFound = findNode(key,pNodeFound->pLeft);
	}
	return result;
}


Word * BSTOfWords::find(string key)
{
	BSTOffilesNode * & pNodeFound = findNode(key,pRoot);
	if(pNodeFound==NULL) return NULL;
	return pNodeFound->pData;
}


BSTOffilesNode * & BSTOfWords::findNode(string key, BSTOffilesNode * & ptrRoot)
{
	if(ptrRoot==NULL)
	{
		return notFound;
	}
	if(key==ptrRoot->pData->getName())
	{
		return ptrRoot;
	}
	if(key<=ptrRoot->pData->getName())
	{
		return findNode(key,ptrRoot->pLeft);
	}
	else
	{
		return findNode(key,ptrRoot->pRight);
	}

}

	string BSTOfWords::displayAll()
	{
		return displayAll(pRoot);
	}

	string BSTOfWords::displayAll(BSTOffilesNode * & ptrRoot)
	{
		string result;
		if(ptrRoot==NULL)
		{
			return "";
		}
		result = displayAll(ptrRoot->pLeft);
		result+=ptrRoot->pData->getName()+"\t"+"\n";
		result+=displayAll(ptrRoot->pRight);
		return result;
	}
