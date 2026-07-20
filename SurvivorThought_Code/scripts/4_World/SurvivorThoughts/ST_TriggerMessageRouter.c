// Survivor Thoughts - focused trigger message router.
// Keeps expansion-pool selection and localization out of action/player classes.

class ST_TriggerMessageRouter
{
    protected static ref ST_TriggerMessageRouter s_Instance;
    protected ref map<string, int> m_LastSent;

    static ST_TriggerMessageRouter Get()
    {
        if (!s_Instance)
            s_Instance = new ST_TriggerMessageRouter();
        return s_Instance;
    }

    void ST_TriggerMessageRouter()
    {
        m_LastSent = new map<string, int>;
    }

    void Send(PlayerBase player, string field, string thoughtType, float cooldownSeconds = 45.0)
    {
        if (!player || !GetGame() || !GetGame().IsServer())
            return;

        string playerId = "";
        if (player.GetIdentity())
            playerId = player.GetIdentity().GetPlainId();

        string key = playerId + "|" + field;
        int now = GetGame().GetTime();
        if (m_LastSent.Contains(key) && now - m_LastSent.Get(key) < cooldownSeconds * 1000)
            return;

        array<string> messages = ST_LocalizationService.Get().GetMessages(field);
        if (!messages || messages.Count() == 0)
            messages = ST_GetMessages(field);
        if (!messages || messages.Count() == 0)
            return;

        m_LastSent.Set(key, now);
        SurvivorThoughtsManager.Get().SendThoughtWithPriority(player, messages.GetRandomElement(), thoughtType);
    }

    protected array<string> ST_GetMessages(string field)
    {
        ST_AdminPriorityTriggerConfig cfg = ST_AdminPriorityTriggerSystem.Get().GetConfig();
        if (!cfg)
            return NULL;

        if (field == "HandsHygieneMessages") return cfg.HandsHygieneMessages;
        if (field == "GasMaskFilterMessages") return cfg.GasMaskFilterMessages;
        if (field == "BloodDiscoveryMessages") return cfg.BloodDiscoveryMessages;
        if (field == "BaseRaidMessages") return cfg.BaseRaidMessages;
        if (field == "BetrayalTrustMessages") return cfg.BetrayalTrustMessages;
        if (field == "VehicleMessages") return cfg.VehicleMessages;
        if (field == "MedicalTreatmentMessages") return cfg.MedicalTreatmentMessages;
        if (field == "FireAndShelterMessages") return cfg.FireAndShelterMessages;
        if (field == "WeaponStateMessages") return cfg.WeaponStateMessages;
        if (field == "AmmoStressMessages") return cfg.AmmoStressMessages;
        if (field == "HuntingFishingMessages") return cfg.HuntingFishingMessages;
        if (field == "CraftingMessages") return cfg.CraftingMessages;
        return NULL;
    }
}
