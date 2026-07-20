
class ST_SurvivorStoryConfig
{
    int ConfigVersion;
    int EnableSurvivorStorySystem;
    int EnableReadablePhysicalJournals;
    int EnableJournalSections;
    int EnableJournalDeathPages;
    int EnableTraitFearThoughtStyle;
    int EnableSpecificPlayerMemory;
    int HashStoredPlayerIds;
    int EnableConditionProfile;
    int EnableSanityHallucinationTextLayer;
    int EnableMapTonePacks;
    int EnableThoughtIntensityTiers;
    int EnableStoryAnalyticsDailyExport;
    int EnablePresetSystem;

    float StoryLayerCheckIntervalSeconds;
    float ConditionThoughtCooldownSeconds;
    float HallucinationThoughtCooldownSeconds;
    float MapToneThoughtCooldownSeconds;
    float SpecificPlayerMemoryCooldownSeconds;

    string StoryRootFolder;
    string JournalRecordsFolder;
    string StoryAnalyticsFolder;
    string ActiveStoryPreset;

    int MaxSectionEntries;
    int MaxKnownPeopleRemembered;
    int MaxDailyAnalyticsEvents;

    ref array<string> ConditionStableMessages;
    ref array<string> ConditionWornDownMessages;
    ref array<string> ConditionStressedMessages;
    ref array<string> ConditionDesperateMessages;
    ref array<string> ConditionNearCollapseMessages;
    ref array<string> ConditionBrokenMessages;

    ref array<string> TraitCautiousMessages;
    ref array<string> TraitAngryMessages;
    ref array<string> TraitQuietMessages;
    ref array<string> TraitPracticalMessages;
    ref array<string> TraitResourcefulMessages;
    ref array<string> TraitStubbornMessages;

    ref array<string> FearDarknessMessages;
    ref array<string> FearInfectedCrowdsMessages;
    ref array<string> FearStarvationMessages;
    ref array<string> FearBeingAloneMessages;
    ref array<string> FearSilenceMessages;

    ref array<string> HallucinationLowSanityMessages;
    ref array<string> HallucinationCannibalismMessages;
    ref array<string> HallucinationNightMessages;
    ref array<string> HallucinationCorpseMessages;

    ref array<string> IntensitySubtlePrefixes;
    ref array<string> IntensityConcernedPrefixes;
    ref array<string> IntensityDesperatePrefixes;
    ref array<string> IntensityCriticalPrefixes;

    ref array<string> MapToneChernarusMessages;
    ref array<string> MapToneLivoniaMessages;
    ref array<string> MapToneNamalskMessages;
    ref array<string> MapToneSakhalMessages;
    ref array<string> MapToneDeerIsleMessages;
    ref array<string> MapToneGenericMessages;

