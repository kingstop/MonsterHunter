#pragma once
#include <XnOpenNI.h>
#include <vector>
#include <map>
#include <iostream>
#include <string>

struct angle_info{
	XnSkeletonJoint pos1;
	XnSkeletonJoint pos2;
	XnSkeletonJoint pos3;
	int angle_min;
	int angle_max;
};

struct frame_info{
	typedef std::vector<angle_info> ANGLES;
	std::string frame_name;
	ANGLES angles;
};

struct player_frames{
	int player_id;
	std::vector<std::string> frames;
};
class action_storage
{
public:
	typedef std::map<std::string, frame_info*> FRAMES;
	typedef std::map<int,player_frames*> PLAERS_FRAME;
public:
	action_storage(void);
	~action_storage(void);
	bool load_from_xml(const char* xml_file);

	void frame_check(int user_id);
protected:
	FRAMES _frames;
	PLAERS_FRAME _players_frames;



	
};

