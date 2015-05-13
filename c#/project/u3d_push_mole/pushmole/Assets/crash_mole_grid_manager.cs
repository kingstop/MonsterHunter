using UnityEngine;
using System.Collections;


public class crash_mole_grid_manager : MonoBehaviour {
    GameObject _source_crash_mole_obj;
    crashmolegrid[,] _crashmolegrids = new crashmolegrid[18, 60];
    ArrayList _objlist = new ArrayList();
    //prush_mo
    public void update_game_type(game_type type)
    {
        switch (type)
        {
            case game_type.edit:
                {
                    global_instance.Instance._crash_manager.clear();
                    create_edit_crash_mole_grid();

                }
                break;
            case game_type.game:
                {
                    create_map();
                    clear_eadit_crash_mole_grid();
                    global_instance.Instance._crash_manager.create_map();
                }
                break;
        }
    }
    public void clear_eadit_crash_mole_grid()
    {
        for (int i = 0; i < 18; i++)
        {
            for (int j = 0; j < 60; j++)
            {
                _crashmolegrids[i, j] = null;                
            }

        }
        int length = _objlist.Count;
        for (int i = 0; i < length; i++)
        {
            GameObject entry_obj = (GameObject)_objlist[i];
            Destroy(entry_obj);
        }
        _objlist.Clear();
    }

    public void create_edit_crash_mole_grid()
    {
        Vector3 new_position = new Vector3((float)7.7, (float)4.7, (float)-10.6);
        Camera.main.transform.position = new_position;
        _source_crash_mole_obj = Resources.Load<GameObject>("prefab/mole_object");
        for (int i = 0; i < 18; i++)
        {
            for (int j = 0; j < 60; j++)
            {

                GameObject obj_temp = Instantiate<GameObject>(_source_crash_mole_obj);
                _objlist.Add(obj_temp);

                obj_temp.name = i.ToString() + "-" + j.ToString();
                _crashmolegrids[i, j] = obj_temp.GetComponent<crashmolegrid>();
                float x = (float)i + (float)(i * 0.022);
                float y = (float)j + (float)(j * 0.022);

                _crashmolegrids[i, j].set_position(x, y);
                _crashmolegrids[i, j].set_color(1, 1, 1, 1);
                _crashmolegrids[i, j].set_group(11);
            }
        }          
    }

    void Awake()
    {
        global_instance.Instance._crash_mole_grid_manager = this;
    }
	// Use this for initialization
	void Start () {
        
      //  create_edit_crash_mole_grid();

       
	}
    void OnMouseDown()
    {
        RaycastHit hitt = new RaycastHit();
        Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition);

        Physics.Raycast(ray, out hitt, 100);

        Debug.DrawLine(Camera.main.transform.position, ray.direction, Color.green);

        if (null != hitt.transform)
        {
            crashmolegrid grid_temp = hitt.transform.gameObject.GetComponent<crashmolegrid>();
            grid_temp.set_color(global_instance.Instance._current_color);
            grid_temp.set_group(global_instance.Instance._current_group);
            print("name[" + hitt.transform.gameObject.name + "] color[" + global_instance.Instance._current_color.ToString() + "]");
            global_instance.Instance._crash_manager.add_color(global_instance.Instance._current_group, global_instance.Instance._current_color);
            print(hitt.point);//鼠标点击的坐标

        }
    }
    public void create_map( )
    {
        for (int i = 0; i < 18; i++)
        {
            for (int j = 0; j < 60; j++)
            {
                int i_temp = i - 1;
                int group_1 = 11;
                int group_2 = 11;
                if (i_temp >= 0)
                {
                    group_1 = _crashmolegrids[i_temp, j]._group;
                }
                int j_temp = j - 1;
                if (j_temp >= 0)
                {
                    group_2 = _crashmolegrids[i, j_temp]._group;
                }
                int group = _crashmolegrids[i, j]._group;
                //Color color = _crashmolegrids[i, j].get_color();
                if(group != 11)
                {
                    crash_obj obj = global_instance.Instance._crash_manager.create_crash_obj(i, j + 20);
                    crash_mole mole_entry = null;
                    if (group == group_1 || group == group_2)
                    {
                        if (group == group_1 && group == group_2)
                        {
                            mole_entry = global_instance.Instance._crash_manager.get_crash_mole_addr(i_temp, 9, j + 20)._crash_mole;                            
                        }
                        else if (group == group_1)
                        {
                            mole_entry = global_instance.Instance._crash_manager.get_crash_mole_addr(i_temp, 9, j + 20)._crash_mole;
                        }
                        else if (group == group_2)
                        {
                            mole_entry = global_instance.Instance._crash_manager.get_crash_mole_addr(i, 9, j_temp + 20)._crash_mole;
                        }
                        if(mole_entry == null)
                        {
                            Debug.Log("mole_entry == null");
                        }
                        else
                        {
                            mole_entry.add_crash_obj(obj);
                        }
                        
                    }
                    else
                    {
                        mole_entry = global_instance.Instance._crash_manager.create_crash_mole();                 
                        mole_entry.add_crash_obj(obj);
                        mole_entry._color_group = group;
                        global_instance.Instance._crash_manager.add_crash_mole(mole_entry);
                    }

                }
                

            }
        }
    }
	// Update is called once per frame
	void Update () {
        global_instance.Instance._crash_manager.update_move_animation();
        //RaycastHit hitt = new RaycastHit();
        //Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition);

        //Physics.Raycast(ray, out hitt, 100);

        //Debug.DrawLine(Camera.main.transform.position, ray.direction, Color.green);

        //if (null != hitt.transform)
        //{
        //    print(hitt.transform.gameObject.name);

        //    print(hitt.point);//鼠标点击的坐标

        //}

        //if (Input.touchCount > 0)
        //{
        //    Touch th = Input.GetTouch(0);//
        //    if (th.phase == TouchPhase.Began)
        //    {
        //        Ray ray = Camera.main.ScreenPointToRay(th.position);//射线从这里生成
        //        RaycastHit hit;//这个是碰撞检测的目标
        //        if (Physics.Raycast(ray, out hit, 500))//传入的参数依次是：射线、射线碰撞物、射线检测距离
        //        {
        //            GameObject obj = hit.transform.gameObject;//看到这里应该明白了吧~
        //            crashmolegrid crash_mole_grid = obj.GetComponent<crashmolegrid>();
        //            if (crash_mole_grid != null)
        //            {
        //                Debug.Log("click crash_mole_grid");
        //            }
        //            else
        //            {
        //                Debug.Log("click not crash_mole_grid");
        //            }

        //        }
        //    }
        //}
	}
}
