# Survivor Thoughts

## Mod Description

**Survivor Thoughts** is an immersive DayZ survival-narrative mod that gives each survivor a reactive internal voice. Instead of displaying random flavour text, the mod responds to what is actually happening to the player: hunger, thirst, injury, illness, temperature, combat, weather, location, equipment condition, actions, social encounters, memories, sanity, and death.

The system is designed to make survival feel more personal without overwhelming players with constant messages. Thoughts are controlled through cooldowns, probability checks, duplicate blockers, condition-stage transitions, and a configurable priority system. Critical survival and combat messages can take precedence over ambient thoughts such as weather, doors, or time of day.

Survivor Thoughts supports vanilla and modded DayZ environments and can be tuned for maps such as:

- Chernarus
- Sakhal
- Livonia
- Deer Isle
- Namalsk
- Custom community maps

### Main Features

- Context-sensitive survival thoughts
- Hunger, thirst, blood, shock, health, and temperature stages
- Yellow, red, critical, and combined-stat warnings
- Named eating and drinking messages
- Combat, bleeding, explosion, infected, and heavy-hit reactions
- Small-fall spam protection
- Equipment condition thoughts from Worn to Ruined
- Weather, time-of-day, location, shelter, and map-environment thoughts
- Custom thought zones for landmarks, bunkers, laboratories, islands, military areas, and story locations
- Personality, memory, sanity, and social-context systems
- Persistent Survivor Journals
- Readable journals from dead survivors
- Priority profiles for map-specific balancing
- Admin diagnostics, trigger coverage, analytics, and message-health checks
- Modular JSON configuration files
- Automatic additive configuration updates for missing priority records

### Survivor Journals

Every survivor can carry a persistent journal containing identity and story information. Journals can record major events and remain with the body after death. Other players can read a journal while holding it or directly from a dead survivor when the journal remains attached.

### Configurable Priorities

Server owners can decide which message types are most important. Higher-priority thoughts win over lower-priority thoughts.

Examples:

- Ambient door thoughts can remain low priority.
- Weather and fire can be emphasized on Sakhal.
- Navigation and custom zones can be emphasized on Deer Isle.
- Sanity and map-environment thoughts can be emphasized on Namalsk.
- Critical health, blood loss, and combat can always remain dominant.

### Designed for Server Owners

The mod is built around modular configuration files so communities can create different experiences without editing scripts. A hardcore winter server can make exposure and fire thoughts dominant, while a roleplay server can emphasize journals, personality, and story messages.

---

# Server Owner Guide

## 1. Installation

1. Stop the server.
2. Copy the complete `@SurvivorThoughts` folder into the DayZ server root.
3. Copy the mod key into the server's global `Keys` folder.
4. Add the mod to the server launch parameter.
5. Ensure players load the same mod through the launcher or server preset.
6. Start the server and allow the configuration files to generate.
7. Stop the server cleanly before editing the generated JSON files.

Example launch parameter:

```text
-mod=@CF;@SurvivorThoughts;@OtherMods
```

Place dependencies before Survivor Thoughts. Place compatibility patches after the mods they patch.

Recommended server options during testing:

```text
-profiles=ServerProfile
-filePatching
-dologs
-adminlog
-netlog
-freezecheck
```

## 2. Profile Folder

Survivor Thoughts stores its files in the configured server profile.

Typical location:

```text
$profile:ZombicideMods/SurvivorThoughts/
```

Typical generated structure:

```text
ZombicideMods/SurvivorThoughts/
├── Configs/
│   ├── 00_Core_Admin_Output.json
│   ├── 01_Player_State_Personality.json
│   ├── 02_Messages_Survival.json
│   ├── 03_Actions_Damage_Combat.json
│   ├── 04_World_Environment.json
│   ├── 05_Items_Corpses.json
│   ├── 06_Social_Sanity_Journal.json
│   ├── 07_Admin_Diagnostics.json
│   ├── 08_Survivor_Story_System.json
│   └── 09_Admin_Priority_Trigger_System.json
├── AdminReports/
├── Analytics/
├── Data/
├── Journals/
└── SurvivorThoughts_Debug.log
```

## 3. First-Startup Procedure

1. Install the mod.
2. Start the server.
3. Wait for mission initialization to complete.
4. Stop the server cleanly.
5. Back up the entire Survivor Thoughts profile folder.
6. Edit one configuration file at a time.
7. Restart the server after each major configuration change.
8. Check the RPT and Survivor Thoughts debug log for errors.

