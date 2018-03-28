#pragma once
#include "Node.h"
#include "AdjacentList.h"
#include <fstream>

////////////////////////////////////////////////////////////
//File Name : Dijkstra.h				  //
//Date : 2015. 12. 04	                  		  //
//Compiler : g++ 4.8.4                                    //
//Os : ubuntu 14.04.3                                     //
//Author : Hyeon A Park                                   //
//Student ID : 2014722030                                 //
//--------------------------------------------------------//
//ver : 1.0.0                                             //
//Description : Design Dijkstra algorithm to know the	  //
//		shortest pathes about vertexes.		  //
//Etc.. : Data Structure Assignment #3                    //
////////////////////////////////////////////////////////////
class Dijkstra
{
private:
	char ** Shortest; //Have all of shortest path that program got
	int * dist; //To know shortest distance from one vertex to another vertex
	int length; //number of vertex
	bool * visit; //To know whetehr I visita a Node
	AdjacentList * Ad_list; //To use Adjacent list in this class
	ofstream output; //output file stream

public:
	Dijkstra(int len);
	~Dijkstra(void);

	void set_list(AdjacentList * list); //get adjacent list address 
	void MakeArray(); //Allocate memory address to Shortest
	int ShortestPath(char start); //Get shortest path from start to the other vertexes
	Node * Search(int index1, int index2); //search a Node to get shortest path
	int Select(int len); //select shortest path among the values of dist
	char * VertexArray(); //make array that has information of index number about each vertex
	char * ShortestWay(char start, char dest); //return Shortest way according to start vertex and dest vertex
	char * Confirm_band(char start, char dest, int use); //Confirm the bandwidth is adquate
	bool Bandwidth_Allocation(char start, char dest, int use); //Allocate bandwidth
	void Print(char start); //Print path about start vertex
	char * Linkfail(char start, char dest); //Linke fail
};

