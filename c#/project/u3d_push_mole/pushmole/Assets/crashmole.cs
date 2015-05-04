using UnityEngine;
using System.Collections;
public enum dir_move
{
    left,
    right,
    back,
    front,
    down,
    up,

}

public struct crash_pos
{
    public int _x;
    public int _y;
    public int _z;
    public void move(dir_move dir)
    {
        switch (dir)
        {
            case dir_move.back:
                {
                    _z = _z + 1;
                }
                break;
            case dir_move.front:
                {
                    _z = _z - 1;
                }
                break;
            case dir_move.down:
                {
                    _y = _y - 1;
                }
                break;
            case dir_move.up:
                {
                    _y = _y + 1;
                }
                break;
            case dir_move.left:
                {
                    _x = _x - 1;
                }
                break;
            case dir_move.right:
                {
                    _x = _x + 1;
                }
                break;

        }
    }

}

public class crash_obj
{

    public crash_obj()
    {
        _pos._x = 0;
        _pos._y = 0;
        _pos._z = 0;
        _target_pos = _pos;
    }
    public crash_obj(int x, int y, int z)
    {
        _pos._x = x;
        _pos._y = y;
        _pos._z = z;
        _target_pos = _pos;
    }

    public void on_remove()
    {
       
    }
   
    public crash_pos _pos = new crash_pos();
    public crash_pos _target_pos = new crash_pos();
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


enum crash_define{
    max_x = 18,
    max_z = 18,
    max_y = 80

}
public class crash_manager
{
    bool[, ,] _can_move_locks = new bool[(int)crash_define.max_x, (int)crash_define.max_z, (int)crash_define.max_y];
    crash_obj_addr[, ,] _crash_objs = new crash_obj_addr[(int)crash_define.max_x, (int)crash_define.max_z ,(int)crash_define.max_y];
    crash_mole_addr[, ,] _crash_moles = new crash_mole_addr[(int)crash_define.max_x, (int)crash_define.max_z, (int)crash_define.max_y];
    public ArrayList _crash_moles_list = new ArrayList();
    public ArrayList _move_mole_list = new ArrayList();
    public int _check_fall_y;
    public crash_manager()
    {
        
    }

    public void create_map()
    {
        for (int x = 0; x < (int)crash_define.max_x; x++)
        {

            for (int z = 0; z < (int)crash_define.max_z; z++)
            {
                for(int y = 0; y < (int)crash_define.max_y; )
            }
        }
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

    public bool check_pos_valid(crash_pos pos)
    {
        if (pos._x < 0 || pos._y < 0 || pos._z < 0)
        {
            return false;
        }

        if (pos._x >= (int)crash_define.max_x || pos._y >= (int)crash_define.max_y || pos._z >= (int)crash_define.max_z)
        {
            return false;
        }
        return true;
    }
    public bool move(int x, int y, int z, dir_move dir)
    {
        _check_fall_y = (int)crash_define.max_y;
        _move_mole_list.Clear();

        crash_mole entry = get_crash_mole_addr(x, z, y)._crash_mole;
        if (entry == null)
        {
            return false;
        }
        _move_mole_list.Add(entry);
        bool b_temp = move(entry, dir);
        if (b_temp)
        {
            int temp_count = _move_mole_list.Count;
            for (int j = 0; j < temp_count; j++)
            {

            }

            if (dir != dir_move.down && dir != dir_move.up)
            {

            }
            else
            {

            }
        }
        else
        {
            _check_fall_y = (int)crash_define.max_y;
        }

        return b_temp;

    }

    public bool need_fall_update()
    {
        int current_count = _crash_moles_list.Count;
        crash_pos temp_pos = new crash_pos();
        bool can_fall_temp = true;
        for (int i = 0; i < current_count; i++)
        {
            can_fall_temp = true;
            crash_mole mole_entry = (crash_mole)_crash_moles_list[i];
            int obj_count = mole_entry._crash_objs.Count;
            for (int j = 0; j < obj_count; j++)
            {

                crash_obj obj_entry = (crash_obj)mole_entry._crash_objs[j];
                temp_pos._x = obj_entry._pos._x;
                temp_pos._y = obj_entry._pos._y - 1;
                temp_pos._z = obj_entry._pos._z;
                if (check_pos_valid(temp_pos))
                {
                    if (get_crash_mole_addr(temp_pos)._crash_mole != null)
                    {
                        if (get_crash_mole_addr(temp_pos)._crash_mole == mole_entry)
                        {
                            continue;
                        }
                        else
                        {
                            can_fall_temp = false;
                            break;
                        }
                    }                                        
                }
                else
                {
                    can_fall_temp =  false;
                    break;
                }

                if (can_fall_temp == false)
                {
                    break;
                }
            }


        }
        return can_fall_temp;
    }

    protected bool move(crash_mole mole, dir_move dir)
    {
        int min_move_y = (int)crash_define.max_y;
        foreach (crash_obj entry in mole._crash_objs)
        {
            crash_pos pos_temp = new crash_pos();
            pos_temp = entry._pos;
            if (min_move_y > pos_temp._y)
            {
                min_move_y = pos_temp._y;
            }
            pos_temp.move(dir);
            if (check_pos_valid(pos_temp))
            {
                crash_mole mole_entry = get_crash_mole_addr(pos_temp)._crash_mole;
                if (mole_entry != null)
                {
                    int length = _move_mole_list.Count;
                    for (int i = 0; i < length; i++)
                    {
                        if (mole == (crash_mole)_move_mole_list[i])
                        {
                            if (_check_fall_y > min_move_y)
                            {
                                _check_fall_y = min_move_y;
                            }
                            return true;
                        }

                    }
                    _move_mole_list.Add(mole_entry);
                    if (move(mole_entry, dir) == false)
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
        if (_check_fall_y > min_move_y)
        {
            _check_fall_y = min_move_y;
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