#include "StdAfx.h"
#include "frameCatch.h"
#include "resource.h"
#include "actioncatchtoolDlg.h"
#include "DlgViewCatch.h"


frameCatch::frameCatch(void)
{
}


frameCatch::~frameCatch(void)
{
}


void frameCatch::add_frame_data(XnVector3D XnVector3Ds[XN_SKEL_MAX])
{
	framedata* temp_frame = new framedata();	
	for (int i = XN_SKEL_BEGIN; i < XN_SKEL_MAX; i ++)
	{
		temp_frame->frame_point[i] = XnVector3Ds[i];
	}

	time_t t = time(0); 
	char tmp[64]; 
	tm* temp_t = localtime(&t);
	sprintf(tmp, "%d/%d/%d %d:%d:%d", temp_t->tm_year, temp_t->tm_mon, temp_t->tm_mday, temp_t->tm_hour, temp_t->tm_min, temp_t->tm_sec);
	temp_frame->frame_name = tmp;
	FRAME_STORAGE::iterator it = _frame_data.find(temp_frame->frame_name);
	if (it != _frame_data.end())
	{
		_frame_data[temp_frame->frame_name] = temp_frame;
	}
	else{
		_frame_data[temp_frame->frame_name] = temp_frame;
		on_frame_added(temp_frame->frame_name.c_str());
	}
	
	
}



void frameCatch::on_frame_added(const char* frame_named)
{
	CString str_temp = frame_named;

	g_dlg->_page_view_catch->_view_catch.AddString(str_temp);
}


framedata* frameCatch::get_cur_select()
{
	framedata* temp = NULL; 
	FRAME_STORAGE::iterator it = _frame_data.find(_cur_sel_catch_frame);
	if (it != _frame_data.end())
	{
		temp = it->second;
	}
	return temp;
}

bool frameCatch::del_frame_data(const char* frame_name)
{
	framedata* temp = NULL; 
	FRAME_STORAGE::iterator it = _frame_data.find(frame_name);
	if (it != _frame_data.end())
	{
		_frame_data.erase(it);
		on_frame_deleted(frame_name);
		return true;
	}
	return false;

}

void frameCatch::on_frame_deleted(const char* frame_named)
{
	//g_dlg->_page_view_catch->_view_catch.d

}
