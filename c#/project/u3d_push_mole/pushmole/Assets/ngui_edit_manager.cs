using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public class ngui_edit_manager : MonoBehaviour {
    public Button[] _Buttons_sliced;
    public Button[] _Buttons_simple;
    public Color _current_color;
	// Use this for initialization
	void Start () {
        //Debug.Log("ngui_edit_manager start[" + _Buttons_simple.Length.ToString()  + ")

        bool b_set = true;
        if(_Buttons_simple.Length > 0 && _Buttons_sliced.Length > 0)
        {
            foreach (Button entry in _Buttons_simple)
            {
                //entry.hideFlags = HideFlags.HideAndDontSave;
                entry.gameObject.SetActive(b_set);
            }

            foreach (Button entry in _Buttons_sliced)
            {
                entry.gameObject.SetActive(!b_set);
            }

            _Buttons_simple[0].gameObject.SetActive(!b_set);
            _Buttons_sliced[0].gameObject.SetActive(b_set);
            
            global_instance.Instance._current_color = _Buttons_simple[0].GetComponent<Image>().color;

        }
        
	}
	
	// Update is called once per frame
	void Update () {
	
	}

    //public void on_horizontal_Scrollbar_change(GameObject obj)
    //{
    //    Scrollbar bar_temp = obj.GetComponent<Scrollbar>();
    //    //float value = bar_temp.value;
    //}

    //public void on_vertical_Scrollbar_change(GameObject obj)
    //{
    //    Scrollbar bar_temp = obj.GetComponent<Scrollbar>();
    //    float value = bar_temp.value;
    //    float min_h = (float)4.7;
    //    float max_h = (float)55.6;
    //    float temp_distance = (max_h - min_h) * value;
    //    float target_h = temp_distance + min_h;
    //    Vector3 pos_new = new Vector3(Camera.main.transform.position.x, target_h, Camera.main.transform.position.z);
    //    Camera.main.transform.position = pos_new;

    //}



    public void message_on_button_click(Button obj)
    {
        int count_temp = _Buttons_sliced.Length;
        //Debug.Log("message_on_button_click [" +  obj.gameObject.name + "]");
        bool b_set = true;
        if (obj.GetComponent<Image>().type == Image.Type.Simple)
        {

            for (int i = 0; i < count_temp; i++)
            {

                if (_Buttons_simple[i] == obj)
                {

                    global_instance.Instance._current_color = _Buttons_simple[i].GetComponent<Image>().color;
                    global_instance.Instance._current_group = i;
                    _Buttons_simple[i].gameObject.SetActive(!b_set);
                    _Buttons_sliced[i].gameObject.SetActive(b_set);

                }
                else
                {

                    _Buttons_simple[i].gameObject.SetActive(b_set);
                    _Buttons_sliced[i].gameObject.SetActive(!b_set);

                }

            }
        }

    }

    public void on_buttion_click(GameObject obj)
    {
        //ngui_edit_manager entry = this.GetComponentInParent<ngui_edit_manager>();
        //entry.message_on_button_click(obj);
        
        
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
