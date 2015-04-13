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


void frameCatch::save()
{
	
	FILE* fp = fopen("frameCatch.data", "wb+");
	if (fp)
	{
		int count_temp =  _frame_data.size();
		int size_temp = sizeof(count_temp);
		int current = 0;

		fseek(fp, 0, SEEK_SET);
		fwrite(&count_temp, size_temp, 1, fp);
		current += size_temp;

		fseek(fp, current, SEEK_SET);

		FRAME_STORAGE::iterator it = _frame_data.begin();
		for (int i = 0; i < count_temp; i ++, ++ it)
		{

		}


		

	}

}

void frameCatch::load()
{

}

void frameCatch::add_frame_data(XnVector3D XnVector3Ds[XN_SKEL_MAX], XnVector3D realXnVector3Ds[XN_SKEL_MAX],double right_temp, double bottom_temp)
{
	framedata* temp_frame = new framedata();	
	memcpy(temp_frame->frame_point, XnVector3Ds, sizeof(XnVector3Ds));
	memcpy(temp_frame->frame_real_point, realXnVector3Ds, sizeof(realXnVector3Ds));

	time_t t = time(0); 
	char tmp[64]; 
	tm* temp_t = localtime(&t);
	sprintf(tmp, "%d/%d/%d %d:%d:%d", temp_t->tm_year, temp_t->tm_mon, temp_t->tm_mday, temp_t->tm_hour, temp_t->tm_min, temp_t->tm_sec);
	temp_frame->frame_name = tmp;
	temp_frame->right_temp = right_temp;
	temp_frame->bottom_temp = bottom_temp;
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
	int count_temp = g_dlg->_page_view_catch->_view_catch.GetCount();
	for (int i = 0; i < count_temp; i ++)
	{
		CString temp_string;
		g_dlg->_page_view_catch->_view_catch.GetText(i, temp_string);
		if (frame_named == temp_string)
		{
			g_dlg->_page_view_catch->_view_catch.DeleteString(i);
			break;
		}
	}
}
