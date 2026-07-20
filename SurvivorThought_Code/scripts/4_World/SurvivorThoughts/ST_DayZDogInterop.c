// Survivor Thoughts - optional DayZ-Dog integration.
// This file is intentionally guarded so Survivor Thoughts does not hard-require DayZ-Dog.
// To enable compile-time hooks, the DayZ-Dog package/server build must expose the DAYZDOG script define.

#ifdef DAYZDOG

static void ST_SendPetDogActionThought(ActionData action_data, string petEventType)
{
    if (!GetGame() || !GetGame().IsServer())
        return;

    if (!action_data)
        return;

    PlayerBase player = PlayerBase.Cast(action_data.m_Player);

    if (!player)
        return;

    SurvivorThoughtsManager.Get().SendPetDogThought(player, petEventType);
}

modded class ActionFeedDog
{
    override void OnExecuteServer(ActionData action_data)
    {
        super.OnExecuteServer(action_data);
        ST_SendPetDogActionThought(action_data, "DOG_FEED");
    }
}

modded class ActionTameDog
{
    override void OnExecuteServer(ActionData action_data)
    {
        super.OnExecuteServer(action_data);
        ST_SendPetDogActionThought(action_data, "DOG_TAME");
    }
}

modded class BBP_FollowMe
{
    override void OnExecuteServer(ActionData action_data)
    {
        super.OnExecuteServer(action_data);
        ST_SendPetDogActionThought(action_data, "DOG_FOLLOW");
    }
}

modded class BBP_StayHere
{
    override void OnExecuteServer(ActionData action_data)
    {
        super.OnExecuteServer(action_data);
        ST_SendPetDogActionThought(action_data, "DOG_STAY");
    }
}

modded class ActionBandageDog
{
    override void OnFinishProgressServer(ActionData action_data)
    {
        super.OnFinishProgressServer(action_data);
        ST_SendPetDogActionThought(action_data, "DOG_BANDAGE");
    }
}

modded class ActionSummonDog
{
    override void OnExecuteServer(ActionData action_data)
    {
        super.OnExecuteServer(action_data);
        ST_SendPetDogActionThought(action_data, "DOG_SUMMON");
    }
}

modded class ActionManageDog
{
    override void OnExecuteServer(ActionData action_data)
    {
        super.OnExecuteServer(action_data);
        ST_SendPetDogActionThought(action_data, "DOG_COMPANION");
    }
}

#endif
