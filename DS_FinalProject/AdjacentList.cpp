#include "AdjacentList.h"


AdjacentList::AdjacentList(void)
{
	Ad_head = NULL;
	number_of_v = 0;
}
/////////////////////////////////////////////////////
//TMatrix :: Insert				   //
//=================================================//
//Input : char, char -> from and to vertex	   //
//        int -> bandwidth, int -> cost		   //
//Output : void					   //
//Purpose : Make adjacent list.			   //
///////////////////////////////////////////////////// 
void AdjacentList::Insert(char id1, char id2, int band, int cost) {
	Node * pCur = Ad_head;
	Node * pPre = NULL;
	Node * rCur = NULL;
	Node * rPre = NULL;
	if(pCur==NULL) { //if Adjacent list doesn't exist
		Node * st = new Node;
		st->set_vertex(id1);

		Node * de = new Node;
		de->set_vertex(id2);
		de->set_bandwidth(band);
		de->set_cost(cost);

		st->set_pRight(de);
		Ad_head = st; //set head to st
	}
	else { //Adjacent list exists
		while(pCur) {
			if(pCur->get_vertex()==id1){ //same start vertex node exists.
				rCur = pCur->get_pRight();
				rPre = pCur;
				while(rCur) {
					if(rCur->get_vertex()>id2) { //same destination vertex doesn't exist
						//case of inserting destination vertex in the middle of right list of pCur
						Node * de = new Node;
						de->set_vertex(id2);
						de->set_cost(cost);
						de->set_bandwidth(band);
						pPre->set_pRight(de);
						de->set_pRight(pCur);

						break;
					}
					else if(rCur->get_vertex() < id2){ //There is the possibility that same vertex2 can exist.
						rPre = rCur;
						rCur= rCur->get_pRight();
					}
					else break;//this case is that same vertex2 also exists. So wrong input of router.
				}
				if(rCur==NULL) { //vertex2 is inserted in the last of right list of pCur
					Node * de = new Node;
					de->set_vertex(id2);
					de->set_cost(cost);
					de->set_bandwidth(band);

					rPre->set_pRight(de);
				}
				break;
			}
			else if(pCur->get_vertex() > id1) { //It means same start vertex node doesn't exist
				//case of inserting start vertex node in the middle of list
				Node * st = new Node;
				Node * de = new Node;
				st->set_vertex(id1);
				de->set_vertex(id2);
				de->set_cost(cost);
				de->set_bandwidth(band);

				st->set_pRight(de);
				pPre->set_pDown(st);
				st->set_pDown(pCur);
				break;
			}
			else { //pCur->get_vertex() < vertex2
				pPre = pCur;
				pCur = pCur->get_pDown();
			}
		}
		if(pCur==NULL) { //case of inserting start vertex in the last of list
			Node * st = new Node;
			Node * de = new Node;

			st->set_vertex(id1);

			de->set_vertex(id2);
			de->set_cost(cost);
			de->set_bandwidth(band);

			st->set_pRight(de);
			pPre->set_pDown(st);
		}
	}
}
/////////////////////////////////////////////////////
//TMatrix :: Get_Index				   //
//=================================================//
//Input : void					   //
//Output : void					   //
//Purpose : Assign index to each vertex.	   //
///////////////////////////////////////////////////// 
void AdjacentList::Get_Index() {
	Node * pCur = Ad_head;
	int index = 0;

	while(pCur) {
		pCur->set_index(index);

		index++;
		pCur = pCur->get_pDown(); //assign index to 'from' vertexes
	}
	number_of_v = index; //result number of index is same with number of vertexes
	
	//To set index of 'to' vertexes
	char * arr = new char [number_of_v];
	pCur = Ad_head;

	for(int i=0;i<number_of_v;i++) { //arr is used to know index according to vertex
		arr[i] = pCur->get_vertex();
		pCur = pCur->get_pDown();
	}

	pCur = Ad_head;
	Node * qCur = NULL;
	while(pCur) { //assign index to 'from' vertex
		qCur = pCur->get_pRight();
		for(int i=0;i<number_of_v;i++) {
			if(qCur->get_vertex()==arr[i]) {
				qCur->set_index(i);
				qCur = qCur->get_pRight();
			}
			if(qCur==NULL) break;
		}
		pCur = pCur->get_pDown();
	}
}
/////////////////////////////////////////////////////
//TMatrix :: get_Num_v				   //
//=================================================//
//Input : void					   //
//Output : int -> number of vertexes 		   //
//Purpose : To use number in other class.	   //
///////////////////////////////////////////////////// 
int AdjacentList::get_Num_v() {return number_of_v;}

/////////////////////////////////////////////////////
//TMatrix :: get_Ad_head			   //
//=================================================//
//Input : void					   //
//Output : Node * -> header of list		   //
//Purpose : To use header of list in other class.  //
///////////////////////////////////////////////////// 
Node * AdjacentList::get_Ad_head() {return Ad_head;}

/////////////////////////////////////////////////////
//TMatrix :: Revise				   //
//=================================================//
//Input : char, char->start and destination vertex //
//Output : void					   //
//Purpose : Revise Adjacent list if Link fail occurs //
///////////////////////////////////////////////////// 
void AdjacentList::Revise(char start, char dest) {
	Node * pCur = Ad_head;

	//Adjacent list is the two side list. 
	//So if start is A and dest is B, fail the path of A-B, B-A
	while(pCur) { //for example, A-B
		if(pCur->get_vertex()==start) { //if vertex of pCur is same with start
			Node * qCur = pCur->get_pRight();
			while(qCur) { //find the Node that has same vertex with dest
				if(qCur->get_vertex()==dest) {
					qCur->set_cost(INT_MAX); //if found, set cost to MAX
					break;
				}
				else qCur = qCur->get_pRight();
			}
			break;
		}
		else pCur = pCur->get_pDown();
	}

	pCur = Ad_head;
	while(pCur) { //for example, B-A
		if(pCur->get_vertex()==dest) {//if vertex of pCur is same with dest
			Node * qCur = pCur->get_pRight();
			while(qCur) {//find the Node that has same vertex with start
				if(qCur->get_vertex()==start) {
					qCur->set_cost(INT_MAX); //if found, set cost to MAX
					break;
				}
				else qCur = qCur->get_pRight();
			}
			break;
		}
		else pCur = pCur->get_pDown();
	}
}
AdjacentList::~AdjacentList(void)
{
}
