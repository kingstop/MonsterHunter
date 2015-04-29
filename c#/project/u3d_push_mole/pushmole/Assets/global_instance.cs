﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using UnityEngine;


public class global_instance
{
 private static global_instance instance;
 private global_instance() {
     _crash_manager = new crash_manager();
 }
 public static global_instance Instance 
 { 
      get  
      { 
         if (instance == null) 
         {
             instance = new global_instance(); 
         } 
         return instance; 
      } 
  } 
  public Color _current_color;
  public int _current_group;
  public crash_manager _crash_manager;

}
