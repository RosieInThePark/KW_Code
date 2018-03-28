#pragma once
#include <iostream>
#include <fstream>
#include "Face.h"

using namespace std;

class Face_list
{
private:
	Face * Face_Header;
	char key_save[1000];
	char mouse_save[1000];
	int count,co;
	int number,numer;
public:
	Face_list(void);
	~Face_list(void);

	void set_head(Face * head);
	Face * get_head();

	void slice_horizontal(int face, int height, int start, int end);
	void slice_vertical(int face, int width, int start, int end);

	void keyboard_log(int num);
	void key_File_out();

	void mouse_log(char name,int RorC, char num, int direction);
	void mouse_File_out();
};

