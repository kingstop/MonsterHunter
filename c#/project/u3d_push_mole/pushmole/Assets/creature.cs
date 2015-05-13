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
        GameObject obj_1 = GameObject.Instantiate<GameObject>(Resources.Load<GameObject>("prefab/character/model/zippermouth_a_PF"));
        _moles.Add(creature_type.creature_1, obj_1);

        GameObject obj_2 = GameObject.Instantiate<GameObject>(Resources.Load<GameObject>("prefab/character/model/zippermouth_b_PF"));
        _moles.Add(creature_type.creature_1, obj_2);

        GameObject obj_3 = GameObject.Instantiate<GameObject>(Resources.Load<GameObject>("prefab/character/model/zippermouth_c_PF"));
        _moles.Add(creature_type.creature_1, obj_3);

    }

    public void set_position(float x, float y, float z)
    {

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

}
