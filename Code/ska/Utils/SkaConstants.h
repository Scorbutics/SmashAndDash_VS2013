#ifndef NDEBUG
#define SKA_DEBUG_GRAPHIC
#define SKA_DEBUG_LOGS
#endif

/* DEBUG CONF */
#undef SKA_DEBUG_GRAPHIC
/* END DEBUG CONF*/

#define FILE_SEPARATOR "/"
#define NOSUCHFILE "."FILE_SEPARATOR"Sprites"FILE_SEPARATOR"nosuchfile.png"
#define SPRITEBANK_ANIMATION 0
#define SPRITEBANK_SKILL 1
#define SPRITEBANK_PHYSIC 2
#define SPRITEBANK_FACESET 3
#define SPRITEBANK_CHARSET 4
#define SPRITEBANK_PARTICLE 5
#define SPRITEBANK_NUMBER 6

#define SPRITEBANK_PATH_DIR "."FILE_SEPARATOR"Sprites"FILE_SEPARATOR
#define SPRITEBANK_PATH_ANIMATION SPRITEBANK_PATH_DIR"Animations"
#define SPRITEBANK_PATH_SKILL SPRITEBANK_PATH_DIR"Fight"
#define SPRITEBANK_PATH_PHYSIC SPRITEBANK_PATH_DIR"Physics"
#define SPRITEBANK_PATH_FACESET SPRITEBANK_PATH_DIR"Facesets"
#define SPRITEBANK_PATH_CHARSET SPRITEBANK_PATH_DIR"Charsets"
#define SPRITEBANK_PATH_PARTICLE SPRITEBANK_PATH_DIR"Particles"

#define P_DEFINED 2 //Path d�fini
#define P_RANDOM 3//ou al�atoire
#define P_FIXED 1 //ou encore fixe

//Transparence non alpha (couleur sous forme RVB)
#define DEFAULT_T_RED 190 
#define DEFAULT_T_GREEN 151
#define DEFAULT_T_BLUE 255

#define PARTICLE 0

#define PARTICLE_GRAVITY 0
#define PARTICLE_LINEAR 1

#define PARTICLE_STATE_LAUNCHED 1
#define PARTICLE_STATE_CREATED 0
#define PARTICLE_STATE_SPLASH 2
#define PARTICLE_STATE_END 3

#define PARTICLE_MANAGER_RAIN 0
#define PARTICLE_MANAGER_CRUMBLING 1
#define PARTICLE_MANAGER_EFFECT 2

#define EARTH_GRAVITY 9.81

#define BLOCK_ID_AIR INT16_MAX
#define BLOCK_ID_GRASS 363
#define BLOCK_ID_WATER_1 120
#define BLOCK_ID_WATER_2 121
#define BLOCK_ID_WATER_3 122

#define BLOCK_PROP_NONE 0
#define BLOCK_PROP_WATER 1
#define BLOCK_PROP_JUMPWALL 2
#define BLOCK_PROP_WIND_SENSITIVITY 3

#define BLOCK_COL_NO 0
#define BLOCK_COL_YES 1
#define BLOCK_COL_VOID 2

#define WIND_STOP 0
#define WIND_LEFT 1
#define WIND_RIGHT 2
#define WIND_NEUTRAL 3

#define EVENT_MOUSE 0
#define EVENT_KEYBOARD 1

#define SPRITE_ID_SHADOW 13

#define DEFAULT_FONT_FILE "."FILE_SEPARATOR"Polices"FILE_SEPARATOR"pkmndp.ttf"