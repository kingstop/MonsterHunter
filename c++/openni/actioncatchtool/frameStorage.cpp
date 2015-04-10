#include "StdAfx.h"
#include "resource.h"
#include "frameStorage.h"

#include "actioncatchtoolDlg.h"
#include "DlgViewEdit.h"
int getangleforposition(XnVector3D position_1, XnVector3D position_2, XnVector3D position_3)
{
	double lineP1P2 = sqrt((double)((position_1.X - position_2.X) * (position_1.X - position_2.X) + (position_1.Y - position_2.Y) * (position_1.Y - position_2.Y) + (position_1.Z - position_2.Z) * (position_1.Z - position_2.Z)));
	double lineP1P3 = sqrt((double)((position_1.X - position_3.X) * (position_1.X - position_3.X) + (position_1.Y - position_3.Y) * (position_1.Y - position_3.Y) + (position_1.Z - position_3.Z) * (position_1.Z - position_3.Z)));
	double lineP2P3 = sqrt((double)((position_2.X - position_3.X) * (position_2.X - position_3.X) + (position_2.Y - position_3.Y) * (position_2.Y - position_3.Y) + (position_2.Z - position_3.Z) * (position_2.Z - position_3.Z)));

	// 根据题目要求，需要将弧度转换为度
	//double angleP1 = acos((lineP1P2 * lineP1P2 + lineP1P3 * lineP1P3 - lineP2P3 * lineP2P3) / (2 * lineP1P2 * lineP1P3)) * 180.0 / 3.1415926;
	double angleP2 = acos((lineP1P2 * lineP1P2 + lineP2P3 * lineP2P3 - lineP1P3 * lineP1P3) / (2 * lineP1P2 * lineP2P3)) * 180.0 / 3.1415926;
	//double angleP3 = acos((lineP1P3 * lineP1P3 + lineP2P3 * lineP2P3 - lineP1P2 * lineP1P2)
	if(angleP2 > 180)
	{
		angleP2 = 360 -angleP2;
	}
	return angleP2;
}

std::string mk_degree_title(XnSkeletonJoint pos_1, XnSkeletonJoint pos_2, XnSkeletonJoint pos_3)
{
	std::string temp;
	temp = pos_name_config[pos_1] + "_" + pos_name_config[pos_2] + "_" + pos_name_config[pos_3];
	return temp;
}
std::string pos_name_config[XN_SKEL_MAX];

frameStorage::frameStorage(void)
{
	pos_name_config[XN_SKEL_BEGIN] = "BEGIN";

	pos_name_config[XN_SKEL_HEAD] = "HEAD";
	pos_name_config[XN_SKEL_NECK] = "NECK";
	pos_name_config[XN_SKEL_TORSO] = "TORSO";
	pos_name_config[XN_SKEL_WAIST] = "WAIST";

	pos_name_config[XN_SKEL_LEFT_COLLAR] = "LEFT_COLLAR";
	pos_name_config[XN_SKEL_LEFT_SHOULDER] = "LEFT_SHOULDER";
	pos_name_config[XN_SKEL_LEFT_ELBOW] = "LEFT_ELBOW";
	pos_name_config[XN_SKEL_LEFT_WRIST] = "LEFT_WRIST";
	pos_name_config[XN_SKEL_LEFT_HAND] = "LEFT_HAND";
	pos_name_config[XN_SKEL_LEFT_FINGERTIP] = "LEFT_FINGERTIP";

	pos_name_config[XN_SKEL_RIGHT_COLLAR] = "RIGHT_COLLAR";
	pos_name_config[XN_SKEL_RIGHT_SHOULDER] = "RIGHT_SHOULDER";
	pos_name_config[XN_SKEL_RIGHT_ELBOW] = "RIGHT_ELBOW";
	pos_name_config[XN_SKEL_RIGHT_WRIST] = "RIGHT_WRIST";
	pos_name_config[XN_SKEL_RIGHT_HAND] = "RIGHT_HAND";
	pos_name_config[XN_SKEL_RIGHT_FINGERTIP] = "RIGHT_FINGERTIP";

	pos_name_config[XN_SKEL_LEFT_HIP] = "LEFT_HIP";
	pos_name_config[XN_SKEL_LEFT_KNEE] = "LEFT_KNEE";
	pos_name_config[XN_SKEL_LEFT_ANKLE] = "LEFT_ANKLE";
	pos_name_config[XN_SKEL_LEFT_FOOT] = "LEFT_FOOT";

	pos_name_config[XN_SKEL_RIGHT_HIP] = "RIGHT_HIP";
	pos_name_config[XN_SKEL_RIGHT_KNEE] = "RIGHT_KNEE";
	pos_name_config[XN_SKEL_RIGHT_ANKLE] = "RIGHT_ANKLE";
	pos_name_config[XN_SKEL_RIGHT_FOOT] = "RIGHT_FOOT";		

	pos_name_config[XN_SKEL_MAX] = "MAX";
}



frameStorage::~frameStorage(void)
{
}

void frameStorage::load()
{
	FILE* fp = fopen("frame_storage", "wb+");
	if (fp)
	{
		int count_temp;
		fread()
	}
}


bool frameStorage::add_frame_check(const char* frame_name, XnVector3D temp_frame_point[XN_SKEL_MAX], XnVector3D temp_real_frame_point[XN_SKEL_MAX])
{
	FRAME_CHECKS::iterator it = _frame_checks.find(frame_name);
	if (it != _frame_checks.end())
	{
		return false;
	}
	frame_check* framecheck = new frame_check();
	framecheck->frame_name = frame_name;
	memcpy(framecheck->frame_point, temp_frame_point, sizeof(temp_frame_point) );	
	memcpy(framecheck->frame_real_point, temp_real_frame_point, sizeof(temp_real_frame_point));

	_frame_checks.insert(FRAME_CHECKS::value_type(framecheck->frame_name,framecheck));
	on_add_frame(frame_name);
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


bool frameStorage::add_cur_sel(const char* save_temp_name)
{
	framedata* temp_data = g_frameCatch.get_cur_select();
	if (temp_data)
	{
		if (_frame_checks.find(save_temp_name) != _frame_checks.end())
		{
			return false;
		}
		
	}
	add_frame_check(save_temp_name, temp_data->frame_point, temp_data->frame_real_point);
	return true;
}


frame_check* frameStorage::get_frame_check(const char* frame_name)
{
	FRAME_CHECKS::iterator it = _frame_checks.find(frame_name);
	if (it == _frame_checks.end())
	{
		return NULL;
	}
	frame_check* framecheck = it->second;
	return framecheck;
}

void frameStorage::on_add_frame(const char* save_temp_name)
{
	g_dlg->_page_view_edit->_edit_frames.AddString(save_temp_name);
}