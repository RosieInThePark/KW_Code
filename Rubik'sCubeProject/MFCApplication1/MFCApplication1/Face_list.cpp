#include "stdafx.h"
#include "Face_list.h"


Face_list::Face_list(void)
{
	Face  * f1,*f2,*f3,*f4,*f5,*f6;

	f1 = new Face;
	f2 = new Face;
	f3 = new Face;
	f4 = new Face;
	f5 = new Face;
	f6 = new Face;

	Face_Header = f1;
	f1->set_name('A');
	f1->set_value(1);
	f1->set_next(f2);
	f1->set_up(f5);

	f2->set_name('B');
	f2->set_value(10);
	f2->set_next(f3);

	f3->set_name('C');
	f3->set_value(19);
	f3->set_next(f4);
	f3->set_up(f6);

	f4->set_name('D');
	f4->set_value(28);
	f4->set_next(f1);

	f5->set_name('E');
	f5->set_value(37);
	f5->set_up(f3);

	f6->set_name('F');
	f6->set_value(46);
	f6->set_up(f1);

	number=1;
	numer =1;
	co=0;
	count=0;
	for(int i=0;i<1000;i++) {
		key_save[i] = NULL;
		mouse_save[i] = NULL;
	}
}
void Face_list::set_head(Face * head) {Face_Header = head;}
Face * Face_list::get_head() {return Face_Header;}

