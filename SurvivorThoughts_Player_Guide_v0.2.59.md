# Survivor Thoughts — Player Guide v0.2.59

## What is Survivor Thoughts?

**Survivor Thoughts** is an immersion mod for DayZ.

It adds internal thoughts to your survivor based on what is happening to you, where you are, what you are doing, and what your character has survived.

You may see thoughts when you are:

```txt
Hungry
Thirsty
Cold
Hot
Sick
Bleeding
Low on blood
In shock
Injured
Near infected
Near corpses
In bad weather
Moving at night
Inside dangerous areas
Using items
Taking damage
Travelling with others
Alone for too long
Losing sanity
Recovering from danger
```

The mod is designed to feel like old-school DayZ internal status messages, but with more personality and memory.

---

## First spawn journal setup

When you first join with a new survivor, you may be shown a **Survivor Journal setup menu**.

This happens before normal gameplay begins.

While the setup menu is active:

```txt
You are protected from damage.
Normal Survivor Thoughts messages are suppressed.
The menu will reopen if closed before completion.
Normal gameplay begins after you confirm your journal.
```

This prevents you from being attacked or killed while filling in your survivor’s backstory.

---

## What you choose in the setup menu

You may be asked to choose or enter details such as:

```txt
Survivor name
Origin
Former occupation
Core trait
Biggest fear
Current goal
Useful skill
Weakness
Moral code
```

These choices help create your character’s journal identity and backstory.

Example:

```txt
Elias came from Chernarus, once working as a rail worker.
He was practical, but afraid of dying alone.
He knows how to repair engines, but takes unnecessary risks.
His rule is simple: trust must be earned.
Now he is looking for somewhere safe enough to sleep.
```

Your server owner may change the available options.

---

## The Survivor Journal item

Your survivor can receive a physical **Survivor Journal** item.

The journal is an identity item.

How it works:

```txt
It is auto-equipped to your character.
It stays with you while you are alive.
It cannot normally be removed while you are alive.
It becomes lootable after death.
It records your survivor’s story over time.
```

If another player finds your body, they may be able to read your journal, depending on server settings.

---

## What the journal records

The journal can record important events from your life.

Examples:

```txt
Your setup/backstory choices
Major injuries
Bleeding events
Near-death moments
Survival crises
Recoveries
Social/group events
Companion deaths
Sanity/cannibalism events
Disease events
Dangerous places visited
Custom server story zones
Final death entry
```

The goal is that your character becomes more than just loot. Their journal becomes a story of what happened to them.

---

## Thoughts during survival

You may see thoughts when your survival stats change.

Examples:

```txt
"I need food now."
"My mouth is too dry."
"My hands are getting stiff."
"I am running out faster than I can stop it."
"The fever is not breaking."
```

The mod can detect severe combinations too.

Examples:

```txt
Low food + health dropping = starving to death
Low water + health dropping = dehydration death
Extreme cold + health dropping = freezing to death
Extreme heat + health dropping = overheating death
Bleeding + low blood = serious blood loss
Cold + wet + night = dangerous exposure
```

---

## Action thoughts

Some actions can trigger immediate thoughts.

Examples:

```txt
Eating
Drinking
Bandaging
Repairing
Fishing
Lighting fires
Opening doors
Using medicine
Skinning animals
Skinning humans
Managing weapons or ammo
```

Door/open-close thoughts have a short cooldown so they should not spam every door.

Repeated actions are also protected by a duplicate-message blocker.

---

## Damage and bleeding thoughts

The mod can react immediately to danger.

Examples:

```txt
Zombie hit
Player melee hit
Gunshot hit
Explosion hit
Heavy hit
Bleeding started
Bleeding got worse
Bleeding stopped
```

Examples of messages:

```txt
"They hit me."
"I am bleeding."
"That shot opened me up."
"The bleeding stopped. I can think again."
```

---

## Weather and time of day

Your survivor can react to the world.

Weather thoughts may include:

```txt
Clear weather
Overcast
Light rain
Heavy rain
Fog
Wind
Storm
```

Time thoughts may include:

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

Example:

```txt
"The dark makes every sound feel closer."
```

---

## Locations and custom areas

Your server may configure location-based thoughts for areas like:

