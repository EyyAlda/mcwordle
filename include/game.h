#ifndef GAME_H
#define GAME_H

typedef struct {
    char *name;
    char *version;
    float height;
    int behavior;
    char *spawn;
    int class;
    int health;
    char *picture_path;
} MinecraftMob;

typedef struct {


} MinecraftBlock;

struct MobDataAccess{
    MinecraftMob *mob_data_pointer;
    struct MobDataAccess *next;
};

int array();

int get_mob_counter();

char ***get_mob_data();

int unref_mob_data();
#endif
