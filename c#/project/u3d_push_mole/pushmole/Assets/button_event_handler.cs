﻿using UnityEngine;
using System.Collections;
using UnityEngine.UI;
using UnityEngine.EventSystems;

//需要EventTrigger脚本的支援
[RequireComponent(typeof(UnityEngine.EventSystems.EventTrigger))]
public class EventHandler : MonoBehaviour
{

    // Use this for initialization
    void Start()
    {

        Button btn = this.GetComponent<Button>();
        UnityEngine.EventSystems.EventTrigger trigger = btn.gameObject.GetComponent<UnityEngine.EventSystems.EventTrigger>();
        EventTrigger.Entry entry = new EventTrigger.Entry();
        entry.eventID = EventTriggerType.PointerClick;
        entry.callback = new EventTrigger.TriggerEvent();
        entry.callback.AddListener(Onclick);

        trigger.delegates.Add(entry);

        EventTrigger.Entry entry_down = new EventTrigger.Entry();
        entry_down.eventID = EventTriggerType.PointerDown;
        trigger.delegates.Add(entry_down);

    }

    private void Onclick(BaseEventData pointData)
    {
        Debug.Log("Button Clicked");

    }

    private void OnButtonDown(BaseEventData pointData)
    {

    }

}