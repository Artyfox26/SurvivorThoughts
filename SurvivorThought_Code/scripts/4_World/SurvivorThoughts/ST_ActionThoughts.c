// Survivor Thoughts - action-triggered internal dialogue hooks.
// v0.2.9: Expanded ActionConstructor coverage.
// Generated from the supplied vanilla ActionConstructor.c list.
// These hooks use OnStartServer so thoughts fire when actions begin.
// Weapon unjamming remains hooked through WeaponManager.Unjam() because it is weapon-manager driven.

static bool ST_IsFoodContainerOpenAction(ActionData action_data)
{
    if (!action_data)
        return false;

    EntityAI candidate = action_data.m_MainItem;

    if (!candidate && action_data.m_Target)
        candidate = EntityAI.Cast(action_data.m_Target.GetObject());

    if (!candidate)
        return false;

    string typeName = candidate.GetType();

    // ActionOpen is shared by doors and openable inventory items. Route known
    // food containers away from environmental door thoughts.
    if (typeName.Contains("Food"))
        return true;

    if (typeName.Contains("Can"))
        return true;

    if (typeName.Contains("Sardines"))
        return true;

    if (typeName.Contains("Tuna"))
        return true;

    if (typeName.Contains("Peaches"))
        return true;

    if (typeName.Contains("Spaghetti"))
        return true;

    if (typeName.Contains("BakedBeans"))
        return true;

    if (typeName.Contains("TacticalBacon"))
        return true;

    if (typeName.Contains("UnknownFood"))
        return true;

    if (typeName.Contains("Lunchmeat"))
        return true;

    if (typeName.Contains("Pajka"))
        return true;

    if (typeName.Contains("Pate"))
        return true;

    if (typeName.Contains("Brisket"))
        return true;

    if (typeName.Contains("Ham"))
        return true;

    return false;
}

static string ST_GetActionItemDisplayName(ActionData action_data)
{
    if (!action_data)
        return "";

    EntityAI item = action_data.m_MainItem;

    if (!item && action_data.m_Target)
        item = EntityAI.Cast(action_data.m_Target.GetObject());

    if (!item)
        return "";

    string displayName = item.GetDisplayName();

    if (displayName == "")
        displayName = item.GetType();

    return displayName;
}

static void ST_SendActionStartThought(ActionData action_data, string action_type)
{
    if (!GetGame() || !GetGame().IsServer())
        return;

    if (!action_data)
        return;

    PlayerBase player = PlayerBase.Cast(action_data.m_Player);
    if (!player)
        return;

    ST_SurvivorThoughtsConfig config = SurvivorThoughtsManager.Get().GetConfig();

    string finalActionType = action_type;

    if (action_type == "SKIN_ANIMAL" && action_data.m_Target)
    {
        Object targetObject = action_data.m_Target.GetObject();

        if (targetObject)
        {
            string targetType = targetObject.GetType();

            if (targetObject.IsInherited(PlayerBase) || targetType.Contains("Survivor") || targetType.Contains("Player"))
                finalActionType = "SKIN_HUMAN";
        }
    }

    if (action_type == "EAT" && action_data.m_MainItem)
    {
        string itemType = action_data.m_MainItem.GetType();

        if (itemType.Contains("Human") && itemType.Contains("Meat"))
            finalActionType = "EAT_HUMAN";
    }

    if (finalActionType == "SKIN_HUMAN" && config)
        player.ST_AddSanityStress("SKIN_HUMAN", config.SanityLossSkinHuman);

    if (finalActionType == "EAT_HUMAN" && config)
        player.ST_AddSanityStress("EAT_HUMAN", config.SanityLossEatHumanMeat);

    if (finalActionType == "OPEN_FOOD" || finalActionType == "EAT" || finalActionType == "EAT_HUMAN" || finalActionType == "DRINK" || finalActionType == "DRINK_UNSAFE")
    {
        string actionItemName = ST_GetActionItemDisplayName(action_data);

        if (actionItemName != "")
            SurvivorThoughtsManager.Get().SendNamedActionThought(player, finalActionType, actionItemName);
        else
            SurvivorThoughtsManager.Get().SendActionThought(player, finalActionType);
    }
    else
    {
        SurvivorThoughtsManager.Get().SendActionThought(player, finalActionType);
    }
}

