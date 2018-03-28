#pragma once
#include <iostream>
#include <string.h>

using namespace std;

////////////////////////////////////////////////////////////
//File Name : Node.h					  //
//Date : 2015. 12. 04	                  		  //
//Compiler : g++ 4.8.4                                    //
//Os : ubuntu 14.04.3                                     //
//Author : Hyeon A Park                                   //
//Student ID : 2014722030                                 //
//--------------------------------------------------------//
//ver : 1.0.0                                             //
//Description : Node has many data to deal in program.	  //
//Etc.. : Data Structure Assignment #3                    //
////////////////////////////////////////////////////////////
class Node
{
private:
	char vertex;
	int Bandwidth; 
	int Cost;
	int Remain_Band; //remain bandwidth after allocating
	int index;
	char path[26]; //shortest path that sart vertex is vertex

	Node * pDown; //down pointer
	Node * pRight; //right pointer
public:
	Node(void);
	~Node(void);

	void set_vertex(char v);
	char get_vertex();

	void set_bandwidth(int b);
	int get_bandwidth();

	void set_cost(int c);
	int get_cost();

	void set_Remain_Band(int ub);
	int get_Remain_Band();

	void set_index(int i);
	int get_index();

	void set_path(char * p);
	char * get_path();

	void set_pDown(Node * d);
	Node * get_pDown();

	void set_pRight(Node * r);
	Node * get_pRight();
};

