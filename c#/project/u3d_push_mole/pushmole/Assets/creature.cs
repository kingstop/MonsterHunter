﻿using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public enum creature_type
{
    creature_1,
    creature_2,
    creature_3
}

public enum creature_state
{
    idle,
    run,
    wound,
    special
}
public class creature {
    Dictionary<creature_type, GameObject> _moles = new Dictionary<creature_type, GameObject>();
    List<GameObject> _moles_list = new List<GameObject>();
    GameObject _creature_physics = null;
    Rigidbody _Rigidbody = null;

    public creature()
    {
        _creature_physics = GameObject.Instantiate<GameObject>(Resources.Load<GameObject>("prefab/creature_physics"));
        GameObject obj_1 = GameObject.Instantiate<GameObject>(Resources.Load<GameObject>("character/model/zippermouth_a_PF"));
        _moles.Add(creature_type.creature_1, obj_1);

        GameObject obj_2 = GameObject.Instantiate<GameObject>(Resources.Load<GameObject>("character/model/zippermouth_b_PF"));
        _moles.Add(creature_type.creature_2, obj_2);

        GameObject obj_3 = GameObject.Instantiate<GameObject>(Resources.Load<GameObject>("character/model/zippermouth_c_PF"));
        _moles.Add(creature_type.creature_3, obj_3);
        _state = creature_state.idle;
        play_idle();
        set_dir(dir_move.front);
        _moles_list.Add(obj_1);
        _moles_list.Add(obj_2);
        _moles_list.Add(obj_3);
        _Rigidbody = _creature_physics.GetComponent<Rigidbody>();

    }

    public void Destroy()
    {
        foreach (var entry in _moles)
        {
            GameObject obj_entry = entry.Value;
            GameObject.Destroy(obj_entry);
        }
    }

    public void set_position(float x, float y, float z)
    {
        _current_position.x = x;
        _current_position.y = y - 0.7f;
        _current_position.z = z;
        
        foreach (var entry in _moles)
        {
            GameObject obj_entry = entry.Value;
            obj_entry.transform.position = _current_position;
        }
        _creature_physics.transform.position = _current_position;
    }

    public Vector3 get_position()
    {
        Vector3 vec = new Vector3();
        vec = _current_position;
        vec.y += 0.7f;
        return vec;
    }

    
    public void set_state(creature_state state)
    {
        if(state != _state)
        {
            switch(state)
            {
                case creature_state.idle:
                    {
                        play_idle();
                    }
                    break;
                case creature_state.run:
                    {
                        play_run();
                    }
                    break;
                case creature_state.special:
                    {
                        play_special();
                    }
                    break;
                case creature_state.wound:
                    {
                        play_wound();
                    }
                    break;
            }
        }

    }
    public void set_dir(dir_move dir)
    {
        if(_dir != dir)
        {
            float y_r = 0.0f;
            switch (dir)
            {
                case dir_move.back:
                    {
                        y_r = 333;
                    }
                    break;
                case dir_move.front:
                    {
                        y_r = 160;
                    }
                    break;
                case dir_move.right:
                    {
                        y_r = 70;
                    }
                    break;
                case dir_move.left:
                    {
                        y_r = 250;
                    }
                    break;
            }

            int length = _moles_list.Count;
            for (int i = 0; i < length; i ++ )
            {
                Vector3 vc = new Vector3();
                vc = _moles_list[i].transform.rotation.ToEulerAngles();
                vc.y = y_r;
                Quaternion a_temp = _moles_list[i].transform.rotation;
                a_temp.SetEulerAngles(vc);
                _moles_list[i].transform.rotation = a_temp;
                
            }
           

        }
        _dir = dir;

    }

    public void set_creature_type(creature_type type)
    {
        _cureent_type = type;
        foreach(var entry in _moles)
        {
            GameObject obj_entry = entry.Value;
            if(entry.Key == _cureent_type)
            {
                obj_entry.transform.localScale = new Vector3(0.5f, 0.5f, 0.5f);
                obj_entry.SetActive(true);
            }
            else
            {
                obj_entry.SetActive(false);
                obj_entry.transform.localScale = new Vector3(0, 0, 0);
            }
        }
    }

    public void play_idle()
    {
        play_animation("idle");
    }

    public void play_run()
    {
        play_animation("run");
    }

    public void play_attack()
    {
        play_animation("attack");
    }

    public void play_special()
    {
        play_animation("special");
    }

    public void play_wound()
    {
        play_animation("wound");
    }

    protected void play_animation(string temp_name)
    {
        foreach (var entry in _moles)
        {
            GameObject obj_entry = entry.Value;
            obj_entry.GetComponent<Animation>().Play(temp_name);
        }
    }


    protected creature_type _cureent_type;
    protected Vector3 _current_position = new Vector3();
    protected dir_move _dir;
    protected creature_state _state;

}
