#include "XYZ_Database.h"
#include "misc.h"
#include <vector>
#include <sstream>
using namespace std;

XYZ_Database::XYZ_Database()
{
	if(listoffilenames.fileexists("savednames.txt")){
		listoffilenames.readdata();
		if(listoffilenames.pTop!=NULL)
		{
		if(listoffilenames.pBottom==listoffilenames.pTop)
		{
			//listoffilenames.add(listoffilenames.pBottom->data);
			listoffilelines.process(listoffilenames.pBottom->data);
		}
		else
		{
	    filenamesNode * pCurrent = listoffilenames.pTop;
		while(pCurrent!=NULL){
		//listoffilenames.add(pCurrent->data);
		listoffilelines.process(pCurrent->data);
		pCurrent=pCurrent->pNext;
		}
		}
		filelinesNode * pCurrent = new filelinesNode;
		pCurrent=listoffilelines.pTop->pNext;
			string sTempWord;
			int flagword=0;
			while(pCurrent!=NULL){
				string sTemp;
				sTemp=pCurrent->data;
				std::istringstream linestream(sTemp); // 
				std::string sTempWord;
				while (linestream >> sTempWord)
				{
					sTempWord=listoffilelines.sanitize(sTempWord);
					stringToLower(sTempWord);
					vector<Word *> vFoundWords = bsttree.findMulti(sTempWord);
					int sizeofresults=vFoundWords.size();
					flagword=0;
					for(int count=0; count<sizeofresults;count++)
					{
						if((vFoundWords[count]->pLine->linenumber==pCurrent->linenumber)&&(vFoundWords[count]->pLine->filename==pCurrent->filename))
						{
						flagword=1;
						}
						
					}
					if(flagword==1){

					}
					else
					{
					
					Word * bTempWord = new Word;
					bTempWord->name=sTempWord;
					bTempWord->pLine=pCurrent;
					bsttree.add(bTempWord);
					}
				}
				
			
                pCurrent=pCurrent->pNext;
			}
		
		}// end if for ptop null
	} //end if for good file
}


string XYZ_Database::transducer(string command)
{
	try
	{
		string result;
		vector<string> token = tokenize(command);
		stringToUpper(token[0]);
		if(token[0]=="HELLO")
		{
			result = "Hi there!";
		}
		else if((token[0]=="QUIT")||(token[0]=="Q"))
		{
			//listoffilenames.writedata(); switched to add_file section(outdated)
			result = "Goodbye";
		}
		else if((token[0]=="CLEAR")||(token[0]=="C"))
		{
			listoffilenames.clear();
			listoffilelines.clear();
			bsttree.clear();
		}
		else if((token[0]=="ADD_FILE")||(token[0]=="A"))
		{
			if(listoffilenames.fileexists(token[1]))
			{
				if(!listoffilenames.checkduplicates(token[1]))
				{
			bsttree.clear();
			listoffilenames.add(token[1]);
			listoffilelines.process(token[1]);
			filelinesNode * pCurrent = new filelinesNode;
			pCurrent=listoffilelines.pBottom;
			//pCurrent=listoffilelines.pTop->pNext;
			string sTempWord;
			while(pCurrent!=NULL){
				string sTemp;
				sTemp=pCurrent->data;
				std::istringstream linestream(sTemp); // 
				std::string sTempWord;
				int flagword=0;
				while (linestream >> sTempWord)
				{
					flagword=0;
					sTempWord=listoffilelines.sanitize(sTempWord);
					stringToLower(sTempWord);
					vector<Word *> vFoundWords = bsttree.findMulti(sTempWord);
					int sizeofresults=vFoundWords.size();
					for(int count=0; count<sizeofresults;count++)
					{
						if((vFoundWords[count]->pLine->linenumber==pCurrent->linenumber)&&(vFoundWords[count]->pLine->filename==pCurrent->filename))
						{
						flagword=1;
						}
						
					}
					if(flagword==1){

					}
					else
					{
					Word * bTempWord = new Word;
					bTempWord->name=sTempWord;
					bTempWord->pLine=pCurrent;
					bsttree.add(bTempWord);
					}
				}
                pCurrent = pCurrent -> pPrev;
			} // end while do of filelines;
			listoffilenames.writedata();
			result = token[1] + " has been added as a file.";
				}//end if for checkduplicates
				else
				{
					result = token[1] + "file already exists";
				}
			//result += bsttree.displayAll() + "\n";
			}
			else
			{
				result = token[1] + "file not found";
			}
		}
		else if((token[0]=="FIND_WORD")||(token[0]=="F"))
		{
			stringToLower(token[1]);
			vector<Word *> vFoundWords = bsttree.findMulti(token[1]);
			int sizeofresults=vFoundWords.size();
			if(sizeofresults==0)
			{
				result= "Not Found";
			}
			else
			{
				for(int count=0; count<sizeofresults;count++)
				{
					    result += vFoundWords[count]->pLine->data;
						string sLineNumber =  intToString(vFoundWords[count]->pLine->linenumber);
						result += "[";
						result += sLineNumber;
						result += "]";
						result += "\n";
						result += vFoundWords[count]->pLine->filename;
						result += "\n";
				}
			}
		}
		else if((token[0]=="HELP")||(token[0]=="H"))
		{
			result = "XYZ_DATABASE Commands:\n";
			result += "--------------------------\n";
			result += "HELP(H)\n";
			result += "ADD_FILE(A)Filename\n";
			result += "FIND_WORD(F)\n";
			result += "CLEAR(C)\n";
			result += "QUIT(Q)\n";
		}
		else
		{
			result="Command not recognized.";
		}
		return result;
	}
	catch(int e)
	{
		string result;
		e=1;
		/*if(e==98)
		{
			result = "Exception: Queue underflow";
			return result;
		}
		else if(e==99)
		{
			result = "Exception: Memory allocation failure in Queue";
			return result;
		}*/
		return result;
	}
	catch(...)
	{
		string result = "Unknown Exception. Call Lofton Bullard at 561-297-3000";
		return result;
	}
}
