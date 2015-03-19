#include "StdAfx.h"
#include "action_storage.h"
#include "../../tinyxml/tinyxml.h"
#include <XnOpenNI.h>
#include <XnCppWrapper.h>
#ifndef USE_GLES
#if (XN_PLATFORM == XN_PLATFORM_MACOSX)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#else
#include "opengles.h"
#endif

extern xn::UserGenerator g_UserGenerator;
extern xn::DepthGenerator g_DepthGenerator;

extern XnBool g_bDrawBackground;
extern XnBool g_bDrawPixels;
extern XnBool g_bDrawSkeleton;
extern XnBool g_bPrintID;
extern XnBool g_bPrintState;


action_storage::action_storage(void)
{
}


action_storage::~action_storage(void)
{
}

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

void action_storage::frame_check(int user_id)
{
	player_frames* player_frames_temp = NULL;
	PLAERS_FRAME::iterator it_player_frame = _players_frames.find(user_id);
	std::vector<std::string> temp_frames;
	if (it_player_frame == _players_frames.end())
	{
		player_frames_temp = new player_frames();
		player_frames_temp->player_id = user_id;
		_players_frames.insert(PLAERS_FRAME::value_type(user_id, player_frames_temp));
	}
	else
	{
		player_frames_temp = it_player_frame->second;
		//player_frames_temp->frames.clear();
	}

	FRAMES::iterator it = _frames.begin();
	for (; it != _frames.end(); it ++)
	{
		frame_info* temp_frame = it->second;
		frame_info::ANGLES::iterator angle_it = temp_frame->angles.begin();
		bool check = true;
		for (; angle_it != temp_frame->angles.end(); angle_it++)			
		{
			angle_info info = *angle_it;
			XnSkeletonJointPosition joint1, joint2, joint3;
			g_UserGenerator.GetSkeletonCap().GetSkeletonJointPosition(user_id, info.pos1, joint1);
			g_UserGenerator.GetSkeletonCap().GetSkeletonJointPosition(user_id, info.pos2, joint2);
			g_UserGenerator.GetSkeletonCap().GetSkeletonJointPosition(user_id, info.pos3, joint3);	
			int temp_angle = getangleforposition(joint1.position, joint2.position, joint3.position);
			if (temp_angle >= info.angle_min && temp_angle <= info.angle_max)
			{

			}
			else
			{
				check = false;
				break;
			}

		}

		if (check)
		{
			temp_frames.push_back(temp_frame->frame_name);
		}
	}

	for (int i = 0; i < player_frames_temp->frames.size(); i ++)
	{
		bool miss = true;
		for (int j = 0; j < temp_frames.size(); j ++)
		{
			if (player_frames_temp->frames[i] == temp_frames[j])
			{
				miss = false;
				break;
			}
		}
		if (miss)
		{
			printf("miss userid[%d] frame_name[%s] \n", user_id, player_frames_temp->frames[i].c_str());
		}

	}

	for (int j = 0; j < temp_frames.size(); j ++)
	{
		bool new_add = true;
		for (int i = 0; i < player_frames_temp->frames.size(); i ++)
		{
			if (player_frames_temp->frames[i] == temp_frames[j])
			{
				new_add = false;
				break;
			}
		}
		if (new_add )
		{
			printf("new userid[%d] frame_name[%s] \n", user_id, temp_frames[j].c_str());
		}

	}
	player_frames_temp->frames = temp_frames;


}

bool action_storage::load_from_xml(const char* xml_file)
{
	bool ret = false;
	TiXmlDocument doc(xml_file);
	if (doc.LoadFile())
	{
		TiXmlNode* node_action =  doc.FirstChild("document");
		node_action = node_action->FirstChild("frame");
		for (TiXmlElement* node_element = node_action->FirstChildElement("info"); node_element != NULL; node_element = node_element->NextSiblingElement("info"))
		{
			frame_info* fram_info_temp = NULL;
			std::string frame_name = node_element->Attribute("name");
			FRAMES::iterator it = _frames.find(frame_name);
			if (it == _frames.end())
			{
				fram_info_temp = new frame_info();
				fram_info_temp->frame_name = frame_name;
				_frames.insert(FRAMES::value_type(frame_name, fram_info_temp));
			}
			else
			{
				fram_info_temp =  it->second;
			}

			for (TiXmlElement* node_angle = node_element->FirstChildElement("angle_info"); node_angle != NULL; node_angle = node_angle->NextSiblingElement("angle_info"))
			{
				angle_info angle_info_temp;
				angle_info_temp.pos1 =(XnSkeletonJoint) atoi(node_angle->Attribute("pos_type_1"));
				angle_info_temp.pos2 =(XnSkeletonJoint) atoi(node_angle->Attribute("pos_type_2"));
				angle_info_temp.pos3 = (XnSkeletonJoint)atoi(node_angle->Attribute("pos_type_3"));
				angle_info_temp.angle_min = atoi(node_angle->Attribute("angle_min"));
				angle_info_temp.angle_max = atoi(node_angle->Attribute("angle_max"));
				fram_info_temp->angles.push_back(angle_info_temp);
			}

		}
		ret = true;
	}
	
	return ret;
}


