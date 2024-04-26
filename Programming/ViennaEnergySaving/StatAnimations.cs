using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Events;
using UnityEngine.UI;

public class StatAnimations : MonoBehaviour
{
    [SerializeField] private RectTransform objectToMove;
    [SerializeField] private RectTransform moveTo;
    [SerializeField] float travelTime = 1.5f;
    
    private Vector2 _startPosition;
    
    private float _currentTime = 0f;
    private float _normValue;

    private bool _running = false;
    private bool _slideIn = false;
	
	//Event to be callse after the animation is finished
    public UnityEvent finishedSlideIn = null;

    private void Awake()
    {
		//UnPause the game, some weird interactions happened, setting the time here eliminates any possibilities of time beeing 0
        Time.timeScale = 1;
        _startPosition = objectToMove.anchoredPosition;
    }

    public void SlideIn()
    {
        if (!running)
        {
            _currentTime = 0f;
            _running = true;
            _slideIn = true;
            StartCoroutine(SlideProcess(objectToMove.anchoredPosition, moveTo.anchoredPosition));
        }
    }

    public void SlideOut()
    {
        if (!running)
        {
            _currentTime = 0f;
            _running = true;
            _slideIn = false;
            StartCoroutine(SlideProcess(objectToMove.anchoredPosition, _startPosition));
        }
    }
    
    IEnumerator SlideProcess(Vector2 start ,Vector2 target)
    {
        while (currentTime <= travelTime)
        {
            _currentTime += Time.deltaTime;
            _normValue = currentTime / travelTime;
            ObjectToMove.anchoredPosition = Vector2.Lerp(start, target, _normValue);
            yield return new WaitForEndOfFrame();
        }
        
        if (_slideIn)
            finishedSlideIn.Invoke();
        _running = false;
    }
}
