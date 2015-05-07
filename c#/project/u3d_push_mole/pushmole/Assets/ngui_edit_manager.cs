using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public class ngui_edit_manager : MonoBehaviour {
    public Button[] _Buttons_sliced;
    public Button[] _Buttons_simple;
    public Button[] _Buttons_sliced_game_type;
    public Button[] _Buttons_simple_game_type;
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
        update_game_type(game_type.edit);
	}
	
	// Update is called once per frame
	void Update () {
	
	}

    public void update_game_type(game_type type)
    {
        bool set_temp = false;
        int length = _Buttons_sliced_game_type.Length;
        for(int i = 0 ; i < length; i ++)
        {
            _Buttons_sliced_game_type[i].gameObject.SetActive(!set_temp);
            _Buttons_simple_game_type[i].gameObject.SetActive(set_temp);            
        }

        _Buttons_sliced_game_type[(int)type].gameObject.SetActive(set_temp);
        _Buttons_simple_game_type[(int)type].gameObject.SetActive(!set_temp);

        global_instance.Instance._crash_mole_grid_manager.update_game_type(type);
    }

    public void check_game_type_click(Button obj)
    {
        int length = _Buttons_sliced_game_type.Length;
        for (int i = 0; i < length; i++)
        {
            if (_Buttons_sliced_game_type[i] == obj)
            {
                Debug.Log("check_game_type_click [" + obj.ToString() + "]");
                update_game_type((game_type)i);
                break;
            }
            
        }
    }


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
