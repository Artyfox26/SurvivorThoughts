class SurvivorThoughtsManager
{
    protected static ref SurvivorThoughtsManager m_Instance;
    protected ref ST_SurvivorThoughtsConfig m_Config;
    protected ref ST_PlayerPersonalityStore m_PersonalityStore;
    protected ref ST_PlayerPersistentStateStore m_PersistentStateStore;
    protected bool m_ST_DebugLogInitialized;

    static SurvivorThoughtsManager Get()
    {
        if (!m_Instance)
        {
            m_Instance = new SurvivorThoughtsManager();
        }

        return m_Instance;
    }

    ST_SurvivorThoughtsConfig GetConfig()
    {
        if (!m_Config)
        {
            LoadConfig();
        }

        return m_Config;
    }

    void LoadConfig()
    {
        if (!GetGame() || !GetGame().IsServer())
            return;

        string rootFolderPath = "$profile:ZombicideMods";
        string folderPath = rootFolderPath + "/SurvivorThoughts";
        string modularFolderPath = folderPath + "/Configs";

        if (!FileExist(rootFolderPath))
            MakeDirectory(rootFolderPath);

        if (!FileExist(folderPath))
            MakeDirectory(folderPath);

        if (!FileExist(modularFolderPath))
            MakeDirectory(modularFolderPath);

        EnsureLogDirectory();

        m_Config = new ST_SurvivorThoughtsConfig();
        m_Config.SetDefaults();

        bool loadedAnyConfig = false;
        bool hasConsolidatedConfig = ST_HasAnyConsolidatedConfigFile(modularFolderPath);
        bool hasLegacyConfig = ST_HasAnyLegacyConfigFile(modularFolderPath);

        if (!hasConsolidatedConfig && hasLegacyConfig)
        {
            Log("Legacy split configs detected. Migrating custom settings/messages into consolidated layout.");

            loadedAnyConfig = ST_LoadLegacyConfigLayout(modularFolderPath);

            m_Config.EnsureDefaults();
            m_Config.ConfigVersion = 64;

            ST_SaveConsolidatedConfigLayout(modularFolderPath);
            ST_MoveLegacyConfigFilesToRedundant(modularFolderPath);

            Log("Legacy split configs migrated to consolidated layout. Old files moved to _Redundant.");
        }

        if (!ST_HasAnyConsolidatedConfigFile(modularFolderPath))
        {
            CreateMissingModularConfigFiles(modularFolderPath);
        }

        loadedAnyConfig = ST_LoadConsolidatedConfigLayout(modularFolderPath) || loadedAnyConfig;

        // Backward compatibility only: if a server restored legacy files after migration, read them as fallback.
        if (!loadedAnyConfig && ST_HasAnyLegacyConfigFile(modularFolderPath))
        {
            loadedAnyConfig = ST_LoadLegacyConfigLayout(modularFolderPath) || loadedAnyConfig;
        }

        m_Config.EnsureDefaults();
        m_Config.ConfigVersion = 64;
        ST_FillStarterMessageDefaults();
        ST_SaveConsolidatedConfigLayout(modularFolderPath);

        InitDebugLogFile();
        DebugLog("Config load completed. Consolidated config path: " + modularFolderPath);
        EnsurePersistentDataDirectory();
        LoadPersonalityStore();
        LoadPersistentStateStore();

        if (loadedAnyConfig)
            Log("Loaded SurvivorThoughts config from: " + modularFolderPath);
        else
            Log("Created default SurvivorThoughts consolidated configs: " + modularFolderPath);
    }

    bool LoadModularConfigFile(string filePath)
    {
        if (!FileExist(filePath))
            return false;

        JsonFileLoader<ST_SurvivorThoughtsConfig>.JsonLoadFile(filePath, m_Config);

        if (m_Config && m_Config.DebugMode == 1)
            Print("[SurvivorThoughts][DEBUG] Loaded modular config: " + filePath);

        return true;
    }

    bool ST_LoadConsolidatedConfigLayout(string modularFolderPath)
    {
        bool loaded = false;

        loaded = LoadModularConfigFile(modularFolderPath + "/00_Core_Admin_Output.json") || loaded;
        loaded = LoadModularConfigFile(modularFolderPath + "/01_Player_State_Personality.json") || loaded;
        loaded = LoadModularConfigFile(modularFolderPath + "/02_Messages_Survival.json") || loaded;
        loaded = LoadModularConfigFile(modularFolderPath + "/03_Actions_Damage_Combat.json") || loaded;
        loaded = LoadModularConfigFile(modularFolderPath + "/04_World_Environment.json") || loaded;
        loaded = LoadModularConfigFile(modularFolderPath + "/05_Items_Corpses.json") || loaded;
        loaded = LoadModularConfigFile(modularFolderPath + "/06_Social_Sanity_Journal.json") || loaded;
        loaded = LoadModularConfigFile(modularFolderPath + "/07_Admin_Diagnostics.json") || loaded;

        if (loaded)
            Log("Loaded consolidated config layout.");

        ST_SurvivorStorySystem.Get().LoadConfig();
        ST_AdminPriorityTriggerSystem.Get().LoadConfig();

        return loaded;
    }

    bool ST_LoadLegacyConfigLayout(string modularFolderPath)
    {
        bool loaded = false;

        loaded = LoadModularConfigFile(modularFolderPath + "/Core.json") || loaded;
        loaded = LoadModularConfigFile(modularFolderPath + "/Output.json") || loaded;
        loaded = LoadModularConfigFile(modularFolderPath + "/Stats.json") || loaded;
        loaded = LoadModularConfigFile(modularFolderPath + "/Messages_Passive.json") || loaded;
        loaded = LoadModularConfigFile(modularFolderPath + "/Messages_Actions.json") || loaded;
        loaded = LoadModularConfigFile(modularFolderPath + "/Messages_Damage.json") || loaded;
        loaded = LoadModularConfigFile(modularFolderPath + "/Messages_Combined.json") || loaded;
        loaded = LoadModularConfigFile(modularFolderPath + "/Messages_Advanced_Combined.json") || loaded;
        loaded = LoadModularConfigFile(modularFolderPath + "/Recovery_Messages.json") || loaded;
        loaded = LoadModularConfigFile(modularFolderPath + "/World_Weather.json") || loaded;
        loaded = LoadModularConfigFile(modularFolderPath + "/World_Time.json") || loaded;
        loaded = LoadModularConfigFile(modularFolderPath + "/World_Locations.json") || loaded;
        loaded = LoadModularConfigFile(modularFolderPath + "/Items.json") || loaded;
        loaded = LoadModularConfigFile(modularFolderPath + "/Corpses.json") || loaded;
        loaded = LoadModularConfigFile(modularFolderPath + "/Personality.json") || loaded;
        loaded = LoadModularConfigFile(modularFolderPath + "/Player_Memory.json") || loaded;
        loaded = LoadModularConfigFile(modularFolderPath + "/Stealth_Noise.json") || loaded;
        loaded = LoadModularConfigFile(modularFolderPath + "/Shelter.json") || loaded;
        loaded = LoadModularConfigFile(modularFolderPath + "/Message_Blocker.json") || loaded;
        loaded = LoadModularConfigFile(modularFolderPath + "/Mental_State.json") || loaded;
        loaded = LoadModularConfigFile(modularFolderPath + "/Custom_Thought_Zones.json") || loaded;
        loaded = LoadModularConfigFile(modularFolderPath + "/Thought_Priority.json") || loaded;
        loaded = LoadModularConfigFile(modularFolderPath + "/Social_Group.json") || loaded;
        loaded = LoadModularConfigFile(modularFolderPath + "/Sanity_Cannibalism.json") || loaded;
        loaded = LoadModularConfigFile(modularFolderPath + "/Persistent_Storage.json") || loaded;
        loaded = LoadModularConfigFile(modularFolderPath + "/Player_State_History.json") || loaded;
        loaded = LoadModularConfigFile(modularFolderPath + "/Thought_Decision_Trace.json") || loaded;
        loaded = LoadModularConfigFile(modularFolderPath + "/NearMiss_Combat.json") || loaded;
        loaded = LoadModularConfigFile(modularFolderPath + "/Disease_Specific.json") || loaded;
        loaded = LoadModularConfigFile(modularFolderPath + "/Admin_Analytics.json") || loaded;
        loaded = LoadModularConfigFile(modularFolderPath + "/Player_Journals.json") || loaded;
        loaded = LoadModularConfigFile(modularFolderPath + "/Map_Environment_Packs.json") || loaded;
        loaded = LoadModularConfigFile(modularFolderPath + "/Journal_Backstories.json") || loaded;
        loaded = LoadModularConfigFile(modularFolderPath + "/Admin.json") || loaded;
        loaded = LoadModularConfigFile(modularFolderPath + "/Items_Combat_Corpses.json") || loaded;

        return loaded;
    }

    void ST_SaveConsolidatedConfigLayout(string modularFolderPath)
    {
        if (!FileExist(modularFolderPath))
            MakeDirectory(modularFolderPath);

        ST_WriteConsolidatedConfig_00_Core_Admin_Output(modularFolderPath);
        ST_WriteConsolidatedConfig_01_Player_State_Personality(modularFolderPath);
        ST_WriteConsolidatedConfig_02_Messages_Survival(modularFolderPath);
        ST_WriteConsolidatedConfig_03_Actions_Damage_Combat(modularFolderPath);
        ST_WriteConsolidatedConfig_04_World_Environment(modularFolderPath);
        ST_WriteConsolidatedConfig_05_Items_Corpses(modularFolderPath);
        ST_WriteConsolidatedConfig_06_Social_Sanity_Journal(modularFolderPath);
        ST_WriteConsolidatedConfig_07_Admin_Diagnostics(modularFolderPath);
    }


    void ST_FillStarterMessageDefaults()
    {
        if (!m_Config)
            return;

        ST_FillStarterMessageDefaults_A();
        ST_FillStarterMessageDefaults_B();
        ST_FillStarterMessageDefaults_C();
        ST_FillStarterMessageDefaults_D();
        DebugLog("Starter message defaults checked. Empty/short message arrays are filled to at least 5 entries.");
    }

    void ST_EnsureStarterMessages(array<string> messages)
    {
        if (!messages)
            return;

        int safety = 0;
        while (messages.Count() < 5 && safety < 8)
        {
            messages.Insert(ST_GetStarterMessageDefault(messages.Count()));
            safety++;
        }
    }

    string ST_GetStarterMessageDefault(int index)
    {
        int selected = index % 8;

        switch (selected)
        {
            case 0:
                return "I need to pay attention to this.";
            case 1:
                return "This is another warning I cannot ignore.";
            case 2:
                return "Keep moving. Think later.";
            case 3:
                return "The world keeps finding new ways to test me.";
            case 4:
                return "I should remember this if I live long enough.";
            case 5:
                return "Every little sign matters out here.";
            case 6:
                return "Survival leaves marks even when nothing breaks.";
        }

        return "I need to stay sharp.";
    }

    void ST_FillStarterMessageDefaults_A()
    {
        if (!m_Config.AlmostDiedRecoveryMessages)
            m_Config.AlmostDiedRecoveryMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.AlmostDiedRecoveryMessages);

        if (!m_Config.AmmoManagementMessages)
            m_Config.AmmoManagementMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.AmmoManagementMessages);

        if (!m_Config.BandageSuccessMessages)
            m_Config.BandageSuccessMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.BandageSuccessMessages);

        if (!m_Config.BandagingMessages)
            m_Config.BandagingMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.BandagingMessages);

        if (!m_Config.BaseBuildingActionMessages)
            m_Config.BaseBuildingActionMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.BaseBuildingActionMessages);

        if (!m_Config.BleedingColdInfectedMessages)
            m_Config.BleedingColdInfectedMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.BleedingColdInfectedMessages);

        if (!m_Config.BleedingColdMessages)
            m_Config.BleedingColdMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.BleedingColdMessages);

        if (!m_Config.BleedingInfectedMessages)
            m_Config.BleedingInfectedMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.BleedingInfectedMessages);

        if (!m_Config.BleedingLowBloodMessages)
            m_Config.BleedingLowBloodMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.BleedingLowBloodMessages);

        if (!m_Config.BleedingLowBloodShockMessages)
            m_Config.BleedingLowBloodShockMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.BleedingLowBloodShockMessages);

        if (!m_Config.BleedingRecoveryMessages)
            m_Config.BleedingRecoveryMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.BleedingRecoveryMessages);

        if (!m_Config.BleedingShockMessages)
            m_Config.BleedingShockMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.BleedingShockMessages);

        if (!m_Config.BleedingSickInfectedMessages)
            m_Config.BleedingSickInfectedMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.BleedingSickInfectedMessages);

        if (!m_Config.BleedingStartedMessages)
            m_Config.BleedingStartedMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.BleedingStartedMessages);

        if (!m_Config.BleedingStoppedMessages)
            m_Config.BleedingStoppedMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.BleedingStoppedMessages);

        if (!m_Config.BleedingWorseMessages)
            m_Config.BleedingWorseMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.BleedingWorseMessages);

        if (!m_Config.Bleeding_Critical_Messages)
            m_Config.Bleeding_Critical_Messages = new array<string>;
        ST_EnsureStarterMessages(m_Config.Bleeding_Critical_Messages);

        if (!m_Config.Bleeding_Multiple_Messages)
            m_Config.Bleeding_Multiple_Messages = new array<string>;
        ST_EnsureStarterMessages(m_Config.Bleeding_Multiple_Messages);

        if (!m_Config.Bleeding_One_Messages)
            m_Config.Bleeding_One_Messages = new array<string>;
        ST_EnsureStarterMessages(m_Config.Bleeding_One_Messages);

        if (!m_Config.BloodMedicalMessages)
            m_Config.BloodMedicalMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.BloodMedicalMessages);

        if (!m_Config.BloodStabilizingMessages)
            m_Config.BloodStabilizingMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.BloodStabilizingMessages);

        if (!m_Config.BloodStage1Messages)
            m_Config.BloodStage1Messages = new array<string>;
        ST_EnsureStarterMessages(m_Config.BloodStage1Messages);

        if (!m_Config.BloodStage2Messages)
            m_Config.BloodStage2Messages = new array<string>;
        ST_EnsureStarterMessages(m_Config.BloodStage2Messages);

        if (!m_Config.BloodStage3Messages)
            m_Config.BloodStage3Messages = new array<string>;
        ST_EnsureStarterMessages(m_Config.BloodStage3Messages);

        if (!m_Config.BloodStage4Messages)
            m_Config.BloodStage4Messages = new array<string>;
        ST_EnsureStarterMessages(m_Config.BloodStage4Messages);

        if (!m_Config.BrokenLegBleedingInfectedMessages)
            m_Config.BrokenLegBleedingInfectedMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.BrokenLegBleedingInfectedMessages);

        if (!m_Config.BrokenLegBleedingMessages)
            m_Config.BrokenLegBleedingMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.BrokenLegBleedingMessages);

        if (!m_Config.BrokenLegColdInfectedMessages)
            m_Config.BrokenLegColdInfectedMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.BrokenLegColdInfectedMessages);

        if (!m_Config.BrokenLegColdMessages)
            m_Config.BrokenLegColdMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.BrokenLegColdMessages);

        if (!m_Config.BrokenLegHotMessages)
            m_Config.BrokenLegHotMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.BrokenLegHotMessages);

        if (!m_Config.BrokenLegHungerMessages)
            m_Config.BrokenLegHungerMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.BrokenLegHungerMessages);

        if (!m_Config.BrokenLegHungerThirstMessages)
            m_Config.BrokenLegHungerThirstMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.BrokenLegHungerThirstMessages);

        if (!m_Config.BrokenLegInfectedMessages)
            m_Config.BrokenLegInfectedMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.BrokenLegInfectedMessages);

        if (!m_Config.BrokenLegMessages)
            m_Config.BrokenLegMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.BrokenLegMessages);

        if (!m_Config.BrokenLegNightMessages)
            m_Config.BrokenLegNightMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.BrokenLegNightMessages);

        if (!m_Config.BrokenLegSickMessages)
            m_Config.BrokenLegSickMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.BrokenLegSickMessages);

        if (!m_Config.BrokenLegThirstMessages)
            m_Config.BrokenLegThirstMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.BrokenLegThirstMessages);

        if (!m_Config.BuryStashMessages)
            m_Config.BuryStashMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.BuryStashMessages);

        if (!m_Config.CannibalismCreepMessages)
            m_Config.CannibalismCreepMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.CannibalismCreepMessages);

        if (!m_Config.ColdInfectedMessages)
            m_Config.ColdInfectedMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.ColdInfectedMessages);

        if (!m_Config.ColdWetMessages)
            m_Config.ColdWetMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.ColdWetMessages);

        if (!m_Config.ColdWetNightMessages)
            m_Config.ColdWetNightMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.ColdWetNightMessages);

        if (!m_Config.ColdWetSickMessages)
            m_Config.ColdWetSickMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.ColdWetSickMessages);

        if (!m_Config.Cold_Critical_Messages)
            m_Config.Cold_Critical_Messages = new array<string>;
        ST_EnsureStarterMessages(m_Config.Cold_Critical_Messages);

        if (!m_Config.Cold_Mild_Messages)
            m_Config.Cold_Mild_Messages = new array<string>;
        ST_EnsureStarterMessages(m_Config.Cold_Mild_Messages);

        if (!m_Config.Cold_Moderate_Messages)
            m_Config.Cold_Moderate_Messages = new array<string>;
        ST_EnsureStarterMessages(m_Config.Cold_Moderate_Messages);

        if (!m_Config.Cold_Severe_Messages)
            m_Config.Cold_Severe_Messages = new array<string>;
        ST_EnsureStarterMessages(m_Config.Cold_Severe_Messages);

        if (!m_Config.CombatHitMessages)
            m_Config.CombatHitMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.CombatHitMessages);

        if (!m_Config.CompanionDeadLowSanityMessages)
            m_Config.CompanionDeadLowSanityMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.CompanionDeadLowSanityMessages);

        if (!m_Config.CompanionDeadNightMessages)
            m_Config.CompanionDeadNightMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.CompanionDeadNightMessages);

        if (!m_Config.CookingMessages)
            m_Config.CookingMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.CookingMessages);

        if (!m_Config.CooledDownMessages)
            m_Config.CooledDownMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.CooledDownMessages);

        if (!m_Config.CorpseLowSanityNightMessages)
            m_Config.CorpseLowSanityNightMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.CorpseLowSanityNightMessages);

        if (!m_Config.CraftingActionMessages)
            m_Config.CraftingActionMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.CraftingActionMessages);

        if (!m_Config.CriticalSurvivalMessages)
            m_Config.CriticalSurvivalMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.CriticalSurvivalMessages);

        if (!m_Config.DawnSurvivalMessages)
            m_Config.DawnSurvivalMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.DawnSurvivalMessages);

        if (!m_Config.DehydratedLowBloodMessages)
            m_Config.DehydratedLowBloodMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.DehydratedLowBloodMessages);

        if (!m_Config.DehydratingToDeathMessages)
            m_Config.DehydratingToDeathMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.DehydratingToDeathMessages);

        if (!m_Config.DeployActionMessages)
            m_Config.DeployActionMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.DeployActionMessages);

        if (!m_Config.DiseaseChemicalMessages)
            m_Config.DiseaseChemicalMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.DiseaseChemicalMessages);

        if (!m_Config.DiseaseCholeraMessages)
            m_Config.DiseaseCholeraMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.DiseaseCholeraMessages);

        if (!m_Config.DiseaseFeverMessages)
            m_Config.DiseaseFeverMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.DiseaseFeverMessages);

        if (!m_Config.DiseaseFoodPoisoningMessages)
            m_Config.DiseaseFoodPoisoningMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.DiseaseFoodPoisoningMessages);

        if (!m_Config.DiseaseGasExposureMessages)
            m_Config.DiseaseGasExposureMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.DiseaseGasExposureMessages);

        if (!m_Config.DiseaseInfluenzaMessages)
            m_Config.DiseaseInfluenzaMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.DiseaseInfluenzaMessages);

        if (!m_Config.DiseaseKuruMessages)
            m_Config.DiseaseKuruMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.DiseaseKuruMessages);

        if (!m_Config.DiseaseUnknownMessages)
            m_Config.DiseaseUnknownMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.DiseaseUnknownMessages);

        if (!m_Config.DiseaseWoundInfectionMessages)
            m_Config.DiseaseWoundInfectionMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.DiseaseWoundInfectionMessages);

        if (!m_Config.DisinfectActionMessages)
            m_Config.DisinfectActionMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.DisinfectActionMessages);

        if (!m_Config.DrinkingMessages)
            m_Config.DrinkingMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.DrinkingMessages);

    }

    void ST_FillStarterMessageDefaults_B()
    {
        if (!m_Config.DryingOffMessages)
            m_Config.DryingOffMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.DryingOffMessages);

        if (!m_Config.EatingMessages)
            m_Config.EatingMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.EatingMessages);

        if (!m_Config.ElectronicsActionMessages)
            m_Config.ElectronicsActionMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.ElectronicsActionMessages);

        if (!m_Config.EnergyStage1Messages)
            m_Config.EnergyStage1Messages = new array<string>;
        ST_EnsureStarterMessages(m_Config.EnergyStage1Messages);

        if (!m_Config.EnergyStage2Messages)
            m_Config.EnergyStage2Messages = new array<string>;
        ST_EnsureStarterMessages(m_Config.EnergyStage2Messages);

        if (!m_Config.EnergyStage3Messages)
            m_Config.EnergyStage3Messages = new array<string>;
        ST_EnsureStarterMessages(m_Config.EnergyStage3Messages);

        if (!m_Config.EnergyStage4Messages)
            m_Config.EnergyStage4Messages = new array<string>;
        ST_EnsureStarterMessages(m_Config.EnergyStage4Messages);

        if (!m_Config.EscapedInfectedMessages)
            m_Config.EscapedInfectedMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.EscapedInfectedMessages);

        if (!m_Config.ExplosionHitMessages)
            m_Config.ExplosionHitMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.ExplosionHitMessages);

        if (!m_Config.ExplosionShockMessages)
            m_Config.ExplosionShockMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.ExplosionShockMessages);

        if (!m_Config.ExtremeSurvivalMessages)
            m_Config.ExtremeSurvivalMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.ExtremeSurvivalMessages);

        if (!m_Config.FireStartingMessages)
            m_Config.FireStartingMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.FireStartingMessages);

        if (!m_Config.FireplaceActionMessages)
            m_Config.FireplaceActionMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.FireplaceActionMessages);

        if (!m_Config.FishingMessages)
            m_Config.FishingMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.FishingMessages);

        if (!m_Config.FoodRecoveryMessages)
            m_Config.FoodRecoveryMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.FoodRecoveryMessages);

        if (!m_Config.FreezingToDeathMessages)
            m_Config.FreezingToDeathMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.FreezingToDeathMessages);

        if (!m_Config.FriendlyNearbyMessages)
            m_Config.FriendlyNearbyMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.FriendlyNearbyMessages);

        if (!m_Config.GardeningActionMessages)
            m_Config.GardeningActionMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.GardeningActionMessages);

        if (!m_Config.GeneralActionMessages)
            m_Config.GeneralActionMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.GeneralActionMessages);

        if (!m_Config.GunshotBleedingLowBloodMessages)
            m_Config.GunshotBleedingLowBloodMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.GunshotBleedingLowBloodMessages);

        if (!m_Config.GunshotBleedingMessages)
            m_Config.GunshotBleedingMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.GunshotBleedingMessages);

        if (!m_Config.GunshotHitMessages)
            m_Config.GunshotHitMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.GunshotHitMessages);

        if (!m_Config.HealthStableRecoveryMessages)
            m_Config.HealthStableRecoveryMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.HealthStableRecoveryMessages);

        if (!m_Config.HeavyHitMessages)
            m_Config.HeavyHitMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.HeavyHitMessages);

        if (!m_Config.HotBleedingMessages)
            m_Config.HotBleedingMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.HotBleedingMessages);

        if (!m_Config.HotDehydratedMessages)
            m_Config.HotDehydratedMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.HotDehydratedMessages);

        if (!m_Config.HotDehydratedSickMessages)
            m_Config.HotDehydratedSickMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.HotDehydratedSickMessages);

        if (!m_Config.HotInfectedMessages)
            m_Config.HotInfectedMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.HotInfectedMessages);

        if (!m_Config.HotSickMessages)
            m_Config.HotSickMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.HotSickMessages);

        if (!m_Config.HotThirstMessages)
            m_Config.HotThirstMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.HotThirstMessages);

        if (!m_Config.Hot_Critical_Messages)
            m_Config.Hot_Critical_Messages = new array<string>;
        ST_EnsureStarterMessages(m_Config.Hot_Critical_Messages);

        if (!m_Config.Hot_Mild_Messages)
            m_Config.Hot_Mild_Messages = new array<string>;
        ST_EnsureStarterMessages(m_Config.Hot_Mild_Messages);

        if (!m_Config.Hot_Moderate_Messages)
            m_Config.Hot_Moderate_Messages = new array<string>;
        ST_EnsureStarterMessages(m_Config.Hot_Moderate_Messages);

        if (!m_Config.Hot_Severe_Messages)
            m_Config.Hot_Severe_Messages = new array<string>;
        ST_EnsureStarterMessages(m_Config.Hot_Severe_Messages);

        if (!m_Config.HungerBleedingMessages)
            m_Config.HungerBleedingMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.HungerBleedingMessages);

        if (!m_Config.HungerColdInfectedMessages)
            m_Config.HungerColdInfectedMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.HungerColdInfectedMessages);

        if (!m_Config.HungerColdMessages)
            m_Config.HungerColdMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.HungerColdMessages);

        if (!m_Config.HungerHotMessages)
            m_Config.HungerHotMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.HungerHotMessages);

        if (!m_Config.HungerInfectedMessages)
            m_Config.HungerInfectedMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.HungerInfectedMessages);

        if (!m_Config.HungerSickMessages)
            m_Config.HungerSickMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.HungerSickMessages);

        if (!m_Config.HungerThirstColdMessages)
            m_Config.HungerThirstColdMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.HungerThirstColdMessages);

        if (!m_Config.HungerThirstHotMessages)
            m_Config.HungerThirstHotMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.HungerThirstHotMessages);

        if (!m_Config.HungerThirstInfectedMessages)
            m_Config.HungerThirstInfectedMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.HungerThirstInfectedMessages);

        if (!m_Config.HungerThirstMessages)
            m_Config.HungerThirstMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.HungerThirstMessages);

        if (!m_Config.Infected_Close_Messages)
            m_Config.Infected_Close_Messages = new array<string>;
        ST_EnsureStarterMessages(m_Config.Infected_Close_Messages);

        if (!m_Config.Infected_Far_Messages)
            m_Config.Infected_Far_Messages = new array<string>;
        ST_EnsureStarterMessages(m_Config.Infected_Far_Messages);

        if (!m_Config.Infected_Surrounded_Messages)
            m_Config.Infected_Surrounded_Messages = new array<string>;
        ST_EnsureStarterMessages(m_Config.Infected_Surrounded_Messages);

        if (!m_Config.Infected_VeryClose_Messages)
            m_Config.Infected_VeryClose_Messages = new array<string>;
        ST_EnsureStarterMessages(m_Config.Infected_VeryClose_Messages);

        if (!m_Config.InjectionMessages)
            m_Config.InjectionMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.InjectionMessages);

        if (!m_Config.InventoryActionMessages)
            m_Config.InventoryActionMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.InventoryActionMessages);

        if (!m_Config.ItemBackpackDamagedMessages)
            m_Config.ItemBackpackDamagedMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.ItemBackpackDamagedMessages);

        if (!m_Config.ItemBadlyDamagedMessages)
            m_Config.ItemBadlyDamagedMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.ItemBadlyDamagedMessages);

        if (!m_Config.ItemBeltDamagedMessages)
            m_Config.ItemBeltDamagedMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.ItemBeltDamagedMessages);

        if (!m_Config.ItemClothingDamagedMessages)
            m_Config.ItemClothingDamagedMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.ItemClothingDamagedMessages);

        if (!m_Config.ItemGlovesDamagedMessages)
            m_Config.ItemGlovesDamagedMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.ItemGlovesDamagedMessages);

        if (!m_Config.ItemHeadgearDamagedMessages)
            m_Config.ItemHeadgearDamagedMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.ItemHeadgearDamagedMessages);

        if (!m_Config.ItemMaskDamagedMessages)
            m_Config.ItemMaskDamagedMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.ItemMaskDamagedMessages);

        if (!m_Config.ItemShoesDamagedMessages)
            m_Config.ItemShoesDamagedMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.ItemShoesDamagedMessages);

        if (!m_Config.ItemVestDamagedMessages)
            m_Config.ItemVestDamagedMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.ItemVestDamagedMessages);

        if (!m_Config.ItemWeaponDamagedMessages)
            m_Config.ItemWeaponDamagedMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.ItemWeaponDamagedMessages);

        if (!m_Config.LeftContaminatedZoneMessages)
            m_Config.LeftContaminatedZoneMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.LeftContaminatedZoneMessages);

        if (!m_Config.LiquidTransferMessages)
            m_Config.LiquidTransferMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.LiquidTransferMessages);

        if (!m_Config.LocationCityMessages)
            m_Config.LocationCityMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.LocationCityMessages);

        if (!m_Config.LocationCoastMessages)
            m_Config.LocationCoastMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.LocationCoastMessages);

        if (!m_Config.LocationFarmMessages)
            m_Config.LocationFarmMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.LocationFarmMessages);

        if (!m_Config.LocationForestMessages)
            m_Config.LocationForestMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.LocationForestMessages);

        if (!m_Config.LocationIndustrialMessages)
            m_Config.LocationIndustrialMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.LocationIndustrialMessages);

        if (!m_Config.LocationMedicalMessages)
            m_Config.LocationMedicalMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.LocationMedicalMessages);

        if (!m_Config.LocationMilitaryMessages)
            m_Config.LocationMilitaryMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.LocationMilitaryMessages);

        if (!m_Config.LocationPoliceMessages)
            m_Config.LocationPoliceMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.LocationPoliceMessages);

    }

    void ST_FillStarterMessageDefaults_C()
    {
        if (!m_Config.LocationTownMessages)
            m_Config.LocationTownMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.LocationTownMessages);

        if (!m_Config.LocationWaterMessages)
            m_Config.LocationWaterMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.LocationWaterMessages);

        if (!m_Config.LocationWildernessMessages)
            m_Config.LocationWildernessMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.LocationWildernessMessages);

        if (!m_Config.LockActionMessages)
            m_Config.LockActionMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.LockActionMessages);

        if (!m_Config.LoneWolfLowSanityNightMessages)
            m_Config.LoneWolfLowSanityNightMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.LoneWolfLowSanityNightMessages);

        if (!m_Config.LoneWolfMessages)
            m_Config.LoneWolfMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.LoneWolfMessages);

        if (!m_Config.LoneWolfNightMessages)
            m_Config.LoneWolfNightMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.LoneWolfNightMessages);

        if (!m_Config.LongBleedingMessages)
            m_Config.LongBleedingMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.LongBleedingMessages);

        if (!m_Config.LongSicknessMessages)
            m_Config.LongSicknessMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.LongSicknessMessages);

        if (!m_Config.LowBloodCorpseMessages)
            m_Config.LowBloodCorpseMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.LowBloodCorpseMessages);

        if (!m_Config.LowSanityCannibalismMessages)
            m_Config.LowSanityCannibalismMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.LowSanityCannibalismMessages);

        if (!m_Config.LowSanityCorpseMessages)
            m_Config.LowSanityCorpseMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.LowSanityCorpseMessages);

        if (!m_Config.LowSanityNightMessages)
            m_Config.LowSanityNightMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.LowSanityNightMessages);

        if (!m_Config.MapChernarusMessages)
            m_Config.MapChernarusMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.MapChernarusMessages);

        if (!m_Config.MapDeerIsleMessages)
            m_Config.MapDeerIsleMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.MapDeerIsleMessages);

        if (!m_Config.MapGenericMessages)
            m_Config.MapGenericMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.MapGenericMessages);

        if (!m_Config.MapLivoniaMessages)
            m_Config.MapLivoniaMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.MapLivoniaMessages);

        if (!m_Config.MapNamalskMessages)
            m_Config.MapNamalskMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.MapNamalskMessages);

        if (!m_Config.MapSakhalMessages)
            m_Config.MapSakhalMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.MapSakhalMessages);

        if (!m_Config.MedicineConsumeMessages)
            m_Config.MedicineConsumeMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.MedicineConsumeMessages);

        if (!m_Config.MentalStateAfraidMessages)
            m_Config.MentalStateAfraidMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.MentalStateAfraidMessages);

        if (!m_Config.MentalStateAggressiveMessages)
            m_Config.MentalStateAggressiveMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.MentalStateAggressiveMessages);

        if (!m_Config.MentalStateBrokenMessages)
            m_Config.MentalStateBrokenMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.MentalStateBrokenMessages);

        if (!m_Config.MentalStateDesperateMessages)
            m_Config.MentalStateDesperateMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.MentalStateDesperateMessages);

        if (!m_Config.MentalStateFocusedMessages)
            m_Config.MentalStateFocusedMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.MentalStateFocusedMessages);

        if (!m_Config.MentalStateNumbMessages)
            m_Config.MentalStateNumbMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.MentalStateNumbMessages);

        if (!m_Config.MentalStateStableMessages)
            m_Config.MentalStateStableMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.MentalStateStableMessages);

        if (!m_Config.MentalStateUneasyMessages)
            m_Config.MentalStateUneasyMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.MentalStateUneasyMessages);

        if (!m_Config.MilitaryCorpseMessages)
            m_Config.MilitaryCorpseMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.MilitaryCorpseMessages);

        if (!m_Config.MilitaryGunshotMessages)
            m_Config.MilitaryGunshotMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.MilitaryGunshotMessages);

        if (!m_Config.MilitaryNightStormMessages)
            m_Config.MilitaryNightStormMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.MilitaryNightStormMessages);

        if (!m_Config.MovementActionMessages)
            m_Config.MovementActionMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.MovementActionMessages);

        if (!m_Config.NavigationActionMessages)
            m_Config.NavigationActionMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.NavigationActionMessages);

        if (!m_Config.NearMissBulletMessages)
            m_Config.NearMissBulletMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.NearMissBulletMessages);

        if (!m_Config.NearMissCombatGeneralMessages)
            m_Config.NearMissCombatGeneralMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.NearMissCombatGeneralMessages);

        if (!m_Config.NearMissExplosionMessages)
            m_Config.NearMissExplosionMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.NearMissExplosionMessages);

        if (!m_Config.NearbyAnimalCorpseMessages)
            m_Config.NearbyAnimalCorpseMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.NearbyAnimalCorpseMessages);

        if (!m_Config.NearbyCorpseMessages)
            m_Config.NearbyCorpseMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.NearbyCorpseMessages);

        if (!m_Config.NearbyInfectedCorpseMessages)
            m_Config.NearbyInfectedCorpseMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.NearbyInfectedCorpseMessages);

        if (!m_Config.NearbyPlayerCorpseMessages)
            m_Config.NearbyPlayerCorpseMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.NearbyPlayerCorpseMessages);

        if (!m_Config.NightFogMessages)
            m_Config.NightFogMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.NightFogMessages);

        if (!m_Config.NightInfectedRainMessages)
            m_Config.NightInfectedRainMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.NightInfectedRainMessages);

        if (!m_Config.NightRainMessages)
            m_Config.NightRainMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.NightRainMessages);

        if (!m_Config.OpenCloseActionMessages)
            m_Config.OpenCloseActionMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.OpenCloseActionMessages);

        if (!m_Config.OverheatingToDeathMessages)
            m_Config.OverheatingToDeathMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.OverheatingToDeathMessages);

        if (!m_Config.PersonalCareMessages)
            m_Config.PersonalCareMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.PersonalCareMessages);

        if (!m_Config.PersonalityAggressiveMessages)
            m_Config.PersonalityAggressiveMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.PersonalityAggressiveMessages);

        if (!m_Config.PersonalityCalmMessages)
            m_Config.PersonalityCalmMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.PersonalityCalmMessages);

        if (!m_Config.PersonalityHopelessMessages)
            m_Config.PersonalityHopelessMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.PersonalityHopelessMessages);

        if (!m_Config.PersonalityMilitaryMessages)
            m_Config.PersonalityMilitaryMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.PersonalityMilitaryMessages);

        if (!m_Config.PersonalityPracticalMessages)
            m_Config.PersonalityPracticalMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.PersonalityPracticalMessages);

        if (!m_Config.PersonalityScaredMessages)
            m_Config.PersonalityScaredMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.PersonalityScaredMessages);

        if (!m_Config.PlayerMeleeHitMessages)
            m_Config.PlayerMeleeHitMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.PlayerMeleeHitMessages);

        if (!m_Config.PlayerMemoryRecentBleedingMessages)
            m_Config.PlayerMemoryRecentBleedingMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.PlayerMemoryRecentBleedingMessages);

        if (!m_Config.PlayerMemoryRecentCorpseMessages)
            m_Config.PlayerMemoryRecentCorpseMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.PlayerMemoryRecentCorpseMessages);

        if (!m_Config.PlayerMemoryRecentDamageMessages)
            m_Config.PlayerMemoryRecentDamageMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.PlayerMemoryRecentDamageMessages);

        if (!m_Config.PlayerMemoryRecentGunshotMessages)
            m_Config.PlayerMemoryRecentGunshotMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.PlayerMemoryRecentGunshotMessages);

        if (!m_Config.PlayerMemoryRecentMilitaryMessages)
            m_Config.PlayerMemoryRecentMilitaryMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.PlayerMemoryRecentMilitaryMessages);

        if (!m_Config.PlayerMemoryRecentSurvivalCrisisMessages)
            m_Config.PlayerMemoryRecentSurvivalCrisisMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.PlayerMemoryRecentSurvivalCrisisMessages);

        if (!m_Config.PostCombatBreathMessages)
            m_Config.PostCombatBreathMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.PostCombatBreathMessages);

        if (!m_Config.ProlongedBleedingMessages)
            m_Config.ProlongedBleedingMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.ProlongedBleedingMessages);

        if (!m_Config.ProlongedColdMessages)
            m_Config.ProlongedColdMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.ProlongedColdMessages);

        if (!m_Config.ProlongedDehydrationMessages)
            m_Config.ProlongedDehydrationMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.ProlongedDehydrationMessages);

        if (!m_Config.ProlongedHeatMessages)
            m_Config.ProlongedHeatMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.ProlongedHeatMessages);

        if (!m_Config.ProlongedSicknessMessages)
            m_Config.ProlongedSicknessMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.ProlongedSicknessMessages);

        if (!m_Config.ProlongedStarvationMessages)
            m_Config.ProlongedStarvationMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.ProlongedStarvationMessages);

        if (!m_Config.RepairMessages)
            m_Config.RepairMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.RepairMessages);

        if (!m_Config.ResourceGatheringMessages)
            m_Config.ResourceGatheringMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.ResourceGatheringMessages);

        if (!m_Config.RestrainActionMessages)
            m_Config.RestrainActionMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.RestrainActionMessages);

        if (!m_Config.SafeShelterRecoveryMessages)
            m_Config.SafeShelterRecoveryMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.SafeShelterRecoveryMessages);

    }

    void ST_FillStarterMessageDefaults_D()
    {
        if (!m_Config.SanityPsychoticMessages)
            m_Config.SanityPsychoticMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.SanityPsychoticMessages);

        if (!m_Config.SanityUneasyMessages)
            m_Config.SanityUneasyMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.SanityUneasyMessages);

        if (!m_Config.SanityUnhingedMessages)
            m_Config.SanityUnhingedMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.SanityUnhingedMessages);

        if (!m_Config.ShelterBadWeatherMessages)
            m_Config.ShelterBadWeatherMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.ShelterBadWeatherMessages);

        if (!m_Config.ShelterFromStormMessages)
            m_Config.ShelterFromStormMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.ShelterFromStormMessages);

        if (!m_Config.ShelterNightInfectedMessages)
            m_Config.ShelterNightInfectedMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.ShelterNightInfectedMessages);

        if (!m_Config.ShelterNightMessages)
            m_Config.ShelterNightMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.ShelterNightMessages);

        if (!m_Config.ShelterSafeMessages)
            m_Config.ShelterSafeMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.ShelterSafeMessages);

        if (!m_Config.ShelterUnsafeMessages)
            m_Config.ShelterUnsafeMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.ShelterUnsafeMessages);

        if (!m_Config.ShockRecoveryMessages)
            m_Config.ShockRecoveryMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.ShockRecoveryMessages);

        if (!m_Config.ShockStage1Messages)
            m_Config.ShockStage1Messages = new array<string>;
        ST_EnsureStarterMessages(m_Config.ShockStage1Messages);

        if (!m_Config.ShockStage2Messages)
            m_Config.ShockStage2Messages = new array<string>;
        ST_EnsureStarterMessages(m_Config.ShockStage2Messages);

        if (!m_Config.ShockStage3Messages)
            m_Config.ShockStage3Messages = new array<string>;
        ST_EnsureStarterMessages(m_Config.ShockStage3Messages);

        if (!m_Config.ShockStage4Messages)
            m_Config.ShockStage4Messages = new array<string>;
        ST_EnsureStarterMessages(m_Config.ShockStage4Messages);

        if (!m_Config.SickBleedingMessages)
            m_Config.SickBleedingMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.SickBleedingMessages);

        if (!m_Config.SickColdInfectedMessages)
            m_Config.SickColdInfectedMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.SickColdInfectedMessages);

        if (!m_Config.SickColdMessages)
            m_Config.SickColdMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.SickColdMessages);

        if (!m_Config.SickContaminatedMessages)
            m_Config.SickContaminatedMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.SickContaminatedMessages);

        if (!m_Config.SickInfectedMessages)
            m_Config.SickInfectedMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.SickInfectedMessages);

        if (!m_Config.SickThirstMessages)
            m_Config.SickThirstMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.SickThirstMessages);

        if (!m_Config.Sickness_Critical_Messages)
            m_Config.Sickness_Critical_Messages = new array<string>;
        ST_EnsureStarterMessages(m_Config.Sickness_Critical_Messages);

        if (!m_Config.Sickness_Early_Messages)
            m_Config.Sickness_Early_Messages = new array<string>;
        ST_EnsureStarterMessages(m_Config.Sickness_Early_Messages);

        if (!m_Config.Sickness_Moderate_Messages)
            m_Config.Sickness_Moderate_Messages = new array<string>;
        ST_EnsureStarterMessages(m_Config.Sickness_Moderate_Messages);

        if (!m_Config.Sickness_Severe_Messages)
            m_Config.Sickness_Severe_Messages = new array<string>;
        ST_EnsureStarterMessages(m_Config.Sickness_Severe_Messages);

        if (!m_Config.SkinningAnimalMessages)
            m_Config.SkinningAnimalMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.SkinningAnimalMessages);

        if (!m_Config.SkinningHumanMessages)
            m_Config.SkinningHumanMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.SkinningHumanMessages);

        if (!m_Config.StarvingDehydratedColdMessages)
            m_Config.StarvingDehydratedColdMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.StarvingDehydratedColdMessages);

        if (!m_Config.StarvingDehydratedMessages)
            m_Config.StarvingDehydratedMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.StarvingDehydratedMessages);

        if (!m_Config.StarvingLowBloodMessages)
            m_Config.StarvingLowBloodMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.StarvingLowBloodMessages);

        if (!m_Config.StarvingToDeathMessages)
            m_Config.StarvingToDeathMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.StarvingToDeathMessages);

        if (!m_Config.StealthNoiseInfectedNearbyMessages)
            m_Config.StealthNoiseInfectedNearbyMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.StealthNoiseInfectedNearbyMessages);

        if (!m_Config.StealthNoiseMilitaryMessages)
            m_Config.StealthNoiseMilitaryMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.StealthNoiseMilitaryMessages);

        if (!m_Config.StealthNoiseNightMessages)
            m_Config.StealthNoiseNightMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.StealthNoiseNightMessages);

        if (!m_Config.TeammateDownMessages)
            m_Config.TeammateDownMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.TeammateDownMessages);

        if (!m_Config.TeammateShotMessages)
            m_Config.TeammateShotMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.TeammateShotMessages);

        if (!m_Config.ThirstBleedingMessages)
            m_Config.ThirstBleedingMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.ThirstBleedingMessages);

        if (!m_Config.ThirstColdMessages)
            m_Config.ThirstColdMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.ThirstColdMessages);

        if (!m_Config.ThirstHotInfectedMessages)
            m_Config.ThirstHotInfectedMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.ThirstHotInfectedMessages);

        if (!m_Config.ThirstInfectedMessages)
            m_Config.ThirstInfectedMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.ThirstInfectedMessages);

        if (!m_Config.TrapExplosiveMessages)
            m_Config.TrapExplosiveMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.TrapExplosiveMessages);

        if (!m_Config.TrendBloodFallingMessages)
            m_Config.TrendBloodFallingMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.TrendBloodFallingMessages);

        if (!m_Config.TrendEnergyFallingMessages)
            m_Config.TrendEnergyFallingMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.TrendEnergyFallingMessages);

        if (!m_Config.TrendHealthFallingMessages)
            m_Config.TrendHealthFallingMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.TrendHealthFallingMessages);

        if (!m_Config.TrendTemperatureWorseningMessages)
            m_Config.TrendTemperatureWorseningMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.TrendTemperatureWorseningMessages);

        if (!m_Config.TrendWaterFallingMessages)
            m_Config.TrendWaterFallingMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.TrendWaterFallingMessages);

        if (!m_Config.TrendWetnessWorseningMessages)
            m_Config.TrendWetnessWorseningMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.TrendWetnessWorseningMessages);

        if (!m_Config.UnjamMessages)
            m_Config.UnjamMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.UnjamMessages);

        if (!m_Config.UnjamSuccessMessages)
            m_Config.UnjamSuccessMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.UnjamSuccessMessages);

        if (!m_Config.UnsafeDrinkingMessages)
            m_Config.UnsafeDrinkingMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.UnsafeDrinkingMessages);

        if (!m_Config.VehicleActionMessages)
            m_Config.VehicleActionMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.VehicleActionMessages);

        if (!m_Config.WarmedUpMessages)
            m_Config.WarmedUpMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.WarmedUpMessages);

        if (!m_Config.WaterRecoveryMessages)
            m_Config.WaterRecoveryMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.WaterRecoveryMessages);

        if (!m_Config.WaterStage1Messages)
            m_Config.WaterStage1Messages = new array<string>;
        ST_EnsureStarterMessages(m_Config.WaterStage1Messages);

        if (!m_Config.WaterStage2Messages)
            m_Config.WaterStage2Messages = new array<string>;
        ST_EnsureStarterMessages(m_Config.WaterStage2Messages);

        if (!m_Config.WaterStage3Messages)
            m_Config.WaterStage3Messages = new array<string>;
        ST_EnsureStarterMessages(m_Config.WaterStage3Messages);

        if (!m_Config.WaterStage4Messages)
            m_Config.WaterStage4Messages = new array<string>;
        ST_EnsureStarterMessages(m_Config.WaterStage4Messages);

        if (!m_Config.WeatherFogMessages)
            m_Config.WeatherFogMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.WeatherFogMessages);

        if (!m_Config.WeatherRainMessages)
            m_Config.WeatherRainMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.WeatherRainMessages);

        if (!m_Config.WeatherStormMessages)
            m_Config.WeatherStormMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.WeatherStormMessages);

        if (!m_Config.WeatherWindMessages)
            m_Config.WeatherWindMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.WeatherWindMessages);

        if (!m_Config.WorldInteractionMessages)
            m_Config.WorldInteractionMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.WorldInteractionMessages);

        if (!m_Config.WoundCareActionMessages)
            m_Config.WoundCareActionMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.WoundCareActionMessages);

        if (!m_Config.ZombieHitMessages)
            m_Config.ZombieHitMessages = new array<string>;
        ST_EnsureStarterMessages(m_Config.ZombieHitMessages);

    }

    void SaveConfig()
    {
        // Modular configs are loaded from $profile:ZombicideMods/SurvivorThoughts/Configs/.
        // This is intentionally a no-op so older internal calls do not recreate
        // the deprecated $profile:ZombicideMods/SurvivorThoughts/SurvivorThoughtsConfig.json file.
    }

    bool ReloadConfigs(PlayerBase requester = NULL)
    {
        LoadConfig();

        if (requester)
            SendThoughtWithPriority(requester, "Survivor Thoughts configs reloaded.", "ADMIN");

        Log("Configs reloaded by admin command.");
        return true;
    }


    string ST_GetPersistentStorageRoot()
    {
        ST_SurvivorThoughtsConfig config = m_Config;

        if (config && config.PersistentStorageRoot != "")
            return config.PersistentStorageRoot;

        return "$mission:storage_1/ZombiCideMods/SurvivorThoughts";
    }

    string ST_GetPersistentDataFolder()
    {
        ST_SurvivorThoughtsConfig config = m_Config;
        string folderName = "Data";

        if (config && config.PersistentDataFolderName != "")
            folderName = config.PersistentDataFolderName;

        return ST_GetPersistentStorageRoot() + "/" + folderName;
    }

    string ST_GetPersistentStateFilePath()
    {
        ST_SurvivorThoughtsConfig config = m_Config;

        if (config && config.PersistentStateDataFile != "")
            return config.PersistentStateDataFile;

        return ST_GetPersistentDataFolder() + "/PlayerPersistentStates.json";
    }

    void EnsurePersistentDataDirectory()
    {
        ST_SurvivorThoughtsConfig config = m_Config;

        if (config && config.EnableMissionStoragePersistentData != 1)
            return;

        if (!FileExist("$mission:storage_1"))
            MakeDirectory("$mission:storage_1");

        if (!FileExist("$mission:storage_1/ZombiCideMods"))
            MakeDirectory("$mission:storage_1/ZombiCideMods");

        string root = ST_GetPersistentStorageRoot();

        if (!FileExist(root))
            MakeDirectory(root);

        string dataFolder = ST_GetPersistentDataFolder();

        if (!FileExist(dataFolder))
            MakeDirectory(dataFolder);
    }

    void LoadPersistentStateStore()
    {
        ST_SurvivorThoughtsConfig config = m_Config;

        if (!config || config.EnableMissionStoragePersistentData != 1)
            return;

        EnsurePersistentDataDirectory();

        if (!m_PersistentStateStore)
            m_PersistentStateStore = new ST_PlayerPersistentStateStore();

        string filePath = ST_GetPersistentStateFilePath();

        if (FileExist(filePath))
        {
            JsonFileLoader<ST_PlayerPersistentStateStore>.JsonLoadFile(filePath, m_PersistentStateStore);
            DebugLog("Loaded persistent player state data from mission storage: " + filePath);
        }
        else
        {
            JsonFileLoader<ST_PlayerPersistentStateStore>.JsonSaveFile(filePath, m_PersistentStateStore);
            DebugLog("Created persistent player state data file: " + filePath);
        }
    }

    void SavePersistentStateStore()
    {
        ST_SurvivorThoughtsConfig config = GetConfig();

        if (!config || config.EnableMissionStoragePersistentData != 1)
            return;

        if (!m_PersistentStateStore)
            m_PersistentStateStore = new ST_PlayerPersistentStateStore();

        EnsurePersistentDataDirectory();

        JsonFileLoader<ST_PlayerPersistentStateStore>.JsonSaveFile(ST_GetPersistentStateFilePath(), m_PersistentStateStore);
    }

    string ST_GetPlayerSteamId(PlayerBase player)
    {
        if (!player)
            return "";

        PlayerIdentity identity = player.GetIdentity();

        if (!identity)
            return "";

        return identity.GetPlainId();
    }

    void ApplyPersistentDataToPlayer(PlayerBase player)
    {
        if (!player)
            return;

        ST_SurvivorThoughtsConfig config = GetConfig();

        if (!config || config.EnableMissionStoragePersistentData != 1)
            return;

        string steamId = ST_GetPlayerSteamId(player);

        if (steamId == "")
            return;

        if (!m_PersistentStateStore)
            LoadPersistentStateStore();

        if (!m_PersistentStateStore)
            m_PersistentStateStore = new ST_PlayerPersistentStateStore();

        ST_PlayerPersistentStateRecord record = m_PersistentStateStore.GetOrCreateRecord(steamId);
        player.ST_ApplyPersistentState(record, config);

        DebugLog("Applied persistent state to player " + steamId);
    }

    void SavePersistentDataForPlayer(PlayerBase player)
    {
        if (!player)
            return;

        ST_SurvivorThoughtsConfig config = GetConfig();

        if (!config || config.EnableMissionStoragePersistentData != 1)
            return;

        string steamId = ST_GetPlayerSteamId(player);

        if (steamId == "")
            return;

        if (!m_PersistentStateStore)
            LoadPersistentStateStore();

        if (!m_PersistentStateStore)
            m_PersistentStateStore = new ST_PlayerPersistentStateStore();

        ST_PlayerPersistentStateRecord record = m_PersistentStateStore.GetOrCreateRecord(steamId);
        player.ST_FillPersistentState(record, config);

        SavePersistentStateStore();
        DebugLog("Saved persistent state for player " + steamId);
    }

    void LoadPersonalityStore()
    {
        ST_SurvivorThoughtsConfig config = m_Config;

        if (!config)
            return;

        EnsurePersistentDataDirectory();

        if (!m_PersonalityStore)
            m_PersonalityStore = new ST_PlayerPersonalityStore();

        if (FileExist(config.PersonalityDataFile))
        {
            JsonFileLoader<ST_PlayerPersonalityStore>.JsonLoadFile(config.PersonalityDataFile, m_PersonalityStore);
            Log("Loaded persistent personality data.");
        }
        else
        {
            JsonFileLoader<ST_PlayerPersonalityStore>.JsonSaveFile(config.PersonalityDataFile, m_PersonalityStore);
            Log("Created persistent personality data file.");
        }
    }

    void SavePersonalityStore()
    {
        ST_SurvivorThoughtsConfig config = GetConfig();

        if (!config || !m_PersonalityStore)
            return;

        EnsurePersistentDataDirectory();

        JsonFileLoader<ST_PlayerPersonalityStore>.JsonSaveFile(config.PersonalityDataFile, m_PersonalityStore);
    }

    string GetOrCreatePersonalityForPlayer(PlayerBase player)
    {
        ST_SurvivorThoughtsConfig config = GetConfig();

        if (!config || config.EnablePersonalityProfiles != 1)
            return "Calm";

        if (!player)
            return GetRandomPersonality();

        PlayerIdentity identity = player.GetIdentity();
        if (!identity)
            return GetRandomPersonality();

        if (config.PersonalityPersistBySteamId != 1)
            return GetRandomPersonality();

        if (!m_PersonalityStore)
            LoadPersonalityStore();

        if (!m_PersonalityStore)
            m_PersonalityStore = new ST_PlayerPersonalityStore();

        string steamId = identity.GetPlainId();
        float now = 0.0;

        if (GetGame())
            now = GetGame().GetTime() / 1000.0;

        ST_PlayerPersonalityRecord record = m_PersonalityStore.GetRecord(steamId);

        if (record && record.Personality != "")
        {
            if (ShouldChangePersonality(config, record, now))
            {
                string changed = GetRandomPersonalityExcept(record.Personality);
                m_PersonalityStore.SetPersonalityWithTime(steamId, changed, now);
                SavePersonalityStore();
                Log("Changed persistent personality for " + steamId + " from '" + record.Personality + "' to '" + changed + "'");
                return changed;
            }

            return record.Personality;
        }

        string created = GetRandomPersonality();
        m_PersonalityStore.SetPersonalityWithTime(steamId, created, now);
        SavePersonalityStore();

        Log("Assigned persistent personality '" + created + "' to " + steamId);
        return created;
    }

    bool ShouldChangePersonality(ST_SurvivorThoughtsConfig config, ST_PlayerPersonalityRecord record, float now)
    {
        if (!config || !record)
            return false;

        if (config.EnablePersonalityChangeOverTime != 1)
            return false;

        if (config.PersonalityChangeChance <= 0.0)
            return false;

        if (record.LastPersonalityChangeTime > 0.0)
        {
            float elapsed = now - record.LastPersonalityChangeTime;

            if (elapsed >= 0.0 && elapsed < config.PersonalityMinimumSecondsBetweenChanges)
                return false;
        }

        return Math.RandomFloat01() <= config.PersonalityChangeChance;
    }

    string GetRandomPersonalityExcept(string currentPersonality)
    {
        string next = GetRandomPersonality();

        int safety = 0;
        while (next == currentPersonality && safety < 10)
        {
            next = GetRandomPersonality();
            safety++;
        }

        return next;
    }

    string GetRandomPersonality()
    {
        int roll = Math.RandomIntInclusive(1, 6);

        switch (roll)
        {
            case 1:
                return "Practical";
            case 2:
                return "Scared";
            case 3:
                return "Military";
            case 4:
                return "Hopeless";
            case 5:
                return "Aggressive";
        }

        return "Calm";
    }

    bool IsAdminAllowed(PlayerBase player)
    {
        ST_SurvivorThoughtsConfig config = GetConfig();

        if (!config || config.EnableAdminReload != 1)
            return false;

        if (!player)
            return false;

        PlayerIdentity identity = player.GetIdentity();
        if (!identity)
            return false;

        if (!config.AdminSteamIds || config.AdminSteamIds.Count() == 0)
            return false;

        string id = identity.GetPlainId();

        foreach (string adminId : config.AdminSteamIds)
        {
            if (adminId == id)
                return true;
        }

        return false;
    }

    bool IsEnabled()
    {
        ST_SurvivorThoughtsConfig config = GetConfig();

        if (!config)
            return false;

        return config.EnableMod == 1;
    }

    void SendThought(PlayerBase player, string message)
    {
        SendThoughtWithPriority(player, message, "PASSIVE");
    }

    void SendThoughtWithPriority(PlayerBase player, string message, string thoughtType)
    {
        if (!player || message == "")
            return;

        if (!GetGame())
            return;

        ST_SurvivorThoughtsConfig config = GetConfig();

        if (!config || config.EnableMod == 0)
            return;

        int priority = ST_GetThoughtPriority(thoughtType, config);

        if (ST_ShouldBlockByThoughtPriority(player, thoughtType, priority, config))
        {
            ST_WriteThoughtDecisionTrace(player, thoughtType, message, priority, "Blocked", "Priority");
            ST_RecordAnalyticsEvent("BlockedByPriority", thoughtType);
            ST_LinkThoughtToSurvivorJournal(player, thoughtType, message, "BlockedPriority");
            return;
        }

        if (ST_ShouldBlockRecentMessage(player, message, config))
        {
            ST_WriteThoughtDecisionTrace(player, thoughtType, message, priority, "Blocked", "RecentMessage");
            ST_RecordAnalyticsEvent("BlockedAsDuplicate", thoughtType);
            ST_LinkThoughtToSurvivorJournal(player, thoughtType, message, "BlockedDuplicate");
            return;
        }

        ST_WriteThoughtDecisionTrace(player, thoughtType, message, priority, "Allowed", "Passed");
        ST_RecordAnalyticsEvent("ThoughtSent", thoughtType);
        ST_WritePlayerJournalEntry(player, thoughtType, message);

        PlayerIdentity identity = player.GetIdentity();

        if (config.UseLocalChatBox == 1)
        {
            if (!identity)
                return;

            Param1<string> msgParam = new Param1<string>("[Thought] " + message);
            GetGame().RPCSingleParam(player, ERPCs.RPC_USER_ACTION_MESSAGE, msgParam, true, identity);
            return;
        }

        if (config.UseNotificationSystem == 1)
        {
            NotificationSystem.SendNotificationToPlayerExtended(player, 4.0, "Survivor Thoughts", message, "");
            return;
        }
    }


    bool ST_ShouldBlockRecentMessage(PlayerBase player, string message, ST_SurvivorThoughtsConfig config)
    {
        if (!player || !config)
            return false;

        if (config.EnableRecentMessageBlocker != 1)
            return false;

        if (message == "")
            return false;

        if (player.ST_ShouldBlockRecentThoughtMessage(message, config.RecentMessageMemoryCount, config.RecentMessageBlockSeconds))
        {
            DebugLog("Recent message blocked to prevent repetition. Message=" + message);
            return true;
        }

        return false;
    }


    int ST_GetThoughtPriority(string thoughtType, ST_SurvivorThoughtsConfig config)
    {
        if (!config)
            return 50;

        int adminPriorityOverride = ST_AdminPriorityTriggerSystem.Get().GetPriorityOverride(thoughtType, -1);
        if (adminPriorityOverride >= 0)
            return adminPriorityOverride;

        switch (thoughtType)
        {
            case "COMBAT_HIT":
            case "ZOMBIE_HIT":
            case "PLAYER_MELEE_HIT":
            case "GUNSHOT_HIT":
            case "EXPLOSION_HIT":
            case "HEAVY_HIT":
            case "IMMEDIATE":
                return config.PriorityImmediateDamage;

            case "BLEEDING_STARTED":
            case "BLEEDING_WORSE":
            case "BLEEDING_STOPPED":
                return config.PriorityBleeding;

            case "DEATH_SPIRAL":
                return config.PriorityDeathSpiral;

            case "CRITICAL_SURVIVAL":
                return config.PriorityCriticalSurvival;

            case "HIGH_SURVIVAL":
                return config.PriorityHighSurvival;

            case "MEDIUM_SURVIVAL":
            case "HUMAN_CONTEXT":
            case "PASSIVE":
                return config.PriorityMediumSurvival;

            case "LOW_SURVIVAL":
            case "PERSONALITY_AMBIENT":
                return config.PriorityLowSurvival;

            case "OPEN_CLOSE":
                return config.PriorityOpenCloseAction;

            case "OPEN_FOOD":
                return config.PriorityOpenCloseAction;

            case "EAT":
            case "DRINK":
            case "DRINK_UNSAFE":
            case "UNJAM":
            case "UNJAM_SUCCESS":
            case "SKIN_ANIMAL":
            case "SKIN_HUMAN":
            case "BANDAGE":
            case "WOUND_CARE":
            case "BANDAGE_SUCCESS":
            case "FIRE_START":
            case "COOK":
            case "FISH":
            case "REPAIR":
            case "GENERAL_ACTION":
            case "MEDICINE_CONSUME":
            case "INJECTION":
            case "BLOOD_MEDICAL":
            case "DISINFECT":
            case "RESTRAIN":
            case "CRAFTING":
            case "DEPLOY":
            case "GARDENING":
            case "RESOURCE_GATHER":
            case "LIQUID_TRANSFER":
            case "FIREPLACE":
            case "ELECTRONICS":
            case "NAVIGATION":
            case "LOCK":
            case "TRAP_EXPLOSIVE":
            case "BASE_BUILDING":
            case "VEHICLE":
            case "INVENTORY_MANAGEMENT":
            case "BURY_STASH":
            case "PERSONAL_CARE":
            case "AMMO_MANAGEMENT":
            case "MOVEMENT":
            case "WORLD_INTERACTION":
                return config.PriorityAction;

            case "COMBAT_STRESS":
                return config.PriorityCombatStress;

            case "WEATHER":
                return config.PriorityWeather;

            case "TIME_OF_DAY":
                return config.PriorityTimeOfDay;

            case "LOCATION":
                return config.PriorityLocation;

            case "STAT_STAGE_CRITICAL":
                return config.PriorityCriticalSurvival;

            case "STAT_MULTI_RED":
                return config.PriorityCriticalSurvival;

            case "STAT_STAGE_RED":
                return config.PriorityHighSurvival;

            case "STAT_STAGE_YELLOW":
                return config.PriorityMediumSurvival;

            case "ITEM_RUINED":
                return config.PriorityHighSurvival;

            case "ITEM_BADLY_DAMAGED":
                return config.PriorityMediumSurvival;

            case "ITEM_DAMAGED":
            case "ITEM_WORN":
            case "ITEM_CONDITION":
                return config.PriorityItemCondition;

            case "CORPSE":
                return config.PriorityCorpse;

            case "CONTAMINATED_ZONE":
                return config.PriorityContaminatedZone;

            case "PERSONALITY":
                return config.PriorityPersonality;

            case "PLAYER_MEMORY":
                return config.PriorityPlayerMemory;

            case "STEALTH_NOISE":
                return config.PriorityStealthNoise;

            case "SHELTER":
                return config.PriorityShelter;

            case "MENTAL_STATE":
                return config.PriorityMentalState;

            case "CUSTOM_THOUGHT_ZONE":
                return config.PriorityCustomThoughtZone;

            case "SOCIAL_GROUP":
                return config.PrioritySocialGroup;

            case "SANITY_CREEP":
                return config.PrioritySanityCreep;
            case "STATE_HISTORY":
            case "TREND":
                return config.PriorityStateHistory;

            case "RECOVERY":
                return config.PriorityRecovery;

            case "ADVANCED_COMBINED":
                return config.PriorityAdvancedCombined;

            case "NEAR_MISS":
                return config.PriorityNearMissCombat;

            case "DISEASE_SPECIFIC":
                return config.PriorityDiseaseSpecific;

            case "MAP_ENVIRONMENT":
                return config.PriorityMapEnvironment;


            case "JOURNAL_SYSTEM":
                return config.PriorityJournalSystem;

            case "ADMIN":
                return config.PriorityAdminSystem;
        }

        return config.PriorityMediumSurvival;
    }

    bool ST_ShouldBlockByThoughtPriority(PlayerBase player, string thoughtType, int priority, ST_SurvivorThoughtsConfig config)
    {
        if (!player)
            return true;

        if (!config || config.EnableThoughtPrioritySystem != 1)
            return false;

        if (!GetGame())
            return true;

        float now = GetGame().GetTime() / 1000.0;
        int lastPriority = player.ST_GetLastThoughtPriority();
        float lastTime = player.ST_GetLastThoughtPriorityTime();
        string lastType = player.ST_GetLastThoughtPriorityType();

        if (lastPriority > priority && (now - lastTime) < config.PriorityInterruptWindowSeconds)
        {
            DebugLog("Thought priority blocked. Type=" + thoughtType + " Priority=" + priority.ToString() + " LastType=" + lastType + " LastPriority=" + lastPriority.ToString());
            return true;
        }

        player.ST_SetLastThoughtPriority(priority, now, thoughtType);
        return false;
    }

    bool ST_IsForcedHitReactionType(string thoughtType)
    {
        switch (thoughtType)
        {
            case "COMBAT_HIT":
            case "ZOMBIE_HIT":
            case "PLAYER_MELEE_HIT":
            case "GUNSHOT_HIT":
            case "EXPLOSION_HIT":
            case "HEAVY_HIT":
                return true;
        }

        return false;
    }

    void SendImmediateThoughtWithPriority(PlayerBase player, string message, string thoughtType)
    {
        if (!player || message == "")
            return;

        if (!GetGame())
            return;

        ST_SurvivorThoughtsConfig config = GetConfig();

        if (!config || config.EnableMod == 0)
            return;

        int priority = ST_GetThoughtPriority(thoughtType, config);
        bool forcedHit = ST_IsForcedHitReactionType(thoughtType);

        if (!forcedHit && ST_ShouldBlockByThoughtPriority(player, thoughtType, priority, config))
        {
            ST_WriteThoughtDecisionTrace(player, thoughtType, message, priority, "Blocked", "Priority");
            ST_RecordAnalyticsEvent("BlockedByPriority", thoughtType);
            ST_LinkThoughtToSurvivorJournal(player, thoughtType, message, "BlockedPriority");
            return;
        }

        if (!forcedHit && ST_ShouldBlockRecentMessage(player, message, config))
        {
            ST_WriteThoughtDecisionTrace(player, thoughtType, message, priority, "Blocked", "RecentMessage");
            ST_RecordAnalyticsEvent("BlockedAsDuplicate", thoughtType);
            ST_LinkThoughtToSurvivorJournal(player, thoughtType, message, "BlockedDuplicate");
            return;
        }

        ST_WriteThoughtDecisionTrace(player, thoughtType, message, priority, "Allowed", "ImmediatePassed");
        ST_RecordAnalyticsEvent("ThoughtSent", thoughtType);
        ST_WritePlayerJournalEntry(player, thoughtType, message);

        string finalMessage = "[Thought] " + message;
        bool sent = false;

        if (config.UseLocalChatBox == 1)
        {
            PlayerIdentity identity = player.GetIdentity();

            if (identity)
            {
                Param1<string> msgParam = new Param1<string>(finalMessage);
                GetGame().RPCSingleParam(player, ERPCs.RPC_USER_ACTION_MESSAGE, msgParam, true, identity);
                sent = true;
            }
            else
            {
                player.MessageAction(finalMessage);
                sent = true;
            }
        }

        if (!sent && config.UseNotificationSystem == 1)
        {
            NotificationSystem.SendNotificationToPlayerExtended(player, 4.0, "Survivor Thoughts", message, "");
            sent = true;
        }

        if (!sent)
        {
            player.MessageAction(finalMessage);
            DebugLog("Immediate thought used MessageAction fallback because all output toggles were disabled.");
        }
    }


    
    /*
        Immediate reactions are used by real gameplay events such as:
        - infected hit
        - gunshot hit
        - melee hit
        - explosion hit
        - heavy hit
        - bleeding started/worsened/stopped

        They bypass passive/combat cooldowns and are sent directly at event time.
        For local chat output, this uses PlayerBase.MessageAction() server-side,
        the same underlying chat style vanilla uses for action messages.
    */
    void SendImmediateThought(PlayerBase player, string message)
    {
        SendImmediateThoughtWithPriority(player, message, "IMMEDIATE");
    }


    
    void ST_AddImmediateFallbackMessages(array<string> messages, string reactionType)
    {
        if (!messages)
            return;

        switch (reactionType)
        {
            case "COMBAT_HIT":
                messages.Insert("That hit me.");
                messages.Insert("I need to move.");
                messages.Insert("I need cover.");
                messages.Insert("Stay focused.");
                break;

            case "ZOMBIE_HIT":
                messages.Insert("An infected hit me.");
                messages.Insert("It got too close.");
                messages.Insert("I need to keep distance from them.");
                messages.Insert("That infected nearly tore into me.");
                break;

            case "PLAYER_MELEE_HIT":
                messages.Insert("Someone hit me.");
                messages.Insert("They are too close.");
                messages.Insert("I need space before they swing again.");
                messages.Insert("Move. Do not let them pin me down.");
                break;

            case "GUNSHOT_HIT":
                messages.Insert("I have been shot.");
                messages.Insert("That round hit me.");
                messages.Insert("I need cover now.");
                messages.Insert("Someone has eyes on me.");
                break;

            case "EXPLOSION_HIT":
                messages.Insert("The blast hit me hard.");
                messages.Insert("My ears are ringing.");
                messages.Insert("Everything is spinning.");
                messages.Insert("I need to get away from here.");
                break;

            case "HEAVY_HIT":
                messages.Insert("That hit hard.");
                messages.Insert("My body is screaming.");
                messages.Insert("I cannot take another hit like that.");
                messages.Insert("I need to get out of this fight.");
                break;

            case "BLEEDING_STARTED":
                messages.Insert("I am bleeding.");
                messages.Insert("That opened me up.");
                messages.Insert("Blood is running down my body.");
                messages.Insert("I need to bandage this now.");
                break;

            case "BLEEDING_WORSE":
                messages.Insert("I am bleeding from more than one wound.");
                messages.Insert("There is too much blood.");
                messages.Insert("I need to stop the bleeding before I pass out.");
                messages.Insert("This is getting bad fast.");
                break;

            case "BLEEDING_STOPPED":
                messages.Insert("The bleeding has stopped.");
                messages.Insert("That should hold for now.");
                messages.Insert("At least I am not bleeding anymore.");
                messages.Insert("That was too close.");
                break;
        }
    }

    void SendImmediateReactionThought(PlayerBase player, string reactionType)
    {
        if (!player)
        {
            DebugLog("Immediate reaction blocked: missing player. Type=" + reactionType);
            return;
        }

        ST_SurvivorThoughtsConfig config = GetConfig();

        if (!config)
        {
            DebugLog("Immediate reaction blocked: missing config. Type=" + reactionType);
            return;
        }

        if (config.EnableMod == 0)
        {
            DebugLog("Immediate reaction blocked: mod disabled. Type=" + reactionType);
            return;
        }

        array<string> messages;

        switch (reactionType)
        {
            case "COMBAT_HIT":
                messages = config.CombatHitMessages;
                break;

            case "ZOMBIE_HIT":
                messages = config.ZombieHitMessages;
                break;

            case "PLAYER_MELEE_HIT":
                messages = config.PlayerMeleeHitMessages;
                break;

            case "GUNSHOT_HIT":
                messages = config.GunshotHitMessages;
                break;

            case "EXPLOSION_HIT":
                messages = config.ExplosionHitMessages;
                break;

            case "HEAVY_HIT":
                messages = config.HeavyHitMessages;
                break;

            case "BLEEDING_STARTED":
                if (config.EnableBleedingReactionThoughts == 0 || config.EnableBleedingStartedMessages == 0)
                {
                    DebugLog("Immediate reaction blocked: bleeding started disabled. EnableBleedingReactionThoughts=" + config.EnableBleedingReactionThoughts.ToString() + " EnableBleedingStartedMessages=" + config.EnableBleedingStartedMessages.ToString());
                    return;
                }
                messages = config.BleedingStartedMessages;
                break;

            case "BLEEDING_WORSE":
                if (config.EnableBleedingReactionThoughts == 0 || config.EnableBleedingWorseMessages == 0)
                {
                    DebugLog("Immediate reaction blocked: bleeding worse disabled. EnableBleedingReactionThoughts=" + config.EnableBleedingReactionThoughts.ToString() + " EnableBleedingWorseMessages=" + config.EnableBleedingWorseMessages.ToString());
                    return;
                }
                messages = config.BleedingWorseMessages;
                break;

            case "BLEEDING_STOPPED":
                if (config.EnableBleedingReactionThoughts == 0 || config.EnableBleedingStoppedMessages == 0)
                {
                    DebugLog("Immediate reaction blocked: bleeding stopped disabled. EnableBleedingReactionThoughts=" + config.EnableBleedingReactionThoughts.ToString() + " EnableBleedingStoppedMessages=" + config.EnableBleedingStoppedMessages.ToString());
                    return;
                }
                messages = config.BleedingStoppedMessages;
                break;

            default:
                DebugLog("Immediate reaction blocked: unknown reaction type " + reactionType);
                return;
        }

        if (!messages)
            messages = new array<string>;

        if (messages.Count() == 0)
        {
            DebugLog("Immediate reaction message pool empty. Using hardcoded fallback. Type=" + reactionType);
            ST_AddImmediateFallbackMessages(messages, reactionType);
        }

        if (messages.Count() == 0)
        {
            DebugLog("Immediate reaction blocked: no messages available after fallback. Type=" + reactionType);
            return;
        }

        string selectedMessage = messages.GetRandomElement();
        DebugLog("Immediate reaction sending. Type=" + reactionType + " Message=" + selectedMessage);
        SendImmediateThoughtWithPriority(player, selectedMessage, reactionType);
    }

bool ST_IsImmediateCombatReactionType(string stressType)
    {
        switch (stressType)
        {
            case "ZOMBIE_HIT":
            case "PLAYER_MELEE_HIT":
            case "GUNSHOT_HIT":
            case "EXPLOSION_HIT":
            case "HEAVY_HIT":
            case "BLEEDING_STARTED":
            case "BLEEDING_WORSE":
            case "BLEEDING_STOPPED":
                return true;
        }

        return false;
    }

    void SendCombatStressThought(PlayerBase player, string stressType)
    {
        if (!player)
            return;

        ST_SurvivorThoughtsConfig config = GetConfig();

        if (!config || config.EnableMod == 0 || config.EnableCombatStressThoughts == 0)
            return;

        array<string> messages;
        bool immediateReaction = ST_IsImmediateCombatReactionType(stressType);

        switch (stressType)
        {
            case "COMBAT_HIT":
                if (config.EnableCombatStressDamageEventThoughts == 0) return;
                messages = config.CombatHitMessages;
                break;

            case "ZOMBIE_HIT":
                if (config.EnableCombatStressDamageEventThoughts == 0) return;
                messages = config.ZombieHitMessages;
                break;

            case "PLAYER_MELEE_HIT":
                if (config.EnableCombatStressDamageEventThoughts == 0) return;
                messages = config.PlayerMeleeHitMessages;
                break;

            case "GUNSHOT_HIT":
                if (config.EnableCombatStressDamageEventThoughts == 0) return;
                messages = config.GunshotHitMessages;
                break;

            case "EXPLOSION_HIT":
                if (config.EnableCombatStressDamageEventThoughts == 0) return;
                messages = config.ExplosionHitMessages;
                break;

            case "HEAVY_HIT":
                if (config.EnableCombatStressDamageEventThoughts == 0) return;
                messages = config.HeavyHitMessages;
                break;

            case "BLEEDING_STARTED":
                if (config.EnableBleedingReactionThoughts == 0 || config.EnableBleedingStartedMessages == 0) return;
                messages = config.BleedingStartedMessages;
                break;

            case "BLEEDING_WORSE":
                if (config.EnableBleedingReactionThoughts == 0 || config.EnableBleedingWorseMessages == 0) return;
                messages = config.BleedingWorseMessages;
                break;

            case "BLEEDING_STOPPED":
                if (config.EnableBleedingReactionThoughts == 0 || config.EnableBleedingStoppedMessages == 0) return;
                messages = config.BleedingStoppedMessages;
                break;

            case "SHOCK":
            case "COMBAT_SHOCK":
                if (config.EnableCombatStressShockThoughts == 0) return;
                messages = config.CombatShockMessages;
                break;

            default:
                if (config.EnableCombatStressShockThoughts == 0) return;
                messages = config.CombatStressMessages;
                break;
        }

        if (!messages || messages.Count() == 0)
            messages = config.CombatStressMessages;

        if (!messages || messages.Count() == 0)
            return;

        if (!GetGame())
            return;

        /*
            Damage/bleeding reaction types are event-driven and should be immediate.
            These bypass passive/combat cooldowns so a zombie hit, gunshot, new bleed,
            worsened bleed, and final bandage/bleed stop can each produce their own
            message when the event happens.
        */
        if (immediateReaction)
        {
            SendImmediateReactionThought(player, stressType);
            return;
        }

        float now = GetGame().GetTime() / 1000.0;
        float last = player.ST_GetLastCombatStressThoughtTime();

        if (config.CombatStressCooldownSeconds > 0.0 && (now - last) < config.CombatStressCooldownSeconds)
        {
            DebugLog("Combat/damage thought blocked by cooldown: " + stressType);
            return;
        }

        player.ST_SetLastCombatStressThoughtTime(now);
        DebugLog("Combat/damage thought sent: " + stressType);
        SendThoughtWithPriority(player, messages.GetRandomElement(), "COMBAT_STRESS");
    }

    
    bool ShouldBlockDuplicateImmediateAction(PlayerBase player, string actionType, ST_SurvivorThoughtsConfig config)
    {
        if (!player)
            return true;

        if (!GetGame())
            return true;

        float duplicateWindow = 0.75;

        if (config && config.DuplicateImmediateActionCooldownSeconds > 0.0)
            duplicateWindow = config.DuplicateImmediateActionCooldownSeconds;

        float now = GetGame().GetTime() / 1000.0;
        string lastType = player.ST_GetLastImmediateActionType();
        float lastTime = player.ST_GetLastImmediateActionTime();

        if (lastType == actionType && (now - lastTime) < duplicateWindow)
        {
            DebugLog("Duplicate immediate action blocked. Type=" + actionType + " Window=" + duplicateWindow.ToString());
            return true;
        }

        player.ST_SetLastImmediateAction(actionType, now);
        return false;
    }

void SendNamedActionThought(PlayerBase player, string actionType, string itemName)
    {
        if (!player)
            return;

        ST_SurvivorThoughtsConfig config = GetConfig();

        if (!config || config.EnableMod == 0 || config.EnableActionThoughts == 0)
            return;

        if (ShouldBlockDuplicateImmediateAction(player, actionType, config))
            return;

        if (itemName == "")
        {
            SendActionThought(player, actionType);
            return;
        }

        array<string> messages = new array<string>;

        if (actionType == "OPEN_FOOD")
        {
            if (config.EnableExtendedVanillaActionMessages == 0)
                return;

            messages.Insert("Let's see what is left in the " + itemName + ".");
            messages.Insert("I hope the " + itemName + " is still edible.");
            messages.Insert("The " + itemName + " might keep me going a little longer.");
            messages.Insert("Food is food. I cannot be picky about the " + itemName + ".");
            messages.Insert("Opening the " + itemName + " had better be worth it.");
        }
        else if (actionType == "EAT" || actionType == "EAT_HUMAN")
        {
            if (config.EnableEatingThoughts == 0)
                return;

            messages.Insert("The " + itemName + " should keep me going.");
            messages.Insert("I need the energy from this " + itemName + ".");
            messages.Insert("Time to eat the " + itemName + ".");
            messages.Insert("I cannot afford to waste the " + itemName + ".");
            messages.Insert("The " + itemName + " is better than going hungry.");
        }
        else if (actionType == "DRINK" || actionType == "DRINK_UNSAFE")
        {
            if (config.EnableDrinkingThoughts == 0)
                return;

            messages.Insert("I need a drink from the " + itemName + ".");
            messages.Insert("The " + itemName + " should help with this thirst.");
            messages.Insert("Time to drink from the " + itemName + ".");
            messages.Insert("I hope the " + itemName + " is safe enough.");
            messages.Insert("A drink from the " + itemName + " should keep me moving.");
        }
        else
        {
            SendActionThought(player, actionType);
            return;
        }

        DebugLog("Named action thought sent. Type=" + actionType + " Item=" + itemName);
        SendImmediateThoughtWithPriority(player, messages.GetRandomElement(), actionType);
    }

void SendActionThought(PlayerBase player, string actionType)
    {
        if (!player)
            return;

        ST_SurvivorThoughtsConfig config = GetConfig();

        if (!config || config.EnableMod == 0 || config.EnableActionThoughts == 0)
            return;

        if (ShouldBlockDuplicateImmediateAction(player, actionType, config))
            return;

        array<string> messages;

        switch (actionType)
        {
            case "EAT":
                if (config.EnableEatingThoughts == 0) return;
                messages = config.EatingMessages;
                break;

            case "EAT_HUMAN":
                if (config.EnableEatingThoughts == 0) return;
                if (config.CannibalismCreepMessages && config.CannibalismCreepMessages.Count() > 0)
                    messages = config.CannibalismCreepMessages;
                else
                    messages = config.EatingMessages;
                break;

            case "DRINK":
                if (config.EnableDrinkingThoughts == 0) return;
                messages = config.DrinkingMessages;
                break;

            case "DRINK_UNSAFE":
                if (config.EnableDrinkingThoughts == 0) return;
                messages = config.UnsafeDrinkingMessages;
                break;

            case "UNJAM":
                if (config.EnableUnjamThoughts == 0) return;
                messages = config.UnjamMessages;
                break;

            case "UNJAM_SUCCESS":
                if (config.EnableUnjamThoughts == 0) return;
                messages = config.UnjamSuccessMessages;
                break;

            case "SKIN_ANIMAL":
                if (config.EnableSkinningThoughts == 0) return;
                messages = config.SkinningAnimalMessages;
                break;

            case "SKIN_HUMAN":
                if (config.EnableSkinningThoughts == 0) return;
                messages = config.SkinningHumanMessages;
                break;

            case "BANDAGE":
            case "WOUND_CARE":
                if (config.EnableBandagingThoughts == 0) return;
                if (actionType == "WOUND_CARE" && config.WoundCareActionMessages && config.WoundCareActionMessages.Count() > 0)
                    messages = config.WoundCareActionMessages;
                else
                    messages = config.BandagingMessages;
                break;

            case "BANDAGE_SUCCESS":
                if (config.EnableBandagingThoughts == 0) return;
                messages = config.BandageSuccessMessages;
                break;

            case "FIRE_START":
                if (config.EnableFireStartingThoughts == 0) return;
                messages = config.FireStartingMessages;
                break;

            case "COOK":
                if (config.EnableCookingThoughts == 0) return;
                messages = config.CookingMessages;
                break;

            case "FISH":
                if (config.EnableFishingThoughts == 0) return;
                messages = config.FishingMessages;
                break;

            case "REPAIR":
                if (config.EnableRepairThoughts == 0) return;
                messages = config.RepairMessages;
                break;

            case "GENERAL_ACTION":
                if (config.EnableExtendedVanillaActionMessages == 0) return;
                messages = config.GeneralActionMessages;
                break;

            case "OPEN_CLOSE":
                if (config.EnableExtendedVanillaActionMessages == 0) return;
                messages = config.OpenCloseActionMessages;
                break;

            case "OPEN_FOOD":
                if (config.EnableExtendedVanillaActionMessages == 0) return;
                messages = new array<string>;
                messages.Insert("Let's see what is left in this.");
                messages.Insert("Please still be edible.");
                messages.Insert("Food is food. I cannot be picky.");
                messages.Insert("I hope opening this is worth it.");
                messages.Insert("This might keep me going a little longer.");
                break;

            case "MEDICINE_CONSUME":
                if (config.EnableExtendedVanillaActionMessages == 0) return;
                messages = config.MedicineConsumeMessages;
                break;

            case "INJECTION":
                if (config.EnableExtendedVanillaActionMessages == 0) return;
                messages = config.InjectionMessages;
                break;

            case "BLOOD_MEDICAL":
                if (config.EnableExtendedVanillaActionMessages == 0) return;
                messages = config.BloodMedicalMessages;
                break;

            case "DISINFECT":
                if (config.EnableExtendedVanillaActionMessages == 0) return;
                messages = config.DisinfectActionMessages;
                break;

            case "RESTRAIN":
                if (config.EnableExtendedVanillaActionMessages == 0) return;
                messages = config.RestrainActionMessages;
                break;

            case "CRAFTING":
                if (config.EnableExtendedVanillaActionMessages == 0) return;
                messages = config.CraftingActionMessages;
                break;

            case "DEPLOY":
                if (config.EnableExtendedVanillaActionMessages == 0) return;
                messages = config.DeployActionMessages;
                break;

            case "GARDENING":
                if (config.EnableExtendedVanillaActionMessages == 0) return;
                messages = config.GardeningActionMessages;
                break;

            case "RESOURCE_GATHER":
                if (config.EnableExtendedVanillaActionMessages == 0) return;
                messages = config.ResourceGatheringMessages;
                break;

            case "LIQUID_TRANSFER":
                if (config.EnableExtendedVanillaActionMessages == 0) return;
                messages = config.LiquidTransferMessages;
                break;

            case "FIREPLACE":
                if (config.EnableExtendedVanillaActionMessages == 0) return;
                messages = config.FireplaceActionMessages;
                break;

            case "ELECTRONICS":
                if (config.EnableExtendedVanillaActionMessages == 0) return;
                messages = config.ElectronicsActionMessages;
                break;

            case "NAVIGATION":
                if (config.EnableExtendedVanillaActionMessages == 0) return;
                messages = config.NavigationActionMessages;
                break;

            case "LOCK":
                if (config.EnableExtendedVanillaActionMessages == 0) return;
                messages = config.LockActionMessages;
                break;

            case "TRAP_EXPLOSIVE":
                if (config.EnableExtendedVanillaActionMessages == 0) return;
                messages = config.TrapExplosiveMessages;
                break;

            case "BASE_BUILDING":
                if (config.EnableExtendedVanillaActionMessages == 0) return;
                messages = config.BaseBuildingActionMessages;
                break;

            case "VEHICLE":
                if (config.EnableExtendedVanillaActionMessages == 0) return;
                messages = config.VehicleActionMessages;
                break;

            case "INVENTORY_MANAGEMENT":
                if (config.EnableExtendedVanillaActionMessages == 0) return;
                messages = config.InventoryActionMessages;
                break;

            case "BURY_STASH":
                if (config.EnableExtendedVanillaActionMessages == 0) return;
                messages = config.BuryStashMessages;
                break;

            case "PERSONAL_CARE":
                if (config.EnableExtendedVanillaActionMessages == 0) return;
                messages = config.PersonalCareMessages;
                break;

            case "AMMO_MANAGEMENT":
                if (config.EnableExtendedVanillaActionMessages == 0) return;
                messages = config.AmmoManagementMessages;
                break;

            case "MOVEMENT":
                if (config.EnableExtendedVanillaActionMessages == 0) return;
                messages = config.MovementActionMessages;
                break;

            case "WORLD_INTERACTION":
                if (config.EnableExtendedVanillaActionMessages == 0) return;
                messages = config.WorldInteractionMessages;
                break;

            default:
                if (config.EnableExtendedVanillaActionMessages == 0) return;
                messages = config.GeneralActionMessages;
                break;
        }

        if (actionType == "OPEN_CLOSE")
        {
            if (!GetGame())
                return;

            float doorCooldown = config.OpenCloseActionCooldownSeconds;

            // Older configs used 2.5 seconds, which caused a thought for nearly
            // every doorway. Enforce a twenty-second minimum without requiring
            // administrators to regenerate their configuration files.
            if (doorCooldown < 20.0)
                doorCooldown = 20.0;

            float nowOpenClose = GetGame().GetTime() / 1000.0;
            float lastOpenClose = player.ST_GetLastOpenCloseActionThoughtTime();

            if ((nowOpenClose - lastOpenClose) < doorCooldown)
            {
                DebugLog("Open/close action thought blocked by door cooldown.");
                return;
            }

            // Even after the cooldown, doors should feel incidental rather than
            // generating narration every time.
            if (Math.RandomFloat01() > 0.35)
            {
                player.ST_SetLastOpenCloseActionThoughtTime(nowOpenClose);
                DebugLog("Open/close action thought skipped by frequency gate.");
                return;
            }

            player.ST_SetLastOpenCloseActionThoughtTime(nowOpenClose);
        }

        if (!messages || messages.Count() == 0)
        {
            DebugLog("Action thought skipped because message pool was empty: " + actionType);
            return;
        }

        DebugLog("Action thought sent immediately on action start: " + actionType);
        SendImmediateThoughtWithPriority(player, messages.GetRandomElement(), actionType);
    }


    void CreateMissingModularConfigFiles(string modularFolderPath)
    {
        if (!FileExist("$profile:ZombicideMods"))
            MakeDirectory("$profile:ZombicideMods");

        if (!FileExist("$profile:ZombicideMods/SurvivorThoughts"))
            MakeDirectory("$profile:ZombicideMods/SurvivorThoughts");

        if (!FileExist(modularFolderPath))
            MakeDirectory(modularFolderPath);

        EnsureLogDirectory();

        ST_CreateDefault_00_Core_Admin_Output_json(modularFolderPath);
        ST_CreateDefault_01_Player_State_Personality_json(modularFolderPath);
        ST_CreateDefault_02_Messages_Survival_json(modularFolderPath);
        ST_CreateDefault_03_Actions_Damage_Combat_json(modularFolderPath);
        ST_CreateDefault_04_World_Environment_json(modularFolderPath);
        ST_CreateDefault_05_Items_Corpses_json(modularFolderPath);
        ST_CreateDefault_06_Social_Sanity_Journal_json(modularFolderPath);
        ST_CreateDefault_07_Admin_Diagnostics_json(modularFolderPath);
    }

    bool ST_HasAnyConsolidatedConfigFile(string folderPath)
    {
        if (FileExist(folderPath + "/00_Core_Admin_Output.json"))
            return true;
        if (FileExist(folderPath + "/01_Player_State_Personality.json"))
            return true;
        if (FileExist(folderPath + "/02_Messages_Survival.json"))
            return true;
        if (FileExist(folderPath + "/03_Actions_Damage_Combat.json"))
            return true;
        if (FileExist(folderPath + "/04_World_Environment.json"))
            return true;
        if (FileExist(folderPath + "/05_Items_Corpses.json"))
            return true;
        if (FileExist(folderPath + "/06_Social_Sanity_Journal.json"))
            return true;
        if (FileExist(folderPath + "/07_Admin_Diagnostics.json"))
            return true;

        return false;
    }

    bool ST_HasAnyLegacyConfigFile(string folderPath)
    {
        if (FileExist(folderPath + "/Core.json"))
            return true;
        if (FileExist(folderPath + "/Output.json"))
            return true;
        if (FileExist(folderPath + "/Stats.json"))
            return true;
        if (FileExist(folderPath + "/Messages_Passive.json"))
            return true;
        if (FileExist(folderPath + "/Messages_Actions.json"))
            return true;
        if (FileExist(folderPath + "/Messages_Damage.json"))
            return true;
        if (FileExist(folderPath + "/Messages_Combined.json"))
            return true;
        if (FileExist(folderPath + "/Messages_Advanced_Combined.json"))
            return true;
        if (FileExist(folderPath + "/Recovery_Messages.json"))
            return true;
        if (FileExist(folderPath + "/World_Weather.json"))
            return true;
        if (FileExist(folderPath + "/World_Time.json"))
            return true;
        if (FileExist(folderPath + "/World_Locations.json"))
            return true;
        if (FileExist(folderPath + "/Items.json"))
            return true;
        if (FileExist(folderPath + "/Corpses.json"))
            return true;
        if (FileExist(folderPath + "/Personality.json"))
            return true;
        if (FileExist(folderPath + "/Player_Memory.json"))
            return true;
        if (FileExist(folderPath + "/Stealth_Noise.json"))
            return true;
        if (FileExist(folderPath + "/Shelter.json"))
            return true;
        if (FileExist(folderPath + "/Message_Blocker.json"))
            return true;
        if (FileExist(folderPath + "/Mental_State.json"))
            return true;
        if (FileExist(folderPath + "/Custom_Thought_Zones.json"))
            return true;
        if (FileExist(folderPath + "/Thought_Priority.json"))
            return true;
        if (FileExist(folderPath + "/Social_Group.json"))
            return true;
        if (FileExist(folderPath + "/Sanity_Cannibalism.json"))
            return true;
        if (FileExist(folderPath + "/Persistent_Storage.json"))
            return true;
        if (FileExist(folderPath + "/Player_State_History.json"))
            return true;
        if (FileExist(folderPath + "/Thought_Decision_Trace.json"))
            return true;
        if (FileExist(folderPath + "/NearMiss_Combat.json"))
            return true;
        if (FileExist(folderPath + "/Disease_Specific.json"))
            return true;
        if (FileExist(folderPath + "/Admin_Analytics.json"))
            return true;
        if (FileExist(folderPath + "/Player_Journals.json"))
            return true;
        if (FileExist(folderPath + "/Map_Environment_Packs.json"))
            return true;
        if (FileExist(folderPath + "/Journal_Backstories.json"))
            return true;
        if (FileExist(folderPath + "/Admin.json"))
            return true;
        if (FileExist(folderPath + "/Items_Combat_Corpses.json"))
            return true;

        return false;
    }

    void ST_MoveLegacyConfigFilesToRedundant(string folderPath)
    {
        string redundantFolderPath = folderPath + "/_Redundant";

        if (!FileExist(redundantFolderPath))
            MakeDirectory(redundantFolderPath);

        ST_MoveLegacyConfigFileToRedundant(folderPath, redundantFolderPath, "Core.json");
        ST_MoveLegacyConfigFileToRedundant(folderPath, redundantFolderPath, "Output.json");
        ST_MoveLegacyConfigFileToRedundant(folderPath, redundantFolderPath, "Stats.json");
        ST_MoveLegacyConfigFileToRedundant(folderPath, redundantFolderPath, "Messages_Passive.json");
        ST_MoveLegacyConfigFileToRedundant(folderPath, redundantFolderPath, "Messages_Actions.json");
        ST_MoveLegacyConfigFileToRedundant(folderPath, redundantFolderPath, "Messages_Damage.json");
        ST_MoveLegacyConfigFileToRedundant(folderPath, redundantFolderPath, "Messages_Combined.json");
        ST_MoveLegacyConfigFileToRedundant(folderPath, redundantFolderPath, "Messages_Advanced_Combined.json");
        ST_MoveLegacyConfigFileToRedundant(folderPath, redundantFolderPath, "Recovery_Messages.json");
        ST_MoveLegacyConfigFileToRedundant(folderPath, redundantFolderPath, "World_Weather.json");
        ST_MoveLegacyConfigFileToRedundant(folderPath, redundantFolderPath, "World_Time.json");
        ST_MoveLegacyConfigFileToRedundant(folderPath, redundantFolderPath, "World_Locations.json");
        ST_MoveLegacyConfigFileToRedundant(folderPath, redundantFolderPath, "Items.json");
        ST_MoveLegacyConfigFileToRedundant(folderPath, redundantFolderPath, "Corpses.json");
        ST_MoveLegacyConfigFileToRedundant(folderPath, redundantFolderPath, "Personality.json");
        ST_MoveLegacyConfigFileToRedundant(folderPath, redundantFolderPath, "Player_Memory.json");
        ST_MoveLegacyConfigFileToRedundant(folderPath, redundantFolderPath, "Stealth_Noise.json");
        ST_MoveLegacyConfigFileToRedundant(folderPath, redundantFolderPath, "Shelter.json");
        ST_MoveLegacyConfigFileToRedundant(folderPath, redundantFolderPath, "Message_Blocker.json");
        ST_MoveLegacyConfigFileToRedundant(folderPath, redundantFolderPath, "Mental_State.json");
        ST_MoveLegacyConfigFileToRedundant(folderPath, redundantFolderPath, "Custom_Thought_Zones.json");
        ST_MoveLegacyConfigFileToRedundant(folderPath, redundantFolderPath, "Thought_Priority.json");
        ST_MoveLegacyConfigFileToRedundant(folderPath, redundantFolderPath, "Social_Group.json");
        ST_MoveLegacyConfigFileToRedundant(folderPath, redundantFolderPath, "Sanity_Cannibalism.json");
        ST_MoveLegacyConfigFileToRedundant(folderPath, redundantFolderPath, "Persistent_Storage.json");
        ST_MoveLegacyConfigFileToRedundant(folderPath, redundantFolderPath, "Player_State_History.json");
        ST_MoveLegacyConfigFileToRedundant(folderPath, redundantFolderPath, "Thought_Decision_Trace.json");
        ST_MoveLegacyConfigFileToRedundant(folderPath, redundantFolderPath, "NearMiss_Combat.json");
        ST_MoveLegacyConfigFileToRedundant(folderPath, redundantFolderPath, "Disease_Specific.json");
        ST_MoveLegacyConfigFileToRedundant(folderPath, redundantFolderPath, "Admin_Analytics.json");
        ST_MoveLegacyConfigFileToRedundant(folderPath, redundantFolderPath, "Player_Journals.json");
        ST_MoveLegacyConfigFileToRedundant(folderPath, redundantFolderPath, "Map_Environment_Packs.json");
        ST_MoveLegacyConfigFileToRedundant(folderPath, redundantFolderPath, "Journal_Backstories.json");
        ST_MoveLegacyConfigFileToRedundant(folderPath, redundantFolderPath, "Admin.json");
        ST_MoveLegacyConfigFileToRedundant(folderPath, redundantFolderPath, "Items_Combat_Corpses.json");
    }

    void ST_MoveLegacyConfigFileToRedundant(string folderPath, string redundantFolderPath, string fileName)
    {
        string sourcePath = folderPath + "/" + fileName;

        if (!FileExist(sourcePath))
            return;

        string destinationPath = redundantFolderPath + "/" + fileName;

        if (FileExist(destinationPath))
            DeleteFile(destinationPath);

        if (ST_CopyTextFile(sourcePath, destinationPath))
        {
            DeleteFile(sourcePath);
            Log("Moved legacy config to _Redundant: " + fileName);
        }
        else
        {
            Log("Failed to move legacy config to _Redundant: " + fileName);
        }
    }

    bool ST_CopyTextFile(string sourcePath, string destinationPath)
    {
        FileHandle sourceFile = OpenFile(sourcePath, FileMode.READ);

        if (!sourceFile)
            return false;

        FileHandle destinationFile = OpenFile(destinationPath, FileMode.WRITE);

        if (!destinationFile)
        {
            CloseFile(sourceFile);
            return false;
        }

        string line;

        while (FGets(sourceFile, line) >= 0)
        {
            FPrintln(destinationFile, line);
        }

        CloseFile(sourceFile);
        CloseFile(destinationFile);

        return true;
    }


    string ST_JsonEscape(string value)
    {
        if (value == string.Empty)
            return "";

        // Compile-safe JSON string helper.
        // Avoids escaped quote/backslash literals that can break DayZ script parsing on some branches.
        // Default generated messages do not contain raw double quotes; server owners should prefer apostrophes in custom messages.
        return value;
    }

    void ST_WriteJsonInt(FileHandle file, string key, int value, bool comma)
    {
        string suffix = "";

        if (comma)
            suffix = ",";

        FPrintln(file, "    \"" + key + "\": " + value.ToString() + suffix);
    }

    void ST_WriteJsonFloat(FileHandle file, string key, float value, bool comma)
    {
        string suffix = "";

        if (comma)
            suffix = ",";

        FPrintln(file, "    \"" + key + "\": " + value.ToString() + suffix);
    }

    void ST_WriteJsonString(FileHandle file, string key, string value, bool comma)
    {
        string suffix = "";

        if (comma)
            suffix = ",";

        FPrintln(file, "    \"" + key + "\": \"" + ST_JsonEscape(value) + "\"" + suffix);
    }

    void ST_WriteJsonStringArray(FileHandle file, string key, array<string> values, bool comma)
    {
        string suffix = "";

        if (comma)
            suffix = ",";

        FPrintln(file, "    \"" + key + "\": [");

        if (values)
        {
            for (int i = 0; i < values.Count(); i++)
            {
                string itemSuffix = "";

                if (i < values.Count() - 1)
                    itemSuffix = ",";

                FPrintln(file, "        \"" + ST_JsonEscape(values.Get(i)) + "\"" + itemSuffix);
            }
        }

        FPrintln(file, "    ]" + suffix);
    }

    void ST_WriteJsonLocationZones(FileHandle file, string key, array<ref ST_LocationZone> values, bool comma)
    {
        string suffix = "";

        if (comma)
            suffix = ",";

        FPrintln(file, "    \"" + key + "\": [");

        if (values)
        {
            for (int i = 0; i < values.Count(); i++)
            {
                ST_LocationZone zone = values.Get(i);

                if (!zone)
                    continue;

                string itemSuffix = "";

                if (i < values.Count() - 1)
                    itemSuffix = ",";

                FPrintln(file, "        {");
                FPrintln(file, "            \"Name\": \"" + ST_JsonEscape(zone.Name) + "\",");
                FPrintln(file, "            \"Type\": \"" + ST_JsonEscape(zone.Type) + "\",");
                FPrintln(file, "            \"X\": " + zone.X.ToString() + ",");
                FPrintln(file, "            \"Z\": " + zone.Z.ToString() + ",");
                FPrintln(file, "            \"Radius\": " + zone.Radius.ToString());
                FPrintln(file, "        }" + itemSuffix);
            }
        }

        FPrintln(file, "    ]" + suffix);
    }

    void ST_WriteJsonCustomThoughtZones(FileHandle file, string key, array<ref ST_CustomThoughtZone> values, bool comma)
    {
        string suffix = "";

        if (comma)
            suffix = ",";

        FPrintln(file, "    \"" + key + "\": [");

        if (values)
        {
            for (int i = 0; i < values.Count(); i++)
            {
                ST_CustomThoughtZone zone = values.Get(i);

                if (!zone)
                    continue;

                string itemSuffix = "";

                if (i < values.Count() - 1)
                    itemSuffix = ",";

                FPrintln(file, "        {");
                FPrintln(file, "            \"Name\": \"" + ST_JsonEscape(zone.Name) + "\",");
                FPrintln(file, "            \"Type\": \"" + ST_JsonEscape(zone.Type) + "\",");
                FPrintln(file, "            \"X\": " + zone.X.ToString() + ",");
                FPrintln(file, "            \"Z\": " + zone.Z.ToString() + ",");
                FPrintln(file, "            \"Radius\": " + zone.Radius.ToString() + ",");
                FPrintln(file, "            \"Chance\": " + zone.Chance.ToString() + ",");
                FPrintln(file, "            \"CooldownSeconds\": " + zone.CooldownSeconds.ToString() + ",");
                ST_WriteJsonStringArray(file, "Messages", zone.Messages, false);
                FPrintln(file, "        }" + itemSuffix);
            }
        }

        FPrintln(file, "    ]" + suffix);
    }

    void ST_WriteConsolidatedConfig_00_Core_Admin_Output(string folderPath)
    {
        if (!m_Config)
            return;

        string filePath = folderPath + "/00_Core_Admin_Output.json";
        FileHandle file = OpenFile(filePath, FileMode.WRITE);

        if (!file)
        {
            Log("Failed to write consolidated config: " + filePath);
            return;
        }

        FPrintln(file, "{");
        ST_WriteJsonInt(file, "ConfigVersion", m_Config.ConfigVersion, true);
        ST_WriteJsonInt(file, "EnableMod", m_Config.EnableMod, true);
        ST_WriteJsonInt(file, "DebugMode", m_Config.DebugMode, true);
        ST_WriteJsonFloat(file, "GlobalCooldownSeconds", m_Config.GlobalCooldownSeconds, true);
        ST_WriteJsonFloat(file, "MinimumRandomDelaySeconds", m_Config.MinimumRandomDelaySeconds, true);
        ST_WriteJsonFloat(file, "MaximumRandomDelaySeconds", m_Config.MaximumRandomDelaySeconds, true);
        ST_WriteJsonInt(file, "ShowHealthyMessages", m_Config.ShowHealthyMessages, true);
        ST_WriteJsonInt(file, "EnableHungerMessages", m_Config.EnableHungerMessages, true);
        ST_WriteJsonInt(file, "EnableThirstMessages", m_Config.EnableThirstMessages, true);
        ST_WriteJsonInt(file, "EnableColdMessages", m_Config.EnableColdMessages, true);
        ST_WriteJsonInt(file, "EnableHotMessages", m_Config.EnableHotMessages, true);
        ST_WriteJsonInt(file, "EnableSicknessMessages", m_Config.EnableSicknessMessages, true);
        ST_WriteJsonInt(file, "EnableBleedingMessages", m_Config.EnableBleedingMessages, true);
        ST_WriteJsonInt(file, "EnableBrokenLegMessages", m_Config.EnableBrokenLegMessages, true);
        ST_WriteJsonInt(file, "EnableInfectedNearbyMessages", m_Config.EnableInfectedNearbyMessages, true);
        ST_WriteJsonFloat(file, "InfectedFarRadius", m_Config.InfectedFarRadius, true);
        ST_WriteJsonFloat(file, "InfectedCloseRadius", m_Config.InfectedCloseRadius, true);
        ST_WriteJsonFloat(file, "InfectedVeryCloseRadius", m_Config.InfectedVeryCloseRadius, true);
        ST_WriteJsonInt(file, "InfectedSurroundedCount", m_Config.InfectedSurroundedCount, true);
        ST_WriteJsonInt(file, "EnableDebugFileLog", m_Config.EnableDebugFileLog, true);
        ST_WriteJsonInt(file, "DebugLogToRPT", m_Config.DebugLogToRPT, true);
        ST_WriteJsonString(file, "DebugLogFileName", m_Config.DebugLogFileName, true);
        ST_WriteJsonInt(file, "ClearDebugLogOnServerStart", m_Config.ClearDebugLogOnServerStart, true);
        ST_WriteJsonInt(file, "UseLocalChatBox", m_Config.UseLocalChatBox, true);
        ST_WriteJsonInt(file, "UseNotificationSystem", m_Config.UseNotificationSystem, true);
        ST_WriteJsonInt(file, "EnableMissionStoragePersistentData", m_Config.EnableMissionStoragePersistentData, true);
        ST_WriteJsonString(file, "PersistentStorageRoot", m_Config.PersistentStorageRoot, true);
        ST_WriteJsonString(file, "PersistentDataFolderName", m_Config.PersistentDataFolderName, true);
        ST_WriteJsonString(file, "PersistentStateDataFile", m_Config.PersistentStateDataFile, true);
        ST_WriteJsonString(file, "PersonalityDataFile", m_Config.PersonalityDataFile, true);
        ST_WriteJsonFloat(file, "PersistentAutosaveSeconds", m_Config.PersistentAutosaveSeconds, true);
        ST_WriteJsonInt(file, "PrioritySocialGroup", m_Config.PrioritySocialGroup, true);
        ST_WriteJsonInt(file, "PrioritySanityCreep", m_Config.PrioritySanityCreep, true);
        ST_WriteJsonInt(file, "PriorityStateHistory", m_Config.PriorityStateHistory, true);
        ST_WriteJsonInt(file, "PriorityRecovery", m_Config.PriorityRecovery, true);
        ST_WriteJsonInt(file, "PriorityAdvancedCombined", m_Config.PriorityAdvancedCombined, true);
        ST_WriteJsonInt(file, "PriorityNearMissCombat", m_Config.PriorityNearMissCombat, true);
        ST_WriteJsonInt(file, "PriorityDiseaseSpecific", m_Config.PriorityDiseaseSpecific, true);
        ST_WriteJsonInt(file, "PriorityMapEnvironment", m_Config.PriorityMapEnvironment, true);
        ST_WriteJsonInt(file, "EnableRecentMessageBlocker", m_Config.EnableRecentMessageBlocker, true);
        ST_WriteJsonInt(file, "RecentMessageMemoryCount", m_Config.RecentMessageMemoryCount, true);
        ST_WriteJsonFloat(file, "RecentMessageBlockSeconds", m_Config.RecentMessageBlockSeconds, true);
        ST_WriteJsonInt(file, "EnableAdminReload", m_Config.EnableAdminReload, true);
        ST_WriteJsonString(file, "AdminReloadCommand", m_Config.AdminReloadCommand, true);
        ST_WriteJsonStringArray(file, "AdminSteamIds", m_Config.AdminSteamIds, false);
        FPrintln(file, "}");
        CloseFile(file);
    }

    void ST_WriteConsolidatedConfig_01_Player_State_Personality(string folderPath)
    {
        if (!m_Config)
            return;

        string filePath = folderPath + "/01_Player_State_Personality.json";
        FileHandle file = OpenFile(filePath, FileMode.WRITE);

        if (!file)
        {
            Log("Failed to write consolidated config: " + filePath);
            return;
        }

        FPrintln(file, "{");
        ST_WriteJsonInt(file, "EnableConfigurableStatThresholds", m_Config.EnableConfigurableStatThresholds, true);
        ST_WriteJsonInt(file, "EnableEnergyStage1Messages", m_Config.EnableEnergyStage1Messages, true);
        ST_WriteJsonFloat(file, "EnergyStage1_Min", m_Config.EnergyStage1_Min, true);
        ST_WriteJsonFloat(file, "EnergyStage1_Max", m_Config.EnergyStage1_Max, true);
        ST_WriteJsonInt(file, "EnableEnergyStage2Messages", m_Config.EnableEnergyStage2Messages, true);
        ST_WriteJsonFloat(file, "EnergyStage2_Min", m_Config.EnergyStage2_Min, true);
        ST_WriteJsonFloat(file, "EnergyStage2_Max", m_Config.EnergyStage2_Max, true);
        ST_WriteJsonInt(file, "EnableEnergyStage3Messages", m_Config.EnableEnergyStage3Messages, true);
        ST_WriteJsonFloat(file, "EnergyStage3_Min", m_Config.EnergyStage3_Min, true);
        ST_WriteJsonFloat(file, "EnergyStage3_Max", m_Config.EnergyStage3_Max, true);
        ST_WriteJsonInt(file, "EnableEnergyStage4Messages", m_Config.EnableEnergyStage4Messages, true);
        ST_WriteJsonFloat(file, "EnergyStage4_Min", m_Config.EnergyStage4_Min, true);
        ST_WriteJsonFloat(file, "EnergyStage4_Max", m_Config.EnergyStage4_Max, true);
        ST_WriteJsonInt(file, "EnableWaterStage1Messages", m_Config.EnableWaterStage1Messages, true);
        ST_WriteJsonFloat(file, "WaterStage1_Min", m_Config.WaterStage1_Min, true);
        ST_WriteJsonFloat(file, "WaterStage1_Max", m_Config.WaterStage1_Max, true);
        ST_WriteJsonInt(file, "EnableWaterStage2Messages", m_Config.EnableWaterStage2Messages, true);
        ST_WriteJsonFloat(file, "WaterStage2_Min", m_Config.WaterStage2_Min, true);
        ST_WriteJsonFloat(file, "WaterStage2_Max", m_Config.WaterStage2_Max, true);
        ST_WriteJsonInt(file, "EnableWaterStage3Messages", m_Config.EnableWaterStage3Messages, true);
        ST_WriteJsonFloat(file, "WaterStage3_Min", m_Config.WaterStage3_Min, true);
        ST_WriteJsonFloat(file, "WaterStage3_Max", m_Config.WaterStage3_Max, true);
        ST_WriteJsonInt(file, "EnableWaterStage4Messages", m_Config.EnableWaterStage4Messages, true);
        ST_WriteJsonFloat(file, "WaterStage4_Min", m_Config.WaterStage4_Min, true);
        ST_WriteJsonFloat(file, "WaterStage4_Max", m_Config.WaterStage4_Max, true);
        ST_WriteJsonInt(file, "EnableBloodStage1Messages", m_Config.EnableBloodStage1Messages, true);
        ST_WriteJsonFloat(file, "BloodStage1_Min", m_Config.BloodStage1_Min, true);
        ST_WriteJsonFloat(file, "BloodStage1_Max", m_Config.BloodStage1_Max, true);
        ST_WriteJsonInt(file, "EnableBloodStage2Messages", m_Config.EnableBloodStage2Messages, true);
        ST_WriteJsonFloat(file, "BloodStage2_Min", m_Config.BloodStage2_Min, true);
        ST_WriteJsonFloat(file, "BloodStage2_Max", m_Config.BloodStage2_Max, true);
        ST_WriteJsonInt(file, "EnableBloodStage3Messages", m_Config.EnableBloodStage3Messages, true);
        ST_WriteJsonFloat(file, "BloodStage3_Min", m_Config.BloodStage3_Min, true);
        ST_WriteJsonFloat(file, "BloodStage3_Max", m_Config.BloodStage3_Max, true);
        ST_WriteJsonInt(file, "EnableBloodStage4Messages", m_Config.EnableBloodStage4Messages, true);
        ST_WriteJsonFloat(file, "BloodStage4_Min", m_Config.BloodStage4_Min, true);
        ST_WriteJsonFloat(file, "BloodStage4_Max", m_Config.BloodStage4_Max, true);
        ST_WriteJsonInt(file, "EnableShockStage1Messages", m_Config.EnableShockStage1Messages, true);
        ST_WriteJsonFloat(file, "ShockStage1_Min", m_Config.ShockStage1_Min, true);
        ST_WriteJsonFloat(file, "ShockStage1_Max", m_Config.ShockStage1_Max, true);
        ST_WriteJsonInt(file, "EnableShockStage2Messages", m_Config.EnableShockStage2Messages, true);
        ST_WriteJsonFloat(file, "ShockStage2_Min", m_Config.ShockStage2_Min, true);
        ST_WriteJsonFloat(file, "ShockStage2_Max", m_Config.ShockStage2_Max, true);
        ST_WriteJsonInt(file, "EnableShockStage3Messages", m_Config.EnableShockStage3Messages, true);
        ST_WriteJsonFloat(file, "ShockStage3_Min", m_Config.ShockStage3_Min, true);
        ST_WriteJsonFloat(file, "ShockStage3_Max", m_Config.ShockStage3_Max, true);
        ST_WriteJsonInt(file, "EnableShockStage4Messages", m_Config.EnableShockStage4Messages, true);
        ST_WriteJsonFloat(file, "ShockStage4_Min", m_Config.ShockStage4_Min, true);
        ST_WriteJsonFloat(file, "ShockStage4_Max", m_Config.ShockStage4_Max, true);
        ST_WriteJsonInt(file, "EnableDeathSpiralThoughts", m_Config.EnableDeathSpiralThoughts, true);
        ST_WriteJsonFloat(file, "HealthDropMinAmount", m_Config.HealthDropMinAmount, true);
        ST_WriteJsonFloat(file, "HealthDropRecentSeconds", m_Config.HealthDropRecentSeconds, true);
        ST_WriteJsonFloat(file, "DeathSpiralColdComfort_Max", m_Config.DeathSpiralColdComfort_Max, true);
        ST_WriteJsonFloat(file, "DeathSpiralHotComfort_Min", m_Config.DeathSpiralHotComfort_Min, true);
        ST_WriteJsonInt(file, "EnableStarvingToDeathMessages", m_Config.EnableStarvingToDeathMessages, true);
        ST_WriteJsonInt(file, "EnableDehydratingToDeathMessages", m_Config.EnableDehydratingToDeathMessages, true);
        ST_WriteJsonInt(file, "EnableFreezingToDeathMessages", m_Config.EnableFreezingToDeathMessages, true);
        ST_WriteJsonInt(file, "EnableOverheatingToDeathMessages", m_Config.EnableOverheatingToDeathMessages, true);
        ST_WriteJsonInt(file, "EnablePlayerStateHistory", m_Config.EnablePlayerStateHistory, true);
        ST_WriteJsonFloat(file, "StateHistorySampleIntervalSeconds", m_Config.StateHistorySampleIntervalSeconds, true);
        ST_WriteJsonFloat(file, "StateHistoryWindowSeconds", m_Config.StateHistoryWindowSeconds, true);
        ST_WriteJsonFloat(file, "TrendChangeThreshold", m_Config.TrendChangeThreshold, true);
        ST_WriteJsonInt(file, "EnableTrendMessages", m_Config.EnableTrendMessages, true);
        ST_WriteJsonInt(file, "EnableStateSnapshots", m_Config.EnableStateSnapshots, true);
        ST_WriteJsonFloat(file, "StateSnapshotIntervalSeconds", m_Config.StateSnapshotIntervalSeconds, true);
        ST_WriteJsonInt(file, "EnablePersistentStateSnapshots", m_Config.EnablePersistentStateSnapshots, true);
        ST_WriteJsonString(file, "StateSnapshotFolder", m_Config.StateSnapshotFolder, true);
        ST_WriteJsonStringArray(file, "TrendEnergyFallingMessages", m_Config.TrendEnergyFallingMessages, true);
        ST_WriteJsonStringArray(file, "TrendWaterFallingMessages", m_Config.TrendWaterFallingMessages, true);
        ST_WriteJsonStringArray(file, "TrendBloodFallingMessages", m_Config.TrendBloodFallingMessages, true);
        ST_WriteJsonStringArray(file, "TrendHealthFallingMessages", m_Config.TrendHealthFallingMessages, true);
        ST_WriteJsonStringArray(file, "TrendTemperatureWorseningMessages", m_Config.TrendTemperatureWorseningMessages, true);
        ST_WriteJsonStringArray(file, "TrendWetnessWorseningMessages", m_Config.TrendWetnessWorseningMessages, true);
        ST_WriteJsonStringArray(file, "LongSicknessMessages", m_Config.LongSicknessMessages, true);
        ST_WriteJsonStringArray(file, "LongBleedingMessages", m_Config.LongBleedingMessages, true);
        ST_WriteJsonInt(file, "EnableProlongedStateMessages", m_Config.EnableProlongedStateMessages, true);
        ST_WriteJsonFloat(file, "ProlongedStateThresholdSeconds", m_Config.ProlongedStateThresholdSeconds, true);
        ST_WriteJsonStringArray(file, "ProlongedStarvationMessages", m_Config.ProlongedStarvationMessages, true);
        ST_WriteJsonStringArray(file, "ProlongedDehydrationMessages", m_Config.ProlongedDehydrationMessages, true);
        ST_WriteJsonStringArray(file, "ProlongedColdMessages", m_Config.ProlongedColdMessages, true);
        ST_WriteJsonStringArray(file, "ProlongedHeatMessages", m_Config.ProlongedHeatMessages, true);
        ST_WriteJsonStringArray(file, "ProlongedBleedingMessages", m_Config.ProlongedBleedingMessages, true);
        ST_WriteJsonStringArray(file, "ProlongedSicknessMessages", m_Config.ProlongedSicknessMessages, true);
        ST_WriteJsonInt(file, "EnablePersonalityProfiles", m_Config.EnablePersonalityProfiles, true);
        ST_WriteJsonFloat(file, "PersonalityThoughtChance", m_Config.PersonalityThoughtChance, true);
        ST_WriteJsonInt(file, "PersonalityPersistBySteamId", m_Config.PersonalityPersistBySteamId, true);
        ST_WriteJsonString(file, "PersonalityDataFile", m_Config.PersonalityDataFile, true);
        ST_WriteJsonInt(file, "EnablePersonalityChangeOverTime", m_Config.EnablePersonalityChangeOverTime, true);
        ST_WriteJsonFloat(file, "PersonalityChangeChance", m_Config.PersonalityChangeChance, true);
        ST_WriteJsonFloat(file, "PersonalityMinimumSecondsBetweenChanges", m_Config.PersonalityMinimumSecondsBetweenChanges, true);
        ST_WriteJsonStringArray(file, "PersonalityPracticalMessages", m_Config.PersonalityPracticalMessages, true);
        ST_WriteJsonStringArray(file, "PersonalityScaredMessages", m_Config.PersonalityScaredMessages, true);
        ST_WriteJsonStringArray(file, "PersonalityMilitaryMessages", m_Config.PersonalityMilitaryMessages, true);
        ST_WriteJsonStringArray(file, "PersonalityHopelessMessages", m_Config.PersonalityHopelessMessages, true);
        ST_WriteJsonStringArray(file, "PersonalityAggressiveMessages", m_Config.PersonalityAggressiveMessages, true);
        ST_WriteJsonStringArray(file, "PersonalityCalmMessages", m_Config.PersonalityCalmMessages, true);
        ST_WriteJsonInt(file, "EnableMentalStateThoughts", m_Config.EnableMentalStateThoughts, true);
        ST_WriteJsonFloat(file, "MentalStateThoughtCooldownSeconds", m_Config.MentalStateThoughtCooldownSeconds, true);
        ST_WriteJsonFloat(file, "MentalStateThoughtChance", m_Config.MentalStateThoughtChance, true);
        ST_WriteJsonFloat(file, "MentalStateCriticalHealthMax", m_Config.MentalStateCriticalHealthMax, true);
        ST_WriteJsonFloat(file, "MentalStateLowBloodMax", m_Config.MentalStateLowBloodMax, true);
        ST_WriteJsonFloat(file, "MentalStateLowFoodMax", m_Config.MentalStateLowFoodMax, true);
        ST_WriteJsonFloat(file, "MentalStateLowWaterMax", m_Config.MentalStateLowWaterMax, true);
        ST_WriteJsonStringArray(file, "MentalStateStableMessages", m_Config.MentalStateStableMessages, true);
        ST_WriteJsonStringArray(file, "MentalStateUneasyMessages", m_Config.MentalStateUneasyMessages, true);
        ST_WriteJsonStringArray(file, "MentalStateAfraidMessages", m_Config.MentalStateAfraidMessages, true);
        ST_WriteJsonStringArray(file, "MentalStateDesperateMessages", m_Config.MentalStateDesperateMessages, true);
        ST_WriteJsonStringArray(file, "MentalStateNumbMessages", m_Config.MentalStateNumbMessages, true);
        ST_WriteJsonStringArray(file, "MentalStateAggressiveMessages", m_Config.MentalStateAggressiveMessages, true);
        ST_WriteJsonStringArray(file, "MentalStateBrokenMessages", m_Config.MentalStateBrokenMessages, true);
        ST_WriteJsonStringArray(file, "MentalStateFocusedMessages", m_Config.MentalStateFocusedMessages, true);
        ST_WriteJsonInt(file, "EnablePlayerMemoryThoughts", m_Config.EnablePlayerMemoryThoughts, true);
        ST_WriteJsonFloat(file, "PlayerMemoryThoughtCooldownSeconds", m_Config.PlayerMemoryThoughtCooldownSeconds, true);
        ST_WriteJsonFloat(file, "PlayerMemoryThoughtChance", m_Config.PlayerMemoryThoughtChance, true);
        ST_WriteJsonFloat(file, "PlayerMemoryDurationSeconds", m_Config.PlayerMemoryDurationSeconds, true);
        ST_WriteJsonStringArray(file, "PlayerMemoryRecentDamageMessages", m_Config.PlayerMemoryRecentDamageMessages, true);
        ST_WriteJsonStringArray(file, "PlayerMemoryRecentBleedingMessages", m_Config.PlayerMemoryRecentBleedingMessages, true);
        ST_WriteJsonStringArray(file, "PlayerMemoryRecentGunshotMessages", m_Config.PlayerMemoryRecentGunshotMessages, true);
        ST_WriteJsonStringArray(file, "PlayerMemoryRecentCorpseMessages", m_Config.PlayerMemoryRecentCorpseMessages, true);
        ST_WriteJsonStringArray(file, "PlayerMemoryRecentMilitaryMessages", m_Config.PlayerMemoryRecentMilitaryMessages, true);
        ST_WriteJsonStringArray(file, "PlayerMemoryRecentSurvivalCrisisMessages", m_Config.PlayerMemoryRecentSurvivalCrisisMessages, false);
        FPrintln(file, "}");
        CloseFile(file);
    }

    void ST_WriteConsolidatedConfig_02_Messages_Survival(string folderPath)
    {
        if (!m_Config)
            return;

        string filePath = folderPath + "/02_Messages_Survival.json";
        FileHandle file = OpenFile(filePath, FileMode.WRITE);

        if (!file)
        {
            Log("Failed to write consolidated config: " + filePath);
            return;
        }

        FPrintln(file, "{");
        ST_WriteJsonStringArray(file, "EnergyStage1Messages", m_Config.EnergyStage1Messages, true);
        ST_WriteJsonStringArray(file, "EnergyStage2Messages", m_Config.EnergyStage2Messages, true);
        ST_WriteJsonStringArray(file, "EnergyStage3Messages", m_Config.EnergyStage3Messages, true);
        ST_WriteJsonStringArray(file, "EnergyStage4Messages", m_Config.EnergyStage4Messages, true);
        ST_WriteJsonStringArray(file, "WaterStage1Messages", m_Config.WaterStage1Messages, true);
        ST_WriteJsonStringArray(file, "WaterStage2Messages", m_Config.WaterStage2Messages, true);
        ST_WriteJsonStringArray(file, "WaterStage3Messages", m_Config.WaterStage3Messages, true);
        ST_WriteJsonStringArray(file, "WaterStage4Messages", m_Config.WaterStage4Messages, true);
        ST_WriteJsonStringArray(file, "BloodStage1Messages", m_Config.BloodStage1Messages, true);
        ST_WriteJsonStringArray(file, "BloodStage2Messages", m_Config.BloodStage2Messages, true);
        ST_WriteJsonStringArray(file, "BloodStage3Messages", m_Config.BloodStage3Messages, true);
        ST_WriteJsonStringArray(file, "BloodStage4Messages", m_Config.BloodStage4Messages, true);
        ST_WriteJsonStringArray(file, "ShockStage1Messages", m_Config.ShockStage1Messages, true);
        ST_WriteJsonStringArray(file, "ShockStage2Messages", m_Config.ShockStage2Messages, true);
        ST_WriteJsonStringArray(file, "ShockStage3Messages", m_Config.ShockStage3Messages, true);
        ST_WriteJsonStringArray(file, "ShockStage4Messages", m_Config.ShockStage4Messages, true);
        ST_WriteJsonStringArray(file, "Cold_Mild_Messages", m_Config.Cold_Mild_Messages, true);
        ST_WriteJsonStringArray(file, "Cold_Moderate_Messages", m_Config.Cold_Moderate_Messages, true);
        ST_WriteJsonStringArray(file, "Cold_Severe_Messages", m_Config.Cold_Severe_Messages, true);
        ST_WriteJsonStringArray(file, "Cold_Critical_Messages", m_Config.Cold_Critical_Messages, true);
        ST_WriteJsonStringArray(file, "Hot_Mild_Messages", m_Config.Hot_Mild_Messages, true);
        ST_WriteJsonStringArray(file, "Hot_Moderate_Messages", m_Config.Hot_Moderate_Messages, true);
        ST_WriteJsonStringArray(file, "Hot_Severe_Messages", m_Config.Hot_Severe_Messages, true);
        ST_WriteJsonStringArray(file, "Hot_Critical_Messages", m_Config.Hot_Critical_Messages, true);
        ST_WriteJsonStringArray(file, "Sickness_Early_Messages", m_Config.Sickness_Early_Messages, true);
        ST_WriteJsonStringArray(file, "Sickness_Moderate_Messages", m_Config.Sickness_Moderate_Messages, true);
        ST_WriteJsonStringArray(file, "Sickness_Severe_Messages", m_Config.Sickness_Severe_Messages, true);
        ST_WriteJsonStringArray(file, "Sickness_Critical_Messages", m_Config.Sickness_Critical_Messages, true);
        ST_WriteJsonStringArray(file, "Bleeding_One_Messages", m_Config.Bleeding_One_Messages, true);
        ST_WriteJsonStringArray(file, "Bleeding_Multiple_Messages", m_Config.Bleeding_Multiple_Messages, true);
        ST_WriteJsonStringArray(file, "Bleeding_Critical_Messages", m_Config.Bleeding_Critical_Messages, true);
        ST_WriteJsonStringArray(file, "BrokenLegMessages", m_Config.BrokenLegMessages, true);
        ST_WriteJsonStringArray(file, "Infected_Far_Messages", m_Config.Infected_Far_Messages, true);
        ST_WriteJsonStringArray(file, "Infected_Close_Messages", m_Config.Infected_Close_Messages, true);
        ST_WriteJsonStringArray(file, "Infected_VeryClose_Messages", m_Config.Infected_VeryClose_Messages, true);
        ST_WriteJsonStringArray(file, "Infected_Surrounded_Messages", m_Config.Infected_Surrounded_Messages, true);
        ST_WriteJsonInt(file, "EnableCombinedThoughts", m_Config.EnableCombinedThoughts, true);
        ST_WriteJsonInt(file, "MaxCombinedThoughtParts", m_Config.MaxCombinedThoughtParts, true);
        ST_WriteJsonFloat(file, "CombinedThoughtChance", m_Config.CombinedThoughtChance, true);
        ST_WriteJsonInt(file, "UseExtremeSurvivalMessagesAtStateCount", m_Config.UseExtremeSurvivalMessagesAtStateCount, true);
        ST_WriteJsonInt(file, "UseCriticalSurvivalMessagesAtStateCount", m_Config.UseCriticalSurvivalMessagesAtStateCount, true);
        ST_WriteJsonStringArray(file, "HungerThirstMessages", m_Config.HungerThirstMessages, true);
        ST_WriteJsonStringArray(file, "HungerColdMessages", m_Config.HungerColdMessages, true);
        ST_WriteJsonStringArray(file, "HungerInfectedMessages", m_Config.HungerInfectedMessages, true);
        ST_WriteJsonStringArray(file, "ThirstColdMessages", m_Config.ThirstColdMessages, true);
        ST_WriteJsonStringArray(file, "HotThirstMessages", m_Config.HotThirstMessages, true);
        ST_WriteJsonStringArray(file, "SickColdMessages", m_Config.SickColdMessages, true);
        ST_WriteJsonStringArray(file, "BleedingInfectedMessages", m_Config.BleedingInfectedMessages, true);
        ST_WriteJsonStringArray(file, "HungerColdInfectedMessages", m_Config.HungerColdInfectedMessages, true);
        ST_WriteJsonStringArray(file, "HungerThirstColdMessages", m_Config.HungerThirstColdMessages, true);
        ST_WriteJsonStringArray(file, "ExtremeSurvivalMessages", m_Config.ExtremeSurvivalMessages, true);
        ST_WriteJsonStringArray(file, "CriticalSurvivalMessages", m_Config.CriticalSurvivalMessages, true);
        ST_WriteJsonStringArray(file, "ColdInfectedMessages", m_Config.ColdInfectedMessages, true);
        ST_WriteJsonStringArray(file, "BleedingColdMessages", m_Config.BleedingColdMessages, true);
        ST_WriteJsonStringArray(file, "SickThirstMessages", m_Config.SickThirstMessages, true);
        ST_WriteJsonStringArray(file, "HungerHotMessages", m_Config.HungerHotMessages, true);
        ST_WriteJsonStringArray(file, "HungerSickMessages", m_Config.HungerSickMessages, true);
        ST_WriteJsonStringArray(file, "HungerBleedingMessages", m_Config.HungerBleedingMessages, true);
        ST_WriteJsonStringArray(file, "ThirstBleedingMessages", m_Config.ThirstBleedingMessages, true);
        ST_WriteJsonStringArray(file, "ThirstInfectedMessages", m_Config.ThirstInfectedMessages, true);
        ST_WriteJsonStringArray(file, "HotSickMessages", m_Config.HotSickMessages, true);
        ST_WriteJsonStringArray(file, "HotBleedingMessages", m_Config.HotBleedingMessages, true);
        ST_WriteJsonStringArray(file, "HotInfectedMessages", m_Config.HotInfectedMessages, true);
        ST_WriteJsonStringArray(file, "SickBleedingMessages", m_Config.SickBleedingMessages, true);
        ST_WriteJsonStringArray(file, "SickInfectedMessages", m_Config.SickInfectedMessages, true);
        ST_WriteJsonStringArray(file, "HungerThirstHotMessages", m_Config.HungerThirstHotMessages, true);
        ST_WriteJsonStringArray(file, "HungerThirstInfectedMessages", m_Config.HungerThirstInfectedMessages, true);
        ST_WriteJsonStringArray(file, "ThirstHotInfectedMessages", m_Config.ThirstHotInfectedMessages, true);
        ST_WriteJsonStringArray(file, "SickColdInfectedMessages", m_Config.SickColdInfectedMessages, true);
        ST_WriteJsonStringArray(file, "BleedingColdInfectedMessages", m_Config.BleedingColdInfectedMessages, true);
        ST_WriteJsonStringArray(file, "BleedingSickInfectedMessages", m_Config.BleedingSickInfectedMessages, true);
        ST_WriteJsonStringArray(file, "BrokenLegHungerMessages", m_Config.BrokenLegHungerMessages, true);
        ST_WriteJsonStringArray(file, "BrokenLegThirstMessages", m_Config.BrokenLegThirstMessages, true);
        ST_WriteJsonStringArray(file, "BrokenLegColdMessages", m_Config.BrokenLegColdMessages, true);
        ST_WriteJsonStringArray(file, "BrokenLegHotMessages", m_Config.BrokenLegHotMessages, true);
        ST_WriteJsonStringArray(file, "BrokenLegSickMessages", m_Config.BrokenLegSickMessages, true);
        ST_WriteJsonStringArray(file, "BrokenLegBleedingMessages", m_Config.BrokenLegBleedingMessages, true);
        ST_WriteJsonStringArray(file, "BrokenLegInfectedMessages", m_Config.BrokenLegInfectedMessages, true);
        ST_WriteJsonStringArray(file, "BrokenLegColdInfectedMessages", m_Config.BrokenLegColdInfectedMessages, true);
        ST_WriteJsonStringArray(file, "BrokenLegBleedingInfectedMessages", m_Config.BrokenLegBleedingInfectedMessages, true);
        ST_WriteJsonStringArray(file, "BrokenLegHungerThirstMessages", m_Config.BrokenLegHungerThirstMessages, true);
        ST_WriteJsonStringArray(file, "StarvingToDeathMessages", m_Config.StarvingToDeathMessages, true);
        ST_WriteJsonStringArray(file, "DehydratingToDeathMessages", m_Config.DehydratingToDeathMessages, true);
        ST_WriteJsonStringArray(file, "FreezingToDeathMessages", m_Config.FreezingToDeathMessages, true);
        ST_WriteJsonStringArray(file, "OverheatingToDeathMessages", m_Config.OverheatingToDeathMessages, true);
        ST_WriteJsonInt(file, "EnableAdvancedCombinedMessages", m_Config.EnableAdvancedCombinedMessages, true);
        ST_WriteJsonFloat(file, "AdvancedCombinedChance", m_Config.AdvancedCombinedChance, true);
        ST_WriteJsonStringArray(file, "StarvingDehydratedMessages", m_Config.StarvingDehydratedMessages, true);
        ST_WriteJsonStringArray(file, "StarvingLowBloodMessages", m_Config.StarvingLowBloodMessages, true);
        ST_WriteJsonStringArray(file, "DehydratedLowBloodMessages", m_Config.DehydratedLowBloodMessages, true);
        ST_WriteJsonStringArray(file, "ColdWetMessages", m_Config.ColdWetMessages, true);
        ST_WriteJsonStringArray(file, "ColdWetNightMessages", m_Config.ColdWetNightMessages, true);
        ST_WriteJsonStringArray(file, "ColdWetSickMessages", m_Config.ColdWetSickMessages, true);
        ST_WriteJsonStringArray(file, "HotDehydratedMessages", m_Config.HotDehydratedMessages, true);
        ST_WriteJsonStringArray(file, "BleedingLowBloodMessages", m_Config.BleedingLowBloodMessages, true);
        ST_WriteJsonStringArray(file, "BleedingShockMessages", m_Config.BleedingShockMessages, true);
        ST_WriteJsonStringArray(file, "GunshotBleedingMessages", m_Config.GunshotBleedingMessages, true);
        ST_WriteJsonStringArray(file, "ExplosionShockMessages", m_Config.ExplosionShockMessages, true);
        ST_WriteJsonStringArray(file, "BrokenLegNightMessages", m_Config.BrokenLegNightMessages, true);
        ST_WriteJsonStringArray(file, "LowBloodCorpseMessages", m_Config.LowBloodCorpseMessages, true);
        ST_WriteJsonStringArray(file, "SickContaminatedMessages", m_Config.SickContaminatedMessages, true);
        ST_WriteJsonStringArray(file, "NightRainMessages", m_Config.NightRainMessages, true);
        ST_WriteJsonStringArray(file, "NightFogMessages", m_Config.NightFogMessages, true);
        ST_WriteJsonStringArray(file, "MilitaryGunshotMessages", m_Config.MilitaryGunshotMessages, true);
        ST_WriteJsonStringArray(file, "MilitaryCorpseMessages", m_Config.MilitaryCorpseMessages, true);
        ST_WriteJsonStringArray(file, "LoneWolfNightMessages", m_Config.LoneWolfNightMessages, true);
        ST_WriteJsonStringArray(file, "LowSanityCannibalismMessages", m_Config.LowSanityCannibalismMessages, true);
        ST_WriteJsonStringArray(file, "LowSanityCorpseMessages", m_Config.LowSanityCorpseMessages, true);
        ST_WriteJsonStringArray(file, "LowSanityNightMessages", m_Config.LowSanityNightMessages, true);
        ST_WriteJsonStringArray(file, "CompanionDeadLowSanityMessages", m_Config.CompanionDeadLowSanityMessages, true);
        ST_WriteJsonInt(file, "EnableExpandedAdvancedCombos", m_Config.EnableExpandedAdvancedCombos, true);
        ST_WriteJsonStringArray(file, "StarvingDehydratedColdMessages", m_Config.StarvingDehydratedColdMessages, true);
        ST_WriteJsonStringArray(file, "HotDehydratedSickMessages", m_Config.HotDehydratedSickMessages, true);
        ST_WriteJsonStringArray(file, "BleedingLowBloodShockMessages", m_Config.BleedingLowBloodShockMessages, true);
        ST_WriteJsonStringArray(file, "GunshotBleedingLowBloodMessages", m_Config.GunshotBleedingLowBloodMessages, true);
        ST_WriteJsonStringArray(file, "NightInfectedRainMessages", m_Config.NightInfectedRainMessages, true);
        ST_WriteJsonStringArray(file, "MilitaryNightStormMessages", m_Config.MilitaryNightStormMessages, true);
        ST_WriteJsonStringArray(file, "LoneWolfLowSanityNightMessages", m_Config.LoneWolfLowSanityNightMessages, true);
        ST_WriteJsonStringArray(file, "CompanionDeadNightMessages", m_Config.CompanionDeadNightMessages, true);
        ST_WriteJsonStringArray(file, "CorpseLowSanityNightMessages", m_Config.CorpseLowSanityNightMessages, true);
        ST_WriteJsonStringArray(file, "ShelterNightInfectedMessages", m_Config.ShelterNightInfectedMessages, true);
        ST_WriteJsonInt(file, "EnableRecoveryMessages", m_Config.EnableRecoveryMessages, true);
        ST_WriteJsonFloat(file, "RecoveryThoughtCooldownSeconds", m_Config.RecoveryThoughtCooldownSeconds, true);
        ST_WriteJsonFloat(file, "RecoveryThoughtChance", m_Config.RecoveryThoughtChance, true);
        ST_WriteJsonStringArray(file, "BleedingRecoveryMessages", m_Config.BleedingRecoveryMessages, true);
        ST_WriteJsonStringArray(file, "HealthStableRecoveryMessages", m_Config.HealthStableRecoveryMessages, true);
        ST_WriteJsonStringArray(file, "FoodRecoveryMessages", m_Config.FoodRecoveryMessages, true);
        ST_WriteJsonStringArray(file, "WaterRecoveryMessages", m_Config.WaterRecoveryMessages, true);
        ST_WriteJsonStringArray(file, "WarmedUpMessages", m_Config.WarmedUpMessages, true);
        ST_WriteJsonStringArray(file, "CooledDownMessages", m_Config.CooledDownMessages, true);
        ST_WriteJsonStringArray(file, "DryingOffMessages", m_Config.DryingOffMessages, true);
        ST_WriteJsonStringArray(file, "LeftContaminatedZoneMessages", m_Config.LeftContaminatedZoneMessages, true);
        ST_WriteJsonStringArray(file, "EscapedInfectedMessages", m_Config.EscapedInfectedMessages, true);
        ST_WriteJsonStringArray(file, "DawnSurvivalMessages", m_Config.DawnSurvivalMessages, true);
        ST_WriteJsonStringArray(file, "ShelterFromStormMessages", m_Config.ShelterFromStormMessages, true);
        ST_WriteJsonStringArray(file, "ShockRecoveryMessages", m_Config.ShockRecoveryMessages, true);
        ST_WriteJsonStringArray(file, "BloodStabilizingMessages", m_Config.BloodStabilizingMessages, true);
        ST_WriteJsonStringArray(file, "AlmostDiedRecoveryMessages", m_Config.AlmostDiedRecoveryMessages, true);
        ST_WriteJsonStringArray(file, "SafeShelterRecoveryMessages", m_Config.SafeShelterRecoveryMessages, true);
        ST_WriteJsonStringArray(file, "PostCombatBreathMessages", m_Config.PostCombatBreathMessages, true);
        ST_WriteJsonInt(file, "EnableDiseaseSpecificMessages", m_Config.EnableDiseaseSpecificMessages, true);
        ST_WriteJsonStringArray(file, "DiseaseWoundInfectionMessages", m_Config.DiseaseWoundInfectionMessages, true);
        ST_WriteJsonStringArray(file, "DiseaseCholeraMessages", m_Config.DiseaseCholeraMessages, true);
        ST_WriteJsonStringArray(file, "DiseaseInfluenzaMessages", m_Config.DiseaseInfluenzaMessages, true);
        ST_WriteJsonStringArray(file, "DiseaseKuruMessages", m_Config.DiseaseKuruMessages, true);
        ST_WriteJsonStringArray(file, "DiseaseChemicalMessages", m_Config.DiseaseChemicalMessages, true);
        ST_WriteJsonStringArray(file, "DiseaseUnknownMessages", m_Config.DiseaseUnknownMessages, true);
        ST_WriteJsonStringArray(file, "DiseaseGasExposureMessages", m_Config.DiseaseGasExposureMessages, true);
        ST_WriteJsonStringArray(file, "DiseaseFeverMessages", m_Config.DiseaseFeverMessages, true);
        ST_WriteJsonStringArray(file, "DiseaseFoodPoisoningMessages", m_Config.DiseaseFoodPoisoningMessages, false);
        FPrintln(file, "}");
        CloseFile(file);
    }

    void ST_WriteConsolidatedConfig_03_Actions_Damage_Combat(string folderPath)
    {
        if (!m_Config)
            return;

        string filePath = folderPath + "/03_Actions_Damage_Combat.json";
        FileHandle file = OpenFile(filePath, FileMode.WRITE);

        if (!file)
        {
            Log("Failed to write consolidated config: " + filePath);
            return;
        }

        FPrintln(file, "{");
        ST_WriteJsonInt(file, "EnableActionThoughts", m_Config.EnableActionThoughts, true);
        ST_WriteJsonInt(file, "EnableExtendedVanillaActionMessages", m_Config.EnableExtendedVanillaActionMessages, true);
        ST_WriteJsonInt(file, "EnableEatingThoughts", m_Config.EnableEatingThoughts, true);
        ST_WriteJsonInt(file, "EnableDrinkingThoughts", m_Config.EnableDrinkingThoughts, true);
        ST_WriteJsonInt(file, "EnableUnjamThoughts", m_Config.EnableUnjamThoughts, true);
        ST_WriteJsonInt(file, "EnableSkinningThoughts", m_Config.EnableSkinningThoughts, true);
        ST_WriteJsonInt(file, "EnableBandagingThoughts", m_Config.EnableBandagingThoughts, true);
        ST_WriteJsonInt(file, "EnableFireStartingThoughts", m_Config.EnableFireStartingThoughts, true);
        ST_WriteJsonInt(file, "EnableCookingThoughts", m_Config.EnableCookingThoughts, true);
        ST_WriteJsonInt(file, "EnableFishingThoughts", m_Config.EnableFishingThoughts, true);
        ST_WriteJsonInt(file, "EnableRepairThoughts", m_Config.EnableRepairThoughts, true);
        ST_WriteJsonStringArray(file, "EatingMessages", m_Config.EatingMessages, true);
        ST_WriteJsonStringArray(file, "DrinkingMessages", m_Config.DrinkingMessages, true);
        ST_WriteJsonStringArray(file, "UnsafeDrinkingMessages", m_Config.UnsafeDrinkingMessages, true);
        ST_WriteJsonStringArray(file, "UnjamMessages", m_Config.UnjamMessages, true);
        ST_WriteJsonStringArray(file, "UnjamSuccessMessages", m_Config.UnjamSuccessMessages, true);
        ST_WriteJsonStringArray(file, "SkinningAnimalMessages", m_Config.SkinningAnimalMessages, true);
        ST_WriteJsonStringArray(file, "SkinningHumanMessages", m_Config.SkinningHumanMessages, true);
        ST_WriteJsonStringArray(file, "BandagingMessages", m_Config.BandagingMessages, true);
        ST_WriteJsonStringArray(file, "BandageSuccessMessages", m_Config.BandageSuccessMessages, true);
        ST_WriteJsonStringArray(file, "FireStartingMessages", m_Config.FireStartingMessages, true);
        ST_WriteJsonStringArray(file, "CookingMessages", m_Config.CookingMessages, true);
        ST_WriteJsonStringArray(file, "FishingMessages", m_Config.FishingMessages, true);
        ST_WriteJsonStringArray(file, "RepairMessages", m_Config.RepairMessages, true);
        ST_WriteJsonStringArray(file, "MedicineConsumeMessages", m_Config.MedicineConsumeMessages, true);
        ST_WriteJsonStringArray(file, "WoundCareActionMessages", m_Config.WoundCareActionMessages, true);
        ST_WriteJsonStringArray(file, "InjectionMessages", m_Config.InjectionMessages, true);
        ST_WriteJsonStringArray(file, "BloodMedicalMessages", m_Config.BloodMedicalMessages, true);
        ST_WriteJsonStringArray(file, "DisinfectActionMessages", m_Config.DisinfectActionMessages, true);
        ST_WriteJsonStringArray(file, "RestrainActionMessages", m_Config.RestrainActionMessages, true);
        ST_WriteJsonStringArray(file, "CraftingActionMessages", m_Config.CraftingActionMessages, true);
        ST_WriteJsonStringArray(file, "DeployActionMessages", m_Config.DeployActionMessages, true);
        ST_WriteJsonStringArray(file, "GardeningActionMessages", m_Config.GardeningActionMessages, true);
        ST_WriteJsonStringArray(file, "ResourceGatheringMessages", m_Config.ResourceGatheringMessages, true);
        ST_WriteJsonStringArray(file, "LiquidTransferMessages", m_Config.LiquidTransferMessages, true);
        ST_WriteJsonStringArray(file, "FireplaceActionMessages", m_Config.FireplaceActionMessages, true);
        ST_WriteJsonStringArray(file, "ElectronicsActionMessages", m_Config.ElectronicsActionMessages, true);
        ST_WriteJsonStringArray(file, "NavigationActionMessages", m_Config.NavigationActionMessages, true);
        ST_WriteJsonStringArray(file, "LockActionMessages", m_Config.LockActionMessages, true);
        ST_WriteJsonStringArray(file, "TrapExplosiveMessages", m_Config.TrapExplosiveMessages, true);
        ST_WriteJsonStringArray(file, "BaseBuildingActionMessages", m_Config.BaseBuildingActionMessages, true);
        ST_WriteJsonStringArray(file, "VehicleActionMessages", m_Config.VehicleActionMessages, true);
        ST_WriteJsonStringArray(file, "BuryStashMessages", m_Config.BuryStashMessages, true);
        ST_WriteJsonStringArray(file, "PersonalCareMessages", m_Config.PersonalCareMessages, true);
        ST_WriteJsonStringArray(file, "AmmoManagementMessages", m_Config.AmmoManagementMessages, true);
        ST_WriteJsonStringArray(file, "OpenCloseActionMessages", m_Config.OpenCloseActionMessages, true);
        ST_WriteJsonStringArray(file, "GeneralActionMessages", m_Config.GeneralActionMessages, true);
        ST_WriteJsonStringArray(file, "InventoryActionMessages", m_Config.InventoryActionMessages, true);
        ST_WriteJsonStringArray(file, "MovementActionMessages", m_Config.MovementActionMessages, true);
        ST_WriteJsonStringArray(file, "WorldInteractionMessages", m_Config.WorldInteractionMessages, true);
        ST_WriteJsonFloat(file, "OpenCloseActionCooldownSeconds", m_Config.OpenCloseActionCooldownSeconds, true);
        ST_WriteJsonInt(file, "EnableDamageReactionThoughts", m_Config.EnableDamageReactionThoughts, true);
        ST_WriteJsonInt(file, "EnableBleedingReactionThoughts", m_Config.EnableBleedingReactionThoughts, true);
        ST_WriteJsonInt(file, "EnableZombieHitMessages", m_Config.EnableZombieHitMessages, true);
        ST_WriteJsonInt(file, "EnablePlayerMeleeHitMessages", m_Config.EnablePlayerMeleeHitMessages, true);
        ST_WriteJsonInt(file, "EnableGunshotHitMessages", m_Config.EnableGunshotHitMessages, true);
        ST_WriteJsonInt(file, "EnableExplosionHitMessages", m_Config.EnableExplosionHitMessages, true);
        ST_WriteJsonInt(file, "EnableHeavyHitMessages", m_Config.EnableHeavyHitMessages, true);
        ST_WriteJsonInt(file, "EnableBleedingStartedMessages", m_Config.EnableBleedingStartedMessages, true);
        ST_WriteJsonInt(file, "EnableBleedingWorseMessages", m_Config.EnableBleedingWorseMessages, true);
        ST_WriteJsonInt(file, "EnableBleedingStoppedMessages", m_Config.EnableBleedingStoppedMessages, true);
        ST_WriteJsonFloat(file, "HeavyHitHealthDamage_Min", m_Config.HeavyHitHealthDamage_Min, true);
        ST_WriteJsonFloat(file, "HeavyHitBloodDamage_Min", m_Config.HeavyHitBloodDamage_Min, true);
        ST_WriteJsonFloat(file, "HeavyHitShockDamage_Min", m_Config.HeavyHitShockDamage_Min, true);
        ST_WriteJsonStringArray(file, "ZombieHitMessages", m_Config.ZombieHitMessages, true);
        ST_WriteJsonStringArray(file, "PlayerMeleeHitMessages", m_Config.PlayerMeleeHitMessages, true);
        ST_WriteJsonStringArray(file, "GunshotHitMessages", m_Config.GunshotHitMessages, true);
        ST_WriteJsonStringArray(file, "ExplosionHitMessages", m_Config.ExplosionHitMessages, true);
        ST_WriteJsonStringArray(file, "HeavyHitMessages", m_Config.HeavyHitMessages, true);
        ST_WriteJsonStringArray(file, "BleedingStartedMessages", m_Config.BleedingStartedMessages, true);
        ST_WriteJsonStringArray(file, "BleedingWorseMessages", m_Config.BleedingWorseMessages, true);
        ST_WriteJsonStringArray(file, "BleedingStoppedMessages", m_Config.BleedingStoppedMessages, true);
        ST_WriteJsonInt(file, "EnableNearMissCombatMessages", m_Config.EnableNearMissCombatMessages, true);
        ST_WriteJsonFloat(file, "NearMissCombatCooldownSeconds", m_Config.NearMissCombatCooldownSeconds, true);
        ST_WriteJsonFloat(file, "NearMissCombatChance", m_Config.NearMissCombatChance, true);
        ST_WriteJsonStringArray(file, "NearMissBulletMessages", m_Config.NearMissBulletMessages, true);
        ST_WriteJsonStringArray(file, "NearMissExplosionMessages", m_Config.NearMissExplosionMessages, true);
        ST_WriteJsonStringArray(file, "NearMissCombatGeneralMessages", m_Config.NearMissCombatGeneralMessages, false);
        FPrintln(file, "}");
        CloseFile(file);
    }

    void ST_WriteConsolidatedConfig_04_World_Environment(string folderPath)
    {
        if (!m_Config)
            return;

        string filePath = folderPath + "/04_World_Environment.json";
        FileHandle file = OpenFile(filePath, FileMode.WRITE);

        if (!file)
        {
            Log("Failed to write consolidated config: " + filePath);
            return;
        }

        FPrintln(file, "{");
        ST_WriteJsonInt(file, "EnableWeatherThoughts", m_Config.EnableWeatherThoughts, true);
        ST_WriteJsonFloat(file, "RainThought_Min", m_Config.RainThought_Min, true);
        ST_WriteJsonFloat(file, "FogThought_Min", m_Config.FogThought_Min, true);
        ST_WriteJsonFloat(file, "WindThought_Min", m_Config.WindThought_Min, true);
        ST_WriteJsonFloat(file, "StormRain_Min", m_Config.StormRain_Min, true);
        ST_WriteJsonFloat(file, "StormWind_Min", m_Config.StormWind_Min, true);
        ST_WriteJsonFloat(file, "StormOvercast_Min", m_Config.StormOvercast_Min, true);
        ST_WriteJsonStringArray(file, "WeatherRainMessages", m_Config.WeatherRainMessages, true);
        ST_WriteJsonStringArray(file, "WeatherFogMessages", m_Config.WeatherFogMessages, true);
        ST_WriteJsonStringArray(file, "WeatherWindMessages", m_Config.WeatherWindMessages, true);
        ST_WriteJsonStringArray(file, "WeatherStormMessages", m_Config.WeatherStormMessages, true);
        ST_WriteJsonInt(file, "EnableLocationThoughts", m_Config.EnableLocationThoughts, true);
        ST_WriteJsonFloat(file, "LocationThoughtCooldownSeconds", m_Config.LocationThoughtCooldownSeconds, true);
        ST_WriteJsonFloat(file, "LocationThoughtChance", m_Config.LocationThoughtChance, true);
        ST_WriteJsonInt(file, "LocationUseCustomZones", m_Config.LocationUseCustomZones, true);
        ST_WriteJsonInt(file, "LocationUseFallbackDetection", m_Config.LocationUseFallbackDetection, true);
        ST_WriteJsonFloat(file, "LocationCoastZMax", m_Config.LocationCoastZMax, true);
        ST_WriteJsonFloat(file, "LocationWildernessScanRadius", m_Config.LocationWildernessScanRadius, true);
        ST_WriteJsonInt(file, "LocationWildernessMaxObjects", m_Config.LocationWildernessMaxObjects, true);
        ST_WriteJsonLocationZones(file, "LocationZones", m_Config.LocationZones, true);
        ST_WriteJsonStringArray(file, "LocationCoastMessages", m_Config.LocationCoastMessages, true);
        ST_WriteJsonStringArray(file, "LocationTownMessages", m_Config.LocationTownMessages, true);
        ST_WriteJsonStringArray(file, "LocationCityMessages", m_Config.LocationCityMessages, true);
        ST_WriteJsonStringArray(file, "LocationForestMessages", m_Config.LocationForestMessages, true);
        ST_WriteJsonStringArray(file, "LocationWildernessMessages", m_Config.LocationWildernessMessages, true);
        ST_WriteJsonStringArray(file, "LocationMilitaryMessages", m_Config.LocationMilitaryMessages, true);
        ST_WriteJsonStringArray(file, "LocationPoliceMessages", m_Config.LocationPoliceMessages, true);
        ST_WriteJsonStringArray(file, "LocationMedicalMessages", m_Config.LocationMedicalMessages, true);
        ST_WriteJsonStringArray(file, "LocationIndustrialMessages", m_Config.LocationIndustrialMessages, true);
        ST_WriteJsonStringArray(file, "LocationFarmMessages", m_Config.LocationFarmMessages, true);
        ST_WriteJsonStringArray(file, "LocationWaterMessages", m_Config.LocationWaterMessages, true);
        ST_WriteJsonInt(file, "EnableMapEnvironmentPacks", m_Config.EnableMapEnvironmentPacks, true);
        ST_WriteJsonString(file, "ActiveMapEnvironmentPack", m_Config.ActiveMapEnvironmentPack, true);
        ST_WriteJsonFloat(file, "MapEnvironmentThoughtChance", m_Config.MapEnvironmentThoughtChance, true);
        ST_WriteJsonFloat(file, "MapEnvironmentThoughtCooldownSeconds", m_Config.MapEnvironmentThoughtCooldownSeconds, true);
        ST_WriteJsonStringArray(file, "MapChernarusMessages", m_Config.MapChernarusMessages, true);
        ST_WriteJsonStringArray(file, "MapLivoniaMessages", m_Config.MapLivoniaMessages, true);
        ST_WriteJsonStringArray(file, "MapNamalskMessages", m_Config.MapNamalskMessages, true);
        ST_WriteJsonStringArray(file, "MapSakhalMessages", m_Config.MapSakhalMessages, true);
        ST_WriteJsonStringArray(file, "MapDeerIsleMessages", m_Config.MapDeerIsleMessages, true);
        ST_WriteJsonStringArray(file, "MapGenericMessages", m_Config.MapGenericMessages, true);
        ST_WriteJsonInt(file, "EnableShelterThoughts", m_Config.EnableShelterThoughts, true);
        ST_WriteJsonFloat(file, "ShelterThoughtCooldownSeconds", m_Config.ShelterThoughtCooldownSeconds, true);
        ST_WriteJsonFloat(file, "ShelterThoughtChance", m_Config.ShelterThoughtChance, true);
        ST_WriteJsonFloat(file, "ShelterScanRadius", m_Config.ShelterScanRadius, true);
        ST_WriteJsonInt(file, "ShelterNearbyBuildingCountRequired", m_Config.ShelterNearbyBuildingCountRequired, true);
        ST_WriteJsonStringArray(file, "ShelterSafeMessages", m_Config.ShelterSafeMessages, true);
        ST_WriteJsonStringArray(file, "ShelterUnsafeMessages", m_Config.ShelterUnsafeMessages, true);
        ST_WriteJsonStringArray(file, "ShelterBadWeatherMessages", m_Config.ShelterBadWeatherMessages, true);
        ST_WriteJsonStringArray(file, "ShelterNightMessages", m_Config.ShelterNightMessages, true);
        ST_WriteJsonInt(file, "EnableCustomThoughtZones", m_Config.EnableCustomThoughtZones, true);
        ST_WriteJsonFloat(file, "CustomThoughtZoneDefaultCooldownSeconds", m_Config.CustomThoughtZoneDefaultCooldownSeconds, true);
        ST_WriteJsonFloat(file, "CustomThoughtZoneDefaultChance", m_Config.CustomThoughtZoneDefaultChance, true);
        ST_WriteJsonCustomThoughtZones(file, "CustomThoughtZones", m_Config.CustomThoughtZones, false);
        FPrintln(file, "}");
        CloseFile(file);
    }

    void ST_WriteConsolidatedConfig_05_Items_Corpses(string folderPath)
    {
        if (!m_Config)
            return;

        string filePath = folderPath + "/05_Items_Corpses.json";
        FileHandle file = OpenFile(filePath, FileMode.WRITE);

        if (!file)
        {
            Log("Failed to write consolidated config: " + filePath);
            return;
        }

        FPrintln(file, "{");
        ST_WriteJsonInt(file, "EnableItemConditionThoughts", m_Config.EnableItemConditionThoughts, true);
        ST_WriteJsonFloat(file, "ItemConditionHealthThreshold", m_Config.ItemConditionHealthThreshold, true);
        ST_WriteJsonInt(file, "ScanEquippedItemsForDamagedThoughts", m_Config.ScanEquippedItemsForDamagedThoughts, true);
        ST_WriteJsonInt(file, "EnableHandsItemConditionMessages", m_Config.EnableHandsItemConditionMessages, true);
        ST_WriteJsonInt(file, "EnableWeaponConditionMessages", m_Config.EnableWeaponConditionMessages, true);
        ST_WriteJsonInt(file, "EnableClothingConditionMessages", m_Config.EnableClothingConditionMessages, true);
        ST_WriteJsonInt(file, "EnableShoesConditionMessages", m_Config.EnableShoesConditionMessages, true);
        ST_WriteJsonInt(file, "EnableBackpackConditionMessages", m_Config.EnableBackpackConditionMessages, true);
        ST_WriteJsonInt(file, "EnableVestConditionMessages", m_Config.EnableVestConditionMessages, true);
        ST_WriteJsonInt(file, "EnableHeadgearConditionMessages", m_Config.EnableHeadgearConditionMessages, true);
        ST_WriteJsonInt(file, "EnableGlovesConditionMessages", m_Config.EnableGlovesConditionMessages, true);
        ST_WriteJsonInt(file, "EnableMaskConditionMessages", m_Config.EnableMaskConditionMessages, true);
        ST_WriteJsonInt(file, "EnableBeltConditionMessages", m_Config.EnableBeltConditionMessages, true);
        ST_WriteJsonStringArray(file, "ItemBadlyDamagedMessages", m_Config.ItemBadlyDamagedMessages, true);
        ST_WriteJsonStringArray(file, "ItemWeaponDamagedMessages", m_Config.ItemWeaponDamagedMessages, true);
        ST_WriteJsonStringArray(file, "ItemShoesDamagedMessages", m_Config.ItemShoesDamagedMessages, true);
        ST_WriteJsonStringArray(file, "ItemClothingDamagedMessages", m_Config.ItemClothingDamagedMessages, true);
        ST_WriteJsonStringArray(file, "ItemBackpackDamagedMessages", m_Config.ItemBackpackDamagedMessages, true);
        ST_WriteJsonStringArray(file, "ItemVestDamagedMessages", m_Config.ItemVestDamagedMessages, true);
        ST_WriteJsonStringArray(file, "ItemHeadgearDamagedMessages", m_Config.ItemHeadgearDamagedMessages, true);
        ST_WriteJsonStringArray(file, "ItemGlovesDamagedMessages", m_Config.ItemGlovesDamagedMessages, true);
        ST_WriteJsonStringArray(file, "ItemMaskDamagedMessages", m_Config.ItemMaskDamagedMessages, true);
        ST_WriteJsonStringArray(file, "ItemBeltDamagedMessages", m_Config.ItemBeltDamagedMessages, true);
        ST_WriteJsonInt(file, "EnableNearbyCorpseThoughts", m_Config.EnableNearbyCorpseThoughts, true);
        ST_WriteJsonFloat(file, "NearbyCorpseRadius", m_Config.NearbyCorpseRadius, true);
        ST_WriteJsonStringArray(file, "NearbyCorpseMessages", m_Config.NearbyCorpseMessages, true);
        ST_WriteJsonStringArray(file, "NearbyPlayerCorpseMessages", m_Config.NearbyPlayerCorpseMessages, true);
        ST_WriteJsonStringArray(file, "NearbyInfectedCorpseMessages", m_Config.NearbyInfectedCorpseMessages, true);
        ST_WriteJsonStringArray(file, "NearbyAnimalCorpseMessages", m_Config.NearbyAnimalCorpseMessages, false);
        FPrintln(file, "}");
        CloseFile(file);
    }

    void ST_WriteConsolidatedConfig_06_Social_Sanity_Journal(string folderPath)
    {
        if (!m_Config)
            return;

        string filePath = folderPath + "/06_Social_Sanity_Journal.json";
        FileHandle file = OpenFile(filePath, FileMode.WRITE);

        if (!file)
        {
            Log("Failed to write consolidated config: " + filePath);
            return;
        }

        FPrintln(file, "{");
        ST_WriteJsonInt(file, "EnableSocialGroupThoughts", m_Config.EnableSocialGroupThoughts, true);
        ST_WriteJsonFloat(file, "SocialGroupThoughtCooldownSeconds", m_Config.SocialGroupThoughtCooldownSeconds, true);
        ST_WriteJsonFloat(file, "SocialGroupThoughtChance", m_Config.SocialGroupThoughtChance, true);
        ST_WriteJsonFloat(file, "SocialNearbyPlayerRadius", m_Config.SocialNearbyPlayerRadius, true);
        ST_WriteJsonFloat(file, "SocialFriendlyTimeRequiredSeconds", m_Config.SocialFriendlyTimeRequiredSeconds, true);
        ST_WriteJsonFloat(file, "SocialMemoryDurationSeconds", m_Config.SocialMemoryDurationSeconds, true);
        ST_WriteJsonFloat(file, "LoneWolfNoPlayerSeenSeconds", m_Config.LoneWolfNoPlayerSeenSeconds, true);
        ST_WriteJsonInt(file, "EnableTeammateShotMessages", m_Config.EnableTeammateShotMessages, true);
        ST_WriteJsonInt(file, "EnableTeammateDownMessages", m_Config.EnableTeammateDownMessages, true);
        ST_WriteJsonInt(file, "EnableLoneWolfMessages", m_Config.EnableLoneWolfMessages, true);
        ST_WriteJsonInt(file, "EnableFriendlyNearbyMessages", m_Config.EnableFriendlyNearbyMessages, true);
        ST_WriteJsonStringArray(file, "TeammateShotMessages", m_Config.TeammateShotMessages, true);
        ST_WriteJsonStringArray(file, "TeammateDownMessages", m_Config.TeammateDownMessages, true);
        ST_WriteJsonStringArray(file, "LoneWolfMessages", m_Config.LoneWolfMessages, true);
        ST_WriteJsonStringArray(file, "FriendlyNearbyMessages", m_Config.FriendlyNearbyMessages, true);
        ST_WriteJsonInt(file, "EnableStealthNoiseThoughts", m_Config.EnableStealthNoiseThoughts, true);
        ST_WriteJsonFloat(file, "StealthNoiseThoughtCooldownSeconds", m_Config.StealthNoiseThoughtCooldownSeconds, true);
        ST_WriteJsonFloat(file, "StealthNoiseThoughtChance", m_Config.StealthNoiseThoughtChance, true);
        ST_WriteJsonFloat(file, "StealthNoiseInfectedRadius", m_Config.StealthNoiseInfectedRadius, true);
        ST_WriteJsonFloat(file, "StealthNoiseRunSpeedThreshold", m_Config.StealthNoiseRunSpeedThreshold, true);
        ST_WriteJsonStringArray(file, "StealthNoiseInfectedNearbyMessages", m_Config.StealthNoiseInfectedNearbyMessages, true);
        ST_WriteJsonStringArray(file, "StealthNoiseNightMessages", m_Config.StealthNoiseNightMessages, true);
        ST_WriteJsonStringArray(file, "StealthNoiseMilitaryMessages", m_Config.StealthNoiseMilitaryMessages, true);
        ST_WriteJsonInt(file, "EnableSanityCreep", m_Config.EnableSanityCreep, true);
        ST_WriteJsonFloat(file, "SanityThoughtCooldownSeconds", m_Config.SanityThoughtCooldownSeconds, true);
        ST_WriteJsonFloat(file, "SanityThoughtChance", m_Config.SanityThoughtChance, true);
        ST_WriteJsonFloat(file, "StartingSanity", m_Config.StartingSanity, true);
        ST_WriteJsonFloat(file, "MinimumSanity", m_Config.MinimumSanity, true);
        ST_WriteJsonFloat(file, "SanityLossSkinHuman", m_Config.SanityLossSkinHuman, true);
        ST_WriteJsonFloat(file, "SanityLossEatHumanMeat", m_Config.SanityLossEatHumanMeat, true);
        ST_WriteJsonFloat(file, "SanityLossKillRestrainedPlayer", m_Config.SanityLossKillRestrainedPlayer, true);
        ST_WriteJsonFloat(file, "SanityRegenPerMinute", m_Config.SanityRegenPerMinute, true);
        ST_WriteJsonFloat(file, "SanityUneasyThreshold", m_Config.SanityUneasyThreshold, true);
        ST_WriteJsonFloat(file, "SanityUnhingedThreshold", m_Config.SanityUnhingedThreshold, true);
        ST_WriteJsonFloat(file, "SanityPsychoticThreshold", m_Config.SanityPsychoticThreshold, true);
        ST_WriteJsonInt(file, "EnableSanityUneasyMessages", m_Config.EnableSanityUneasyMessages, true);
        ST_WriteJsonInt(file, "EnableSanityUnhingedMessages", m_Config.EnableSanityUnhingedMessages, true);
        ST_WriteJsonInt(file, "EnableSanityPsychoticMessages", m_Config.EnableSanityPsychoticMessages, true);
        ST_WriteJsonInt(file, "EnableCannibalismCreepMessages", m_Config.EnableCannibalismCreepMessages, true);
        ST_WriteJsonStringArray(file, "SanityUneasyMessages", m_Config.SanityUneasyMessages, true);
        ST_WriteJsonStringArray(file, "SanityUnhingedMessages", m_Config.SanityUnhingedMessages, true);
        ST_WriteJsonStringArray(file, "SanityPsychoticMessages", m_Config.SanityPsychoticMessages, true);
        ST_WriteJsonStringArray(file, "CannibalismCreepMessages", m_Config.CannibalismCreepMessages, true);
        ST_WriteJsonInt(file, "EnablePlayerJournals", m_Config.EnablePlayerJournals, true);
        ST_WriteJsonString(file, "PlayerJournalFolder", m_Config.PlayerJournalFolder, true);
        ST_WriteJsonInt(file, "JournalOnlyMajorEvents", m_Config.JournalOnlyMajorEvents, true);
        ST_WriteJsonInt(file, "JournalIncludePlayerStats", m_Config.JournalIncludePlayerStats, true);
        ST_WriteJsonInt(file, "JournalWriteAllRecoveryEvents", m_Config.JournalWriteAllRecoveryEvents, true);
        ST_WriteJsonInt(file, "JournalWriteSanityEvents", m_Config.JournalWriteSanityEvents, true);
        ST_WriteJsonInt(file, "JournalWriteSocialEvents", m_Config.JournalWriteSocialEvents, true);
        ST_WriteJsonInt(file, "JournalWriteNearDeathEvents", m_Config.JournalWriteNearDeathEvents, true);
        ST_WriteJsonInt(file, "EnableSurvivorJournalItem", m_Config.EnableSurvivorJournalItem, true);
        ST_WriteJsonInt(file, "GiveJournalOnFreshSpawn", m_Config.GiveJournalOnFreshSpawn, true);
        ST_WriteJsonInt(file, "DropJournalOnDeath", m_Config.DropJournalOnDeath, true);
        ST_WriteJsonInt(file, "AutoEquipJournalOnFreshSpawn", m_Config.AutoEquipJournalOnFreshSpawn, true);
        ST_WriteJsonInt(file, "AutoEquipJournalOnLoginIfMissing", m_Config.AutoEquipJournalOnLoginIfMissing, true);
        ST_WriteJsonInt(file, "LockJournalToPlayerWhileAlive", m_Config.LockJournalToPlayerWhileAlive, true);
        ST_WriteJsonInt(file, "AllowJournalLootingAfterDeath", m_Config.AllowJournalLootingAfterDeath, true);
        ST_WriteJsonInt(file, "DeleteJournalIfRemovedWhileAlive", m_Config.DeleteJournalIfRemovedWhileAlive, true);
        ST_WriteJsonInt(file, "WriteJournalDeathEntryOnKilled", m_Config.WriteJournalDeathEntryOnKilled, true);
        ST_WriteJsonInt(file, "JournalRequiredBeforeNormalPlay", m_Config.JournalRequiredBeforeNormalPlay, true);
        ST_WriteJsonInt(file, "AllowReadingOtherPlayersJournals", m_Config.AllowReadingOtherPlayersJournals, true);
        ST_WriteJsonInt(file, "RequireJournalSetupMenu", m_Config.RequireJournalSetupMenu, true);
        ST_WriteJsonInt(file, "ShowJournalSetupMenuOnlyOnFreshCharacter", m_Config.ShowJournalSetupMenuOnlyOnFreshCharacter, true);
        ST_WriteJsonInt(file, "AllowJournalSetupSkip", m_Config.AllowJournalSetupSkip, true);
        ST_WriteJsonInt(file, "AllowJournalSetupRandomize", m_Config.AllowJournalSetupRandomize, true);
        ST_WriteJsonString(file, "PlayerBackstoryDataFile", m_Config.PlayerBackstoryDataFile, true);
        ST_WriteJsonInt(file, "MaxMajorJournalEventsStored", m_Config.MaxMajorJournalEventsStored, true);
        ST_WriteJsonInt(file, "JournalBackstoryMinMajorEvents", m_Config.JournalBackstoryMinMajorEvents, true);
        ST_WriteJsonInt(file, "ShowRealPlayerNameInJournal", m_Config.ShowRealPlayerNameInJournal, true);
        ST_WriteJsonInt(file, "PriorityJournalSystem", m_Config.PriorityJournalSystem, true);
        ST_WriteJsonStringArray(file, "JournalCharacterTypeOptions", m_Config.JournalCharacterTypeOptions, true);
        ST_WriteJsonStringArray(file, "JournalHeadTypeOptions", m_Config.JournalHeadTypeOptions, true);
        ST_WriteJsonStringArray(file, "JournalOriginOptions", m_Config.JournalOriginOptions, true);
        ST_WriteJsonStringArray(file, "JournalOccupationOptions", m_Config.JournalOccupationOptions, true);
        ST_WriteJsonStringArray(file, "JournalTraitOptions", m_Config.JournalTraitOptions, true);
        ST_WriteJsonStringArray(file, "JournalFearOptions", m_Config.JournalFearOptions, true);
        ST_WriteJsonStringArray(file, "JournalGoalOptions", m_Config.JournalGoalOptions, true);
        ST_WriteJsonStringArray(file, "JournalBackstoryTemplates", m_Config.JournalBackstoryTemplates, true);
        ST_WriteJsonInt(file, "EnableJournalSetupSpawnProtection", m_Config.EnableJournalSetupSpawnProtection, true);
        ST_WriteJsonInt(file, "JournalSetupBlockDamageUntilComplete", m_Config.JournalSetupBlockDamageUntilComplete, true);
        ST_WriteJsonInt(file, "JournalSetupSuppressThoughtsUntilComplete", m_Config.JournalSetupSuppressThoughtsUntilComplete, true);
        ST_WriteJsonInt(file, "JournalSetupProtectionDebug", m_Config.JournalSetupProtectionDebug, true);
        ST_WriteJsonInt(file, "JournalSetupRestoreStatsWhileActive", m_Config.JournalSetupRestoreStatsWhileActive, true);
        ST_WriteJsonFloat(file, "JournalSetupProtectedHealthValue", m_Config.JournalSetupProtectedHealthValue, true);
        ST_WriteJsonFloat(file, "JournalSetupProtectedBloodValue", m_Config.JournalSetupProtectedBloodValue, true);
        ST_WriteJsonFloat(file, "JournalSetupProtectedShockValue", m_Config.JournalSetupProtectedShockValue, true);
        ST_WriteJsonFloat(file, "JournalSetupProtectedEnergyValue", m_Config.JournalSetupProtectedEnergyValue, true);
        ST_WriteJsonFloat(file, "JournalSetupProtectedWaterValue", m_Config.JournalSetupProtectedWaterValue, true);
        ST_WriteJsonFloat(file, "JournalSetupProtectedHeatComfortValue", m_Config.JournalSetupProtectedHeatComfortValue, true);
        ST_WriteJsonStringArray(file, "JournalSkillOptions", m_Config.JournalSkillOptions, true);
        ST_WriteJsonStringArray(file, "JournalWeaknessOptions", m_Config.JournalWeaknessOptions, true);
        ST_WriteJsonStringArray(file, "JournalMoralCodeOptions", m_Config.JournalMoralCodeOptions, true);
        ST_WriteJsonStringArray(file, "JournalSurvivalInstinctOptions", m_Config.JournalSurvivalInstinctOptions, true);
        ST_WriteJsonStringArray(file, "JournalKeepsakeOptions", m_Config.JournalKeepsakeOptions, true);
        ST_WriteJsonInt(file, "EnableJournalSystemIntegration", m_Config.EnableJournalSystemIntegration, true);
        ST_WriteJsonInt(file, "JournalRecordAllThoughtSystems", m_Config.JournalRecordAllThoughtSystems, true);
        ST_WriteJsonInt(file, "JournalRecordAmbientSystems", m_Config.JournalRecordAmbientSystems, true);
        ST_WriteJsonInt(file, "JournalRecordBlockedDecisionEvents", m_Config.JournalRecordBlockedDecisionEvents, true);
        ST_WriteJsonInt(file, "JournalMajorEventMinPriority", m_Config.JournalMajorEventMinPriority, true);
        ST_WriteJsonInt(file, "JournalMajorEventPrefixWithSystem", m_Config.JournalMajorEventPrefixWithSystem, true);
        ST_WriteJsonInt(file, "JournalMajorEventIncludeStats", m_Config.JournalMajorEventIncludeStats, true);
        ST_WriteJsonInt(file, "JournalRecordDeathEntries", m_Config.JournalRecordDeathEntries, true);
        ST_WriteJsonInt(file, "JournalRecordSetupChoices", m_Config.JournalRecordSetupChoices, true);
        ST_WriteJsonInt(file, "JournalRecordSystemLinkDebug", m_Config.JournalRecordSystemLinkDebug, false);
        FPrintln(file, "}");
        CloseFile(file);
    }

    void ST_WriteConsolidatedConfig_07_Admin_Diagnostics(string folderPath)
    {
        if (!m_Config)
            return;

        string filePath = folderPath + "/07_Admin_Diagnostics.json";
        FileHandle file = OpenFile(filePath, FileMode.WRITE);

        if (!file)
        {
            Log("Failed to write consolidated config: " + filePath);
            return;
        }

        FPrintln(file, "{");
        ST_WriteJsonInt(file, "EnableThoughtDecisionTrace", m_Config.EnableThoughtDecisionTrace, true);
        ST_WriteJsonInt(file, "TraceOnlyBlockedThoughts", m_Config.TraceOnlyBlockedThoughts, true);
        ST_WriteJsonInt(file, "TraceToDebugLog", m_Config.TraceToDebugLog, true);
        ST_WriteJsonInt(file, "TraceToMissionStorage", m_Config.TraceToMissionStorage, true);
        ST_WriteJsonString(file, "DecisionTraceFolder", m_Config.DecisionTraceFolder, true);
        ST_WriteJsonInt(file, "EnableAdminAnalytics", m_Config.EnableAdminAnalytics, true);
        ST_WriteJsonFloat(file, "AnalyticsSaveIntervalSeconds", m_Config.AnalyticsSaveIntervalSeconds, true);
        ST_WriteJsonString(file, "AnalyticsFolder", m_Config.AnalyticsFolder, true);
        ST_WriteJsonInt(file, "EnableAnalyticsJsonLines", m_Config.EnableAnalyticsJsonLines, true);
        ST_WriteJsonString(file, "AnalyticsJsonLineFile", m_Config.AnalyticsJsonLineFile, true);
        ST_WriteJsonInt(file, "TrackBlockedByPriority", m_Config.TrackBlockedByPriority, true);
        ST_WriteJsonInt(file, "TrackBlockedByDuplicate", m_Config.TrackBlockedByDuplicate, true);
        ST_WriteJsonInt(file, "TrackThoughtTypes", m_Config.TrackThoughtTypes, true);
        ST_WriteJsonInt(file, "TrackRecoveryEvents", m_Config.TrackRecoveryEvents, true);
        ST_WriteJsonInt(file, "TrackSanityEvents", m_Config.TrackSanityEvents, true);
        ST_WriteJsonInt(file, "TrackSocialEvents", m_Config.TrackSocialEvents, true);
        ST_WriteJsonInt(file, "TrackStateHistoryEvents", m_Config.TrackStateHistoryEvents, false);
        FPrintln(file, "}");
        CloseFile(file);
    }

void ST_CreateDefault_00_Core_Admin_Output_json(string folderPath)
    {
        string filePath = folderPath + "/00_Core_Admin_Output.json";
        if (FileExist(filePath))
            return;

        array<string> lines = new array<string>;
        lines.Insert("{");
        lines.Insert("    \"ConfigVersion\": 57,");
        lines.Insert("    \"EnableMod\": 1,");
        lines.Insert("    \"DebugMode\": 0,");
        lines.Insert("    \"GlobalCooldownSeconds\": 120.0,");
        lines.Insert("    \"MinimumRandomDelaySeconds\": 45.0,");
        lines.Insert("    \"MaximumRandomDelaySeconds\": 180.0,");
        lines.Insert("    \"ShowHealthyMessages\": 0,");
        lines.Insert("    \"EnableHungerMessages\": 1,");
        lines.Insert("    \"EnableThirstMessages\": 1,");
        lines.Insert("    \"EnableColdMessages\": 1,");
        lines.Insert("    \"EnableHotMessages\": 1,");
        lines.Insert("    \"EnableSicknessMessages\": 1,");
        lines.Insert("    \"EnableBleedingMessages\": 1,");
        lines.Insert("    \"EnableBrokenLegMessages\": 1,");
        lines.Insert("    \"EnableInfectedNearbyMessages\": 1,");
        lines.Insert("    \"InfectedFarRadius\": 40.0,");
        lines.Insert("    \"InfectedCloseRadius\": 25.0,");
        lines.Insert("    \"InfectedVeryCloseRadius\": 10.0,");
        lines.Insert("    \"InfectedSurroundedCount\": 4,");
        lines.Insert("    \"EnableDebugFileLog\": 1,");
        lines.Insert("    \"DebugLogToRPT\": 1,");
        lines.Insert("    \"DebugLogFileName\": \"SurvivorThoughts_Debug.log\",");
        lines.Insert("    \"ClearDebugLogOnServerStart\": 1,");
        lines.Insert("    \"UseLocalChatBox\": 1,");
        lines.Insert("    \"UseNotificationSystem\": 0,");
        lines.Insert("    \"EnableMissionStoragePersistentData\": 1,");
        lines.Insert("    \"PersistentStorageRoot\": \"$mission:storage_1/ZombiCideMods/SurvivorThoughts\",");
        lines.Insert("    \"PersistentDataFolderName\": \"Data\",");
        lines.Insert("    \"PersistentStateDataFile\": \"$mission:storage_1/ZombiCideMods/SurvivorThoughts/Data/PlayerPersistentStates.json\",");
        lines.Insert("    \"PersonalityDataFile\": \"$mission:storage_1/ZombiCideMods/SurvivorThoughts/Data/PlayerPersonalities.json\",");
        lines.Insert("    \"PersistentAutosaveSeconds\": 60.0,");
        lines.Insert("    \"PrioritySocialGroup\": 65,");
        lines.Insert("    \"PrioritySanityCreep\": 70,");
        lines.Insert("    \"PriorityStateHistory\": 50,");
        lines.Insert("    \"PriorityRecovery\": 55,");
        lines.Insert("    \"PriorityAdvancedCombined\": 85,");
        lines.Insert("    \"PriorityNearMissCombat\": 80,");
        lines.Insert("    \"PriorityDiseaseSpecific\": 70,");
        lines.Insert("    \"PriorityMapEnvironment\": 18,");
        lines.Insert("    \"EnableRecentMessageBlocker\": 1,");
        lines.Insert("    \"RecentMessageMemoryCount\": 12,");
        lines.Insert("    \"RecentMessageBlockSeconds\": 900.0,");
        lines.Insert("    \"EnableAdminReload\": 1,");
        lines.Insert("    \"AdminReloadCommand\": \"!streload\",");
        lines.Insert("    \"AdminSteamIds\": [");
        lines.Insert("        \"76561198000000000\"");
        lines.Insert("    ]");
        lines.Insert("}");

        ST_WriteDefaultJsonFile(filePath, lines);
        Log("Created default consolidated config: " + filePath);
    }

    void ST_CreateDefault_01_Player_State_Personality_json(string folderPath)
    {
        string filePath = folderPath + "/01_Player_State_Personality.json";
        if (FileExist(filePath))
            return;

        array<string> lines = new array<string>;
        lines.Insert("{");
        lines.Insert("    \"EnableConfigurableStatThresholds\": 1,");
        lines.Insert("    \"EnableEnergyStage1Messages\": 0,");
        lines.Insert("    \"EnergyStage1_Min\": 4000.0,");
        lines.Insert("    \"EnergyStage1_Max\": 5000.0,");
        lines.Insert("    \"EnableEnergyStage2Messages\": 1,");
        lines.Insert("    \"EnergyStage2_Min\": 3000.0,");
        lines.Insert("    \"EnergyStage2_Max\": 3999.0,");
        lines.Insert("    \"EnableEnergyStage3Messages\": 1,");
        lines.Insert("    \"EnergyStage3_Min\": 1000.0,");
        lines.Insert("    \"EnergyStage3_Max\": 2999.0,");
        lines.Insert("    \"EnableEnergyStage4Messages\": 1,");
        lines.Insert("    \"EnergyStage4_Min\": 0.0,");
        lines.Insert("    \"EnergyStage4_Max\": 999.0,");
        lines.Insert("    \"EnableWaterStage1Messages\": 0,");
        lines.Insert("    \"WaterStage1_Min\": 4000.0,");
        lines.Insert("    \"WaterStage1_Max\": 5000.0,");
        lines.Insert("    \"EnableWaterStage2Messages\": 1,");
        lines.Insert("    \"WaterStage2_Min\": 3000.0,");
        lines.Insert("    \"WaterStage2_Max\": 3999.0,");
        lines.Insert("    \"EnableWaterStage3Messages\": 1,");
        lines.Insert("    \"WaterStage3_Min\": 1000.0,");
        lines.Insert("    \"WaterStage3_Max\": 2999.0,");
        lines.Insert("    \"EnableWaterStage4Messages\": 1,");
        lines.Insert("    \"WaterStage4_Min\": 0.0,");
        lines.Insert("    \"WaterStage4_Max\": 999.0,");
        lines.Insert("    \"EnableBloodStage1Messages\": 0,");
        lines.Insert("    \"BloodStage1_Min\": 4500.0,");
        lines.Insert("    \"BloodStage1_Max\": 5000.0,");
        lines.Insert("    \"EnableBloodStage2Messages\": 1,");
        lines.Insert("    \"BloodStage2_Min\": 3500.0,");
        lines.Insert("    \"BloodStage2_Max\": 4499.0,");
        lines.Insert("    \"EnableBloodStage3Messages\": 1,");
        lines.Insert("    \"BloodStage3_Min\": 2500.0,");
        lines.Insert("    \"BloodStage3_Max\": 3499.0,");
        lines.Insert("    \"EnableBloodStage4Messages\": 1,");
        lines.Insert("    \"BloodStage4_Min\": 0.0,");
        lines.Insert("    \"BloodStage4_Max\": 2499.0,");
        lines.Insert("    \"EnableShockStage1Messages\": 0,");
        lines.Insert("    \"ShockStage1_Min\": 75.0,");
        lines.Insert("    \"ShockStage1_Max\": 100.0,");
        lines.Insert("    \"EnableShockStage2Messages\": 1,");
        lines.Insert("    \"ShockStage2_Min\": 50.0,");
        lines.Insert("    \"ShockStage2_Max\": 74.0,");
        lines.Insert("    \"EnableShockStage3Messages\": 1,");
        lines.Insert("    \"ShockStage3_Min\": 25.0,");
        lines.Insert("    \"ShockStage3_Max\": 49.0,");
        lines.Insert("    \"EnableShockStage4Messages\": 1,");
        lines.Insert("    \"ShockStage4_Min\": 0.0,");
        lines.Insert("    \"ShockStage4_Max\": 24.0,");
        lines.Insert("    \"EnableDeathSpiralThoughts\": 1,");
        lines.Insert("    \"HealthDropMinAmount\": 0.1,");
        lines.Insert("    \"HealthDropRecentSeconds\": 90.0,");
        lines.Insert("    \"DeathSpiralColdComfort_Max\": -0.75,");
        lines.Insert("    \"DeathSpiralHotComfort_Min\": 0.75,");
        lines.Insert("    \"EnableStarvingToDeathMessages\": 1,");
        lines.Insert("    \"EnableDehydratingToDeathMessages\": 1,");
        lines.Insert("    \"EnableFreezingToDeathMessages\": 1,");
        lines.Insert("    \"EnableOverheatingToDeathMessages\": 1,");
        lines.Insert("    \"EnablePlayerStateHistory\": 1,");
        lines.Insert("    \"StateHistorySampleIntervalSeconds\": 30.0,");
        lines.Insert("    \"StateHistoryWindowSeconds\": 900.0,");
        lines.Insert("    \"TrendChangeThreshold\": 0.1,");
        lines.Insert("    \"EnableTrendMessages\": 1,");
        lines.Insert("    \"EnableStateSnapshots\": 0,");
        lines.Insert("    \"StateSnapshotIntervalSeconds\": 300.0,");
        lines.Insert("    \"EnablePersistentStateSnapshots\": 0,");
        lines.Insert("    \"StateSnapshotFolder\": \"$mission:storage_1/ZombiCideMods/SurvivorThoughts/Debug/PlayerStateSnapshots\",");
        lines.Insert("    \"TrendEnergyFallingMessages\": [");
        lines.Insert("        \"I am burning through what little energy I have left.\",");
        lines.Insert("        \"The hunger is getting worse, not better.\",");
        lines.Insert("        \"My body is running out of fuel.\",");
        lines.Insert("        \"Every step costs more than I can afford.\"");
        lines.Insert("    ],");
        lines.Insert("    \"TrendWaterFallingMessages\": [");
        lines.Insert("        \"My mouth is only getting drier.\",");
        lines.Insert("        \"The thirst is catching up with me.\",");
        lines.Insert("        \"I am losing water faster than I can replace it.\",");
        lines.Insert("        \"I need fluids before this gets worse.\"");
        lines.Insert("    ],");
        lines.Insert("    \"TrendBloodFallingMessages\": [");
        lines.Insert("        \"My blood is still dropping.\",");
        lines.Insert("        \"I am not replacing what I am losing.\",");
        lines.Insert("        \"The weakness is spreading through me.\",");
        lines.Insert("        \"I need to stop this blood loss.\"");
        lines.Insert("    ],");
        lines.Insert("    \"TrendHealthFallingMessages\": [");
        lines.Insert("        \"My condition is getting worse.\",");
        lines.Insert("        \"I am slipping, slowly but surely.\",");
        lines.Insert("        \"Whatever is happening, it is taking me down.\",");
        lines.Insert("        \"I need to stabilize before I collapse.\"");
        lines.Insert("    ],");
        lines.Insert("    \"TrendTemperatureWorseningMessages\": [");
        lines.Insert("        \"My temperature is moving the wrong way.\",");
        lines.Insert("        \"This exposure is getting worse.\",");
        lines.Insert("        \"My body cannot keep up with the weather.\",");
        lines.Insert("        \"I need shelter before this turns critical.\"");
        lines.Insert("    ],");
        lines.Insert("    \"TrendWetnessWorseningMessages\": [");
        lines.Insert("        \"Everything is getting soaked.\",");
        lines.Insert("        \"The wet is working its way through my clothes.\",");
        lines.Insert("        \"I need to dry out before the cold finds me.\",");
        lines.Insert("        \"This damp is going to become a problem.\"");
        lines.Insert("    ],");
        lines.Insert("    \"LongSicknessMessages\": [");
        lines.Insert("        \"I have been sick for too long.\",");
        lines.Insert("        \"The fever is not breaking.\",");
        lines.Insert("        \"This illness is wearing me down.\",");
        lines.Insert("        \"I need proper treatment before this settles in.\"");
        lines.Insert("    ],");
        lines.Insert("    \"LongBleedingMessages\": [");
        lines.Insert("        \"I have been bleeding too long.\",");
        lines.Insert("        \"This wound is taking more from me than I thought.\",");
        lines.Insert("        \"The bleeding needs to stop now.\",");
        lines.Insert("        \"I cannot keep leaking blood like this.\"");
        lines.Insert("    ],");
        lines.Insert("    \"EnableProlongedStateMessages\": 1,");
        lines.Insert("    \"ProlongedStateThresholdSeconds\": 600.0,");
        lines.Insert("    \"ProlongedStarvationMessages\": [");
        lines.Insert("        \"I have been starving too long. My body is starting to give up.\",");
        lines.Insert("        \"This hunger is not a warning anymore. It is damage.\",");
        lines.Insert("        \"Every minute without food is taking something permanent from me.\",");
        lines.Insert("        \"I cannot keep moving on nothing.\",");
        lines.Insert("        \"The weakness is settling deep now.\",");
        lines.Insert("        \"Food is no longer comfort. It is survival.\"");
        lines.Insert("    ],");
        lines.Insert("    \"ProlongedDehydrationMessages\": [");
        lines.Insert("        \"I have been dry for too long. My thoughts are slowing down.\",");
        lines.Insert("        \"My body is begging for water now.\",");
        lines.Insert("        \"This thirst is turning into panic.\",");
        lines.Insert("        \"My mouth feels like dust.\",");
        lines.Insert("        \"I need water before my legs stop listening.\",");
        lines.Insert("        \"Dehydration is killing me quietly.\"");
        lines.Insert("    ],");
        lines.Insert("    \"ProlongedColdMessages\": [");
        lines.Insert("        \"The cold has been inside me too long.\",");
        lines.Insert("        \"I am not just cold anymore. I am fading.\",");
        lines.Insert("        \"My fingers feel distant, like they belong to someone else.\",");
        lines.Insert("        \"If I do not get warm soon, I may not get warm at all.\",");
        lines.Insert("        \"The shivering is taking all the strength I have left.\",");
        lines.Insert("        \"This cold is grinding me down minute by minute.\"");
        lines.Insert("    ],");
        lines.Insert("    \"ProlongedHeatMessages\": [");
        lines.Insert("        \"The heat has been pressing on me for too long.\",");
        lines.Insert("        \"I can feel myself overheating from the inside.\",");
        lines.Insert("        \"My head is thick from the heat.\",");
        lines.Insert("        \"I need shade or water before this gets worse.\",");
        lines.Insert("        \"The air feels too hot to breathe.\",");
        lines.Insert("        \"This heat is starting to feel dangerous.\"");
        lines.Insert("    ],");
        lines.Insert("    \"ProlongedBleedingMessages\": [");
        lines.Insert("        \"I have been bleeding too long.\",");
        lines.Insert("        \"This blood loss is catching up with me.\",");
        lines.Insert("        \"Every step leaves more of me behind.\",");
        lines.Insert("        \"I need pressure on the wound now.\",");
        lines.Insert("        \"The bleeding has gone from bad to critical.\",");
        lines.Insert("        \"I cannot ignore this wound any longer.\"");
        lines.Insert("    ],");
        lines.Insert("    \"ProlongedSicknessMessages\": [");
        lines.Insert("        \"I have been sick too long.\",");
        lines.Insert("        \"The illness is settling in.\",");
        lines.Insert("        \"This is not passing on its own.\",");
        lines.Insert("        \"My body is losing the argument.\",");
        lines.Insert("        \"The fever keeps coming back.\",");
        lines.Insert("        \"I need medicine before this becomes permanent.\"");
        lines.Insert("    ],");
        lines.Insert("    \"EnablePersonalityProfiles\": 1,");
        lines.Insert("    \"PersonalityThoughtChance\": 0.2,");
        lines.Insert("    \"PersonalityPersistBySteamId\": 1,");
        lines.Insert("    \"PersonalityDataFile\": \"$profile:SurvivorThoughts/Data/PlayerPersonalities.json\",");
        lines.Insert("    \"EnablePersonalityChangeOverTime\": 1,");
        lines.Insert("    \"PersonalityChangeChance\": 0.08,");
        lines.Insert("    \"PersonalityMinimumSecondsBetweenChanges\": 7200.0,");
        lines.Insert("    \"PersonalityPracticalMessages\": [");
        lines.Insert("        \"Priorities first. Water, food, shelter.\",");
        lines.Insert("        \"Check supplies, check exits, keep moving.\",");
        lines.Insert("        \"Do not waste energy.\",");
        lines.Insert("        \"Solve the worst problem first.\",");
        lines.Insert("        \"Inventory, route, risk. In that order.\",");
        lines.Insert("        \"If it cannot help me survive, leave it.\",");
        lines.Insert("        \"Stay quiet and make decisions.\",");
        lines.Insert("        \"One useful item is better than three useless ones.\"");
        lines.Insert("    ],");
        lines.Insert("    \"PersonalityScaredMessages\": [");
        lines.Insert("        \"I hate this place.\",");
        lines.Insert("        \"Every sound feels too close.\",");
        lines.Insert("        \"I do not want to die here.\",");
        lines.Insert("        \"Something is always moving out there.\",");
        lines.Insert("        \"I need to get away from this area.\",");
        lines.Insert("        \"My hands will not stop shaking.\",");
        lines.Insert("        \"This silence feels wrong.\",");
        lines.Insert("        \"I should not be alone out here.\"");
        lines.Insert("    ],");
        lines.Insert("    \"PersonalityMilitaryMessages\": [");
        lines.Insert("        \"Assess the area. Move with purpose.\",");
        lines.Insert("        \"Cover first, then supplies.\",");
        lines.Insert("        \"Noise discipline. Always.\",");
        lines.Insert("        \"Check angles before crossing.\",");
        lines.Insert("        \"Do not skyline yourself.\",");
        lines.Insert("        \"Keep the weapon ready and the route clear.\",");
        lines.Insert("        \"Threats first, comfort second.\",");
        lines.Insert("        \"Plan the exit before entering.\"");
        lines.Insert("    ],");
        lines.Insert("    \"PersonalityHopelessMessages\": [");
        lines.Insert("        \"It never gets easier.\",");
        lines.Insert("        \"Nobody is coming.\",");
        lines.Insert("        \"This place takes everything eventually.\",");
        lines.Insert("        \"Every day feels borrowed.\",");
        lines.Insert("        \"I do not know how much more I have left.\",");
        lines.Insert("        \"The world ended, but the suffering did not.\",");
        lines.Insert("        \"Surviving is starting to feel like habit.\",");
        lines.Insert("        \"There is always another problem.\"");
        lines.Insert("    ],");
        lines.Insert("    \"PersonalityAggressiveMessages\": [");
        lines.Insert("        \"Keep moving. Take what you need.\",");
        lines.Insert("        \"Fear gets people killed.\",");
        lines.Insert("        \"If someone is nearby, be ready.\",");
        lines.Insert("        \"Do not hesitate if it turns bad.\",");
        lines.Insert("        \"This world rewards the faster hand.\",");
        lines.Insert("        \"Weakness invites trouble.\",");
        lines.Insert("        \"Push through it.\",");
        lines.Insert("        \"Survive first, regret later.\"");
        lines.Insert("    ],");
        lines.Insert("    \"PersonalityCalmMessages\": [");
        lines.Insert("        \"Breathe. Think. Move.\",");
        lines.Insert("        \"One problem at a time.\",");
        lines.Insert("        \"Panic wastes strength.\",");
        lines.Insert("        \"Slow is smooth. Smooth is alive.\",");
        lines.Insert("        \"Listen before moving.\",");
        lines.Insert("        \"Do what needs doing.\",");
        lines.Insert("        \"Stay calm and keep control.\",");
        lines.Insert("        \"There is still a way through this.\"");
        lines.Insert("    ],");
        lines.Insert("    \"EnableMentalStateThoughts\": 1,");
        lines.Insert("    \"MentalStateThoughtCooldownSeconds\": 300.0,");
        lines.Insert("    \"MentalStateThoughtChance\": 0.25,");
        lines.Insert("    \"MentalStateCriticalHealthMax\": 30.0,");
        lines.Insert("    \"MentalStateLowBloodMax\": 3500.0,");
        lines.Insert("    \"MentalStateLowFoodMax\": 500.0,");
        lines.Insert("    \"MentalStateLowWaterMax\": 500.0,");
        lines.Insert("    \"MentalStateStableMessages\": [");
        lines.Insert("        \"Keep priorities simple. Water, food, shelter.\",");
        lines.Insert("        \"Think clearly. Waste nothing.\",");
        lines.Insert("        \"I can handle this if I stay methodical.\",");
        lines.Insert("        \"One good decision after another.\"");
        lines.Insert("    ],");
        lines.Insert("    \"MentalStateUneasyMessages\": [");
        lines.Insert("        \"Something feels wrong.\",");
        lines.Insert("        \"I cannot shake the feeling that I am being watched.\",");
        lines.Insert("        \"I need to slow down and listen.\",");
        lines.Insert("        \"This place is getting under my skin.\"");
        lines.Insert("    ],");
        lines.Insert("    \"MentalStateAfraidMessages\": [");
        lines.Insert("        \"Do not panic. Panic wastes energy.\",");
        lines.Insert("        \"I hate how close everything sounds.\",");
        lines.Insert("        \"Fear is useful if it keeps me careful.\",");
        lines.Insert("        \"I need to breathe and keep moving.\"");
        lines.Insert("    ],");
        lines.Insert("    \"MentalStateDesperateMessages\": [");
        lines.Insert("        \"I am running out of choices.\",");
        lines.Insert("        \"Anything useful matters now.\",");
        lines.Insert("        \"I need supplies before I need a plan.\",");
        lines.Insert("        \"Desperation makes people loud. I need to stay smart.\"");
        lines.Insert("    ],");
        lines.Insert("    \"MentalStateNumbMessages\": [");
        lines.Insert("        \"I do not feel much anymore.\",");
        lines.Insert("        \"Maybe numb is better than scared.\",");
        lines.Insert("        \"Keep moving. Feeling can come later.\",");
        lines.Insert("        \"This place takes pieces from everyone.\"");
        lines.Insert("    ],");
        lines.Insert("    \"MentalStateAggressiveMessages\": [");
        lines.Insert("        \"If someone pushes me now, they will regret it.\",");
        lines.Insert("        \"I am tired of being hunted.\",");
        lines.Insert("        \"No more hesitation.\",");
        lines.Insert("        \"Threats need to be dealt with before they grow.\"");
        lines.Insert("    ],");
        lines.Insert("    \"MentalStateBrokenMessages\": [");
        lines.Insert("        \"I do not know how much longer I can keep doing this.\",");
        lines.Insert("        \"Everything hurts. Everything is heavy.\",");
        lines.Insert("        \"I need one reason to keep moving.\",");
        lines.Insert("        \"The world is getting smaller with every step.\"");
        lines.Insert("    ],");
        lines.Insert("    \"MentalStateFocusedMessages\": [");
        lines.Insert("        \"Focus. Check corners. Check supplies. Move.\",");
        lines.Insert("        \"Noise, cover, exits. Nothing else matters.\",");
        lines.Insert("        \"Stay sharp and stay alive.\",");
        lines.Insert("        \"I need to solve the next problem, not all of them.\"");
        lines.Insert("    ],");
        lines.Insert("    \"EnablePlayerMemoryThoughts\": 1,");
        lines.Insert("    \"PlayerMemoryThoughtCooldownSeconds\": 240.0,");
        lines.Insert("    \"PlayerMemoryThoughtChance\": 0.3,");
        lines.Insert("    \"PlayerMemoryDurationSeconds\": 600.0,");
        lines.Insert("    \"PlayerMemoryRecentDamageMessages\": [");
        lines.Insert("        \"That hit is still on my mind.\",");
        lines.Insert("        \"I need to keep moving after that.\",");
        lines.Insert("        \"Pain makes every decision slower.\",");
        lines.Insert("        \"I should not let that happen again.\"");
        lines.Insert("    ],");
        lines.Insert("    \"PlayerMemoryRecentBleedingMessages\": [");
        lines.Insert("        \"I can still feel where I was bleeding.\",");
        lines.Insert("        \"That wound could have ended me.\",");
        lines.Insert("        \"I need to check myself before moving on.\",");
        lines.Insert("        \"Blood loss changes how everything feels.\"");
        lines.Insert("    ],");
        lines.Insert("    \"PlayerMemoryRecentGunshotMessages\": [");
        lines.Insert("        \"That gunshot is still ringing in my head.\",");
        lines.Insert("        \"Someone with a gun changes everything.\",");
        lines.Insert("        \"I need cover before confidence.\",");
        lines.Insert("        \"One shot was enough warning.\"");
        lines.Insert("    ],");
        lines.Insert("    \"PlayerMemoryRecentCorpseMessages\": [");
        lines.Insert("        \"That body was a warning.\",");
        lines.Insert("        \"Someone died close by. I should not ignore that.\",");
        lines.Insert("        \"Bodies draw questions, flies, and people.\",");
        lines.Insert("        \"I need to leave before I become part of the scene.\"");
        lines.Insert("    ],");
        lines.Insert("    \"PlayerMemoryRecentMilitaryMessages\": [");
        lines.Insert("        \"Military places bring armed survivors.\",");
        lines.Insert("        \"Good loot is never free.\",");
        lines.Insert("        \"I should assume someone watched this place before me.\",");
        lines.Insert("        \"The risk here follows me even after I leave.\"");
        lines.Insert("    ],");
        lines.Insert("    \"PlayerMemoryRecentSurvivalCrisisMessages\": [");
        lines.Insert("        \"I came too close to dying.\",");
        lines.Insert("        \"My body needs a break before it gives up.\",");
        lines.Insert("        \"I need food, water, warmth, and time.\",");
        lines.Insert("        \"Survival is getting narrower.\"");
        lines.Insert("    ]");
        lines.Insert("}");

        ST_WriteDefaultJsonFile(filePath, lines);
        Log("Created default consolidated config: " + filePath);
    }

    void ST_CreateDefault_02_Messages_Survival_json(string folderPath)
    {
        string filePath = folderPath + "/02_Messages_Survival.json";
        if (FileExist(filePath))
            return;

        array<string> lines = new array<string>;
        lines.Insert("{");
        lines.Insert("    \"EnergyStage1Messages\": [");
        lines.Insert("        \"I feel fed for now.\",");
        lines.Insert("        \"My stomach is settled.\",");
        lines.Insert("        \"I can keep moving for a while.\",");
        lines.Insert("        \"Food is not a problem right now.\"");
        lines.Insert("    ],");
        lines.Insert("    \"EnergyStage2Messages\": [");
        lines.Insert("        \"I could use something to eat.\",");
        lines.Insert("        \"My stomach is starting to feel empty.\",");
        lines.Insert("        \"I should keep an eye out for food.\",");
        lines.Insert("        \"A small meal would help.\"");
        lines.Insert("    ],");
        lines.Insert("    \"EnergyStage3Messages\": [");
        lines.Insert("        \"I need food soon.\",");
        lines.Insert("        \"My strength is starting to fade.\",");
        lines.Insert("        \"Every step feels heavier without food.\",");
        lines.Insert("        \"I keep thinking about food.\"");
        lines.Insert("    ],");
        lines.Insert("    \"EnergyStage4Messages\": [");
        lines.Insert("        \"I am starving.\",");
        lines.Insert("        \"My body feels weak.\",");
        lines.Insert("        \"I need food now.\",");
        lines.Insert("        \"I do not know how much longer I can go without eating.\"");
        lines.Insert("    ],");
        lines.Insert("    \"WaterStage1Messages\": [");
        lines.Insert("        \"I feel hydrated.\",");
        lines.Insert("        \"My mouth feels fine.\",");
        lines.Insert("        \"Water is not an issue right now.\",");
        lines.Insert("        \"I can travel without worrying about thirst.\"");
        lines.Insert("    ],");
        lines.Insert("    \"WaterStage2Messages\": [");
        lines.Insert("        \"My mouth is getting dry.\",");
        lines.Insert("        \"I should drink soon.\",");
        lines.Insert("        \"I need to remember the next water source.\",");
        lines.Insert("        \"I could use some water.\"");
        lines.Insert("    ],");
        lines.Insert("    \"WaterStage3Messages\": [");
        lines.Insert("        \"My throat is dry.\",");
        lines.Insert("        \"I need water soon.\",");
        lines.Insert("        \"My head is starting to ache.\",");
        lines.Insert("        \"I should not ignore this thirst.\"");
        lines.Insert("    ],");
        lines.Insert("    \"WaterStage4Messages\": [");
        lines.Insert("        \"I am dehydrated.\",");
        lines.Insert("        \"My mouth feels like sand.\",");
        lines.Insert("        \"I need water now.\",");
        lines.Insert("        \"I feel faint from thirst.\"");
        lines.Insert("    ],");
        lines.Insert("    \"BloodStage1Messages\": [");
        lines.Insert("        \"I feel steady for now.\",");
        lines.Insert("        \"My blood feels strong enough.\",");
        lines.Insert("        \"I can keep moving.\",");
        lines.Insert("        \"I have not lost enough blood to slow me yet.\"");
        lines.Insert("    ],");
        lines.Insert("    \"BloodStage2Messages\": [");
        lines.Insert("        \"I feel a little light-headed.\",");
        lines.Insert("        \"I should avoid losing any more blood.\",");
        lines.Insert("        \"That blood loss is starting to show.\",");
        lines.Insert("        \"I need to take it easy for a moment.\"");
        lines.Insert("    ],");
        lines.Insert("    \"BloodStage3Messages\": [");
        lines.Insert("        \"My head is swimming.\",");
        lines.Insert("        \"The blood loss is slowing me down.\",");
        lines.Insert("        \"I need to recover before pushing further.\",");
        lines.Insert("        \"My vision is not right.\"");
        lines.Insert("    ],");
        lines.Insert("    \"BloodStage4Messages\": [");
        lines.Insert("        \"I have lost too much blood.\",");
        lines.Insert("        \"My vision keeps fading.\",");
        lines.Insert("        \"I feel like I am going to pass out.\",");
        lines.Insert("        \"I need help before I black out.\"");
        lines.Insert("    ],");
        lines.Insert("    \"ShockStage1Messages\": [");
        lines.Insert("        \"I feel alert enough.\",");
        lines.Insert("        \"My nerves are steady.\",");
        lines.Insert("        \"I can keep myself together.\",");
        lines.Insert("        \"I can still focus.\"");
        lines.Insert("    ],");
        lines.Insert("    \"ShockStage2Messages\": [");
        lines.Insert("        \"That shook me.\",");
        lines.Insert("        \"My hands are not steady.\",");
        lines.Insert("        \"I need a second to focus.\",");
        lines.Insert("        \"My body is still reacting.\"");
        lines.Insert("    ],");
        lines.Insert("    \"ShockStage3Messages\": [");
        lines.Insert("        \"I feel stunned.\",");
        lines.Insert("        \"My body is struggling to respond.\",");
        lines.Insert("        \"I need cover.\",");
        lines.Insert("        \"Everything feels slow.\"");
        lines.Insert("    ],");
        lines.Insert("    \"ShockStage4Messages\": [");
        lines.Insert("        \"Everything is fading.\",");
        lines.Insert("        \"I am about to black out.\",");
        lines.Insert("        \"I cannot stay conscious much longer.\",");
        lines.Insert("        \"I need to get down before I collapse.\"");
        lines.Insert("    ],");
        lines.Insert("    \"Cold_Mild_Messages\": [");
        lines.Insert("        \"The air feels cold.\",");
        lines.Insert("        \"I should keep moving.\",");
        lines.Insert("        \"My hands are getting stiff.\",");
        lines.Insert("        \"I need to stay dry.\"");
        lines.Insert("    ],");
        lines.Insert("    \"Cold_Moderate_Messages\": [");
        lines.Insert("        \"I am getting cold.\",");
        lines.Insert("        \"My clothes are not keeping the chill out.\",");
        lines.Insert("        \"I need shelter or a fire.\",");
        lines.Insert("        \"My fingers are going numb.\"");
        lines.Insert("    ],");
        lines.Insert("    \"Cold_Severe_Messages\": [");
        lines.Insert("        \"I am freezing.\",");
        lines.Insert("        \"This cold is cutting through me.\",");
        lines.Insert("        \"I need warmth now.\",");
        lines.Insert("        \"I can barely feel my hands.\"");
        lines.Insert("    ],");
        lines.Insert("    \"Cold_Critical_Messages\": [");
        lines.Insert("        \"I cannot stop shaking.\",");
        lines.Insert("        \"My body is shutting down from the cold.\",");
        lines.Insert("        \"I need fire, shelter, or dry clothes immediately.\",");
        lines.Insert("        \"I am not going to survive this cold much longer.\"");
        lines.Insert("    ],");
        lines.Insert("    \"Hot_Mild_Messages\": [");
        lines.Insert("        \"I feel warm.\",");
        lines.Insert("        \"I should avoid overheating.\",");
        lines.Insert("        \"The heat is starting to build.\",");
        lines.Insert("        \"I may need to slow down.\"");
        lines.Insert("    ],");
        lines.Insert("    \"Hot_Moderate_Messages\": [");
        lines.Insert("        \"I am getting too hot.\",");
        lines.Insert("        \"I need shade or lighter clothing.\",");
        lines.Insert("        \"This heat is draining me.\",");
        lines.Insert("        \"I should drink more water.\"");
        lines.Insert("    ],");
        lines.Insert("    \"Hot_Severe_Messages\": [");
        lines.Insert("        \"I am overheating.\",");
        lines.Insert("        \"My head feels heavy from the heat.\",");
        lines.Insert("        \"I need to cool down.\",");
        lines.Insert("        \"I should stop running.\"");
        lines.Insert("    ],");
        lines.Insert("    \"Hot_Critical_Messages\": [");
        lines.Insert("        \"I feel like I am going to collapse.\",");
        lines.Insert("        \"The heat is unbearable.\",");
        lines.Insert("        \"I need water and shade now.\",");
        lines.Insert("        \"My body cannot handle this heat much longer.\"");
        lines.Insert("    ],");
        lines.Insert("    \"Sickness_Early_Messages\": [");
        lines.Insert("        \"Something feels off.\",");
        lines.Insert("        \"My stomach feels unsettled.\",");
        lines.Insert("        \"I do not feel right.\",");
        lines.Insert("        \"I might be getting sick.\"");
        lines.Insert("    ],");
        lines.Insert("    \"Sickness_Moderate_Messages\": [");
        lines.Insert("        \"I feel ill.\",");
        lines.Insert("        \"My body aches.\",");
        lines.Insert("        \"My stomach keeps turning.\",");
        lines.Insert("        \"I need medicine.\"");
        lines.Insert("    ],");
        lines.Insert("    \"Sickness_Severe_Messages\": [");
        lines.Insert("        \"I feel feverish.\",");
        lines.Insert("        \"I can barely focus.\",");
        lines.Insert("        \"This sickness is getting worse.\",");
        lines.Insert("        \"I need treatment soon.\"");
        lines.Insert("    ],");
        lines.Insert("    \"Sickness_Critical_Messages\": [");
        lines.Insert("        \"I feel like I am dying.\",");
        lines.Insert("        \"My body is fighting something bad.\",");
        lines.Insert("        \"I need medicine now.\",");
        lines.Insert("        \"I do not know how much longer I can keep going.\"");
        lines.Insert("    ],");
        lines.Insert("    \"Bleeding_One_Messages\": [");
        lines.Insert("        \"I am bleeding.\",");
        lines.Insert("        \"I need to bandage this.\",");
        lines.Insert("        \"Blood is running down my body.\",");
        lines.Insert("        \"This wound needs attention.\"");
        lines.Insert("    ],");
        lines.Insert("    \"Bleeding_Multiple_Messages\": [");
        lines.Insert("        \"I am losing blood fast.\",");
        lines.Insert("        \"There is blood everywhere.\",");
        lines.Insert("        \"I need to stop the bleeding now.\",");
        lines.Insert("        \"I have more than one wound open.\"");
        lines.Insert("    ],");
        lines.Insert("    \"Bleeding_Critical_Messages\": [");
        lines.Insert("        \"I am bleeding out.\",");
        lines.Insert("        \"My vision is starting to fade.\",");
        lines.Insert("        \"I need bandages immediately.\",");
        lines.Insert("        \"If I do not stop this bleeding, I am dead.\"");
        lines.Insert("    ],");
        lines.Insert("    \"BrokenLegMessages\": [");
        lines.Insert("        \"My leg is broken.\",");
        lines.Insert("        \"I cannot move like this.\",");
        lines.Insert("        \"Every step is agony.\",");
        lines.Insert("        \"I need a splint before this gets worse.\"");
        lines.Insert("    ],");
        lines.Insert("    \"Infected_Far_Messages\": [");
        lines.Insert("        \"I hear infected nearby.\",");
        lines.Insert("        \"Something is moving out there.\",");
        lines.Insert("        \"I should stay quiet.\",");
        lines.Insert("        \"I do not think I am alone.\"");
        lines.Insert("    ],");
        lines.Insert("    \"Infected_Close_Messages\": [");
        lines.Insert("        \"There are infected close.\",");
        lines.Insert("        \"I need to watch my noise.\",");
        lines.Insert("        \"I can hear them breathing.\",");
        lines.Insert("        \"One wrong move and they will hear me.\"");
        lines.Insert("    ],");
        lines.Insert("    \"Infected_VeryClose_Messages\": [");
        lines.Insert("        \"They are right on top of me.\",");
        lines.Insert("        \"I need to move carefully.\",");
        lines.Insert("        \"I can hear them just outside.\",");
        lines.Insert("        \"This place is not safe.\"");
        lines.Insert("    ],");
        lines.Insert("    \"Infected_Surrounded_Messages\": [");
        lines.Insert("        \"There are too many of them.\",");
        lines.Insert("        \"I am surrounded.\",");
        lines.Insert("        \"I need an escape route.\",");
        lines.Insert("        \"If they hear me, this could go bad fast.\"");
        lines.Insert("    ],");
        lines.Insert("    \"EnableCombinedThoughts\": 1,");
        lines.Insert("    \"MaxCombinedThoughtParts\": 3,");
        lines.Insert("    \"CombinedThoughtChance\": 0.65,");
        lines.Insert("    \"UseExtremeSurvivalMessagesAtStateCount\": 4,");
        lines.Insert("    \"UseCriticalSurvivalMessagesAtStateCount\": 5,");
        lines.Insert("    \"HungerThirstMessages\": [");
        lines.Insert("        \"My stomach is empty and my mouth is dry.\",");
        lines.Insert("        \"I need food and water soon.\",");
        lines.Insert("        \"I cannot keep moving like this without supplies.\",");
        lines.Insert("        \"Every step feels harder without food or water.\"");
        lines.Insert("    ],");
        lines.Insert("    \"HungerColdMessages\": [");
        lines.Insert("        \"The hunger is worse in this cold.\",");
        lines.Insert("        \"I need food and warmth before my body gives up.\",");
        lines.Insert("        \"My stomach is empty and my hands are going numb.\",");
        lines.Insert("        \"The cold is biting harder with nothing in my stomach.\"");
        lines.Insert("    ],");
        lines.Insert("    \"HungerInfectedMessages\": [");
        lines.Insert("        \"I need food, but the infected are too close.\",");
        lines.Insert("        \"My stomach is empty, and I can hear infected nearby.\",");
        lines.Insert("        \"I should not search for food with infected this close.\",");
        lines.Insert("        \"The hunger is pushing me toward danger.\"");
        lines.Insert("    ],");
        lines.Insert("    \"ThirstColdMessages\": [");
        lines.Insert("        \"My mouth is dry and my hands are freezing.\",");
        lines.Insert("        \"I need water and warmth.\",");
        lines.Insert("        \"The cold is slowing me down, and the thirst is getting worse.\",");
        lines.Insert("        \"I should find shelter and something safe to drink.\"");
        lines.Insert("    ],");
        lines.Insert("    \"HotThirstMessages\": [");
        lines.Insert("        \"The heat is draining me dry.\",");
        lines.Insert("        \"I need water before this heat drops me.\",");
        lines.Insert("        \"My mouth is dry and my body is overheating.\",");
        lines.Insert("        \"I need shade and water now.\"");
        lines.Insert("    ],");
        lines.Insert("    \"SickColdMessages\": [");
        lines.Insert("        \"The sickness and cold are wearing me down.\",");
        lines.Insert("        \"I feel ill, and the cold is making everything worse.\",");
        lines.Insert("        \"I need medicine and warmth.\",");
        lines.Insert("        \"My body aches with every cold breath.\"");
        lines.Insert("    ],");
        lines.Insert("    \"BleedingInfectedMessages\": [");
        lines.Insert("        \"I am bleeding, and the infected are close.\",");
        lines.Insert("        \"The blood might draw attention. I need to move.\",");
        lines.Insert("        \"I need to stop this bleeding before they find me.\",");
        lines.Insert("        \"I cannot fight them while losing blood.\"");
        lines.Insert("    ],");
        lines.Insert("    \"HungerColdInfectedMessages\": [");
        lines.Insert("        \"My stomach is empty, the cold is biting, and I can hear infected nearby.\",");
        lines.Insert("        \"I need food, warmth, and a way out before those infected find me.\",");
        lines.Insert("        \"I am hungry, freezing, and not alone out here.\",");
        lines.Insert("        \"Every step feels heavier with hunger, cold, and infected close by.\"");
        lines.Insert("    ],");
        lines.Insert("    \"HungerThirstColdMessages\": [");
        lines.Insert("        \"I need food, water, and warmth before my body gives out.\",");
        lines.Insert("        \"My stomach is empty, my mouth is dry, and the cold is biting.\",");
        lines.Insert("        \"I cannot survive long like this.\",");
        lines.Insert("        \"I need shelter and supplies now.\"");
        lines.Insert("    ],");
        lines.Insert("    \"ExtremeSurvivalMessages\": [");
        lines.Insert("        \"Everything is going wrong at once.\",");
        lines.Insert("        \"My body is failing, and this place is not safe.\",");
        lines.Insert("        \"I need shelter, supplies, and a way out now.\",");
        lines.Insert("        \"I cannot keep surviving like this.\"");
        lines.Insert("    ],");
        lines.Insert("    \"CriticalSurvivalMessages\": [");
        lines.Insert("        \"I am falling apart.\",");
        lines.Insert("        \"This is bad. Really bad.\",");
        lines.Insert("        \"I need to survive the next minute before thinking about anything else.\",");
        lines.Insert("        \"Everything hurts, everything is wrong, and I am not safe.\"");
        lines.Insert("    ],");
        lines.Insert("    \"ColdInfectedMessages\": [");
        lines.Insert("        \"This is getting worse.\",");
        lines.Insert("        \"I need to deal with this now.\",");
        lines.Insert("        \"One problem is feeding the next.\",");
        lines.Insert("        \"I need to survive the next few minutes.\"");
        lines.Insert("    ],");
        lines.Insert("    \"BleedingColdMessages\": [");
        lines.Insert("        \"This is getting worse.\",");
        lines.Insert("        \"I need to deal with this now.\",");
        lines.Insert("        \"One problem is feeding the next.\",");
        lines.Insert("        \"I need to survive the next few minutes.\"");
        lines.Insert("    ],");
        lines.Insert("    \"SickThirstMessages\": [");
        lines.Insert("        \"This is getting worse.\",");
        lines.Insert("        \"I need to deal with this now.\",");
        lines.Insert("        \"One problem is feeding the next.\",");
        lines.Insert("        \"I need to survive the next few minutes.\"");
        lines.Insert("    ],");
        lines.Insert("    \"HungerHotMessages\": [");
        lines.Insert("        \"This is getting worse.\",");
        lines.Insert("        \"I need to deal with this now.\",");
        lines.Insert("        \"One problem is feeding the next.\",");
        lines.Insert("        \"I need to survive the next few minutes.\"");
        lines.Insert("    ],");
        lines.Insert("    \"HungerSickMessages\": [");
        lines.Insert("        \"This is getting worse.\",");
        lines.Insert("        \"I need to deal with this now.\",");
        lines.Insert("        \"One problem is feeding the next.\",");
        lines.Insert("        \"I need to survive the next few minutes.\"");
        lines.Insert("    ],");
        lines.Insert("    \"HungerBleedingMessages\": [");
        lines.Insert("        \"This is getting worse.\",");
        lines.Insert("        \"I need to deal with this now.\",");
        lines.Insert("        \"One problem is feeding the next.\",");
        lines.Insert("        \"I need to survive the next few minutes.\"");
        lines.Insert("    ],");
        lines.Insert("    \"ThirstBleedingMessages\": [");
        lines.Insert("        \"This is getting worse.\",");
        lines.Insert("        \"I need to deal with this now.\",");
        lines.Insert("        \"One problem is feeding the next.\",");
        lines.Insert("        \"I need to survive the next few minutes.\"");
        lines.Insert("    ],");
        lines.Insert("    \"ThirstInfectedMessages\": [");
        lines.Insert("        \"This is getting worse.\",");
        lines.Insert("        \"I need to deal with this now.\",");
        lines.Insert("        \"One problem is feeding the next.\",");
        lines.Insert("        \"I need to survive the next few minutes.\"");
        lines.Insert("    ],");
        lines.Insert("    \"HotSickMessages\": [");
        lines.Insert("        \"The fever and the heat are blending together.\",");
        lines.Insert("        \"I cannot tell where the sickness ends and the heat begins.\",");
        lines.Insert("        \"This warmth feels poisonous.\",");
        lines.Insert("        \"I need to cool down before I cook myself.\"");
        lines.Insert("    ],");
        lines.Insert("    \"HotBleedingMessages\": [");
        lines.Insert("        \"This is getting worse.\",");
        lines.Insert("        \"I need to deal with this now.\",");
        lines.Insert("        \"One problem is feeding the next.\",");
        lines.Insert("        \"I need to survive the next few minutes.\"");
        lines.Insert("    ],");
        lines.Insert("    \"HotInfectedMessages\": [");
        lines.Insert("        \"This is getting worse.\",");
        lines.Insert("        \"I need to deal with this now.\",");
        lines.Insert("        \"One problem is feeding the next.\",");
        lines.Insert("        \"I need to survive the next few minutes.\"");
        lines.Insert("    ],");
        lines.Insert("    \"SickBleedingMessages\": [");
        lines.Insert("        \"This is getting worse.\",");
        lines.Insert("        \"I need to deal with this now.\",");
        lines.Insert("        \"One problem is feeding the next.\",");
        lines.Insert("        \"I need to survive the next few minutes.\"");
        lines.Insert("    ],");
        lines.Insert("    \"SickInfectedMessages\": [");
        lines.Insert("        \"This is getting worse.\",");
        lines.Insert("        \"I need to deal with this now.\",");
        lines.Insert("        \"One problem is feeding the next.\",");
        lines.Insert("        \"I need to survive the next few minutes.\"");
        lines.Insert("    ],");
        lines.Insert("    \"HungerThirstHotMessages\": [");
        lines.Insert("        \"This is getting worse.\",");
        lines.Insert("        \"I need to deal with this now.\",");
        lines.Insert("        \"One problem is feeding the next.\",");
        lines.Insert("        \"I need to survive the next few minutes.\"");
        lines.Insert("    ],");
        lines.Insert("    \"HungerThirstInfectedMessages\": [");
        lines.Insert("        \"This is getting worse.\",");
        lines.Insert("        \"I need to deal with this now.\",");
        lines.Insert("        \"One problem is feeding the next.\",");
        lines.Insert("        \"I need to survive the next few minutes.\"");
        lines.Insert("    ],");
        lines.Insert("    \"ThirstHotInfectedMessages\": [");
        lines.Insert("        \"This is getting worse.\",");
        lines.Insert("        \"I need to deal with this now.\",");
        lines.Insert("        \"One problem is feeding the next.\",");
        lines.Insert("        \"I need to survive the next few minutes.\"");
        lines.Insert("    ],");
        lines.Insert("    \"SickColdInfectedMessages\": [");
        lines.Insert("        \"This is getting worse.\",");
        lines.Insert("        \"I need to deal with this now.\",");
        lines.Insert("        \"One problem is feeding the next.\",");
        lines.Insert("        \"I need to survive the next few minutes.\"");
        lines.Insert("    ],");
        lines.Insert("    \"BleedingColdInfectedMessages\": [");
        lines.Insert("        \"This is getting worse.\",");
        lines.Insert("        \"I need to deal with this now.\",");
        lines.Insert("        \"One problem is feeding the next.\",");
        lines.Insert("        \"I need to survive the next few minutes.\"");
        lines.Insert("    ],");
        lines.Insert("    \"BleedingSickInfectedMessages\": [");
        lines.Insert("        \"This is getting worse.\",");
        lines.Insert("        \"I need to deal with this now.\",");
        lines.Insert("        \"One problem is feeding the next.\",");
        lines.Insert("        \"I need to survive the next few minutes.\"");
        lines.Insert("    ],");
        lines.Insert("    \"BrokenLegHungerMessages\": [");
        lines.Insert("        \"This is getting worse.\",");
        lines.Insert("        \"I need to deal with this now.\",");
        lines.Insert("        \"One problem is feeding the next.\",");
        lines.Insert("        \"I need to survive the next few minutes.\"");
        lines.Insert("    ],");
        lines.Insert("    \"BrokenLegThirstMessages\": [");
        lines.Insert("        \"This is getting worse.\",");
        lines.Insert("        \"I need to deal with this now.\",");
        lines.Insert("        \"One problem is feeding the next.\",");
        lines.Insert("        \"I need to survive the next few minutes.\"");
        lines.Insert("    ],");
        lines.Insert("    \"BrokenLegColdMessages\": [");
        lines.Insert("        \"This is getting worse.\",");
        lines.Insert("        \"I need to deal with this now.\",");
        lines.Insert("        \"One problem is feeding the next.\",");
        lines.Insert("        \"I need to survive the next few minutes.\"");
        lines.Insert("    ],");
        lines.Insert("    \"BrokenLegHotMessages\": [");
        lines.Insert("        \"This is getting worse.\",");
        lines.Insert("        \"I need to deal with this now.\",");
        lines.Insert("        \"One problem is feeding the next.\",");
        lines.Insert("        \"I need to survive the next few minutes.\"");
        lines.Insert("    ],");
        lines.Insert("    \"BrokenLegSickMessages\": [");
        lines.Insert("        \"This is getting worse.\",");
        lines.Insert("        \"I need to deal with this now.\",");
        lines.Insert("        \"One problem is feeding the next.\",");
        lines.Insert("        \"I need to survive the next few minutes.\"");
        lines.Insert("    ],");
        lines.Insert("    \"BrokenLegBleedingMessages\": [");
        lines.Insert("        \"This is getting worse.\",");
        lines.Insert("        \"I need to deal with this now.\",");
        lines.Insert("        \"One problem is feeding the next.\",");
        lines.Insert("        \"I need to survive the next few minutes.\"");
        lines.Insert("    ],");
        lines.Insert("    \"BrokenLegInfectedMessages\": [");
        lines.Insert("        \"I cannot run, and they are getting closer.\",");
        lines.Insert("        \"A broken leg with infected nearby is a death trap.\",");
        lines.Insert("        \"I need distance, but my leg will not give it.\",");
        lines.Insert("        \"If they hear me, I am finished.\"");
        lines.Insert("    ],");
        lines.Insert("    \"BrokenLegColdInfectedMessages\": [");
        lines.Insert("        \"This is getting worse.\",");
        lines.Insert("        \"I need to deal with this now.\",");
        lines.Insert("        \"One problem is feeding the next.\",");
        lines.Insert("        \"I need to survive the next few minutes.\"");
        lines.Insert("    ],");
        lines.Insert("    \"BrokenLegBleedingInfectedMessages\": [");
        lines.Insert("        \"I cannot run, I am bleeding, and they are coming.\",");
        lines.Insert("        \"Bad leg, open wound, infected nearby. This is a trap.\",");
        lines.Insert("        \"Every sound is closer when I cannot move right.\",");
        lines.Insert("        \"I need to stop the bleeding before they reach me.\",");
        lines.Insert("        \"Crawling and bleeding is not a plan.\",");
        lines.Insert("        \"If they see me now, I am finished.\"");
        lines.Insert("    ],");
        lines.Insert("    \"BrokenLegHungerThirstMessages\": [");
        lines.Insert("        \"This is getting worse.\",");
        lines.Insert("        \"I need to deal with this now.\",");
        lines.Insert("        \"One problem is feeding the next.\",");
        lines.Insert("        \"I need to survive the next few minutes.\"");
        lines.Insert("    ],");
        lines.Insert("    \"StarvingToDeathMessages\": [");
        lines.Insert("        \"I am starving to death.\",");
        lines.Insert("        \"My body is eating itself, and my health is dropping.\",");
        lines.Insert("        \"I need food now or this is the end.\",");
        lines.Insert("        \"The hunger has gone past pain. I am dying.\"");
        lines.Insert("    ],");
        lines.Insert("    \"DehydratingToDeathMessages\": [");
        lines.Insert("        \"I am dying of thirst.\",");
        lines.Insert("        \"My body is shutting down without water.\",");
        lines.Insert("        \"I need water now or I will not make it.\",");
        lines.Insert("        \"My mouth is dry, my head is spinning, and my health is dropping.\"");
        lines.Insert("    ],");
        lines.Insert("    \"FreezingToDeathMessages\": [");
        lines.Insert("        \"I am freezing to death.\",");
        lines.Insert("        \"The cold is taking my health now.\",");
        lines.Insert("        \"I need fire or shelter immediately.\",");
        lines.Insert("        \"My body is shutting down from the cold.\"");
        lines.Insert("    ],");
        lines.Insert("    \"OverheatingToDeathMessages\": [");
        lines.Insert("        \"I am overheating to death.\",");
        lines.Insert("        \"The heat is taking my health now.\",");
        lines.Insert("        \"I need shade and water immediately.\",");
        lines.Insert("        \"My body cannot survive this heat much longer.\"");
        lines.Insert("    ],");
        lines.Insert("    \"EnableAdvancedCombinedMessages\": 1,");
        lines.Insert("    \"AdvancedCombinedChance\": 0.65,");
        lines.Insert("    \"StarvingDehydratedMessages\": [");
        lines.Insert("        \"No food, no water. My body has nothing left to trade.\",");
        lines.Insert("        \"Hunger and thirst are hollowing me out together.\",");
        lines.Insert("        \"I need calories and water before my legs stop listening.\",");
        lines.Insert("        \"Everything in me is empty.\"");
        lines.Insert("    ],");
        lines.Insert("    \"StarvingLowBloodMessages\": [");
        lines.Insert("        \"I am starving, and there is barely enough blood left to carry me.\",");
        lines.Insert("        \"My body cannot heal while it is eating itself.\",");
        lines.Insert("        \"No food, low blood, and no margin left.\",");
        lines.Insert("        \"I need food before this weakness becomes permanent.\"");
        lines.Insert("    ],");
        lines.Insert("    \"DehydratedLowBloodMessages\": [");
        lines.Insert("        \"My blood feels thick and my mouth is dry.\",");
        lines.Insert("        \"Low blood and no water. That is a bad combination.\",");
        lines.Insert("        \"I need fluids before my body gives up.\",");
        lines.Insert("        \"Every pulse feels weaker than the last.\"");
        lines.Insert("    ],");
        lines.Insert("    \"ColdWetMessages\": [");
        lines.Insert("        \"Wet clothes and cold air are working together.\",");
        lines.Insert("        \"The cold is using the rain against me.\",");
        lines.Insert("        \"I need fire, shelter, or both.\",");
        lines.Insert("        \"Being wet out here is a slow sentence.\"");
        lines.Insert("    ],");
        lines.Insert("    \"ColdWetNightMessages\": [");
        lines.Insert("        \"The cold, the wet, and the dark are working together.\",");
        lines.Insert("        \"Night makes soaked clothes feel like ice.\",");
        lines.Insert("        \"I need shelter before the dark freezes me still.\",");
        lines.Insert("        \"This is how people disappear quietly.\"");
        lines.Insert("    ],");
        lines.Insert("    \"ColdWetSickMessages\": [");
        lines.Insert("        \"Wet, cold, and sick. My body is losing the argument.\",");
        lines.Insert("        \"The illness has more room to grow in this cold.\",");
        lines.Insert("        \"I need warmth before the sickness digs deeper.\",");
        lines.Insert("        \"Everything about this weather is making me worse.\"");
        lines.Insert("    ],");
        lines.Insert("    \"HotDehydratedMessages\": [");
        lines.Insert("        \"The heat is taking water I do not have.\",");
        lines.Insert("        \"I am drying out from the inside.\",");
        lines.Insert("        \"This heat will finish what thirst started.\",");
        lines.Insert("        \"I need shade and water now.\"");
        lines.Insert("    ],");
        lines.Insert("    \"BleedingLowBloodMessages\": [");
        lines.Insert("        \"I am running out faster than I can stop it.\",");
        lines.Insert("        \"The blood loss is becoming critical.\",");
        lines.Insert("        \"I need pressure on the wound now.\",");
        lines.Insert("        \"There is not enough left in me to keep bleeding.\"");
        lines.Insert("    ],");
        lines.Insert("    \"BleedingShockMessages\": [");
        lines.Insert("        \"Bleeding and shaking. Focus on the bandage.\",");
        lines.Insert("        \"My hands are not steady enough for this.\",");
        lines.Insert("        \"Blood loss and panic are feeding each other.\",");
        lines.Insert("        \"I need to control the wound and my breathing.\"");
        lines.Insert("    ],");
        lines.Insert("    \"GunshotBleedingMessages\": [");
        lines.Insert("        \"The shot opened me up. I need cover and pressure now.\",");
        lines.Insert("        \"I am hit and bleeding. Move first, bandage second.\",");
        lines.Insert("        \"That bullet is still taking from me.\",");
        lines.Insert("        \"Cover, bandage, breathe.\"");
        lines.Insert("    ],");
        lines.Insert("    \"ExplosionShockMessages\": [");
        lines.Insert("        \"The blast is still inside my head.\",");
        lines.Insert("        \"I can barely think through the ringing.\",");
        lines.Insert("        \"The explosion knocked the world sideways.\",");
        lines.Insert("        \"Get up. Move. Count limbs later.\"");
        lines.Insert("    ],");
        lines.Insert("    \"BrokenLegNightMessages\": [");
        lines.Insert("        \"A broken leg in the dark is bad planning by the universe.\",");
        lines.Insert("        \"I need shelter before night finishes what the fall started.\",");
        lines.Insert("        \"Every crawl in the dark feels too loud.\",");
        lines.Insert("        \"I cannot see far enough to know if crawling is safe.\"");
        lines.Insert("    ],");
        lines.Insert("    \"LowBloodCorpseMessages\": [");
        lines.Insert("        \"Someone died here, and I am not far behind.\",");
        lines.Insert("        \"This corpse feels like a warning.\",");
        lines.Insert("        \"Low blood makes every body look like a mirror.\",");
        lines.Insert("        \"I should leave before I become part of the scene.\"");
        lines.Insert("    ],");
        lines.Insert("    \"SickContaminatedMessages\": [");
        lines.Insert("        \"The air is wrong, and so is my body.\",");
        lines.Insert("        \"This contamination is feeding the sickness.\",");
        lines.Insert("        \"I need clean air and medicine.\",");
        lines.Insert("        \"Every breath feels like a mistake.\"");
        lines.Insert("    ],");
        lines.Insert("    \"NightRainMessages\": [");
        lines.Insert("        \"Rain and darkness. Perfect cover for someone I cannot see.\",");
        lines.Insert("        \"The rain hides footsteps, including mine.\",");
        lines.Insert("        \"Night rain makes the whole world feel occupied.\",");
        lines.Insert("        \"I cannot hear enough to feel safe.\"");
        lines.Insert("    ],");
        lines.Insert("    \"NightFogMessages\": [");
        lines.Insert("        \"The dark and fog have swallowed the road.\",");
        lines.Insert("        \"Anything could be ten steps away.\",");
        lines.Insert("        \"The fog is worse at night. It feels alive.\",");
        lines.Insert("        \"I should move slower than my fear wants me to.\"");
        lines.Insert("    ],");
        lines.Insert("    \"MilitaryGunshotMessages\": [");
        lines.Insert("        \"A gunshot near military ground is never random.\",");
        lines.Insert("        \"Someone came here for weapons and found a target.\",");
        lines.Insert("        \"Military loot brings military problems.\",");
        lines.Insert("        \"That shot just made this place worse.\"");
        lines.Insert("    ],");
        lines.Insert("    \"MilitaryCorpseMessages\": [");
        lines.Insert("        \"Military places always collect bodies.\",");
        lines.Insert("        \"Good gear, bad endings.\",");
        lines.Insert("        \"Someone paid for this loot already.\",");
        lines.Insert("        \"I should assume whoever did this is still close.\"");
        lines.Insert("    ],");
        lines.Insert("    \"LoneWolfNightMessages\": [");
        lines.Insert("        \"Alone at night again. That should not feel normal.\",");
        lines.Insert("        \"The dark makes loneliness louder.\",");
        lines.Insert("        \"No voices, no footsteps, no one to blame if I fail.\",");
        lines.Insert("        \"I have been alone so long the night feels like company.\"");
        lines.Insert("    ],");
        lines.Insert("    \"LowSanityCannibalismMessages\": [");
        lines.Insert("        \"There are hungers that should have stayed empty.\",");
        lines.Insert("        \"The worst part is that it helped.\",");
        lines.Insert("        \"I crossed something I cannot uncross.\",");
        lines.Insert("        \"I know what I ate. I know.\"");
        lines.Insert("    ],");
        lines.Insert("    \"LowSanityCorpseMessages\": [");
        lines.Insert("        \"The dead are starting to feel familiar.\",");
        lines.Insert("        \"Their faces follow me after I walk away.\",");
        lines.Insert("        \"A body should bother me more than this.\",");
        lines.Insert("        \"I keep expecting the corpse to speak first.\"");
        lines.Insert("    ],");
        lines.Insert("    \"LowSanityNightMessages\": [");
        lines.Insert("        \"The dark is starting to sound like voices.\",");
        lines.Insert("        \"Night gives shape to things I should not be hearing.\",");
        lines.Insert("        \"I am not sure every thought in my head is mine.\",");
        lines.Insert("        \"The silence keeps laughing.\"");
        lines.Insert("    ],");
        lines.Insert("    \"CompanionDeadLowSanityMessages\": [");
        lines.Insert("        \"They are gone, but I keep expecting them to answer.\",");
        lines.Insert("        \"I could not keep them alive. I keep replaying it.\",");
        lines.Insert("        \"Their silence is louder than anything out here.\",");
        lines.Insert("        \"I am alone with what happened.\"");
        lines.Insert("    ],");
        lines.Insert("    \"EnableExpandedAdvancedCombos\": 1,");
        lines.Insert("    \"StarvingDehydratedColdMessages\": [");
        lines.Insert("        \"No food, no water, and the cold is taking the rest.\",");
        lines.Insert("        \"My body has nothing left to burn, and the cold knows it.\",");
        lines.Insert("        \"Hunger, thirst, cold. All of it is pulling me down.\",");
        lines.Insert("        \"I need food, water, and warmth before I stop making sense.\",");
        lines.Insert("        \"Everything my body needs is missing at once.\",");
        lines.Insert("        \"The cold feels worse when there is nothing left inside me.\"");
        lines.Insert("    ],");
        lines.Insert("    \"HotDehydratedSickMessages\": [");
        lines.Insert("        \"Heat, thirst, sickness. My body is turning against itself.\",");
        lines.Insert("        \"I need water and shade before this fever cooks me.\",");
        lines.Insert("        \"The heat is making the sickness worse.\",");
        lines.Insert("        \"My stomach turns and the air feels too hot.\",");
        lines.Insert("        \"This is how people collapse in the open.\",");
        lines.Insert("        \"I cannot tell where the fever ends and the heat begins.\"");
        lines.Insert("    ],");
        lines.Insert("    \"BleedingLowBloodShockMessages\": [");
        lines.Insert("        \"Too much blood is gone, and my head is going with it.\",");
        lines.Insert("        \"I am bleeding, weak, and close to blacking out.\",");
        lines.Insert("        \"The wound is draining more than blood now.\",");
        lines.Insert("        \"My vision is narrowing. I need to stop this.\",");
        lines.Insert("        \"I am losing blood faster than I can think.\",");
        lines.Insert("        \"If I pass out like this, I may not wake up.\"");
        lines.Insert("    ],");
        lines.Insert("    \"GunshotBleedingLowBloodMessages\": [");
        lines.Insert("        \"The shot opened me up, and I am running empty.\",");
        lines.Insert("        \"I need cover and pressure on the wound now.\",");
        lines.Insert("        \"Gunshot, blood loss, shock. One mistake and I am done.\",");
        lines.Insert("        \"That round is still taking pieces of me.\",");
        lines.Insert("        \"I can feel the blood leaving faster than my fear.\",");
        lines.Insert("        \"Move first. Bleed later. If there is a later.\"");
        lines.Insert("    ],");
        lines.Insert("    \"NightInfectedRainMessages\": [");
        lines.Insert("        \"Rain, infected, darkness. I cannot trust my ears.\",");
        lines.Insert("        \"The rain hides them until they are too close.\",");
        lines.Insert("        \"Night and rain make every infected sound like ten.\",");
        lines.Insert("        \"I need shelter before the dark fills with teeth.\",");
        lines.Insert("        \"The rain is covering too much movement.\",");
        lines.Insert("        \"I can hear them, but I cannot place them.\"");
        lines.Insert("    ],");
        lines.Insert("    \"MilitaryNightStormMessages\": [");
        lines.Insert("        \"A storm over a military site. Perfect cover for a bad decision.\",");
        lines.Insert("        \"The weather is hiding every sniper lane.\",");
        lines.Insert("        \"At night, this place belongs to whoever sees first.\",");
        lines.Insert("        \"The storm makes the base feel alive.\",");
        lines.Insert("        \"Good loot, bad weather, worse odds.\",");
        lines.Insert("        \"Every flash of lightning could give me away.\"");
        lines.Insert("    ],");
        lines.Insert("    \"LoneWolfLowSanityNightMessages\": [");
        lines.Insert("        \"Alone at night, my thoughts get too loud.\",");
        lines.Insert("        \"There is nobody to tell me I am still myself.\",");
        lines.Insert("        \"The dark answers back now.\",");
        lines.Insert("        \"I have been alone too long to trust my own head.\",");
        lines.Insert("        \"My shadow feels like company, and that scares me.\",");
        lines.Insert("        \"I need a voice that is not mine.\"");
        lines.Insert("    ],");
        lines.Insert("    \"CompanionDeadNightMessages\": [");
        lines.Insert("        \"Night makes their absence feel bigger.\",");
        lines.Insert("        \"I keep expecting footsteps that are not coming.\",");
        lines.Insert("        \"They should be here. They are not.\",");
        lines.Insert("        \"The dark is quieter without them, and worse for it.\",");
        lines.Insert("        \"I am listening for someone who will never answer.\",");
        lines.Insert("        \"I did not know silence could feel this heavy.\"");
        lines.Insert("    ],");
        lines.Insert("    \"CorpseLowSanityNightMessages\": [");
        lines.Insert("        \"The bodies look different at night.\",");
        lines.Insert("        \"I should not stay near the dead while my head is like this.\",");
        lines.Insert("        \"Their faces keep changing in the dark.\",");
        lines.Insert("        \"The dead are quiet, but my mind is not.\",");
        lines.Insert("        \"I know they cannot move. I still keep watching.\",");
        lines.Insert("        \"Night makes the corpses feel less finished.\"");
        lines.Insert("    ],");
        lines.Insert("    \"ShelterNightInfectedMessages\": [");
        lines.Insert("        \"Walls help, but they know I am in here.\",");
        lines.Insert("        \"I can hear them outside the shelter.\",");
        lines.Insert("        \"This place is shelter until they find the door.\",");
        lines.Insert("        \"I need exits, not comfort.\",");
        lines.Insert("        \"The building feels smaller with infected nearby.\",");
        lines.Insert("        \"If they get inside, I have nowhere to run.\"");
        lines.Insert("    ],");
        lines.Insert("    \"EnableRecoveryMessages\": 1,");
        lines.Insert("    \"RecoveryThoughtCooldownSeconds\": 180.0,");
        lines.Insert("    \"RecoveryThoughtChance\": 0.4,");
        lines.Insert("    \"BleedingRecoveryMessages\": [");
        lines.Insert("        \"The bleeding stopped. I can think again.\",");
        lines.Insert("        \"Pressure worked. I am still here.\",");
        lines.Insert("        \"The blood has stopped running for now.\",");
        lines.Insert("        \"One problem closed. Many left.\"");
        lines.Insert("    ],");
        lines.Insert("    \"HealthStableRecoveryMessages\": [");
        lines.Insert("        \"My condition has stopped getting worse.\",");
        lines.Insert("        \"I am not better, but I am not falling apart as fast.\",");
        lines.Insert("        \"I can feel myself stabilizing.\",");
        lines.Insert("        \"For now, I am holding together.\"");
        lines.Insert("    ],");
        lines.Insert("    \"FoodRecoveryMessages\": [");
        lines.Insert("        \"The food is starting to help.\",");
        lines.Insert("        \"My body has something to burn again.\",");
        lines.Insert("        \"That might keep me moving.\",");
        lines.Insert("        \"The hollow feeling is easing.\"");
        lines.Insert("    ],");
        lines.Insert("    \"WaterRecoveryMessages\": [");
        lines.Insert("        \"The water is starting to settle in.\",");
        lines.Insert("        \"My mouth does not feel as dry now.\",");
        lines.Insert("        \"That drink bought me time.\",");
        lines.Insert("        \"I can think clearer with water in me.\"");
        lines.Insert("    ],");
        lines.Insert("    \"WarmedUpMessages\": [");
        lines.Insert("        \"My hands are warming up.\",");
        lines.Insert("        \"The cold is letting go a little.\",");
        lines.Insert("        \"Warmth is coming back slowly.\",");
        lines.Insert("        \"I might have caught this in time.\"");
        lines.Insert("    ],");
        lines.Insert("    \"CooledDownMessages\": [");
        lines.Insert("        \"The heat is easing off.\",");
        lines.Insert("        \"I can breathe better now.\",");
        lines.Insert("        \"My body is cooling down.\",");
        lines.Insert("        \"Shade and patience are working.\"");
        lines.Insert("    ],");
        lines.Insert("    \"DryingOffMessages\": [");
        lines.Insert("        \"I am starting to dry out.\",");
        lines.Insert("        \"The damp is finally leaving my clothes.\",");
        lines.Insert("        \"Dry gear feels like hope.\",");
        lines.Insert("        \"Less wet means less cold later.\"");
        lines.Insert("    ],");
        lines.Insert("    \"LeftContaminatedZoneMessages\": [");
        lines.Insert("        \"The air tastes cleaner now.\",");
        lines.Insert("        \"I am out of the gas, but not out of trouble.\",");
        lines.Insert("        \"Check filters, check skin, keep moving.\",");
        lines.Insert("        \"Clean air feels better than it should.\"");
        lines.Insert("    ],");
        lines.Insert("    \"EscapedInfectedMessages\": [");
        lines.Insert("        \"I cannot hear them anymore.\",");
        lines.Insert("        \"The infected are behind me for now.\",");
        lines.Insert("        \"Distance is the only medicine for that noise.\",");
        lines.Insert("        \"I got away. This time.\"");
        lines.Insert("    ],");
        lines.Insert("    \"DawnSurvivalMessages\": [");
        lines.Insert("        \"Daylight. I made it.\",");
        lines.Insert("        \"The sun came back, and so did I.\",");
        lines.Insert("        \"Another night survived.\",");
        lines.Insert("        \"Morning does not mean safe, but it means I lasted.\"");
        lines.Insert("    ],");
        lines.Insert("    \"ShelterFromStormMessages\": [");
        lines.Insert("        \"This shelter is holding the weather back.\",");
        lines.Insert("        \"Four walls against the storm. Good enough for now.\",");
        lines.Insert("        \"The storm can have outside.\",");
        lines.Insert("        \"I need to use this cover while I have it.\"");
        lines.Insert("    ],");
        lines.Insert("    \"ShockRecoveryMessages\": [");
        lines.Insert("        \"My head is clearing. I am still here.\",");
        lines.Insert("        \"The ringing is fading.\",");
        lines.Insert("        \"I can think again. Not well, but enough.\",");
        lines.Insert("        \"My hands are steadier now.\",");
        lines.Insert("        \"The blackout passed me by this time.\",");
        lines.Insert("        \"Breathe. Focus. Check wounds.\"");
        lines.Insert("    ],");
        lines.Insert("    \"BloodStabilizingMessages\": [");
        lines.Insert("        \"The blood loss is not pulling as hard now.\",");
        lines.Insert("        \"I might have stopped the worst of it.\",");
        lines.Insert("        \"My pulse is still weak, but steadier.\",");
        lines.Insert("        \"I am not recovering fast, but I am not falling as quickly.\",");
        lines.Insert("        \"The world is less grey than it was.\",");
        lines.Insert("        \"I need time, food, and quiet.\"");
        lines.Insert("    ],");
        lines.Insert("    \"AlmostDiedRecoveryMessages\": [");
        lines.Insert("        \"That was too close.\",");
        lines.Insert("        \"I was nearly gone.\",");
        lines.Insert("        \"I do not get many chances like that.\",");
        lines.Insert("        \"Still breathing. Somehow.\",");
        lines.Insert("        \"I need to remember how close that came.\",");
        lines.Insert("        \"I survived the minute. Now survive the next.\"");
        lines.Insert("    ],");
        lines.Insert("    \"SafeShelterRecoveryMessages\": [");
        lines.Insert("        \"Shelter. Not safety, but close enough for now.\",");
        lines.Insert("        \"The walls give me a moment to think.\",");
        lines.Insert("        \"I can breathe in here for a second.\",");
        lines.Insert("        \"This place buys time.\",");
        lines.Insert("        \"Cover first. Then wounds. Then plans.\",");
        lines.Insert("        \"Four walls are better than open ground.\"");
        lines.Insert("    ],");
        lines.Insert("    \"PostCombatBreathMessages\": [");
        lines.Insert("        \"The fight is over, but my hands have not noticed.\",");
        lines.Insert("        \"I need to listen before moving again.\",");
        lines.Insert("        \"Count rounds. Count wounds. Count exits.\",");
        lines.Insert("        \"The danger passed, maybe. Do not trust that.\",");
        lines.Insert("        \"My heart is still running.\",");
        lines.Insert("        \"I need to calm down before I make a stupid choice.\"");
        lines.Insert("    ],");
        lines.Insert("    \"EnableDiseaseSpecificMessages\": 1,");
        lines.Insert("    \"DiseaseWoundInfectionMessages\": [");
        lines.Insert("        \"The wound feels hot. That is not good.\",");
        lines.Insert("        \"The infection is in the wound now.\",");
        lines.Insert("        \"I need disinfectant or antibiotics.\",");
        lines.Insert("        \"This cut is turning against me.\"");
        lines.Insert("    ],");
        lines.Insert("    \"DiseaseCholeraMessages\": [");
        lines.Insert("        \"My stomach is turning against me.\",");
        lines.Insert("        \"Water did this to me.\",");
        lines.Insert("        \"I need clean fluids and medicine.\",");
        lines.Insert("        \"This sickness is draining me from inside.\"");
        lines.Insert("    ],");
        lines.Insert("    \"DiseaseInfluenzaMessages\": [");
        lines.Insert("        \"The fever is climbing.\",");
        lines.Insert("        \"Every breath feels heavier.\",");
        lines.Insert("        \"My bones ache like they are full of ice.\",");
        lines.Insert("        \"I need warmth, rest, and medicine.\"");
        lines.Insert("    ],");
        lines.Insert("    \"DiseaseKuruMessages\": [");
        lines.Insert("        \"The laugh comes before I can stop it.\",");
        lines.Insert("        \"Something is wrong in my head.\",");
        lines.Insert("        \"My own mouth is betraying me.\",");
        lines.Insert("        \"The giggle does not feel like mine.\"");
        lines.Insert("    ],");
        lines.Insert("    \"DiseaseChemicalMessages\": [");
        lines.Insert("        \"My mouth tastes like metal.\",");
        lines.Insert("        \"The air burned something into me.\",");
        lines.Insert("        \"My skin feels wrong.\",");
        lines.Insert("        \"I need treatment before this poison settles.\"");
        lines.Insert("    ],");
        lines.Insert("    \"DiseaseUnknownMessages\": [");
        lines.Insert("        \"Something is wrong with me.\",");
        lines.Insert("        \"My body is warning me, but I cannot name it.\",");
        lines.Insert("        \"This sickness does not feel normal.\",");
        lines.Insert("        \"I need medicine before I know what for.\"");
        lines.Insert("    ],");
        lines.Insert("    \"DiseaseGasExposureMessages\": [");
        lines.Insert("        \"The air is poison here.\",");
        lines.Insert("        \"My lungs know this place is wrong.\",");
        lines.Insert("        \"I need filters, distance, or both.\",");
        lines.Insert("        \"This gas is getting through something.\",");
        lines.Insert("        \"Every breath feels expensive.\",");
        lines.Insert("        \"I should not be breathing this.\"");
        lines.Insert("    ],");
        lines.Insert("    \"DiseaseFeverMessages\": [");
        lines.Insert("        \"The fever is burning through me.\",");
        lines.Insert("        \"My skin feels wrong.\",");
        lines.Insert("        \"Hot and cold keep trading places.\",");
        lines.Insert("        \"The sickness is making time blur.\",");
        lines.Insert("        \"I need medicine before the fever wins.\",");
        lines.Insert("        \"My body cannot decide if it is freezing or burning.\"");
        lines.Insert("    ],");
        lines.Insert("    \"DiseaseFoodPoisoningMessages\": [");
        lines.Insert("        \"My stomach is punishing me.\",");
        lines.Insert("        \"Whatever I ate was a mistake.\",");
        lines.Insert("        \"I need water, medicine, and somewhere quiet.\",");
        lines.Insert("        \"My gut is turning itself inside out.\",");
        lines.Insert("        \"This is not normal hunger.\",");
        lines.Insert("        \"I should have checked the food.\"");
        lines.Insert("    ]");
        lines.Insert("}");

        ST_WriteDefaultJsonFile(filePath, lines);
        Log("Created default consolidated config: " + filePath);
    }

    void ST_CreateDefault_03_Actions_Damage_Combat_json(string folderPath)
    {
        string filePath = folderPath + "/03_Actions_Damage_Combat.json";
        if (FileExist(filePath))
            return;

        array<string> lines = new array<string>;
        lines.Insert("{");
        lines.Insert("    \"EnableActionThoughts\": 1,");
        lines.Insert("    \"EnableExtendedVanillaActionMessages\": 1,");
        lines.Insert("    \"EnableEatingThoughts\": 1,");
        lines.Insert("    \"EnableDrinkingThoughts\": 1,");
        lines.Insert("    \"EnableUnjamThoughts\": 1,");
        lines.Insert("    \"EnableSkinningThoughts\": 1,");
        lines.Insert("    \"EnableBandagingThoughts\": 1,");
        lines.Insert("    \"EnableFireStartingThoughts\": 1,");
        lines.Insert("    \"EnableCookingThoughts\": 1,");
        lines.Insert("    \"EnableFishingThoughts\": 1,");
        lines.Insert("    \"EnableRepairThoughts\": 1,");
        lines.Insert("    \"EatingMessages\": [");
        lines.Insert("        \"That helped.\",");
        lines.Insert("        \"I needed that.\",");
        lines.Insert("        \"My stomach settles a little.\",");
        lines.Insert("        \"I should find more food before moving on.\",");
        lines.Insert("        \"That tasted awful, but it will keep me alive.\"");
        lines.Insert("    ],");
        lines.Insert("    \"DrinkingMessages\": [");
        lines.Insert("        \"That feels better.\",");
        lines.Insert("        \"My throat needed that.\",");
        lines.Insert("        \"I should refill before I leave.\",");
        lines.Insert("        \"Clean water is worth more than ammo out here.\",");
        lines.Insert("        \"I needed every drop.\"");
        lines.Insert("    ],");
        lines.Insert("    \"UnsafeDrinkingMessages\": [");
        lines.Insert("        \"I hope that water was clean.\",");
        lines.Insert("        \"That tasted off.\",");
        lines.Insert("        \"My stomach turns after drinking that.\",");
        lines.Insert("        \"I should have purified it first.\"");
        lines.Insert("    ],");
        lines.Insert("    \"UnjamMessages\": [");
        lines.Insert("        \"Come on, clear it.\",");
        lines.Insert("        \"Not now.\",");
        lines.Insert("        \"This weapon is going to get me killed.\",");
        lines.Insert("        \"I need to maintain this gun.\",");
        lines.Insert("        \"Clear the jam before it gets me killed.\"");
        lines.Insert("    ],");
        lines.Insert("    \"UnjamSuccessMessages\": [");
        lines.Insert("        \"It is clear.\",");
        lines.Insert("        \"Back in the fight.\",");
        lines.Insert("        \"I got it working again.\",");
        lines.Insert("        \"That could have ended badly.\"");
        lines.Insert("    ],");
        lines.Insert("    \"SkinningAnimalMessages\": [");
        lines.Insert("        \"This will keep me alive.\",");
        lines.Insert("        \"Fresh meat means another day.\",");
        lines.Insert("        \"I should cook this before moving on.\",");
        lines.Insert("        \"The smell might attract attention.\",");
        lines.Insert("        \"Waste nothing.\"");
        lines.Insert("    ],");
        lines.Insert("    \"SkinningHumanMessages\": [");
        lines.Insert("        \"I should not think about what I am doing.\",");
        lines.Insert("        \"Survival changes people.\",");
        lines.Insert("        \"There is no going back from this.\",");
        lines.Insert("        \"I hope nobody saw that.\",");
        lines.Insert("        \"This is what the world has made of me.\"");
        lines.Insert("    ],");
        lines.Insert("    \"BandagingMessages\": [");
        lines.Insert("        \"Hold pressure.\",");
        lines.Insert("        \"I need to stop the bleeding.\",");
        lines.Insert("        \"That should slow it down.\",");
        lines.Insert("        \"I cannot afford to lose more blood.\",");
        lines.Insert("        \"Stay calm. Wrap it tight.\"");
        lines.Insert("    ],");
        lines.Insert("    \"BandageSuccessMessages\": [");
        lines.Insert("        \"The bleeding has stopped.\",");
        lines.Insert("        \"That was close.\",");
        lines.Insert("        \"I need to be more careful.\",");
        lines.Insert("        \"That should hold for now.\"");
        lines.Insert("    ],");
        lines.Insert("    \"FireStartingMessages\": [");
        lines.Insert("        \"Come on, catch.\",");
        lines.Insert("        \"A fire would change everything right now.\",");
        lines.Insert("        \"I need warmth.\",");
        lines.Insert("        \"Smoke might give me away.\",");
        lines.Insert("        \"Finally, some heat.\"");
        lines.Insert("    ],");
        lines.Insert("    \"CookingMessages\": [");
        lines.Insert("        \"The smell makes me hungry.\",");
        lines.Insert("        \"Hot food might keep me going.\",");
        lines.Insert("        \"I should not burn this.\",");
        lines.Insert("        \"A warm meal feels rare now.\"");
        lines.Insert("    ],");
        lines.Insert("    \"FishingMessages\": [");
        lines.Insert("        \"Patience.\",");
        lines.Insert("        \"Something has to bite eventually.\",");
        lines.Insert("        \"Food from the water is safer than the towns.\",");
        lines.Insert("        \"I hope this line holds.\"");
        lines.Insert("    ],");
        lines.Insert("    \"RepairMessages\": [");
        lines.Insert("        \"This should hold for now.\",");
        lines.Insert("        \"Better than letting it fall apart.\",");
        lines.Insert("        \"I need to take care of my gear.\",");
        lines.Insert("        \"Nothing lasts out here.\"");
        lines.Insert("    ],");
        lines.Insert("    \"MedicineConsumeMessages\": [");
        lines.Insert("        \"This might help.\",");
        lines.Insert("        \"I hope this is the right medicine.\",");
        lines.Insert("        \"Give it time to work.\",");
        lines.Insert("        \"I need to trust the pills now.\"");
        lines.Insert("    ],");
        lines.Insert("    \"WoundCareActionMessages\": [");
        lines.Insert("        \"This is going to hurt.\",");
        lines.Insert("        \"I need to close this wound.\",");
        lines.Insert("        \"Hold still. Breathe.\",");
        lines.Insert("        \"If I do not treat this now, it gets worse.\"");
        lines.Insert("    ],");
        lines.Insert("    \"InjectionMessages\": [");
        lines.Insert("        \"Steady hand.\",");
        lines.Insert("        \"This better help.\",");
        lines.Insert("        \"I hate using needles out here.\",");
        lines.Insert("        \"One shot could make the difference.\"");
        lines.Insert("    ],");
        lines.Insert("    \"BloodMedicalMessages\": [");
        lines.Insert("        \"I hope this blood is compatible.\",");
        lines.Insert("        \"I need this to work.\",");
        lines.Insert("        \"This bag could save me or finish me.\",");
        lines.Insert("        \"I can feel how weak I am.\"");
        lines.Insert("    ],");
        lines.Insert("    \"DisinfectActionMessages\": [");
        lines.Insert("        \"This should clean the wound.\",");
        lines.Insert("        \"It burns, but it might save me.\",");
        lines.Insert("        \"I need to keep infection out.\",");
        lines.Insert("        \"Better pain now than sickness later.\"");
        lines.Insert("    ],");
        lines.Insert("    \"RestrainActionMessages\": [");
        lines.Insert("        \"This could get ugly.\",");
        lines.Insert("        \"Keep control.\",");
        lines.Insert("        \"Do not give them a chance.\",");
        lines.Insert("        \"I need to finish this quickly.\"");
        lines.Insert("    ],");
        lines.Insert("    \"CraftingActionMessages\": [");
        lines.Insert("        \"Use what is left.\",");
        lines.Insert("        \"This might be useful.\",");
        lines.Insert("        \"Improvising keeps me alive.\",");
        lines.Insert("        \"Nothing out here is wasted.\"");
        lines.Insert("    ],");
        lines.Insert("    \"DeployActionMessages\": [");
        lines.Insert("        \"This spot will have to do.\",");
        lines.Insert("        \"Set it down carefully.\",");
        lines.Insert("        \"I should not leave obvious signs.\",");
        lines.Insert("        \"Someone could notice this.\"");
        lines.Insert("    ],");
        lines.Insert("    \"GardeningActionMessages\": [");
        lines.Insert("        \"Food takes patience.\",");
        lines.Insert("        \"If I live long enough, this might matter.\",");
        lines.Insert("        \"Seeds are hope in a dead place.\",");
        lines.Insert("        \"This could keep me alive later.\"");
        lines.Insert("    ],");
        lines.Insert("    \"ResourceGatheringMessages\": [");
        lines.Insert("        \"Take what I can use.\",");
        lines.Insert("        \"This might be worth the effort.\",");
        lines.Insert("        \"Tools, fuel, food, anything helps.\",");
        lines.Insert("        \"Do not make too much noise.\"");
        lines.Insert("    ],");
        lines.Insert("    \"LiquidTransferMessages\": [");
        lines.Insert("        \"Do not spill it.\",");
        lines.Insert("        \"Every drop matters.\",");
        lines.Insert("        \"I need clean water more than anything.\",");
        lines.Insert("        \"Fill it now, move later.\"");
        lines.Insert("    ],");
        lines.Insert("    \"FireplaceActionMessages\": [");
        lines.Insert("        \"This fire could save me.\",");
        lines.Insert("        \"Smoke could betray me.\",");
        lines.Insert("        \"Warmth is worth the risk.\",");
        lines.Insert("        \"Keep it small and controlled.\"");
        lines.Insert("    ],");
        lines.Insert("    \"ElectronicsActionMessages\": [");
        lines.Insert("        \"Power still means something.\",");
        lines.Insert("        \"I hope this works.\",");
        lines.Insert("        \"A signal could bring help or danger.\",");
        lines.Insert("        \"Old tech, new risks.\"");
        lines.Insert("    ],");
        lines.Insert("    \"NavigationActionMessages\": [");
        lines.Insert("        \"I need to know where I am.\",");
        lines.Insert("        \"Get bearings before moving.\",");
        lines.Insert("        \"A wrong turn can kill out here.\",");
        lines.Insert("        \"Check the route, then move.\"");
        lines.Insert("    ],");
        lines.Insert("    \"LockActionMessages\": [");
        lines.Insert("        \"Keep it secure.\",");
        lines.Insert("        \"Locks slow people down, not stop them.\",");
        lines.Insert("        \"This might buy time.\",");
        lines.Insert("        \"Someone may still get through.\"");
        lines.Insert("    ],");
        lines.Insert("    \"TrapExplosiveMessages\": [");
        lines.Insert("        \"Careful. One mistake and it is over.\",");
        lines.Insert("        \"This is dangerous work.\",");
        lines.Insert("        \"I need steady hands.\",");
        lines.Insert("        \"This could save me or kill me.\"");
        lines.Insert("    ],");
        lines.Insert("    \"BaseBuildingActionMessages\": [");
        lines.Insert("        \"This might keep someone out.\",");
        lines.Insert("        \"It will not stop everyone, but it helps.\",");
        lines.Insert("        \"A wall is only as strong as the time behind it.\",");
        lines.Insert("        \"Do not make this place too obvious.\"");
        lines.Insert("    ],");
        lines.Insert("    \"VehicleActionMessages\": [");
        lines.Insert("        \"This thing might run if I can keep it together.\",");
        lines.Insert("        \"Every part matters.\",");
        lines.Insert("        \"A working vehicle changes everything.\",");
        lines.Insert("        \"Noise and speed both attract trouble.\"");
        lines.Insert("    ],");
        lines.Insert("    \"BuryStashMessages\": [");
        lines.Insert("        \"Hide it well.\",");
        lines.Insert("        \"If someone finds this, I lose everything.\",");
        lines.Insert("        \"The ground keeps secrets for a while.\",");
        lines.Insert("        \"I need to remember this place.\"");
        lines.Insert("    ],");
        lines.Insert("    \"PersonalCareMessages\": [");
        lines.Insert("        \"Small things still matter.\",");
        lines.Insert("        \"Clean up before it gets worse.\",");
        lines.Insert("        \"Ignore yourself and the world wins.\",");
        lines.Insert("        \"Take care of the body that carries you.\"");
        lines.Insert("    ],");
        lines.Insert("    \"AmmoManagementMessages\": [");
        lines.Insert("        \"Every round matters.\",");
        lines.Insert("        \"Count it twice.\",");
        lines.Insert("        \"Do not waste ammunition.\",");
        lines.Insert("        \"Empty magazines get people killed.\"");
        lines.Insert("    ],");
        lines.Insert("    \"OpenCloseActionMessages\": [");
        lines.Insert("        \"Do it quietly.\",");
        lines.Insert("        \"Check the other side.\",");
        lines.Insert("        \"Every door is a risk.\",");
        lines.Insert("        \"Open it slow.\"");
        lines.Insert("    ],");
        lines.Insert("    \"GeneralActionMessages\": [");
        lines.Insert("        \"Keep moving.\",");
        lines.Insert("        \"Stay alert.\",");
        lines.Insert("        \"Do not make noise.\",");
        lines.Insert("        \"Finish this and move on.\"");
        lines.Insert("    ],");
        lines.Insert("    \"InventoryActionMessages\": [");
        lines.Insert("        \"Keep moving.\",");
        lines.Insert("        \"Stay alert.\",");
        lines.Insert("        \"Do not make noise.\",");
        lines.Insert("        \"Finish this and move on.\"");
        lines.Insert("    ],");
        lines.Insert("    \"MovementActionMessages\": [");
        lines.Insert("        \"Keep moving.\",");
        lines.Insert("        \"Stay alert.\",");
        lines.Insert("        \"Do not make noise.\",");
        lines.Insert("        \"Finish this and move on.\"");
        lines.Insert("    ],");
        lines.Insert("    \"WorldInteractionMessages\": [");
        lines.Insert("        \"Keep moving.\",");
        lines.Insert("        \"Stay alert.\",");
        lines.Insert("        \"Do not make noise.\",");
        lines.Insert("        \"Finish this and move on.\"");
        lines.Insert("    ],");
        lines.Insert("    \"OpenCloseActionCooldownSeconds\": 2.5,");
        lines.Insert("    \"EnableDamageReactionThoughts\": 1,");
        lines.Insert("    \"EnableBleedingReactionThoughts\": 1,");
        lines.Insert("    \"EnableZombieHitMessages\": 1,");
        lines.Insert("    \"EnablePlayerMeleeHitMessages\": 1,");
        lines.Insert("    \"EnableGunshotHitMessages\": 1,");
        lines.Insert("    \"EnableExplosionHitMessages\": 1,");
        lines.Insert("    \"EnableHeavyHitMessages\": 1,");
        lines.Insert("    \"EnableBleedingStartedMessages\": 1,");
        lines.Insert("    \"EnableBleedingWorseMessages\": 1,");
        lines.Insert("    \"EnableBleedingStoppedMessages\": 1,");
        lines.Insert("    \"HeavyHitHealthDamage_Min\": 25.0,");
        lines.Insert("    \"HeavyHitBloodDamage_Min\": 300.0,");
        lines.Insert("    \"HeavyHitShockDamage_Min\": 35.0,");
        lines.Insert("    \"ZombieHitMessages\": [");
        lines.Insert("        \"An infected hit me.\",");
        lines.Insert("        \"It got too close.\",");
        lines.Insert("        \"I need to keep distance from them.\",");
        lines.Insert("        \"That infected nearly tore into me.\",");
        lines.Insert("        \"Do not let them surround me.\"");
        lines.Insert("    ],");
        lines.Insert("    \"PlayerMeleeHitMessages\": [");
        lines.Insert("        \"Someone hit me.\",");
        lines.Insert("        \"They are too close.\",");
        lines.Insert("        \"I need space before they swing again.\",");
        lines.Insert("        \"Move. Do not let them pin me down.\",");
        lines.Insert("        \"I need to break contact.\"");
        lines.Insert("    ],");
        lines.Insert("    \"GunshotHitMessages\": [");
        lines.Insert("        \"I have been shot.\",");
        lines.Insert("        \"That round hit me.\",");
        lines.Insert("        \"I need cover now.\",");
        lines.Insert("        \"Someone has eyes on me.\",");
        lines.Insert("        \"I cannot stay in the open.\"");
        lines.Insert("    ],");
        lines.Insert("    \"ExplosionHitMessages\": [");
        lines.Insert("        \"The blast hit me hard.\",");
        lines.Insert("        \"My ears are ringing.\",");
        lines.Insert("        \"Everything is spinning.\",");
        lines.Insert("        \"I need to get away from here.\",");
        lines.Insert("        \"That nearly ended me.\"");
        lines.Insert("    ],");
        lines.Insert("    \"HeavyHitMessages\": [");
        lines.Insert("        \"That hit hard.\",");
        lines.Insert("        \"My body is screaming.\",");
        lines.Insert("        \"I cannot take another hit like that.\",");
        lines.Insert("        \"I need to get out of this fight.\",");
        lines.Insert("        \"I need a second to recover.\"");
        lines.Insert("    ],");
        lines.Insert("    \"BleedingStartedMessages\": [");
        lines.Insert("        \"I am bleeding.\",");
        lines.Insert("        \"That opened me up.\",");
        lines.Insert("        \"Blood is running down my body.\",");
        lines.Insert("        \"I need to bandage this now.\",");
        lines.Insert("        \"This wound is not closing itself.\"");
        lines.Insert("    ],");
        lines.Insert("    \"BleedingWorseMessages\": [");
        lines.Insert("        \"I am bleeding from more than one wound.\",");
        lines.Insert("        \"There is too much blood.\",");
        lines.Insert("        \"I need to stop the bleeding before I pass out.\",");
        lines.Insert("        \"This is getting bad fast.\",");
        lines.Insert("        \"I cannot keep losing blood like this.\"");
        lines.Insert("    ],");
        lines.Insert("    \"BleedingStoppedMessages\": [");
        lines.Insert("        \"The bleeding has stopped.\",");
        lines.Insert("        \"That should hold for now.\",");
        lines.Insert("        \"At least I am not bleeding anymore.\",");
        lines.Insert("        \"That was too close.\",");
        lines.Insert("        \"I need to be more careful.\"");
        lines.Insert("    ],");
        lines.Insert("    \"EnableNearMissCombatMessages\": 1,");
        lines.Insert("    \"NearMissCombatCooldownSeconds\": 45.0,");
        lines.Insert("    \"NearMissCombatChance\": 0.35,");
        lines.Insert("    \"NearMissBulletMessages\": [");
        lines.Insert("        \"That snapped past my head.\",");
        lines.Insert("        \"Too close. Move now.\",");
        lines.Insert("        \"Someone has the range.\",");
        lines.Insert("        \"That shot was not random.\"");
        lines.Insert("    ],");
        lines.Insert("    \"NearMissExplosionMessages\": [");
        lines.Insert("        \"The blast was too close.\",");
        lines.Insert("        \"Fragments found everything except me.\",");
        lines.Insert("        \"Move before the next one lands.\",");
        lines.Insert("        \"That explosion was a warning I survived.\"");
        lines.Insert("    ],");
        lines.Insert("    \"NearMissCombatGeneralMessages\": [");
        lines.Insert("        \"That was too close.\",");
        lines.Insert("        \"I nearly lost it there.\",");
        lines.Insert("        \"Do not freeze now.\",");
        lines.Insert("        \"Someone almost had me.\"");
        lines.Insert("    ]");
        lines.Insert("}");

        ST_WriteDefaultJsonFile(filePath, lines);
        Log("Created default consolidated config: " + filePath);
    }

    void ST_CreateDefault_04_World_Environment_json(string folderPath)
    {
        string filePath = folderPath + "/04_World_Environment.json";
        if (FileExist(filePath))
            return;

        array<string> lines = new array<string>;
        lines.Insert("{");
        lines.Insert("    \"EnableWeatherThoughts\": 1,");
        lines.Insert("    \"RainThought_Min\": 0.35,");
        lines.Insert("    \"FogThought_Min\": 0.45,");
        lines.Insert("    \"WindThought_Min\": 8.0,");
        lines.Insert("    \"StormRain_Min\": 0.65,");
        lines.Insert("    \"StormWind_Min\": 10.0,");
        lines.Insert("    \"StormOvercast_Min\": 0.9,");
        lines.Insert("    \"WeatherRainMessages\": [");
        lines.Insert("        \"This rain is soaking through everything.\",");
        lines.Insert("        \"I need to get dry before the cold settles in.\",");
        lines.Insert("        \"The rain makes every step feel heavier.\",");
        lines.Insert("        \"Wet clothes will make the cold worse.\"");
        lines.Insert("    ],");
        lines.Insert("    \"WeatherFogMessages\": [");
        lines.Insert("        \"The fog is hiding too much.\",");
        lines.Insert("        \"I cannot see far enough to feel safe.\",");
        lines.Insert("        \"Anything could be moving out there.\",");
        lines.Insert("        \"The world disappears a few steps ahead.\"");
        lines.Insert("    ],");
        lines.Insert("    \"WeatherWindMessages\": [");
        lines.Insert("        \"The wind makes it hard to hear anything moving.\",");
        lines.Insert("        \"Every branch sounds like footsteps in this wind.\",");
        lines.Insert("        \"The trees are too loud today.\",");
        lines.Insert("        \"This wind hides too much noise.\"");
        lines.Insert("    ],");
        lines.Insert("    \"WeatherStormMessages\": [");
        lines.Insert("        \"The storm makes it hard to hear anything.\",");
        lines.Insert("        \"This weather could hide me, or someone else.\",");
        lines.Insert("        \"I should find shelter before this gets worse.\",");
        lines.Insert("        \"The sky sounds angry enough to cover gunfire.\"");
        lines.Insert("    ],");
        lines.Insert("    \"EnableLocationThoughts\": 1,");
        lines.Insert("    \"LocationThoughtCooldownSeconds\": 240.0,");
        lines.Insert("    \"LocationThoughtChance\": 0.35,");
        lines.Insert("    \"LocationUseCustomZones\": 1,");
        lines.Insert("    \"LocationUseFallbackDetection\": 1,");
        lines.Insert("    \"LocationCoastZMax\": 3500.0,");
        lines.Insert("    \"LocationWildernessScanRadius\": 80.0,");
        lines.Insert("    \"LocationWildernessMaxObjects\": 8,");
        lines.Insert("    \"LocationZones\": [],");
        lines.Insert("    \"LocationCoastMessages\": [");
        lines.Insert("        \"The coast is where everyone starts, and where too many people die.\",");
        lines.Insert("        \"I should not stay near the coast for long.\",");
        lines.Insert("        \"Fresh tracks, empty houses, and bad decisions. That is the coast.\",");
        lines.Insert("        \"The sea is behind me. Survival is inland.\"");
        lines.Insert("    ],");
        lines.Insert("    \"LocationTownMessages\": [");
        lines.Insert("        \"This town feels picked clean.\",");
        lines.Insert("        \"Every window feels like it is watching me.\",");
        lines.Insert("        \"Small towns are quiet until they are not.\",");
        lines.Insert("        \"There might still be something useful here.\"");
        lines.Insert("    ],");
        lines.Insert("    \"LocationCityMessages\": [");
        lines.Insert("        \"Too many buildings. Too many angles.\",");
        lines.Insert("        \"A city can hide supplies, infected, and people with bad intentions.\",");
        lines.Insert("        \"I do not like how many windows overlook these streets.\",");
        lines.Insert("        \"The bigger the city, the more chances to die.\"");
        lines.Insert("    ],");
        lines.Insert("    \"LocationForestMessages\": [");
        lines.Insert("        \"The trees might keep me hidden.\",");
        lines.Insert("        \"The forest is safer, but it gives nothing for free.\",");
        lines.Insert("        \"I can disappear here if I stay quiet.\",");
        lines.Insert("        \"Every branch snap sounds louder out here.\"");
        lines.Insert("    ],");
        lines.Insert("    \"LocationWildernessMessages\": [");
        lines.Insert("        \"There is nothing out here but distance and bad weather.\",");
        lines.Insert("        \"If I get hurt out here, nobody will find me.\",");
        lines.Insert("        \"The wilderness hides me, but it can starve me too.\",");
        lines.Insert("        \"I need to know where the next water source is.\"");
        lines.Insert("    ],");
        lines.Insert("    \"LocationMilitaryMessages\": [");
        lines.Insert("        \"Military places always smell like trouble.\",");
        lines.Insert("        \"Good gear brings bad company.\",");
        lines.Insert("        \"Someone else will come here looking for weapons.\",");
        lines.Insert("        \"I should assume I am being watched.\"");
        lines.Insert("    ],");
        lines.Insert("    \"LocationPoliceMessages\": [");
        lines.Insert("        \"Police stations are never as empty as they look.\",");
        lines.Insert("        \"There might be ammunition here, or someone waiting for it.\",");
        lines.Insert("        \"I should check the corners.\",");
        lines.Insert("        \"This place attracts desperate people.\"");
        lines.Insert("    ],");
        lines.Insert("    \"LocationMedicalMessages\": [");
        lines.Insert("        \"Hospitals always mean someone desperate came here first.\",");
        lines.Insert("        \"Medicine is worth the risk.\",");
        lines.Insert("        \"If anything is left, it will not be much.\",");
        lines.Insert("        \"I need to move fast. Everyone needs medical supplies.\"");
        lines.Insert("    ],");
        lines.Insert("    \"LocationIndustrialMessages\": [");
        lines.Insert("        \"Rust, metal, and hiding places everywhere.\",");
        lines.Insert("        \"Industrial yards always have too many blind corners.\",");
        lines.Insert("        \"Tools might be worth the risk.\",");
        lines.Insert("        \"I should listen before crossing the open ground.\"");
        lines.Insert("    ],");
        lines.Insert("    \"LocationFarmMessages\": [");
        lines.Insert("        \"A farm might mean food, tools, or nothing at all.\",");
        lines.Insert("        \"The open fields make me feel exposed.\",");
        lines.Insert("        \"Barns hide more than hay now.\",");
        lines.Insert("        \"There may be animals nearby.\"");
        lines.Insert("    ],");
        lines.Insert("    \"LocationWaterMessages\": [");
        lines.Insert("        \"Water means life, and footsteps.\",");
        lines.Insert("        \"Someone else may come here to drink.\",");
        lines.Insert("        \"I should fill everything I can.\",");
        lines.Insert("        \"A water source is useful, but it is never truly safe.\"");
        lines.Insert("    ],");
        lines.Insert("    \"EnableMapEnvironmentPacks\": 1,");
        lines.Insert("    \"ActiveMapEnvironmentPack\": \"Generic\",");
        lines.Insert("    \"MapEnvironmentThoughtChance\": 0.2,");
        lines.Insert("    \"MapEnvironmentThoughtCooldownSeconds\": 600.0,");
        lines.Insert("    \"MapChernarusMessages\": [");
        lines.Insert("        \"Chernarus always feels like it is watching from the treeline.\",");
        lines.Insert("        \"Every town here has learned to stay quiet.\",");
        lines.Insert("        \"The coast gives nothing for free.\",");
        lines.Insert("        \"The hills remember every gunshot.\"");
        lines.Insert("    ],");
        lines.Insert("    \"MapLivoniaMessages\": [");
        lines.Insert("        \"Livonia's forests make every sound feel closer.\",");
        lines.Insert("        \"The green hides more than it shows.\",");
        lines.Insert("        \"Every clearing feels like a question.\",");
        lines.Insert("        \"The trees here make good cover for everyone.\"");
        lines.Insert("    ],");
        lines.Insert("    \"MapNamalskMessages\": [");
        lines.Insert("        \"The cold here is not weather. It is a predator.\",");
        lines.Insert("        \"Namalsk does not forgive mistakes.\",");
        lines.Insert("        \"This island wants heat, blood, or both.\",");
        lines.Insert("        \"Every exposed minute feels borrowed.\"");
        lines.Insert("    ],");
        lines.Insert("    \"MapSakhalMessages\": [");
        lines.Insert("        \"Sakhal feels like it is trying to freeze me in place.\",");
        lines.Insert("        \"The island cold gets under everything.\",");
        lines.Insert("        \"The sea air makes the silence sharper.\",");
        lines.Insert("        \"Warmth matters more here than pride.\"");
        lines.Insert("    ],");
        lines.Insert("    \"MapDeerIsleMessages\": [");
        lines.Insert("        \"This island hides stories in every road.\",");
        lines.Insert("        \"The coast is beautiful enough to be dangerous.\",");
        lines.Insert("        \"Something about this place feels staged.\",");
        lines.Insert("        \"Deer Isle has too many quiet corners.\"");
        lines.Insert("    ],");
        lines.Insert("    \"MapGenericMessages\": [");
        lines.Insert("        \"This place has survived worse than me.\",");
        lines.Insert("        \"The land keeps its own secrets.\",");
        lines.Insert("        \"Every road leads to somebody's mistake.\",");
        lines.Insert("        \"I should learn the shape of this place before it learns mine.\"");
        lines.Insert("    ],");
        lines.Insert("    \"EnableShelterThoughts\": 1,");
        lines.Insert("    \"ShelterThoughtCooldownSeconds\": 300.0,");
        lines.Insert("    \"ShelterThoughtChance\": 0.3,");
        lines.Insert("    \"ShelterScanRadius\": 14.0,");
        lines.Insert("    \"ShelterNearbyBuildingCountRequired\": 1,");
        lines.Insert("    \"ShelterSafeMessages\": [");
        lines.Insert("        \"Four walls help, but they do not make me safe.\",");
        lines.Insert("        \"This place might give me a moment to think.\",");
        lines.Insert("        \"Shelter is useful. Exits matter more.\",");
        lines.Insert("        \"I should check every corner before trusting this place.\"");
        lines.Insert("    ],");
        lines.Insert("    \"ShelterUnsafeMessages\": [");
        lines.Insert("        \"This building could already belong to someone else.\",");
        lines.Insert("        \"Closed rooms hide bad surprises.\",");
        lines.Insert("        \"I need an exit plan before I relax.\",");
        lines.Insert("        \"Shelter can become a trap fast.\"");
        lines.Insert("    ],");
        lines.Insert("    \"ShelterBadWeatherMessages\": [");
        lines.Insert("        \"At least this place can keep some weather off me.\",");
        lines.Insert("        \"I need to dry out while I can.\",");
        lines.Insert("        \"Bad weather makes shelter worth the risk.\",");
        lines.Insert("        \"This cover might save my temperature.\"");
        lines.Insert("    ],");
        lines.Insert("    \"ShelterNightMessages\": [");
        lines.Insert("        \"Night makes every doorway feel dangerous.\",");
        lines.Insert("        \"If I stay here, I need to secure the exits.\",");
        lines.Insert("        \"This place is better than standing outside in the dark.\",");
        lines.Insert("        \"I should listen before I move through the rooms.\"");
        lines.Insert("    ],");
        lines.Insert("    \"EnableCustomThoughtZones\": 1,");
        lines.Insert("    \"CustomThoughtZoneDefaultCooldownSeconds\": 600.0,");
        lines.Insert("    \"CustomThoughtZoneDefaultChance\": 0.35,");
        lines.Insert("    \"CustomThoughtZones\": [");
        lines.Insert("        {");
        lines.Insert("            \"Name\": \"Example Haunted Camp\",");
        lines.Insert("            \"Type\": \"Horror\",");
        lines.Insert("            \"X\": 4500.0,");
        lines.Insert("            \"Z\": 10200.0,");
        lines.Insert("            \"Radius\": 150.0,");
        lines.Insert("            \"Chance\": 0.35,");
        lines.Insert("            \"CooldownSeconds\": 600.0,");
        lines.Insert("            \"Messages\": [");
        lines.Insert("                \"Something is wrong with this place.\",");
        lines.Insert("                \"I should not stay here longer than I need to.\",");
        lines.Insert("                \"This camp feels abandoned for a reason.\",");
        lines.Insert("                \"Every quiet corner here feels watched.\"");
        lines.Insert("            ]");
        lines.Insert("        }");
        lines.Insert("    ]");
        lines.Insert("}");

        ST_WriteDefaultJsonFile(filePath, lines);
        Log("Created default consolidated config: " + filePath);
    }

    void ST_CreateDefault_05_Items_Corpses_json(string folderPath)
    {
        string filePath = folderPath + "/05_Items_Corpses.json";
        if (FileExist(filePath))
            return;

        array<string> lines = new array<string>;
        lines.Insert("{");
        lines.Insert("    \"EnableItemConditionThoughts\": 1,");
        lines.Insert("    \"ItemConditionHealthThreshold\": 0.35,");
        lines.Insert("    \"ScanEquippedItemsForDamagedThoughts\": 1,");
        lines.Insert("    \"EnableHandsItemConditionMessages\": 1,");
        lines.Insert("    \"EnableWeaponConditionMessages\": 1,");
        lines.Insert("    \"EnableClothingConditionMessages\": 1,");
        lines.Insert("    \"EnableShoesConditionMessages\": 1,");
        lines.Insert("    \"EnableBackpackConditionMessages\": 1,");
        lines.Insert("    \"EnableVestConditionMessages\": 1,");
        lines.Insert("    \"EnableHeadgearConditionMessages\": 1,");
        lines.Insert("    \"EnableGlovesConditionMessages\": 1,");
        lines.Insert("    \"EnableMaskConditionMessages\": 1,");
        lines.Insert("    \"EnableBeltConditionMessages\": 1,");
        lines.Insert("    \"ItemBadlyDamagedMessages\": [");
        lines.Insert("        \"This gear will not last much longer.\",");
        lines.Insert("        \"My equipment is falling apart.\",");
        lines.Insert("        \"I should repair this before it fails me.\",");
        lines.Insert("        \"Nothing lasts out here without care.\"");
        lines.Insert("    ],");
        lines.Insert("    \"ItemWeaponDamagedMessages\": [");
        lines.Insert("        \"This weapon needs maintenance.\",");
        lines.Insert("        \"I do not trust this weapon in its current state.\",");
        lines.Insert("        \"One jam at the wrong time could kill me.\",");
        lines.Insert("        \"I should clean or repair this before a fight.\"");
        lines.Insert("    ],");
        lines.Insert("    \"ItemShoesDamagedMessages\": [");
        lines.Insert("        \"My boots are falling apart.\",");
        lines.Insert("        \"My feet are going to suffer if I do not fix these.\",");
        lines.Insert("        \"Bad shoes will get me killed slowly.\",");
        lines.Insert("        \"Every step is wearing these down.\"");
        lines.Insert("    ],");
        lines.Insert("    \"ItemClothingDamagedMessages\": [");
        lines.Insert("        \"My clothes are barely holding together.\",");
        lines.Insert("        \"This clothing will not protect me much longer.\",");
        lines.Insert("        \"The fabric is torn and useless in places.\",");
        lines.Insert("        \"I need to patch this before the weather gets worse.\"");
        lines.Insert("    ],");
        lines.Insert("    \"ItemBackpackDamagedMessages\": [");
        lines.Insert("        \"My backpack is falling apart.\",");
        lines.Insert("        \"If this pack gives out, I lose everything.\",");
        lines.Insert("        \"The straps feel weak.\",");
        lines.Insert("        \"I should repair this bag before it splits.\"");
        lines.Insert("    ],");
        lines.Insert("    \"ItemVestDamagedMessages\": [");
        lines.Insert("        \"My vest has taken a beating.\",");
        lines.Insert("        \"This vest will not protect me much longer.\",");
        lines.Insert("        \"I should repair this before trusting it.\",");
        lines.Insert("        \"The damage is starting to show.\"");
        lines.Insert("    ],");
        lines.Insert("    \"ItemHeadgearDamagedMessages\": [");
        lines.Insert("        \"My headgear is barely holding up.\",");
        lines.Insert("        \"This helmet has seen better days.\",");
        lines.Insert("        \"I should not trust this to stop much.\",");
        lines.Insert("        \"One more hit could ruin it.\"");
        lines.Insert("    ],");
        lines.Insert("    \"ItemGlovesDamagedMessages\": [");
        lines.Insert("        \"My gloves are wearing thin.\",");
        lines.Insert("        \"My hands need better protection.\",");
        lines.Insert("        \"These gloves will not last.\",");
        lines.Insert("        \"Cold and cuts will get through soon.\"");
        lines.Insert("    ],");
        lines.Insert("    \"ItemMaskDamagedMessages\": [");
        lines.Insert("        \"My mask is in bad shape.\",");
        lines.Insert("        \"I should not trust this mask much longer.\",");
        lines.Insert("        \"The seal feels wrong.\",");
        lines.Insert("        \"This needs replacing before it matters.\"");
        lines.Insert("    ],");
        lines.Insert("    \"ItemBeltDamagedMessages\": [");
        lines.Insert("        \"My belt is coming apart.\",");
        lines.Insert("        \"If this gives out, I lose gear.\",");
        lines.Insert("        \"The fastening feels weak.\",");
        lines.Insert("        \"I should repair this before moving far.\"");
        lines.Insert("    ],");
        lines.Insert("    \"EnableNearbyCorpseThoughts\": 1,");
        lines.Insert("    \"NearbyCorpseRadius\": 35.0,");
        lines.Insert("    \"NearbyCorpseMessages\": [");
        lines.Insert("        \"Someone died here recently.\",");
        lines.Insert("        \"This was not long ago.\",");
        lines.Insert("        \"I should not stay near the body.\",");
        lines.Insert("        \"Where there is one corpse, there may be another.\"");
        lines.Insert("    ],");
        lines.Insert("    \"NearbyPlayerCorpseMessages\": [");
        lines.Insert("        \"That was a survivor.\",");
        lines.Insert("        \"Someone ended up here before me.\",");
        lines.Insert("        \"I should find out what killed them before it finds me.\",");
        lines.Insert("        \"A dead survivor means danger passed through.\"");
        lines.Insert("    ],");
        lines.Insert("    \"NearbyInfectedCorpseMessages\": [");
        lines.Insert("        \"An infected dropped here.\",");
        lines.Insert("        \"Something killed this infected.\",");
        lines.Insert("        \"Dead infected usually mean someone passed through.\",");
        lines.Insert("        \"This place may not be as empty as it looks.\"");
        lines.Insert("    ],");
        lines.Insert("    \"NearbyAnimalCorpseMessages\": [");
        lines.Insert("        \"Fresh meat, or fresh danger.\",");
        lines.Insert("        \"Something killed this animal.\",");
        lines.Insert("        \"This carcass might draw attention.\",");
        lines.Insert("        \"I should not stand around it for long.\"");
        lines.Insert("    ]");
        lines.Insert("}");

        ST_WriteDefaultJsonFile(filePath, lines);
        Log("Created default consolidated config: " + filePath);
    }

    void ST_CreateDefault_06_Social_Sanity_Journal_json(string folderPath)
    {
        string filePath = folderPath + "/06_Social_Sanity_Journal.json";
        if (FileExist(filePath))
            return;

        array<string> lines = new array<string>;
        lines.Insert("{");
        lines.Insert("    \"EnableSocialGroupThoughts\": 1,");
        lines.Insert("    \"SocialGroupThoughtCooldownSeconds\": 240.0,");
        lines.Insert("    \"SocialGroupThoughtChance\": 0.35,");
        lines.Insert("    \"SocialNearbyPlayerRadius\": 45.0,");
        lines.Insert("    \"SocialFriendlyTimeRequiredSeconds\": 300.0,");
        lines.Insert("    \"SocialMemoryDurationSeconds\": 900.0,");
        lines.Insert("    \"LoneWolfNoPlayerSeenSeconds\": 10800.0,");
        lines.Insert("    \"EnableTeammateShotMessages\": 1,");
        lines.Insert("    \"EnableTeammateDownMessages\": 1,");
        lines.Insert("    \"EnableLoneWolfMessages\": 1,");
        lines.Insert("    \"EnableFriendlyNearbyMessages\": 1,");
        lines.Insert("    \"TeammateShotMessages\": [");
        lines.Insert("        \"They hit them. Move, now.\",");
        lines.Insert("        \"No, no, no. Stay with me.\",");
        lines.Insert("        \"Someone just dropped my cover.\",");
        lines.Insert("        \"I cannot lose them here.\",");
        lines.Insert("        \"That shot was meant to split us apart.\",");
        lines.Insert("        \"Keep them alive. Think later.\"");
        lines.Insert("    ],");
        lines.Insert("    \"TeammateDownMessages\": [");
        lines.Insert("        \"No, no, no! Hang on, do not die on me.\",");
        lines.Insert("        \"I am completely on my own now.\",");
        lines.Insert("        \"They were right beside me a second ago.\",");
        lines.Insert("        \"Do not leave me out here alone.\",");
        lines.Insert("        \"I should have covered them better.\",");
        lines.Insert("        \"Their silence is louder than the gunshot.\"");
        lines.Insert("    ],");
        lines.Insert("    \"LoneWolfMessages\": [");
        lines.Insert("        \"I have not talked to anyone in days.\",");
        lines.Insert("        \"I am starting to forget what my own voice sounds like.\",");
        lines.Insert("        \"No footsteps but mine. That should feel safer than it does.\",");
        lines.Insert("        \"Being alone keeps me alive, until it does not.\",");
        lines.Insert("        \"The silence is beginning to feel like company.\",");
        lines.Insert("        \"I wonder if there is anyone left worth trusting.\"");
        lines.Insert("    ],");
        lines.Insert("    \"FriendlyNearbyMessages\": [");
        lines.Insert("        \"Another set of eyes makes the road feel shorter.\",");
        lines.Insert("        \"Stay close. Wandering off gets people killed.\",");
        lines.Insert("        \"I need to keep track of them.\",");
        lines.Insert("        \"Two people make more noise, but fewer mistakes.\",");
        lines.Insert("        \"Trust is useful. Dangerous, but useful.\",");
        lines.Insert("        \"If this goes bad, I am not the only one at risk.\"");
        lines.Insert("    ],");
        lines.Insert("    \"EnableStealthNoiseThoughts\": 1,");
        lines.Insert("    \"StealthNoiseThoughtCooldownSeconds\": 180.0,");
        lines.Insert("    \"StealthNoiseThoughtChance\": 0.35,");
        lines.Insert("    \"StealthNoiseInfectedRadius\": 35.0,");
        lines.Insert("    \"StealthNoiseRunSpeedThreshold\": 3.2,");
        lines.Insert("    \"StealthNoiseInfectedNearbyMessages\": [");
        lines.Insert("        \"Too much noise will pull them straight to me.\",");
        lines.Insert("        \"Slow down. The infected are close enough to hear.\",");
        lines.Insert("        \"Every step matters when they are this near.\",");
        lines.Insert("        \"Quiet movement keeps me alive longer than speed.\"");
        lines.Insert("    ],");
        lines.Insert("    \"StealthNoiseNightMessages\": [");
        lines.Insert("        \"Sound feels louder in the dark.\",");
        lines.Insert("        \"At night, one bad step can give me away.\",");
        lines.Insert("        \"I should move like someone is listening.\",");
        lines.Insert("        \"The dark hides me, but it hides everyone else too.\"");
        lines.Insert("    ],");
        lines.Insert("    \"StealthNoiseMilitaryMessages\": [");
        lines.Insert("        \"Running through a military zone is asking to be heard.\",");
        lines.Insert("        \"Slow, quiet, and ready. That is how I leave here.\",");
        lines.Insert("        \"Noise here travels to the wrong people.\",");
        lines.Insert("        \"Good gear brings bad company. I should move carefully.\"");
        lines.Insert("    ],");
        lines.Insert("    \"EnableSanityCreep\": 1,");
        lines.Insert("    \"SanityThoughtCooldownSeconds\": 300.0,");
        lines.Insert("    \"SanityThoughtChance\": 0.3,");
        lines.Insert("    \"StartingSanity\": 100.0,");
        lines.Insert("    \"MinimumSanity\": 0.0,");
        lines.Insert("    \"SanityLossSkinHuman\": 18.0,");
        lines.Insert("    \"SanityLossEatHumanMeat\": 25.0,");
        lines.Insert("    \"SanityLossKillRestrainedPlayer\": 35.0,");
        lines.Insert("    \"SanityRegenPerMinute\": 0.0,");
        lines.Insert("    \"SanityUneasyThreshold\": 70.0,");
        lines.Insert("    \"SanityUnhingedThreshold\": 35.0,");
        lines.Insert("    \"SanityPsychoticThreshold\": 15.0,");
        lines.Insert("    \"EnableSanityUneasyMessages\": 1,");
        lines.Insert("    \"EnableSanityUnhingedMessages\": 1,");
        lines.Insert("    \"EnableSanityPsychoticMessages\": 1,");
        lines.Insert("    \"EnableCannibalismCreepMessages\": 1,");
        lines.Insert("    \"SanityUneasyMessages\": [");
        lines.Insert("        \"I need to keep my head clear.\",");
        lines.Insert("        \"Something about this is staying with me.\",");
        lines.Insert("        \"My hands will not stop shaking.\",");
        lines.Insert("        \"I should not think about what I have done.\",");
        lines.Insert("        \"Breathe. Count supplies. Keep moving.\",");
        lines.Insert("        \"There are lines out here. I can still see them.\"");
        lines.Insert("    ],");
        lines.Insert("    \"SanityUnhingedMessages\": [");
        lines.Insert("        \"Their faces keep coming back when I close my eyes.\",");
        lines.Insert("        \"I keep hearing things that are not there.\",");
        lines.Insert("        \"The silence laughs at me.\",");
        lines.Insert("        \"I am still in control. I have to be.\",");
        lines.Insert("        \"I did what I had to do. That is what I keep telling myself.\",");
        lines.Insert("        \"Every bad choice feels easier than the last.\"");
        lines.Insert("    ],");
        lines.Insert("    \"SanityPsychoticMessages\": [");
        lines.Insert("        \"The giggling... I can hear it even when I am not laughing.\",");
        lines.Insert("        \"Their faces. Why do I keep seeing their faces?\",");
        lines.Insert("        \"Maybe the dead are the only honest ones now.\",");
        lines.Insert("        \"I do not remember when this started feeling normal.\",");
        lines.Insert("        \"Something in me broke quietly.\",");
        lines.Insert("        \"I should be horrified. I am not.\"");
        lines.Insert("    ],");
        lines.Insert("    \"CannibalismCreepMessages\": [");
        lines.Insert("        \"That was a person. I know that.\",");
        lines.Insert("        \"There are some hungers that should stay empty.\",");
        lines.Insert("        \"I can still taste what I should not have eaten.\",");
        lines.Insert("        \"My stomach accepts what my mind refuses.\",");
        lines.Insert("        \"The worst part is that it helped.\",");
        lines.Insert("        \"I crossed something I cannot uncross.\"");
        lines.Insert("    ],");
        lines.Insert("    \"EnablePlayerJournals\": 1,");
        lines.Insert("    \"PlayerJournalFolder\": \"$mission:storage_1/ZombiCideMods/SurvivorThoughts/Journals\",");
        lines.Insert("    \"JournalOnlyMajorEvents\": 1,");
        lines.Insert("    \"JournalIncludePlayerStats\": 1,");
        lines.Insert("    \"JournalWriteAllRecoveryEvents\": 1,");
        lines.Insert("    \"JournalWriteSanityEvents\": 1,");
        lines.Insert("    \"JournalWriteSocialEvents\": 1,");
        lines.Insert("    \"JournalWriteNearDeathEvents\": 1,");
        lines.Insert("    \"EnableSurvivorJournalItem\": 1,");
        lines.Insert("    \"GiveJournalOnFreshSpawn\": 1,");
        lines.Insert("    \"DropJournalOnDeath\": 1,");
        lines.Insert("    \"AutoEquipJournalOnFreshSpawn\": 1,");
        lines.Insert("    \"AutoEquipJournalOnLoginIfMissing\": 1,");
        lines.Insert("    \"LockJournalToPlayerWhileAlive\": 1,");
        lines.Insert("    \"AllowJournalLootingAfterDeath\": 1,");
        lines.Insert("    \"DeleteJournalIfRemovedWhileAlive\": 1,");
        lines.Insert("    \"WriteJournalDeathEntryOnKilled\": 1,");
        lines.Insert("    \"JournalRequiredBeforeNormalPlay\": 0,");
        lines.Insert("    \"AllowReadingOtherPlayersJournals\": 1,");
        lines.Insert("    \"RequireJournalSetupMenu\": 0,");
        lines.Insert("    \"ShowJournalSetupMenuOnlyOnFreshCharacter\": 0,");
        lines.Insert("    \"AllowJournalSetupSkip\": 0,");
        lines.Insert("    \"AllowJournalSetupRandomize\": 0,");
        lines.Insert("    \"PlayerBackstoryDataFile\": \"$mission:storage_1/ZombiCideMods/SurvivorThoughts/Data/PlayerBackstories.json\",");
        lines.Insert("    \"MaxMajorJournalEventsStored\": 25,");
        lines.Insert("    \"JournalBackstoryMinMajorEvents\": 0,");
        lines.Insert("    \"ShowRealPlayerNameInJournal\": 0,");
        lines.Insert("    \"PriorityJournalSystem\": 62,");
        lines.Insert("    \"JournalCharacterTypeOptions\": [");
        lines.Insert("        \"Male\",");
        lines.Insert("        \"Female\"");
        lines.Insert("    ],");
        lines.Insert("    \"JournalHeadTypeOptions\": [");
        lines.Insert("        \"Default head\",");
        lines.Insert("        \"Head 1\",");
        lines.Insert("        \"Head 2\",");
        lines.Insert("        \"Head 3\",");
        lines.Insert("        \"Head 4\",");
        lines.Insert("        \"Head 5\",");
        lines.Insert("        \"Head 6\",");
        lines.Insert("        \"Head 7\",");
        lines.Insert("        \"Head 8\"");
        lines.Insert("    ],");
        lines.Insert("    \"JournalOriginOptions\": [");
        lines.Insert("        \"Chernarus\",");
        lines.Insert("        \"Livonia\",");
        lines.Insert("        \"Sakhal\",");
        lines.Insert("        \"Namalsk\",");
        lines.Insert("        \"Unknown coast\",");
        lines.Insert("        \"Inland settlement\"");
        lines.Insert("    ],");
        lines.Insert("    \"JournalOccupationOptions\": [");
        lines.Insert("        \"rail worker\",");
        lines.Insert("        \"paramedic\",");
        lines.Insert("        \"hunter\",");
        lines.Insert("        \"mechanic\",");
        lines.Insert("        \"teacher\",");
        lines.Insert("        \"dock worker\",");
        lines.Insert("        \"soldier\",");
        lines.Insert("        \"farmer\"");
        lines.Insert("    ],");
        lines.Insert("    \"JournalTraitOptions\": [");
        lines.Insert("        \"practical\",");
        lines.Insert("        \"quiet\",");
        lines.Insert("        \"stubborn\",");
        lines.Insert("        \"cautious\",");
        lines.Insert("        \"angry\",");
        lines.Insert("        \"calm under pressure\",");
        lines.Insert("        \"resourceful\",");
        lines.Insert("        \"distrustful\"");
        lines.Insert("    ],");
        lines.Insert("    \"JournalFearOptions\": [");
        lines.Insert("        \"dying alone\",");
        lines.Insert("        \"being left behind\",");
        lines.Insert("        \"the dark\",");
        lines.Insert("        \"infected crowds\",");
        lines.Insert("        \"starvation\",");
        lines.Insert("        \"silence\"");
        lines.Insert("    ],");
        lines.Insert("    \"JournalGoalOptions\": [");
        lines.Insert("        \"find a safe place\",");
        lines.Insert("        \"reach the next town\",");
        lines.Insert("        \"keep moving north\",");
        lines.Insert("        \"find someone worth trusting\",");
        lines.Insert("        \"survive one more day\",");
        lines.Insert("        \"learn what happened\"");
        lines.Insert("    ],");
        lines.Insert("    \"JournalBackstoryTemplates\": [");
        lines.Insert("        \"{name} came from {origin}, once working as a {occupation}. They were {trait}, skilled at {skill}, but the outbreak left them afraid of {fear}. Their weakness is that they {weakness}. Their line is simple: {moral}. Now they are trying to {goal}.\",");
        lines.Insert("        \"Before everything collapsed, {name} was a {occupation}. People called them {trait}. They survived by {skill}, but {weakness}. They left {origin} after the first panic and now only writes about one thing: {goal}. They still believe they {moral}.\",");
        lines.Insert("        \"{name} does not write much about life before. The few clear notes mention {origin}, {occupation}, {skill}, and a fear of {fear}. The rest is survival. One sentence is underlined twice: {moral}.\"");
        lines.Insert("    ],");
        lines.Insert("    \"EnableJournalSetupSpawnProtection\": 0,");
        lines.Insert("    \"JournalSetupBlockDamageUntilComplete\": 0,");
        lines.Insert("    \"JournalSetupSuppressThoughtsUntilComplete\": 0,");
        lines.Insert("    \"JournalSetupProtectionDebug\": 0,");
        lines.Insert("    \"JournalSetupRestoreStatsWhileActive\": 0,");
        lines.Insert("    \"JournalSetupProtectedHealthValue\": 100.0,");
        lines.Insert("    \"JournalSetupProtectedBloodValue\": 5000.0,");
        lines.Insert("    \"JournalSetupProtectedShockValue\": 100.0,");
        lines.Insert("    \"JournalSetupProtectedEnergyValue\": 5000.0,");
        lines.Insert("    \"JournalSetupProtectedWaterValue\": 5000.0,");
        lines.Insert("    \"JournalSetupProtectedHeatComfortValue\": 0.0,");
        lines.Insert("    \"JournalSetupRestoreStatsWhileActive\": 0,");
        lines.Insert("    \"JournalSetupProtectedHealthValue\": 100.0,");
        lines.Insert("    \"JournalSetupProtectedBloodValue\": 5000.0,");
        lines.Insert("    \"JournalSetupProtectedShockValue\": 100.0,");
        lines.Insert("    \"JournalSetupProtectedEnergyValue\": 5000.0,");
        lines.Insert("    \"JournalSetupProtectedWaterValue\": 5000.0,");
        lines.Insert("    \"JournalSetupProtectedHeatComfortValue\": 0.0,");
        lines.Insert("    \"JournalSkillOptions\": [");
        lines.Insert("        \"first aid\",");
        lines.Insert("        \"repairing engines\",");
        lines.Insert("        \"hunting\",");
        lines.Insert("        \"navigation\",");
        lines.Insert("        \"farming\",");
        lines.Insert("        \"keeping quiet\",");
        lines.Insert("        \"handling weapons\",");
        lines.Insert("        \"scavenging\"");
        lines.Insert("    ],");
        lines.Insert("    \"JournalWeaknessOptions\": [");
        lines.Insert("        \"trusts too easily\",");
        lines.Insert("        \"panics in the dark\",");
        lines.Insert("        \"hates being alone\",");
        lines.Insert("        \"takes unnecessary risks\",");
        lines.Insert("        \"cannot ignore people in trouble\",");
        lines.Insert("        \"holds grudges\",");
        lines.Insert("        \"struggles with hunger\",");
        lines.Insert("        \"freezes under pressure\"");
        lines.Insert("    ],");
        lines.Insert("    \"JournalMoralCodeOptions\": [");
        lines.Insert("        \"will not abandon a friend\",");
        lines.Insert("        \"will not eat human meat\",");
        lines.Insert("        \"avoids killing unless forced\",");
        lines.Insert("        \"protects the weak when possible\",");
        lines.Insert("        \"survival comes before mercy\",");
        lines.Insert("        \"trust must be earned\",");
        lines.Insert("        \"never wastes supplies\",");
        lines.Insert("        \"keeps moving, no matter what\"");
        lines.Insert("    ],");
        lines.Insert("    \"EnableJournalSystemIntegration\": 1,");
        lines.Insert("    \"JournalRecordAllThoughtSystems\": 1,");
        lines.Insert("    \"JournalRecordAmbientSystems\": 0,");
        lines.Insert("    \"JournalRecordBlockedDecisionEvents\": 0,");
        lines.Insert("    \"JournalMajorEventMinPriority\": 55,");
        lines.Insert("    \"JournalMajorEventPrefixWithSystem\": 1,");
        lines.Insert("    \"JournalMajorEventIncludeStats\": 0,");
        lines.Insert("    \"JournalRecordDeathEntries\": 1,");
        lines.Insert("    \"JournalRecordSetupChoices\": 1,");
        lines.Insert("    \"JournalRecordSystemLinkDebug\": 0");
        lines.Insert("}");

        ST_WriteDefaultJsonFile(filePath, lines);
        Log("Created default consolidated config: " + filePath);
    }

    void ST_CreateDefault_07_Admin_Diagnostics_json(string folderPath)
    {
        string filePath = folderPath + "/07_Admin_Diagnostics.json";
        if (FileExist(filePath))
            return;

        array<string> lines = new array<string>;
        lines.Insert("{");
        lines.Insert("    \"EnableThoughtDecisionTrace\": 0,");
        lines.Insert("    \"TraceOnlyBlockedThoughts\": 1,");
        lines.Insert("    \"TraceToDebugLog\": 1,");
        lines.Insert("    \"TraceToMissionStorage\": 0,");
        lines.Insert("    \"DecisionTraceFolder\": \"$mission:storage_1/ZombiCideMods/SurvivorThoughts/Debug/DecisionTrace\",");
        lines.Insert("    \"EnableAdminAnalytics\": 1,");
        lines.Insert("    \"AnalyticsSaveIntervalSeconds\": 300.0,");
        lines.Insert("    \"AnalyticsFolder\": \"$mission:storage_1/ZombiCideMods/SurvivorThoughts/Analytics\",");
        lines.Insert("    \"EnableAnalyticsJsonLines\": 1,");
        lines.Insert("    \"AnalyticsJsonLineFile\": \"$mission:storage_1/ZombiCideMods/SurvivorThoughts/Analytics/SurvivorThoughts_Analytics.jsonl\",");
        lines.Insert("    \"TrackBlockedByPriority\": 1,");
        lines.Insert("    \"TrackBlockedByDuplicate\": 1,");
        lines.Insert("    \"TrackThoughtTypes\": 1,");
        lines.Insert("    \"TrackRecoveryEvents\": 1,");
        lines.Insert("    \"TrackSanityEvents\": 1,");
        lines.Insert("    \"TrackSocialEvents\": 1,");
        lines.Insert("    \"TrackStateHistoryEvents\": 1");
        lines.Insert("}");

        ST_WriteDefaultJsonFile(filePath, lines);
        Log("Created default consolidated config: " + filePath);
    }
    void ST_WriteDefaultJsonFile(string filePath, array<string> lines)
    {
        FileHandle file = OpenFile(filePath, FileMode.WRITE);

        if (!file)
        {
            Print("[SurvivorThoughts][ERROR] Could not create config file: " + filePath);
            return;
        }

        foreach (string line : lines)
        {
            FPrintln(file, line);
        }

        CloseFile(file);
    }


    void ST_WriteDefaultJsonStringFile(string filePath, string json)
    {
        if (FileExist(filePath))
            return;

        FileHandle file = OpenFile(filePath, FileMode.WRITE);

        if (!file)
        {
            Print("[SurvivorThoughts][ERROR] Could not create config file: " + filePath);
            return;
        }

        FPrintln(file, json);
        CloseFile(file);
        Log("Created default modular config: " + filePath);
    }

    void ST_CreateDefault_Core_json(string folderPath)
    {
        string filePath = folderPath + "/Core.json";
        if (FileExist(filePath))
            return;

        array<string> lines = new array<string>;
        lines.Insert("{");
        lines.Insert("    \"ConfigVersion\": 33,");
        lines.Insert("    \"EnableMod\": 1,");
        lines.Insert("    \"GlobalCooldownSeconds\": 120.0,");
        lines.Insert("    \"MinimumRandomDelaySeconds\": 45.0,");
        lines.Insert("    \"MaximumRandomDelaySeconds\": 180.0,");
        lines.Insert("    \"ShowHealthyMessages\": 0,");
        lines.Insert("    \"EnableHungerMessages\": 1,");
        lines.Insert("    \"EnableThirstMessages\": 1,");
        lines.Insert("    \"EnableColdMessages\": 1,");
        lines.Insert("    \"EnableHotMessages\": 1,");
        lines.Insert("    \"EnableSicknessMessages\": 1,");
        lines.Insert("    \"EnableBleedingMessages\": 1,");
        lines.Insert("    \"EnableBrokenLegMessages\": 1,");
        lines.Insert("    \"EnableInfectedNearbyMessages\": 1,");
        lines.Insert("    \"InfectedFarRadius\": 40.0,");
        lines.Insert("    \"InfectedCloseRadius\": 25.0,");
        lines.Insert("    \"InfectedVeryCloseRadius\": 10.0,");
        lines.Insert("    \"InfectedSurroundedCount\": 4,");
        lines.Insert("    \"DebugMode\": 0,");
        lines.Insert("    \"EnableDebugFileLog\": 1,");
        lines.Insert("    \"DebugLogToRPT\": 1,");
        lines.Insert("    \"DebugLogFileName\": \"SurvivorThoughts_Debug.log\",");
        lines.Insert("    \"ClearDebugLogOnServerStart\": 1");
        lines.Insert("}");

        ST_WriteDefaultJsonFile(filePath, lines);
        Log("Created default modular config: " + filePath);
    }

    void ST_CreateDefault_Output_json(string folderPath)
    {
        string filePath = folderPath + "/Output.json";
        if (FileExist(filePath))
            return;

        array<string> lines = new array<string>;
        lines.Insert("{");
        lines.Insert("    \"UseNotificationSystem\": 0,");
        lines.Insert("    \"UseLocalChatBox\": 1");
        lines.Insert("}");

        ST_WriteDefaultJsonFile(filePath, lines);
        Log("Created default modular config: " + filePath);
    }



    void ST_CreateDefault_Persistent_Storage_json(string folderPath)
    {
        string filePath = folderPath + "/Persistent_Storage.json";
        if (FileExist(filePath))
            return;

        array<string> lines = new array<string>;
        lines.Insert("{");
        lines.Insert("    \"EnableMissionStoragePersistentData\": 1,");
        lines.Insert("    \"PersistentStorageRoot\": \"$mission:storage_1/ZombiCideMods/SurvivorThoughts\",");
        lines.Insert("    \"PersistentDataFolderName\": \"Data\",");
        lines.Insert("    \"PersistentStateDataFile\": \"$mission:storage_1/ZombiCideMods/SurvivorThoughts/Data/PlayerPersistentStates.json\",");
        lines.Insert("    \"PersonalityDataFile\": \"$mission:storage_1/ZombiCideMods/SurvivorThoughts/Data/PlayerPersonalities.json\",");
        lines.Insert("    \"PersistentAutosaveSeconds\": 60.0");
        lines.Insert("}");

        ST_WriteDefaultJsonFile(filePath, lines);
        Log("Created default modular config: " + filePath);
    }

    void ST_CreateDefault_Thought_Priority_json(string folderPath)
    {
        string filePath = folderPath + "/Thought_Priority.json";
        if (FileExist(filePath))
            return;

        array<string> lines = new array<string>;
        lines.Insert("{");
        lines.Insert("    \"EnableThoughtPrioritySystem\": 1,");
        lines.Insert("    \"PriorityInterruptWindowSeconds\": 8.0,");
        lines.Insert("    \"PriorityImmediateDamage\": 100,");
        lines.Insert("    \"PriorityBleeding\": 100,");
        lines.Insert("    \"PriorityDeathSpiral\": 95,");
        lines.Insert("    \"PriorityCriticalSurvival\": 90,");
        lines.Insert("    \"PriorityHighSurvival\": 70,");
        lines.Insert("    \"PriorityMediumSurvival\": 50,");
        lines.Insert("    \"PriorityLowSurvival\": 25,");
        lines.Insert("    \"PriorityAction\": 35,");
        lines.Insert("    \"PriorityOpenCloseAction\": 20,");
        lines.Insert("    \"PriorityCombatStress\": 75,");
        lines.Insert("    \"PriorityWeather\": 15,");
        lines.Insert("    \"PriorityTimeOfDay\": 15,");
        lines.Insert("    \"PriorityLocation\": 20,");
        lines.Insert("    \"PriorityItemCondition\": 55,");
        lines.Insert("    \"PriorityCorpse\": 45,");
        lines.Insert("    \"PriorityContaminatedZone\": 80,");
        lines.Insert("    \"PriorityPersonality\": 10,");
        lines.Insert("    \"PriorityPlayerMemory\": 40,");
        lines.Insert("    \"PriorityStealthNoise\": 45,");
        lines.Insert("    \"PriorityShelter\": 25,");
        lines.Insert("    \"PriorityMentalState\": 60,");
        lines.Insert("    \"PriorityCustomThoughtZone\": 30,");
        lines.Insert("    \"PrioritySocialGroup\": 65,");
        lines.Insert("    \"PrioritySanityCreep\": 70,");
        lines.Insert("    \"PriorityStateHistory\": 50,");
        lines.Insert("    \"PriorityRecovery\": 55,");
        lines.Insert("    \"PriorityAdvancedCombined\": 85,");
        lines.Insert("    \"PriorityNearMissCombat\": 80,");
        lines.Insert("    \"PriorityDiseaseSpecific\": 70,");
        lines.Insert("    \"PriorityMapEnvironment\": 18,");
        lines.Insert("    \"PriorityAdminSystem\": 100");
        lines.Insert("}");

        ST_WriteDefaultJsonFile(filePath, lines);
        Log("Created default modular config: " + filePath);
    }

    void ST_CreateDefault_Player_Memory_json(string folderPath)
    {
        string filePath = folderPath + "/Player_Memory.json";
        if (FileExist(filePath))
            return;

        array<string> lines = new array<string>;
        lines.Insert("{");
        lines.Insert("    \"EnablePlayerMemoryThoughts\": 1,");
        lines.Insert("    \"PlayerMemoryThoughtCooldownSeconds\": 240.0,");
        lines.Insert("    \"PlayerMemoryThoughtChance\": 0.3,");
        lines.Insert("    \"PlayerMemoryDurationSeconds\": 600.0,");
        lines.Insert("    \"PlayerMemoryRecentDamageMessages\": [");
        lines.Insert("        \"That hit is still on my mind.\",");
        lines.Insert("        \"I need to keep moving after that.\",");
        lines.Insert("        \"Pain makes every decision slower.\",");
        lines.Insert("        \"I should not let that happen again.\"");
        lines.Insert("    ],");
        lines.Insert("    \"PlayerMemoryRecentBleedingMessages\": [");
        lines.Insert("        \"I can still feel where I was bleeding.\",");
        lines.Insert("        \"That wound could have ended me.\",");
        lines.Insert("        \"I need to check myself before moving on.\",");
        lines.Insert("        \"Blood loss changes how everything feels.\"");
        lines.Insert("    ],");
        lines.Insert("    \"PlayerMemoryRecentGunshotMessages\": [");
        lines.Insert("        \"That gunshot is still ringing in my head.\",");
        lines.Insert("        \"Someone with a gun changes everything.\",");
        lines.Insert("        \"I need cover before confidence.\",");
        lines.Insert("        \"One shot was enough warning.\"");
        lines.Insert("    ],");
        lines.Insert("    \"PlayerMemoryRecentCorpseMessages\": [");
        lines.Insert("        \"That body was a warning.\",");
        lines.Insert("        \"Someone died close by. I should not ignore that.\",");
        lines.Insert("        \"Bodies draw questions, flies, and people.\",");
        lines.Insert("        \"I need to leave before I become part of the scene.\"");
        lines.Insert("    ],");
        lines.Insert("    \"PlayerMemoryRecentMilitaryMessages\": [");
        lines.Insert("        \"Military places bring armed survivors.\",");
        lines.Insert("        \"Good loot is never free.\",");
        lines.Insert("        \"I should assume someone watched this place before me.\",");
        lines.Insert("        \"The risk here follows me even after I leave.\"");
        lines.Insert("    ],");
        lines.Insert("    \"PlayerMemoryRecentSurvivalCrisisMessages\": [");
        lines.Insert("        \"I came too close to dying.\",");
        lines.Insert("        \"My body needs a break before it gives up.\",");
        lines.Insert("        \"I need food, water, warmth, and time.\",");
        lines.Insert("        \"Survival is getting narrower.\"");
        lines.Insert("    ]");
        lines.Insert("}");

        ST_WriteDefaultJsonFile(filePath, lines);
        Log("Created default modular config: " + filePath);
    }

    void ST_CreateDefault_Stealth_Noise_json(string folderPath)
    {
        string filePath = folderPath + "/Stealth_Noise.json";
        if (FileExist(filePath))
            return;

        array<string> lines = new array<string>;
        lines.Insert("{");
        lines.Insert("    \"EnableStealthNoiseThoughts\": 1,");
        lines.Insert("    \"StealthNoiseThoughtCooldownSeconds\": 180.0,");
        lines.Insert("    \"StealthNoiseThoughtChance\": 0.35,");
        lines.Insert("    \"StealthNoiseInfectedRadius\": 35.0,");
        lines.Insert("    \"StealthNoiseRunSpeedThreshold\": 3.2,");
        lines.Insert("    \"StealthNoiseInfectedNearbyMessages\": [");
        lines.Insert("        \"Too much noise will pull them straight to me.\",");
        lines.Insert("        \"Slow down. The infected are close enough to hear.\",");
        lines.Insert("        \"Every step matters when they are this near.\",");
        lines.Insert("        \"Quiet movement keeps me alive longer than speed.\"");
        lines.Insert("    ],");
        lines.Insert("    \"StealthNoiseNightMessages\": [");
        lines.Insert("        \"Sound feels louder in the dark.\",");
        lines.Insert("        \"At night, one bad step can give me away.\",");
        lines.Insert("        \"I should move like someone is listening.\",");
        lines.Insert("        \"The dark hides me, but it hides everyone else too.\"");
        lines.Insert("    ],");
        lines.Insert("    \"StealthNoiseMilitaryMessages\": [");
        lines.Insert("        \"Running through a military zone is asking to be heard.\",");
        lines.Insert("        \"Slow, quiet, and ready. That is how I leave here.\",");
        lines.Insert("        \"Noise here travels to the wrong people.\",");
        lines.Insert("        \"Good gear brings bad company. I should move carefully.\"");
        lines.Insert("    ]");
        lines.Insert("}");

        ST_WriteDefaultJsonFile(filePath, lines);
        Log("Created default modular config: " + filePath);
    }

    void ST_CreateDefault_Shelter_json(string folderPath)
    {
        string filePath = folderPath + "/Shelter.json";
        if (FileExist(filePath))
            return;

        array<string> lines = new array<string>;
        lines.Insert("{");
        lines.Insert("    \"EnableShelterThoughts\": 1,");
        lines.Insert("    \"ShelterThoughtCooldownSeconds\": 300.0,");
        lines.Insert("    \"ShelterThoughtChance\": 0.3,");
        lines.Insert("    \"ShelterScanRadius\": 14.0,");
        lines.Insert("    \"ShelterNearbyBuildingCountRequired\": 1,");
        lines.Insert("    \"ShelterSafeMessages\": [");
        lines.Insert("        \"Four walls help, but they do not make me safe.\",");
        lines.Insert("        \"This place might give me a moment to think.\",");
        lines.Insert("        \"Shelter is useful. Exits matter more.\",");
        lines.Insert("        \"I should check every corner before trusting this place.\"");
        lines.Insert("    ],");
        lines.Insert("    \"ShelterUnsafeMessages\": [");
        lines.Insert("        \"This building could already belong to someone else.\",");
        lines.Insert("        \"Closed rooms hide bad surprises.\",");
        lines.Insert("        \"I need an exit plan before I relax.\",");
        lines.Insert("        \"Shelter can become a trap fast.\"");
        lines.Insert("    ],");
        lines.Insert("    \"ShelterBadWeatherMessages\": [");
        lines.Insert("        \"At least this place can keep some weather off me.\",");
        lines.Insert("        \"I need to dry out while I can.\",");
        lines.Insert("        \"Bad weather makes shelter worth the risk.\",");
        lines.Insert("        \"This cover might save my temperature.\"");
        lines.Insert("    ],");
        lines.Insert("    \"ShelterNightMessages\": [");
        lines.Insert("        \"Night makes every doorway feel dangerous.\",");
        lines.Insert("        \"If I stay here, I need to secure the exits.\",");
        lines.Insert("        \"This place is better than standing outside in the dark.\",");
        lines.Insert("        \"I should listen before I move through the rooms.\"");
        lines.Insert("    ]");
        lines.Insert("}");

        ST_WriteDefaultJsonFile(filePath, lines);
        Log("Created default modular config: " + filePath);
    }

    void ST_CreateDefault_Message_Blocker_json(string folderPath)
    {
        string filePath = folderPath + "/Message_Blocker.json";
        if (FileExist(filePath))
            return;

        array<string> lines = new array<string>;
        lines.Insert("{");
        lines.Insert("    \"EnableRecentMessageBlocker\": 1,");
        lines.Insert("    \"RecentMessageMemoryCount\": 12,");
        lines.Insert("    \"RecentMessageBlockSeconds\": 900.0");
        lines.Insert("}");

        ST_WriteDefaultJsonFile(filePath, lines);
        Log("Created default modular config: " + filePath);
    }

    void ST_CreateDefault_Mental_State_json(string folderPath)
    {
        string filePath = folderPath + "/Mental_State.json";
        if (FileExist(filePath))
            return;

        array<string> lines = new array<string>;
        lines.Insert("{");
        lines.Insert("    \"EnableMentalStateThoughts\": 1,");
        lines.Insert("    \"MentalStateThoughtCooldownSeconds\": 300.0,");
        lines.Insert("    \"MentalStateThoughtChance\": 0.25,");
        lines.Insert("    \"MentalStateCriticalHealthMax\": 30.0,");
        lines.Insert("    \"MentalStateLowBloodMax\": 3500.0,");
        lines.Insert("    \"MentalStateLowFoodMax\": 500.0,");
        lines.Insert("    \"MentalStateLowWaterMax\": 500.0,");
        lines.Insert("    \"MentalStateStableMessages\": [");
        lines.Insert("        \"Keep priorities simple. Water, food, shelter.\",");
        lines.Insert("        \"Think clearly. Waste nothing.\",");
        lines.Insert("        \"I can handle this if I stay methodical.\",");
        lines.Insert("        \"One good decision after another.\"");
        lines.Insert("    ],");
        lines.Insert("    \"MentalStateUneasyMessages\": [");
        lines.Insert("        \"Something feels wrong.\",");
        lines.Insert("        \"I cannot shake the feeling that I am being watched.\",");
        lines.Insert("        \"I need to slow down and listen.\",");
        lines.Insert("        \"This place is getting under my skin.\"");
        lines.Insert("    ],");
        lines.Insert("    \"MentalStateAfraidMessages\": [");
        lines.Insert("        \"Do not panic. Panic wastes energy.\",");
        lines.Insert("        \"I hate how close everything sounds.\",");
        lines.Insert("        \"Fear is useful if it keeps me careful.\",");
        lines.Insert("        \"I need to breathe and keep moving.\"");
        lines.Insert("    ],");
        lines.Insert("    \"MentalStateDesperateMessages\": [");
        lines.Insert("        \"I am running out of choices.\",");
        lines.Insert("        \"Anything useful matters now.\",");
        lines.Insert("        \"I need supplies before I need a plan.\",");
        lines.Insert("        \"Desperation makes people loud. I need to stay smart.\"");
        lines.Insert("    ],");
        lines.Insert("    \"MentalStateNumbMessages\": [");
        lines.Insert("        \"I do not feel much anymore.\",");
        lines.Insert("        \"Maybe numb is better than scared.\",");
        lines.Insert("        \"Keep moving. Feeling can come later.\",");
        lines.Insert("        \"This place takes pieces from everyone.\"");
        lines.Insert("    ],");
        lines.Insert("    \"MentalStateAggressiveMessages\": [");
        lines.Insert("        \"If someone pushes me now, they will regret it.\",");
        lines.Insert("        \"I am tired of being hunted.\",");
        lines.Insert("        \"No more hesitation.\",");
        lines.Insert("        \"Threats need to be dealt with before they grow.\"");
        lines.Insert("    ],");
        lines.Insert("    \"MentalStateBrokenMessages\": [");
        lines.Insert("        \"I do not know how much longer I can keep doing this.\",");
        lines.Insert("        \"Everything hurts. Everything is heavy.\",");
        lines.Insert("        \"I need one reason to keep moving.\",");
        lines.Insert("        \"The world is getting smaller with every step.\"");
        lines.Insert("    ],");
        lines.Insert("    \"MentalStateFocusedMessages\": [");
        lines.Insert("        \"Focus. Check corners. Check supplies. Move.\",");
        lines.Insert("        \"Noise, cover, exits. Nothing else matters.\",");
        lines.Insert("        \"Stay sharp and stay alive.\",");
        lines.Insert("        \"I need to solve the next problem, not all of them.\"");
        lines.Insert("    ]");
        lines.Insert("}");

        ST_WriteDefaultJsonFile(filePath, lines);
        Log("Created default modular config: " + filePath);
    }

    void ST_CreateDefault_Custom_Thought_Zones_json(string folderPath)
    {
        string filePath = folderPath + "/Custom_Thought_Zones.json";
        if (FileExist(filePath))
            return;

        array<string> lines = new array<string>;
        lines.Insert("{");
        lines.Insert("    \"EnableCustomThoughtZones\": 1,");
        lines.Insert("    \"CustomThoughtZoneDefaultCooldownSeconds\": 600.0,");
        lines.Insert("    \"CustomThoughtZoneDefaultChance\": 0.35,");
        lines.Insert("    \"CustomThoughtZones\": [");
        lines.Insert("        {");
        lines.Insert("            \"Name\": \"Example Haunted Camp\",");
        lines.Insert("            \"Type\": \"Horror\",");
        lines.Insert("            \"X\": 4500.0,");
        lines.Insert("            \"Z\": 10200.0,");
        lines.Insert("            \"Radius\": 150.0,");
        lines.Insert("            \"Chance\": 0.35,");
        lines.Insert("            \"CooldownSeconds\": 600.0,");
        lines.Insert("            \"Messages\": [");
        lines.Insert("                \"Something is wrong with this place.\",");
        lines.Insert("                \"I should not stay here longer than I need to.\",");
        lines.Insert("                \"This camp feels abandoned for a reason.\",");
        lines.Insert("                \"Every quiet corner here feels watched.\"");
        lines.Insert("            ]");
        lines.Insert("        }");
        lines.Insert("    ]");
        lines.Insert("}");

        ST_WriteDefaultJsonFile(filePath, lines);
        Log("Created default modular config: " + filePath);
    }


    void ST_CreateDefault_Social_Group_json(string path)
    {
        string json = "{\n";
        json += "  \"EnableSocialGroupThoughts\": 1,\n";
        json += "  \"SocialGroupThoughtCooldownSeconds\": 240.0,\n";
        json += "  \"SocialGroupThoughtChance\": 0.35,\n";
        json += "  \"SocialNearbyPlayerRadius\": 45.0,\n";
        json += "  \"SocialFriendlyTimeRequiredSeconds\": 300.0,\n";
        json += "  \"SocialMemoryDurationSeconds\": 900.0,\n";
        json += "  \"LoneWolfNoPlayerSeenSeconds\": 10800.0,\n";
        json += "  \"EnableTeammateShotMessages\": 1,\n";
        json += "  \"EnableTeammateDownMessages\": 1,\n";
        json += "  \"EnableLoneWolfMessages\": 1,\n";
        json += "  \"EnableFriendlyNearbyMessages\": 1,\n";
        json += "  \"TeammateShotMessages\": [\n";
        json += "    \"They hit them. Move, now.\",\n";
        json += "    \"No, no, no. Stay with me.\",\n";
        json += "    \"Someone just dropped my cover.\",\n";
        json += "    \"I cannot lose them here.\",\n";
        json += "    \"That shot was meant to split us apart.\",\n";
        json += "    \"Keep them alive. Think later.\"\n";
        json += "  ],\n";
        json += "  \"TeammateDownMessages\": [\n";
        json += "    \"No, no, no! Hang on, do not die on me.\",\n";
        json += "    \"I am completely on my own now.\",\n";
        json += "    \"They were right beside me a second ago.\",\n";
        json += "    \"Do not leave me out here alone.\",\n";
        json += "    \"I should have covered them better.\",\n";
        json += "    \"Their silence is louder than the gunshot.\"\n";
        json += "  ],\n";
        json += "  \"LoneWolfMessages\": [\n";
        json += "    \"I have not talked to anyone in days.\",\n";
        json += "    \"I am starting to forget what my own voice sounds like.\",\n";
        json += "    \"No footsteps but mine. That should feel safer than it does.\",\n";
        json += "    \"Being alone keeps me alive, until it does not.\",\n";
        json += "    \"The silence is beginning to feel like company.\",\n";
        json += "    \"I wonder if there is anyone left worth trusting.\"\n";
        json += "  ],\n";
        json += "  \"FriendlyNearbyMessages\": [\n";
        json += "    \"Another set of eyes makes the road feel shorter.\",\n";
        json += "    \"Stay close. Wandering off gets people killed.\",\n";
        json += "    \"I need to keep track of them.\",\n";
        json += "    \"Two people make more noise, but fewer mistakes.\",\n";
        json += "    \"Trust is useful. Dangerous, but useful.\",\n";
        json += "    \"If this goes bad, I am not the only one at risk.\"\n";
        json += "  ]\n";
        json += "}\n";
        ST_WriteDefaultJsonStringFile(path, json);
    }

    void ST_CreateDefault_Sanity_Cannibalism_json(string path)
    {
        string json = "{\n";
        json += "  \"EnableSanityCreep\": 1,\n";
        json += "  \"SanityThoughtCooldownSeconds\": 300.0,\n";
        json += "  \"SanityThoughtChance\": 0.30,\n";
        json += "  \"StartingSanity\": 100.0,\n";
        json += "  \"MinimumSanity\": 0.0,\n";
        json += "  \"SanityLossSkinHuman\": 18.0,\n";
        json += "  \"SanityLossEatHumanMeat\": 25.0,\n";
        json += "  \"SanityLossKillRestrainedPlayer\": 35.0,\n";
        json += "  \"SanityRegenPerMinute\": 0.0,\n";
        json += "  \"SanityUneasyThreshold\": 70.0,\n";
        json += "  \"SanityUnhingedThreshold\": 35.0,\n";
        json += "  \"SanityPsychoticThreshold\": 15.0,\n";
        json += "  \"EnableSanityUneasyMessages\": 1,\n";
        json += "  \"EnableSanityUnhingedMessages\": 1,\n";
        json += "  \"EnableSanityPsychoticMessages\": 1,\n";
        json += "  \"EnableCannibalismCreepMessages\": 1,\n";
        json += "  \"SanityUneasyMessages\": [\n";
        json += "    \"I need to keep my head clear.\",\n";
        json += "    \"Something about this is staying with me.\",\n";
        json += "    \"My hands will not stop shaking.\",\n";
        json += "    \"I should not think about what I have done.\",\n";
        json += "    \"Breathe. Count supplies. Keep moving.\",\n";
        json += "    \"There are lines out here. I can still see them.\"\n";
        json += "  ],\n";
        json += "  \"SanityUnhingedMessages\": [\n";
        json += "    \"Their faces keep coming back when I close my eyes.\",\n";
        json += "    \"I keep hearing things that are not there.\",\n";
        json += "    \"The silence laughs at me.\",\n";
        json += "    \"I am still in control. I have to be.\",\n";
        json += "    \"I did what I had to do. That is what I keep telling myself.\",\n";
        json += "    \"Every bad choice feels easier than the last.\"\n";
        json += "  ],\n";
        json += "  \"SanityPsychoticMessages\": [\n";
        json += "    \"The giggling... I can hear it even when I am not laughing.\",\n";
        json += "    \"Their faces. Why do I keep seeing their faces?\",\n";
        json += "    \"Maybe the dead are the only honest ones now.\",\n";
        json += "    \"I do not remember when this started feeling normal.\",\n";
        json += "    \"Something in me broke quietly.\",\n";
        json += "    \"I should be horrified. I am not.\"\n";
        json += "  ],\n";
        json += "  \"CannibalismCreepMessages\": [\n";
        json += "    \"That was a person. I know that.\",\n";
        json += "    \"There are some hungers that should stay empty.\",\n";
        json += "    \"I can still taste what I should not have eaten.\",\n";
        json += "    \"My stomach accepts what my mind refuses.\",\n";
        json += "    \"The worst part is that it helped.\",\n";
        json += "    \"I crossed something I cannot uncross.\"\n";
        json += "  ]\n";
        json += "}\n";
        ST_WriteDefaultJsonStringFile(path, json);
    }

    void SendSocialGroupEventThought(PlayerBase player, string eventType)
    {
        if (!player)
            return;

        ST_SurvivorThoughtsConfig config = GetConfig();

        if (!config || config.EnableMod != 1 || config.EnableSocialGroupThoughts != 1)
            return;

        array<string> messages;

        if (eventType == "TEAMMATE_SHOT" && config.EnableTeammateShotMessages == 1)
            messages = config.TeammateShotMessages;

        if (eventType == "TEAMMATE_DOWN" && config.EnableTeammateDownMessages == 1)
            messages = config.TeammateDownMessages;

        if (!messages || messages.Count() == 0)
            return;

        SendImmediateThoughtWithPriority(player, messages.GetRandomElement(), "SOCIAL_GROUP");
        DebugLog("Social group event thought sent. Type=" + eventType);
    }

    void NotifyNearbyPlayersOfSocialEvent(PlayerBase victim, string eventType)
    {
        if (!victim || !GetGame())
            return;

        ST_SurvivorThoughtsConfig config = GetConfig();

        if (!config || config.EnableMod != 1 || config.EnableSocialGroupThoughts != 1)
            return;

        array<Object> objects = new array<Object>;
        GetGame().GetObjectsAtPosition(victim.GetPosition(), config.SocialNearbyPlayerRadius, objects, NULL);

        for (int i = 0; i < objects.Count(); i++)
        {
            PlayerBase otherPlayer = PlayerBase.Cast(objects[i]);

            if (!otherPlayer || otherPlayer == victim || !otherPlayer.IsAlive())
                continue;

            if (!otherPlayer.ST_HasRecentSocialBond())
                continue;

            SendSocialGroupEventThought(otherPlayer, eventType);
        }
    }


    void ST_CreateDefault_Stats_json(string folderPath)
    {
        string filePath = folderPath + "/Stats.json";
        if (FileExist(filePath))
            return;

        array<string> lines = new array<string>;
        lines.Insert("{");
        lines.Insert("    \"EnableEnergyStage1Messages\": 0,");
        lines.Insert("    \"EnergyStage1_Min\": 4000.0,");
        lines.Insert("    \"EnergyStage1_Max\": 5000.0,");
        lines.Insert("    \"EnableEnergyStage2Messages\": 1,");
        lines.Insert("    \"EnergyStage2_Min\": 3000.0,");
        lines.Insert("    \"EnergyStage2_Max\": 3999.0,");
        lines.Insert("    \"EnableEnergyStage3Messages\": 1,");
        lines.Insert("    \"EnergyStage3_Min\": 1000.0,");
        lines.Insert("    \"EnergyStage3_Max\": 2999.0,");
        lines.Insert("    \"EnableEnergyStage4Messages\": 1,");
        lines.Insert("    \"EnergyStage4_Min\": 0.0,");
        lines.Insert("    \"EnergyStage4_Max\": 999.0,");
        lines.Insert("    \"EnableWaterStage1Messages\": 0,");
        lines.Insert("    \"WaterStage1_Min\": 4000.0,");
        lines.Insert("    \"WaterStage1_Max\": 5000.0,");
        lines.Insert("    \"EnableWaterStage2Messages\": 1,");
        lines.Insert("    \"WaterStage2_Min\": 3000.0,");
        lines.Insert("    \"WaterStage2_Max\": 3999.0,");
        lines.Insert("    \"EnableWaterStage3Messages\": 1,");
        lines.Insert("    \"WaterStage3_Min\": 1000.0,");
        lines.Insert("    \"WaterStage3_Max\": 2999.0,");
        lines.Insert("    \"EnableWaterStage4Messages\": 1,");
        lines.Insert("    \"WaterStage4_Min\": 0.0,");
        lines.Insert("    \"WaterStage4_Max\": 999.0,");
        lines.Insert("    \"EnableBloodStage1Messages\": 0,");
        lines.Insert("    \"BloodStage1_Min\": 4500.0,");
        lines.Insert("    \"BloodStage1_Max\": 5000.0,");
        lines.Insert("    \"EnableBloodStage2Messages\": 1,");
        lines.Insert("    \"BloodStage2_Min\": 3500.0,");
        lines.Insert("    \"BloodStage2_Max\": 4499.0,");
        lines.Insert("    \"EnableBloodStage3Messages\": 1,");
        lines.Insert("    \"BloodStage3_Min\": 2500.0,");
        lines.Insert("    \"BloodStage3_Max\": 3499.0,");
        lines.Insert("    \"EnableBloodStage4Messages\": 1,");
        lines.Insert("    \"BloodStage4_Min\": 0.0,");
        lines.Insert("    \"BloodStage4_Max\": 2499.0,");
        lines.Insert("    \"EnableShockStage1Messages\": 0,");
        lines.Insert("    \"ShockStage1_Min\": 75.0,");
        lines.Insert("    \"ShockStage1_Max\": 100.0,");
        lines.Insert("    \"EnableShockStage2Messages\": 1,");
        lines.Insert("    \"ShockStage2_Min\": 50.0,");
        lines.Insert("    \"ShockStage2_Max\": 74.0,");
        lines.Insert("    \"EnableShockStage3Messages\": 1,");
        lines.Insert("    \"ShockStage3_Min\": 25.0,");
        lines.Insert("    \"ShockStage3_Max\": 49.0,");
        lines.Insert("    \"EnableShockStage4Messages\": 1,");
        lines.Insert("    \"ShockStage4_Min\": 0.0,");
        lines.Insert("    \"ShockStage4_Max\": 24.0,");
        lines.Insert("    \"EnableConfigurableStatThresholds\": 1,");
        lines.Insert("    \"EnableDeathSpiralThoughts\": 1,");
        lines.Insert("    \"HealthDropMinAmount\": 0.10,");
        lines.Insert("    \"HealthDropRecentSeconds\": 90.0,");
        lines.Insert("    \"DeathSpiralColdComfort_Max\": -0.75,");
        lines.Insert("    \"DeathSpiralHotComfort_Min\": 0.75,");
        lines.Insert("    \"EnableStarvingToDeathMessages\": 1,");
        lines.Insert("    \"EnableDehydratingToDeathMessages\": 1,");
        lines.Insert("    \"EnableFreezingToDeathMessages\": 1,");
        lines.Insert("    \"EnableOverheatingToDeathMessages\": 1");
        lines.Insert("}");

        ST_WriteDefaultJsonFile(filePath, lines);
        Log("Created default modular config: " + filePath);
    }

    void ST_CreateDefault_Messages_Passive_json(string folderPath)
    {
        string filePath = folderPath + "/Messages_Passive.json";
        if (FileExist(filePath))
            return;

        array<string> lines = new array<string>;
        lines.Insert("{");
        lines.Insert("    \"EnergyStage1Messages\": [");
        lines.Insert("        \"I feel fed for now.\",");
        lines.Insert("        \"My stomach is settled.\",");
        lines.Insert("        \"I can keep moving for a while.\",");
        lines.Insert("        \"Food is not a problem right now.\"");
        lines.Insert("    ],");
        lines.Insert("    \"EnergyStage2Messages\": [");
        lines.Insert("        \"I could eat soon.\",");
        lines.Insert("        \"My stomach feels a little empty.\",");
        lines.Insert("        \"I should keep an eye out for food.\",");
        lines.Insert("        \"A small meal would help.\"");
        lines.Insert("    ],");
        lines.Insert("    \"EnergyStage3Messages\": [");
        lines.Insert("        \"My stomach is starting to hurt.\",");
        lines.Insert("        \"I need food soon.\",");
        lines.Insert("        \"I can feel my strength fading.\",");
        lines.Insert("        \"I keep thinking about food.\"");
        lines.Insert("    ],");
        lines.Insert("    \"EnergyStage4Messages\": [");
        lines.Insert("        \"I am starving.\",");
        lines.Insert("        \"My body feels weak.\",");
        lines.Insert("        \"I need food now.\",");
        lines.Insert("        \"I do not know how much longer I can go without eating.\"");
        lines.Insert("    ],");
        lines.Insert("    \"WaterStage1Messages\": [");
        lines.Insert("        \"I feel hydrated.\",");
        lines.Insert("        \"My mouth feels fine.\",");
        lines.Insert("        \"Water is not an issue right now.\",");
        lines.Insert("        \"I can travel without worrying about thirst.\"");
        lines.Insert("    ],");
        lines.Insert("    \"WaterStage2Messages\": [");
        lines.Insert("        \"My mouth is getting dry.\",");
        lines.Insert("        \"I should drink soon.\",");
        lines.Insert("        \"I could use some water.\",");
        lines.Insert("        \"I need to remember the next well.\"");
        lines.Insert("    ],");
        lines.Insert("    \"WaterStage3Messages\": [");
        lines.Insert("        \"My throat is dry.\",");
        lines.Insert("        \"I need water soon.\",");
        lines.Insert("        \"My head is starting to ache.\",");
        lines.Insert("        \"I should not ignore this thirst.\"");
        lines.Insert("    ],");
        lines.Insert("    \"WaterStage4Messages\": [");
        lines.Insert("        \"I am dehydrated.\",");
        lines.Insert("        \"My mouth feels like sand.\",");
        lines.Insert("        \"I need water now.\",");
        lines.Insert("        \"I feel faint from thirst.\"");
        lines.Insert("    ],");
        lines.Insert("    \"BloodStage1Messages\": [");
        lines.Insert("        \"I feel steady for now.\",");
        lines.Insert("        \"My blood feels strong enough.\",");
        lines.Insert("        \"I can keep moving.\"");
        lines.Insert("    ],");
        lines.Insert("    \"BloodStage2Messages\": [");
        lines.Insert("        \"I feel a little light-headed.\",");
        lines.Insert("        \"I should avoid losing more blood.\",");
        lines.Insert("        \"That blood loss is starting to show.\"");
        lines.Insert("    ],");
        lines.Insert("    \"BloodStage3Messages\": [");
        lines.Insert("        \"My head is swimming.\",");
        lines.Insert("        \"I need to recover before pushing further.\",");
        lines.Insert("        \"The blood loss is slowing me down.\"");
        lines.Insert("    ],");
        lines.Insert("    \"BloodStage4Messages\": [");
        lines.Insert("        \"I feel like I am going to pass out.\",");
        lines.Insert("        \"My vision keeps fading.\",");
        lines.Insert("        \"I have lost too much blood.\"");
        lines.Insert("    ],");
        lines.Insert("    \"ShockStage1Messages\": [");
        lines.Insert("        \"I feel alert enough.\",");
        lines.Insert("        \"I can keep myself together.\",");
        lines.Insert("        \"My nerves are steady.\"");
        lines.Insert("    ],");
        lines.Insert("    \"ShockStage2Messages\": [");
        lines.Insert("        \"That shook me.\",");
        lines.Insert("        \"I need a second to steady myself.\",");
        lines.Insert("        \"My hands are not as steady as they should be.\"");
        lines.Insert("    ],");
        lines.Insert("    \"ShockStage3Messages\": [");
        lines.Insert("        \"I feel stunned.\",");
        lines.Insert("        \"My body is struggling to respond.\",");
        lines.Insert("        \"I need to get behind cover.\"");
        lines.Insert("    ],");
        lines.Insert("    \"ShockStage4Messages\": [");
        lines.Insert("        \"I am about to black out.\",");
        lines.Insert("        \"Everything is fading.\",");
        lines.Insert("        \"I cannot stay conscious much longer.\"");
        lines.Insert("    ],");
        lines.Insert("    \"Cold_Mild_Messages\": [");
        lines.Insert("        \"The air feels cold.\",");
        lines.Insert("        \"I should keep moving.\",");
        lines.Insert("        \"My hands are getting stiff.\",");
        lines.Insert("        \"I need to stay dry.\"");
        lines.Insert("    ],");
        lines.Insert("    \"Cold_Moderate_Messages\": [");
        lines.Insert("        \"I am getting cold.\",");
        lines.Insert("        \"My clothes are not keeping the chill out.\",");
        lines.Insert("        \"I need shelter or a fire.\",");
        lines.Insert("        \"My fingers are going numb.\"");
        lines.Insert("    ],");
        lines.Insert("    \"Cold_Severe_Messages\": [");
        lines.Insert("        \"I am freezing.\",");
        lines.Insert("        \"This cold is cutting through me.\",");
        lines.Insert("        \"I need warmth now.\",");
        lines.Insert("        \"I can barely feel my hands.\"");
        lines.Insert("    ],");
        lines.Insert("    \"Cold_Critical_Messages\": [");
        lines.Insert("        \"I cannot stop shaking.\",");
        lines.Insert("        \"My body is shutting down from the cold.\",");
        lines.Insert("        \"I need fire, shelter, or dry clothes immediately.\",");
        lines.Insert("        \"I am not going to survive this cold much longer.\"");
        lines.Insert("    ],");
        lines.Insert("    \"Hot_Mild_Messages\": [");
        lines.Insert("        \"I feel warm.\",");
        lines.Insert("        \"I should avoid overheating.\",");
        lines.Insert("        \"The heat is starting to build.\",");
        lines.Insert("        \"I may need to slow down.\"");
        lines.Insert("    ],");
        lines.Insert("    \"Hot_Moderate_Messages\": [");
        lines.Insert("        \"I am getting too hot.\",");
        lines.Insert("        \"I need shade or lighter clothing.\",");
        lines.Insert("        \"This heat is draining me.\",");
        lines.Insert("        \"I should drink more water.\"");
        lines.Insert("    ],");
        lines.Insert("    \"Hot_Severe_Messages\": [");
        lines.Insert("        \"I am overheating.\",");
        lines.Insert("        \"My head feels heavy from the heat.\",");
        lines.Insert("        \"I need to cool down.\",");
        lines.Insert("        \"I should stop running.\"");
        lines.Insert("    ],");
        lines.Insert("    \"Hot_Critical_Messages\": [");
        lines.Insert("        \"I feel like I am going to collapse.\",");
        lines.Insert("        \"The heat is unbearable.\",");
        lines.Insert("        \"I need water and shade now.\",");
        lines.Insert("        \"My body cannot handle this heat much longer.\"");
        lines.Insert("    ],");
        lines.Insert("    \"Sickness_Early_Messages\": [");
        lines.Insert("        \"Something feels off.\",");
        lines.Insert("        \"My stomach feels unsettled.\",");
        lines.Insert("        \"I do not feel right.\",");
        lines.Insert("        \"I might be getting sick.\"");
        lines.Insert("    ],");
        lines.Insert("    \"Sickness_Moderate_Messages\": [");
        lines.Insert("        \"I feel ill.\",");
        lines.Insert("        \"My body aches.\",");
        lines.Insert("        \"My stomach keeps turning.\",");
        lines.Insert("        \"I need medicine.\"");
        lines.Insert("    ],");
        lines.Insert("    \"Sickness_Severe_Messages\": [");
        lines.Insert("        \"I feel feverish.\",");
        lines.Insert("        \"I can barely focus.\",");
        lines.Insert("        \"This sickness is getting worse.\",");
        lines.Insert("        \"I need treatment soon.\"");
        lines.Insert("    ],");
        lines.Insert("    \"Sickness_Critical_Messages\": [");
        lines.Insert("        \"I feel like I am dying.\",");
        lines.Insert("        \"My body is fighting something bad.\",");
        lines.Insert("        \"I need medicine now.\",");
        lines.Insert("        \"I do not know how much longer I can keep going.\"");
        lines.Insert("    ],");
        lines.Insert("    \"Bleeding_One_Messages\": [");
        lines.Insert("        \"I am bleeding.\",");
        lines.Insert("        \"I need to bandage this.\",");
        lines.Insert("        \"Blood is running down my body.\",");
        lines.Insert("        \"This wound needs attention.\"");
        lines.Insert("    ],");
        lines.Insert("    \"Bleeding_Multiple_Messages\": [");
        lines.Insert("        \"I am losing blood fast.\",");
        lines.Insert("        \"There is blood everywhere.\",");
        lines.Insert("        \"I need to stop the bleeding now.\",");
        lines.Insert("        \"I have more than one wound open.\"");
        lines.Insert("    ],");
        lines.Insert("    \"Bleeding_Critical_Messages\": [");
        lines.Insert("        \"I am bleeding out.\",");
        lines.Insert("        \"My vision is starting to fade.\",");
        lines.Insert("        \"I need bandages immediately.\",");
        lines.Insert("        \"If I do not stop this bleeding, I am dead.\"");
        lines.Insert("    ],");
        lines.Insert("    \"BrokenLegMessages\": [");
        lines.Insert("        \"My leg is broken.\",");
        lines.Insert("        \"I cannot move like this.\",");
        lines.Insert("        \"Every step sends pain through my body.\",");
        lines.Insert("        \"I need a splint before this gets me killed.\",");
        lines.Insert("        \"I am not getting far on this leg.\"");
        lines.Insert("    ],");
        lines.Insert("    \"Infected_Far_Messages\": [");
        lines.Insert("        \"I hear infected nearby.\",");
        lines.Insert("        \"Something is moving out there.\",");
        lines.Insert("        \"I should stay quiet.\",");
        lines.Insert("        \"I do not think I am alone.\"");
        lines.Insert("    ],");
        lines.Insert("    \"Infected_Close_Messages\": [");
        lines.Insert("        \"There are infected close.\",");
        lines.Insert("        \"I need to watch my noise.\",");
        lines.Insert("        \"I can hear them breathing.\",");
        lines.Insert("        \"One wrong move and they will hear me.\"");
        lines.Insert("    ],");
        lines.Insert("    \"Infected_VeryClose_Messages\": [");
        lines.Insert("        \"They are right on top of me.\",");
        lines.Insert("        \"I need to move carefully.\",");
        lines.Insert("        \"I can hear them just outside.\",");
        lines.Insert("        \"This place is not safe.\"");
        lines.Insert("    ],");
        lines.Insert("    \"Infected_Surrounded_Messages\": [");
        lines.Insert("        \"There are too many of them.\",");
        lines.Insert("        \"I am surrounded.\",");
        lines.Insert("        \"I need an escape route.\",");
        lines.Insert("        \"If they hear me, this could go bad fast.\"");
        lines.Insert("    ]");
        lines.Insert("}");

        ST_WriteDefaultJsonFile(filePath, lines);
        Log("Created default modular config: " + filePath);
    }

    void ST_CreateDefault_Messages_Actions_json(string folderPath)
    {
        string filePath = folderPath + "/Messages_Actions.json";
        if (FileExist(filePath))
            return;

        array<string> lines = new array<string>;
        lines.Insert("{");
        lines.Insert("    \"EnableActionThoughts\": 1,");
        lines.Insert("    \"EnableExtendedVanillaActionMessages\": 1,");
        lines.Insert("    \"OpenCloseActionCooldownSeconds\": 2.5,");
        lines.Insert("    \"DuplicateImmediateActionCooldownSeconds\": 0.75,");
        lines.Insert("    \"EnableEatingThoughts\": 1,");
        lines.Insert("    \"EnableDrinkingThoughts\": 1,");
        lines.Insert("    \"EnableUnjamThoughts\": 1,");
        lines.Insert("    \"EnableSkinningThoughts\": 1,");
        lines.Insert("    \"EnableBandagingThoughts\": 1,");
        lines.Insert("    \"EnableFireStartingThoughts\": 1,");
        lines.Insert("    \"EnableCookingThoughts\": 1,");
        lines.Insert("    \"EnableFishingThoughts\": 1,");
        lines.Insert("    \"EnableRepairThoughts\": 1,");
        lines.Insert("    \"EatingMessages\": [");
        lines.Insert("        \"That helped.\",");
        lines.Insert("        \"I needed that.\",");
        lines.Insert("        \"My stomach settles a little.\",");
        lines.Insert("        \"I should find more food before moving on.\",");
        lines.Insert("        \"That tasted awful, but it will keep me alive.\"");
        lines.Insert("    ],");
        lines.Insert("    \"DrinkingMessages\": [");
        lines.Insert("        \"That feels better.\",");
        lines.Insert("        \"My throat needed that.\",");
        lines.Insert("        \"I should refill before I leave.\",");
        lines.Insert("        \"Clean water is worth more than ammo out here.\",");
        lines.Insert("        \"I needed every drop.\"");
        lines.Insert("    ],");
        lines.Insert("    \"UnsafeDrinkingMessages\": [");
        lines.Insert("        \"I hope that water was clean.\",");
        lines.Insert("        \"That tasted off.\",");
        lines.Insert("        \"My stomach turns after drinking that.\",");
        lines.Insert("        \"I should have purified it first.\"");
        lines.Insert("    ],");
        lines.Insert("    \"UnjamMessages\": [");
        lines.Insert("        \"Come on, clear it.\",");
        lines.Insert("        \"Not now.\",");
        lines.Insert("        \"This weapon is going to get me killed.\",");
        lines.Insert("        \"I need to maintain this gun.\",");
        lines.Insert("        \"Clear the jam before it gets me killed.\"");
        lines.Insert("    ],");
        lines.Insert("    \"UnjamSuccessMessages\": [");
        lines.Insert("        \"It is clear.\",");
        lines.Insert("        \"Back in the fight.\",");
        lines.Insert("        \"I got it working again.\",");
        lines.Insert("        \"That could have ended badly.\"");
        lines.Insert("    ],");
        lines.Insert("    \"SkinningAnimalMessages\": [");
        lines.Insert("        \"This will keep me alive.\",");
        lines.Insert("        \"Fresh meat means another day.\",");
        lines.Insert("        \"I should cook this before moving on.\",");
        lines.Insert("        \"The smell might attract attention.\",");
        lines.Insert("        \"Waste nothing.\"");
        lines.Insert("    ],");
        lines.Insert("    \"SkinningHumanMessages\": [");
        lines.Insert("        \"I should not think about what I am doing.\",");
        lines.Insert("        \"Survival changes people.\",");
        lines.Insert("        \"There is no going back from this.\",");
        lines.Insert("        \"I hope nobody saw that.\",");
        lines.Insert("        \"This is what the world has made of me.\"");
        lines.Insert("    ],");
        lines.Insert("    \"BandagingMessages\": [");
        lines.Insert("        \"Hold pressure.\",");
        lines.Insert("        \"I need to stop the bleeding.\",");
        lines.Insert("        \"That should slow it down.\",");
        lines.Insert("        \"I cannot afford to lose more blood.\",");
        lines.Insert("        \"Stay calm. Wrap it tight.\"");
        lines.Insert("    ],");
        lines.Insert("    \"BandageSuccessMessages\": [");
        lines.Insert("        \"The bleeding has stopped.\",");
        lines.Insert("        \"That was close.\",");
        lines.Insert("        \"I need to be more careful.\",");
        lines.Insert("        \"That should hold for now.\"");
        lines.Insert("    ],");
        lines.Insert("    \"FireStartingMessages\": [");
        lines.Insert("        \"Come on, catch.\",");
        lines.Insert("        \"A fire would change everything right now.\",");
        lines.Insert("        \"I need warmth.\",");
        lines.Insert("        \"Smoke might give me away.\",");
        lines.Insert("        \"Finally, some heat.\"");
        lines.Insert("    ],");
        lines.Insert("    \"CookingMessages\": [");
        lines.Insert("        \"The smell makes me hungry.\",");
        lines.Insert("        \"Hot food might keep me going.\",");
        lines.Insert("        \"I should not burn this.\",");
        lines.Insert("        \"A warm meal feels rare now.\"");
        lines.Insert("    ],");
        lines.Insert("    \"FishingMessages\": [");
        lines.Insert("        \"Patience.\",");
        lines.Insert("        \"Something has to bite eventually.\",");
        lines.Insert("        \"Food from the water is safer than the towns.\",");
        lines.Insert("        \"I hope this line holds.\"");
        lines.Insert("    ],");
        lines.Insert("    \"RepairMessages\": [");
        lines.Insert("        \"This should hold for now.\",");
        lines.Insert("        \"Better than letting it fall apart.\",");
        lines.Insert("        \"I need to take care of my gear.\",");
        lines.Insert("        \"Nothing lasts out here.\"");
        lines.Insert("    ],");
        lines.Insert("    \"MedicineConsumeMessages\": [");
        lines.Insert("        \"This might help.\",");
        lines.Insert("        \"I hope this is the right medicine.\",");
        lines.Insert("        \"Give it time to work.\",");
        lines.Insert("        \"I need to trust the pills now.\"");
        lines.Insert("    ],");
        lines.Insert("    \"WoundCareActionMessages\": [");
        lines.Insert("        \"This is going to hurt.\",");
        lines.Insert("        \"I need to close this wound.\",");
        lines.Insert("        \"Hold still. Breathe.\",");
        lines.Insert("        \"If I do not treat this now, it gets worse.\"");
        lines.Insert("    ],");
        lines.Insert("    \"InjectionMessages\": [");
        lines.Insert("        \"Steady hand.\",");
        lines.Insert("        \"This better help.\",");
        lines.Insert("        \"I hate using needles out here.\",");
        lines.Insert("        \"One shot could make the difference.\"");
        lines.Insert("    ],");
        lines.Insert("    \"BloodMedicalMessages\": [");
        lines.Insert("        \"I hope this blood is compatible.\",");
        lines.Insert("        \"I need this to work.\",");
        lines.Insert("        \"This bag could save me or finish me.\",");
        lines.Insert("        \"I can feel how weak I am.\"");
        lines.Insert("    ],");
        lines.Insert("    \"DisinfectActionMessages\": [");
        lines.Insert("        \"This should clean the wound.\",");
        lines.Insert("        \"It burns, but it might save me.\",");
        lines.Insert("        \"I need to keep infection out.\",");
        lines.Insert("        \"Better pain now than sickness later.\"");
        lines.Insert("    ],");
        lines.Insert("    \"RestrainActionMessages\": [");
        lines.Insert("        \"This could get ugly.\",");
        lines.Insert("        \"Keep control.\",");
        lines.Insert("        \"Do not give them a chance.\",");
        lines.Insert("        \"I need to finish this quickly.\"");
        lines.Insert("    ],");
        lines.Insert("    \"CraftingActionMessages\": [");
        lines.Insert("        \"Use what is left.\",");
        lines.Insert("        \"This might be useful.\",");
        lines.Insert("        \"Improvising keeps me alive.\",");
        lines.Insert("        \"Nothing out here is wasted.\"");
        lines.Insert("    ],");
        lines.Insert("    \"DeployActionMessages\": [");
        lines.Insert("        \"This spot will have to do.\",");
        lines.Insert("        \"Set it down carefully.\",");
        lines.Insert("        \"I should not leave obvious signs.\",");
        lines.Insert("        \"Someone could notice this.\"");
        lines.Insert("    ],");
        lines.Insert("    \"GardeningActionMessages\": [");
        lines.Insert("        \"Food takes patience.\",");
        lines.Insert("        \"If I live long enough, this might matter.\",");
        lines.Insert("        \"Seeds are hope in a dead place.\",");
        lines.Insert("        \"This could keep me alive later.\"");
        lines.Insert("    ],");
        lines.Insert("    \"ResourceGatheringMessages\": [");
        lines.Insert("        \"Take what I can use.\",");
        lines.Insert("        \"This might be worth the effort.\",");
        lines.Insert("        \"Tools, fuel, food, anything helps.\",");
        lines.Insert("        \"Do not make too much noise.\"");
        lines.Insert("    ],");
        lines.Insert("    \"LiquidTransferMessages\": [");
        lines.Insert("        \"Do not spill it.\",");
        lines.Insert("        \"Every drop matters.\",");
        lines.Insert("        \"I need clean water more than anything.\",");
        lines.Insert("        \"Fill it now, move later.\"");
        lines.Insert("    ],");
        lines.Insert("    \"FireplaceActionMessages\": [");
        lines.Insert("        \"This fire could save me.\",");
        lines.Insert("        \"Smoke could betray me.\",");
        lines.Insert("        \"Warmth is worth the risk.\",");
        lines.Insert("        \"Keep it small and controlled.\"");
        lines.Insert("    ],");
        lines.Insert("    \"ElectronicsActionMessages\": [");
        lines.Insert("        \"Power still means something.\",");
        lines.Insert("        \"I hope this works.\",");
        lines.Insert("        \"A signal could bring help or danger.\",");
        lines.Insert("        \"Old tech, new risks.\"");
        lines.Insert("    ],");
        lines.Insert("    \"NavigationActionMessages\": [");
        lines.Insert("        \"I need to know where I am.\",");
        lines.Insert("        \"Get bearings before moving.\",");
        lines.Insert("        \"A wrong turn can kill out here.\",");
        lines.Insert("        \"Check the route, then move.\"");
        lines.Insert("    ],");
        lines.Insert("    \"LockActionMessages\": [");
        lines.Insert("        \"Keep it secure.\",");
        lines.Insert("        \"Locks slow people down, not stop them.\",");
        lines.Insert("        \"This might buy time.\",");
        lines.Insert("        \"Someone may still get through.\"");
        lines.Insert("    ],");
        lines.Insert("    \"TrapExplosiveMessages\": [");
        lines.Insert("        \"Careful. One mistake and it is over.\",");
        lines.Insert("        \"This is dangerous work.\",");
        lines.Insert("        \"I need steady hands.\",");
        lines.Insert("        \"This could save me or kill me.\"");
        lines.Insert("    ],");
        lines.Insert("    \"BaseBuildingActionMessages\": [");
        lines.Insert("        \"This might keep someone out.\",");
        lines.Insert("        \"It will not stop everyone, but it helps.\",");
        lines.Insert("        \"A wall is only as strong as the time behind it.\",");
        lines.Insert("        \"Do not make this place too obvious.\"");
        lines.Insert("    ],");
        lines.Insert("    \"VehicleActionMessages\": [");
        lines.Insert("        \"This thing might run if I can keep it together.\",");
        lines.Insert("        \"Every part matters.\",");
        lines.Insert("        \"A working vehicle changes everything.\",");
        lines.Insert("        \"Noise and speed both attract trouble.\"");
        lines.Insert("    ],");
        lines.Insert("    \"BuryStashMessages\": [");
        lines.Insert("        \"Hide it well.\",");
        lines.Insert("        \"If someone finds this, I lose everything.\",");
        lines.Insert("        \"The ground keeps secrets for a while.\",");
        lines.Insert("        \"I need to remember this place.\"");
        lines.Insert("    ],");
        lines.Insert("    \"PersonalCareMessages\": [");
        lines.Insert("        \"Small things still matter.\",");
        lines.Insert("        \"Clean up before it gets worse.\",");
        lines.Insert("        \"Ignore yourself and the world wins.\",");
        lines.Insert("        \"Take care of the body that carries you.\"");
        lines.Insert("    ],");
        lines.Insert("    \"AmmoManagementMessages\": [");
        lines.Insert("        \"Every round matters.\",");
        lines.Insert("        \"Count it twice.\",");
        lines.Insert("        \"Do not waste ammunition.\",");
        lines.Insert("        \"Empty magazines get people killed.\"");
        lines.Insert("    ],");
        lines.Insert("    \"OpenCloseActionMessages\": [");
        lines.Insert("        \"Do it quietly.\",");
        lines.Insert("        \"Check the other side.\",");
        lines.Insert("        \"Every door is a risk.\",");
        lines.Insert("        \"Open it slow.\"");
        lines.Insert("    ],");
        lines.Insert("    \"GeneralActionMessages\": [");
        lines.Insert("        \"Keep moving.\",");
        lines.Insert("        \"Stay alert.\",");
        lines.Insert("        \"Do not make noise.\",");
        lines.Insert("        \"Finish this and move on.\"");
        lines.Insert("    ],");
        lines.Insert("    \"InventoryActionMessages\": [");
        lines.Insert("        \"Keep moving.\",");
        lines.Insert("        \"Stay alert.\",");
        lines.Insert("        \"Do not make noise.\",");
        lines.Insert("        \"Finish this and move on.\"");
        lines.Insert("    ],");
        lines.Insert("    \"MovementActionMessages\": [");
        lines.Insert("        \"Keep moving.\",");
        lines.Insert("        \"Stay alert.\",");
        lines.Insert("        \"Do not make noise.\",");
        lines.Insert("        \"Finish this and move on.\"");
        lines.Insert("    ],");
        lines.Insert("    \"WorldInteractionMessages\": [");
        lines.Insert("        \"Keep moving.\",");
        lines.Insert("        \"Stay alert.\",");
        lines.Insert("        \"Do not make noise.\",");
        lines.Insert("        \"Finish this and move on.\"");
        lines.Insert("    ]");
        lines.Insert("}");

        ST_WriteDefaultJsonFile(filePath, lines);
        Log("Created default modular config: " + filePath);
    }

    void ST_CreateDefault_Messages_Combined_json(string folderPath)
    {
        string filePath = folderPath + "/Messages_Combined.json";
        if (FileExist(filePath))
            return;

        array<string> lines = new array<string>;
        lines.Insert("{");
        lines.Insert("    \"EnableCombinedThoughts\": 1,");
        lines.Insert("    \"MaxCombinedThoughtParts\": 3,");
        lines.Insert("    \"CombinedThoughtChance\": 0.65,");
        lines.Insert("    \"UseExtremeSurvivalMessagesAtStateCount\": 4,");
        lines.Insert("    \"UseCriticalSurvivalMessagesAtStateCount\": 5,");
        lines.Insert("    \"EnableHungerMessages\": 1,");
        lines.Insert("    \"EnableThirstMessages\": 1,");
        lines.Insert("    \"EnableColdMessages\": 1,");
        lines.Insert("    \"EnableHotMessages\": 1,");
        lines.Insert("    \"EnableSicknessMessages\": 1,");
        lines.Insert("    \"EnableBleedingMessages\": 1,");
        lines.Insert("    \"EnableBrokenLegMessages\": 1,");
        lines.Insert("    \"EnableInfectedNearbyMessages\": 1,");
        lines.Insert("    \"HungerThirstMessages\": [");
        lines.Insert("        \"My stomach is empty and my mouth is dry.\",");
        lines.Insert("        \"I need food and water soon.\",");
        lines.Insert("        \"I cannot keep moving like this without supplies.\",");
        lines.Insert("        \"Every step feels harder without food or water.\",");
        lines.Insert("        \"I need to find something to eat and something safe to drink.\"");
        lines.Insert("    ],");
        lines.Insert("    \"HungerColdMessages\": [");
        lines.Insert("        \"The hunger is worse in this cold.\",");
        lines.Insert("        \"I need food and warmth before my body gives up.\",");
        lines.Insert("        \"My stomach is empty and my hands are going numb.\",");
        lines.Insert("        \"The cold is biting harder with nothing in my stomach.\",");
        lines.Insert("        \"I need calories and heat.\"");
        lines.Insert("    ],");
        lines.Insert("    \"HungerHotMessages\": [");
        lines.Insert("        \"The heat is draining what little strength I have left.\",");
        lines.Insert("        \"I am hungry and overheating.\",");
        lines.Insert("        \"My body feels weak in this heat.\",");
        lines.Insert("        \"I need food, shade, and a moment to breathe.\",");
        lines.Insert("        \"The heat makes the hunger feel worse.\"");
        lines.Insert("    ],");
        lines.Insert("    \"HungerSickMessages\": [");
        lines.Insert("        \"I feel sick, and the hunger is making it worse.\",");
        lines.Insert("        \"My stomach is empty, but I do not know if I can keep food down.\",");
        lines.Insert("        \"I need food, but my body feels wrong.\",");
        lines.Insert("        \"The sickness is eating at me as much as the hunger.\",");
        lines.Insert("        \"I need to treat this before I get any weaker.\"");
        lines.Insert("    ],");
        lines.Insert("    \"HungerBleedingMessages\": [");
        lines.Insert("        \"I am hungry and losing blood. This is bad.\",");
        lines.Insert("        \"My body needs food, but first I need to stop the bleeding.\",");
        lines.Insert("        \"The blood loss is making the hunger feel worse.\",");
        lines.Insert("        \"I cannot recover like this.\",");
        lines.Insert("        \"I need to stop bleeding and find food.\"");
        lines.Insert("    ],");
        lines.Insert("    \"HungerInfectedMessages\": [");
        lines.Insert("        \"I need food, but the infected are too close.\",");
        lines.Insert("        \"My stomach is empty, and I can hear infected nearby.\",");
        lines.Insert("        \"I should not search for food with infected this close.\",");
        lines.Insert("        \"I need supplies, but I need to stay quiet.\",");
        lines.Insert("        \"The hunger is pushing me toward danger.\"");
        lines.Insert("    ],");
        lines.Insert("    \"ThirstColdMessages\": [");
        lines.Insert("        \"My mouth is dry and my hands are freezing.\",");
        lines.Insert("        \"I need water and warmth.\",");
        lines.Insert("        \"The cold is slowing me down, and the thirst is getting worse.\",");
        lines.Insert("        \"I should find shelter and something safe to drink.\",");
        lines.Insert("        \"I cannot ignore thirst just because I am cold.\"");
        lines.Insert("    ],");
        lines.Insert("    \"HotThirstMessages\": [");
        lines.Insert("        \"The heat is draining me dry.\",");
        lines.Insert("        \"I need water before this heat drops me.\",");
        lines.Insert("        \"My mouth is dry and my body is overheating.\",");
        lines.Insert("        \"I need shade and water now.\",");
        lines.Insert("        \"Running in this heat is a mistake.\"");
        lines.Insert("    ],");
        lines.Insert("    \"SickThirstMessages\": [");
        lines.Insert("        \"I feel sick, and I need water badly.\",");
        lines.Insert("        \"My throat is dry, but my stomach feels wrong.\",");
        lines.Insert("        \"I need clean water and medicine.\",");
        lines.Insert("        \"The thirst is making the sickness harder to fight.\",");
        lines.Insert("        \"I need to hydrate before this gets worse.\"");
        lines.Insert("    ],");
        lines.Insert("    \"ThirstBleedingMessages\": [");
        lines.Insert("        \"I am losing blood and drying out.\",");
        lines.Insert("        \"I need water, but this bleeding comes first.\",");
        lines.Insert("        \"My mouth is dry and my wound is still open.\",");
        lines.Insert("        \"I cannot keep bleeding like this.\",");
        lines.Insert("        \"I need to patch myself up and find water.\"");
        lines.Insert("    ],");
        lines.Insert("    \"ThirstInfectedMessages\": [");
        lines.Insert("        \"I need water, but the infected are nearby.\",");
        lines.Insert("        \"My throat is dry, and I can hear them moving.\",");
        lines.Insert("        \"The well is useless if I get caught reaching it.\",");
        lines.Insert("        \"I need to stay quiet and find water.\",");
        lines.Insert("        \"Thirst is making me careless.\"");
        lines.Insert("    ],");
        lines.Insert("    \"SickColdMessages\": [");
        lines.Insert("        \"The sickness and cold are wearing me down.\",");
        lines.Insert("        \"I feel ill, and the cold is making everything worse.\",");
        lines.Insert("        \"I need medicine and warmth.\",");
        lines.Insert("        \"My body aches with every cold breath.\",");
        lines.Insert("        \"I need shelter before this sickness takes hold.\"");
        lines.Insert("    ],");
        lines.Insert("    \"BleedingColdMessages\": [");
        lines.Insert("        \"I am bleeding, and the cold is slowing my hands.\",");
        lines.Insert("        \"I need to bandage before my fingers go numb.\",");
        lines.Insert("        \"The blood feels warm against the cold air.\",");
        lines.Insert("        \"I need shelter and pressure on this wound.\",");
        lines.Insert("        \"I cannot afford blood loss in this cold.\"");
        lines.Insert("    ],");
        lines.Insert("    \"ColdInfectedMessages\": [");
        lines.Insert("        \"The cold is making my hands stiff, and I can hear infected nearby.\",");
        lines.Insert("        \"I need warmth, but the infected are too close.\",");
        lines.Insert("        \"I should not stay here, but I am too cold to think straight.\",");
        lines.Insert("        \"My fingers are numb, and something is moving nearby.\",");
        lines.Insert("        \"The cold makes it harder to stay quiet.\"");
        lines.Insert("    ],");
        lines.Insert("    \"HotSickMessages\": [");
        lines.Insert("        \"The heat is making this sickness worse.\",");
        lines.Insert("        \"I feel feverish and overheated.\",");
        lines.Insert("        \"I need shade, water, and medicine.\",");
        lines.Insert("        \"My head is pounding from heat and illness.\",");
        lines.Insert("        \"I cannot tell if this is fever or the weather.\"");
        lines.Insert("    ],");
        lines.Insert("    \"HotBleedingMessages\": [");
        lines.Insert("        \"I am bleeding and overheating.\",");
        lines.Insert("        \"The heat is making me feel faint.\",");
        lines.Insert("        \"I need to stop the bleeding and cool down.\",");
        lines.Insert("        \"My vision is swimming in this heat.\",");
        lines.Insert("        \"I cannot keep losing blood under this sun.\"");
        lines.Insert("    ],");
        lines.Insert("    \"HotInfectedMessages\": [");
        lines.Insert("        \"The heat is draining me, and the infected are close.\",");
        lines.Insert("        \"I need shade, but I cannot stop here.\",");
        lines.Insert("        \"Sweat is running into my eyes, and I can hear them nearby.\",");
        lines.Insert("        \"The heat is making every sound feel closer.\",");
        lines.Insert("        \"I need to move before they hear me.\"");
        lines.Insert("    ],");
        lines.Insert("    \"SickBleedingMessages\": [");
        lines.Insert("        \"I am sick and bleeding. My body cannot take much more.\",");
        lines.Insert("        \"The wound is open, and I already feel ill.\",");
        lines.Insert("        \"I need treatment before this gets worse.\",");
        lines.Insert("        \"This sickness will not heal while I am losing blood.\",");
        lines.Insert("        \"I need medicine and bandages.\"");
        lines.Insert("    ],");
        lines.Insert("    \"SickInfectedMessages\": [");
        lines.Insert("        \"I feel sick, and the infected are nearby.\",");
        lines.Insert("        \"I can barely focus with them this close.\",");
        lines.Insert("        \"I need medicine, but I need to survive this first.\",");
        lines.Insert("        \"Every cough could give me away.\",");
        lines.Insert("        \"I should not be near infected while I feel this weak.\"");
        lines.Insert("    ],");
        lines.Insert("    \"BleedingInfectedMessages\": [");
        lines.Insert("        \"I am bleeding, and the infected are close.\",");
        lines.Insert("        \"The blood might draw attention. I need to move.\",");
        lines.Insert("        \"I need to stop this bleeding before they find me.\",");
        lines.Insert("        \"I cannot fight them while losing blood.\",");
        lines.Insert("        \"If they hear me now, I am finished.\"");
        lines.Insert("    ],");
        lines.Insert("    \"HungerThirstColdMessages\": [");
        lines.Insert("        \"I need food, water, and warmth before my body gives out.\",");
        lines.Insert("        \"My stomach is empty, my mouth is dry, and the cold is biting.\",");
        lines.Insert("        \"I cannot survive long like this.\",");
        lines.Insert("        \"I need shelter and supplies now.\",");
        lines.Insert("        \"Every basic need is catching up with me.\"");
        lines.Insert("    ],");
        lines.Insert("    \"HungerThirstHotMessages\": [");
        lines.Insert("        \"I am hungry, thirsty, and overheating.\",");
        lines.Insert("        \"The heat is burning through what little strength I have left.\",");
        lines.Insert("        \"I need shade, water, and food.\",");
        lines.Insert("        \"My body is running on nothing in this heat.\",");
        lines.Insert("        \"I cannot keep moving like this.\"");
        lines.Insert("    ],");
        lines.Insert("    \"HungerColdInfectedMessages\": [");
        lines.Insert("        \"My stomach is empty, the cold is biting, and I can hear infected nearby.\",");
        lines.Insert("        \"I need food, warmth, and a way out before those infected find me.\",");
        lines.Insert("        \"I am hungry, freezing, and not alone out here.\",");
        lines.Insert("        \"Every step feels heavier with hunger, cold, and infected close by.\",");
        lines.Insert("        \"I need to move, but the cold and hunger are slowing me down.\"");
        lines.Insert("    ],");
        lines.Insert("    \"ThirstHotInfectedMessages\": [");
        lines.Insert("        \"I need water, I am overheating, and the infected are close.\",");
        lines.Insert("        \"The heat is drying me out, but I cannot stop here.\",");
        lines.Insert("        \"My throat is dry, sweat is in my eyes, and I can hear them nearby.\",");
        lines.Insert("        \"I need water, shade, and distance from the infected.\",");
        lines.Insert("        \"This heat is making me careless around infected.\"");
        lines.Insert("    ],");
        lines.Insert("    \"SickColdInfectedMessages\": [");
        lines.Insert("        \"I feel sick, the cold is biting, and infected are nearby.\",");
        lines.Insert("        \"I need warmth and medicine, but I cannot stop here.\",");
        lines.Insert("        \"My body is weak, my hands are numb, and I can hear them close.\",");
        lines.Insert("        \"I need shelter before the sickness and infected finish me.\",");
        lines.Insert("        \"Every sound feels closer while I am this weak.\"");
        lines.Insert("    ],");
        lines.Insert("    \"BleedingColdInfectedMessages\": [");
        lines.Insert("        \"I am bleeding, freezing, and the infected are close.\",");
        lines.Insert("        \"My hands are numb, and I need to stop this bleeding now.\",");
        lines.Insert("        \"The cold is slowing me down while the infected close in.\",");
        lines.Insert("        \"I need shelter, bandages, and a way out.\",");
        lines.Insert("        \"If I cannot stop the bleeding, the cold or infected will finish me.\"");
        lines.Insert("    ],");
        lines.Insert("    \"BleedingSickInfectedMessages\": [");
        lines.Insert("        \"I am sick, bleeding, and the infected are close.\",");
        lines.Insert("        \"My body is failing, and I can hear them nearby.\",");
        lines.Insert("        \"I need bandages, medicine, and silence.\",");
        lines.Insert("        \"I cannot fight like this.\",");
        lines.Insert("        \"If they find me now, I am done.\"");
        lines.Insert("    ],");
        lines.Insert("    \"HungerThirstInfectedMessages\": [");
        lines.Insert("        \"I need food and water, but the infected are too close.\",");
        lines.Insert("        \"My body is empty, and I can hear them nearby.\",");
        lines.Insert("        \"I need supplies, but searching now could get me killed.\",");
        lines.Insert("        \"Hunger and thirst are pushing me into danger.\",");
        lines.Insert("        \"I need to stay quiet and find supplies.\"");
        lines.Insert("    ],");
        lines.Insert("    \"BrokenLegHungerMessages\": [");
        lines.Insert("        \"My leg is broken, and hunger is making every movement worse.\",");
        lines.Insert("        \"I need food, but I can barely move.\",");
        lines.Insert("        \"I am hurt, hungry, and running out of options.\",");
        lines.Insert("        \"Dragging myself around like this is burning what little strength I have left.\"");
        lines.Insert("    ],");
        lines.Insert("    \"BrokenLegThirstMessages\": [");
        lines.Insert("        \"My leg is broken, and my throat is dry.\",");
        lines.Insert("        \"I need water, but I can barely move.\",");
        lines.Insert("        \"Every crawl feels worse with this thirst.\",");
        lines.Insert("        \"I need to reach water before this leg traps me here.\"");
        lines.Insert("    ],");
        lines.Insert("    \"BrokenLegColdMessages\": [");
        lines.Insert("        \"My leg is broken, and the cold is setting in.\",");
        lines.Insert("        \"I need warmth, but moving is agony.\",");
        lines.Insert("        \"The cold is making the pain worse.\",");
        lines.Insert("        \"I need shelter before this injury leaves me frozen.\"");
        lines.Insert("    ],");
        lines.Insert("    \"BrokenLegHotMessages\": [");
        lines.Insert("        \"My leg is broken, and the heat is draining me.\",");
        lines.Insert("        \"I need shade, but moving hurts too much.\",");
        lines.Insert("        \"The heat is making this injury harder to endure.\",");
        lines.Insert("        \"I cannot stay exposed like this.\"");
        lines.Insert("    ],");
        lines.Insert("    \"BrokenLegSickMessages\": [");
        lines.Insert("        \"My leg is broken, and I feel sick.\",");
        lines.Insert("        \"My body is falling apart.\",");
        lines.Insert("        \"I need medicine and a splint.\",");
        lines.Insert("        \"I cannot recover while I am this hurt and ill.\"");
        lines.Insert("    ],");
        lines.Insert("    \"BrokenLegBleedingMessages\": [");
        lines.Insert("        \"My leg is broken, and I am bleeding.\",");
        lines.Insert("        \"I need to stop the bleeding before I worry about walking.\",");
        lines.Insert("        \"I am injured badly and losing blood.\",");
        lines.Insert("        \"I need bandages and a splint now.\"");
        lines.Insert("    ],");
        lines.Insert("    \"BrokenLegInfectedMessages\": [");
        lines.Insert("        \"My leg is broken, and the infected are nearby.\",");
        lines.Insert("        \"I cannot outrun them like this.\",");
        lines.Insert("        \"I need to stay silent. I cannot move fast.\",");
        lines.Insert("        \"If they hear me now, I am trapped.\"");
        lines.Insert("    ],");
        lines.Insert("    \"BrokenLegColdInfectedMessages\": [");
        lines.Insert("        \"My leg is broken, the cold is biting, and infected are nearby.\",");
        lines.Insert("        \"I cannot run, I cannot get warm, and I am not alone.\",");
        lines.Insert("        \"I need shelter, silence, and a splint.\",");
        lines.Insert("        \"The cold and infected are closing in while I can barely move.\"");
        lines.Insert("    ],");
        lines.Insert("    \"BrokenLegBleedingInfectedMessages\": [");
        lines.Insert("        \"My leg is broken, I am bleeding, and infected are close.\",");
        lines.Insert("        \"I cannot run and I cannot keep bleeding.\",");
        lines.Insert("        \"If they hear me now, this injury will get me killed.\",");
        lines.Insert("        \"I need to stop the bleeding before they find me.\"");
        lines.Insert("    ],");
        lines.Insert("    \"BrokenLegHungerThirstMessages\": [");
        lines.Insert("        \"My leg is broken, my stomach is empty, and my mouth is dry.\",");
        lines.Insert("        \"I need food, water, and a way to move.\",");
        lines.Insert("        \"I cannot search for supplies like this.\",");
        lines.Insert("        \"This injury is turning every need into a crisis.\"");
        lines.Insert("    ],");
        lines.Insert("    \"ExtremeSurvivalMessages\": [");
        lines.Insert("        \"Everything is going wrong at once.\",");
        lines.Insert("        \"My body is failing, and this place is not safe.\",");
        lines.Insert("        \"I need shelter, supplies, and a way out now.\",");
        lines.Insert("        \"I cannot keep surviving like this.\",");
        lines.Insert("        \"One more mistake could finish me.\",");
        lines.Insert("        \"I need to stop, think, and survive the next few minutes.\",");
        lines.Insert("        \"My body is screaming for help.\",");
        lines.Insert("        \"I am running out of time.\",");
        lines.Insert("        \"I need to deal with the worst problem first.\",");
        lines.Insert("        \"This is how people die out here.\"");
        lines.Insert("    ],");
        lines.Insert("    \"CriticalSurvivalMessages\": [");
        lines.Insert("        \"I am falling apart.\",");
        lines.Insert("        \"This is bad. Really bad.\",");
        lines.Insert("        \"I need to survive the next minute before thinking about anything else.\",");
        lines.Insert("        \"Everything hurts, everything is wrong, and I am not safe.\",");
        lines.Insert("        \"I am close to the edge.\",");
        lines.Insert("        \"I need help, but there is nobody coming.\",");
        lines.Insert("        \"My body is giving up.\",");
        lines.Insert("        \"I cannot let panic take over.\",");
        lines.Insert("        \"Stop the bleeding. Find shelter. Stay alive.\",");
        lines.Insert("        \"I do not know how much longer I can keep going.\"");
        lines.Insert("    ],");
        lines.Insert("    \"StarvingToDeathMessages\": [");
        lines.Insert("        \"I am starving to death.\",");
        lines.Insert("        \"My body is eating itself, and my health is dropping.\",");
        lines.Insert("        \"I need food now or this is the end.\",");
        lines.Insert("        \"The hunger has gone past pain. I am dying.\"");
        lines.Insert("    ],");
        lines.Insert("    \"DehydratingToDeathMessages\": [");
        lines.Insert("        \"I am dying of thirst.\",");
        lines.Insert("        \"My body is shutting down without water.\",");
        lines.Insert("        \"I need water now or I will not make it.\",");
        lines.Insert("        \"My mouth is dry, my head is spinning, and my health is dropping.\"");
        lines.Insert("    ],");
        lines.Insert("    \"FreezingToDeathMessages\": [");
        lines.Insert("        \"I am freezing to death.\",");
        lines.Insert("        \"The cold is taking my health now.\",");
        lines.Insert("        \"I need fire or shelter immediately.\",");
        lines.Insert("        \"My body is shutting down from the cold.\"");
        lines.Insert("    ],");
        lines.Insert("    \"OverheatingToDeathMessages\": [");
        lines.Insert("        \"I am overheating to death.\",");
        lines.Insert("        \"The heat is taking my health now.\",");
        lines.Insert("        \"I need shade and water immediately.\",");
        lines.Insert("        \"My body cannot survive this heat much longer.\"");
        lines.Insert("    ]");
        lines.Insert("}");

        ST_WriteDefaultJsonFile(filePath, lines);
        Log("Created default modular config: " + filePath);
    }

    void ST_CreateDefault_World_Weather_json(string folderPath)
    {
        string filePath = folderPath + "/World_Weather.json";
        if (FileExist(filePath))
            return;

        array<string> lines = new array<string>;
        lines.Insert("{");
        lines.Insert("    \"EnableWeatherThoughts\": 1,");
        lines.Insert("    \"WeatherThoughtCooldownSeconds\": 240.0,");
        lines.Insert("    \"WeatherThoughtChance\": 0.35,");
        lines.Insert("    \"EnableClearWeatherMessages\": 1,");
        lines.Insert("    \"EnableOvercastWeatherMessages\": 1,");
        lines.Insert("    \"EnableLightRainMessages\": 1,");
        lines.Insert("    \"EnableHeavyRainMessages\": 1,");
        lines.Insert("    \"EnableFogWeatherMessages\": 1,");
        lines.Insert("    \"EnableWindWeatherMessages\": 1,");
        lines.Insert("    \"EnableStormWeatherMessages\": 1,");
        lines.Insert("    \"WeatherClearMessages\": [");
        lines.Insert("        \"Clear skies make me feel exposed.\",");
        lines.Insert("        \"Good visibility cuts both ways.\",");
        lines.Insert("        \"At least the weather is not trying to kill me.\",");
        lines.Insert("        \"The sky is open, and so is every sightline.\"");
        lines.Insert("    ],");
        lines.Insert("    \"WeatherOvercastMessages\": [");
        lines.Insert("        \"The clouds make everything feel heavier.\",");
        lines.Insert("        \"Grey skies, grey thoughts.\",");
        lines.Insert("        \"This weather feels like trouble settling in.\",");
        lines.Insert("        \"The light is flat. The world feels dead.\"");
        lines.Insert("    ],");
        lines.Insert("    \"WeatherLightRainMessages\": [");
        lines.Insert("        \"A little rain is enough to make everything miserable.\",");
        lines.Insert("        \"This drizzle will soak in if I ignore it.\",");
        lines.Insert("        \"The rain is light, but it still gives me away.\",");
        lines.Insert("        \"Wet roads, wet clothes, bad luck.\"");
        lines.Insert("    ],");
        lines.Insert("    \"WeatherHeavyRainMessages\": [");
        lines.Insert("        \"This rain is hammering everything.\",");
        lines.Insert("        \"I can barely hear through the downpour.\",");
        lines.Insert("        \"Heavy rain hides movement, including mine.\",");
        lines.Insert("        \"I need shelter before this soaks me through.\"");
        lines.Insert("    ],");
        lines.Insert("    \"WeatherRainMessages\": [");
        lines.Insert("        \"This rain is soaking through everything.\",");
        lines.Insert("        \"I need to get dry before the cold settles in.\",");
        lines.Insert("        \"Rain hides sound, but it ruins everything else.\",");
        lines.Insert("        \"Wet clothes will make the next few hours worse.\"");
        lines.Insert("    ],");
        lines.Insert("    \"WeatherFogMessages\": [");
        lines.Insert("        \"The fog is hiding too much.\",");
        lines.Insert("        \"I cannot see far enough to feel safe.\",");
        lines.Insert("        \"Everything sounds closer in this fog.\",");
        lines.Insert("        \"I should move carefully until this clears.\"");
        lines.Insert("    ],");
        lines.Insert("    \"WeatherStormMessages\": [");
        lines.Insert("        \"The weather is turning ugly.\",");
        lines.Insert("        \"This storm will cover my noise, but it could get me killed.\",");
        lines.Insert("        \"I need shelter before this gets worse.\",");
        lines.Insert("        \"Bad weather makes every decision heavier.\"");
        lines.Insert("    ],");
        lines.Insert("    \"WeatherWindMessages\": [");
        lines.Insert("        \"The wind makes it hard to hear anything moving.\",");
        lines.Insert("        \"Every gust sounds like footsteps.\",");
        lines.Insert("        \"The wind is cutting through me.\",");
        lines.Insert("        \"I should not trust my ears in this weather.\"");
        lines.Insert("    ],");
        lines.Insert("    \"LightRainThought_Min\": 0.15,");
        lines.Insert("    \"RainThought_Min\": 0.35,");
        lines.Insert("    \"HeavyRainThought_Min\": 0.65,");
        lines.Insert("    \"FogThought_Min\": 0.45,");
        lines.Insert("    \"WindThought_Min\": 8.0,");
        lines.Insert("    \"OvercastThought_Min\": 0.65,");
        lines.Insert("    \"StormRain_Min\": 0.65,");
        lines.Insert("    \"StormWind_Min\": 10.0,");
        lines.Insert("    \"StormOvercast_Min\": 0.9");
        lines.Insert("}");

        ST_WriteDefaultJsonFile(filePath, lines);
        Log("Created default modular config: " + filePath);
    }

    void ST_CreateDefault_World_Time_json(string folderPath)
    {
        string filePath = folderPath + "/World_Time.json";
        if (FileExist(filePath))
            return;

        array<string> lines = new array<string>;
        lines.Insert("{");
        lines.Insert("    \"EnableTimeOfDayThoughts\": 1,");
        lines.Insert("    \"TimeOfDayThoughtCooldownSeconds\": 300.0,");
        lines.Insert("    \"TimeOfDayThoughtChance\": 0.35,");
        lines.Insert("    \"EnableDawnMessages\": 1,");
        lines.Insert("    \"EnableMorningMessages\": 1,");
        lines.Insert("    \"EnableNoonMessages\": 1,");
        lines.Insert("    \"EnableAfternoonMessages\": 1,");
        lines.Insert("    \"EnableDuskMessages\": 1,");
        lines.Insert("    \"EnableNightMessages\": 1,");
        lines.Insert("    \"EnableMidnightMessages\": 1,");
        lines.Insert("    \"EnableEarlyMorningMessages\": 1,");
        lines.Insert("    \"DawnStartHour\": 5.0,");
        lines.Insert("    \"MorningStartHour\": 7.0,");
        lines.Insert("    \"NoonStartHour\": 11.0,");
        lines.Insert("    \"AfternoonStartHour\": 13.0,");
        lines.Insert("    \"DuskStartHour\": 18.0,");
        lines.Insert("    \"NightStartHour\": 20.0,");
        lines.Insert("    \"MidnightStartHour\": 0.0,");
        lines.Insert("    \"EarlyMorningStartHour\": 3.0,");
        lines.Insert("    \"DawnMessages\": [");
        lines.Insert("        \"The light is coming back. I made it through the dark.\",");
        lines.Insert("        \"Dawn makes everything look quieter than it is.\",");
        lines.Insert("        \"First light means movement. I will not be the only one awake.\",");
        lines.Insert("        \"The morning cold is still in my bones.\"");
        lines.Insert("    ],");
        lines.Insert("    \"MorningMessages\": [");
        lines.Insert("        \"Morning means supplies, footsteps, and bad decisions.\",");
        lines.Insert("        \"The day is young. So are the risks.\",");
        lines.Insert("        \"Light makes travel easier, but hiding harder.\",");
        lines.Insert("        \"I should move while I can still see.\"");
        lines.Insert("    ],");
        lines.Insert("    \"NoonMessages\": [");
        lines.Insert("        \"The sun is high. Shadows are short.\",");
        lines.Insert("        \"Noon makes every open field feel wider.\",");
        lines.Insert("        \"Hard daylight leaves fewer places to hide.\",");
        lines.Insert("        \"This is a good time to move, if no one is watching.\"");
        lines.Insert("    ],");
        lines.Insert("    \"AfternoonMessages\": [");
        lines.Insert("        \"The day is slipping away.\",");
        lines.Insert("        \"Afternoon always feels shorter than it should.\",");
        lines.Insert("        \"I need to think about where I will be when the light fades.\",");
        lines.Insert("        \"There is still time to search, but not much.\"");
        lines.Insert("    ],");
        lines.Insert("    \"DuskMessages\": [");
        lines.Insert("        \"Daylight is bleeding out.\",");
        lines.Insert("        \"Dusk is when mistakes start costing more.\",");
        lines.Insert("        \"I need to decide where I am sleeping.\",");
        lines.Insert("        \"The world is getting harder to read.\"");
        lines.Insert("    ],");
        lines.Insert("    \"NightMessages\": [");
        lines.Insert("        \"The dark makes every sound feel closer.\",");
        lines.Insert("        \"Night belongs to anyone patient enough to wait.\",");
        lines.Insert("        \"I should not move without a reason.\",");
        lines.Insert("        \"Every light in the dark is a confession.\"");
        lines.Insert("    ],");
        lines.Insert("    \"MidnightMessages\": [");
        lines.Insert("        \"This is the hour people disappear.\",");
        lines.Insert("        \"Midnight makes the world feel empty, but it never is.\",");
        lines.Insert("        \"The dark feels deeper now.\",");
        lines.Insert("        \"I need to stay quiet until the night starts to break.\"");
        lines.Insert("    ],");
        lines.Insert("    \"EarlyMorningMessages\": [");
        lines.Insert("        \"The last part of night always feels the longest.\",");
        lines.Insert("        \"Morning is close, but close does not mean safe.\",");
        lines.Insert("        \"Everything is cold, still, and waiting.\",");
        lines.Insert("        \"I just need to make it to first light.\"");
        lines.Insert("    ]");
        lines.Insert("}");

        ST_WriteDefaultJsonFile(filePath, lines);
        Log("Created default modular config: " + filePath);
    }

    void ST_CreateDefault_World_Locations_json(string folderPath)
    {
        string filePath = folderPath + "/World_Locations.json";
        if (FileExist(filePath))
            return;

        array<string> lines = new array<string>;
        lines.Insert("{");
        lines.Insert("    \"EnableLocationThoughts\": 1,");
        lines.Insert("    \"LocationThoughtCooldownSeconds\": 240.0,");
        lines.Insert("    \"LocationThoughtChance\": 0.35,");
        lines.Insert("    \"LocationUseCustomZones\": 1,");
        lines.Insert("    \"LocationUseFallbackDetection\": 1,");
        lines.Insert("    \"LocationCoastZMax\": 3500.0,");
        lines.Insert("    \"LocationWildernessScanRadius\": 80.0,");
        lines.Insert("    \"LocationWildernessMaxObjects\": 8,");
        lines.Insert("    \"LocationZones\": [");
        lines.Insert("        {");
        lines.Insert("            \"Name\": \"North West Airfield\",");
        lines.Insert("            \"Type\": \"Military\",");
        lines.Insert("            \"X\": 4620.0,");
        lines.Insert("            \"Z\": 10300.0,");
        lines.Insert("            \"Radius\": 900.0");
        lines.Insert("        },");
        lines.Insert("        {");
        lines.Insert("            \"Name\": \"Chernogorsk\",");
        lines.Insert("            \"Type\": \"City\",");
        lines.Insert("            \"X\": 6700.0,");
        lines.Insert("            \"Z\": 2600.0,");
        lines.Insert("            \"Radius\": 900.0");
        lines.Insert("        },");
        lines.Insert("        {");
        lines.Insert("            \"Name\": \"Elektrozavodsk\",");
        lines.Insert("            \"Type\": \"City\",");
        lines.Insert("            \"X\": 10400.0,");
        lines.Insert("            \"Z\": 2200.0,");
        lines.Insert("            \"Radius\": 850.0");
        lines.Insert("        },");
        lines.Insert("        {");
        lines.Insert("            \"Name\": \"Balota Airstrip\",");
        lines.Insert("            \"Type\": \"Military\",");
        lines.Insert("            \"X\": 4970.0,");
        lines.Insert("            \"Z\": 2450.0,");
        lines.Insert("            \"Radius\": 500.0");
        lines.Insert("        }");
        lines.Insert("    ],");
        lines.Insert("    \"LocationCoastMessages\": [");
        lines.Insert("        \"The coast is where everyone starts, and where too many people die.\",");
        lines.Insert("        \"I should not stay near the coast for long.\",");
        lines.Insert("        \"Fresh tracks, empty houses, and bad decisions. That is the coast.\",");
        lines.Insert("        \"The sea is behind me. Survival is inland.\",");
        lines.Insert("        \"Someone desperate is always close to the coast.\"");
        lines.Insert("    ],");
        lines.Insert("    \"LocationTownMessages\": [");
        lines.Insert("        \"This town feels picked clean.\",");
        lines.Insert("        \"Every window feels like it is watching me.\",");
        lines.Insert("        \"Small towns are quiet until they are not.\",");
        lines.Insert("        \"There might still be something useful here.\",");
        lines.Insert("        \"I should search quickly and leave.\"");
        lines.Insert("    ],");
        lines.Insert("    \"LocationCityMessages\": [");
        lines.Insert("        \"Too many buildings. Too many angles.\",");
        lines.Insert("        \"A city can hide supplies, infected, and people with bad intentions.\",");
        lines.Insert("        \"I do not like how many windows overlook these streets.\",");
        lines.Insert("        \"The bigger the city, the more chances to die.\",");
        lines.Insert("        \"Every street here feels exposed.\"");
        lines.Insert("    ],");
        lines.Insert("    \"LocationForestMessages\": [");
        lines.Insert("        \"The trees might keep me hidden.\",");
        lines.Insert("        \"The forest is safer, but it gives nothing for free.\",");
        lines.Insert("        \"I can disappear here if I stay quiet.\",");
        lines.Insert("        \"Every branch snap sounds louder out here.\",");
        lines.Insert("        \"The woods feel empty, but I know better.\"");
        lines.Insert("    ],");
        lines.Insert("    \"LocationWildernessMessages\": [");
        lines.Insert("        \"There is nothing out here but distance and bad weather.\",");
        lines.Insert("        \"If I get hurt out here, nobody will find me.\",");
        lines.Insert("        \"The wilderness hides me, but it can starve me too.\",");
        lines.Insert("        \"I need to know where the next water source is.\",");
        lines.Insert("        \"Out here, mistakes take longer to kill you, but they still kill you.\"");
        lines.Insert("    ],");
        lines.Insert("    \"LocationMilitaryMessages\": [");
        lines.Insert("        \"Military places always smell like trouble.\",");
        lines.Insert("        \"Good gear brings bad company.\",");
        lines.Insert("        \"Someone else will come here looking for weapons.\",");
        lines.Insert("        \"I should assume I am being watched.\",");
        lines.Insert("        \"This place is worth looting, but not worth dying for.\"");
        lines.Insert("    ],");
        lines.Insert("    \"LocationPoliceMessages\": [");
        lines.Insert("        \"Police stations are never as empty as they look.\",");
        lines.Insert("        \"There might be ammunition here, or someone waiting for it.\",");
        lines.Insert("        \"I should check the corners.\",");
        lines.Insert("        \"This place attracts desperate people.\"");
        lines.Insert("    ],");
        lines.Insert("    \"LocationMedicalMessages\": [");
        lines.Insert("        \"Hospitals always mean someone desperate came here first.\",");
        lines.Insert("        \"Medicine is worth the risk.\",");
        lines.Insert("        \"If anything is left, it will not be much.\",");
        lines.Insert("        \"I need to move fast. Everyone needs medical supplies.\",");
        lines.Insert("        \"This place feels like panic frozen in time.\"");
        lines.Insert("    ],");
        lines.Insert("    \"LocationIndustrialMessages\": [");
        lines.Insert("        \"Rust, metal, and hiding places everywhere.\",");
        lines.Insert("        \"Industrial yards always have too many blind corners.\",");
        lines.Insert("        \"Tools might be worth the risk.\",");
        lines.Insert("        \"I should listen before crossing the open ground.\",");
        lines.Insert("        \"This place echoes too much.\"");
        lines.Insert("    ],");
        lines.Insert("    \"LocationFarmMessages\": [");
        lines.Insert("        \"A farm might mean food, tools, or nothing at all.\",");
        lines.Insert("        \"The open fields make me feel exposed.\",");
        lines.Insert("        \"Barns hide more than hay now.\",");
        lines.Insert("        \"There may be animals nearby.\",");
        lines.Insert("        \"Food used to grow here. Now I have to fight for scraps.\"");
        lines.Insert("    ],");
        lines.Insert("    \"LocationWaterMessages\": [");
        lines.Insert("        \"Water means life, and footsteps.\",");
        lines.Insert("        \"Someone else may come here to drink.\",");
        lines.Insert("        \"I should fill everything I can.\",");
        lines.Insert("        \"A water source is useful, but it is never truly safe.\",");
        lines.Insert("        \"I need to drink and move before someone finds me.\"");
        lines.Insert("    ]");
        lines.Insert("}");

        ST_WriteDefaultJsonFile(filePath, lines);
        Log("Created default modular config: " + filePath);
    }

    void ST_CreateDefault_Items_Combat_Corpses_json(string folderPath)
    {
        string filePath = folderPath + "/Items_Combat_Corpses.json";
        if (FileExist(filePath))
            return;

        array<string> lines = new array<string>;
        lines.Insert("{");
        lines.Insert("    \"EnableItemConditionThoughts\": 1,");
        lines.Insert("    \"ItemConditionHealthThreshold\": 0.35,");
        lines.Insert("    \"EnableCombatStressThoughts\": 1,");
        lines.Insert("    \"CombatStressShockThreshold\": 65.0,");
        lines.Insert("    \"EnableContaminatedZoneThoughts\": 1,");
        lines.Insert("    \"EnableNearbyCorpseThoughts\": 1,");
        lines.Insert("    \"NearbyCorpseRadius\": 35.0,");
        lines.Insert("    \"ItemBadlyDamagedMessages\": [");
        lines.Insert("        \"This gear will not last much longer.\",");
        lines.Insert("        \"I should repair this before it fails me.\",");
        lines.Insert("        \"Everything I own is falling apart.\",");
        lines.Insert("        \"This could break when I need it most.\"");
        lines.Insert("    ],");
        lines.Insert("    \"CombatStressMessages\": [");
        lines.Insert("        \"That shook me.\",");
        lines.Insert("        \"Keep moving. Find cover.\",");
        lines.Insert("        \"I need a second to steady myself.\",");
        lines.Insert("        \"Do not panic.\",");
        lines.Insert("        \"My hands are not as steady as they should be.\"");
        lines.Insert("    ],");
        lines.Insert("    \"ContaminatedZoneMessages\": [");
        lines.Insert("        \"The air is wrong here.\",");
        lines.Insert("        \"I need to check my filters.\",");
        lines.Insert("        \"This suit is the only thing keeping me alive.\",");
        lines.Insert("        \"I should not stay in this gas any longer.\"");
        lines.Insert("    ],");
        lines.Insert("    \"NearbyCorpseMessages\": [");
        lines.Insert("        \"Someone died here recently.\",");
        lines.Insert("        \"This was not long ago.\",");
        lines.Insert("        \"I should not stay near the body.\",");
        lines.Insert("        \"Where there is one corpse, there may be another.\"");
        lines.Insert("    ],");
        lines.Insert("    \"ScanEquippedItemsForDamagedThoughts\": 1,");
        lines.Insert("    \"EnableCombatStressShockThoughts\": 1,");
        lines.Insert("    \"EnableCombatStressDamageEventThoughts\": 1,");
        lines.Insert("    \"CombatStressCooldownSeconds\": 20.0,");
        lines.Insert("    \"ItemWeaponDamagedMessages\": [");
        lines.Insert("        \"This weapon needs maintenance.\",");
        lines.Insert("        \"I do not trust this gun in its current state.\",");
        lines.Insert("        \"A bad weapon gets people killed.\",");
        lines.Insert("        \"This thing might fail when I need it most.\"");
        lines.Insert("    ],");
        lines.Insert("    \"ItemShoesDamagedMessages\": [");
        lines.Insert("        \"My boots are falling apart.\",");
        lines.Insert("        \"My feet are going to suffer if I do not fix these.\",");
        lines.Insert("        \"Bad shoes will slow me down.\",");
        lines.Insert("        \"I need to repair these before they give out.\"");
        lines.Insert("    ],");
        lines.Insert("    \"ItemClothingDamagedMessages\": [");
        lines.Insert("        \"My clothes are barely holding together.\",");
        lines.Insert("        \"This clothing will not protect me much longer.\",");
        lines.Insert("        \"The next fight could ruin what is left of this.\",");
        lines.Insert("        \"I need a sewing kit before this falls apart.\"");
        lines.Insert("    ],");
        lines.Insert("    \"ItemBackpackDamagedMessages\": [");
        lines.Insert("        \"My backpack is barely holding together.\",");
        lines.Insert("        \"If this pack gives out, I lose everything.\",");
        lines.Insert("        \"I should repair this bag before moving on.\",");
        lines.Insert("        \"This pack has seen better days.\"");
        lines.Insert("    ],");
        lines.Insert("    \"CombatHitMessages\": [");
        lines.Insert("        \"That hit hard.\",");
        lines.Insert("        \"I need cover now.\",");
        lines.Insert("        \"Move. Do not freeze.\",");
        lines.Insert("        \"I cannot take another hit like that.\",");
        lines.Insert("        \"Someone has me dialed in.\",");
        lines.Insert("        \"Stay low. Stay alive.\"");
        lines.Insert("    ],");
        lines.Insert("    \"CombatShockMessages\": [");
        lines.Insert("        \"My hands are not steady.\",");
        lines.Insert("        \"I need a second to get myself together.\",");
        lines.Insert("        \"Everything feels too loud.\",");
        lines.Insert("        \"I can feel myself slipping.\",");
        lines.Insert("        \"Breathe. Think. Move.\"");
        lines.Insert("    ],");
        lines.Insert("    \"ItemVestDamagedMessages\": [");
        lines.Insert("        \"My vest is barely holding together.\",");
        lines.Insert("        \"This vest will not stop much in this condition.\",");
        lines.Insert("        \"I should repair this vest before I trust it.\",");
        lines.Insert("        \"Bad armor gives false confidence.\"");
        lines.Insert("    ],");
        lines.Insert("    \"ItemHeadgearDamagedMessages\": [");
        lines.Insert("        \"My headgear is in bad shape.\",");
        lines.Insert("        \"This helmet has taken too much abuse.\",");
        lines.Insert("        \"I do not trust this on my head anymore.\",");
        lines.Insert("        \"One more hit could finish this helmet.\"");
        lines.Insert("    ],");
        lines.Insert("    \"ItemGlovesDamagedMessages\": [");
        lines.Insert("        \"My gloves are falling apart.\",");
        lines.Insert("        \"Cold hands and torn gloves are a bad mix.\",");
        lines.Insert("        \"I need to fix these gloves before they give out.\",");
        lines.Insert("        \"My hands need better protection than this.\"");
        lines.Insert("    ],");
        lines.Insert("    \"ItemMaskDamagedMessages\": [");
        lines.Insert("        \"My face covering is almost ruined.\",");
        lines.Insert("        \"This mask will not protect me much longer.\",");
        lines.Insert("        \"I should replace this before I need it.\",");
        lines.Insert("        \"Breathing through torn gear feels wrong.\"");
        lines.Insert("    ],");
        lines.Insert("    \"ItemBeltDamagedMessages\": [");
        lines.Insert("        \"This belt is barely holding my gear together.\",");
        lines.Insert("        \"If this belt fails, I lose more than cloth.\",");
        lines.Insert("        \"I should repair this before it gives out.\",");
        lines.Insert("        \"Everything hanging from this feels less secure.\"");
        lines.Insert("    ],");
        lines.Insert("    \"EnableBleedingReactionThoughts\": 1,");
        lines.Insert("    \"HeavyHitHealthDamage_Min\": 25.0,");
        lines.Insert("    \"HeavyHitBloodDamage_Min\": 300.0,");
        lines.Insert("    \"HeavyHitShockDamage_Min\": 35.0,");
        lines.Insert("    \"ZombieHitMessages\": [");
        lines.Insert("        \"An infected hit me.\",");
        lines.Insert("        \"It got too close.\",");
        lines.Insert("        \"I need to keep distance from them.\",");
        lines.Insert("        \"That infected nearly tore into me.\",");
        lines.Insert("        \"I should not let them surround me.\",");
        lines.Insert("        \"Back up. Do not let them grab me.\",");
        lines.Insert("        \"Their hands are quicker than they look.\"");
        lines.Insert("    ],");
        lines.Insert("    \"PlayerMeleeHitMessages\": [");
        lines.Insert("        \"Someone hit me.\",");
        lines.Insert("        \"That was too close.\",");
        lines.Insert("        \"I need space before they swing again.\",");
        lines.Insert("        \"They are on top of me.\",");
        lines.Insert("        \"I need to move.\",");
        lines.Insert("        \"Keep distance. Do not let them control the fight.\"");
        lines.Insert("    ],");
        lines.Insert("    \"GunshotHitMessages\": [");
        lines.Insert("        \"I have been shot.\",");
        lines.Insert("        \"That round hit me.\",");
        lines.Insert("        \"I need cover now.\",");
        lines.Insert("        \"Someone has eyes on me.\",");
        lines.Insert("        \"I cannot stay in the open.\",");
        lines.Insert("        \"Find cover. Stop the bleeding. Stay alive.\",");
        lines.Insert("        \"The shot came from somewhere close enough.\"");
        lines.Insert("    ],");
        lines.Insert("    \"ExplosionHitMessages\": [");
        lines.Insert("        \"The blast hit me hard.\",");
        lines.Insert("        \"My ears are ringing.\",");
        lines.Insert("        \"I need to get away from here.\",");
        lines.Insert("        \"Everything is spinning after that explosion.\",");
        lines.Insert("        \"That nearly killed me.\",");
        lines.Insert("        \"Move before another one lands.\"");
        lines.Insert("    ],");
        lines.Insert("    \"HeavyHitMessages\": [");
        lines.Insert("        \"That hit hard.\",");
        lines.Insert("        \"I need to recover.\",");
        lines.Insert("        \"My body is screaming.\",");
        lines.Insert("        \"I cannot take another hit like that.\",");
        lines.Insert("        \"I need to get out of this fight.\",");
        lines.Insert("        \"Everything hurts. Move anyway.\",");
        lines.Insert("        \"I need cover before my legs give out.\"");
        lines.Insert("    ],");
        lines.Insert("    \"BleedingStartedMessages\": [");
        lines.Insert("        \"I am bleeding.\",");
        lines.Insert("        \"That opened me up.\",");
        lines.Insert("        \"Blood is running down my body.\",");
        lines.Insert("        \"I need to bandage this now.\",");
        lines.Insert("        \"This wound is not going to close itself.\",");
        lines.Insert("        \"I need pressure on this wound.\"");
        lines.Insert("    ],");
        lines.Insert("    \"BleedingWorseMessages\": [");
        lines.Insert("        \"I am bleeding from more than one wound.\",");
        lines.Insert("        \"There is too much blood.\",");
        lines.Insert("        \"I need to stop the bleeding before I pass out.\",");
        lines.Insert("        \"I cannot keep losing blood like this.\",");
        lines.Insert("        \"This is getting bad fast.\",");
        lines.Insert("        \"Too many wounds. I need to deal with this now.\"");
        lines.Insert("    ],");
        lines.Insert("    \"BleedingStoppedMessages\": [");
        lines.Insert("        \"The bleeding has stopped.\",");
        lines.Insert("        \"That should hold for now.\",");
        lines.Insert("        \"I need to keep pressure off this wound.\",");
        lines.Insert("        \"That was too close.\",");
        lines.Insert("        \"At least I am not bleeding anymore.\",");
        lines.Insert("        \"I bought myself a little more time.\"");
        lines.Insert("    ]");
        lines.Insert("}");

        ST_WriteDefaultJsonFile(filePath, lines);
        Log("Created default modular config: " + filePath);
    }

    void ST_CreateDefault_Messages_Damage_json(string folderPath)
    {
        string filePath = folderPath + "/Messages_Damage.json";
        if (FileExist(filePath))
            return;

        array<string> lines = new array<string>;
        lines.Insert("{");
        lines.Insert("    \"EnableDamageReactionThoughts\": 1,");
        lines.Insert("    \"EnableBleedingReactionThoughts\": 1,");
        lines.Insert("    \"EnableZombieHitMessages\": 1,");
        lines.Insert("    \"EnablePlayerMeleeHitMessages\": 1,");
        lines.Insert("    \"EnableGunshotHitMessages\": 1,");
        lines.Insert("    \"EnableExplosionHitMessages\": 1,");
        lines.Insert("    \"EnableHeavyHitMessages\": 1,");
        lines.Insert("    \"EnableBleedingStartedMessages\": 1,");
        lines.Insert("    \"EnableBleedingWorseMessages\": 1,");
        lines.Insert("    \"EnableBleedingStoppedMessages\": 1,");
        lines.Insert("    \"HeavyHitHealthDamage_Min\": 25.0,");
        lines.Insert("    \"HeavyHitBloodDamage_Min\": 300.0,");
        lines.Insert("    \"HeavyHitShockDamage_Min\": 35.0,");
        lines.Insert("    \"ZombieHitMessages\": [");
        lines.Insert("        \"An infected hit me.\",");
        lines.Insert("        \"It got too close.\",");
        lines.Insert("        \"I need to keep distance from them.\",");
        lines.Insert("        \"That infected nearly tore into me.\",");
        lines.Insert("        \"Do not let them surround me.\"");
        lines.Insert("    ],");
        lines.Insert("    \"PlayerMeleeHitMessages\": [");
        lines.Insert("        \"Someone hit me.\",");
        lines.Insert("        \"They are too close.\",");
        lines.Insert("        \"I need space before they swing again.\",");
        lines.Insert("        \"Move. Do not let them pin me down.\",");
        lines.Insert("        \"I need to break contact.\"");
        lines.Insert("    ],");
        lines.Insert("    \"GunshotHitMessages\": [");
        lines.Insert("        \"I have been shot.\",");
        lines.Insert("        \"That round hit me.\",");
        lines.Insert("        \"I need cover now.\",");
        lines.Insert("        \"Someone has eyes on me.\",");
        lines.Insert("        \"I cannot stay in the open.\"");
        lines.Insert("    ],");
        lines.Insert("    \"ExplosionHitMessages\": [");
        lines.Insert("        \"The blast hit me hard.\",");
        lines.Insert("        \"My ears are ringing.\",");
        lines.Insert("        \"Everything is spinning.\",");
        lines.Insert("        \"I need to get away from here.\",");
        lines.Insert("        \"That nearly ended me.\"");
        lines.Insert("    ],");
        lines.Insert("    \"HeavyHitMessages\": [");
        lines.Insert("        \"That hit hard.\",");
        lines.Insert("        \"My body is screaming.\",");
        lines.Insert("        \"I cannot take another hit like that.\",");
        lines.Insert("        \"I need to get out of this fight.\",");
        lines.Insert("        \"I need a second to recover.\"");
        lines.Insert("    ],");
        lines.Insert("    \"BleedingStartedMessages\": [");
        lines.Insert("        \"I am bleeding.\",");
        lines.Insert("        \"That opened me up.\",");
        lines.Insert("        \"Blood is running down my body.\",");
        lines.Insert("        \"I need to bandage this now.\",");
        lines.Insert("        \"This wound is not closing itself.\"");
        lines.Insert("    ],");
        lines.Insert("    \"BleedingWorseMessages\": [");
        lines.Insert("        \"I am bleeding from more than one wound.\",");
        lines.Insert("        \"There is too much blood.\",");
        lines.Insert("        \"I need to stop the bleeding before I pass out.\",");
        lines.Insert("        \"This is getting bad fast.\",");
        lines.Insert("        \"I cannot keep losing blood like this.\"");
        lines.Insert("    ],");
        lines.Insert("    \"BleedingStoppedMessages\": [");
        lines.Insert("        \"The bleeding has stopped.\",");
        lines.Insert("        \"That should hold for now.\",");
        lines.Insert("        \"At least I am not bleeding anymore.\",");
        lines.Insert("        \"That was too close.\",");
        lines.Insert("        \"I need to be more careful.\"");
        lines.Insert("    ]");
        lines.Insert("}");

        ST_WriteDefaultJsonFile(filePath, lines);
        Log("Created default modular config: " + filePath);
    }

    void ST_CreateDefault_Items_json(string folderPath)
    {
        string filePath = folderPath + "/Items.json";
        if (FileExist(filePath))
            return;

        array<string> lines = new array<string>;
        lines.Insert("{");
        lines.Insert("    \"EnableItemConditionThoughts\": 1,");
        lines.Insert("    \"ItemConditionHealthThreshold\": 0.35,");
        lines.Insert("    \"ScanEquippedItemsForDamagedThoughts\": 1,");
        lines.Insert("    \"EnableHandsItemConditionMessages\": 1,");
        lines.Insert("    \"EnableWeaponConditionMessages\": 1,");
        lines.Insert("    \"EnableClothingConditionMessages\": 1,");
        lines.Insert("    \"EnableShoesConditionMessages\": 1,");
        lines.Insert("    \"EnableBackpackConditionMessages\": 1,");
        lines.Insert("    \"EnableVestConditionMessages\": 1,");
        lines.Insert("    \"EnableHeadgearConditionMessages\": 1,");
        lines.Insert("    \"EnableGlovesConditionMessages\": 1,");
        lines.Insert("    \"EnableMaskConditionMessages\": 1,");
        lines.Insert("    \"EnableBeltConditionMessages\": 1,");
        lines.Insert("    \"ItemBadlyDamagedMessages\": [");
        lines.Insert("        \"This gear will not last much longer.\",");
        lines.Insert("        \"My equipment is falling apart.\",");
        lines.Insert("        \"I should repair this before it fails me.\",");
        lines.Insert("        \"Nothing lasts out here without care.\"");
        lines.Insert("    ],");
        lines.Insert("    \"ItemWeaponDamagedMessages\": [");
        lines.Insert("        \"This weapon needs maintenance.\",");
        lines.Insert("        \"I do not trust this weapon in its current state.\",");
        lines.Insert("        \"One jam at the wrong time could kill me.\",");
        lines.Insert("        \"I should clean or repair this before a fight.\"");
        lines.Insert("    ],");
        lines.Insert("    \"ItemShoesDamagedMessages\": [");
        lines.Insert("        \"My boots are falling apart.\",");
        lines.Insert("        \"My feet are going to suffer if I do not fix these.\",");
        lines.Insert("        \"Bad shoes will get me killed slowly.\",");
        lines.Insert("        \"Every step is wearing these down.\"");
        lines.Insert("    ],");
        lines.Insert("    \"ItemClothingDamagedMessages\": [");
        lines.Insert("        \"My clothes are barely holding together.\",");
        lines.Insert("        \"This clothing will not protect me much longer.\",");
        lines.Insert("        \"The fabric is torn and useless in places.\",");
        lines.Insert("        \"I need to patch this before the weather gets worse.\"");
        lines.Insert("    ],");
        lines.Insert("    \"ItemBackpackDamagedMessages\": [");
        lines.Insert("        \"My backpack is falling apart.\",");
        lines.Insert("        \"If this pack gives out, I lose everything.\",");
        lines.Insert("        \"The straps feel weak.\",");
        lines.Insert("        \"I should repair this bag before it splits.\"");
        lines.Insert("    ],");
        lines.Insert("    \"ItemVestDamagedMessages\": [");
        lines.Insert("        \"My vest has taken a beating.\",");
        lines.Insert("        \"This vest will not protect me much longer.\",");
        lines.Insert("        \"I should repair this before trusting it.\",");
        lines.Insert("        \"The damage is starting to show.\"");
        lines.Insert("    ],");
        lines.Insert("    \"ItemHeadgearDamagedMessages\": [");
        lines.Insert("        \"My headgear is barely holding up.\",");
        lines.Insert("        \"This helmet has seen better days.\",");
        lines.Insert("        \"I should not trust this to stop much.\",");
        lines.Insert("        \"One more hit could ruin it.\"");
        lines.Insert("    ],");
        lines.Insert("    \"ItemGlovesDamagedMessages\": [");
        lines.Insert("        \"My gloves are wearing thin.\",");
        lines.Insert("        \"My hands need better protection.\",");
        lines.Insert("        \"These gloves will not last.\",");
        lines.Insert("        \"Cold and cuts will get through soon.\"");
        lines.Insert("    ],");
        lines.Insert("    \"ItemMaskDamagedMessages\": [");
        lines.Insert("        \"My mask is in bad shape.\",");
        lines.Insert("        \"I should not trust this mask much longer.\",");
        lines.Insert("        \"The seal feels wrong.\",");
        lines.Insert("        \"This needs replacing before it matters.\"");
        lines.Insert("    ],");
        lines.Insert("    \"ItemBeltDamagedMessages\": [");
        lines.Insert("        \"My belt is coming apart.\",");
        lines.Insert("        \"If this gives out, I lose gear.\",");
        lines.Insert("        \"The fastening feels weak.\",");
        lines.Insert("        \"I should repair this before moving far.\"");
        lines.Insert("    ]");
        lines.Insert("}");

        ST_WriteDefaultJsonFile(filePath, lines);
        Log("Created default modular config: " + filePath);
    }

    void ST_CreateDefault_Corpses_json(string folderPath)
    {
        string filePath = folderPath + "/Corpses.json";
        if (FileExist(filePath))
            return;

        array<string> lines = new array<string>;
        lines.Insert("{");
        lines.Insert("    \"EnableNearbyCorpseThoughts\": 1,");
        lines.Insert("    \"NearbyCorpseRadius\": 35.0,");
        lines.Insert("    \"NearbyCorpseMessages\": [");
        lines.Insert("        \"Someone died here recently.\",");
        lines.Insert("        \"This was not long ago.\",");
        lines.Insert("        \"I should not stay near the body.\",");
        lines.Insert("        \"Where there is one corpse, there may be another.\"");
        lines.Insert("    ],");
        lines.Insert("    \"NearbyPlayerCorpseMessages\": [");
        lines.Insert("        \"That was a survivor.\",");
        lines.Insert("        \"Someone ended up here before me.\",");
        lines.Insert("        \"I should find out what killed them before it finds me.\",");
        lines.Insert("        \"A dead survivor means danger passed through.\"");
        lines.Insert("    ],");
        lines.Insert("    \"NearbyInfectedCorpseMessages\": [");
        lines.Insert("        \"An infected dropped here.\",");
        lines.Insert("        \"Something killed this infected.\",");
        lines.Insert("        \"Dead infected usually mean someone passed through.\",");
        lines.Insert("        \"This place may not be as empty as it looks.\"");
        lines.Insert("    ],");
        lines.Insert("    \"NearbyAnimalCorpseMessages\": [");
        lines.Insert("        \"Fresh meat, or fresh danger.\",");
        lines.Insert("        \"Something killed this animal.\",");
        lines.Insert("        \"This carcass might draw attention.\",");
        lines.Insert("        \"I should not stand around it for long.\"");
        lines.Insert("    ]");
        lines.Insert("}");

        ST_WriteDefaultJsonFile(filePath, lines);
        Log("Created default modular config: " + filePath);
    }

    void ST_CreateDefault_Personality_json(string folderPath)
    {
        string filePath = folderPath + "/Personality.json";
        if (FileExist(filePath))
            return;

        array<string> lines = new array<string>;
        lines.Insert("{");
        lines.Insert("    \"EnablePersonalityProfiles\": 1,");
        lines.Insert("    \"PersonalityThoughtChance\": 0.2,");
        lines.Insert("    \"PersonalityPersistBySteamId\": 1,");
        lines.Insert("    \"PersonalityDataFile\": \"$mission:storage_1/ZombiCideMods/SurvivorThoughts/Data/PlayerPersonalities.json\",");
        lines.Insert("    \"EnablePersonalityChangeOverTime\": 1,");
        lines.Insert("    \"PersonalityChangeChance\": 0.08,");
        lines.Insert("    \"PersonalityMinimumSecondsBetweenChanges\": 7200.0,");
        lines.Insert("    \"PersonalityPracticalMessages\": [");
        lines.Insert("        \"Priorities first. Water, food, shelter.\",");
        lines.Insert("        \"Check supplies, check exits, keep moving.\",");
        lines.Insert("        \"Do not waste energy.\",");
        lines.Insert("        \"Solve the worst problem first.\",");
        lines.Insert("        \"Inventory, route, risk. In that order.\",");
        lines.Insert("        \"If it cannot help me survive, leave it.\",");
        lines.Insert("        \"Stay quiet and make decisions.\",");
        lines.Insert("        \"One useful item is better than three useless ones.\"");
        lines.Insert("    ],");
        lines.Insert("    \"PersonalityScaredMessages\": [");
        lines.Insert("        \"I hate this place.\",");
        lines.Insert("        \"Every sound feels too close.\",");
        lines.Insert("        \"I do not want to die here.\",");
        lines.Insert("        \"Something is always moving out there.\",");
        lines.Insert("        \"I need to get away from this area.\",");
        lines.Insert("        \"My hands will not stop shaking.\",");
        lines.Insert("        \"This silence feels wrong.\",");
        lines.Insert("        \"I should not be alone out here.\"");
        lines.Insert("    ],");
        lines.Insert("    \"PersonalityMilitaryMessages\": [");
        lines.Insert("        \"Assess the area. Move with purpose.\",");
        lines.Insert("        \"Cover first, then supplies.\",");
        lines.Insert("        \"Noise discipline. Always.\",");
        lines.Insert("        \"Check angles before crossing.\",");
        lines.Insert("        \"Do not skyline yourself.\",");
        lines.Insert("        \"Keep the weapon ready and the route clear.\",");
        lines.Insert("        \"Threats first, comfort second.\",");
        lines.Insert("        \"Plan the exit before entering.\"");
        lines.Insert("    ],");
        lines.Insert("    \"PersonalityHopelessMessages\": [");
        lines.Insert("        \"It never gets easier.\",");
        lines.Insert("        \"Nobody is coming.\",");
        lines.Insert("        \"This place takes everything eventually.\",");
        lines.Insert("        \"Every day feels borrowed.\",");
        lines.Insert("        \"I do not know how much more I have left.\",");
        lines.Insert("        \"The world ended, but the suffering did not.\",");
        lines.Insert("        \"Surviving is starting to feel like habit.\",");
        lines.Insert("        \"There is always another problem.\"");
        lines.Insert("    ],");
        lines.Insert("    \"PersonalityAggressiveMessages\": [");
        lines.Insert("        \"Keep moving. Take what you need.\",");
        lines.Insert("        \"Fear gets people killed.\",");
        lines.Insert("        \"If someone is nearby, be ready.\",");
        lines.Insert("        \"Do not hesitate if it turns bad.\",");
        lines.Insert("        \"This world rewards the faster hand.\",");
        lines.Insert("        \"Weakness invites trouble.\",");
        lines.Insert("        \"Push through it.\",");
        lines.Insert("        \"Survive first, regret later.\"");
        lines.Insert("    ],");
        lines.Insert("    \"PersonalityCalmMessages\": [");
        lines.Insert("        \"Breathe. Think. Move.\",");
        lines.Insert("        \"One problem at a time.\",");
        lines.Insert("        \"Panic wastes strength.\",");
        lines.Insert("        \"Slow is smooth. Smooth is alive.\",");
        lines.Insert("        \"Listen before moving.\",");
        lines.Insert("        \"Do what needs doing.\",");
        lines.Insert("        \"Stay calm and keep control.\",");
        lines.Insert("        \"There is still a way through this.\"");
        lines.Insert("    ]");
        lines.Insert("}");

        ST_WriteDefaultJsonFile(filePath, lines);
        Log("Created default modular config: " + filePath);
    }

    void ST_CreateDefault_Admin_json(string folderPath)
    {
        string filePath = folderPath + "/Admin.json";
        if (FileExist(filePath))
            return;

        array<string> lines = new array<string>;
        lines.Insert("{");
        lines.Insert("    \"EnableAdminReload\": 1,");
        lines.Insert("    \"AdminReloadCommand\": \"!streload\",");
        lines.Insert("    \"AdminSteamIds\": [");
        lines.Insert("        \"76561198833385698\"");
        lines.Insert("    ]");
        lines.Insert("}");

        ST_WriteDefaultJsonFile(filePath, lines);
        Log("Created default modular config: " + filePath);
    }

    string ST_GetTimestamp()
    {
        int year, month, day, hour, minute, second;
        GetYearMonthDay(year, month, day);
        GetHourMinuteSecond(hour, minute, second);

        return year.ToStringLen(4) + "-" + month.ToStringLen(2) + "-" + day.ToStringLen(2) + " " + hour.ToStringLen(2) + ":" + minute.ToStringLen(2) + ":" + second.ToStringLen(2);
    }

    void EnsureLogDirectory()
    {
        if (!FileExist("$profile:ZombicideMods"))
            MakeDirectory("$profile:ZombicideMods");

        if (!FileExist("$profile:ZombicideMods/SurvivorThoughts"))
            MakeDirectory("$profile:ZombicideMods/SurvivorThoughts");

        if (!FileExist("$profile:ZombicideMods/SurvivorThoughts/Logs"))
            MakeDirectory("$profile:ZombicideMods/SurvivorThoughts/Logs");
    }

    string ST_GetDebugLogPath()
    {
        ST_SurvivorThoughtsConfig config = m_Config;

        string fileName = "SurvivorThoughts_Debug.log";

        if (config && config.DebugLogFileName != "")
            fileName = config.DebugLogFileName;

        return "$profile:ZombicideMods/SurvivorThoughts/Logs/" + fileName;
    }

    void InitDebugLogFile()
    {
        ST_SurvivorThoughtsConfig config = m_Config;

        if (!config)
            return;

        if (config.EnableDebugFileLog != 1)
            return;

        EnsureLogDirectory();

        string logPath = ST_GetDebugLogPath();

        if (!m_ST_DebugLogInitialized)
        {
            if (config.ClearDebugLogOnServerStart == 1)
            {
                FileHandle clearFile = OpenFile(logPath, FileMode.WRITE);

                if (clearFile)
                {
                    FPrintln(clearFile, "============================================================");
                    FPrintln(clearFile, " Survivor Thoughts Debug Log");
                    FPrintln(clearFile, " Started: " + ST_GetTimestamp());
                    FPrintln(clearFile, "============================================================");
                    CloseFile(clearFile);
                }
                else
                {
                    Print("[SurvivorThoughts][ERROR] Failed to create debug log file: " + logPath);
                }
            }
            else
            {
                FileHandle appendFile = OpenFile(logPath, FileMode.APPEND);

                if (appendFile)
                {
                    FPrintln(appendFile, "");
                    FPrintln(appendFile, "================ New Server Session: " + ST_GetTimestamp() + " ================");
                    CloseFile(appendFile);
                }
                else
                {
                    Print("[SurvivorThoughts][ERROR] Failed to append debug log file: " + logPath);
                }
            }

            m_ST_DebugLogInitialized = true;
        }
        else
        {
            FileHandle reloadFile = OpenFile(logPath, FileMode.APPEND);

            if (reloadFile)
            {
                FPrintln(reloadFile, "[" + ST_GetTimestamp() + "] Debug log refreshed / configs reloaded.");
                CloseFile(reloadFile);
            }
        }
    }

    void Log(string message)
    {
        ST_SurvivorThoughtsConfig config = m_Config;

        if (config && config.DebugMode == 1)
        {
            Print("[SurvivorThoughts] " + message);
        }
    }

    void DebugLog(string message)
    {
        ST_SurvivorThoughtsConfig config = m_Config;

        if (!config)
            return;

        if (config.DebugMode != 1)
            return;

        string finalMessage = "[SurvivorThoughts][DEBUG][" + ST_GetTimestamp() + "] " + message;

        if (config.DebugLogToRPT == 1)
        {
            Print(finalMessage);
        }

        if (config.EnableDebugFileLog == 1)
        {
            EnsureLogDirectory();

            string logPath = ST_GetDebugLogPath();
            FileHandle file = OpenFile(logPath, FileMode.APPEND);

            if (file)
            {
                FPrintln(file, finalMessage);
                CloseFile(file);
            }
            else
            {
                Print("[SurvivorThoughts][ERROR] Failed to open debug log file: " + logPath);
            }
        }
    }


    void ST_EnsureDirectoryPath(string dirPath)
    {
        if (dirPath == "")
            return;

        // Create the standard mission-storage parent folders first.
        // DayZ MakeDirectory is safest when parents already exist.
        if (!FileExist("$mission:storage_1/ZombiCideMods"))
            MakeDirectory("$mission:storage_1/ZombiCideMods");

        if (!FileExist("$mission:storage_1/ZombiCideMods/SurvivorThoughts"))
            MakeDirectory("$mission:storage_1/ZombiCideMods/SurvivorThoughts");

        if (!FileExist("$mission:storage_1/ZombiCideMods/SurvivorThoughts/Debug"))
            MakeDirectory("$mission:storage_1/ZombiCideMods/SurvivorThoughts/Debug");

        if (!FileExist("$mission:storage_1/ZombiCideMods/SurvivorThoughts/Analytics"))
            MakeDirectory("$mission:storage_1/ZombiCideMods/SurvivorThoughts/Analytics");

        if (!FileExist("$mission:storage_1/ZombiCideMods/SurvivorThoughts/Journals"))
            MakeDirectory("$mission:storage_1/ZombiCideMods/SurvivorThoughts/Journals");

        if (!FileExist(dirPath))
            MakeDirectory(dirPath);
    }

    string ST_GetSafeSteamId(PlayerBase player)
    {
        if (!player || !player.GetIdentity())
            return "UnknownPlayer";

        return player.GetIdentity().GetPlainId();
    }

    string ST_GetSafePlayerName(PlayerBase player)
    {
        if (!player || !player.GetIdentity())
            return "Unknown";

        return player.GetIdentity().GetName();
    }

    void ST_WriteThoughtDecisionTrace(PlayerBase player, string thoughtType, string message, int priority, string result, string reason)
    {
        ST_SurvivorThoughtsConfig config = GetConfig();

        if (!config || config.EnableThoughtDecisionTrace != 1)
            return;

        if (config.TraceOnlyBlockedThoughts == 1 && result != "Blocked")
            return;

        string line = "[SurvivorThoughts][TRACE][" + ST_GetTimestamp() + "] Player=" + ST_GetSafePlayerName(player) + " Type=" + thoughtType + " Priority=" + priority.ToString() + " Result=" + result + " Reason=" + reason + " Message=" + message;

        if (config.TraceToDebugLog == 1)
            DebugLog(line);

        if (config.TraceToMissionStorage == 1)
        {
            ST_EnsureDirectoryPath(config.DecisionTraceFolder);
            string path = config.DecisionTraceFolder + "/" + ST_GetSafeSteamId(player) + "_DecisionTrace.log";
            FileHandle file = OpenFile(path, FileMode.APPEND);

            if (file)
            {
                FPrintln(file, line);
                CloseFile(file);
            }
        }
    }

    void ST_WritePlayerStateSnapshot(PlayerBase player, string snapshotLine)
    {
        ST_SurvivorThoughtsConfig config = GetConfig();

        if (!config || config.EnableStateSnapshots != 1 || config.EnablePersistentStateSnapshots != 1)
            return;

        ST_EnsureDirectoryPath(config.StateSnapshotFolder);
        string path = config.StateSnapshotFolder + "/" + ST_GetSafeSteamId(player) + "_PlayerState.jsonl";
        FileHandle file = OpenFile(path, FileMode.APPEND);

        if (file)
        {
            FPrintln(file, snapshotLine);
            CloseFile(file);
        }
    }

    void ST_RecordAnalyticsEvent(string eventName, string thoughtType)
    {
        ST_SurvivorThoughtsConfig config = GetConfig();

        if (!config || config.EnableAdminAnalytics != 1)
            return;

        ST_EnsureDirectoryPath(config.AnalyticsFolder);
        string path = config.AnalyticsFolder + "/SurvivorThoughts_Analytics.log";
        FileHandle file = OpenFile(path, FileMode.APPEND);

        if (file)
        {
            FPrintln(file, ST_GetTimestamp() + " Event=" + eventName + " Type=" + thoughtType);
            CloseFile(file);
        }

        if (config.EnableAnalyticsJsonLines == 1 && config.AnalyticsJsonLineFile != "")
        {
            ST_EnsureDirectoryPath(config.AnalyticsFolder);
            FileHandle jsonFile = OpenFile(config.AnalyticsJsonLineFile, FileMode.APPEND);

            if (jsonFile)
            {
                FPrintln(jsonFile, "{ \"Time\": \"" + ST_GetTimestamp() + "\", \"Event\": \"" + eventName + "\", \"Type\": \"" + thoughtType + "\" }");
                CloseFile(jsonFile);
            }
        }
    }

    bool ST_IsJournalAmbientThoughtType(string thoughtType)
    {
        switch (thoughtType)
        {
            case "WEATHER":
            case "TIME_OF_DAY":
            case "LOCATION":
            case "MAP_ENVIRONMENT":
            case "PERSONALITY":
            case "LOW_SURVIVAL":
            case "OPEN_CLOSE":
                return true;
        }

        return false;
    }

    bool ST_IsJournalAlwaysMajorThoughtType(string thoughtType)
    {
        switch (thoughtType)
        {
            case "BLEEDING_STARTED":
            case "BLEEDING_WORSE":
            case "BLEEDING_STOPPED":
            case "GUNSHOT_HIT":
            case "EXPLOSION_HIT":
            case "HEAVY_HIT":
            case "PLAYER_MELEE_HIT":
            case "ZOMBIE_HIT":
            case "DEATH_SPIRAL":
            case "CRITICAL_SURVIVAL":
            case "ADVANCED_COMBINED":
            case "RECOVERY":
            case "NEAR_MISS":
            case "DISEASE_SPECIFIC":
            case "SOCIAL_GROUP":
            case "SANITY_CREEP":
            case "MENTAL_STATE":
            case "PLAYER_MEMORY":
            case "CUSTOM_THOUGHT_ZONE":
            case "CONTAMINATED_ZONE":
            case "CORPSE":
            case "JOURNAL_SYSTEM":
                return true;
        }

        return false;
    }

    void ST_LinkThoughtToSurvivorJournal(PlayerBase player, string thoughtType, string message, string result)
    {
        if (!player || message == "")
            return;

        ST_SurvivorThoughtsConfig config = GetConfig();

        if (!config)
            return;

        if (config.EnableSurvivorJournalItem != 1 || config.EnableJournalSystemIntegration != 1)
            return;

        if (result != "Allowed" && config.JournalRecordBlockedDecisionEvents != 1)
            return;

        int priority = ST_GetThoughtPriority(thoughtType, config);

        if (ST_IsJournalAmbientThoughtType(thoughtType) && config.JournalRecordAmbientSystems != 1 && priority < config.JournalMajorEventMinPriority)
            return;

        if (config.JournalRecordAllThoughtSystems != 1 && !ST_IsJournalAlwaysMajorThoughtType(thoughtType) && priority < config.JournalMajorEventMinPriority)
            return;

        if (!ST_IsJournalAlwaysMajorThoughtType(thoughtType) && priority < config.JournalMajorEventMinPriority)
            return;

        string entry = message;

        if (config.JournalMajorEventPrefixWithSystem == 1)
            entry = "[" + thoughtType + "] " + entry;

        if (result != "Allowed")
            entry = "[" + result + "] " + entry;

        if (config.JournalMajorEventIncludeStats == 1)
            entry = entry + " Stats=" + player.ST_GetSurvivorThoughtsStatSummary();

        if (!m_PersistentStateStore)
            LoadPersistentStateStore();

        if (!m_PersistentStateStore)
            m_PersistentStateStore = new ST_PlayerPersistentStateStore();

        string steamId = ST_GetPlayerSteamId(player);
        if (steamId == "")
            return;

        ST_PlayerPersistentStateRecord record = m_PersistentStateStore.GetOrCreateRecord(steamId);

        if (!record.MajorJournalEvents)
            record.MajorJournalEvents = new array<string>;

        record.MajorJournalEvents.Insert(entry);

        while (record.MajorJournalEvents.Count() > config.MaxMajorJournalEventsStored)
            record.MajorJournalEvents.Remove(0);

        if (GetGame())
            record.JournalLastUpdatedTime = GetGame().GetTime() / 1000.0;

        SavePersistentStateStore();

        if (config.JournalRecordSystemLinkDebug == 1)
            DebugLog("Journal linked thought. Type=" + thoughtType + " Result=" + result + " Priority=" + priority.ToString());
    }


    void ST_WritePlayerJournalEntry(PlayerBase player, string thoughtType, string message)
    {
        ST_SurvivorThoughtsConfig config = GetConfig();

        if (!config)
            return;

        bool wroteJsonLine = false;

        if (config.EnablePlayerJournals == 1)
        {
            bool allowJsonLine = true;

            if (config.JournalOnlyMajorEvents == 1)
            {
                int priority = ST_GetThoughtPriority(thoughtType, config);

                if (priority < 70)
                {
                    if (!(config.JournalWriteAllRecoveryEvents == 1 && thoughtType == "RECOVERY"))
                        allowJsonLine = false;
                }
            }

            if (allowJsonLine)
            {
                ST_EnsureDirectoryPath(config.PlayerJournalFolder);
                string path = config.PlayerJournalFolder + "/" + ST_GetSafeSteamId(player) + "_Journal.jsonl";
                FileHandle file = OpenFile(path, FileMode.APPEND);

                if (file)
                {
                    if (config.JournalIncludePlayerStats == 1 && player)
                    {
                        string stats = player.ST_GetSurvivorThoughtsStatSummary();
                        FPrintln(file, "{ \"Time\": \"" + ST_GetTimestamp() + "\", \"Type\": \"" + thoughtType + "\", \"Message\": \"" + message + "\", \"Stats\": " + stats + " }");
                    }
                    else
                    {
                        FPrintln(file, "{ \"Time\": \"" + ST_GetTimestamp() + "\", \"Type\": \"" + thoughtType + "\", \"Message\": \"" + message + "\" }");
                    }

                    CloseFile(file);
                    wroteJsonLine = true;
                }
            }
        }

        ST_LinkThoughtToSurvivorJournal(player, thoughtType, message, "Allowed");
    }

    void ST_CreateDefault_Player_State_History_json(string modularFolderPath)
    {
        string json = "{\n";
        json += "  \"EnablePlayerStateHistory\": 1,\n";
        json += "  \"StateHistorySampleIntervalSeconds\": 30.0,\n";
        json += "  \"StateHistoryWindowSeconds\": 900.0,\n";
        json += "  \"TrendChangeThreshold\": 0.10,\n";
        json += "  \"EnableTrendMessages\": 1,\n";
        json += "  \"EnableProlongedStateMessages\": 1,\n";
        json += "  \"ProlongedStateThresholdSeconds\": 600.0,\n";
        json += "  \"EnableStateSnapshots\": 0,\n";
        json += "  \"StateSnapshotIntervalSeconds\": 300.0,\n";
        json += "  \"EnablePersistentStateSnapshots\": 0,\n";
        json += "  \"StateSnapshotFolder\": \"$mission:storage_1/ZombiCideMods/SurvivorThoughts/Debug/PlayerStateSnapshots\",\n";
        json += "  \"TrendEnergyFallingMessages\": [\"I am burning through what little energy I have left.\", \"The hunger is getting worse, not better.\", \"My body is running out of fuel.\", \"Every step costs more than I can afford.\"],\n";
        json += "  \"TrendWaterFallingMessages\": [\"My mouth is only getting drier.\", \"The thirst is catching up with me.\", \"I am losing water faster than I can replace it.\", \"I need fluids before this gets worse.\"],\n";
        json += "  \"TrendBloodFallingMessages\": [\"My blood is still dropping.\", \"I am not replacing what I am losing.\", \"The weakness is spreading through me.\", \"I need to stop this blood loss.\"],\n";
        json += "  \"TrendHealthFallingMessages\": [\"My condition is getting worse.\", \"I am slipping, slowly but surely.\", \"Whatever is happening, it is taking me down.\", \"I need to stabilize before I collapse.\"],\n";
        json += "  \"TrendTemperatureWorseningMessages\": [\"My temperature is moving the wrong way.\", \"The weather is getting inside me.\", \"My body cannot keep up with this temperature.\", \"I need to correct this before it becomes damage.\"],\n";
        json += "  \"TrendWetnessWorseningMessages\": [\"I am getting wetter by the minute.\", \"The damp is working its way through everything.\", \"Wet clothes are going to cost me heat.\", \"I need cover before this soaks through.\"],\n";
        json += "  \"LongSicknessMessages\": [\"I have been sick for too long.\", \"The fever is not breaking.\", \"This illness is wearing me down.\", \"I need proper treatment before this settles in.\"],\n";
        json += "  \"LongBleedingMessages\": [\"I have been bleeding too long.\", \"This wound is taking more from me than I thought.\", \"The bleeding needs to stop now.\", \"I cannot keep leaking blood like this.\"],\n";
        json += "  \"ProlongedStarvationMessages\": [\"I have been starving too long. My body is starting to give up.\", \"This hunger is not a warning anymore. It is damage.\", \"Every minute without food is taking something permanent from me.\", \"I cannot keep moving on nothing.\", \"The weakness is settling deep now.\", \"Food is no longer comfort. It is survival.\"],\n";
        json += "  \"ProlongedDehydrationMessages\": [\"I have been dry for too long. My thoughts are slowing down.\", \"My body is begging for water now.\", \"This thirst is turning into panic.\", \"My mouth feels like dust.\", \"I need water before my legs stop listening.\", \"Dehydration is killing me quietly.\"],\n";
        json += "  \"ProlongedColdMessages\": [\"The cold has been inside me too long.\", \"I am not just cold anymore. I am fading.\", \"My fingers feel distant, like they belong to someone else.\", \"If I do not get warm soon, I may not get warm at all.\", \"The shivering is taking all the strength I have left.\", \"This cold is grinding me down minute by minute.\"],\n";
        json += "  \"ProlongedHeatMessages\": [\"The heat has been pressing on me for too long.\", \"I can feel myself overheating from the inside.\", \"My head is thick from the heat.\", \"I need shade or water before this gets worse.\", \"The air feels too hot to breathe.\", \"This heat is starting to feel dangerous.\"],\n";
        json += "  \"ProlongedBleedingMessages\": [\"I have been bleeding too long.\", \"This blood loss is catching up with me.\", \"Every step leaves more of me behind.\", \"I need pressure on the wound now.\", \"The bleeding has gone from bad to critical.\", \"I cannot ignore this wound any longer.\"],\n";
        json += "  \"ProlongedSicknessMessages\": [\"I have been sick too long.\", \"The illness is settling in.\", \"This is not passing on its own.\", \"My body is losing the argument.\", \"The fever keeps coming back.\", \"I need medicine before this becomes permanent.\"]\n";
        json += "}";
        ST_WriteDefaultJsonStringFile(modularFolderPath + "/Player_State_History.json", json);
    }



    void ST_CreateDefault_Thought_Decision_Trace_json(string modularFolderPath)
    {
        string json = "{\n";
        json += "  \"EnableThoughtDecisionTrace\": 0,\n";
        json += "  \"TraceOnlyBlockedThoughts\": 1,\n";
        json += "  \"TraceToDebugLog\": 1,\n";
        json += "  \"TraceToMissionStorage\": 0,\n";
        json += "  \"DecisionTraceFolder\": \"$mission:storage_1/ZombiCideMods/SurvivorThoughts/Debug/DecisionTrace\"\n";
        json += "}";
        ST_WriteDefaultJsonStringFile(modularFolderPath + "/Thought_Decision_Trace.json", json);
    }

    void ST_CreateDefault_Messages_Advanced_Combined_json(string modularFolderPath)
    {
        string json = "{\n";
        json += "  \"EnableAdvancedCombinedMessages\": 1,\n";
        json += "  \"AdvancedCombinedChance\": 0.65,\n";
        json += "  \"EnableExpandedAdvancedCombos\": 1,\n";
        json += "  \"StarvingDehydratedMessages\": [\"No food, no water. My body has nothing left to trade.\", \"Hunger and thirst are hollowing me out together.\", \"I need calories and water before my legs stop listening.\", \"Everything in me is empty.\"],\n";
        json += "  \"ColdWetNightMessages\": [\"The cold, the wet, and the dark are working together.\", \"Night makes soaked clothes feel like ice.\", \"I need shelter before the dark freezes me still.\", \"This is how people disappear quietly.\"],\n";
        json += "  \"BleedingLowBloodMessages\": [\"I am running out faster than I can stop it.\", \"The blood loss is becoming critical.\", \"I need pressure on the wound now.\", \"There is not enough left in me to keep bleeding.\"],\n";
        json += "  \"GunshotBleedingMessages\": [\"The shot opened me up. I need cover and pressure now.\", \"I am hit and bleeding. Move first, bandage second.\", \"That bullet is still taking from me.\", \"Cover, bandage, breathe.\"],\n";
        json += "  \"BrokenLegInfectedMessages\": [\"I cannot run, and they are getting closer.\", \"A broken leg with infected nearby is a death trap.\", \"I need distance, but my leg will not give it.\", \"If they hear me, I am finished.\"],\n";
        json += "  \"LowSanityNightMessages\": [\"The dark is starting to sound like voices.\", \"Night gives shape to things I should not be hearing.\", \"I am not sure every thought in my head is mine.\", \"The silence keeps laughing.\"],\n";
        json += "  \"StarvingDehydratedColdMessages\": [";
        json += "\"No food, no water, and the cold is taking the rest.\", ";
        json += "\"My body has nothing left to burn, and the cold knows it.\", ";
        json += "\"Hunger, thirst, cold. All of it is pulling me down.\", ";
        json += "\"I need food, water, and warmth before I stop making sense.\", ";
        json += "\"Everything my body needs is missing at once.\", ";
        json += "\"The cold feels worse when there is nothing left inside me.\"],\n";
        json += "  \"HotDehydratedSickMessages\": [\"Heat, thirst, sickness. My body is turning against itself.\", \"I need water and shade before this fever cooks me.\", \"The heat is making the sickness worse.\", \"My stomach turns and the air feels too hot.\", \"This is how people collapse in the open.\", \"I cannot tell where the fever ends and the heat begins.\"],\n";
        json += "  \"BleedingLowBloodShockMessages\": [\"Too much blood is gone, and my head is going with it.\", \"I am bleeding, weak, and close to blacking out.\", \"The wound is draining more than blood now.\", \"My vision is narrowing. I need to stop this.\", \"I am losing blood faster than I can think.\", \"If I pass out like this, I may not wake up.\"],\n";
        json += "  \"GunshotBleedingLowBloodMessages\": [\"The shot opened me up, and I am running empty.\", \"I need cover and pressure on the wound now.\", \"Gunshot, blood loss, shock. One mistake and I am done.\", \"That round is still taking pieces of me.\", \"I can feel the blood leaving faster than my fear.\", \"Move first. Bleed later. If there is a later.\"],\n";
        json += "  \"BrokenLegBleedingInfectedMessages\": [\"I cannot run, I am bleeding, and they are coming.\", \"Bad leg, open wound, infected nearby. This is a trap.\", \"Every sound is closer when I cannot move right.\", \"I need to stop the bleeding before they reach me.\", \"Crawling and bleeding is not a plan.\", \"If they see me now, I am finished.\"],\n";
        json += "  \"NightInfectedRainMessages\": [\"Rain, infected, darkness. I cannot trust my ears.\", \"The rain hides them until they are too close.\", \"Night and rain make every infected sound like ten.\", \"I need shelter before the dark fills with teeth.\", \"The rain is covering too much movement.\", \"I can hear them, but I cannot place them.\"],\n";
        json += "  \"MilitaryNightStormMessages\": [\"A storm over a military site. Perfect cover for a bad decision.\", \"The weather is hiding every sniper lane.\", \"At night, this place belongs to whoever sees first.\", \"The storm makes the base feel alive.\", \"Good loot, bad weather, worse odds.\", \"Every flash of lightning could give me away.\"],\n";
        json += "  \"LoneWolfLowSanityNightMessages\": [\"Alone at night, my thoughts get too loud.\", \"There is nobody to tell me I am still myself.\", \"The dark answers back now.\", \"I have been alone too long to trust my own head.\", \"My shadow feels like company, and that scares me.\", \"I need a voice that is not mine.\"],\n";
        json += "  \"CompanionDeadNightMessages\": [\"Night makes their absence feel bigger.\", \"I keep expecting footsteps that are not coming.\", \"They should be here. They are not.\", \"The dark is quieter without them, and worse for it.\", \"I am listening for someone who will never answer.\", \"I did not know silence could feel this heavy.\"],\n";
        json += "  \"CorpseLowSanityNightMessages\": [\"The bodies look different at night.\", \"I should not stay near the dead while my head is like this.\", \"Their faces keep changing in the dark.\", \"The dead are quiet, but my mind is not.\", \"I know they cannot move. I still keep watching.\", \"Night makes the corpses feel less finished.\"],\n";
        json += "  \"ShelterNightInfectedMessages\": [\"Walls help, but they know I am in here.\", \"I can hear them outside the shelter.\", \"This place is shelter until they find the door.\", \"I need exits, not comfort.\", \"The building feels smaller with infected nearby.\", \"If they get inside, I have nowhere to run.\"]\n";
        json += "}";
        ST_WriteDefaultJsonStringFile(modularFolderPath + "/Messages_Advanced_Combined.json", json);
    }



    void ST_CreateDefault_Recovery_Messages_json(string modularFolderPath)
    {
        string json = "{\n";
        json += "  \"EnableRecoveryMessages\": 1,\n";
        json += "  \"RecoveryThoughtCooldownSeconds\": 180.0,\n";
        json += "  \"RecoveryThoughtChance\": 0.40,\n";
        json += "  \"BleedingRecoveryMessages\": [\"The bleeding stopped. I can think again.\", \"Pressure worked. I am still here.\", \"The blood has stopped running for now.\", \"One problem closed. Many left.\"],\n";
        json += "  \"HealthStableRecoveryMessages\": [\"My condition has stopped getting worse.\", \"I am not better, but I am not falling apart as fast.\", \"I can feel myself stabilizing.\", \"For now, I am holding together.\"],\n";
        json += "  \"FoodRecoveryMessages\": [\"The food is starting to help.\", \"My body has something to burn again.\", \"That might keep me moving.\", \"The hollow feeling is easing.\"],\n";
        json += "  \"WaterRecoveryMessages\": [\"The water is starting to settle in.\", \"My mouth does not feel as dry now.\", \"That drink bought me time.\", \"I can think clearer with water in me.\"],\n";
        json += "  \"DawnSurvivalMessages\": [\"Daylight. I made it.\", \"The sun came back, and so did I.\", \"Another night survived.\", \"Morning does not mean safe, but it means I lasted.\"],\n";
        json += "  \"ShockRecoveryMessages\": [\"My head is clearing. I am still here.\", \"The ringing is fading.\", \"I can think again. Not well, but enough.\", \"My hands are steadier now.\", \"The blackout passed me by this time.\", \"Breathe. Focus. Check wounds.\"],\n";
        json += "  \"BloodStabilizingMessages\": [\"The blood loss is not pulling as hard now.\", \"I might have stopped the worst of it.\", \"My pulse is still weak, but steadier.\", \"I am not recovering fast, but I am not falling as quickly.\", \"The world is less grey than it was.\", \"I need time, food, and quiet.\"],\n";
        json += "  \"AlmostDiedRecoveryMessages\": [\"That was too close.\", \"I was nearly gone.\", \"I do not get many chances like that.\", \"Still breathing. Somehow.\", \"I need to remember how close that came.\", \"I survived the minute. Now survive the next.\"],\n";
        json += "  \"SafeShelterRecoveryMessages\": [\"Shelter. Not safety, but close enough for now.\", \"The walls give me a moment to think.\", \"I can breathe in here for a second.\", \"This place buys time.\", \"Cover first. Then wounds. Then plans.\", \"Four walls are better than open ground.\"],\n";
        json += "  \"PostCombatBreathMessages\": [\"The fight is over, but my hands have not noticed.\", \"I need to listen before moving again.\", \"Count rounds. Count wounds. Count exits.\", \"The danger passed, maybe. Do not trust that.\", \"My heart is still running.\", \"I need to calm down before I make a stupid choice.\"]\n";
        json += "}";
        ST_WriteDefaultJsonStringFile(modularFolderPath + "/Recovery_Messages.json", json);
    }



    void ST_CreateDefault_NearMiss_Combat_json(string modularFolderPath)
    {
        string json = "{\n";
        json += "  \"EnableNearMissCombatMessages\": 1,\n";
        json += "  \"NearMissCombatCooldownSeconds\": 45.0,\n";
        json += "  \"NearMissCombatChance\": 0.35,\n";
        json += "  \"NearMissBulletMessages\": [\"That snapped past my head.\", \"Too close. Move now.\", \"Someone has the range.\", \"That shot was not random.\"],\n";
        json += "  \"NearMissExplosionMessages\": [\"The blast was too close.\", \"Fragments found everything except me.\", \"Move before the next one lands.\", \"That explosion was a warning I survived.\"],\n";
        json += "  \"NearMissCombatGeneralMessages\": [\"That was too close.\", \"I nearly lost it there.\", \"Do not freeze now.\", \"Someone almost had me.\"]\n";
        json += "}";
        ST_WriteDefaultJsonStringFile(modularFolderPath + "/NearMiss_Combat.json", json);
    }

    void ST_CreateDefault_Disease_Specific_json(string modularFolderPath)
    {
        string json = "{\n";
        json += "  \"EnableDiseaseSpecificMessages\": 1,\n";
        json += "  \"DiseaseWoundInfectionMessages\": [\"The wound feels hot. That is not good.\", \"The infection is in the wound now.\", \"I need disinfectant or antibiotics.\", \"This cut is turning against me.\"],\n";
        json += "  \"DiseaseCholeraMessages\": [\"My stomach is turning against me.\", \"Water did this to me.\", \"I need clean fluids and medicine.\", \"This sickness is draining me from inside.\"],\n";
        json += "  \"DiseaseInfluenzaMessages\": [\"The fever is climbing.\", \"Every breath feels heavier.\", \"My bones ache like they are full of ice.\", \"I need warmth, rest, and medicine.\"],\n";
        json += "  \"DiseaseKuruMessages\": [\"The laugh comes before I can stop it.\", \"Something is wrong in my head.\", \"My own mouth is betraying me.\", \"The giggle does not feel like mine.\"],\n";
        json += "  \"DiseaseChemicalMessages\": [\"My mouth tastes like metal.\", \"The air burned something into me.\", \"My skin feels wrong.\", \"I need treatment before this poison settles.\"],\n";
        json += "  \"DiseaseUnknownMessages\": [\"Something is wrong with me.\", \"My body is warning me, but I cannot name it.\", \"This sickness does not feel normal.\", \"I need medicine before I know what for.\"],\n";
        json += "  \"DiseaseGasExposureMessages\": [\"The air is poison here.\", \"My lungs know this place is wrong.\", \"I need filters, distance, or both.\", \"This gas is getting through something.\", \"Every breath feels expensive.\", \"I should not be breathing this.\"],\n";
        json += "  \"DiseaseFeverMessages\": [\"The fever is burning through me.\", \"My skin feels wrong.\", \"Hot and cold keep trading places.\", \"The sickness is making time blur.\", \"I need medicine before the fever wins.\", \"My body cannot decide if it is freezing or burning.\"],\n";
        json += "  \"DiseaseFoodPoisoningMessages\": [\"My stomach is punishing me.\", \"Whatever I ate was a mistake.\", \"I need water, medicine, and somewhere quiet.\", \"My gut is turning itself inside out.\", \"This is not normal hunger.\", \"I should have checked the food.\"]\n";
        json += "}";
        ST_WriteDefaultJsonStringFile(modularFolderPath + "/Disease_Specific.json", json);
    }



    void ST_CreateDefault_Admin_Analytics_json(string modularFolderPath)
    {
        string json = "{\n";
        json += "  \"EnableAdminAnalytics\": 1,\n";
        json += "  \"AnalyticsSaveIntervalSeconds\": 300.0,\n";
        json += "  \"AnalyticsFolder\": \"$mission:storage_1/ZombiCideMods/SurvivorThoughts/Analytics\",\n";
        json += "  \"EnableAnalyticsJsonLines\": 1,\n";
        json += "  \"AnalyticsJsonLineFile\": \"$mission:storage_1/ZombiCideMods/SurvivorThoughts/Analytics/SurvivorThoughts_Analytics.jsonl\",\n";
        json += "  \"TrackBlockedByPriority\": 1,\n";
        json += "  \"TrackBlockedByDuplicate\": 1,\n";
        json += "  \"TrackThoughtTypes\": 1,\n";
        json += "  \"TrackRecoveryEvents\": 1,\n";
        json += "  \"TrackSanityEvents\": 1,\n";
        json += "  \"TrackSocialEvents\": 1,\n";
        json += "  \"TrackStateHistoryEvents\": 1\n";
        json += "}";
        ST_WriteDefaultJsonStringFile(modularFolderPath + "/Admin_Analytics.json", json);
    }



    void ST_CreateDefault_Player_Journals_json(string modularFolderPath)
    {
        string json = "{\n";
        json += "  \"EnablePlayerJournals\": 1,\n";
        json += "  \"PlayerJournalFolder\": \"$mission:storage_1/ZombiCideMods/SurvivorThoughts/Journals\",\n";
        json += "  \"JournalOnlyMajorEvents\": 1,\n";
        json += "  \"JournalIncludePlayerStats\": 1,\n";
        json += "  \"JournalWriteAllRecoveryEvents\": 1,\n";
        json += "  \"JournalWriteSanityEvents\": 1,\n";
        json += "  \"JournalWriteSocialEvents\": 1,\n";
        json += "  \"JournalWriteNearDeathEvents\": 1\n";
        json += "}";
        ST_WriteDefaultJsonStringFile(modularFolderPath + "/Player_Journals.json", json);
    }



    void ST_CreateDefault_Map_Environment_Packs_json(string modularFolderPath)
    {
        string json = "{\n";
        json += "  \"EnableMapEnvironmentPacks\": 1,\n";
        json += "  \"ActiveMapEnvironmentPack\": \"Generic\",\n";
        json += "  \"MapEnvironmentThoughtChance\": 0.20,\n";
        json += "  \"MapEnvironmentThoughtCooldownSeconds\": 600.0,\n";
        json += "  \"MapChernarusMessages\": [\"Chernarus always feels like it is watching from the treeline.\", \"Every town here has learned to stay quiet.\", \"The coast gives nothing for free.\", \"The hills remember every gunshot.\"],\n";
        json += "  \"MapLivoniaMessages\": [\"Livonia's forests make every sound feel closer.\", \"The green hides more than it shows.\", \"Every clearing feels like a question.\", \"The trees here make good cover for everyone.\"],\n";
        json += "  \"MapNamalskMessages\": [\"The cold here is not weather. It is a predator.\", \"Namalsk does not forgive mistakes.\", \"This island wants heat, blood, or both.\", \"Every exposed minute feels borrowed.\"],\n";
        json += "  \"MapSakhalMessages\": [\"Sakhal feels like it is trying to freeze me in place.\", \"The island cold gets under everything.\", \"The sea air makes the silence sharper.\", \"Warmth matters more here than pride.\"],\n";
        json += "  \"MapGenericMessages\": [\"This place has survived worse than me.\", \"The land keeps its own secrets.\", \"Every road leads to somebody's mistake.\", \"I should learn the shape of this place before it learns mine.\"]\n";
        json += "}";
        ST_WriteDefaultJsonStringFile(modularFolderPath + "/Map_Environment_Packs.json", json);
    }


    void ST_HandleJournalSetupRPC(PlayerBase player, string charName, string charType, string headType, string origin, string occupation, string trait, string fear, string goal, string skill, string weakness, string moralCode)
    {
        if (!player)
            return;

        ST_SurvivorThoughtsConfig config = GetConfig();

        if (!config || config.EnableSurvivorJournalItem != 1)
            return;

        string finalName = charName;
        if (finalName == "")
            finalName = ST_GetFallbackJournalName(player, config);

        string finalCharType = ST_ValidatePoolValue(charType, config.JournalCharacterTypeOptions);
        string finalHeadType = ST_ValidatePoolValue(headType, config.JournalHeadTypeOptions);
        string finalOrigin = ST_ValidatePoolValue(origin, config.JournalOriginOptions);
        string finalOccupation = ST_ValidatePoolValue(occupation, config.JournalOccupationOptions);
        string finalTrait = ST_ValidatePoolValue(trait, config.JournalTraitOptions);
        string finalFear = ST_ValidatePoolValue(fear, config.JournalFearOptions);
        string finalGoal = ST_ValidatePoolValue(goal, config.JournalGoalOptions);
        string finalSkill = ST_ValidatePoolValue(skill, config.JournalSkillOptions);
        string finalWeakness = ST_ValidatePoolValue(weakness, config.JournalWeaknessOptions);
        string finalMoralCode = ST_ValidatePoolValue(moralCode, config.JournalMoralCodeOptions);

        string backstory = ST_BuildJournalBackstory(finalName, finalCharType, finalHeadType, finalOrigin, finalOccupation, finalTrait, finalFear, finalGoal, finalSkill, finalWeakness, finalMoralCode, config);
        player.ST_SetJournalIdentity(finalName, finalCharType, finalHeadType, finalOrigin, finalOccupation, finalTrait, finalFear, finalGoal, finalSkill, finalWeakness, finalMoralCode, backstory);
        SavePersistentDataForPlayer(player);
        ST_GiveJournalToPlayer(player, config);
        ST_SurvivorStorySystem.Get().OnJournalSetup(player, finalName, finalCharType, finalHeadType, finalOrigin, finalOccupation, finalTrait, finalFear, finalGoal, finalSkill, finalWeakness, finalMoralCode, backstory);
        SendThoughtWithPriority(player, "I wrote down who I was. Maybe that matters.", "JOURNAL_SYSTEM");

        DebugLog("Journal setup completed for player: " + ST_GetPlayerSteamId(player));
    }

    string ST_GetFallbackJournalName(PlayerBase player, ST_SurvivorThoughtsConfig config)
    {
        if (config && config.ShowRealPlayerNameInJournal == 1 && player && player.GetIdentity())
            return player.GetIdentity().GetName();

        return "Unknown Survivor";
    }

    string ST_ValidatePoolValue(string value, array<string> pool)
    {
        if (value != "")
            return value;

        if (pool && pool.Count() > 0)
            return pool.GetRandomElement();

        return "Unknown";
    }

    string ST_BuildJournalBackstory(string charName, string charType, string headType, string origin, string occupation, string trait, string fear, string goal, string skill, string weakness, string moralCode, ST_SurvivorThoughtsConfig config)
    {
        string templateText = "{name} is a {characterType} survivor with {headType}, from {origin}. Before the outbreak, they worked as a {occupation}. They were {trait}, skilled at {skill}, but the outbreak left them afraid of {fear}. Their weakness is that they {weakness}. Their line is simple: {moral}. Now they are trying to {goal}.";

        if (config && config.JournalBackstoryTemplates && config.JournalBackstoryTemplates.Count() > 0)
            templateText = config.JournalBackstoryTemplates.GetRandomElement();

        templateText.Replace("{name}", charName);
        templateText.Replace("{characterType}", charType);
        templateText.Replace("{headType}", headType);
        templateText.Replace("{origin}", origin);
        templateText.Replace("{occupation}", occupation);
        templateText.Replace("{trait}", trait);
        templateText.Replace("{fear}", fear);
        templateText.Replace("{goal}", goal);
        templateText.Replace("{skill}", skill);
        templateText.Replace("{weakness}", weakness);
        templateText.Replace("{moral}", moralCode);

        return templateText;
    }

    void ST_GiveJournalToPlayer(PlayerBase player, ST_SurvivorThoughtsConfig config)
    {
        if (!player || !config || config.EnableSurvivorJournalItem != 1)
            return;

        if (config.GiveJournalOnFreshSpawn != 1 && config.AutoEquipJournalOnFreshSpawn != 1 && config.AutoEquipJournalOnLoginIfMissing != 1)
            return;

        SurvivorJournal journal = player.ST_EnsureSurvivorJournalAttachment(config);

        if (journal)
        {
            string ownerName = player.ST_GetJournalCharacterName();

            if (ownerName == "" && player.GetIdentity())
                ownerName = player.GetIdentity().GetName();

            journal.ST_SetJournalOwner(ST_GetPlayerSteamId(player), ownerName);
            player.ST_SetJournalGiven(true);
            DebugLog("Ensured locked Survivor Journal attachment for player: " + ST_GetPlayerSteamId(player));
        }
    }

    void ST_ReadSurvivorJournal(PlayerBase reader, SurvivorJournal journal)
    {
        if (!reader || !journal)
            return;

        ST_SurvivorThoughtsConfig config = GetConfig();
        if (!config || config.EnableSurvivorJournalItem != 1)
            return;

        if (ST_SurvivorStorySystem.Get().ST_ReadSurvivorJournal(reader, journal))
            return;

        string ownerId = journal.ST_GetJournalOwnerId();

        if (ownerId == "")
            ownerId = ST_GetPlayerSteamId(reader);

        if (config.AllowReadingOtherPlayersJournals != 1 && ownerId != ST_GetPlayerSteamId(reader))
            return;

        ST_PlayerPersistentStateRecord record = NULL;

        if (m_PersistentStateStore)
            record = m_PersistentStateStore.GetRecord(ownerId);

        if (!record)
        {
            SendThoughtWithPriority(reader, "The journal is mostly blank.", "JOURNAL_SYSTEM");
            return;
        }

        string name = record.JournalCharacterName;
        if (name == "")
            name = "Unknown Survivor";

        SendThoughtWithPriority(reader, "Journal of " + name + ": " + record.JournalBackstory, "JOURNAL_SYSTEM");

        if (record.JournalSkill != "" || record.JournalWeakness != "" || record.JournalMoralCode != "")
        {
            string detailLine = "Journal details:";
            if (record.JournalSkill != "")
                detailLine += " skill: " + record.JournalSkill + ".";
            if (record.JournalWeakness != "")
                detailLine += " weakness: " + record.JournalWeakness + ".";
            if (record.JournalMoralCode != "")
                detailLine += " line: " + record.JournalMoralCode + ".";
            SendThoughtWithPriority(reader, detailLine, "JOURNAL_SYSTEM");
        }

        if (record.MajorJournalEvents && record.MajorJournalEvents.Count() > 0)
        {
            int startIndex = record.MajorJournalEvents.Count() - 3;
            if (startIndex < 0)
                startIndex = 0;

            for (int i = startIndex; i < record.MajorJournalEvents.Count(); i++)
            {
                SendThoughtWithPriority(reader, "Journal entry: " + record.MajorJournalEvents.Get(i), "JOURNAL_SYSTEM");
            }
        }
    }

    void ST_AddMajorJournalEvent(PlayerBase player, string eventText)
    {
        if (!player || eventText == "")
            return;

        ST_SurvivorThoughtsConfig config = GetConfig();

        if (!config || config.EnableSurvivorJournalItem != 1)
            return;

        string steamId = ST_GetPlayerSteamId(player);

        if (steamId == "")
            return;

        if (!m_PersistentStateStore)
            LoadPersistentStateStore();

        ST_PlayerPersistentStateRecord record = m_PersistentStateStore.GetOrCreateRecord(steamId);

        if (!record.MajorJournalEvents)
            record.MajorJournalEvents = new array<string>;

        record.MajorJournalEvents.Insert(eventText);

        while (record.MajorJournalEvents.Count() > config.MaxMajorJournalEventsStored)
        {
            record.MajorJournalEvents.Remove(0);
        }

        record.JournalLastUpdatedTime = 0.0;
        SavePersistentStateStore();
        ST_SurvivorStorySystem.Get().AddMajorEvent(player, eventText);
    }

    void ST_CreateDefault_Journal_Backstories_json(string modularFolderPath)
    {
        string json = "{\n";
        json += "  \"EnableSurvivorJournalItem\": 1,\n";
        json += "  \"GiveJournalOnFreshSpawn\": 1,\n";
        json += "  \"DropJournalOnDeath\": 1,\n";
        json += "  \"AllowReadingOtherPlayersJournals\": 1,\n";
        json += "  \"RequireJournalSetupMenu\": 0,\n";
        json += "  \"ShowJournalSetupMenuOnlyOnFreshCharacter\": 0,\n";
        json += "  \"AllowJournalSetupSkip\": 0,\n";
        json += "  \"AllowJournalSetupRandomize\": 0,\n";
        json += "  \"EnableJournalSetupSpawnProtection\": 0,\n";
        json += "  \"JournalSetupBlockDamageUntilComplete\": 0,\n";
        json += "  \"JournalSetupSuppressThoughtsUntilComplete\": 0,\n";
        json += "  \"JournalSetupProtectionDebug\": 0,\n";
        json += "  \"PlayerBackstoryDataFile\": \"$mission:storage_1/ZombiCideMods/SurvivorThoughts/Data/PlayerBackstories.json\",\n";
        json += "  \"MaxMajorJournalEventsStored\": 25,\n";
        json += "  \"JournalBackstoryMinMajorEvents\": 0,\n";
        json += "  \"ShowRealPlayerNameInJournal\": 0,\n";
        json += "  \"PriorityJournalSystem\": 62,\n";
        json += "  \"EnableJournalSystemIntegration\": 1,\n";
        json += "  \"JournalRecordAllThoughtSystems\": 1,\n";
        json += "  \"JournalRecordAmbientSystems\": 0,\n";
        json += "  \"JournalRecordBlockedDecisionEvents\": 0,\n";
        json += "  \"JournalMajorEventMinPriority\": 55,\n";
        json += "  \"JournalMajorEventPrefixWithSystem\": 1,\n";
        json += "  \"JournalMajorEventIncludeStats\": 0,\n";
        json += "  \"JournalRecordDeathEntries\": 1,\n";
        json += "  \"JournalRecordSetupChoices\": 1,\n";
        json += "  \"JournalRecordSystemLinkDebug\": 0,\n";
        json += "  \"JournalCharacterTypeOptions\": [\"Male\", \"Female\"],\n";
        json += "  \"JournalHeadTypeOptions\": [\"Default head\", \"Head 1\", \"Head 2\", \"Head 3\", \"Head 4\", \"Head 5\", \"Head 6\", \"Head 7\", \"Head 8\"],\n";
        json += "  \"JournalOriginOptions\": [\"Chernarus\", \"Livonia\", \"Sakhal\", \"Namalsk\", \"Unknown coast\", \"Inland settlement\"],\n";
        json += "  \"JournalOccupationOptions\": [\"rail worker\", \"paramedic\", \"hunter\", \"mechanic\", \"teacher\", \"dock worker\", \"soldier\", \"farmer\"],\n";
        json += "  \"JournalTraitOptions\": [\"practical\", \"quiet\", \"stubborn\", \"cautious\", \"angry\", \"calm under pressure\", \"resourceful\", \"distrustful\"],\n";
        json += "  \"JournalFearOptions\": [\"dying alone\", \"being left behind\", \"the dark\", \"infected crowds\", \"starvation\", \"silence\"],\n";
        json += "  \"JournalGoalOptions\": [\"find a safe place\", \"reach the next town\", \"keep moving north\", \"find someone worth trusting\", \"survive one more day\", \"learn what happened\"],\n";
        json += "  \"JournalSkillOptions\": [\"first aid\", \"repairing engines\", \"hunting\", \"navigation\", \"farming\", \"keeping quiet\", \"handling weapons\", \"scavenging\"],\n";
        json += "  \"JournalWeaknessOptions\": [\"trusts too easily\", \"panics in the dark\", \"hates being alone\", \"takes unnecessary risks\", \"cannot ignore people in trouble\", \"holds grudges\", \"struggles with hunger\", \"freezes under pressure\"],\n";
        json += "  \"JournalMoralCodeOptions\": [\"will not abandon a friend\", \"will not eat human meat\", \"avoids killing unless forced\", \"protects the weak when possible\", \"survival comes before mercy\", \"trust must be earned\", \"never wastes supplies\", \"keeps moving, no matter what\"],\n";
        json += "  \"JournalBackstoryTemplates\": [";
        json += "\"{name} came from {origin}, once working as a {occupation}. They were {trait}, skilled at {skill}, but the outbreak left them afraid of {fear}. Their weakness is that they {weakness}. Their line is simple: {moral}. Now they are trying to {goal}.\", ";
        json += "\"Before everything collapsed, {name} was a {occupation}. People called them {trait}. They survived by {skill}, but {weakness}. They left {origin} after the first panic and now only writes about one thing: {goal}. They still believe they {moral}.\", ";
        json += "\"{name} does not write much about life before. The few clear notes mention {origin}, {occupation}, {skill}, and a fear of {fear}. The rest is survival. One sentence is underlined twice: {moral}.\"";
        json += "]\n";
        json += "}";
        ST_WriteDefaultJsonStringFile(modularFolderPath + "/Journal_Backstories.json", json);
    }


}