// ------------------------------------------------------------
// AMMO_MANAGEMENT action hooks.
// ------------------------------------------------------------

modded class ActionLoadMagazine
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "AMMO_MANAGEMENT");
    }
}

modded class ActionLoadMagazineQuick
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "AMMO_MANAGEMENT");
    }
}

// ------------------------------------------------------------
// BASE_BUILDING action hooks.
// ------------------------------------------------------------

modded class ActionAttachToConstruction
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "BASE_BUILDING");
    }
}

modded class ActionBuildPart
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "BASE_BUILDING");
    }
}

modded class ActionActionBuildPartNoTool
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "BASE_BUILDING");
    }
}

modded class ActionDismantlePart
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "BASE_BUILDING");
    }
}

modded class ActionDestroyPart
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "BASE_BUILDING");
    }
}

modded class ActionMountBarbedWire
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "BASE_BUILDING");
    }
}

modded class ActionUnmountBarbedWire
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "BASE_BUILDING");
    }
}

modded class ActionRaiseFlag
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "BASE_BUILDING");
    }
}

modded class ActionLowerFlag
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "BASE_BUILDING");
    }
}

modded class ActionDeconstructShelter
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "BASE_BUILDING");
    }
}

modded class ActionBuildShelter
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "BASE_BUILDING");
    }
}

// ------------------------------------------------------------
// BLOOD_MEDICAL action hooks.
// ------------------------------------------------------------

modded class ActionTestBloodSelf
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "BLOOD_MEDICAL");
    }

    override void OnExecuteServer(ActionData action_data)
    {
        super.OnExecuteServer(action_data);
        if (action_data && action_data.m_Player)
            ST_TriggerMessageRouter.Get().Send(action_data.m_Player, "BloodDiscoveryMessages", "MEDICAL", 30.0);
    }
}

modded class ActionTestBloodTarget
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "BLOOD_MEDICAL");
    }

    override void OnExecuteServer(ActionData action_data)
    {
        super.OnExecuteServer(action_data);
        if (action_data && action_data.m_Player)
            ST_TriggerMessageRouter.Get().Send(action_data.m_Player, "BloodDiscoveryMessages", "MEDICAL", 30.0);
    }
}

modded class ActionGiveBloodSelf
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "BLOOD_MEDICAL");
    }
}

modded class ActionGiveBloodTarget
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "BLOOD_MEDICAL");
    }
}

modded class ActionGiveSalineSelf
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "BLOOD_MEDICAL");
    }
}

modded class ActionGiveSalineTarget
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "BLOOD_MEDICAL");
    }
}

modded class ActionCollectBloodSelf
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "BLOOD_MEDICAL");
    }
}

modded class ActionCollectBloodTarget
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "BLOOD_MEDICAL");
    }
}

modded class ActionCollectSampleSelf
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "BLOOD_MEDICAL");
    }
}

modded class ActionCollectSampleTarget
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "BLOOD_MEDICAL");
    }
}

// ------------------------------------------------------------
// BURY_STASH action hooks.
// ------------------------------------------------------------

modded class ActionBuryAshes
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "BURY_STASH");
    }
}

modded class ActionBuryBody
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "BURY_STASH");
    }
}

modded class ActionDigInStash
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "BURY_STASH");
    }
}

modded class ActionDigOutStash
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "BURY_STASH");
    }
}

// ------------------------------------------------------------
// COOK action hooks.
// ------------------------------------------------------------

modded class ActionCookOnStick
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "COOK");
    }
}

modded class ActionEmptyCookingPot
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "COOK");
    }
}

// ------------------------------------------------------------
// CRAFTING action hooks.
// ------------------------------------------------------------

modded class ActionWorldCraft
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "CRAFTING");
    }
}

modded class ActionCraftImprovisedHandsCover
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "CRAFTING");
    }
}

modded class ActionCraftImprovisedHeadCover
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "CRAFTING");
    }
}

modded class ActionCraftImprovisedFeetCover
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "CRAFTING");
    }
}

modded class ActionCraftImprovisedFaceCover
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "CRAFTING");
    }
}

modded class ActionCraftImprovisedTorsoCover
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "CRAFTING");
    }
}

modded class ActionCraftImprovisedLegsCover
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "CRAFTING");
    }
}

modded class ActionCraftImprovisedEyePatch
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "CRAFTING");
    }
}

