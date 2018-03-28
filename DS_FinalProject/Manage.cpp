#include "Manage.h"


Manage::Manage(void)
{
	Adj_list = new AdjacentList;

	D_que = NULL;
	A_que = NULL;
}
/////////////////////////////////////////////////////
//TMatrix :: DoMain				   //
//=================================================//
//Input : void					   //
//Output : int -> 1 successm, 0 fail		   //
//Purpose : Act like main function		   //
///////////////////////////////////////////////////// 
int Manage::DoMain() {
	router_in.open("router.in");
	char string[100] = {NULL, };

	if(!router_in.is_open()) {
		cout << "Router File Open Error !!" << endl;
		return 1;
	}

	while(!router_in.eof()) { //Make Adjacent list by using router information
		router_in.getline(string, 100);
		if(string[0]==NULL) continue;

		char * token = strtok(string, " \t");
		char ID1 = token[0];
		token = strtok(NULL, " \t");
		char ID2 = token[0];
		token = strtok(NULL, " \t");
		int band = atoi(token);
		token = strtok(NULL, " \t");
		int cost = atoi(token);

		Adj_list->Insert(ID1,ID2,band,cost);
		Adj_list->Insert(ID2,ID1,band,cost);
	}
	router_in.close();

//////////////////////////////////////////////////////////////////////////////////////////////////////////

	Adj_list->Get_Index();
	Di_list = new Dijkstra(Adj_list->get_Num_v());
	Di_list->set_list(Adj_list);
	event_list.open("event.in");

	if(!event_list.is_open()) {
		cout << "Event File Open Error !!" << endl;
		return 1;
	}
	while(!event_list.eof()) {
		event_list.getline(string, 100); //get an event list
		if(string[0]==NULL) continue;

		output.open("result.out", std::ios_base::app);
		output << string << endl;
		output.close();

		char * token = strtok(string, " \t"); //token has operation

		if(strcmp(token, "request")==0) { //REQUEST

			token = strtok(NULL, " \t");
			int index = atoi(token); //number of request
			token = strtok(NULL, " \t");
			char start = token[0]; //start vertex
			token = strtok(NULL, " \t");
			char dest = token[0]; //dest vertex
			Di_list->ShortestPath(start);
			token = strtok(NULL, " \t");
			int band = atoi(token); //bandwidth 

			Node * from = new Node;
			Node * to = new Node;
			char s[26] = {NULL, };
			from->set_index(index);
			from->set_vertex(start);
			to->set_vertex(dest);
			to->set_bandwidth(band);
			from->set_pRight(to);

			Di_list->ShortestPath(start); //get Shortest path about start
			Di_list->Print(start); //Print Shortest path about start

			output.open("result.out", std::ios_base::app);
			output << "ALLOCATE ACCORDING TO REQUST " << index << " : " << band << "   ";
			output.close();

			bool success = Di_list->Bandwidth_Allocation(start, dest, band); //allocate bandwidth
			strcpy(s,Di_list->ShortestWay(start,dest));
			from->set_path(s); //set shortest way into Node

			if(success==true) { //if success to allocate
				output.open("result.out", std::ios_base::app);
				output << "                  SUCCESS!!!!!!!" << endl;
				output.close();

				Allocate_Queue(from); //insert 'from' Node to A que
			}
			else if(success==false) { //if not success to allocate
				output.open("result.out", std::ios_base::app);
				output << "                     FALSE!!!!!!!" << endl;
				output.close();

				Defer_Queue(from); //insert 'from' Node to D que
			}

		}
		else if(strcmp(token, "linkfail")==0) { //LINKFAIL
			token = strtok(NULL, " \t");
			char start = token[0]; //start vertex
			token = strtok(NULL, " \t");
			char dest = token[0]; //dest vertex

			char starter[26] = {NULL, };
			strcpy(starter, Di_list->Linkfail(start, dest)); //get path that has linke fail path
			int len = strlen(starter);

			output.open("result.out", std::ios_base::app);
			output << "<<REALLOCATE>>" << endl;
			output.close();

			Adj_list->Revise(start, dest); //revise adjacent list

			Node * pCur = A_que;
			Node * pre = NULL;
			while(pCur) {
				for(int i=0;i<len;i++) {
					if(pCur->get_vertex()==starter[i]) { //find start vertex
						Node * right = pCur->get_pRight();
						char temp[26] = {NULL, };
						strcpy(temp, pCur->get_path());
						int a = strlen(temp);
						bool sel = false;

						for(int j=0;j<a;j++) {
							if(temp[j]==start && temp[j+1]==dest) { //if link fail path exist in shortest path
								Di_list->Bandwidth_Allocation(pCur->get_vertex(), right->get_vertex(), (-1)*(right->get_bandwidth())); //return allocated bandwidth
								sel = Realloc(start, dest,pCur); //reallocate

								if(sel==true) { //success to reallocate
									output.open("result.out", std::ios_base::app);
									output << "   SUCCESS" << endl;
									output.close();
								}
								else if(sel==false) { //fail to reallocate
									if(pCur==A_que) { //if fail request is header of A que
										A_que = pCur->get_pDown(); //change header
										pCur->set_pDown(NULL);
										Defer_Queue(pCur); //insert pCur to D que
										pCur = A_que; 

										output.open("result.out", std::ios_base::app);
										output << "     FALSE" << endl;
										output.close();
									}
									else {
										pre->set_pDown(pCur->get_pDown());
										pCur->set_pDown(NULL);
										Defer_Queue(pCur); //insert pCur to D que
										pCur = pre;

										output.open("result.out", std::ios_base::app);
										output << "    FALSE" << endl;
										output.close();
									}
								}
								break;
							}
							else if(temp[j]==dest && temp[j+1]==start) { //if link fail path exist in shortest path
								Di_list->Bandwidth_Allocation(pCur->get_vertex(), right->get_vertex(), (-1)*(right->get_bandwidth())); //return allocated bandwidth
								sel = Realloc(start, dest,pCur);//reallocate

								if(sel==true) { //success to reallocate
									output.open("result.out", std::ios_base::app);
									output << "   SUCCESS!!!" << endl;
									output.close();
								}
								else if(sel==false) { //fail to reallocate
									if(pCur==A_que) { //if fail request is header of A que
										A_que = pCur->get_pDown(); //change header
										pCur->set_pDown(NULL);
										Defer_Queue(pCur); //insert pCur to D que
										pCur = A_que; 

										output.open("result.out", std::ios_base::app);
										output << "     FALSE" << endl;
										output.close();
									}
									else {
										pre->set_pDown(pCur->get_pDown());
										pCur->set_pDown(NULL);
										Defer_Queue(pCur); //insert pCur to D que
										pCur = pre;

										output.open("result.out", std::ios_base::app);
										output << "    FALSE" << endl;
										output.close();
									}
								}
								break;
							}
						}
						break;
					}
				}
				pre = pCur;
				pCur=pCur->get_pDown();
			}
		}
		else if(strcmp(token, "eos")==0) { //EOS
			token = strtok(NULL, " \t");
			int index = atoi(token); //number of request

			Node * pCur = Delete_A(index); //take out a request from A que
			if(pCur==NULL) { //that request not exist in A
				Node * qCur = Delete_D(index); //take out a request from D que

				if(qCur==NULL) { //also not exist in D que
					output.open("result.out", std::ios_base::app);
					output << "REQUEST " << index << " NOT EXIST" << endl;
					output.close();
				}
				else if(qCur!=NULL) { //exist in D que
					delete qCur->get_pRight(); 
					delete qCur; //delete from que
				}
			}
			else { //request exist in A
				Di_list->Bandwidth_Allocation(pCur->get_vertex(), pCur->get_pRight()->get_vertex(), (-1) * (pCur->get_pRight()->get_bandwidth())); //return bandwidth
				delete pCur->get_pRight();
				delete pCur;
				//delete from que

				Node * rCur = NULL;
				Node * temp = NULL;
				Node * last = NULL;
				bool confirm = false;

				while(1) { //try to reallocate about D que
					rCur = Pop_D();
					Di_list->ShortestPath(rCur->get_vertex()); //get shortest path
					Node * right = rCur->get_pRight();
					confirm = Di_list->Bandwidth_Allocation(rCur->get_vertex(),right->get_vertex(), right->get_bandwidth()); //allocate

					if(confirm==true) { //success to reallocate
						output.open("result.out", std::ios_base::app);
						output << "   REALLOCATE SUCCESS!!!!!!!" << endl;
						output.close();

						Allocate_Queue(rCur);
					}
					else if(confirm==false) { //fail to reallocate
						output.open("result.out", std::ios_base::app);
						output << "    REALLOCATE FALSE!!!!!!" << endl;
						output.close();
						if(temp==NULL)  {
							temp = rCur;
							last = temp;
						}
						else  {
							last->set_pDown(rCur);
							last = rCur;
						}
					}

					if(D_que==NULL) {
						D_que = temp;
						break;
					}
				}
			}
		}
		else if(strcmp(token, "end")==0) {
			output.open("result.out", std::ios_base::app);
			output << "<<<<<<<<<END EVENT LIST>>>>>>>>>>" << endl;
			output.close();
		}
		else {
			output.open("result.out", std::ios_base::app);
			output << "WRONG OPERATION" << endl;
			output.close();
		}
	}
	output.close();
	event_list.close();
	return 0;
}
/////////////////////////////////////////////////////
//TMatrix :: Defer_Queue			   //
//=================================================//
//Input : Node * -> deferred request		   //
//Output : void					   //
//Purpose : Make deferred queue			   //
///////////////////////////////////////////////////// 
void Manage::Defer_Queue(Node * p) {
	if(D_que==NULL) { //D que not exist
		D_que = p;
	}
	else {
		Node * pCur = D_que;
		Node * pre = NULL;

		while(pCur) {
			if(pCur->get_index()>p->get_index()) { //p is inserted between pCur and pre
				if(pCur==D_que) { //if pCur is header of D que
					p->set_pDown(pCur);
					D_que = p;
					break;
				}
				else {
					pre->set_pDown(p);
					p->set_pDown(pCur);
					break;
				}
			}
			else {
				pre = pCur;
				pCur = pCur->get_pDown();
			}
		}
		if(pCur==NULL) { //p is inserted last of the que
			pre->set_pDown(p);
		}
	}
}
/////////////////////////////////////////////////////
//TMatrix :: Allocate_Queue			   //
//=================================================//
//Input : Node * -> allocated request		   //
//Output : void					   //
//Purpose : Make allocated queue		   //
///////////////////////////////////////////////////// 
void Manage::Allocate_Queue(Node * p) {
	if(A_que==NULL) { //A que not exist
		A_que = p;
	}
	else {
		Node * pCur = A_que;
		Node * pre = NULL;

		while(pCur) {
			if(pCur->get_index()>p->get_index()) { //p is inserted between pCur and pre
				if(pCur==A_que) { //if pCur is header of A que
					p->set_pDown(pCur);
					A_que = p;
					break;
				}
				else {
					pre->set_pDown(p);
					p->set_pDown(pCur);
					break;
				}
			}
			else {
				pre = pCur;
				pCur = pCur->get_pDown();
			}
		}
		if(pCur==NULL) { //p is inserted the last of A que
			pre->set_pDown(p);
		}
	}
}
/////////////////////////////////////////////////////
//TMatrix :: Delete_D				   //
//=================================================//
//Input : int -> index to delete		   //
//Output : Node * -> find Node to delete from que  //
//Purpose : Delete a Node not Pop		   //
/////////////////////////////////////////////////////
Node * Manage::Delete_D(int index) {
	Node * pCur = D_que;
	Node * pre = NULL;

	while(pCur) {
		if(pCur->get_index()==index) { //find a node
			if(pCur==D_que) {//if header
				D_que = pCur->get_pDown();
				pCur->set_pDown(NULL);
			}
			else {
				pre->set_pDown(pCur->get_pDown());
				pCur->set_pDown(NULL);
			}
			return pCur;
		}
		else {
			pre = pCur;
			pCur = pCur->get_pDown();
		}
	}

	return pCur;
}
/////////////////////////////////////////////////////
//TMatrix :: Delete_A				   //
//=================================================//
//Input : int -> index to delete from A que        //
//Output : Node * -> to delete from que		   //
//Purpose : Delete a Node from que not pop	   //
/////////////////////////////////////////////////////
Node * Manage::Delete_A(int index) {
	Node * pCur = A_que;
	Node * pre = NULL;

	while(pCur) {
		if(pCur->get_index()==index) { //find a node
			if(pCur==A_que) { //if header
				A_que = pCur->get_pDown();
				pCur->set_pDown(NULL);
			}
			else {
				pre->set_pDown(pCur->get_pDown());
				pCur->set_pDown(NULL);
			}
			return pCur;
		}
		else {
			pre = pCur;
			pCur = pCur->get_pDown();
		}
	}

	return pCur;
}
/////////////////////////////////////////////////////
//TMatrix :: Pop_D				   //
//=================================================//
//Input : void					   //
//Output : Node * -> node to pop		   //
//Purpose : Pop a node from D que		   //
/////////////////////////////////////////////////////
Node * Manage::Pop_D() {
	Node * pCur = D_que;

	D_que = pCur->get_pDown();
	pCur->set_pDown(NULL);

	return pCur; //pop
}
/////////////////////////////////////////////////////
//TMatrix :: Realloc				   //
//=================================================//
//Input : char, char -> vertex of start and dest   //
//Output : bool -> true, false 			   //
//Purpose : Reallocate when link fail occurs	   //
/////////////////////////////////////////////////////
bool Manage::Realloc(char start, char dest, Node * pCur) {
	Node * qCur = Adj_list->get_Ad_head();

	Di_list->ShortestPath(pCur->get_vertex()); //get Shortest path

	Node * right = pCur->get_pRight();

	output.open("result.out", std::ios_base::app);
	output << "REQUEST " << pCur->get_index() << " : ";
	output << pCur->get_vertex() << "    " << right->get_vertex() << "    " << right->get_bandwidth() << endl;
	output.close();

	Di_list->Print(pCur->get_vertex()); //Print newly got Shortest path

	output.open("result.out", std::ios_base::app);
	output << "ALLOCATE ACCORDING TO REQUST " << pCur->get_index() << " : ";
	output.close();

	bool k = Di_list->Bandwidth_Allocation(pCur->get_vertex(),right->get_vertex(),right->get_bandwidth()); //
	//Allocate Band width about new path

	return k;
}
Manage::~Manage(void)
{
}
