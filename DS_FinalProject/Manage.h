#pragma once
#include <iostream>
#include <fstream>
#include "Node.h"
#include "AdjacentList.h"
#include "Dijkstra.h"
#include <string.h>
#include <stdlib.h>

using namespace std;

////////////////////////////////////////////////////////////
//File Name : Manage.h					  //
//Date : 2015. 12. 04	                  		  //
//Compiler : g++ 4.8.4                                    //
//Os : ubuntu 14.04.3                                     //
//Author : Hyeon A Park                                   //
//Student ID : 2014722030                                 //
//--------------------------------------------------------//
//ver : 1.0.0                                             //
//Description : Act like main function.			  //
//Etc.. : Data Structure Assignment #3                    //
////////////////////////////////////////////////////////////
class Manage
{
private:
	ifstream router_in;
	ifstream event_list;
	ofstream output;

	AdjacentList * Adj_list;
	Dijkstra * Di_list;

	Node * D_que; //Deferred queue
	Node * A_que; //Alocated queue
public:
	Manage(void);
	~Manage(void);

	int DoMain();

	void Defer_Queue(Node * p); //insert deferred request 
	void Allocate_Queue(Node * p); //insert allocated request
	Node * Delete_D(int index); //get a request from D que
	Node * Delete_A(int index); //get a request from A que
	Node * Pop_D(); //pop
	bool Realloc(char start, char dest, Node * pCur); //realloc bandwidth
};

