class ST_AdvancedCombinedState
{
    bool HasHunger;
    bool HasThirst;
    bool HasCold;
    bool HasHot;
    bool HasSick;
    bool HasBleeding;
    bool HasBlood;
    bool HasShock;
    bool HasBrokenLeg;
    bool HasInfected;
    bool HasWeather;
    bool HasTimeOfDay;
    bool HasBadItem;
    bool HasCombatStress;
    bool HasContamination;
    bool HasCorpse;
    bool HasLowSanity;
    bool HasRecentGunshot;
    bool HasCompanionBond;
}

modded class PlayerBase
{

    float ST_AC_GetWorldHour()
    {
        if (!GetGame() || !GetGame().GetWorld())
            return 12.0;

        int year, month, day, hour, minute;
        GetGame().GetWorld().GetDate(year, month, day, hour, minute);

        return hour + (minute / 60.0);
    }

    bool ST_AC_IsNight(ST_SurvivorThoughtsConfig config)
    {
        if (!config)
            return false;

        float hour = ST_AC_GetWorldHour();

        if (hour >= config.NightStartHour || hour < config.DawnStartHour)
            return true;

        return false;
    }

    bool ST_AC_IsInMilitaryZone(ST_SurvivorThoughtsConfig config)
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

    bool ST_AC_IsNearShelter(ST_SurvivorThoughtsConfig config)
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


    string ST_GetAdvancedCombinedThoughtMessage(ST_SurvivorThoughtsConfig config, ST_AdvancedCombinedState state)
    {
        if (!config || config.EnableAdvancedCombinedMessages != 1)
            return "";

        if (!state)
            return "";

        if (Math.RandomFloatInclusive(0.0, 1.0) > config.AdvancedCombinedChance)
            return "";

        bool isNight = ST_AC_IsNight(config);
        bool isMilitary = ST_AC_IsInMilitaryZone(config);
        bool lowSanity = state.HasLowSanity;

        if (config.EnableExpandedAdvancedCombos == 1)
        {
            if (state.HasHunger && state.HasThirst && state.HasCold && config.StarvingDehydratedColdMessages && config.StarvingDehydratedColdMessages.Count() > 0)
                return config.StarvingDehydratedColdMessages.GetRandomElement();

            if (state.HasHot && state.HasThirst && state.HasSick && config.HotDehydratedSickMessages && config.HotDehydratedSickMessages.Count() > 0)
                return config.HotDehydratedSickMessages.GetRandomElement();

            if (state.HasBleeding && state.HasBlood && state.HasShock && config.BleedingLowBloodShockMessages && config.BleedingLowBloodShockMessages.Count() > 0)
                return config.BleedingLowBloodShockMessages.GetRandomElement();

            if (state.HasBleeding && state.HasBlood && state.HasRecentGunshot && config.GunshotBleedingLowBloodMessages && config.GunshotBleedingLowBloodMessages.Count() > 0)
                return config.GunshotBleedingLowBloodMessages.GetRandomElement();

            if (state.HasBrokenLeg && state.HasBleeding && state.HasInfected && config.BrokenLegBleedingInfectedMessages && config.BrokenLegBleedingInfectedMessages.Count() > 0)
                return config.BrokenLegBleedingInfectedMessages.GetRandomElement();

            if (isNight && state.HasInfected && state.HasWeather && config.NightInfectedRainMessages && config.NightInfectedRainMessages.Count() > 0)
                return config.NightInfectedRainMessages.GetRandomElement();

            if (isMilitary && isNight && state.HasWeather && config.MilitaryNightStormMessages && config.MilitaryNightStormMessages.Count() > 0)
                return config.MilitaryNightStormMessages.GetRandomElement();

            if (lowSanity && isNight && config.LoneWolfLowSanityNightMessages && config.LoneWolfLowSanityNightMessages.Count() > 0)
                return config.LoneWolfLowSanityNightMessages.GetRandomElement();

            if (state.HasCompanionBond && isNight && config.CompanionDeadNightMessages && config.CompanionDeadNightMessages.Count() > 0)
                return config.CompanionDeadNightMessages.GetRandomElement();

            if (state.HasCorpse && lowSanity && isNight && config.CorpseLowSanityNightMessages && config.CorpseLowSanityNightMessages.Count() > 0)
                return config.CorpseLowSanityNightMessages.GetRandomElement();

            if (state.HasInfected && isNight && ST_AC_IsNearShelter(config) && config.ShelterNightInfectedMessages && config.ShelterNightInfectedMessages.Count() > 0)
                return config.ShelterNightInfectedMessages.GetRandomElement();
        }

        if (state.HasHunger && state.HasThirst && config.StarvingDehydratedMessages && config.StarvingDehydratedMessages.Count() > 0)
            return config.StarvingDehydratedMessages.GetRandomElement();

        if (state.HasCold && state.HasWeather && isNight && config.ColdWetNightMessages && config.ColdWetNightMessages.Count() > 0)
            return config.ColdWetNightMessages.GetRandomElement();

        if (state.HasBleeding && state.HasBlood && config.BleedingLowBloodMessages && config.BleedingLowBloodMessages.Count() > 0)
            return config.BleedingLowBloodMessages.GetRandomElement();

        if (state.HasBleeding && state.HasRecentGunshot && config.GunshotBleedingMessages && config.GunshotBleedingMessages.Count() > 0)
            return config.GunshotBleedingMessages.GetRandomElement();

        if (state.HasBrokenLeg && state.HasInfected && config.BrokenLegInfectedMessages && config.BrokenLegInfectedMessages.Count() > 0)
            return config.BrokenLegInfectedMessages.GetRandomElement();

        if (state.HasBrokenLeg && isNight && config.BrokenLegNightMessages && config.BrokenLegNightMessages.Count() > 0)
            return config.BrokenLegNightMessages.GetRandomElement();

        if (state.HasBlood && state.HasCorpse && config.LowBloodCorpseMessages && config.LowBloodCorpseMessages.Count() > 0)
            return config.LowBloodCorpseMessages.GetRandomElement();

        if (state.HasSick && state.HasContamination && config.SickContaminatedMessages && config.SickContaminatedMessages.Count() > 0)
            return config.SickContaminatedMessages.GetRandomElement();

        if (isNight && state.HasWeather && config.NightRainMessages && config.NightRainMessages.Count() > 0)
            return config.NightRainMessages.GetRandomElement();

        if (isMilitary && state.HasRecentGunshot && config.MilitaryGunshotMessages && config.MilitaryGunshotMessages.Count() > 0)
            return config.MilitaryGunshotMessages.GetRandomElement();

        if (isMilitary && state.HasCorpse && config.MilitaryCorpseMessages && config.MilitaryCorpseMessages.Count() > 0)
            return config.MilitaryCorpseMessages.GetRandomElement();

        if (lowSanity && isNight && config.LowSanityNightMessages && config.LowSanityNightMessages.Count() > 0)
            return config.LowSanityNightMessages.GetRandomElement();

        if (lowSanity && state.HasCorpse && config.LowSanityCorpseMessages && config.LowSanityCorpseMessages.Count() > 0)
            return config.LowSanityCorpseMessages.GetRandomElement();

        return "";
    }
}