void Face_list::slice_horizontal(int face, int height, int start, int end) {
	int temp1[3], temp2[3];

	if(face==0) {
		if(start<end) {
			for(int i=0;i<3;i++) temp2[i] = Face_Header->get_one_value(height,i);
			for(int i=0;i<3;i++) temp1[i] = Face_Header->get_next()->get_one_value(height,i);
			Face_Header->get_next()->set_horizontal(height,temp2);
			for(int i=0;i<3;i++) temp2[i] = Face_Header->get_next()->get_next()->get_one_value(height,i);
			Face_Header->get_next()->get_next()->set_horizontal(height,temp1);
			for(int i=0;i<3;i++) temp1[i] = Face_Header->get_next()->get_next()->get_next()->get_one_value(height,i);
			Face_Header->get_next()->get_next()->get_next()->set_horizontal(height,temp2);
			Face_Header->set_horizontal(height,temp1);

			if(height==0) Face_Header->get_up()->turn_side(1);
			else if(height==2) Face_Header->get_up()->get_up()->get_up()->turn_side(2);
		}
		else if(start>end) {
			for(int i=0;i<3;i++) temp1[i] = Face_Header->get_one_value(height,i);
			for(int i=0;i<3;i++) temp2[i] = Face_Header->get_next()->get_one_value(height,i);
			Face_Header->set_horizontal(height,temp2);
			for(int i=0;i<3;i++) temp2[i] = Face_Header->get_next()->get_next()->get_one_value(height,i);
			Face_Header->get_next()->set_horizontal(height,temp2);
			for(int i=0;i<3;i++) temp2[i] = Face_Header->get_next()->get_next()->get_next()->get_one_value(height,i);
			Face_Header->get_next()->get_next()->set_horizontal(height,temp2);
			Face_Header->get_next()->get_next()->get_next()->set_horizontal(height,temp1);

			if(height==0) Face_Header->get_up()->turn_side(2);
			else if(height==2) Face_Header->get_up()->get_up()->get_up()->turn_side(1);
		}
	}
	else if(face==1) {
		if(start<end) {
			for(int i=0;i<3;i++) temp1[i] = Face_Header->get_up()->get_one_value(height,i);
			for(int i=0;i<3;i++) temp2[i] = Face_Header->get_next()->get_one_value(2-i,2-height);
			Face_Header->get_next()->set_vertical(2-height, temp1);
			for(int i=0;i<3;i++) temp1[i] = Face_Header->get_up()->get_up()->get_up()->get_one_value(2-height, i);
			Face_Header->get_up()->get_up()->get_up()->set_horizontal(2-height,temp2);
			for(int i=0;i<3;i++) temp2[i] = Face_Header->get_next()->get_next()->get_next()->get_one_value(2-i,height);
			Face_Header->get_next()->get_next()->get_next()->set_vertical(height, temp1);
			Face_Header->get_up()->set_horizontal(height,temp2);

			if(height==0) Face_Header->get_up()->get_up()->turn_side(1);
			else if(height==2) Face_Header->turn_side(2);
		}
		else if(start>end) {
			for(int i=0;i<3;i++) temp1[i] = Face_Header->get_up()->get_one_value(height,i);
			for(int i=0;i<3;i++) temp2[i] = Face_Header->get_next()->get_one_value(i,2-height);
			Face_Header->get_up()->set_horizontal(height, temp2);
			for(int i=0;i<3;i++) temp2[i] = Face_Header->get_up()->get_up()->get_up()->get_one_value(2-height, 2-i);
			Face_Header->get_next()->set_vertical(2-height,temp2);
			for(int i=0;i<3;i++) temp2[i] = Face_Header->get_next()->get_next()->get_next()->get_one_value(i,height);
			Face_Header->get_up()->get_up()->get_up()->set_horizontal(2-height, temp2);
			Face_Header->get_next()->get_next()->get_next()->set_vertical(height,temp1);

			if(height==0) Face_Header->get_up()->get_up()->turn_side(2);
			else if(height==2) Face_Header->turn_side(1);
		}
	}
	else if(face==2) {
		if(start<end) {
			for(int i=0;i<3;i++) temp2[i] = Face_Header->get_one_value(height,i);
			for(int i=0;i<3;i++) temp1[i] = Face_Header->get_next()->get_one_value(height,i);
			Face_Header->get_next()->set_horizontal(height,temp2);
			for(int i=0;i<3;i++) temp2[i] = Face_Header->get_next()->get_next()->get_one_value(height,i);
			Face_Header->get_next()->get_next()->set_horizontal(height,temp1);
			for(int i=0;i<3;i++) temp1[i] = Face_Header->get_next()->get_next()->get_next()->get_one_value(height,i);
			Face_Header->get_next()->get_next()->get_next()->set_horizontal(height,temp2);
			Face_Header->set_horizontal(height,temp1);

			if(height==0) Face_Header->get_up()->turn_side(1);
			else if(height==2) Face_Header->get_up()->get_up()->get_up()->turn_side(2);
		}
		else if(start>end) {
			for(int i=0;i<3;i++) temp1[i] = Face_Header->get_one_value(height,i);
			for(int i=0;i<3;i++) temp2[i] = Face_Header->get_next()->get_one_value(height,i);
			Face_Header->set_horizontal(height,temp2);
			for(int i=0;i<3;i++) temp2[i] = Face_Header->get_next()->get_next()->get_one_value(height,i);
			Face_Header->get_next()->set_horizontal(height,temp2);
			for(int i=0;i<3;i++) temp2[i] = Face_Header->get_next()->get_next()->get_next()->get_one_value(height,i);
			Face_Header->get_next()->get_next()->set_horizontal(height,temp2);
			Face_Header->get_next()->get_next()->get_next()->set_horizontal(height,temp1);

			if(height==0) Face_Header->get_up()->turn_side(2);
			else if(height==2) Face_Header->get_up()->get_up()->get_up()->turn_side(1);
		}
	}
}
void Face_list::slice_vertical(int face, int width, int start, int end) {
	int temp1[3], temp2[3];
	if(face==0) {
		if(start<end) {
			for(int i=0;i<3;i++) temp1[i] = Face_Header->get_one_value(i,width);
			for(int i=0;i<3;i++) temp2[i] = Face_Header->get_up()->get_one_value(i,width);
			Face_Header->set_vertical(width,temp2);
			for(int i=0;i<3;i++) temp2[i] = Face_Header->get_up()->get_up()->get_one_value(2-i,2-width);
			Face_Header->get_up()->set_vertical(width,temp2);
			for(int i=0;i<3;i++) temp2[i] = Face_Header->get_up()->get_up()->get_up()->get_one_value(2-i,width);
			Face_Header->get_up()->get_up()->set_vertical(2-width,temp2);
			Face_Header->get_up()->get_up()->get_up()->set_vertical(width,temp1);

			if(width==0) Face_Header->get_next()->get_next()->get_next()->turn_side(2);
			else if(width==2) Face_Header->get_next()->turn_side(1);
		}
		else if(start>end) {
			for(int i=0;i<3;i++) temp2[i] = Face_Header->get_one_value(i,width);
			for(int i=0;i<3;i++) temp1[i] = Face_Header->get_up()->get_one_value(2-i,width);
			Face_Header->get_up()->set_vertical(width,temp2);
			for(int i=0;i<3;i++) temp2[i] = Face_Header->get_up()->get_up()->get_one_value(2-i,2-width);
			Face_Header->get_up()->get_up()->set_vertical(2-width,temp1);
			for(int i=0;i<3;i++) temp1[i] = Face_Header->get_up()->get_up()->get_up()->get_one_value(i,width);
			Face_Header->get_up()->get_up()->get_up()->set_vertical(width,temp2);
			Face_Header->set_vertical(width,temp1);

			if(width==0) Face_Header->get_next()->get_next()->get_next()->turn_side(1);
			else if(width==2)  Face_Header->get_next()->turn_side(2);
		}
	}
	else if(face==1) {
		if(start<end) {
			for(int i=0;i<3;i++) temp1[i] = Face_Header->get_one_value(i,width);
			for(int i=0;i<3;i++) temp2[i] = Face_Header->get_up()->get_one_value(i,width);
			Face_Header->set_vertical(width,temp2);
			for(int i=0;i<3;i++) temp2[i] = Face_Header->get_up()->get_up()->get_one_value(2-i,2-width);
			Face_Header->get_up()->set_vertical(width,temp2);
			for(int i=0;i<3;i++) temp2[i] = Face_Header->get_up()->get_up()->get_up()->get_one_value(2-i,width);
			Face_Header->get_up()->get_up()->set_vertical(2-width,temp2);
			Face_Header->get_up()->get_up()->get_up()->set_vertical(width,temp1);

			if(width==0) Face_Header->get_next()->get_next()->get_next()->turn_side(2);
			else if(width==2) Face_Header->get_next()->turn_side(1);
		}
		else if(start>end) {
			for(int i=0;i<3;i++) temp2[i] = Face_Header->get_one_value(i,width);
			for(int i=0;i<3;i++) temp1[i] = Face_Header->get_up()->get_one_value(2-i,width);
			Face_Header->get_up()->set_vertical(width,temp2);
			for(int i=0;i<3;i++) temp2[i] = Face_Header->get_up()->get_up()->get_one_value(2-i,2-width);
			Face_Header->get_up()->get_up()->set_vertical(2-width,temp1);
			for(int i=0;i<3;i++) temp1[i] = Face_Header->get_up()->get_up()->get_up()->get_one_value(i,width);
			Face_Header->get_up()->get_up()->get_up()->set_vertical(width,temp2);
			Face_Header->set_vertical(width,temp1);

			if(width==0) Face_Header->get_next()->get_next()->get_next()->turn_side(1);
			else if(width==2)  Face_Header->get_next()->turn_side(2);
		}
	}
	else if(face==2) {
		if(start<end) {
			for(int i=0;i<3;i++) temp1[i] = Face_Header->get_up()->get_one_value(2-width,i);
			for(int i=0;i<3;i++) temp2[i] = Face_Header->get_next()->get_one_value(2-i,width);
			Face_Header->get_next()->set_vertical(width, temp1);
			for(int i=0;i<3;i++) temp1[i] = Face_Header->get_up()->get_up()->get_up()->get_one_value(width, i);
			Face_Header->get_up()->get_up()->get_up()->set_horizontal(width,temp2);
			for(int i=0;i<3;i++) temp2[i] = Face_Header->get_next()->get_next()->get_next()->get_one_value(2-i,2-width);
			Face_Header->get_next()->get_next()->get_next()->set_vertical(2-width, temp1);
			Face_Header->get_up()->set_horizontal(2-width,temp2);

			if(width==0) Face_Header->turn_side(2);
			else if(width==2) Face_Header->get_up()->get_up()->turn_side(1);
		}
		else if(start>end) {
			for(int i=0;i<3;i++) temp1[i] = Face_Header->get_up()->get_one_value(2-width,2-i);
			for(int i=0;i<3;i++) temp2[i] = Face_Header->get_next()->get_one_value(i,width);
			Face_Header->get_up()->set_horizontal(2-width, temp2);
			for(int i=0;i<3;i++) temp2[i] = Face_Header->get_up()->get_up()->get_up()->get_one_value(width, 2-i);
			Face_Header->get_next()->set_vertical(width,temp2);
			for(int i=0;i<3;i++) temp2[i] = Face_Header->get_next()->get_next()->get_next()->get_one_value(i,2-width);
			Face_Header->get_up()->get_up()->get_up()->set_horizontal(width, temp2);
			Face_Header->get_next()->get_next()->get_next()->set_vertical(2-width,temp1);

			if(width==0) Face_Header->turn_side(1);
			else if(width==2) Face_Header->get_up()->get_up()->turn_side(2);
		}
	}
}

