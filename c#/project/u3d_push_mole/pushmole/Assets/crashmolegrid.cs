using UnityEngine;
using System.Collections;

public class crashmolegrid : MonoBehaviour
{
    public MeshRenderer current_mesh_render_;
    public int _group;
 
	// Use this for initialization
	void Start () {
        //Color temp = new Color(255, 255, 255, 255);
        //current_mesh_render_.materials[0].color = temp;
        
	
	}

    public void set_color(Color color)
    {
        //color.r = (int)(color.r * 255);
        //color.g = (int)(color.g * 255);
        //color.b = (int)(color.b * 255);
        //color.a = (int)(color.a * 255);
        Debug.Log("set color ["+ color.ToString()+ "]");
       
        current_mesh_render_.materials[0].color =  color;
    }

    public void set_color(float r, float g, float b, float a)
    {
        Color temp = new Color(r, g, b, a);
        current_mesh_render_.materials[0].color = temp;
    }

    public Color get_color()
    {
        return current_mesh_render_.materials[0].color;
    }

    public void set_group(int i)
    {
        _group = i;
    }
    public void set_position(float x, float y)
    {
        Vector3 new_position = new Vector3(x, y, this.gameObject.transform.position.z);
        this.gameObject.transform.position = new_position;
      
    }


    void OnMouseDown()
    {
        RaycastHit hitt = new RaycastHit();
        Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition);

        Physics.Raycast(ray, out hitt, 100);

        Debug.DrawLine(Camera.main.transform.position, ray.direction, Color.green);

        if (null != hitt.transform)
        {
            crashmolegrid grid_temp = hitt.transform.gameObject.GetComponent<crashmolegrid>();
            grid_temp.set_color(global_instance.Instance._current_color);
            print(hitt.transform.gameObject.name);

            print(hitt.point);//鼠标点击的坐标

        }
    }
	
	// Update is called once per frame
	void Update () {
	
	}
}
