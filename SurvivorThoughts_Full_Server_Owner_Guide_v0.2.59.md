# Survivor Thoughts — Server Owner Guide v0.2.59

## 1. Overview

**Survivor Thoughts** is a Vanilla+ immersion, psychology, and journal system for DayZ.

It adds internal survivor dialogue based on:

- Hunger, thirst, blood, shock, health, temperature, sickness, bleeding, broken legs
- Damage, gunshots, explosions, melee, infected hits, near-miss combat
- Weather, time of day, locations, shelter, contaminated zones, corpses
- Actions such as eating, drinking, bandaging, repairing, fishing, doors, fires, and other vanilla interactions
- Personality, mental state, sanity, social/group memory, lone-wolf isolation
- Pet dog context if DayZ-Dog is installed and enabled
- Persistent player journals that build a story from setup choices and in-game events

The current tested working version is:

```txt
v0.2.59 — Journal NetSync Compatibility Fix
```

This version starts clean after removing unsupported string NetSync calls from the Survivor Journal item.

---

## 2. Current folder layout

Survivor Thoughts now uses a cleaner split between **profile configs/logs** and **mission persistent data**.

### Profile folder

Configs and logs live here:

```txt
$profile:ZombicideMods/SurvivorThoughts/
```

Expected profile layout:

```txt
ZombicideMods/
└── SurvivorThoughts/
    ├── Configs/
    │   ├── 00_Core_Admin_Output.json
    │   ├── 01_Player_State_Personality.json
    │   ├── 02_Messages_Survival.json
    │   ├── 03_Actions_Damage_Combat.json
    │   ├── 04_World_Environment.json
    │   ├── 05_Items_Corpses.json
    │   ├── 06_Social_Sanity_Journal.json
    │   ├── 07_Admin_Diagnostics.json
    │   └── _Redundant/
    └── Logs/
        └── SurvivorThoughts_Debug.log
```

### Mission storage folder

Persistent player/story data lives here:

```txt
$mission:storage_1/ZombiCideMods/SurvivorThoughts/
```

Expected mission-storage layout:

```txt
storage_1/
└── ZombiCideMods/
    └── SurvivorThoughts/
        ├── Data/
        │   ├── PlayerPersonalities.json
        │   ├── PlayerPersistentStates.json
        │   └── PlayerBackstories.json
        ├── Debug/
        │   ├── PlayerStateSnapshots/
        │   └── DecisionTrace/
        ├── Analytics/
        └── Journals/
```

Logs stay in profile. Long-term player data moves to mission storage.

---

## 3. Automatic config migration

Older Survivor Thoughts versions used many separate config files. v0.2.40+ consolidates them into eight grouped files.

On startup, the mod can:

```txt
1. Detect old split config files.
2. Load old custom settings and message arrays.
3. Apply missing defaults for new fields.
4. Write the new eight-file config layout.
5. Move old files into Configs/_Redundant/.
```

This preserves old custom messages/settings while cleaning the active config folder.

### Important migration advice

Before first boot after a major config update, back up:

```txt
$profile:ZombicideMods/SurvivorThoughts/Configs/
```

Old files moved into:

```txt
$profile:ZombicideMods/SurvivorThoughts/Configs/_Redundant/
```

should not be edited unless you are manually recovering old custom text.

---

## 4. Config file overview

### 00_Core_Admin_Output.json

Controls core mod behaviour, output, debug logging, priority, message blocker, admin reload, and persistent storage paths.

Common settings:

```json
{
  "EnableMod": 1,
  "ConfigVersion": 59,
  "DebugMode": 0,
  "UseLocalChatBox": 1,
  "UseNotificationSystem": 0,
  "GlobalCooldownSeconds": 120.0,
  "MinimumRandomDelaySeconds": 45.0,
  "MaximumRandomDelaySeconds": 180.0,
  "EnableDebugFileLog": 1,
  "DebugLogToRPT": 1,
  "DebugLogFileName": "SurvivorThoughts_Debug.log",
  "ClearDebugLogOnServerStart": 1
}
```

