
// Survivor Thoughts - Admin Priority / Trigger Coverage / Message Health system.
// v0.3.7 foundation: safe runtime admin tools, priority overrides, diagnostics, and editor queue.

class ST_MessagePriorityProfileRecord
{
    string ThoughtType;
    int Priority;
    float CooldownSeconds;
    int Enabled;

    void ST_MessagePriorityProfileRecord()
    {
        ThoughtType = "";
        Priority = -1;
        CooldownSeconds = 0.0;
        Enabled = 1;
    }
}

class ST_TriggerCoverageRecord
{
    string TriggerType;
    string MessageField;
    int TriggerConnected;
    int MinRecommendedMessages;
    string Notes;

    void ST_TriggerCoverageRecord()
    {
        TriggerType = "";
        MessageField = "";
        TriggerConnected = 0;
        MinRecommendedMessages = 5;
        Notes = "";
    }
}

class ST_AdminQueuedMessageEdit
{
    string Action;
    string TargetConfigFile;
    string MessageField;
    string MessageText;
    string AdminSteamId;
    string AdminName;
    int CreatedTime;

    void ST_AdminQueuedMessageEdit()
    {
        Action = "";
        TargetConfigFile = "";
        MessageField = "";
        MessageText = "";
        AdminSteamId = "";
        AdminName = "";
        CreatedTime = 0;
    }
}

class ST_AdminMessageEditQueue
{
    ref array<ref ST_AdminQueuedMessageEdit> PendingEdits;

    void ST_AdminMessageEditQueue()
    {
        PendingEdits = new array<ref ST_AdminQueuedMessageEdit>;
    }
}

class ST_AdminPriorityTriggerConfig
{
    int EnableInGameAdminMenu;
    string AdminMenuOpenActionText;
    string AdminMenuOpenCommand;
    int AllowAdminMenuForServerHost;
    ref array<string> AdminSteamIds;

    int EnablePriorityProfiles;
    int EnableTriggerCoverageReport;
    int EnableMessageHealthChecker;
    int EnableTriggerTester;
    int EnableAdminConfigBackups;
    int EnableAdminMessageEditorQueue;
    int EnableMissingTriggerDiagnostics;
    string Language;
    string LocalizedMessagesRoot;

    string AdminReportsFolder;
    string AdminConfigBackupFolder;
    string AdminPendingMessageEditsFile;

    ref array<ref ST_MessagePriorityProfileRecord> PriorityProfiles;
    ref array<ref ST_TriggerCoverageRecord> TriggerCoverage;

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

    void ST_AdminPriorityTriggerConfig()
    {
        PriorityProfiles = new array<ref ST_MessagePriorityProfileRecord>;
        TriggerCoverage = new array<ref ST_TriggerCoverageRecord>;

        AdminSteamIds = new array<string>;
        MedicalTreatmentMessages = new array<string>;
        BloodDiscoveryMessages = new array<string>;
        FireAndShelterMessages = new array<string>;
        WeaponStateMessages = new array<string>;
        AmmoStressMessages = new array<string>;
        VehicleMessages = new array<string>;
        BaseRaidMessages = new array<string>;
        HuntingFishingMessages = new array<string>;
        CraftingMessages = new array<string>;
        HandsHygieneMessages = new array<string>;
        GasMaskFilterMessages = new array<string>;
        BetrayalTrustMessages = new array<string>;

        SetDefaults();
    }

