modded class MissionGameplay
{
    protected UAInput m_ST_AdminMenuInput;

    override void OnUpdate(float timeslice)
    {
        super.OnUpdate(timeslice);

        if (!GetGame())
            return;

        ST_UpdateAdminMenuKeybind();
    }

    protected void ST_UpdateAdminMenuKeybind()
    {
        if (!GetUApi() || !GetGame().GetUIManager())
            return;

        if (!m_ST_AdminMenuInput)
            m_ST_AdminMenuInput = GetUApi().GetInputByName("UA_ST_ToggleAdminMenu");

        if (!m_ST_AdminMenuInput || !m_ST_AdminMenuInput.LocalPress())
            return;

        UIScriptedMenu currentMenu = GetGame().GetUIManager().GetMenu();

        if (ST_AdminMenu.Cast(currentMenu))
        {
            GetGame().GetUIManager().Back();
            return;
        }

        if (currentMenu)
            return;

        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        if (!player || !player.GetIdentity())
            return;

        GetGame().GetUIManager().EnterScriptedMenu(827361, NULL);
    }

    override UIScriptedMenu CreateScriptedMenu(int id)
    {
        if (id == 827361)
            return new ST_AdminMenu();

        return super.CreateScriptedMenu(id);
    }
}
