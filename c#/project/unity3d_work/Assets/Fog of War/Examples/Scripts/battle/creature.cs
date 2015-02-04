using UnityEngine;
using System.Collections;

public class creature_info : character_info
{

}



public class creature : character
{
    public creature()
    {
        set_obj_type(obj_type.creature);
    }
}