#pragma once
#include "Node.h"
#include <limits.h>

////////////////////////////////////////////////////////////
//File Name : AdjacentList.h				  //
//Date : 2015. 12. 04	                  		  //
//Compiler : g++ 4.8.4                                    //
//Os : ubuntu 14.04.3                                     //
//Author : Hyeon A Park                                   //
//Student ID : 2014722030                                 //
//--------------------------------------------------------//
//ver : 1.0.0                                             //
//Description : This class is to make Adjacent List.	  //
//Etc.. : Data Structure Assignment #3                    //
////////////////////////////////////////////////////////////
class AdjacentList
{
private:
	Node * Ad_head; //header of Adjacent list
	int number_of_v; //number of vertex in list
public:
	AdjacentList(void);
	~AdjacentList(void);

	void Insert(char id1, char id2, int band, int cost); //make Adjacent list
	void Get_Index(); //get index of vertexes
	int get_Num_v(); //return number of vertexes
	Node * get_Ad_head(); //return header of adjacent list
	void Revise(char start, char dest); //revise adjacent list if link fail is broken
};
