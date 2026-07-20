// Survivor Thoughts - persistent pairwise trust ledger.
// Trust rises slowly while two living players remain close and falls sharply on betrayal damage.

class ST_TrustPairRecord
{
    string PlayerA;
    string PlayerB;
    float Trust;
    int LastUpdated;

    void ST_TrustPairRecord()
    {
        PlayerA = "";
        PlayerB = "";
        Trust = 0.0;
        LastUpdated = 0;
    }
}

class ST_TrustLedgerFile
{
    ref array<ref ST_TrustPairRecord> Pairs;

    void ST_TrustLedgerFile()
    {
        Pairs = new array<ref ST_TrustPairRecord>;
    }
}

class ST_TrustLedger
{
    protected static ref ST_TrustLedger s_Instance;
    protected ref ST_TrustLedgerFile m_Data;
    protected string m_Path;
    protected bool m_Started;

    static ST_TrustLedger Get()
    {
        if (!s_Instance)
            s_Instance = new ST_TrustLedger();
        return s_Instance;
    }

    void ST_TrustLedger()
    {
        m_Path = "$mission:storage_1/ZombiCideMods/SurvivorThoughts/Data/TrustLedger.json";
        m_Data = new ST_TrustLedgerFile();
        ST_Load();
    }

    void Start()
    {
        if (m_Started || !GetGame() || !GetGame().IsServer())
            return;

        m_Started = true;
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(ST_ProximityTick, 60000, true);
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(ST_Save, 300000, true);
    }

    protected void ST_Load()
    {
        if (FileExist(m_Path))
            JsonFileLoader<ST_TrustLedgerFile>.JsonLoadFile(m_Path, m_Data);

        if (!m_Data)
            m_Data = new ST_TrustLedgerFile();
        if (!m_Data.Pairs)
            m_Data.Pairs = new array<ref ST_TrustPairRecord>;
    }

    void ST_Save()
    {
        if (!GetGame() || !GetGame().IsServer() || !m_Data)
            return;
        JsonFileLoader<ST_TrustLedgerFile>.JsonSaveFile(m_Path, m_Data);
    }

    protected string ST_Id(PlayerBase player)
    {
        if (!player || !player.GetIdentity())
            return "";
        return player.GetIdentity().GetPlainId();
    }

    protected ST_TrustPairRecord ST_Find(string first, string second, bool create)
    {
        foreach (ST_TrustPairRecord record : m_Data.Pairs)
        {
            if (!record)
                continue;
            if ((record.PlayerA == first && record.PlayerB == second) || (record.PlayerA == second && record.PlayerB == first))
                return record;
        }

        if (!create)
            return NULL;

        ST_TrustPairRecord created = new ST_TrustPairRecord();
        created.PlayerA = first;
        created.PlayerB = second;
        m_Data.Pairs.Insert(created);
        return created;
    }

    float GetTrust(PlayerBase first, PlayerBase second)
    {
        ST_TrustPairRecord record = ST_Find(ST_Id(first), ST_Id(second), false);
        if (!record)
            return 0.0;
        return record.Trust;
    }

    void AddTrust(PlayerBase first, PlayerBase second, float amount)
    {
        string firstId = ST_Id(first);
        string secondId = ST_Id(second);
        if (firstId == "" || secondId == "" || firstId == secondId)
            return;

        ST_TrustPairRecord record = ST_Find(firstId, secondId, true);
        record.Trust = Math.Clamp(record.Trust + amount, -100.0, 100.0);
        record.LastUpdated = GetGame().GetTime();
    }

    void RecordDamageBetrayal(PlayerBase victim, PlayerBase attacker)
    {
        if (!victim || !attacker || victim == attacker)
            return;

        float priorTrust = GetTrust(victim, attacker);
        AddTrust(victim, attacker, -40.0);

        if (priorTrust >= 15.0)
        {
            ST_TriggerMessageRouter.Get().Send(victim, "BetrayalTrustMessages", "SOCIAL_GROUP", 120.0);
            ST_SurvivorStorySystem.Get().AddMajorEvent(victim, "[BETRAYAL] Someone I trusted turned their weapon on me.");
        }
    }

    protected void ST_ProximityTick()
    {
        if (!GetGame() || !GetGame().IsServer())
            return;

        array<Man> players = new array<Man>;
        GetGame().GetPlayers(players);

        for (int i = 0; i < players.Count(); i++)
        {
            PlayerBase first = PlayerBase.Cast(players.Get(i));
            if (!first || !first.IsAlive())
                continue;

            for (int j = i + 1; j < players.Count(); j++)
            {
                PlayerBase second = PlayerBase.Cast(players.Get(j));
                if (!second || !second.IsAlive())
                    continue;

                float distance = vector.Distance(first.GetPosition(), second.GetPosition());
                if (distance <= 15.0)
                    AddTrust(first, second, 0.5);
            }
        }

        ST_Decay();
    }

    protected void ST_Decay()
    {
        if (!m_Data || !m_Data.Pairs)
            return;

        foreach (ST_TrustPairRecord record : m_Data.Pairs)
        {
            if (!record)
                continue;

            if (record.Trust > 0.0)
                record.Trust = Math.Max(0.0, record.Trust - 0.10);
            else if (record.Trust < 0.0)
                record.Trust = Math.Min(0.0, record.Trust + 0.05);
        }
    }
}