Do not edit configuration files while the server is actively saving.

## 4. Configuration Files

### `00_Core_Admin_Output.json`

Controls the global mod state and shared systems.

Common settings include:

- Master enable/disable
- Global cooldown
- Random thought delay
- Output method
- Persistent storage
- Base priority values
- Admin access
- Debug logging

Example:

```json
{
  "EnableMod": 1,
  "GlobalCooldownSeconds": 120.0,
  "MinimumRandomDelaySeconds": 45.0,
  "MaximumRandomDelaySeconds": 180.0
}
```

### `01_Player_State_Personality.json`

Controls player-state tracking and character behaviour.

Includes:

- Personality selection
- Player memory
- State history
- Trend detection
- Stealth and noise thoughts
- Shelter thoughts
- Mental-state checks
- Survival thresholds
- Passive context

Use this file to control how frequently the survivor reflects on their condition and previous events.

### `02_Messages_Survival.json`

Contains survival message pools and condition-stage settings.

Includes messages for:

- Hunger
- Thirst
- Blood
- Shock
- Health
- Cold
- Heat
- Sickness
- Bleeding
- Broken legs
- Combined survival problems

Each message array can be edited or expanded.

Example:

```json
"HungerRedMessages": [
  "I need food now.",
  "My body is running out of strength.",
  "I cannot keep moving like this."
]
```

### `03_Actions_Damage_Combat.json`

Controls action and combat reactions.

Includes:

- Eating and drinking
- Opening food
- Doors and containers
- Bandaging and wound care
- Medicine and injections
- Crafting and repairs
- Fireplaces and cooking
- Weapon unjamming
- Ammunition management
- Combat hits
- Infected attacks
- Gunshot hits
- Explosions
- Heavy damage
- Fall reactions

### `04_World_Environment.json`

Controls world-based thoughts.

Includes:

- Weather
- Rain
- Snow and cold exposure
- Time of day
- Location zones
- Wilderness detection
- Military areas
- Shelter
- Custom thought zones
- Contaminated zones
- Map-environment messages

### `05_Items_Corpses.json`

Controls equipment and corpse reactions.

Includes:

- Worn, damaged, badly damaged, and ruined gear
- Weapon condition
- Clothing condition
- Masks and filters
- Boots and backpacks
- Held-item condition
- Corpse detection radius
- Corpse context messages

Consumable food and drink in the player's hands are excluded from normal gear-wear thoughts.

### `06_Social_Sanity_Journal.json`

Controls social, sanity, and journal systems.

Includes:

- Survivor Journals
- Journal creation
- Journal attachment and locking
- Reading other players' journals
- Journal looting after death
- Sanity loss and recovery
- Cannibalism reactions
- Social-group messages
- Trust and betrayal
- Character background options

### `07_Admin_Diagnostics.json`

Controls diagnostic and analytics systems.

Includes:

- Decision tracing
- Blocked-thought logging
- Analytics saving
- JSON-lines output
- Recovery tracking
- Sanity tracking
- Social-event tracking
- State-history tracking

Use detailed tracing only during testing because it can create large logs.

### `08_Survivor_Story_System.json`

Controls the advanced narrative layer.

Includes:

- Story presets
- Map-tone packs
- Condition profiles
- Trait and fear wording
- Hallucination text
- Persistent player memory
- Journal sections
- Story analytics
- Daily story exports

Example story preset:

```json
"ActiveStoryPreset": "VanillaPlus_Light"
```

### `09_Admin_Priority_Trigger_System.json`

Controls runtime priority overrides and admin diagnostics.

Includes:

- Priority profiles
- Trigger coverage
- Message-health checks
- Admin menu access
- Trigger testing
- Config backups
- Missing-trigger diagnostics
- Specialized message arrays

## 5. Priority System

Higher numbers win against lower numbers.

Suggested ranges:

| Priority | Purpose |
|---:|---|
| 5-20 | Background ambience |
| 20-40 | Normal contextual thoughts |
| 40-65 | Important non-critical thoughts |
| 65-85 | Urgent survival or combat |
| 85-100 | Critical, lethal, or major narrative events |

Example:

```json
{
  "ThoughtType": "STAT_STAGE_CRITICAL",
  "Priority": 95,
  "CooldownSeconds": 0.0,
  "Enabled": 1
}
```

Exact thought types are checked before grouped aliases.

