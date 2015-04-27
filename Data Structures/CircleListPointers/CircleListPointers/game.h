//game.h
//Geoffrey Stoner COP3530
//Circle List HW -- Pointers


#include <iostream>
using namespace std;


class player
{

private:
	string name;
	player * pNext;
	friend class CircleList;
	friend class Game;
};

class CircleList
{
public:
	CircleList() {pHead = NULL;}
	~CircleList()
	{
		clearList();
		/*if (pHead)
		{
			player * pTemp = pHead;
			while (pTemp->pNext != pHead)
			{
				player * pCurrent = pTemp;
				pTemp = pTemp->pNext;
				delete(pCurrent);
			}
		}
		pHead = NULL;*/
	}
	void clearList()
	{
		if (pHead)
		{
			player * pTemp = pHead;
			while (pTemp->pNext != pHead)
			{
				player * pCurrent = pTemp;
				pTemp = pTemp->pNext;
				delete(pCurrent);
			}
		}
		pHead = NULL;
	}
	void addplayer(string s)
	{

		player * pNewNode = new player;
		//player * pTemp = new player;
		//pTemp=pHead;
		if (!pNewNode) // pnewnode = null;
		{
			//out of memory?
		}
		else
		{
			if (isEmpty())
			{
				(*pNewNode).name = s;
				pHead = pNewNode;
				pNewNode->pNext = pNewNode;
			}
			else
			{
				pNewNode->name = s;
				pNewNode->pNext = pHead->pNext;
				pHead->pNext = pNewNode;
				pHead = pNewNode;
				return;
			}
		} // else
	}
	string removeplayer(string s)
	{
		if (isEmpty())
		{
			throw(98);
		}
		string result;
		player * pTemp = pHead;
		player * pCurrent = NULL;
		while (pTemp->pNext != pHead)
		{
			if (pTemp->name == s) break;
			pCurrent = pTemp;
			pTemp = pTemp->pNext;
		}
		if (pTemp == pHead)
		{
			result = pTemp->name;
			while (pTemp->pNext != pHead)
			{
				pTemp = pTemp->pNext;
			}
			pTemp->pNext = pHead->pNext;
			delete pHead;
			pHead = pTemp->pNext;
		}
		else
		{
			result = pTemp->name;
			pCurrent->pNext = pTemp->pNext;
			delete pTemp;
		}

		return result;
	}
	bool isEmpty() { return pHead == NULL; };
	int count()
	{
		int result = 0;
		player * temp = new player;
		temp = pHead;
		if (pHead == NULL)
		{
			return 0;
			// Empty
		}
		else
		{
			result = 1;
			while (temp->pNext != pHead)
			{
				temp = temp->pNext;
				result++;
			}

		}
		return result;
	}
	friend class Game;
	player * pHead;
private:
//Maybe a struct instead of a class?
};

class Game
{

public:
	int maxplayers;
	string play()
	{
		string result;
		player * pTemp = new player;
		pTemp = listofplayers.pHead;
		while (pTemp->pNext != listofplayers.pHead)
		{
			pTemp = pTemp->pNext;

		}
		result = pTemp->pNext->name;
		listofplayers.pHead = pTemp;
		return result;

	}
	string playround();
	CircleList listofplayers;

};







