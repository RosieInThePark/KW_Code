#include "Node.h"


Node::Node(void)
{
	vertex = NULL;
	Bandwidth = 0;
	Remain_Band = 0;
	Cost = 0;
	index = -1;
	pDown = NULL;
	pRight = NULL;
	memset(path,NULL,26);
}
////////////////////////////////////////////
//TMatrix :: set_vertex			  //
//========================================//
//Input : char -> vertex		  //
//Output : void				  //
//Purpose : set vertex			  //
////////////////////////////////////////////
void Node::set_vertex(char v) {vertex = v;}
////////////////////////////////////////////
//TMatrix :: get_vertex			  //
//========================================//
//Input : void				  //
//Output : char -> vertex		  //
//Purpose : get vertex			  //
////////////////////////////////////////////
char Node::get_vertex() {return vertex;}

////////////////////////////////////////////
//TMatrix :: set_bandwidth		  //
//========================================//
//Input : int -> bandwidth		  //
//Output : void				  //
//Purpose : set bandwidth and remain band //
////////////////////////////////////////////
void Node::set_bandwidth(int b) {Bandwidth = b;Remain_Band = b;}
////////////////////////////////////////////
//TMatrix :: get_bandwidth		  //
//========================================//
//Input : void				  //
//Output : int -> bandwidth		  //
//Purpose : get bandwidth		  //
////////////////////////////////////////////
int Node::get_bandwidth() {return Bandwidth;}

////////////////////////////////////////////
//TMatrix :: set_cost			  //
//========================================//
//Input : int -> cost			  //
//Output : void				  //
//Purpose : set cost			  //
////////////////////////////////////////////
void Node::set_cost(int c) {Cost = c;}
////////////////////////////////////////////
//TMatrix :: get_cost			  //
//========================================//
//Input : void				  //
//Output : int -> cost			  //
//Purpose : get cost			  //
////////////////////////////////////////////
int Node::get_cost() {return Cost;}

////////////////////////////////////////////
//TMatrix :: set_Remain_Band		  //
//========================================//
//Input : int -> allocated bandwidth	  //
//Output : void				  //
//Purpose : subtract allocated bandwidth  //
////////////////////////////////////////////
void Node::set_Remain_Band(int ub) {Remain_Band -= ub;}
////////////////////////////////////////////
//TMatrix :: get_Remain_Band		  //
//========================================//
//Input : void				  //
//Output : int -> Remain bandwidth	  //
//Purpose : get remain bandwidth	  //
////////////////////////////////////////////
int Node::get_Remain_Band() {return Remain_Band;}

////////////////////////////////////////////
//TMatrix :: set_index			  //
//========================================//
//Input : int -> index			  //
//Output : void				  //
//Purpose : set index			  //
////////////////////////////////////////////
void Node::set_index(int i) {index = i;}
////////////////////////////////////////////
//TMatrix :: get_index			  //
//========================================//
//Input : void				  //
//Output : int -> index			  //
//Purpose : get index			  //
////////////////////////////////////////////
int Node::get_index() {return index;}

////////////////////////////////////////////
//TMatrix :: set_path			  //
//========================================//
//Input : char * -> shortest path	  //
//Output : void				  //
//Purpose : save shortest path in Node    //
////////////////////////////////////////////
void Node::set_path(char * p) {strcpy(path, p);}
////////////////////////////////////////////
//TMatrix :: get_path			  //
//========================================//
//Input : void				  //
//Output : char * -> shortest path	  //
//Purpose : get shortest path easily	  //
////////////////////////////////////////////
char * Node::get_path() {return path;}

////////////////////////////////////////////
//TMatrix :: set_pDown			  //
//========================================//
//Input : Node * -> address of Node	  //
//Output : void				  //
//Purpose : set down pointer		  //
////////////////////////////////////////////
void Node::set_pDown(Node * d) {pDown = d;}
////////////////////////////////////////////
//TMatrix :: get_pDown			  //
//========================================//
//Input : void				  //
//Output : Node * -> address of Node	  //
//Purpose : get down pointer		  //
////////////////////////////////////////////
Node * Node::get_pDown() {return pDown;}

////////////////////////////////////////////
//TMatrix :: set_pRight			  //
//========================================//
//Input : Node * r -> address of Node	  //
//Output : void				  //
//Purpose : set right pointer		  //
////////////////////////////////////////////
void Node::set_pRight(Node * r) {pRight = r;}
////////////////////////////////////////////
//TMatrix :: get_pRight			  //
//========================================//
//Input : void				  //
//Output : Node * -> address of Node	  //
//Purpose : get right pointer		  //
////////////////////////////////////////////
Node * Node::get_pRight() {return pRight;}

Node::~Node(void)
{
}
