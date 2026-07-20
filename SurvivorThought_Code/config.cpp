class CfgPatches
{
    class SurvivorThoughts
    {
        requiredAddons[] =
        {
            "DZ_Data",
            "DZ_Scripts",
            "DZ_Characters",
            "DZ_Gear_Containers",
            "DZ_Gear_Camping",
            "DZ_Gear_Consumables"
        };
        units[] = {"SurvivorJournal"};
        weapons[] = {};
    };
};

class CfgMods
{
    class SurvivorThoughts
    {
        dir = "SurvivorThoughts";
        picture = "";
        action = "";
        hideName = 0;
        hidePicture = 1;
        name = "Survivor Thoughts";
        credits = "Rebirth Network";
        author = "DayZ Architect";
        authorID = "0";
        version = "0.3.9.6";
        extra = 0;
        type = "mod";

        dependencies[] =
        {
            "Game",
            "World",
            "Mission"
        };

        class defs
        {
            class gameScriptModule
            {
                value = "";
                files[] =
                {
                    "SurvivorThoughts/Scripts/3_Game"
                };
            };

            class worldScriptModule
            {
                value = "";
                files[] =
                {
                    "SurvivorThoughts/Scripts/4_World"
                };
            };

            class missionScriptModule
            {
                value = "";
                files[] =
                {
                    "SurvivorThoughts/Scripts/5_Mission"
                };
            };
        };
    };
};



class CfgSlots
{
    class Slot_SurvivorJournal
    {
        name = "SurvivorJournal";
        displayName = "Survivor Journal";
        selection = "slot_survivorjournal";
        ghostIcon = "set:dayz_inventory image:book";
    };
};

class CfgVehicles
{
    class Man;
    class Inventory_Base;

    class SurvivorBase: Man
    {
        attachments[] += {"SurvivorJournal"};

        class InventoryEquipment
        {
            playerSlots[] += {"Slot_SurvivorJournal"};
        };
    };

    class SurvivorJournal: Inventory_Base
    {
        scope = 2;
        displayName = "Survivor Journal";
        descriptionShort = "A worn survivor journal containing identity, backstory, and survival notes.";
        model = "\dz\gear\books\book_kniga.p3d";
        weight = 250;
        itemSize[] = {2,3};
        absorbency = 0.5;
        rotationFlags = 17;
        inventorySlot[] = {"SurvivorJournal"};
        hiddenSelections[] = {};
        hiddenSelectionsTextures[] = {};
    };
};

