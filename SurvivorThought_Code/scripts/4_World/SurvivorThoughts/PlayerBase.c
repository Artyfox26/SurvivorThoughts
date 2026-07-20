modded class PlayerBase
{

    void PlayerBase()
    {
        RegisterNetSyncVariableBool("m_ST_JournalSetupComplete");

        m_ST_ImportantGearLevels = new map<string, int>;
    }

    protected float m_ST_LastThoughtTime;
    protected float m_ST_NextThoughtDelay;
    protected float m_ST_LastActionThoughtTime;
    protected float m_ST_LastCombatStressThoughtTime;
    protected float m_ST_LastFallDamageThoughtTime;
    protected string m_ST_PersonalityProfile;
    protected int m_ST_LastKnownBleedingSourceCount = -1;
    protected float m_ST_LastHealthValue = -1.0;
    protected float m_ST_LastHealthDropTime;
    protected float m_ST_LastOpenCloseActionThoughtTime;
    protected float m_ST_LastWeatherThoughtTime;
    protected float m_ST_LastTimeOfDayThoughtTime;
    protected string m_ST_LastImmediateActionType;
    protected float m_ST_LastImmediateActionTime;
    protected int m_ST_LastThoughtPriority;
    protected float m_ST_LastThoughtPriorityTime;
    protected string m_ST_LastThoughtPriorityType;
    protected string m_ST_SelectedThoughtType;

    // Dedicated equipment-condition tracker. Gear is important enough to have
    // its own scan cadence instead of competing only inside passive stat pools.
    protected float m_ST_LastImportantGearScanTime;
    protected ref map<string, int> m_ST_ImportantGearLevels;

    // Player-stat stage tracker. Stage 0 is normal/white; stage 1 begins at the
    // first warning/yellow range. A thought is emitted only when the stage changes.
    protected int m_ST_LastEnergyStage = -1;
    protected int m_ST_LastWaterStage = -1;
    protected int m_ST_LastBloodStage = -1;
    protected int m_ST_LastShockStage = -1;
    protected int m_ST_LastHealthStage = -1;
    protected int m_ST_LastTemperatureStage = -1;
    protected int m_ST_LastCombinedRedMask;

    protected float m_ST_LastPlayerMemoryThoughtTime;
    protected float m_ST_LastStealthNoiseThoughtTime;
    protected float m_ST_LastShelterThoughtTime;
    protected float m_ST_LastMentalStateThoughtTime;
    protected float m_ST_LastCustomThoughtZoneThoughtTime;

    protected float m_ST_RecentDamageTime;
    protected float m_ST_RecentBleedingTime;
    protected float m_ST_RecentGunshotTime;
    protected float m_ST_RecentCorpseTime;
    protected float m_ST_RecentMilitaryTime;
    protected float m_ST_RecentSurvivalCrisisTime;

    protected float m_ST_LastSocialGroupThoughtTime;
    protected float m_ST_LastSeenPlayerTime;
    protected float m_ST_NearbyFriendlySince;
    protected float m_ST_SocialBondActiveUntil;

    protected float m_ST_SanityValue = -1.0;
    protected float m_ST_LastSanityThoughtTime;
    protected float m_ST_LastSanityUpdateTime;
    protected float m_ST_LastCannibalActionTime;
    protected bool m_ST_PersistentStateLoaded;
    protected float m_ST_LastPersistentStateSaveTime;

    protected float m_ST_StateHistoryLastSampleTime;
    protected float m_ST_StateHistoryLastEnergy = -1.0;
    protected float m_ST_StateHistoryLastWater = -1.0;
    protected float m_ST_StateHistoryLastBlood = -1.0;
    protected float m_ST_StateHistoryLastHealth = -1.0;
    protected float m_ST_StateHistoryLastShock = -1.0;
    protected float m_ST_StateHistoryLastHeatComfort = 0.0;
    protected int m_ST_EnergyTrend;
    protected int m_ST_WaterTrend;
    protected int m_ST_BloodTrend;
    protected int m_ST_HealthTrend;
    protected int m_ST_ShockTrend;
    protected int m_ST_TemperatureTrend;
    protected float m_ST_LastStateSnapshotTime;
    protected float m_ST_LastRecoveryThoughtTime;
    protected float m_ST_LastMapEnvironmentThoughtTime;
    protected float m_ST_LastNearMissCombatThoughtTime;
    protected float m_ST_LastNearMissCombatTime;
    protected bool m_ST_WasBleedingForRecovery;
    protected bool m_ST_WasHealthDroppingForRecovery;
    protected bool m_ST_WasStarvingForRecovery;
    protected bool m_ST_WasDehydratedForRecovery;
    protected bool m_ST_WasColdForRecovery;
    protected bool m_ST_WasHotForRecovery;
    protected bool m_ST_WasContaminatedForRecovery;
    protected bool m_ST_WasThreatenedByInfectedForRecovery;
    protected bool m_ST_WasNightForRecovery;
    protected bool m_ST_WasLowBloodForRecovery;
    protected bool m_ST_WasLowShockForRecovery;
    protected bool m_ST_WasCombatStressedForRecovery;
    protected bool m_ST_WasNearDeathForRecovery;
    protected bool m_ST_WasInShelterForRecovery;

    protected float m_ST_StarvingSince;
    protected float m_ST_DehydratedSince;
    protected float m_ST_ColdSince;
    protected float m_ST_HotSince;
    protected float m_ST_BleedingSince;
    protected float m_ST_SickSince;


    protected ref array<string> m_ST_RecentThoughtMessages;
    protected ref array<float> m_ST_RecentThoughtTimes;


    protected bool m_ST_JournalSetupComplete;
    protected bool m_ST_JournalGiven;
    protected string m_ST_JournalCharacterName;
    protected string m_ST_JournalCharacterType;
    protected string m_ST_JournalHeadType;
    protected string m_ST_JournalOrigin;
    protected string m_ST_JournalOccupation;
    protected string m_ST_JournalTrait;
    protected string m_ST_JournalFear;
    protected string m_ST_JournalGoal;
    protected string m_ST_JournalSkill;
    protected string m_ST_JournalWeakness;
    protected string m_ST_JournalMoralCode;
    protected string m_ST_JournalBackstory;




    void ST_EnsurePersistentStateLoaded(ST_SurvivorThoughtsConfig config)
    {
        if (m_ST_PersistentStateLoaded)
            return;

        if (!config || config.EnableMissionStoragePersistentData != 1)
        {
            m_ST_PersistentStateLoaded = true;
            return;
        }

        if (!GetIdentity())
            return;

        SurvivorThoughtsManager.Get().ApplyPersistentDataToPlayer(this);
        m_ST_PersistentStateLoaded = true;
    }

    void ST_MaybeAutosavePersistentState(ST_SurvivorThoughtsConfig config)
    {
        if (!config || config.EnableMissionStoragePersistentData != 1)
            return;

        if (!GetGame())
            return;

        float now = GetGame().GetTime() / 1000.0;

        if (m_ST_LastPersistentStateSaveTime > 0.0 && (now - m_ST_LastPersistentStateSaveTime) < config.PersistentAutosaveSeconds)
            return;

        m_ST_LastPersistentStateSaveTime = now;
        SurvivorThoughtsManager.Get().SavePersistentDataForPlayer(this);
    }

    void ST_SavePersistentStateNow()
    {
        ST_SurvivorThoughtsConfig config = SurvivorThoughtsManager.Get().GetConfig();

        if (!config || config.EnableMissionStoragePersistentData != 1)
            return;

        if (GetGame())
        {
            float now = GetGame().GetTime() / 1000.0;

            if (config.EnablePersistentSaveThrottle == 1 && m_ST_LastPersistentStateSaveTime > 0.0 && (now - m_ST_LastPersistentStateSaveTime) < config.PersistentForcedSaveCooldownSeconds)
                return;

            m_ST_LastPersistentStateSaveTime = now;
        }

        SurvivorThoughtsManager.Get().SavePersistentDataForPlayer(this);
    }

    void ST_ApplyPersistentState(ST_PlayerPersistentStateRecord record, ST_SurvivorThoughtsConfig config)
    {
        if (!record)
            return;

        m_ST_LastPlayerMemoryThoughtTime = record.LastPlayerMemoryThoughtTime;
        m_ST_RecentDamageTime = record.RecentDamageTime;
        m_ST_RecentBleedingTime = record.RecentBleedingTime;
        m_ST_RecentGunshotTime = record.RecentGunshotTime;
        m_ST_RecentCorpseTime = record.RecentCorpseTime;
        m_ST_RecentMilitaryTime = record.RecentMilitaryTime;
        m_ST_RecentSurvivalCrisisTime = record.RecentSurvivalCrisisTime;

        m_ST_LastSocialGroupThoughtTime = record.LastSocialGroupThoughtTime;
        m_ST_LastSeenPlayerTime = record.LastSeenPlayerTime;
        m_ST_NearbyFriendlySince = record.NearbyFriendlySince;
        m_ST_SocialBondActiveUntil = record.SocialBondActiveUntil;

        if (record.SanityValue >= 0.0)
            m_ST_SanityValue = record.SanityValue;
        else if (config)
            m_ST_SanityValue = config.StartingSanity;

        m_ST_LastSanityThoughtTime = record.LastSanityThoughtTime;
        m_ST_LastSanityUpdateTime = record.LastSanityUpdateTime;
        m_ST_LastCannibalActionTime = record.LastCannibalActionTime;

        m_ST_JournalSetupComplete = record.JournalSetupComplete == 1;
        m_ST_JournalCharacterName = record.JournalCharacterName;
        m_ST_JournalCharacterType = record.JournalCharacterType;
        m_ST_JournalHeadType = record.JournalHeadType;
        m_ST_JournalOrigin = record.JournalOrigin;
        m_ST_JournalOccupation = record.JournalOccupation;
        m_ST_JournalTrait = record.JournalTrait;
        m_ST_JournalFear = record.JournalFear;
        m_ST_JournalGoal = record.JournalGoal;
        m_ST_JournalSkill = record.JournalSkill;
        m_ST_JournalWeakness = record.JournalWeakness;
        m_ST_JournalMoralCode = record.JournalMoralCode;
        m_ST_JournalBackstory = record.JournalBackstory;
        SetSynchDirty();

        if (record.RecentThoughtMessages)
        {
            m_ST_RecentThoughtMessages = new array<string>;
            foreach (string msg : record.RecentThoughtMessages)
            {
                m_ST_RecentThoughtMessages.Insert(msg);
            }
        }

        if (record.RecentThoughtTimes)
        {
            m_ST_RecentThoughtTimes = new array<float>;
            foreach (float msgTime : record.RecentThoughtTimes)
            {
                m_ST_RecentThoughtTimes.Insert(msgTime);
            }
        }
    }

    void ST_FillPersistentState(ST_PlayerPersistentStateRecord record, ST_SurvivorThoughtsConfig config)
    {
        if (!record)
            return;

        record.LastPlayerMemoryThoughtTime = m_ST_LastPlayerMemoryThoughtTime;
        record.RecentDamageTime = m_ST_RecentDamageTime;
        record.RecentBleedingTime = m_ST_RecentBleedingTime;
        record.RecentGunshotTime = m_ST_RecentGunshotTime;
        record.RecentCorpseTime = m_ST_RecentCorpseTime;
        record.RecentMilitaryTime = m_ST_RecentMilitaryTime;
        record.RecentSurvivalCrisisTime = m_ST_RecentSurvivalCrisisTime;

        record.LastSocialGroupThoughtTime = m_ST_LastSocialGroupThoughtTime;
        record.LastSeenPlayerTime = m_ST_LastSeenPlayerTime;
        record.NearbyFriendlySince = m_ST_NearbyFriendlySince;
        record.SocialBondActiveUntil = m_ST_SocialBondActiveUntil;

        if (m_ST_SanityValue < 0.0 && config)
            m_ST_SanityValue = config.StartingSanity;

        record.SanityValue = m_ST_SanityValue;
        record.LastSanityThoughtTime = m_ST_LastSanityThoughtTime;
        record.LastSanityUpdateTime = m_ST_LastSanityUpdateTime;
        record.LastCannibalActionTime = m_ST_LastCannibalActionTime;

        if (!record.RecentThoughtMessages)
            record.RecentThoughtMessages = new array<string>;
        else
            record.RecentThoughtMessages.Clear();

        if (m_ST_RecentThoughtMessages)
        {
            foreach (string message : m_ST_RecentThoughtMessages)
            {
                record.RecentThoughtMessages.Insert(message);
            }
        }

        if (!record.RecentThoughtTimes)
            record.RecentThoughtTimes = new array<float>;
        else
            record.RecentThoughtTimes.Clear();

        record.JournalSetupComplete = m_ST_JournalSetupComplete;
        record.JournalCharacterName = m_ST_JournalCharacterName;
        record.JournalCharacterType = m_ST_JournalCharacterType;
        record.JournalHeadType = m_ST_JournalHeadType;
        record.JournalOrigin = m_ST_JournalOrigin;
        record.JournalOccupation = m_ST_JournalOccupation;
        record.JournalTrait = m_ST_JournalTrait;
        record.JournalFear = m_ST_JournalFear;
        record.JournalGoal = m_ST_JournalGoal;
        record.JournalSkill = m_ST_JournalSkill;
        record.JournalWeakness = m_ST_JournalWeakness;
        record.JournalMoralCode = m_ST_JournalMoralCode;
        record.JournalBackstory = m_ST_JournalBackstory;

        if (m_ST_RecentThoughtTimes)
        {
            foreach (float timeValue : m_ST_RecentThoughtTimes)
            {
                record.RecentThoughtTimes.Insert(timeValue);
            }
        }
    }



    float ST_GetLastSocialGroupThoughtTime()
    {
        return m_ST_LastSocialGroupThoughtTime;
    }

    void ST_SetLastSocialGroupThoughtTime(float time)
    {
        m_ST_LastSocialGroupThoughtTime = time;
    }

    float ST_GetLastSanityThoughtTime()
    {
        return m_ST_LastSanityThoughtTime;
    }

    void ST_SetLastSanityThoughtTime(float time)
    {
        m_ST_LastSanityThoughtTime = time;
    }

    bool ST_HasRecentSocialBond()
    {
        if (!GetGame())
            return false;

        float now = GetGame().GetTime() / 1000.0;
        return m_ST_SocialBondActiveUntil > now;
    }

    float ST_GetSanityValue(ST_SurvivorThoughtsConfig config)
    {
        if (!config)
            return 100.0;

        if (m_ST_SanityValue < 0.0)
            m_ST_SanityValue = config.StartingSanity;

        return m_ST_SanityValue;
    }

    void ST_AddSanityStress(string reason, float amount)
    {
        if (!GetGame() || amount <= 0.0)
            return;

        ST_SurvivorThoughtsConfig config = SurvivorThoughtsManager.Get().GetConfig();

        if (!config || config.EnableSanityCreep != 1)
            return;

        if (m_ST_SanityValue < 0.0)
            m_ST_SanityValue = config.StartingSanity;

        m_ST_SanityValue = m_ST_SanityValue - amount;

        if (m_ST_SanityValue < config.MinimumSanity)
            m_ST_SanityValue = config.MinimumSanity;

        m_ST_LastCannibalActionTime = GetGame().GetTime() / 1000.0;

        SurvivorThoughtsManager.Get().DebugLog("Sanity stress applied. Reason=" + reason + " Amount=" + amount.ToString() + " Sanity=" + m_ST_SanityValue.ToString());

        if (config.JournalWriteSanityEvents == 1)
            SurvivorThoughtsManager.Get().ST_AddMajorJournalEvent(this, "[SANITY_CREEP] Sanity changed after " + reason + ". Current sanity=" + m_ST_SanityValue.ToString());

        ST_SavePersistentStateNow();
    }

    void ST_UpdateSanityRecovery(ST_SurvivorThoughtsConfig config)
    {
        if (!config || config.EnableSanityCreep != 1 || config.SanityRegenPerMinute <= 0.0)
            return;

        if (!GetGame())
            return;

        float now = GetGame().GetTime() / 1000.0;

        if (m_ST_LastSanityUpdateTime <= 0.0)
        {
            m_ST_LastSanityUpdateTime = now;
            return;
        }

        float delta = now - m_ST_LastSanityUpdateTime;
        m_ST_LastSanityUpdateTime = now;

        if (m_ST_SanityValue < 0.0)
            m_ST_SanityValue = config.StartingSanity;

        m_ST_SanityValue = m_ST_SanityValue + ((config.SanityRegenPerMinute / 60.0) * delta);

        if (m_ST_SanityValue > config.StartingSanity)
            m_ST_SanityValue = config.StartingSanity;
    }

    void ST_UpdateSocialAwareness(ST_SurvivorThoughtsConfig config)
    {
        if (!config || config.EnableSocialGroupThoughts != 1)
            return;

        if (!GetGame())
            return;

        float now = GetGame().GetTime() / 1000.0;

        if (m_ST_LastSeenPlayerTime <= 0.0)
            m_ST_LastSeenPlayerTime = now;

        array<Object> objects = new array<Object>;
        GetGame().GetObjectsAtPosition(GetPosition(), config.SocialNearbyPlayerRadius, objects, NULL);

        bool foundOtherPlayer = false;

        for (int i = 0; i < objects.Count(); i++)
        {
            PlayerBase otherPlayer = PlayerBase.Cast(objects[i]);

            if (!otherPlayer || otherPlayer == this || !otherPlayer.IsAlive())
                continue;

            foundOtherPlayer = true;
            ST_SurvivorStorySystem.Get().RememberSpecificPlayer(this, otherPlayer, "seen nearby");
            break;
        }

        if (foundOtherPlayer)
        {
            m_ST_LastSeenPlayerTime = now;

            if (m_ST_NearbyFriendlySince <= 0.0)
                m_ST_NearbyFriendlySince = now;

            if ((now - m_ST_NearbyFriendlySince) >= config.SocialFriendlyTimeRequiredSeconds)
                m_ST_SocialBondActiveUntil = now + config.SocialMemoryDurationSeconds;
        }
        else
        {
            m_ST_NearbyFriendlySince = 0.0;
        }
    }


    float ST_GetLastPlayerMemoryThoughtTime()
    {
        return m_ST_LastPlayerMemoryThoughtTime;
    }

    void ST_SetLastPlayerMemoryThoughtTime(float time)
    {
        m_ST_LastPlayerMemoryThoughtTime = time;
    }

    float ST_GetLastStealthNoiseThoughtTime()
    {
        return m_ST_LastStealthNoiseThoughtTime;
    }

    void ST_SetLastStealthNoiseThoughtTime(float time)
    {
        m_ST_LastStealthNoiseThoughtTime = time;
    }

    float ST_GetLastShelterThoughtTime()
    {
        return m_ST_LastShelterThoughtTime;
    }

    void ST_SetLastShelterThoughtTime(float time)
    {
        m_ST_LastShelterThoughtTime = time;
    }

    float ST_GetLastMentalStateThoughtTime()
    {
        return m_ST_LastMentalStateThoughtTime;
    }

    void ST_SetLastMentalStateThoughtTime(float time)
    {
        m_ST_LastMentalStateThoughtTime = time;
    }

    float ST_GetLastCustomThoughtZoneThoughtTime()
    {
        return m_ST_LastCustomThoughtZoneThoughtTime;
    }

    void ST_SetLastCustomThoughtZoneThoughtTime(float time)
    {
        m_ST_LastCustomThoughtZoneThoughtTime = time;
    }

    void ST_SetMemoryFlag(string memoryType)
    {
        if (!GetGame())
            return;

        float now = GetGame().GetTime() / 1000.0;

        switch (memoryType)
        {
            case "DAMAGE":
                m_ST_RecentDamageTime = now;
                break;

            case "BLEEDING":
                m_ST_RecentBleedingTime = now;
                break;

            case "GUNSHOT":
                m_ST_RecentGunshotTime = now;
                break;

            case "CORPSE":
                m_ST_RecentCorpseTime = now;
                break;

            case "MILITARY":
                m_ST_RecentMilitaryTime = now;
                break;

            case "SURVIVAL_CRISIS":
                m_ST_RecentSurvivalCrisisTime = now;
                break;
        }

        ST_SurvivorThoughtsConfig memoryConfig = SurvivorThoughtsManager.Get().GetConfig();
        if (memoryConfig && memoryConfig.EnableJournalSystemIntegration == 1)
        {
            if (memoryType == "SURVIVAL_CRISIS" || memoryType == "GUNSHOT" || memoryType == "BLEEDING" || memoryType == "CORPSE")
                SurvivorThoughtsManager.Get().ST_AddMajorJournalEvent(this, "[PLAYER_MEMORY] Remembered event: " + memoryType);
        }

        ST_SavePersistentStateNow();
    }

    bool ST_HasMemoryFlag(string memoryType, float durationSeconds)
    {
        if (!GetGame())
            return false;

        float now = GetGame().GetTime() / 1000.0;
        float eventTime = 0.0;

        switch (memoryType)
        {
            case "DAMAGE":
                eventTime = m_ST_RecentDamageTime;
                break;

            case "BLEEDING":
                eventTime = m_ST_RecentBleedingTime;
                break;

            case "GUNSHOT":
                eventTime = m_ST_RecentGunshotTime;
                break;

            case "CORPSE":
                eventTime = m_ST_RecentCorpseTime;
                break;

            case "MILITARY":
                eventTime = m_ST_RecentMilitaryTime;
                break;

            case "SURVIVAL_CRISIS":
                eventTime = m_ST_RecentSurvivalCrisisTime;
                break;
        }

        if (eventTime <= 0.0)
            return false;

        return (now - eventTime) <= durationSeconds;
    }

    bool ST_ShouldBlockRecentThoughtMessage(string message, int memoryCount, float blockSeconds)
    {
        if (message == "" || !GetGame())
            return false;

        if (!m_ST_RecentThoughtMessages)
            m_ST_RecentThoughtMessages = new array<string>;

        if (!m_ST_RecentThoughtTimes)
            m_ST_RecentThoughtTimes = new array<float>;

        float now = GetGame().GetTime() / 1000.0;

        for (int i = 0; i < m_ST_RecentThoughtMessages.Count(); i++)
        {
            if (m_ST_RecentThoughtMessages.Get(i) == message)
            {
                float oldTime = m_ST_RecentThoughtTimes.Get(i);

                if ((now - oldTime) < blockSeconds)
                    return true;
            }
        }

        m_ST_RecentThoughtMessages.Insert(message);
        m_ST_RecentThoughtTimes.Insert(now);

        while (m_ST_RecentThoughtMessages.Count() > memoryCount)
        {
            m_ST_RecentThoughtMessages.Remove(0);
            m_ST_RecentThoughtTimes.Remove(0);
        }

        return false;
    }


    override void SetActions(out TInputActionMap InputActionMap)
    {
        super.SetActions(InputActionMap);

        AddAction(ActionSTReloadConfigs, InputActionMap);
        AddAction(ActionSTAdminHealthReport, InputActionMap);
        AddAction(ActionSTAdminTriggerCoverage, InputActionMap);
    }

    float ST_GetLastActionThoughtTime()
    {
        return m_ST_LastActionThoughtTime;
    }

    void ST_SetLastActionThoughtTime(float time)
    {
        m_ST_LastActionThoughtTime = time;
    }

    float ST_GetLastCombatStressThoughtTime()
    {
        return m_ST_LastCombatStressThoughtTime;
    }

    void ST_SetLastCombatStressThoughtTime(float time)
    {
        m_ST_LastCombatStressThoughtTime = time;
    }

    float ST_GetLastOpenCloseActionThoughtTime()
    {
        return m_ST_LastOpenCloseActionThoughtTime;
    }

    void ST_SetLastOpenCloseActionThoughtTime(float time)
    {
        m_ST_LastOpenCloseActionThoughtTime = time;
    }

    string ST_GetLastImmediateActionType()
    {
        return m_ST_LastImmediateActionType;
    }

    float ST_GetLastImmediateActionTime()
    {
        return m_ST_LastImmediateActionTime;
    }

    void ST_SetLastImmediateAction(string actionType, float time)
    {
        m_ST_LastImmediateActionType = actionType;
        m_ST_LastImmediateActionTime = time;
    }

    int ST_GetLastThoughtPriority()
    {
        return m_ST_LastThoughtPriority;
    }

    float ST_GetLastThoughtPriorityTime()
    {
        return m_ST_LastThoughtPriorityTime;
    }

    string ST_GetLastThoughtPriorityType()
    {
        return m_ST_LastThoughtPriorityType;
    }

    void ST_SetLastThoughtPriority(int priority, float time, string thoughtType)
    {
        m_ST_LastThoughtPriority = priority;
        m_ST_LastThoughtPriorityTime = time;
        m_ST_LastThoughtPriorityType = thoughtType;
    }

    override void EEHitBy(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
    {
        super.EEHitBy(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);

        if (!GetGame() || !GetGame().IsServer())
            return;

        if (!IsAlive())
            return;

        ST_SurvivorThoughtsConfig stConfig = SurvivorThoughtsManager.Get().GetConfig();
        ST_HandleDamageThought(damageResult, damageType, source, dmgZone, ammo);
        PlayerBase stAttacker = NULL;
        if (source)
            stAttacker = PlayerBase.Cast(source.GetHierarchyRootPlayer());
        if (stAttacker && stAttacker != this)
            ST_TrustLedger.Get().RecordDamageBetrayal(this, stAttacker);
    }




    override void SetActions()
    {
        super.SetActions();
        AddAction(ActionSTReadDeadSurvivorJournal);
    }

    SurvivorJournal ST_GetSurvivorJournal()
    {
        int slotId = InventorySlots.GetSlotIdFromString("SurvivorJournal");
        EntityAI attachment = GetInventory().FindAttachment(slotId);
        return SurvivorJournal.Cast(attachment);
    }

    bool ST_HasSurvivorJournal()
    {
        return ST_GetSurvivorJournal() != NULL;
    }

    SurvivorJournal ST_EnsureSurvivorJournalAttachment(ST_SurvivorThoughtsConfig config)
    {
        if (!GetGame() || !GetGame().IsServer())
            return NULL;

        if (!config || config.EnableSurvivorJournalItem != 1)
            return NULL;

        if (config.AutoEquipJournalOnFreshSpawn != 1 && config.AutoEquipJournalOnLoginIfMissing != 1 && config.GiveJournalOnFreshSpawn != 1)
            return NULL;

        SurvivorJournal existing = ST_GetSurvivorJournal();

        if (existing)
        {
            if (existing.ST_GetJournalOwnerId() == "")
                existing.ST_SetJournalOwner(ST_GetSurvivorThoughtsSteamIdSafe(), ST_GetJournalCharacterName());

            m_ST_JournalGiven = true;
            return existing;
        }

        int slotId = InventorySlots.GetSlotIdFromString("SurvivorJournal");
        EntityAI item = GetInventory().CreateAttachmentEx("SurvivorJournal", slotId);
        SurvivorJournal journal = SurvivorJournal.Cast(item);

        if (journal)
        {
            string ownerName = ST_GetJournalCharacterName();

            if (ownerName == "" && GetIdentity())
                ownerName = GetIdentity().GetName();

            journal.ST_SetJournalOwner(ST_GetSurvivorThoughtsSteamIdSafe(), ownerName);
            m_ST_JournalGiven = true;
            SurvivorThoughtsManager.Get().DebugLog("Auto-equipped locked Survivor Journal attachment.");
        }

        return journal;
    }

    string ST_GetSurvivorThoughtsSteamIdSafe()
    {
        if (GetIdentity())
            return GetIdentity().GetPlainId();

        return "";
    }

    override bool CanReleaseAttachment(EntityAI attachment)
    {
        if (!super.CanReleaseAttachment(attachment))
            return false;

        SurvivorJournal journal = SurvivorJournal.Cast(attachment);

        if (journal)
        {
            ST_SurvivorThoughtsConfig config = SurvivorThoughtsManager.Get().GetConfig();

            if (!config || config.EnableSurvivorJournalItem != 1)
                return true;

            if (config.LockJournalToPlayerWhileAlive != 1)
                return true;

            if (!IsAlive())
                return config.AllowJournalLootingAfterDeath == 1;

            return journal.ST_IsOwnerDead() && config.AllowJournalLootingAfterDeath == 1;
        }

        return true;
    }


    override void EEKilled(Object killer)
    {
        super.EEKilled(killer);

        if (!GetGame() || !GetGame().IsServer())
            return;

        ST_SurvivorThoughtsConfig killConfig = SurvivorThoughtsManager.Get().GetConfig();

        SurvivorJournal stJournal = ST_GetSurvivorJournal();
        if (stJournal)
        {
            stJournal.ST_OnCarrierKilled(this, killer);
            stJournal.ST_SetOwnerDead(true);
            SurvivorThoughtsManager.Get().DebugLog("Survivor Journal unlocked after owner death.");
        }

        if (killConfig && killConfig.WriteJournalDeathEntryOnKilled == 1 && killConfig.JournalRecordDeathEntries == 1)
        {
            string deathEntry = "Final entry: died with Health=" + ST_GetHealthValue().ToString() + ", Blood=" + ST_GetBloodValue().ToString() + ", Shock=" + ST_GetShockValue().ToString() + ".";
            SurvivorThoughtsManager.Get().ST_AddMajorJournalEvent(this, deathEntry);
        }

        ST_SavePersistentStateNow();
        SurvivorThoughtsManager.Get().NotifyNearbyPlayersOfSocialEvent(this, "TEAMMATE_DOWN");
    }

    void ST_HandleDamageThought(TotalDamageResult damageResult, int damageType, EntityAI source, string dmgZone, string ammo)
    {
        if (!damageResult)
            return;

        ST_SurvivorThoughtsConfig config = SurvivorThoughtsManager.Get().GetConfig();
        if (!config || config.EnableMod != 1)
            return;

        float healthDamage = damageResult.GetDamage(dmgZone, "Health");
        float bloodDamage = damageResult.GetDamage(dmgZone, "Blood");
        float shockDamage = damageResult.GetDamage(dmgZone, "Shock");

        bool isFallDamage = ammo.Contains("Fall") || ammo.Contains("fall");

        if (isFallDamage)
        {
            if (healthDamage < 8.0 && bloodDamage <= 0.0 && shockDamage < 18.0)
            {
                SurvivorThoughtsManager.Get().DebugLog("Trivial fall reaction suppressed.");
                return;
            }

            float fallNow = GetGame().GetTime() / 1000.0;

            if ((fallNow - m_ST_LastFallDamageThoughtTime) < 12.0)
            {
                SurvivorThoughtsManager.Get().DebugLog("Fall reaction blocked by cooldown.");
                return;
            }

            m_ST_LastFallDamageThoughtTime = fallNow;
        }

        if ((damageType == DamageType.FIRE_ARM || damageType == DamageType.EXPLOSION) && healthDamage <= 0.0 && bloodDamage <= 0.0 && shockDamage > 0.0)
        {
            m_ST_LastNearMissCombatTime = GetGame().GetTime() / 1000.0;
            SurvivorThoughtsManager.Get().DebugLog("Near-miss combat approximation detected. DamageType=" + damageType.ToString() + " ShockDamage=" + shockDamage.ToString());
        }

        string thoughtType = "COMBAT_HIT";

        if (source && source.IsZombie())
        {
            thoughtType = "ZOMBIE_HIT";
        }
        else if (damageType == DamageType.FIRE_ARM)
        {
            thoughtType = "GUNSHOT_HIT";
        }
        else if (damageType == DamageType.EXPLOSION)
        {
            thoughtType = "EXPLOSION_HIT";
        }
        else if (damageType == DamageType.CLOSE_COMBAT)
        {
            thoughtType = "PLAYER_MELEE_HIT";
        }

        ST_SetMemoryFlag("DAMAGE");
        if (thoughtType == "GUNSHOT_HIT")
            ST_SetMemoryFlag("GUNSHOT");

        if (thoughtType == "GUNSHOT_HIT" || thoughtType == "PLAYER_MELEE_HIT" || thoughtType == "COMBAT_HIT")
            SurvivorThoughtsManager.Get().NotifyNearbyPlayersOfSocialEvent(this, "TEAMMATE_SHOT");

        SurvivorThoughtsManager.Get().DebugLog("Damage event hook fired. Type=" + thoughtType + " HealthDamage=" + healthDamage.ToString() + " BloodDamage=" + bloodDamage.ToString() + " ShockDamage=" + shockDamage.ToString());
        SurvivorThoughtsManager.Get().ST_AddMajorJournalEvent(this, "[" + thoughtType + "] Took damage. HealthDamage=" + healthDamage.ToString() + " BloodDamage=" + bloodDamage.ToString() + " ShockDamage=" + shockDamage.ToString());

        // Always send the specific reaction first. Do not let HEAVY_HIT override
        // ZOMBIE_HIT, GUNSHOT_HIT, EXPLOSION_HIT, or PLAYER_MELEE_HIT.
        SurvivorThoughtsManager.Get().SendImmediateReactionThought(this, thoughtType);

        if (healthDamage >= config.HeavyHitHealthDamage_Min || shockDamage >= config.HeavyHitShockDamage_Min || bloodDamage >= config.HeavyHitBloodDamage_Min)
        {
            SurvivorThoughtsManager.Get().SendImmediateReactionThought(this, "HEAVY_HIT");
        }
    }

    override void OnBleedingSourceAdded()
    {
        super.OnBleedingSourceAdded();

        if (!GetGame() || !GetGame().IsServer())
            return;

        if (!IsAlive())
            return;

        ST_SurvivorThoughtsConfig config = SurvivorThoughtsManager.Get().GetConfig();
        if (!config || config.EnableMod != 1 || config.EnableBleedingReactionThoughts != 1)
            return;

        int bleedCount = GetBleedingSourceCount();
        m_ST_LastKnownBleedingSourceCount = bleedCount;

        ST_SetMemoryFlag("BLEEDING");

        SurvivorThoughtsManager.Get().DebugLog("Bleeding source added hook fired. Count=" + bleedCount.ToString());
        SurvivorThoughtsManager.Get().ST_AddMajorJournalEvent(this, "[BLEEDING_STARTED] Bleeding started. Sources=" + bleedCount.ToString());

        if (bleedCount > 1)
        {
            SurvivorThoughtsManager.Get().SendImmediateReactionThought(this, "BLEEDING_WORSE");
        }
        else
        {
            SurvivorThoughtsManager.Get().SendImmediateReactionThought(this, "BLEEDING_STARTED");
        }
    }

    override void OnBleedingSourceRemovedEx(ItemBase item)
    {
        super.OnBleedingSourceRemovedEx(item);

        if (!GetGame() || !GetGame().IsServer())
            return;

        if (!IsAlive())
            return;

        ST_SurvivorThoughtsConfig config = SurvivorThoughtsManager.Get().GetConfig();
        if (!config || config.EnableMod != 1 || config.EnableBleedingReactionThoughts != 1)
            return;

        int bleedCount = GetBleedingSourceCount();
        m_ST_LastKnownBleedingSourceCount = bleedCount;

        SurvivorThoughtsManager.Get().DebugLog("Bleeding source removed hook fired. Count=" + bleedCount.ToString());
        if (bleedCount <= 0)
            SurvivorThoughtsManager.Get().ST_AddMajorJournalEvent(this, "[BLEEDING_STOPPED] Bleeding stopped.");

        if (bleedCount <= 0)
        {
            SurvivorThoughtsManager.Get().SendImmediateReactionThought(this, "BLEEDING_STOPPED");
        }
    }

    void ST_CheckBleedingStateChangeImmediate()
    {
        ST_SurvivorThoughtsConfig config = SurvivorThoughtsManager.Get().GetConfig();

        if (!config || config.EnableMod != 1 || config.EnableBleedingReactionThoughts != 1)
            return;

        int currentBleedCount = GetBleedingSourceCount();

        if (m_ST_LastKnownBleedingSourceCount < 0)
        {
            m_ST_LastKnownBleedingSourceCount = 0;

            if (currentBleedCount > 0)
            {
                SurvivorThoughtsManager.Get().DebugLog("Bleeding fallback initialised while already bleeding. Count=" + currentBleedCount.ToString());

                if (currentBleedCount > 1)
                    SurvivorThoughtsManager.Get().SendImmediateReactionThought(this, "BLEEDING_WORSE");
                else
                    SurvivorThoughtsManager.Get().SendImmediateReactionThought(this, "BLEEDING_STARTED");

                m_ST_LastKnownBleedingSourceCount = currentBleedCount;
            }

            return;
        }

        if (currentBleedCount == m_ST_LastKnownBleedingSourceCount)
            return;

        SurvivorThoughtsManager.Get().DebugLog("Bleeding count changed by tick fallback. Old=" + m_ST_LastKnownBleedingSourceCount.ToString() + " New=" + currentBleedCount.ToString());

        if (currentBleedCount > m_ST_LastKnownBleedingSourceCount)
        {
            if (currentBleedCount > 1)
                SurvivorThoughtsManager.Get().SendImmediateReactionThought(this, "BLEEDING_WORSE");
            else
                SurvivorThoughtsManager.Get().SendImmediateReactionThought(this, "BLEEDING_STARTED");
        }
        else if (currentBleedCount <= 0 && m_ST_LastKnownBleedingSourceCount > 0)
        {
            SurvivorThoughtsManager.Get().SendImmediateReactionThought(this, "BLEEDING_STOPPED");
        }

        m_ST_LastKnownBleedingSourceCount = currentBleedCount;
    }


    bool ST_IsJournalSetupComplete()
    {
        return true;
    }

    string ST_GetJournalCharacterName()
    {
        return m_ST_JournalCharacterName;
    }

    string ST_GetJournalBackstory()
    {
        return m_ST_JournalBackstory;
    }

    string ST_GetJournalTrait()
    {
        return m_ST_JournalTrait;
    }

    string ST_GetJournalFear()
    {
        return m_ST_JournalFear;
    }

    string ST_GetJournalGoal()
    {
        return m_ST_JournalGoal;
    }

    string ST_GetJournalSkill()
    {
        return m_ST_JournalSkill;
    }

    string ST_GetJournalWeakness()
    {
        return m_ST_JournalWeakness;
    }

    string ST_GetJournalMoralCode()
    {
        return m_ST_JournalMoralCode;
    }


    void ST_SetJournalIdentity(string charName, string charType, string headType, string origin, string occupation, string trait, string fear, string goal, string skill, string weakness, string moralCode, string backstory)
    {
        m_ST_JournalSetupComplete = true;
        m_ST_JournalCharacterName = charName;
        m_ST_JournalCharacterType = charType;
        m_ST_JournalHeadType = headType;
        m_ST_JournalOrigin = origin;
        m_ST_JournalOccupation = occupation;
        m_ST_JournalTrait = trait;
        m_ST_JournalFear = fear;
        m_ST_JournalGoal = goal;
        m_ST_JournalSkill = skill;
        m_ST_JournalWeakness = weakness;
        m_ST_JournalMoralCode = moralCode;
        m_ST_JournalBackstory = backstory;
        SetSynchDirty();
    }

    void ST_SetJournalGiven(bool state)
    {
        m_ST_JournalGiven = state;
    }

    bool ST_HasJournalBeenGiven()
    {
        return m_ST_JournalGiven;
    }


    override void OnScheduledTick(float deltaTime)
    {
        super.OnScheduledTick(deltaTime);

        if (!GetGame() || !GetGame().IsServer())
            return;

        if (!IsAlive())
            return;

        ST_SurvivorThoughtsConfig stConfig = SurvivorThoughtsManager.Get().GetConfig();
        ST_EnsurePersistentStateLoaded(stConfig);
        ST_EnsureSurvivorJournalAttachment(stConfig);


        ST_SurvivorStorySystem.Get().UpdatePlayerStorySystems(this);

        ST_UpdateHealthDropTracker(stConfig);
        ST_UpdateSocialAwareness(stConfig);
        ST_UpdateSanityRecovery(stConfig);
        ST_UpdatePlayerStateHistory(stConfig);
        ST_CheckBleedingStateChangeImmediate();
        ST_UpdateImportantGearThoughts(stConfig);
        ST_UpdatePlayerStatStageThoughts(stConfig);
        ST_MaybeAutosavePersistentState(stConfig);

        ST_TickThoughts(deltaTime);
    }

    void ST_TickThoughts(float deltaTime)
    {
        SurvivorThoughtsManager manager = SurvivorThoughtsManager.Get();
        ST_SurvivorThoughtsConfig config = manager.GetConfig();

        if (!config || config.EnableMod != 1)
            return;

        float currentTime = GetGame().GetTime() / 1000.0;

        if (m_ST_NextThoughtDelay <= 0.0)
            m_ST_NextThoughtDelay = Math.RandomFloatInclusive(config.MinimumRandomDelaySeconds, config.MaximumRandomDelaySeconds);

        if ((currentTime - m_ST_LastThoughtTime) < m_ST_NextThoughtDelay)
            return;

        string message = ST_GetBestThoughtMessage(config);

        if (message != "")
        {
            if (m_ST_SelectedThoughtType == "")
                m_ST_SelectedThoughtType = "PASSIVE";

            manager.SendThoughtWithPriority(this, message, m_ST_SelectedThoughtType);
            m_ST_LastThoughtTime = currentTime;
            m_ST_NextThoughtDelay = Math.RandomFloatInclusive(config.MinimumRandomDelaySeconds, config.MaximumRandomDelaySeconds);
            m_ST_SelectedThoughtType = "";
        }
    }

    string ST_GetBestThoughtMessage(ST_SurvivorThoughtsConfig config)
    {
        /*
            The character voice is deliberately split into three lanes:

            1. Urgent survival: immediate danger that must be heard.
            2. Human/context: personality, mental state, weather, time, place,
               memory, social context, shelter, sanity, recovery, and environment.
            3. Routine survival: non-critical stat reminders.

            Critical/high danger always wins. When the player is not in immediate
            danger, contextual/personality thoughts receive the majority share so
            the system feels like a person rather than a spoken HUD.
        */
        array<string> urgentCritical = new array<string>;
        array<string> urgentHigh = new array<string>;
        array<string> routineMedium = new array<string>;
        array<string> routineLow = new array<string>;
        array<string> humanMedium = new array<string>;
        array<string> humanLow = new array<string>;

        // Urgent and routine physical state.
        ST_AddDeathSpiralThoughts(config, urgentCritical);
        ST_AddBleedingThoughts(config, urgentCritical, urgentHigh);
        ST_AddBrokenLegThoughts(config, urgentCritical, urgentHigh);
        ST_AddSicknessThoughts(config, urgentCritical, urgentHigh, routineMedium);
        ST_AddInfectedNearbyThoughts(config, urgentHigh, routineMedium, routineLow);
        ST_AddCombatStressThoughts(config, urgentHigh, routineMedium);
        ST_AddContaminatedZoneThoughts(config, urgentCritical, urgentHigh);
        ST_AddNearMissCombatThoughts(config, urgentHigh, routineMedium);
        ST_AddDiseaseSpecificThoughts(config, urgentHigh, routineMedium);
        ST_AddStateHistoryThoughts(config, urgentHigh, humanMedium, humanLow);

        // Human/context lane. These systems are intentionally not mixed into the
        // routine stat arrays, otherwise the stat pools dominate by sheer count.
        ST_AddWeatherThoughts(config, humanMedium, humanMedium, humanLow);
        ST_AddTimeOfDayThoughts(config, humanMedium, humanLow);
        ST_AddLocationThoughts(config, humanMedium, humanLow);
        ST_AddNearbyCorpseThoughts(config, humanMedium, humanLow);
        ST_AddPlayerMemoryThoughts(config, humanMedium, humanLow);
        ST_AddStealthNoiseThoughts(config, humanMedium, humanLow);
        ST_AddShelterThoughts(config, humanMedium, humanLow);
        ST_AddMentalStateThoughts(config, humanMedium, humanMedium, humanLow);
        ST_AddCustomThoughtZoneThoughts(config, humanMedium, humanLow);
        ST_AddSocialGroupThoughts(config, humanMedium, humanLow);
        ST_AddRecoveryThoughts(config, humanMedium, humanLow);
        ST_AddMapEnvironmentThoughts(config, humanLow);
        ST_AddSanityCreepThoughts(config, humanMedium, humanMedium, humanLow);
        ST_AddPersonalityThoughts(config, humanLow);

        // Immediate danger is never sacrificed for ambience.
        if (urgentCritical.Count() > 0)
        {
            m_ST_SelectedThoughtType = "CRITICAL_SURVIVAL";
            return urgentCritical.GetRandomElement();
        }

        if (urgentHigh.Count() > 0)
        {
            m_ST_SelectedThoughtType = "HIGH_SURVIVAL";
            return urgentHigh.GetRandomElement();
        }

        bool hasHuman = humanMedium.Count() > 0 || humanLow.Count() > 0;
        bool hasRoutine = routineMedium.Count() > 0 || routineLow.Count() > 0;

        /*
            70% contextual/human voice, 30% routine physical state whenever both
            lanes have candidates. This prevents hunger/thirst/temperature from
            monopolising ordinary play while still allowing them through.
        */
        if (hasHuman && hasRoutine)
        {
            float laneRoll = Math.RandomFloatInclusive(0.0, 1.0);

            if (laneRoll <= 0.70)
                return ST_SelectHumanThought(humanMedium, humanLow);

            return ST_SelectRoutineThought(config, routineMedium, routineLow);
        }

        if (hasHuman)
            return ST_SelectHumanThought(humanMedium, humanLow);

        if (hasRoutine)
            return ST_SelectRoutineThought(config, routineMedium, routineLow);

        return "";
    }

    string ST_SelectHumanThought(array<string> medium, array<string> low)
    {
        if (medium && medium.Count() > 0)
        {
            m_ST_SelectedThoughtType = "HUMAN_CONTEXT";
            return medium.GetRandomElement();
        }

        if (low && low.Count() > 0)
        {
            m_ST_SelectedThoughtType = "PERSONALITY_AMBIENT";
            return low.GetRandomElement();
        }

        return "";
    }

    string ST_SelectRoutineThought(ST_SurvivorThoughtsConfig config, array<string> medium, array<string> low)
    {
        /*
            Combined thoughts now belong only to the routine lane. They no longer
            pre-empt weather, time, personality, memory, or mental-state output.
        */
        if (config.EnableCombinedThoughts == 1)
        {
            float roll = Math.RandomFloatInclusive(0.0, 1.0);

            if (roll <= config.CombinedThoughtChance)
            {
                string combinedMessage = ST_GetCombinedThoughtMessage(config);

                if (combinedMessage != "")
                {
                    m_ST_SelectedThoughtType = "MEDIUM_SURVIVAL";
                    return combinedMessage;
                }
            }
        }

        if (medium && medium.Count() > 0)
        {
            m_ST_SelectedThoughtType = "MEDIUM_SURVIVAL";
            return medium.GetRandomElement();
        }

        if (low && low.Count() > 0)
        {
            m_ST_SelectedThoughtType = "LOW_SURVIVAL";
            return low.GetRandomElement();
        }

        return "";
    }

    string ST_GetCombinedThoughtMessage(ST_SurvivorThoughtsConfig config)
    {
        array<string> parts = new array<string>;

        bool hasHunger = ST_AddCombinedHungerThought(config, parts);
        bool hasThirst = ST_AddCombinedThirstThought(config, parts);
        bool hasCold = ST_AddCombinedColdThought(config, parts);
        bool hasHot = ST_AddCombinedHotThought(config, parts);
        bool hasSick = ST_AddCombinedSicknessThought(config, parts);
        bool hasBleeding = ST_AddCombinedBleedingThought(config, parts);
        bool hasBlood = ST_AddCombinedBloodThought(config, parts);
        bool hasShock = ST_AddCombinedShockThought(config, parts);
        bool hasBrokenLeg = ST_AddCombinedBrokenLegThought(config, parts);
        bool hasInfected = ST_AddCombinedInfectedThought(config, parts);
        bool hasWeather = ST_AddCombinedWeatherThought(config, parts);
        bool hasTimeOfDay = ST_AddCombinedTimeOfDayThought(config, parts);
        bool hasBadItem = ST_AddCombinedItemConditionThought(config, parts);
        bool hasCombatStress = ST_AddCombinedCombatStressThought(config, parts);
        bool hasContamination = ST_AddCombinedContaminatedZoneThought(config, parts);
        bool hasCorpse = ST_AddCombinedNearbyCorpseThought(config, parts);

        int activeCount = 0;

        if (hasHunger) activeCount++;
        if (hasThirst) activeCount++;
        if (hasCold) activeCount++;
        if (hasHot) activeCount++;
        if (hasSick) activeCount++;
        if (hasBleeding) activeCount++;
        if (hasBlood) activeCount++;
        if (hasShock) activeCount++;
        if (hasBrokenLeg) activeCount++;
        if (hasInfected) activeCount++;
        if (hasWeather) activeCount++;
        if (hasTimeOfDay) activeCount++;
        if (hasBadItem) activeCount++;
        if (hasCombatStress) activeCount++;
        if (hasContamination) activeCount++;
        if (hasCorpse) activeCount++;

        if (activeCount < 2)
            return "";

        ST_AdvancedCombinedState advancedState = new ST_AdvancedCombinedState();
        advancedState.HasHunger = hasHunger;
        advancedState.HasThirst = hasThirst;
        advancedState.HasCold = hasCold;
        advancedState.HasHot = hasHot;
        advancedState.HasSick = hasSick;
        advancedState.HasBleeding = hasBleeding;
        advancedState.HasBlood = hasBlood;
        advancedState.HasShock = hasShock;
        advancedState.HasBrokenLeg = hasBrokenLeg;
        advancedState.HasInfected = hasInfected;
        advancedState.HasWeather = hasWeather;
        advancedState.HasTimeOfDay = hasTimeOfDay;
        advancedState.HasBadItem = hasBadItem;
        advancedState.HasCombatStress = hasCombatStress;
        advancedState.HasContamination = hasContamination;
        advancedState.HasCorpse = hasCorpse;

        float stSanityForAdvancedCombos = ST_GetSanityValue(config);
        advancedState.HasLowSanity = stSanityForAdvancedCombos <= config.SanityUnhingedThreshold;

        float stNowForAdvancedCombos = 0.0;
        if (GetGame())
            stNowForAdvancedCombos = GetGame().GetTime() / 1000.0;

        advancedState.HasRecentGunshot = false;
        if (m_ST_RecentGunshotTime > 0.0 && (stNowForAdvancedCombos - m_ST_RecentGunshotTime) <= config.PlayerMemoryDurationSeconds)
            advancedState.HasRecentGunshot = true;

        advancedState.HasCompanionBond = false;
        if (m_ST_SocialBondActiveUntil > stNowForAdvancedCombos)
            advancedState.HasCompanionBond = true;

        string advancedCombinedMessage = ST_GetAdvancedCombinedThoughtMessage(config, advancedState);
        if (advancedCombinedMessage != "")
        {
            m_ST_SelectedThoughtType = "ADVANCED_COMBINED";
            return advancedCombinedMessage;
        }

        // Broad emergency fallbacks. These stop the config needing hundreds of exact 4+ state arrays.
        if (activeCount >= config.UseCriticalSurvivalMessagesAtStateCount && config.CriticalSurvivalMessages && config.CriticalSurvivalMessages.Count() > 0)
            return config.CriticalSurvivalMessages.GetRandomElement();

        if (activeCount >= config.UseExtremeSurvivalMessagesAtStateCount && config.ExtremeSurvivalMessages && config.ExtremeSurvivalMessages.Count() > 0)
            return config.ExtremeSurvivalMessages.GetRandomElement();

        // Exact 3-state combo pools first. These sound better than joined status lines.
        if (hasBrokenLeg && hasCold && hasInfected && config.BrokenLegColdInfectedMessages && config.BrokenLegColdInfectedMessages.Count() > 0)
            return config.BrokenLegColdInfectedMessages.GetRandomElement();

        if (hasBrokenLeg && hasBleeding && hasInfected && config.BrokenLegBleedingInfectedMessages && config.BrokenLegBleedingInfectedMessages.Count() > 0)
            return config.BrokenLegBleedingInfectedMessages.GetRandomElement();

        if (hasBrokenLeg && hasHunger && hasThirst && config.BrokenLegHungerThirstMessages && config.BrokenLegHungerThirstMessages.Count() > 0)
            return config.BrokenLegHungerThirstMessages.GetRandomElement();

        if (hasHunger && hasThirst && hasCold && config.HungerThirstColdMessages && config.HungerThirstColdMessages.Count() > 0)
            return config.HungerThirstColdMessages.GetRandomElement();

        if (hasHunger && hasThirst && hasHot && config.HungerThirstHotMessages && config.HungerThirstHotMessages.Count() > 0)
            return config.HungerThirstHotMessages.GetRandomElement();

        if (hasHunger && hasThirst && hasInfected && config.HungerThirstInfectedMessages && config.HungerThirstInfectedMessages.Count() > 0)
            return config.HungerThirstInfectedMessages.GetRandomElement();

        if (hasHunger && hasCold && hasInfected && config.HungerColdInfectedMessages && config.HungerColdInfectedMessages.Count() > 0)
            return config.HungerColdInfectedMessages.GetRandomElement();

        if (hasThirst && hasHot && hasInfected && config.ThirstHotInfectedMessages && config.ThirstHotInfectedMessages.Count() > 0)
            return config.ThirstHotInfectedMessages.GetRandomElement();

        if (hasSick && hasCold && hasInfected && config.SickColdInfectedMessages && config.SickColdInfectedMessages.Count() > 0)
            return config.SickColdInfectedMessages.GetRandomElement();

        if (hasBleeding && hasCold && hasInfected && config.BleedingColdInfectedMessages && config.BleedingColdInfectedMessages.Count() > 0)
            return config.BleedingColdInfectedMessages.GetRandomElement();

        if (hasBleeding && hasSick && hasInfected && config.BleedingSickInfectedMessages && config.BleedingSickInfectedMessages.Count() > 0)
            return config.BleedingSickInfectedMessages.GetRandomElement();

        // Exact 2-state combo pools.
        if (hasHunger && hasThirst && config.HungerThirstMessages && config.HungerThirstMessages.Count() > 0)
            return config.HungerThirstMessages.GetRandomElement();

        if (hasHunger && hasCold && config.HungerColdMessages && config.HungerColdMessages.Count() > 0)
            return config.HungerColdMessages.GetRandomElement();

        if (hasHunger && hasHot && config.HungerHotMessages && config.HungerHotMessages.Count() > 0)
            return config.HungerHotMessages.GetRandomElement();

        if (hasHunger && hasSick && config.HungerSickMessages && config.HungerSickMessages.Count() > 0)
            return config.HungerSickMessages.GetRandomElement();

        if (hasHunger && hasBleeding && config.HungerBleedingMessages && config.HungerBleedingMessages.Count() > 0)
            return config.HungerBleedingMessages.GetRandomElement();

        if (hasHunger && hasInfected && config.HungerInfectedMessages && config.HungerInfectedMessages.Count() > 0)
            return config.HungerInfectedMessages.GetRandomElement();

        if (hasThirst && hasCold && config.ThirstColdMessages && config.ThirstColdMessages.Count() > 0)
            return config.ThirstColdMessages.GetRandomElement();

        if (hasThirst && hasHot && config.HotThirstMessages && config.HotThirstMessages.Count() > 0)
            return config.HotThirstMessages.GetRandomElement();

        if (hasThirst && hasSick && config.SickThirstMessages && config.SickThirstMessages.Count() > 0)
            return config.SickThirstMessages.GetRandomElement();

        if (hasThirst && hasBleeding && config.ThirstBleedingMessages && config.ThirstBleedingMessages.Count() > 0)
            return config.ThirstBleedingMessages.GetRandomElement();

        if (hasThirst && hasInfected && config.ThirstInfectedMessages && config.ThirstInfectedMessages.Count() > 0)
            return config.ThirstInfectedMessages.GetRandomElement();

        if (hasCold && hasSick && config.SickColdMessages && config.SickColdMessages.Count() > 0)
            return config.SickColdMessages.GetRandomElement();

        if (hasCold && hasBleeding && config.BleedingColdMessages && config.BleedingColdMessages.Count() > 0)
            return config.BleedingColdMessages.GetRandomElement();

        if (hasCold && hasInfected && config.ColdInfectedMessages && config.ColdInfectedMessages.Count() > 0)
            return config.ColdInfectedMessages.GetRandomElement();

        if (hasHot && hasSick && config.HotSickMessages && config.HotSickMessages.Count() > 0)
            return config.HotSickMessages.GetRandomElement();

        if (hasHot && hasBleeding && config.HotBleedingMessages && config.HotBleedingMessages.Count() > 0)
            return config.HotBleedingMessages.GetRandomElement();

        if (hasHot && hasInfected && config.HotInfectedMessages && config.HotInfectedMessages.Count() > 0)
            return config.HotInfectedMessages.GetRandomElement();

        if (hasSick && hasBleeding && config.SickBleedingMessages && config.SickBleedingMessages.Count() > 0)
            return config.SickBleedingMessages.GetRandomElement();

        if (hasSick && hasInfected && config.SickInfectedMessages && config.SickInfectedMessages.Count() > 0)
            return config.SickInfectedMessages.GetRandomElement();

        if (hasBleeding && hasInfected && config.BleedingInfectedMessages && config.BleedingInfectedMessages.Count() > 0)
            return config.BleedingInfectedMessages.GetRandomElement();

        if (hasBrokenLeg && hasHunger && config.BrokenLegHungerMessages && config.BrokenLegHungerMessages.Count() > 0)
            return config.BrokenLegHungerMessages.GetRandomElement();

        if (hasBrokenLeg && hasThirst && config.BrokenLegThirstMessages && config.BrokenLegThirstMessages.Count() > 0)
            return config.BrokenLegThirstMessages.GetRandomElement();

        if (hasBrokenLeg && hasCold && config.BrokenLegColdMessages && config.BrokenLegColdMessages.Count() > 0)
            return config.BrokenLegColdMessages.GetRandomElement();

        if (hasBrokenLeg && hasHot && config.BrokenLegHotMessages && config.BrokenLegHotMessages.Count() > 0)
            return config.BrokenLegHotMessages.GetRandomElement();

        if (hasBrokenLeg && hasSick && config.BrokenLegSickMessages && config.BrokenLegSickMessages.Count() > 0)
            return config.BrokenLegSickMessages.GetRandomElement();

        if (hasBrokenLeg && hasBleeding && config.BrokenLegBleedingMessages && config.BrokenLegBleedingMessages.Count() > 0)
            return config.BrokenLegBleedingMessages.GetRandomElement();

        if (hasBrokenLeg && hasInfected && config.BrokenLegInfectedMessages && config.BrokenLegInfectedMessages.Count() > 0)
            return config.BrokenLegInfectedMessages.GetRandomElement();

        // Last fallback: join one active line from each state so every possible mixture still works.
        return ST_BuildJoinedThought(parts, config.MaxCombinedThoughtParts);
    }

    string ST_BuildJoinedThought(array<string> parts, int maxParts)
    {
        if (!parts || parts.Count() == 0)
            return "";

        if (maxParts <= 0)
            maxParts = 3;

        while (parts.Count() > maxParts)
        {
            parts.Remove(Math.RandomInt(0, parts.Count()));
        }

        if (parts.Count() == 1)
            return parts[0];

        string finalMessage = "";

        for (int i = 0; i < parts.Count(); i++)
        {
            if (i > 0)
                finalMessage = finalMessage + " ";

            finalMessage = finalMessage + parts[i];
        }

        return finalMessage;
    }

    bool ST_AddRandomPart(array<string> source, array<string> parts)
    {
        if (!source || source.Count() == 0)
            return false;

        parts.Insert(source.GetRandomElement());
        return true;
    }

    bool ST_IsValueInRange(float value, float minValue, float maxValue)
    {
        return value >= minValue && value <= maxValue;
    }

    float ST_GetEnergyValue()
    {
        if (!GetStatEnergy())
            return 0.0;

        return GetStatEnergy().Get();
    }

    float ST_GetWaterValue()
    {
        if (!GetStatWater())
            return 0.0;

        return GetStatWater().Get();
    }

    float ST_GetBloodValue()
    {
        return GetHealth("", "Blood");
    }

    float ST_GetShockValue()
    {
        // Shock is not exposed as GetStatShock() in vanilla.
        // Vanilla ShockHandler reads current shock from GetHealth("", "Shock")
        // and syncs it through m_CurrentShock.
        return GetHealth("", "Shock");
    }

    float ST_GetHealthValue()
    {
        return GetHealth("", "Health");
    }

    float ST_GetHeatComfortValue()
    {
        if (!GetStatHeatComfort())
            return 0.0;

        return GetStatHeatComfort().Get();
    }

    void ST_InsertRandomStageMessage(array<string> source, array<string> target)
    {
        if (!source || !target || source.Count() == 0)
            return;

        target.Insert(source.GetRandomElement());
    }

    bool ST_AddCombinedHungerThought(ST_SurvivorThoughtsConfig config, array<string> parts)
    {
        if (config.EnableHungerMessages != 1)
            return false;

        float energy = ST_GetEnergyValue();

        if (ST_IsValueInRange(energy, config.EnergyStage1_Min, config.EnergyStage1_Max))
        {
            if (config.EnableEnergyStage1Messages == 1)
                return ST_AddRandomPart(config.EnergyStage1Messages, parts);

            return false;
        }

        if (ST_IsValueInRange(energy, config.EnergyStage2_Min, config.EnergyStage2_Max) && config.EnableEnergyStage2Messages == 1)
            return ST_AddRandomPart(config.EnergyStage2Messages, parts);

        if (ST_IsValueInRange(energy, config.EnergyStage3_Min, config.EnergyStage3_Max) && config.EnableEnergyStage3Messages == 1)
            return ST_AddRandomPart(config.EnergyStage3Messages, parts);

        if (ST_IsValueInRange(energy, config.EnergyStage4_Min, config.EnergyStage4_Max) && config.EnableEnergyStage4Messages == 1)
            return ST_AddRandomPart(config.EnergyStage4Messages, parts);

        return false;
    }

    bool ST_AddCombinedThirstThought(ST_SurvivorThoughtsConfig config, array<string> parts)
    {
        if (config.EnableThirstMessages != 1)
            return false;

        float water = ST_GetWaterValue();

        if (ST_IsValueInRange(water, config.WaterStage1_Min, config.WaterStage1_Max))
        {
            if (config.EnableWaterStage1Messages == 1)
                return ST_AddRandomPart(config.WaterStage1Messages, parts);

            return false;
        }

        if (ST_IsValueInRange(water, config.WaterStage2_Min, config.WaterStage2_Max) && config.EnableWaterStage2Messages == 1)
            return ST_AddRandomPart(config.WaterStage2Messages, parts);

        if (ST_IsValueInRange(water, config.WaterStage3_Min, config.WaterStage3_Max) && config.EnableWaterStage3Messages == 1)
            return ST_AddRandomPart(config.WaterStage3Messages, parts);

        if (ST_IsValueInRange(water, config.WaterStage4_Min, config.WaterStage4_Max) && config.EnableWaterStage4Messages == 1)
            return ST_AddRandomPart(config.WaterStage4Messages, parts);

        return false;
    }

    bool ST_AddCombinedColdThought(ST_SurvivorThoughtsConfig config, array<string> parts)
    {
        if (config.EnableColdMessages != 1)
            return false;

        float comfort = ST_GetHeatComfortValue();

        if (comfort <= -0.75)
            return ST_AddRandomPart(config.Cold_Critical_Messages, parts);

        if (comfort <= -0.50)
            return ST_AddRandomPart(config.Cold_Severe_Messages, parts);

        if (comfort <= -0.25)
            return ST_AddRandomPart(config.Cold_Moderate_Messages, parts);

        if (comfort <= -0.10)
            return ST_AddRandomPart(config.Cold_Mild_Messages, parts);

        return false;
    }

    bool ST_AddCombinedHotThought(ST_SurvivorThoughtsConfig config, array<string> parts)
    {
        if (config.EnableHotMessages != 1)
            return false;

        float comfort = ST_GetHeatComfortValue();

        if (comfort >= 0.75)
            return ST_AddRandomPart(config.Hot_Critical_Messages, parts);

        if (comfort >= 0.50)
            return ST_AddRandomPart(config.Hot_Severe_Messages, parts);

        if (comfort >= 0.25)
            return ST_AddRandomPart(config.Hot_Moderate_Messages, parts);

        if (comfort >= 0.10)
            return ST_AddRandomPart(config.Hot_Mild_Messages, parts);

        return false;
    }


    bool ST_IsModifierActiveSafe(eModifiers modifier_id)
    {
        ModifiersManager modifiersManager = GetModifiersManager();

        if (!modifiersManager)
            return false;

        ModifierBase modifier = modifiersManager.GetModifier(modifier_id);

        if (!modifier)
            return false;

        return modifier.IsActive();
    }

    bool ST_AddCombinedSicknessThought(ST_SurvivorThoughtsConfig config, array<string> parts)
    {
        if (config.EnableSicknessMessages != 1)
            return false;

        if (!GetModifiersManager())
            return false;

        if (ST_IsModifierActiveSafe(eModifiers.MDF_WOUND_INFECTION))
            return ST_AddRandomPart(config.Sickness_Critical_Messages, parts);

        if (ST_IsModifierActiveSafe(eModifiers.MDF_CHOLERA))
            return ST_AddRandomPart(config.Sickness_Severe_Messages, parts);

        if (ST_IsModifierActiveSafe(eModifiers.MDF_INFLUENZA))
            return ST_AddRandomPart(config.Sickness_Moderate_Messages, parts);

        if (ST_IsModifierActiveSafe(eModifiers.MDF_COMMON_COLD))
            return ST_AddRandomPart(config.Sickness_Early_Messages, parts);

        return false;
    }

    bool ST_AddCombinedBleedingThought(ST_SurvivorThoughtsConfig config, array<string> parts)
    {
        if (config.EnableBleedingMessages != 1)
            return false;

        int bleedCount = GetBleedingSourceCount();

        if (bleedCount <= 0)
            return false;

        if (bleedCount == 1)
            return ST_AddRandomPart(config.Bleeding_One_Messages, parts);

        if (bleedCount <= 3)
            return ST_AddRandomPart(config.Bleeding_Multiple_Messages, parts);

        return ST_AddRandomPart(config.Bleeding_Critical_Messages, parts);
    }

    bool ST_AddCombinedBloodThought(ST_SurvivorThoughtsConfig config, array<string> parts)
    {
        float blood = ST_GetBloodValue();

        if (ST_IsValueInRange(blood, config.BloodStage1_Min, config.BloodStage1_Max))
        {
            if (config.EnableBloodStage1Messages == 1)
                return ST_AddRandomPart(config.BloodStage1Messages, parts);

            return false;
        }

        if (ST_IsValueInRange(blood, config.BloodStage2_Min, config.BloodStage2_Max) && config.EnableBloodStage2Messages == 1)
            return ST_AddRandomPart(config.BloodStage2Messages, parts);

        if (ST_IsValueInRange(blood, config.BloodStage3_Min, config.BloodStage3_Max) && config.EnableBloodStage3Messages == 1)
            return ST_AddRandomPart(config.BloodStage3Messages, parts);

        if (ST_IsValueInRange(blood, config.BloodStage4_Min, config.BloodStage4_Max) && config.EnableBloodStage4Messages == 1)
            return ST_AddRandomPart(config.BloodStage4Messages, parts);

        return false;
    }

    bool ST_AddCombinedShockThought(ST_SurvivorThoughtsConfig config, array<string> parts)
    {
        float shock = ST_GetShockValue();

        if (ST_IsValueInRange(shock, config.ShockStage1_Min, config.ShockStage1_Max))
        {
            if (config.EnableShockStage1Messages == 1)
                return ST_AddRandomPart(config.ShockStage1Messages, parts);

            return false;
        }

        if (ST_IsValueInRange(shock, config.ShockStage2_Min, config.ShockStage2_Max) && config.EnableShockStage2Messages == 1)
            return ST_AddRandomPart(config.ShockStage2Messages, parts);

        if (ST_IsValueInRange(shock, config.ShockStage3_Min, config.ShockStage3_Max) && config.EnableShockStage3Messages == 1)
            return ST_AddRandomPart(config.ShockStage3Messages, parts);

        if (ST_IsValueInRange(shock, config.ShockStage4_Min, config.ShockStage4_Max) && config.EnableShockStage4Messages == 1)
            return ST_AddRandomPart(config.ShockStage4Messages, parts);

        return false;
    }

    bool ST_HasBrokenLeg()
    {
        return GetBrokenLegs() != eBrokenLegs.NO_BROKEN_LEGS;
    }

    bool ST_AddCombinedBrokenLegThought(ST_SurvivorThoughtsConfig config, array<string> parts)
    {
        if (config.EnableBrokenLegMessages != 1)
            return false;

        if (!ST_HasBrokenLeg())
            return false;

        return ST_AddRandomPart(config.BrokenLegMessages, parts);
    }

    bool ST_AddCombinedInfectedThought(ST_SurvivorThoughtsConfig config, array<string> parts)
    {
        if (config.EnableInfectedNearbyMessages != 1)
            return false;

        array<Object> nearbyObjects = new array<Object>;
        array<CargoBase> proxyCargos = new array<CargoBase>;

        if (!GetGame())
            return false;

        GetGame().GetObjectsAtPosition3D(GetPosition(), config.InfectedFarRadius, nearbyObjects, proxyCargos);

        int infectedCount = 0;
        float closestDistance = 99999.0;

        foreach (Object obj : nearbyObjects)
        {
            ZombieBase infected = ZombieBase.Cast(obj);

            if (!infected)
                continue;

            if (!infected.IsAlive())
                continue;

            infectedCount++;

            float distance = vector.Distance(GetPosition(), infected.GetPosition());

            if (distance < closestDistance)
                closestDistance = distance;
        }

        if (infectedCount <= 0)
            return false;

        if (infectedCount >= config.InfectedSurroundedCount)
            return ST_AddRandomPart(config.Infected_Surrounded_Messages, parts);

        if (closestDistance <= config.InfectedVeryCloseRadius)
            return ST_AddRandomPart(config.Infected_VeryClose_Messages, parts);

        if (closestDistance <= config.InfectedCloseRadius)
            return ST_AddRandomPart(config.Infected_Close_Messages, parts);

        return ST_AddRandomPart(config.Infected_Far_Messages, parts);
    }

    void ST_UpdateHealthDropTracker(ST_SurvivorThoughtsConfig config)
    {
        if (!config || !GetGame())
            return;

        float health = ST_GetHealthValue();

        if (m_ST_LastHealthValue >= 0.0)
        {
            if (health < (m_ST_LastHealthValue - config.HealthDropMinAmount))
            {
                m_ST_LastHealthDropTime = GetGame().GetTime() / 1000.0;
                SurvivorThoughtsManager.Get().DebugLog("Health drop detected. Old=" + m_ST_LastHealthValue.ToString() + " New=" + health.ToString());
            }
        }

        m_ST_LastHealthValue = health;
    }

    bool ST_IsHealthRecentlyDropping(ST_SurvivorThoughtsConfig config)
    {
        if (!config || !GetGame())
            return false;

        if (m_ST_LastHealthDropTime <= 0.0)
            return false;

        float now = GetGame().GetTime() / 1000.0;

        return (now - m_ST_LastHealthDropTime) <= config.HealthDropRecentSeconds;
    }

    void ST_AddDeathSpiralThoughts(ST_SurvivorThoughtsConfig config, array<string> critical)
    {
        if (!config || config.EnableDeathSpiralThoughts != 1)
            return;

        if (!ST_IsHealthRecentlyDropping(config))
            return;

        ST_SetMemoryFlag("SURVIVAL_CRISIS");

        float energy = ST_GetEnergyValue();
        float water = ST_GetWaterValue();
        float comfort = ST_GetHeatComfortValue();

        if (config.EnableStarvingToDeathMessages == 1 && energy <= config.EnergyStage4_Max)
        {
            ST_InsertRandomStageMessage(config.StarvingToDeathMessages, critical);
            return;
        }

        if (config.EnableDehydratingToDeathMessages == 1 && water <= config.WaterStage4_Max)
        {
            ST_InsertRandomStageMessage(config.DehydratingToDeathMessages, critical);
            return;
        }

        if (config.EnableFreezingToDeathMessages == 1 && comfort <= config.DeathSpiralColdComfort_Max)
        {
            ST_InsertRandomStageMessage(config.FreezingToDeathMessages, critical);
            return;
        }

        if (config.EnableOverheatingToDeathMessages == 1 && comfort >= config.DeathSpiralHotComfort_Min)
        {
            ST_InsertRandomStageMessage(config.OverheatingToDeathMessages, critical);
            return;
        }
    }

    void ST_UpdatePlayerStatStageThoughts(ST_SurvivorThoughtsConfig config)
    {
        if (!config || config.EnableMod != 1)
            return;

        int energyStage = 0;
        float energyValue = ST_GetEnergyValue();

        if (energyValue <= config.EnergyStage4_Max)
            energyStage = 3;
        else if (energyValue <= config.EnergyStage3_Max)
            energyStage = 2;
        else if (energyValue <= config.EnergyStage2_Max)
            energyStage = 1;

        int waterStage = 0;
        float waterValue = ST_GetWaterValue();

        if (waterValue <= config.WaterStage4_Max)
            waterStage = 3;
        else if (waterValue <= config.WaterStage3_Max)
            waterStage = 2;
        else if (waterValue <= config.WaterStage2_Max)
            waterStage = 1;

        int bloodStage = 0;
        float bloodValue = ST_GetBloodValue();

        if (bloodValue <= config.BloodStage4_Max)
            bloodStage = 3;
        else if (bloodValue <= config.BloodStage3_Max)
            bloodStage = 2;
        else if (bloodValue <= config.BloodStage2_Max)
            bloodStage = 1;

        int shockStage = 0;
        float shockValue = ST_GetShockValue();

        if (shockValue <= config.ShockStage4_Max)
            shockStage = 3;
        else if (shockValue <= config.ShockStage3_Max)
            shockStage = 2;
        else if (shockValue <= config.ShockStage2_Max)
            shockStage = 1;

        int healthStage = ST_GetHealthWarningStage();
        int temperatureStage = ST_GetTemperatureWarningStage();

        int redMask = 0;

        if (energyStage == 2)
            redMask = redMask | 1;

        if (waterStage == 2)
            redMask = redMask | 2;

        if (bloodStage == 2)
            redMask = redMask | 4;

        if (shockStage == 2)
            redMask = redMask | 8;

        if (healthStage == 2)
            redMask = redMask | 16;

        if (temperatureStage == 2)
            redMask = redMask | 32;

        bool sentCombinedRed = false;

        int redCount = 0;

        if ((redMask & 1) != 0)
            redCount++;

        if ((redMask & 2) != 0)
            redCount++;

        if ((redMask & 4) != 0)
            redCount++;

        if ((redMask & 8) != 0)
            redCount++;

        if ((redMask & 16) != 0)
            redCount++;

        if ((redMask & 32) != 0)
            redCount++;

        if (redCount > 1 && redMask != m_ST_LastCombinedRedMask)
        {
            array<string> redProblems = new array<string>;

            if ((redMask & 1) != 0)
                redProblems.Insert("hunger");

            if ((redMask & 2) != 0)
                redProblems.Insert("thirst");

            if ((redMask & 4) != 0)
                redProblems.Insert("blood loss");

            if ((redMask & 8) != 0)
                redProblems.Insert("shock");

            if ((redMask & 16) != 0)
                redProblems.Insert("injuries");

            if ((redMask & 32) != 0)
            {
                if (ST_GetHeatComfortValue() < 0.0)
                    redProblems.Insert("cold");
                else
                    redProblems.Insert("heat");
            }

            string joinedProblems = "";

            if (redProblems.Count() > 0)
                joinedProblems = redProblems.Get(0);

            for (int redIndex = 1; redIndex < redProblems.Count(); redIndex++)
            {
                if (redIndex == redProblems.Count() - 1)
                    joinedProblems += " and " + redProblems.Get(redIndex);
                else
                    joinedProblems += ", " + redProblems.Get(redIndex);
            }

            array<string> combinedMessages = new array<string>;
            combinedMessages.Insert("Too much is going wrong at once: " + joinedProblems + ".");
            combinedMessages.Insert("My body is struggling with " + joinedProblems + ".");
            combinedMessages.Insert("I need to deal with this now. " + joinedProblems + " are becoming dangerous.");
            combinedMessages.Insert("I cannot ignore this anymore. " + joinedProblems + " are pushing me too far.");

            string combinedMessage = combinedMessages.GetRandomElement();
            SurvivorThoughtsManager.Get().SendThoughtWithPriority(this, combinedMessage, "STAT_MULTI_RED");
            sentCombinedRed = true;
        }

        m_ST_LastCombinedRedMask = redMask;

        if (!sentCombinedRed)
        {
            ST_ProcessPlayerStatStage("ENERGY", m_ST_LastEnergyStage, energyStage, config.EnableHungerMessages, config.EnableEnergyStage2Messages, config.EnableEnergyStage3Messages, config.EnableEnergyStage4Messages, config.EnergyStage2Messages, config.EnergyStage3Messages, config.EnergyStage4Messages);
        }

        m_ST_LastEnergyStage = energyStage;

        ST_ProcessPlayerStatStage("WATER", m_ST_LastWaterStage, waterStage, config.EnableThirstMessages, config.EnableWaterStage2Messages, config.EnableWaterStage3Messages, config.EnableWaterStage4Messages, config.WaterStage2Messages, config.WaterStage3Messages, config.WaterStage4Messages);
        m_ST_LastWaterStage = waterStage;

        ST_ProcessPlayerStatStage("BLOOD", m_ST_LastBloodStage, bloodStage, 1, config.EnableBloodStage2Messages, config.EnableBloodStage3Messages, config.EnableBloodStage4Messages, config.BloodStage2Messages, config.BloodStage3Messages, config.BloodStage4Messages);
        m_ST_LastBloodStage = bloodStage;

        ST_ProcessPlayerStatStage("SHOCK", m_ST_LastShockStage, shockStage, 1, config.EnableShockStage2Messages, config.EnableShockStage3Messages, config.EnableShockStage4Messages, config.ShockStage2Messages, config.ShockStage3Messages, config.ShockStage4Messages);
        m_ST_LastShockStage = shockStage;

        ST_ProcessHealthStage(m_ST_LastHealthStage, healthStage);
        m_ST_LastHealthStage = healthStage;

        ST_ProcessTemperatureStage(config, m_ST_LastTemperatureStage, temperatureStage);
        m_ST_LastTemperatureStage = temperatureStage;
    }

    int ST_GetHealthWarningStage()
    {
        float health = GetHealth("", "Health");

        if (health <= 20.0)
            return 3;
        if (health <= 40.0)
            return 2;
        if (health <= 70.0)
            return 1;

        return 0;
    }

    int ST_GetTemperatureWarningStage()
    {
        float comfort = ST_GetHeatComfortValue();
        float absoluteComfort = Math.AbsFloat(comfort);

        if (absoluteComfort >= 0.75)
            return 3;
        if (absoluteComfort >= 0.50)
            return 2;
        if (absoluteComfort >= 0.25)
            return 1;

        return 0;
    }

    void ST_ProcessPlayerStatStage(
        string statName,
        int previousStage,
        int currentStage,
        int masterEnabled,
        int yellowEnabled,
        int redEnabled,
        int criticalEnabled,
        array<string> yellowMessages,
        array<string> redMessages,
        array<string> criticalMessages
    )
    {
        if (masterEnabled != 1)
            return;

        // First scan establishes the current state without announcing spawn stats.
        if (previousStage < 0)
            return;

        if (currentStage == previousStage)
            return;

        // Stage 0 is normal. Existing recovery systems handle improvement.
        if (currentStage <= 0)
            return;

        array<string> pool;

        if (currentStage == 1 && yellowEnabled == 1)
            pool = yellowMessages;
        else if (currentStage == 2 && redEnabled == 1)
            pool = redMessages;
        else if (currentStage >= 3 && criticalEnabled == 1)
            pool = criticalMessages;

        if (!pool || pool.Count() == 0)
            return;

        string thoughtType = "STAT_STAGE_YELLOW";

        if (currentStage == 2)
            thoughtType = "STAT_STAGE_RED";
        else if (currentStage >= 3)
            thoughtType = "STAT_STAGE_CRITICAL";

        SurvivorThoughtsManager.Get().SendThoughtWithPriority(this, pool.GetRandomElement(), thoughtType);

        string statStageDebug = "Player stat stage changed: " + statName;
        statStageDebug += " Previous=" + previousStage.ToString();
        statStageDebug += " Current=" + currentStage.ToString();
        SurvivorThoughtsManager.Get().DebugLog(statStageDebug);
    }

    void ST_ProcessHealthStage(int previousStage, int currentStage)
    {
        if (previousStage < 0 || currentStage == previousStage || currentStage <= 0)
            return;

        string message;
        string thoughtType = "STAT_STAGE_YELLOW";

        if (currentStage == 1)
        {
            message = "I am hurt. I need to be more careful.";
        }
        else if (currentStage == 2)
        {
            message = "I am badly hurt. I need safety and time to recover.";
            thoughtType = "STAT_STAGE_RED";
        }
        else
        {
            message = "I am barely holding on.";
            thoughtType = "STAT_STAGE_CRITICAL";
        }

        SurvivorThoughtsManager.Get().SendThoughtWithPriority(this, message, thoughtType);
    }

    void ST_ProcessTemperatureStage(
        ST_SurvivorThoughtsConfig config,
        int previousStage,
        int currentStage
    )
    {
        if (previousStage < 0 || currentStage == previousStage || currentStage <= 0)
            return;

        float comfort = ST_GetHeatComfortValue();
        string message;
        string thoughtType = "STAT_STAGE_YELLOW";

        if (comfort < 0.0 && config.EnableColdMessages != 1)
            return;
        if (comfort > 0.0 && config.EnableHotMessages != 1)
            return;

        if (currentStage == 1)
        {
            if (comfort < 0.0)
                message = "I am starting to feel the cold.";
            else
                message = "I am starting to overheat.";
        }
        else if (currentStage == 2)
        {
            if (comfort < 0.0)
                message = "I am freezing. I need warmth soon.";
            else
                message = "I am overheating. I need to cool down.";
            thoughtType = "STAT_STAGE_RED";
        }
        else
        {
            if (comfort < 0.0)
                message = "The cold is shutting my body down.";
            else
                message = "The heat is becoming dangerous.";
            thoughtType = "STAT_STAGE_CRITICAL";
        }

        SurvivorThoughtsManager.Get().SendThoughtWithPriority(this, message, thoughtType);
    }

    void ST_AddHungerThoughts(ST_SurvivorThoughtsConfig config, array<string> critical, array<string> high, array<string> medium, array<string> low)
    {
        if (config.EnableHungerMessages != 1)
            return;

        float energy = ST_GetEnergyValue();

        if (ST_IsValueInRange(energy, config.EnergyStage1_Min, config.EnergyStage1_Max))
        {
            if (config.EnableEnergyStage1Messages == 1)
                ST_InsertRandomStageMessage(config.EnergyStage1Messages, low);

            return;
        }

        if (ST_IsValueInRange(energy, config.EnergyStage2_Min, config.EnergyStage2_Max))
        {
            if (config.EnableEnergyStage2Messages == 1)
                ST_InsertRandomStageMessage(config.EnergyStage2Messages, low);

            return;
        }

        if (ST_IsValueInRange(energy, config.EnergyStage3_Min, config.EnergyStage3_Max))
        {
            if (config.EnableEnergyStage3Messages == 1)
                ST_InsertRandomStageMessage(config.EnergyStage3Messages, medium);

            return;
        }

        if (ST_IsValueInRange(energy, config.EnergyStage4_Min, config.EnergyStage4_Max))
        {
            if (config.EnableEnergyStage4Messages == 1)
                ST_InsertRandomStageMessage(config.EnergyStage4Messages, high);
        }
    }

    void ST_AddThirstThoughts(ST_SurvivorThoughtsConfig config, array<string> critical, array<string> high, array<string> medium, array<string> low)
    {
        if (config.EnableThirstMessages != 1)
            return;

        float water = ST_GetWaterValue();

        if (ST_IsValueInRange(water, config.WaterStage1_Min, config.WaterStage1_Max))
        {
            if (config.EnableWaterStage1Messages == 1)
                ST_InsertRandomStageMessage(config.WaterStage1Messages, low);

            return;
        }

        if (ST_IsValueInRange(water, config.WaterStage2_Min, config.WaterStage2_Max))
        {
            if (config.EnableWaterStage2Messages == 1)
                ST_InsertRandomStageMessage(config.WaterStage2Messages, low);

            return;
        }

        if (ST_IsValueInRange(water, config.WaterStage3_Min, config.WaterStage3_Max))
        {
            if (config.EnableWaterStage3Messages == 1)
                ST_InsertRandomStageMessage(config.WaterStage3Messages, medium);

            return;
        }

        if (ST_IsValueInRange(water, config.WaterStage4_Min, config.WaterStage4_Max))
        {
            if (config.EnableWaterStage4Messages == 1)
                ST_InsertRandomStageMessage(config.WaterStage4Messages, high);
        }
    }

    void ST_AddTemperatureThoughts(ST_SurvivorThoughtsConfig config, array<string> critical, array<string> high, array<string> medium)
    {
        float comfort = ST_GetHeatComfortValue();

        if (comfort <= -0.75 && config.EnableColdMessages == 1)
        {
            critical.Insert("I cannot stop shaking.");
            critical.Insert("My body is shutting down from the cold.");
            critical.Insert("I need fire, shelter, or dry clothes immediately.");
        }
        else if (comfort <= -0.50 && config.EnableColdMessages == 1)
        {
            high.Insert("I am freezing.");
            high.Insert("This cold is cutting through me.");
            high.Insert("I need warmth now.");
        }
        else if (comfort <= -0.25 && config.EnableColdMessages == 1)
        {
            medium.Insert("I am getting cold.");
            medium.Insert("My clothes are not keeping the chill out.");
            medium.Insert("I need shelter or a fire.");
        }
        else if (comfort >= 0.75 && config.EnableHotMessages == 1)
        {
            critical.Insert("I feel like I am going to collapse.");
            critical.Insert("The heat is unbearable.");
            critical.Insert("I need water and shade now.");
        }
        else if (comfort >= 0.50 && config.EnableHotMessages == 1)
        {
            high.Insert("I am overheating.");
            high.Insert("My head feels heavy from the heat.");
            high.Insert("I need to cool down.");
        }
        else if (comfort >= 0.25 && config.EnableHotMessages == 1)
        {
            medium.Insert("I am getting too hot.");
            medium.Insert("I need shade or lighter clothing.");
            medium.Insert("This heat is draining me.");
        }
    }

    void ST_AddSicknessThoughts(ST_SurvivorThoughtsConfig config, array<string> critical, array<string> high, array<string> medium)
    {
        if (config.EnableSicknessMessages != 1)
            return;

        // Starter-safe generic check. Some server versions/mod stacks expose stronger disease APIs.
        if (ST_IsModifierActiveSafe(eModifiers.MDF_COMMON_COLD))
        {
            medium.Insert("Something feels off.");
            medium.Insert("My body aches.");
            medium.Insert("I might be getting sick.");
        }

        if (ST_IsModifierActiveSafe(eModifiers.MDF_CHOLERA))
        {
            high.Insert("My stomach keeps turning.");
            high.Insert("I need medicine.");
            high.Insert("This sickness is getting worse.");
        }

        if (ST_IsModifierActiveSafe(eModifiers.MDF_INFLUENZA))
        {
            high.Insert("I feel feverish.");
            high.Insert("I can barely focus.");
            high.Insert("My body is fighting something bad.");
        }

        if (ST_IsModifierActiveSafe(eModifiers.MDF_WOUND_INFECTION))
        {
            critical.Insert("My wound feels infected.");
            critical.Insert("The infection is spreading.");
            critical.Insert("I need treatment now.");
        }
    }

    void ST_AddBleedingThoughts(ST_SurvivorThoughtsConfig config, array<string> critical, array<string> high)
    {
        if (config.EnableBleedingMessages != 1)
            return;

        int bleedCount = GetBleedingSourceCount();

        if (bleedCount <= 0)
            return;

        if (bleedCount == 1)
        {
            high.Insert("I am bleeding.");
            high.Insert("I need to bandage this.");
            high.Insert("Blood is running down my body.");
        }
        else if (bleedCount <= 3)
        {
            critical.Insert("I am losing blood fast.");
            critical.Insert("There is blood everywhere.");
            critical.Insert("I need to stop the bleeding now.");
        }
        else
        {
            critical.Insert("I am bleeding out.");
            critical.Insert("My vision is starting to fade.");
            critical.Insert("I need bandages immediately.");
        }
    }

    void ST_AddBloodThoughts(ST_SurvivorThoughtsConfig config, array<string> critical, array<string> high, array<string> medium, array<string> low)
    {
        float blood = ST_GetBloodValue();

        if (ST_IsValueInRange(blood, config.BloodStage1_Min, config.BloodStage1_Max))
        {
            if (config.EnableBloodStage1Messages == 1)
                ST_InsertRandomStageMessage(config.BloodStage1Messages, low);

            return;
        }

        if (ST_IsValueInRange(blood, config.BloodStage2_Min, config.BloodStage2_Max))
        {
            if (config.EnableBloodStage2Messages == 1)
                ST_InsertRandomStageMessage(config.BloodStage2Messages, medium);

            return;
        }

        if (ST_IsValueInRange(blood, config.BloodStage3_Min, config.BloodStage3_Max))
        {
            if (config.EnableBloodStage3Messages == 1)
                ST_InsertRandomStageMessage(config.BloodStage3Messages, high);

            return;
        }

        if (ST_IsValueInRange(blood, config.BloodStage4_Min, config.BloodStage4_Max))
        {
            if (config.EnableBloodStage4Messages == 1)
                ST_InsertRandomStageMessage(config.BloodStage4Messages, critical);
        }
    }

    void ST_AddShockThoughts(ST_SurvivorThoughtsConfig config, array<string> critical, array<string> high, array<string> medium, array<string> low)
    {
        float shock = ST_GetShockValue();

        if (ST_IsValueInRange(shock, config.ShockStage1_Min, config.ShockStage1_Max))
        {
            if (config.EnableShockStage1Messages == 1)
                ST_InsertRandomStageMessage(config.ShockStage1Messages, low);

            return;
        }

        if (ST_IsValueInRange(shock, config.ShockStage2_Min, config.ShockStage2_Max))
        {
            if (config.EnableShockStage2Messages == 1)
                ST_InsertRandomStageMessage(config.ShockStage2Messages, medium);

            return;
        }

        if (ST_IsValueInRange(shock, config.ShockStage3_Min, config.ShockStage3_Max))
        {
            if (config.EnableShockStage3Messages == 1)
                ST_InsertRandomStageMessage(config.ShockStage3Messages, high);

            return;
        }

        if (ST_IsValueInRange(shock, config.ShockStage4_Min, config.ShockStage4_Max))
        {
            if (config.EnableShockStage4Messages == 1)
                ST_InsertRandomStageMessage(config.ShockStage4Messages, critical);
        }
    }

    void ST_AddBrokenLegThoughts(ST_SurvivorThoughtsConfig config, array<string> critical, array<string> high)
    {
        if (config.EnableBrokenLegMessages != 1)
            return;

        if (!ST_HasBrokenLeg())
            return;

        if (config.BrokenLegMessages && config.BrokenLegMessages.Count() > 0)
        {
            high.Insert(config.BrokenLegMessages.GetRandomElement());
        }
        else
        {
            high.Insert("My leg is broken.");
            high.Insert("I need a splint before I can travel safely.");
        }
    }

    void ST_AddInfectedNearbyThoughts(ST_SurvivorThoughtsConfig config, array<string> high, array<string> medium, array<string> low)
    {
        if (config.EnableInfectedNearbyMessages != 1)
            return;

        array<Object> nearbyObjects = new array<Object>;
        array<CargoBase> proxyCargos = new array<CargoBase>;

        if (!GetGame())
            return;

        GetGame().GetObjectsAtPosition3D(GetPosition(), config.InfectedFarRadius, nearbyObjects, proxyCargos);

        int infectedCount = 0;
        float closestDistance = 99999.0;

        foreach (Object obj : nearbyObjects)
        {
            ZombieBase infected = ZombieBase.Cast(obj);

            if (!infected)
                continue;

            if (!infected.IsAlive())
                continue;

            infectedCount++;

            float distance = vector.Distance(GetPosition(), infected.GetPosition());
            if (distance < closestDistance)
                closestDistance = distance;
        }

        if (infectedCount <= 0)
            return;

        if (infectedCount >= config.InfectedSurroundedCount)
        {
            high.Insert("There are too many of them.");
            high.Insert("I am surrounded.");
            high.Insert("I need an escape route.");
        }
        else if (closestDistance <= config.InfectedVeryCloseRadius)
        {
            high.Insert("They are right on top of me.");
            high.Insert("I need to move carefully.");
            high.Insert("This place is not safe.");
        }
        else if (closestDistance <= config.InfectedCloseRadius)
        {
            medium.Insert("There are infected close.");
            medium.Insert("I need to watch my noise.");
            medium.Insert("One wrong move and they will hear me.");
        }
        else
        {
            low.Insert("I hear infected nearby.");
            low.Insert("Something is moving out there.");
            low.Insert("I do not think I am alone.");
        }
    }
    void ST_AddLocationThoughts(ST_SurvivorThoughtsConfig config, array<string> medium, array<string> low)
    {
        if (!config || config.EnableLocationThoughts != 1)
            return;

        float roll = Math.RandomFloatInclusive(0.0, 1.0);
        if (roll > config.LocationThoughtChance)
            return;

        array<string> messages = ST_GetCurrentLocationMessages(config);

        if (!messages || messages.Count() == 0)
            return;

        low.Insert(messages.GetRandomElement());
    }

    array<string> ST_GetCurrentLocationMessages(ST_SurvivorThoughtsConfig config)
    {
        if (config.LocationUseCustomZones == 1 && config.LocationZones && config.LocationZones.Count() > 0)
        {
            vector pos = GetPosition();

            foreach (ST_LocationZone zone : config.LocationZones)
            {
                if (!zone)
                    continue;

                vector zonePos = Vector(zone.X, pos[1], zone.Z);
                float dist = vector.Distance(pos, zonePos);

                if (dist <= zone.Radius)
                {
                    array<string> zoneMessages = ST_GetLocationMessagesByType(config, zone.Type);

                    if (zoneMessages && zoneMessages.Count() > 0)
                        return zoneMessages;
                }
            }
        }

        if (config.LocationUseFallbackDetection == 1)
            return ST_GetFallbackLocationMessages(config);

        return null;
    }

    array<string> ST_GetFallbackLocationMessages(ST_SurvivorThoughtsConfig config)
    {
        vector pos = GetPosition();

        // Generic fallback 1: coast/coastal-spawn style check.
        // This is intentionally configurable because maps differ.
        if (pos[2] <= config.LocationCoastZMax)
            return config.LocationCoastMessages;

        // Generic fallback 2: sparse-object scan for wilderness-style areas.
        array<Object> nearbyObjects = new array<Object>;
        array<CargoBase> proxyCargos = new array<CargoBase>;

        if (!GetGame())
            return null;

        GetGame().GetObjectsAtPosition3D(pos, config.LocationWildernessScanRadius, nearbyObjects, proxyCargos);

        if (nearbyObjects && nearbyObjects.Count() <= config.LocationWildernessMaxObjects)
            return config.LocationWildernessMessages;

        return null;
    }

    array<string> ST_GetLocationMessagesByType(ST_SurvivorThoughtsConfig config, string locationType)
    {
        if (locationType == "Coast")
            return config.LocationCoastMessages;

        if (locationType == "Town")
            return config.LocationTownMessages;

        if (locationType == "City")
            return config.LocationCityMessages;

        if (locationType == "Forest")
            return config.LocationForestMessages;

        if (locationType == "Wilderness")
            return config.LocationWildernessMessages;

        if (locationType == "Military")
            return config.LocationMilitaryMessages;

        if (locationType == "Police")
            return config.LocationPoliceMessages;

        if (locationType == "Medical")
            return config.LocationMedicalMessages;

        if (locationType == "Industrial")
            return config.LocationIndustrialMessages;

        if (locationType == "Farm")
            return config.LocationFarmMessages;

        if (locationType == "Water")
            return config.LocationWaterMessages;

        return null;
    }

    void ST_AddWeatherThoughts(ST_SurvivorThoughtsConfig config, array<string> high, array<string> medium, array<string> low)
    {
        if (!config || config.EnableWeatherThoughts != 1)
            return;

        if (!GetGame())
            return;

        float now = GetGame().GetTime() / 1000.0;
        if (config.WeatherThoughtCooldownSeconds > 0.0 && (now - m_ST_LastWeatherThoughtTime) < config.WeatherThoughtCooldownSeconds)
            return;

        float roll = Math.RandomFloatInclusive(0.0, 1.0);
        if (roll > config.WeatherThoughtChance)
            return;

        Weather weather = GetGame().GetWeather();
        if (!weather)
            return;

        float rain = 0.0;
        float fog = 0.0;
        float overcast = 0.0;
        float wind = weather.GetWindSpeed();

        WeatherPhenomenon rainPhenomenon = weather.GetRain();
        if (rainPhenomenon)
            rain = rainPhenomenon.GetActual();

        WeatherPhenomenon fogPhenomenon = weather.GetFog();
        if (fogPhenomenon)
            fog = fogPhenomenon.GetActual();

        WeatherPhenomenon overcastPhenomenon = weather.GetOvercast();
        if (overcastPhenomenon)
            overcast = overcastPhenomenon.GetActual();

        if (config.EnableStormWeatherMessages == 1 && ((rain >= config.StormRain_Min && wind >= config.StormWind_Min) || overcast >= config.StormOvercast_Min))
        {
            ST_InsertRandomStageMessage(config.WeatherStormMessages, medium);
            m_ST_LastWeatherThoughtTime = now;
            SurvivorThoughtsManager.Get().DebugLog("Weather thought candidate added: STORM rain=" + rain.ToString() + " fog=" + fog.ToString() + " overcast=" + overcast.ToString() + " wind=" + wind.ToString());
            return;
        }

        if (config.EnableHeavyRainMessages == 1 && rain >= config.HeavyRainThought_Min)
        {
            if (config.WeatherHeavyRainMessages && config.WeatherHeavyRainMessages.Count() > 0)
                ST_InsertRandomStageMessage(config.WeatherHeavyRainMessages, low);
            else
                ST_InsertRandomStageMessage(config.WeatherRainMessages, low);

            m_ST_LastWeatherThoughtTime = now;
            SurvivorThoughtsManager.Get().DebugLog("Weather thought candidate added: HEAVY_RAIN rain=" + rain.ToString());
            return;
        }

        if (config.EnableLightRainMessages == 1 && rain >= config.LightRainThought_Min)
        {
            if (config.WeatherLightRainMessages && config.WeatherLightRainMessages.Count() > 0)
                ST_InsertRandomStageMessage(config.WeatherLightRainMessages, low);
            else
                ST_InsertRandomStageMessage(config.WeatherRainMessages, low);

            m_ST_LastWeatherThoughtTime = now;
            SurvivorThoughtsManager.Get().DebugLog("Weather thought candidate added: LIGHT_RAIN rain=" + rain.ToString());
            return;
        }

        if (rain >= config.RainThought_Min)
        {
            ST_InsertRandomStageMessage(config.WeatherRainMessages, low);
            m_ST_LastWeatherThoughtTime = now;
            SurvivorThoughtsManager.Get().DebugLog("Weather thought candidate added: RAIN rain=" + rain.ToString());
            return;
        }

        if (config.EnableFogWeatherMessages == 1 && fog >= config.FogThought_Min)
        {
            ST_InsertRandomStageMessage(config.WeatherFogMessages, low);
            m_ST_LastWeatherThoughtTime = now;
            SurvivorThoughtsManager.Get().DebugLog("Weather thought candidate added: FOG fog=" + fog.ToString());
            return;
        }

        if (config.EnableWindWeatherMessages == 1 && wind >= config.WindThought_Min)
        {
            ST_InsertRandomStageMessage(config.WeatherWindMessages, low);
            m_ST_LastWeatherThoughtTime = now;
            SurvivorThoughtsManager.Get().DebugLog("Weather thought candidate added: WIND wind=" + wind.ToString());
            return;
        }

        if (config.EnableOvercastWeatherMessages == 1 && overcast >= config.OvercastThought_Min)
        {
            ST_InsertRandomStageMessage(config.WeatherOvercastMessages, low);
            m_ST_LastWeatherThoughtTime = now;
            SurvivorThoughtsManager.Get().DebugLog("Weather thought candidate added: OVERCAST overcast=" + overcast.ToString());
            return;
        }

        if (config.EnableClearWeatherMessages == 1 && overcast < config.OvercastThought_Min && rain < config.LightRainThought_Min && fog < config.FogThought_Min)
        {
            ST_InsertRandomStageMessage(config.WeatherClearMessages, low);
            m_ST_LastWeatherThoughtTime = now;
            SurvivorThoughtsManager.Get().DebugLog("Weather thought candidate added: CLEAR");
            return;
        }
    }

    void ST_AddTimeOfDayThoughts(ST_SurvivorThoughtsConfig config, array<string> medium, array<string> low)
    {
        if (!config || config.EnableTimeOfDayThoughts != 1)
            return;

        if (!GetGame())
            return;

        float now = GetGame().GetTime() / 1000.0;
        if (config.TimeOfDayThoughtCooldownSeconds > 0.0 && (now - m_ST_LastTimeOfDayThoughtTime) < config.TimeOfDayThoughtCooldownSeconds)
            return;

        float roll = Math.RandomFloatInclusive(0.0, 1.0);
        if (roll > config.TimeOfDayThoughtChance)
            return;

        array<string> messages = ST_GetCurrentTimeOfDayMessages(config);
        if (!messages || messages.Count() == 0)
            return;

        low.Insert(messages.GetRandomElement());
        m_ST_LastTimeOfDayThoughtTime = now;
        SurvivorThoughtsManager.Get().DebugLog("Time-of-day thought candidate added. Hour=" + ST_GetWorldHour().ToString());
    }

    float ST_GetWorldHour()
    {
        if (!GetGame() || !GetGame().GetWorld())
            return 12.0;

        int year, month, day, hour, minute;
        GetGame().GetWorld().GetDate(year, month, day, hour, minute);

        return hour + (minute / 60.0);
    }

    bool ST_HourInWindow(float hour, float startHour, float endHour)
    {
        if (startHour <= endHour)
            return hour >= startHour && hour < endHour;

        return hour >= startHour || hour < endHour;
    }

    array<string> ST_GetCurrentTimeOfDayMessages(ST_SurvivorThoughtsConfig config)
    {
        float hour = ST_GetWorldHour();

        if (config.EnableMidnightMessages == 1 && ST_HourInWindow(hour, config.MidnightStartHour, config.EarlyMorningStartHour))
            return config.MidnightMessages;

        if (config.EnableEarlyMorningMessages == 1 && ST_HourInWindow(hour, config.EarlyMorningStartHour, config.DawnStartHour))
            return config.EarlyMorningMessages;

        if (config.EnableDawnMessages == 1 && ST_HourInWindow(hour, config.DawnStartHour, config.MorningStartHour))
            return config.DawnMessages;

        if (config.EnableMorningMessages == 1 && ST_HourInWindow(hour, config.MorningStartHour, config.NoonStartHour))
            return config.MorningMessages;

        if (config.EnableNoonMessages == 1 && ST_HourInWindow(hour, config.NoonStartHour, config.AfternoonStartHour))
            return config.NoonMessages;

        if (config.EnableAfternoonMessages == 1 && ST_HourInWindow(hour, config.AfternoonStartHour, config.DuskStartHour))
            return config.AfternoonMessages;

        if (config.EnableDuskMessages == 1 && ST_HourInWindow(hour, config.DuskStartHour, config.NightStartHour))
            return config.DuskMessages;

        if (config.EnableNightMessages == 1)
            return config.NightMessages;

        return null;
    }

    bool ST_IsConsumableHeldItem(EntityAI item)
    {
        if (!item)
            return false;

        if (Edible_Base.Cast(item))
            return true;

        if (Bottle_Base.Cast(item))
            return true;

        string heldType = item.GetType();

        if (heldType.Contains("Food"))
            return true;

        if (heldType.Contains("Sardines") || heldType.Contains("Tuna") || heldType.Contains("Peaches"))
            return true;

        if (heldType.Contains("Spaghetti") || heldType.Contains("BakedBeans") || heldType.Contains("TacticalBacon"))
            return true;

        if (heldType.Contains("Pajka") || heldType.Contains("Pate") || heldType.Contains("Lunchmeat"))
            return true;

        if (heldType.Contains("SodaCan") || heldType.Contains("WaterBottle") || heldType.Contains("Canteen"))
            return true;

        return false;
    }

    void ST_UpdateImportantGearThoughts(ST_SurvivorThoughtsConfig config)
    {
        if (!config || config.EnableMod != 1 || config.EnableItemConditionThoughts != 1)
            return;

        float now = GetGame().GetTime() / 1000.0;

        // Five-second scan cadence keeps the system responsive without doing an
        // attachment walk every frame.
        if ((now - m_ST_LastImportantGearScanTime) < 5.0)
            return;

        m_ST_LastImportantGearScanTime = now;

        array<string> slots = new array<string>;
        array<string> categories = new array<string>;

        // Index 0 represents the item in hands.
        slots.Insert("");
        categories.Insert("HANDS");

        slots.Insert("Shoulder");
        categories.Insert("WEAPON");

        slots.Insert("Melee");
        categories.Insert("WEAPON");

        slots.Insert("Headgear");
        categories.Insert("HEADGEAR");

        slots.Insert("Mask");
        categories.Insert("MASK");

        slots.Insert("Eyewear");
        categories.Insert("MASK");

        slots.Insert("Gloves");
        categories.Insert("GLOVES");

        slots.Insert("Vest");
        categories.Insert("VEST");

        slots.Insert("Body");
        categories.Insert("CLOTHING");

        slots.Insert("Legs");
        categories.Insert("CLOTHING");

        slots.Insert("Hips");
        categories.Insert("BELT");

        slots.Insert("Back");
        categories.Insert("BACKPACK");

        slots.Insert("Feet");
        categories.Insert("SHOES");

        int count = slots.Count();
        int startIndex = Math.RandomInt(0, count);

        for (int offset = 0; offset < count; offset++)
        {
            int index = (startIndex + offset) % count;
            string slotName = slots.Get(index);
            string category = categories.Get(index);

            EntityAI item;

            if (index == 0)
                item = GetItemInHands();
            else
                item = FindAttachmentBySlotName(slotName);

            if (!item)
                continue;

            if (index == 0 && ST_IsConsumableHeldItem(item))
                continue;

            int stage = ST_GetImportantGearStage(item);
            string key = slotName + ":" + category + ":" + item.GetType();

            int previousStage = 0;
            bool knownItem = m_ST_ImportantGearLevels.Contains(key);

            if (knownItem)
                previousStage = m_ST_ImportantGearLevels.Get(key);

            // Always store the current DayZ condition level. This includes
            // repairs, allowing the same item to trigger again if it worsens.
            m_ST_ImportantGearLevels.Set(key, stage);

            if (stage <= 0)
                continue;

            // Trigger only when first observed in a non-pristine state or when
            // the item crosses into a worse DayZ condition stage.
            if (knownItem && stage <= previousStage)
                continue;

            string categoryMessage = ST_GetImportantGearMessage(config, item, category);

            if (categoryMessage == "")
                continue;

            string message = ST_BuildImportantGearStageMessage(item, stage, categoryMessage);
            string thoughtType = ST_GetImportantGearThoughtType(stage);

            SurvivorThoughtsManager.Get().SendThoughtWithPriority(this, message, thoughtType);

            string gearDebugMessage = "Gear condition stage changed: Item=" + item.GetType();
            gearDebugMessage += " Category=" + category;
            gearDebugMessage += " Previous=" + ST_GetImportantGearStageName(previousStage);
            gearDebugMessage += " Current=" + ST_GetImportantGearStageName(stage);
            gearDebugMessage += " Health01=" + item.GetHealth01("", "").ToString();
            SurvivorThoughtsManager.Get().DebugLog(gearDebugMessage);

            // Only one equipment thought is sent per five-second scan. Other
            // changed items remain unknown/at their previous state and are
            // picked up on the next scan.
            return;
        }
    }

    int ST_GetImportantGearStage(EntityAI item)
    {
        if (!item)
            return 0;

        int level = item.GetHealthLevel();

        if (level <= GameConstants.STATE_PRISTINE)
            return 0;

        if (level == GameConstants.STATE_WORN)
            return 1;

        if (level == GameConstants.STATE_DAMAGED)
            return 2;

        if (level == GameConstants.STATE_BADLY_DAMAGED)
            return 3;

        if (level >= GameConstants.STATE_RUINED)
            return 4;

        return 0;
    }

    string ST_GetImportantGearStageName(int stage)
    {
        switch (stage)
        {
            case 1:
                return "Worn";

            case 2:
                return "Damaged";

            case 3:
                return "Badly Damaged";

            case 4:
                return "Ruined";
        }

        return "Pristine";
    }

    string ST_GetImportantGearThoughtType(int stage)
    {
        switch (stage)
        {
            case 1:
                return "ITEM_WORN";

            case 2:
                return "ITEM_DAMAGED";

            case 3:
                return "ITEM_BADLY_DAMAGED";

            case 4:
                return "ITEM_RUINED";
        }

        return "ITEM_CONDITION";
    }

    string ST_BuildImportantGearStageMessage(EntityAI item, int stage, string categoryMessage)
    {
        string displayName = item.GetDisplayName();

        if (displayName == "")
            displayName = item.GetType();

        switch (stage)
        {
            case 1:
                return "My " + displayName + " is starting to show wear.";

            case 2:
                return "My " + displayName + " is damaged. I need to look after it.";

            case 3:
                if (categoryMessage != "")
                    return categoryMessage;

                return "My " + displayName + " is badly damaged. It may not last.";

            case 4:
                return "My " + displayName + " is ruined.";
        }

        return categoryMessage;
    }

    string ST_GetImportantGearMessage(ST_SurvivorThoughtsConfig config, EntityAI item, string category)
    {
        if (!config || !item)
            return "";

        array<string> pool;

        if (category == "HANDS")
        {
            if (item.IsWeapon())
            {
                if (config.EnableWeaponConditionMessages != 1)
                    return "";

                pool = config.ItemWeaponDamagedMessages;
            }
            else
            {
                if (config.EnableHandsItemConditionMessages != 1)
                    return "";

                pool = config.ItemBadlyDamagedMessages;
            }
        }
        else if (category == "WEAPON")
        {
            if (config.EnableWeaponConditionMessages != 1)
                return "";

            pool = config.ItemWeaponDamagedMessages;
        }
        else if (category == "CLOTHING")
        {
            if (config.EnableClothingConditionMessages != 1)
                return "";

            pool = config.ItemClothingDamagedMessages;
        }
        else if (category == "SHOES")
        {
            if (config.EnableShoesConditionMessages != 1)
                return "";

            pool = config.ItemShoesDamagedMessages;
        }
        else if (category == "BACKPACK")
        {
            if (config.EnableBackpackConditionMessages != 1)
                return "";

            pool = config.ItemBackpackDamagedMessages;
        }
        else if (category == "VEST")
        {
            if (config.EnableVestConditionMessages != 1)
                return "";

            pool = config.ItemVestDamagedMessages;
        }
        else if (category == "HEADGEAR")
        {
            if (config.EnableHeadgearConditionMessages != 1)
                return "";

            pool = config.ItemHeadgearDamagedMessages;
        }
        else if (category == "GLOVES")
        {
            if (config.EnableGlovesConditionMessages != 1)
                return "";

            pool = config.ItemGlovesDamagedMessages;
        }
        else if (category == "MASK")
        {
            if (config.EnableMaskConditionMessages != 1)
                return "";

            pool = config.ItemMaskDamagedMessages;
        }
        else if (category == "BELT")
        {
            if (config.EnableBeltConditionMessages != 1)
                return "";

            pool = config.ItemBeltDamagedMessages;
        }

        if (pool && pool.Count() > 0)
            return pool.GetRandomElement();

        if (config.ItemBadlyDamagedMessages && config.ItemBadlyDamagedMessages.Count() > 0)
            return config.ItemBadlyDamagedMessages.GetRandomElement();

        return "This gear is falling apart.";
    }

    void ST_AddItemConditionThoughts(ST_SurvivorThoughtsConfig config, array<string> medium, array<string> low)
    {
        if (config.EnableItemConditionThoughts != 1)
            return;

        // Hands first: the item being actively used should be the most relevant.
        EntityAI item = GetItemInHands();
        if (ST_IsItemBadlyDamaged(item, config.ItemConditionHealthThreshold))
        {
            SurvivorThoughtsManager.Get().DebugLog("Damaged item condition thought detected in hands.");

            if (item && item.IsWeapon())
                ST_InsertRandomStageMessage(config.ItemWeaponDamagedMessages, low);
            else
                ST_InsertRandomStageMessage(config.ItemBadlyDamagedMessages, low);

            return;
        }

        if (config.ScanEquippedItemsForDamagedThoughts != 1)
            return;

        // Attachment slots are checked explicitly rather than scanning all cargo.
        // This keeps the system cheap and focuses thoughts on gear the survivor is wearing/using.
        if (ST_CheckDamagedSlot(low, "Shoulder", config.ItemWeaponDamagedMessages, config.ItemConditionHealthThreshold)) return;
        if (ST_CheckDamagedSlot(low, "Melee", config.ItemWeaponDamagedMessages, config.ItemConditionHealthThreshold)) return;

        if (ST_CheckDamagedSlot(low, "Headgear", config.ItemHeadgearDamagedMessages, config.ItemConditionHealthThreshold)) return;
        if (ST_CheckDamagedSlot(low, "Mask", config.ItemMaskDamagedMessages, config.ItemConditionHealthThreshold)) return;
        if (ST_CheckDamagedSlot(low, "Eyewear", config.ItemMaskDamagedMessages, config.ItemConditionHealthThreshold)) return;
        if (ST_CheckDamagedSlot(low, "Gloves", config.ItemGlovesDamagedMessages, config.ItemConditionHealthThreshold)) return;
        if (ST_CheckDamagedSlot(low, "Vest", config.ItemVestDamagedMessages, config.ItemConditionHealthThreshold)) return;
        if (ST_CheckDamagedSlot(low, "Body", config.ItemClothingDamagedMessages, config.ItemConditionHealthThreshold)) return;
        if (ST_CheckDamagedSlot(low, "Legs", config.ItemClothingDamagedMessages, config.ItemConditionHealthThreshold)) return;
        if (ST_CheckDamagedSlot(low, "Hips", config.ItemBeltDamagedMessages, config.ItemConditionHealthThreshold)) return;
        if (ST_CheckDamagedSlot(low, "Back", config.ItemBackpackDamagedMessages, config.ItemConditionHealthThreshold)) return;
        if (ST_CheckDamagedSlot(low, "Feet", config.ItemShoesDamagedMessages, config.ItemConditionHealthThreshold)) return;
    }

    bool ST_CheckDamagedSlot(array<string> low, string slotName, array<string> messagePool, float threshold)
    {
        EntityAI attachment = FindAttachmentBySlotName(slotName);

        if (!ST_IsItemBadlyDamaged(attachment, threshold))
            return false;

        if (messagePool && messagePool.Count() > 0)
        {
            SurvivorThoughtsManager.Get().DebugLog("Damaged item condition thought detected in slot: " + slotName);
            ST_InsertRandomStageMessage(low, messagePool);
            return true;
        }

        ST_SurvivorThoughtsConfig fallbackConfig = SurvivorThoughtsManager.Get().GetConfig();
        if (fallbackConfig && fallbackConfig.ItemBadlyDamagedMessages && fallbackConfig.ItemBadlyDamagedMessages.Count() > 0)
        {
            ST_InsertRandomStageMessage(low, fallbackConfig.ItemBadlyDamagedMessages);
            return true;
        }

        return false;
    }

    bool ST_IsItemBadlyDamaged(EntityAI item, float threshold)
    {
        if (!item)
            return false;

        float health01 = item.GetHealth01("", "");

        if (health01 < 0.0)
            return false;

        return health01 <= threshold;
    }

    void ST_AddCombatStressThoughts(ST_SurvivorThoughtsConfig config, array<string> high, array<string> medium)
    {
        if (config.EnableCombatStressThoughts != 1 || config.EnableCombatStressShockThoughts != 1)
            return;

        float shock = ST_GetShockValue();

        if (shock > 0.0 && shock <= config.CombatStressShockThreshold)
        {
            ST_InsertRandomStageMessage(config.CombatShockMessages, medium);
        }
    }

    void ST_AddContaminatedZoneThoughts(ST_SurvivorThoughtsConfig config, array<string> critical, array<string> high)
    {
        if (config.EnableContaminatedZoneThoughts != 1)
            return;

        if (!GetModifiersManager())
            return;

        if (ST_IsModifierActiveSafe(eModifiers.MDF_AREAEXPOSURE))
        {
            ST_InsertRandomStageMessage(config.ContaminatedZoneMessages, high);
        }
    }

    void ST_AddNearbyCorpseThoughts(ST_SurvivorThoughtsConfig config, array<string> medium, array<string> low)
    {
        if (config.EnableNearbyCorpseThoughts != 1)
            return;

        array<Object> nearbyObjects = new array<Object>;
        array<CargoBase> proxyCargos = new array<CargoBase>;

        if (!GetGame())
            return;

        GetGame().GetObjectsAtPosition3D(GetPosition(), config.NearbyCorpseRadius, nearbyObjects, proxyCargos);

        foreach (Object obj : nearbyObjects)
        {
            if (!obj || obj == this)
                continue;

            SurvivorBase survivor = SurvivorBase.Cast(obj);
            if (survivor && !survivor.IsAlive())
            {
                ST_SetMemoryFlag("CORPSE");
                ST_InsertRandomStageMessage(config.NearbyCorpseMessages, low);
                return;
            }

            ZombieBase infected = ZombieBase.Cast(obj);
            if (infected && !infected.IsAlive())
            {
                ST_SetMemoryFlag("CORPSE");
                ST_InsertRandomStageMessage(config.NearbyCorpseMessages, low);
                return;
            }

            AnimalBase animal = AnimalBase.Cast(obj);
            if (animal && !animal.IsAlive())
            {
                ST_SetMemoryFlag("CORPSE");
                ST_InsertRandomStageMessage(config.NearbyCorpseMessages, low);
                return;
            }
        }
    }


    int ST_CountNearbyInfectedForSmartSystems(float radius)
    {
        if (!GetGame())
            return 0;

        array<Object> nearbyObjects = new array<Object>;
        array<CargoBase> proxyCargos = new array<CargoBase>;
        GetGame().GetObjectsAtPosition3D(GetPosition(), radius, nearbyObjects, proxyCargos);

        int infectedCount = 0;

        foreach (Object obj : nearbyObjects)
        {
            ZombieBase infected = ZombieBase.Cast(obj);

            if (infected && infected.IsAlive())
                infectedCount++;
        }

        return infectedCount;
    }

    bool ST_IsNightForSmartSystems(ST_SurvivorThoughtsConfig config)
    {
        float hour = ST_GetWorldHour();

        if (hour >= config.NightStartHour || hour < config.DawnStartHour)
            return true;

        return false;
    }

    bool ST_IsBadWeatherForSmartSystems(ST_SurvivorThoughtsConfig config)
    {
        if (!GetGame())
            return false;

        Weather weather = GetGame().GetWeather();

        if (!weather)
            return false;

        float rain = 0.0;
        WeatherPhenomenon rainPhenomenon = weather.GetRain();
        if (rainPhenomenon)
            rain = rainPhenomenon.GetActual();

        float overcast = weather.GetOvercast().GetActual();
        float wind = weather.GetWindSpeed();

        if (rain >= config.RainThought_Min)
            return true;

        if (overcast >= config.OvercastThought_Min && wind >= config.WindThought_Min)
            return true;

        return false;
    }

    bool ST_IsInMilitaryZoneForSmartSystems(ST_SurvivorThoughtsConfig config)
    {
        if (!config || !config.LocationZones)
            return false;

        vector pos = GetPosition();

        foreach (ST_LocationZone zone : config.LocationZones)
        {
            if (!zone)
                continue;

            if (zone.Type != "Military")
                continue;

            vector zonePos = Vector(zone.X, pos[1], zone.Z);
            if (vector.Distance(pos, zonePos) <= zone.Radius)
                return true;
        }

        return false;
    }

    bool ST_IsNearShelterForSmartSystems(ST_SurvivorThoughtsConfig config)
    {
        if (!GetGame() || !config)
            return false;

        array<Object> nearbyObjects = new array<Object>;
        array<CargoBase> proxyCargos = new array<CargoBase>;
        GetGame().GetObjectsAtPosition3D(GetPosition(), config.ShelterScanRadius, nearbyObjects, proxyCargos);

        int buildingCount = 0;

        foreach (Object obj : nearbyObjects)
        {
            if (!obj || obj == this)
                continue;

            string typeName = obj.GetType();

            if (typeName.Contains("Land_") || typeName.Contains("House") || typeName.Contains("Building") || typeName.Contains("Shed") || typeName.Contains("Barn"))
                buildingCount++;
        }

        return buildingCount >= config.ShelterNearbyBuildingCountRequired;
    }

    void ST_AddPlayerMemoryThoughts(ST_SurvivorThoughtsConfig config, array<string> medium, array<string> low)
    {
        if (!config || config.EnablePlayerMemoryThoughts != 1 || !GetGame())
            return;

        float now = GetGame().GetTime() / 1000.0;

        if (config.PlayerMemoryThoughtCooldownSeconds > 0.0 && (now - m_ST_LastPlayerMemoryThoughtTime) < config.PlayerMemoryThoughtCooldownSeconds)
            return;

        if (Math.RandomFloatInclusive(0.0, 1.0) > config.PlayerMemoryThoughtChance)
            return;

        array<string> candidates = new array<string>;

        if (ST_HasMemoryFlag("GUNSHOT", config.PlayerMemoryDurationSeconds))
            ST_InsertRandomStageMessage(candidates, config.PlayerMemoryRecentGunshotMessages);

        if (ST_HasMemoryFlag("BLEEDING", config.PlayerMemoryDurationSeconds))
            ST_InsertRandomStageMessage(candidates, config.PlayerMemoryRecentBleedingMessages);

        if (ST_HasMemoryFlag("DAMAGE", config.PlayerMemoryDurationSeconds))
            ST_InsertRandomStageMessage(candidates, config.PlayerMemoryRecentDamageMessages);

        if (ST_HasMemoryFlag("CORPSE", config.PlayerMemoryDurationSeconds))
            ST_InsertRandomStageMessage(candidates, config.PlayerMemoryRecentCorpseMessages);

        if (ST_HasMemoryFlag("MILITARY", config.PlayerMemoryDurationSeconds))
            ST_InsertRandomStageMessage(candidates, config.PlayerMemoryRecentMilitaryMessages);

        if (ST_HasMemoryFlag("SURVIVAL_CRISIS", config.PlayerMemoryDurationSeconds))
            ST_InsertRandomStageMessage(candidates, config.PlayerMemoryRecentSurvivalCrisisMessages);

        if (candidates.Count() <= 0)
            return;

        medium.Insert(candidates.GetRandomElement());
        m_ST_LastPlayerMemoryThoughtTime = now;
    }

    void ST_AddStealthNoiseThoughts(ST_SurvivorThoughtsConfig config, array<string> medium, array<string> low)
    {
        if (!config || config.EnableStealthNoiseThoughts != 1 || !GetGame())
            return;

        float now = GetGame().GetTime() / 1000.0;

        if (config.StealthNoiseThoughtCooldownSeconds > 0.0 && (now - m_ST_LastStealthNoiseThoughtTime) < config.StealthNoiseThoughtCooldownSeconds)
            return;

        if (Math.RandomFloatInclusive(0.0, 1.0) > config.StealthNoiseThoughtChance)
            return;

        array<string> candidates = new array<string>;

        if (ST_CountNearbyInfectedForSmartSystems(config.StealthNoiseInfectedRadius) > 0)
            ST_InsertRandomStageMessage(candidates, config.StealthNoiseInfectedNearbyMessages);

        if (ST_IsNightForSmartSystems(config))
            ST_InsertRandomStageMessage(candidates, config.StealthNoiseNightMessages);

        if (ST_IsInMilitaryZoneForSmartSystems(config))
        {
            ST_SetMemoryFlag("MILITARY");
            ST_InsertRandomStageMessage(candidates, config.StealthNoiseMilitaryMessages);
        }

        if (candidates.Count() <= 0)
            return;

        medium.Insert(candidates.GetRandomElement());
        m_ST_LastStealthNoiseThoughtTime = now;
    }

    void ST_AddShelterThoughts(ST_SurvivorThoughtsConfig config, array<string> medium, array<string> low)
    {
        if (!config || config.EnableShelterThoughts != 1 || !GetGame())
            return;

        float now = GetGame().GetTime() / 1000.0;

        if (config.ShelterThoughtCooldownSeconds > 0.0 && (now - m_ST_LastShelterThoughtTime) < config.ShelterThoughtCooldownSeconds)
            return;

        if (Math.RandomFloatInclusive(0.0, 1.0) > config.ShelterThoughtChance)
            return;

        if (!ST_IsNearShelterForSmartSystems(config))
            return;

        array<string> candidates = new array<string>;

        if (ST_IsBadWeatherForSmartSystems(config))
            ST_InsertRandomStageMessage(candidates, config.ShelterBadWeatherMessages);

        if (ST_IsNightForSmartSystems(config))
            ST_InsertRandomStageMessage(candidates, config.ShelterNightMessages);

        if (ST_CountNearbyInfectedForSmartSystems(config.InfectedCloseRadius) > 0)
            ST_InsertRandomStageMessage(candidates, config.ShelterUnsafeMessages);
        else
            ST_InsertRandomStageMessage(candidates, config.ShelterSafeMessages);

        if (candidates.Count() <= 0)
            return;

        low.Insert(candidates.GetRandomElement());
        m_ST_LastShelterThoughtTime = now;
    }

    void ST_AddMentalStateThoughts(ST_SurvivorThoughtsConfig config, array<string> high, array<string> medium, array<string> low)
    {
        if (!config || config.EnableMentalStateThoughts != 1 || !GetGame())
            return;

        float now = GetGame().GetTime() / 1000.0;

        if (config.MentalStateThoughtCooldownSeconds > 0.0 && (now - m_ST_LastMentalStateThoughtTime) < config.MentalStateThoughtCooldownSeconds)
            return;

        if (Math.RandomFloatInclusive(0.0, 1.0) > config.MentalStateThoughtChance)
            return;

        float health = ST_GetHealthValue();
        float blood = ST_GetBloodValue();
        float energy = ST_GetEnergyValue();
        float water = ST_GetWaterValue();

        array<string> messages = null;
        bool highPriority = false;

        if (health <= config.MentalStateCriticalHealthMax && blood <= config.MentalStateLowBloodMax)
        {
            messages = config.MentalStateBrokenMessages;
            highPriority = true;
        }
        else if (energy <= config.MentalStateLowFoodMax || water <= config.MentalStateLowWaterMax)
        {
            messages = config.MentalStateDesperateMessages;
            highPriority = true;
        }
        else if (ST_HasMemoryFlag("GUNSHOT", config.PlayerMemoryDurationSeconds) || ST_HasMemoryFlag("DAMAGE", config.PlayerMemoryDurationSeconds))
        {
            messages = config.MentalStateFocusedMessages;
        }
        else if (ST_HasMemoryFlag("CORPSE", config.PlayerMemoryDurationSeconds))
        {
            messages = config.MentalStateNumbMessages;
        }
        else if (ST_CountNearbyInfectedForSmartSystems(config.InfectedCloseRadius) > 0)
        {
            messages = config.MentalStateAfraidMessages;
        }
        else if (ST_IsNightForSmartSystems(config))
        {
            messages = config.MentalStateUneasyMessages;
        }
        else
        {
            messages = config.MentalStateStableMessages;
        }

        if (!messages || messages.Count() <= 0)
            return;

        if (highPriority)
            high.Insert(messages.GetRandomElement());
        else
            medium.Insert(messages.GetRandomElement());

        m_ST_LastMentalStateThoughtTime = now;
    }

    void ST_AddCustomThoughtZoneThoughts(ST_SurvivorThoughtsConfig config, array<string> medium, array<string> low)
    {
        if (!config || config.EnableCustomThoughtZones != 1 || !config.CustomThoughtZones || !GetGame())
            return;

        float now = GetGame().GetTime() / 1000.0;

        if (config.CustomThoughtZoneDefaultCooldownSeconds > 0.0 && (now - m_ST_LastCustomThoughtZoneThoughtTime) < config.CustomThoughtZoneDefaultCooldownSeconds)
            return;

        vector pos = GetPosition();

        foreach (ST_CustomThoughtZone zone : config.CustomThoughtZones)
        {
            if (!zone || !zone.Messages || zone.Messages.Count() == 0)
                continue;

            vector zonePos = Vector(zone.X, pos[1], zone.Z);
            if (vector.Distance(pos, zonePos) > zone.Radius)
                continue;

            float chance = zone.Chance;
            if (chance <= 0.0)
                chance = config.CustomThoughtZoneDefaultChance;

            if (Math.RandomFloatInclusive(0.0, 1.0) > chance)
                continue;

            low.Insert(zone.Messages.GetRandomElement());
            m_ST_LastCustomThoughtZoneThoughtTime = now;
            return;
        }
    }



    void ST_AddSocialGroupThoughts(ST_SurvivorThoughtsConfig config, array<string> medium, array<string> low)
    {
        if (!config || config.EnableSocialGroupThoughts != 1)
            return;

        if (!GetGame())
            return;

        float now = GetGame().GetTime() / 1000.0;

        if ((now - m_ST_LastSocialGroupThoughtTime) < config.SocialGroupThoughtCooldownSeconds)
            return;

        if (Math.RandomFloatInclusive(0.0, 1.0) > config.SocialGroupThoughtChance)
            return;

        bool hasBond = ST_HasRecentSocialBond();

        if (m_ST_LastSeenPlayerTime > 0.0 && (now - m_ST_LastSeenPlayerTime) >= config.LoneWolfNoPlayerSeenSeconds)
        {
            if (config.EnableLoneWolfMessages == 1 && config.LoneWolfMessages && config.LoneWolfMessages.Count() > 0)
            {
                low.Insert(config.LoneWolfMessages.GetRandomElement());
                m_ST_LastSocialGroupThoughtTime = now;
                m_ST_SelectedThoughtType = "SOCIAL_GROUP";
            }

            return;
        }

        if (hasBond && config.EnableFriendlyNearbyMessages == 1 && config.FriendlyNearbyMessages && config.FriendlyNearbyMessages.Count() > 0)
        {
            low.Insert(config.FriendlyNearbyMessages.GetRandomElement());
            m_ST_LastSocialGroupThoughtTime = now;
            m_ST_SelectedThoughtType = "SOCIAL_GROUP";
        }
    }

    void ST_AddSanityCreepThoughts(ST_SurvivorThoughtsConfig config, array<string> high, array<string> medium, array<string> low)
    {
        if (!config || config.EnableSanityCreep != 1)
            return;

        if (!GetGame())
            return;

        float now = GetGame().GetTime() / 1000.0;

        if ((now - m_ST_LastSanityThoughtTime) < config.SanityThoughtCooldownSeconds)
            return;

        if (Math.RandomFloatInclusive(0.0, 1.0) > config.SanityThoughtChance)
            return;

        float sanity = ST_GetSanityValue(config);

        if (sanity <= config.SanityPsychoticThreshold)
        {
            if (config.EnableSanityPsychoticMessages == 1 && config.SanityPsychoticMessages && config.SanityPsychoticMessages.Count() > 0)
            {
                high.Insert(config.SanityPsychoticMessages.GetRandomElement());
                m_ST_LastSanityThoughtTime = now;
                m_ST_SelectedThoughtType = "SANITY_CREEP";
            }

            return;
        }

        if (sanity <= config.SanityUnhingedThreshold)
        {
            if (config.EnableSanityUnhingedMessages == 1 && config.SanityUnhingedMessages && config.SanityUnhingedMessages.Count() > 0)
            {
                medium.Insert(config.SanityUnhingedMessages.GetRandomElement());
                m_ST_LastSanityThoughtTime = now;
                m_ST_SelectedThoughtType = "SANITY_CREEP";
            }

            return;
        }

        if (sanity <= config.SanityUneasyThreshold)
        {
            if (config.EnableSanityUneasyMessages == 1 && config.SanityUneasyMessages && config.SanityUneasyMessages.Count() > 0)
            {
                low.Insert(config.SanityUneasyMessages.GetRandomElement());
                m_ST_LastSanityThoughtTime = now;
                m_ST_SelectedThoughtType = "SANITY_CREEP";
            }
        }
    }


    void ST_AddPersonalityThoughts(ST_SurvivorThoughtsConfig config, array<string> low)
    {
        if (config.EnablePersonalityProfiles != 1)
            return;

        float roll = Math.RandomFloatInclusive(0.0, 1.0);
        if (roll > config.PersonalityThoughtChance)
            return;

        if (m_ST_PersonalityProfile == "")
            m_ST_PersonalityProfile = SurvivorThoughtsManager.Get().GetOrCreatePersonalityForPlayer(this);

        if (m_ST_PersonalityProfile == "Practical")
            ST_InsertRandomStageMessage(config.PersonalityPracticalMessages, low);
        else if (m_ST_PersonalityProfile == "Scared")
            ST_InsertRandomStageMessage(config.PersonalityScaredMessages, low);
        else if (m_ST_PersonalityProfile == "Military")
            ST_InsertRandomStageMessage(config.PersonalityMilitaryMessages, low);
        else if (m_ST_PersonalityProfile == "Hopeless")
            ST_InsertRandomStageMessage(config.PersonalityHopelessMessages, low);
        else if (m_ST_PersonalityProfile == "Aggressive")
            ST_InsertRandomStageMessage(config.PersonalityAggressiveMessages, low);
        else
            ST_InsertRandomStageMessage(config.PersonalityCalmMessages, low);
    }

    bool ST_AddCombinedWeatherThought(ST_SurvivorThoughtsConfig config, array<string> parts)
    {
        if (!config || config.EnableWeatherThoughts != 1)
            return false;

        if (!GetGame())
            return false;

        Weather weather = GetGame().GetWeather();
        if (!weather)
            return false;

        float rain = 0.0;
        float fog = 0.0;
        float overcast = 0.0;
        float wind = weather.GetWindSpeed();

        WeatherPhenomenon rainPhenomenon = weather.GetRain();
        if (rainPhenomenon)
            rain = rainPhenomenon.GetActual();

        WeatherPhenomenon fogPhenomenon = weather.GetFog();
        if (fogPhenomenon)
            fog = fogPhenomenon.GetActual();

        WeatherPhenomenon overcastPhenomenon = weather.GetOvercast();
        if (overcastPhenomenon)
            overcast = overcastPhenomenon.GetActual();

        if (config.EnableStormWeatherMessages == 1 && ((rain >= config.StormRain_Min && wind >= config.StormWind_Min) || overcast >= config.StormOvercast_Min))
            return ST_AddRandomPart(config.WeatherStormMessages, parts);

        if (config.EnableHeavyRainMessages == 1 && rain >= config.HeavyRainThought_Min)
        {
            if (config.WeatherHeavyRainMessages && config.WeatherHeavyRainMessages.Count() > 0)
                return ST_AddRandomPart(config.WeatherHeavyRainMessages, parts);

            return ST_AddRandomPart(config.WeatherRainMessages, parts);
        }

        if (config.EnableLightRainMessages == 1 && rain >= config.LightRainThought_Min)
        {
            if (config.WeatherLightRainMessages && config.WeatherLightRainMessages.Count() > 0)
                return ST_AddRandomPart(config.WeatherLightRainMessages, parts);

            return ST_AddRandomPart(config.WeatherRainMessages, parts);
        }

        if (rain >= config.RainThought_Min)
            return ST_AddRandomPart(config.WeatherRainMessages, parts);

        if (config.EnableFogWeatherMessages == 1 && fog >= config.FogThought_Min)
            return ST_AddRandomPart(config.WeatherFogMessages, parts);

        if (config.EnableWindWeatherMessages == 1 && wind >= config.WindThought_Min)
            return ST_AddRandomPart(config.WeatherWindMessages, parts);

        if (config.EnableOvercastWeatherMessages == 1 && overcast >= config.OvercastThought_Min)
            return ST_AddRandomPart(config.WeatherOvercastMessages, parts);

        if (config.EnableClearWeatherMessages == 1 && overcast < config.OvercastThought_Min && rain < config.LightRainThought_Min && fog < config.FogThought_Min)
            return ST_AddRandomPart(config.WeatherClearMessages, parts);

        return false;
    }

    bool ST_AddCombinedTimeOfDayThought(ST_SurvivorThoughtsConfig config, array<string> parts)
    {
        if (!config || config.EnableTimeOfDayThoughts != 1)
            return false;

        array<string> messages = ST_GetCurrentTimeOfDayMessages(config);
        if (!messages || messages.Count() == 0)
            return false;

        return ST_AddRandomPart(messages, parts);
    }

    bool ST_AddCombinedItemConditionThought(ST_SurvivorThoughtsConfig config, array<string> parts)
    {
        if (config.EnableItemConditionThoughts != 1)
            return false;

        EntityAI item = GetItemInHands();
        if (ST_IsItemBadlyDamaged(item, config.ItemConditionHealthThreshold))
            return ST_AddRandomPart(config.ItemBadlyDamagedMessages, parts);

        if (config.ScanEquippedItemsForDamagedThoughts != 1)
            return false;

        EntityAI shoulder = FindAttachmentBySlotName("Shoulder");
        if (ST_IsItemBadlyDamaged(shoulder, config.ItemConditionHealthThreshold))
            return ST_AddRandomPart(config.ItemWeaponDamagedMessages, parts);

        EntityAI feet = FindAttachmentBySlotName("Feet");
        if (ST_IsItemBadlyDamaged(feet, config.ItemConditionHealthThreshold))
            return ST_AddRandomPart(config.ItemShoesDamagedMessages, parts);

        EntityAI body = FindAttachmentBySlotName("Body");
        if (ST_IsItemBadlyDamaged(body, config.ItemConditionHealthThreshold))
            return ST_AddRandomPart(config.ItemClothingDamagedMessages, parts);

        EntityAI back = FindAttachmentBySlotName("Back");
        if (ST_IsItemBadlyDamaged(back, config.ItemConditionHealthThreshold))
            return ST_AddRandomPart(config.ItemBackpackDamagedMessages, parts);

        return false;
    }

    bool ST_AddCombinedCombatStressThought(ST_SurvivorThoughtsConfig config, array<string> parts)
    {
        if (config.EnableCombatStressThoughts != 1 || config.EnableCombatStressShockThoughts != 1)
            return false;

        float shock = ST_GetShockValue();

        if (shock > 0.0 && shock <= config.CombatStressShockThreshold)
            return ST_AddRandomPart(config.CombatShockMessages, parts);

        return false;
    }

    bool ST_AddCombinedContaminatedZoneThought(ST_SurvivorThoughtsConfig config, array<string> parts)
    {
        if (config.EnableContaminatedZoneThoughts != 1)
            return false;

        if (!GetModifiersManager())
            return false;

        if (ST_IsModifierActiveSafe(eModifiers.MDF_AREAEXPOSURE))
            return ST_AddRandomPart(config.ContaminatedZoneMessages, parts);

        return false;
    }

    bool ST_AddCombinedNearbyCorpseThought(ST_SurvivorThoughtsConfig config, array<string> parts)
    {
        if (config.EnableNearbyCorpseThoughts != 1)
            return false;

        array<Object> nearbyObjects = new array<Object>;
        array<CargoBase> proxyCargos = new array<CargoBase>;

        if (!GetGame())
            return false;

        GetGame().GetObjectsAtPosition3D(GetPosition(), config.NearbyCorpseRadius, nearbyObjects, proxyCargos);

        foreach (Object obj : nearbyObjects)
        {
            if (!obj || obj == this)
                continue;

            SurvivorBase survivor = SurvivorBase.Cast(obj);
            if (survivor && !survivor.IsAlive())
                return ST_AddRandomPart(config.NearbyCorpseMessages, parts);

            ZombieBase infected = ZombieBase.Cast(obj);
            if (infected && !infected.IsAlive())
                return ST_AddRandomPart(config.NearbyCorpseMessages, parts);

            AnimalBase animal = AnimalBase.Cast(obj);
            if (animal && !animal.IsAlive())
                return ST_AddRandomPart(config.NearbyCorpseMessages, parts);
        }

        return false;
    }


    int ST_GetTrendValue(float oldValue, float newValue, float threshold)
    {
        if (oldValue < 0.0)
            return 0;

        if ((newValue - oldValue) > threshold)
            return 1;

        if ((oldValue - newValue) > threshold)
            return -1;

        return 0;
    }

    void ST_UpdatePlayerStateHistory(ST_SurvivorThoughtsConfig config)
    {
        if (!config || config.EnablePlayerStateHistory != 1 || !GetGame())
            return;

        float now = GetGame().GetTime() / 1000.0;

        if (m_ST_StateHistoryLastSampleTime > 0.0 && (now - m_ST_StateHistoryLastSampleTime) < config.StateHistorySampleIntervalSeconds)
            return;

        float energy = ST_GetEnergyValue();
        float water = ST_GetWaterValue();
        float blood = ST_GetBloodValue();
        float health = ST_GetHealthValue();
        float shock = ST_GetShockValue();
        float heatComfort = ST_GetHeatComfortValue();

        if (energy <= config.EnergyStage4_Max)
        {
            if (m_ST_StarvingSince <= 0.0)
                m_ST_StarvingSince = now;
        }
        else
        {
            m_ST_StarvingSince = 0.0;
        }

        if (water <= config.WaterStage4_Max)
        {
            if (m_ST_DehydratedSince <= 0.0)
                m_ST_DehydratedSince = now;
        }
        else
        {
            m_ST_DehydratedSince = 0.0;
        }

        if (heatComfort <= config.DeathSpiralColdComfort_Max)
        {
            if (m_ST_ColdSince <= 0.0)
                m_ST_ColdSince = now;
        }
        else
        {
            m_ST_ColdSince = 0.0;
        }

        if (heatComfort >= config.DeathSpiralHotComfort_Min)
        {
            if (m_ST_HotSince <= 0.0)
                m_ST_HotSince = now;
        }
        else
        {
            m_ST_HotSince = 0.0;
        }

        if (GetBleedingSourceCount() > 0)
        {
            if (m_ST_BleedingSince <= 0.0)
                m_ST_BleedingSince = now;
        }
        else
        {
            m_ST_BleedingSince = 0.0;
        }

        if (ST_IsModifierActiveSafe(eModifiers.MDF_WOUND_INFECTION) || ST_IsModifierActiveSafe(eModifiers.MDF_CHOLERA) || ST_IsModifierActiveSafe(eModifiers.MDF_INFLUENZA))
        {
            if (m_ST_SickSince <= 0.0)
                m_ST_SickSince = now;
        }
        else
        {
            m_ST_SickSince = 0.0;
        }

        m_ST_EnergyTrend = ST_GetTrendValue(m_ST_StateHistoryLastEnergy, energy, config.TrendChangeThreshold);
        m_ST_WaterTrend = ST_GetTrendValue(m_ST_StateHistoryLastWater, water, config.TrendChangeThreshold);
        m_ST_BloodTrend = ST_GetTrendValue(m_ST_StateHistoryLastBlood, blood, config.TrendChangeThreshold);
        m_ST_HealthTrend = ST_GetTrendValue(m_ST_StateHistoryLastHealth, health, config.TrendChangeThreshold);
        m_ST_ShockTrend = ST_GetTrendValue(m_ST_StateHistoryLastShock, shock, config.TrendChangeThreshold);
        m_ST_TemperatureTrend = ST_GetTrendValue(m_ST_StateHistoryLastHeatComfort, heatComfort, 0.05);

        m_ST_StateHistoryLastEnergy = energy;
        m_ST_StateHistoryLastWater = water;
        m_ST_StateHistoryLastBlood = blood;
        m_ST_StateHistoryLastHealth = health;
        m_ST_StateHistoryLastShock = shock;
        m_ST_StateHistoryLastHeatComfort = heatComfort;
        m_ST_StateHistoryLastSampleTime = now;

        if (config.EnableStateSnapshots == 1 && (m_ST_LastStateSnapshotTime <= 0.0 || (now - m_ST_LastStateSnapshotTime) >= config.StateSnapshotIntervalSeconds))
        {
            m_ST_LastStateSnapshotTime = now;
            string snapshot = "{ \"Time\": \"" + SurvivorThoughtsManager.Get().ST_GetTimestamp() + "\"";
            snapshot = snapshot + ", \"Health\": " + health.ToString();
            snapshot = snapshot + ", \"Blood\": " + blood.ToString();
            snapshot = snapshot + ", \"Shock\": " + shock.ToString();
            snapshot = snapshot + ", \"Energy\": " + energy.ToString();
            snapshot = snapshot + ", \"Water\": " + water.ToString();
            snapshot = snapshot + ", \"HeatComfort\": " + heatComfort.ToString();
            snapshot = snapshot + ", \"BleedingSources\": " + GetBleedingSourceCount().ToString();
            snapshot = snapshot + ", \"Sanity\": " + ST_GetSanityValue(config).ToString();
            snapshot = snapshot + " }";
            SurvivorThoughtsManager.Get().ST_WritePlayerStateSnapshot(this, snapshot);
        }
    }

    void ST_AddStateHistoryThoughts(ST_SurvivorThoughtsConfig config, array<string> high, array<string> medium, array<string> low)
    {
        if (!config || config.EnablePlayerStateHistory != 1 || config.EnableTrendMessages != 1)
            return;

        if (m_ST_EnergyTrend < 0 && ST_GetEnergyValue() <= config.EnergyStage4_Max)
        {
            m_ST_SelectedThoughtType = "STATE_HISTORY";
            ST_InsertRandomStageMessage(config.TrendEnergyFallingMessages, high);
        }

        if (m_ST_WaterTrend < 0 && ST_GetWaterValue() <= config.WaterStage4_Max)
        {
            m_ST_SelectedThoughtType = "STATE_HISTORY";
            ST_InsertRandomStageMessage(config.TrendWaterFallingMessages, high);
        }

        if (m_ST_BloodTrend < 0 && ST_GetBloodValue() <= config.BloodStage3_Max)
        {
            m_ST_SelectedThoughtType = "STATE_HISTORY";
            ST_InsertRandomStageMessage(config.TrendBloodFallingMessages, high);
        }

        if (m_ST_HealthTrend < 0)
        {
            m_ST_SelectedThoughtType = "STATE_HISTORY";
            ST_InsertRandomStageMessage(config.TrendHealthFallingMessages, medium);
        }

        if (ST_IsModifierActiveSafe(eModifiers.MDF_WOUND_INFECTION) || ST_IsModifierActiveSafe(eModifiers.MDF_CHOLERA) || ST_IsModifierActiveSafe(eModifiers.MDF_INFLUENZA))
        {
            m_ST_SelectedThoughtType = "STATE_HISTORY";
            ST_InsertRandomStageMessage(config.LongSicknessMessages, medium);
        }

        if (GetBleedingSourceCount() > 0)
        {
            m_ST_SelectedThoughtType = "STATE_HISTORY";
            ST_InsertRandomStageMessage(config.LongBleedingMessages, high);
        }

        if (config.EnableProlongedStateMessages == 1 && GetGame())
        {
            float now = GetGame().GetTime() / 1000.0;

            if (m_ST_StarvingSince > 0.0 && (now - m_ST_StarvingSince) >= config.ProlongedStateThresholdSeconds)
            {
                m_ST_SelectedThoughtType = "STATE_HISTORY";
                ST_InsertRandomStageMessage(config.ProlongedStarvationMessages, high);
            }

            if (m_ST_DehydratedSince > 0.0 && (now - m_ST_DehydratedSince) >= config.ProlongedStateThresholdSeconds)
            {
                m_ST_SelectedThoughtType = "STATE_HISTORY";
                ST_InsertRandomStageMessage(config.ProlongedDehydrationMessages, high);
            }

            if (m_ST_ColdSince > 0.0 && (now - m_ST_ColdSince) >= config.ProlongedStateThresholdSeconds)
            {
                m_ST_SelectedThoughtType = "STATE_HISTORY";
                ST_InsertRandomStageMessage(config.ProlongedColdMessages, high);
            }

            if (m_ST_HotSince > 0.0 && (now - m_ST_HotSince) >= config.ProlongedStateThresholdSeconds)
            {
                m_ST_SelectedThoughtType = "STATE_HISTORY";
                ST_InsertRandomStageMessage(config.ProlongedHeatMessages, high);
            }

            if (m_ST_BleedingSince > 0.0 && (now - m_ST_BleedingSince) >= config.ProlongedStateThresholdSeconds)
            {
                m_ST_SelectedThoughtType = "STATE_HISTORY";
                ST_InsertRandomStageMessage(config.ProlongedBleedingMessages, high);
            }

            if (m_ST_SickSince > 0.0 && (now - m_ST_SickSince) >= config.ProlongedStateThresholdSeconds)
            {
                m_ST_SelectedThoughtType = "STATE_HISTORY";
                ST_InsertRandomStageMessage(config.ProlongedSicknessMessages, medium);
            }
        }
    }



    void ST_AddRecoveryThoughts(ST_SurvivorThoughtsConfig config, array<string> medium, array<string> low)
    {
        if (!config || config.EnableRecoveryMessages != 1 || !GetGame())
            return;

        float now = GetGame().GetTime() / 1000.0;

        if (m_ST_LastRecoveryThoughtTime > 0.0 && (now - m_ST_LastRecoveryThoughtTime) < config.RecoveryThoughtCooldownSeconds)
            return;

        if (Math.RandomFloatInclusive(0.0, 1.0) > config.RecoveryThoughtChance)
            return;

        bool isBleeding = GetBleedingSourceCount() > 0;
        bool isStarving = ST_GetEnergyValue() <= config.EnergyStage4_Max;
        bool isDehydrated = ST_GetWaterValue() <= config.WaterStage4_Max;
        bool isCold = ST_GetHeatComfortValue() <= config.DeathSpiralColdComfort_Max;
        bool isHot = ST_GetHeatComfortValue() >= config.DeathSpiralHotComfort_Min;
        bool infectedThreat = ST_CountNearbyInfectedForSmartSystems(config.InfectedCloseRadius) > 0;
        bool lowShock = ST_GetShockValue() <= config.ShockStage4_Max;
        bool lowBlood = ST_GetBloodValue() <= config.BloodStage4_Max;
        bool nearDeath = ST_GetHealthValue() <= 20.0;
        bool nearShelter = ST_IsNearShelterForSmartSystems(config);
        bool combatStressed = m_ST_RecentDamageTime > 0.0 && (now - m_ST_RecentDamageTime) < 180.0;

        if (m_ST_WasNearDeathForRecovery && !nearDeath)
        {
            m_ST_SelectedThoughtType = "RECOVERY";
            m_ST_LastRecoveryThoughtTime = now;
            ST_InsertRandomStageMessage(config.AlmostDiedRecoveryMessages, medium);
        }
        else if (m_ST_WasLowShockForRecovery && !lowShock)
        {
            m_ST_SelectedThoughtType = "RECOVERY";
            m_ST_LastRecoveryThoughtTime = now;
            ST_InsertRandomStageMessage(config.ShockRecoveryMessages, medium);
        }
        else if (m_ST_WasLowBloodForRecovery && !lowBlood)
        {
            m_ST_SelectedThoughtType = "RECOVERY";
            m_ST_LastRecoveryThoughtTime = now;
            ST_InsertRandomStageMessage(config.BloodStabilizingMessages, medium);
        }
        else if (!m_ST_WasInShelterForRecovery && nearShelter && (isCold || isHot || infectedThreat))
        {
            m_ST_SelectedThoughtType = "RECOVERY";
            m_ST_LastRecoveryThoughtTime = now;
            ST_InsertRandomStageMessage(config.SafeShelterRecoveryMessages, low);
        }
        else if (m_ST_WasCombatStressedForRecovery && !combatStressed)
        {
            m_ST_SelectedThoughtType = "RECOVERY";
            m_ST_LastRecoveryThoughtTime = now;
            ST_InsertRandomStageMessage(config.PostCombatBreathMessages, medium);
        }
        else if (m_ST_WasBleedingForRecovery && !isBleeding)
        {
            m_ST_SelectedThoughtType = "RECOVERY";
            m_ST_LastRecoveryThoughtTime = now;
            ST_InsertRandomStageMessage(config.BleedingRecoveryMessages, medium);
        }
        else if (m_ST_WasStarvingForRecovery && !isStarving)
        {
            m_ST_SelectedThoughtType = "RECOVERY";
            m_ST_LastRecoveryThoughtTime = now;
            ST_InsertRandomStageMessage(config.FoodRecoveryMessages, low);
        }
        else if (m_ST_WasDehydratedForRecovery && !isDehydrated)
        {
            m_ST_SelectedThoughtType = "RECOVERY";
            m_ST_LastRecoveryThoughtTime = now;
            ST_InsertRandomStageMessage(config.WaterRecoveryMessages, low);
        }
        else if (m_ST_WasColdForRecovery && !isCold)
        {
            m_ST_SelectedThoughtType = "RECOVERY";
            m_ST_LastRecoveryThoughtTime = now;
            ST_InsertRandomStageMessage(config.WarmedUpMessages, low);
        }
        else if (m_ST_WasHotForRecovery && !isHot)
        {
            m_ST_SelectedThoughtType = "RECOVERY";
            m_ST_LastRecoveryThoughtTime = now;
            ST_InsertRandomStageMessage(config.CooledDownMessages, low);
        }
        else if (m_ST_WasThreatenedByInfectedForRecovery && !infectedThreat)
        {
            m_ST_SelectedThoughtType = "RECOVERY";
            m_ST_LastRecoveryThoughtTime = now;
            ST_InsertRandomStageMessage(config.EscapedInfectedMessages, low);
        }

        m_ST_WasBleedingForRecovery = isBleeding;
        m_ST_WasStarvingForRecovery = isStarving;
        m_ST_WasDehydratedForRecovery = isDehydrated;
        m_ST_WasColdForRecovery = isCold;
        m_ST_WasHotForRecovery = isHot;
        m_ST_WasThreatenedByInfectedForRecovery = infectedThreat;
        m_ST_WasLowShockForRecovery = lowShock;
        m_ST_WasLowBloodForRecovery = lowBlood;
        m_ST_WasNearDeathForRecovery = nearDeath;
        m_ST_WasInShelterForRecovery = nearShelter;
        m_ST_WasCombatStressedForRecovery = combatStressed;
    }

    void ST_AddNearMissCombatThoughts(ST_SurvivorThoughtsConfig config, array<string> high, array<string> medium)
    {
        if (!config || config.EnableNearMissCombatMessages != 1 || !GetGame())
            return;

        float now = GetGame().GetTime() / 1000.0;

        if (m_ST_LastNearMissCombatTime <= 0.0)
            return;

        if ((now - m_ST_LastNearMissCombatTime) > 60.0)
            return;

        if (m_ST_LastNearMissCombatThoughtTime > 0.0 && (now - m_ST_LastNearMissCombatThoughtTime) < config.NearMissCombatCooldownSeconds)
            return;

        if (Math.RandomFloatInclusive(0.0, 1.0) > config.NearMissCombatChance)
            return;

        m_ST_SelectedThoughtType = "NEAR_MISS";
        m_ST_LastNearMissCombatThoughtTime = now;
        ST_InsertRandomStageMessage(config.NearMissCombatGeneralMessages, medium);
    }

    void ST_AddDiseaseSpecificThoughts(ST_SurvivorThoughtsConfig config, array<string> high, array<string> medium)
    {
        if (!config || config.EnableDiseaseSpecificMessages != 1)
            return;

        if (ST_IsModifierActiveSafe(eModifiers.MDF_WOUND_INFECTION))
        {
            m_ST_SelectedThoughtType = "DISEASE_SPECIFIC";
            ST_InsertRandomStageMessage(config.DiseaseWoundInfectionMessages, high);
        }

        if (ST_IsModifierActiveSafe(eModifiers.MDF_CHOLERA))
        {
            m_ST_SelectedThoughtType = "DISEASE_SPECIFIC";
            ST_InsertRandomStageMessage(config.DiseaseCholeraMessages, high);
        }

        if (ST_IsModifierActiveSafe(eModifiers.MDF_INFLUENZA))
        {
            m_ST_SelectedThoughtType = "DISEASE_SPECIFIC";
            ST_InsertRandomStageMessage(config.DiseaseInfluenzaMessages, medium);
            ST_InsertRandomStageMessage(config.DiseaseFeverMessages, medium);
        }

        if (ST_IsModifierActiveSafe(eModifiers.MDF_AREAEXPOSURE))
        {
            m_ST_SelectedThoughtType = "DISEASE_SPECIFIC";
            ST_InsertRandomStageMessage(config.DiseaseGasExposureMessages, high);
        }
    }

    void ST_AddMapEnvironmentThoughts(ST_SurvivorThoughtsConfig config, array<string> low)
    {
        if (!config || config.EnableMapEnvironmentPacks != 1 || !GetGame())
            return;

        float now = GetGame().GetTime() / 1000.0;

        if (m_ST_LastMapEnvironmentThoughtTime > 0.0 && (now - m_ST_LastMapEnvironmentThoughtTime) < config.MapEnvironmentThoughtCooldownSeconds)
            return;

        if (Math.RandomFloatInclusive(0.0, 1.0) > config.MapEnvironmentThoughtChance)
            return;

        m_ST_SelectedThoughtType = "MAP_ENVIRONMENT";
        m_ST_LastMapEnvironmentThoughtTime = now;

        string pack = config.ActiveMapEnvironmentPack;

        if (pack == "Chernarus")
            ST_InsertRandomStageMessage(config.MapChernarusMessages, low);
        else if (pack == "Livonia")
            ST_InsertRandomStageMessage(config.MapLivoniaMessages, low);
        else if (pack == "Namalsk")
            ST_InsertRandomStageMessage(config.MapNamalskMessages, low);
        else if (pack == "Sakhal")
            ST_InsertRandomStageMessage(config.MapSakhalMessages, low);
        else if (pack == "DeerIsle")
            ST_InsertRandomStageMessage(config.MapDeerIsleMessages, low);
        else
            ST_InsertRandomStageMessage(config.MapGenericMessages, low);
    }


    string ST_GetSurvivorThoughtsStatSummary()
    {
        string result = "{";
        result += "\"Health\":" + ST_GetHealthValue().ToString();
        result += ",\"Blood\":" + ST_GetBloodValue().ToString();
        result += ",\"Shock\":" + ST_GetShockValue().ToString();
        result += ",\"Energy\":" + ST_GetEnergyValue().ToString();
        result += ",\"Water\":" + ST_GetWaterValue().ToString();
        result += ",\"HeatComfort\":" + ST_GetHeatComfortValue().ToString();
        result += ",\"BleedingSources\":" + GetBleedingSourceCount().ToString();
        result += ",\"Sanity\":" + ST_GetSanityValue(SurvivorThoughtsManager.Get().GetConfig()).ToString();
        result += "}";
        return result;
    }




    override void OnRPC(PlayerIdentity sender, int rpc_type, ParamsReadContext ctx)
    {
        super.OnRPC(sender, rpc_type, ctx);

        // Server-to-client config-editor responses.
        if (GetGame() && !GetGame().IsServer())
        {
            ST_AdminConfigEditorClientState state = ST_AdminConfigEditorClientState.Get();

            if (rpc_type == ST_JournalRPC.ST_RPC_ADMIN_CONFIG_LIST_RESPONSE)
            {
                state.OnFileList(ctx);
                return;
            }

            if (rpc_type == ST_JournalRPC.ST_RPC_ADMIN_CONFIG_LOAD_BEGIN)
            {
                state.OnLoadBegin(ctx);
                return;
            }

            if (rpc_type == ST_JournalRPC.ST_RPC_ADMIN_CONFIG_LOAD_CHUNK)
            {
                state.OnLoadChunk(ctx);
                return;
            }

            if (rpc_type == ST_JournalRPC.ST_RPC_ADMIN_CONFIG_LOAD_END)
            {
                state.OnLoadEnd(ctx);
                return;
            }

            if (rpc_type == ST_JournalRPC.ST_RPC_ADMIN_CONFIG_RESULT)
            {
                state.OnResult(ctx);
                return;
            }

            return;
        }

        if (!GetGame() || !GetGame().IsServer())
            return;

        if (ST_AdminConfigEditorService.Get().IsEditorRPC(rpc_type))
        {
            ST_AdminConfigEditorService.Get().HandleRPC(this, sender, rpc_type, ctx);
            return;
        }

        if (ST_AdminPriorityTriggerSystem.Get().IsAdminRPC(rpc_type))
        {
            if (!sender)
                return;

            string adminCommand;
            if (!ctx.Read(adminCommand))
                adminCommand = "";

            ST_AdminPriorityTriggerSystem.Get().HandleAdminCommand(this, adminCommand);
            return;
        }

        return;
    }
}