Recommended live output:

```json
{
  "UseLocalChatBox": 1,
  "UseNotificationSystem": 0
}
```

Avoid enabling both unless you intentionally want double display.

### Debug log

Dedicated log path:

```txt
$profile:ZombicideMods/SurvivorThoughts/Logs/SurvivorThoughts_Debug.log
```

Search for:

```txt
[SurvivorThoughts][DEBUG]
```

---

### 01_Player_State_Personality.json

Controls:

```txt
- Stat thresholds
- Player state history
- Personality profiles
- Personality drift
- Mental state
- Player memory
```

Tracked stats include:

```txt
Health
Blood
Shock
Energy / food
Water / thirst
Heat comfort
Bleeding count
Sickness state
Broken legs
Recent danger
Recent social/corpse/sanity events
```

Personality profiles include:

```txt
Practical
Scared
Military
Hopeless
Aggressive
Calm
```

Mental states include:

```txt
Stable
Uneasy
Afraid
Desperate
Numb
Aggressive
Broken
Focused
```

Player memory tracks recent events such as:

```txt
Recently shot
Recently bleeding
Recently near corpse
Recently in military zone
Recently starving/dehydrating/freezing/overheating
Recently alone
Recently companion harmed
```

---

### 02_Messages_Survival.json

Controls survival, combined, advanced combined, recovery, and disease-specific message pools.

Includes:

```txt
EnergyStage1Messages ... EnergyStage4Messages
WaterStage1Messages ... WaterStage4Messages
BloodStage1Messages ... BloodStage4Messages
ShockStage1Messages ... ShockStage4Messages

Cold_Mild_Messages
Cold_Moderate_Messages
Cold_Severe_Messages
Cold_Critical_Messages

Hot_Mild_Messages
Hot_Moderate_Messages
Hot_Severe_Messages
Hot_Critical_Messages

Sickness_Early_Messages
Sickness_Moderate_Messages
Sickness_Severe_Messages
Sickness_Critical_Messages

Bleeding_One_Messages
Bleeding_Multiple_Messages
Bleeding_Critical_Messages

BrokenLegMessages
Infected_Far_Messages
Infected_Close_Messages
Infected_VeryClose_Messages
Infected_Surrounded_Messages
```

Advanced combined examples:

```txt
Starving + dehydrated
Cold + wet + night
Gunshot + bleeding
Bleeding + low blood + shock
Broken leg + infected nearby
Low sanity + corpse nearby
Companion dead + night
Shelter + infected + night
```

Recovery messages include:

```txt
Bleeding stopped
Health stabilizing
Food/water improving
Warming up
Cooling down
Escaped infected
Survived until dawn
Post-combat breath
Almost died recovery
```

Disease-specific pools include:

```txt
Wound infection
Cholera
Influenza
Kuru-style deterioration
Gas exposure
Fever
Food poisoning
Unknown sickness fallback
```

---

### 03_Actions_Damage_Combat.json

Controls action messages, damage reactions, bleeding reactions, combat stress, and near-miss combat.

Action categories include:

```txt
Eating
Drinking
Unsafe drinking
Unjamming
Skinning animals
Skinning humans
Bandaging
Fire starting
Cooking
Fishing
Repairing
Open/close doors
Medicine
Wound care
Crafting
Deploying
Gardening
Resource gathering
Vehicle actions
Inventory management
Ammo management
Movement
World interaction
```

Damage reaction types:

```txt
Zombie hit
Player melee hit
Gunshot hit
Explosion hit
Heavy hit
Bleeding started
Bleeding worse
Bleeding stopped
```

Useful cooldowns:

```json
{
  "ActionThoughtCooldownSeconds": 30.0,
  "OpenCloseActionCooldownSeconds": 2.5,
  "DuplicateImmediateActionCooldownSeconds": 0.75
}
```

The duplicate-action cooldown prevents inheritance/double-hook spam such as:

```txt
EAT + EAT
DRINK + DRINK
OPEN_CLOSE + OPEN_CLOSE
```

