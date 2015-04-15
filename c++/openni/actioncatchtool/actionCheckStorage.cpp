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
	ACTIONCHECKS::iterator it = _action_checks.find(szname);
	if (it != _action_checks.end())
	{
		return false;
	}
	actionCheck* temp_enry = new actionCheck();
	std::string str_name = szname;
	_action_checks.insert(ACTIONCHECKS::value_type(str_name, temp_enry));
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

void actionCheckStorage::on_action_added(const char* szname)
{
	g_dlg->_page_view_action->_lits_actions.AddString(szname);
}