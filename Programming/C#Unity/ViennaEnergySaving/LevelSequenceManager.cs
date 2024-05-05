using System;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Events;
using UnityEngine.SceneManagement;
using Random = UnityEngine.Random;

public class LevelSequenceManager : MonoBehaviour
{
    public static LevelSequenceManager Instance;
	
	[SerializeField] private 
    MusicPlayer musicPlayer;

    public List<string> SceneList;
    public int[] KitchenLevels;
    public int[] BathroomLevels;

    public UnityEvent<int> onRepeatNumUpdated;

    private Queue<int> randomLevels;

    private int tempLevel;
    private int levelSet = 1;
    private int repeatNumber = 0;
    private int lastLoadedSceneIdx = -1;

    private void Awake()
    {
        if (Instance != null)
        {
            Destroy(gameObject);
            return;
            
        }
        Instance = this;
        DontDestroyOnLoad(gameObject);

        randomLevels = new Queue<int>();
    }
    
    public void LoadSceneByName(string SceneToLoad)
    {
        lastLoadedSceneIdx = sceneList.IndexOf(SceneToLoad);
        SceneManager.LoadScene(SceneToLoad);
    }

    public void GenerateNewQueue(int level)
    {
        randomLevels.Clear();
        int[] randomNumb;
        switch (level)
        {
            case 1:
                randomNumb = KitchenLevels;
                break;
            case 2:
                randomNumb = BathroomLevels;
                break;
            default:
                randomNumb = new[] {0, 1, 2, 3, 4};
                break;
        }
        
        //shuffle the array

        for (int i = 0; i < randomNumb.Length -1; i++)
        {
            int rnd = Random.Range(i, randomNumb.Length);
            tempLevel = randomNumb[rnd];
            randomNumb[rnd] = randomNumb[i];
            randomNumb[i] = tempLevel;
        }

        // avoid last level being first in next queue
        if (lastLoadedSceneIdx >= 0 && randomNumb.Length >= 2 && randomNumb[0] == lastLoadedSceneIdx)
        {
            int swapIdx = Random.Range(1, randomNumb.Length);
            randomNumb[0] = randomNumb[swapIdx];
            randomNumb[swapIdx] = lastLoadedSceneIdx;
        }
        
        for (int i = 0; i < randomNumb.Length; i++)
        {
            randomLevels.Enqueue(randomNumb[i]);
        }
    }

    public void LoadNextRandom()
    {
        if (randomLevels.Count == 0)
        {
            GenerateNewQueue(levelSet);
            SetRepeatNum(repeatNumber + 1);
        }

        if (randomLevels.Count > 0)
        {
            LoadSceneByName(sceneList[randomLevels.Dequeue()]);
        }
    }

    private void SetRepeatNum(int newRepeatNum)
    {
        repeatNumber = newRepeatNum;
        musicPlayer.SetRepeatNum(repeatNumber);
        onRepeatNumUpdated?.Invoke(repeatNumber);
    }

    public void CreateListAndStart(int set)
    {
        SaveManager.KwhNeuestRun = 0;
        SetRepeatNum(0);
        this.levelSet = set;
        GenerateNewQueue(levelSet);
        LoadNextRandom();
    }

    public int GetRepeats()
    {
        return repeatNumber;
    }
    
    public float GetCurrentSpeedUpPercentage()
    {
        return GetSpeedUpPercentageForRepeats(GetRepeats());
    }
    
    public static float GetSpeedUpPercentageForRepeats(int repeats)
    {
        float targetPercent = 1f - (repeats / 10f);
        return Math.Max(0.25f, targetPercent);
    }

    public void SetRepeatNum_Development(int newRepeatNum)
    {
        if (Debug.isDebugBuild)
        {
            SetRepeatNum(newRepeatNum);
        }
    }
}
