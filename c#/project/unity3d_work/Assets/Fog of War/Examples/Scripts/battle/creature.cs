using UnityEngine;
using System.Collections;

public enum ai_type
{
    ai_normol,
    ai_combat,
}
public class creature_info : character_info
{

}



public class creature : character
{
    protected ai_type _type;
    protected mapobj _target = null;
    public creature()
    {
        set_obj_type(obj_type.creature);
    }

    public override void init(map_base_source source)
    {
        _type = ai_type.ai_normol;
        base.init(source);
    }


    public void combat_update(int interval_time)
    {

    }

    public void normol_update(int interval_time)
    {

    }

    public override void obj_update(int interval_time)
    {
        switch (_type)
        {
            case ai_type.ai_combat:
                {
                    combat_update(interval_time);
                }
                break;
            case ai_type.ai_normol:
                {
                    normol_update(interval_time);
                }
                break;
        }
        
        base.obj_update(interval_time);
    }
}