---

### 04_World_Environment.json

Controls weather, time of day, locations, map environment packs, shelter, and custom thought zones.

Weather pools include:

```txt
Clear weather
Overcast
Light rain
Heavy rain
Rain fallback
Fog
Wind
Storm
```

Time-of-day pools include:

```txt
Dawn
Morning
Noon
Afternoon
Dusk
Night
Midnight
Early morning
```

Location types include:

```txt
Coast
Town
City
Forest
Wilderness
Military
Police
Medical
Industrial
Farm
Water
```

Shelter thoughts cover:

```txt
Nearby buildings
Shelter during rain/storm
Shelter at night
Unsafe shelter with infected nearby
Safe shelter relief
```

Custom thought zones let admins define RP/lore/event areas:

```json
{
  "Name": "Haunted Military Camp",
  "Type": "Horror",
  "X": 4520.0,
  "Z": 10220.0,
  "Radius": 150.0,
  "Chance": 0.5,
  "CooldownSeconds": 600.0,
  "Messages": [
    "Something is wrong with this place.",
    "I should not stay here."
  ]
}
```

Map packs include support-style message pools for:

```txt
Generic
Chernarus
Livonia
Namalsk
Sakhal
Deer Isle
```

---

### 05_Items_Corpses.json

Controls item-condition and corpse proximity thoughts.

Item checks can scan:

```txt
Hands
Shoulder
Melee
Headgear
Mask
Eyewear
Gloves
Vest
Body
Legs
Hips
Back
Feet
```

Message categories include:

```txt
Badly damaged generic items
Weapons
Shoes
Clothing
Backpack
Vest
Headgear
Gloves
Mask
Belt
```

Corpse thoughts include:

```txt
Nearby corpse
Nearby player corpse
Nearby infected corpse
Nearby animal corpse
```

---

### 06_Social_Sanity_Journal.json

Controls social/group thoughts, stealth/noise, sanity/cannibalism, player journals, backstories, the Survivor Journal item, setup menu, and optional DayZ-Dog messages.

#### Social/group system

Tracks nearby players by proximity over time. A player can become a temporary companion if they stay nearby long enough.

Message categories:

```txt
Friendly nearby
Teammate shot
Teammate down
Lone wolf
```

#### Stealth/noise system

Can trigger thoughts around:

```txt
Sprinting near infected
Moving at night
Military-zone noise risk
Unsafe movement near danger
```

#### Sanity/cannibalism system

Tracks hidden sanity/stress.

Sanity can drop after:

```txt
Skinning humans
Eating human meat
Other configured disturbing actions
```

Message pools include:

```txt
SanityUneasyMessages
SanityUnhingedMessages
SanityPsychoticMessages
CannibalismCreepMessages
```

#### Survivor Journal item

The journal now behaves like an identity item.

Features:

```txt
Auto-equipped to players
Custom SurvivorJournal attachment slot
Locked while owner is alive
Unlocked/lootable after owner death
Stores owner Steam64/name/journal ID/timestamps/death state
Writes final death entries
Anti-exploit fallback deletes living-owner journals moved away by inventory glitches
```

Important config options:

```json
{
  "EnableSurvivorJournalItem": 1,
  "AutoEquipJournalOnFreshSpawn": 1,
  "AutoEquipJournalOnLoginIfMissing": 1,
  "LockJournalToPlayerWhileAlive": 1,
  "AllowJournalLootingAfterDeath": 1,
  "DeleteJournalIfRemovedWhileAlive": 1,
  "WriteJournalDeathEntryOnKilled": 1,
  "JournalRequiredBeforeNormalPlay": 1
}
```

#### Journal setup menu

When enabled, players complete a protected setup menu shortly after character creation.

Fields:

```txt
Survivor name
Origin
Former occupation
Core trait
Fear
Current goal
Useful skill
Weakness
Moral code
```

Protected setup behaviour:

```txt
Damage blocked while setup is active
Thoughts suppressed until setup complete
Menu reopens if closed before submission
Normal gameplay starts only after confirmation
```

