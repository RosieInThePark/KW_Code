#pragma once
#include <iostream>

using namespace std;

class Face
{
private:
	char m_face_name;
	int m_element_values[3][3];
	Face * p_Next;
	Face * p_Up;
public:
	Face(void);
	~Face(void);

	void set_name(char name);
	char get_name();

	void set_value(int count);
	int * get_value();

	void set_next(Face * next);
	Face * get_next();

	void set_up(Face * up);
	Face * get_up();

	void set_num(int i, int j);
	int get_num();

	void turn_side(int num);

	int get_one_value(int i, int j);
	void set_vertical(int i,int * temp);
	void set_horizontal(int i, int * temp);
	void change_back();
};

