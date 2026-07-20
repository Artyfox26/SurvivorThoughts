// Survivor Thoughts - data-only localization for expansion trigger pools.
// Server owners can create Messages_<language>/09_Admin_Priority_Trigger_System.json.
// Empty or missing localized arrays fall back to the main English config.

class ST_LocalizedExpansionMessages
{
    ref array<string> MedicalTreatmentMessages;
    ref array<string> BloodDiscoveryMessages;
    ref array<string> FireAndShelterMessages;
    ref array<string> WeaponStateMessages;
    ref array<string> AmmoStressMessages;
    ref array<string> VehicleMessages;
    ref array<string> BaseRaidMessages;
    ref array<string> HuntingFishingMessages;
    ref array<string> CraftingMessages;
    ref array<string> HandsHygieneMessages;
    ref array<string> GasMaskFilterMessages;
    ref array<string> BetrayalTrustMessages;
}

class ST_LocalizationService
{
    protected static ref ST_LocalizationService s_Instance;
    protected ref ST_LocalizedExpansionMessages m_Pack;
    protected string m_LoadedLanguage;

    static ST_LocalizationService Get()
    {
        if (!s_Instance)
            s_Instance = new ST_LocalizationService();
        return s_Instance;
    }

    void Reload()
    {
        m_Pack = NULL;
        m_LoadedLanguage = "";

        ST_AdminPriorityTriggerConfig config = ST_AdminPriorityTriggerSystem.Get().GetConfig();
        if (!config || config.Language == "" || config.Language == "en")
            return;

        string path = config.LocalizedMessagesRoot + "/Messages_" + config.Language + "/09_Admin_Priority_Trigger_System.json";
        if (!FileExist(path))
            return;

        m_Pack = new ST_LocalizedExpansionMessages();
        JsonFileLoader<ST_LocalizedExpansionMessages>.JsonLoadFile(path, m_Pack);
        m_LoadedLanguage = config.Language;
    }

    array<string> GetMessages(string field)
    {
        ST_AdminPriorityTriggerConfig config = ST_AdminPriorityTriggerSystem.Get().GetConfig();
        if (!config)
            return NULL;

        if (m_LoadedLanguage != config.Language)
            Reload();

        if (!m_Pack)
            return NULL;

        if (field == "MedicalTreatmentMessages") return m_Pack.MedicalTreatmentMessages;
        if (field == "BloodDiscoveryMessages") return m_Pack.BloodDiscoveryMessages;
        if (field == "FireAndShelterMessages") return m_Pack.FireAndShelterMessages;
        if (field == "WeaponStateMessages") return m_Pack.WeaponStateMessages;
        if (field == "AmmoStressMessages") return m_Pack.AmmoStressMessages;
        if (field == "VehicleMessages") return m_Pack.VehicleMessages;
        if (field == "BaseRaidMessages") return m_Pack.BaseRaidMessages;
        if (field == "HuntingFishingMessages") return m_Pack.HuntingFishingMessages;
        if (field == "CraftingMessages") return m_Pack.CraftingMessages;
        if (field == "HandsHygieneMessages") return m_Pack.HandsHygieneMessages;
        if (field == "GasMaskFilterMessages") return m_Pack.GasMaskFilterMessages;
        if (field == "BetrayalTrustMessages") return m_Pack.BetrayalTrustMessages;
        return NULL;
    }
}
