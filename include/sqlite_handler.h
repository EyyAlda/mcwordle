#ifndef SQLITE_HANDLER_H
#define SQLITE_HANDLER_H

struct MobQueryData {
    const char *name;
    const char *version;
    const char *height;
    const char *health;
    const char *class;
    const char *behavior;
    const char *spawn;
    const char *picture_path;
    struct MobQueryData *next;
};

struct MobQueryData* get_search_results(const char *text);

int clear_search_result_data(struct MobQueryData* mob_query_data);

#endif
