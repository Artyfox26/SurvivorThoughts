class ST_PlayerJournalRecord
{
    string SteamId;
    string JournalId;
    string OwnerName;
    int OwnerDead;

    string JournalCharacterName;
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
    float JournalDeathTime;

    ref array<string> MajorJournalEvents;

    void ST_PlayerJournalRecord()
    {
        MajorJournalEvents = new array<string>;
    }
}
