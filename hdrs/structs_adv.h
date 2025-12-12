#ifndef STRUCTS_ADV_H
#define STRUCTS_ADV_H

typedef struct _helmet_stats {
    char name[30];
    int lvl;
    double exp;
    int defense;
} helmet_stats;

typedef struct _chestplate_stats {
    char name[30];
    int lvl;
    double exp;
    int defense;
} chestplate_stats;

typedef struct _armlet_stats {
    char name[30];
    int lvl;
    double exp;
    int defense;
} armlet_stats;

typedef struct _boots_stats {
    char name[30];
    int lvl;
    double exp;
    int defense;
} boots_stats;

typedef struct _weapon_stats {
    char name[30];
    int lvl;
    double exp;
    int physical_dmg;
    int magic_dmg;
    int passive_id;
} weapon_stats;

typedef struct _stats {
    char name[30];
    char class[30];
    int lvl;
    double exp;
    int max_hp;
    int max_mana;
    int physical_dmg;
    int magic_dmg;
} stats;

typedef struct _moves {
    int move1_id;
    int move2_id;
    int move3_id;
    int move4_id;
} moves;

typedef struct _equipment {
    helmet_stats h_s;
    chestplate_stats c_s;
    armlet_stats a_s;
    boots_stats b_s;
    weapon_stats w_s;
} equipment;

typedef struct _adv {
    int adv_id;
    stats* stats;
    moves* moves;
    equipment* equipment;
} adv;

#endif