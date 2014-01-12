class Tile_Camera
{
    float camera_posX;
    float camera_posY;
    float camera_posZ;
    float look_posX;
    float look_posY;
    float look_posZ;
    float up_posX;
    float up_posY;
    float up_posZ;

public:

    void get_camera_pos(int x,int z,World world)
    {
        camera_posX = world.get_tile_center_x(x);
        camera_posY = 10;
        camera_posZ = world.get_tile_center_z(z) - 85;
        look_posX = camera_posX + 10*sin(DEG2RAD(tile_view_angle));
        look_posY = 10;
        look_posZ = camera_posZ + 10*cos(DEG2RAD(tile_view_angle));
        if(world.moving[x][z])
            camera_posY += world.block_motion_value[x][z];
        look_posY = camera_posY;
    }

    void init_camera(int x,int z,World world)
    {
        get_camera_pos(x,z,world);
        gluLookAt(camera_posX,camera_posY,camera_posZ,
                  look_posX,look_posY,look_posZ,
                  0,1,0);
    }
};

class Tower_Camera
{
    float camera_posX;
    float camera_posY;
    float camera_posZ;
    float look_posX;
    float look_posY;
    float look_posZ;
    float radius;

public:

    void get_camera_pos(World world)
    {
        radius = world.get_center_x()>world.get_center_z()?world.get_center_x():world.get_center_z();
        radius = radius * SQRT2;
        camera_posX = world.get_center_x()+radius*sin(DEG2RAD(tower_view_angle))*SQRT2;
        camera_posY = radius;
        camera_posZ = world.get_center_z()+radius*cos(DEG2RAD(tower_view_angle))*SQRT2;
        look_posX = world.get_center_x();
        look_posY = 0;
        look_posZ = world.get_center_z();
    }

    void init_camera(World world)
    {
        get_camera_pos(world);
        gluLookAt(camera_posX,camera_posY,camera_posZ,
                  look_posX,look_posY,look_posZ,
                  0,1,0);
    }
};

class World_Camera
{
    float camera_posX;
    float camera_posY;
    float camera_posZ;
    float look_posX;
    float look_posY;
    float look_posZ;

public:

    void get_camera_pos()
    {
        camera_posX = 200+r_x/2+jump_translate_x/2.0;
        camera_posY = 200+jump_translate_y/2.0;
        camera_posZ = -200+r_z/2+jump_translate_z/2.0;
        look_posX = 120+r_x/2+jump_translate_x/2.0;
        look_posY = jump_translate_y/2.0;
        look_posZ = -35+r_z/2+jump_translate_z/2.0;
    }

    void init_camera()
    {
        get_camera_pos();
        gluLookAt(camera_posX,camera_posY,camera_posZ,
                  look_posX,look_posY,look_posZ,
                  0,1,0);
    }
};

class First_Person_Camera
{
    float camera_posX;
    float camera_posY;
    float camera_posZ;
    float look_posX;
    float look_posY;
    float look_posZ;

public:

    void get_camera_pos(float ba)
    {
        camera_posX = r_x/2+jump_translate_x/2.0;
        camera_posY = 19.5 + jump_translate_y/2.0;
        camera_posZ = r_z/2+jump_translate_z/2.0 - 85 + 20;
        look_posX = r_x/2+jump_translate_x/2.0-20*sin(DEG2RAD(ba));
        look_posY = 12 + jump_translate_y/2.0;
        look_posZ = r_z/2+jump_translate_z/2.0+20*cos(DEG2RAD(ba))-85 + 20;
        if(detect_is_on_moving_block(humanoid,world))
        {
            vector2d block_num = get_humanoid_block(humanoid,world);
            camera_posY += world.block_motion_value[block_num.x][block_num.z];
            look_posY += world.block_motion_value[block_num.x][block_num.z];
        }
    }

    void init_camera(float ba)
    {
        get_camera_pos(ba);
        gluLookAt(camera_posX,camera_posY,camera_posZ,
                  look_posX,look_posY,look_posZ,
                  0,1,0);
    }
};

class Center_Tower_Camera
{
    float camera_posX;
    float camera_posY;
    float camera_posZ;
    float look_posX;
    float look_posY;
    float look_posZ;
    float radius;

public:

    void get_camera_pos(World world)
    {
        radius = world.get_center_x()>world.get_center_z()?world.get_center_x():world.get_center_z();
        camera_posX = world.get_center_x();
        camera_posY = radius*SQRT2;
        camera_posZ = world.get_center_z();
        look_posX = world.get_center_x()+radius*sin(DEG2RAD(center_tower_view_angle));
        look_posY = 0.0;
        look_posZ = world.get_center_z()+radius*cos(DEG2RAD(center_tower_view_angle));
    }

    void init_camera(World world)
    {
        get_camera_pos(world);
        gluLookAt(camera_posX,camera_posY,camera_posZ,
                  look_posX,look_posY,look_posZ,
                  0,1,0);
    }
};

class Third_Person_Camera
{
    float camera_posX;
    float camera_posY;
    float camera_posZ;
    float look_posX;
    float look_posY;
    float look_posZ;

public:

    void get_camera_pos(float ba)
    {
        camera_posX = r_x/2+jump_translate_x/2.0  + 5*sin(DEG2RAD(ba));
        camera_posY = 17.0 + jump_translate_y/2.0;
        camera_posZ = r_z/2+jump_translate_z/2.0 - 5*cos(DEG2RAD(ba));
        look_posX = r_x/2+jump_translate_x/2.0;
        look_posY = jump_translate_y/2.0 + 15;
        look_posZ = r_z/2+jump_translate_z/2.0;
        if(falling)
            camera_posY = look_posY + abs(jump_translate_y/2.0);
        if(detect_is_on_moving_block(humanoid,world))
        {
            vector2d block_num = get_humanoid_block(humanoid,world);
            camera_posY += world.block_motion_value[block_num.x][block_num.z];
            look_posY += world.block_motion_value[block_num.x][block_num.z];
        }
    }

    void init_camera(float ba)
    {
        get_camera_pos(ba);
        if(falling)
            glRotatef(-90,1,0,0);
        gluLookAt(camera_posX,camera_posY,camera_posZ,
                  look_posX,look_posY,look_posZ,
                  0,1,0);
    }
};

class Helicoptor_Camera
{
    float camera_posX;
    float camera_posY;
    float camera_posZ;
    float look_posX;
    float look_posY;
    float look_posZ;
    float radius;

public:

    void get_camera_pos()
    {
        radius = world.get_center_x()>world.get_center_z()?world.get_center_x():world.get_center_z();
        radius = radius * SQRT2;
        camera_posX = world.get_center_x()+radius*sin(DEG2RAD(helicoptor_view_angle))*SQRT2;
        camera_posY = radius * ( 1 - cos(DEG2RAD(helicoptor_angle)) );
        camera_posZ = world.get_center_z()+radius*cos(DEG2RAD(helicoptor_view_angle))*SQRT2;
        look_posX = world.get_center_x();
        look_posY = 0;
        look_posZ = world.get_center_z();
    }

    void init_camera()
    {
        get_camera_pos();
        gluLookAt(camera_posX,camera_posY,camera_posZ,
                  look_posX,look_posY,look_posZ,
                  0,1,0);
    }
};
