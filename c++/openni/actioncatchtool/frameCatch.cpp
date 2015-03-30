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
	strftime( tmp, sizeof(tmp), "%Y/%m/%d ¡¾%T¡¿",localtime(&t) ); 
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

void frameCatch::on_frame_deleted(const char* frame_named)
{


}