    void SetDefaults()
    {
        EnableInGameAdminMenu = 1;
        AdminMenuOpenActionText = "Open Survivor Thoughts Admin";
        AdminMenuOpenCommand = "/stadmin";
        AllowAdminMenuForServerHost = 1;

        EnablePriorityProfiles = 1;
        EnableTriggerCoverageReport = 1;
        EnableMessageHealthChecker = 1;
        EnableTriggerTester = 1;
        EnableAdminConfigBackups = 1;
        EnableAdminMessageEditorQueue = 1;
        EnableMissingTriggerDiagnostics = 1;
        Language = "en";
        LocalizedMessagesRoot = "$profile:ZombicideMods/SurvivorThoughts";

        AdminReportsFolder = "$profile:ZombicideMods/SurvivorThoughts/AdminReports";
        AdminConfigBackupFolder = "$profile:ZombicideMods/SurvivorThoughts/Configs/_Backups";
        AdminPendingMessageEditsFile = "$profile:ZombicideMods/SurvivorThoughts/Configs/_PendingMessageEdits.json";

        ST_AddPriority("Passive", 10, 0.0);
        ST_AddPriority("Weather", 15, 0.0);
        ST_AddPriority("TimeOfDay", 15, 0.0);
        ST_AddPriority("Location", 20, 0.0);
        ST_AddPriority("ItemCondition", 25, 0.0);
        ST_AddPriority("Action", 30, 0.0);
        ST_AddPriority("Corpse", 35, 0.0);
        ST_AddPriority("Social", 40, 0.0);
        ST_AddPriority("Memory", 45, 0.0);
        ST_AddPriority("Sanity", 50, 0.0);
        ST_AddPriority("Disease", 55, 0.0);
        ST_AddPriority("Recovery", 60, 0.0);
        ST_AddPriority("Bleeding", 70, 0.0);
        ST_AddPriority("Combat", 80, 0.0);
        ST_AddPriority("DeathSpiral", 90, 0.0);
        ST_AddPriority("JournalMajorEvent", 100, 0.0);

        ST_AddPriority("PASSIVE", 10, 0.0);
        ST_AddPriority("WEATHER", 15, 0.0);
        ST_AddPriority("TIME_OF_DAY", 15, 0.0);
        ST_AddPriority("LOCATION", 20, 0.0);
        ST_AddPriority("ITEM_CONDITION", 25, 0.0);
        ST_AddPriority("ACTION", 30, 0.0);
        ST_AddPriority("CORPSE", 35, 0.0);
        ST_AddPriority("SOCIAL_GROUP", 40, 0.0);
        ST_AddPriority("PLAYER_MEMORY", 45, 0.0);
        ST_AddPriority("SANITY", 50, 0.0);
        ST_AddPriority("DISEASE", 55, 0.0);
        ST_AddPriority("RECOVERY", 60, 0.0);
        ST_AddPriority("BLEEDING_STARTED", 70, 0.0);
        ST_AddPriority("BLEEDING_WORSE", 70, 0.0);
        ST_AddPriority("BLEEDING_STOPPED", 60, 0.0);
        ST_AddPriority("COMBAT_HIT", 80, 0.0);
        ST_AddPriority("ZOMBIE_HIT", 80, 0.0);
        ST_AddPriority("PLAYER_MELEE_HIT", 80, 0.0);
        ST_AddPriority("GUNSHOT_HIT", 85, 0.0);
        ST_AddPriority("EXPLOSION_HIT", 90, 0.0);
        ST_AddPriority("DEATH_SPIRAL", 90, 0.0);
        ST_AddPriority("JOURNAL_SYSTEM", 100, 0.0);

        ST_AddTrigger("BloodTypeDiscovered", "BloodDiscoveryMessages", 1, "Connected to vanilla blood-test actions.");
        ST_AddTrigger("MedicalTreatment", "MedicalTreatmentMessages", 1, "Generic medical action hooks can route here.");
        ST_AddTrigger("FireAndShelter", "FireAndShelterMessages", 1, "Fireplace/shelter action groups can route here.");
        ST_AddTrigger("WeaponState", "WeaponStateMessages", 1, "Unjam and weapon maintenance can route here.");
        ST_AddTrigger("AmmoStress", "AmmoStressMessages", 1, "Ammo management actions can route here.");
        ST_AddTrigger("Vehicle", "VehicleMessages", 1, "Vehicle action hooks already exist.");
        ST_AddTrigger("BaseRaid", "BaseRaidMessages", 0, "Raid-specific hooks need server rules/mod compatibility.");
        ST_AddTrigger("HuntingFishing", "HuntingFishingMessages", 1, "Fishing/skinning hooks can route here.");
        ST_AddTrigger("Crafting", "CraftingMessages", 1, "Crafting action hooks already exist.");
        ST_AddTrigger("HandsHygiene", "HandsHygieneMessages", 1, "Connected to vanilla wash-hands actions.");
        ST_AddTrigger("GasMaskFilter", "GasMaskFilterMessages", 1, "Connected to periodic gas-filter condition monitor.");
        ST_AddTrigger("BetrayalTrust", "BetrayalTrustMessages", 1, "Connected to persistent pairwise trust ledger and betrayal damage.");

        ST_FillMessageDefaults(MedicalTreatmentMessages, "MEDICAL");
        ST_FillMessageDefaults(BloodDiscoveryMessages, "BLOOD");
        ST_FillMessageDefaults(FireAndShelterMessages, "FIRE");
        ST_FillMessageDefaults(WeaponStateMessages, "WEAPON");
        ST_FillMessageDefaults(AmmoStressMessages, "AMMO");
        ST_FillMessageDefaults(VehicleMessages, "VEHICLE");
        ST_FillMessageDefaults(BaseRaidMessages, "BASE");
        ST_FillMessageDefaults(HuntingFishingMessages, "HUNT");
        ST_FillMessageDefaults(CraftingMessages, "CRAFT");
        ST_FillMessageDefaults(HandsHygieneMessages, "HANDS");
        ST_FillMessageDefaults(GasMaskFilterMessages, "GAS");
        ST_FillMessageDefaults(BetrayalTrustMessages, "TRUST");
    }