    void SetDefaults()
    {
        ConfigVersion = 300;
        EnableSurvivorStorySystem = 1;
        EnableReadablePhysicalJournals = 1;
        EnableJournalSections = 1;
        EnableJournalDeathPages = 1;
        EnableTraitFearThoughtStyle = 1;
        EnableSpecificPlayerMemory = 1;
        HashStoredPlayerIds = 1;
        EnableConditionProfile = 1;
        EnableSanityHallucinationTextLayer = 1;
        EnableMapTonePacks = 1;
        EnableThoughtIntensityTiers = 1;
        EnableStoryAnalyticsDailyExport = 1;
        EnablePresetSystem = 1;

        StoryLayerCheckIntervalSeconds = 60.0;
        ConditionThoughtCooldownSeconds = 420.0;
        HallucinationThoughtCooldownSeconds = 600.0;
        MapToneThoughtCooldownSeconds = 900.0;
        SpecificPlayerMemoryCooldownSeconds = 300.0;

        StoryRootFolder = "$mission:storage_1/ZombiCideMods/SurvivorThoughts/Story";
        JournalRecordsFolder = "$mission:storage_1/ZombiCideMods/SurvivorThoughts/Data/Journals";
        StoryAnalyticsFolder = "$mission:storage_1/ZombiCideMods/SurvivorThoughts/Analytics/Story";
        ActiveStoryPreset = "VanillaPlus_Light";

        MaxSectionEntries = 60;
        MaxKnownPeopleRemembered = 40;
        MaxDailyAnalyticsEvents = 5000;

        ConditionStableMessages = new array<string>;
        ConditionStableMessages.Insert("For once, my body is not arguing with me.");
        ConditionStableMessages.Insert("I can think clearly enough to make the next choice.");
        ConditionStableMessages.Insert("Steady hands. Steady breath. Keep it that way.");
        ConditionStableMessages.Insert("Nothing is fixed, but I am not falling apart yet.");
        ConditionStableMessages.Insert("A quiet minute is still worth something.");

        ConditionWornDownMessages = new array<string>;
        ConditionWornDownMessages.Insert("The miles are starting to sit in my bones.");
        ConditionWornDownMessages.Insert("Every small problem feels heavier than it should.");
        ConditionWornDownMessages.Insert("I need food, water, warmth, or luck. Any of them would do.");
        ConditionWornDownMessages.Insert("I can keep moving, but I can feel the cost.");
        ConditionWornDownMessages.Insert("This place is sanding me down a little at a time.");

        ConditionStressedMessages = new array<string>;
        ConditionStressedMessages.Insert("Too many things are wrong at once.");
        ConditionStressedMessages.Insert("My thoughts are moving faster than my hands.");
        ConditionStressedMessages.Insert("I need to stop reacting and start choosing.");
        ConditionStressedMessages.Insert("One mistake now will become three more.");
        ConditionStressedMessages.Insert("I can feel panic waiting for an opening.");

        ConditionDesperateMessages = new array<string>;
        ConditionDesperateMessages.Insert("There is no room left for pride.");
        ConditionDesperateMessages.Insert("I need shelter, supplies, or a miracle.");
        ConditionDesperateMessages.Insert("Every sound feels like it is meant for me.");
        ConditionDesperateMessages.Insert("Survival has become a list of things I do not have.");
        ConditionDesperateMessages.Insert("I am making choices I would have judged yesterday.");

        ConditionNearCollapseMessages = new array<string>;
        ConditionNearCollapseMessages.Insert("My body is starting to make decisions without me.");
        ConditionNearCollapseMessages.Insert("The world keeps narrowing to the next breath.");
        ConditionNearCollapseMessages.Insert("If I stop now, I might not start again.");
        ConditionNearCollapseMessages.Insert("I can feel the edge under every step.");
        ConditionNearCollapseMessages.Insert("There is not enough left in me for another mistake.");

        ConditionBrokenMessages = new array<string>;
        ConditionBrokenMessages.Insert("I am not surviving now. I am delaying the end.");
        ConditionBrokenMessages.Insert("Everything hurts, and even fear feels tired.");
        ConditionBrokenMessages.Insert("This might be the last page I ever write.");
        ConditionBrokenMessages.Insert("The body gives warnings until it has none left.");
        ConditionBrokenMessages.Insert("I need help. I hate that I need help.");

        TraitCautiousMessages = new array<string>;
        TraitCautiousMessages.Insert("Check the treeline before the road.");
        TraitCautiousMessages.Insert("The obvious path is where people aim first.");
        TraitCautiousMessages.Insert("Slow is alive. Fast is loud.");
        TraitCautiousMessages.Insert("Every doorway deserves suspicion.");
        TraitCautiousMessages.Insert("Leave before the place starts feeling safe.");

        TraitAngryMessages = new array<string>;
        TraitAngryMessages.Insert("Let the world push. I am still here.");
        TraitAngryMessages.Insert("Fear can wait its turn.");
        TraitAngryMessages.Insert("I am tired of being hunted by hunger and noise.");
        TraitAngryMessages.Insert("Pain is another debt I will collect later.");
        TraitAngryMessages.Insert("If something wants me dead, it can stand in line.");

        TraitQuietMessages = new array<string>;
        TraitQuietMessages.Insert("Silence is the only thing that has not lied to me.");
        TraitQuietMessages.Insert("Do not speak unless the words can save you.");
        TraitQuietMessages.Insert("The world talks enough. I only need to listen.");
        TraitQuietMessages.Insert("A quiet survivor leaves fewer ghosts behind.");
        TraitQuietMessages.Insert("Stillness has kept me alive this long.");

        TraitPracticalMessages = new array<string>;
        TraitPracticalMessages.Insert("Need first. Want later.");
        TraitPracticalMessages.Insert("Count what matters: food, water, exits, rounds.");
        TraitPracticalMessages.Insert("A useful thing is worth more than a pretty one.");
        TraitPracticalMessages.Insert("Do the ugly job before it becomes impossible.");
        TraitPracticalMessages.Insert("Survival is just maintenance with consequences.");

        TraitResourcefulMessages = new array<string>;
        TraitResourcefulMessages.Insert("There is always something useful if I look twice.");
        TraitResourcefulMessages.Insert("Broken things still have parts.");
        TraitResourcefulMessages.Insert("Nothing is trash until I know what it can become.");
        TraitResourcefulMessages.Insert("Improvising is just planning with fewer choices.");
        TraitResourcefulMessages.Insert("The world is full of tools pretending to be junk.");

        TraitStubbornMessages = new array<string>;
        TraitStubbornMessages.Insert("Not here. Not yet.");
        TraitStubbornMessages.Insert("The road can take more from me, but not all of it.");
        TraitStubbornMessages.Insert("I have outlasted worse minutes than this one.");
        TraitStubbornMessages.Insert("Keep moving out of spite if nothing else.");
        TraitStubbornMessages.Insert("I refuse to become another quiet shape in the grass.");

        FearDarknessMessages = new array<string>;
        FearDarknessMessages.Insert("The dark makes every sound grow teeth.");
        FearDarknessMessages.Insert("Night hides the distance between me and panic.");
        FearDarknessMessages.Insert("I hate how the black spaces feel occupied.");
        FearDarknessMessages.Insert("The dark does not chase. It waits.");
        FearDarknessMessages.Insert("I need light before my head starts inventing shapes.");

        FearInfectedCrowdsMessages = new array<string>;
        FearInfectedCrowdsMessages.Insert("One infected is noise. A crowd is a sentence.");
        FearInfectedCrowdsMessages.Insert("If they start screaming together, I run.");
        FearInfectedCrowdsMessages.Insert("Crowds were dangerous before they were dead.");
        FearInfectedCrowdsMessages.Insert("Too many bodies moving one way. That is how people vanish.");
        FearInfectedCrowdsMessages.Insert("I can handle one. I cannot handle the sound of many.");

        FearStarvationMessages = new array<string>;
        FearStarvationMessages.Insert("Hunger makes honest people think like animals.");
        FearStarvationMessages.Insert("Empty is a sound inside the ribs.");
        FearStarvationMessages.Insert("I know what hunger can talk me into.");
        FearStarvationMessages.Insert("Food is not comfort anymore. It is permission to continue.");
        FearStarvationMessages.Insert("The thought of starving is worse than the ache itself.");

        FearBeingAloneMessages = new array<string>;
        FearBeingAloneMessages.Insert("No voices. No footsteps. Just me to blame.");
        FearBeingAloneMessages.Insert("Being alone makes the world feel already abandoned.");
        FearBeingAloneMessages.Insert("I keep listening for someone who is not coming.");
        FearBeingAloneMessages.Insert("Company is dangerous. Absence is worse.");
        FearBeingAloneMessages.Insert("The silence feels personal when nobody answers it.");

        FearSilenceMessages = new array<string>;
        FearSilenceMessages.Insert("Silence means something stopped making noise.");
        FearSilenceMessages.Insert("It is too quiet. Quiet has a reason.");
        FearSilenceMessages.Insert("When the world goes still, I start counting exits.");
        FearSilenceMessages.Insert("No birds. No wind. Nothing good starts like this.");
        FearSilenceMessages.Insert("The quiet feels like it is holding its breath.");

        HallucinationLowSanityMessages = new array<string>;
        HallucinationLowSanityMessages.Insert("Someone whispered my name. No one is here.");
        HallucinationLowSanityMessages.Insert("For a second, the trees looked like people watching the road.");
        HallucinationLowSanityMessages.Insert("I heard footsteps stop when I stopped.");
        HallucinationLowSanityMessages.Insert("The silence keeps repeating itself.");
        HallucinationLowSanityMessages.Insert("I should not trust every thought that uses my voice.");

        HallucinationCannibalismMessages = new array<string>;
        HallucinationCannibalismMessages.Insert("My teeth remember something I wish they did not.");
        HallucinationCannibalismMessages.Insert("The thought comes back hungry.");
        HallucinationCannibalismMessages.Insert("There are lines that do not grow back after crossing.");
        HallucinationCannibalismMessages.Insert("I can still taste the choice.");
        HallucinationCannibalismMessages.Insert("Some hunger is not in the stomach.");

        HallucinationNightMessages = new array<string>;
        HallucinationNightMessages.Insert("The dark moved in the corner of my eye.");
        HallucinationNightMessages.Insert("A shape became a person, then became nothing.");
        HallucinationNightMessages.Insert("Night makes a liar out of distance.");
        HallucinationNightMessages.Insert("I saw a light blink where there should be no light.");
        HallucinationNightMessages.Insert("The black between the trees feels crowded.");

        HallucinationCorpseMessages = new array<string>;
        HallucinationCorpseMessages.Insert("That corpse looked warmer a moment ago.");
        HallucinationCorpseMessages.Insert("Dead faces all start asking the same question.");
        HallucinationCorpseMessages.Insert("I thought I saw the hand move.");
        HallucinationCorpseMessages.Insert("The body is still, but my head is not convinced.");
        HallucinationCorpseMessages.Insert("Every corpse feels like a warning written badly.");

        IntensitySubtlePrefixes = new array<string>;
        IntensitySubtlePrefixes.Insert("");
        IntensitySubtlePrefixes.Insert("A small thought: ");
        IntensitySubtlePrefixes.Insert("Quietly, ");
        IntensitySubtlePrefixes.Insert("For now, ");

        IntensityConcernedPrefixes = new array<string>;
        IntensityConcernedPrefixes.Insert("");
        IntensityConcernedPrefixes.Insert("I should pay attention: ");
        IntensityConcernedPrefixes.Insert("This is getting worse: ");
        IntensityConcernedPrefixes.Insert("Do not ignore it: ");

        IntensityDesperatePrefixes = new array<string>;
        IntensityDesperatePrefixes.Insert("");
        IntensityDesperatePrefixes.Insert("No more pretending: ");
        IntensityDesperatePrefixes.Insert("This is bad: ");
        IntensityDesperatePrefixes.Insert("I need to act now: ");

        IntensityCriticalPrefixes = new array<string>;
        IntensityCriticalPrefixes.Insert("");
        IntensityCriticalPrefixes.Insert("Last chance: ");
        IntensityCriticalPrefixes.Insert("Everything is narrowing: ");
        IntensityCriticalPrefixes.Insert("Move or die: ");

        MapToneChernarusMessages = new array<string>;
        MapToneChernarusMessages.Insert("Chernarus watches from the treeline.");
        MapToneChernarusMessages.Insert("Every village here feels like it locked its doors too late.");
        MapToneChernarusMessages.Insert("The coast teaches hunger, then the hills test memory.");
        MapToneChernarusMessages.Insert("Old roads, old farms, old ghosts.");
        MapToneChernarusMessages.Insert("The rain here makes every town feel abandoned twice.");

        MapToneLivoniaMessages = new array<string>;
        MapToneLivoniaMessages.Insert("Livonia hides things under green leaves and military concrete.");
        MapToneLivoniaMessages.Insert("The forest gives cover to everyone, friend or otherwise.");
        MapToneLivoniaMessages.Insert("Every clearing feels watched.");
        MapToneLivoniaMessages.Insert("The south keeps secrets under its roots.");
        MapToneLivoniaMessages.Insert("The bunkers are not the only things buried here.");

        MapToneNamalskMessages = new array<string>;
        MapToneNamalskMessages.Insert("Namalsk does not feel cold. It feels hungry.");
        MapToneNamalskMessages.Insert("This island punishes slow thinking.");
        MapToneNamalskMessages.Insert("Warmth is currency here.");
        MapToneNamalskMessages.Insert("The wind sounds like a warning nobody survived to translate.");
        MapToneNamalskMessages.Insert("Every exposed minute feels borrowed.");

        MapToneSakhalMessages = new array<string>;
        MapToneSakhalMessages.Insert("Sakhal makes warmth feel like a memory.");
        MapToneSakhalMessages.Insert("The sea air cuts through everything.");
        MapToneSakhalMessages.Insert("Fishing villages, ice, and quiet mistakes.");
        MapToneSakhalMessages.Insert("The island keeps its dead cold.");
        MapToneSakhalMessages.Insert("Out here, shelter is more important than pride.");

        MapToneDeerIsleMessages = new array<string>;
        MapToneDeerIsleMessages.Insert("Deer Isle feels beautiful enough to be suspicious.");
        MapToneDeerIsleMessages.Insert("The coast smiles before it takes something.");
        MapToneDeerIsleMessages.Insert("Strange places make strange survivors.");
        MapToneDeerIsleMessages.Insert("The island has corners that do not feel finished.");
        MapToneDeerIsleMessages.Insert("Every landmark feels like it is hiding a story.");

        MapToneGenericMessages = new array<string>;
        MapToneGenericMessages.Insert("This place has survived worse than me.");
        MapToneGenericMessages.Insert("Every road leads to someone's last plan.");
        MapToneGenericMessages.Insert("The land keeps its own records.");
        MapToneGenericMessages.Insert("I should learn this place before it learns me.");
        MapToneGenericMessages.Insert("No map shows where a person starts breaking.");
    }
}

