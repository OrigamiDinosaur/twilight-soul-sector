# Twilight Soul Sector

## Overview 

I have worked in Unreal Engine for around 5 years, but all of my professional work is under NDA, so I can't show any of it off. As such this is an effort to both demonstrate my UE knowledge and improve upon it.

This is a project built on the Gameplay Ability System (GAS). I have chosen to do this for two main reasons. 
1. I love RPGs and so this will keep me interested in the work. 
2. It's something I'm not that familiar with, and I want to keep expanding my knowledge. 

## Current State

I have just completed Stage 1 of my roadmap. 

This entailed creating the foundation for the other stages, primarily:
- Basic Locomotion
- Vital Attributes (Health, Mana, Stamina)
- Basic Abilities	 
- A Dummy to attack
- Functionality to swap out abilities
- Basic HUD
- Consumables 

## Roadmap 

### Stage 2 - Attributes and Experience

While I implemented the basic attributes for Stage 1, Stage 2 will focus on creating an RPG style attribute set.

These attributes will be used to derive the Vital Attributes (Health, Mana, Stamina), as well as how much damage abilities deal, and how much an agent can resist damage.

I do not intend to go crazy with this (at least not for the time being), merely demonstrate my understanding on Primary and Derived attributes, and how to tie them into the greater system. 

I also intend to implement experience and levelling during this stage. Again, I don't intend for this to be overly deep at this stage. Likely a FF style you have X stats at Y level system. 

### Stage 3 - Enemy Behaviours

At this stage enemies will go from stationary dummies to fighting back. 

Enemies will range from stationary 'turret' style enemies, to mobile casters and melee weapon users. 

I intend to use Behaviour Trees primarly for this, as in professional projects we had mostly used C++ state machine based behaviours, and learning is good! 

### Stage 4 - Loot 

A not well defined stage yet, but I hope to have enemies drop potions, and perhaps a currency. 

This stage may feature the ability to buy more powerful abilities, or maybe using a currency to upgrade them. 

### Stage 5 - Completing the Puzzle

The final stage of this project will be slotting all these pieces together to create a simple level, ending in a boss fight. 

## Known Issues / Things to Implement

Audio
- Potion Pickup 
- Ability Equip
- Enemy Hit
- Enemy Die

Animation
- Player locomotion blendstate has issues on diagonals



