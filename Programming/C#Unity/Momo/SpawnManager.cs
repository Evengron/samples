using System;
using System.Collections.Generic;
using FMOD.Studio;
using FMODUnity;
using UnityEngine;
using UnityEngine.Events;
using Random = UnityEngine.Random;

[RequireComponent(typeof(StudioEventEmitter))]
public class SpawnManager : MonoBehaviour
{
    public GameObject[] allEntities;
    public Spawner[] spawners;
    public UnityEvent<float> onDespawn;
    public UnityEvent<float> onSpawn;
    public float MaxTimer = 3.5f;
    
    
    private Queue<GameObject> InactivePool = new Queue<GameObject>();
    private float _activeNumber = 0;
    private float _spawnTimer = 0f;
    private float _averageActive = 0f;
    private float _activeLastCycle = 0f;
    private float _totalEnemies = 0f;
    private StudioEventEmitter _emitter;
    
    private void Start()
    {
        _emitter = GetComponent<StudioEventEmitter>();
        //Initial enquement of all units.
        foreach (GameObject x in allEntities)
        {
            InactivePool.Enqueue(x);

            x.GetComponentInChildren<GrauerMann>().SetManager(this);
            x.SetActive(false);
            _totalEnemies++;
        }
        
    }

    private void Update()
    {
        //basic timer to spawn new entities
        if (SpawnTimer < MaxTimer)
        {
            SpawnTimer += Time.deltaTime;
        }
        else if(InactivePool.Count != 0)
        {
            SpawnNextEntity();
            SetAverageEntities();
        }
        
    }

    private void Enqueue(GameObject newInactive)
    {
        InactivePool.Enqueue(newInactive);
        FMODUnity.RuntimeManager.StudioSystem.setParameterByName("activeNumber", activeNumber);
        onDespawn.Invoke(--activeNumber);
    }

    private void SpawnNextEntity()
    {
        int randomIndex = Random.Range(0, spawners.Length);
        var currentSpawner = spawners[randomIndex];
            
        _emitter.Play();
            
        GameObject newSpawn = InactivePool.Dequeue();
        newSpawn.SetActive(true);
        newSpawn.GetComponentInChildren<GrauerMann>().SetMovement(currentSpawner.GetDirection());
        newSpawn.transform.position = currentSpawner.transform.position;
            
        FMODUnity.RuntimeManager.StudioSystem.setParameterByName("activeNumber", _activeNumber);
        onSpawn.Invoke(++activeNumber);
        SpawnTimer = MaxTimer;
    }

    //Check for the average numbers of entities, to change the sound landscape
    private void SetAverageEntities()
    {
        FMODUnity.RuntimeManager.StudioSystem.setParameterByName("Fog", _averageActive);
        _averageActive = (_activeNumber + _activeLastCycle) / 2;
        _averageActive /= _totalEnemies;
        _activeLastCycle = _activeNumber;
    }
}
