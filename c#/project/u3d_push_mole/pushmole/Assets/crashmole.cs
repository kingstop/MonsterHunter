using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public enum crash_obj_type
{
    normal,
    player,
    target
}
public enum game_type
{
    edit,
    game,
    max
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

public class crash_base_obj
{
    public crash_base_obj()
    {
        _pos._x = 0;
        _pos._y = 0;
        _pos._z = 0;
        _last_pos = _pos;


    }
    public crash_base_obj(int x, int y, int z)
    {
        _pos._x = x;
        _pos._y = y;
        _pos._z = z;
        _last_pos = _pos;
    }
    public virtual  void set_position(float x, float y)
    {

    }

    public virtual  void set_position(float x, float y, float z)
    {

    }

    public crash_obj_type get_obj_type()
    {
        return _type;
    }


    public crash_pos _pos = new crash_pos();
    public crash_pos _last_pos = new crash_pos();
    public crash_mole _crash_mole;
    protected crash_obj_type _type;

}

public class crash_obj_creature : crash_base_obj
{
    public crash_obj_creature()
        : base()
    {
        _type = crash_obj_type.player;
    }
    public crash_obj_creature(int x, int y, int z)
        : base(x, y, z)
    {
        _type = crash_obj_type.player;
    }

}
public class crash_obj : crash_base_obj
{

    public crash_obj() : base()
    {
        _type = crash_obj_type.normal;

    }
    public crash_obj(int x, int y, int z) :base(x, y, z)
    {
        _type = crash_obj_type.normal;
    }



    public override void set_position(float x, float y)
    {
        _grid.set_position(x, y);
    }

    public override void set_position(float x, float y, float z)
    {
        _grid.set_position(x, y, z);
    }
    public crashmolegrid _grid;
 

}


public class crash_mole
{
    public crash_mole()
    {

    }

    public bool add_crash_obj(crash_base_obj obj_entry)
    {
        foreach (crash_base_obj enry in _crash_objs)
        {
            if(obj_entry._pos._x == enry._pos._x &&
                obj_entry._pos._y == enry._pos._y &&
                obj_entry._pos._z == enry._pos._z)
            {
                return false;
            }
        }
        crash_obj_addr obj_addr = _crash_manager.get_crash_obj_addr(obj_entry._pos);
        if(obj_addr == null)
        {
            return false;
        }

        if (_crash_manager.get_crash_obj_addr(obj_entry._pos)._crash_obj != null)
        {
            return false;
        }

       // add_crash_obj(obj_entry);
        obj_entry._crash_mole = this;
       
        _crash_objs.Add(obj_entry);
        _crash_manager._crash_objs[obj_entry._pos._x, obj_entry._pos._z, obj_entry._pos._y]._crash_obj = obj_entry;
        _crash_manager._crash_moles[obj_entry._pos._x, obj_entry._pos._z, obj_entry._pos._y]._crash_mole = this;
        return true;
    }

    public ArrayList _crash_objs = new ArrayList();

    public crash_manager _crash_manager;
    public int _color_group;
}


public class crash_obj_addr
{
    public crash_base_obj _crash_obj = null;
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
    public Dictionary<int, Color> _group_colors = new Dictionary<int, Color>();
    bool[, ,] _can_move_locks = new bool[(int)crash_define.max_x, (int)crash_define.max_z, (int)crash_define.max_y];
    public crash_obj_addr[, ,] _crash_objs = new crash_obj_addr[(int)crash_define.max_x, (int)crash_define.max_z, (int)crash_define.max_y];
    public crash_mole_addr[, ,] _crash_moles = new crash_mole_addr[(int)crash_define.max_x, (int)crash_define.max_z, (int)crash_define.max_y];
    public List<crash_mole> _crash_moles_list = new List<crash_mole>();
    public List<crash_mole> _move_mole_list = new List<crash_mole>();
    
    public float _grid_distance;
    public float _current_move_distance;
    public float _move_animation_distance;
    public bool _need_play_animation;
    dir_move _last_move_dir;
    GameObject _source_crash_mole_obj;
    protected ArrayList _Game_objs = new ArrayList();
    public int _use_count = 0;
    public void add_color(int group, Color temp_color)
    {
        if (_group_colors.ContainsKey(group) == false)
        {
            _group_colors.Add(group, temp_color);
        }
        
    }
    public crash_manager()
    {
        _source_crash_mole_obj = Resources.Load<GameObject>("prefab/mole_object");

        for (int x = 0; x < (int)crash_define.max_x; x ++)
        {
            for(int y = 0; y < (int)crash_define.max_y; y ++)
            {
                for(int z = 0; z < (int)crash_define.max_z; z ++)
                {
                    _crash_objs[x, z, y] = new crash_obj_addr();
                    _crash_moles[x, z, y] = new crash_mole_addr();
                }
            }
        }

    }

