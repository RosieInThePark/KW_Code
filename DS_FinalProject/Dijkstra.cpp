#include "Dijkstra.h"


Dijkstra::Dijkstra(int len)
{
	dist = new int[len];
	visit = new bool [len];

	Shortest = new char * [len];
	for(int i=0;i<len;i++) {
		Shortest[i] = new char [len];
		memset(Shortest[i], NULL, sizeof(char)*len);
	}
	length = len;
}
/////////////////////////////////////////////////////
//TMatrix :: MakeArray				   //
//=================================================//
//Input : void					   //
//Output : void					   //
//Purpose : Allocate memory address to Shortest	   //
///////////////////////////////////////////////////// 
void Dijkstra::MakeArray() {
	int length = Ad_list->get_Num_v(); //get number of vertex

	Shortest = new char * [length]; //allocate hieght
	for(int i=0;i<length;i++) { //allocate width
		Shortest[i] = new char [length];
	}
}
/////////////////////////////////////////////////////
//TMatrix :: set_list				   //
//=================================================//
//Input : AdjacentList * -> address of class	   //
//Output : void					   //
//Purpose : Get address of class to use list	   //
///////////////////////////////////////////////////// 
void Dijkstra::set_list(AdjacentList * list) {Ad_list = list;}

/////////////////////////////////////////////////////
//TMatrix :: ShortestPath			   //
//=================================================//
//Input : char -> start vertex			   //
//Output : int -> 0 is success, 1 is false	   //
//Purpose : Get Shortest path about start vertex   //
///////////////////////////////////////////////////// 
int Dijkstra::ShortestPath(char start) {
	Node * pCur = Ad_list->get_Ad_head();
	char * arr = VertexArray(); //save vertex array into arr

	memset(dist, INT_MAX, length);
	memset(visit, false, length);

	while(pCur) { //get an index of start vertex
		if(pCur->get_vertex()==start) break;
		else pCur = pCur->get_pDown();
	}
	if(pCur==NULL) return 1; //same vertex doesn't exist

	int index = pCur->get_index(); //save index of start into 'index'
	memset(Shortest[index], start, length); 

	Node * fNode = NULL;
	for(int i=0;i<length;i++) {
		fNode = Search(index, i); //Search a Node
		if(fNode==NULL) { //path deosn't exist
			dist[i] = INT_MAX;
			Shortest[index][i] = NULL;
		}
		else { //path existes
			dist[i] = fNode->get_cost();
			Shortest[index][i] = arr[index];
		}
	}
	dist[index] = 0; //distance from start to start
	visit[index] = true;

	for(int i=0;i<(length-2);i++) {
		int u = Select(length); //select shortest path in dist
		visit[u] = true; //then that path is visited

		for(int w = 0;w<length;w++) {
			if(visit[w] == false) { //if visit[w] vertex is not visited
				Node * s = Search(u,w); //Search whether there are a path from u to w
				if(s!=NULL) { //if exist
					int Short_path = s->get_cost();
					if(Short_path != INT_MAX && dist[u] + Short_path < dist[w]) { //if u + utow is smaller than dist[w]
						dist[w] = dist[u] + Short_path;
						Shortest[index][w] = arr[u];
					}
				}
			}
		}
	}
	return 0;
}
/////////////////////////////////////////////////////
//TMatrix :: Search				   //
//=================================================//
//Input : int, int -> index of from and to         //
//Output : Node * -> return 'to' Node		   //
//Purpose :  Search a path according to indexes    //
///////////////////////////////////////////////////// 
Node * Dijkstra::Search(int index1, int index2) {
	Node * pCur = Ad_list->get_Ad_head();

	while(pCur) {
		if(pCur->get_index()==index1) { //find start vertex
			Node * qCur = pCur;
			while(qCur) {
				if(qCur->get_index()==index2) return qCur; //find dest vertex
				else qCur = qCur->get_pRight();
			}
			break;
		}
		else pCur = pCur->get_pDown();
	}
	return NULL; //Not exist
}
/////////////////////////////////////////////////////
//TMatrix :: Select				   //
//=================================================//
//Input : int -> length of arr			   //
//Output : int -> Minimum path index		   //
//Purpose : To get minimum path index in dist array//
///////////////////////////////////////////////////// 
int Dijkstra::Select(int len) {
	int Cost_MIN = INT_MAX; //standard
	int Index_MIN =0;

	for(int i=0;i<len;i++) {
		if(Cost_MIN > dist[i] && visit[i]==false) { //if i vertex dist is smaller than standard 
							    //and not visited yet
			Cost_MIN = dist[i];
			Index_MIN = i;
		}
	}

	return Index_MIN;
}
/////////////////////////////////////////////////////
//TMatrix :: VertexArray			   //
//=================================================//
//Input : void					   //
//Output : char * -> array that has vertex	   //
//Purpose : To know index of vertex easily	   //
///////////////////////////////////////////////////// 
char * Dijkstra::VertexArray() {
	Node * pCur = Ad_list->get_Ad_head();
	char * arr = new char[Ad_list->get_Num_v()]; //Dynamic allocation
	int i = 0;

	while(pCur) { //set vertexes
		arr[i] = pCur->get_vertex();
		i++;
		pCur = pCur->get_pDown();
	}

	return arr;
}
/////////////////////////////////////////////////////
//TMatrix :: Confirm_band			   //
//=================================================//
//Input : char, char->vertex of start and dest     //
//	  int -> bandwidth to use		   //
//Output : char * ->Shortest way		   //
//Purpose : Before to allocate bandwidth, confirm  //
// 	    whether there are enough bandwidth	   //
///////////////////////////////////////////////////// 
char * Dijkstra::Confirm_band(char start, char dest, int use) {
	char * arr = VertexArray();
	char way[26] = {NULL, }; //save to shortest way about start and dest
	int len = 0;
	int u = 0;

	Node * pCur = Ad_list->get_Ad_head();

	strcpy(way, ShortestWay(start, dest)); //get shortest way about vertex from and dest

	if(use<0) return way; //if use <0, just return way
	else u = use;
	output.open("result.out", std::ios_base::app);

	for(int i=0;way[i]!=NULL;i++) { //print shortest way
		output << way[i] << "    ";
	}
	output << endl;
	output.close();

	pCur = Ad_list->get_Ad_head();
	for(int i=0; way[i+1]!=NULL; i++) { //confirm bandwidth
		while(pCur) { //get start vertex
			if(pCur->get_vertex()==way[i]) { //find start vertex
				pCur = pCur->get_pRight();
				while(pCur) { //get dest vertex
					if(pCur->get_vertex()==way[i+1]) break; //find dest vertex
					else pCur = pCur->get_pRight();
				}
				if(pCur->get_Remain_Band() >= u) { //compare whetehr remain bandwidth is larger than u
					pCur = Ad_list->get_Ad_head(); //set to head again
					break;
				}
				else return "a"; //lack of bandwidth, return "a"
			}
			else pCur = pCur->get_pDown();
		}
	}
	return way;
}
/////////////////////////////////////////////////////
//TMatrix :: Bandwidth_Allocation		   //
//=================================================//
//Input : char, char -> vertex of start and dest   //
//        int -> bandwidth to allocate		   //
//Output : bool -> true, false			   //
//Purpose : To allocate bandwidth		   //
///////////////////////////////////////////////////// 
bool Dijkstra::Bandwidth_Allocation(char start, char dest, int use) {
	char con[26] = {NULL, };
	int u = 0;

	if(use<0) u = use * (-1);
	else u = use;
	strcpy(con, Confirm_band(start, dest, use)); //Confirm whether there are enough bandwidth


	if(strcmp(con, "a")==0) return false; //lack of bandwidth
	else {
		Node * pCur = Ad_list->get_Ad_head();

		for(int i=0; con[i+1]!=NULL; i++) {
			while(pCur) { //get start vertex
				if(pCur->get_vertex()==con[i]) { //find start vertex
					pCur = pCur->get_pRight();
					while(pCur) { //get dest vertex
						if(pCur->get_vertex()==con[i+1]) break; //find dest vertex
						else pCur = pCur->get_pRight();
					}
					pCur->set_Remain_Band(use); //allocate bandwidth
					pCur = Ad_list->get_Ad_head(); //set header of adjacent list again
					break;
				}
				else pCur = pCur->get_pDown();
			}
		}

		int len = strlen(con);
		char temp = NULL;
		for(int i=0;i<len/2;i++) { //swap path because graph is the two side path
			temp = con[i];
			con[i] = con[len-1-i];
			con[len-1-i] = temp;
		}

		pCur = Ad_list->get_Ad_head();
		for(int i=0; con[i+1]!=NULL; i++) {
			while(pCur) { //get start vertex
				if(pCur->get_vertex()==con[i]) { //find start vertex
					pCur = pCur->get_pRight();
					while(pCur) { //get dest vertex
						if(pCur->get_vertex()==con[i+1]) break; //find dest vertex
						else pCur = pCur->get_pRight();
					}
					pCur->set_Remain_Band(use); //allocate bandwidth
					pCur = Ad_list->get_Ad_head();
					break;
				}
				else pCur = pCur->get_pDown();
			}
		}
	}
	return true;
}
/////////////////////////////////////////////////////
//TMatrix :: ShortestWay			   //
//=================================================//
//Input : char, char -> vertex of start and dest   //
//Output : char * -> return shortest way	   //
//Purpose : To get shortest way from Shortest	   //
///////////////////////////////////////////////////// 
char * Dijkstra::ShortestWay(char start, char dest) {
	char * arr = VertexArray();
	char way[26] = {NULL, };
	int len = 0;

	Node * pCur = Ad_list->get_Ad_head();

	while(pCur) { //get an index of start vertex
		if(pCur->get_vertex()==start) break;
		else pCur = pCur->get_pDown();
	}
	int start_index = pCur->get_index();

	pCur = Ad_list->get_Ad_head();
	while(pCur) { //get an index of dest vertex
		if(pCur->get_vertex()==dest) break;
		else pCur = pCur->get_pDown();
	}
	int dest_index = pCur->get_index();

	way[0] = dest;
	len++;
	for(int i=1;;i++) { //get shortest way by using Shortest
		way[i] = Shortest[start_index][dest_index];
		len++;
		if(way[i] == arr[start_index]) break;
		for(int j=0;;j++) {
			if(way[i] == arr[j]) {
				dest_index = j;
				break;
			}
		}
	}

	char temp = NULL;
	for(int i=0;i<len/2;i++) { //Swap
		temp = way[i];
		way[i] = way[len-1-i];
		way[len-1-i] = temp;
	}
	return way;
}
/////////////////////////////////////////////////////
//TMatrix :: Print				   //
//=================================================//
//Input : char -> vertex of start		   //
//Output : void					   //
//Purpose : Print all of shortest way from start   //
//	    to the other vertexes		   //
///////////////////////////////////////////////////// 
void Dijkstra::Print(char start) {
	char * arr = VertexArray();
	Node * pCur = Ad_list->get_Ad_head();
	char way[26] = {NULL, };

	output.open("result.out", std::ios_base::app);
	output << "=====================<< " << start<<" >>=====================" << endl;

	while(pCur) { //get an index of start vertex
		if(pCur->get_vertex()==start) break;
		else pCur = pCur->get_pDown();
	}
	int start_index = pCur->get_index();

	for(int i=0;i<length;i++) {
		if(i==start_index) continue;
		else {
			strcpy(way, ShortestWay(start, arr[i])); //get shortest way 
			int j=0;
			output << "        ";
			while(way[j]!=NULL) { //print shortest way
				output << way[j] << "    ";
				j++;
			}
			output << endl;
		}
	}
	output << "=================================================" << endl;
	output.close();
}
/////////////////////////////////////////////////////
//TMatrix :: Linkfail				   //
//=================================================//
//Input : char, char -> vertex of start and dest   //
//Output : char * -> return start vertex	   //
//Purpose : To find start vertex that has the path //
//	    of linkd fail			   //
///////////////////////////////////////////////////// 
char * Dijkstra::Linkfail(char start, char dest) {
	Node * pCur = Ad_list->get_Ad_head();
	char * arr = VertexArray();
	char starter[26] = {NULL, };
	int len = 0;

	while(pCur) { //get an index of start vertex
		if(pCur->get_vertex()==start) break;
		else pCur = pCur->get_pDown();
	}
	int start_index = pCur->get_index();

	pCur = Ad_list->get_Ad_head();
	while(pCur) { //get a index of dest vertex
		if(pCur->get_vertex()==dest) break;
		else pCur = pCur->get_pDown();
	}
	int dest_index = pCur->get_index();

	for(int i=0;i<length;i++) {
		if(Shortest[i][start_index] == dest || Shortest[i][dest_index] == start) { //linke fail path include
			starter[len] = arr[i]; //save that start to starter array
			len++;
		} 
	}
	return starter;
}
Dijkstra::~Dijkstra(void)
{
}
