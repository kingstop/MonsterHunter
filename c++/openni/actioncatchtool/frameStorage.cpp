#include "StdAfx.h"
#include "frameStorage.h"


frameStorage::frameStorage(void)
{

}



frameStorage::~frameStorage(void)
{
}


bool frameStorage::add_frame_check(const char* frame_name, XnVector3D temp_frame_point[XN_SKEL_MAX])
{
	FRAME_CHECKS::iterator it = _frame_checks.find(frame_name);
	if (it != _frame_checks.end())
	{
		return false;
	}
	frame_check* framecheck = new frame_check();
	framecheck->frame_name = frame_name;
	memcpy(framecheck->frame_point, temp_frame_point, sizeof(temp_frame_point) );	
	_frame_checks.insert(FRAME_CHECKS::value_type(framecheck->frame_name,framecheck));
	return true;
}

bool frameStorage::modify_frame(const char* frame_name, CHECKDEGREES& temp_check_degrees)
{
	FRAME_CHECKS::iterator it = _frame_checks.find(frame_name);
	if (it == _frame_checks.end())
	{
		return false;
	}
	frame_check* framecheck = it->second;

	if (framecheck)
	{
		framecheck->check_degrees = temp_check_degrees;
	}
	return true;
}