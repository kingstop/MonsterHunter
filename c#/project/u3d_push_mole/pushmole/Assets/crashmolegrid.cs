using UnityEngine;
using System.Collections;

public class crashmolegrid : MonoBehaviour
{
    public MeshRenderer current_mesh_render_;
 
	// Use this for initialization
	void Start () {
        Color temp = new Color(255, 0, 0, 255);
        current_mesh_render_.materials[0].color = temp;
        
	
	}

    public void set_color(float r, float g, float b, float a)
    {
        Color temp = new Color(r, g, b, a);
        current_mesh_render_.materials[0].color = temp;
    }
    public void set_position(float x, float y)
    {
        Vector3 new_position = new Vector3(x, y, this.gameObject.transform.position.z);
        this.gameObject.transform.position = new_position;
      
    }

	
	// Update is called once per frame
	void Update () {
	
	}
}
