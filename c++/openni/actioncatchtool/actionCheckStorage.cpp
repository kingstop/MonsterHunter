#include "StdAfx.h"
#include "resource.h"
#include "actionCheckStorage.h"
#include "actioncatchtoolDlg.h"
#include "DlgActionCheck.h"

actionCheckStorage::actionCheckStorage(void)
{
}


actionCheckStorage::~actionCheckStorage(void)
{
}


bool actionCheckStorage::add_action(const char* szname)
{
	if (szname == "")
	{
		return false;
	}
	ACTIONCHECKS::iterator it = _action_checks.find(szname);
	if (it != _action_checks.end())
	{
		return false;
	}
	actionCheck* temp_enry = new actionCheck();
	std::string str_name = szname;
	temp_enry->action_name = str_name;
	_action_checks.insert(ACTIONCHECKS::value_type(str_name, temp_enry));
	on_action_added(str_name.c_str());
	return true;
}

actionCheck* actionCheckStorage::get_action(const char* szname)
{
	actionCheck* action_check = NULL;
	ACTIONCHECKS::iterator it = _action_checks.find(szname);
	if (it != _action_checks.end())
	{
		action_check = it->second;
	}
	return action_check;
}

void actionCheckStorage::save()
{
	FILE* fp = fopen("actionCheckStorage.data", "wb+");
	if (fp)
	{
		
		int current = 0;
		char sztemp[256];
		fseek(fp,current,SEEK_SET);
		int count_temp = 0;
		int size_temp = sizeof(count_temp);
		count_temp = _action_checks.size();
		fwrite(&count_temp, size_temp, 1, fp);

		current += size_temp;
		fseek(fp, current, SEEK_SET);


		ACTIONCHECKS::iterator it = _action_checks.begin();
		for (; it != _action_checks.end(); ++ it)
		{
			actionCheck* temp_entry = it->second;
			sprintf_s(sztemp, "%s", temp_entry->action_name.c_str());
			size_temp = sizeof(sztemp);
			fwrite(sztemp, size_temp, 1, fp);
			current += size_temp;
			fseek(fp, current, SEEK_SET);

			count_temp = temp_entry->check_frames.size();
			size_temp = sizeof(count_temp);
			fwrite(&count_temp, size_temp, 1, fp);
			current += size_temp;
			fseek(fp, current, SEEK_SET);

			FRAMECHECKS::iterator it_entry = temp_entry->check_frames.begin();
			for (; it_entry != temp_entry->check_frames.end(); ++ it_entry)
			{
				frameCheck temp_frameCheck = (*it_entry);
				count_temp = temp_frameCheck.check_degrees.size();
				size_temp = sizeof(count_temp);
				fwrite(&count_temp, size_temp, 1, fp);
				current += size_temp;
				fseek(fp, current, SEEK_SET);

				FRAMESCHECKDEGREES::iterator it_entry_check_degrees = temp_frameCheck.check_degrees.begin();
				for (; it_entry_check_degrees != temp_frameCheck.check_degrees.end(); ++ it_entry_check_degrees)
				{
					size_temp = sizeof(it_entry_check_degrees->degree);
					fwrite(&(it_entry_check_degrees->degree), size_temp, 1, fp);
					current += size_temp;
					fseek(fp, current, SEEK_SET);

					size_temp = sizeof(it_entry_check_degrees->pos);
					fwrite(it_entry_check_degrees->pos, size_temp, 1, fp);
					current += size_temp;
					fseek(fp, current, SEEK_SET);

					size_temp = sizeof(it_entry_check_degrees->Recognize);
					fwrite(&(it_entry_check_degrees->Recognize), size_temp, 1, fp);
					current += size_temp;
					fseek(fp, current, SEEK_SET);				
				}
				
				sprintf_s(sztemp, "%s", temp_frameCheck.check_name.c_str());
				size_temp = sizeof(sztemp);
				fwrite(sztemp, size_temp, 1, fp);
				current += size_temp;
				fseek(fp, current, SEEK_SET);


				size_temp = sizeof(temp_frameCheck.duration_time);
				fwrite(&temp_frameCheck.duration_time, size_temp, 1, fp);
				current += size_temp;
				fseek(fp, current, SEEK_SET);


				size_temp = sizeof(temp_frameCheck.interval_time);
				fwrite(&temp_frameCheck.interval_time, size_temp, 1, fp);
				current += size_temp;
				fseek(fp, current, SEEK_SET);
			}


		}
		fclose(fp);
	}
}