modded class ActionCraftRopeBelt
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "CRAFTING");
    }
}

modded class ActionDeCraftRopeBelt
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "CRAFTING");
    }
}

modded class ActionCraftBoneKnife
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "CRAFTING");
    }
}

modded class ActionCraftArmband
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "CRAFTING");
    }
}

modded class ActionCraftBoneKnifeEnv
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "CRAFTING");
    }
}

modded class ActionCraftStoneKnifeEnv
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "CRAFTING");
    }
}

modded class ActionCraftBolts
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "CRAFTING");
    }
}

modded class ActionCraftBoltsFeather
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "CRAFTING");
    }
}

modded class ActionDeCraftWitchHoodCoif
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "CRAFTING");
    }
}

modded class ActionDeCraftDrysackBag
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "CRAFTING");
    }
}

// ------------------------------------------------------------
// DEPLOY action hooks.
// ------------------------------------------------------------

modded class ActionTogglePlaceObject
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "DEPLOY");
    }
}

modded class ActionTogglePlaceObjectDigging
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "DEPLOY");
    }
}

modded class ActionPlaceOvenIndoor
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "DEPLOY");
    }
}

modded class ActionPlaceObject
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "DEPLOY");
    }
}

modded class ActionDeployObject
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "DEPLOY");
    }
}

modded class ActionDeployHuntingTrap
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "DEPLOY");
    }
}

modded class ActionUnpackBox
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "DEPLOY");
    }
}

modded class ActionFoldBaseBuildingObject
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "DEPLOY");
    }
}

modded class ActionUnpackGift
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "DEPLOY");
    }
}

modded class ActionPackGift
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "DEPLOY");
    }
}

modded class ActionFoldObject
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "DEPLOY");
    }
}

// ------------------------------------------------------------
// DISINFECT action hooks.
// ------------------------------------------------------------

modded class ActionDisinfectSelf
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "DISINFECT");
    }
}

modded class ActionDisinfectTarget
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "DISINFECT");
    }
}

modded class ActionDisinfectPlantBit
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "DISINFECT");
    }
}

modded class ActionDisinfectPlant
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "DISINFECT");
    }
}

// ------------------------------------------------------------
// DRINK action hooks.
// ------------------------------------------------------------

modded class ActionDrink
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "DRINK");
    }
}

modded class ActionDrinkCookingPot
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "DRINK");
    }
}

modded class ActionDrinkWellContinuous
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "DRINK");
    }
}

modded class ActionDrinkCan
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "DRINK");
    }
}

// ------------------------------------------------------------
// DRINK_UNSAFE action hooks.
// ------------------------------------------------------------

modded class ActionForceDrink
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "DRINK_UNSAFE");
    }
}

modded class ActionFillBottleSnow
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "DRINK_UNSAFE");
    }
}

modded class ActionDrinkPondContinuous
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "DRINK_UNSAFE");
    }
}

modded class ActionEatSnowContinuous
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "DRINK_UNSAFE");
    }
}

modded class ActionDrinkThroughContinuous
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "DRINK_UNSAFE");
    }
}

// ------------------------------------------------------------
// EAT action hooks.
// ------------------------------------------------------------

modded class ActionConsumeSingle
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "EAT");
    }
}

modded class ActionForceConsumeSingle
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "EAT");
    }
}

modded class ActionForceFeed
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "EAT");
    }
}

modded class ActionForceFeedSmall
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "EAT");
    }
}

modded class ActionEatBig
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "EAT");
    }
}

modded class ActionEatMeat
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "EAT");
    }
}

modded class ActionEatFruit
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "EAT");
    }
}

modded class ActionEatCan
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "EAT");
    }
}

modded class ActionEatSmallCan
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "EAT");
    }
}

modded class ActionForceFeedCan
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "EAT");
    }
}

modded class ActionEat
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "EAT");
    }
}

modded class ActionEatSmall
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "EAT");
    }
}

modded class ActionEatCereal
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "EAT");
    }
}

// ------------------------------------------------------------
// ELECTRONICS action hooks.
// ------------------------------------------------------------

modded class ActionPlugIn
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "ELECTRONICS");
    }
}

modded class ActionTurnOnWhileInHands
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "ELECTRONICS");
    }
}

modded class ActionTurnOffWhileInHands
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "ELECTRONICS");
    }
}

modded class ActionTurnOnHeatpack
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "ELECTRONICS");
    }
}