#### Journal story integration

The journal story can record major events from:

```txt
Setup/backstory choices
Survival crises
Actions
Damage
Bleeding
Recovery
Social/group events
Sanity/cannibalism
Mental state
Disease
Near-miss combat
Custom zones
Corpse/contaminated-zone events
Death/final snapshot
```

The system is designed to build a story from the player’s Survivor Thoughts and actions over time.

#### DayZ-Dog optional integration

If DayZ-Dog is installed and the `DAYZDOG` define is available, optional direct hooks can trigger pet-related thoughts. There is also a safe runtime nearby-dog awareness check using object type strings, so Survivor Thoughts does not hard-require DayZ-Dog.

Pet dog message pools:

```txt
PetDogNearbyMessages
PetDogFeedMessages
PetDogTameMessages
PetDogFollowMessages
PetDogStayMessages
PetDogBandageMessages
PetDogSummonMessages
PetDogCompanionMessages
```

Example config fields:

```json
{
  "EnablePetDogThoughts": 1,
  "PetDogThoughtCooldownSeconds": 180.0,
  "PetDogThoughtChance": 0.45,
  "EnablePetDogNearbyMessages": 1,
  "EnablePetDogFeedMessages": 1,
  "EnablePetDogTameMessages": 1,
  "EnablePetDogFollowMessages": 1,
  "EnablePetDogStayMessages": 1,
  "EnablePetDogBandageMessages": 1,
  "EnablePetDogSummonMessages": 1,
  "EnablePetDogCompanionMessages": 1
}
```

---

### 07_Admin_Diagnostics.json

Controls trace logging, state snapshots, analytics, journals, and debug diagnostics.

Optional systems:

```txt
Thought decision trace
Player state snapshots
Admin analytics JSONL
Journal event debug
Blocked-thought debug
```

Mission-storage debug paths:

```txt
$mission:storage_1/ZombiCideMods/SurvivorThoughts/Debug/PlayerStateSnapshots/
$mission:storage_1/ZombiCideMods/SurvivorThoughts/Debug/DecisionTrace/
$mission:storage_1/ZombiCideMods/SurvivorThoughts/Analytics/
$mission:storage_1/ZombiCideMods/SurvivorThoughts/Journals/
```

Use these carefully on live servers because they can generate disk output.

Recommended live setting:

```json
{
  "EnablePlayerStateSnapshots": 0,
  "EnableThoughtDecisionTrace": 0,
  "EnableAdminAnalytics": 0
}
```

Recommended testing setting:

```json
{
  "DebugMode": 1,
  "EnableDebugFileLog": 1,
  "EnableThoughtDecisionTrace": 1,
  "TraceOnlyBlockedThoughts": 1
}
```

---

## 5. Thought priority system

The priority system stops low-importance ambient thoughts from interrupting urgent survival events.

Example priority logic:

```txt
Bleeding / gunshot / explosion = very high
Death spiral states = very high
Contaminated zone / combat stress = high
Item condition / corpse = medium
Action thoughts = medium-low
Weather / time / personality = low
```

Example behaviour:

```txt
A player starts bleeding.
A weather thought tries to fire two seconds later.
The weather thought is blocked because bleeding has higher priority.
```

Debug line example:

```txt
Thought priority blocked. Type=WEATHER Priority=15 LastType=BLEEDING_STARTED LastPriority=100
```

---

## 6. Message blocker

The recent-message blocker prevents exact repeated text from appearing too often.

It tracks recent messages per player and can block duplicates for a configurable time window.

Use this to keep small custom message pools from feeling repetitive.

---

## 7. Persistent story and journal data

The player story is built from two parts:

```txt
1. Player-created setup/backstory choices
2. Auto-logged major events from Survivor Thoughts systems
```

Important persistent files:

```txt
$mission:storage_1/ZombiCideMods/SurvivorThoughts/Data/PlayerBackstories.json
$mission:storage_1/ZombiCideMods/SurvivorThoughts/Data/PlayerPersistentStates.json
$mission:storage_1/ZombiCideMods/SurvivorThoughts/Data/PlayerPersonalities.json
```

