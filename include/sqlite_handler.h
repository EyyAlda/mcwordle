#ifndef SQLITE_HANDLER_H
#define SQLITE_HANDLER_H


struct MobQueryData {
    char *name;
    char *version;
    char *height;
    char *health;
    char *class;
    char *behavior;
    char *spawn;
    char *picture_path;
    struct MobQueryData *next;
};

struct MobQueryData* get_search_results(const char *text);
int clear_search_result_data(struct MobQueryData* mob_query_data);
struct MobQueryData* select_random_Mob();
#endif