modded class ActionTurnOnTransmitter
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "ELECTRONICS");
    }
}

modded class ActionTurnOffTransmitter
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "ELECTRONICS");
    }
}

modded class ActionPlugTargetIntoThis
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "ELECTRONICS");
    }
}

modded class ActionTurnOnWeaponFlashlight
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "ELECTRONICS");
    }
}

modded class ActionTurnOffWeaponFlashlight
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "ELECTRONICS");
    }
}

modded class ActionTurnOnHeadtorch
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "ELECTRONICS");
    }
}

modded class ActionTurnOffHeadtorch
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "ELECTRONICS");
    }
}

modded class ActionTurnOnHelmetFlashlight
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "ELECTRONICS");
    }
}

modded class ActionTurnOffHelmetFlashlight
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "ELECTRONICS");
    }
}

modded class ActionToggleNVG
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "ELECTRONICS");
    }
}

modded class ActionTuneFrequency
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "ELECTRONICS");
    }
}

modded class ActionTuneRadioStation
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "ELECTRONICS");
    }
}

modded class ActionRaiseMegaphone
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "ELECTRONICS");
    }
}

modded class ActionToggleNVMode
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "ELECTRONICS");
    }
}

modded class ActionPullOutPlug
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "ELECTRONICS");
    }
}

modded class ActionUnplugThisByCord
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "ELECTRONICS");
    }
}

modded class ActionTurnOnWhileOnGround
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "ELECTRONICS");
    }
}

modded class ActionTurnOffWhileOnGround
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "ELECTRONICS");
    }
}

modded class ActionTurnOnPowerGenerator
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "ELECTRONICS");
    }
}

modded class ActionTurnOffPowerGenerator
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "ELECTRONICS");
    }
}

modded class ActionTurnOnSpotlight
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "ELECTRONICS");
    }
}

modded class ActionTurnOffSpotlight
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "ELECTRONICS");
    }
}

modded class ActionRepositionPluggedItem
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "ELECTRONICS");
    }
}

modded class ActionTurnOnTransmitterOnGround
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "ELECTRONICS");
    }
}

modded class ActionTurnOffTransmitterOnGround
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "ELECTRONICS");
    }
}

modded class ActionTuneFrequencyOnGround
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "ELECTRONICS");
    }
}

modded class ActionDetachPowerSourceFromPanel
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "ELECTRONICS");
    }
}

modded class ActionOperatePanelPowerStation
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "ELECTRONICS");
    }
}

modded class ActionSwitchLights
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "ELECTRONICS");
    }
}

modded class ActionSetAlarmClock
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "ELECTRONICS");
    }
}

modded class ActionTurnOnAlarmClock
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "ELECTRONICS");
    }
}

modded class ActionTurnOffAlarmClock
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "ELECTRONICS");
    }
}

modded class ActionSetKitchenTimer
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "ELECTRONICS");
    }
}

modded class ActionResetKitchenTimer
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "ELECTRONICS");
    }
}

modded class ActionUseUndergroundPanel
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "ELECTRONICS");
    }
}

// ------------------------------------------------------------
// FIREPLACE action hooks.
// ------------------------------------------------------------

modded class ActionPlaceFireplaceIndoor
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "FIREPLACE");
    }
}

modded class ActionPlaceFireplaceIntoBarrel
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "FIREPLACE");
    }
}

modded class ActionUpgradeTorchFromGasPump
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "FIREPLACE");
    }
}

modded class ActionRefuelTorch
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "FIREPLACE");
    }
}

modded class ActionExtinguishFireplaceByLiquid
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "FIREPLACE");
    }
}

modded class ActionExtinguishFireplaceByExtinguisher
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "FIREPLACE");
    }
}

modded class ActionBuildOven
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "FIREPLACE");
    }
}

modded class ActionDismantleOven
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "FIREPLACE");
    }
}

modded class ActionBuildStoneCircle
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "FIREPLACE");
    }
}

modded class ActionDismantleStoneCircle
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "FIREPLACE");
    }
}

// ------------------------------------------------------------
// FIRE_START action hooks.
// ------------------------------------------------------------

modded class ActionCreateIndoorFireplace
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "FIRE_START");
    }
}

modded class ActionIgniteFireplaceByAir
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "FIRE_START");
    }
}

