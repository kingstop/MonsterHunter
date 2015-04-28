using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public class ngui_edit_manager : MonoBehaviour {
    public Button[] _Buttons_sliced;
    public Button[] _Buttons_simple;
    public Color _current_color;
	// Use this for initialization
	void Start () {
        if(_Buttons_simple.Length > 0 && _Buttons_sliced.Length > 0)
        {
            foreach (Button entry in _Buttons_simple)
            {
                entry.hideFlags = HideFlags.HideAndDontSave;
            }

            foreach (Button entry in _Buttons_sliced)
            {
                entry.hideFlags = HideFlags.None;
            }

            _Buttons_simple[0].hideFlags = HideFlags.None;
            _Buttons_sliced[0].hideFlags = HideFlags.HideAndDontSave;
            
            _current_color = _Buttons_simple[0].GetComponent<Image>().color;

        }
        
	}
	
	// Update is called once per frame
	void Update () {
	
	}

    public void on_horizontal_Scrollbar_change(GameObject obj)
    {
        Scrollbar bar_temp = obj.GetComponent<Scrollbar>();
        float value = bar_temp.value;
    }

    public void on_vertical_Scrollbar_change(GameObject obj)
    {
        Scrollbar bar_temp = obj.GetComponent<Scrollbar>();
        float value = bar_temp.value;
        float min_h = (float)4.7;
        float max_h = (float)55.6;
        float temp_distance = (max_h - min_h) * value;
        float target_h = temp_distance + min_h;
        Vector3 pos_new = new Vector3(Camera.main.transform.position.x, target_h, Camera.main.transform.position.z);
        Camera.main.transform.position = pos_new;

    }

    public void message_on_button_click(GameObject obj)
    {
        int count_temp = _Buttons_sliced.Length;
        for (int i = 0; i < count_temp; i++)
        {
            if (_Buttons_sliced[i] == obj)
            {

                _Buttons_simple[0].hideFlags = HideFlags.None;
                _Buttons_sliced[i].hideFlags = HideFlags.HideAndDontSave; 
            }
            else
            {
                _Buttons_simple[0].hideFlags = HideFlags.HideAndDontSave;
                _Buttons_sliced[i].hideFlags = HideFlags.None;
            }
            
        }
    }

    public void on_buttion_click(GameObject obj)
    {
        ngui_edit_manager entry = this.GetComponentInParent<ngui_edit_manager>();
        entry.message_on_button_click(obj);
        
        
        //foreach (Button entry in _Buttons)
        //{
        //    Image temp = entry.GetComponent<Image>();
        //    if (entry == obj)
        //    {
                
        //        temp.type = Image.Type.Sliced;
        //    }
        //    else
        //    {
        //        temp.type = Image.Type.Simple;
        //    }
        //}
    }


}
