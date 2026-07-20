class ST_PlayerPersonalityRecord
{
    string SteamId;
    string Personality;
    float LastPersonalityChangeTime;
    int PersonalityChanges;
}

class ST_PlayerPersonalityStore
{
    ref array<ref ST_PlayerPersonalityRecord> Profiles;

    void ST_PlayerPersonalityStore()
    {
        Profiles = new array<ref ST_PlayerPersonalityRecord>;
    }

    string GetPersonality(string steamId)
    {
        if (!Profiles)
            Profiles = new array<ref ST_PlayerPersonalityRecord>;

        foreach (ST_PlayerPersonalityRecord record : Profiles)
        {
            if (record && record.SteamId == steamId)
                return record.Personality;
        }

        return "";
    }

    ST_PlayerPersonalityRecord GetRecord(string steamId)
    {
        if (!Profiles)
            Profiles = new array<ref ST_PlayerPersonalityRecord>;

        foreach (ST_PlayerPersonalityRecord record : Profiles)
        {
            if (record && record.SteamId == steamId)
                return record;
        }

        return NULL;
    }

    void SetPersonalityWithTime(string steamId, string personality, float changeTime)
    {
        if (!Profiles)
            Profiles = new array<ref ST_PlayerPersonalityRecord>;

        ST_PlayerPersonalityRecord record = GetRecord(steamId);

        if (record)
        {
            if (record.Personality != personality)
                record.PersonalityChanges++;

            record.Personality = personality;
            record.LastPersonalityChangeTime = changeTime;
            return;
        }

        ST_PlayerPersonalityRecord newRecord = new ST_PlayerPersonalityRecord();
        newRecord.SteamId = steamId;
        newRecord.Personality = personality;
        newRecord.LastPersonalityChangeTime = changeTime;
        newRecord.PersonalityChanges = 0;
        Profiles.Insert(newRecord);
    }


    void SetPersonality(string steamId, string personality)
    {
        SetPersonalityWithTime(steamId, personality, 0.0);
    }
}


class ST_PlayerPersistentStateRecord
{
    string SteamId;

    float LastPlayerMemoryThoughtTime;
    float RecentDamageTime;
    float RecentBleedingTime;
    float RecentGunshotTime;
    float RecentCorpseTime;
    float RecentMilitaryTime;
    float RecentSurvivalCrisisTime;

    float LastSocialGroupThoughtTime;
    float LastSeenPlayerTime;
    float NearbyFriendlySince;
    float SocialBondActiveUntil;
    int CompanionShotEvents;
    int CompanionDeathEvents;

    float SanityValue;
    float LastSanityThoughtTime;
    float LastSanityUpdateTime;
    float LastCannibalActionTime;
    int HumanSkinningCount;
    int HumanMeatCount;

    ref array<string> RecentThoughtMessages;

    int JournalSetupComplete;
    string JournalCharacterName;
    string JournalCharacterType;
    string JournalHeadType;
    string JournalOrigin;
    string JournalOccupation;
    string JournalTrait;
    string JournalFear;
    string JournalGoal;
    string JournalSkill;
    string JournalWeakness;
    string JournalMoralCode;
    string JournalBackstory;
    float JournalCreatedTime;
    float JournalLastUpdatedTime;
    ref array<string> MajorJournalEvents;

    ref array<float> RecentThoughtTimes;

    void ST_PlayerPersistentStateRecord()
    {
        RecentThoughtMessages = new array<string>;
        RecentThoughtTimes = new array<float>;
        MajorJournalEvents = new array<string>;
    }
}

class ST_PlayerPersistentStateStore
{
    ref array<ref ST_PlayerPersistentStateRecord> Players;

    void ST_PlayerPersistentStateStore()
    {
        Players = new array<ref ST_PlayerPersistentStateRecord>;
    }

    ST_PlayerPersistentStateRecord GetRecord(string steamId)
    {
        if (!Players)
            Players = new array<ref ST_PlayerPersistentStateRecord>;

        foreach (ST_PlayerPersistentStateRecord record : Players)
        {
            if (record && record.SteamId == steamId)
                return record;
        }

        return NULL;
    }

    ST_PlayerPersistentStateRecord GetOrCreateRecord(string steamId)
    {
        if (!Players)
            Players = new array<ref ST_PlayerPersistentStateRecord>;

        ST_PlayerPersistentStateRecord record = GetRecord(steamId);

        if (record)
        {
            if (!record.RecentThoughtMessages)
                record.RecentThoughtMessages = new array<string>;

            if (!record.RecentThoughtTimes)
                record.RecentThoughtTimes = new array<float>;

            if (!record.MajorJournalEvents)
                record.MajorJournalEvents = new array<string>;

            return record;
        }

        ST_PlayerPersistentStateRecord newRecord = new ST_PlayerPersistentStateRecord();
        newRecord.SteamId = steamId;
        newRecord.SanityValue = -1.0;
        Players.Insert(newRecord);

        return newRecord;
    }
}
