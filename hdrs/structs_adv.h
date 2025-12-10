#ifndef STRUCTS_ADV_H
#define STRUCTS_ADV_H

typedef struct _helmet_stats {
    int lvl;
    double exp;
    int defense;
} helmet_stats;

typedef struct _chestplate_stats {
    int lvl;
    double exp;
    int defense;
} chestplate_stats;

typedef struct _armlet_stats {
    int lvl;
    double exp;
    int defense;
} armlet_stats;

typedef struct _boots_stats {
    int lvl;
    double exp;
    int defense;
} boots_stats;

typedef struct _weapon_stats {
    int lvl;
    double exp;
    int physical_dmg;
    int magic_dmg;
    int id_passive;
} weapon_stats;

typedef struct _adv_stats {
    char* name;
    char* class;
    int lvl;
    double exp;
    int max_hp;
    int max_mana;
    int physical_dmg;
    int magic_dmg;
} adv_stats;

typedef struct _adv_moves {
    int id_move1;
    int id_move2;
    int id_move3;
    int id_move4;
} adv_moves;

typedef struct _adv_equipment {
    int id_helmet;
    helmet_stats h_s;
    int id_chestplate;
    chestplate_stats c_s;
    int id_armlet;
    armlet_stats a_s;
    int id_boots;
    boots_stats b_s;
    int id_weapon;
    weapon_stats w_s;
} adv_equipment;

typedef struct _adv {
    int adv_id;
    adv_stats stats;
    adv_moves moves;
    adv_equipment equipment;
} adv;

#endif