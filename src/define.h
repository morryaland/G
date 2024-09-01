#include <SDL2/SDL_image.h>

#define img(a) IMG_Load(a)

#define IMG_FILE_FORMAT ".gif"
#define MAP_FILE_FORMAT ".xml"
#define ASSETS_DIR "./assets/"
#define LOCATION_DIR "locations/"

/* IMG */
#define IMG_ERROR          img("")
#define IMG_PLAYER_FORWARD img("")
#define IMG_PLAYER_LEFT    img("")
#define IMG_PLAYER_RIGHT   img("")
#define IMG_PLAYER_BACK    img("")

/* ID */
#define ENTITY_MAX 1024
#define ID_ERROR  0
#define ID_PLAYER 1
