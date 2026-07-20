// Survivor Thoughts - guarded DayZ Expansion integration extension points.
// Kept isolated so core servers do not compile against optional Expansion classes.
// The installed Expansion-version adapter should call these methods from its supported hooks.

#ifdef EXPANSIONMODVEHICLE
class ST_ExpansionVehicleInterop
{
    static void OnVehicleRepair(PlayerBase player)
    {
        ST_TriggerMessageRouter.Get().Send(player, "VehicleMessages", "ACTION", 60.0);
    }

    static void OnVehicleRefuel(PlayerBase player)
    {
        ST_TriggerMessageRouter.Get().Send(player, "VehicleMessages", "ACTION", 60.0);
    }

    static void OnVehicleCrash(PlayerBase player)
    {
        ST_TriggerMessageRouter.Get().Send(player, "VehicleMessages", "COMBAT_HIT", 30.0);
    }
}
#endif

#ifdef EXPANSIONMODBASEBUILDING
class ST_ExpansionBaseRaidInterop
{
    static void OnOwnedBasePartDamaged(PlayerBase owner)
    {
        ST_TriggerMessageRouter.Get().Send(owner, "BaseRaidMessages", "SOCIAL_GROUP", 120.0);
        if (owner)
            ST_SurvivorStorySystem.Get().AddMajorEvent(owner, "[BASE RAID] Something is attacking the walls I trusted.");
    }
}
#endif
