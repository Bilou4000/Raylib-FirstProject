#pragma once

#include <iostream>
#include <vector>
using namespace std;

static Ability BodySlam = Ability("BodySlam", 85, PokeType::Normal, 1);
static Ability FireSpin = Ability("FireSpin", 35, PokeType::Fire, 3);
static Ability WaterShuriken = Ability("WaterShuriken", 15, PokeType::Water, 5);
static Ability GigaDrain = Ability("GigaDrain", 75, PokeType::Grass, 2);
static Ability Thunder = Ability("Thunder", 110, PokeType::Electric, 1);
static Ability IcyWind = Ability("IcyWind", 55, PokeType::Ice, 2);
static Ability RollingKick = Ability("RollingKick", 60, PokeType::Fighting, 2);
static Ability Acid = Ability("Acid", 40, PokeType::Poison, 4);
static Ability Dig = Ability("Dig", 80, PokeType::Ground, 1);
static Ability Aeroblast = Ability("Aeroblast", 100, PokeType::Flying, 1);
static Ability Confusion = Ability("Confusion", 50, PokeType::Psychic, 2);
static Ability UTurn = Ability("UTurn", 70, PokeType::Bug, 2);
static Ability Accelerock = Ability("Accelerock", 40, PokeType::Rock, 3);
static Ability MenacingMoonrazeMaelstrom = Ability("MenacingMoonrazeMaelstrom", 200, PokeType::Ghost, 1);
static Ability RoarOfTime = Ability("RoarOfTime", 150, PokeType::Dragon, 1);
static Ability Pursuit = Ability("Pursuit", 40, PokeType::Dark, 3);
static Ability MetalClaw = Ability("MetalClaw", 50, PokeType::Steel, 2);
static Ability LetsSnuggleForever = Ability("LetsSnuggleForever", 190, PokeType::Fairy, 1);

static vector<Ability> allAbility = { BodySlam, FireSpin, WaterShuriken, GigaDrain, Thunder, IcyWind, RollingKick, Acid, Dig,
Aeroblast, Confusion, UTurn, Accelerock, MenacingMoonrazeMaelstrom, RoarOfTime, Pursuit, MetalClaw, LetsSnuggleForever };