void actionCheckStorage::load()
{
	FILE* fp = fopen("actionCheckStorage.data", "rb");
	if (fp)
	{
		int current = 0;
		char sztemp[256];
		fseek(fp,current,SEEK_SET);
		int count_temp = 0;
		int size_temp = sizeof(count_temp);
		//count_temp = _action_checks.size();
		fread(&count_temp, size_temp, 1, fp);

		current += size_temp;
		fseek(fp, current, SEEK_SET);


		//ACTIONCHECKS::iterator it = _action_checks.begin();
		for (int i = 0; i < count_temp; i ++)
		{
			actionCheck* temp_entry = new actionCheck();
			size_temp = sizeof(sztemp);
			fread(sztemp, size_temp, 1, fp);
			current += size_temp;
			temp_entry->action_name = sztemp;
			fseek(fp, current, SEEK_SET);

			int frame_count = 0;
			size_temp = sizeof(frame_count);
			fread(&frame_count, size_temp, 1, fp);
			current += size_temp;
			fseek(fp, current, SEEK_SET);

			for (int j = 0; j < frame_count; j ++)
			{
				frameCheck temp_frameCheck;
				int degrees_count_temp = temp_frameCheck.check_degrees.size();
				size_temp = sizeof(degrees_count_temp);
				fread(&degrees_count_temp, size_temp, 1, fp);
				current += size_temp;
				fseek(fp, current, SEEK_SET);

				for (int c = 0; c < degrees_count_temp; c ++)
				{
					check_degree check_degree_entry;
					size_temp = sizeof(check_degree_entry.degree);
					fread(&(check_degree_entry.degree), size_temp, 1, fp);
					current += size_temp;
					fseek(fp, current, SEEK_SET);

					size_temp = sizeof(check_degree_entry.pos);
					fread(check_degree_entry.pos, size_temp, 1, fp);
					current += size_temp;
					fseek(fp, current, SEEK_SET);

					size_temp = sizeof(check_degree_entry.Recognize);
					fread(&(check_degree_entry.Recognize), size_temp, 1, fp);
					current += size_temp;
					fseek(fp, current, SEEK_SET);

					temp_frameCheck.check_degrees.push_back(check_degree_entry);
				}
				//sprintf_s(sztemp, "%s", temp_frameCheck.check_name.c_str());
				size_temp = sizeof(sztemp);
				fread(sztemp, size_temp, 1, fp);
				current += size_temp;
				fseek(fp, current, SEEK_SET);
				temp_frameCheck.check_name = sztemp;

				size_temp = sizeof(temp_frameCheck.duration_time);
				fread(&temp_frameCheck.duration_time, size_temp, 1, fp);
				current += size_temp;
				fseek(fp, current, SEEK_SET);

				size_temp = sizeof(temp_frameCheck.interval_time);
				fread(&temp_frameCheck.interval_time, size_temp, 1, fp);
				current += size_temp;
				fseek(fp, current, SEEK_SET);
				temp_entry->check_frames.push_back(temp_frameCheck);
			}		
			_action_checks.insert(ACTIONCHECKS::value_type(temp_entry->action_name, temp_entry));
			on_action_added(temp_entry->action_name.c_str());
		}
		fclose(fp);
	}
}

void actionCheckStorage::on_action_added(const char* szname)
{
	g_dlg->_page_view_action->_lits_actions.AddString(szname);
}