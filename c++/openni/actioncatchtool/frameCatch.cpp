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
	
	framedata* frame_data_temp = new framedata();
	frame_data_temp->frame_name = "4334";
	frame_data_temp->bottom_temp = 1231;
	frame_data_temp->right_temp = 1231;
	XnVector3D entry_3d;
	entry_3d.X = 32.1f;
	entry_3d.Y = 33.1f;
	entry_3d.Z = 34.1f;
	frame_data_temp->frame_point[0] = entry_3d;
	frame_data_temp->frame_real_point[0] = entry_3d;

	entry_3d.X = 42.1f;
	entry_3d.Y = 43.1f;
	entry_3d.Z = 44.1f;
	frame_data_temp->frame_point[1] = entry_3d;
	frame_data_temp->frame_real_point[1] = entry_3d;
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
		char sz_temp[256];

		FRAME_STORAGE::iterator it = _frame_data.begin();
		framedata* frame_data_temp = NULL;

		for (int i = 0; i < count_temp; i ++, ++ it)
		{
			frame_data_temp = it->second;
			size_temp = sizeof(sz_temp);
			sprintf(sz_temp, "%s", frame_data_temp->frame_name.c_str());
			fwrite(sz_temp, size_temp, 1, fp);
			current += size_temp;
			fseek(fp, current, SEEK_SET);

			size_temp = sizeof(frame_data_temp->bottom_temp);			
			fwrite(&(frame_data_temp->bottom_temp), size_temp, 1, fp);
			current += size_temp;
			fseek(fp, current, SEEK_SET);


			size_temp = sizeof(frame_data_temp->right_temp);			
			fwrite(&(frame_data_temp->right_temp), size_temp, 1, fp);
			current += size_temp;
			fseek(fp, current, SEEK_SET);

			size_temp = sizeof(frame_data_temp->frame_point);
			fwrite(&(frame_data_temp->frame_point), size_temp, 1, fp);
			current += size_temp;
			fseek(fp, current, SEEK_SET);

			size_temp = sizeof(frame_data_temp->frame_real_point);
			fwrite(&(frame_data_temp->frame_real_point), size_temp, 1, fp);
			current += size_temp;
			fseek(fp, current, SEEK_SET);

			//_frame_data.insert(FRAME_STORAGE::value_type(frame_data_temp->frame_name, frame_data_temp));
		}		

		fseek(fp, 0, SEEK_END);
		int length_entry = ftell(fp);
		fclose(fp);
	}

	 fp = fopen("frameCatch.data", "rb");
	 fseek(fp, 0, SEEK_END);
	 int length_entry = ftell(fp);
	 fclose(fp);

}

void frameCatch::load()
{
	FILE* fp = fopen("frameCatch.data", "rb");
	if (fp)
	{
		int count_temp =  _frame_data.size();
		int size_temp = sizeof(count_temp);
		int current = 0;

		fseek(fp, 0, SEEK_END);
		int length_entry = ftell(fp);
		if (length_entry != 0)
		{
			fseek(fp, 0, SEEK_SET);
			fread(&count_temp, size_temp, 1, fp);
			current += size_temp;

			fseek(fp, current, SEEK_SET);
			char sz_temp[256];		
			framedata* frame_data_temp = NULL;

			for (int i = 0; i < count_temp; i ++)
			{
				frame_data_temp = new framedata();
				size_temp = sizeof(sz_temp);
				fread(sz_temp, size_temp, 1, fp);
				frame_data_temp->frame_name = sz_temp;
				current += size_temp;
				fseek(fp, current, SEEK_SET);

				size_temp = sizeof(frame_data_temp->bottom_temp);			
				fread(&(frame_data_temp->bottom_temp), size_temp, 1, fp);
				current += size_temp;
				fseek(fp, current, SEEK_SET);


				size_temp = sizeof(frame_data_temp->right_temp);			
				fread(&(frame_data_temp->right_temp), size_temp, 1, fp);
				current += size_temp;
				fseek(fp, current, SEEK_SET);

				size_temp = sizeof(frame_data_temp->frame_point);
				fread(&(frame_data_temp->frame_point), size_temp, 1, fp);
				current += size_temp;
				fseek(fp, current, SEEK_SET);

				size_temp = sizeof(frame_data_temp->frame_real_point);
				fread(&(frame_data_temp->frame_real_point), size_temp, 1, fp);
				current += size_temp;
				fseek(fp, current, SEEK_SET);

				_frame_data.insert(FRAME_STORAGE::value_type(frame_data_temp->frame_name, frame_data_temp));
				on_frame_added(frame_data_temp->frame_name.c_str());
			}		
		}



		fclose(fp);
	}
}

void frameCatch::add_frame_data(XnVector3D XnVector3Ds[XN_SKEL_MAX], XnVector3D realXnVector3Ds[XN_SKEL_MAX],double right_temp, double bottom_temp)
{
	framedata* temp_frame = new framedata();	
	for (int i = XN_SKEL_BEGIN; i < XN_SKEL_MAX; i ++)
	{
		temp_frame->frame_point[i] = XnVector3Ds[i];
		temp_frame->frame_real_point[i] = realXnVector3Ds[i];

	}
	//memcpy(temp_frame->frame_point, XnVector3Ds, sizeof(XnVector3Ds) * XN_SKEL_MAX);
	//memcpy(temp_frame->frame_real_point, realXnVector3Ds, sizeof(realXnVector3Ds) * XN_SKEL_MAX);

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