void Face_list::keyboard_log(int num) {
	if(num==1) { //right
		key_save[count] = '.'; count++;
		key_save[count] = 'K'; count++;
		key_save[count] = 'e'; count++;
		key_save[count] = 'y'; count++;
		key_save[count] = '_'; count++;
		key_save[count] = 'R'; count++;
		key_save[count] = 'i'; count++;
		key_save[count] = 'g'; count++;
		key_save[count] = 'h'; count++;
		key_save[count] = 't'; count++;
		key_save[count] = '\n'; count++;
	}
	else if(num==2) { //left
		key_save[count] = '.'; count++;
		key_save[count] = 'K'; count++;
		key_save[count] = 'e'; count++;
		key_save[count] = 'y'; count++;
		key_save[count] = '_'; count++;
		key_save[count] = 'L'; count++;
		key_save[count] = 'e'; count++;
		key_save[count] = 'f'; count++;
		key_save[count] = 't'; count++;
		key_save[count] = '\n'; count++;
	}
	else if(num==3) { //up
		key_save[count] = '.'; count++;
		key_save[count] = 'K'; count++;
		key_save[count] = 'e'; count++;
		key_save[count] = 'y'; count++;
		key_save[count] = '_'; count++;
		key_save[count] = 'U'; count++;
		key_save[count] = 'p'; count++;
		key_save[count] = '\n'; count++;
	}
	else if(num==4) { //down
		key_save[count] = '.'; count++;
		key_save[count] = 'K'; count++;
		key_save[count] = 'e'; count++;
		key_save[count] = 'y'; count++;
		key_save[count] = '_'; count++;
		key_save[count] = 'D'; count++;
		key_save[count] = 'o'; count++;
		key_save[count] = 'w'; count++;
		key_save[count] = 'n'; count++;
		key_save[count] = '\n'; count++;
	}
}
void Face_list::key_File_out() {
	ofstream keyout;
	keyout.open("keyboard_log.txt");
	int index=0;
	while(key_save[index]!=NULL) {
		keyout<<number;
		while(key_save[index]!='\n') {
			keyout << key_save[index];
			index++;
		}
		keyout<<key_save[index];
		index++;
		number++;
	}
	keyout.close();
}
void Face_list::mouse_log(char name,int RorC, char num, int direction) {
	mouse_save[co] = '.'; co++;
	mouse_save[co] = 'F'; co++;
	mouse_save[co] = 'a'; co++;
	mouse_save[co] = 'c'; co++;
	mouse_save[co] = 'e'; co++;
	mouse_save[co] = ':'; co++;
	mouse_save[co] = name; co++;
	mouse_save[co] = '/'; co++;
	if(RorC == 0) {//Row
		mouse_save[co] = 'R'; co++;
		mouse_save[co] = 'o'; co++;
		mouse_save[co] = 'w'; co++;
		mouse_save[co] = ':'; co++;
	}
	else if(RorC == 1) {
		mouse_save[co] = 'C'; co++;
		mouse_save[co] = 'o'; co++;
		mouse_save[co] = 'l'; co++;
		mouse_save[co] = ':'; co++;
	}
	mouse_save[co] = num; co++;
	mouse_save[co] = '/'; co++;
	if(direction==1) { //right
		mouse_save[co] = 'R'; co++;
		mouse_save[co] = 'i';co++;
		mouse_save[co] = 'g'; co++;
		mouse_save[co] = 'h'; co++;
		mouse_save[co] = 't';co++;
		mouse_save[co] = '\n'; co++;
	}
	else if(direction==2) { //left
		mouse_save[co] = 'L'; co++;
		mouse_save[co] = 'e'; co++;
		mouse_save[co] = 'f'; co++;
		mouse_save[co] = 't'; co++;
		mouse_save[co] = '\n'; co++;
	}
	else if(direction==3) { //up
		mouse_save[co] = 'U'; co++;
		mouse_save[co] = 'p'; co++;
		mouse_save[co] = '\n'; co++;
	}
	else if(direction==4) { //down
		mouse_save[co] = 'D';co++;
		mouse_save[co] = 'o';co++;
		mouse_save[co] = 'w'; co++;
		mouse_save[co] = 'n'; co++;
		mouse_save[co] = '\n'; co++;
	}
}
void Face_list::mouse_File_out() {
	ofstream mout;
	mout.open("mouse_log.txt");
	int index=0;
	while(mouse_save[index]!=NULL) {
		mout << numer;
		while(mouse_save[index]!='\n') {
		mout << mouse_save[index];
		index++;
		}
		mout << mouse_save[index];
		index++;
		numer++;
	}
	mout.close();
}
Face_list::~Face_list(void)
{
}
