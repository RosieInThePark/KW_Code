#include "stdafx.h"
#include "Face.h"


Face::Face(void)
{
}
void Face::set_name(char name) {m_face_name = name;}
char Face::get_name() {return m_face_name;}
void Face::set_value(int count) {
	for(int i=0;i<3;i++) {
		for(int j=0;j<3;j++) {
			m_element_values[i][j] = count;
			count++;
		}
	}
}
int * Face::get_value() {
	return (int *)m_element_values;
}
void Face::set_next(Face * next) {p_Next = next;}
Face * Face::get_next() {return p_Next;}
void Face::set_up(Face * up) {p_Up = up;}
Face * Face::get_up() {return p_Up;}
int Face::get_one_value(int i, int j) {return m_element_values[i][j];}

void Face::set_horizontal(int i, int * temp) {
	for(int j=0;j<3;j++) {
		m_element_values[i][j] = temp[j];
	}
}
void Face::set_vertical(int i, int * temp) {
	for(int j=0;j<3;j++) {
		m_element_values[j][i] = temp[j];
	}
}
void Face::turn_side(int num) {
	int arr[9];
	int count=0;
	for(int i=0;i<3;i++) {
		for(int j=0;j<3;j++) {
			arr[count] = m_element_values[i][j];
			count++;
		}
	}
	count = 0;
	if(num==1) {
		for(int i=0;i<3;i++) {
			for(int j=2;j>=0;j--){
				m_element_values[j][i] = arr[count];
				count++;
			}
		}
	} //right & down
	else if(num==2) {
		for(int i=2;i>=0;i--) {
			for(int j=0;j<3;j++) {
				m_element_values[j][i] = arr[count];
				count++;
			}
		}
	}//left & up
}
void Face::change_back() {
	int temp;
	
	temp = m_element_values[0][0];
	m_element_values[0][0] = m_element_values[2][2];
	m_element_values[2][2] = temp; //(0,0)<->(2,2)

	temp = m_element_values[0][1];
	m_element_values[0][1] = m_element_values[2][1];
	m_element_values[2][1] = temp; //(0,1)<->(2,1)

	temp = m_element_values[0][2];
	m_element_values[0][2] = m_element_values[2][0];
	m_element_values[2][0] = temp; //(0,2)<->(2,0)

	temp = m_element_values[1][0];
	m_element_values[1][0] = m_element_values[1][2];
	m_element_values[1][2] = temp; //(1,0)<->(1,2)
}	
Face::~Face(void)
{
}
