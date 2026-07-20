class SurvivorJournal : ItemBase
{
    protected string m_ST_OwnerSteamId;
    protected string m_ST_OwnerName;
    protected string m_ST_JournalId;
    protected bool m_ST_OwnerDead;
    protected int m_ST_CreatedTimestamp;
    protected int m_ST_DeathTimestamp;

    void SurvivorJournal()
    {
        // Only bool net sync is used here for broad DayZ branch compatibility.
        // Owner/name/journal-id are persisted server-side through OnStoreSave/OnStoreLoad
        // and read through server-side journal actions, so string net-sync is not required.
        RegisterNetSyncVariableBool("m_ST_OwnerDead");
    }

    void ST_SetJournalOwner(string steamId, string ownerName)
    {
        m_ST_OwnerSteamId = steamId;
        m_ST_OwnerName = ownerName;

        if (m_ST_JournalId == "")
            m_ST_JournalId = steamId + "_" + GetGame().GetTime().ToString();

        if (m_ST_CreatedTimestamp <= 0 && GetGame())
            m_ST_CreatedTimestamp = GetGame().GetTime();

        SetSynchDirty();
    }

    void ST_SetJournalId(string journalId)
    {
        m_ST_JournalId = journalId;
        SetSynchDirty();
    }

    string ST_GetJournalOwnerId()
    {
        return m_ST_OwnerSteamId;
    }

    string ST_GetJournalOwnerName()
    {
        return m_ST_OwnerName;
    }

    string ST_GetJournalId()
    {
        return m_ST_JournalId;
    }

    bool ST_IsOwnerDead()
    {
        return m_ST_OwnerDead;
    }

    void ST_SetOwnerDead(bool state)
    {
        m_ST_OwnerDead = state;

        if (state && m_ST_DeathTimestamp <= 0 && GetGame())
            m_ST_DeathTimestamp = GetGame().GetTime();

        SetSynchDirty();
    }

    void ST_OnCarrierKilled(PlayerBase carrier, Object killer)
    {
        ST_SetOwnerDead(true);

        if (carrier)
        {
            if (m_ST_OwnerSteamId == "" && carrier.GetIdentity())
                m_ST_OwnerSteamId = carrier.GetIdentity().GetPlainId();

            if (m_ST_OwnerName == "")
                m_ST_OwnerName = carrier.ST_GetJournalCharacterName();

            if (m_ST_OwnerName == "" && carrier.GetIdentity())
                m_ST_OwnerName = carrier.GetIdentity().GetName();
        }

        SetSynchDirty();
    }

    override bool CanPutInCargo(EntityAI parent)
    {
        if (!m_ST_OwnerDead)
            return false;

        return super.CanPutInCargo(parent);
    }

    override bool CanPutIntoHands(EntityAI parent)
    {
        if (!m_ST_OwnerDead)
            return false;

        return super.CanPutIntoHands(parent);
    }


    override void EEItemLocationChanged(notnull InventoryLocation oldLoc, notnull InventoryLocation newLoc)
    {
        super.EEItemLocationChanged(oldLoc, newLoc);

        if (!GetGame() || !GetGame().IsServer())
            return;

        if (m_ST_OwnerDead)
            return;

        ST_SurvivorThoughtsConfig config = SurvivorThoughtsManager.Get().GetConfig();

        if (!config || config.DeleteJournalIfRemovedWhileAlive != 1)
            return;

        EntityAI parent = newLoc.GetParent();

        if (!parent || !parent.IsMan())
        {
            SurvivorThoughtsManager.Get().DebugLog("Deleting Survivor Journal moved away from living owner.");
            Delete();
        }
    }

    override void OnStoreSave(ParamsWriteContext ctx)
    {
        super.OnStoreSave(ctx);
        ctx.Write(m_ST_OwnerSteamId);
        ctx.Write(m_ST_OwnerName);
        ctx.Write(m_ST_JournalId);
        ctx.Write(m_ST_OwnerDead);
        ctx.Write(m_ST_CreatedTimestamp);
        ctx.Write(m_ST_DeathTimestamp);
    }

    override bool OnStoreLoad(ParamsReadContext ctx, int version)
    {
        if (!super.OnStoreLoad(ctx, version))
            return false;

        if (!ctx.Read(m_ST_OwnerSteamId))
            return false;

        if (!ctx.Read(m_ST_OwnerName))
            return false;

        if (!ctx.Read(m_ST_JournalId))
            m_ST_JournalId = "";

        if (!ctx.Read(m_ST_OwnerDead))
            m_ST_OwnerDead = false;

        if (!ctx.Read(m_ST_CreatedTimestamp))
            m_ST_CreatedTimestamp = 0;

        if (!ctx.Read(m_ST_DeathTimestamp))
            m_ST_DeathTimestamp = 0;

        return true;
    }

    override void SetActions()
    {
        super.SetActions();
        AddAction(ActionSTReadSurvivorJournal);
    }
}