class ST_SurvivorStoryJournalFile
{
    string JournalId;
    string OwnerSteamId;
    string OwnerName;
    string CharacterName;
    string JournalCharacterType;
    string JournalHeadType;
    string Origin;
    string Occupation;
    string Trait;
    string Fear;
    string Goal;
    string Skill;
    string Weakness;
    string MoralCode;
    string Backstory;
    string CreatedTime;
    string LastUpdatedTime;
    int OwnerDead;

    ref array<string> FirstEntry;
    ref array<string> DailyNotes;
    ref array<string> WoundsAndIllnesses;
    ref array<string> PeopleMet;
    ref array<string> PlacesRemembered;
    ref array<string> SanityNotes;
    ref array<string> LastWords;
    ref array<string> DeathPage;

    void ST_SurvivorStoryJournalFile()
    {
        FirstEntry = new array<string>;
        DailyNotes = new array<string>;
        WoundsAndIllnesses = new array<string>;
        PeopleMet = new array<string>;
        PlacesRemembered = new array<string>;
        SanityNotes = new array<string>;
        LastWords = new array<string>;
        DeathPage = new array<string>;
    }
}

class ST_SurvivorStoryPlayerRuntime
{
    float LastStoryCheckTime;
    float LastConditionThoughtTime;
    float LastHallucinationThoughtTime;
    float LastMapToneThoughtTime;
    float LastSpecificPlayerMemoryTime;
    float LastTraitFearThoughtTime;
    string LastConditionProfile;
}