    void EnsureDefaults()
    {
        if (!PriorityProfiles)
            PriorityProfiles = new array<ref ST_MessagePriorityProfileRecord>;

        if (!TriggerCoverage)
            TriggerCoverage = new array<ref ST_TriggerCoverageRecord>;

        if (!AdminSteamIds)
            AdminSteamIds = new array<string>;

        if (!MedicalTreatmentMessages)
            MedicalTreatmentMessages = new array<string>;
        if (!BloodDiscoveryMessages)
            BloodDiscoveryMessages = new array<string>;
        if (!FireAndShelterMessages)
            FireAndShelterMessages = new array<string>;
        if (!WeaponStateMessages)
            WeaponStateMessages = new array<string>;
        if (!AmmoStressMessages)
            AmmoStressMessages = new array<string>;
        if (!VehicleMessages)
            VehicleMessages = new array<string>;
        if (!BaseRaidMessages)
            BaseRaidMessages = new array<string>;
        if (!HuntingFishingMessages)
            HuntingFishingMessages = new array<string>;
        if (!CraftingMessages)
            CraftingMessages = new array<string>;
        if (!HandsHygieneMessages)
            HandsHygieneMessages = new array<string>;
        if (!GasMaskFilterMessages)
            GasMaskFilterMessages = new array<string>;
        if (!BetrayalTrustMessages)
            BetrayalTrustMessages = new array<string>;

        if (Language == "")
            Language = "en";
        if (LocalizedMessagesRoot == "")
            LocalizedMessagesRoot = "$profile:ZombicideMods/SurvivorThoughts";

        if (AdminReportsFolder == "")
            AdminReportsFolder = "$profile:ZombicideMods/SurvivorThoughts/AdminReports";
        if (AdminConfigBackupFolder == "")
            AdminConfigBackupFolder = "$profile:ZombicideMods/SurvivorThoughts/Configs/_Backups";
        if (AdminPendingMessageEditsFile == "")
            AdminPendingMessageEditsFile = "$profile:ZombicideMods/SurvivorThoughts/Configs/_PendingMessageEdits.json";

        if (PriorityProfiles.Count() == 0)
            SetDefaults();

        ST_EnsureFive(MedicalTreatmentMessages, "MEDICAL");
        ST_EnsureFive(BloodDiscoveryMessages, "BLOOD");
        ST_EnsureFive(FireAndShelterMessages, "FIRE");
        ST_EnsureFive(WeaponStateMessages, "WEAPON");
        ST_EnsureFive(AmmoStressMessages, "AMMO");
        ST_EnsureFive(VehicleMessages, "VEHICLE");
        ST_EnsureFive(BaseRaidMessages, "BASE");
        ST_EnsureFive(HuntingFishingMessages, "HUNT");
        ST_EnsureFive(CraftingMessages, "CRAFT");
        ST_EnsureFive(HandsHygieneMessages, "HANDS");
        ST_EnsureFive(GasMaskFilterMessages, "GAS");
        ST_EnsureFive(BetrayalTrustMessages, "TRUST");
    }

    void ST_AddPriority(string thoughtType, int priority, float cooldown)
    {
        ST_MessagePriorityProfileRecord record = new ST_MessagePriorityProfileRecord();
        record.ThoughtType = thoughtType;
        record.Priority = priority;
        record.CooldownSeconds = cooldown;
        record.Enabled = 1;
        PriorityProfiles.Insert(record);
    }

    void ST_AddTrigger(string triggerType, string messageField, int connected, string notes)
    {
        ST_TriggerCoverageRecord record = new ST_TriggerCoverageRecord();
        record.TriggerType = triggerType;
        record.MessageField = messageField;
        record.TriggerConnected = connected;
        record.MinRecommendedMessages = 5;
        record.Notes = notes;
        TriggerCoverage.Insert(record);
    }

    void ST_EnsureFive(array<string> messages, string style)
    {
        if (!messages)
            return;

        while (messages.Count() < 5)
        {
            int index = messages.Count();
            messages.Insert(ST_DefaultMessage(style, index));
        }
    }

