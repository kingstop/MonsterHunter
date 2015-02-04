using UnityEngine;
using System.Collections;

public enum Arguments_type{
    pos_x = 0,
    pos_y,
    want_move_pos_x,
    want_move_pos_y,
    dir_x,
    dir_y,
    dir_z,
    type_obj,
    state_life,
    move_state,
    max_hp,
    begin_hp,
    walk_speed,
    run_speed,
    max
}
public enum obj_type
{
    mapobj,
    character,
    creature,
    player,

}

public enum life_state
{
    alife,
    dead,
}
public class Map_Pos
{
    public int X;
    public int Y;
}


public enum MoveState
{
    No,
    Walk,
    Run
}


public class map_base_source{
    public Map_Pos _pos = new Map_Pos();
    public obj_type _type;
    public Vector3 _dir;
    public int max_hp;
    public int begin_hp;
    public int walk_speed;
    public int run_speed;

}

public class mapobj
{
    protected map_base_source _source;
    protected int[] _arguments = new int[(int)Arguments_type.max];

    public mapobj()
    {
        set_obj_type(obj_type.mapobj);
    }
    public virtual void init(map_base_source source)
    {
        _source = source;
    }

    public virtual void set_argument(Arguments_type type, int temp_value)
    {
        _arguments[(int)type] = temp_value;
    }

    public virtual int get_argument(Arguments_type type)
    {
        return _arguments[(int)type];
    }

    public virtual void set_want_move_pos(int X, int Y)
    {
        set_argument(Arguments_type.want_move_pos_x, X);
        set_argument(Arguments_type.want_move_pos_y, Y);
    }


    public virtual bool is_need_move()
    {
       if(get_want_move_pos() == get_pos())
       {
           return false;
       }
       return true;
    }
    public virtual void set_want_move_pos(Map_Pos pos)
    {
        set_want_move_pos(pos.X, pos.Y);
    }

    public virtual Map_Pos get_want_move_pos()
    {
        Map_Pos pos = new Map_Pos();
        pos.X = get_argument(Arguments_type.want_move_pos_x);
        pos.Y = get_argument(Arguments_type.want_move_pos_y);
        return pos;
    }

    public virtual void set_map_pos(Map_Pos pos)
    {
        set_map_pos(pos.X, pos.Y);
    }

    public virtual void set_map_pos(int X, int Y)
    {
        set_argument(Arguments_type.pos_x, X);
        set_argument(Arguments_type.pos_y, Y);
    }

    public virtual MoveState get_move_state()
    {
        return (MoveState)get_argument(Arguments_type.move_state);
    }

    public virtual void set_move_state(MoveState state)
    {
        if (get_move_state() != state)
        {
            set_argument(Arguments_type.move_state, (int)state);
        }
    }


    public virtual bool is_move_state()
    {
        if (get_move_state() != MoveState.No)
        {
            return true;
        }
        return false;
        
    }

    public virtual void obj_update_move()
    {
        if (is_move_state() == false)
        {
            return;
        }

        int move_speed = 0;
        if (get_move_state() == MoveState.Walk)
        {
            move_speed = get_walk_speed();
        }
        else if (get_move_state() == MoveState.Run)
        {
            move_speed = get_run_speed();
        }

       
        



    }
    public virtual void obj_update()
    {

    }

    public virtual void reset()
    {
        set_map_pos(_source._pos);
    }

    public virtual obj_type get_obj_type()
    {
        return (obj_type) get_argument(Arguments_type.type_obj);
    }

    public virtual void set_obj_type(obj_type type)
    {
        set_argument(Arguments_type.type_obj, (int)type);
    }

    public virtual int get_begin_hp()
    {
        return get_argument(Arguments_type.begin_hp);
    }

    public virtual int get_max_hp()
    {
        return get_argument(Arguments_type.max_hp);
    }

    public virtual void set_dir(Vector3 dir)
    {
        int dir_x_temp = (int)dir.x * 1000;
        int dir_y_temp = (int)dir.y * 1000;
        int dir_z_temp = (int)dir.z * 1000;
        set_argument(Arguments_type.dir_x, dir_x_temp);
        set_argument(Arguments_type.dir_y, dir_y_temp);
        set_argument(Arguments_type.dir_z, dir_z_temp);
    }

    public virtual Vector3 get_dir()
    {
        Vector3 temp_dir = new Vector3();
        temp_dir.x = (float)get_argument(Arguments_type.dir_x) / 1000;
        temp_dir.y = (float)get_argument(Arguments_type.dir_y) / 1000;
        temp_dir.z = (float)get_argument(Arguments_type.dir_z) / 1000;
        return temp_dir;
    }

    public virtual Map_Pos get_pos()
    {
        Map_Pos Pos = new Map_Pos();
        Pos.X = get_argument(Arguments_type.pos_x);
        Pos.Y = get_argument(Arguments_type.pos_y);
        return Pos;
    }

    public virtual int get_walk_speed()
    {
        return get_argument(Arguments_type.walk_speed);
    }

    public virtual int get_run_speed()
    {
        return get_argument(Arguments_type.run_speed);
    }
    public virtual life_state get_life_state()
    {
        life_state state_cur = (life_state)get_argument(Arguments_type.state_life);
        return state_cur;
    }

  
     
}