class ST_SurvivorStorySystem
{
    protected static ref ST_SurvivorStorySystem m_Instance;
    protected ref ST_SurvivorStoryConfig m_Config;
    protected ref map<string, ref ST_SurvivorStoryPlayerRuntime> m_Runtime;

    static ST_SurvivorStorySystem Get()
    {
        if (!m_Instance)
            m_Instance = new ST_SurvivorStorySystem();

        return m_Instance;
    }

    void ST_SurvivorStorySystem()
    {
        m_Runtime = new map<string, ref ST_SurvivorStoryPlayerRuntime>;
    }

    ST_SurvivorStoryConfig GetConfig()
    {
        if (!m_Config)
            LoadConfig();

        return m_Config;
    }

    void LoadConfig()
    {
        m_Config = new ST_SurvivorStoryConfig();
        m_Config.SetDefaults();

        string rootFolderPath = "$profile:ZombicideMods";
        string folderPath = rootFolderPath + "/SurvivorThoughts";
        string modularFolderPath = folderPath + "/Configs";

        if (!FileExist(rootFolderPath))
            MakeDirectory(rootFolderPath);

        if (!FileExist(folderPath))
            MakeDirectory(folderPath);

        if (!FileExist(modularFolderPath))
            MakeDirectory(modularFolderPath);

        string configPath = modularFolderPath + "/08_Survivor_Story_System.json";

        if (FileExist(configPath))
        {
            JsonFileLoader<ST_SurvivorStoryConfig>.JsonLoadFile(configPath, m_Config);
        }
        else
        {
            JsonFileLoader<ST_SurvivorStoryConfig>.JsonSaveFile(configPath, m_Config);
        }

        EnsureFolders();
    }

    void EnsureFolders()
    {
        ST_SurvivorStoryConfig config = GetConfig();

        if (!config)
            return;

        ST_EnsureFolder("$mission:storage_1");
        ST_EnsureFolder("$mission:storage_1/ZombiCideMods");
        ST_EnsureFolder("$mission:storage_1/ZombiCideMods/SurvivorThoughts");
        ST_EnsureFolder("$mission:storage_1/ZombiCideMods/SurvivorThoughts/Data");
        ST_EnsureFolder("$mission:storage_1/ZombiCideMods/SurvivorThoughts/Data/Journals");
        ST_EnsureFolder("$mission:storage_1/ZombiCideMods/SurvivorThoughts/Story");
        ST_EnsureFolder("$mission:storage_1/ZombiCideMods/SurvivorThoughts/Analytics");
        ST_EnsureFolder("$mission:storage_1/ZombiCideMods/SurvivorThoughts/Analytics/Story");
    }

    void ST_EnsureFolder(string path)
    {
        if (path != "" && !FileExist(path))
            MakeDirectory(path);
    }

    string ST_GetSteamId(PlayerBase player)
    {
        if (!player || !player.GetIdentity())
            return "";

        return player.GetIdentity().GetPlainId();
    }

    string ST_GetOwnerFolder(string steamId)
    {
        ST_SurvivorStoryConfig config = GetConfig();

        if (!config)
            return "";

        string folder = config.JournalRecordsFolder + "/" + steamId;

        if (!FileExist(folder))
            MakeDirectory(folder);

        return folder;
    }

    string ST_GetJournalId(PlayerBase player)
    {
        if (!player)
            return "";

        SurvivorJournal journal = player.ST_GetSurvivorJournal();

        if (journal)
        {
            string journalId = journal.ST_GetJournalId();

            if (journalId != "")
                return journalId;
        }

        string steamId = ST_GetSteamId(player);

        if (steamId == "")
            return "";

        return steamId + "_" + GetGame().GetTime().ToString();
    }

    string ST_GetJournalPath(PlayerBase player)
    {
        string steamId = ST_GetSteamId(player);
        string journalId = ST_GetJournalId(player);

        if (steamId == "" || journalId == "")
            return "";

        return ST_GetOwnerFolder(steamId) + "/" + journalId + ".json";
    }

