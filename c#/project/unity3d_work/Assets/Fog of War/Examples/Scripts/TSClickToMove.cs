using UnityEngine;

[AddComponentMenu("FOW Example/Click To Move")]

public enum role_state
{
    run,
    idle,
    die,
    attack
}
public class TSClickToMove : MonoBehaviour
{
	public LayerMask layerMask = 1;
	public KeyCode keyCode = KeyCode.Mouse0;
    public role_state _state = role_state.idle;
    public float _dir = 0;

	Transform mTrans;
	Vector3 mTarget;
	Vector2 mMousePress;

	void Start ()
	{
		mTrans = transform;
		mTarget = mTrans.position;
        _state = role_state.idle;
        animation.Play("idle");

        

	}

    void change_dir(Vector3 dir)
    {

        transform.LookAt( dir);
        //Debug.Log("rotation [" + transform.rotation.ToString() + "] dir ["+ dir.ToString()+"]");
    }

    void change_state(role_state state)
    {
        if(_state != state)
        {
            _state = state;
            switch(_state){
                case role_state.idle:
                    {
                        animation.Play("idle");
                    }
                    break;
                case role_state.attack:
                    {
                        animation.Play("attack");
                    }
                    break;
                case role_state.run:
                    {
                        animation.Play("run");
                    }
                    break;
                case role_state.die:
                    {
                        animation.Play("die");
                    }
                    break;
            }
        }
    }



	void Update ()
	{
		if (Input.GetKeyDown(keyCode)) mMousePress = Input.mousePosition;

		if (Input.GetKeyUp(keyCode))
		{
			if (Vector2.Distance(Input.mousePosition, mMousePress) > 5f) return;

			RaycastHit hit;
			Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition);

			if (Physics.Raycast(ray, out hit, 300f, layerMask))
			{
				mTarget = hit.point;
			}
		}

		float dist = Vector3.Distance(mTrans.position, mTarget);

		if (dist > 0.001f)
		{
			Vector3 newPos = Vector3.MoveTowards(mTrans.position, mTarget, 10f * Time.deltaTime);
			newPos.y = Terrain.activeTerrain.SampleHeight(newPos);

            Vector3 dir = mTarget - mTrans.position;
            change_state(role_state.run);
            //Debug.Log( "dir [" + dir.ToString() + "]");
            change_dir(mTarget);
            mTrans.position = newPos;
		}
        else
        {
            change_state(role_state.idle);
        }
	}
}