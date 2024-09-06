#include <SDL2/SDL_image.h>

#define IMG_FILE_FORMAT ".gif"
#define MAP_FILE_FORMAT ".xml"
#define ASSETS_DIR "./assets/"
#define LOCATION_DIR "locations/"
#define ENTITY_DIR "entities/"

#define img(a) IMG_Load(a)
#define limg(a) IMG_Load( ASSETS_DIR LOCATION_DIR a IMG_FILE_FORMAT )
#define eimg(a) IMG_Load( ASSETS_DIR ENTITY_DIR a IMG_FILE_FORMAT )

/* IMG */
#define IMG_ERROR          eimg("ERROR/ERROR")
#define IMG_PLAYER_FORWARD eimg("ERROR/ERROR")
#define IMG_PLAYER_LEFT    eimg("ERROR/ERROR")
#define IMG_PLAYER_RIGHT   eimg("ERROR/ERROR")
#define IMG_PLAYER_BACK    eimg("ERROR/ERROR")

/* ID */
#define ENTITY_MAX 1024
#define ID_ERROR  0
#define ID_PLAYER 1

/* NAME */
#define NAME_ERROR "ERROR"
#define NAME_PLAYER "player"