    string ST_GetJournalPathFromItem(SurvivorJournal journal)
    {
        if (!journal)
            return "";

        string steamId = journal.ST_GetJournalOwnerId();
        string journalId = journal.ST_GetJournalId();

        if (steamId == "" || journalId == "")
            return "";

        return ST_GetOwnerFolder(steamId) + "/" + journalId + ".json";
    }

    ST_SurvivorStoryJournalFile ST_LoadOrCreateJournalForPlayer(PlayerBase player)
    {
        string path = ST_GetJournalPath(player);

        if (path == "")
            return NULL;

        ST_SurvivorStoryJournalFile data = new ST_SurvivorStoryJournalFile();

        if (FileExist(path))
            JsonFileLoader<ST_SurvivorStoryJournalFile>.JsonLoadFile(path, data);

        if (data.JournalId == "")
            data.JournalId = ST_GetJournalId(player);

        if (data.OwnerSteamId == "")
            data.OwnerSteamId = ST_GetSteamId(player);

        if (data.OwnerName == "" && player.GetIdentity())
            data.OwnerName = player.GetIdentity().GetName();

        if (data.CharacterName == "")
            data.CharacterName = player.ST_GetJournalCharacterName();

        if (data.Backstory == "")
            data.Backstory = player.ST_GetJournalBackstory();

        ST_SaveJournal(path, data);
        return data;
    }

    ST_SurvivorStoryJournalFile ST_LoadJournalFromItem(SurvivorJournal journal)
    {
        string path = ST_GetJournalPathFromItem(journal);

        if (path == "")
            return NULL;

        if (!FileExist(path))
            return NULL;

        ST_SurvivorStoryJournalFile data = new ST_SurvivorStoryJournalFile();
        JsonFileLoader<ST_SurvivorStoryJournalFile>.JsonLoadFile(path, data);
        return data;
    }

    void ST_SaveJournal(string path, ST_SurvivorStoryJournalFile data)
    {
        if (path == "" || !data)
            return;

        data.LastUpdatedTime = GetGame().GetTime().ToString();
        JsonFileLoader<ST_SurvivorStoryJournalFile>.JsonSaveFile(path, data);
    }

    void OnJournalSetup(PlayerBase player, string charName, string charType, string headType, string origin, string occupation, string trait, string fear, string goal, string skill, string weakness, string moralCode, string backstory)
    {
        ST_SurvivorStoryConfig config = GetConfig();

        if (!config || config.EnableSurvivorStorySystem != 1 || config.EnableJournalSections != 1)
            return;

        ST_SurvivorStoryJournalFile data = ST_LoadOrCreateJournalForPlayer(player);

        if (!data)
            return;

        data.CharacterName = charName;
        data.JournalCharacterType = charType;
        data.JournalHeadType = headType;
        data.Origin = origin;
        data.Occupation = occupation;
        data.Trait = trait;
        data.Fear = fear;
        data.Goal = goal;
        data.Skill = skill;
        data.Weakness = weakness;
        data.MoralCode = moralCode;
        data.Backstory = backstory;
        data.CreatedTime = GetGame().GetTime().ToString();

        ST_AddToSection(data.FirstEntry, "First entry: " + backstory, config.MaxSectionEntries);
        ST_AddToSection(data.DailyNotes, "I finished the first page. The world did not wait for me.", config.MaxSectionEntries);

        ST_SaveJournal(ST_GetJournalPath(player), data);
        ST_WriteStoryAnalytics("JournalSetup", "Created per-journal story file");
    }

    void AddMajorEvent(PlayerBase player, string eventText)
    {
        ST_SurvivorStoryConfig config = GetConfig();

        if (!config || config.EnableSurvivorStorySystem != 1 || config.EnableJournalSections != 1)
            return;

        ST_SurvivorStoryJournalFile data = ST_LoadOrCreateJournalForPlayer(player);

        if (!data)
            return;

        string section = ST_GetSectionForEvent(eventText);

        if (section == "Wounds")
            ST_AddToSection(data.WoundsAndIllnesses, eventText, config.MaxSectionEntries);
        else if (section == "People")
            ST_AddToSection(data.PeopleMet, eventText, config.MaxSectionEntries);
        else if (section == "Places")
            ST_AddToSection(data.PlacesRemembered, eventText, config.MaxSectionEntries);
        else if (section == "Sanity")
            ST_AddToSection(data.SanityNotes, eventText, config.MaxSectionEntries);
        else if (section == "Death")
        {
            data.OwnerDead = 1;
            ST_AddToSection(data.LastWords, eventText, config.MaxSectionEntries);
            ST_AddToSection(data.DeathPage, ST_BuildDeathPage(player, eventText), config.MaxSectionEntries);
        }
        else
            ST_AddToSection(data.DailyNotes, eventText, config.MaxSectionEntries);

        ST_SaveJournal(ST_GetJournalPath(player), data);
        ST_WriteStoryAnalytics("JournalEvent", section);
    }

    string ST_GetSectionForEvent(string eventText)
    {
        string e = eventText;

        if (ST_HasText(e, "Final entry") || ST_HasText(e, "died") || ST_HasText(e, "DEATH"))
            return "Death";

        if (ST_HasText(e, "BLEED") || ST_HasText(e, "DAMAGE") || ST_HasText(e, "SICK") || ST_HasText(e, "ILLNESS") || ST_HasText(e, "WOUND") || ST_HasText(e, "Blood") || ST_HasText(e, "Health"))
            return "Wounds";

        if (ST_HasText(e, "PLAYER") || ST_HasText(e, "SOCIAL") || ST_HasText(e, "TEAMMATE") || ST_HasText(e, "COMPANION"))
            return "People";

        if (ST_HasText(e, "LOCATION") || ST_HasText(e, "MAP") || ST_HasText(e, "WEATHER") || ST_HasText(e, "ZONE"))
            return "Places";

        if (ST_HasText(e, "SANITY") || ST_HasText(e, "KURU") || ST_HasText(e, "CANNIBAL"))
            return "Sanity";

        return "Daily";
    }

