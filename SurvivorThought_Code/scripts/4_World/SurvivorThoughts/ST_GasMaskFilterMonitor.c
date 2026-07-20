// Survivor Thoughts - periodic gas-mask filter condition monitor.
// Uses vanilla attachment slots and only emits when a filter crosses into a worse health level.

class ST_GasMaskFilterMonitor
{
    protected static ref ST_GasMaskFilterMonitor s_Instance;
    protected ref map<string, int> m_LastLevel;
    protected bool m_Started;

    static ST_GasMaskFilterMonitor Get()
    {
        if (!s_Instance)
            s_Instance = new ST_GasMaskFilterMonitor();
        return s_Instance;
    }

    void ST_GasMaskFilterMonitor()
    {
        m_LastLevel = new map<string, int>;
    }

    void Start()
    {
        if (m_Started || !GetGame() || !GetGame().IsServer())
            return;
        m_Started = true;
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(ST_Tick, 15000, true);
    }

    protected void ST_Tick()
    {
        array<Man> players = new array<Man>;
        GetGame().GetPlayers(players);

        foreach (Man man : players)
        {
            PlayerBase player = PlayerBase.Cast(man);
            if (!player || !player.IsAlive() || !player.GetIdentity())
                continue;

            int maskSlot = InventorySlots.GetSlotIdFromString("Mask");
            EntityAI mask = player.GetInventory().FindAttachment(maskSlot);
            if (!mask)
                continue;

            int filterSlot = InventorySlots.GetSlotIdFromString("GasMaskFilter");
            EntityAI filter = mask.GetInventory().FindAttachment(filterSlot);
            if (!filter)
                continue;

            int level = filter.GetHealthLevel();
            string key = player.GetIdentity().GetPlainId();

            if (!m_LastLevel.Contains(key))
            {
                m_LastLevel.Set(key, level);
                continue;
            }

            int previous = m_LastLevel.Get(key);
            m_LastLevel.Set(key, level);

            if (level > previous && level >= 2)
                ST_TriggerMessageRouter.Get().Send(player, "GasMaskFilterMessages", "ITEM_CONDITION", 120.0);
        }
    }
}