modded class ActionLightItemOnFire
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "FIRE_START");
    }
}

modded class ActionLightItemOnFireWithBlowtorch
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "FIRE_START");
    }
}

// ------------------------------------------------------------
// FISH action hooks.
// ------------------------------------------------------------

modded class ActionFishingNew
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "FISH");
    }
}

// ------------------------------------------------------------
// GARDENING action hooks.
// ------------------------------------------------------------

modded class ActionPlantSeed
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "GARDENING");
    }
}

modded class ActionAttachSeeds
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "GARDENING");
    }
}

modded class ActionCreateGreenhouseGardenPlot
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "GARDENING");
    }
}

modded class ActionEmptySeedsPack
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "GARDENING");
    }
}

modded class ActionDigGardenPlot
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "GARDENING");
    }
}

modded class ActionDismantleGardenPlot
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "GARDENING");
    }
}

modded class ActionWaterPlant
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "GARDENING");
    }
}

modded class ActionFertilizeSlot
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "GARDENING");
    }
}

modded class ActionWaterGardenSlot
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "GARDENING");
    }
}

modded class ActionRemoveSeed
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "GARDENING");
    }
}

modded class ActionRemovePlant
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "GARDENING");
    }
}

modded class ActionHarvestCrops
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "GARDENING");
    }
}

// ------------------------------------------------------------
// GENERAL_ACTION action hooks.
// ------------------------------------------------------------

modded class ActionCreateIndoorOven
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "GENERAL_ACTION");
    }
}

modded class ActionPackTent
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "GENERAL_ACTION");
    }
}

modded class ActionSidePlateInteract
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "GENERAL_ACTION");
    }
}

// ------------------------------------------------------------
// INJECTION action hooks.
// ------------------------------------------------------------

modded class ActionInjectSelf
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "INJECTION");
    }
}

modded class ActionInjectTarget
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "INJECTION");
    }
}

modded class ActionInjectEpinephrineSelf
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "INJECTION");
    }
}

modded class ActionInjectEpinephrineTarget
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "INJECTION");
    }
}

modded class ActionInjectMorphineSelf
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "INJECTION");
    }
}

modded class ActionInjectMorphineTarget
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "INJECTION");
    }
}

modded class ActionDefibrilateSelf
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "INJECTION");
    }
}

modded class ActionDefibrilateTarget
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "INJECTION");
    }
}

// ------------------------------------------------------------
// INVENTORY_MANAGEMENT action hooks.
// ------------------------------------------------------------

modded class ActionAttach
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "INVENTORY_MANAGEMENT");
    }
}

modded class ActionAttachOnProxy
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "INVENTORY_MANAGEMENT");
    }
}

modded class ActionAttachOnSelection
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "INVENTORY_MANAGEMENT");
    }
}

modded class ActionDropItem
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "INVENTORY_MANAGEMENT");
    }
}

modded class ActionDropItemSimple
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "INVENTORY_MANAGEMENT");
    }
}

modded class ActionAttachOnTentProxy
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "INVENTORY_MANAGEMENT");
    }
}

modded class ActionTakeItem
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "INVENTORY_MANAGEMENT");
    }
}

modded class ActionSwapItemToHands
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "INVENTORY_MANAGEMENT");
    }
}

modded class ActionTakeItemToHands
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "INVENTORY_MANAGEMENT");
    }
}

modded class ActionDetach
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "INVENTORY_MANAGEMENT");
    }
}

modded class ActionDetachFromTarget
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "INVENTORY_MANAGEMENT");
    }
}

modded class ActionDetachFromTarget_SpecificSlot_WoodenLogs
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "INVENTORY_MANAGEMENT");
    }
}

modded class ActionDetachFromTarget_SpecificSlot_WoodenPlanks
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "INVENTORY_MANAGEMENT");
    }
}

modded class ActionDetachFromTarget_SpecificSlot_MetalSheets
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "INVENTORY_MANAGEMENT");
    }
}

modded class ActionDetachFromTarget_SpecificSlotsCategory_WoodenCrate
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "INVENTORY_MANAGEMENT");
    }
}

modded class ActionTakeArrow
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "INVENTORY_MANAGEMENT");
    }
}

modded class ActionTakeArrowToHands
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "INVENTORY_MANAGEMENT");
    }
}

modded class ActionAttachWithSwitch
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "INVENTORY_MANAGEMENT");
    }
}