    bool ST_HasText(string source, string needle)
    {
        if (source == "" || needle == "")
            return false;

        string temp = source;
        temp.Replace(needle, "");

        return temp != source;
    }

    string ST_BuildDeathPage(PlayerBase player, string eventText)
    {
        string text = "Final page: ";

        if (player)
        {
            text += "Health=" + player.ST_GetHealthValue().ToString();
            text += " Blood=" + player.ST_GetBloodValue().ToString();
            text += " Shock=" + player.ST_GetShockValue().ToString();
            text += ". ";
        }

        text += eventText;
        return text;
    }

    void ST_AddToSection(array<string> list, string value, int maxCount)
    {
        if (!list || value == "")
            return;

        list.Insert(value);

        if (maxCount <= 0)
            maxCount = 60;

        while (list.Count() > maxCount)
        {
            list.Remove(0);
        }
    }

    bool ST_ReadSurvivorJournal(PlayerBase reader, SurvivorJournal journal)
    {
        ST_SurvivorStoryConfig config = GetConfig();

        if (!config || config.EnableSurvivorStorySystem != 1 || config.EnableReadablePhysicalJournals != 1)
            return false;

        ST_SurvivorStoryJournalFile data = ST_LoadJournalFromItem(journal);

        if (!data)
        {
            SurvivorThoughtsManager.Get().SendThoughtWithPriority(reader, "The journal pages are blank or too damaged to read.", "JOURNAL_SYSTEM");
            return true;
        }

        string title = "Journal of " + data.CharacterName;

        if (data.CharacterName == "")
            title = "Journal of an unknown survivor";

        SurvivorThoughtsManager.Get().SendThoughtWithPriority(reader, title, "JOURNAL_SYSTEM");

        ST_SendSection(reader, "First page", data.FirstEntry, 1);
        ST_SendSection(reader, "Daily note", data.DailyNotes, 3);
        ST_SendSection(reader, "Wounds", data.WoundsAndIllnesses, 2);
        ST_SendSection(reader, "People", data.PeopleMet, 2);
        ST_SendSection(reader, "Places", data.PlacesRemembered, 2);
        ST_SendSection(reader, "Mind", data.SanityNotes, 2);
        ST_SendSection(reader, "Last words", data.LastWords, 2);
        ST_SendSection(reader, "Death page", data.DeathPage, 1);

        ST_WriteStoryAnalytics("JournalRead", data.JournalId);
        return true;
    }

    void ST_SendSection(PlayerBase reader, string title, array<string> list, int maxLines)
    {
        if (!reader || !list || list.Count() <= 0)
            return;

        int start = list.Count() - maxLines;

        if (start < 0)
            start = 0;

        for (int i = start; i < list.Count(); i++)
        {
            SurvivorThoughtsManager.Get().SendThoughtWithPriority(reader, title + ": " + list.Get(i), "JOURNAL_SYSTEM");
        }
    }

    void UpdatePlayerStorySystems(PlayerBase player)
    {
        ST_SurvivorStoryConfig config = GetConfig();

        if (!player || !config || config.EnableSurvivorStorySystem != 1)
            return;

        if (!player.ST_IsJournalSetupComplete())
            return;

        string steamId = ST_GetSteamId(player);

        if (steamId == "")
            return;

        ST_SurvivorStoryPlayerRuntime runtime = ST_GetRuntime(steamId);

        if (!GetGame())
            return;

        float now = GetGame().GetTime() / 1000.0;

        if (runtime.LastStoryCheckTime > 0.0 && (now - runtime.LastStoryCheckTime) < config.StoryLayerCheckIntervalSeconds)
            return;

        runtime.LastStoryCheckTime = now;

        if (config.EnableConditionProfile == 1)
            ST_UpdateConditionProfile(player, runtime, config, now);

        if (config.EnableTraitFearThoughtStyle == 1)
            ST_MaybeSendTraitFearThought(player, runtime, config, now);

        if (config.EnableSanityHallucinationTextLayer == 1)
            ST_MaybeSendHallucinationThought(player, runtime, config, now);

        if (config.EnableMapTonePacks == 1)
            ST_MaybeSendMapToneThought(player, runtime, config, now);
    }

    ST_SurvivorStoryPlayerRuntime ST_GetRuntime(string steamId)
    {
        ST_SurvivorStoryPlayerRuntime runtime = m_Runtime.Get(steamId);

        if (!runtime)
        {
            runtime = new ST_SurvivorStoryPlayerRuntime();
            m_Runtime.Set(steamId, runtime);
        }

        return runtime;
    }

    string ST_GetConditionProfile(PlayerBase player)
    {
        if (!player)
            return "Stable";

        float health = player.ST_GetHealthValue();
        float blood = player.ST_GetBloodValue();
        float shock = player.ST_GetShockValue();
        float energy = player.ST_GetEnergyValue();
        float water = player.ST_GetWaterValue();

        int score = 0;

        if (health < 25.0) score += 4;
        else if (health < 50.0) score += 2;

        if (blood < 2500.0) score += 3;
        else if (blood < 4000.0) score += 1;

        if (shock < 25.0) score += 2;
        if (energy < 500.0) score += 3;
        else if (energy < 1500.0) score += 1;
        if (water < 500.0) score += 3;
        else if (water < 1500.0) score += 1;

        if (score >= 11)
            return "Broken";

        if (score >= 8)
            return "NearCollapse";

        if (score >= 6)
            return "Desperate";

        if (score >= 3)
            return "Stressed";

        if (score >= 1)
            return "WornDown";

        return "Stable";
    }

