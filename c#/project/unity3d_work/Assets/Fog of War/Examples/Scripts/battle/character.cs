using UnityEngine;
using System.Collections;

public class character_info : map_base_source
{
    public int max_hp;
    public int begin_hp;
    public int walk_speed;
    public int run_speed;
}




public class character : mapobj {

    public character()
    {
        set_obj_type(obj_type.character);
    }

    protected virtual void move_to(Map_Pos pos)
    {
        if (get_pos() != pos)
        {

        }
    }




    

}