// ------------------------------------------------------------
// LIQUID_TRANSFER action hooks.
// ------------------------------------------------------------

modded class ActionFillObject
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "LIQUID_TRANSFER");
    }
}

modded class ActionFillBottleBase
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "LIQUID_TRANSFER");
    }
}

modded class ActionEmptyMagazine
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "LIQUID_TRANSFER");
    }
}

modded class ActionDrainLiquid
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "LIQUID_TRANSFER");
    }
}

modded class ActionPourLiquid
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "LIQUID_TRANSFER");
    }
}

modded class ActionEmptyBottleBase
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "LIQUID_TRANSFER");
    }
}

modded class ActionTurnValve
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "LIQUID_TRANSFER");
    }
}

modded class ActionTurnValveUndergroundReservoir
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "LIQUID_TRANSFER");
    }
}

// ------------------------------------------------------------
// LOCK action hooks.
// ------------------------------------------------------------

modded class ActionNextCombinationLockDial
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "LOCK");
    }
}

modded class ActionLockDoors
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "LOCK");
    }
}

modded class ActionUnlockDoors
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "LOCK");
    }
}

modded class ActionDialCombinationLock
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "LOCK");
    }
}

modded class ActionDialCombinationLockOnTarget
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "LOCK");
    }
}

modded class ActionLockAttachment
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "LOCK");
    }
}

modded class ActionUnlockShippingContainer
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "LOCK");
    }
}

modded class ActionLockedDoors
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "LOCK");
    }
}

modded class ActionNextCombinationLockDialOnTarget
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "LOCK");
    }
}

// ------------------------------------------------------------
// MEDICINE_CONSUME action hooks.
// ------------------------------------------------------------

modded class ActionEatPillFromBottle
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "MEDICINE_CONSUME");
    }
}

modded class ActionEatTabletFromWrapper
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "MEDICINE_CONSUME");
    }
}

// ------------------------------------------------------------
// MOVEMENT action hooks.
// ------------------------------------------------------------

modded class ActionEnterLadder
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "MOVEMENT");
    }
}

modded class ActionExitLadder
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "MOVEMENT");
    }
}

// ------------------------------------------------------------
// NAVIGATION action hooks.
// ------------------------------------------------------------

modded class ActionUnfoldMap
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "NAVIGATION");
    }
}

modded class ActionFoldMap
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "NAVIGATION");
    }
}

modded class ActionViewOptics
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "NAVIGATION");
    }
}

modded class ActionViewBinoculars
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "NAVIGATION");
    }
}

// ------------------------------------------------------------
// OPEN_CLOSE action hooks.
// ------------------------------------------------------------

modded class ActionOpen
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);

        if (ST_IsFoodContainerOpenAction(action_data))
            ST_SendActionStartThought(action_data, "OPEN_FOOD");
        else
            ST_SendActionStartThought(action_data, "OPEN_CLOSE");
    }
}

modded class ActionClose
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "OPEN_CLOSE");
    }
}

modded class ActionToggleTentOpen
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "OPEN_CLOSE");
    }
}

modded class ActionOpenBarrel
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "OPEN_CLOSE");
    }
}

modded class ActionCloseBarrel
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "OPEN_CLOSE");
    }
}

modded class ActionOpenBarrelHoles
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "OPEN_CLOSE");
    }
}

modded class ActionCloseBarrelHoles
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "OPEN_CLOSE");
    }
}

modded class ActionOpenDoors
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "OPEN_CLOSE");
    }
}

modded class ActionCloseDoors
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "OPEN_CLOSE");
    }
}

modded class ActionOpenFence
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "OPEN_CLOSE");
    }
}

modded class ActionCloseFence
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "OPEN_CLOSE");
    }
}

modded class ActionDetachFromTarget_SpecificSlotsCategory_Barrel
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "OPEN_CLOSE");
    }
}

// ------------------------------------------------------------
// PERSONAL_CARE action hooks.
// ------------------------------------------------------------

modded class ActionMeasureTemperatureSelf
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "PERSONAL_CARE");
    }
}

modded class ActionMeasureTemperatureTarget
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "PERSONAL_CARE");
    }
}

modded class ActionWashHandsItemContinuous
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "PERSONAL_CARE");
        if (action_data && action_data.m_Player)
            ST_TriggerMessageRouter.Get().Send(action_data.m_Player, "HandsHygieneMessages", "ACTION", 45.0);
    }
}

