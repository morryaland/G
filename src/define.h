#include <SDL2/SDL_image.h>

#define IMG_FILE_FORMAT ".gif"
#define MAP_FILE_FORMAT ".xml"
#define ASSETS_DIR "./assets/"
#define LOCATION_DIR "locations/"
#define ENTITY_DIR "entities/"
#define PLAYER_DIR "player/"

#define NAME_MAX 64
#define PATH_MAX 256
#define PLAYER_SPRITE 4

#define img(a) IMG_Load(a)