    void ST_FillMessageDefaults(array<string> messages, string style)
    {
        if (!messages)
            return;

        messages.Clear();

        for (int i = 0; i < 6; i++)
        {
            messages.Insert(ST_DefaultMessage(style, i));
        }
    }

    string ST_DefaultMessage(string style, int index)
    {
        if (style == "MEDICAL")
        {
            if (index == 0) return "Hold still. This might keep me alive.";
            if (index == 1) return "Clean hands, steady breath, then the wound.";
            if (index == 2) return "Pain means I am still here.";
            if (index == 3) return "Patch it now or pay for it later.";
            if (index == 4) return "Medicine only matters if I survive long enough.";
            return "One more treatment. One more chance.";
        }

        if (style == "BLOOD")
        {
            if (index == 0) return "So that is my blood. Useful, if I live.";
            if (index == 1) return "My blood has a name now.";
            if (index == 2) return "Good to know before I bleed out.";
            if (index == 3) return "That little test might save me one day.";
            if (index == 4) return "Information is another kind of supply.";
            return "Remember the type. Forgetting could kill me.";
        }

        if (style == "FIRE")
        {
            if (index == 0) return "Warmth makes the world feel less dead.";
            if (index == 1) return "Smoke can be seen, but cold kills quieter.";
            if (index == 2) return "A roof and a flame. Almost civilization.";
            if (index == 3) return "Stay close to the heat, but watch the dark.";
            if (index == 4) return "This place might hold for a few minutes.";
            return "The fire sounds too loud in the silence.";
        }

        if (style == "WEAPON")
        {
            if (index == 0) return "Check the weapon. It only matters if it works.";
            if (index == 1) return "A jam at the wrong time is a death sentence.";
            if (index == 2) return "Metal, oil, and luck.";
            if (index == 3) return "Keep it clean. Keep it close.";
            if (index == 4) return "The weapon feels heavier when I need it.";
            return "One bad click and everything changes.";
        }

        if (style == "AMMO")
        {
            if (index == 0) return "Count what is left. Then count it again.";
            if (index == 1) return "Every round has to matter now.";
            if (index == 2) return "Empty magazines make loud promises.";
            if (index == 3) return "Do not waste the last one.";
            if (index == 4) return "The quiet after the last shot is worse.";
            return "A handful of rounds is not safety.";
        }

        if (style == "VEHICLE")
        {
            if (index == 0) return "Engines draw attention. So does walking.";
            if (index == 1) return "If this thing dies out here, I walk.";
            if (index == 2) return "Wheels mean distance. Distance means time.";
            if (index == 3) return "The noise will carry.";
            if (index == 4) return "Check it twice before trusting it.";
            return "A running engine feels like hope and bait.";
        }

        if (style == "BASE")
        {
            if (index == 0) return "Walls only slow people down.";
            if (index == 1) return "Every lock is an invitation to someone.";
            if (index == 2) return "This place is safe until someone wants it.";
            if (index == 3) return "Wood, metal, and false confidence.";
            if (index == 4) return "Hide what matters. Reinforce what shows.";
            return "A base is just a promise to defend something.";
        }

        if (style == "HUNT")
        {
            if (index == 0) return "Food with blood still warm.";
            if (index == 1) return "Waste nothing. Not anymore.";
            if (index == 2) return "The land still gives, if I know where to look.";
            if (index == 3) return "Scales, hide, bone, meat. Survival has parts.";
            if (index == 4) return "The quiet work keeps me alive.";
            return "Another meal bought with patience.";
        }

        if (style == "CRAFT")
        {
            if (index == 0) return "Make do. That is the rule now.";
            if (index == 1) return "Broken things can still be useful.";
            if (index == 2) return "My hands remember more than I do.";
            if (index == 3) return "Small repairs keep death delayed.";
            if (index == 4) return "Nothing is junk until I cannot use it.";
            return "Improvised does not mean useless.";
        }

        if (style == "HANDS")
        {
            if (index == 0) return "My hands need cleaning before they kill me.";
            if (index == 1) return "Blood under the nails. Not all of it mine.";
            if (index == 2) return "Clean hands, cleaner food, better odds.";
            if (index == 3) return "I should wash this off before I forget.";
            if (index == 4) return "The smell stays longer than it should.";
            return "Dirt is one thing. Blood is another.";
        }

        if (style == "GAS")
        {
            if (index == 0) return "The filter will not last forever.";
            if (index == 1) return "Every breath has a timer.";
            if (index == 2) return "The mask makes me sound alone.";
            if (index == 3) return "If the seal fails, I am done.";
            if (index == 4) return "Do not trust clean air in a dead zone.";
            return "Breathe slow. Count the filter.";
        }

        if (style == "TRUST")
        {
            if (index == 0) return "Trust is heavier after it breaks.";
            if (index == 1) return "I remember what they did.";
            if (index == 2) return "A friendly voice can still hide a knife.";
            if (index == 3) return "Debt, mercy, betrayal. It all stays with me.";
            if (index == 4) return "Some faces are warnings now.";
            return "People are the hardest weather to read.";
        }

        return "Another thought pushes through the noise.";
    }
}

