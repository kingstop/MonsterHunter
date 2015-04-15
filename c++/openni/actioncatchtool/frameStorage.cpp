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

void frameStorage::save()
{
	FILE* fp = fopen("frame_storage", "wb+");
	if (fp)
	{
		int current = 0;
		char sztemp[256];
		fseek(fp,current,SEEK_SET);
		int count_temp = 0;
		int size_temp = sizeof(count_temp);
		count_temp = _frame_checks.size();

		fwrite(&count_temp, size_temp, 1, fp);
		current += size_temp;
		fseek(fp, current, SEEK_SET);
		if (count_temp > 0)
		{			
			FRAME_CHECKS::iterator it = _frame_checks.begin();
			for (int i = 0  ; i < count_temp; i ++, ++ it )
			{
				std::string frame_name = it->first;
				frame_check* temp_check = it->second;
				sprintf(sztemp, "%s", frame_name.c_str());
				size_temp = sizeof(sztemp);
				fwrite(sztemp, size_temp, 1, fp);	

				current += size_temp;
				fseek(fp,current,SEEK_SET);
				size_temp = sizeof(temp_check->right_temp);
				fread(&(temp_check->right_temp), size_temp, 1, fp);


				current += size_temp;
				fseek(fp,current,SEEK_SET);
				size_temp = sizeof(temp_check->bottom_temp);
				fread(&(temp_check->bottom_temp), size_temp, 1, fp);

				current += size_temp;
				fseek(fp, current, SEEK_SET);


				size_temp = sizeof(temp_check->frame_point);
				fwrite(temp_check->frame_point, size_temp, 1, fp);

				current += size_temp;
				fseek(fp, current, SEEK_SET);
				size_temp = sizeof(temp_check->frame_real_point);
				fwrite(temp_check->frame_real_point, size_temp, 1, fp);

				current += size_temp;
				fseek(fp, current, SEEK_SET);

				int coun_check_temp = temp_check->check_degrees.size();
				size_temp = sizeof(coun_check_temp);
				fwrite(&coun_check_temp, size_temp, 1, fp);

				current += size_temp;
				fseek(fp, current, SEEK_SET);
				if (coun_check_temp > 0)
				{
					CHECKDEGREES::iterator it_entry = temp_check->check_degrees.begin();

					for (int j = 0; j < coun_check_temp; j ++, ++ it_entry)
					{
						sprintf(sztemp, "%s", it_entry->first.c_str());
						size_temp = sizeof(sztemp);
						fwrite(sztemp, size_temp, 1, fp);

						current += size_temp;
						fseek(fp, current, SEEK_SET);

						check_degree temp_degree = it_entry->second;
						size_temp = sizeof(temp_degree.pos);
						fwrite(temp_degree.pos, size_temp, 1, fp);

						current += size_temp;
						fseek(fp, current, SEEK_SET);
						size_temp = sizeof(temp_degree.degree);
						fwrite(&(temp_degree.degree), size_temp, 1, fp);


						current += size_temp;
						fseek(fp,current,SEEK_SET);
						size_temp = sizeof(temp_degree.Recognize);
						fwrite(&(temp_degree.Recognize), size_temp, 1, fp);

						current += size_temp;
						fseek(fp,current,SEEK_SET);
					}
				}



			}


		}

		fclose(fp);



	}
}

void frameStorage::load()
{
	FILE* fp = fopen("frame_storage", "rb");
	if (fp)
	{
		long length=0;//声明文件长度

		fseek(fp,0,SEEK_END);//将文件内部指针放到文件最后面

		length=ftell(fp);//读取文件指针的位置，得到文件字符的个数
		

		if (length != 0)
		{
			char sztemp[256];
			int current = 0;
			int count_temp;
			fseek(fp,current,SEEK_SET);
			int size_temp = sizeof(count_temp);
			
			fread(&count_temp, size_temp, 1, fp);
			current += size_temp;
			fseek(fp,current,SEEK_SET);
			frame_check* temp_check = NULL;


			for (int i = 0; i < count_temp; i ++)
			{
				temp_check = new frame_check();
				size_temp = sizeof(sztemp);
				fread(sztemp, size_temp, 1, fp);				
				temp_check->frame_name = sztemp;

				current += size_temp;
				fseek(fp,current,SEEK_SET);
				size_temp = sizeof(temp_check->right_temp);
				fread(&(temp_check->right_temp), size_temp, 1, fp);


				current += size_temp;
				fseek(fp,current,SEEK_SET);
				size_temp = sizeof(temp_check->bottom_temp);
				fread(&(temp_check->bottom_temp), size_temp, 1, fp);



				current += size_temp;
				fseek(fp,current,SEEK_SET);
				size_temp = sizeof(temp_check->frame_point);
				fread(temp_check->frame_point, size_temp, 1, fp);

				current += size_temp;
				fseek(fp,current,SEEK_SET);
				size_temp = sizeof(temp_check->frame_real_point);
				fread(temp_check->frame_real_point, size_temp, 1, fp);

				int count_degrees;
				current += size_temp;
				fseek(fp,current,SEEK_SET);				
				size_temp = sizeof(count_degrees);
				fread(&count_degrees, size_temp, 1, fp);

				current += size_temp;
				fseek(fp,current,SEEK_SET);
				if (count_degrees > 0)
				{
					check_degree temp_degree;
					std::string temp_degree_name;


					for (int j = 0; j < count_degrees; j ++)
					{
						size_temp = sizeof(sztemp);
						fread(sztemp, size_temp, 1, fp);
						
						temp_degree_name = sztemp;

						current += size_temp;
						fseek(fp,current,SEEK_SET);
						
						size_temp = sizeof(temp_degree.pos);
						fread(temp_degree.pos, size_temp, 1, fp);

						current += size_temp;
						fseek(fp,current,SEEK_SET);

						size_temp = sizeof(temp_degree.degree);
						fread(&(temp_degree.degree), size_temp, 1, fp);


						current += size_temp;
						fseek(fp,current,SEEK_SET);


						size_temp = sizeof(temp_degree.Recognize);
						fread(&(temp_degree.Recognize), size_temp, 1, fp);

						current += size_temp;
						fseek(fp,current,SEEK_SET);

						temp_check->check_degrees.insert(CHECKDEGREES::value_type(temp_degree_name, temp_degree));
					}
				}
				_frame_checks.insert(FRAME_CHECKS::value_type(temp_check->frame_name, temp_check));
				on_add_frame(temp_check->frame_name.c_str());
				
			}			
		}
		fclose(fp);
	}
}


bool frameStorage::add_frame_check(const char* frame_name, XnVector3D temp_frame_point[XN_SKEL_MAX], XnVector3D temp_real_frame_point[XN_SKEL_MAX], 
	double right_temp, double bottom_temp)
{
	FRAME_CHECKS::iterator it = _frame_checks.find(frame_name);
	if (it != _frame_checks.end())
	{
		return false;
	}
	frame_check* framecheck = new frame_check();
	framecheck->frame_name = frame_name;
	for (int i = XN_SKEL_BEGIN; i < XN_SKEL_MAX; i ++)
	{
		framecheck->frame_point[i] = temp_frame_point[i];
		framecheck->frame_real_point[i] = temp_real_frame_point[i];

	}
	framecheck->right_temp = right_temp;
	framecheck->bottom_temp = bottom_temp;

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
		add_frame_check(save_temp_name, temp_data->frame_point, temp_data->frame_real_point, temp_data->right_temp, temp_data->bottom_temp);
		return true;	
	}
	return false;
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