    public void clear()
    {
        for (int x = 0; x < (int)crash_define.max_x; x++)
        {
            for (int y = 0; y < (int)crash_define.max_y; y++)
            {
                for (int z = 0; z < (int)crash_define.max_z; z++)
                {
                    _crash_objs[x, z, y]._crash_obj = null;
                    _crash_moles[x, z, y]._crash_mole = null;
                }
            }
        }

        _grid_distance = (float)1.022;
        
        _need_play_animation = false;
        _move_animation_distance = (float)0.05;
        int length = _Game_objs.Count;
        for(int i = 0; i < length; i ++)
        {
            GameObject obj = (GameObject)_Game_objs[i];
            GameObject.Destroy(obj);            
        }
        _crash_moles_list.Clear();
        _move_mole_list.Clear();
        _Game_objs.Clear();
    }
    public void update_move_animation()
    {
        if (_need_play_animation)
        {
            bool last_move = false;
            float move_distance = _current_move_distance + _move_animation_distance;
            if (move_distance >= _grid_distance)
            {
                last_move = true;
                _current_move_distance = _grid_distance;
            }
            else
            {
                _current_move_distance = move_distance;
            }
            int temp_count = _move_mole_list.Count;
            for (int j = 0; j < temp_count; j++)
            {
                crash_mole mole = (crash_mole)_move_mole_list[j];
                int crash_obj_count = mole._crash_objs.Count;
                for (int i = 0; i < crash_obj_count; i++)
                {
                    crash_obj obj = (crash_obj)mole._crash_objs[i];
                    float x_temp = obj._last_pos._x * _grid_distance;
                    float z_temp = obj._last_pos._z * _grid_distance ;
                    float y_temp = obj._last_pos._y * _grid_distance;
                    
                    switch (_last_move_dir)
                    {
                        case dir_move.back:
                            {
                                z_temp += _current_move_distance;
                            }
                            break;
                        case dir_move.front:
                            {
                                z_temp -= _current_move_distance;
                            }
                            break;
                        case dir_move.left:
                            {
                                x_temp -= _current_move_distance;
                            }
                            break;
                        case dir_move.right:
                            {
                                x_temp += _current_move_distance;
                            }
                            break;
                        case dir_move.down:
                            {
                                y_temp -= _current_move_distance;
                            }
                            break;
                        case dir_move.up:
                            {
                                y_temp += _current_move_distance;
                            }
                            break;
                    }
                    obj._grid.set_position(x_temp, y_temp, z_temp);
                }



            }
            if (last_move)
            {
                temp_count = _move_mole_list.Count;
                for (int j = 0; j < temp_count; j++)
                {
                    crash_mole mole = (crash_mole)_move_mole_list[j];
                    int crash_obj_count = mole._crash_objs.Count;
                    for (int i = 0; i < crash_obj_count; i++)
                    {
                        crash_obj obj = (crash_obj)mole._crash_objs[i];
                        obj._last_pos = obj._pos;

                    }



                }

                _current_move_distance = 0;
                _need_play_animation = false;
            }
        }

    }