modded class ActionShave
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "PERSONAL_CARE");
    }
}

modded class ActionWringClothes
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "PERSONAL_CARE");
    }
}

modded class ActionShaveTarget
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "PERSONAL_CARE");
    }
}

modded class ActionWashHandsWater
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "PERSONAL_CARE");
        if (action_data && action_data.m_Player)
            ST_TriggerMessageRouter.Get().Send(action_data.m_Player, "HandsHygieneMessages", "ACTION", 45.0);
    }
}

modded class ActionWashHandsSnow
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "PERSONAL_CARE");
        if (action_data && action_data.m_Player)
            ST_TriggerMessageRouter.Get().Send(action_data.m_Player, "HandsHygieneMessages", "ACTION", 45.0);
    }
}

modded class ActionWashHandsWell
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "PERSONAL_CARE");
        if (action_data && action_data.m_Player)
            ST_TriggerMessageRouter.Get().Send(action_data.m_Player, "HandsHygieneMessages", "ACTION", 45.0);
    }
}

modded class ActionCheckPulseTarget
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "PERSONAL_CARE");
    }
}

// ------------------------------------------------------------
// REPAIR action hooks.
// ------------------------------------------------------------

modded class ActionRepairTent
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "REPAIR");
    }
}

modded class ActionRepairTentPart
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "REPAIR");
    }
}

modded class ActionRepairPart
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "REPAIR");
    }
}

modded class ActionRepairCarPart
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "REPAIR");
    }
}

modded class ActionRepairCarPartWithBlowtorch
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "REPAIR");
    }
}

modded class ActionRepairCarChassis
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "REPAIR");
    }
}

modded class ActionRepairBoatChassis
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "REPAIR");
    }
}

modded class ActionRepairCarChassisWithBlowtorch
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "REPAIR");
    }
}

modded class ActionRepairCarEngineWithBlowtorch
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "REPAIR");
    }
}

modded class ActionRepairBoatEngine
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "REPAIR");
    }
}

modded class ActionRepairShelter
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "REPAIR");
    }
}

modded class ActionRepairItemWithBlowtorch
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "REPAIR");
    }
}

// ------------------------------------------------------------
// RESOURCE_GATHER action hooks.
// ------------------------------------------------------------

modded class ActionMineTree
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "RESOURCE_GATHER");
    }
}

modded class ActionMineBush
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "RESOURCE_GATHER");
    }
}

modded class ActionMineRock
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "RESOURCE_GATHER");
    }
}

modded class ActionMineRock1H
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "RESOURCE_GATHER");
    }
}

modded class ActionSawPlanks
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "RESOURCE_GATHER");
    }
}

modded class ActionMineTreeBark
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "RESOURCE_GATHER");
    }
}

modded class ActionDigWorms
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "RESOURCE_GATHER");
    }
}

modded class ActionMineBushByHand
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "RESOURCE_GATHER");
    }
}

modded class ActionBreakLongWoodenStick
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "RESOURCE_GATHER");
    }
}

// ------------------------------------------------------------
// RESTRAIN action hooks.
// ------------------------------------------------------------

modded class ActionCoverHeadSelf
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "RESTRAIN");
    }
}

modded class ActionUncoverHeadSelf
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "RESTRAIN");
    }
}

modded class ActionCoverHeadTarget
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "RESTRAIN");
    }
}

modded class ActionRestrainTarget
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "RESTRAIN");
    }
}

modded class ActionRestrainSelf
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "RESTRAIN");
    }
}

modded class ActionUnrestrainTarget
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "RESTRAIN");
    }
}

modded class ActionUnrestrainSelf
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "RESTRAIN");
    }
}

modded class ActionUncoverHeadTarget
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "RESTRAIN");
    }
}

modded class ActionGagSelf
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "RESTRAIN");
    }
}

modded class ActionGagTarget
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "RESTRAIN");
    }
}

modded class ActionUngagSelf
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "RESTRAIN");
    }
}

modded class ActionUngagTarget
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "RESTRAIN");
    }
}

modded class ActionUnrestrainTargetHands
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "RESTRAIN");
    }
}

// ------------------------------------------------------------
// SKIN_ANIMAL action hooks.
// ------------------------------------------------------------