class ST_AdminPriorityTriggerSystem
{
    protected static ref ST_AdminPriorityTriggerSystem s_Instance;
    protected ref ST_AdminPriorityTriggerConfig m_Config;
    protected string m_ConfigPath;

    static ST_AdminPriorityTriggerSystem Get()
    {
        if (!s_Instance)
            s_Instance = new ST_AdminPriorityTriggerSystem();

        return s_Instance;
    }

    void LoadConfig()
    {
        if (!GetGame() || !GetGame().IsServer())
            return;

        string rootFolderPath = "$profile:ZombicideMods";
        string folderPath = rootFolderPath + "/SurvivorThoughts";
        string configsPath = folderPath + "/Configs";
        m_ConfigPath = configsPath + "/09_Admin_Priority_Trigger_System.json";

        if (!FileExist(rootFolderPath))
            MakeDirectory(rootFolderPath);
        if (!FileExist(folderPath))
            MakeDirectory(folderPath);
        if (!FileExist(configsPath))
            MakeDirectory(configsPath);

        m_Config = new ST_AdminPriorityTriggerConfig();

        if (FileExist(m_ConfigPath))
            JsonFileLoader<ST_AdminPriorityTriggerConfig>.JsonLoadFile(m_ConfigPath, m_Config);

        if (!m_Config)
            m_Config = new ST_AdminPriorityTriggerConfig();

        m_Config.EnsureDefaults();

        if (!FileExist(m_Config.AdminReportsFolder))
            MakeDirectory(m_Config.AdminReportsFolder);
        if (!FileExist(m_Config.AdminConfigBackupFolder))
            MakeDirectory(m_Config.AdminConfigBackupFolder);

        JsonFileLoader<ST_AdminPriorityTriggerConfig>.JsonSaveFile(m_ConfigPath, m_Config);
        ST_WriteBootDiagnostics();
    }

    ST_AdminPriorityTriggerConfig GetConfig()
    {
        if (!m_Config)
            LoadConfig();

        return m_Config;
    }

    bool IsEnabled()
    {
        ST_AdminPriorityTriggerConfig config = GetConfig();
        return config && config.EnableInGameAdminMenu == 1;
    }

    int GetPriorityOverride(string thoughtType, int fallback)
    {
        ST_AdminPriorityTriggerConfig config = GetConfig();

        if (!config || config.EnablePriorityProfiles != 1 || !config.PriorityProfiles)
            return fallback;

        string normalized = ST_NormalizePriorityType(thoughtType);

        foreach (ST_MessagePriorityProfileRecord record : config.PriorityProfiles)
        {
            if (!record)
                continue;

            if (record.Enabled != 1)
                continue;

            if (record.ThoughtType == thoughtType || record.ThoughtType == normalized)
                return record.Priority;
        }

        return fallback;
    }

    string ST_NormalizePriorityType(string thoughtType)
    {
        if (thoughtType == "COMBAT_HIT" || thoughtType == "ZOMBIE_HIT" || thoughtType == "PLAYER_MELEE_HIT" || thoughtType == "GUNSHOT_HIT" || thoughtType == "EXPLOSION_HIT" || thoughtType == "HEAVY_HIT")
            return "Combat";

        if (thoughtType == "BLEEDING_STARTED" || thoughtType == "BLEEDING_WORSE" || thoughtType == "BLEEDING_STOPPED")
            return "Bleeding";

        if (thoughtType == "DEATH_SPIRAL")
            return "DeathSpiral";

        if (thoughtType == "TIME_OF_DAY")
            return "TimeOfDay";

        if (thoughtType == "PLAYER_MEMORY")
            return "Memory";

        if (thoughtType == "SOCIAL_GROUP")
            return "Social";

        if (thoughtType == "JOURNAL_SYSTEM")
            return "JournalMajorEvent";

        if (thoughtType == "PASSIVE")
            return "Passive";

        return thoughtType;
    }

