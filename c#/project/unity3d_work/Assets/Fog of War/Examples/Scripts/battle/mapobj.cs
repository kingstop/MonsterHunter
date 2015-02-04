using UnityEngine;
using System.Collections;

public enum Arguments_type{
    pos_x = 0,
    pos_y,
    dir_x,
    dir_y,
    dir_z,
    type_obj,
    state_life,
    max
}
public enum obj_type
{
    mapobj,
    character,
    creature,
    plyaer,

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

public class map_base_source{
    public Map_Pos _pos = new Map_Pos();
    public obj_type _type;
    public Vector3 _dir;

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

    public virtual void set_map_pos(Map_Pos pos)
    {
        set_map_pos(pos.X, pos.Y);
    }

    public virtual void set_map_pos(int X, int Y)
    {
        set_argument(Arguments_type.pos_x, X);
        set_argument(Arguments_type.pos_y, Y);
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

    public virtual life_state get_life_state()
    {
        life_state state_cur = (life_state)get_argument(Arguments_type.state_life);
        return state_cur;
    }

  
     
}
