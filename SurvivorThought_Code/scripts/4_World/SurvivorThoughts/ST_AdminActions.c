class ActionSTReloadConfigs : ActionInteractBase
{
    void ActionSTReloadConfigs()
    {
        m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
        m_StanceMask = DayZPlayerConstants.STANCEMASK_ALL;
        m_Text = "Reload Survivor Thoughts Configs";
    }

    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
    {
        if (!GetGame())
            return false;

        // Client-side action visibility cannot securely check server admin config.
        // Server-side execution below still enforces AdminSteamIds.
        if (!GetGame().IsServer())
            return true;

        return SurvivorThoughtsManager.Get().IsAdminAllowed(player);
    }

    override void OnExecuteServer(ActionData action_data)
    {
        PlayerBase player = PlayerBase.Cast(action_data.m_Player);

        if (!player)
            return;

        if (!SurvivorThoughtsManager.Get().IsAdminAllowed(player))
            return;

        SurvivorThoughtsManager.Get().ReloadConfigs(player);
    }
}


class ActionSTOpenAdminMenu : ActionInteractBase
{
    void ActionSTOpenAdminMenu()
    {
        m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
        m_StanceMask = DayZPlayerConstants.STANCEMASK_ALL;
        m_Text = "Open Survivor Thoughts Admin";
    }

    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
    {
        if (!GetGame())
            return false;

        if (!GetGame().IsServer())
            return true;

        return ST_AdminPriorityTriggerSystem.Get().IsAdminAllowed(player);
    }

    override void OnExecuteClient(ActionData action_data)
    {
        if (!GetGame() || !GetGame().GetUIManager())
            return;

        GetGame().GetUIManager().EnterScriptedMenu(827361, NULL);
    }
}

class ActionSTAdminHealthReport : ActionInteractBase
{
    void ActionSTAdminHealthReport()
    {
        m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
        m_StanceMask = DayZPlayerConstants.STANCEMASK_ALL;
        m_Text = "ST: Write Message Health Report";
    }

    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
    {
        if (!GetGame())
            return false;

        if (!GetGame().IsServer())
            return true;

        return ST_AdminPriorityTriggerSystem.Get().IsAdminAllowed(player);
    }

    override void OnExecuteServer(ActionData action_data)
    {
        PlayerBase player = PlayerBase.Cast(action_data.m_Player);

        if (!player)
            return;

        ST_AdminPriorityTriggerSystem.Get().HandleAdminCommand(player, "HEALTH");
    }
}

class ActionSTAdminTriggerCoverage : ActionInteractBase
{
    void ActionSTAdminTriggerCoverage()
    {
        m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
        m_StanceMask = DayZPlayerConstants.STANCEMASK_ALL;
        m_Text = "ST: Write Trigger Coverage Report";
    }

    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
    {
        if (!GetGame())
            return false;

        if (!GetGame().IsServer())
            return true;

        return ST_AdminPriorityTriggerSystem.Get().IsAdminAllowed(player);
    }

    override void OnExecuteServer(ActionData action_data)
    {
        PlayerBase player = PlayerBase.Cast(action_data.m_Player);

        if (!player)
            return;

        ST_AdminPriorityTriggerSystem.Get().HandleAdminCommand(player, "COVERAGE");
    }
}
