#pragma once
#include "frameStorage.h"

typedef std::vector<check_degree> FRAMESCHECKDEGREES;
struct frameCheck{
	FRAMESCHECKDEGREES check_degrees;
	std::string check_name;
	int interval_time;
	int duration_time;
};

typedef std::vector<frameCheck> FRAMECHECKS;
struct frame_check_source
{	
	XnVector3D frame_point[XN_SKEL_MAX];
	XnVector3D frame_real_point[XN_SKEL_MAX];
	std::string frame_name;
	double right_temp;
	double bottom_temp;
};

struct actionCheck{
	FRAMECHECKS check_frames;
	std::string action_name;
};
typedef std::map<std::string, actionCheck*> ACTIONCHECKS;
class actionCheckStorage
{
public:
	actionCheckStorage(void);
	virtual ~actionCheckStorage(void);
public:
	bool add_action(const char* szname);
	actionCheck* get_action(const char* szname);
	void load();
	void save();
	std::string cur_select;
	std::string cur_select_edit;
protected:
	void on_action_added(const char* szname);
protected:
	ACTIONCHECKS _action_checks;		
};

