using UnityEngine;
using System.Collections;

public struct crash_pos
{
    public int _x;
    public int _y;
    public int _z;
}

public class crash_obj
{

    public crash_obj()
    {
        _pos._x = 0;
        _pos._y = 0;
        _pos._z = 0;
    }
    public crash_obj(int x, int y, int z)
    {
        _pos._x = x;
        _pos._y = y;
        _pos._z = z;
    }

    public void on_remove()
    {
       
    }
   
    public crash_pos _pos = new crash_pos();

    crash_manager _manager;
}


public class crash_mole
{
    public crash_mole()
    {

    }
    void add_crash_obj(crash_obj obj_entry)
    {
        _crash_objs.Add(obj_entry);
    }

    public ArrayList _crash_objs = new ArrayList();


}


public class crash_obj_addr
{
    public crash_obj _crash_obj = null;
}

public class crash_mole_addr
{
    public crash_mole _crash_mole = null;
}

enum crash_define{
    max_x = 18,
    max_z = 18,
    max_y = 80

}
public class crash_manager
{

    crash_obj_addr[, ,] _crash_objs = new crash_obj_addr[(int)crash_define.max_x, (int)crash_define.max_z ,(int)crash_define.max_y];
    crash_mole_addr[, ,] _crash_moles = new crash_mole_addr[(int)crash_define.max_x, (int)crash_define.max_z, (int)crash_define.max_y];
    public ArrayList _crash_moles_list = new ArrayList();
    public crash_manager()
    {
        
    }

    public bool can_fall()
    {
        int temp_count = _crash_moles_list.Count;
        for (int i = 0; i < temp_count; i ++)
        {

        }
        return true;
    }

    public bool can_fall(crash_mole mole_entry)
    {
        int count_temp = mole_entry._crash_objs.Count;
        for (int i = 0; i < count_temp; i++)
        {
            crash_obj obj_entry = (crash_obj)mole_entry._crash_objs[i];
            if (obj_entry._pos._y > 0)
            {
                if (get_crash_mole_addr(obj_entry._pos._x, obj_entry._pos._z, obj_entry._pos._y - 1)._crash_mole != mole_entry)
                {
                    if (get_crash_mole_addr(obj_entry._pos._x, obj_entry._pos._z, obj_entry._pos._y - 1)._crash_mole != null)
                    {
                        return false;
                    }
                }                
            }
            else
            {
                return false;
            }

        }
        return true;
    }

    public crash_obj_addr get_crash_obj_addr(int x, int z, int y)
    {
        return _crash_objs[x, y, z];
    }


    public crash_mole_addr get_crash_mole_addr(int x, int z, int y)
    {
        return _crash_moles[x, z, y];
    }


    public crash_obj_addr get_crash_obj_addr(crash_pos pos)
    {
        return _crash_objs[pos._x, pos._z, pos._y];
    }

    public crash_mole_addr get_crash_mole_addr(crash_pos pos)
    {
        return _crash_moles[pos._x, pos._z, pos._y];
    }

    public bool add_crash_obj(crash_obj obj_temp)
    {
        if (isEmpty(obj_temp))
        {
            _crash_objs[obj_temp._pos._x, obj_temp._pos._z, obj_temp._pos._y]._crash_obj = obj_temp;
            return true;
        }
        else
        {
            return false;
        }
    }

    public bool add_crash_mole(crash_mole obj_temp)
    {
        if (isEmpty(obj_temp) == true)
        {
            int count_temp = obj_temp._crash_objs.Count;
            for (int i = 0; i < count_temp; i++)
            {
                crash_pos pos = ((crash_obj)obj_temp._crash_objs[i])._pos;

                _crash_moles[pos._x, pos._z, pos._y]._crash_mole = obj_temp;

            }

            _crash_moles_list.Add(obj_temp);
            return true;
        }
        return false;
    }

    private bool isEmpty(crash_mole obj_temp)
    {
        int count_temp = obj_temp._crash_objs.Count;
        for (int i = 0; i < count_temp; i++)
        {
            if (isEmpty(((crash_obj)obj_temp._crash_objs[i])) == false)
            {
                return false;
            }                        
        }
        return true;        
    }
    private bool isEmpty(crash_obj obj_temp)
    {
        if (_crash_objs[obj_temp._pos._x, obj_temp._pos._z, obj_temp._pos._y]._crash_obj == null)
        {
            return true;
        }
        return false;
    }

}