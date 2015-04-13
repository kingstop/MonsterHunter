#pragma once

extern std::string pos_name_config[XN_SKEL_MAX];
std::string mk_degree_title(XnSkeletonJoint pos_1, XnSkeletonJoint pos_2, XnSkeletonJoint pos_3);


struct check_degree
{
	XnSkeletonJoint pos[3];
	int degree;
	int Recognize;
};
typedef std::map<std::string, check_degree> CHECKDEGREES;
struct frame_check
{	
	XnVector3D frame_point[XN_SKEL_MAX];
	XnVector3D frame_real_point[XN_SKEL_MAX];
	std::string frame_name;
	CHECKDEGREES check_degrees;
};

int getangleforposition(XnVector3D position_1, XnVector3D position_2, XnVector3D position_3);
class frameStorage
{
public:
	typedef std::map<std::string, frame_check*> FRAME_CHECKS;
public:
	frameStorage(void);
	~frameStorage(void);
public:
	void load();
	void save();
	bool add_frame_check(const char* frame_name, XnVector3D temp_frame_point[XN_SKEL_MAX], XnVector3D temp_real_frame_point[XN_SKEL_MAX]);
	bool modify_frame(const char* frame_name, CHECKDEGREES& temp_check_degrees);
	bool add_cur_sel(const char* save_temp_name);

	frame_check* get_frame_check(const char* frame_name);

	void on_add_frame(const char* save_temp_name);
public:
	std::string _cur_sel;






protected:
	FRAME_CHECKS _frame_checks;

};

