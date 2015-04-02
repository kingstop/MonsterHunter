#pragma once
struct check_degree
{
	XnSkeletonJoint pos_1;
	XnSkeletonJoint pos_2;
	XnSkeletonJoint pos_3;
	int degree;
	int Recognize;
};
typedef std::vector<check_degree> CHECKDEGREES;
struct frame_check
{	
	XnVector3D frame_point[XN_SKEL_MAX];
	std::string frame_name;
	CHECKDEGREES check_degrees;
};
class frameStorage
{
public:
	typedef std::map<std::string, frame_check*> FRAME_CHECKS;
public:
	frameStorage(void);
	~frameStorage(void);
public:
	bool add_frame_check(const char* frame_name, XnVector3D temp_frame_point[XN_SKEL_MAX]);
	bool modify_frame(const char* frame_name, CHECKDEGREES& temp_check_degrees);
	bool add_cur_sel(const char* save_temp_name);


protected:
	FRAME_CHECKS _frame_checks;

};

