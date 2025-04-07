#ifndef PATH_HANDLER_H
#define PATH_HANDLER_H


enum PathType {
    ROOT,
    GAME_BACKGROUND,
    HOME_BACKGROUND,
    DATABASE,
    MOB_PICTURES,
    BLOCK_PICTURES,
    FONTS,
    STYLESHEET
};


char *get_program_path(enum PathType type);


#endif