    void ST_UpdateConditionProfile(PlayerBase player, ST_SurvivorStoryPlayerRuntime runtime, ST_SurvivorStoryConfig config, float now)
    {
        if (!runtime || !config)
            return;

        string profile = ST_GetConditionProfile(player);
        runtime.LastConditionProfile = profile;

        if (runtime.LastConditionThoughtTime > 0.0 && (now - runtime.LastConditionThoughtTime) < config.ConditionThoughtCooldownSeconds)
            return;

        string message = ST_GetConditionMessage(profile, config);

        if (message == "")
            return;

        runtime.LastConditionThoughtTime = now;
        message = ST_ApplyIntensityPrefix(player, message, config);
        SurvivorThoughtsManager.Get().SendThoughtWithPriority(player, message, "MENTAL_STATE");
        AddMajorEvent(player, "[CONDITION_" + profile + "] " + message);
        ST_WriteStoryAnalytics("ConditionProfile", profile);
    }

    string ST_GetConditionMessage(string profile, ST_SurvivorStoryConfig config)
    {
        if (profile == "Broken" && config.ConditionBrokenMessages && config.ConditionBrokenMessages.Count() > 0)
            return config.ConditionBrokenMessages.GetRandomElement();

        if (profile == "NearCollapse" && config.ConditionNearCollapseMessages && config.ConditionNearCollapseMessages.Count() > 0)
            return config.ConditionNearCollapseMessages.GetRandomElement();

        if (profile == "Desperate" && config.ConditionDesperateMessages && config.ConditionDesperateMessages.Count() > 0)
            return config.ConditionDesperateMessages.GetRandomElement();

        if (profile == "Stressed" && config.ConditionStressedMessages && config.ConditionStressedMessages.Count() > 0)
            return config.ConditionStressedMessages.GetRandomElement();

        if (profile == "WornDown" && config.ConditionWornDownMessages && config.ConditionWornDownMessages.Count() > 0)
            return config.ConditionWornDownMessages.GetRandomElement();

        if (config.ConditionStableMessages && config.ConditionStableMessages.Count() > 0)
            return config.ConditionStableMessages.GetRandomElement();

        return "";
    }

    string ST_ApplyIntensityPrefix(PlayerBase player, string message, ST_SurvivorStoryConfig config)
    {
        if (!player || !config || config.EnableThoughtIntensityTiers != 1)
            return message;

        string profile = ST_GetConditionProfile(player);
        string prefix = "";

        if (profile == "Broken" || profile == "NearCollapse")
        {
            if (config.IntensityCriticalPrefixes && config.IntensityCriticalPrefixes.Count() > 0)
                prefix = config.IntensityCriticalPrefixes.GetRandomElement();
        }
        else if (profile == "Desperate")
        {
            if (config.IntensityDesperatePrefixes && config.IntensityDesperatePrefixes.Count() > 0)
                prefix = config.IntensityDesperatePrefixes.GetRandomElement();
        }
        else if (profile == "Stressed" || profile == "WornDown")
        {
            if (config.IntensityConcernedPrefixes && config.IntensityConcernedPrefixes.Count() > 0)
                prefix = config.IntensityConcernedPrefixes.GetRandomElement();
        }
        else
        {
            if (config.IntensitySubtlePrefixes && config.IntensitySubtlePrefixes.Count() > 0)
                prefix = config.IntensitySubtlePrefixes.GetRandomElement();
        }

        return prefix + message;
    }

    void ST_MaybeSendTraitFearThought(PlayerBase player, ST_SurvivorStoryPlayerRuntime runtime, ST_SurvivorStoryConfig config, float now)
    {
        if (!player || !runtime || !config)
            return;

        if (runtime.LastTraitFearThoughtTime > 0.0 && (now - runtime.LastTraitFearThoughtTime) < config.SpecificPlayerMemoryCooldownSeconds)
            return;

        string msg = ST_GetTraitMessage(player.ST_GetJournalTrait(), config);

        if (msg == "")
            msg = ST_GetFearMessage(player.ST_GetJournalFear(), config);

        if (msg == "")
            return;

        runtime.LastTraitFearThoughtTime = now;
        SurvivorThoughtsManager.Get().SendThoughtWithPriority(player, msg, "PERSONALITY");
        AddMajorEvent(player, "[IDENTITY_TONE] " + msg);
    }

    string ST_GetTraitMessage(string trait, ST_SurvivorStoryConfig config)
    {
        if (!config)
            return "";

        if (ST_HasText(trait, "cautious") && config.TraitCautiousMessages && config.TraitCautiousMessages.Count() > 0)
            return config.TraitCautiousMessages.GetRandomElement();

        if (ST_HasText(trait, "angry") && config.TraitAngryMessages && config.TraitAngryMessages.Count() > 0)
            return config.TraitAngryMessages.GetRandomElement();

        if (ST_HasText(trait, "quiet") && config.TraitQuietMessages && config.TraitQuietMessages.Count() > 0)
            return config.TraitQuietMessages.GetRandomElement();

        if (ST_HasText(trait, "resourceful") && config.TraitResourcefulMessages && config.TraitResourcefulMessages.Count() > 0)
            return config.TraitResourcefulMessages.GetRandomElement();

        if (ST_HasText(trait, "stubborn") && config.TraitStubbornMessages && config.TraitStubbornMessages.Count() > 0)
            return config.TraitStubbornMessages.GetRandomElement();

        if (config.TraitPracticalMessages && config.TraitPracticalMessages.Count() > 0)
            return config.TraitPracticalMessages.GetRandomElement();

        return "";
    }

