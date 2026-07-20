// Survivor Thoughts - guarded optional administration/trader extension points.
// Version-specific adapters can call these without adding hard dependencies to the core mod.

#ifdef VPPADMINTOOLS
class ST_VPPAdminInterop
{
    static void OnAdminTeleported(PlayerBase player)
    {
        if (player)
            SurvivorThoughtsManager.Get().SendThoughtWithPriority(player, "[Admin] Position changed by an administrator.", "ADMIN");
    }
}
#endif

#ifdef COMMUNITY_FRAMEWORK
class ST_CFAdminInterop
{
    static void OnAdminEvent(PlayerBase player, string eventText)
    {
        if (player && eventText != "")
            SurvivorThoughtsManager.Get().SendThoughtWithPriority(player, "[Admin] " + eventText, "ADMIN");
    }
}
#endif

#ifdef TRADER
class ST_TraderInterop
{
    static void OnFirstTrade(PlayerBase player)
    {
        SurvivorThoughtsManager.Get().SendThoughtWithPriority(player, "A deal still means something in this world.", "ACTION");
    }

    static void OnLargeSale(PlayerBase player)
    {
        SurvivorThoughtsManager.Get().SendThoughtWithPriority(player, "That trade changed what I can afford to risk.", "ACTION");
    }

    static void OnBroke(PlayerBase player)
    {
        SurvivorThoughtsManager.Get().SendThoughtWithPriority(player, "Nothing left to spend. Back to surviving.", "PASSIVE");
    }
}
#endif