    bool IsAdminRPC(int rpc_type)
    {
        return rpc_type == ST_JournalRPC.ST_RPC_ADMIN_MENU_COMMAND;
    }

    bool IsAdminAllowed(PlayerBase player)
    {
        if (!player)
            return false;

        ST_AdminPriorityTriggerConfig localConfig = GetConfig();
        ST_SurvivorThoughtsConfig mainConfig = SurvivorThoughtsManager.Get().GetConfig();

        if (mainConfig && SurvivorThoughtsManager.Get().IsAdminAllowed(player))
            return true;

        if (!localConfig)
            return false;

        PlayerIdentity identity = player.GetIdentity();

        if (!identity)
            return false;

        string steamId = identity.GetPlainId();

        if (localConfig.AdminSteamIds)
        {
            foreach (string adminId : localConfig.AdminSteamIds)
            {
                if (adminId == steamId)
                    return true;
            }
        }

        return false;
    }

    void HandleAdminCommand(PlayerBase player, string command)
    {
        if (!GetGame() || !GetGame().IsServer())
            return;

        if (!IsAdminAllowed(player))
            return;

        if (command == "RELOAD")
        {
            SurvivorThoughtsManager.Get().ReloadConfigs(player);
            ST_SendAdminResponse(player, "Survivor Thoughts configs reloaded.");
            return;
        }

        if (command == "HEALTH")
        {
            ST_WriteMessageHealthReport();
            ST_SendAdminResponse(player, "Message health report written.");
            return;
        }

        if (command == "COVERAGE")
        {
            ST_WriteTriggerCoverageReport();
            ST_SendAdminResponse(player, "Trigger coverage report written.");
            return;
        }

        if (command == "TEST_COMBAT")
        {
            SurvivorThoughtsManager.Get().SendThoughtWithPriority(player, "Admin test: combat-priority thought route is working.", "COMBAT_HIT");
            return;
        }

        if (command == "TEST_PASSIVE")
        {
            SurvivorThoughtsManager.Get().SendThoughtWithPriority(player, "Admin test: passive thought route is working.", "PASSIVE");
            return;
        }

        if (command == "BACKUP")
        {
            ST_WriteConfigBackupMarker();
            ST_SendAdminResponse(player, "Config backup marker/report written. Use filesystem backup for full config copies.");
            return;
        }

        if (command == "QUEUE_SAMPLE_EDIT")
        {
            ST_QueueMessageEdit(player, "ADD", "09_Admin_Priority_Trigger_System.json", "HandsHygieneMessages", "Clean hands feel like one less thing trying to kill me.");
            ST_SendAdminResponse(player, "Sample pending message edit queued.");
            return;
        }

        if (command == "APPLY_PENDING")
        {
            string result = ST_ApplyPendingMessageEdits();
            ST_SendAdminResponse(player, result);
            return;
        }

        ST_SendAdminResponse(player, "Unknown Survivor Thoughts admin command.");
    }

    void ST_SendAdminResponse(PlayerBase player, string message)
    {
        if (!player || message == "")
            return;

        SurvivorThoughtsManager.Get().SendThoughtWithPriority(player, "[Admin] " + message, "JOURNAL_SYSTEM");
    }

    void ST_WriteBootDiagnostics()
    {
        ST_AdminPriorityTriggerConfig config = GetConfig();

        if (!config)
            return;

        if (config.EnableMessageHealthChecker == 1)
            ST_WriteMessageHealthReport();

        if (config.EnableTriggerCoverageReport == 1)
            ST_WriteTriggerCoverageReport();
    }