modded class ActionSkinning
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "SKIN_ANIMAL");
    }
}

// ------------------------------------------------------------
// TRAP_EXPLOSIVE action hooks.
// ------------------------------------------------------------

modded class ActionAttachOnTrap
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "TRAP_EXPLOSIVE");
    }
}

modded class ActionClapBearTrapWithThisItem
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "TRAP_EXPLOSIVE");
    }
}

modded class ActionDisarmMine
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "TRAP_EXPLOSIVE");
    }
}

modded class ActionTriggerRemotely
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "TRAP_EXPLOSIVE");
    }
}

modded class ActionDisarmExplosive
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "TRAP_EXPLOSIVE");
    }
}

modded class ActionDisarmExplosiveWithRemoteDetonator
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "TRAP_EXPLOSIVE");
    }
}

modded class ActionDisarmExplosiveWithRemoteDetonatorUnpaired
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "TRAP_EXPLOSIVE");
    }
}

modded class ActionActivateTrap
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "TRAP_EXPLOSIVE");
    }
}

modded class ActionAttachExplosivesTrigger
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "TRAP_EXPLOSIVE");
    }
}

modded class ActionArmExplosive
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "TRAP_EXPLOSIVE");
    }
}

modded class ActionUnpin
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "TRAP_EXPLOSIVE");
    }
}

modded class ActionPin
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "TRAP_EXPLOSIVE");
    }
}

// ------------------------------------------------------------
// VEHICLE action hooks.
// ------------------------------------------------------------

modded class ActionStopEngine
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "VEHICLE");
    }
}

modded class ActionStopEngineBoat
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "VEHICLE");
    }
}

modded class ActionSwitchSeats
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "VEHICLE");
    }
}

modded class ActionFillGeneratorTank
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "VEHICLE");
    }
}

modded class ActionFillFuel
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "VEHICLE");
    }
}

modded class ActionStartEngine
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "VEHICLE");
    }
}

modded class ActionStartEngineBoat
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "VEHICLE");
    }
}

modded class ActionFillCoolant
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "VEHICLE");
    }
}

modded class ActionFillOil
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "VEHICLE");
    }
}

modded class ActionGetInTransport
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "VEHICLE");
    }
}

modded class ActionOpenCarDoors
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "VEHICLE");
    }
}

modded class ActionCloseCarDoors
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "VEHICLE");
    }
}

modded class ActionOpenCarDoorsOutside
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "VEHICLE");
    }
}

modded class ActionCloseCarDoorsOutside
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "VEHICLE");
    }
}

modded class ActionGetOutTransport
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "VEHICLE");
    }
}

modded class ActionAnimateSeats
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "VEHICLE");
    }
}

modded class ActionCarHornShort
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "VEHICLE");
    }
}

modded class ActionCarHornLong
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "VEHICLE");
    }
}

modded class ActionPushCar
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "VEHICLE");
    }
}

modded class ActionPushBoat
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "VEHICLE");
    }
}

modded class ActionPullBodyFromTransport
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "VEHICLE");
    }
}

// ------------------------------------------------------------
// WORLD_INTERACTION action hooks.
// ------------------------------------------------------------

modded class ActionUseUndergroundLever
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "WORLD_INTERACTION");
    }
}

// ------------------------------------------------------------
// WOUND_CARE action hooks.
// ------------------------------------------------------------

modded class ActionSplintSelf
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "WOUND_CARE");
    }
}

modded class ActionSplintTarget
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "WOUND_CARE");
    }
}

modded class ActionBandageSelf
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "WOUND_CARE");
    }
}

modded class ActionBandageTarget
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "WOUND_CARE");
    }
}

modded class ActionSewSelf
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "WOUND_CARE");
    }
}

modded class ActionSewTarget
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "WOUND_CARE");
    }
}

modded class ActionCPR
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);
        ST_SendActionStartThought(action_data, "WOUND_CARE");
    }
}

// ------------------------------------------------------------
// Weapon unjam hook.
// ------------------------------------------------------------

modded class WeaponManager
{
    override bool Unjam(ActionBase control_action = NULL)
    {
        bool result = super.Unjam(control_action);

        PlayerBase player = PlayerBase.Cast(m_player);

        if (player && result)
        {
            SurvivorThoughtsManager.Get().SendActionThought(player, "UNJAM");
        }

        return result;
    }
}
