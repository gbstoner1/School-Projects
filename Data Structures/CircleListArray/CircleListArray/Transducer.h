
//Transducer.h
//Geoffrey Stoner COP3530
//Circle List HW -- Pointers

#pragma once

#include <string>
#include "game.h"
using namespace std;




class Transducer
{
public:
	string transduce(string command);
private:
	//Add main functional object here 
	Game game;
	Game firstgame;
};