    void ST_WriteMessageHealthReport()
    {
        ST_AdminPriorityTriggerConfig config = GetConfig();

        if (!config)
            return;

        string filePath = config.AdminReportsFolder + "/MessageHealthReport.txt";
        FileHandle file = OpenFile(filePath, FileMode.WRITE);

        if (!file)
            return;

        FPrintln(file, "Survivor Thoughts - Message Health Report");
        FPrintln(file, "Generated at game time: " + GetGame().GetTime().ToString());
        FPrintln(file, "");
        FPrintln(file, "Recommended minimum messages per field: 5");
        FPrintln(file, "");

        ST_WriteArrayHealthLine(file, "MedicalTreatmentMessages", config.MedicalTreatmentMessages);
        ST_WriteArrayHealthLine(file, "BloodDiscoveryMessages", config.BloodDiscoveryMessages);
        ST_WriteArrayHealthLine(file, "FireAndShelterMessages", config.FireAndShelterMessages);
        ST_WriteArrayHealthLine(file, "WeaponStateMessages", config.WeaponStateMessages);
        ST_WriteArrayHealthLine(file, "AmmoStressMessages", config.AmmoStressMessages);
        ST_WriteArrayHealthLine(file, "VehicleMessages", config.VehicleMessages);
        ST_WriteArrayHealthLine(file, "BaseRaidMessages", config.BaseRaidMessages);
        ST_WriteArrayHealthLine(file, "HuntingFishingMessages", config.HuntingFishingMessages);
        ST_WriteArrayHealthLine(file, "CraftingMessages", config.CraftingMessages);
        ST_WriteArrayHealthLine(file, "HandsHygieneMessages", config.HandsHygieneMessages);
        ST_WriteArrayHealthLine(file, "GasMaskFilterMessages", config.GasMaskFilterMessages);
        ST_WriteArrayHealthLine(file, "BetrayalTrustMessages", config.BetrayalTrustMessages);

        FPrintln(file, "");
        FPrintln(file, "Note: consolidated config files are still the authoritative source for existing legacy message pools.");
        FPrintln(file, "This report covers the new v0.3.7 admin/trigger expansion pools.");

        CloseFile(file);
    }

    void ST_WriteArrayHealthLine(FileHandle file, string name, array<string> messages)
    {
        int count = 0;
        string state = "MISSING";

        if (messages)
        {
            count = messages.Count();

            if (count <= 0)
                state = "EMPTY";
            else if (count < 5)
                state = "UNDERFILLED";
            else
                state = "OK";
        }

        FPrintln(file, name + " = " + count.ToString() + " messages [" + state + "]");
    }

    void ST_WriteTriggerCoverageReport()
    {
        ST_AdminPriorityTriggerConfig config = GetConfig();

        if (!config)
            return;

        string filePath = config.AdminReportsFolder + "/TriggerCoverageReport.txt";
        FileHandle file = OpenFile(filePath, FileMode.WRITE);

        if (!file)
            return;

        FPrintln(file, "Survivor Thoughts - Trigger Coverage Report");
        FPrintln(file, "Generated at game time: " + GetGame().GetTime().ToString());
        FPrintln(file, "");

        if (config.TriggerCoverage)
        {
            foreach (ST_TriggerCoverageRecord record : config.TriggerCoverage)
            {
                if (!record)
                    continue;

                string connected = "NO";
                if (record.TriggerConnected == 1)
                    connected = "YES";

                FPrintln(file, record.TriggerType + " -> " + record.MessageField + " | Connected=" + connected + " | " + record.Notes);
            }
        }

        CloseFile(file);
    }

    void ST_WriteConfigBackupMarker()
    {
        ST_AdminPriorityTriggerConfig config = GetConfig();

        if (!config)
            return;

        string filePath = config.AdminConfigBackupFolder + "/BackupMarker.txt";
        FileHandle file = OpenFile(filePath, FileMode.APPEND);

        if (!file)
            return;

        FPrintln(file, "Backup requested at game time: " + GetGame().GetTime().ToString());
        FPrintln(file, "Use this folder for external backups of $profile:ZombicideMods/SurvivorThoughts/Configs.");
        CloseFile(file);
    }

    void ST_QueueMessageEdit(PlayerBase player, string action, string configFile, string field, string messageText)
    {
        ST_AdminPriorityTriggerConfig config = GetConfig();

        if (!config || config.EnableAdminMessageEditorQueue != 1)
            return;

        ST_AdminMessageEditQueue queue = new ST_AdminMessageEditQueue();

        if (FileExist(config.AdminPendingMessageEditsFile))
            JsonFileLoader<ST_AdminMessageEditQueue>.JsonLoadFile(config.AdminPendingMessageEditsFile, queue);

        if (!queue)
            queue = new ST_AdminMessageEditQueue();

        if (!queue.PendingEdits)
            queue.PendingEdits = new array<ref ST_AdminQueuedMessageEdit>;

        ST_AdminQueuedMessageEdit edit = new ST_AdminQueuedMessageEdit();
        edit.Action = action;
        edit.TargetConfigFile = configFile;
        edit.MessageField = field;
        edit.MessageText = messageText;

        if (player && player.GetIdentity())
        {
            edit.AdminSteamId = player.GetIdentity().GetPlainId();
            edit.AdminName = player.GetIdentity().GetName();
        }

        if (GetGame())
            edit.CreatedTime = GetGame().GetTime();

        queue.PendingEdits.Insert(edit);
        JsonFileLoader<ST_AdminMessageEditQueue>.JsonSaveFile(config.AdminPendingMessageEditsFile, queue);
    }

