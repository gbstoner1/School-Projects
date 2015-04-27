//Transducer.cpp
//Geoffrey Stoner COP3530
//Circle List HW -- Pointers

#include "Transducer.h"
#include <vector>
#include "misc.h"
using namespace std;
const int maxplayers = 19;


//ADD This is a string.

string Transducer::transduce(string command)
{
	string result;
	vector<string> token = tokenize(command);
	if((token[0]=="HELP")||(token[0]=="H"))
	{
		result="Commands:\n";
		result+="-------------------\n";
		result+="\tHELP(H)\n";
		result += "\tADD(A) <Player Name>\n";
		result += "\tREMOVE(R) <Player Name\n";
		result += "\tPLAY(P)\n";
		result += "\tPLAYROUND(L)\n";
		result += "\tCLEAR(CLR)\n";
		result+="\tQUIT(Q)\n";
	}
	else if((token[0]=="ADD")||(token[0]=="A"))
	{
		if (firstgame.listofplayers.count() < maxplayers)
		{
			firstgame.listofplayers.addplayer(token[1]);
			result = token[1] + " has been added to the Queue.";
		}
		else
		{
			result = "Max Players are already playing \n";
		}
	}

	else if ((token[0] == "REMOVE") || (token[0] == "R"))
	{
		string s = firstgame.listofplayers.removeplayer(token[1]);
		result = s + " has been removed from the Queue.";
	}
	else if ((token[0] == "COUNT") || (token[0] == "C"))
	{
		int n = firstgame.listofplayers.count();
		result = intToString(n) + " items are in the Queue.";
	}
	else if ((token[0] == "PLAY") || (token[0] == "P"))
	{
		string s = firstgame.play();
		result = s + " has taken a turn.";
	}
	else if ((token[0] == "PLAYROUND") || (token[0] == "L"))
	{
		int n = firstgame.listofplayers.count();
		for (int i = 0; i<n; i++)
		{
			string s = firstgame.play();
			result = s + " has taken a turn. \n" ;
		}
	}
	else if ((token[0] == "CLEAR") || (token[0] == "CLR"))
	{
		CircleList Clear();
		result = "Player list is empty";
	}
	
	else if ((token[0] == "QUIT") || (token[0] == "Q"))
	{
		result = "Goodbye.";
	}
	else
	{
		result="Unrecognized Command!!!";
	}
	return result;
}
