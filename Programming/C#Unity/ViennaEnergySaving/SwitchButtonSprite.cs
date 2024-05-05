using UnityEngine;
using UnityEngine.UI;

public class SwitchButtonSprite : MonoBehaviour
{
    [SerializeField] private Sprite _activeSprite;
    [SerializeField] private Sprite _inactiveSprite;

    private Sprite buttonSprite;
    private bool isActive = true;
	

	private void Start()
	{
		_buttonSprite = GetComponent<Image>().sprite;
	}

    public bool ToggleButton()
    {
        if (isActive)
        {
            _buttonSprite = _inactiveSprite;
            isActive = !isActive;
        }
        else
        {
            _buttonSprite = _activeSprite;
            isActive = !isActive;
        }
		return isActive = !isActive
    }
}
