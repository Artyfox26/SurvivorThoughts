# Survivor Thoughts — Detailed Server Owner Guide

**For Chernarus, Sakhal, Livonia, Deer Isle, Namalsk, and custom maps**  
**Guide version:** 1.0  
**Mod baseline:** v0.3.10.21

> This guide is written for dedicated-server owners, community administrators, and modpack maintainers. It covers installation, configuration, map-specific priority tuning, journals, updates, testing, performance, and troubleshooting.

---

## Contents

1. [What Survivor Thoughts Does](#1-what-survivor-thoughts-does)
2. [Server Requirements and Folder Layout](#2-server-requirements-and-folder-layout)
3. [Installation and Launch Parameters](#3-installation-and-launch-parameters)
4. [First Startup and Generated Files](#4-first-startup-and-generated-files)
5. [Configuration Architecture](#5-configuration-architecture)
6. [Core Settings](#6-core-settings)
7. [Action, Survival, Damage, and Environment Messages](#7-action-survival-damage-and-environment-messages)
8. [Priority Profiles and Map Tuning](#8-priority-profiles-and-map-tuning)
9. [Survivor Journals](#9-survivor-journals)
10. [Update and Migration Behavior](#10-update-and-migration-behavior)
11. [Recommended Map Presets](#11-recommended-map-presets)
12. [Testing and Validation](#12-testing-and-validation)
13. [Performance and Administration](#13-performance-and-administration)
14. [Troubleshooting](#14-troubleshooting)
15. [Safe Change Workflow](#15-safe-change-workflow)
16. [Quick Reference](#16-quick-reference)

---

# 1. What Survivor Thoughts Does

Survivor Thoughts adds context-sensitive internal dialogue to DayZ. The system reacts to survival states, combat, damage, weather, time of day, locations, equipment condition, actions, personality, sanity, social situations, and journals.

Main systems include:

- Survival state transitions for hunger, thirst, blood, shock, health, and temperature.
- Action thoughts for eating, drinking, opening food, opening doors, bandaging, repairs, crafting, navigation, and many other actions.
- Damage reactions for infected attacks, melee hits, firearm hits, explosions, heavy damage, and meaningful fall damage.
- Equipment reactions for gear condition stages from Worn through Ruined.
- World context for weather, time, location, shelter, stealth, map environment, and custom thought zones.
- Narrative systems for personality, memory, sanity, major journal events, and readable survivor journals.
- Admin systems for priority profiles, trigger coverage, diagnostics, message-health checks, and configurable message pools.

> **Design principle:** The mod should add atmosphere without drowning the player in text. Cooldowns, priority arbitration, duplicate blockers, stage transitions, and frequency gates are central to good configuration.

---

# 2. Server Requirements and Folder Layout

Typical mod structure:

```text
@SurvivorThoughts/
├── Addons/
├── Keys/
├── mod.cpp
└── meta.cpp
```

Typical server profile output:

```text
$profile:ZombicideMods/SurvivorThoughts/
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
├── JournalRecords/
├── StoryAnalytics/
└── SurvivorThoughts_Debug.log
```

> **Important:** `$profile` points to the directory supplied by the server's `-profiles` launch parameter.

---

# 3. Installation and Launch Parameters

## 3.1 Install the server mod

1. Stop the server.
2. Copy the complete `@SurvivorThoughts` folder into the server root.
3. Copy the mod key from the mod's `Keys` folder into the server's global `Keys` folder.
4. Add `@SurvivorThoughts` to the server mod parameter.
5. Add the same mod to client-side distribution through the launcher or preset.
6. Start the server and inspect the script logs before allowing players to join.

Example:

```text
-mod=@CF;@SurvivorThoughts;@OtherMods
```

Place dependencies before Survivor Thoughts. Place compatibility patches after both mods they patch.

## 3.2 Recommended launch options

```text
-profiles=ServerProfile
-filePatching
-dologs
-adminlog
-netlog
-freezecheck
```

`-filePatching` is useful for development and testing. Production servers may choose not to use it once the PBO is final.

---

# 4. First Startup and Generated Files

On first successful startup, the mod creates its profile folders and configuration files.

Recommended first-boot procedure:

1. Start the server with the mod enabled.
2. Wait until mission initialization completes.
3. Stop the server cleanly.
4. Open the generated `Configs` folder.
5. Back up the entire `SurvivorThoughts` profile directory.
6. Edit one subsystem at a time.
7. Restart and inspect the RPT and Survivor Thoughts debug log.

> **Do not edit while the server is saving.** Editing JSON while the server is running can be overwritten or produce a partially written file.

---

# 5. Configuration Architecture

| File | Purpose | Common edits |
|---|---|---|
| `00_Core_Admin_Output.json` | Master enable, output, admin, debug behavior | Enable/disable systems, debug logging |
| `01_Player_State_Personality.json` | Player state, personality, memory, mental-state settings | Chances, cooldowns, thresholds |
| `02_Messages_Survival.json` | Hunger, thirst, blood, shock, health, temperature messages | Message wording and pool size |
| `03_Actions_Damage_Combat.json` | Action hooks, combat, damage, medical, eating, drinking | Action pools and cooldowns |
| `04_World_Environment.json` | Weather, time, location, shelter, map environment | Map-specific world balance |
| `05_Items_Corpses.json` | Gear condition, corpse context, item messages | Condition reactions and corpse atmosphere |
| `06_Social_Sanity_Journal.json` | Social, sanity, journals, memory | Journal behavior and narrative intensity |
| `07_Admin_Diagnostics.json` | Diagnostics and admin support | Logging and validation |
| `08_Survivor_Story_System.json` | Story presets, map tone, traits, condition profiles | Preset and narrative tuning |
| `09_Admin_Priority_Trigger_System.json` | Priority profiles, trigger coverage, health checks | Per-map arbitration and overrides |

The numbered files are separated so server owners can maintain focused changes and compare updates more easily.

---

# 6. Core Settings

## 6.1 Master enable flags

Most systems have both a global master flag and a subsystem flag.

Example:

```json
{
  "EnableMod": 1,
  "EnableActionThoughts": 1,
  "EnableItemConditionThoughts": 1,
  "EnableMentalStateThoughts": 1
}
```

A message pool can be populated correctly but never fire if its enable flag is disabled.

## 6.2 Cooldowns and duplicate blocking

Important settings include:

- `ActionThoughtCooldownSeconds`
- `OpenCloseActionCooldownSeconds`
- `DuplicateImmediateActionCooldownSeconds`
- `RecentMessageBlockSeconds`
- Subsystem-specific cooldowns

Recommended approach:

- Keep door thoughts low priority and infrequent.
- Keep critical survival, bleeding, and serious combat reactions high priority.
- Keep scan intervals shorter than cooldowns.
- Avoid setting all cooldowns to very low values.

---

# 7. Action, Survival, Damage, and Environment Messages

## 7.1 Eating and drinking

Eating and drinking thoughts can include the held item's display name.

Examples:

```text
The Baked Beans should keep me going.
I need a drink from the Canteen.
```

Direct-world actions, such as drinking from a well, may use generic wording when no held item exists.

## 7.2 Food and gear condition

Consumable food and drink items held in the player's hands are excluded from important-gear wear messages.

Durable equipment remains eligible, including:

- Weapons
- Tools
- Clothing
- Masks
- Backpacks
- Boots
- Vests
- Belts

## 7.3 Stat stages

The tracked stages are:

- Yellow: warning-level thought
- Red: high-priority survival thought
- Critical: critical survival thought
- Multiple red stats: combined warning

The system tracks stage changes rather than repeatedly announcing the same state.

## 7.4 Fall damage

Minor falls are filtered. Meaningful fall reactions use a cooldown so stepping off small ledges does not flood the player.

## 7.5 Door frequency

Door and open-close thoughts use:

- A minimum cooldown
- A frequency gate
- Low default priority

They should remain ambient and should not compete with survival or combat.

---

# 8. Priority Profiles and Map Tuning

Priority determines which thought wins when several systems attempt to speak at nearly the same time.

Higher values win over lower values.

Example record:

```json
{
  "ThoughtType": "WEATHER",
  "Priority": 45,
  "CooldownSeconds": 0.0,
  "Enabled": 1
}
```

## 8.1 Exact type vs group alias

Exact thought types are checked before broad group aliases.

Example:

```json
{"ThoughtType":"StatWarnings","Priority":65,"CooldownSeconds":0.0,"Enabled":1}
{"ThoughtType":"STAT_STAGE_CRITICAL","Priority":95,"CooldownSeconds":0.0,"Enabled":1}
```

Here, `STAT_STAGE_CRITICAL` overrides the broader `StatWarnings` group.

## 8.2 Important configurable groups

- `MapEnvironment`
- `Personality`
- `Survival`
- `StatWarnings`
- `FoodDrink`
- `ContaminatedZone`
- `Combat`
- `Bleeding`
- `ItemCondition`
- `JournalMajorEvent`

## 8.3 Important exact types

```text
WEATHER
TIME_OF_DAY
LOCATION
MAP_ENVIRONMENT
CUSTOM_THOUGHT_ZONE
CONTAMINATED_ZONE
STAT_STAGE_YELLOW
STAT_STAGE_RED
STAT_STAGE_CRITICAL
STAT_MULTI_RED
LOW_SURVIVAL
HIGH_SURVIVAL
CRITICAL_SURVIVAL
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

## 8.4 Practical priority ranges

| Range | Use | Examples |
|---:|---|---|
| 5–20 | Background ambience | Doors, time, passive mood |
| 20–40 | Normal context | Location, food, navigation, crafting |
| 40–65 | Important but non-critical | Disease, bandaging, damaged gear |
| 65–85 | Urgent | Red stats, bleeding, combat stress |
| 85–100 | Critical or major | Critical stats, explosions, death spiral, major journal events |

---

# 9. Survivor Journals

Survivor Journals can:

- Attach to players
- Persist owner data
- Record major events
- Become readable after death
- Remain locked while the owner is alive
- Become lootable after death
- Be read while held
- Be read while still attached to a dead player

Expected actions:

```text
Read survivor journal
Read dead survivor journal
```

## 9.1 Journal troubleshooting

1. Confirm the journal item exists on the player or corpse.
2. Confirm both journal actions are registered through `ActionConstructor`.
3. Confirm the journal's `SetActions()` adds the held-item read action.
4. Confirm `PlayerBase.SetActions()` adds the dead-player target action.
5. Check the debug log for held or dead-player action execution entries.
6. Verify journal configuration allows post-death looting and reading.

> A dead body can change inventory state during cleanup or corpse conversion. Test journal reading before corpse lifetime expires and before another mod moves or replaces the body.

---

# 10. Update and Migration Behavior

## 10.1 Automatic config updates

The priority profile loader appends missing records when the server starts.

It should:

- Preserve existing edited values
- Add missing priority records
- Save the updated JSON
- Preserve exact-type precedence over grouped aliases

## 10.2 Config version tracking

The current priority configuration does not use a dedicated internal `ConfigVersion` field.

The package version is:

```text
v0.3.10.21
```

The priority JSON itself does not yet expose a schema version.

## 10.3 Safe update process

1. Stop the server.
2. Back up the mod folder and profile configuration folder.
3. Replace the complete scripts/PBO package.
4. Start the server once and allow migration to finish.
5. Stop the server.
6. Compare the updated JSON against the backup.
7. Reapply only intentional custom values.
8. Run the runtime test checklist.

---

# 11. Recommended Map Presets

## 11.1 Chernarus

```json
{"ThoughtType":"WEATHER","Priority":20,"CooldownSeconds":0.0,"Enabled":1}
{"ThoughtType":"LOCATION","Priority":28,"CooldownSeconds":0.0,"Enabled":1}
{"ThoughtType":"OPEN_CLOSE","Priority":8,"CooldownSeconds":0.0,"Enabled":1}
{"ThoughtType":"MAP_ENVIRONMENT","Priority":24,"CooldownSeconds":0.0,"Enabled":1}
```

Chernarus benefits from restrained ambience.

## 11.2 Sakhal

```json
{"ThoughtType":"WEATHER","Priority":45,"CooldownSeconds":0.0,"Enabled":1}
{"ThoughtType":"STAT_STAGE_RED","Priority":85,"CooldownSeconds":0.0,"Enabled":1}
{"ThoughtType":"STAT_STAGE_CRITICAL","Priority":97,"CooldownSeconds":0.0,"Enabled":1}
{"ThoughtType":"FIREPLACE","Priority":55,"CooldownSeconds":0.0,"Enabled":1}
{"ThoughtType":"CONTAMINATED_ZONE","Priority":90,"CooldownSeconds":0.0,"Enabled":1}
```

Sakhal should emphasize exposure, fire, cold, and survival escalation.

## 11.3 Deer Isle

```json
{"ThoughtType":"MAP_ENVIRONMENT","Priority":40,"CooldownSeconds":0.0,"Enabled":1}
{"ThoughtType":"NAVIGATION","Priority":32,"CooldownSeconds":0.0,"Enabled":1}
{"ThoughtType":"CUSTOM_THOUGHT_ZONE","Priority":50,"CooldownSeconds":0.0,"Enabled":1}
{"ThoughtType":"LOCATION","Priority":36,"CooldownSeconds":0.0,"Enabled":1}
```

Deer Isle benefits from strong exploration and landmark context.

## 11.4 Namalsk

```json
{"ThoughtType":"WEATHER","Priority":50,"CooldownSeconds":0.0,"Enabled":1}
{"ThoughtType":"MAP_ENVIRONMENT","Priority":50,"CooldownSeconds":0.0,"Enabled":1}
{"ThoughtType":"MENTAL_STATE","Priority":65,"CooldownSeconds":0.0,"Enabled":1}
{"ThoughtType":"SANITY_CREEP","Priority":68,"CooldownSeconds":0.0,"Enabled":1}
{"ThoughtType":"CUSTOM_THOUGHT_ZONE","Priority":70,"CooldownSeconds":0.0,"Enabled":1}
```

## 11.5 Livonia

```json
{"ThoughtType":"WEATHER","Priority":28,"CooldownSeconds":0.0,"Enabled":1}
{"ThoughtType":"SHELTER","Priority":38,"CooldownSeconds":0.0,"Enabled":1}
{"ThoughtType":"LOCATION","Priority":34,"CooldownSeconds":0.0,"Enabled":1}
{"ThoughtType":"STEALTH_NOISE","Priority":40,"CooldownSeconds":0.0,"Enabled":1}
```

---

# 12. Testing and Validation

## 12.1 Compile validation

- Compile the World script module.
- Resolve the first error before assuming later errors are independent.
- Restart Workbench after replacing large script sets.
- Delete stale extracted files rather than merging over previous versions.
- Inspect exact line numbers in the file Workbench is compiling.

## 12.2 Runtime test checklist

| Test | Expected result |
|---|---|
| Food condition | Hold worn canned food; no gear-wear thought |
| Eating | Message includes the item's display name |
| Drinking | Message includes the held container's display name |
| Door spam | Repeated door thoughts are suppressed |
| Falls | Small ledges do not create reaction spam |
| Stats | One message per yellow, red, and critical transition |
| Combined stats | More than one red stat produces a combined warning |
| Gear stages | One message per worsening condition stage |
| Journals | Read while held and while attached to a dead player |
| Priorities | Critical warning wins over ambient thoughts |

---

# 13. Performance and Administration

Recommended practices:

- Keep scan intervals reasonable.
- Do not reduce every timer to one second.
- Use cooldowns before increasing message-pool size.
- Avoid excessive custom zones.
- Keep debug logging enabled during development.
- Reduce noisy logging in production.
- Archive old logs and journal records.
- Test with realistic player counts.

## 13.1 Message pool quality

Five to ten strong messages per trigger is usually better than a very large repetitive pool.

Avoid messages that differ by only one or two words.

## 13.2 Admin change control

- Use source control or dated ZIP backups.
- Record every changed JSON key in a changelog.
- Change one subsystem at a time.
- Keep separate development and production profiles.
- Do not let multiple admins edit the same JSON simultaneously.

---

# 14. Troubleshooting

| Problem | Likely cause | Action |
|---|---|---|
| No thoughts at all | Master flag disabled, mod not loaded, config not generated | Check launch parameters, `EnableMod`, RPT, and profile path |
| Only some systems work | Subsystem flag disabled or empty message pool | Check the relevant numbered JSON file |
| Repeated door messages | Cooldown too low or old config retained | Raise `OpenCloseActionCooldownSeconds` and lower `OPEN_CLOSE` priority |
| Food appears as gear wear | Old scripts or consumable classification issue | Confirm current scripts and held-consumable exclusion |
| Eating lacks item name | No main item or old action routing | Test with a held edible |
| Short-fall spam | Thresholds too low or cooldown missing | Increase trivial-fall thresholds or cooldown |
| Journal action missing | Action not registered or corpse lacks journal | Check `ActionConstructor`, `SetActions()`, and debug logs |
| Priority changes ignored | Wrong `ThoughtType` or disabled record | Use exact type and confirm `Enabled=1` |
| New priority entries missing | Server has not completed a clean boot/save | Start once, stop cleanly, inspect JSON |
| World module compile error | Parser issue or stale merge | Replace the complete scripts folder |

---

# 15. Safe Change Workflow

1. Clone the production profile into a test profile.
2. Apply one category of changes.
3. Validate JSON syntax.
4. Compile the World module.
5. Start a local or staging server.
6. Test the relevant trigger manually.
7. Inspect RPT and Survivor Thoughts debug logs.
8. Run a short multiplayer test.
9. Back up the validated profile.
10. Deploy during a maintenance window.

> Never use production as the first place a new priority map, message pool, journal action, or threshold change is tested.

---

# 16. Quick Reference

## Key profile file

```text
$profile:ZombicideMods/SurvivorThoughts/Configs/09_Admin_Priority_Trigger_System.json
```

## Priority rule

Higher numbers win. Exact thought types are checked before grouped aliases.

## Recommended critical priorities

```text
STAT_STAGE_CRITICAL    95
STAT_MULTI_RED         98
EXPLOSION_HIT          90
DEATH_SPIRAL           90
JOURNAL_SYSTEM        100
```

## Recommended low priorities

```text
OPEN_CLOSE              8–12
PASSIVE                 10
TIME_OF_DAY             15
MOVEMENT                15
INVENTORY_MANAGEMENT    16
```

---

## Support

- Rebirth Network: https://rebirthnetwork.gg
- Discord: https://discord.gg/rebirthnetwork

---

*Created with **DayZ Architect** by [Rebirth Network](https://rebirthnetwork.gg). Need help or feedback? Join our [Discord](https://discord.gg/rebirthnetwork).*
