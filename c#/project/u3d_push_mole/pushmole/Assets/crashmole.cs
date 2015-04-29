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
}


public class crash_mole
{
    public crash_mole()
    {

    }
    public bool add_crash_obj(crash_obj obj_entry)
    {
        foreach (crash_obj enry in _crash_objs)
        {
            if(obj_entry._pos._x == enry._pos._x &&
                obj_entry._pos._y == enry._pos._y &&
                obj_entry._pos._z == enry._pos._z)
            {
                return false;
            }
        }
        if (_crash_manager.get_crash_obj_addr(obj_entry._pos)._crash_obj != null)
        {
            return false;
        }

        add_crash_obj(obj_entry);
        _crash_objs.Add(obj_entry);
        return true;
    }

    public ArrayList _crash_objs = new ArrayList();

    public crash_manager _crash_manager;
    public float _r;
    public float _g;
    public float _b;
}


public class crash_obj_addr
{
    public crash_obj _crash_obj = null;
}

public class crash_mole_addr
{
    public crash_mole _crash_mole = null;
}

public enum dir_move
{
    left,
    right,
    back,
    front,
    down,
    up,

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
    public ArrayList _move_mole_list = new ArrayList();
    public crash_manager()
    {
        
    }

    public crash_obj create_crash_obj(int x, int y)
    {
        crash_obj obj = new crash_obj();
        obj._pos._x = x;
        obj._pos._y = y;
        obj._pos._z = 9;
        //add_crash_obj(obj);
        return obj;
    }

    public crash_mole create_crash_mole()
    {
        crash_mole mole_entry = new crash_mole();
        mole_entry._crash_manager = this;
        return mole_entry;
    }


    public bool move(crash_mole mole, dir_move dir)
    {
        int length = _move_mole_list.Count;
        for (int i = 0; i < length; i++)
        {
            if (mole == (crash_mole)_move_mole_list[i])
            {
                return true;
            }
            
        }

        foreach (crash_obj entry in mole._crash_objs)
        {
            switch (dir)
            {
                case dir_move.left:
                    {

                    }
                    break;
                case dir_move.right:
                    {

                    }
                    break;
                case dir_move.back:
                    {

                    }
                    break;
                case dir_move.front:
                    {

                    }
                    break;
                case dir_move.down:
                    {

                    }
                    break;
                case dir_move.up:
                    {

                    }
                    break;
            }
        }


    }

    public bool move_left(crash_mole mole)
    {
        if (can_move_left(mole))
        {

        }
        return true;
    }

    public bool can_fall()
    {
        int temp_count = _crash_moles_list.Count;
        for (int i = 0; i < temp_count; i ++)
        {
            crash_mole mole_entry = (crash_mole)_crash_moles_list[i];
            if (can_fall(mole_entry))
            {
                return true;
            }
        }
        return false;
    }

    public bool can_move(crash_mole mole_entry, int move_x, int move_z)
    {
        int count_temp = mole_entry._crash_objs.Count;
        for (int i = 0; i < count_temp; i++)
        {
            crash_obj obj_entry = (crash_obj)mole_entry._crash_objs[i];
            int target_x = obj_entry._pos._x + move_x;
            int target_z = obj_entry._pos._z + move_z;
            if (target_x < 0 || target_z < 0 || target_x >= (int)crash_define.max_x || target_z >= (int)crash_define.max_z)
            {
                return false;
            }
            if (get_crash_mole_addr(obj_entry._pos._x, obj_entry._pos._z, obj_entry._pos._y - 1)._crash_mole != null)
            {
                return false;
            }
        }
        return true;
    }

    public bool can_move_left(crash_mole mole_entry)
    {
        if (can_move(mole_entry, -1, 0))
        {
            return true;
        }
        return false;

    }

    public bool can_move_right(crash_mole mole_entry)
    {

        if (can_move(mole_entry, 1, 0))
        {
            return true;
        }
        return false;
    }

    public bool can_move_back(crash_mole mole_entry)
    {

        if (can_move(mole_entry, 0, 1))
        {
            return true;
        }
        return false;
    }

    public bool can_move_front(crash_mole mole_entry)
    {

        if (can_move(mole_entry, 0, -1))
        {
            return true;
        }
        return false;
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
        int count_temp = obj_temp._crash_objs.Count;
        for (int i = 0; i < count_temp; i++)
        {
            crash_pos pos = ((crash_obj)obj_temp._crash_objs[i])._pos;
            //add_crash_obj((crash_obj)obj_temp._crash_objs[i]);
            _crash_moles[pos._x, pos._z, pos._y]._crash_mole = obj_temp;

        }

        _crash_moles_list.Add(obj_temp);
        return true;
       
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