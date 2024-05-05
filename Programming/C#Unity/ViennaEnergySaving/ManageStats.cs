using System;
using System.Collections;
using TMPro;
using UnityEngine;
using UnityEngine.Events;
using UnityEngine.Serialization;
using UnityEngine.UI;

public class ManageStats : MonoBehaviour
{
    [SerializeField]
    private TextMeshProUGUI experienceText;
    [SerializeField]
    private TextMeshProUGUI levelText;
    [SerializeField] 
    private Slider slider;
	[SerializeField]
	private float xpToLevelUp = 5000f;
	[SerializeField] 
	private float additionalXpPercent = 0.1f;

    [SerializeField] private float animationTime = 1.5f;

    private float _currentTime = 0;
    private float _currentExp;
    private int _maxExp;
    private int _level;
    private string _title;

    private void OnEnable()
    {
        LoadStats();
        UpdateInterface();
    }

    private void UpdateInterface()
    {
        SetExperienceBar();
        SetExperienceText();
        SetLevelText();
    }

    private void SetExperienceBar()
    {
        slider.maxValue = _maxExp;
        slider.value = _currentExp;
    }

    private void SetExperienceText()
    {
        experienceText.text = $"{_currentExp}/{_maxExp}";
    }

    private void SetLevelText()
    {
        levelText.text = $"Lvl.{_level}";
    }

    private void LoadStats()
    {	
		//Different cases for either a new run was made or the menu was opened without new data
        _currentExp = SaveManager.KwhNeuestRun > 0 ? SaveManager.TotalKwh - SaveManager.KwhNeuestRun : SaveManager.TotalKwh;
        _level = SaveManager.CurrentLevel;
        UpdateExperience();
    }

    public void UpdateExperience()
    {	
		//Setting of current MaxXP
        _maxExp = Mathf.RoundToInt(xpToLevelUp + (xpToLevelUp * (_level -1)  * additionalXpPercent));
		//Short while loop, in case that multiple level ups need to be made. even 20 levels tage only a few frames
        while (SaveManager.TotalKwh >= _maxExp)
        {
            _level++;
            _maxExp = Mathf.RoundToInt(xpToLevelUp + (xpToLevelUp * (_level -1)  * additionalXpPercent));
            slider.minValue = _currentExp;
        }
        SaveManager.CurrentLevel = _level;
        UpdateInterface();
    }

    public void StartExpAnimation()
    {
        if (SaveManager.KwhNeuestRun > 0)
        {
            StartCoroutine(AnimateExperience());
        }
    }

    IEnumerator AnimateExperience()
    {
		//Using Vectors to lerp between values is clean, fast and always returns the desired value (no decimals)
        Vector2 currentExpAsVec = new Vector2(_currentExp, 0);
        Vector2 targetAsVec = new Vector2(SaveManager.TotalKwh, 0);
        
        while (_currentTime <= animationTime)
        {
            _currentTime += Time.deltaTime;
            var normValue = currentTime / animationTime;

            _currentExp = (int)Vector2.Lerp(currentExpAsVec, targetAsVec, normValue).x;
            UpdateInterface();
            yield return 0;
        }

        SaveManager.KwhNeuestRun = 0;
    }
}
