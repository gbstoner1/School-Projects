//game.h
//Geoffrey Stoner COP3530
//Circle List HW -- Pointers


//#include <iostream>
using namespace std;


class player
{

	private:
		string name;
		friend class CircleList;
		friend class Game;
};

class CircleList
{
	public:
		CircleList() 
		{
			turn = 0;
			maxsize = 20;
			myArray = new player[maxsize];
			for (int i = 0; i<maxsize; i++)
			{
				myArray[i].name = "null";
			}

		}
		~CircleList(){ delete[] myArray; };
	
		void addplayer(string s)
		{
			if (turn>0)
			{
				int i, counter;
				counter = count() + 1;
				player * mytemparray;
				mytemparray = new player[maxsize];
				for (i = 0; i<count(); i++)
				{
					mytemparray[i].name = myArray[i].name;
				}
				i = turn;
				while (i != counter)
				{
					myArray[i].name = mytemparray[i - 1].name;
					i++;
				}
				delete[] mytemparray;
				myArray[turn].name = s;
				turn = turn + 1;
			}
			else
			{
				myArray[count()].name = s;
			}
		}
		void Clear()
		{
			delete[] myArray;
		}
		string removeplayer(string s)
		{
			int i, j;
			for (i = 0; i<count(); i++)
			{
				if (myArray[i].name == s)
				{
					for (j = i; j <= count(); j++)
					{
						myArray[j].name = myArray[j + 1].name;

					}
					myArray[j + 1].name = "null";
					turn = count();
				}
			}
			return s;

		}
		int count()
		{
			int i = 0;
			while (myArray[i].name != "null")
			{
				i++;
			}
			return i;
		}
		friend class Game;
	 
	private:
		player * myArray;
		int maxsize;
		int turn;
};

class Game
{
	public:
		
		string play()
		{
			string result;
			if (listofplayers.turn == 0)
			{
				listofplayers.turn = listofplayers.count();
			}
			listofplayers.turn = listofplayers.turn - 1;
			result = listofplayers.myArray[listofplayers.turn].name;
			
			
			return result;
		}

		CircleList listofplayers;

};