Example:

```json
{"ThoughtType":"StatWarnings","Priority":65,"CooldownSeconds":0.0,"Enabled":1}
{"ThoughtType":"STAT_STAGE_CRITICAL","Priority":95,"CooldownSeconds":0.0,"Enabled":1}
```

The exact critical record wins.

## 6. Common Priority Types

Useful exact types include:

```text
WEATHER
TIME_OF_DAY
LOCATION
MAP_ENVIRONMENT
CUSTOM_THOUGHT_ZONE
CONTAMINATED_ZONE
LOW_SURVIVAL
MEDIUM_SURVIVAL
HIGH_SURVIVAL
CRITICAL_SURVIVAL
STAT_STAGE_YELLOW
STAT_STAGE_RED
STAT_STAGE_CRITICAL
STAT_MULTI_RED
ITEM_WORN
ITEM_DAMAGED
ITEM_BADLY_DAMAGED
ITEM_RUINED
OPEN_CLOSE
OPEN_FOOD
EAT
DRINK
FIREPLACE
NAVIGATION
NEAR_MISS
COMBAT_STRESS
HEAVY_HIT
GUNSHOT_HIT
EXPLOSION_HIT
JOURNAL_SYSTEM
```

Useful groups include:

```text
MapEnvironment
Personality
Survival
StatWarnings
FoodDrink
ContaminatedZone
Combat
Bleeding
ItemCondition
JournalMajorEvent
```

## 7. Map-Specific Tuning

### Chernarus

Keep ambience restrained and let location, weather, survival, and combat remain dominant.

```json
{"ThoughtType":"WEATHER","Priority":20,"CooldownSeconds":0.0,"Enabled":1}
{"ThoughtType":"LOCATION","Priority":28,"CooldownSeconds":0.0,"Enabled":1}
{"ThoughtType":"OPEN_CLOSE","Priority":8,"CooldownSeconds":0.0,"Enabled":1}
{"ThoughtType":"MAP_ENVIRONMENT","Priority":24,"CooldownSeconds":0.0,"Enabled":1}
```

### Sakhal

Emphasize exposure, fire, temperature, and critical survival.

```json
{"ThoughtType":"WEATHER","Priority":45,"CooldownSeconds":0.0,"Enabled":1}
{"ThoughtType":"STAT_STAGE_RED","Priority":85,"CooldownSeconds":0.0,"Enabled":1}
{"ThoughtType":"STAT_STAGE_CRITICAL","Priority":97,"CooldownSeconds":0.0,"Enabled":1}
{"ThoughtType":"FIREPLACE","Priority":55,"CooldownSeconds":0.0,"Enabled":1}
```

### Deer Isle

Emphasize navigation, discovery, custom zones, and map environment.

```json
{"ThoughtType":"MAP_ENVIRONMENT","Priority":40,"CooldownSeconds":0.0,"Enabled":1}
{"ThoughtType":"NAVIGATION","Priority":32,"CooldownSeconds":0.0,"Enabled":1}
{"ThoughtType":"CUSTOM_THOUGHT_ZONE","Priority":50,"CooldownSeconds":0.0,"Enabled":1}
{"ThoughtType":"LOCATION","Priority":36,"CooldownSeconds":0.0,"Enabled":1}
```

### Namalsk

Emphasize weather, mental state, sanity, and special zones.

```json
{"ThoughtType":"WEATHER","Priority":50,"CooldownSeconds":0.0,"Enabled":1}
{"ThoughtType":"MAP_ENVIRONMENT","Priority":50,"CooldownSeconds":0.0,"Enabled":1}
{"ThoughtType":"MENTAL_STATE","Priority":65,"CooldownSeconds":0.0,"Enabled":1}
{"ThoughtType":"SANITY_CREEP","Priority":68,"CooldownSeconds":0.0,"Enabled":1}
```

### Livonia

Emphasize shelter, stealth, weather, and rural location context.

```json
{"ThoughtType":"WEATHER","Priority":28,"CooldownSeconds":0.0,"Enabled":1}
{"ThoughtType":"SHELTER","Priority":38,"CooldownSeconds":0.0,"Enabled":1}
{"ThoughtType":"LOCATION","Priority":34,"CooldownSeconds":0.0,"Enabled":1}
{"ThoughtType":"STEALTH_NOISE","Priority":40,"CooldownSeconds":0.0,"Enabled":1}
```

## 8. Custom Thought Zones