class ActionSTReadSurvivorJournal : ActionSingleUseBase
{
    void ActionSTReadSurvivorJournal()
    {
        m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_OPENITEM;
        m_CommandUIDProne = DayZPlayerConstants.CMD_ACTIONFB_OPENITEM;
        m_Text = "Read survivor journal";
    }

    override void CreateConditionComponents()
    {
        m_ConditionItem = new CCINone;
        m_ConditionTarget = new CCTNone;
    }

    override bool HasTarget()
    {
        return false;
    }

    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
    {
        if (!player)
            return false;

        SurvivorJournal journal = SurvivorJournal.Cast(item);

        if (!journal)
            return false;

        return true;
    }

    override void OnExecuteServer(ActionData action_data)
    {
        if (!action_data || !action_data.m_Player)
            return;

        SurvivorJournal journal = SurvivorJournal.Cast(action_data.m_MainItem);

        if (!journal)
            journal = SurvivorJournal.Cast(action_data.m_Player.GetItemInHands());

        if (!journal)
            return;

        SurvivorThoughtsManager.Get().DebugLog("Held Survivor Journal read action executed.");
        SurvivorThoughtsManager.Get().ST_ReadSurvivorJournal(action_data.m_Player, journal);
    }
}


class ActionSTReadDeadSurvivorJournal : ActionSingleUseBase
{
    void ActionSTReadDeadSurvivorJournal()
    {
        m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_OPENITEM;
        m_CommandUIDProne = DayZPlayerConstants.CMD_ACTIONFB_OPENITEM;
        m_Text = "Read dead survivor journal";
    }

    override void CreateConditionComponents()
    {
        m_ConditionItem = new CCINone;
        m_ConditionTarget = new CCTMan(UAMaxDistances.DEFAULT);
    }

    override bool HasTarget()
    {
        return true;
    }

    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
    {
        if (!player || !target)
            return false;

        Object targetObject = target.GetObject();

        if (!targetObject)
            return false;

        PlayerBase deadPlayer = PlayerBase.Cast(targetObject);

        if (!deadPlayer)
        {
            EntityAI targetEntity = EntityAI.Cast(targetObject);

            if (targetEntity)
                deadPlayer = PlayerBase.Cast(targetEntity.GetHierarchyRootPlayer());
        }

        if (!deadPlayer || deadPlayer.IsAlive())
            return false;

        SurvivorJournal deadJournal = deadPlayer.ST_GetSurvivorJournal();

        if (!deadJournal)
            return false;

        return true;
    }

    override void OnExecuteServer(ActionData action_data)
    {
        if (!action_data || !action_data.m_Player || !action_data.m_Target)
            return;

        Object targetObject = action_data.m_Target.GetObject();

        if (!targetObject)
            return;

        PlayerBase deadPlayer = PlayerBase.Cast(targetObject);

        if (!deadPlayer)
        {
            EntityAI targetEntity = EntityAI.Cast(targetObject);

            if (targetEntity)
                deadPlayer = PlayerBase.Cast(targetEntity.GetHierarchyRootPlayer());
        }

        if (!deadPlayer || deadPlayer.IsAlive())
            return;

        SurvivorJournal deadJournal = deadPlayer.ST_GetSurvivorJournal();

        if (!deadJournal)
            return;

        SurvivorThoughtsManager.Get().DebugLog("Dead-player Survivor Journal read action executed.");
        SurvivorThoughtsManager.Get().ST_ReadSurvivorJournal(action_data.m_Player, deadJournal);
    }
}


modded class ActionConstructor
{
    override void RegisterActions(TTypenameArray actions)
    {
        super.RegisterActions(actions);
        actions.Insert(ActionSTReadSurvivorJournal);
        actions.Insert(ActionSTReadDeadSurvivorJournal);
    }
}
