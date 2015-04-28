using UnityEngine;
using System.Collections;
using UnityEngine;

public class crash_mole_grid_manager : MonoBehaviour {
    GameObject _source_crash_mole_obj;
    crashmolegrid[,] _crashmolegrids = new crashmolegrid[18, 60];
    //prush_mo

	// Use this for initialization
	void Start () {
        Vector3 new_position = new Vector3((float)7.7, (float)4.7, (float)-10.6);
        Camera.main.transform.position = new_position;
        _source_crash_mole_obj = Resources.Load<GameObject>("prefab/mole_object");
        for (int i = 0; i < 18; i++)
        {
            for (int j = 0; j < 60; j++)
            {
               GameObject obj_temp = Instantiate<GameObject>(_source_crash_mole_obj);
               _crashmolegrids[i, j] = obj_temp.GetComponent<crashmolegrid>();
               float x = (float)i + (float)(i * 0.022);
               float y = (float)j + (float)(j * 0.022);

               _crashmolegrids[i, j].set_position(x , y);
            }
        }

            

	}
	
	// Update is called once per frame
	void Update () {
	
	}
}
