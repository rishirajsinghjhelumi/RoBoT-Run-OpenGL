#define PI 3.141592653589
#define DEG2RAD(deg) (deg * PI / 180)
#define MAX 100
#define INF 1<<20
#define EPS 0.001
#define SQRT2 1.41421356237
#define GRAVITY 9.80665

#if !defined(GL_TEXTURE_MAX_ANISOTROPY_EXT)
#define GL_TEXTURE_MAX_ANISOTROPY_EXT 0x84FE
#define GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT 0x84FF
#endif

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

#define FIRST_PERSON 1
#define THIRD_PERSON 2
#define WORLD_VIEW 3
#define TOWER_VIEW 4
#define TILE_VIEW 5
#define CENTER_TOWER_VIEW 6
#define HELICOPTOR_VIEW 7

#define MAGNET 0
#define SPEED 1
#define INVISIBLE 2

#define FIRE 0
#define LASER 1

using namespace std;

int screen_width;
int screen_height;
float window_width;
float window_height;

struct vector3d
{
    float x;
    float y;
    float z;
};
typedef struct vector3d vector3d;

struct vector2d
{
    int x;
    int z;
};
typedef struct vector2d vector2d;

float rot_x = -10.0;
float rot_y = 0.0;
float rot_z = 0.0;

float WHITE[] = {1,1,1};
float BLACK[] = {0,0,0};
float RED[] = {1,0,0};
float GREEN[] = {0,1,0};

GLfloat redDiffuseMaterial[] = {1.0, 0.0, 0.0};
GLfloat whiteSpecularMaterial[] = {1.0, 1.0, 1.0};
GLfloat greenEmissiveMaterial[] = {0.0, 1.0, 0.0};
GLfloat whiteSpecularLight[] = {1.0, 1.0, 1.0};
GLfloat blackAmbientLight[] = {0.0, 0.0, 0.0};
GLfloat whiteDiffuseLight[] = {1.0, 1.0, 1.0};
GLfloat blankMaterial[] = {0.0, 0.0, 0.0};
GLfloat mShininess[] = {128};

int no_lane_x=1,no_lane_z=10;
float lane_width_x=45,lane_depth_z=180;
float world_rotate = 0.0;
float movement_angle = 0.0;
float movement_direction_angle = 0.0;
int game_start = 0;

float r_x=lane_width_x,r_y=0.0,r_z=0.0;

vector3d current_origin;

int generate_lane = 0;
int available_lane[3] = {1,0,0};
int selected_lane = UP;
int lane_selection_done = 0;
int check_selected_lane = 0;
int lane_changed = 0;
int prev_selected = UP;
int change_lane = 0;
int first_world_load = 0;

int texture;
int texture1;

int texture_track[5];
int texture_side[5];
int texture_background[5];
int texture_boundary[5];
int world_choosen = 1;
int temp_world_choosen[3];
int new_world_choosen = 0;
int world_crossed = 0;

int coin_texture;
int magnet_texture;
int invisible_texture;
int speed_texture;
int gem_texture;
int wood_texture;
int fire_texture;
int laser_texture;
int metal_texture;

float gem_rotate = 0.0;

int robot_rotation = 0;
float rotation_angle = 0.0;

int robot_direction = UP;
int robot_movement_direction = UP;
int robot_motion = 0;
float robot_motion_timer = 10.0;
float robot_velocity = 30.0;
int direction_keys[4][4] =
{
    {GLUT_KEY_UP,GLUT_KEY_DOWN,GLUT_KEY_LEFT,GLUT_KEY_RIGHT},
    {GLUT_KEY_DOWN,GLUT_KEY_UP,GLUT_KEY_RIGHT,GLUT_KEY_LEFT},
    {GLUT_KEY_LEFT,GLUT_KEY_RIGHT,GLUT_KEY_DOWN,GLUT_KEY_UP},
    {GLUT_KEY_RIGHT,GLUT_KEY_LEFT,GLUT_KEY_UP,GLUT_KEY_DOWN}
};
int direction[4][4] =
{
    {UP,DOWN,LEFT,RIGHT},
    {DOWN,UP,RIGHT,LEFT},
    {LEFT,RIGHT,DOWN,UP},
    {RIGHT,LEFT,UP,DOWN}
};
float direction_angles[4][4] =
{
    {0.0,180.0,-90.0,90.0},
    {180.0,0.0,90.0,-90.0},
    {-90.0,90.0,180.0,0.0},
    {90.0,-90.0,0.0,180.0}
};

int robot_jump = 0;
float jump_translate_x = 0.0;
float jump_translate_z = 0.0;
float jump_translate_y = 0.0;
float jump_velocity = 30.0;
float jump_update_time = 0.25;

int robot_slide = 0;
float slide_angle = 90.0;

int view_mode = THIRD_PERSON;

float tower_view_angle = 180.0;
float center_tower_view_angle = 180.0;

float helicoptor_view_angle = 180.0;
float helicoptor_angle = 90.0;
int helicoptor_moveX = 0;
int helicoptor_moveY = 0;

int tile_num_width = 1;
int tile_num_depth = 1;
float tile_view_angle = 0.0;

float mouse_posX;
float mouse_posY;
float mouse_posZ;

float zoom_camera = 0.1;

vector3d player_position;

float coin_rotate = 0.0;
int coins_collected = 0;
int coin_multiplier = 1;
vector3d coin_pattern[3][15];
int coin_selected_pattern = 0;
int coin_apply_pattern = 0;
int coinX = 0;
float coinZ = 0;
int coin_available[15];
vector3d coin_positions[15];
int coins_num = 15;

int power_choosen = 0;
int power_available = 0;
vector3d power_position;
int power_taken = 0;

vector3d obstacle_wood_position[3];
int obstacle_wood_num = 0;
vector3d obstacle_laser_position[3];
int obstacle_laser_num = 0;

float magnet_factor = 60.0;

float glow_value = 0.05;

int falling = 0;
float fall_height;

vector3d humanoid_prev_loc;
vector3d prev_r;
vector2d prev_block;