    public void create_map()
    {
        for (int x = 0; x < (int)crash_define.max_x; x++)
        {

            for (int z = 0; z < (int)crash_define.max_z; z++)
            {
                for (int y = 0; y < (int)crash_define.max_y; y++)
                {
                    if (_crash_objs[x, z, y]._crash_obj != null)
                    {
                        GameObject obj_temp = Object.Instantiate<GameObject>(_source_crash_mole_obj);
                        _Game_objs.Add(obj_temp);
                        crash_base_obj entry = _crash_objs[x, z, y]._crash_obj;
                        if(entry.get_obj_type() == crash_obj_type.normal)
                        {
                            crash_obj crash_obj_temp = (crash_obj)entry;
                            crash_obj_temp._grid = obj_temp.GetComponent<crashmolegrid>();
                            crash_obj_temp._grid.set_color(_group_colors[_crash_objs[x, z, y]._crash_obj._crash_mole._color_group]);
                        }

                        float x_temp = x * _grid_distance;
                        float z_temp = z * _grid_distance;
                        float y_temp = y * _grid_distance;
                        entry.set_position(x_temp, y_temp, z_temp);
                    }
                    
                }
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

    public void clear_block()
    {

        for (int x = 0; x < (int)crash_define.max_x; x++)
        {

            for (int z = 0; z < (int)crash_define.max_z; z++)
            {
                for (int y = 0; y < (int)crash_define.max_y; y++)
                {
                    _can_move_locks[x, z, y] = false;
                }
            }
        }
    }

    public void set_block(int x, int z, int y)
    {
        _can_move_locks[x, z, y] = true;
    }
    public bool move(int x, int y, int z, dir_move dir)
    {

        clear_block();
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
            _last_move_dir = dir;
            int temp_count = _move_mole_list.Count;
            for (int j = 0; j < temp_count; j++)
            {
                crash_mole mole = (crash_mole)_crash_moles_list[j];
                int crash_obj_count = mole._crash_objs.Count;
                for (int i = 0; i < crash_obj_count; i++)
                {
                    crash_obj obj = (crash_obj)mole._crash_objs[i];
                    set_block(obj._pos._x, obj._pos._z, obj._pos._y);
                    //obj._last_pos = obj._pos;
                    //obj._pos.move(dir);

                }

                

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
            
            _move_mole_list.Clear();
        }

        return b_temp;

    }

    public bool need_fall_update()
    {
        if(_need_play_animation == true)
        {
            return false;
        }
        _move_mole_list.Clear();
        List<crash_mole> enry_list = new List<crash_mole>();
        int current_count = _crash_moles_list.Count;
        //crash_pos temp_pos = new crash_pos();
        bool can_fall_temp = true;
        
        for (int i = 0; i < current_count; i++)
        {
            bool need_continue = false;
            int move_count = enry_list.Count;
            crash_mole cur_entry = _crash_moles_list[i];
            for(int j = 0; j < move_count; j ++)
            {
                crash_mole temp_entry = enry_list[j];
                if(temp_entry == cur_entry)
                {
                    need_continue = true;
                    break;
                }            
            }
            if(need_continue == true)
            {
                continue;
            }

            _move_mole_list.Add(cur_entry);
            if (move(cur_entry, dir_move.down) == true)
            {
                move_count = _move_mole_list.Count;
                for(int j = 0; j < move_count; j ++)
                {
                    enry_list.Add(_move_mole_list[j]);
                }
                update_move_list(_move_mole_list, dir_move.down);

            }
            _move_mole_list.Clear();

        }

        int cur_count = enry_list.Count;
        if(cur_count > 0)
        {
            can_fall_temp = true;
            _need_play_animation = true;
            _last_move_dir = dir_move.down;
            _move_mole_list.Clear();
            for(int i = 0; i < cur_count; i ++)
            {
                _move_mole_list.Add(enry_list[i]);
            }

        }
        
        return can_fall_temp;
    }

    public void update_move_list(List<crash_mole> temp_list, dir_move dir)
    {
        int count_temp = temp_list.Count;
        for (int i = 0; i < count_temp; i ++ )
        {
            crash_mole obj_mole = (crash_mole)temp_list[i];
            int crash_objs_count = obj_mole._crash_objs.Count;
            for(int j = 0; j < crash_objs_count; j ++)
            {
                crash_obj obj_obj = (crash_obj)obj_mole._crash_objs[j];
                _crash_moles[obj_obj._pos._x, obj_obj._pos._z, obj_obj._pos._y]._crash_mole = null;
                _crash_objs[obj_obj._pos._x, obj_obj._pos._z, obj_obj._pos._y]._crash_obj = null;                
            }
        }

        
        for (int i = 0; i < count_temp; i++)
        {
            crash_mole obj_mole = (crash_mole)temp_list[i];
            int crash_objs_count = obj_mole._crash_objs.Count;
            for (int j = 0; j < crash_objs_count; j++)
            {
                crash_obj obj_obj = (crash_obj)obj_mole._crash_objs[j];
                obj_obj._last_pos = obj_obj._pos;
                obj_obj._pos.move(dir);
                _crash_moles[obj_obj._pos._x, obj_obj._pos._z, obj_obj._pos._y]._crash_mole = obj_obj._crash_mole;
                _crash_objs[obj_obj._pos._x, obj_obj._pos._z, obj_obj._pos._y]._crash_obj = obj_obj;
            }
        }
    }

    protected bool move(crash_mole mole, dir_move dir)
    {
        _use_count++;
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
                string cc;
                if(mole_entry != null)
                {
                    cc = mole_entry.ToString() + "[" + _use_count.ToString() + "]";
                }
                else
                {
                    cc = "mole_entry [null]" + "[" + _use_count.ToString() + "]";
                }
                
                Debug.Log(cc);
                if(mole_entry == null)
                {
                    continue;
                }
                else
                {
                    if(mole_entry == mole)
                    {
                        continue;
                    }
                    int length = _move_mole_list.Count;
                    for (int i = 0; i < length; i++)
                    {
                        if (mole == (crash_mole)_move_mole_list[i] && i != 0)
                        {
                            continue;
                        }
                    }

                    _move_mole_list.Add(mole_entry);
                    if (move(mole_entry, dir) == false)
                    {
                        _move_mole_list.Clear();
                        return false;
                    }                    
                    
                }
                
            }
            else
            {
                _move_mole_list.Clear();
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
        //int count_temp = obj_temp._crash_objs.Count;
        //for (int i = 0; i < count_temp; i++)
        //{
        //    crash_pos pos = ((crash_obj)obj_temp._crash_objs[i])._pos;
        //    //add_crash_obj((crash_obj)obj_temp._crash_objs[i]);
        //    _crash_moles[pos._x, pos._z, pos._y]._crash_mole = obj_temp;

        //}

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