Physical journal item data stores lookup details such as:

```txt
Owner Steam64
Owner name
Journal ID
Created timestamp
Death timestamp
Owner-dead state
```

The long story record lives in mission storage.

---

## 8. Recommended server presets

### Balanced Vanilla+

```json
{
  "UseLocalChatBox": 1,
  "UseNotificationSystem": 0,
  "GlobalCooldownSeconds": 120.0,
  "MinimumRandomDelaySeconds": 45.0,
  "MaximumRandomDelaySeconds": 180.0,
  "ShowHealthyMessages": 0
}
```

### Quiet Hardcore

```json
{
  "GlobalCooldownSeconds": 240.0,
  "MinimumRandomDelaySeconds": 120.0,
  "MaximumRandomDelaySeconds": 360.0,
  "WeatherThoughtChance": 0.15,
  "TimeOfDayThoughtChance": 0.15,
  "PersonalityThoughtChance": 0.10
}
```

### RP / Story Heavy

```json
{
  "GlobalCooldownSeconds": 90.0,
  "PersonalityThoughtChance": 0.25,
  "EnableJournalSystemIntegration": 1,
  "JournalRecordAllThoughtSystems": 1,
  "JournalRecordAmbientSystems": 1,
  "EnableSocialGroupThoughts": 1,
  "EnableSanitySystem": 1
}
```

### Debug / Testing

```json
{
  "DebugMode": 1,
  "EnableDebugFileLog": 1,
  "DebugLogToRPT": 1,
  "ClearDebugLogOnServerStart": 1,
  "EnableThoughtDecisionTrace": 1,
  "TraceOnlyBlockedThoughts": 1
}
```

---

## 9. Troubleshooting

### No messages appear

Check:

```txt
EnableMod = 1
UseLocalChatBox or UseNotificationSystem = 1
Global cooldown is not too high
Thought priority is not blocking low-priority messages
Message blocker is not blocking repeated text
Journal setup is complete
```

### Debug file not created

Check:

```txt
DebugMode = 1
EnableDebugFileLog = 1
Server has write permissions to profile folder
```

Expected path:

```txt
$profile:ZombicideMods/SurvivorThoughts/Logs/SurvivorThoughts_Debug.log
```

### Journal cannot be removed

This is intended while the player is alive.

It should become removable after death if:

```txt
AllowJournalLootingAfterDeath = 1
WriteJournalDeathEntryOnKilled = 1
```

### Journal setup menu keeps reopening

This means the player has not submitted the setup form yet. Submit the form to begin normal gameplay.

### DayZ-Dog not installed

The mod should still run. Direct DayZ-Dog hooks are wrapped in `#ifdef DAYZDOG`, and runtime dog awareness avoids direct hard class dependencies.

---

## 10. Updating safely

Recommended update flow:

```txt
1. Back up Configs folder.
2. Back up mission storage SurvivorThoughts Data folder.
3. Install new PBO/scripts.
4. Start server with DebugMode = 1 for one test boot.
5. Check SurvivorThoughts_Debug.log.
6. Confirm configs generated/migrated cleanly.
7. Turn DebugMode back off for live operation.
```

---

## 11. Current known working baseline

Version:

```txt
v0.2.59
```

Key stability fixes included:

```txt
- Journal RPC enum duplicate fixed
- MissionServer OnRPC override removed
- Journal setup RPC moved to PlayerBase
- XComboBoxWidget.GetItem removed
- Advanced combined logic split and state-object based
- Cross-file m_ST_* direct reads removed from advanced-combo split
- Unsupported RegisterNetSyncVariableString removed
- SurvivorJournal registered in config.cpp
- Dedicated debug log support
- Consolidated config layout with legacy migration
```

---

*Created with **DayZ Architect** by [Rebirth Network](https://rebirthnetwork.gg). Need help or feedback? Join our [Discord](https://discord.gg/rebirthnetwork).*
