using System;
using UnityEngine;
using UnityEngine.Events;
using FMOD.Studio;
using TMPro;

public class SettingsManager : MonoBehaviour
{
    [SerializeField] private GameObject soundButton;
    [SerializeField] private GameObject musicButton;
    [SerializeField] private GameObject soundOffButton;
    [SerializeField] private GameObject musicOffButton;

    private void Awake()
    {
        if (!SaveManager.SoundEnabled)
        {
            soundButton.gameObject.SetActive(false);
            soundOffButton.gameObject.SetActive(true);
        }

        if (!SaveManager.MusicEnabled)
        {
            musicButton.gameObject.SetActive(false);
            musicOffButton.gameObject.SetActive(true);
        }
    }

    public void UnMuteSound()
    {
        string vcaPath = "vca:/SFX";
        VCA vca = FMODUnity.RuntimeManager.GetVCA(vcaPath);
        vca.setVolume(1);
        SaveManager.SoundEnabled = true;
    }

    public void MuteSound()
    {
        string vcaPath = "vca:/SFX";
        VCA vca = FMODUnity.RuntimeManager.GetVCA(vcaPath);
        vca.setVolume(0);
        SaveManager.SoundEnabled = false;
    }

    public void UnMuteMusic()
    {
        string vcaPath = "vca:/MUSIC";
        VCA vca = FMODUnity.RuntimeManager.GetVCA(vcaPath);
        vca.setVolume(1);
        SaveManager.MusicEnabled = true;
    }

    public void MuteMusic()
    {
        string vcaPath = "vca:/MUSIC";
        VCA vca = FMODUnity.RuntimeManager.GetVCA(vcaPath);
        vca.setVolume(0);
        SaveManager.MusicEnabled = false;
    }

    public void OpenLink(string url)
    {
        Application.OpenURL(url);
    }

    public void ExitGame()
    {
        Application.Quit();
    }
}