Custom zones allow server owners to add messages to specific coordinates.

Example:

```json
{
  "Name": "Island Laboratory",
  "Type": "LABORATORY",
  "X": 8500.0,
  "Z": 6200.0,
  "Radius": 200.0,
  "Chance": 0.5,
  "CooldownSeconds": 600.0,
  "Messages": [
    "This place feels wrong.",
    "Someone built this far away for a reason.",
    "I should not stay here longer than necessary."
  ]
}
```

Field meanings:

- `Name`: Administrative name
- `Type`: Zone category
- `X` and `Z`: Map coordinates
- `Radius`: Detection radius in metres
- `Chance`: Probability from `0.0` to `1.0`
- `CooldownSeconds`: Delay before another zone thought
- `Messages`: Candidate thought lines

## 9. Survivor Journals

Recommended journal settings:

```json
{
  "EnableSurvivorJournalItem": 1,
  "GiveJournalOnFreshSpawn": 1,
  "AutoEquipJournalOnFreshSpawn": 1,
  "LockJournalToPlayerWhileAlive": 1,
  "AllowJournalLootingAfterDeath": 1,
  "AllowReadingOtherPlayersJournals": 1
}
```

Expected actions:

```text
Read survivor journal
Read dead survivor journal
```

Test both cases:

1. Place a journal in the player's hands.
2. Confirm the held-item read action appears.
3. Kill a character carrying an attached journal.
4. Aim at the body.
5. Confirm the dead-survivor read action appears.
6. Loot the journal and confirm it remains readable.

## 10. Automatic Config Updates

The priority configuration uses additive migration.

When the server starts:

1. The existing file is loaded.
2. Missing priority records are detected.
3. Missing records are appended.
4. Existing edited priorities are preserved.
5. The updated file is saved.

The current priority config does not have its own dedicated `ConfigVersion` field. Always keep a backup before updating.

## 11. Recommended Editing Workflow

1. Stop the server.
2. Back up the complete Survivor Thoughts profile folder.
3. Edit one file.
4. Validate the JSON.
5. Start the server.
6. Test the affected system.
7. Check the RPT and debug log.
8. Record the change in a server changelog.
9. Move the change to production only after testing.

## 12. Runtime Test Checklist

| Test | Expected result |
|---|---|
| Food in hands | Worn food does not generate gear-wear thoughts |
| Eating | Thought includes the food display name |
| Drinking | Thought includes the container display name |
| Doors | Repeated opening does not cause spam |
| Small falls | Small ledges do not cause repeated damage thoughts |
| Survival stages | One thought per stage transition |
| Multiple red stats | Combined red warning appears |
| Equipment | One message per worsening condition stage |
| Held journal | Read action appears |
| Dead-player journal | Read action appears on corpse |
| Priority conflict | Critical thought wins over ambience |

## 13. Troubleshooting

### No thoughts appear

Check:

- The mod is loaded on server and client.
- `EnableMod` is `1`.
- The profile folder exists.
- The config files are valid JSON.
- The RPT contains no World script errors.

### Only some thoughts appear

Check the subsystem's enable flag and message array.

### Door spam

Increase the open-close cooldown and lower the `OPEN_CLOSE` priority.

### Priority changes do not work

Check:

- The exact `ThoughtType` spelling
- `Enabled` is `1`
- The record is in `PriorityProfiles`
- The server restarted after editing

### Journal action does not appear

Check:

- The journal exists
- Custom actions compiled
- Actions are registered through `ActionConstructor`
- The journal is still attached to the corpse
- Another mod has not replaced or cleaned up the body

### New config entries are missing

Start the server once, let it initialize fully, then stop it cleanly and inspect the JSON again.

### Compile errors after updating

Replace the complete scripts or PBO package. Do not merge random files from different versions.

## 14. Performance Recommendations

- Do not reduce all scan intervals to one second.
- Keep ambient thoughts on longer cooldowns.
- Use 4-10 strong messages per pool.
- Avoid excessive custom zones.
- Disable detailed tracing in production.
- Archive large analytics and journal folders.
- Test with realistic player counts.

## 15. Support

**Rebirth Network:** https://rebirthnetwork.gg  
**Discord:** https://discord.gg/rebirthnetwork

---

*Created with **DayZ Architect** by [Rebirth Network](https://rebirthnetwork.gg). Need help or feedback? Join our [Discord](https://discord.gg/rebirthnetwork).*
