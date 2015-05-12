using UnityEngine;
using System.Collections;

public class next_step_click : MonoBehaviour {

	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
	
	}

    public void ButtonStepNextClick()
    {
        global_instance.Instance._crash_manager.need_fall_update();
    }
}
