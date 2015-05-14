using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public enum creature_type
{
    creature_1,
    creature_2,
    creature_3
}
public class creature {
    Dictionary<creature_type, GameObject> _moles = new Dictionary<creature_type, GameObject>();
    public creature()
    {
        GameObject obj_1 = GameObject.Instantiate<GameObject>(Resources.Load<GameObject>("character/model/zippermouth_a_PF"));
        _moles.Add(creature_type.creature_1, obj_1);

        GameObject obj_2 = GameObject.Instantiate<GameObject>(Resources.Load<GameObject>("character/model/zippermouth_b_PF"));
        _moles.Add(creature_type.creature_2, obj_2);

        GameObject obj_3 = GameObject.Instantiate<GameObject>(Resources.Load<GameObject>("character/model/zippermouth_c_PF"));
        _moles.Add(creature_type.creature_3, obj_3);

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
        _current_position.y = y;
        _current_position.z = z;
        
        foreach (var entry in _moles)
        {
            GameObject obj_entry = entry.Value;
            obj_entry.transform.position = _current_position;
        }
    }

    public void set_dir(dir_move dir)
    {
        _dir = dir;
        float y_r = 0.0f;
        switch(dir)
        {
            case dir_move.back:
                {
                    y_r = 340;
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

        foreach (var entry in _moles)
        {
            GameObject obj_entry = entry.Value;
            obj_entry.transform.rotation.SetEulerRotation(obj_entry.transform.rotation.x, y_r, obj_entry.transform.rotation.z);

        }
    }

    public void set_creature_type(creature_type type)
    {
        _cureent_type = type;
        foreach(var entry in _moles)
        {
            GameObject obj_entry = entry.Value;
            if(entry.Key == _cureent_type)
            {
                obj_entry.transform.localScale = new Vector3(1, 1, 1);                
            }
            else
            {
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

}