```txt
Coast
Town
City
Forest
Wilderness
Military base
Police station
Hospital
Industrial area
Farm
Water source
```

Admins can also create custom lore zones.

Example:

```txt
"Something is wrong with this place."
```

---

## Items and corpses

Your survivor can notice badly damaged gear.

Examples:

```txt
"This weapon needs attention."
"My boots are falling apart."
"This gear will not last much longer."
```

Your survivor can also react to nearby corpses:

```txt
"Someone died here recently."
"Where there is one corpse, there may be another."
```

---

## Personality and mental state

Your survivor can have a personality profile and a changing mental state.

Personality styles may include:

```txt
Practical
Scared
Military
Hopeless
Aggressive
Calm
```

Mental states may include:

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

Your character may feel different after long-term danger, injury, isolation, or traumatic actions.

---

## Sanity and cannibalism creep

Some servers may enable sanity tracking.

Disturbing actions such as skinning humans or eating human meat can affect your survivor.

You may see darker thoughts such as:

```txt
"I should not think about what I have done."
"Their faces keep coming back when I close my eyes."
"The giggling... I can hear it even when I am not laughing."
"I crossed something I cannot uncross."
```

This does not mean you are banned or punished. It is part of the character story system.

---

## Social and group thoughts

The mod can notice if you travel near another player for long enough.

That player may become a temporary companion in your character’s mind.

You may see thoughts like:

```txt
"Another set of eyes makes the road feel shorter."
"Stay close. Wandering off gets people killed."
```

If a companion is shot or dies nearby, your survivor may react:

```txt
"No, no, no. Stay with me."
"I am completely on my own now."
```

If you have not seen another player for a long time, you may see lone-wolf thoughts:

```txt
"I have not talked to anyone in days."
"I am starting to forget what my own voice sounds like."
```

---

## Pet dog thoughts

If the server runs DayZ-Dog integration, Survivor Thoughts may add dog-related thoughts.

Possible dog thoughts include:

```txt
Nearby dog
Feeding dog
Taming dog
Dog follow command
Dog stay command
Bandaging dog
Summoning dog
Dog companion moments
```

Example:

```txt
"At least the dog still trusts me."
```

This depends on server settings and whether the dog mod is installed.

---

## Recovery thoughts

Survivor Thoughts does not only talk when things are bad. It can also notice recovery.

Examples:

```txt
"The bleeding stopped. I can think again."
"My hands are warming up."
"Daylight. I made it."
"I am not safe, but I am still here."
```

---

## Why some messages may not appear

The mod uses priority and cooldown systems.

A message may not appear because:

```txt
A more important thought recently happened.
The same exact message appeared too recently.
The system is on cooldown.
Your journal setup is not complete.
The server owner disabled that message category.
The chance roll did not trigger.
```

For example, if you start bleeding, the mod may block a low-priority weather thought for a few seconds.

That is intentional.

---

## Can I remove my journal?

Usually, no.

The Survivor Journal is meant to stay with your character while alive.

It normally becomes removable/lootable after death.

This is intentional so the journal acts like your survivor’s identity and story item.

---

## Does the journal save forever?

Your server saves journal/backstory data in mission storage. Server owners control how long this data remains and whether wipes remove it.

A server wipe may reset your journal history.

---

## Roleplay tips

Use your journal choices to create a character you can actually play.

Good examples:

```txt
A scared medic who refuses to abandon people.
A practical mechanic who trusts nobody.
A calm hunter who is terrified of cities.
A former soldier trying not to become violent again.
A drifter whose only rule is to keep moving.
```

The mod will build from those choices as you survive.

---

## What this mod does not do

Survivor Thoughts does not normally add:

```txt
Traders
Overpowered gear
Map markers
Safe zones
Quest markers
Arcade abilities
```

It is mainly an immersion, story, and atmosphere mod.

---

## Best way to experience it

Play normally.

Let the thoughts and journal build naturally.

Your story will come from:

```txt
What you survive
Who you travel with
What you lose
What you do when desperate
Where you die
What someone finds on your body
```

---
*Created with **DayZ Architect** by [Rebirth Network](https://rebirthnetwork.gg). Need help or feedback? Join our [Discord](https://discord.gg/rebirthnetwork).*
