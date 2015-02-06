using UnityEngine;
using System.Collections;

public class character_info : map_base_source
{

}




public class character : mapobj
{

    public character()
    {
        set_obj_type(obj_type.character);
    }

    public override void init(map_base_source map)
    {
        base.init(map);        
    }

    public override void reset()
    {
        base.reset();
    }

}
