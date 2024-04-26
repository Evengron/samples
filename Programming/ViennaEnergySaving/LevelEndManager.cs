using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Events;
using UnityEngine.Serialization;

public class LevelEndManager : MonoBehaviour
{
    [SerializeField] private Timer timer;
    [SerializeField] private GameObject winScreen;
    [SerializeField] private GameObject loseScreen;
    [SerializeField] private int kwhForWin = 50;
    [SerializeField] private float cutoffForMaxExp = 0.9f;
    [SerializeField] private float minExp = 0.4f;
    [SerializeField] private float kwhScaleFactor = 10f;
    [SerializeField] private float minimumKwhPercent = 0.2ff;
    [SerializeField] private float maximumKwhPercent = 2f;

    /// <summary>
    /// Invoked when level is ended. Either by successful finish or by lose (timer, waterTank, ...).
    /// </summary>
    public UnityEvent onLevelEnded;
    
    private float startTimer;
    private int newKwh;

    public void EndGame()
    {
        bool isWin = timer.getTime() > 0;
        EndGameInternal(isWin);
    }
    //Debug Function
    public void LoseGameNow()
    {
        EndGameInternal(false);
    }

    private void EndGameInternal(bool didWin)
    {
        startTimer = timer.getStartTime();
        
        Time.timeScale = 0f;
        newKwh = CalculateGainKwh();
        SaveManager.KwhNeuestRun += newKwh;
        SaveManager.Runchain += 1;

        if (didWin)
        {
            winScreen.SetActive(true);
        }
        else
        {
            loseScreen.SetActive(true);
        }
        
        onLevelEnded?.Invoke();
    }

    private int CalculateGainKwh()
    {
        //double XP if timer is above the cutoff for maximum experience
        if(timer.getTime() > startTimer * cutoffForMaxExp)
            return Mathf.RoundToInt(kwhForWin*kwhScaleFactor * maximumKwhPercent);
        //minimum possible experience, if time has run out
        if (timer.getTime() <= 0)
            return Mathf.RoundToInt(kwhForWin*kwhScaleFactor * minimumKwhPercent);

        return Mathf.RoundToInt(kwhForWin * kwhScaleFactor * (minimumKwhPercent + timer.getTime() / startTimer));
    }

    public int getNewKwh()
    {
        return newKwh;
    }
}