    string ST_GetFearMessage(string fear, ST_SurvivorStoryConfig config)
    {
        if (!config)
            return "";

        if (ST_HasText(fear, "dark") && config.FearDarknessMessages && config.FearDarknessMessages.Count() > 0)
            return config.FearDarknessMessages.GetRandomElement();

        if (ST_HasText(fear, "infected") && config.FearInfectedCrowdsMessages && config.FearInfectedCrowdsMessages.Count() > 0)
            return config.FearInfectedCrowdsMessages.GetRandomElement();

        if (ST_HasText(fear, "starvation") && config.FearStarvationMessages && config.FearStarvationMessages.Count() > 0)
            return config.FearStarvationMessages.GetRandomElement();

        if (ST_HasText(fear, "alone") && config.FearBeingAloneMessages && config.FearBeingAloneMessages.Count() > 0)
            return config.FearBeingAloneMessages.GetRandomElement();

        if (ST_HasText(fear, "silence") && config.FearSilenceMessages && config.FearSilenceMessages.Count() > 0)
            return config.FearSilenceMessages.GetRandomElement();

        return "";
    }

    void ST_MaybeSendHallucinationThought(PlayerBase player, ST_SurvivorStoryPlayerRuntime runtime, ST_SurvivorStoryConfig config, float now)
    {
        if (!runtime || !config)
            return;

        if (runtime.LastHallucinationThoughtTime > 0.0 && (now - runtime.LastHallucinationThoughtTime) < config.HallucinationThoughtCooldownSeconds)
            return;

        string profile = ST_GetConditionProfile(player);

        if (profile != "Desperate" && profile != "NearCollapse" && profile != "Broken")
            return;

        string msg = "";

        if (config.HallucinationLowSanityMessages && config.HallucinationLowSanityMessages.Count() > 0)
            msg = config.HallucinationLowSanityMessages.GetRandomElement();

        if (msg == "")
            return;

        runtime.LastHallucinationThoughtTime = now;
        SurvivorThoughtsManager.Get().SendThoughtWithPriority(player, msg, "SANITY_CREEP");
        AddMajorEvent(player, "[SANITY_TEXT_LAYER] " + msg);
        ST_WriteStoryAnalytics("HallucinationText", profile);
    }

    void ST_MaybeSendMapToneThought(PlayerBase player, ST_SurvivorStoryPlayerRuntime runtime, ST_SurvivorStoryConfig config, float now)
    {
        if (!runtime || !config)
            return;

        if (runtime.LastMapToneThoughtTime > 0.0 && (now - runtime.LastMapToneThoughtTime) < config.MapToneThoughtCooldownSeconds)
            return;

        string msg = "";

        if (config.ActiveStoryPreset == "Namalsk_Horror" && config.MapToneNamalskMessages && config.MapToneNamalskMessages.Count() > 0)
            msg = config.MapToneNamalskMessages.GetRandomElement();
        else if (config.ActiveStoryPreset == "Livonia_Hardcore" && config.MapToneLivoniaMessages && config.MapToneLivoniaMessages.Count() > 0)
            msg = config.MapToneLivoniaMessages.GetRandomElement();
        else if (config.ActiveStoryPreset == "Sakhal_Exposure" && config.MapToneSakhalMessages && config.MapToneSakhalMessages.Count() > 0)
            msg = config.MapToneSakhalMessages.GetRandomElement();
        else if (config.MapToneGenericMessages && config.MapToneGenericMessages.Count() > 0)
            msg = config.MapToneGenericMessages.GetRandomElement();

        if (msg == "")
            return;

        runtime.LastMapToneThoughtTime = now;
        SurvivorThoughtsManager.Get().SendThoughtWithPriority(player, msg, "MAP_ENVIRONMENT");
        AddMajorEvent(player, "[MAP_TONE] " + msg);
        ST_WriteStoryAnalytics("MapTone", config.ActiveStoryPreset);
    }

    void RememberSpecificPlayer(PlayerBase player, PlayerBase otherPlayer, string reason)
    {
        ST_SurvivorStoryConfig config = GetConfig();

        if (!config || config.EnableSpecificPlayerMemory != 1)
            return;

        if (!player || !otherPlayer || !otherPlayer.GetIdentity())
            return;

        if (!player.ST_IsJournalSetupComplete())
            return;

        if (!GetGame())
            return;

        string steamId = ST_GetSteamId(player);

        if (steamId == "")
            return;

        ST_SurvivorStoryPlayerRuntime runtime = ST_GetRuntime(steamId);
        float now = GetGame().GetTime() / 1000.0;

        if (runtime.LastSpecificPlayerMemoryTime > 0.0 && (now - runtime.LastSpecificPlayerMemoryTime) < config.SpecificPlayerMemoryCooldownSeconds)
            return;

        runtime.LastSpecificPlayerMemoryTime = now;

        string remembered = otherPlayer.GetIdentity().GetName();

        if (config.HashStoredPlayerIds == 1)
            remembered = "known survivor";

        AddMajorEvent(player, "[PLAYER_MEMORY] Remembered " + remembered + " because " + reason + ".");
        ST_WriteStoryAnalytics("SpecificPlayerMemory", reason);
    }

    void ST_WriteStoryAnalytics(string eventType, string detail)
    {
        ST_SurvivorStoryConfig config = GetConfig();

        if (!config || config.EnableStoryAnalyticsDailyExport != 1)
            return;

        string filePath = config.StoryAnalyticsFolder + "/SurvivorStory_Analytics.jsonl";
        FileHandle file = OpenFile(filePath, FileMode.APPEND);

        if (!file)
            return;

        string safeEvent = ST_SanitizeAnalyticsText(eventType);
        string safeDetail = ST_SanitizeAnalyticsText(detail);
        string line = "{time:" + GetGame().GetTime().ToString() + ",event:" + safeEvent + ",detail:" + safeDetail + "}";

        FPrintln(file, line);
        CloseFile(file);
    }

    string ST_SanitizeAnalyticsText(string value)
    {
        string output = value;

        output.Replace("{", "(");
        output.Replace("}", ")");
        output.Replace(",", ";");

        return output;
    }
}
