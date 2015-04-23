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

void actionCheckStorage::load()
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

			}


		}


	}
}

void actionCheckStorage::on_action_added(const char* szname)
{
	g_dlg->_page_view_action->_lits_actions.AddString(szname);
}