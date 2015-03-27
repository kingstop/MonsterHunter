#pragma once
#include <XnOpenNI.h>
#include <map>
#include <iostream>
#include <string>
#define  XN_SKEL_MAX XN_SKEL_RIGHT_FOOT + 1
#define  XN_SKEL_BEGIN XN_SKEL_HEAD

struct framedata{
	XnVector3D frame_point[XN_SKEL_MAX];
	std::string frame_name;
};


class frameCatch
{
public:
	typedef std::map<std::string, framedata*> FRAME_STORAGE;
public:
	frameCatch(void);
	~frameCatch(void);
public:
	void add_frame_data(XnVector3D XnVector3Ds[XN_SKEL_MAX]);
	void on_frame_added(const char* frame_named);
	void on_frame_deleted(const char* frame_named);
public:

protected:
	FRAME_STORAGE _frame_data;

	std::string _cur_sel_catch_frame;


};



