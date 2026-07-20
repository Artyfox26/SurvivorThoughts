class ST_SurvivorThoughtsConfig
{
    int ConfigVersion;
    int EnableMod;

    int EnableThoughtPrioritySystem;
    float PriorityInterruptWindowSeconds;
    int PriorityImmediateDamage;
    int PriorityBleeding;
    int PriorityDeathSpiral;
    int PriorityCriticalSurvival;
    int PriorityHighSurvival;
    int PriorityMediumSurvival;
    int PriorityLowSurvival;
    int PriorityAction;
    int PriorityOpenCloseAction;
    int PriorityCombatStress;
    int PriorityWeather;
    int PriorityTimeOfDay;
    int PriorityLocation;
    int PriorityItemCondition;
    int PriorityCorpse;
    int PriorityContaminatedZone;
    int PriorityPersonality;
    int PriorityAdminSystem;

    int PriorityPlayerMemory;
    int PriorityStealthNoise;
    int PriorityShelter;
    int PriorityMentalState;
    int PriorityCustomThoughtZone;
    int PrioritySocialGroup;
    int PrioritySanityCreep;

    int PriorityStateHistory;
    int PriorityRecovery;
    int PriorityAdvancedCombined;
    int PriorityNearMissCombat;
    int PriorityDiseaseSpecific;
    int PriorityMapEnvironment;

    int EnablePlayerStateHistory;
    float StateHistorySampleIntervalSeconds;
    float StateHistoryWindowSeconds;
    float TrendChangeThreshold;
    int EnableTrendMessages;
    int EnableStateSnapshots;
    float StateSnapshotIntervalSeconds;
    int EnablePersistentStateSnapshots;
    string StateSnapshotFolder;
    int EnableThoughtDecisionTrace;
    int TraceOnlyBlockedThoughts;
    int TraceToDebugLog;
    int TraceToMissionStorage;
    string DecisionTraceFolder;

    int EnableAdvancedCombinedMessages;
    float AdvancedCombinedChance;
    int EnableRecoveryMessages;
    float RecoveryThoughtCooldownSeconds;
    float RecoveryThoughtChance;
    int EnableNearMissCombatMessages;
    float NearMissCombatCooldownSeconds;
    float NearMissCombatChance;
    int EnableDiseaseSpecificMessages;
    int EnableAdminAnalytics;
    float AnalyticsSaveIntervalSeconds;
    string AnalyticsFolder;
    int EnablePlayerJournals;
    string PlayerJournalFolder;
    int JournalOnlyMajorEvents;

    int EnableSurvivorJournalItem;
    int GiveJournalOnFreshSpawn;
    int DropJournalOnDeath;
    int AutoEquipJournalOnFreshSpawn;
    int AutoEquipJournalOnLoginIfMissing;
    int LockJournalToPlayerWhileAlive;
    int AllowJournalLootingAfterDeath;
    int DeleteJournalIfRemovedWhileAlive;
    int WriteJournalDeathEntryOnKilled;
    int JournalRequiredBeforeNormalPlay;
    int AllowReadingOtherPlayersJournals;
    int RequireJournalSetupMenu;
    int ShowJournalSetupMenuOnlyOnFreshCharacter;
    int AllowJournalSetupSkip;
    int AllowJournalSetupRandomize;
    string PlayerBackstoryDataFile;
    int MaxMajorJournalEventsStored;
    int JournalBackstoryMinMajorEvents;
    int ShowRealPlayerNameInJournal;
    int JournalSetupDefaultPage;
    int PriorityJournalSystem;

    ref array<string> JournalCharacterTypeOptions;
    ref array<string> JournalHeadTypeOptions;
    ref array<string> JournalAgeOptions;
    ref array<string> JournalBloodTypeOptions;
    ref array<string> JournalSurvivalInstinctOptions;
    ref array<string> JournalKeepsakeOptions;
    ref array<string> JournalOriginOptions;
    ref array<string> JournalOccupationOptions;
    ref array<string> JournalTraitOptions;
    ref array<string> JournalFearOptions;
    ref array<string> JournalGoalOptions;
    ref array<string> JournalSkillOptions;
    ref array<string> JournalWeaknessOptions;
    ref array<string> JournalMoralCodeOptions;
    ref array<string> JournalBackstoryTemplates;

    int EnableJournalSetupSpawnProtection;
    int JournalSetupBlockDamageUntilComplete;
    int JournalSetupSuppressThoughtsUntilComplete;
    int JournalSetupProtectionDebug;
    int JournalSetupRestoreStatsWhileActive;
    float JournalSetupProtectedHealthValue;
    float JournalSetupProtectedBloodValue;
    float JournalSetupProtectedShockValue;
    float JournalSetupProtectedEnergyValue;
    float JournalSetupProtectedWaterValue;
    float JournalSetupProtectedHeatComfortValue;

    int EnableMapEnvironmentPacks;
    string ActiveMapEnvironmentPack;
    float MapEnvironmentThoughtChance;
    float MapEnvironmentThoughtCooldownSeconds;

    int EnableProlongedStateMessages;
    float ProlongedStateThresholdSeconds;
    int EnableExpandedAdvancedCombos;
    int EnableAnalyticsJsonLines;
    string AnalyticsJsonLineFile;
    int JournalIncludePlayerStats;
    int JournalWriteAllRecoveryEvents;
    int TrackBlockedByPriority;
    int TrackBlockedByDuplicate;
    int TrackThoughtTypes;
    int TrackRecoveryEvents;
    int TrackSanityEvents;
    int TrackSocialEvents;
    int TrackStateHistoryEvents;
    int JournalWriteSanityEvents;
    int JournalWriteSocialEvents;
    int JournalWriteNearDeathEvents;
    int EnableJournalSystemIntegration;
    int JournalRecordAllThoughtSystems;
    int JournalRecordAmbientSystems;
    int JournalRecordBlockedDecisionEvents;
    int JournalMajorEventMinPriority;
    int JournalMajorEventPrefixWithSystem;
    int JournalMajorEventIncludeStats;
    int JournalRecordDeathEntries;
    int JournalRecordSetupChoices;
    int JournalRecordSystemLinkDebug;

    float GlobalCooldownSeconds;
    float MinimumRandomDelaySeconds;
    float MaximumRandomDelaySeconds;

    int ShowHealthyMessages;

    int EnableHungerMessages;
    int EnableThirstMessages;
    int EnableColdMessages;
    int EnableHotMessages;
    int EnableSicknessMessages;
    int EnableBleedingMessages;
    int EnableBrokenLegMessages;
    int EnableInfectedNearbyMessages;

    int EnableWeatherThoughts;
    int EnableItemConditionThoughts;
    float ItemConditionHealthThreshold;
    int EnableCombatStressThoughts;
    float CombatStressShockThreshold;
    int EnableContaminatedZoneThoughts;
    int EnableNearbyCorpseThoughts;
    float NearbyCorpseRadius;
    int EnablePersonalityProfiles;
    float PersonalityThoughtChance;
    int PersonalityPersistBySteamId;
    string PersonalityDataFile;

    int EnableMissionStoragePersistentData;
    string PersistentStorageRoot;
    string PersistentDataFolderName;
    string PersistentStateDataFile;
    float PersistentAutosaveSeconds;
    int EnablePersistentSaveThrottle;
    float PersistentForcedSaveCooldownSeconds;

    int EnablePersonalityChangeOverTime;
    float PersonalityChangeChance;
    float PersonalityMinimumSecondsBetweenChanges;

    int EnableCombatStressShockThoughts;
    int EnableCombatStressDamageEventThoughts;
    int EnableDamageReactionThoughts;
    int EnableZombieHitMessages;
    int EnablePlayerMeleeHitMessages;
    int EnableGunshotHitMessages;
    int EnableExplosionHitMessages;
    int EnableHeavyHitMessages;
    int EnableBleedingStartedMessages;
    int EnableBleedingWorseMessages;
    int EnableBleedingStoppedMessages;
    float CombatStressCooldownSeconds;
    int EnableBleedingReactionThoughts;
    float HeavyHitHealthDamage_Min;
    float HeavyHitBloodDamage_Min;
    float HeavyHitShockDamage_Min;

    int EnableDeathSpiralThoughts;
    float HealthDropMinAmount;
    float HealthDropRecentSeconds;
    float DeathSpiralColdComfort_Max;
    float DeathSpiralHotComfort_Min;
    int EnableStarvingToDeathMessages;
    int EnableDehydratingToDeathMessages;
    int EnableFreezingToDeathMessages;
    int EnableOverheatingToDeathMessages;

    float RainThought_Min;
    float LightRainThought_Min;
    float HeavyRainThought_Min;
    float FogThought_Min;
    float WindThought_Min;
    float OvercastThought_Min;
    float StormRain_Min;
    float StormWind_Min;
    float StormOvercast_Min;
    int EnableClearWeatherMessages;
    int EnableOvercastWeatherMessages;
    int EnableLightRainMessages;
    int EnableHeavyRainMessages;
    int EnableFogWeatherMessages;
    int EnableWindWeatherMessages;
    int EnableStormWeatherMessages;
    float WeatherThoughtCooldownSeconds;
    float WeatherThoughtChance;

    int EnableTimeOfDayThoughts;
    float TimeOfDayThoughtCooldownSeconds;
    float TimeOfDayThoughtChance;
    int EnableDawnMessages;
    int EnableMorningMessages;
    int EnableNoonMessages;
    int EnableAfternoonMessages;
    int EnableDuskMessages;
    int EnableNightMessages;
    int EnableMidnightMessages;
    int EnableEarlyMorningMessages;
    float DawnStartHour;
    float MorningStartHour;
    float NoonStartHour;
    float AfternoonStartHour;
    float DuskStartHour;
    float NightStartHour;
    float MidnightStartHour;
    float EarlyMorningStartHour;

    int ScanEquippedItemsForDamagedThoughts;
    int EnableHandsItemConditionMessages;
    int EnableWeaponConditionMessages;
    int EnableClothingConditionMessages;
    int EnableShoesConditionMessages;
    int EnableBackpackConditionMessages;
    int EnableVestConditionMessages;
    int EnableHeadgearConditionMessages;
    int EnableGlovesConditionMessages;
    int EnableMaskConditionMessages;
    int EnableBeltConditionMessages;

    int EnableLocationThoughts;
    float LocationThoughtCooldownSeconds;
    float LocationThoughtChance;
    int LocationUseCustomZones;
    int LocationUseFallbackDetection;
    float LocationCoastZMax;
    float LocationWildernessScanRadius;
    int LocationWildernessMaxObjects;
    ref array<ref ST_LocationZone> LocationZones;

    int EnablePlayerMemoryThoughts;
    float PlayerMemoryThoughtCooldownSeconds;
    float PlayerMemoryThoughtChance;
    float PlayerMemoryDurationSeconds;

    int EnableStealthNoiseThoughts;
    float StealthNoiseThoughtCooldownSeconds;
    float StealthNoiseThoughtChance;
    float StealthNoiseInfectedRadius;
    float StealthNoiseRunSpeedThreshold;

    int EnableShelterThoughts;
    float ShelterThoughtCooldownSeconds;
    float ShelterThoughtChance;
    float ShelterScanRadius;
    int ShelterNearbyBuildingCountRequired;

    int EnableRecentMessageBlocker;
    int RecentMessageMemoryCount;
    float RecentMessageBlockSeconds;

    int EnableMentalStateThoughts;
    float MentalStateThoughtCooldownSeconds;
    float MentalStateThoughtChance;
    float MentalStateCriticalHealthMax;
    float MentalStateLowBloodMax;
    float MentalStateLowFoodMax;
    float MentalStateLowWaterMax;

    int EnableCustomThoughtZones;
    float CustomThoughtZoneDefaultCooldownSeconds;
    float CustomThoughtZoneDefaultChance;

    int EnableSocialGroupThoughts;
    float SocialGroupThoughtCooldownSeconds;
    float SocialGroupThoughtChance;
    float SocialNearbyPlayerRadius;
    float SocialFriendlyTimeRequiredSeconds;
    float SocialMemoryDurationSeconds;
    float LoneWolfNoPlayerSeenSeconds;
    int EnableTeammateShotMessages;
    int EnableTeammateDownMessages;
    int EnableLoneWolfMessages;
    int EnableFriendlyNearbyMessages;

    int EnableSanityCreep;
    float SanityThoughtCooldownSeconds;
    float SanityThoughtChance;
    float StartingSanity;
    float MinimumSanity;
    float SanityLossSkinHuman;
    float SanityLossEatHumanMeat;
    float SanityLossKillRestrainedPlayer;
    float SanityRegenPerMinute;
    float SanityUneasyThreshold;
    float SanityUnhingedThreshold;
    float SanityPsychoticThreshold;
    int EnableSanityUneasyMessages;
    int EnableSanityUnhingedMessages;
    int EnableSanityPsychoticMessages;
    int EnableCannibalismCreepMessages;

    ref array<ref ST_CustomThoughtZone> CustomThoughtZones;

    ref array<string> TeammateShotMessages;
    ref array<string> TeammateDownMessages;
    ref array<string> LoneWolfMessages;
    ref array<string> FriendlyNearbyMessages;

    ref array<string> SanityUneasyMessages;
    ref array<string> SanityUnhingedMessages;
    ref array<string> SanityPsychoticMessages;
    ref array<string> CannibalismCreepMessages;

    ref array<string> TrendEnergyFallingMessages;
    ref array<string> TrendWaterFallingMessages;
    ref array<string> TrendBloodFallingMessages;
    ref array<string> TrendHealthFallingMessages;
    ref array<string> TrendTemperatureWorseningMessages;
    ref array<string> TrendWetnessWorseningMessages;
    ref array<string> LongSicknessMessages;
    ref array<string> LongBleedingMessages;

    ref array<string> StarvingDehydratedMessages;
    ref array<string> StarvingLowBloodMessages;
    ref array<string> DehydratedLowBloodMessages;
    ref array<string> ColdWetMessages;
    ref array<string> ColdWetNightMessages;
    ref array<string> ColdWetSickMessages;
    ref array<string> HotDehydratedMessages;
    ref array<string> HotSickMessages;
    ref array<string> BleedingLowBloodMessages;
    ref array<string> BleedingShockMessages;
    ref array<string> GunshotBleedingMessages;
    ref array<string> ExplosionShockMessages;
    ref array<string> BrokenLegInfectedMessages;
    ref array<string> BrokenLegNightMessages;
    ref array<string> LowBloodCorpseMessages;
    ref array<string> SickContaminatedMessages;
    ref array<string> NightRainMessages;
    ref array<string> NightFogMessages;
    ref array<string> MilitaryGunshotMessages;
    ref array<string> MilitaryCorpseMessages;
    ref array<string> LoneWolfNightMessages;
    ref array<string> LowSanityCannibalismMessages;
    ref array<string> LowSanityCorpseMessages;
    ref array<string> LowSanityNightMessages;
    ref array<string> CompanionDeadLowSanityMessages;

    ref array<string> BleedingRecoveryMessages;
    ref array<string> HealthStableRecoveryMessages;
    ref array<string> FoodRecoveryMessages;
    ref array<string> WaterRecoveryMessages;
    ref array<string> WarmedUpMessages;
    ref array<string> CooledDownMessages;
    ref array<string> DryingOffMessages;
    ref array<string> LeftContaminatedZoneMessages;
    ref array<string> EscapedInfectedMessages;
    ref array<string> DawnSurvivalMessages;
    ref array<string> ShelterFromStormMessages;

    ref array<string> NearMissBulletMessages;
    ref array<string> NearMissExplosionMessages;
    ref array<string> NearMissCombatGeneralMessages;

    ref array<string> DiseaseWoundInfectionMessages;
    ref array<string> DiseaseCholeraMessages;
    ref array<string> DiseaseInfluenzaMessages;
    ref array<string> DiseaseKuruMessages;
    ref array<string> DiseaseChemicalMessages;
    ref array<string> DiseaseUnknownMessages;

    ref array<string> MapChernarusMessages;
    ref array<string> MapLivoniaMessages;
    ref array<string> MapNamalskMessages;
    ref array<string> MapSakhalMessages;
    ref array<string> MapDeerIsleMessages;
    ref array<string> MapGenericMessages;

    ref array<string> ProlongedStarvationMessages;
    ref array<string> ProlongedDehydrationMessages;
    ref array<string> ProlongedColdMessages;
    ref array<string> ProlongedHeatMessages;
    ref array<string> ProlongedBleedingMessages;
    ref array<string> ProlongedSicknessMessages;

    ref array<string> StarvingDehydratedColdMessages;
    ref array<string> HotDehydratedSickMessages;
    ref array<string> BleedingLowBloodShockMessages;
    ref array<string> GunshotBleedingLowBloodMessages;
    ref array<string> BrokenLegBleedingInfectedMessages;
    ref array<string> NightInfectedRainMessages;
    ref array<string> MilitaryNightStormMessages;
    ref array<string> LoneWolfLowSanityNightMessages;
    ref array<string> CompanionDeadNightMessages;
    ref array<string> CorpseLowSanityNightMessages;
    ref array<string> ShelterNightInfectedMessages;

    ref array<string> ShockRecoveryMessages;
    ref array<string> BloodStabilizingMessages;
    ref array<string> AlmostDiedRecoveryMessages;
    ref array<string> SafeShelterRecoveryMessages;
    ref array<string> PostCombatBreathMessages;

    ref array<string> DiseaseGasExposureMessages;
    ref array<string> DiseaseFeverMessages;
    ref array<string> DiseaseFoodPoisoningMessages;

    int EnableAdminReload;
    string AdminReloadCommand;
    ref array<string> AdminSteamIds;

    ref array<string> LocationCoastMessages;
    ref array<string> LocationTownMessages;
    ref array<string> LocationCityMessages;
    ref array<string> LocationForestMessages;
    ref array<string> LocationWildernessMessages;
    ref array<string> LocationMilitaryMessages;
    ref array<string> LocationPoliceMessages;
    ref array<string> LocationMedicalMessages;
    ref array<string> LocationIndustrialMessages;
    ref array<string> LocationFarmMessages;
    ref array<string> LocationWaterMessages;


    ref array<string> PlayerMemoryRecentDamageMessages;
    ref array<string> PlayerMemoryRecentBleedingMessages;
    ref array<string> PlayerMemoryRecentGunshotMessages;
    ref array<string> PlayerMemoryRecentCorpseMessages;
    ref array<string> PlayerMemoryRecentMilitaryMessages;
    ref array<string> PlayerMemoryRecentSurvivalCrisisMessages;

    ref array<string> StealthNoiseInfectedNearbyMessages;
    ref array<string> StealthNoiseNightMessages;
    ref array<string> StealthNoiseMilitaryMessages;

    ref array<string> ShelterSafeMessages;
    ref array<string> ShelterUnsafeMessages;
    ref array<string> ShelterBadWeatherMessages;
    ref array<string> ShelterNightMessages;

    ref array<string> MentalStateStableMessages;
    ref array<string> MentalStateUneasyMessages;
    ref array<string> MentalStateAfraidMessages;
    ref array<string> MentalStateDesperateMessages;
    ref array<string> MentalStateNumbMessages;
    ref array<string> MentalStateAggressiveMessages;
    ref array<string> MentalStateBrokenMessages;
    ref array<string> MentalStateFocusedMessages;

    float InfectedFarRadius;
    float InfectedCloseRadius;
    float InfectedVeryCloseRadius;
    int InfectedSurroundedCount;

    int UseNotificationSystem;
    int UseLocalChatBox;
    int EnableActionThoughts;
    int EnableEatingThoughts;
    int EnableDrinkingThoughts;
    int EnableUnjamThoughts;
    int EnableSkinningThoughts;
    int EnableBandagingThoughts;
    int EnableFireStartingThoughts;
    int EnableCookingThoughts;
    int EnableFishingThoughts;
    int EnableRepairThoughts;
    int EnableExtendedVanillaActionMessages;

    float ActionThoughtCooldownSeconds;
    float OpenCloseActionCooldownSeconds;
    float DuplicateImmediateActionCooldownSeconds;
    int AllowActionThoughtsDuringCombat;

    int DebugMode;
    int EnableDebugFileLog;
    int DebugLogToRPT;
    string DebugLogFileName;
    int ClearDebugLogOnServerStart;

    int EnableConfigurableStatThresholds;

    int EnableEnergyStage1Messages;
    float EnergyStage1_Min;
    float EnergyStage1_Max;
    int EnableEnergyStage2Messages;
    float EnergyStage2_Min;
    float EnergyStage2_Max;
    int EnableEnergyStage3Messages;
    float EnergyStage3_Min;
    float EnergyStage3_Max;
    int EnableEnergyStage4Messages;
    float EnergyStage4_Min;
    float EnergyStage4_Max;

    int EnableWaterStage1Messages;
    float WaterStage1_Min;
    float WaterStage1_Max;
    int EnableWaterStage2Messages;
    float WaterStage2_Min;
    float WaterStage2_Max;
    int EnableWaterStage3Messages;
    float WaterStage3_Min;
    float WaterStage3_Max;
    int EnableWaterStage4Messages;
    float WaterStage4_Min;
    float WaterStage4_Max;

    int EnableBloodStage1Messages;
    float BloodStage1_Min;
    float BloodStage1_Max;
    int EnableBloodStage2Messages;
    float BloodStage2_Min;
    float BloodStage2_Max;
    int EnableBloodStage3Messages;
    float BloodStage3_Min;
    float BloodStage3_Max;
    int EnableBloodStage4Messages;
    float BloodStage4_Min;
    float BloodStage4_Max;

    int EnableShockStage1Messages;
    float ShockStage1_Min;
    float ShockStage1_Max;
    int EnableShockStage2Messages;
    float ShockStage2_Min;
    float ShockStage2_Max;
    int EnableShockStage3Messages;
    float ShockStage3_Min;
    float ShockStage3_Max;
    int EnableShockStage4Messages;
    float ShockStage4_Min;
    float ShockStage4_Max;

    int EnableCombinedThoughts;
    int MaxCombinedThoughtParts;
    float CombinedThoughtChance;
    int UseExtremeSurvivalMessagesAtStateCount;
    int UseCriticalSurvivalMessagesAtStateCount;

    ref array<string> HungerColdInfectedMessages;
    ref array<string> HungerThirstMessages;
    ref array<string> ColdInfectedMessages;
    ref array<string> BleedingInfectedMessages;
    ref array<string> SickColdMessages;
    ref array<string> HotThirstMessages;
    ref array<string> SickThirstMessages;
    ref array<string> BleedingColdMessages;

    ref array<string> BrokenLegHungerMessages;
    ref array<string> BrokenLegThirstMessages;
    ref array<string> BrokenLegColdMessages;
    ref array<string> BrokenLegHotMessages;
    ref array<string> BrokenLegSickMessages;
    ref array<string> BrokenLegBleedingMessages;
    ref array<string> BrokenLegColdInfectedMessages;
    ref array<string> BrokenLegHungerThirstMessages;

    ref array<string> HungerColdMessages;
    ref array<string> HungerHotMessages;
    ref array<string> HungerSickMessages;
    ref array<string> HungerBleedingMessages;
    ref array<string> HungerInfectedMessages;
    ref array<string> ThirstColdMessages;
    ref array<string> ThirstBleedingMessages;
    ref array<string> ThirstInfectedMessages;
    ref array<string> HotBleedingMessages;
    ref array<string> HotInfectedMessages;
    ref array<string> SickBleedingMessages;
    ref array<string> SickInfectedMessages;
    ref array<string> HungerThirstColdMessages;
    ref array<string> HungerThirstHotMessages;
    ref array<string> HungerThirstInfectedMessages;
    ref array<string> ThirstHotInfectedMessages;
    ref array<string> SickColdInfectedMessages;
    ref array<string> BleedingColdInfectedMessages;
    ref array<string> BleedingSickInfectedMessages;
    ref array<string> ExtremeSurvivalMessages;
    ref array<string> CriticalSurvivalMessages;

    ref array<string> StarvingToDeathMessages;
    ref array<string> DehydratingToDeathMessages;
    ref array<string> FreezingToDeathMessages;
    ref array<string> OverheatingToDeathMessages;



    ref array<string> WeatherClearMessages;
    ref array<string> WeatherOvercastMessages;
    ref array<string> WeatherLightRainMessages;
    ref array<string> WeatherHeavyRainMessages;
    ref array<string> WeatherRainMessages;
    ref array<string> WeatherFogMessages;
    ref array<string> WeatherStormMessages;
    ref array<string> WeatherWindMessages;

    ref array<string> DawnMessages;
    ref array<string> MorningMessages;
    ref array<string> NoonMessages;
    ref array<string> AfternoonMessages;
    ref array<string> DuskMessages;
    ref array<string> NightMessages;
    ref array<string> MidnightMessages;
    ref array<string> EarlyMorningMessages;

    ref array<string> ItemBadlyDamagedMessages;
    ref array<string> ItemWeaponDamagedMessages;
    ref array<string> ItemShoesDamagedMessages;
    ref array<string> ItemClothingDamagedMessages;
    ref array<string> ItemBackpackDamagedMessages;
    ref array<string> ItemVestDamagedMessages;
    ref array<string> ItemHeadgearDamagedMessages;
    ref array<string> ItemGlovesDamagedMessages;
    ref array<string> ItemMaskDamagedMessages;
    ref array<string> ItemBeltDamagedMessages;

    ref array<string> CombatStressMessages;
    ref array<string> CombatHitMessages;
    ref array<string> CombatShockMessages;
    ref array<string> ZombieHitMessages;
    ref array<string> PlayerMeleeHitMessages;
    ref array<string> GunshotHitMessages;
    ref array<string> ExplosionHitMessages;
    ref array<string> HeavyHitMessages;
    ref array<string> BleedingStartedMessages;
    ref array<string> BleedingWorseMessages;
    ref array<string> BleedingStoppedMessages;
    ref array<string> ContaminatedZoneMessages;
    ref array<string> NearbyCorpseMessages;
    ref array<string> NearbyPlayerCorpseMessages;
    ref array<string> NearbyInfectedCorpseMessages;
    ref array<string> NearbyAnimalCorpseMessages;

    ref array<string> PersonalityPracticalMessages;
    ref array<string> PersonalityScaredMessages;
    ref array<string> PersonalityMilitaryMessages;
    ref array<string> PersonalityHopelessMessages;
    ref array<string> PersonalityAggressiveMessages;
    ref array<string> PersonalityCalmMessages;


    ref array<string> EnergyStage1Messages;
    ref array<string> EnergyStage2Messages;
    ref array<string> EnergyStage3Messages;
    ref array<string> EnergyStage4Messages;

    ref array<string> WaterStage1Messages;
    ref array<string> WaterStage2Messages;
    ref array<string> WaterStage3Messages;
    ref array<string> WaterStage4Messages;

    ref array<string> BloodStage1Messages;
    ref array<string> BloodStage2Messages;
    ref array<string> BloodStage3Messages;
    ref array<string> BloodStage4Messages;

    ref array<string> ShockStage1Messages;
    ref array<string> ShockStage2Messages;
    ref array<string> ShockStage3Messages;
    ref array<string> ShockStage4Messages;

    ref array<string> Cold_Mild_Messages;
    ref array<string> Cold_Moderate_Messages;
    ref array<string> Cold_Severe_Messages;
    ref array<string> Cold_Critical_Messages;

    ref array<string> Hot_Mild_Messages;
    ref array<string> Hot_Moderate_Messages;
    ref array<string> Hot_Severe_Messages;
    ref array<string> Hot_Critical_Messages;

    ref array<string> Sickness_Early_Messages;
    ref array<string> Sickness_Moderate_Messages;
    ref array<string> Sickness_Severe_Messages;
    ref array<string> Sickness_Critical_Messages;

    ref array<string> Bleeding_One_Messages;
    ref array<string> Bleeding_Multiple_Messages;
    ref array<string> Bleeding_Critical_Messages;

    ref array<string> BrokenLegMessages;

    ref array<string> Infected_Far_Messages;
    ref array<string> Infected_Close_Messages;
    ref array<string> Infected_VeryClose_Messages;
    ref array<string> Infected_Surrounded_Messages;

    ref array<string> EatingMessages;
    ref array<string> DrinkingMessages;
    ref array<string> UnsafeDrinkingMessages;

    ref array<string> UnjamMessages;
    ref array<string> UnjamSuccessMessages;

    ref array<string> SkinningAnimalMessages;
    ref array<string> SkinningHumanMessages;

    ref array<string> BandagingMessages;
    ref array<string> BandageSuccessMessages;

    ref array<string> FireStartingMessages;
    ref array<string> CookingMessages;
    ref array<string> FishingMessages;
    ref array<string> RepairMessages;
    ref array<string> GeneralActionMessages;
    ref array<string> OpenCloseActionMessages;
    ref array<string> MedicineConsumeMessages;
    ref array<string> WoundCareActionMessages;
    ref array<string> InjectionMessages;
    ref array<string> BloodMedicalMessages;
    ref array<string> DisinfectActionMessages;
    ref array<string> RestrainActionMessages;
    ref array<string> CraftingActionMessages;
    ref array<string> DeployActionMessages;
    ref array<string> GardeningActionMessages;
    ref array<string> ResourceGatheringMessages;
    ref array<string> LiquidTransferMessages;
    ref array<string> FireplaceActionMessages;
    ref array<string> ElectronicsActionMessages;
    ref array<string> NavigationActionMessages;
    ref array<string> LockActionMessages;
    ref array<string> TrapExplosiveMessages;
    ref array<string> BaseBuildingActionMessages;
    ref array<string> VehicleActionMessages;
    ref array<string> InventoryActionMessages;
    ref array<string> BuryStashMessages;
    ref array<string> PersonalCareMessages;
    ref array<string> AmmoManagementMessages;
    ref array<string> MovementActionMessages;
    ref array<string> WorldInteractionMessages;

    void ST_SurvivorThoughtsConfig()
    {
        SetDefaults();
    }

    void SetDefaults()
    {
        ConfigVersion = 64;
        EnableMod = 1;

        EnableThoughtPrioritySystem = 1;
        PriorityInterruptWindowSeconds = 8.0;
        PriorityImmediateDamage = 100;
        PriorityBleeding = 100;
        PriorityDeathSpiral = 95;
        PriorityCriticalSurvival = 90;
        PriorityHighSurvival = 70;
        PriorityMediumSurvival = 50;
        PriorityLowSurvival = 25;
        PriorityAction = 35;
        PriorityOpenCloseAction = 20;
        PriorityCombatStress = 75;
        PriorityWeather = 15;
        PriorityTimeOfDay = 15;
        PriorityLocation = 20;
        PriorityItemCondition = 55;
        PriorityCorpse = 45;
        PriorityContaminatedZone = 80;
        PriorityPersonality = 10;
        PriorityAdminSystem = 100;
        PriorityPlayerMemory = 40;
        PriorityStealthNoise = 45;
        PriorityShelter = 25;
        PriorityMentalState = 60;
        PriorityCustomThoughtZone = 30;
        PrioritySocialGroup = 65;
        PrioritySanityCreep = 70;

        PriorityStateHistory = 50;
        PriorityRecovery = 55;
        PriorityAdvancedCombined = 85;
        PriorityNearMissCombat = 80;
        PriorityDiseaseSpecific = 70;
        PriorityMapEnvironment = 18;

        EnablePlayerStateHistory = 1;
        StateHistorySampleIntervalSeconds = 30.0;
        StateHistoryWindowSeconds = 900.0;
        TrendChangeThreshold = 0.10;
        EnableTrendMessages = 1;
        EnableStateSnapshots = 0;
        StateSnapshotIntervalSeconds = 300.0;
        EnablePersistentStateSnapshots = 0;
        StateSnapshotFolder = "$mission:storage_1/ZombiCideMods/SurvivorThoughts/Debug/PlayerStateSnapshots";
        EnableThoughtDecisionTrace = 0;
        TraceOnlyBlockedThoughts = 1;
        TraceToDebugLog = 1;
        TraceToMissionStorage = 0;
        DecisionTraceFolder = "$mission:storage_1/ZombiCideMods/SurvivorThoughts/Debug/DecisionTrace";

        EnableAdvancedCombinedMessages = 1;
        AdvancedCombinedChance = 0.65;
        EnableRecoveryMessages = 1;
        RecoveryThoughtCooldownSeconds = 180.0;
        RecoveryThoughtChance = 0.40;
        EnableNearMissCombatMessages = 1;
        NearMissCombatCooldownSeconds = 45.0;
        NearMissCombatChance = 0.35;
        EnableDiseaseSpecificMessages = 1;
        EnableAdminAnalytics = 1;
        AnalyticsSaveIntervalSeconds = 300.0;
        AnalyticsFolder = "$mission:storage_1/ZombiCideMods/SurvivorThoughts/Analytics";
        EnablePlayerJournals = 1;
        PlayerJournalFolder = "$mission:storage_1/ZombiCideMods/SurvivorThoughts/Journals";
        JournalOnlyMajorEvents = 1;

        EnableSurvivorJournalItem = 1;
        GiveJournalOnFreshSpawn = 1;
        DropJournalOnDeath = 1;
        AllowReadingOtherPlayersJournals = 1;
        RequireJournalSetupMenu = 0;
        ShowJournalSetupMenuOnlyOnFreshCharacter = 0;
        AllowJournalSetupSkip = 0;
        AllowJournalSetupRandomize = 0;
        PlayerBackstoryDataFile = "$mission:storage_1/ZombiCideMods/SurvivorThoughts/Data/PlayerBackstories.json";
        MaxMajorJournalEventsStored = 25;
        JournalBackstoryMinMajorEvents = 0;
        ShowRealPlayerNameInJournal = 0;
        JournalSetupDefaultPage = 0;
        EnableJournalSetupSpawnProtection = 0;
        JournalSetupBlockDamageUntilComplete = 0;
        JournalSetupSuppressThoughtsUntilComplete = 0;
        JournalSetupProtectionDebug = 0;
        JournalSetupRestoreStatsWhileActive = 0;
        JournalSetupProtectedHealthValue = 100.0;
        JournalSetupProtectedBloodValue = 5000.0;
        JournalSetupProtectedShockValue = 100.0;
        JournalSetupProtectedEnergyValue = 5000.0;
        JournalSetupProtectedWaterValue = 5000.0;
        JournalSetupProtectedHeatComfortValue = 0.0;
        PriorityJournalSystem = 62;

        JournalOriginOptions = new array<string>;
        JournalOriginOptions.Insert("Chernarus");
        JournalOriginOptions.Insert("Livonia");
        JournalOriginOptions.Insert("Sakhal");
        JournalOriginOptions.Insert("Namalsk");
        JournalOriginOptions.Insert("Unknown coast");
        JournalOriginOptions.Insert("Inland settlement");

        JournalOccupationOptions = new array<string>;
        JournalOccupationOptions.Insert("rail worker");
        JournalOccupationOptions.Insert("paramedic");
        JournalOccupationOptions.Insert("hunter");
        JournalOccupationOptions.Insert("mechanic");
        JournalOccupationOptions.Insert("teacher");
        JournalOccupationOptions.Insert("dock worker");
        JournalOccupationOptions.Insert("soldier");
        JournalOccupationOptions.Insert("farmer");

        JournalTraitOptions = new array<string>;
        JournalTraitOptions.Insert("practical");
        JournalTraitOptions.Insert("quiet");
        JournalTraitOptions.Insert("stubborn");
        JournalTraitOptions.Insert("cautious");
        JournalTraitOptions.Insert("angry");
        JournalTraitOptions.Insert("calm under pressure");
        JournalTraitOptions.Insert("resourceful");
        JournalTraitOptions.Insert("distrustful");

        JournalFearOptions = new array<string>;
        JournalFearOptions.Insert("dying alone");
        JournalFearOptions.Insert("being left behind");
        JournalFearOptions.Insert("the dark");
        JournalFearOptions.Insert("infected crowds");
        JournalFearOptions.Insert("starvation");
        JournalFearOptions.Insert("silence");

        JournalGoalOptions = new array<string>;
        JournalGoalOptions.Insert("find a safe place");
        JournalGoalOptions.Insert("reach the next town");
        JournalGoalOptions.Insert("keep moving north");
        JournalGoalOptions.Insert("find someone worth trusting");
        JournalGoalOptions.Insert("survive one more day");
        JournalGoalOptions.Insert("learn what happened");

        JournalSkillOptions = new array<string>;
        JournalSkillOptions.Insert("first aid");
        JournalSkillOptions.Insert("repairing engines");
        JournalSkillOptions.Insert("hunting");
        JournalSkillOptions.Insert("navigation");
        JournalSkillOptions.Insert("farming");
        JournalSkillOptions.Insert("keeping quiet");
        JournalSkillOptions.Insert("handling weapons");
        JournalSkillOptions.Insert("scavenging");

        JournalWeaknessOptions = new array<string>;
        JournalWeaknessOptions.Insert("trusts too easily");
        JournalWeaknessOptions.Insert("panics in the dark");
        JournalWeaknessOptions.Insert("hates being alone");
        JournalWeaknessOptions.Insert("takes unnecessary risks");
        JournalWeaknessOptions.Insert("cannot ignore people in trouble");
        JournalWeaknessOptions.Insert("holds grudges");
        JournalWeaknessOptions.Insert("struggles with hunger");
        JournalWeaknessOptions.Insert("freezes under pressure");

        JournalMoralCodeOptions = new array<string>;
        JournalMoralCodeOptions.Insert("will not abandon a friend");
        JournalMoralCodeOptions.Insert("will not eat human meat");
        JournalMoralCodeOptions.Insert("avoids killing unless forced");
        JournalMoralCodeOptions.Insert("protects the weak when possible");
        JournalMoralCodeOptions.Insert("survival comes before mercy");
        JournalMoralCodeOptions.Insert("trust must be earned");
        JournalMoralCodeOptions.Insert("never wastes supplies");
        JournalMoralCodeOptions.Insert("keeps moving, no matter what");

        JournalBackstoryTemplates = new array<string>;
        JournalBackstoryTemplates.Insert("{name} came from {origin}, once working as a {occupation}. They were {trait}, skilled at {skill}, but the outbreak left them afraid of {fear}. Their weakness is that they {weakness}. Their line is simple: {moral}. Now they are trying to {goal}.");
        JournalBackstoryTemplates.Insert("Before everything collapsed, {name} was a {occupation}. People called them {trait}. They survived by {skill}, but {weakness}. They left {origin} after the first panic and now only writes about one thing: {goal}. They still believe they {moral}.");
        JournalBackstoryTemplates.Insert("{name} does not write much about life before. The few clear notes mention {origin}, {occupation}, {skill}, and a fear of {fear}. The rest is survival. One sentence is underlined twice: {moral}.");

        EnableMapEnvironmentPacks = 1;
        ActiveMapEnvironmentPack = "Generic";
        MapEnvironmentThoughtChance = 0.20;
        MapEnvironmentThoughtCooldownSeconds = 600.0;
        EnableProlongedStateMessages = 1;
        ProlongedStateThresholdSeconds = 600.0;
        EnableExpandedAdvancedCombos = 1;
        EnableAnalyticsJsonLines = 1;
        AnalyticsJsonLineFile = "$mission:storage_1/ZombiCideMods/SurvivorThoughts/Analytics/SurvivorThoughts_Analytics.jsonl";
        JournalIncludePlayerStats = 1;
        JournalWriteAllRecoveryEvents = 1;
        TrackBlockedByPriority = 1;
        TrackBlockedByDuplicate = 1;
        TrackThoughtTypes = 1;
        TrackRecoveryEvents = 1;
        TrackSanityEvents = 1;
        TrackSocialEvents = 1;
        TrackStateHistoryEvents = 1;
        JournalWriteSanityEvents = 1;
        JournalWriteSocialEvents = 1;
        JournalWriteNearDeathEvents = 1;

        GlobalCooldownSeconds = 120.0;
        MinimumRandomDelaySeconds = 45.0;
        MaximumRandomDelaySeconds = 180.0;

        ShowHealthyMessages = 0;

        EnableHungerMessages = 1;
        EnableThirstMessages = 1;
        EnableColdMessages = 1;
        EnableHotMessages = 1;
        EnableSicknessMessages = 1;
        EnableBleedingMessages = 1;
        EnableBrokenLegMessages = 1;
        EnableInfectedNearbyMessages = 1;

        EnableWeatherThoughts = 1;
        EnableItemConditionThoughts = 1;
        ItemConditionHealthThreshold = 0.50;
        EnableHandsItemConditionMessages = 1;
        EnableWeaponConditionMessages = 1;
        EnableClothingConditionMessages = 1;
        EnableShoesConditionMessages = 1;
        EnableBackpackConditionMessages = 1;
        EnableVestConditionMessages = 1;
        EnableHeadgearConditionMessages = 1;
        EnableGlovesConditionMessages = 1;
        EnableMaskConditionMessages = 1;
        EnableBeltConditionMessages = 1;
        EnableCombatStressThoughts = 1;
        CombatStressShockThreshold = 65.0;
        EnableContaminatedZoneThoughts = 1;
        EnableNearbyCorpseThoughts = 1;
        NearbyCorpseRadius = 35.0;
        EnablePersonalityProfiles = 1;
        PersonalityThoughtChance = 0.20;
        PersonalityPersistBySteamId = 1;
        PersonalityDataFile = "$mission:storage_1/ZombiCideMods/SurvivorThoughts/Data/PlayerPersonalities.json";
        EnableMissionStoragePersistentData = 1;
        PersistentStorageRoot = "$mission:storage_1/ZombiCideMods/SurvivorThoughts";
        PersistentDataFolderName = "Data";
        PersistentStateDataFile = "$mission:storage_1/ZombiCideMods/SurvivorThoughts/Data/PlayerPersistentStates.json";
        PersistentAutosaveSeconds = 60.0;
        EnablePersonalityChangeOverTime = 1;
        PersonalityChangeChance = 0.08;
        PersonalityMinimumSecondsBetweenChanges = 7200.0;

        EnableCombatStressShockThoughts = 1;
        EnableCombatStressDamageEventThoughts = 1;
        EnableDamageReactionThoughts = 1;
        EnableZombieHitMessages = 1;
        EnablePlayerMeleeHitMessages = 1;
        EnableGunshotHitMessages = 1;
        EnableExplosionHitMessages = 1;
        EnableHeavyHitMessages = 1;
        EnableBleedingStartedMessages = 1;
        EnableBleedingWorseMessages = 1;
        EnableBleedingStoppedMessages = 1;
        CombatStressCooldownSeconds = 20.0;
        EnableBleedingReactionThoughts = 1;
        HeavyHitHealthDamage_Min = 25.0;
        HeavyHitBloodDamage_Min = 300.0;
        HeavyHitShockDamage_Min = 35.0;

        RainThought_Min = 0.35;
        LightRainThought_Min = 0.15;
        HeavyRainThought_Min = 0.65;
        FogThought_Min = 0.45;
        WindThought_Min = 8.0;
        OvercastThought_Min = 0.65;
        StormRain_Min = 0.65;
        StormWind_Min = 10.0;
        StormOvercast_Min = 0.90;
        EnableClearWeatherMessages = 1;
        EnableOvercastWeatherMessages = 1;
        EnableLightRainMessages = 1;
        EnableHeavyRainMessages = 1;
        EnableFogWeatherMessages = 1;
        EnableWindWeatherMessages = 1;
        EnableStormWeatherMessages = 1;
        WeatherThoughtCooldownSeconds = 240.0;
        WeatherThoughtChance = 0.35;

        EnableTimeOfDayThoughts = 1;
        TimeOfDayThoughtCooldownSeconds = 300.0;
        TimeOfDayThoughtChance = 0.35;
        EnableDawnMessages = 1;
        EnableMorningMessages = 1;
        EnableNoonMessages = 1;
        EnableAfternoonMessages = 1;
        EnableDuskMessages = 1;
        EnableNightMessages = 1;
        EnableMidnightMessages = 1;
        EnableEarlyMorningMessages = 1;
        DawnStartHour = 5.0;
        MorningStartHour = 7.0;
        NoonStartHour = 11.0;
        AfternoonStartHour = 13.0;
        DuskStartHour = 18.0;
        NightStartHour = 20.0;
        MidnightStartHour = 0.0;
        EarlyMorningStartHour = 3.0;

        ScanEquippedItemsForDamagedThoughts = 1;


        EnableLocationThoughts = 1;
        LocationThoughtCooldownSeconds = 240.0;
        LocationThoughtChance = 0.35;
        LocationUseCustomZones = 1;
        LocationUseFallbackDetection = 1;
        LocationCoastZMax = 3500.0;
        LocationWildernessScanRadius = 80.0;
        LocationWildernessMaxObjects = 8;

        EnablePlayerMemoryThoughts = 1;
        PlayerMemoryThoughtCooldownSeconds = 240.0;
        PlayerMemoryThoughtChance = 0.30;
        PlayerMemoryDurationSeconds = 600.0;

        EnableStealthNoiseThoughts = 1;
        StealthNoiseThoughtCooldownSeconds = 180.0;
        StealthNoiseThoughtChance = 0.35;
        StealthNoiseInfectedRadius = 35.0;
        StealthNoiseRunSpeedThreshold = 3.2;

        EnableShelterThoughts = 1;
        ShelterThoughtCooldownSeconds = 300.0;
        ShelterThoughtChance = 0.30;
        ShelterScanRadius = 14.0;
        ShelterNearbyBuildingCountRequired = 1;

        EnableRecentMessageBlocker = 1;
        RecentMessageMemoryCount = 12;
        RecentMessageBlockSeconds = 900.0;

        EnableMentalStateThoughts = 1;
        MentalStateThoughtCooldownSeconds = 300.0;
        MentalStateThoughtChance = 0.25;
        MentalStateCriticalHealthMax = 30.0;
        MentalStateLowBloodMax = 3500.0;
        MentalStateLowFoodMax = 500.0;
        MentalStateLowWaterMax = 500.0;

        EnableCustomThoughtZones = 1;
        CustomThoughtZoneDefaultCooldownSeconds = 600.0;
        CustomThoughtZoneDefaultChance = 0.35;

        EnableSocialGroupThoughts = 1;
        SocialGroupThoughtCooldownSeconds = 240.0;
        SocialGroupThoughtChance = 0.35;
        SocialNearbyPlayerRadius = 45.0;
        SocialFriendlyTimeRequiredSeconds = 300.0;
        SocialMemoryDurationSeconds = 900.0;
        LoneWolfNoPlayerSeenSeconds = 10800.0;
        EnableTeammateShotMessages = 1;
        EnableTeammateDownMessages = 1;
        EnableLoneWolfMessages = 1;
        EnableFriendlyNearbyMessages = 1;

        EnableSanityCreep = 1;
        SanityThoughtCooldownSeconds = 300.0;
        SanityThoughtChance = 0.30;
        StartingSanity = 100.0;
        MinimumSanity = 0.0;
        SanityLossSkinHuman = 18.0;
        SanityLossEatHumanMeat = 25.0;
        SanityLossKillRestrainedPlayer = 35.0;
        SanityRegenPerMinute = 0.0;
        SanityUneasyThreshold = 70.0;
        SanityUnhingedThreshold = 35.0;
        SanityPsychoticThreshold = 15.0;
        EnableSanityUneasyMessages = 1;
        EnableSanityUnhingedMessages = 1;
        EnableSanityPsychoticMessages = 1;
        EnableCannibalismCreepMessages = 1;

        EnableAdminReload = 1;
        AdminReloadCommand = "!streload";


        InfectedFarRadius = 40.0;
        InfectedCloseRadius = 25.0;
        InfectedVeryCloseRadius = 10.0;
        InfectedSurroundedCount = 4;

        UseNotificationSystem = 0;
        UseLocalChatBox = 1;

        EnableActionThoughts = 1;
        EnableEatingThoughts = 1;
        EnableDrinkingThoughts = 1;
        EnableUnjamThoughts = 1;
        EnableSkinningThoughts = 1;
        EnableBandagingThoughts = 1;
        EnableFireStartingThoughts = 1;
        EnableCookingThoughts = 1;
        EnableFishingThoughts = 1;
        EnableRepairThoughts = 1;
        EnableExtendedVanillaActionMessages = 1;

        ActionThoughtCooldownSeconds = 30.0;
        OpenCloseActionCooldownSeconds = 20.0;
        DuplicateImmediateActionCooldownSeconds = 0.75;
        AllowActionThoughtsDuringCombat = 1;

        DebugMode = 0;
        EnableDebugFileLog = 1;
        DebugLogToRPT = 1;
        DebugLogFileName = "SurvivorThoughts_Debug.log";
        ClearDebugLogOnServerStart = 1;

        EnableConfigurableStatThresholds = 1;

        EnableEnergyStage1Messages = 0;
        EnergyStage1_Min = 4000.0;
        EnergyStage1_Max = 5000.0;
        EnableEnergyStage2Messages = 1;
        EnergyStage2_Min = 3000.0;
        EnergyStage2_Max = 3999.0;
        EnableEnergyStage3Messages = 1;
        EnergyStage3_Min = 1000.0;
        EnergyStage3_Max = 2999.0;
        EnableEnergyStage4Messages = 1;
        EnergyStage4_Min = 0.0;
        EnergyStage4_Max = 999.0;

        EnableWaterStage1Messages = 0;
        WaterStage1_Min = 4000.0;
        WaterStage1_Max = 5000.0;
        EnableWaterStage2Messages = 1;
        WaterStage2_Min = 3000.0;
        WaterStage2_Max = 3999.0;
        EnableWaterStage3Messages = 1;
        WaterStage3_Min = 1000.0;
        WaterStage3_Max = 2999.0;
        EnableWaterStage4Messages = 1;
        WaterStage4_Min = 0.0;
        WaterStage4_Max = 999.0;

        EnableBloodStage1Messages = 0;
        BloodStage1_Min = 4500.0;
        BloodStage1_Max = 5000.0;
        EnableBloodStage2Messages = 1;
        BloodStage2_Min = 3500.0;
        BloodStage2_Max = 4499.0;
        EnableBloodStage3Messages = 1;
        BloodStage3_Min = 2500.0;
        BloodStage3_Max = 3499.0;
        EnableBloodStage4Messages = 1;
        BloodStage4_Min = 0.0;
        BloodStage4_Max = 2499.0;

        EnableShockStage1Messages = 0;
        ShockStage1_Min = 75.0;
        ShockStage1_Max = 100.0;
        EnableShockStage2Messages = 1;
        ShockStage2_Min = 50.0;
        ShockStage2_Max = 74.0;
        EnableShockStage3Messages = 1;
        ShockStage3_Min = 25.0;
        ShockStage3_Max = 49.0;
        EnableShockStage4Messages = 1;
        ShockStage4_Min = 0.0;
        ShockStage4_Max = 24.0;

        EnableCombinedThoughts = 1;
        MaxCombinedThoughtParts = 3;
        CombinedThoughtChance = 0.65;
        if (UseExtremeSurvivalMessagesAtStateCount <= 0)
            UseExtremeSurvivalMessagesAtStateCount = 4;

        if (UseCriticalSurvivalMessagesAtStateCount <= 0)
            UseCriticalSurvivalMessagesAtStateCount = 5;

        if (WeatherThoughtCooldownSeconds <= 0.0)
            WeatherThoughtCooldownSeconds = 240.0;

        if (WeatherThoughtChance <= 0.0)
            WeatherThoughtChance = 0.35;

        if (LightRainThought_Min <= 0.0)
            LightRainThought_Min = 0.15;

        if (HeavyRainThought_Min <= 0.0)
            HeavyRainThought_Min = 0.65;

        if (OvercastThought_Min <= 0.0)
            OvercastThought_Min = 0.65;

        if (!WeatherClearMessages || WeatherClearMessages.Count() == 0)
        {
            WeatherClearMessages = new array<string>;
            WeatherClearMessages.Insert("Clear skies make me feel exposed.");
            WeatherClearMessages.Insert("Good visibility cuts both ways.");
            WeatherClearMessages.Insert("At least the weather is not trying to kill me.");
            WeatherClearMessages.Insert("The sky is open, and so is every sightline.");
        }

        if (!WeatherOvercastMessages || WeatherOvercastMessages.Count() == 0)
        {
            WeatherOvercastMessages = new array<string>;
            WeatherOvercastMessages.Insert("The clouds make everything feel heavier.");
            WeatherOvercastMessages.Insert("Grey skies, grey thoughts.");
            WeatherOvercastMessages.Insert("This weather feels like trouble settling in.");
            WeatherOvercastMessages.Insert("The light is flat. The world feels dead.");
        }

        if (!WeatherLightRainMessages || WeatherLightRainMessages.Count() == 0)
        {
            WeatherLightRainMessages = new array<string>;
            WeatherLightRainMessages.Insert("A little rain is enough to make everything miserable.");
            WeatherLightRainMessages.Insert("This drizzle will soak in if I ignore it.");
            WeatherLightRainMessages.Insert("The rain is light, but it still gives me away.");
            WeatherLightRainMessages.Insert("Wet roads, wet clothes, bad luck.");
        }

        if (!WeatherHeavyRainMessages || WeatherHeavyRainMessages.Count() == 0)
        {
            WeatherHeavyRainMessages = new array<string>;
            WeatherHeavyRainMessages.Insert("This rain is hammering everything.");
            WeatherHeavyRainMessages.Insert("I can barely hear through the downpour.");
            WeatherHeavyRainMessages.Insert("Heavy rain hides movement, including mine.");
            WeatherHeavyRainMessages.Insert("I need shelter before this soaks me through.");
        }

        if (!WeatherRainMessages || WeatherRainMessages.Count() == 0)
        {
            WeatherRainMessages = new array<string>;
            WeatherRainMessages.Insert("This rain is soaking through everything.");
            WeatherRainMessages.Insert("I need to get dry before the cold settles in.");
            WeatherRainMessages.Insert("Rain hides sound, but it ruins everything else.");
            WeatherRainMessages.Insert("Wet clothes will make the next few hours worse.");
        }

        if (!WeatherFogMessages || WeatherFogMessages.Count() == 0)
        {
            WeatherFogMessages = new array<string>;
            WeatherFogMessages.Insert("The fog is hiding too much.");
            WeatherFogMessages.Insert("I cannot see far enough to feel safe.");
            WeatherFogMessages.Insert("Everything sounds closer in this fog.");
            WeatherFogMessages.Insert("I should move carefully until this clears.");
        }

        if (!WeatherStormMessages || WeatherStormMessages.Count() == 0)
        {
            WeatherStormMessages = new array<string>;
            WeatherStormMessages.Insert("The weather is turning ugly.");
            WeatherStormMessages.Insert("This storm will cover my noise, but it could get me killed.");
            WeatherStormMessages.Insert("I need shelter before this gets worse.");
            WeatherStormMessages.Insert("Bad weather makes every decision heavier.");
        }

        if (!WeatherWindMessages || WeatherWindMessages.Count() == 0)
        {
            WeatherWindMessages = new array<string>;
            WeatherWindMessages.Insert("The wind makes it hard to hear anything moving.");
            WeatherWindMessages.Insert("Every gust sounds like footsteps.");
            WeatherWindMessages.Insert("The wind is cutting through me.");
            WeatherWindMessages.Insert("I should not trust my ears in this weather.");
        }

        if (TimeOfDayThoughtCooldownSeconds <= 0.0)
            TimeOfDayThoughtCooldownSeconds = 300.0;

        if (TimeOfDayThoughtChance <= 0.0)
            TimeOfDayThoughtChance = 0.35;

        if (DawnStartHour <= 0.0)
            DawnStartHour = 5.0;

        if (MorningStartHour <= 0.0)
            MorningStartHour = 7.0;

        if (NoonStartHour <= 0.0)
            NoonStartHour = 11.0;

        if (AfternoonStartHour <= 0.0)
            AfternoonStartHour = 13.0;

        if (DuskStartHour <= 0.0)
            DuskStartHour = 18.0;

        if (NightStartHour <= 0.0)
            NightStartHour = 20.0;

        if (EarlyMorningStartHour <= 0.0)
            EarlyMorningStartHour = 3.0;

        if (!DawnMessages || DawnMessages.Count() == 0)
        {
            DawnMessages = new array<string>;
            DawnMessages.Insert("The light is coming back. I made it through the dark.");
            DawnMessages.Insert("Dawn makes everything look quieter than it is.");
            DawnMessages.Insert("First light means movement. I will not be the only one awake.");
            DawnMessages.Insert("The morning cold is still in my bones.");
        }

        if (!MorningMessages || MorningMessages.Count() == 0)
        {
            MorningMessages = new array<string>;
            MorningMessages.Insert("Morning means supplies, footsteps, and bad decisions.");
            MorningMessages.Insert("The day is young. So are the risks.");
            MorningMessages.Insert("Light makes travel easier, but hiding harder.");
            MorningMessages.Insert("I should move while I can still see.");
        }

        if (!NoonMessages || NoonMessages.Count() == 0)
        {
            NoonMessages = new array<string>;
            NoonMessages.Insert("The sun is high. Shadows are short.");
            NoonMessages.Insert("Noon makes every open field feel wider.");
            NoonMessages.Insert("Hard daylight leaves fewer places to hide.");
            NoonMessages.Insert("This is a good time to move, if no one is watching.");
        }

        if (!AfternoonMessages || AfternoonMessages.Count() == 0)
        {
            AfternoonMessages = new array<string>;
            AfternoonMessages.Insert("The day is slipping away.");
            AfternoonMessages.Insert("Afternoon always feels shorter than it should.");
            AfternoonMessages.Insert("I need to think about where I will be when the light fades.");
            AfternoonMessages.Insert("There is still time to search, but not much.");
        }

        if (!DuskMessages || DuskMessages.Count() == 0)
        {
            DuskMessages = new array<string>;
            DuskMessages.Insert("Daylight is bleeding out.");
            DuskMessages.Insert("Dusk is when mistakes start costing more.");
            DuskMessages.Insert("I need to decide where I am sleeping.");
            DuskMessages.Insert("The world is getting harder to read.");
        }

        if (!NightMessages || NightMessages.Count() == 0)
        {
            NightMessages = new array<string>;
            NightMessages.Insert("The dark makes every sound feel closer.");
            NightMessages.Insert("Night belongs to anyone patient enough to wait.");
            NightMessages.Insert("I should not move without a reason.");
            NightMessages.Insert("Every light in the dark is a confession.");
        }

        if (!MidnightMessages || MidnightMessages.Count() == 0)
        {
            MidnightMessages = new array<string>;
            MidnightMessages.Insert("This is the hour people disappear.");
            MidnightMessages.Insert("Midnight makes the world feel empty, but it never is.");
            MidnightMessages.Insert("The dark feels deeper now.");
            MidnightMessages.Insert("I need to stay quiet until the night starts to break.");
        }

        if (!EarlyMorningMessages || EarlyMorningMessages.Count() == 0)
        {
            EarlyMorningMessages = new array<string>;
            EarlyMorningMessages.Insert("The last part of night always feels the longest.");
            EarlyMorningMessages.Insert("Morning is close, but close does not mean safe.");
            EarlyMorningMessages.Insert("Everything is cold, still, and waiting.");
            EarlyMorningMessages.Insert("I just need to make it to first light.");
        }

        if (!ItemBadlyDamagedMessages || ItemBadlyDamagedMessages.Count() == 0)
        {
            ItemBadlyDamagedMessages = new array<string>;
            ItemBadlyDamagedMessages.Insert("This gear will not last much longer.");
            ItemBadlyDamagedMessages.Insert("I should repair this before it fails me.");
            ItemBadlyDamagedMessages.Insert("Everything I own is falling apart.");
            ItemBadlyDamagedMessages.Insert("This could break when I need it most.");
        }

        if (!ItemWeaponDamagedMessages || ItemWeaponDamagedMessages.Count() == 0)
        {
            ItemWeaponDamagedMessages = new array<string>;
            ItemWeaponDamagedMessages.Insert("This weapon needs maintenance.");
            ItemWeaponDamagedMessages.Insert("I do not trust this gun in its current state.");
            ItemWeaponDamagedMessages.Insert("A bad weapon gets people killed.");
            ItemWeaponDamagedMessages.Insert("This thing might fail when I need it most.");
        }

        if (!ItemShoesDamagedMessages || ItemShoesDamagedMessages.Count() == 0)
        {
            ItemShoesDamagedMessages = new array<string>;
            ItemShoesDamagedMessages.Insert("My boots are falling apart.");
            ItemShoesDamagedMessages.Insert("My feet are going to suffer if I do not fix these.");
            ItemShoesDamagedMessages.Insert("Bad shoes will slow me down.");
            ItemShoesDamagedMessages.Insert("I need to repair these before they give out.");
        }

        if (!ItemClothingDamagedMessages || ItemClothingDamagedMessages.Count() == 0)
        {
            ItemClothingDamagedMessages = new array<string>;
            ItemClothingDamagedMessages.Insert("My clothes are barely holding together.");
            ItemClothingDamagedMessages.Insert("This clothing will not protect me much longer.");
            ItemClothingDamagedMessages.Insert("The next fight could ruin what is left of this.");
            ItemClothingDamagedMessages.Insert("I need a sewing kit before this falls apart.");
        }

        if (!ItemBackpackDamagedMessages || ItemBackpackDamagedMessages.Count() == 0)
        {
            ItemBackpackDamagedMessages = new array<string>;
            ItemBackpackDamagedMessages.Insert("My backpack is barely holding together.");
            ItemBackpackDamagedMessages.Insert("If this pack gives out, I lose everything.");
            ItemBackpackDamagedMessages.Insert("I should repair this bag before moving on.");
            ItemBackpackDamagedMessages.Insert("This pack has seen better days.");
        }

        if (!ItemVestDamagedMessages || ItemVestDamagedMessages.Count() == 0)
        {
            ItemVestDamagedMessages = new array<string>;
            ItemVestDamagedMessages.Insert("My vest is barely holding together.");
            ItemVestDamagedMessages.Insert("This vest will not stop much in this condition.");
            ItemVestDamagedMessages.Insert("I should repair this vest before I trust it.");
            ItemVestDamagedMessages.Insert("Bad armor gives false confidence.");
        }

        if (!ItemHeadgearDamagedMessages || ItemHeadgearDamagedMessages.Count() == 0)
        {
            ItemHeadgearDamagedMessages = new array<string>;
            ItemHeadgearDamagedMessages.Insert("My headgear is in bad shape.");
            ItemHeadgearDamagedMessages.Insert("This helmet has taken too much abuse.");
            ItemHeadgearDamagedMessages.Insert("I do not trust this on my head anymore.");
            ItemHeadgearDamagedMessages.Insert("One more hit could finish this helmet.");
        }

        if (!ItemGlovesDamagedMessages || ItemGlovesDamagedMessages.Count() == 0)
        {
            ItemGlovesDamagedMessages = new array<string>;
            ItemGlovesDamagedMessages.Insert("My gloves are falling apart.");
            ItemGlovesDamagedMessages.Insert("Cold hands and torn gloves are a bad mix.");
            ItemGlovesDamagedMessages.Insert("I need to fix these gloves before they give out.");
            ItemGlovesDamagedMessages.Insert("My hands need better protection than this.");
        }

        if (!ItemMaskDamagedMessages || ItemMaskDamagedMessages.Count() == 0)
        {
            ItemMaskDamagedMessages = new array<string>;
            ItemMaskDamagedMessages.Insert("My face covering is almost ruined.");
            ItemMaskDamagedMessages.Insert("This mask will not protect me much longer.");
            ItemMaskDamagedMessages.Insert("I should replace this before I need it.");
            ItemMaskDamagedMessages.Insert("Breathing through torn gear feels wrong.");
        }

        if (!ItemBeltDamagedMessages || ItemBeltDamagedMessages.Count() == 0)
        {
            ItemBeltDamagedMessages = new array<string>;
            ItemBeltDamagedMessages.Insert("This belt is barely holding my gear together.");
            ItemBeltDamagedMessages.Insert("If this belt fails, I lose more than cloth.");
            ItemBeltDamagedMessages.Insert("I should repair this before it gives out.");
            ItemBeltDamagedMessages.Insert("Everything hanging from this feels less secure.");
        }

        if (!CombatStressMessages || CombatStressMessages.Count() == 0)
        {
            CombatStressMessages = new array<string>;
            CombatStressMessages.Insert("That shook me.");
            CombatStressMessages.Insert("Keep moving. Find cover.");
            CombatStressMessages.Insert("I need a second to steady myself.");
            CombatStressMessages.Insert("Do not panic.");
            CombatStressMessages.Insert("My hands are not as steady as they should be.");
        }

        if (!CombatHitMessages || CombatHitMessages.Count() == 0)
        {
            CombatHitMessages = new array<string>;
            CombatHitMessages.Insert("That hit hard.");
            CombatHitMessages.Insert("I need cover now.");
            CombatHitMessages.Insert("Move. Do not freeze.");
            CombatHitMessages.Insert("I cannot take another hit like that.");
            CombatHitMessages.Insert("Someone has me dialed in.");
            CombatHitMessages.Insert("Stay low. Stay alive.");
        }

        
        if (!ZombieHitMessages || ZombieHitMessages.Count() == 0)
        {
            ZombieHitMessages = new array<string>;
            ZombieHitMessages.Insert("An infected hit me.");
            ZombieHitMessages.Insert("It got too close.");
            ZombieHitMessages.Insert("I need to keep distance from them.");
            ZombieHitMessages.Insert("That infected nearly tore into me.");
            ZombieHitMessages.Insert("I should not let them surround me.");
            ZombieHitMessages.Insert("Back up. Do not let them grab me.");
            ZombieHitMessages.Insert("Their hands are quicker than they look.");
        }

        if (!PlayerMeleeHitMessages || PlayerMeleeHitMessages.Count() == 0)
        {
            PlayerMeleeHitMessages = new array<string>;
            PlayerMeleeHitMessages.Insert("Someone hit me.");
            PlayerMeleeHitMessages.Insert("That was too close.");
            PlayerMeleeHitMessages.Insert("I need space before they swing again.");
            PlayerMeleeHitMessages.Insert("They are on top of me.");
            PlayerMeleeHitMessages.Insert("I need to move.");
            PlayerMeleeHitMessages.Insert("Keep distance. Do not let them control the fight.");
        }

        if (!GunshotHitMessages || GunshotHitMessages.Count() == 0)
        {
            GunshotHitMessages = new array<string>;
            GunshotHitMessages.Insert("I have been shot.");
            GunshotHitMessages.Insert("That round hit me.");
            GunshotHitMessages.Insert("I need cover now.");
            GunshotHitMessages.Insert("Someone has eyes on me.");
            GunshotHitMessages.Insert("I cannot stay in the open.");
            GunshotHitMessages.Insert("Find cover. Stop the bleeding. Stay alive.");
            GunshotHitMessages.Insert("The shot came from somewhere close enough.");
        }

        if (!ExplosionHitMessages || ExplosionHitMessages.Count() == 0)
        {
            ExplosionHitMessages = new array<string>;
            ExplosionHitMessages.Insert("The blast hit me hard.");
            ExplosionHitMessages.Insert("My ears are ringing.");
            ExplosionHitMessages.Insert("I need to get away from here.");
            ExplosionHitMessages.Insert("Everything is spinning after that explosion.");
            ExplosionHitMessages.Insert("That nearly killed me.");
            ExplosionHitMessages.Insert("Move before another one lands.");
        }

        if (!HeavyHitMessages || HeavyHitMessages.Count() == 0)
        {
            HeavyHitMessages = new array<string>;
            HeavyHitMessages.Insert("That hit hard.");
            HeavyHitMessages.Insert("I need to recover.");
            HeavyHitMessages.Insert("My body is screaming.");
            HeavyHitMessages.Insert("I cannot take another hit like that.");
            HeavyHitMessages.Insert("I need to get out of this fight.");
            HeavyHitMessages.Insert("Everything hurts. Move anyway.");
            HeavyHitMessages.Insert("I need cover before my legs give out.");
        }

        if (!BleedingStartedMessages || BleedingStartedMessages.Count() == 0)
        {
            BleedingStartedMessages = new array<string>;
            BleedingStartedMessages.Insert("I am bleeding.");
            BleedingStartedMessages.Insert("That opened me up.");
            BleedingStartedMessages.Insert("Blood is running down my body.");
            BleedingStartedMessages.Insert("I need to bandage this now.");
            BleedingStartedMessages.Insert("This wound is not going to close itself.");
            BleedingStartedMessages.Insert("I need pressure on this wound.");
        }

        if (!BleedingWorseMessages || BleedingWorseMessages.Count() == 0)
        {
            BleedingWorseMessages = new array<string>;
            BleedingWorseMessages.Insert("I am bleeding from more than one wound.");
            BleedingWorseMessages.Insert("There is too much blood.");
            BleedingWorseMessages.Insert("I need to stop the bleeding before I pass out.");
            BleedingWorseMessages.Insert("I cannot keep losing blood like this.");
            BleedingWorseMessages.Insert("This is getting bad fast.");
            BleedingWorseMessages.Insert("Too many wounds. I need to deal with this now.");
        }

        if (!BleedingStoppedMessages || BleedingStoppedMessages.Count() == 0)
        {
            BleedingStoppedMessages = new array<string>;
            BleedingStoppedMessages.Insert("The bleeding has stopped.");
            BleedingStoppedMessages.Insert("That should hold for now.");
            BleedingStoppedMessages.Insert("I need to keep pressure off this wound.");
            BleedingStoppedMessages.Insert("That was too close.");
            BleedingStoppedMessages.Insert("At least I am not bleeding anymore.");
            BleedingStoppedMessages.Insert("I bought myself a little more time.");
        }

if (!CombatShockMessages || CombatShockMessages.Count() == 0)
        {
            CombatShockMessages = new array<string>;
            CombatShockMessages.Insert("My hands are not steady.");
            CombatShockMessages.Insert("I need a second to get myself together.");
            CombatShockMessages.Insert("Everything feels too loud.");
            CombatShockMessages.Insert("I can feel myself slipping.");
            CombatShockMessages.Insert("Breathe. Think. Move.");
        }

        if (!ContaminatedZoneMessages || ContaminatedZoneMessages.Count() == 0)
        {
            ContaminatedZoneMessages = new array<string>;
            ContaminatedZoneMessages.Insert("The air is wrong here.");
            ContaminatedZoneMessages.Insert("I need to check my filters.");
            ContaminatedZoneMessages.Insert("This suit is the only thing keeping me alive.");
            ContaminatedZoneMessages.Insert("I should not stay in this gas any longer.");
        }

        if (!NearbyCorpseMessages || NearbyCorpseMessages.Count() == 0)
        {
            NearbyCorpseMessages = new array<string>;
            NearbyCorpseMessages.Insert("Someone died here recently.");
            NearbyCorpseMessages.Insert("This was not long ago.");
            NearbyCorpseMessages.Insert("I should not stay near the body.");
            NearbyCorpseMessages.Insert("Where there is one corpse, there may be another.");
        }


        if (!NearbyPlayerCorpseMessages || NearbyPlayerCorpseMessages.Count() == 0)
        {
            NearbyPlayerCorpseMessages = new array<string>;
            NearbyPlayerCorpseMessages.Insert("That was a survivor.");
            NearbyPlayerCorpseMessages.Insert("Someone else did not make it.");
            NearbyPlayerCorpseMessages.Insert("This body has a story I will never hear.");
            NearbyPlayerCorpseMessages.Insert("If they died here, I can too.");
        }

        if (!NearbyInfectedCorpseMessages || NearbyInfectedCorpseMessages.Count() == 0)
        {
            NearbyInfectedCorpseMessages = new array<string>;
            NearbyInfectedCorpseMessages.Insert("One less infected, but the smell remains.");
            NearbyInfectedCorpseMessages.Insert("This thing was moving not long ago.");
            NearbyInfectedCorpseMessages.Insert("The dead infected still make this place feel wrong.");
            NearbyInfectedCorpseMessages.Insert("I should not linger near rotten bodies.");
        }

        if (!NearbyAnimalCorpseMessages || NearbyAnimalCorpseMessages.Count() == 0)
        {
            NearbyAnimalCorpseMessages = new array<string>;
            NearbyAnimalCorpseMessages.Insert("Something fed here, or someone hunted here.");
            NearbyAnimalCorpseMessages.Insert("An animal died nearby. That can mean food or danger.");
            NearbyAnimalCorpseMessages.Insert("Fresh meat brings more than survivors.");
            NearbyAnimalCorpseMessages.Insert("This carcass might draw attention.");
        }

        if (!PersonalityPracticalMessages || PersonalityPracticalMessages.Count() == 0)
        {
            PersonalityPracticalMessages = new array<string>;
            PersonalityPracticalMessages.Insert("Prioritise the worst problem first.");
            PersonalityPracticalMessages.Insert("Check supplies, check cover, keep moving.");
            PersonalityPracticalMessages.Insert("Food, water, shelter. In that order.");
        }

        if (!PersonalityScaredMessages || PersonalityScaredMessages.Count() == 0)
        {
            PersonalityScaredMessages = new array<string>;
            PersonalityScaredMessages.Insert("I do not like this place.");
            PersonalityScaredMessages.Insert("Every sound feels too close.");
            PersonalityScaredMessages.Insert("I need to get somewhere safer.");
        }

        if (!PersonalityMilitaryMessages || PersonalityMilitaryMessages.Count() == 0)
        {
            PersonalityMilitaryMessages = new array<string>;
            PersonalityMilitaryMessages.Insert("Assess the area. Move with purpose.");
            PersonalityMilitaryMessages.Insert("Noise discipline. Watch the corners.");
            PersonalityMilitaryMessages.Insert("Supplies first, exposure second, route out third.");
        }

        if (!PersonalityHopelessMessages || PersonalityHopelessMessages.Count() == 0)
        {
            PersonalityHopelessMessages = new array<string>;
            PersonalityHopelessMessages.Insert("Same hunger. Same cold. Keep going.");
            PersonalityHopelessMessages.Insert("Nobody is coming.");
            PersonalityHopelessMessages.Insert("Surviving another day still feels like losing.");
        }

        if (!PersonalityAggressiveMessages || PersonalityAggressiveMessages.Count() == 0)
        {
            PersonalityAggressiveMessages = new array<string>;
            PersonalityAggressiveMessages.Insert("Keep moving. Take what is needed.");
            PersonalityAggressiveMessages.Insert("Hesitation gets people killed.");
            PersonalityAggressiveMessages.Insert("If something blocks the way, deal with it.");
        }

        if (!PersonalityCalmMessages || PersonalityCalmMessages.Count() == 0)
        {
            PersonalityCalmMessages = new array<string>;
            PersonalityCalmMessages.Insert("Breathe. Think. Move.");
            PersonalityCalmMessages.Insert("Panic wastes strength.");
            PersonalityCalmMessages.Insert("One problem at a time.");
        }

        EnsureDefaults();
    
}

    void ST_EnsureStarterMessageDefaults_1()
    {
        if (!TeammateShotMessages)
            TeammateShotMessages = new array<string>;

        if (TeammateShotMessages.Count() == 0)
        {
            TeammateShotMessages.Insert("They are hit. I need to move.");
            TeammateShotMessages.Insert("No, stay with me.");
            TeammateShotMessages.Insert("Someone just found us.");
            TeammateShotMessages.Insert("I cannot let them bleed out here.");
        }

        if (!TeammateDownMessages)
            TeammateDownMessages = new array<string>;

        if (TeammateDownMessages.Count() == 0)
        {
            TeammateDownMessages.Insert("They are gone. I am alone now.");
            TeammateDownMessages.Insert("I should have been faster.");
            TeammateDownMessages.Insert("Their silence feels heavier than the gunshot.");
            TeammateDownMessages.Insert("I have to keep moving, even without them.");
        }

        if (!LoneWolfMessages)
            LoneWolfMessages = new array<string>;

        if (LoneWolfMessages.Count() == 0)
        {
            LoneWolfMessages.Insert("I have not seen anyone friendly in too long.");
            LoneWolfMessages.Insert("The silence is starting to feel normal.");
            LoneWolfMessages.Insert("No voices. No footsteps. Just me.");
            LoneWolfMessages.Insert("Being alone keeps me alive, but it wears me down.");
        }

        if (!FriendlyNearbyMessages)
            FriendlyNearbyMessages = new array<string>;

        if (FriendlyNearbyMessages.Count() == 0)
        {
            FriendlyNearbyMessages.Insert("Another survivor nearby changes everything.");
            FriendlyNearbyMessages.Insert("I need to keep track of them.");
            FriendlyNearbyMessages.Insert("Two people make more noise, but fewer mistakes.");
            FriendlyNearbyMessages.Insert("Trust is useful. Dangerous, but useful.");
        }

        if (!SanityUneasyMessages)
            SanityUneasyMessages = new array<string>;

        if (SanityUneasyMessages.Count() == 0)
        {
            SanityUneasyMessages.Insert("I need to keep my head clear.");
            SanityUneasyMessages.Insert("Something about this is staying with me.");
            SanityUneasyMessages.Insert("My hands will not stop shaking.");
            SanityUneasyMessages.Insert("Breathe. Count supplies. Keep moving.");
        }

        if (!SanityUnhingedMessages)
            SanityUnhingedMessages = new array<string>;

        if (SanityUnhingedMessages.Count() == 0)
        {
            SanityUnhingedMessages.Insert("I keep hearing things that are not there.");
            SanityUnhingedMessages.Insert("Every bad choice feels easier than the last.");
            SanityUnhingedMessages.Insert("I am still in control. I have to be.");
            SanityUnhingedMessages.Insert("The silence is starting to answer back.");
        }

        if (!SanityPsychoticMessages)
            SanityPsychoticMessages = new array<string>;

        if (SanityPsychoticMessages.Count() == 0)
        {
            SanityPsychoticMessages.Insert("The laughing will not stop in my head.");
            SanityPsychoticMessages.Insert("Their faces come back when I close my eyes.");
            SanityPsychoticMessages.Insert("I should be horrified. I am not.");
            SanityPsychoticMessages.Insert("Something in me broke quietly.");
        }

        if (!CannibalismCreepMessages)
            CannibalismCreepMessages = new array<string>;

        if (CannibalismCreepMessages.Count() == 0)
        {
            CannibalismCreepMessages.Insert("That was a person. I know that.");
            CannibalismCreepMessages.Insert("There are hungers that should stay empty.");
            CannibalismCreepMessages.Insert("I crossed something I cannot uncross.");
            CannibalismCreepMessages.Insert("The worst part is that it helped.");
        }

        if (!TrendEnergyFallingMessages)
            TrendEnergyFallingMessages = new array<string>;

        if (TrendEnergyFallingMessages.Count() == 0)
        {
            TrendEnergyFallingMessages.Insert("My stomach is turning against me.");
            TrendEnergyFallingMessages.Insert("I need food before my strength goes.");
            TrendEnergyFallingMessages.Insert("Every step costs more than I have.");
            TrendEnergyFallingMessages.Insert("I cannot run on nothing much longer.");
        }

        if (!TrendWaterFallingMessages)
            TrendWaterFallingMessages = new array<string>;

        if (TrendWaterFallingMessages.Count() == 0)
        {
            TrendWaterFallingMessages.Insert("My mouth is too dry.");
            TrendWaterFallingMessages.Insert("I need water soon.");
            TrendWaterFallingMessages.Insert("Dehydration is starting to slow my thoughts.");
            TrendWaterFallingMessages.Insert("I have to find something safe to drink.");
        }

        if (!TrendBloodFallingMessages)
            TrendBloodFallingMessages = new array<string>;

        if (TrendBloodFallingMessages.Count() == 0)
        {
            TrendBloodFallingMessages.Insert("I am losing blood.");
            TrendBloodFallingMessages.Insert("I need to stop this before it gets worse.");
            TrendBloodFallingMessages.Insert("Warmth is leaving with every drop.");
            TrendBloodFallingMessages.Insert("Pressure first. Panic later.");
        }

        if (!TrendHealthFallingMessages)
            TrendHealthFallingMessages = new array<string>;

        if (TrendHealthFallingMessages.Count() == 0)
        {
            TrendHealthFallingMessages.Insert("This trend health falling is getting to me.");
            TrendHealthFallingMessages.Insert("I need to pay attention to this trend health falling.");
            TrendHealthFallingMessages.Insert("Something about this trend health falling feels wrong.");
            TrendHealthFallingMessages.Insert("I should not ignore this trend health falling.");
        }

        if (!TrendTemperatureWorseningMessages)
            TrendTemperatureWorseningMessages = new array<string>;

        if (TrendTemperatureWorseningMessages.Count() == 0)
        {
            TrendTemperatureWorseningMessages.Insert("This trend temperature worsening is getting to me.");
            TrendTemperatureWorseningMessages.Insert("I need to pay attention to this trend temperature worsening.");
            TrendTemperatureWorseningMessages.Insert("Something about this trend temperature worsening feels wrong.");
            TrendTemperatureWorseningMessages.Insert("I should not ignore this trend temperature worsening.");
        }

        if (!TrendWetnessWorseningMessages)
            TrendWetnessWorseningMessages = new array<string>;

        if (TrendWetnessWorseningMessages.Count() == 0)
        {
            TrendWetnessWorseningMessages.Insert("The weather is wearing me down.");
            TrendWetnessWorseningMessages.Insert("This makes every sound harder to trust.");
            TrendWetnessWorseningMessages.Insert("I need to get out of this weather.");
            TrendWetnessWorseningMessages.Insert("Bad weather hides bad decisions.");
        }

        if (!LongSicknessMessages)
            LongSicknessMessages = new array<string>;

        if (LongSicknessMessages.Count() == 0)
        {
            LongSicknessMessages.Insert("Something is wrong inside me.");
            LongSicknessMessages.Insert("I need medicine before this gets worse.");
            LongSicknessMessages.Insert("My body is fighting and losing ground.");
            LongSicknessMessages.Insert("This sickness is stealing my strength.");
        }

        if (!LongBleedingMessages)
            LongBleedingMessages = new array<string>;

        if (LongBleedingMessages.Count() == 0)
        {
            LongBleedingMessages.Insert("I am losing blood.");
            LongBleedingMessages.Insert("I need to stop this before it gets worse.");
            LongBleedingMessages.Insert("Warmth is leaving with every drop.");
            LongBleedingMessages.Insert("Pressure first. Panic later.");
        }

        if (!StarvingDehydratedMessages)
            StarvingDehydratedMessages = new array<string>;

        if (StarvingDehydratedMessages.Count() == 0)
        {
            StarvingDehydratedMessages.Insert("My stomach is turning against me.");
            StarvingDehydratedMessages.Insert("I need food before my strength goes.");
            StarvingDehydratedMessages.Insert("Every step costs more than I have.");
            StarvingDehydratedMessages.Insert("I cannot run on nothing much longer.");
        }

        if (!StarvingLowBloodMessages)
            StarvingLowBloodMessages = new array<string>;

        if (StarvingLowBloodMessages.Count() == 0)
        {
            StarvingLowBloodMessages.Insert("My stomach is turning against me.");
            StarvingLowBloodMessages.Insert("I need food before my strength goes.");
            StarvingLowBloodMessages.Insert("Every step costs more than I have.");
            StarvingLowBloodMessages.Insert("I cannot run on nothing much longer.");
        }

        if (!DehydratedLowBloodMessages)
            DehydratedLowBloodMessages = new array<string>;

        if (DehydratedLowBloodMessages.Count() == 0)
        {
            DehydratedLowBloodMessages.Insert("My mouth is too dry.");
            DehydratedLowBloodMessages.Insert("I need water soon.");
            DehydratedLowBloodMessages.Insert("Dehydration is starting to slow my thoughts.");
            DehydratedLowBloodMessages.Insert("I have to find something safe to drink.");
        }

        if (!ColdWetMessages)
            ColdWetMessages = new array<string>;

        if (ColdWetMessages.Count() == 0)
        {
            ColdWetMessages.Insert("The cold is getting into my bones.");
            ColdWetMessages.Insert("I need warmth before this gets worse.");
            ColdWetMessages.Insert("My fingers are stiff.");
            ColdWetMessages.Insert("Shelter and heat. That is all that matters.");
        }

        if (!ColdWetNightMessages)
            ColdWetNightMessages = new array<string>;

        if (ColdWetNightMessages.Count() == 0)
        {
            ColdWetNightMessages.Insert("The cold is getting into my bones.");
            ColdWetNightMessages.Insert("I need warmth before this gets worse.");
            ColdWetNightMessages.Insert("My fingers are stiff.");
            ColdWetNightMessages.Insert("Shelter and heat. That is all that matters.");
        }

        if (!ColdWetSickMessages)
            ColdWetSickMessages = new array<string>;

        if (ColdWetSickMessages.Count() == 0)
        {
            ColdWetSickMessages.Insert("The cold is getting into my bones.");
            ColdWetSickMessages.Insert("I need warmth before this gets worse.");
            ColdWetSickMessages.Insert("My fingers are stiff.");
            ColdWetSickMessages.Insert("Shelter and heat. That is all that matters.");
        }

        if (!HotDehydratedMessages)
            HotDehydratedMessages = new array<string>;

        if (HotDehydratedMessages.Count() == 0)
        {
            HotDehydratedMessages.Insert("My mouth is too dry.");
            HotDehydratedMessages.Insert("I need water soon.");
            HotDehydratedMessages.Insert("Dehydration is starting to slow my thoughts.");
            HotDehydratedMessages.Insert("I have to find something safe to drink.");
        }

        if (!HotSickMessages)
            HotSickMessages = new array<string>;

        if (HotSickMessages.Count() == 0)
        {
            HotSickMessages.Insert("The heat is draining me.");
            HotSickMessages.Insert("I need shade or water.");
            HotSickMessages.Insert("My head feels heavy.");
            HotSickMessages.Insert("I am overheating out here.");
        }

        if (!BleedingLowBloodMessages)
            BleedingLowBloodMessages = new array<string>;

        if (BleedingLowBloodMessages.Count() == 0)
        {
            BleedingLowBloodMessages.Insert("I am losing blood.");
            BleedingLowBloodMessages.Insert("I need to stop this before it gets worse.");
            BleedingLowBloodMessages.Insert("Warmth is leaving with every drop.");
            BleedingLowBloodMessages.Insert("Pressure first. Panic later.");
        }

        if (!BleedingShockMessages)
            BleedingShockMessages = new array<string>;

        if (BleedingShockMessages.Count() == 0)
        {
            BleedingShockMessages.Insert("I am losing blood.");
            BleedingShockMessages.Insert("I need to stop this before it gets worse.");
            BleedingShockMessages.Insert("Warmth is leaving with every drop.");
            BleedingShockMessages.Insert("Pressure first. Panic later.");
        }

        if (!GunshotBleedingMessages)
            GunshotBleedingMessages = new array<string>;

        if (GunshotBleedingMessages.Count() == 0)
        {
            GunshotBleedingMessages.Insert("I am losing blood.");
            GunshotBleedingMessages.Insert("I need to stop this before it gets worse.");
            GunshotBleedingMessages.Insert("Warmth is leaving with every drop.");
            GunshotBleedingMessages.Insert("Pressure first. Panic later.");
        }

        if (!ExplosionShockMessages)
            ExplosionShockMessages = new array<string>;

        if (ExplosionShockMessages.Count() == 0)
        {
            ExplosionShockMessages.Insert("That was too close.");
            ExplosionShockMessages.Insert("Move. Breathe. Find cover.");
            ExplosionShockMessages.Insert("My hands are shaking.");
            ExplosionShockMessages.Insert("I need to stay alive for the next few seconds.");
        }

        if (!BrokenLegInfectedMessages)
            BrokenLegInfectedMessages = new array<string>;

        if (BrokenLegInfectedMessages.Count() == 0)
        {
            BrokenLegInfectedMessages.Insert("I cannot move like this.");
            BrokenLegInfectedMessages.Insert("Every step is a mistake.");
            BrokenLegInfectedMessages.Insert("I need cover before something hears me.");
            BrokenLegInfectedMessages.Insert("A broken leg out here can be a death sentence.");
        }

        if (!BrokenLegNightMessages)
            BrokenLegNightMessages = new array<string>;

        if (BrokenLegNightMessages.Count() == 0)
        {
            BrokenLegNightMessages.Insert("The dark makes every sound feel closer.");
            BrokenLegNightMessages.Insert("I cannot see far enough to feel safe.");
            BrokenLegNightMessages.Insert("Night belongs to whoever moves quietly.");
            BrokenLegNightMessages.Insert("I should slow down and listen.");
        }

        if (!LowBloodCorpseMessages)
            LowBloodCorpseMessages = new array<string>;

        if (LowBloodCorpseMessages.Count() == 0)
        {
            LowBloodCorpseMessages.Insert("I am losing blood.");
            LowBloodCorpseMessages.Insert("I need to stop this before it gets worse.");
            LowBloodCorpseMessages.Insert("Warmth is leaving with every drop.");
            LowBloodCorpseMessages.Insert("Pressure first. Panic later.");
        }

        if (!SickContaminatedMessages)
            SickContaminatedMessages = new array<string>;

        if (SickContaminatedMessages.Count() == 0)
        {
            SickContaminatedMessages.Insert("Something is wrong inside me.");
            SickContaminatedMessages.Insert("I need medicine before this gets worse.");
            SickContaminatedMessages.Insert("My body is fighting and losing ground.");
            SickContaminatedMessages.Insert("This sickness is stealing my strength.");
        }

        if (!NightRainMessages)
            NightRainMessages = new array<string>;

        if (NightRainMessages.Count() == 0)
        {
            NightRainMessages.Insert("The weather is wearing me down.");
            NightRainMessages.Insert("This makes every sound harder to trust.");
            NightRainMessages.Insert("I need to get out of this weather.");
            NightRainMessages.Insert("Bad weather hides bad decisions.");
        }

        if (!NightFogMessages)
            NightFogMessages = new array<string>;

        if (NightFogMessages.Count() == 0)
        {
            NightFogMessages.Insert("The weather is wearing me down.");
            NightFogMessages.Insert("This makes every sound harder to trust.");
            NightFogMessages.Insert("I need to get out of this weather.");
            NightFogMessages.Insert("Bad weather hides bad decisions.");
        }

        if (!MilitaryGunshotMessages)
            MilitaryGunshotMessages = new array<string>;

        if (MilitaryGunshotMessages.Count() == 0)
        {
            MilitaryGunshotMessages.Insert("That was too close.");
            MilitaryGunshotMessages.Insert("Move. Breathe. Find cover.");
            MilitaryGunshotMessages.Insert("My hands are shaking.");
            MilitaryGunshotMessages.Insert("I need to stay alive for the next few seconds.");
        }

        if (!MilitaryCorpseMessages)
            MilitaryCorpseMessages = new array<string>;

        if (MilitaryCorpseMessages.Count() == 0)
        {
            MilitaryCorpseMessages.Insert("Someone died here.");
            MilitaryCorpseMessages.Insert("Bodies mean danger came through already.");
            MilitaryCorpseMessages.Insert("I should not stay near this.");
            MilitaryCorpseMessages.Insert("Where there is one corpse, there may be another.");
        }

        if (!LoneWolfNightMessages)
            LoneWolfNightMessages = new array<string>;

        if (LoneWolfNightMessages.Count() == 0)
        {
            LoneWolfNightMessages.Insert("I have not seen anyone friendly in too long.");
            LoneWolfNightMessages.Insert("The silence is starting to feel normal.");
            LoneWolfNightMessages.Insert("No voices. No footsteps. Just me.");
            LoneWolfNightMessages.Insert("Being alone keeps me alive, but it wears me down.");
        }

        if (!LowSanityCannibalismMessages)
            LowSanityCannibalismMessages = new array<string>;

        if (LowSanityCannibalismMessages.Count() == 0)
        {
            LowSanityCannibalismMessages.Insert("I keep hearing things that are not there.");
            LowSanityCannibalismMessages.Insert("Every bad choice feels easier than the last.");
            LowSanityCannibalismMessages.Insert("I am still in control. I have to be.");
            LowSanityCannibalismMessages.Insert("The silence is starting to answer back.");
        }

        if (!LowSanityCorpseMessages)
            LowSanityCorpseMessages = new array<string>;

        if (LowSanityCorpseMessages.Count() == 0)
        {
            LowSanityCorpseMessages.Insert("I keep hearing things that are not there.");
            LowSanityCorpseMessages.Insert("Every bad choice feels easier than the last.");
            LowSanityCorpseMessages.Insert("I am still in control. I have to be.");
            LowSanityCorpseMessages.Insert("The silence is starting to answer back.");
        }

        if (!LowSanityNightMessages)
            LowSanityNightMessages = new array<string>;

        if (LowSanityNightMessages.Count() == 0)
        {
            LowSanityNightMessages.Insert("I keep hearing things that are not there.");
            LowSanityNightMessages.Insert("Every bad choice feels easier than the last.");
            LowSanityNightMessages.Insert("I am still in control. I have to be.");
            LowSanityNightMessages.Insert("The silence is starting to answer back.");
        }

    }

    void ST_EnsureStarterMessageDefaults_2()
    {
        if (!CompanionDeadLowSanityMessages)
            CompanionDeadLowSanityMessages = new array<string>;

        if (CompanionDeadLowSanityMessages.Count() == 0)
        {
            CompanionDeadLowSanityMessages.Insert("They are gone. I am alone now.");
            CompanionDeadLowSanityMessages.Insert("I should have been faster.");
            CompanionDeadLowSanityMessages.Insert("Their silence feels heavier than the gunshot.");
            CompanionDeadLowSanityMessages.Insert("I have to keep moving, even without them.");
        }

        if (!BleedingRecoveryMessages)
            BleedingRecoveryMessages = new array<string>;

        if (BleedingRecoveryMessages.Count() == 0)
        {
            BleedingRecoveryMessages.Insert("I am losing blood.");
            BleedingRecoveryMessages.Insert("I need to stop this before it gets worse.");
            BleedingRecoveryMessages.Insert("Warmth is leaving with every drop.");
            BleedingRecoveryMessages.Insert("Pressure first. Panic later.");
        }

        if (!HealthStableRecoveryMessages)
            HealthStableRecoveryMessages = new array<string>;

        if (HealthStableRecoveryMessages.Count() == 0)
        {
            HealthStableRecoveryMessages.Insert("I am not safe, but I am still here.");
            HealthStableRecoveryMessages.Insert("That could have ended worse.");
            HealthStableRecoveryMessages.Insert("My breathing is starting to settle.");
            HealthStableRecoveryMessages.Insert("One crisis is over. The next one can wait.");
        }

        if (!FoodRecoveryMessages)
            FoodRecoveryMessages = new array<string>;

        if (FoodRecoveryMessages.Count() == 0)
        {
            FoodRecoveryMessages.Insert("My stomach is turning against me.");
            FoodRecoveryMessages.Insert("I need food before my strength goes.");
            FoodRecoveryMessages.Insert("Every step costs more than I have.");
            FoodRecoveryMessages.Insert("I cannot run on nothing much longer.");
        }

        if (!WaterRecoveryMessages)
            WaterRecoveryMessages = new array<string>;

        if (WaterRecoveryMessages.Count() == 0)
        {
            WaterRecoveryMessages.Insert("I am not safe, but I am still here.");
            WaterRecoveryMessages.Insert("That could have ended worse.");
            WaterRecoveryMessages.Insert("My breathing is starting to settle.");
            WaterRecoveryMessages.Insert("One crisis is over. The next one can wait.");
        }

        if (!WarmedUpMessages)
            WarmedUpMessages = new array<string>;

        if (WarmedUpMessages.Count() == 0)
        {
            WarmedUpMessages.Insert("The cold is getting into my bones.");
            WarmedUpMessages.Insert("I need warmth before this gets worse.");
            WarmedUpMessages.Insert("My fingers are stiff.");
            WarmedUpMessages.Insert("Shelter and heat. That is all that matters.");
        }

        if (!CooledDownMessages)
            CooledDownMessages = new array<string>;

        if (CooledDownMessages.Count() == 0)
        {
            CooledDownMessages.Insert("The heat is draining me.");
            CooledDownMessages.Insert("I need shade or water.");
            CooledDownMessages.Insert("My head feels heavy.");
            CooledDownMessages.Insert("I am overheating out here.");
        }

        if (!DryingOffMessages)
            DryingOffMessages = new array<string>;

        if (DryingOffMessages.Count() == 0)
        {
            DryingOffMessages.Insert("This drying off is getting to me.");
            DryingOffMessages.Insert("I need to pay attention to this drying off.");
            DryingOffMessages.Insert("Something about this drying off feels wrong.");
            DryingOffMessages.Insert("I should not ignore this drying off.");
        }

        if (!LeftContaminatedZoneMessages)
            LeftContaminatedZoneMessages = new array<string>;

        if (LeftContaminatedZoneMessages.Count() == 0)
        {
            LeftContaminatedZoneMessages.Insert("The air is wrong here.");
            LeftContaminatedZoneMessages.Insert("I need to check my protection.");
            LeftContaminatedZoneMessages.Insert("This place is not safe to breathe.");
            LeftContaminatedZoneMessages.Insert("I should not stay in this contamination.");
        }

        if (!EscapedInfectedMessages)
            EscapedInfectedMessages = new array<string>;

        if (EscapedInfectedMessages.Count() == 0)
        {
            EscapedInfectedMessages.Insert("Infected are too close.");
            EscapedInfectedMessages.Insert("I need to move quietly.");
            EscapedInfectedMessages.Insert("One wrong noise and they will be on me.");
            EscapedInfectedMessages.Insert("I can hear them nearby.");
        }

        if (!DawnSurvivalMessages)
            DawnSurvivalMessages = new array<string>;

        if (DawnSurvivalMessages.Count() == 0)
        {
            DawnSurvivalMessages.Insert("I am not safe, but I am still here.");
            DawnSurvivalMessages.Insert("That could have ended worse.");
            DawnSurvivalMessages.Insert("My breathing is starting to settle.");
            DawnSurvivalMessages.Insert("One crisis is over. The next one can wait.");
        }

        if (!ShelterFromStormMessages)
            ShelterFromStormMessages = new array<string>;

        if (ShelterFromStormMessages.Count() == 0)
        {
            ShelterFromStormMessages.Insert("The weather is wearing me down.");
            ShelterFromStormMessages.Insert("This makes every sound harder to trust.");
            ShelterFromStormMessages.Insert("I need to get out of this weather.");
            ShelterFromStormMessages.Insert("Bad weather hides bad decisions.");
        }

        if (!NearMissBulletMessages)
            NearMissBulletMessages = new array<string>;

        if (NearMissBulletMessages.Count() == 0)
        {
            NearMissBulletMessages.Insert("That was too close.");
            NearMissBulletMessages.Insert("Move. Breathe. Find cover.");
            NearMissBulletMessages.Insert("My hands are shaking.");
            NearMissBulletMessages.Insert("I need to stay alive for the next few seconds.");
        }

        if (!NearMissExplosionMessages)
            NearMissExplosionMessages = new array<string>;

        if (NearMissExplosionMessages.Count() == 0)
        {
            NearMissExplosionMessages.Insert("That was too close.");
            NearMissExplosionMessages.Insert("Move. Breathe. Find cover.");
            NearMissExplosionMessages.Insert("My hands are shaking.");
            NearMissExplosionMessages.Insert("I need to stay alive for the next few seconds.");
        }

        if (!NearMissCombatGeneralMessages)
            NearMissCombatGeneralMessages = new array<string>;

        if (NearMissCombatGeneralMessages.Count() == 0)
        {
            NearMissCombatGeneralMessages.Insert("That was too close.");
            NearMissCombatGeneralMessages.Insert("Move. Breathe. Find cover.");
            NearMissCombatGeneralMessages.Insert("My hands are shaking.");
            NearMissCombatGeneralMessages.Insert("I need to stay alive for the next few seconds.");
        }

        if (!DiseaseWoundInfectionMessages)
            DiseaseWoundInfectionMessages = new array<string>;

        if (DiseaseWoundInfectionMessages.Count() == 0)
        {
            DiseaseWoundInfectionMessages.Insert("Something is wrong inside me.");
            DiseaseWoundInfectionMessages.Insert("I need medicine before this gets worse.");
            DiseaseWoundInfectionMessages.Insert("My body is fighting and losing ground.");
            DiseaseWoundInfectionMessages.Insert("This sickness is stealing my strength.");
        }

        if (!DiseaseCholeraMessages)
            DiseaseCholeraMessages = new array<string>;

        if (DiseaseCholeraMessages.Count() == 0)
        {
            DiseaseCholeraMessages.Insert("Something is wrong inside me.");
            DiseaseCholeraMessages.Insert("I need medicine before this gets worse.");
            DiseaseCholeraMessages.Insert("My body is fighting and losing ground.");
            DiseaseCholeraMessages.Insert("This sickness is stealing my strength.");
        }

        if (!DiseaseInfluenzaMessages)
            DiseaseInfluenzaMessages = new array<string>;

        if (DiseaseInfluenzaMessages.Count() == 0)
        {
            DiseaseInfluenzaMessages.Insert("Something is wrong inside me.");
            DiseaseInfluenzaMessages.Insert("I need medicine before this gets worse.");
            DiseaseInfluenzaMessages.Insert("My body is fighting and losing ground.");
            DiseaseInfluenzaMessages.Insert("This sickness is stealing my strength.");
        }

        if (!DiseaseKuruMessages)
            DiseaseKuruMessages = new array<string>;

        if (DiseaseKuruMessages.Count() == 0)
        {
            DiseaseKuruMessages.Insert("That was a person. I know that.");
            DiseaseKuruMessages.Insert("There are hungers that should stay empty.");
            DiseaseKuruMessages.Insert("I crossed something I cannot uncross.");
            DiseaseKuruMessages.Insert("The worst part is that it helped.");
        }

        if (!DiseaseChemicalMessages)
            DiseaseChemicalMessages = new array<string>;

        if (DiseaseChemicalMessages.Count() == 0)
        {
            DiseaseChemicalMessages.Insert("Something is wrong inside me.");
            DiseaseChemicalMessages.Insert("I need medicine before this gets worse.");
            DiseaseChemicalMessages.Insert("My body is fighting and losing ground.");
            DiseaseChemicalMessages.Insert("This sickness is stealing my strength.");
        }

        if (!DiseaseUnknownMessages)
            DiseaseUnknownMessages = new array<string>;

        if (DiseaseUnknownMessages.Count() == 0)
        {
            DiseaseUnknownMessages.Insert("Something is wrong inside me.");
            DiseaseUnknownMessages.Insert("I need medicine before this gets worse.");
            DiseaseUnknownMessages.Insert("My body is fighting and losing ground.");
            DiseaseUnknownMessages.Insert("This sickness is stealing my strength.");
        }

        if (!MapChernarusMessages)
            MapChernarusMessages = new array<string>;

        if (MapChernarusMessages.Count() == 0)
        {
            MapChernarusMessages.Insert("This place has its own kind of danger.");
            MapChernarusMessages.Insert("I should learn the exits before I relax.");
            MapChernarusMessages.Insert("Someone else may pass through here.");
            MapChernarusMessages.Insert("Every landmark is a risk and an opportunity.");
        }

        if (!MapLivoniaMessages)
            MapLivoniaMessages = new array<string>;

        if (MapLivoniaMessages.Count() == 0)
        {
            MapLivoniaMessages.Insert("This place has its own kind of danger.");
            MapLivoniaMessages.Insert("I should learn the exits before I relax.");
            MapLivoniaMessages.Insert("Someone else may pass through here.");
            MapLivoniaMessages.Insert("Every landmark is a risk and an opportunity.");
        }

        if (!MapNamalskMessages)
            MapNamalskMessages = new array<string>;

        if (MapNamalskMessages.Count() == 0)
        {
            MapNamalskMessages.Insert("This place has its own kind of danger.");
            MapNamalskMessages.Insert("I should learn the exits before I relax.");
            MapNamalskMessages.Insert("Someone else may pass through here.");
            MapNamalskMessages.Insert("Every landmark is a risk and an opportunity.");
        }

        if (!MapSakhalMessages)
            MapSakhalMessages = new array<string>;

        if (MapSakhalMessages.Count() == 0)
        {
            MapSakhalMessages.Insert("This place has its own kind of danger.");
            MapSakhalMessages.Insert("I should learn the exits before I relax.");
            MapSakhalMessages.Insert("Someone else may pass through here.");
            MapSakhalMessages.Insert("Every landmark is a risk and an opportunity.");
        }

        if (!MapDeerIsleMessages)
            MapDeerIsleMessages = new array<string>;

        if (MapDeerIsleMessages.Count() == 0)
        {
            MapDeerIsleMessages.Insert("This place has its own kind of danger.");
            MapDeerIsleMessages.Insert("I should learn the exits before I relax.");
            MapDeerIsleMessages.Insert("Someone else may pass through here.");
            MapDeerIsleMessages.Insert("Every landmark is a risk and an opportunity.");
        }

        if (!MapGenericMessages)
            MapGenericMessages = new array<string>;

        if (MapGenericMessages.Count() == 0)
        {
            MapGenericMessages.Insert("This place has its own kind of danger.");
            MapGenericMessages.Insert("I should learn the exits before I relax.");
            MapGenericMessages.Insert("Someone else may pass through here.");
            MapGenericMessages.Insert("Every landmark is a risk and an opportunity.");
        }

        if (!ProlongedStarvationMessages)
            ProlongedStarvationMessages = new array<string>;

        if (ProlongedStarvationMessages.Count() == 0)
        {
            ProlongedStarvationMessages.Insert("This prolonged starvation is getting to me.");
            ProlongedStarvationMessages.Insert("I need to pay attention to this prolonged starvation.");
            ProlongedStarvationMessages.Insert("Something about this prolonged starvation feels wrong.");
            ProlongedStarvationMessages.Insert("I should not ignore this prolonged starvation.");
        }

        if (!ProlongedDehydrationMessages)
            ProlongedDehydrationMessages = new array<string>;

        if (ProlongedDehydrationMessages.Count() == 0)
        {
            ProlongedDehydrationMessages.Insert("My mouth is too dry.");
            ProlongedDehydrationMessages.Insert("I need water soon.");
            ProlongedDehydrationMessages.Insert("Dehydration is starting to slow my thoughts.");
            ProlongedDehydrationMessages.Insert("I have to find something safe to drink.");
        }

        if (!ProlongedColdMessages)
            ProlongedColdMessages = new array<string>;

        if (ProlongedColdMessages.Count() == 0)
        {
            ProlongedColdMessages.Insert("The cold is getting into my bones.");
            ProlongedColdMessages.Insert("I need warmth before this gets worse.");
            ProlongedColdMessages.Insert("My fingers are stiff.");
            ProlongedColdMessages.Insert("Shelter and heat. That is all that matters.");
        }

        if (!ProlongedHeatMessages)
            ProlongedHeatMessages = new array<string>;

        if (ProlongedHeatMessages.Count() == 0)
        {
            ProlongedHeatMessages.Insert("The heat is draining me.");
            ProlongedHeatMessages.Insert("I need shade or water.");
            ProlongedHeatMessages.Insert("My head feels heavy.");
            ProlongedHeatMessages.Insert("I am overheating out here.");
        }

        if (!ProlongedBleedingMessages)
            ProlongedBleedingMessages = new array<string>;

        if (ProlongedBleedingMessages.Count() == 0)
        {
            ProlongedBleedingMessages.Insert("I am losing blood.");
            ProlongedBleedingMessages.Insert("I need to stop this before it gets worse.");
            ProlongedBleedingMessages.Insert("Warmth is leaving with every drop.");
            ProlongedBleedingMessages.Insert("Pressure first. Panic later.");
        }

        if (!ProlongedSicknessMessages)
            ProlongedSicknessMessages = new array<string>;

        if (ProlongedSicknessMessages.Count() == 0)
        {
            ProlongedSicknessMessages.Insert("Something is wrong inside me.");
            ProlongedSicknessMessages.Insert("I need medicine before this gets worse.");
            ProlongedSicknessMessages.Insert("My body is fighting and losing ground.");
            ProlongedSicknessMessages.Insert("This sickness is stealing my strength.");
        }

        if (!StarvingDehydratedColdMessages)
            StarvingDehydratedColdMessages = new array<string>;

        if (StarvingDehydratedColdMessages.Count() == 0)
        {
            StarvingDehydratedColdMessages.Insert("My stomach is turning against me.");
            StarvingDehydratedColdMessages.Insert("I need food before my strength goes.");
            StarvingDehydratedColdMessages.Insert("Every step costs more than I have.");
            StarvingDehydratedColdMessages.Insert("I cannot run on nothing much longer.");
        }

        if (!HotDehydratedSickMessages)
            HotDehydratedSickMessages = new array<string>;

        if (HotDehydratedSickMessages.Count() == 0)
        {
            HotDehydratedSickMessages.Insert("My mouth is too dry.");
            HotDehydratedSickMessages.Insert("I need water soon.");
            HotDehydratedSickMessages.Insert("Dehydration is starting to slow my thoughts.");
            HotDehydratedSickMessages.Insert("I have to find something safe to drink.");
        }

        if (!BleedingLowBloodShockMessages)
            BleedingLowBloodShockMessages = new array<string>;

        if (BleedingLowBloodShockMessages.Count() == 0)
        {
            BleedingLowBloodShockMessages.Insert("I am losing blood.");
            BleedingLowBloodShockMessages.Insert("I need to stop this before it gets worse.");
            BleedingLowBloodShockMessages.Insert("Warmth is leaving with every drop.");
            BleedingLowBloodShockMessages.Insert("Pressure first. Panic later.");
        }

        if (!GunshotBleedingLowBloodMessages)
            GunshotBleedingLowBloodMessages = new array<string>;

        if (GunshotBleedingLowBloodMessages.Count() == 0)
        {
            GunshotBleedingLowBloodMessages.Insert("I am losing blood.");
            GunshotBleedingLowBloodMessages.Insert("I need to stop this before it gets worse.");
            GunshotBleedingLowBloodMessages.Insert("Warmth is leaving with every drop.");
            GunshotBleedingLowBloodMessages.Insert("Pressure first. Panic later.");
        }

        if (!BrokenLegBleedingInfectedMessages)
            BrokenLegBleedingInfectedMessages = new array<string>;

        if (BrokenLegBleedingInfectedMessages.Count() == 0)
        {
            BrokenLegBleedingInfectedMessages.Insert("I am losing blood.");
            BrokenLegBleedingInfectedMessages.Insert("I need to stop this before it gets worse.");
            BrokenLegBleedingInfectedMessages.Insert("Warmth is leaving with every drop.");
            BrokenLegBleedingInfectedMessages.Insert("Pressure first. Panic later.");
        }

        if (!NightInfectedRainMessages)
            NightInfectedRainMessages = new array<string>;

        if (NightInfectedRainMessages.Count() == 0)
        {
            NightInfectedRainMessages.Insert("The weather is wearing me down.");
            NightInfectedRainMessages.Insert("This makes every sound harder to trust.");
            NightInfectedRainMessages.Insert("I need to get out of this weather.");
            NightInfectedRainMessages.Insert("Bad weather hides bad decisions.");
        }

        if (!MilitaryNightStormMessages)
            MilitaryNightStormMessages = new array<string>;

        if (MilitaryNightStormMessages.Count() == 0)
        {
            MilitaryNightStormMessages.Insert("The weather is wearing me down.");
            MilitaryNightStormMessages.Insert("This makes every sound harder to trust.");
            MilitaryNightStormMessages.Insert("I need to get out of this weather.");
            MilitaryNightStormMessages.Insert("Bad weather hides bad decisions.");
        }

    }

    void ST_EnsureStarterMessageDefaults_3()
    {
        if (!LoneWolfLowSanityNightMessages)
            LoneWolfLowSanityNightMessages = new array<string>;

        if (LoneWolfLowSanityNightMessages.Count() == 0)
        {
            LoneWolfLowSanityNightMessages.Insert("I have not seen anyone friendly in too long.");
            LoneWolfLowSanityNightMessages.Insert("The silence is starting to feel normal.");
            LoneWolfLowSanityNightMessages.Insert("No voices. No footsteps. Just me.");
            LoneWolfLowSanityNightMessages.Insert("Being alone keeps me alive, but it wears me down.");
        }

        if (!CompanionDeadNightMessages)
            CompanionDeadNightMessages = new array<string>;

        if (CompanionDeadNightMessages.Count() == 0)
        {
            CompanionDeadNightMessages.Insert("They are gone. I am alone now.");
            CompanionDeadNightMessages.Insert("I should have been faster.");
            CompanionDeadNightMessages.Insert("Their silence feels heavier than the gunshot.");
            CompanionDeadNightMessages.Insert("I have to keep moving, even without them.");
        }

        if (!CorpseLowSanityNightMessages)
            CorpseLowSanityNightMessages = new array<string>;

        if (CorpseLowSanityNightMessages.Count() == 0)
        {
            CorpseLowSanityNightMessages.Insert("I keep hearing things that are not there.");
            CorpseLowSanityNightMessages.Insert("Every bad choice feels easier than the last.");
            CorpseLowSanityNightMessages.Insert("I am still in control. I have to be.");
            CorpseLowSanityNightMessages.Insert("The silence is starting to answer back.");
        }

        if (!ShelterNightInfectedMessages)
            ShelterNightInfectedMessages = new array<string>;

        if (ShelterNightInfectedMessages.Count() == 0)
        {
            ShelterNightInfectedMessages.Insert("The dark makes every sound feel closer.");
            ShelterNightInfectedMessages.Insert("I cannot see far enough to feel safe.");
            ShelterNightInfectedMessages.Insert("Night belongs to whoever moves quietly.");
            ShelterNightInfectedMessages.Insert("I should slow down and listen.");
        }

        if (!ShockRecoveryMessages)
            ShockRecoveryMessages = new array<string>;

        if (ShockRecoveryMessages.Count() == 0)
        {
            ShockRecoveryMessages.Insert("That was too close.");
            ShockRecoveryMessages.Insert("Move. Breathe. Find cover.");
            ShockRecoveryMessages.Insert("My hands are shaking.");
            ShockRecoveryMessages.Insert("I need to stay alive for the next few seconds.");
        }

        if (!BloodStabilizingMessages)
            BloodStabilizingMessages = new array<string>;

        if (BloodStabilizingMessages.Count() == 0)
        {
            BloodStabilizingMessages.Insert("I am losing blood.");
            BloodStabilizingMessages.Insert("I need to stop this before it gets worse.");
            BloodStabilizingMessages.Insert("Warmth is leaving with every drop.");
            BloodStabilizingMessages.Insert("Pressure first. Panic later.");
        }

        if (!AlmostDiedRecoveryMessages)
            AlmostDiedRecoveryMessages = new array<string>;

        if (AlmostDiedRecoveryMessages.Count() == 0)
        {
            AlmostDiedRecoveryMessages.Insert("I am not safe, but I am still here.");
            AlmostDiedRecoveryMessages.Insert("That could have ended worse.");
            AlmostDiedRecoveryMessages.Insert("My breathing is starting to settle.");
            AlmostDiedRecoveryMessages.Insert("One crisis is over. The next one can wait.");
        }

        if (!SafeShelterRecoveryMessages)
            SafeShelterRecoveryMessages = new array<string>;

        if (SafeShelterRecoveryMessages.Count() == 0)
        {
            SafeShelterRecoveryMessages.Insert("Four walls do not mean safe.");
            SafeShelterRecoveryMessages.Insert("Shelter helps, but exits matter.");
            SafeShelterRecoveryMessages.Insert("I should check the corners first.");
            SafeShelterRecoveryMessages.Insert("This place could keep me alive for a while.");
        }

        if (!PostCombatBreathMessages)
            PostCombatBreathMessages = new array<string>;

        if (PostCombatBreathMessages.Count() == 0)
        {
            PostCombatBreathMessages.Insert("That was too close.");
            PostCombatBreathMessages.Insert("Move. Breathe. Find cover.");
            PostCombatBreathMessages.Insert("My hands are shaking.");
            PostCombatBreathMessages.Insert("I need to stay alive for the next few seconds.");
        }

        if (!DiseaseGasExposureMessages)
            DiseaseGasExposureMessages = new array<string>;

        if (DiseaseGasExposureMessages.Count() == 0)
        {
            DiseaseGasExposureMessages.Insert("Something is wrong inside me.");
            DiseaseGasExposureMessages.Insert("I need medicine before this gets worse.");
            DiseaseGasExposureMessages.Insert("My body is fighting and losing ground.");
            DiseaseGasExposureMessages.Insert("This sickness is stealing my strength.");
        }

        if (!DiseaseFeverMessages)
            DiseaseFeverMessages = new array<string>;

        if (DiseaseFeverMessages.Count() == 0)
        {
            DiseaseFeverMessages.Insert("Something is wrong inside me.");
            DiseaseFeverMessages.Insert("I need medicine before this gets worse.");
            DiseaseFeverMessages.Insert("My body is fighting and losing ground.");
            DiseaseFeverMessages.Insert("This sickness is stealing my strength.");
        }

        if (!DiseaseFoodPoisoningMessages)
            DiseaseFoodPoisoningMessages = new array<string>;

        if (DiseaseFoodPoisoningMessages.Count() == 0)
        {
            DiseaseFoodPoisoningMessages.Insert("My stomach is turning against me.");
            DiseaseFoodPoisoningMessages.Insert("I need food before my strength goes.");
            DiseaseFoodPoisoningMessages.Insert("Every step costs more than I have.");
            DiseaseFoodPoisoningMessages.Insert("I cannot run on nothing much longer.");
        }

        if (!LocationCoastMessages)
            LocationCoastMessages = new array<string>;

        if (LocationCoastMessages.Count() == 0)
        {
            LocationCoastMessages.Insert("This place has its own kind of danger.");
            LocationCoastMessages.Insert("I should learn the exits before I relax.");
            LocationCoastMessages.Insert("Someone else may pass through here.");
            LocationCoastMessages.Insert("Every landmark is a risk and an opportunity.");
        }

        if (!LocationTownMessages)
            LocationTownMessages = new array<string>;

        if (LocationTownMessages.Count() == 0)
        {
            LocationTownMessages.Insert("This place has its own kind of danger.");
            LocationTownMessages.Insert("I should learn the exits before I relax.");
            LocationTownMessages.Insert("Someone else may pass through here.");
            LocationTownMessages.Insert("Every landmark is a risk and an opportunity.");
        }

        if (!LocationCityMessages)
            LocationCityMessages = new array<string>;

        if (LocationCityMessages.Count() == 0)
        {
            LocationCityMessages.Insert("This place has its own kind of danger.");
            LocationCityMessages.Insert("I should learn the exits before I relax.");
            LocationCityMessages.Insert("Someone else may pass through here.");
            LocationCityMessages.Insert("Every landmark is a risk and an opportunity.");
        }

        if (!LocationForestMessages)
            LocationForestMessages = new array<string>;

        if (LocationForestMessages.Count() == 0)
        {
            LocationForestMessages.Insert("This place has its own kind of danger.");
            LocationForestMessages.Insert("I should learn the exits before I relax.");
            LocationForestMessages.Insert("Someone else may pass through here.");
            LocationForestMessages.Insert("Every landmark is a risk and an opportunity.");
        }

        if (!LocationWildernessMessages)
            LocationWildernessMessages = new array<string>;

        if (LocationWildernessMessages.Count() == 0)
        {
            LocationWildernessMessages.Insert("This place has its own kind of danger.");
            LocationWildernessMessages.Insert("I should learn the exits before I relax.");
            LocationWildernessMessages.Insert("Someone else may pass through here.");
            LocationWildernessMessages.Insert("Every landmark is a risk and an opportunity.");
        }

        if (!LocationMilitaryMessages)
            LocationMilitaryMessages = new array<string>;

        if (LocationMilitaryMessages.Count() == 0)
        {
            LocationMilitaryMessages.Insert("Good gear brings bad company.");
            LocationMilitaryMessages.Insert("Someone else will come here armed.");
            LocationMilitaryMessages.Insert("I should assume I am being watched.");
            LocationMilitaryMessages.Insert("Military places never feel abandoned.");
        }

        if (!LocationPoliceMessages)
            LocationPoliceMessages = new array<string>;

        if (LocationPoliceMessages.Count() == 0)
        {
            LocationPoliceMessages.Insert("This place has its own kind of danger.");
            LocationPoliceMessages.Insert("I should learn the exits before I relax.");
            LocationPoliceMessages.Insert("Someone else may pass through here.");
            LocationPoliceMessages.Insert("Every landmark is a risk and an opportunity.");
        }

        if (!LocationMedicalMessages)
            LocationMedicalMessages = new array<string>;

        if (LocationMedicalMessages.Count() == 0)
        {
            LocationMedicalMessages.Insert("This place has its own kind of danger.");
            LocationMedicalMessages.Insert("I should learn the exits before I relax.");
            LocationMedicalMessages.Insert("Someone else may pass through here.");
            LocationMedicalMessages.Insert("Every landmark is a risk and an opportunity.");
        }

        if (!LocationIndustrialMessages)
            LocationIndustrialMessages = new array<string>;

        if (LocationIndustrialMessages.Count() == 0)
        {
            LocationIndustrialMessages.Insert("This place has its own kind of danger.");
            LocationIndustrialMessages.Insert("I should learn the exits before I relax.");
            LocationIndustrialMessages.Insert("Someone else may pass through here.");
            LocationIndustrialMessages.Insert("Every landmark is a risk and an opportunity.");
        }

        if (!LocationFarmMessages)
            LocationFarmMessages = new array<string>;

        if (LocationFarmMessages.Count() == 0)
        {
            LocationFarmMessages.Insert("This place has its own kind of danger.");
            LocationFarmMessages.Insert("I should learn the exits before I relax.");
            LocationFarmMessages.Insert("Someone else may pass through here.");
            LocationFarmMessages.Insert("Every landmark is a risk and an opportunity.");
        }

        if (!LocationWaterMessages)
            LocationWaterMessages = new array<string>;

        if (LocationWaterMessages.Count() == 0)
        {
            LocationWaterMessages.Insert("This place has its own kind of danger.");
            LocationWaterMessages.Insert("I should learn the exits before I relax.");
            LocationWaterMessages.Insert("Someone else may pass through here.");
            LocationWaterMessages.Insert("Every landmark is a risk and an opportunity.");
        }

        if (!PlayerMemoryRecentDamageMessages)
            PlayerMemoryRecentDamageMessages = new array<string>;

        if (PlayerMemoryRecentDamageMessages.Count() == 0)
        {
            PlayerMemoryRecentDamageMessages.Insert("This player memory recent damage is getting to me.");
            PlayerMemoryRecentDamageMessages.Insert("I need to pay attention to this player memory recent damage.");
            PlayerMemoryRecentDamageMessages.Insert("Something about this player memory recent damage feels wrong.");
            PlayerMemoryRecentDamageMessages.Insert("I should not ignore this player memory recent damage.");
        }

        if (!PlayerMemoryRecentBleedingMessages)
            PlayerMemoryRecentBleedingMessages = new array<string>;

        if (PlayerMemoryRecentBleedingMessages.Count() == 0)
        {
            PlayerMemoryRecentBleedingMessages.Insert("I am losing blood.");
            PlayerMemoryRecentBleedingMessages.Insert("I need to stop this before it gets worse.");
            PlayerMemoryRecentBleedingMessages.Insert("Warmth is leaving with every drop.");
            PlayerMemoryRecentBleedingMessages.Insert("Pressure first. Panic later.");
        }

        if (!PlayerMemoryRecentGunshotMessages)
            PlayerMemoryRecentGunshotMessages = new array<string>;

        if (PlayerMemoryRecentGunshotMessages.Count() == 0)
        {
            PlayerMemoryRecentGunshotMessages.Insert("That was too close.");
            PlayerMemoryRecentGunshotMessages.Insert("Move. Breathe. Find cover.");
            PlayerMemoryRecentGunshotMessages.Insert("My hands are shaking.");
            PlayerMemoryRecentGunshotMessages.Insert("I need to stay alive for the next few seconds.");
        }

        if (!PlayerMemoryRecentCorpseMessages)
            PlayerMemoryRecentCorpseMessages = new array<string>;

        if (PlayerMemoryRecentCorpseMessages.Count() == 0)
        {
            PlayerMemoryRecentCorpseMessages.Insert("Someone died here.");
            PlayerMemoryRecentCorpseMessages.Insert("Bodies mean danger came through already.");
            PlayerMemoryRecentCorpseMessages.Insert("I should not stay near this.");
            PlayerMemoryRecentCorpseMessages.Insert("Where there is one corpse, there may be another.");
        }

        if (!PlayerMemoryRecentMilitaryMessages)
            PlayerMemoryRecentMilitaryMessages = new array<string>;

        if (PlayerMemoryRecentMilitaryMessages.Count() == 0)
        {
            PlayerMemoryRecentMilitaryMessages.Insert("Good gear brings bad company.");
            PlayerMemoryRecentMilitaryMessages.Insert("Someone else will come here armed.");
            PlayerMemoryRecentMilitaryMessages.Insert("I should assume I am being watched.");
            PlayerMemoryRecentMilitaryMessages.Insert("Military places never feel abandoned.");
        }

        if (!PlayerMemoryRecentSurvivalCrisisMessages)
            PlayerMemoryRecentSurvivalCrisisMessages = new array<string>;

        if (PlayerMemoryRecentSurvivalCrisisMessages.Count() == 0)
        {
            PlayerMemoryRecentSurvivalCrisisMessages.Insert("This player memory recent survival crisis is getting to me.");
            PlayerMemoryRecentSurvivalCrisisMessages.Insert("I need to pay attention to this player memory recent survival crisis.");
            PlayerMemoryRecentSurvivalCrisisMessages.Insert("Something about this player memory recent survival crisis feels wrong.");
            PlayerMemoryRecentSurvivalCrisisMessages.Insert("I should not ignore this player memory recent survival crisis.");
        }

        if (!StealthNoiseInfectedNearbyMessages)
            StealthNoiseInfectedNearbyMessages = new array<string>;

        if (StealthNoiseInfectedNearbyMessages.Count() == 0)
        {
            StealthNoiseInfectedNearbyMessages.Insert("Infected are too close.");
            StealthNoiseInfectedNearbyMessages.Insert("I need to move quietly.");
            StealthNoiseInfectedNearbyMessages.Insert("One wrong noise and they will be on me.");
            StealthNoiseInfectedNearbyMessages.Insert("I can hear them nearby.");
        }

        if (!StealthNoiseNightMessages)
            StealthNoiseNightMessages = new array<string>;

        if (StealthNoiseNightMessages.Count() == 0)
        {
            StealthNoiseNightMessages.Insert("The dark makes every sound feel closer.");
            StealthNoiseNightMessages.Insert("I cannot see far enough to feel safe.");
            StealthNoiseNightMessages.Insert("Night belongs to whoever moves quietly.");
            StealthNoiseNightMessages.Insert("I should slow down and listen.");
        }

        if (!StealthNoiseMilitaryMessages)
            StealthNoiseMilitaryMessages = new array<string>;

        if (StealthNoiseMilitaryMessages.Count() == 0)
        {
            StealthNoiseMilitaryMessages.Insert("Good gear brings bad company.");
            StealthNoiseMilitaryMessages.Insert("Someone else will come here armed.");
            StealthNoiseMilitaryMessages.Insert("I should assume I am being watched.");
            StealthNoiseMilitaryMessages.Insert("Military places never feel abandoned.");
        }

        if (!ShelterSafeMessages)
            ShelterSafeMessages = new array<string>;

        if (ShelterSafeMessages.Count() == 0)
        {
            ShelterSafeMessages.Insert("Four walls do not mean safe.");
            ShelterSafeMessages.Insert("Shelter helps, but exits matter.");
            ShelterSafeMessages.Insert("I should check the corners first.");
            ShelterSafeMessages.Insert("This place could keep me alive for a while.");
        }

        if (!ShelterUnsafeMessages)
            ShelterUnsafeMessages = new array<string>;

        if (ShelterUnsafeMessages.Count() == 0)
        {
            ShelterUnsafeMessages.Insert("Four walls do not mean safe.");
            ShelterUnsafeMessages.Insert("Shelter helps, but exits matter.");
            ShelterUnsafeMessages.Insert("I should check the corners first.");
            ShelterUnsafeMessages.Insert("This place could keep me alive for a while.");
        }

        if (!ShelterBadWeatherMessages)
            ShelterBadWeatherMessages = new array<string>;

        if (ShelterBadWeatherMessages.Count() == 0)
        {
            ShelterBadWeatherMessages.Insert("The weather is wearing me down.");
            ShelterBadWeatherMessages.Insert("This makes every sound harder to trust.");
            ShelterBadWeatherMessages.Insert("I need to get out of this weather.");
            ShelterBadWeatherMessages.Insert("Bad weather hides bad decisions.");
        }

        if (!ShelterNightMessages)
            ShelterNightMessages = new array<string>;

        if (ShelterNightMessages.Count() == 0)
        {
            ShelterNightMessages.Insert("The dark makes every sound feel closer.");
            ShelterNightMessages.Insert("I cannot see far enough to feel safe.");
            ShelterNightMessages.Insert("Night belongs to whoever moves quietly.");
            ShelterNightMessages.Insert("I should slow down and listen.");
        }

        if (!MentalStateStableMessages)
            MentalStateStableMessages = new array<string>;

        if (MentalStateStableMessages.Count() == 0)
        {
            MentalStateStableMessages.Insert("I am not safe, but I am still here.");
            MentalStateStableMessages.Insert("That could have ended worse.");
            MentalStateStableMessages.Insert("My breathing is starting to settle.");
            MentalStateStableMessages.Insert("One crisis is over. The next one can wait.");
        }

        if (!MentalStateUneasyMessages)
            MentalStateUneasyMessages = new array<string>;

        if (MentalStateUneasyMessages.Count() == 0)
        {
            MentalStateUneasyMessages.Insert("I need to keep myself together.");
            MentalStateUneasyMessages.Insert("My thoughts are getting louder.");
            MentalStateUneasyMessages.Insert("Focus on what is real.");
            MentalStateUneasyMessages.Insert("Do the next necessary thing.");
        }

        if (!MentalStateAfraidMessages)
            MentalStateAfraidMessages = new array<string>;

        if (MentalStateAfraidMessages.Count() == 0)
        {
            MentalStateAfraidMessages.Insert("I need to keep myself together.");
            MentalStateAfraidMessages.Insert("My thoughts are getting louder.");
            MentalStateAfraidMessages.Insert("Focus on what is real.");
            MentalStateAfraidMessages.Insert("Do the next necessary thing.");
        }

        if (!MentalStateDesperateMessages)
            MentalStateDesperateMessages = new array<string>;

        if (MentalStateDesperateMessages.Count() == 0)
        {
            MentalStateDesperateMessages.Insert("I need to keep myself together.");
            MentalStateDesperateMessages.Insert("My thoughts are getting louder.");
            MentalStateDesperateMessages.Insert("Focus on what is real.");
            MentalStateDesperateMessages.Insert("Do the next necessary thing.");
        }

    }

    void ST_EnsureStarterMessageDefaults_4()
    {
        if (!MentalStateNumbMessages)
            MentalStateNumbMessages = new array<string>;

        if (MentalStateNumbMessages.Count() == 0)
        {
            MentalStateNumbMessages.Insert("I need to keep myself together.");
            MentalStateNumbMessages.Insert("My thoughts are getting louder.");
            MentalStateNumbMessages.Insert("Focus on what is real.");
            MentalStateNumbMessages.Insert("Do the next necessary thing.");
        }

        if (!MentalStateAggressiveMessages)
            MentalStateAggressiveMessages = new array<string>;

        if (MentalStateAggressiveMessages.Count() == 0)
        {
            MentalStateAggressiveMessages.Insert("I need to keep myself together.");
            MentalStateAggressiveMessages.Insert("My thoughts are getting louder.");
            MentalStateAggressiveMessages.Insert("Focus on what is real.");
            MentalStateAggressiveMessages.Insert("Do the next necessary thing.");
        }

        if (!MentalStateBrokenMessages)
            MentalStateBrokenMessages = new array<string>;

        if (MentalStateBrokenMessages.Count() == 0)
        {
            MentalStateBrokenMessages.Insert("I need to keep myself together.");
            MentalStateBrokenMessages.Insert("My thoughts are getting louder.");
            MentalStateBrokenMessages.Insert("Focus on what is real.");
            MentalStateBrokenMessages.Insert("Do the next necessary thing.");
        }

        if (!MentalStateFocusedMessages)
            MentalStateFocusedMessages = new array<string>;

        if (MentalStateFocusedMessages.Count() == 0)
        {
            MentalStateFocusedMessages.Insert("I need to keep myself together.");
            MentalStateFocusedMessages.Insert("My thoughts are getting louder.");
            MentalStateFocusedMessages.Insert("Focus on what is real.");
            MentalStateFocusedMessages.Insert("Do the next necessary thing.");
        }

        if (!HungerColdInfectedMessages)
            HungerColdInfectedMessages = new array<string>;

        if (HungerColdInfectedMessages.Count() == 0)
        {
            HungerColdInfectedMessages.Insert("My stomach is turning against me.");
            HungerColdInfectedMessages.Insert("I need food before my strength goes.");
            HungerColdInfectedMessages.Insert("Every step costs more than I have.");
            HungerColdInfectedMessages.Insert("I cannot run on nothing much longer.");
        }

        if (!HungerThirstMessages)
            HungerThirstMessages = new array<string>;

        if (HungerThirstMessages.Count() == 0)
        {
            HungerThirstMessages.Insert("My stomach is turning against me.");
            HungerThirstMessages.Insert("I need food before my strength goes.");
            HungerThirstMessages.Insert("Every step costs more than I have.");
            HungerThirstMessages.Insert("I cannot run on nothing much longer.");
        }

        if (!ColdInfectedMessages)
            ColdInfectedMessages = new array<string>;

        if (ColdInfectedMessages.Count() == 0)
        {
            ColdInfectedMessages.Insert("The cold is getting into my bones.");
            ColdInfectedMessages.Insert("I need warmth before this gets worse.");
            ColdInfectedMessages.Insert("My fingers are stiff.");
            ColdInfectedMessages.Insert("Shelter and heat. That is all that matters.");
        }

        if (!BleedingInfectedMessages)
            BleedingInfectedMessages = new array<string>;

        if (BleedingInfectedMessages.Count() == 0)
        {
            BleedingInfectedMessages.Insert("I am losing blood.");
            BleedingInfectedMessages.Insert("I need to stop this before it gets worse.");
            BleedingInfectedMessages.Insert("Warmth is leaving with every drop.");
            BleedingInfectedMessages.Insert("Pressure first. Panic later.");
        }

        if (!SickColdMessages)
            SickColdMessages = new array<string>;

        if (SickColdMessages.Count() == 0)
        {
            SickColdMessages.Insert("The cold is getting into my bones.");
            SickColdMessages.Insert("I need warmth before this gets worse.");
            SickColdMessages.Insert("My fingers are stiff.");
            SickColdMessages.Insert("Shelter and heat. That is all that matters.");
        }

        if (!HotThirstMessages)
            HotThirstMessages = new array<string>;

        if (HotThirstMessages.Count() == 0)
        {
            HotThirstMessages.Insert("My mouth is too dry.");
            HotThirstMessages.Insert("I need water soon.");
            HotThirstMessages.Insert("Dehydration is starting to slow my thoughts.");
            HotThirstMessages.Insert("I have to find something safe to drink.");
        }

        if (!SickThirstMessages)
            SickThirstMessages = new array<string>;

        if (SickThirstMessages.Count() == 0)
        {
            SickThirstMessages.Insert("My mouth is too dry.");
            SickThirstMessages.Insert("I need water soon.");
            SickThirstMessages.Insert("Dehydration is starting to slow my thoughts.");
            SickThirstMessages.Insert("I have to find something safe to drink.");
        }

        if (!BleedingColdMessages)
            BleedingColdMessages = new array<string>;

        if (BleedingColdMessages.Count() == 0)
        {
            BleedingColdMessages.Insert("I am losing blood.");
            BleedingColdMessages.Insert("I need to stop this before it gets worse.");
            BleedingColdMessages.Insert("Warmth is leaving with every drop.");
            BleedingColdMessages.Insert("Pressure first. Panic later.");
        }

        if (!BrokenLegHungerMessages)
            BrokenLegHungerMessages = new array<string>;

        if (BrokenLegHungerMessages.Count() == 0)
        {
            BrokenLegHungerMessages.Insert("My stomach is turning against me.");
            BrokenLegHungerMessages.Insert("I need food before my strength goes.");
            BrokenLegHungerMessages.Insert("Every step costs more than I have.");
            BrokenLegHungerMessages.Insert("I cannot run on nothing much longer.");
        }

        if (!BrokenLegThirstMessages)
            BrokenLegThirstMessages = new array<string>;

        if (BrokenLegThirstMessages.Count() == 0)
        {
            BrokenLegThirstMessages.Insert("My mouth is too dry.");
            BrokenLegThirstMessages.Insert("I need water soon.");
            BrokenLegThirstMessages.Insert("Dehydration is starting to slow my thoughts.");
            BrokenLegThirstMessages.Insert("I have to find something safe to drink.");
        }

        if (!BrokenLegColdMessages)
            BrokenLegColdMessages = new array<string>;

        if (BrokenLegColdMessages.Count() == 0)
        {
            BrokenLegColdMessages.Insert("The cold is getting into my bones.");
            BrokenLegColdMessages.Insert("I need warmth before this gets worse.");
            BrokenLegColdMessages.Insert("My fingers are stiff.");
            BrokenLegColdMessages.Insert("Shelter and heat. That is all that matters.");
        }

        if (!BrokenLegHotMessages)
            BrokenLegHotMessages = new array<string>;

        if (BrokenLegHotMessages.Count() == 0)
        {
            BrokenLegHotMessages.Insert("The heat is draining me.");
            BrokenLegHotMessages.Insert("I need shade or water.");
            BrokenLegHotMessages.Insert("My head feels heavy.");
            BrokenLegHotMessages.Insert("I am overheating out here.");
        }

        if (!BrokenLegSickMessages)
            BrokenLegSickMessages = new array<string>;

        if (BrokenLegSickMessages.Count() == 0)
        {
            BrokenLegSickMessages.Insert("Something is wrong inside me.");
            BrokenLegSickMessages.Insert("I need medicine before this gets worse.");
            BrokenLegSickMessages.Insert("My body is fighting and losing ground.");
            BrokenLegSickMessages.Insert("This sickness is stealing my strength.");
        }

        if (!BrokenLegBleedingMessages)
            BrokenLegBleedingMessages = new array<string>;

        if (BrokenLegBleedingMessages.Count() == 0)
        {
            BrokenLegBleedingMessages.Insert("I am losing blood.");
            BrokenLegBleedingMessages.Insert("I need to stop this before it gets worse.");
            BrokenLegBleedingMessages.Insert("Warmth is leaving with every drop.");
            BrokenLegBleedingMessages.Insert("Pressure first. Panic later.");
        }

        if (!BrokenLegColdInfectedMessages)
            BrokenLegColdInfectedMessages = new array<string>;

        if (BrokenLegColdInfectedMessages.Count() == 0)
        {
            BrokenLegColdInfectedMessages.Insert("The cold is getting into my bones.");
            BrokenLegColdInfectedMessages.Insert("I need warmth before this gets worse.");
            BrokenLegColdInfectedMessages.Insert("My fingers are stiff.");
            BrokenLegColdInfectedMessages.Insert("Shelter and heat. That is all that matters.");
        }

        if (!BrokenLegHungerThirstMessages)
            BrokenLegHungerThirstMessages = new array<string>;

        if (BrokenLegHungerThirstMessages.Count() == 0)
        {
            BrokenLegHungerThirstMessages.Insert("My stomach is turning against me.");
            BrokenLegHungerThirstMessages.Insert("I need food before my strength goes.");
            BrokenLegHungerThirstMessages.Insert("Every step costs more than I have.");
            BrokenLegHungerThirstMessages.Insert("I cannot run on nothing much longer.");
        }

        if (!HungerColdMessages)
            HungerColdMessages = new array<string>;

        if (HungerColdMessages.Count() == 0)
        {
            HungerColdMessages.Insert("My stomach is turning against me.");
            HungerColdMessages.Insert("I need food before my strength goes.");
            HungerColdMessages.Insert("Every step costs more than I have.");
            HungerColdMessages.Insert("I cannot run on nothing much longer.");
        }

        if (!HungerHotMessages)
            HungerHotMessages = new array<string>;

        if (HungerHotMessages.Count() == 0)
        {
            HungerHotMessages.Insert("My stomach is turning against me.");
            HungerHotMessages.Insert("I need food before my strength goes.");
            HungerHotMessages.Insert("Every step costs more than I have.");
            HungerHotMessages.Insert("I cannot run on nothing much longer.");
        }

        if (!HungerSickMessages)
            HungerSickMessages = new array<string>;

        if (HungerSickMessages.Count() == 0)
        {
            HungerSickMessages.Insert("My stomach is turning against me.");
            HungerSickMessages.Insert("I need food before my strength goes.");
            HungerSickMessages.Insert("Every step costs more than I have.");
            HungerSickMessages.Insert("I cannot run on nothing much longer.");
        }

        if (!HungerBleedingMessages)
            HungerBleedingMessages = new array<string>;

        if (HungerBleedingMessages.Count() == 0)
        {
            HungerBleedingMessages.Insert("My stomach is turning against me.");
            HungerBleedingMessages.Insert("I need food before my strength goes.");
            HungerBleedingMessages.Insert("Every step costs more than I have.");
            HungerBleedingMessages.Insert("I cannot run on nothing much longer.");
        }

        if (!HungerInfectedMessages)
            HungerInfectedMessages = new array<string>;

        if (HungerInfectedMessages.Count() == 0)
        {
            HungerInfectedMessages.Insert("My stomach is turning against me.");
            HungerInfectedMessages.Insert("I need food before my strength goes.");
            HungerInfectedMessages.Insert("Every step costs more than I have.");
            HungerInfectedMessages.Insert("I cannot run on nothing much longer.");
        }

        if (!ThirstColdMessages)
            ThirstColdMessages = new array<string>;

        if (ThirstColdMessages.Count() == 0)
        {
            ThirstColdMessages.Insert("My mouth is too dry.");
            ThirstColdMessages.Insert("I need water soon.");
            ThirstColdMessages.Insert("Dehydration is starting to slow my thoughts.");
            ThirstColdMessages.Insert("I have to find something safe to drink.");
        }

        if (!ThirstBleedingMessages)
            ThirstBleedingMessages = new array<string>;

        if (ThirstBleedingMessages.Count() == 0)
        {
            ThirstBleedingMessages.Insert("My mouth is too dry.");
            ThirstBleedingMessages.Insert("I need water soon.");
            ThirstBleedingMessages.Insert("Dehydration is starting to slow my thoughts.");
            ThirstBleedingMessages.Insert("I have to find something safe to drink.");
        }

        if (!ThirstInfectedMessages)
            ThirstInfectedMessages = new array<string>;

        if (ThirstInfectedMessages.Count() == 0)
        {
            ThirstInfectedMessages.Insert("My mouth is too dry.");
            ThirstInfectedMessages.Insert("I need water soon.");
            ThirstInfectedMessages.Insert("Dehydration is starting to slow my thoughts.");
            ThirstInfectedMessages.Insert("I have to find something safe to drink.");
        }

        if (!HotBleedingMessages)
            HotBleedingMessages = new array<string>;

        if (HotBleedingMessages.Count() == 0)
        {
            HotBleedingMessages.Insert("I am losing blood.");
            HotBleedingMessages.Insert("I need to stop this before it gets worse.");
            HotBleedingMessages.Insert("Warmth is leaving with every drop.");
            HotBleedingMessages.Insert("Pressure first. Panic later.");
        }

        if (!HotInfectedMessages)
            HotInfectedMessages = new array<string>;

        if (HotInfectedMessages.Count() == 0)
        {
            HotInfectedMessages.Insert("The heat is draining me.");
            HotInfectedMessages.Insert("I need shade or water.");
            HotInfectedMessages.Insert("My head feels heavy.");
            HotInfectedMessages.Insert("I am overheating out here.");
        }

        if (!SickBleedingMessages)
            SickBleedingMessages = new array<string>;

        if (SickBleedingMessages.Count() == 0)
        {
            SickBleedingMessages.Insert("I am losing blood.");
            SickBleedingMessages.Insert("I need to stop this before it gets worse.");
            SickBleedingMessages.Insert("Warmth is leaving with every drop.");
            SickBleedingMessages.Insert("Pressure first. Panic later.");
        }

        if (!SickInfectedMessages)
            SickInfectedMessages = new array<string>;

        if (SickInfectedMessages.Count() == 0)
        {
            SickInfectedMessages.Insert("Something is wrong inside me.");
            SickInfectedMessages.Insert("I need medicine before this gets worse.");
            SickInfectedMessages.Insert("My body is fighting and losing ground.");
            SickInfectedMessages.Insert("This sickness is stealing my strength.");
        }

        if (!HungerThirstColdMessages)
            HungerThirstColdMessages = new array<string>;

        if (HungerThirstColdMessages.Count() == 0)
        {
            HungerThirstColdMessages.Insert("My stomach is turning against me.");
            HungerThirstColdMessages.Insert("I need food before my strength goes.");
            HungerThirstColdMessages.Insert("Every step costs more than I have.");
            HungerThirstColdMessages.Insert("I cannot run on nothing much longer.");
        }

        if (!HungerThirstHotMessages)
            HungerThirstHotMessages = new array<string>;

        if (HungerThirstHotMessages.Count() == 0)
        {
            HungerThirstHotMessages.Insert("My stomach is turning against me.");
            HungerThirstHotMessages.Insert("I need food before my strength goes.");
            HungerThirstHotMessages.Insert("Every step costs more than I have.");
            HungerThirstHotMessages.Insert("I cannot run on nothing much longer.");
        }

        if (!HungerThirstInfectedMessages)
            HungerThirstInfectedMessages = new array<string>;

        if (HungerThirstInfectedMessages.Count() == 0)
        {
            HungerThirstInfectedMessages.Insert("My stomach is turning against me.");
            HungerThirstInfectedMessages.Insert("I need food before my strength goes.");
            HungerThirstInfectedMessages.Insert("Every step costs more than I have.");
            HungerThirstInfectedMessages.Insert("I cannot run on nothing much longer.");
        }

        if (!ThirstHotInfectedMessages)
            ThirstHotInfectedMessages = new array<string>;

        if (ThirstHotInfectedMessages.Count() == 0)
        {
            ThirstHotInfectedMessages.Insert("My mouth is too dry.");
            ThirstHotInfectedMessages.Insert("I need water soon.");
            ThirstHotInfectedMessages.Insert("Dehydration is starting to slow my thoughts.");
            ThirstHotInfectedMessages.Insert("I have to find something safe to drink.");
        }

        if (!SickColdInfectedMessages)
            SickColdInfectedMessages = new array<string>;

        if (SickColdInfectedMessages.Count() == 0)
        {
            SickColdInfectedMessages.Insert("The cold is getting into my bones.");
            SickColdInfectedMessages.Insert("I need warmth before this gets worse.");
            SickColdInfectedMessages.Insert("My fingers are stiff.");
            SickColdInfectedMessages.Insert("Shelter and heat. That is all that matters.");
        }

        if (!BleedingColdInfectedMessages)
            BleedingColdInfectedMessages = new array<string>;

        if (BleedingColdInfectedMessages.Count() == 0)
        {
            BleedingColdInfectedMessages.Insert("I am losing blood.");
            BleedingColdInfectedMessages.Insert("I need to stop this before it gets worse.");
            BleedingColdInfectedMessages.Insert("Warmth is leaving with every drop.");
            BleedingColdInfectedMessages.Insert("Pressure first. Panic later.");
        }

        if (!BleedingSickInfectedMessages)
            BleedingSickInfectedMessages = new array<string>;

        if (BleedingSickInfectedMessages.Count() == 0)
        {
            BleedingSickInfectedMessages.Insert("I am losing blood.");
            BleedingSickInfectedMessages.Insert("I need to stop this before it gets worse.");
            BleedingSickInfectedMessages.Insert("Warmth is leaving with every drop.");
            BleedingSickInfectedMessages.Insert("Pressure first. Panic later.");
        }

        if (!ExtremeSurvivalMessages)
            ExtremeSurvivalMessages = new array<string>;

        if (ExtremeSurvivalMessages.Count() == 0)
        {
            ExtremeSurvivalMessages.Insert("This extreme survival is getting to me.");
            ExtremeSurvivalMessages.Insert("I need to pay attention to this extreme survival.");
            ExtremeSurvivalMessages.Insert("Something about this extreme survival feels wrong.");
            ExtremeSurvivalMessages.Insert("I should not ignore this extreme survival.");
        }

    }

    void ST_EnsureStarterMessageDefaults_5()
    {
        if (!CriticalSurvivalMessages)
            CriticalSurvivalMessages = new array<string>;

        if (CriticalSurvivalMessages.Count() == 0)
        {
            CriticalSurvivalMessages.Insert("This critical survival is getting to me.");
            CriticalSurvivalMessages.Insert("I need to pay attention to this critical survival.");
            CriticalSurvivalMessages.Insert("Something about this critical survival feels wrong.");
            CriticalSurvivalMessages.Insert("I should not ignore this critical survival.");
        }

        if (!StarvingToDeathMessages)
            StarvingToDeathMessages = new array<string>;

        if (StarvingToDeathMessages.Count() == 0)
        {
            StarvingToDeathMessages.Insert("My stomach is turning against me.");
            StarvingToDeathMessages.Insert("I need food before my strength goes.");
            StarvingToDeathMessages.Insert("Every step costs more than I have.");
            StarvingToDeathMessages.Insert("I cannot run on nothing much longer.");
        }

        if (!DehydratingToDeathMessages)
            DehydratingToDeathMessages = new array<string>;

        if (DehydratingToDeathMessages.Count() == 0)
        {
            DehydratingToDeathMessages.Insert("My mouth is too dry.");
            DehydratingToDeathMessages.Insert("I need water soon.");
            DehydratingToDeathMessages.Insert("Dehydration is starting to slow my thoughts.");
            DehydratingToDeathMessages.Insert("I have to find something safe to drink.");
        }

        if (!FreezingToDeathMessages)
            FreezingToDeathMessages = new array<string>;

        if (FreezingToDeathMessages.Count() == 0)
        {
            FreezingToDeathMessages.Insert("The cold is getting into my bones.");
            FreezingToDeathMessages.Insert("I need warmth before this gets worse.");
            FreezingToDeathMessages.Insert("My fingers are stiff.");
            FreezingToDeathMessages.Insert("Shelter and heat. That is all that matters.");
        }

        if (!OverheatingToDeathMessages)
            OverheatingToDeathMessages = new array<string>;

        if (OverheatingToDeathMessages.Count() == 0)
        {
            OverheatingToDeathMessages.Insert("This overheating to death is getting to me.");
            OverheatingToDeathMessages.Insert("I need to pay attention to this overheating to death.");
            OverheatingToDeathMessages.Insert("Something about this overheating to death feels wrong.");
            OverheatingToDeathMessages.Insert("I should not ignore this overheating to death.");
        }

        if (!WeatherClearMessages)
            WeatherClearMessages = new array<string>;

        if (WeatherClearMessages.Count() == 0)
        {
            WeatherClearMessages.Insert("The weather is wearing me down.");
            WeatherClearMessages.Insert("This makes every sound harder to trust.");
            WeatherClearMessages.Insert("I need to get out of this weather.");
            WeatherClearMessages.Insert("Bad weather hides bad decisions.");
        }

        if (!WeatherOvercastMessages)
            WeatherOvercastMessages = new array<string>;

        if (WeatherOvercastMessages.Count() == 0)
        {
            WeatherOvercastMessages.Insert("The weather is wearing me down.");
            WeatherOvercastMessages.Insert("This makes every sound harder to trust.");
            WeatherOvercastMessages.Insert("I need to get out of this weather.");
            WeatherOvercastMessages.Insert("Bad weather hides bad decisions.");
        }

        if (!WeatherLightRainMessages)
            WeatherLightRainMessages = new array<string>;

        if (WeatherLightRainMessages.Count() == 0)
        {
            WeatherLightRainMessages.Insert("The weather is wearing me down.");
            WeatherLightRainMessages.Insert("This makes every sound harder to trust.");
            WeatherLightRainMessages.Insert("I need to get out of this weather.");
            WeatherLightRainMessages.Insert("Bad weather hides bad decisions.");
        }

        if (!WeatherHeavyRainMessages)
            WeatherHeavyRainMessages = new array<string>;

        if (WeatherHeavyRainMessages.Count() == 0)
        {
            WeatherHeavyRainMessages.Insert("The weather is wearing me down.");
            WeatherHeavyRainMessages.Insert("This makes every sound harder to trust.");
            WeatherHeavyRainMessages.Insert("I need to get out of this weather.");
            WeatherHeavyRainMessages.Insert("Bad weather hides bad decisions.");
        }

        if (!WeatherRainMessages)
            WeatherRainMessages = new array<string>;

        if (WeatherRainMessages.Count() == 0)
        {
            WeatherRainMessages.Insert("The weather is wearing me down.");
            WeatherRainMessages.Insert("This makes every sound harder to trust.");
            WeatherRainMessages.Insert("I need to get out of this weather.");
            WeatherRainMessages.Insert("Bad weather hides bad decisions.");
        }

        if (!WeatherFogMessages)
            WeatherFogMessages = new array<string>;

        if (WeatherFogMessages.Count() == 0)
        {
            WeatherFogMessages.Insert("The weather is wearing me down.");
            WeatherFogMessages.Insert("This makes every sound harder to trust.");
            WeatherFogMessages.Insert("I need to get out of this weather.");
            WeatherFogMessages.Insert("Bad weather hides bad decisions.");
        }

        if (!WeatherStormMessages)
            WeatherStormMessages = new array<string>;

        if (WeatherStormMessages.Count() == 0)
        {
            WeatherStormMessages.Insert("The weather is wearing me down.");
            WeatherStormMessages.Insert("This makes every sound harder to trust.");
            WeatherStormMessages.Insert("I need to get out of this weather.");
            WeatherStormMessages.Insert("Bad weather hides bad decisions.");
        }

        if (!WeatherWindMessages)
            WeatherWindMessages = new array<string>;

        if (WeatherWindMessages.Count() == 0)
        {
            WeatherWindMessages.Insert("The weather is wearing me down.");
            WeatherWindMessages.Insert("This makes every sound harder to trust.");
            WeatherWindMessages.Insert("I need to get out of this weather.");
            WeatherWindMessages.Insert("Bad weather hides bad decisions.");
        }

        if (!DawnMessages)
            DawnMessages = new array<string>;

        if (DawnMessages.Count() == 0)
        {
            DawnMessages.Insert("Dawn is coming. I made it through the dark.");
            DawnMessages.Insert("The light is returning, slowly.");
            DawnMessages.Insert("Morning might give me a chance.");
            DawnMessages.Insert("Surviving the night still counts.");
        }

        if (!MorningMessages)
            MorningMessages = new array<string>;

        if (MorningMessages.Count() == 0)
        {
            MorningMessages.Insert("Morning means movement.");
            MorningMessages.Insert("Others will be looking for supplies now.");
            MorningMessages.Insert("The day is starting whether I am ready or not.");
            MorningMessages.Insert("I should use the light while I have it.");
        }

        if (!NoonMessages)
            NoonMessages = new array<string>;

        if (NoonMessages.Count() == 0)
        {
            NoonMessages.Insert("The dark makes every sound feel closer.");
            NoonMessages.Insert("I cannot see far enough to feel safe.");
            NoonMessages.Insert("Night belongs to whoever moves quietly.");
            NoonMessages.Insert("I should slow down and listen.");
        }

        if (!AfternoonMessages)
            AfternoonMessages = new array<string>;

        if (AfternoonMessages.Count() == 0)
        {
            AfternoonMessages.Insert("The dark makes every sound feel closer.");
            AfternoonMessages.Insert("I cannot see far enough to feel safe.");
            AfternoonMessages.Insert("Night belongs to whoever moves quietly.");
            AfternoonMessages.Insert("I should slow down and listen.");
        }

        if (!DuskMessages)
            DuskMessages = new array<string>;

        if (DuskMessages.Count() == 0)
        {
            DuskMessages.Insert("The light is fading fast.");
            DuskMessages.Insert("I need to decide where I am spending the night.");
            DuskMessages.Insert("Dusk makes every town feel worse.");
            DuskMessages.Insert("Night is coming, and I am not ready.");
        }

        if (!NightMessages)
            NightMessages = new array<string>;

        if (NightMessages.Count() == 0)
        {
            NightMessages.Insert("The dark makes every sound feel closer.");
            NightMessages.Insert("I cannot see far enough to feel safe.");
            NightMessages.Insert("Night belongs to whoever moves quietly.");
            NightMessages.Insert("I should slow down and listen.");
        }

        if (!MidnightMessages)
            MidnightMessages = new array<string>;

        if (MidnightMessages.Count() == 0)
        {
            MidnightMessages.Insert("The dark makes every sound feel closer.");
            MidnightMessages.Insert("I cannot see far enough to feel safe.");
            MidnightMessages.Insert("Night belongs to whoever moves quietly.");
            MidnightMessages.Insert("I should slow down and listen.");
        }

        if (!EarlyMorningMessages)
            EarlyMorningMessages = new array<string>;

        if (EarlyMorningMessages.Count() == 0)
        {
            EarlyMorningMessages.Insert("The dark makes every sound feel closer.");
            EarlyMorningMessages.Insert("I cannot see far enough to feel safe.");
            EarlyMorningMessages.Insert("Night belongs to whoever moves quietly.");
            EarlyMorningMessages.Insert("I should slow down and listen.");
        }

        if (!ItemBadlyDamagedMessages)
            ItemBadlyDamagedMessages = new array<string>;

        if (ItemBadlyDamagedMessages.Count() == 0)
        {
            ItemBadlyDamagedMessages.Insert("This gear will not last much longer.");
            ItemBadlyDamagedMessages.Insert("I should repair this before it fails.");
            ItemBadlyDamagedMessages.Insert("Bad equipment gets people killed.");
            ItemBadlyDamagedMessages.Insert("Everything I own is wearing down.");
        }

        if (!ItemWeaponDamagedMessages)
            ItemWeaponDamagedMessages = new array<string>;

        if (ItemWeaponDamagedMessages.Count() == 0)
        {
            ItemWeaponDamagedMessages.Insert("This gear will not last much longer.");
            ItemWeaponDamagedMessages.Insert("I should repair this before it fails.");
            ItemWeaponDamagedMessages.Insert("Bad equipment gets people killed.");
            ItemWeaponDamagedMessages.Insert("Everything I own is wearing down.");
        }

        if (!ItemShoesDamagedMessages)
            ItemShoesDamagedMessages = new array<string>;

        if (ItemShoesDamagedMessages.Count() == 0)
        {
            ItemShoesDamagedMessages.Insert("This gear will not last much longer.");
            ItemShoesDamagedMessages.Insert("I should repair this before it fails.");
            ItemShoesDamagedMessages.Insert("Bad equipment gets people killed.");
            ItemShoesDamagedMessages.Insert("Everything I own is wearing down.");
        }

        if (!ItemClothingDamagedMessages)
            ItemClothingDamagedMessages = new array<string>;

        if (ItemClothingDamagedMessages.Count() == 0)
        {
            ItemClothingDamagedMessages.Insert("This gear will not last much longer.");
            ItemClothingDamagedMessages.Insert("I should repair this before it fails.");
            ItemClothingDamagedMessages.Insert("Bad equipment gets people killed.");
            ItemClothingDamagedMessages.Insert("Everything I own is wearing down.");
        }

        if (!ItemBackpackDamagedMessages)
            ItemBackpackDamagedMessages = new array<string>;

        if (ItemBackpackDamagedMessages.Count() == 0)
        {
            ItemBackpackDamagedMessages.Insert("This gear will not last much longer.");
            ItemBackpackDamagedMessages.Insert("I should repair this before it fails.");
            ItemBackpackDamagedMessages.Insert("Bad equipment gets people killed.");
            ItemBackpackDamagedMessages.Insert("Everything I own is wearing down.");
        }

        if (!ItemVestDamagedMessages)
            ItemVestDamagedMessages = new array<string>;

        if (ItemVestDamagedMessages.Count() == 0)
        {
            ItemVestDamagedMessages.Insert("This gear will not last much longer.");
            ItemVestDamagedMessages.Insert("I should repair this before it fails.");
            ItemVestDamagedMessages.Insert("Bad equipment gets people killed.");
            ItemVestDamagedMessages.Insert("Everything I own is wearing down.");
        }

        if (!ItemHeadgearDamagedMessages)
            ItemHeadgearDamagedMessages = new array<string>;

        if (ItemHeadgearDamagedMessages.Count() == 0)
        {
            ItemHeadgearDamagedMessages.Insert("This gear will not last much longer.");
            ItemHeadgearDamagedMessages.Insert("I should repair this before it fails.");
            ItemHeadgearDamagedMessages.Insert("Bad equipment gets people killed.");
            ItemHeadgearDamagedMessages.Insert("Everything I own is wearing down.");
        }

        if (!ItemGlovesDamagedMessages)
            ItemGlovesDamagedMessages = new array<string>;

        if (ItemGlovesDamagedMessages.Count() == 0)
        {
            ItemGlovesDamagedMessages.Insert("This gear will not last much longer.");
            ItemGlovesDamagedMessages.Insert("I should repair this before it fails.");
            ItemGlovesDamagedMessages.Insert("Bad equipment gets people killed.");
            ItemGlovesDamagedMessages.Insert("Everything I own is wearing down.");
        }

        if (!ItemMaskDamagedMessages)
            ItemMaskDamagedMessages = new array<string>;

        if (ItemMaskDamagedMessages.Count() == 0)
        {
            ItemMaskDamagedMessages.Insert("This gear will not last much longer.");
            ItemMaskDamagedMessages.Insert("I should repair this before it fails.");
            ItemMaskDamagedMessages.Insert("Bad equipment gets people killed.");
            ItemMaskDamagedMessages.Insert("Everything I own is wearing down.");
        }

        if (!ItemBeltDamagedMessages)
            ItemBeltDamagedMessages = new array<string>;

        if (ItemBeltDamagedMessages.Count() == 0)
        {
            ItemBeltDamagedMessages.Insert("This gear will not last much longer.");
            ItemBeltDamagedMessages.Insert("I should repair this before it fails.");
            ItemBeltDamagedMessages.Insert("Bad equipment gets people killed.");
            ItemBeltDamagedMessages.Insert("Everything I own is wearing down.");
        }

        if (!CombatStressMessages)
            CombatStressMessages = new array<string>;

        if (CombatStressMessages.Count() == 0)
        {
            CombatStressMessages.Insert("That was too close.");
            CombatStressMessages.Insert("Move. Breathe. Find cover.");
            CombatStressMessages.Insert("My hands are shaking.");
            CombatStressMessages.Insert("I need to stay alive for the next few seconds.");
        }

        if (!CombatHitMessages)
            CombatHitMessages = new array<string>;

        if (CombatHitMessages.Count() == 0)
        {
            CombatHitMessages.Insert("That was too close.");
            CombatHitMessages.Insert("Move. Breathe. Find cover.");
            CombatHitMessages.Insert("My hands are shaking.");
            CombatHitMessages.Insert("I need to stay alive for the next few seconds.");
        }

        if (!CombatShockMessages)
            CombatShockMessages = new array<string>;

        if (CombatShockMessages.Count() == 0)
        {
            CombatShockMessages.Insert("That was too close.");
            CombatShockMessages.Insert("Move. Breathe. Find cover.");
            CombatShockMessages.Insert("My hands are shaking.");
            CombatShockMessages.Insert("I need to stay alive for the next few seconds.");
        }

        if (!ZombieHitMessages)
            ZombieHitMessages = new array<string>;

        if (ZombieHitMessages.Count() == 0)
        {
            ZombieHitMessages.Insert("That was too close.");
            ZombieHitMessages.Insert("Move. Breathe. Find cover.");
            ZombieHitMessages.Insert("My hands are shaking.");
            ZombieHitMessages.Insert("I need to stay alive for the next few seconds.");
        }

        if (!PlayerMeleeHitMessages)
            PlayerMeleeHitMessages = new array<string>;

        if (PlayerMeleeHitMessages.Count() == 0)
        {
            PlayerMeleeHitMessages.Insert("That was too close.");
            PlayerMeleeHitMessages.Insert("Move. Breathe. Find cover.");
            PlayerMeleeHitMessages.Insert("My hands are shaking.");
            PlayerMeleeHitMessages.Insert("I need to stay alive for the next few seconds.");
        }

        if (!GunshotHitMessages)
            GunshotHitMessages = new array<string>;

        if (GunshotHitMessages.Count() == 0)
        {
            GunshotHitMessages.Insert("That was too close.");
            GunshotHitMessages.Insert("Move. Breathe. Find cover.");
            GunshotHitMessages.Insert("My hands are shaking.");
            GunshotHitMessages.Insert("I need to stay alive for the next few seconds.");
        }

        if (!ExplosionHitMessages)
            ExplosionHitMessages = new array<string>;

        if (ExplosionHitMessages.Count() == 0)
        {
            ExplosionHitMessages.Insert("That was too close.");
            ExplosionHitMessages.Insert("Move. Breathe. Find cover.");
            ExplosionHitMessages.Insert("My hands are shaking.");
            ExplosionHitMessages.Insert("I need to stay alive for the next few seconds.");
        }

        if (!HeavyHitMessages)
            HeavyHitMessages = new array<string>;

        if (HeavyHitMessages.Count() == 0)
        {
            HeavyHitMessages.Insert("That was too close.");
            HeavyHitMessages.Insert("Move. Breathe. Find cover.");
            HeavyHitMessages.Insert("My hands are shaking.");
            HeavyHitMessages.Insert("I need to stay alive for the next few seconds.");
        }

        if (!BleedingStartedMessages)
            BleedingStartedMessages = new array<string>;

        if (BleedingStartedMessages.Count() == 0)
        {
            BleedingStartedMessages.Insert("I am losing blood.");
            BleedingStartedMessages.Insert("I need to stop this before it gets worse.");
            BleedingStartedMessages.Insert("Warmth is leaving with every drop.");
            BleedingStartedMessages.Insert("Pressure first. Panic later.");
        }

    }

    void ST_EnsureStarterMessageDefaults_6()
    {
        if (!BleedingWorseMessages)
            BleedingWorseMessages = new array<string>;

        if (BleedingWorseMessages.Count() == 0)
        {
            BleedingWorseMessages.Insert("I am losing blood.");
            BleedingWorseMessages.Insert("I need to stop this before it gets worse.");
            BleedingWorseMessages.Insert("Warmth is leaving with every drop.");
            BleedingWorseMessages.Insert("Pressure first. Panic later.");
        }

        if (!BleedingStoppedMessages)
            BleedingStoppedMessages = new array<string>;

        if (BleedingStoppedMessages.Count() == 0)
        {
            BleedingStoppedMessages.Insert("I am losing blood.");
            BleedingStoppedMessages.Insert("I need to stop this before it gets worse.");
            BleedingStoppedMessages.Insert("Warmth is leaving with every drop.");
            BleedingStoppedMessages.Insert("Pressure first. Panic later.");
        }

        if (!ContaminatedZoneMessages)
            ContaminatedZoneMessages = new array<string>;

        if (ContaminatedZoneMessages.Count() == 0)
        {
            ContaminatedZoneMessages.Insert("The air is wrong here.");
            ContaminatedZoneMessages.Insert("I need to check my protection.");
            ContaminatedZoneMessages.Insert("This place is not safe to breathe.");
            ContaminatedZoneMessages.Insert("I should not stay in this contamination.");
        }

        if (!NearbyCorpseMessages)
            NearbyCorpseMessages = new array<string>;

        if (NearbyCorpseMessages.Count() == 0)
        {
            NearbyCorpseMessages.Insert("Someone died here.");
            NearbyCorpseMessages.Insert("Bodies mean danger came through already.");
            NearbyCorpseMessages.Insert("I should not stay near this.");
            NearbyCorpseMessages.Insert("Where there is one corpse, there may be another.");
        }

        if (!NearbyPlayerCorpseMessages)
            NearbyPlayerCorpseMessages = new array<string>;

        if (NearbyPlayerCorpseMessages.Count() == 0)
        {
            NearbyPlayerCorpseMessages.Insert("Someone died here.");
            NearbyPlayerCorpseMessages.Insert("Bodies mean danger came through already.");
            NearbyPlayerCorpseMessages.Insert("I should not stay near this.");
            NearbyPlayerCorpseMessages.Insert("Where there is one corpse, there may be another.");
        }

        if (!NearbyInfectedCorpseMessages)
            NearbyInfectedCorpseMessages = new array<string>;

        if (NearbyInfectedCorpseMessages.Count() == 0)
        {
            NearbyInfectedCorpseMessages.Insert("Infected are too close.");
            NearbyInfectedCorpseMessages.Insert("I need to move quietly.");
            NearbyInfectedCorpseMessages.Insert("One wrong noise and they will be on me.");
            NearbyInfectedCorpseMessages.Insert("I can hear them nearby.");
        }

        if (!NearbyAnimalCorpseMessages)
            NearbyAnimalCorpseMessages = new array<string>;

        if (NearbyAnimalCorpseMessages.Count() == 0)
        {
            NearbyAnimalCorpseMessages.Insert("Someone died here.");
            NearbyAnimalCorpseMessages.Insert("Bodies mean danger came through already.");
            NearbyAnimalCorpseMessages.Insert("I should not stay near this.");
            NearbyAnimalCorpseMessages.Insert("Where there is one corpse, there may be another.");
        }

        if (!PersonalityPracticalMessages)
            PersonalityPracticalMessages = new array<string>;

        if (PersonalityPracticalMessages.Count() == 0)
        {
            PersonalityPracticalMessages.Insert("Priorities first. Water, food, shelter.");
            PersonalityPracticalMessages.Insert("Check supplies, check exits, keep moving.");
            PersonalityPracticalMessages.Insert("Do not waste energy.");
            PersonalityPracticalMessages.Insert("Solve the next problem.");
        }

        if (!PersonalityScaredMessages)
            PersonalityScaredMessages = new array<string>;

        if (PersonalityScaredMessages.Count() == 0)
        {
            PersonalityScaredMessages.Insert("I hate this place.");
            PersonalityScaredMessages.Insert("Every sound feels too close.");
            PersonalityScaredMessages.Insert("I do not want to die here.");
            PersonalityScaredMessages.Insert("Something is watching. It has to be.");
        }

        if (!PersonalityMilitaryMessages)
            PersonalityMilitaryMessages = new array<string>;

        if (PersonalityMilitaryMessages.Count() == 0)
        {
            PersonalityMilitaryMessages.Insert("Good gear brings bad company.");
            PersonalityMilitaryMessages.Insert("Someone else will come here armed.");
            PersonalityMilitaryMessages.Insert("I should assume I am being watched.");
            PersonalityMilitaryMessages.Insert("Military places never feel abandoned.");
        }

        if (!PersonalityHopelessMessages)
            PersonalityHopelessMessages = new array<string>;

        if (PersonalityHopelessMessages.Count() == 0)
        {
            PersonalityHopelessMessages.Insert("This place takes everything eventually.");
            PersonalityHopelessMessages.Insert("I am tired of pretending this gets better.");
            PersonalityHopelessMessages.Insert("Maybe surviving is just a slower way to lose.");
            PersonalityHopelessMessages.Insert("Keep walking. That is all I have left.");
        }

        if (!PersonalityAggressiveMessages)
            PersonalityAggressiveMessages = new array<string>;

        if (PersonalityAggressiveMessages.Count() == 0)
        {
            PersonalityAggressiveMessages.Insert("Hit first if it comes to it.");
            PersonalityAggressiveMessages.Insert("Fear makes people slow.");
            PersonalityAggressiveMessages.Insert("I will not be easy prey.");
            PersonalityAggressiveMessages.Insert("Let them make the first mistake.");
        }

        if (!PersonalityCalmMessages)
            PersonalityCalmMessages = new array<string>;

        if (PersonalityCalmMessages.Count() == 0)
        {
            PersonalityCalmMessages.Insert("Breathe. Think. Move.");
            PersonalityCalmMessages.Insert("Panic wastes strength.");
            PersonalityCalmMessages.Insert("One problem at a time.");
            PersonalityCalmMessages.Insert("There is still a way through this.");
        }

        if (!EnergyStage1Messages)
            EnergyStage1Messages = new array<string>;

        if (EnergyStage1Messages.Count() == 0)
        {
            EnergyStage1Messages.Insert("My stomach is turning against me.");
            EnergyStage1Messages.Insert("I need food before my strength goes.");
            EnergyStage1Messages.Insert("Every step costs more than I have.");
            EnergyStage1Messages.Insert("I cannot run on nothing much longer.");
        }

        if (!EnergyStage2Messages)
            EnergyStage2Messages = new array<string>;

        if (EnergyStage2Messages.Count() == 0)
        {
            EnergyStage2Messages.Insert("My stomach is turning against me.");
            EnergyStage2Messages.Insert("I need food before my strength goes.");
            EnergyStage2Messages.Insert("Every step costs more than I have.");
            EnergyStage2Messages.Insert("I cannot run on nothing much longer.");
        }

        if (!EnergyStage3Messages)
            EnergyStage3Messages = new array<string>;

        if (EnergyStage3Messages.Count() == 0)
        {
            EnergyStage3Messages.Insert("My stomach is turning against me.");
            EnergyStage3Messages.Insert("I need food before my strength goes.");
            EnergyStage3Messages.Insert("Every step costs more than I have.");
            EnergyStage3Messages.Insert("I cannot run on nothing much longer.");
        }

        if (!EnergyStage4Messages)
            EnergyStage4Messages = new array<string>;

        if (EnergyStage4Messages.Count() == 0)
        {
            EnergyStage4Messages.Insert("My stomach is turning against me.");
            EnergyStage4Messages.Insert("I need food before my strength goes.");
            EnergyStage4Messages.Insert("Every step costs more than I have.");
            EnergyStage4Messages.Insert("I cannot run on nothing much longer.");
        }

        if (!WaterStage1Messages)
            WaterStage1Messages = new array<string>;

        if (WaterStage1Messages.Count() == 0)
        {
            WaterStage1Messages.Insert("My mouth is too dry.");
            WaterStage1Messages.Insert("I need water soon.");
            WaterStage1Messages.Insert("Dehydration is starting to slow my thoughts.");
            WaterStage1Messages.Insert("I have to find something safe to drink.");
        }

        if (!WaterStage2Messages)
            WaterStage2Messages = new array<string>;

        if (WaterStage2Messages.Count() == 0)
        {
            WaterStage2Messages.Insert("My mouth is too dry.");
            WaterStage2Messages.Insert("I need water soon.");
            WaterStage2Messages.Insert("Dehydration is starting to slow my thoughts.");
            WaterStage2Messages.Insert("I have to find something safe to drink.");
        }

        if (!WaterStage3Messages)
            WaterStage3Messages = new array<string>;

        if (WaterStage3Messages.Count() == 0)
        {
            WaterStage3Messages.Insert("My mouth is too dry.");
            WaterStage3Messages.Insert("I need water soon.");
            WaterStage3Messages.Insert("Dehydration is starting to slow my thoughts.");
            WaterStage3Messages.Insert("I have to find something safe to drink.");
        }

        if (!WaterStage4Messages)
            WaterStage4Messages = new array<string>;

        if (WaterStage4Messages.Count() == 0)
        {
            WaterStage4Messages.Insert("My mouth is too dry.");
            WaterStage4Messages.Insert("I need water soon.");
            WaterStage4Messages.Insert("Dehydration is starting to slow my thoughts.");
            WaterStage4Messages.Insert("I have to find something safe to drink.");
        }

        if (!BloodStage1Messages)
            BloodStage1Messages = new array<string>;

        if (BloodStage1Messages.Count() == 0)
        {
            BloodStage1Messages.Insert("I am losing blood.");
            BloodStage1Messages.Insert("I need to stop this before it gets worse.");
            BloodStage1Messages.Insert("Warmth is leaving with every drop.");
            BloodStage1Messages.Insert("Pressure first. Panic later.");
        }

        if (!BloodStage2Messages)
            BloodStage2Messages = new array<string>;

        if (BloodStage2Messages.Count() == 0)
        {
            BloodStage2Messages.Insert("I am losing blood.");
            BloodStage2Messages.Insert("I need to stop this before it gets worse.");
            BloodStage2Messages.Insert("Warmth is leaving with every drop.");
            BloodStage2Messages.Insert("Pressure first. Panic later.");
        }

        if (!BloodStage3Messages)
            BloodStage3Messages = new array<string>;

        if (BloodStage3Messages.Count() == 0)
        {
            BloodStage3Messages.Insert("I am losing blood.");
            BloodStage3Messages.Insert("I need to stop this before it gets worse.");
            BloodStage3Messages.Insert("Warmth is leaving with every drop.");
            BloodStage3Messages.Insert("Pressure first. Panic later.");
        }

        if (!BloodStage4Messages)
            BloodStage4Messages = new array<string>;

        if (BloodStage4Messages.Count() == 0)
        {
            BloodStage4Messages.Insert("I am losing blood.");
            BloodStage4Messages.Insert("I need to stop this before it gets worse.");
            BloodStage4Messages.Insert("Warmth is leaving with every drop.");
            BloodStage4Messages.Insert("Pressure first. Panic later.");
        }

        if (!ShockStage1Messages)
            ShockStage1Messages = new array<string>;

        if (ShockStage1Messages.Count() == 0)
        {
            ShockStage1Messages.Insert("That was too close.");
            ShockStage1Messages.Insert("Move. Breathe. Find cover.");
            ShockStage1Messages.Insert("My hands are shaking.");
            ShockStage1Messages.Insert("I need to stay alive for the next few seconds.");
        }

        if (!ShockStage2Messages)
            ShockStage2Messages = new array<string>;

        if (ShockStage2Messages.Count() == 0)
        {
            ShockStage2Messages.Insert("That was too close.");
            ShockStage2Messages.Insert("Move. Breathe. Find cover.");
            ShockStage2Messages.Insert("My hands are shaking.");
            ShockStage2Messages.Insert("I need to stay alive for the next few seconds.");
        }

        if (!ShockStage3Messages)
            ShockStage3Messages = new array<string>;

        if (ShockStage3Messages.Count() == 0)
        {
            ShockStage3Messages.Insert("That was too close.");
            ShockStage3Messages.Insert("Move. Breathe. Find cover.");
            ShockStage3Messages.Insert("My hands are shaking.");
            ShockStage3Messages.Insert("I need to stay alive for the next few seconds.");
        }

        if (!ShockStage4Messages)
            ShockStage4Messages = new array<string>;

        if (ShockStage4Messages.Count() == 0)
        {
            ShockStage4Messages.Insert("That was too close.");
            ShockStage4Messages.Insert("Move. Breathe. Find cover.");
            ShockStage4Messages.Insert("My hands are shaking.");
            ShockStage4Messages.Insert("I need to stay alive for the next few seconds.");
        }

        if (!Cold_Mild_Messages)
            Cold_Mild_Messages = new array<string>;

        if (Cold_Mild_Messages.Count() == 0)
        {
            Cold_Mild_Messages.Insert("The cold is getting into my bones.");
            Cold_Mild_Messages.Insert("I need warmth before this gets worse.");
            Cold_Mild_Messages.Insert("My fingers are stiff.");
            Cold_Mild_Messages.Insert("Shelter and heat. That is all that matters.");
        }

        if (!Cold_Moderate_Messages)
            Cold_Moderate_Messages = new array<string>;

        if (Cold_Moderate_Messages.Count() == 0)
        {
            Cold_Moderate_Messages.Insert("The cold is getting into my bones.");
            Cold_Moderate_Messages.Insert("I need warmth before this gets worse.");
            Cold_Moderate_Messages.Insert("My fingers are stiff.");
            Cold_Moderate_Messages.Insert("Shelter and heat. That is all that matters.");
        }

        if (!Cold_Severe_Messages)
            Cold_Severe_Messages = new array<string>;

        if (Cold_Severe_Messages.Count() == 0)
        {
            Cold_Severe_Messages.Insert("The cold is getting into my bones.");
            Cold_Severe_Messages.Insert("I need warmth before this gets worse.");
            Cold_Severe_Messages.Insert("My fingers are stiff.");
            Cold_Severe_Messages.Insert("Shelter and heat. That is all that matters.");
        }

        if (!Cold_Critical_Messages)
            Cold_Critical_Messages = new array<string>;

        if (Cold_Critical_Messages.Count() == 0)
        {
            Cold_Critical_Messages.Insert("The cold is getting into my bones.");
            Cold_Critical_Messages.Insert("I need warmth before this gets worse.");
            Cold_Critical_Messages.Insert("My fingers are stiff.");
            Cold_Critical_Messages.Insert("Shelter and heat. That is all that matters.");
        }

        if (!Hot_Mild_Messages)
            Hot_Mild_Messages = new array<string>;

        if (Hot_Mild_Messages.Count() == 0)
        {
            Hot_Mild_Messages.Insert("The heat is draining me.");
            Hot_Mild_Messages.Insert("I need shade or water.");
            Hot_Mild_Messages.Insert("My head feels heavy.");
            Hot_Mild_Messages.Insert("I am overheating out here.");
        }

        if (!Hot_Moderate_Messages)
            Hot_Moderate_Messages = new array<string>;

        if (Hot_Moderate_Messages.Count() == 0)
        {
            Hot_Moderate_Messages.Insert("The heat is draining me.");
            Hot_Moderate_Messages.Insert("I need shade or water.");
            Hot_Moderate_Messages.Insert("My head feels heavy.");
            Hot_Moderate_Messages.Insert("I am overheating out here.");
        }

        if (!Hot_Severe_Messages)
            Hot_Severe_Messages = new array<string>;

        if (Hot_Severe_Messages.Count() == 0)
        {
            Hot_Severe_Messages.Insert("The heat is draining me.");
            Hot_Severe_Messages.Insert("I need shade or water.");
            Hot_Severe_Messages.Insert("My head feels heavy.");
            Hot_Severe_Messages.Insert("I am overheating out here.");
        }

        if (!Hot_Critical_Messages)
            Hot_Critical_Messages = new array<string>;

        if (Hot_Critical_Messages.Count() == 0)
        {
            Hot_Critical_Messages.Insert("The heat is draining me.");
            Hot_Critical_Messages.Insert("I need shade or water.");
            Hot_Critical_Messages.Insert("My head feels heavy.");
            Hot_Critical_Messages.Insert("I am overheating out here.");
        }

        if (!Sickness_Early_Messages)
            Sickness_Early_Messages = new array<string>;

        if (Sickness_Early_Messages.Count() == 0)
        {
            Sickness_Early_Messages.Insert("Something is wrong inside me.");
            Sickness_Early_Messages.Insert("I need medicine before this gets worse.");
            Sickness_Early_Messages.Insert("My body is fighting and losing ground.");
            Sickness_Early_Messages.Insert("This sickness is stealing my strength.");
        }

        if (!Sickness_Moderate_Messages)
            Sickness_Moderate_Messages = new array<string>;

        if (Sickness_Moderate_Messages.Count() == 0)
        {
            Sickness_Moderate_Messages.Insert("Something is wrong inside me.");
            Sickness_Moderate_Messages.Insert("I need medicine before this gets worse.");
            Sickness_Moderate_Messages.Insert("My body is fighting and losing ground.");
            Sickness_Moderate_Messages.Insert("This sickness is stealing my strength.");
        }

        if (!Sickness_Severe_Messages)
            Sickness_Severe_Messages = new array<string>;

        if (Sickness_Severe_Messages.Count() == 0)
        {
            Sickness_Severe_Messages.Insert("Something is wrong inside me.");
            Sickness_Severe_Messages.Insert("I need medicine before this gets worse.");
            Sickness_Severe_Messages.Insert("My body is fighting and losing ground.");
            Sickness_Severe_Messages.Insert("This sickness is stealing my strength.");
        }

    }

    void ST_EnsureStarterMessageDefaults_7()
    {
        if (!Sickness_Critical_Messages)
            Sickness_Critical_Messages = new array<string>;

        if (Sickness_Critical_Messages.Count() == 0)
        {
            Sickness_Critical_Messages.Insert("Something is wrong inside me.");
            Sickness_Critical_Messages.Insert("I need medicine before this gets worse.");
            Sickness_Critical_Messages.Insert("My body is fighting and losing ground.");
            Sickness_Critical_Messages.Insert("This sickness is stealing my strength.");
        }

        if (!Bleeding_One_Messages)
            Bleeding_One_Messages = new array<string>;

        if (Bleeding_One_Messages.Count() == 0)
        {
            Bleeding_One_Messages.Insert("I am losing blood.");
            Bleeding_One_Messages.Insert("I need to stop this before it gets worse.");
            Bleeding_One_Messages.Insert("Warmth is leaving with every drop.");
            Bleeding_One_Messages.Insert("Pressure first. Panic later.");
        }

        if (!Bleeding_Multiple_Messages)
            Bleeding_Multiple_Messages = new array<string>;

        if (Bleeding_Multiple_Messages.Count() == 0)
        {
            Bleeding_Multiple_Messages.Insert("I am losing blood.");
            Bleeding_Multiple_Messages.Insert("I need to stop this before it gets worse.");
            Bleeding_Multiple_Messages.Insert("Warmth is leaving with every drop.");
            Bleeding_Multiple_Messages.Insert("Pressure first. Panic later.");
        }

        if (!Bleeding_Critical_Messages)
            Bleeding_Critical_Messages = new array<string>;

        if (Bleeding_Critical_Messages.Count() == 0)
        {
            Bleeding_Critical_Messages.Insert("I am losing blood.");
            Bleeding_Critical_Messages.Insert("I need to stop this before it gets worse.");
            Bleeding_Critical_Messages.Insert("Warmth is leaving with every drop.");
            Bleeding_Critical_Messages.Insert("Pressure first. Panic later.");
        }

        if (!BrokenLegMessages)
            BrokenLegMessages = new array<string>;

        if (BrokenLegMessages.Count() == 0)
        {
            BrokenLegMessages.Insert("I cannot move like this.");
            BrokenLegMessages.Insert("Every step is a mistake.");
            BrokenLegMessages.Insert("I need cover before something hears me.");
            BrokenLegMessages.Insert("A broken leg out here can be a death sentence.");
        }

        if (!Infected_Far_Messages)
            Infected_Far_Messages = new array<string>;

        if (Infected_Far_Messages.Count() == 0)
        {
            Infected_Far_Messages.Insert("Infected are too close.");
            Infected_Far_Messages.Insert("I need to move quietly.");
            Infected_Far_Messages.Insert("One wrong noise and they will be on me.");
            Infected_Far_Messages.Insert("I can hear them nearby.");
        }

        if (!Infected_Close_Messages)
            Infected_Close_Messages = new array<string>;

        if (Infected_Close_Messages.Count() == 0)
        {
            Infected_Close_Messages.Insert("Infected are too close.");
            Infected_Close_Messages.Insert("I need to move quietly.");
            Infected_Close_Messages.Insert("One wrong noise and they will be on me.");
            Infected_Close_Messages.Insert("I can hear them nearby.");
        }

        if (!Infected_VeryClose_Messages)
            Infected_VeryClose_Messages = new array<string>;

        if (Infected_VeryClose_Messages.Count() == 0)
        {
            Infected_VeryClose_Messages.Insert("Infected are too close.");
            Infected_VeryClose_Messages.Insert("I need to move quietly.");
            Infected_VeryClose_Messages.Insert("One wrong noise and they will be on me.");
            Infected_VeryClose_Messages.Insert("I can hear them nearby.");
        }

        if (!Infected_Surrounded_Messages)
            Infected_Surrounded_Messages = new array<string>;

        if (Infected_Surrounded_Messages.Count() == 0)
        {
            Infected_Surrounded_Messages.Insert("Infected are too close.");
            Infected_Surrounded_Messages.Insert("I need to move quietly.");
            Infected_Surrounded_Messages.Insert("One wrong noise and they will be on me.");
            Infected_Surrounded_Messages.Insert("I can hear them nearby.");
        }

        if (!EatingMessages)
            EatingMessages = new array<string>;

        if (EatingMessages.Count() == 0)
        {
            EatingMessages.Insert("Done. Keep moving.");
            EatingMessages.Insert("That might help for now.");
            EatingMessages.Insert("Small tasks keep me alive.");
            EatingMessages.Insert("One more thing handled.");
        }

        if (!DrinkingMessages)
            DrinkingMessages = new array<string>;

        if (DrinkingMessages.Count() == 0)
        {
            DrinkingMessages.Insert("Done. Keep moving.");
            DrinkingMessages.Insert("That might help for now.");
            DrinkingMessages.Insert("Small tasks keep me alive.");
            DrinkingMessages.Insert("One more thing handled.");
        }

        if (!UnsafeDrinkingMessages)
            UnsafeDrinkingMessages = new array<string>;

        if (UnsafeDrinkingMessages.Count() == 0)
        {
            UnsafeDrinkingMessages.Insert("Done. Keep moving.");
            UnsafeDrinkingMessages.Insert("That might help for now.");
            UnsafeDrinkingMessages.Insert("Small tasks keep me alive.");
            UnsafeDrinkingMessages.Insert("One more thing handled.");
        }

        if (!UnjamMessages)
            UnjamMessages = new array<string>;

        if (UnjamMessages.Count() == 0)
        {
            UnjamMessages.Insert("Done. Keep moving.");
            UnjamMessages.Insert("That might help for now.");
            UnjamMessages.Insert("Small tasks keep me alive.");
            UnjamMessages.Insert("One more thing handled.");
        }

        if (!UnjamSuccessMessages)
            UnjamSuccessMessages = new array<string>;

        if (UnjamSuccessMessages.Count() == 0)
        {
            UnjamSuccessMessages.Insert("Done. Keep moving.");
            UnjamSuccessMessages.Insert("That might help for now.");
            UnjamSuccessMessages.Insert("Small tasks keep me alive.");
            UnjamSuccessMessages.Insert("One more thing handled.");
        }

        if (!SkinningAnimalMessages)
            SkinningAnimalMessages = new array<string>;

        if (SkinningAnimalMessages.Count() == 0)
        {
            SkinningAnimalMessages.Insert("Done. Keep moving.");
            SkinningAnimalMessages.Insert("That might help for now.");
            SkinningAnimalMessages.Insert("Small tasks keep me alive.");
            SkinningAnimalMessages.Insert("One more thing handled.");
        }

        if (!SkinningHumanMessages)
            SkinningHumanMessages = new array<string>;

        if (SkinningHumanMessages.Count() == 0)
        {
            SkinningHumanMessages.Insert("Done. Keep moving.");
            SkinningHumanMessages.Insert("That might help for now.");
            SkinningHumanMessages.Insert("Small tasks keep me alive.");
            SkinningHumanMessages.Insert("One more thing handled.");
        }

        if (!BandagingMessages)
            BandagingMessages = new array<string>;

        if (BandagingMessages.Count() == 0)
        {
            BandagingMessages.Insert("Done. Keep moving.");
            BandagingMessages.Insert("That might help for now.");
            BandagingMessages.Insert("Small tasks keep me alive.");
            BandagingMessages.Insert("One more thing handled.");
        }

        if (!BandageSuccessMessages)
            BandageSuccessMessages = new array<string>;

        if (BandageSuccessMessages.Count() == 0)
        {
            BandageSuccessMessages.Insert("Done. Keep moving.");
            BandageSuccessMessages.Insert("That might help for now.");
            BandageSuccessMessages.Insert("Small tasks keep me alive.");
            BandageSuccessMessages.Insert("One more thing handled.");
        }

        if (!FireStartingMessages)
            FireStartingMessages = new array<string>;

        if (FireStartingMessages.Count() == 0)
        {
            FireStartingMessages.Insert("Done. Keep moving.");
            FireStartingMessages.Insert("That might help for now.");
            FireStartingMessages.Insert("Small tasks keep me alive.");
            FireStartingMessages.Insert("One more thing handled.");
        }

        if (!CookingMessages)
            CookingMessages = new array<string>;

        if (CookingMessages.Count() == 0)
        {
            CookingMessages.Insert("Done. Keep moving.");
            CookingMessages.Insert("That might help for now.");
            CookingMessages.Insert("Small tasks keep me alive.");
            CookingMessages.Insert("One more thing handled.");
        }

        if (!FishingMessages)
            FishingMessages = new array<string>;

        if (FishingMessages.Count() == 0)
        {
            FishingMessages.Insert("Done. Keep moving.");
            FishingMessages.Insert("That might help for now.");
            FishingMessages.Insert("Small tasks keep me alive.");
            FishingMessages.Insert("One more thing handled.");
        }

        if (!RepairMessages)
            RepairMessages = new array<string>;

        if (RepairMessages.Count() == 0)
        {
            RepairMessages.Insert("Done. Keep moving.");
            RepairMessages.Insert("That might help for now.");
            RepairMessages.Insert("Small tasks keep me alive.");
            RepairMessages.Insert("One more thing handled.");
        }

        if (!GeneralActionMessages)
            GeneralActionMessages = new array<string>;

        if (GeneralActionMessages.Count() == 0)
        {
            GeneralActionMessages.Insert("Done. Keep moving.");
            GeneralActionMessages.Insert("That might help for now.");
            GeneralActionMessages.Insert("Small tasks keep me alive.");
            GeneralActionMessages.Insert("One more thing handled.");
        }

        if (!OpenCloseActionMessages)
            OpenCloseActionMessages = new array<string>;

        if (OpenCloseActionMessages.Count() == 0)
        {
            OpenCloseActionMessages.Insert("Another doorway. Keep moving.");
            OpenCloseActionMessages.Insert("I should not linger in the open.");
            OpenCloseActionMessages.Insert("Every door could hide trouble.");
            OpenCloseActionMessages.Insert("Quietly. I do not know what is beyond this.");
        }

        if (!MedicineConsumeMessages)
            MedicineConsumeMessages = new array<string>;

        if (MedicineConsumeMessages.Count() == 0)
        {
            MedicineConsumeMessages.Insert("This medicine consume is getting to me.");
            MedicineConsumeMessages.Insert("I need to pay attention to this medicine consume.");
            MedicineConsumeMessages.Insert("Something about this medicine consume feels wrong.");
            MedicineConsumeMessages.Insert("I should not ignore this medicine consume.");
        }

        if (!WoundCareActionMessages)
            WoundCareActionMessages = new array<string>;

        if (WoundCareActionMessages.Count() == 0)
        {
            WoundCareActionMessages.Insert("Done. Keep moving.");
            WoundCareActionMessages.Insert("That might help for now.");
            WoundCareActionMessages.Insert("Small tasks keep me alive.");
            WoundCareActionMessages.Insert("One more thing handled.");
        }

        if (!InjectionMessages)
            InjectionMessages = new array<string>;

        if (InjectionMessages.Count() == 0)
        {
            InjectionMessages.Insert("This injection is getting to me.");
            InjectionMessages.Insert("I need to pay attention to this injection.");
            InjectionMessages.Insert("Something about this injection feels wrong.");
            InjectionMessages.Insert("I should not ignore this injection.");
        }

        if (!BloodMedicalMessages)
            BloodMedicalMessages = new array<string>;

        if (BloodMedicalMessages.Count() == 0)
        {
            BloodMedicalMessages.Insert("I am losing blood.");
            BloodMedicalMessages.Insert("I need to stop this before it gets worse.");
            BloodMedicalMessages.Insert("Warmth is leaving with every drop.");
            BloodMedicalMessages.Insert("Pressure first. Panic later.");
        }

        if (!DisinfectActionMessages)
            DisinfectActionMessages = new array<string>;

        if (DisinfectActionMessages.Count() == 0)
        {
            DisinfectActionMessages.Insert("Done. Keep moving.");
            DisinfectActionMessages.Insert("That might help for now.");
            DisinfectActionMessages.Insert("Small tasks keep me alive.");
            DisinfectActionMessages.Insert("One more thing handled.");
        }

        if (!RestrainActionMessages)
            RestrainActionMessages = new array<string>;

        if (RestrainActionMessages.Count() == 0)
        {
            RestrainActionMessages.Insert("Done. Keep moving.");
            RestrainActionMessages.Insert("That might help for now.");
            RestrainActionMessages.Insert("Small tasks keep me alive.");
            RestrainActionMessages.Insert("One more thing handled.");
        }

        if (!CraftingActionMessages)
            CraftingActionMessages = new array<string>;

        if (CraftingActionMessages.Count() == 0)
        {
            CraftingActionMessages.Insert("Done. Keep moving.");
            CraftingActionMessages.Insert("That might help for now.");
            CraftingActionMessages.Insert("Small tasks keep me alive.");
            CraftingActionMessages.Insert("One more thing handled.");
        }

        if (!DeployActionMessages)
            DeployActionMessages = new array<string>;

        if (DeployActionMessages.Count() == 0)
        {
            DeployActionMessages.Insert("Done. Keep moving.");
            DeployActionMessages.Insert("That might help for now.");
            DeployActionMessages.Insert("Small tasks keep me alive.");
            DeployActionMessages.Insert("One more thing handled.");
        }

        if (!GardeningActionMessages)
            GardeningActionMessages = new array<string>;

        if (GardeningActionMessages.Count() == 0)
        {
            GardeningActionMessages.Insert("Done. Keep moving.");
            GardeningActionMessages.Insert("That might help for now.");
            GardeningActionMessages.Insert("Small tasks keep me alive.");
            GardeningActionMessages.Insert("One more thing handled.");
        }

        if (!ResourceGatheringMessages)
            ResourceGatheringMessages = new array<string>;

        if (ResourceGatheringMessages.Count() == 0)
        {
            ResourceGatheringMessages.Insert("This resource gathering is getting to me.");
            ResourceGatheringMessages.Insert("I need to pay attention to this resource gathering.");
            ResourceGatheringMessages.Insert("Something about this resource gathering feels wrong.");
            ResourceGatheringMessages.Insert("I should not ignore this resource gathering.");
        }

        if (!LiquidTransferMessages)
            LiquidTransferMessages = new array<string>;

        if (LiquidTransferMessages.Count() == 0)
        {
            LiquidTransferMessages.Insert("This liquid transfer is getting to me.");
            LiquidTransferMessages.Insert("I need to pay attention to this liquid transfer.");
            LiquidTransferMessages.Insert("Something about this liquid transfer feels wrong.");
            LiquidTransferMessages.Insert("I should not ignore this liquid transfer.");
        }

        if (!FireplaceActionMessages)
            FireplaceActionMessages = new array<string>;

        if (FireplaceActionMessages.Count() == 0)
        {
            FireplaceActionMessages.Insert("Done. Keep moving.");
            FireplaceActionMessages.Insert("That might help for now.");
            FireplaceActionMessages.Insert("Small tasks keep me alive.");
            FireplaceActionMessages.Insert("One more thing handled.");
        }

        if (!ElectronicsActionMessages)
            ElectronicsActionMessages = new array<string>;

        if (ElectronicsActionMessages.Count() == 0)
        {
            ElectronicsActionMessages.Insert("Done. Keep moving.");
            ElectronicsActionMessages.Insert("That might help for now.");
            ElectronicsActionMessages.Insert("Small tasks keep me alive.");
            ElectronicsActionMessages.Insert("One more thing handled.");
        }

        if (!NavigationActionMessages)
            NavigationActionMessages = new array<string>;

        if (NavigationActionMessages.Count() == 0)
        {
            NavigationActionMessages.Insert("Done. Keep moving.");
            NavigationActionMessages.Insert("That might help for now.");
            NavigationActionMessages.Insert("Small tasks keep me alive.");
            NavigationActionMessages.Insert("One more thing handled.");
        }

        if (!LockActionMessages)
            LockActionMessages = new array<string>;

        if (LockActionMessages.Count() == 0)
        {
            LockActionMessages.Insert("Done. Keep moving.");
            LockActionMessages.Insert("That might help for now.");
            LockActionMessages.Insert("Small tasks keep me alive.");
            LockActionMessages.Insert("One more thing handled.");
        }

        if (!TrapExplosiveMessages)
            TrapExplosiveMessages = new array<string>;

        if (TrapExplosiveMessages.Count() == 0)
        {
            TrapExplosiveMessages.Insert("This trap explosive is getting to me.");
            TrapExplosiveMessages.Insert("I need to pay attention to this trap explosive.");
            TrapExplosiveMessages.Insert("Something about this trap explosive feels wrong.");
            TrapExplosiveMessages.Insert("I should not ignore this trap explosive.");
        }

    }

    void ST_EnsureStarterMessageDefaults_8()
    {
        if (!BaseBuildingActionMessages)
            BaseBuildingActionMessages = new array<string>;

        if (BaseBuildingActionMessages.Count() == 0)
        {
            BaseBuildingActionMessages.Insert("Done. Keep moving.");
            BaseBuildingActionMessages.Insert("That might help for now.");
            BaseBuildingActionMessages.Insert("Small tasks keep me alive.");
            BaseBuildingActionMessages.Insert("One more thing handled.");
        }

        if (!VehicleActionMessages)
            VehicleActionMessages = new array<string>;

        if (VehicleActionMessages.Count() == 0)
        {
            VehicleActionMessages.Insert("Done. Keep moving.");
            VehicleActionMessages.Insert("That might help for now.");
            VehicleActionMessages.Insert("Small tasks keep me alive.");
            VehicleActionMessages.Insert("One more thing handled.");
        }

        if (!InventoryActionMessages)
            InventoryActionMessages = new array<string>;

        if (InventoryActionMessages.Count() == 0)
        {
            InventoryActionMessages.Insert("Done. Keep moving.");
            InventoryActionMessages.Insert("That might help for now.");
            InventoryActionMessages.Insert("Small tasks keep me alive.");
            InventoryActionMessages.Insert("One more thing handled.");
        }

        if (!BuryStashMessages)
            BuryStashMessages = new array<string>;

        if (BuryStashMessages.Count() == 0)
        {
            BuryStashMessages.Insert("This bury stash is getting to me.");
            BuryStashMessages.Insert("I need to pay attention to this bury stash.");
            BuryStashMessages.Insert("Something about this bury stash feels wrong.");
            BuryStashMessages.Insert("I should not ignore this bury stash.");
        }

        if (!PersonalCareMessages)
            PersonalCareMessages = new array<string>;

        if (PersonalCareMessages.Count() == 0)
        {
            PersonalCareMessages.Insert("This personal care is getting to me.");
            PersonalCareMessages.Insert("I need to pay attention to this personal care.");
            PersonalCareMessages.Insert("Something about this personal care feels wrong.");
            PersonalCareMessages.Insert("I should not ignore this personal care.");
        }

        if (!AmmoManagementMessages)
            AmmoManagementMessages = new array<string>;

        if (AmmoManagementMessages.Count() == 0)
        {
            AmmoManagementMessages.Insert("This ammo management is getting to me.");
            AmmoManagementMessages.Insert("I need to pay attention to this ammo management.");
            AmmoManagementMessages.Insert("Something about this ammo management feels wrong.");
            AmmoManagementMessages.Insert("I should not ignore this ammo management.");
        }

        if (!MovementActionMessages)
            MovementActionMessages = new array<string>;

        if (MovementActionMessages.Count() == 0)
        {
            MovementActionMessages.Insert("Done. Keep moving.");
            MovementActionMessages.Insert("That might help for now.");
            MovementActionMessages.Insert("Small tasks keep me alive.");
            MovementActionMessages.Insert("One more thing handled.");
        }

        if (!WorldInteractionMessages)
            WorldInteractionMessages = new array<string>;

        if (WorldInteractionMessages.Count() == 0)
        {
            WorldInteractionMessages.Insert("This world interaction is getting to me.");
            WorldInteractionMessages.Insert("I need to pay attention to this world interaction.");
            WorldInteractionMessages.Insert("Something about this world interaction feels wrong.");
            WorldInteractionMessages.Insert("I should not ignore this world interaction.");
        }

    }

    void ST_EnsureAllStarterMessageDefaults()
    {
        ST_EnsureStarterMessageDefaults_1();
        ST_EnsureStarterMessageDefaults_2();
        ST_EnsureStarterMessageDefaults_3();
        ST_EnsureStarterMessageDefaults_4();
        ST_EnsureStarterMessageDefaults_5();
        ST_EnsureStarterMessageDefaults_6();
        ST_EnsureStarterMessageDefaults_7();
        ST_EnsureStarterMessageDefaults_8();
    }

    void EnsureDefaults()
    {
        int previousConfigVersion = ConfigVersion;
        if (previousConfigVersion < 38)
        {
            ConfigVersion = 38;
            EnableJournalSystemIntegration = 1;
            JournalRecordAllThoughtSystems = 1;
            JournalRecordAmbientSystems = 0;
            JournalRecordBlockedDecisionEvents = 0;
            JournalMajorEventMinPriority = 55;
            JournalMajorEventPrefixWithSystem = 1;
            JournalMajorEventIncludeStats = 0;
            JournalRecordDeathEntries = 1;
            JournalRecordSetupChoices = 1;
            JournalRecordSystemLinkDebug = 0;
        }

        if (previousConfigVersion < 37)
        {
            ConfigVersion = 37;
            EnableSurvivorJournalItem = 1;
            GiveJournalOnFreshSpawn = 1;
            DropJournalOnDeath = 1;
            AllowReadingOtherPlayersJournals = 1;
            RequireJournalSetupMenu = 0;
            ShowJournalSetupMenuOnlyOnFreshCharacter = 0;
            AllowJournalSetupSkip = 0;
            AllowJournalSetupRandomize = 0;
            PlayerBackstoryDataFile = "$mission:storage_1/ZombiCideMods/SurvivorThoughts/Data/PlayerBackstories.json";
            MaxMajorJournalEventsStored = 25;
            JournalBackstoryMinMajorEvents = 0;
            ShowRealPlayerNameInJournal = 0;
            JournalSetupDefaultPage = 0;
            EnableJournalSetupSpawnProtection = 0;
            JournalSetupBlockDamageUntilComplete = 0;
            JournalSetupSuppressThoughtsUntilComplete = 0;
            JournalSetupProtectionDebug = 0;
            JournalSetupRestoreStatsWhileActive = 0;
            JournalSetupProtectedHealthValue = 100.0;
            JournalSetupProtectedBloodValue = 5000.0;
            JournalSetupProtectedShockValue = 100.0;
            JournalSetupProtectedEnergyValue = 5000.0;
            JournalSetupProtectedWaterValue = 5000.0;
            JournalSetupProtectedHeatComfortValue = 0.0;
            PriorityJournalSystem = 62;
        }

        if (previousConfigVersion < 57)
        {
            ConfigVersion = 64;
            AutoEquipJournalOnFreshSpawn = 1;
            AutoEquipJournalOnLoginIfMissing = 1;
            LockJournalToPlayerWhileAlive = 1;
            AllowJournalLootingAfterDeath = 1;
            DeleteJournalIfRemovedWhileAlive = 1;
            WriteJournalDeathEntryOnKilled = 1;
            JournalRequiredBeforeNormalPlay = 0;
        }

        if (previousConfigVersion < 63)
        {
            ConfigVersion = 64;
            EnablePersistentSaveThrottle = 1;
            PersistentForcedSaveCooldownSeconds = 20.0;
        }



        if (previousConfigVersion < 64)
        {
            ConfigVersion = 64;
        }

        if (AutoEquipJournalOnFreshSpawn != 0 && AutoEquipJournalOnFreshSpawn != 1)
            AutoEquipJournalOnFreshSpawn = 1;

        if (AutoEquipJournalOnLoginIfMissing != 0 && AutoEquipJournalOnLoginIfMissing != 1)
            AutoEquipJournalOnLoginIfMissing = 1;

        if (LockJournalToPlayerWhileAlive != 0 && LockJournalToPlayerWhileAlive != 1)
            LockJournalToPlayerWhileAlive = 1;

        if (AllowJournalLootingAfterDeath != 0 && AllowJournalLootingAfterDeath != 1)
            AllowJournalLootingAfterDeath = 1;

        if (DeleteJournalIfRemovedWhileAlive != 0 && DeleteJournalIfRemovedWhileAlive != 1)
            DeleteJournalIfRemovedWhileAlive = 1;

        if (WriteJournalDeathEntryOnKilled != 0 && WriteJournalDeathEntryOnKilled != 1)
            WriteJournalDeathEntryOnKilled = 1;

        if (JournalRequiredBeforeNormalPlay != 0 && JournalRequiredBeforeNormalPlay != 1)
            JournalRequiredBeforeNormalPlay = 0;

        if (EnablePersistentSaveThrottle != 0 && EnablePersistentSaveThrottle != 1)
            EnablePersistentSaveThrottle = 1;

        if (PersistentForcedSaveCooldownSeconds <= 0.0)
            PersistentForcedSaveCooldownSeconds = 20.0;

        if (!JournalCharacterTypeOptions)
        {
            JournalCharacterTypeOptions = new array<string>;
            JournalCharacterTypeOptions.Insert("Male");
            JournalCharacterTypeOptions.Insert("Female");
            JournalCharacterTypeOptions.Insert("Non-specific survivor");
            JournalCharacterTypeOptions.Insert("Unknown survivor");
        }

        if (JournalCharacterTypeOptions.Count() == 0)
        {
            JournalCharacterTypeOptions.Insert("Male");
            JournalCharacterTypeOptions.Insert("Female");
            JournalCharacterTypeOptions.Insert("Non-specific survivor");
            JournalCharacterTypeOptions.Insert("Unknown survivor");
        }

        if (!JournalHeadTypeOptions)
        {
            JournalHeadTypeOptions = new array<string>;
            JournalHeadTypeOptions.Insert("Default head");
            JournalHeadTypeOptions.Insert("Head 1");
            JournalHeadTypeOptions.Insert("Head 2");
            JournalHeadTypeOptions.Insert("Head 3");
            JournalHeadTypeOptions.Insert("Head 4");
            JournalHeadTypeOptions.Insert("Head 5");
            JournalHeadTypeOptions.Insert("Head 6");
            JournalHeadTypeOptions.Insert("Head 7");
            JournalHeadTypeOptions.Insert("Head 8");
            JournalHeadTypeOptions.Insert("Head 9");
            JournalHeadTypeOptions.Insert("Head 10");
            JournalHeadTypeOptions.Insert("Head 11");
            JournalHeadTypeOptions.Insert("Head 12");
        }

        if (JournalHeadTypeOptions.Count() == 0)
        {
            JournalHeadTypeOptions.Insert("Default head");
            JournalHeadTypeOptions.Insert("Head 1");
            JournalHeadTypeOptions.Insert("Head 2");
            JournalHeadTypeOptions.Insert("Head 3");
            JournalHeadTypeOptions.Insert("Head 4");
            JournalHeadTypeOptions.Insert("Head 5");
            JournalHeadTypeOptions.Insert("Head 6");
            JournalHeadTypeOptions.Insert("Head 7");
            JournalHeadTypeOptions.Insert("Head 8");
            JournalHeadTypeOptions.Insert("Head 9");
            JournalHeadTypeOptions.Insert("Head 10");
            JournalHeadTypeOptions.Insert("Head 11");
            JournalHeadTypeOptions.Insert("Head 12");
        }

        if (!JournalSurvivalInstinctOptions)
        {
            JournalSurvivalInstinctOptions = new array<string>;
            JournalSurvivalInstinctOptions.Insert("avoids unnecessary fights");
            JournalSurvivalInstinctOptions.Insert("runs toward people in trouble");
            JournalSurvivalInstinctOptions.Insert("checks every exit first");
            JournalSurvivalInstinctOptions.Insert("trusts silence more than voices");
            JournalSurvivalInstinctOptions.Insert("keeps moving before fear catches up");
            JournalSurvivalInstinctOptions.Insert("waits, watches, then acts");
            JournalSurvivalInstinctOptions.Insert("checks the treeline before the road");
            JournalSurvivalInstinctOptions.Insert("counts exits before entering");
            JournalSurvivalInstinctOptions.Insert("keeps one hand free");
            JournalSurvivalInstinctOptions.Insert("listens before speaking");
            JournalSurvivalInstinctOptions.Insert("saves the last round");
        }

        if (JournalSurvivalInstinctOptions.Count() == 0)
        {
            JournalSurvivalInstinctOptions.Insert("avoids unnecessary fights");
            JournalSurvivalInstinctOptions.Insert("runs toward people in trouble");
            JournalSurvivalInstinctOptions.Insert("checks every exit first");
            JournalSurvivalInstinctOptions.Insert("trusts silence more than voices");
            JournalSurvivalInstinctOptions.Insert("keeps moving before fear catches up");
            JournalSurvivalInstinctOptions.Insert("waits, watches, then acts");
            JournalSurvivalInstinctOptions.Insert("checks the treeline before the road");
            JournalSurvivalInstinctOptions.Insert("counts exits before entering");
            JournalSurvivalInstinctOptions.Insert("keeps one hand free");
            JournalSurvivalInstinctOptions.Insert("listens before speaking");
            JournalSurvivalInstinctOptions.Insert("saves the last round");
        }

        if (!JournalKeepsakeOptions)
        {
            JournalKeepsakeOptions = new array<string>;
            JournalKeepsakeOptions.Insert("a torn photograph");
            JournalKeepsakeOptions.Insert("an old house key");
            JournalKeepsakeOptions.Insert("a folded note");
            JournalKeepsakeOptions.Insert("a wedding ring");
            JournalKeepsakeOptions.Insert("a cracked watch");
            JournalKeepsakeOptions.Insert("a child's drawing");
            JournalKeepsakeOptions.Insert("nothing but the clothes they woke up in");
            JournalKeepsakeOptions.Insert("a rusted lighter");
            JournalKeepsakeOptions.Insert("a strip of red cloth");
            JournalKeepsakeOptions.Insert("a pressed flower");
            JournalKeepsakeOptions.Insert("a brass button");
            JournalKeepsakeOptions.Insert("a railway ticket");
            JournalKeepsakeOptions.Insert("a photograph too damaged to recognize");
        }

        if (JournalKeepsakeOptions.Count() == 0)
        {
            JournalKeepsakeOptions.Insert("a torn photograph");
            JournalKeepsakeOptions.Insert("an old house key");
            JournalKeepsakeOptions.Insert("a folded note");
            JournalKeepsakeOptions.Insert("a wedding ring");
            JournalKeepsakeOptions.Insert("a cracked watch");
            JournalKeepsakeOptions.Insert("a child's drawing");
            JournalKeepsakeOptions.Insert("nothing but the clothes they woke up in");
            JournalKeepsakeOptions.Insert("a rusted lighter");
            JournalKeepsakeOptions.Insert("a strip of red cloth");
            JournalKeepsakeOptions.Insert("a pressed flower");
            JournalKeepsakeOptions.Insert("a brass button");
            JournalKeepsakeOptions.Insert("a railway ticket");
            JournalKeepsakeOptions.Insert("a photograph too damaged to recognize");
        }

        if (JournalSetupRestoreStatsWhileActive != 0 && JournalSetupRestoreStatsWhileActive != 1)
            JournalSetupRestoreStatsWhileActive = 0;

        if (JournalSetupProtectedHealthValue <= 0.0)
            JournalSetupProtectedHealthValue = 100.0;

        if (JournalSetupProtectedBloodValue <= 0.0)
            JournalSetupProtectedBloodValue = 5000.0;

        if (JournalSetupProtectedShockValue <= 0.0)
            JournalSetupProtectedShockValue = 100.0;

        if (JournalSetupProtectedEnergyValue <= 0.0)
            JournalSetupProtectedEnergyValue = 5000.0;

        if (JournalSetupProtectedWaterValue <= 0.0)
            JournalSetupProtectedWaterValue = 5000.0;

        if (!JournalOriginOptions)
        {
            JournalOriginOptions = new array<string>;
            JournalOriginOptions.Insert("Chernarus");
            JournalOriginOptions.Insert("Livonia");
            JournalOriginOptions.Insert("Sakhal");
            JournalOriginOptions.Insert("Namalsk");
            JournalOriginOptions.Insert("Deer Isle");
            JournalOriginOptions.Insert("Unknown coast");
            JournalOriginOptions.Insert("inland settlement");
            JournalOriginOptions.Insert("fishing village");
            JournalOriginOptions.Insert("border town");
            JournalOriginOptions.Insert("evacuation camp");
            JournalOriginOptions.Insert("rail yard");
            JournalOriginOptions.Insert("nowhere they talk about");
        }

        if (!JournalOccupationOptions)
        {
            JournalOccupationOptions = new array<string>;
            JournalOccupationOptions.Insert("rail worker");
            JournalOccupationOptions.Insert("paramedic");
            JournalOccupationOptions.Insert("hunter");
            JournalOccupationOptions.Insert("teacher");
            JournalOccupationOptions.Insert("dock worker");
            JournalOccupationOptions.Insert("soldier");
            JournalOccupationOptions.Insert("mechanic");
            JournalOccupationOptions.Insert("farmer");
            JournalOccupationOptions.Insert("student");
            JournalOccupationOptions.Insert("fisherman");
            JournalOccupationOptions.Insert("nurse");
            JournalOccupationOptions.Insert("police officer");
            JournalOccupationOptions.Insert("warehouse worker");
            JournalOccupationOptions.Insert("truck driver");
            JournalOccupationOptions.Insert("forest ranger");
            JournalOccupationOptions.Insert("factory hand");
            JournalOccupationOptions.Insert("smuggler");
        }

        if (!JournalTraitOptions)
        {
            JournalTraitOptions = new array<string>;
            JournalTraitOptions.Insert("practical");
            JournalTraitOptions.Insert("fearful");
            JournalTraitOptions.Insert("stubborn");
            JournalTraitOptions.Insert("quiet");
            JournalTraitOptions.Insert("aggressive");
            JournalTraitOptions.Insert("calm under pressure");
            JournalTraitOptions.Insert("watchful");
            JournalTraitOptions.Insert("coldly practical");
            JournalTraitOptions.Insert("reckless when cornered");
            JournalTraitOptions.Insert("slow to trust");
            JournalTraitOptions.Insert("quietly stubborn");
        }

        if (!JournalFearOptions)
        {
            JournalFearOptions = new array<string>;
            JournalFearOptions.Insert("being left behind");
            JournalFearOptions.Insert("the dark");
            JournalFearOptions.Insert("dying alone");
            JournalFearOptions.Insert("infected crowds");
            JournalFearOptions.Insert("starvation");
            JournalFearOptions.Insert("silence");
            JournalFearOptions.Insert("being trapped indoors");
            JournalFearOptions.Insert("running out of light");
            JournalFearOptions.Insert("hearing laughter in the dark");
            JournalFearOptions.Insert("watching someone turn");
            JournalFearOptions.Insert("becoming the thing they hate");
        }

        if (!JournalGoalOptions)
        {
            JournalGoalOptions = new array<string>;
            JournalGoalOptions.Insert("survive one more day");
            JournalGoalOptions.Insert("find a safe place");
            JournalGoalOptions.Insert("reach the coast again");
            JournalGoalOptions.Insert("find someone they lost");
            JournalGoalOptions.Insert("keep a promise");
            JournalGoalOptions.Insert("make it through winter");
            JournalGoalOptions.Insert("leave a record behind");
            JournalGoalOptions.Insert("stay human as long as possible");
        }

        if (!JournalSkillOptions)
        {
            JournalSkillOptions = new array<string>;
            JournalSkillOptions.Insert("first aid");
            JournalSkillOptions.Insert("repairing engines");
            JournalSkillOptions.Insert("hunting");
            JournalSkillOptions.Insert("navigation");
            JournalSkillOptions.Insert("farming");
            JournalSkillOptions.Insert("keeping quiet");
            JournalSkillOptions.Insert("handling weapons");
            JournalSkillOptions.Insert("scavenging");
            JournalSkillOptions.Insert("reading weather");
            JournalSkillOptions.Insert("finding clean water");
            JournalSkillOptions.Insert("patching wounds");
            JournalSkillOptions.Insert("moving unseen");
            JournalSkillOptions.Insert("making fires");
            JournalSkillOptions.Insert("bartering");
        }

        if (!JournalWeaknessOptions)
        {
            JournalWeaknessOptions = new array<string>;
            JournalWeaknessOptions.Insert("trusts too easily");
            JournalWeaknessOptions.Insert("panics in the dark");
            JournalWeaknessOptions.Insert("hates being alone");
            JournalWeaknessOptions.Insert("takes unnecessary risks");
            JournalWeaknessOptions.Insert("cannot ignore people in trouble");
            JournalWeaknessOptions.Insert("holds grudges");
            JournalWeaknessOptions.Insert("struggles with hunger");
            JournalWeaknessOptions.Insert("freezes under pressure");
            JournalWeaknessOptions.Insert("keeps old promises too long");
            JournalWeaknessOptions.Insert("cannot sleep after violence");
            JournalWeaknessOptions.Insert("hoards things they do not need");
            JournalWeaknessOptions.Insert("goes quiet when afraid");
            JournalWeaknessOptions.Insert("pushes on when they should rest");
        }

        if (!JournalMoralCodeOptions)
        {
            JournalMoralCodeOptions = new array<string>;
            JournalMoralCodeOptions.Insert("will not abandon a friend");
            JournalMoralCodeOptions.Insert("will not eat human meat");
            JournalMoralCodeOptions.Insert("avoids killing unless forced");
            JournalMoralCodeOptions.Insert("protects the weak when possible");
            JournalMoralCodeOptions.Insert("survival comes before mercy");
            JournalMoralCodeOptions.Insert("trust must be earned");
            JournalMoralCodeOptions.Insert("never wastes supplies");
            JournalMoralCodeOptions.Insert("keeps moving, no matter what");
            JournalMoralCodeOptions.Insert("never takes from the helpless");
            JournalMoralCodeOptions.Insert("will not leave a body unsearched");
            JournalMoralCodeOptions.Insert("mercy ends when trust breaks");
            JournalMoralCodeOptions.Insert("food is shared until it cannot be");
            JournalMoralCodeOptions.Insert("every debt is remembered");
        }

        if (!JournalBackstoryTemplates)
        {
            JournalBackstoryTemplates = new array<string>;
            JournalBackstoryTemplates.Insert("{name} came from {origin}, once working as a {occupation}. They were {trait}, but the outbreak left them afraid of {fear}. Now they are trying to {goal}.");
            JournalBackstoryTemplates.Insert("Before everything collapsed, {name} was a {occupation}. People called them {trait}. They left {origin} after the first panic and now only writes about one thing: {goal}.");
            JournalBackstoryTemplates.Insert("{name} does not write much about life before. The few clear notes mention {origin}, {occupation}, and a fear of {fear}. The rest is survival.");
        }

        if (previousConfigVersion < 35)
        {
            ConfigVersion = 36;
            EnableProlongedStateMessages = 1;
            ProlongedStateThresholdSeconds = 600.0;
            EnableExpandedAdvancedCombos = 1;
            EnableAnalyticsJsonLines = 1;
            AnalyticsJsonLineFile = "$mission:storage_1/ZombiCideMods/SurvivorThoughts/Analytics/SurvivorThoughts_Analytics.jsonl";
            JournalIncludePlayerStats = 1;
            JournalWriteAllRecoveryEvents = 1;
        }

        if (previousConfigVersion < 34)
        {
            ConfigVersion = 34;
            PriorityStateHistory = 50;
            PriorityRecovery = 55;
            PriorityAdvancedCombined = 85;
            PriorityNearMissCombat = 80;
            PriorityDiseaseSpecific = 70;
            PriorityMapEnvironment = 18;
            EnablePlayerStateHistory = 1;
            StateHistorySampleIntervalSeconds = 30.0;
            StateHistoryWindowSeconds = 900.0;
            TrendChangeThreshold = 0.10;
            EnableTrendMessages = 1;
            EnableStateSnapshots = 0;
            StateSnapshotIntervalSeconds = 300.0;
            EnablePersistentStateSnapshots = 0;
            StateSnapshotFolder = "$mission:storage_1/ZombiCideMods/SurvivorThoughts/Debug/PlayerStateSnapshots";
            EnableThoughtDecisionTrace = 0;
            TraceOnlyBlockedThoughts = 1;
            TraceToDebugLog = 1;
            TraceToMissionStorage = 0;
            DecisionTraceFolder = "$mission:storage_1/ZombiCideMods/SurvivorThoughts/Debug/DecisionTrace";
            EnableAdvancedCombinedMessages = 1;
            AdvancedCombinedChance = 0.65;
            EnableRecoveryMessages = 1;
            RecoveryThoughtCooldownSeconds = 180.0;
            RecoveryThoughtChance = 0.40;
            EnableNearMissCombatMessages = 1;
            NearMissCombatCooldownSeconds = 45.0;
            NearMissCombatChance = 0.35;
            EnableDiseaseSpecificMessages = 1;
            EnableAdminAnalytics = 1;
            AnalyticsSaveIntervalSeconds = 300.0;
            AnalyticsFolder = "$mission:storage_1/ZombiCideMods/SurvivorThoughts/Analytics";
            EnablePlayerJournals = 1;
            PlayerJournalFolder = "$mission:storage_1/ZombiCideMods/SurvivorThoughts/Journals";
            JournalOnlyMajorEvents = 1;
    
        EnableSurvivorJournalItem = 1;
        GiveJournalOnFreshSpawn = 1;
        DropJournalOnDeath = 1;
        AllowReadingOtherPlayersJournals = 1;
        RequireJournalSetupMenu = 0;
        ShowJournalSetupMenuOnlyOnFreshCharacter = 0;
        AllowJournalSetupSkip = 0;
        AllowJournalSetupRandomize = 0;
        PlayerBackstoryDataFile = "$mission:storage_1/ZombiCideMods/SurvivorThoughts/Data/PlayerBackstories.json";
        MaxMajorJournalEventsStored = 25;
        JournalBackstoryMinMajorEvents = 0;
        ShowRealPlayerNameInJournal = 0;
        JournalSetupDefaultPage = 0;
        PriorityJournalSystem = 62;

        JournalOriginOptions = new array<string>;
        JournalOriginOptions.Insert("Chernarus");
        JournalOriginOptions.Insert("Livonia");
        JournalOriginOptions.Insert("Sakhal");
        JournalOriginOptions.Insert("Namalsk");
        JournalOriginOptions.Insert("Unknown coast");
        JournalOriginOptions.Insert("Inland settlement");

        JournalOccupationOptions = new array<string>;
        JournalOccupationOptions.Insert("rail worker");
        JournalOccupationOptions.Insert("paramedic");
        JournalOccupationOptions.Insert("hunter");
        JournalOccupationOptions.Insert("mechanic");
        JournalOccupationOptions.Insert("teacher");
        JournalOccupationOptions.Insert("dock worker");
        JournalOccupationOptions.Insert("soldier");
        JournalOccupationOptions.Insert("farmer");

        JournalTraitOptions = new array<string>;
        JournalTraitOptions.Insert("practical");
        JournalTraitOptions.Insert("quiet");
        JournalTraitOptions.Insert("stubborn");
        JournalTraitOptions.Insert("cautious");
        JournalTraitOptions.Insert("angry");
        JournalTraitOptions.Insert("calm under pressure");
        JournalTraitOptions.Insert("resourceful");
        JournalTraitOptions.Insert("distrustful");

        JournalFearOptions = new array<string>;
        JournalFearOptions.Insert("dying alone");
        JournalFearOptions.Insert("being left behind");
        JournalFearOptions.Insert("the dark");
        JournalFearOptions.Insert("infected crowds");
        JournalFearOptions.Insert("starvation");
        JournalFearOptions.Insert("silence");

        JournalGoalOptions = new array<string>;
        JournalGoalOptions.Insert("find a safe place");
        JournalGoalOptions.Insert("reach the next town");
        JournalGoalOptions.Insert("keep moving north");
        JournalGoalOptions.Insert("find someone worth trusting");
        JournalGoalOptions.Insert("survive one more day");
        JournalGoalOptions.Insert("learn what happened");

        JournalBackstoryTemplates = new array<string>;
        JournalBackstoryTemplates.Insert("{name} came from {origin}, once working as a {occupation}. They were {trait}, but the outbreak left them afraid of {fear}. Now they are trying to {goal}.");
        JournalBackstoryTemplates.Insert("Before everything collapsed, {name} was a {occupation}. People called them {trait}. They left {origin} after the first panic and now only writes about one thing: {goal}.");
        JournalBackstoryTemplates.Insert("{name} does not write much about life before. The few clear notes mention {origin}, {occupation}, and a fear of {fear}. The rest is survival.");

        EnableMapEnvironmentPacks = 1;
            ActiveMapEnvironmentPack = "Generic";
            MapEnvironmentThoughtChance = 0.20;
            MapEnvironmentThoughtCooldownSeconds = 600.0;
        }


        if (previousConfigVersion < 33)
        {
            EnableMissionStoragePersistentData = 1;
            PersistentStorageRoot = "$mission:storage_1/ZombiCideMods/SurvivorThoughts";
            PersistentDataFolderName = "Data";
            PersistentStateDataFile = "$mission:storage_1/ZombiCideMods/SurvivorThoughts/Data/PlayerPersistentStates.json";
            PersonalityDataFile = "$mission:storage_1/ZombiCideMods/SurvivorThoughts/Data/PlayerPersonalities.json";
            PersistentAutosaveSeconds = 60.0;
        }

        if (previousConfigVersion < 32)
        {
            PrioritySocialGroup = 65;
            PrioritySanityCreep = 70;

            EnableSocialGroupThoughts = 1;
            SocialGroupThoughtCooldownSeconds = 240.0;
            SocialGroupThoughtChance = 0.35;
            SocialNearbyPlayerRadius = 45.0;
            SocialFriendlyTimeRequiredSeconds = 300.0;
            SocialMemoryDurationSeconds = 900.0;
            LoneWolfNoPlayerSeenSeconds = 10800.0;
            EnableTeammateShotMessages = 1;
            EnableTeammateDownMessages = 1;
            EnableLoneWolfMessages = 1;
            EnableFriendlyNearbyMessages = 1;

            EnableSanityCreep = 1;
            SanityThoughtCooldownSeconds = 300.0;
            SanityThoughtChance = 0.30;
            StartingSanity = 100.0;
            MinimumSanity = 0.0;
            SanityLossSkinHuman = 18.0;
            SanityLossEatHumanMeat = 25.0;
            SanityLossKillRestrainedPlayer = 35.0;
            SanityRegenPerMinute = 0.0;
            SanityUneasyThreshold = 70.0;
            SanityUnhingedThreshold = 35.0;
            SanityPsychoticThreshold = 15.0;
            EnableSanityUneasyMessages = 1;
            EnableSanityUnhingedMessages = 1;
            EnableSanityPsychoticMessages = 1;
            EnableCannibalismCreepMessages = 1;
        }

        if (previousConfigVersion < 30)
        {
            EnableThoughtPrioritySystem = 1;
            PriorityInterruptWindowSeconds = 8.0;
            PriorityImmediateDamage = 100;
            PriorityBleeding = 100;
            PriorityDeathSpiral = 95;
            PriorityCriticalSurvival = 90;
            PriorityHighSurvival = 70;
            PriorityMediumSurvival = 50;
            PriorityLowSurvival = 25;
            PriorityAction = 35;
            PriorityOpenCloseAction = 20;
            PriorityCombatStress = 75;
            PriorityWeather = 15;
            PriorityTimeOfDay = 15;
            PriorityLocation = 20;
            PriorityItemCondition = 55;
            PriorityCorpse = 45;
            PriorityContaminatedZone = 80;
            PriorityPersonality = 10;
            PriorityAdminSystem = 100;
        PriorityPlayerMemory = 40;
        PriorityStealthNoise = 45;
        PriorityShelter = 25;
        PriorityMentalState = 60;
        PriorityCustomThoughtZone = 30;
        PrioritySocialGroup = 65;
        PrioritySanityCreep = 70;
        }

        if (previousConfigVersion < 28)
        {
            LightRainThought_Min = 0.15;
            HeavyRainThought_Min = 0.65;
            OvercastThought_Min = 0.65;

            EnableClearWeatherMessages = 1;
            EnableOvercastWeatherMessages = 1;
            EnableLightRainMessages = 1;
            EnableHeavyRainMessages = 1;
            EnableFogWeatherMessages = 1;
            EnableWindWeatherMessages = 1;
            EnableStormWeatherMessages = 1;
            WeatherThoughtCooldownSeconds = 240.0;
            WeatherThoughtChance = 0.35;

            EnableTimeOfDayThoughts = 1;
            TimeOfDayThoughtCooldownSeconds = 300.0;
            TimeOfDayThoughtChance = 0.35;
            EnableDawnMessages = 1;
            EnableMorningMessages = 1;
            EnableNoonMessages = 1;
            EnableAfternoonMessages = 1;
            EnableDuskMessages = 1;
            EnableNightMessages = 1;
            EnableMidnightMessages = 1;
            EnableEarlyMorningMessages = 1;
            DawnStartHour = 5.0;
            MorningStartHour = 7.0;
            NoonStartHour = 11.0;
            AfternoonStartHour = 13.0;
            DuskStartHour = 18.0;
            NightStartHour = 20.0;
            MidnightStartHour = 0.0;
            EarlyMorningStartHour = 3.0;
        }

        if (previousConfigVersion < 27)
        {
            DuplicateImmediateActionCooldownSeconds = 0.75;
        }

        if (previousConfigVersion < 25)
        {
            // v0.2.25: force immediate reaction toggles on for old modular configs
            // that were created before the per-message toggles existed.
            EnableDamageReactionThoughts = 1;
            EnableBleedingReactionThoughts = 1;
            EnableCombatStressDamageEventThoughts = 1;

            EnableZombieHitMessages = 1;
            EnablePlayerMeleeHitMessages = 1;
            EnableGunshotHitMessages = 1;
            EnableExplosionHitMessages = 1;
            EnableHeavyHitMessages = 1;

            EnableBleedingStartedMessages = 1;
            EnableBleedingWorseMessages = 1;
            EnableBleedingStoppedMessages = 1;
        }


        if (previousConfigVersion < 23)
        {
            EnableDebugFileLog = 1;
            DebugLogToRPT = 1;
            if (DebugLogFileName == "")
                DebugLogFileName = "SurvivorThoughts_Debug.log";
            ClearDebugLogOnServerStart = 1;
        }

        if (previousConfigVersion < 22)
        {
            EnableDeathSpiralThoughts = 1;
            EnableStarvingToDeathMessages = 1;
            EnableDehydratingToDeathMessages = 1;
            EnableFreezingToDeathMessages = 1;
            EnableOverheatingToDeathMessages = 1;
        }

        if (CombatStressCooldownSeconds <= 0.0)
            CombatStressCooldownSeconds = 20.0;

        if (OpenCloseActionCooldownSeconds <= 0.0)
            OpenCloseActionCooldownSeconds = 20.0;

        if (DuplicateImmediateActionCooldownSeconds <= 0.0)
            DuplicateImmediateActionCooldownSeconds = 0.75;

        if (previousConfigVersion < 17)
            EnableBleedingReactionThoughts = 1;


        if (HeavyHitHealthDamage_Min <= 0.0)
            HeavyHitHealthDamage_Min = 25.0;

        if (HeavyHitBloodDamage_Min <= 0.0)
            HeavyHitBloodDamage_Min = 300.0;

        if (HeavyHitShockDamage_Min <= 0.0)
            HeavyHitShockDamage_Min = 35.0;

        if (EnableDeathSpiralThoughts != 0 && EnableDeathSpiralThoughts != 1)
            EnableDeathSpiralThoughts = 1;

        if (HealthDropMinAmount <= 0.0)
            HealthDropMinAmount = 0.10;

        if (HealthDropRecentSeconds <= 0.0)
            HealthDropRecentSeconds = 90.0;

        if (DeathSpiralColdComfort_Max >= 0.0)
            DeathSpiralColdComfort_Max = -0.75;

        if (DeathSpiralHotComfort_Min <= 0.0)
            DeathSpiralHotComfort_Min = 0.75;

        EnableStarvingToDeathMessages = 1;
        EnableDehydratingToDeathMessages = 1;
        EnableFreezingToDeathMessages = 1;
        EnableOverheatingToDeathMessages = 1;

        if (EnableDebugFileLog != 0 && EnableDebugFileLog != 1)
            EnableDebugFileLog = 1;

        if (DebugLogToRPT != 0 && DebugLogToRPT != 1)
            DebugLogToRPT = 1;

        if (DebugLogFileName == "")
            DebugLogFileName = "SurvivorThoughts_Debug.log";

        if (ClearDebugLogOnServerStart != 0 && ClearDebugLogOnServerStart != 1)
            ClearDebugLogOnServerStart = 1;


        if (EnableThoughtPrioritySystem != 0 && EnableThoughtPrioritySystem != 1)
            EnableThoughtPrioritySystem = 1;

        if (PriorityInterruptWindowSeconds <= 0.0)
            PriorityInterruptWindowSeconds = 8.0;

        if (PriorityImmediateDamage <= 0)
            PriorityImmediateDamage = 100;

        if (PriorityBleeding <= 0)
            PriorityBleeding = 100;

        if (PriorityDeathSpiral <= 0)
            PriorityDeathSpiral = 95;

        if (PriorityCriticalSurvival <= 0)
            PriorityCriticalSurvival = 90;

        if (PriorityHighSurvival <= 0)
            PriorityHighSurvival = 70;

        if (PriorityMediumSurvival <= 0)
            PriorityMediumSurvival = 50;

        if (PriorityLowSurvival <= 0)
            PriorityLowSurvival = 25;

        if (PriorityAction <= 0)
            PriorityAction = 35;

        if (PriorityOpenCloseAction <= 0)
            PriorityOpenCloseAction = 20;

        if (PriorityCombatStress <= 0)
            PriorityCombatStress = 75;

        if (PriorityWeather <= 0)
            PriorityWeather = 15;

        if (PriorityTimeOfDay <= 0)
            PriorityTimeOfDay = 15;

        if (PriorityLocation <= 0)
            PriorityLocation = 20;

        if (PriorityItemCondition <= 0)
            PriorityItemCondition = 55;

        if (PriorityCorpse <= 0)
            PriorityCorpse = 45;

        if (PriorityContaminatedZone <= 0)
            PriorityContaminatedZone = 80;

        if (PriorityPersonality <= 0)
            PriorityPersonality = 10;

        if (PriorityAdminSystem <= 0)
            PriorityAdminSystem = 100;
        PriorityPlayerMemory = 40;
        PriorityStealthNoise = 45;
        PriorityShelter = 25;
        PriorityMentalState = 60;
        PriorityCustomThoughtZone = 30;
        PrioritySocialGroup = 65;
        PrioritySanityCreep = 70;


        if (PrioritySocialGroup <= 0)
            PrioritySocialGroup = 65;

        if (PrioritySanityCreep <= 0)
            PrioritySanityCreep = 70;

        if (SocialGroupThoughtCooldownSeconds <= 0.0)
            SocialGroupThoughtCooldownSeconds = 240.0;

        if (SocialGroupThoughtChance <= 0.0)
            SocialGroupThoughtChance = 0.35;

        if (SocialNearbyPlayerRadius <= 0.0)
            SocialNearbyPlayerRadius = 45.0;

        if (SocialFriendlyTimeRequiredSeconds <= 0.0)
            SocialFriendlyTimeRequiredSeconds = 300.0;

        if (SocialMemoryDurationSeconds <= 0.0)
            SocialMemoryDurationSeconds = 900.0;

        if (LoneWolfNoPlayerSeenSeconds <= 0.0)
            LoneWolfNoPlayerSeenSeconds = 10800.0;

        if (!TeammateShotMessages || TeammateShotMessages.Count() == 0)
        {
            TeammateShotMessages = new array<string>;
            TeammateShotMessages.Insert("They hit them. Move, now.");
            TeammateShotMessages.Insert("No, no, no. Stay with me.");
            TeammateShotMessages.Insert("Someone just dropped my cover.");
            TeammateShotMessages.Insert("I cannot lose them here.");
            TeammateShotMessages.Insert("That shot was meant to split us apart.");
            TeammateShotMessages.Insert("Keep them alive. Think later.");
        }

        if (!TeammateDownMessages || TeammateDownMessages.Count() == 0)
        {
            TeammateDownMessages = new array<string>;
            TeammateDownMessages.Insert("No, no, no! Hang on, do not die on me.");
            TeammateDownMessages.Insert("I am completely on my own now.");
            TeammateDownMessages.Insert("They were right beside me a second ago.");
            TeammateDownMessages.Insert("Do not leave me out here alone.");
            TeammateDownMessages.Insert("I should have covered them better.");
            TeammateDownMessages.Insert("Their silence is louder than the gunshot.");
        }

        if (!LoneWolfMessages || LoneWolfMessages.Count() == 0)
        {
            LoneWolfMessages = new array<string>;
            LoneWolfMessages.Insert("I have not talked to anyone in days.");
            LoneWolfMessages.Insert("I am starting to forget what my own voice sounds like.");
            LoneWolfMessages.Insert("No footsteps but mine. That should feel safer than it does.");
            LoneWolfMessages.Insert("Being alone keeps me alive, until it does not.");
            LoneWolfMessages.Insert("The silence is beginning to feel like company.");
            LoneWolfMessages.Insert("I wonder if there is anyone left worth trusting.");
        }

        if (!FriendlyNearbyMessages || FriendlyNearbyMessages.Count() == 0)
        {
            FriendlyNearbyMessages = new array<string>;
            FriendlyNearbyMessages.Insert("Another set of eyes makes the road feel shorter.");
            FriendlyNearbyMessages.Insert("Stay close. Wandering off gets people killed.");
            FriendlyNearbyMessages.Insert("I need to keep track of them.");
            FriendlyNearbyMessages.Insert("Two people make more noise, but fewer mistakes.");
            FriendlyNearbyMessages.Insert("Trust is useful. Dangerous, but useful.");
            FriendlyNearbyMessages.Insert("If this goes bad, I am not the only one at risk.");
        }

        if (SanityThoughtCooldownSeconds <= 0.0)
            SanityThoughtCooldownSeconds = 300.0;

        if (SanityThoughtChance <= 0.0)
            SanityThoughtChance = 0.30;

        if (StartingSanity <= 0.0)
            StartingSanity = 100.0;

        if (SanityUneasyThreshold <= 0.0)
            SanityUneasyThreshold = 70.0;

        if (SanityUnhingedThreshold <= 0.0)
            SanityUnhingedThreshold = 35.0;

        if (SanityPsychoticThreshold <= 0.0)
            SanityPsychoticThreshold = 15.0;

        if (SanityLossSkinHuman <= 0.0)
            SanityLossSkinHuman = 18.0;

        if (SanityLossEatHumanMeat <= 0.0)
            SanityLossEatHumanMeat = 25.0;

        if (!SanityUneasyMessages || SanityUneasyMessages.Count() == 0)
        {
            SanityUneasyMessages = new array<string>;
            SanityUneasyMessages.Insert("I need to keep my head clear.");
            SanityUneasyMessages.Insert("Something about this is staying with me.");
            SanityUneasyMessages.Insert("My hands will not stop shaking.");
            SanityUneasyMessages.Insert("I should not think about what I have done.");
            SanityUneasyMessages.Insert("Breathe. Count supplies. Keep moving.");
            SanityUneasyMessages.Insert("There are lines out here. I can still see them.");
        }

        if (!SanityUnhingedMessages || SanityUnhingedMessages.Count() == 0)
        {
            SanityUnhingedMessages = new array<string>;
            SanityUnhingedMessages.Insert("Their faces keep coming back when I close my eyes.");
            SanityUnhingedMessages.Insert("I keep hearing things that are not there.");
            SanityUnhingedMessages.Insert("The silence laughs at me.");
            SanityUnhingedMessages.Insert("I am still in control. I have to be.");
            SanityUnhingedMessages.Insert("I did what I had to do. That is what I keep telling myself.");
            SanityUnhingedMessages.Insert("Every bad choice feels easier than the last.");
        }

        if (!SanityPsychoticMessages || SanityPsychoticMessages.Count() == 0)
        {
            SanityPsychoticMessages = new array<string>;
            SanityPsychoticMessages.Insert("The giggling... I can hear it even when I am not laughing.");
            SanityPsychoticMessages.Insert("Their faces. Why do I keep seeing their faces?");
            SanityPsychoticMessages.Insert("Maybe the dead are the only honest ones now.");
            SanityPsychoticMessages.Insert("I do not remember when this started feeling normal.");
            SanityPsychoticMessages.Insert("Something in me broke quietly.");
            SanityPsychoticMessages.Insert("I should be horrified. I am not.");
        }

        if (!CannibalismCreepMessages || CannibalismCreepMessages.Count() == 0)
        {
            CannibalismCreepMessages = new array<string>;
            CannibalismCreepMessages.Insert("That was a person. I know that.");
            CannibalismCreepMessages.Insert("There are some hungers that should stay empty.");
            CannibalismCreepMessages.Insert("I can still taste what I should not have eaten.");
            CannibalismCreepMessages.Insert("My stomach accepts what my mind refuses.");
            CannibalismCreepMessages.Insert("The worst part is that it helped.");
            CannibalismCreepMessages.Insert("I crossed something I cannot uncross.");
        }

        ConfigVersion = 34;

        if (UseNotificationSystem != 0 && UseNotificationSystem != 1)
            UseNotificationSystem = 0;

        if (UseLocalChatBox != 0 && UseLocalChatBox != 1)
            UseLocalChatBox = 1;

        if (EnableCombinedThoughts != 0 && EnableCombinedThoughts != 1)
            EnableCombinedThoughts = 1;

        if (EnableWeatherThoughts != 0 && EnableWeatherThoughts != 1)
            EnableWeatherThoughts = 1;

        if (EnableItemConditionThoughts != 0 && EnableItemConditionThoughts != 1)
            EnableItemConditionThoughts = 1;

        if (ItemConditionHealthThreshold <= 0.0 || ItemConditionHealthThreshold > 1.0)
            ItemConditionHealthThreshold = 0.50;

        if (EnableCombatStressThoughts != 0 && EnableCombatStressThoughts != 1)
            EnableCombatStressThoughts = 1;

        if (CombatStressShockThreshold <= 0.0)
            CombatStressShockThreshold = 65.0;

        if (EnableContaminatedZoneThoughts != 0 && EnableContaminatedZoneThoughts != 1)
            EnableContaminatedZoneThoughts = 1;

        if (EnableNearbyCorpseThoughts != 0 && EnableNearbyCorpseThoughts != 1)
            EnableNearbyCorpseThoughts = 1;

        if (NearbyCorpseRadius <= 0.0)
            NearbyCorpseRadius = 35.0;

        if (EnablePersonalityProfiles != 0 && EnablePersonalityProfiles != 1)
            EnablePersonalityProfiles = 1;

        if (PersonalityThoughtChance <= 0.0 || PersonalityThoughtChance > 1.0)
            PersonalityThoughtChance = 0.20;

        if (PersonalityPersistBySteamId != 0 && PersonalityPersistBySteamId != 1)
            PersonalityPersistBySteamId = 1;

        if (PersonalityDataFile == "")
            PersonalityDataFile = "$mission:storage_1/ZombiCideMods/SurvivorThoughts/Data/PlayerPersonalities.json";
        EnableMissionStoragePersistentData = 1;
        PersistentStorageRoot = "$mission:storage_1/ZombiCideMods/SurvivorThoughts";
        PersistentDataFolderName = "Data";
        PersistentStateDataFile = "$mission:storage_1/ZombiCideMods/SurvivorThoughts/Data/PlayerPersistentStates.json";
        PersistentAutosaveSeconds = 60.0;
        EnablePersonalityChangeOverTime = 1;
        PersonalityChangeChance = 0.08;
        PersonalityMinimumSecondsBetweenChanges = 7200.0;

        if (EnableCombatStressShockThoughts != 0 && EnableCombatStressShockThoughts != 1)
            EnableCombatStressShockThoughts = 1;

        if (EnableCombatStressDamageEventThoughts != 0 && EnableCombatStressDamageEventThoughts != 1)
            EnableCombatStressDamageEventThoughts = 1;
        EnableDamageReactionThoughts = 1;
        EnableZombieHitMessages = 1;
        EnablePlayerMeleeHitMessages = 1;
        EnableGunshotHitMessages = 1;
        EnableExplosionHitMessages = 1;
        EnableHeavyHitMessages = 1;
        EnableBleedingStartedMessages = 1;
        EnableBleedingWorseMessages = 1;
        EnableBleedingStoppedMessages = 1;

        if (CombatStressCooldownSeconds <= 0.0)
            CombatStressCooldownSeconds = 20.0;
        EnableBleedingReactionThoughts = 1;
        HeavyHitHealthDamage_Min = 25.0;
        HeavyHitBloodDamage_Min = 300.0;
        HeavyHitShockDamage_Min = 35.0;

        if (RainThought_Min <= 0.0)
            RainThought_Min = 0.35;

        if (FogThought_Min <= 0.0)
            FogThought_Min = 0.45;

        if (WindThought_Min <= 0.0)
            WindThought_Min = 8.0;

        if (StormRain_Min <= 0.0)
            StormRain_Min = 0.65;

        if (StormWind_Min <= 0.0)
            StormWind_Min = 10.0;

        if (StormOvercast_Min <= 0.0)
            StormOvercast_Min = 0.90;

        if (ScanEquippedItemsForDamagedThoughts != 0 && ScanEquippedItemsForDamagedThoughts != 1)
            ScanEquippedItemsForDamagedThoughts = 1;


        EnableLocationThoughts = 1;
        LocationThoughtCooldownSeconds = 240.0;
        LocationThoughtChance = 0.35;
        LocationUseCustomZones = 1;
        LocationUseFallbackDetection = 1;
        LocationCoastZMax = 3500.0;
        LocationWildernessScanRadius = 80.0;
        LocationWildernessMaxObjects = 8;

        EnablePlayerMemoryThoughts = 1;
        PlayerMemoryThoughtCooldownSeconds = 240.0;
        PlayerMemoryThoughtChance = 0.30;
        PlayerMemoryDurationSeconds = 600.0;

        EnableStealthNoiseThoughts = 1;
        StealthNoiseThoughtCooldownSeconds = 180.0;
        StealthNoiseThoughtChance = 0.35;
        StealthNoiseInfectedRadius = 35.0;
        StealthNoiseRunSpeedThreshold = 3.2;

        EnableShelterThoughts = 1;
        ShelterThoughtCooldownSeconds = 300.0;
        ShelterThoughtChance = 0.30;
        ShelterScanRadius = 14.0;
        ShelterNearbyBuildingCountRequired = 1;

        EnableRecentMessageBlocker = 1;
        RecentMessageMemoryCount = 12;
        RecentMessageBlockSeconds = 900.0;

        EnableMentalStateThoughts = 1;
        MentalStateThoughtCooldownSeconds = 300.0;
        MentalStateThoughtChance = 0.25;
        MentalStateCriticalHealthMax = 30.0;
        MentalStateLowBloodMax = 3500.0;
        MentalStateLowFoodMax = 500.0;
        MentalStateLowWaterMax = 500.0;

        EnableCustomThoughtZones = 1;
        CustomThoughtZoneDefaultCooldownSeconds = 600.0;
        CustomThoughtZoneDefaultChance = 0.35;

        EnableSocialGroupThoughts = 1;
        SocialGroupThoughtCooldownSeconds = 240.0;
        SocialGroupThoughtChance = 0.35;
        SocialNearbyPlayerRadius = 45.0;
        SocialFriendlyTimeRequiredSeconds = 300.0;
        SocialMemoryDurationSeconds = 900.0;
        LoneWolfNoPlayerSeenSeconds = 10800.0;
        EnableTeammateShotMessages = 1;
        EnableTeammateDownMessages = 1;
        EnableLoneWolfMessages = 1;
        EnableFriendlyNearbyMessages = 1;

        EnableSanityCreep = 1;
        SanityThoughtCooldownSeconds = 300.0;
        SanityThoughtChance = 0.30;
        StartingSanity = 100.0;
        MinimumSanity = 0.0;
        SanityLossSkinHuman = 18.0;
        SanityLossEatHumanMeat = 25.0;
        SanityLossKillRestrainedPlayer = 35.0;
        SanityRegenPerMinute = 0.0;
        SanityUneasyThreshold = 70.0;
        SanityUnhingedThreshold = 35.0;
        SanityPsychoticThreshold = 15.0;
        EnableSanityUneasyMessages = 1;
        EnableSanityUnhingedMessages = 1;
        EnableSanityPsychoticMessages = 1;
        EnableCannibalismCreepMessages = 1;

        EnableAdminReload = 1;
        AdminReloadCommand = "!streload";


        if (MaxCombinedThoughtParts <= 0)
            MaxCombinedThoughtParts = 3;

        if (CombinedThoughtChance <= 0.0)
            CombinedThoughtChance = 0.65;
        if (UseExtremeSurvivalMessagesAtStateCount <= 0)
            UseExtremeSurvivalMessagesAtStateCount = 4;

        if (UseCriticalSurvivalMessagesAtStateCount <= 0)
            UseCriticalSurvivalMessagesAtStateCount = 5;

        if (!StarvingToDeathMessages || StarvingToDeathMessages.Count() == 0)
        {
            StarvingToDeathMessages = new array<string>;
            StarvingToDeathMessages.Insert("I am starving to death.");
            StarvingToDeathMessages.Insert("My body is eating itself, and my health is dropping.");
            StarvingToDeathMessages.Insert("I need food now or this is the end.");
            StarvingToDeathMessages.Insert("The hunger has gone past pain. I am dying.");
        }

        if (!DehydratingToDeathMessages || DehydratingToDeathMessages.Count() == 0)
        {
            DehydratingToDeathMessages = new array<string>;
            DehydratingToDeathMessages.Insert("I am dying of thirst.");
            DehydratingToDeathMessages.Insert("My body is shutting down without water.");
            DehydratingToDeathMessages.Insert("I need water now or I will not make it.");
            DehydratingToDeathMessages.Insert("My mouth is dry, my head is spinning, and my health is dropping.");
        }

        if (!FreezingToDeathMessages || FreezingToDeathMessages.Count() == 0)
        {
            FreezingToDeathMessages = new array<string>;
            FreezingToDeathMessages.Insert("I am freezing to death.");
            FreezingToDeathMessages.Insert("The cold is taking my health now.");
            FreezingToDeathMessages.Insert("I need fire or shelter immediately.");
            FreezingToDeathMessages.Insert("My body is shutting down from the cold.");
        }

        if (!OverheatingToDeathMessages || OverheatingToDeathMessages.Count() == 0)
        {
            OverheatingToDeathMessages = new array<string>;
            OverheatingToDeathMessages.Insert("I am overheating to death.");
            OverheatingToDeathMessages.Insert("The heat is taking my health now.");
            OverheatingToDeathMessages.Insert("I need shade and water immediately.");
            OverheatingToDeathMessages.Insert("My body cannot survive this heat much longer.");
        }

        if (!HungerColdInfectedMessages || HungerColdInfectedMessages.Count() == 0)
        {
            HungerColdInfectedMessages = new array<string>;
            HungerColdInfectedMessages.Insert("My stomach is empty, the cold is biting, and I can hear infected nearby.");
            HungerColdInfectedMessages.Insert("I need food, warmth, and a way out before those infected find me.");
            HungerColdInfectedMessages.Insert("I am hungry, freezing, and not alone out here.");
            HungerColdInfectedMessages.Insert("Every step feels heavier with hunger, cold, and infected close by.");
        }

        if (!HungerThirstMessages || HungerThirstMessages.Count() == 0)
        {
            HungerThirstMessages = new array<string>;
            HungerThirstMessages.Insert("I need food and water soon.");
            HungerThirstMessages.Insert("My stomach is empty and my mouth is dry.");
            HungerThirstMessages.Insert("I cannot keep moving like this without supplies.");
            HungerThirstMessages.Insert("Hunger and thirst are starting to wear me down.");
        }

        if (!ColdInfectedMessages || ColdInfectedMessages.Count() == 0)
        {
            ColdInfectedMessages = new array<string>;
            ColdInfectedMessages.Insert("The cold is making my hands stiff, and I can hear infected nearby.");
            ColdInfectedMessages.Insert("I need warmth, but the infected are too close.");
            ColdInfectedMessages.Insert("I should not stay here, but I am too cold to think straight.");
            ColdInfectedMessages.Insert("The cold is bad enough without infected nearby.");
        }

        if (!BleedingInfectedMessages || BleedingInfectedMessages.Count() == 0)
        {
            BleedingInfectedMessages = new array<string>;
            BleedingInfectedMessages.Insert("I am bleeding, and the infected are close.");
            BleedingInfectedMessages.Insert("The blood might draw attention. I need to move.");
            BleedingInfectedMessages.Insert("I need to stop this bleeding before they find me.");
            BleedingInfectedMessages.Insert("I cannot fight them like this while I am losing blood.");
        }

        if (!SickColdMessages || SickColdMessages.Count() == 0)
        {
            SickColdMessages = new array<string>;
            SickColdMessages.Insert("The sickness and cold are wearing me down.");
            SickColdMessages.Insert("I feel ill, and the cold is making everything worse.");
            SickColdMessages.Insert("I need medicine and warmth.");
            SickColdMessages.Insert("My body cannot fight sickness and cold forever.");
        }

        if (!HotThirstMessages || HotThirstMessages.Count() == 0)
        {
            HotThirstMessages = new array<string>;
            HotThirstMessages.Insert("The heat and thirst are draining me.");
            HotThirstMessages.Insert("I need water before this heat gets worse.");
            HotThirstMessages.Insert("My mouth is dry and my body is overheating.");
            HotThirstMessages.Insert("I need shade and water soon.");
        }

        if (!SickThirstMessages || SickThirstMessages.Count() == 0)
        {
            SickThirstMessages = new array<string>;
            SickThirstMessages.Insert("I feel sick, and thirst is making it worse.");
            SickThirstMessages.Insert("I need clean water and medicine.");
            SickThirstMessages.Insert("My stomach turns, and my mouth is dry.");
            SickThirstMessages.Insert("This sickness is harder to fight without water.");
        }

        if (!BleedingColdMessages || BleedingColdMessages.Count() == 0)
        {
            BleedingColdMessages = new array<string>;
            BleedingColdMessages.Insert("I am bleeding, and the cold is creeping in.");
            BleedingColdMessages.Insert("My blood is running warm, but everything else feels cold.");
            BleedingColdMessages.Insert("I need to stop the bleeding and get warm.");
            BleedingColdMessages.Insert("The cold makes my hands clumsy while I try to stop the blood.");
        }

        if (!BrokenLegHungerMessages || BrokenLegHungerMessages.Count() == 0)
        {
            BrokenLegHungerMessages = new array<string>;
            BrokenLegHungerMessages.Insert("My leg is ruined, and I still need food.");
            BrokenLegHungerMessages.Insert("I cannot search properly with this leg and an empty stomach.");
            BrokenLegHungerMessages.Insert("The hunger is bad, but moving on this leg is worse.");
            BrokenLegHungerMessages.Insert("I need food, but every step hurts.");
        }

        if (!BrokenLegThirstMessages || BrokenLegThirstMessages.Count() == 0)
        {
            BrokenLegThirstMessages = new array<string>;
            BrokenLegThirstMessages.Insert("My leg is broken, and my mouth is dry.");
            BrokenLegThirstMessages.Insert("I need water, but I can barely move.");
            BrokenLegThirstMessages.Insert("The thirst is pushing me forward, but this leg is holding me back.");
            BrokenLegThirstMessages.Insert("I need to find water before crawling becomes impossible.");
        }

        if (!BrokenLegColdMessages || BrokenLegColdMessages.Count() == 0)
        {
            BrokenLegColdMessages = new array<string>;
            BrokenLegColdMessages.Insert("My leg is broken, and the cold is setting in.");
            BrokenLegColdMessages.Insert("I need warmth, but moving hurts too much.");
            BrokenLegColdMessages.Insert("The cold is making this injury feel worse.");
            BrokenLegColdMessages.Insert("I need shelter before this leg and the cold finish me.");
        }

        if (!BrokenLegHotMessages || BrokenLegHotMessages.Count() == 0)
        {
            BrokenLegHotMessages = new array<string>;
            BrokenLegHotMessages.Insert("My leg is broken, and the heat is draining me.");
            BrokenLegHotMessages.Insert("I need shade, but moving is agony.");
            BrokenLegHotMessages.Insert("The heat makes every painful step worse.");
            BrokenLegHotMessages.Insert("I cannot keep dragging myself through this heat.");
        }

        if (!BrokenLegSickMessages || BrokenLegSickMessages.Count() == 0)
        {
            BrokenLegSickMessages = new array<string>;
            BrokenLegSickMessages.Insert("I feel sick, and my leg is ruined.");
            BrokenLegSickMessages.Insert("My body is weak, and I can barely move.");
            BrokenLegSickMessages.Insert("I need medicine and something for this leg.");
            BrokenLegSickMessages.Insert("This sickness and injury are wearing me down together.");
        }

        if (!BrokenLegBleedingMessages || BrokenLegBleedingMessages.Count() == 0)
        {
            BrokenLegBleedingMessages = new array<string>;
            BrokenLegBleedingMessages.Insert("My leg is broken, and I am bleeding.");
            BrokenLegBleedingMessages.Insert("I need to stop the bleeding before I worry about moving.");
            BrokenLegBleedingMessages.Insert("I cannot run, and I am losing blood.");
            BrokenLegBleedingMessages.Insert("This injury is bad enough without blood loss.");
        }

        if (!BrokenLegInfectedMessages || BrokenLegInfectedMessages.Count() == 0)
        {
            BrokenLegInfectedMessages = new array<string>;
            BrokenLegInfectedMessages.Insert("My leg is broken, and infected are nearby.");
            BrokenLegInfectedMessages.Insert("I cannot run from them like this.");
            BrokenLegInfectedMessages.Insert("I need to stay quiet. I will not outrun them.");
            BrokenLegInfectedMessages.Insert("If they hear me now, this leg will get me killed.");
        }

        if (!BrokenLegColdInfectedMessages || BrokenLegColdInfectedMessages.Count() == 0)
        {
            BrokenLegColdInfectedMessages = new array<string>;
            BrokenLegColdInfectedMessages.Insert("My leg is broken, the cold is biting, and infected are nearby.");
            BrokenLegColdInfectedMessages.Insert("I need warmth and silence, but I can barely move.");
            BrokenLegColdInfectedMessages.Insert("I cannot run, my hands are numb, and I can hear them close.");
            BrokenLegColdInfectedMessages.Insert("The cold and infected are closing in while this leg slows me down.");
        }

        if (!BrokenLegBleedingInfectedMessages || BrokenLegBleedingInfectedMessages.Count() == 0)
        {
            BrokenLegBleedingInfectedMessages = new array<string>;
            BrokenLegBleedingInfectedMessages.Insert("My leg is broken, I am bleeding, and infected are close.");
            BrokenLegBleedingInfectedMessages.Insert("I cannot run, and the blood will not stop.");
            BrokenLegBleedingInfectedMessages.Insert("I need bandages and silence before they find me.");
            BrokenLegBleedingInfectedMessages.Insert("If they come now, I cannot get away.");
        }

        if (!BrokenLegHungerThirstMessages || BrokenLegHungerThirstMessages.Count() == 0)
        {
            BrokenLegHungerThirstMessages = new array<string>;
            BrokenLegHungerThirstMessages.Insert("My leg is broken, my stomach is empty, and my mouth is dry.");
            BrokenLegHungerThirstMessages.Insert("I need supplies, but moving is almost impossible.");
            BrokenLegHungerThirstMessages.Insert("Food and water mean nothing if I cannot reach them.");
            BrokenLegHungerThirstMessages.Insert("I need to treat this leg before hunger and thirst finish me.");
        }

        if (!HungerColdMessages || HungerColdMessages.Count() == 0)
        {
            HungerColdMessages = new array<string>;
            HungerColdMessages.Insert("The hunger is worse in this cold.");
            HungerColdMessages.Insert("I need food and warmth before my body gives up.");
            HungerColdMessages.Insert("My stomach is empty and my hands are going numb.");
            HungerColdMessages.Insert("The cold is biting harder with nothing in my stomach.");
            HungerColdMessages.Insert("I need calories and heat.");
        }

        if (!HungerHotMessages || HungerHotMessages.Count() == 0)
        {
            HungerHotMessages = new array<string>;
            HungerHotMessages.Insert("The heat is draining what little strength I have left.");
            HungerHotMessages.Insert("I am hungry and overheating.");
            HungerHotMessages.Insert("My body feels weak in this heat.");
            HungerHotMessages.Insert("I need food, shade, and a moment to breathe.");
            HungerHotMessages.Insert("The heat makes the hunger feel worse.");
        }

        if (!HungerSickMessages || HungerSickMessages.Count() == 0)
        {
            HungerSickMessages = new array<string>;
            HungerSickMessages.Insert("I feel sick, and the hunger is making it worse.");
            HungerSickMessages.Insert("My stomach is empty, but I do not know if I can keep food down.");
            HungerSickMessages.Insert("I need food, but my body feels wrong.");
            HungerSickMessages.Insert("The sickness is eating at me as much as the hunger.");
            HungerSickMessages.Insert("I need to treat this before I get any weaker.");
        }

        if (!HungerBleedingMessages || HungerBleedingMessages.Count() == 0)
        {
            HungerBleedingMessages = new array<string>;
            HungerBleedingMessages.Insert("I am hungry and losing blood. This is bad.");
            HungerBleedingMessages.Insert("My body needs food, but first I need to stop the bleeding.");
            HungerBleedingMessages.Insert("The blood loss is making the hunger feel worse.");
            HungerBleedingMessages.Insert("I cannot recover like this.");
            HungerBleedingMessages.Insert("I need to stop bleeding and find food.");
        }

        if (!HungerInfectedMessages || HungerInfectedMessages.Count() == 0)
        {
            HungerInfectedMessages = new array<string>;
            HungerInfectedMessages.Insert("I need food, but the infected are too close.");
            HungerInfectedMessages.Insert("My stomach is empty, and I can hear infected nearby.");
            HungerInfectedMessages.Insert("I should not search for food with infected this close.");
            HungerInfectedMessages.Insert("I need supplies, but I need to stay quiet.");
            HungerInfectedMessages.Insert("The hunger is pushing me toward danger.");
        }

        if (!ThirstColdMessages || ThirstColdMessages.Count() == 0)
        {
            ThirstColdMessages = new array<string>;
            ThirstColdMessages.Insert("My mouth is dry and my hands are freezing.");
            ThirstColdMessages.Insert("I need water and warmth.");
            ThirstColdMessages.Insert("The cold is slowing me down, and the thirst is getting worse.");
            ThirstColdMessages.Insert("I should find shelter and something safe to drink.");
            ThirstColdMessages.Insert("I cannot ignore thirst just because I am cold.");
        }

        if (!ThirstBleedingMessages || ThirstBleedingMessages.Count() == 0)
        {
            ThirstBleedingMessages = new array<string>;
            ThirstBleedingMessages.Insert("I am losing blood and drying out.");
            ThirstBleedingMessages.Insert("I need water, but this bleeding comes first.");
            ThirstBleedingMessages.Insert("My mouth is dry and my wound is still open.");
            ThirstBleedingMessages.Insert("I cannot keep bleeding like this.");
            ThirstBleedingMessages.Insert("I need to patch myself up and find water.");
        }

        if (!ThirstInfectedMessages || ThirstInfectedMessages.Count() == 0)
        {
            ThirstInfectedMessages = new array<string>;
            ThirstInfectedMessages.Insert("I need water, but the infected are nearby.");
            ThirstInfectedMessages.Insert("My throat is dry, and I can hear them moving.");
            ThirstInfectedMessages.Insert("The well is useless if I get caught reaching it.");
            ThirstInfectedMessages.Insert("I need to stay quiet and find water.");
            ThirstInfectedMessages.Insert("Thirst is making me careless.");
        }

        if (!HotSickMessages || HotSickMessages.Count() == 0)
        {
            HotSickMessages = new array<string>;
            HotSickMessages.Insert("The heat is making this sickness worse.");
            HotSickMessages.Insert("I feel feverish and overheated.");
            HotSickMessages.Insert("I need shade, water, and medicine.");
            HotSickMessages.Insert("My head is pounding from heat and illness.");
            HotSickMessages.Insert("I cannot tell if this is fever or the weather.");
        }

        if (!HotBleedingMessages || HotBleedingMessages.Count() == 0)
        {
            HotBleedingMessages = new array<string>;
            HotBleedingMessages.Insert("I am bleeding and overheating.");
            HotBleedingMessages.Insert("The heat is making me feel faint.");
            HotBleedingMessages.Insert("I need to stop the bleeding and cool down.");
            HotBleedingMessages.Insert("My vision is swimming in this heat.");
            HotBleedingMessages.Insert("I cannot keep losing blood under this sun.");
        }

        if (!HotInfectedMessages || HotInfectedMessages.Count() == 0)
        {
            HotInfectedMessages = new array<string>;
            HotInfectedMessages.Insert("The heat is draining me, and the infected are close.");
            HotInfectedMessages.Insert("I need shade, but I cannot stop here.");
            HotInfectedMessages.Insert("Sweat is running into my eyes, and I can hear them nearby.");
            HotInfectedMessages.Insert("The heat is making every sound feel closer.");
            HotInfectedMessages.Insert("I need to move before they hear me.");
        }

        if (!SickBleedingMessages || SickBleedingMessages.Count() == 0)
        {
            SickBleedingMessages = new array<string>;
            SickBleedingMessages.Insert("I am sick and bleeding. My body cannot take much more.");
            SickBleedingMessages.Insert("The wound is open, and I already feel ill.");
            SickBleedingMessages.Insert("I need treatment before this gets worse.");
            SickBleedingMessages.Insert("This sickness will not heal while I am losing blood.");
            SickBleedingMessages.Insert("I need medicine and bandages.");
        }

        if (!SickInfectedMessages || SickInfectedMessages.Count() == 0)
        {
            SickInfectedMessages = new array<string>;
            SickInfectedMessages.Insert("I feel sick, and the infected are nearby.");
            SickInfectedMessages.Insert("I can barely focus with them this close.");
            SickInfectedMessages.Insert("I need medicine, but I need to survive this first.");
            SickInfectedMessages.Insert("Every cough could give me away.");
            SickInfectedMessages.Insert("I should not be near infected while I feel this weak.");
        }

        if (!HungerThirstColdMessages || HungerThirstColdMessages.Count() == 0)
        {
            HungerThirstColdMessages = new array<string>;
            HungerThirstColdMessages.Insert("I need food, water, and warmth before my body gives out.");
            HungerThirstColdMessages.Insert("My stomach is empty, my mouth is dry, and the cold is biting.");
            HungerThirstColdMessages.Insert("I cannot survive long like this.");
            HungerThirstColdMessages.Insert("I need shelter and supplies now.");
            HungerThirstColdMessages.Insert("Every basic need is catching up with me.");
        }

        if (!HungerThirstHotMessages || HungerThirstHotMessages.Count() == 0)
        {
            HungerThirstHotMessages = new array<string>;
            HungerThirstHotMessages.Insert("I am hungry, thirsty, and overheating.");
            HungerThirstHotMessages.Insert("The heat is burning through what little strength I have left.");
            HungerThirstHotMessages.Insert("I need shade, water, and food.");
            HungerThirstHotMessages.Insert("My body is running on nothing in this heat.");
            HungerThirstHotMessages.Insert("I cannot keep moving like this.");
        }

        if (!HungerThirstInfectedMessages || HungerThirstInfectedMessages.Count() == 0)
        {
            HungerThirstInfectedMessages = new array<string>;
            HungerThirstInfectedMessages.Insert("I need food and water, but the infected are too close.");
            HungerThirstInfectedMessages.Insert("My body is empty, and I can hear them nearby.");
            HungerThirstInfectedMessages.Insert("I need supplies, but searching now could get me killed.");
            HungerThirstInfectedMessages.Insert("Hunger and thirst are pushing me into danger.");
            HungerThirstInfectedMessages.Insert("I need to stay quiet and find supplies.");
        }

        if (!ThirstHotInfectedMessages || ThirstHotInfectedMessages.Count() == 0)
        {
            ThirstHotInfectedMessages = new array<string>;
            ThirstHotInfectedMessages.Insert("I need water, I am overheating, and the infected are close.");
            ThirstHotInfectedMessages.Insert("The heat is drying me out, but I cannot stop here.");
            ThirstHotInfectedMessages.Insert("My throat is dry, sweat is in my eyes, and I can hear them nearby.");
            ThirstHotInfectedMessages.Insert("I need water, shade, and distance from the infected.");
            ThirstHotInfectedMessages.Insert("This heat is making me careless around infected.");
        }

        if (!SickColdInfectedMessages || SickColdInfectedMessages.Count() == 0)
        {
            SickColdInfectedMessages = new array<string>;
            SickColdInfectedMessages.Insert("I feel sick, the cold is biting, and infected are nearby.");
            SickColdInfectedMessages.Insert("I need warmth and medicine, but I cannot stop here.");
            SickColdInfectedMessages.Insert("My body is weak, my hands are numb, and I can hear them close.");
            SickColdInfectedMessages.Insert("I need shelter before the sickness and infected finish me.");
            SickColdInfectedMessages.Insert("Every sound feels closer while I am this weak.");
        }

        if (!BleedingColdInfectedMessages || BleedingColdInfectedMessages.Count() == 0)
        {
            BleedingColdInfectedMessages = new array<string>;
            BleedingColdInfectedMessages.Insert("I am bleeding, freezing, and the infected are close.");
            BleedingColdInfectedMessages.Insert("My hands are numb, and I need to stop this bleeding now.");
            BleedingColdInfectedMessages.Insert("The cold is slowing me down while the infected close in.");
            BleedingColdInfectedMessages.Insert("I need shelter, bandages, and a way out.");
            BleedingColdInfectedMessages.Insert("If I cannot stop the bleeding, the cold or infected will finish me.");
        }

        if (!BleedingSickInfectedMessages || BleedingSickInfectedMessages.Count() == 0)
        {
            BleedingSickInfectedMessages = new array<string>;
            BleedingSickInfectedMessages.Insert("I am sick, bleeding, and the infected are close.");
            BleedingSickInfectedMessages.Insert("My body is failing, and I can hear them nearby.");
            BleedingSickInfectedMessages.Insert("I need bandages, medicine, and silence.");
            BleedingSickInfectedMessages.Insert("I cannot fight like this.");
            BleedingSickInfectedMessages.Insert("If they find me now, I am done.");
        }

        if (!ExtremeSurvivalMessages || ExtremeSurvivalMessages.Count() == 0)
        {
            ExtremeSurvivalMessages = new array<string>;
            ExtremeSurvivalMessages.Insert("Everything is going wrong at once.");
            ExtremeSurvivalMessages.Insert("My body is failing, and this place is not safe.");
            ExtremeSurvivalMessages.Insert("I need shelter, supplies, and a way out now.");
            ExtremeSurvivalMessages.Insert("I cannot keep surviving like this.");
            ExtremeSurvivalMessages.Insert("One more mistake could finish me.");
            ExtremeSurvivalMessages.Insert("I need to stop, think, and survive the next few minutes.");
            ExtremeSurvivalMessages.Insert("My body is screaming for help.");
            ExtremeSurvivalMessages.Insert("I am running out of time.");
            ExtremeSurvivalMessages.Insert("I need to deal with the worst problem first.");
            ExtremeSurvivalMessages.Insert("This is how people die out here.");
        }

        if (!CriticalSurvivalMessages || CriticalSurvivalMessages.Count() == 0)
        {
            CriticalSurvivalMessages = new array<string>;
            CriticalSurvivalMessages.Insert("I am falling apart.");
            CriticalSurvivalMessages.Insert("This is bad. Really bad.");
            CriticalSurvivalMessages.Insert("I need to survive the next minute before thinking about anything else.");
            CriticalSurvivalMessages.Insert("Everything hurts, everything is wrong, and I am not safe.");
            CriticalSurvivalMessages.Insert("I am close to the edge.");
            CriticalSurvivalMessages.Insert("I need help, but there is nobody coming.");
            CriticalSurvivalMessages.Insert("My body is giving up.");
            CriticalSurvivalMessages.Insert("I cannot let panic take over.");
            CriticalSurvivalMessages.Insert("Stop the bleeding. Find shelter. Stay alive.");
            CriticalSurvivalMessages.Insert("I do not know how much longer I can keep going.");
        }


        if (!EnergyStage1Messages || EnergyStage1Messages.Count() == 0)
        {
            EnergyStage1Messages = new array<string>;
            EnergyStage1Messages.Insert("I feel fed for now.");
            EnergyStage1Messages.Insert("My stomach is settled.");
            EnergyStage1Messages.Insert("I can keep moving for a while.");
            EnergyStage1Messages.Insert("Food is not a problem right now.");
        }

        if (!EnergyStage2Messages || EnergyStage2Messages.Count() == 0)
        {
            EnergyStage2Messages = new array<string>;
            EnergyStage2Messages.Insert("I could eat soon.");
            EnergyStage2Messages.Insert("My stomach feels a little empty.");
            EnergyStage2Messages.Insert("I should keep an eye out for food.");
            EnergyStage2Messages.Insert("A small meal would help.");
        }

        if (!EnergyStage3Messages || EnergyStage3Messages.Count() == 0)
        {
            EnergyStage3Messages = new array<string>;
            EnergyStage3Messages.Insert("My stomach is starting to hurt.");
            EnergyStage3Messages.Insert("I need food soon.");
            EnergyStage3Messages.Insert("I can feel my strength fading.");
            EnergyStage3Messages.Insert("I keep thinking about food.");
        }

        if (!EnergyStage4Messages || EnergyStage4Messages.Count() == 0)
        {
            EnergyStage4Messages = new array<string>;
            EnergyStage4Messages.Insert("I am starving.");
            EnergyStage4Messages.Insert("My body feels weak.");
            EnergyStage4Messages.Insert("I need food now.");
            EnergyStage4Messages.Insert("I do not know how much longer I can go without eating.");
        }

        if (!WaterStage1Messages || WaterStage1Messages.Count() == 0)
        {
            WaterStage1Messages = new array<string>;
            WaterStage1Messages.Insert("I feel hydrated.");
            WaterStage1Messages.Insert("My mouth feels fine.");
            WaterStage1Messages.Insert("Water is not an issue right now.");
            WaterStage1Messages.Insert("I can travel without worrying about thirst.");
        }

        if (!WaterStage2Messages || WaterStage2Messages.Count() == 0)
        {
            WaterStage2Messages = new array<string>;
            WaterStage2Messages.Insert("My mouth is getting dry.");
            WaterStage2Messages.Insert("I should drink soon.");
            WaterStage2Messages.Insert("I could use some water.");
            WaterStage2Messages.Insert("I need to remember the next well.");
        }

        if (!WaterStage3Messages || WaterStage3Messages.Count() == 0)
        {
            WaterStage3Messages = new array<string>;
            WaterStage3Messages.Insert("My throat is dry.");
            WaterStage3Messages.Insert("I need water soon.");
            WaterStage3Messages.Insert("My head is starting to ache.");
            WaterStage3Messages.Insert("I should not ignore this thirst.");
        }

        if (!WaterStage4Messages || WaterStage4Messages.Count() == 0)
        {
            WaterStage4Messages = new array<string>;
            WaterStage4Messages.Insert("I am dehydrated.");
            WaterStage4Messages.Insert("My mouth feels like sand.");
            WaterStage4Messages.Insert("I need water now.");
            WaterStage4Messages.Insert("I feel faint from thirst.");
        }

        if (!BloodStage1Messages || BloodStage1Messages.Count() == 0)
        {
            BloodStage1Messages = new array<string>;
            BloodStage1Messages.Insert("I feel steady for now.");
            BloodStage1Messages.Insert("My blood feels strong enough.");
            BloodStage1Messages.Insert("I can keep moving.");
        }

        if (!BloodStage2Messages || BloodStage2Messages.Count() == 0)
        {
            BloodStage2Messages = new array<string>;
            BloodStage2Messages.Insert("I feel a little light-headed.");
            BloodStage2Messages.Insert("I should avoid losing more blood.");
            BloodStage2Messages.Insert("That blood loss is starting to show.");
        }

        if (!BloodStage3Messages || BloodStage3Messages.Count() == 0)
        {
            BloodStage3Messages = new array<string>;
            BloodStage3Messages.Insert("My head is swimming.");
            BloodStage3Messages.Insert("I need to recover before pushing further.");
            BloodStage3Messages.Insert("The blood loss is slowing me down.");
        }

        if (!BloodStage4Messages || BloodStage4Messages.Count() == 0)
        {
            BloodStage4Messages = new array<string>;
            BloodStage4Messages.Insert("I feel like I am going to pass out.");
            BloodStage4Messages.Insert("My vision keeps fading.");
            BloodStage4Messages.Insert("I have lost too much blood.");
        }

        if (!ShockStage1Messages || ShockStage1Messages.Count() == 0)
        {
            ShockStage1Messages = new array<string>;
            ShockStage1Messages.Insert("I feel alert enough.");
            ShockStage1Messages.Insert("I can keep myself together.");
            ShockStage1Messages.Insert("My nerves are steady.");
        }

        if (!ShockStage2Messages || ShockStage2Messages.Count() == 0)
        {
            ShockStage2Messages = new array<string>;
            ShockStage2Messages.Insert("That shook me.");
            ShockStage2Messages.Insert("I need a second to steady myself.");
            ShockStage2Messages.Insert("My hands are not as steady as they should be.");
        }

        if (!ShockStage3Messages || ShockStage3Messages.Count() == 0)
        {
            ShockStage3Messages = new array<string>;
            ShockStage3Messages.Insert("I feel stunned.");
            ShockStage3Messages.Insert("My body is struggling to respond.");
            ShockStage3Messages.Insert("I need to get behind cover.");
        }

        if (!ShockStage4Messages || ShockStage4Messages.Count() == 0)
        {
            ShockStage4Messages = new array<string>;
            ShockStage4Messages.Insert("I am about to black out.");
            ShockStage4Messages.Insert("Everything is fading.");
            ShockStage4Messages.Insert("I cannot stay conscious much longer.");
        }

        if (!Cold_Mild_Messages || Cold_Mild_Messages.Count() == 0)
        {
            Cold_Mild_Messages = new array<string>;
            Cold_Mild_Messages.Insert("The air feels cold.");
            Cold_Mild_Messages.Insert("I should keep moving.");
            Cold_Mild_Messages.Insert("My hands are getting stiff.");
            Cold_Mild_Messages.Insert("I need to stay dry.");
        }

        if (!Cold_Moderate_Messages || Cold_Moderate_Messages.Count() == 0)
        {
            Cold_Moderate_Messages = new array<string>;
            Cold_Moderate_Messages.Insert("I am getting cold.");
            Cold_Moderate_Messages.Insert("My clothes are not keeping the chill out.");
            Cold_Moderate_Messages.Insert("I need shelter or a fire.");
            Cold_Moderate_Messages.Insert("My fingers are going numb.");
        }

        if (!Cold_Severe_Messages || Cold_Severe_Messages.Count() == 0)
        {
            Cold_Severe_Messages = new array<string>;
            Cold_Severe_Messages.Insert("I am freezing.");
            Cold_Severe_Messages.Insert("This cold is cutting through me.");
            Cold_Severe_Messages.Insert("I need warmth now.");
            Cold_Severe_Messages.Insert("I can barely feel my hands.");
        }

        if (!Cold_Critical_Messages || Cold_Critical_Messages.Count() == 0)
        {
            Cold_Critical_Messages = new array<string>;
            Cold_Critical_Messages.Insert("I cannot stop shaking.");
            Cold_Critical_Messages.Insert("My body is shutting down from the cold.");
            Cold_Critical_Messages.Insert("I need fire, shelter, or dry clothes immediately.");
            Cold_Critical_Messages.Insert("I am not going to survive this cold much longer.");
        }

        if (!Hot_Mild_Messages || Hot_Mild_Messages.Count() == 0)
        {
            Hot_Mild_Messages = new array<string>;
            Hot_Mild_Messages.Insert("I feel warm.");
            Hot_Mild_Messages.Insert("I should avoid overheating.");
            Hot_Mild_Messages.Insert("The heat is starting to build.");
            Hot_Mild_Messages.Insert("I may need to slow down.");
        }

        if (!Hot_Moderate_Messages || Hot_Moderate_Messages.Count() == 0)
        {
            Hot_Moderate_Messages = new array<string>;
            Hot_Moderate_Messages.Insert("I am getting too hot.");
            Hot_Moderate_Messages.Insert("I need shade or lighter clothing.");
            Hot_Moderate_Messages.Insert("This heat is draining me.");
            Hot_Moderate_Messages.Insert("I should drink more water.");
        }

        if (!Hot_Severe_Messages || Hot_Severe_Messages.Count() == 0)
        {
            Hot_Severe_Messages = new array<string>;
            Hot_Severe_Messages.Insert("I am overheating.");
            Hot_Severe_Messages.Insert("My head feels heavy from the heat.");
            Hot_Severe_Messages.Insert("I need to cool down.");
            Hot_Severe_Messages.Insert("I should stop running.");
        }

        if (!Hot_Critical_Messages || Hot_Critical_Messages.Count() == 0)
        {
            Hot_Critical_Messages = new array<string>;
            Hot_Critical_Messages.Insert("I feel like I am going to collapse.");
            Hot_Critical_Messages.Insert("The heat is unbearable.");
            Hot_Critical_Messages.Insert("I need water and shade now.");
            Hot_Critical_Messages.Insert("My body cannot handle this heat much longer.");
        }

        if (!Sickness_Early_Messages || Sickness_Early_Messages.Count() == 0)
        {
            Sickness_Early_Messages = new array<string>;
            Sickness_Early_Messages.Insert("Something feels off.");
            Sickness_Early_Messages.Insert("My stomach feels unsettled.");
            Sickness_Early_Messages.Insert("I do not feel right.");
            Sickness_Early_Messages.Insert("I might be getting sick.");
        }

        if (!Sickness_Moderate_Messages || Sickness_Moderate_Messages.Count() == 0)
        {
            Sickness_Moderate_Messages = new array<string>;
            Sickness_Moderate_Messages.Insert("I feel ill.");
            Sickness_Moderate_Messages.Insert("My body aches.");
            Sickness_Moderate_Messages.Insert("My stomach keeps turning.");
            Sickness_Moderate_Messages.Insert("I need medicine.");
        }

        if (!Sickness_Severe_Messages || Sickness_Severe_Messages.Count() == 0)
        {
            Sickness_Severe_Messages = new array<string>;
            Sickness_Severe_Messages.Insert("I feel feverish.");
            Sickness_Severe_Messages.Insert("I can barely focus.");
            Sickness_Severe_Messages.Insert("This sickness is getting worse.");
            Sickness_Severe_Messages.Insert("I need treatment soon.");
        }

        if (!Sickness_Critical_Messages || Sickness_Critical_Messages.Count() == 0)
        {
            Sickness_Critical_Messages = new array<string>;
            Sickness_Critical_Messages.Insert("I feel like I am dying.");
            Sickness_Critical_Messages.Insert("My body is fighting something bad.");
            Sickness_Critical_Messages.Insert("I need medicine now.");
            Sickness_Critical_Messages.Insert("I do not know how much longer I can keep going.");
        }

        if (!Bleeding_One_Messages || Bleeding_One_Messages.Count() == 0)
        {
            Bleeding_One_Messages = new array<string>;
            Bleeding_One_Messages.Insert("I am bleeding.");
            Bleeding_One_Messages.Insert("I need to bandage this.");
            Bleeding_One_Messages.Insert("Blood is running down my body.");
            Bleeding_One_Messages.Insert("This wound needs attention.");
        }

        if (!Bleeding_Multiple_Messages || Bleeding_Multiple_Messages.Count() == 0)
        {
            Bleeding_Multiple_Messages = new array<string>;
            Bleeding_Multiple_Messages.Insert("I am losing blood fast.");
            Bleeding_Multiple_Messages.Insert("There is blood everywhere.");
            Bleeding_Multiple_Messages.Insert("I need to stop the bleeding now.");
            Bleeding_Multiple_Messages.Insert("I have more than one wound open.");
        }

        if (!Bleeding_Critical_Messages || Bleeding_Critical_Messages.Count() == 0)
        {
            Bleeding_Critical_Messages = new array<string>;
            Bleeding_Critical_Messages.Insert("I am bleeding out.");
            Bleeding_Critical_Messages.Insert("My vision is starting to fade.");
            Bleeding_Critical_Messages.Insert("I need bandages immediately.");
            Bleeding_Critical_Messages.Insert("If I do not stop this bleeding, I am dead.");
        }

        if (!BrokenLegMessages || BrokenLegMessages.Count() == 0)
        {
            BrokenLegMessages = new array<string>;
            BrokenLegMessages.Insert("My leg is broken.");
            BrokenLegMessages.Insert("I cannot move properly like this.");
            BrokenLegMessages.Insert("Every step sends pain through my leg.");
            BrokenLegMessages.Insert("I need a splint before I can travel safely.");
            BrokenLegMessages.Insert("Running is not an option now.");
            BrokenLegMessages.Insert("This leg will get me killed if I do not treat it.");
        }

        if (!Infected_Far_Messages || Infected_Far_Messages.Count() == 0)
        {
            Infected_Far_Messages = new array<string>;
            Infected_Far_Messages.Insert("I hear infected nearby.");
            Infected_Far_Messages.Insert("Something is moving out there.");
            Infected_Far_Messages.Insert("I should stay quiet.");
            Infected_Far_Messages.Insert("I do not think I am alone.");
        }

        if (!Infected_Close_Messages || Infected_Close_Messages.Count() == 0)
        {
            Infected_Close_Messages = new array<string>;
            Infected_Close_Messages.Insert("There are infected close.");
            Infected_Close_Messages.Insert("I need to watch my noise.");
            Infected_Close_Messages.Insert("I can hear them breathing.");
            Infected_Close_Messages.Insert("One wrong move and they will hear me.");
        }

        if (!Infected_VeryClose_Messages || Infected_VeryClose_Messages.Count() == 0)
        {
            Infected_VeryClose_Messages = new array<string>;
            Infected_VeryClose_Messages.Insert("They are right on top of me.");
            Infected_VeryClose_Messages.Insert("I need to move carefully.");
            Infected_VeryClose_Messages.Insert("I can hear them just outside.");
            Infected_VeryClose_Messages.Insert("This place is not safe.");
        }

        if (!Infected_Surrounded_Messages || Infected_Surrounded_Messages.Count() == 0)
        {
            Infected_Surrounded_Messages = new array<string>;
            Infected_Surrounded_Messages.Insert("There are too many of them.");
            Infected_Surrounded_Messages.Insert("I am surrounded.");
            Infected_Surrounded_Messages.Insert("I need an escape route.");
            Infected_Surrounded_Messages.Insert("If they hear me, this could go bad fast.");
        }

        if (!EatingMessages || EatingMessages.Count() == 0)
        {
            EatingMessages = new array<string>;
            EatingMessages.Insert("That helped.");
            EatingMessages.Insert("I needed that.");
            EatingMessages.Insert("My stomach settles a little.");
            EatingMessages.Insert("I should find more food before moving on.");
            EatingMessages.Insert("That tasted awful, but it will keep me alive.");
        }

        if (!DrinkingMessages || DrinkingMessages.Count() == 0)
        {
            DrinkingMessages = new array<string>;
            DrinkingMessages.Insert("That feels better.");
            DrinkingMessages.Insert("My throat needed that.");
            DrinkingMessages.Insert("I should refill before I leave.");
            DrinkingMessages.Insert("Clean water is worth more than ammo out here.");
            DrinkingMessages.Insert("I needed every drop.");
        }

        if (!UnsafeDrinkingMessages || UnsafeDrinkingMessages.Count() == 0)
        {
            UnsafeDrinkingMessages = new array<string>;
            UnsafeDrinkingMessages.Insert("I hope that water was clean.");
            UnsafeDrinkingMessages.Insert("That tasted off.");
            UnsafeDrinkingMessages.Insert("My stomach turns after drinking that.");
            UnsafeDrinkingMessages.Insert("I should have purified it first.");
        }

        if (!UnjamMessages || UnjamMessages.Count() == 0)
        {
            UnjamMessages = new array<string>;
            UnjamMessages.Insert("Come on, clear it.");
            UnjamMessages.Insert("Not now.");
            UnjamMessages.Insert("This weapon is going to get me killed.");
            UnjamMessages.Insert("I need to maintain this gun.");
            UnjamMessages.Insert("That could have been the end of me.");
        }

        if (!UnjamSuccessMessages || UnjamSuccessMessages.Count() == 0)
        {
            UnjamSuccessMessages = new array<string>;
            UnjamSuccessMessages.Insert("It is clear.");
            UnjamSuccessMessages.Insert("Back in the fight.");
            UnjamSuccessMessages.Insert("I got it working again.");
        }

        if (!SkinningAnimalMessages || SkinningAnimalMessages.Count() == 0)
        {
            SkinningAnimalMessages = new array<string>;
            SkinningAnimalMessages.Insert("This will keep me alive.");
            SkinningAnimalMessages.Insert("Fresh meat means another day.");
            SkinningAnimalMessages.Insert("I should cook this before moving on.");
            SkinningAnimalMessages.Insert("The smell might attract attention.");
            SkinningAnimalMessages.Insert("Waste nothing.");
        }

        if (!SkinningHumanMessages || SkinningHumanMessages.Count() == 0)
        {
            SkinningHumanMessages = new array<string>;
            SkinningHumanMessages.Insert("I should not think about what I am doing.");
            SkinningHumanMessages.Insert("Survival changes people.");
            SkinningHumanMessages.Insert("There is no going back from this.");
            SkinningHumanMessages.Insert("I hope nobody saw that.");
        }

        if (!BandagingMessages || BandagingMessages.Count() == 0)
        {
            BandagingMessages = new array<string>;
            BandagingMessages.Insert("Hold pressure.");
            BandagingMessages.Insert("I need to stop the bleeding.");
            BandagingMessages.Insert("That should slow it down.");
            BandagingMessages.Insert("I cannot afford to lose more blood.");
            BandagingMessages.Insert("Stay calm. Wrap it tight.");
        }

        if (!BandageSuccessMessages || BandageSuccessMessages.Count() == 0)
        {
            BandageSuccessMessages = new array<string>;
            BandageSuccessMessages.Insert("The bleeding has stopped.");
            BandageSuccessMessages.Insert("That was close.");
            BandageSuccessMessages.Insert("I need to be more careful.");
        }

        if (!FireStartingMessages || FireStartingMessages.Count() == 0)
        {
            FireStartingMessages = new array<string>;
            FireStartingMessages.Insert("Come on, catch.");
            FireStartingMessages.Insert("A fire would change everything right now.");
            FireStartingMessages.Insert("I need warmth.");
            FireStartingMessages.Insert("Smoke might give me away.");
            FireStartingMessages.Insert("Finally, some heat.");
        }

        if (!CookingMessages || CookingMessages.Count() == 0)
        {
            CookingMessages = new array<string>;
            CookingMessages.Insert("The smell makes me hungry.");
            CookingMessages.Insert("Hot food might keep me going.");
            CookingMessages.Insert("I should not burn this.");
            CookingMessages.Insert("A warm meal feels rare now.");
        }

        if (!FishingMessages || FishingMessages.Count() == 0)
        {
            FishingMessages = new array<string>;
            FishingMessages.Insert("Patience.");
            FishingMessages.Insert("Something has to bite eventually.");
            FishingMessages.Insert("Food from the water is safer than the towns.");
            FishingMessages.Insert("I hope this line holds.");
        }

        if (!RepairMessages || RepairMessages.Count() == 0)
        {
            RepairMessages = new array<string>;
            RepairMessages.Insert("This should hold for now.");
            RepairMessages.Insert("Better than letting it fall apart.");
            RepairMessages.Insert("I need to take care of my gear.");
            RepairMessages.Insert("Nothing lasts out here.");
        }

        if (!GeneralActionMessages || GeneralActionMessages.Count() == 0)
        {
            GeneralActionMessages = new array<string>;
            GeneralActionMessages.Insert("Keep moving.");
            GeneralActionMessages.Insert("One more thing to do.");
            GeneralActionMessages.Insert("Do it carefully.");
            GeneralActionMessages.Insert("Small tasks keep me alive.");
        }

        if (!OpenCloseActionMessages || OpenCloseActionMessages.Count() == 0)
        {
            OpenCloseActionMessages = new array<string>;
            OpenCloseActionMessages.Insert("Careful. Doors make noise.");
            OpenCloseActionMessages.Insert("Check the corners before moving through.");
            OpenCloseActionMessages.Insert("Every door could have someone behind it.");
            OpenCloseActionMessages.Insert("Quiet hands. Slow movements.");
        }

        if (!MedicineConsumeMessages || MedicineConsumeMessages.Count() == 0)
        {
            MedicineConsumeMessages = new array<string>;
            MedicineConsumeMessages.Insert("I hope this helps.");
            MedicineConsumeMessages.Insert("This better be the right medicine.");
            MedicineConsumeMessages.Insert("Give it time to work.");
            MedicineConsumeMessages.Insert("Medicine is worth more than ammunition right now.");
        }

        if (!WoundCareActionMessages || WoundCareActionMessages.Count() == 0)
        {
            WoundCareActionMessages = new array<string>;
            WoundCareActionMessages.Insert("Hold still. Fix the damage.");
            WoundCareActionMessages.Insert("This is going to hurt.");
            WoundCareActionMessages.Insert("Patch it now or pay for it later.");
            WoundCareActionMessages.Insert("Breathe. One wound at a time.");
        }

        if (!InjectionMessages || InjectionMessages.Count() == 0)
        {
            InjectionMessages = new array<string>;
            InjectionMessages.Insert("Needle in. Do not think about it.");
            InjectionMessages.Insert("This might keep me standing.");
            InjectionMessages.Insert("I hope this works fast.");
            InjectionMessages.Insert("No room for hesitation.");
        }

        if (!BloodMedicalMessages || BloodMedicalMessages.Count() == 0)
        {
            BloodMedicalMessages = new array<string>;
            BloodMedicalMessages.Insert("I need to trust this blood.");
            BloodMedicalMessages.Insert("This could save a life, or end one.");
            BloodMedicalMessages.Insert("Check it twice. Mistakes kill.");
            BloodMedicalMessages.Insert("Blood and saline are hope in a bag.");
        }

        if (!DisinfectActionMessages || DisinfectActionMessages.Count() == 0)
        {
            DisinfectActionMessages = new array<string>;
            DisinfectActionMessages.Insert("Clean it before it turns bad.");
            DisinfectActionMessages.Insert("This sting is better than infection.");
            DisinfectActionMessages.Insert("I need to keep this from getting worse.");
            DisinfectActionMessages.Insert("Dirty wounds kill slowly.");
        }

        if (!RestrainActionMessages || RestrainActionMessages.Count() == 0)
        {
            RestrainActionMessages = new array<string>;
            RestrainActionMessages.Insert("This is not a good situation.");
            RestrainActionMessages.Insert("Hands controlled. Threat reduced.");
            RestrainActionMessages.Insert("Nobody trusts anyone anymore.");
            RestrainActionMessages.Insert("This could turn ugly fast.");
        }

        if (!CraftingActionMessages || CraftingActionMessages.Count() == 0)
        {
            CraftingActionMessages = new array<string>;
            CraftingActionMessages.Insert("Make do with what is left.");
            CraftingActionMessages.Insert("Improvised is better than nothing.");
            CraftingActionMessages.Insert("Hands busy. Mind focused.");
            CraftingActionMessages.Insert("If it holds, it is good enough.");
        }

        if (!DeployActionMessages || DeployActionMessages.Count() == 0)
        {
            DeployActionMessages = new array<string>;
            DeployActionMessages.Insert("This place will have to do.");
            DeployActionMessages.Insert("Set it down and keep watch.");
            DeployActionMessages.Insert("I should not stay exposed for long.");
            DeployActionMessages.Insert("Placement matters. Escape routes matter more.");
        }

        if (!GardeningActionMessages || GardeningActionMessages.Count() == 0)
        {
            GardeningActionMessages = new array<string>;
            GardeningActionMessages.Insert("Food takes patience.");
            GardeningActionMessages.Insert("If this grows, it might save me later.");
            GardeningActionMessages.Insert("The soil still remembers life.");
            GardeningActionMessages.Insert("A garden is hope, if nobody finds it first.");
        }

        if (!ResourceGatheringMessages || ResourceGatheringMessages.Count() == 0)
        {
            ResourceGatheringMessages = new array<string>;
            ResourceGatheringMessages.Insert("Useful materials are worth the noise.");
            ResourceGatheringMessages.Insert("Every swing could draw attention.");
            ResourceGatheringMessages.Insert("Take what I need and move.");
            ResourceGatheringMessages.Insert("Nothing comes free out here.");
        }

        if (!LiquidTransferMessages || LiquidTransferMessages.Count() == 0)
        {
            LiquidTransferMessages = new array<string>;
            LiquidTransferMessages.Insert("Do not waste a drop.");
            LiquidTransferMessages.Insert("Water, fuel, blood. Everything has value now.");
            LiquidTransferMessages.Insert("Fill it while I can.");
            LiquidTransferMessages.Insert("I should check what I am carrying.");
        }

        if (!FireplaceActionMessages || FireplaceActionMessages.Count() == 0)
        {
            FireplaceActionMessages = new array<string>;
            FireplaceActionMessages.Insert("A fire is comfort and a signal.");
            FireplaceActionMessages.Insert("Heat helps, smoke betrays.");
            FireplaceActionMessages.Insert("This could keep me alive tonight.");
            FireplaceActionMessages.Insert("I need warmth, but I need caution too.");
        }

        if (!ElectronicsActionMessages || ElectronicsActionMessages.Count() == 0)
        {
            ElectronicsActionMessages = new array<string>;
            ElectronicsActionMessages.Insert("If this still works, it could matter.");
            ElectronicsActionMessages.Insert("Power means attention.");
            ElectronicsActionMessages.Insert("Old technology still has uses.");
            ElectronicsActionMessages.Insert("Light and noise can save me or expose me.");
        }

        if (!NavigationActionMessages || NavigationActionMessages.Count() == 0)
        {
            NavigationActionMessages = new array<string>;
            NavigationActionMessages.Insert("Know where I am before moving.");
            NavigationActionMessages.Insert("A wrong turn can kill as surely as a bullet.");
            NavigationActionMessages.Insert("Check the route. Then move.");
            NavigationActionMessages.Insert("I need a plan, not panic.");
        }

        if (!LockActionMessages || LockActionMessages.Count() == 0)
        {
            LockActionMessages = new array<string>;
            LockActionMessages.Insert("Locks mean someone wanted control.");
            LockActionMessages.Insert("This might keep something safe, or keep me out.");
            LockActionMessages.Insert("Take the time. Watch the area.");
            LockActionMessages.Insert("Security always attracts attention.");
        }

        if (!TrapExplosiveMessages || TrapExplosiveMessages.Count() == 0)
        {
            TrapExplosiveMessages = new array<string>;
            TrapExplosiveMessages.Insert("Careful. One mistake here is final.");
            TrapExplosiveMessages.Insert("Slow hands. Clear head.");
            TrapExplosiveMessages.Insert("This kind of work gets people killed.");
            TrapExplosiveMessages.Insert("Do not rush explosives or traps.");
        }

        if (!BaseBuildingActionMessages || BaseBuildingActionMessages.Count() == 0)
        {
            BaseBuildingActionMessages = new array<string>;
            BaseBuildingActionMessages.Insert("Build it strong or do not build it at all.");
            BaseBuildingActionMessages.Insert("Every wall is a promise and a target.");
            BaseBuildingActionMessages.Insert("This might hold for a while.");
            BaseBuildingActionMessages.Insert("A base is never truly safe.");
        }

        if (!VehicleActionMessages || VehicleActionMessages.Count() == 0)
        {
            VehicleActionMessages = new array<string>;
            VehicleActionMessages.Insert("Engines are freedom and noise.");
            VehicleActionMessages.Insert("If this runs, everyone nearby will know.");
            VehicleActionMessages.Insert("Vehicles solve problems and create new ones.");
            VehicleActionMessages.Insert("Check it twice before trusting it.");
        }

        if (!InventoryActionMessages || InventoryActionMessages.Count() == 0)
        {
            InventoryActionMessages = new array<string>;
            InventoryActionMessages.Insert("Sort it fast. Stay aware.");
            InventoryActionMessages.Insert("Too much gear slows decisions.");
            InventoryActionMessages.Insert("Everything I carry should earn its weight.");
            InventoryActionMessages.Insert("Pack it so I can survive with it.");
        }

        if (!BuryStashMessages || BuryStashMessages.Count() == 0)
        {
            BuryStashMessages = new array<string>;
            BuryStashMessages.Insert("Hide it well. Forget nothing.");
            BuryStashMessages.Insert("Someone could still find this.");
            BuryStashMessages.Insert("The ground keeps secrets until it does not.");
            BuryStashMessages.Insert("A stash is only safe if nobody sees me make it.");
        }

        if (!PersonalCareMessages || PersonalCareMessages.Count() == 0)
        {
            PersonalCareMessages = new array<string>;
            PersonalCareMessages.Insert("Small comforts still matter.");
            PersonalCareMessages.Insert("Clean hands, clear head.");
            PersonalCareMessages.Insert("It is easy to forget being human.");
            PersonalCareMessages.Insert("Take care of the body that carries me.");
        }

        if (!AmmoManagementMessages || AmmoManagementMessages.Count() == 0)
        {
            AmmoManagementMessages = new array<string>;
            AmmoManagementMessages.Insert("Count the rounds.");
            AmmoManagementMessages.Insert("Every bullet matters.");
            AmmoManagementMessages.Insert("Load it now, need it later.");
            AmmoManagementMessages.Insert("Do not fumble this when it counts.");
        }

        if (!MovementActionMessages || MovementActionMessages.Count() == 0)
        {
            MovementActionMessages = new array<string>;
            MovementActionMessages.Insert("Watch the footing.");
            MovementActionMessages.Insert("One slip could be enough.");
            MovementActionMessages.Insert("Move carefully.");
            MovementActionMessages.Insert("Do not get stuck here.");
        }

        if (!WorldInteractionMessages || WorldInteractionMessages.Count() == 0)
        {
            WorldInteractionMessages = new array<string>;
            WorldInteractionMessages.Insert("This place still has systems buried in it.");
            WorldInteractionMessages.Insert("Old infrastructure, new danger.");
            WorldInteractionMessages.Insert("I should be ready for what this changes.");
            WorldInteractionMessages.Insert("Nothing down here feels safe.");
        }

        if (!AdminSteamIds || AdminSteamIds.Count() == 0)
        {
            AdminSteamIds = new array<string>;
            AdminSteamIds.Insert("76561198000000000");
        }

        if (!LocationZones || LocationZones.Count() == 0)
        {
            LocationZones = new array<ref ST_LocationZone>;

            ST_LocationZone zone1 = new ST_LocationZone();
            zone1.Name = "North West Airfield";
            zone1.Type = "Military";
            zone1.X = 4620.0;
            zone1.Z = 10300.0;
            zone1.Radius = 900.0;
            LocationZones.Insert(zone1);

            ST_LocationZone zone2 = new ST_LocationZone();
            zone2.Name = "Chernogorsk";
            zone2.Type = "City";
            zone2.X = 6700.0;
            zone2.Z = 2600.0;
            zone2.Radius = 900.0;
            LocationZones.Insert(zone2);

            ST_LocationZone zone3 = new ST_LocationZone();
            zone3.Name = "Elektrozavodsk";
            zone3.Type = "City";
            zone3.X = 10400.0;
            zone3.Z = 2200.0;
            zone3.Radius = 850.0;
            LocationZones.Insert(zone3);

            ST_LocationZone zone4 = new ST_LocationZone();
            zone4.Name = "Balota Airstrip";
            zone4.Type = "Military";
            zone4.X = 4970.0;
            zone4.Z = 2450.0;
            zone4.Radius = 500.0;
            LocationZones.Insert(zone4);
        }

        if (!LocationCoastMessages || LocationCoastMessages.Count() == 0)
        {
            LocationCoastMessages = new array<string>;
            LocationCoastMessages.Insert("The coast is where everyone starts, and where too many people die.");
            LocationCoastMessages.Insert("I should not stay near the coast for long.");
            LocationCoastMessages.Insert("Fresh tracks, empty houses, and bad decisions. That is the coast.");
            LocationCoastMessages.Insert("The sea is behind me. Survival is inland.");
            LocationCoastMessages.Insert("Someone desperate is always close to the coast.");
        }

        if (!LocationTownMessages || LocationTownMessages.Count() == 0)
        {
            LocationTownMessages = new array<string>;
            LocationTownMessages.Insert("This town feels picked clean.");
            LocationTownMessages.Insert("Every window feels like it is watching me.");
            LocationTownMessages.Insert("Small towns are quiet until they are not.");
            LocationTownMessages.Insert("There might still be something useful here.");
            LocationTownMessages.Insert("I should search quickly and leave.");
        }

        if (!LocationCityMessages || LocationCityMessages.Count() == 0)
        {
            LocationCityMessages = new array<string>;
            LocationCityMessages.Insert("Too many buildings. Too many angles.");
            LocationCityMessages.Insert("A city can hide supplies, infected, and people with bad intentions.");
            LocationCityMessages.Insert("I do not like how many windows overlook these streets.");
            LocationCityMessages.Insert("The bigger the city, the more chances to die.");
            LocationCityMessages.Insert("Every street here feels exposed.");
        }

        if (!LocationForestMessages || LocationForestMessages.Count() == 0)
        {
            LocationForestMessages = new array<string>;
            LocationForestMessages.Insert("The trees might keep me hidden.");
            LocationForestMessages.Insert("The forest is safer, but it gives nothing for free.");
            LocationForestMessages.Insert("I can disappear here if I stay quiet.");
            LocationForestMessages.Insert("Every branch snap sounds louder out here.");
            LocationForestMessages.Insert("The woods feel empty, but I know better.");
        }

        if (!LocationWildernessMessages || LocationWildernessMessages.Count() == 0)
        {
            LocationWildernessMessages = new array<string>;
            LocationWildernessMessages.Insert("There is nothing out here but distance and bad weather.");
            LocationWildernessMessages.Insert("If I get hurt out here, nobody will find me.");
            LocationWildernessMessages.Insert("The wilderness hides me, but it can starve me too.");
            LocationWildernessMessages.Insert("I need to know where the next water source is.");
            LocationWildernessMessages.Insert("Out here, mistakes take longer to kill you, but they still kill you.");
        }

        if (!LocationMilitaryMessages || LocationMilitaryMessages.Count() == 0)
        {
            LocationMilitaryMessages = new array<string>;
            LocationMilitaryMessages.Insert("Military places always smell like trouble.");
            LocationMilitaryMessages.Insert("Good gear brings bad company.");
            LocationMilitaryMessages.Insert("Someone else will come here looking for weapons.");
            LocationMilitaryMessages.Insert("I should assume I am being watched.");
            LocationMilitaryMessages.Insert("This place is worth looting, but not worth dying for.");
        }

        if (!LocationPoliceMessages || LocationPoliceMessages.Count() == 0)
        {
            LocationPoliceMessages = new array<string>;
            LocationPoliceMessages.Insert("Police stations are never as empty as they look.");
            LocationPoliceMessages.Insert("There might be ammunition here, or someone waiting for it.");
            LocationPoliceMessages.Insert("I should check the corners.");
            LocationPoliceMessages.Insert("This place attracts desperate people.");
        }

        if (!LocationMedicalMessages || LocationMedicalMessages.Count() == 0)
        {
            LocationMedicalMessages = new array<string>;
            LocationMedicalMessages.Insert("Hospitals always mean someone desperate came here first.");
            LocationMedicalMessages.Insert("Medicine is worth the risk.");
            LocationMedicalMessages.Insert("If anything is left, it will not be much.");
            LocationMedicalMessages.Insert("I need to move fast. Everyone needs medical supplies.");
            LocationMedicalMessages.Insert("This place feels like panic frozen in time.");
        }

        if (!LocationIndustrialMessages || LocationIndustrialMessages.Count() == 0)
        {
            LocationIndustrialMessages = new array<string>;
            LocationIndustrialMessages.Insert("Rust, metal, and hiding places everywhere.");
            LocationIndustrialMessages.Insert("Industrial yards always have too many blind corners.");
            LocationIndustrialMessages.Insert("Tools might be worth the risk.");
            LocationIndustrialMessages.Insert("I should listen before crossing the open ground.");
            LocationIndustrialMessages.Insert("This place echoes too much.");
        }

        if (!LocationFarmMessages || LocationFarmMessages.Count() == 0)
        {
            LocationFarmMessages = new array<string>;
            LocationFarmMessages.Insert("A farm might mean food, tools, or nothing at all.");
            LocationFarmMessages.Insert("The open fields make me feel exposed.");
            LocationFarmMessages.Insert("Barns hide more than hay now.");
            LocationFarmMessages.Insert("There may be animals nearby.");
            LocationFarmMessages.Insert("Food used to grow here. Now I have to fight for scraps.");
        }

        if (!LocationWaterMessages || LocationWaterMessages.Count() == 0)
        {
            LocationWaterMessages = new array<string>;
            LocationWaterMessages.Insert("Water means life, and footsteps.");
            LocationWaterMessages.Insert("Someone else may come here to drink.");
            LocationWaterMessages.Insert("I should fill everything I can.");
            LocationWaterMessages.Insert("A water source is useful, but it is never truly safe.");
            LocationWaterMessages.Insert("I need to drink and move before someone finds me.");
        }


        if (PriorityPlayerMemory <= 0) PriorityPlayerMemory = 40;
        if (PriorityStealthNoise <= 0) PriorityStealthNoise = 45;
        if (PriorityShelter <= 0) PriorityShelter = 25;
        if (PriorityMentalState <= 0) PriorityMentalState = 60;
        if (PriorityCustomThoughtZone <= 0) PriorityCustomThoughtZone = 30;

        if (PlayerMemoryThoughtCooldownSeconds <= 0.0) PlayerMemoryThoughtCooldownSeconds = 240.0;
        if (PlayerMemoryThoughtChance <= 0.0) PlayerMemoryThoughtChance = 0.30;
        if (PlayerMemoryDurationSeconds <= 0.0) PlayerMemoryDurationSeconds = 600.0;

        if (StealthNoiseThoughtCooldownSeconds <= 0.0) StealthNoiseThoughtCooldownSeconds = 180.0;
        if (StealthNoiseThoughtChance <= 0.0) StealthNoiseThoughtChance = 0.35;
        if (StealthNoiseInfectedRadius <= 0.0) StealthNoiseInfectedRadius = 35.0;
        if (StealthNoiseRunSpeedThreshold <= 0.0) StealthNoiseRunSpeedThreshold = 3.2;

        if (ShelterThoughtCooldownSeconds <= 0.0) ShelterThoughtCooldownSeconds = 300.0;
        if (ShelterThoughtChance <= 0.0) ShelterThoughtChance = 0.30;
        if (ShelterScanRadius <= 0.0) ShelterScanRadius = 14.0;
        if (ShelterNearbyBuildingCountRequired <= 0) ShelterNearbyBuildingCountRequired = 1;

        if (RecentMessageMemoryCount <= 0) RecentMessageMemoryCount = 12;
        if (RecentMessageBlockSeconds <= 0.0) RecentMessageBlockSeconds = 900.0;

        if (MentalStateThoughtCooldownSeconds <= 0.0) MentalStateThoughtCooldownSeconds = 300.0;
        if (MentalStateThoughtChance <= 0.0) MentalStateThoughtChance = 0.25;
        if (MentalStateCriticalHealthMax <= 0.0) MentalStateCriticalHealthMax = 30.0;
        if (MentalStateLowBloodMax <= 0.0) MentalStateLowBloodMax = 3500.0;
        if (MentalStateLowFoodMax <= 0.0) MentalStateLowFoodMax = 500.0;
        if (MentalStateLowWaterMax <= 0.0) MentalStateLowWaterMax = 500.0;

        if (CustomThoughtZoneDefaultCooldownSeconds <= 0.0) CustomThoughtZoneDefaultCooldownSeconds = 600.0;
        if (CustomThoughtZoneDefaultChance <= 0.0) CustomThoughtZoneDefaultChance = 0.35;
        if (!CustomThoughtZones) CustomThoughtZones = new array<ref ST_CustomThoughtZone>;

        if (!PlayerMemoryRecentDamageMessages || PlayerMemoryRecentDamageMessages.Count() == 0)
        {
            PlayerMemoryRecentDamageMessages = new array<string>;
            PlayerMemoryRecentDamageMessages.Insert("That hit is still on my mind.");
            PlayerMemoryRecentDamageMessages.Insert("I need to keep moving after that.");
            PlayerMemoryRecentDamageMessages.Insert("Pain makes every decision slower.");
            PlayerMemoryRecentDamageMessages.Insert("I should not let that happen again.");
        }

        if (!PlayerMemoryRecentBleedingMessages || PlayerMemoryRecentBleedingMessages.Count() == 0)
        {
            PlayerMemoryRecentBleedingMessages = new array<string>;
            PlayerMemoryRecentBleedingMessages.Insert("I can still feel where I was bleeding.");
            PlayerMemoryRecentBleedingMessages.Insert("That wound could have ended me.");
            PlayerMemoryRecentBleedingMessages.Insert("I need to check myself before moving on.");
            PlayerMemoryRecentBleedingMessages.Insert("Blood loss changes how everything feels.");
        }

        if (!PlayerMemoryRecentGunshotMessages || PlayerMemoryRecentGunshotMessages.Count() == 0)
        {
            PlayerMemoryRecentGunshotMessages = new array<string>;
            PlayerMemoryRecentGunshotMessages.Insert("That gunshot is still ringing in my head.");
            PlayerMemoryRecentGunshotMessages.Insert("Someone with a gun changes everything.");
            PlayerMemoryRecentGunshotMessages.Insert("I need cover before confidence.");
            PlayerMemoryRecentGunshotMessages.Insert("One shot was enough warning.");
        }

        if (!PlayerMemoryRecentCorpseMessages || PlayerMemoryRecentCorpseMessages.Count() == 0)
        {
            PlayerMemoryRecentCorpseMessages = new array<string>;
            PlayerMemoryRecentCorpseMessages.Insert("That body was a warning.");
            PlayerMemoryRecentCorpseMessages.Insert("Someone died close by. I should not ignore that.");
            PlayerMemoryRecentCorpseMessages.Insert("Bodies draw questions, flies, and people.");
            PlayerMemoryRecentCorpseMessages.Insert("I need to leave before I become part of the scene.");
        }

        if (!PlayerMemoryRecentMilitaryMessages || PlayerMemoryRecentMilitaryMessages.Count() == 0)
        {
            PlayerMemoryRecentMilitaryMessages = new array<string>;
            PlayerMemoryRecentMilitaryMessages.Insert("Military places bring armed survivors.");
            PlayerMemoryRecentMilitaryMessages.Insert("Good loot is never free.");
            PlayerMemoryRecentMilitaryMessages.Insert("I should assume someone watched this place before me.");
            PlayerMemoryRecentMilitaryMessages.Insert("The risk here follows me even after I leave.");
        }

        if (!PlayerMemoryRecentSurvivalCrisisMessages || PlayerMemoryRecentSurvivalCrisisMessages.Count() == 0)
        {
            PlayerMemoryRecentSurvivalCrisisMessages = new array<string>;
            PlayerMemoryRecentSurvivalCrisisMessages.Insert("I came too close to dying.");
            PlayerMemoryRecentSurvivalCrisisMessages.Insert("My body needs a break before it gives up.");
            PlayerMemoryRecentSurvivalCrisisMessages.Insert("I need food, water, warmth, and time.");
            PlayerMemoryRecentSurvivalCrisisMessages.Insert("Survival is getting narrower.");
        }

        if (!StealthNoiseInfectedNearbyMessages || StealthNoiseInfectedNearbyMessages.Count() == 0)
        {
            StealthNoiseInfectedNearbyMessages = new array<string>;
            StealthNoiseInfectedNearbyMessages.Insert("Too much noise will pull them straight to me.");
            StealthNoiseInfectedNearbyMessages.Insert("Slow down. The infected are close enough to hear.");
            StealthNoiseInfectedNearbyMessages.Insert("Every step matters when they are this near.");
            StealthNoiseInfectedNearbyMessages.Insert("Quiet movement keeps me alive longer than speed.");
        }

        if (!StealthNoiseNightMessages || StealthNoiseNightMessages.Count() == 0)
        {
            StealthNoiseNightMessages = new array<string>;
            StealthNoiseNightMessages.Insert("Sound feels louder in the dark.");
            StealthNoiseNightMessages.Insert("At night, one bad step can give me away.");
            StealthNoiseNightMessages.Insert("I should move like someone is listening.");
            StealthNoiseNightMessages.Insert("The dark hides me, but it hides everyone else too.");
        }

        if (!StealthNoiseMilitaryMessages || StealthNoiseMilitaryMessages.Count() == 0)
        {
            StealthNoiseMilitaryMessages = new array<string>;
            StealthNoiseMilitaryMessages.Insert("Running through a military zone is asking to be heard.");
            StealthNoiseMilitaryMessages.Insert("Slow, quiet, and ready. That is how I leave here.");
            StealthNoiseMilitaryMessages.Insert("Noise here travels to the wrong people.");
            StealthNoiseMilitaryMessages.Insert("Good gear brings bad company. I should move carefully.");
        }

        if (!ShelterSafeMessages || ShelterSafeMessages.Count() == 0)
        {
            ShelterSafeMessages = new array<string>;
            ShelterSafeMessages.Insert("Four walls help, but they do not make me safe.");
            ShelterSafeMessages.Insert("This place might give me a moment to think.");
            ShelterSafeMessages.Insert("Shelter is useful. Exits matter more.");
            ShelterSafeMessages.Insert("I should check every corner before trusting this place.");
        }

        if (!ShelterUnsafeMessages || ShelterUnsafeMessages.Count() == 0)
        {
            ShelterUnsafeMessages = new array<string>;
            ShelterUnsafeMessages.Insert("This building could already belong to someone else.");
            ShelterUnsafeMessages.Insert("Closed rooms hide bad surprises.");
            ShelterUnsafeMessages.Insert("I need an exit plan before I relax.");
            ShelterUnsafeMessages.Insert("Shelter can become a trap fast.");
        }

        if (!ShelterBadWeatherMessages || ShelterBadWeatherMessages.Count() == 0)
        {
            ShelterBadWeatherMessages = new array<string>;
            ShelterBadWeatherMessages.Insert("At least this place can keep some weather off me.");
            ShelterBadWeatherMessages.Insert("I need to dry out while I can.");
            ShelterBadWeatherMessages.Insert("Bad weather makes shelter worth the risk.");
            ShelterBadWeatherMessages.Insert("This cover might save my temperature.");
        }

        if (!ShelterNightMessages || ShelterNightMessages.Count() == 0)
        {
            ShelterNightMessages = new array<string>;
            ShelterNightMessages.Insert("Night makes every doorway feel dangerous.");
            ShelterNightMessages.Insert("If I stay here, I need to secure the exits.");
            ShelterNightMessages.Insert("This place is better than standing outside in the dark.");
            ShelterNightMessages.Insert("I should listen before I move through the rooms.");
        }

        if (!MentalStateStableMessages || MentalStateStableMessages.Count() == 0)
        {
            MentalStateStableMessages = new array<string>;
            MentalStateStableMessages.Insert("Keep priorities simple. Water, food, shelter.");
            MentalStateStableMessages.Insert("Think clearly. Waste nothing.");
            MentalStateStableMessages.Insert("I can handle this if I stay methodical.");
            MentalStateStableMessages.Insert("One good decision after another.");
        }

        if (!MentalStateUneasyMessages || MentalStateUneasyMessages.Count() == 0)
        {
            MentalStateUneasyMessages = new array<string>;
            MentalStateUneasyMessages.Insert("Something feels wrong.");
            MentalStateUneasyMessages.Insert("I cannot shake the feeling that I am being watched.");
            MentalStateUneasyMessages.Insert("I need to slow down and listen.");
            MentalStateUneasyMessages.Insert("This place is getting under my skin.");
        }

        if (!MentalStateAfraidMessages || MentalStateAfraidMessages.Count() == 0)
        {
            MentalStateAfraidMessages = new array<string>;
            MentalStateAfraidMessages.Insert("Do not panic. Panic wastes energy.");
            MentalStateAfraidMessages.Insert("I hate how close everything sounds.");
            MentalStateAfraidMessages.Insert("Fear is useful if it keeps me careful.");
            MentalStateAfraidMessages.Insert("I need to breathe and keep moving.");
        }

        if (!MentalStateDesperateMessages || MentalStateDesperateMessages.Count() == 0)
        {
            MentalStateDesperateMessages = new array<string>;
            MentalStateDesperateMessages.Insert("I am running out of choices.");
            MentalStateDesperateMessages.Insert("Anything useful matters now.");
            MentalStateDesperateMessages.Insert("I need supplies before I need a plan.");
            MentalStateDesperateMessages.Insert("Desperation makes people loud. I need to stay smart.");
        }

        if (!MentalStateNumbMessages || MentalStateNumbMessages.Count() == 0)
        {
            MentalStateNumbMessages = new array<string>;
            MentalStateNumbMessages.Insert("I do not feel much anymore.");
            MentalStateNumbMessages.Insert("Maybe numb is better than scared.");
            MentalStateNumbMessages.Insert("Keep moving. Feeling can come later.");
            MentalStateNumbMessages.Insert("This place takes pieces from everyone.");
        }

        if (!MentalStateAggressiveMessages || MentalStateAggressiveMessages.Count() == 0)
        {
            MentalStateAggressiveMessages = new array<string>;
            MentalStateAggressiveMessages.Insert("If someone pushes me now, they will regret it.");
            MentalStateAggressiveMessages.Insert("I am tired of being hunted.");
            MentalStateAggressiveMessages.Insert("No more hesitation.");
            MentalStateAggressiveMessages.Insert("Threats need to be dealt with before they grow.");
        }

        if (!MentalStateBrokenMessages || MentalStateBrokenMessages.Count() == 0)
        {
            MentalStateBrokenMessages = new array<string>;
            MentalStateBrokenMessages.Insert("I do not know how much longer I can keep doing this.");
            MentalStateBrokenMessages.Insert("Everything hurts. Everything is heavy.");
            MentalStateBrokenMessages.Insert("I need one reason to keep moving.");
            MentalStateBrokenMessages.Insert("The world is getting smaller with every step.");
        }

        if (!MentalStateFocusedMessages || MentalStateFocusedMessages.Count() == 0)
        {
            MentalStateFocusedMessages = new array<string>;
            MentalStateFocusedMessages.Insert("Focus. Check corners. Check supplies. Move.");
            MentalStateFocusedMessages.Insert("Noise, cover, exits. Nothing else matters.");
            MentalStateFocusedMessages.Insert("Stay sharp and stay alive.");
            MentalStateFocusedMessages.Insert("I need to solve the next problem, not all of them.");
        }

        if (EnableMissionStoragePersistentData == 0 && previousConfigVersion < 33)
            EnableMissionStoragePersistentData = 1;

        if (PersistentStorageRoot == "")
            PersistentStorageRoot = "$mission:storage_1/ZombiCideMods/SurvivorThoughts";

        if (PersistentDataFolderName == "")
            PersistentDataFolderName = "Data";

        if (PersistentStateDataFile == "")
            PersistentStateDataFile = "$mission:storage_1/ZombiCideMods/SurvivorThoughts/Data/PlayerPersistentStates.json";

        if (PersonalityDataFile == "" || PersonalityDataFile == "$profile:ZombicideMods/SurvivorThoughts/Data/PlayerPersonalities.json")
            PersonalityDataFile = "$mission:storage_1/ZombiCideMods/SurvivorThoughts/Data/PlayerPersonalities.json";

        if (PersistentAutosaveSeconds <= 0.0)
            PersistentAutosaveSeconds = 60.0;

        ConfigVersion = 64;
    

        if (ConfigVersion < 39)
            ConfigVersion = 64;

        if (JournalMajorEventMinPriority <= 0)
            JournalMajorEventMinPriority = 55;

        ST_EnsureAllStarterMessageDefaults();


        ST_EnsureImmediateReactionStarterMessages();
        ConfigVersion = 64;
    }


    void ST_EnsureImmediateReactionStarterMessages()
    {
        if (!CombatHitMessages) CombatHitMessages = new array<string>;
        if (CombatHitMessages.Count() == 0)
        {
            CombatHitMessages.Insert("That hit shook me.");
            CombatHitMessages.Insert("Pain flashes through me.");
            CombatHitMessages.Insert("I need to move before another hit lands.");
            CombatHitMessages.Insert("That hurt more than I expected.");
        }

        if (!ZombieHitMessages) ZombieHitMessages = new array<string>;
        if (ZombieHitMessages.Count() == 0)
        {
            ZombieHitMessages.Insert("It clawed through me.");
            ZombieHitMessages.Insert("That infected got too close.");
            ZombieHitMessages.Insert("I need distance before it tears me open.");
            ZombieHitMessages.Insert("The hit leaves my skin burning.");
        }

        if (!PlayerMeleeHitMessages) PlayerMeleeHitMessages = new array<string>;
        if (PlayerMeleeHitMessages.Count() == 0)
        {
            PlayerMeleeHitMessages.Insert("Someone hit me. Think later, move now.");
            PlayerMeleeHitMessages.Insert("That was a person, not infected.");
            PlayerMeleeHitMessages.Insert("They are close enough to finish this.");
            PlayerMeleeHitMessages.Insert("I need space before they swing again.");
        }

        if (!GunshotHitMessages) GunshotHitMessages = new array<string>;
        if (GunshotHitMessages.Count() == 0)
        {
            GunshotHitMessages.Insert("I have been shot.");
            GunshotHitMessages.Insert("The round punched through before I heard it.");
            GunshotHitMessages.Insert("Find cover. Stop the bleeding. Survive.");
            GunshotHitMessages.Insert("Someone has me ranged in.");
        }

        if (!ExplosionHitMessages) ExplosionHitMessages = new array<string>;
        if (ExplosionHitMessages.Count() == 0)
        {
            ExplosionHitMessages.Insert("The blast took the world out from under me.");
            ExplosionHitMessages.Insert("My ears are ringing. I need cover.");
            ExplosionHitMessages.Insert("That explosion nearly ended me.");
            ExplosionHitMessages.Insert("Everything hurts after that blast.");
        }

        if (!HeavyHitMessages) HeavyHitMessages = new array<string>;
        if (HeavyHitMessages.Count() == 0)
        {
            HeavyHitMessages.Insert("That nearly dropped me.");
            HeavyHitMessages.Insert("My body almost gave out.");
            HeavyHitMessages.Insert("I cannot take another hit like that.");
            HeavyHitMessages.Insert("For a second, everything went black.");
        }

        if (!BleedingStartedMessages) BleedingStartedMessages = new array<string>;
        if (BleedingStartedMessages.Count() == 0)
        {
            BleedingStartedMessages.Insert("I am bleeding.");
            BleedingStartedMessages.Insert("That opened me up.");
            BleedingStartedMessages.Insert("Blood is running down my body.");
            BleedingStartedMessages.Insert("I need to bandage this now.");
        }

        if (!BleedingWorseMessages) BleedingWorseMessages = new array<string>;
        if (BleedingWorseMessages.Count() == 0)
        {
            BleedingWorseMessages.Insert("I am bleeding from more than one wound.");
            BleedingWorseMessages.Insert("There is too much blood.");
            BleedingWorseMessages.Insert("I need to stop the bleeding before I pass out.");
            BleedingWorseMessages.Insert("This is getting bad fast.");
        }

        if (!BleedingStoppedMessages) BleedingStoppedMessages = new array<string>;
        if (BleedingStoppedMessages.Count() == 0)
        {
            BleedingStoppedMessages.Insert("The bleeding has stopped.");
            BleedingStoppedMessages.Insert("That should hold for now.");
            BleedingStoppedMessages.Insert("At least I am not bleeding anymore.");
            BleedingStoppedMessages.Insert("That was too close.");
        }
    }
}