    string ST_ApplyPendingMessageEdits()
    {
        ST_AdminPriorityTriggerConfig config = GetConfig();
        if (!config || config.EnableAdminMessageEditorQueue != 1)
            return "Message edit queue is disabled.";

        if (!FileExist(config.AdminPendingMessageEditsFile))
            return "No pending message-edit file exists.";

        ST_AdminMessageEditQueue queue = new ST_AdminMessageEditQueue();
        JsonFileLoader<ST_AdminMessageEditQueue>.JsonLoadFile(config.AdminPendingMessageEditsFile, queue);

        if (!queue || !queue.PendingEdits || queue.PendingEdits.Count() == 0)
            return "No pending message edits.";

        string backupPath = config.AdminConfigBackupFolder + "/09_Admin_Priority_Trigger_System_PreApply.json";
        JsonFileLoader<ST_AdminPriorityTriggerConfig>.JsonSaveFile(backupPath, config);

        int applied = 0;
        int rejected = 0;

        foreach (ST_AdminQueuedMessageEdit edit : queue.PendingEdits)
        {
            if (!edit || edit.TargetConfigFile != "09_Admin_Priority_Trigger_System.json")
            {
                rejected++;
                continue;
            }

            array<string> target = ST_GetEditableMessageArray(config, edit.MessageField);
            if (!target || edit.MessageText == "" || edit.MessageText.Length() > 240)
            {
                rejected++;
                continue;
            }

            if (edit.Action == "ADD")
            {
                if (target.Find(edit.MessageText) == -1)
                    target.Insert(edit.MessageText);
                applied++;
                continue;
            }

            if (edit.Action == "REMOVE")
            {
                int index = target.Find(edit.MessageText);
                if (index >= 0)
                {
                    target.Remove(index);
                    applied++;
                }
                else
                    rejected++;
                continue;
            }

            rejected++;
        }

        config.EnsureDefaults();
        JsonFileLoader<ST_AdminPriorityTriggerConfig>.JsonSaveFile(m_ConfigPath, config);

        ST_AdminMessageEditQueue cleared = new ST_AdminMessageEditQueue();
        JsonFileLoader<ST_AdminMessageEditQueue>.JsonSaveFile(config.AdminPendingMessageEditsFile, cleared);

        ST_WriteMessageHealthReport();
        return "Pending edits applied: " + applied.ToString() + "; rejected: " + rejected.ToString() + ". Backup and health report written.";
    }

    protected array<string> ST_GetEditableMessageArray(ST_AdminPriorityTriggerConfig config, string field)
    {
        if (!config)
            return NULL;
        if (field == "MedicalTreatmentMessages") return config.MedicalTreatmentMessages;
        if (field == "BloodDiscoveryMessages") return config.BloodDiscoveryMessages;
        if (field == "FireAndShelterMessages") return config.FireAndShelterMessages;
        if (field == "WeaponStateMessages") return config.WeaponStateMessages;
        if (field == "AmmoStressMessages") return config.AmmoStressMessages;
        if (field == "VehicleMessages") return config.VehicleMessages;
        if (field == "BaseRaidMessages") return config.BaseRaidMessages;
        if (field == "HuntingFishingMessages") return config.HuntingFishingMessages;
        if (field == "CraftingMessages") return config.CraftingMessages;
        if (field == "HandsHygieneMessages") return config.HandsHygieneMessages;
        if (field == "GasMaskFilterMessages") return config.GasMaskFilterMessages;
        if (field == "BetrayalTrustMessages") return config.BetrayalTrustMessages;
        return NULL;
    }

    string GetDashboardText()
    {
        ST_AdminPriorityTriggerConfig config = GetConfig();

        if (!config)
            return "Survivor Thoughts admin config not loaded.";

        string text = "Survivor Thoughts Admin\n";
        text += "Priority profiles: ";
        if (config.EnablePriorityProfiles == 1) text += "ON\n"; else text += "OFF\n";

        text += "Health checker: ";
        if (config.EnableMessageHealthChecker == 1) text += "ON\n"; else text += "OFF\n";

        text += "Trigger coverage: ";
        if (config.EnableTriggerCoverageReport == 1) text += "ON\n"; else text += "OFF\n";

        text += "Editor queue: ";
        if (config.EnableAdminMessageEditorQueue == 1) text += "ON\n"; else text += "OFF\n";

        text += "Use buttons to reload, test, and write reports.";
        return text;
    }
}
