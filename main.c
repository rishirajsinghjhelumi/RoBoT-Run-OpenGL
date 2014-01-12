#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<time.h>
#include<GL/glx.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>

//#include<AL/alut.h>
//#include<AL/al.h>
//#include<AL/alc.h>

#include<X11/X.h>
#include<X11/keysym.h>

#include "functions.h"
#include "variable.h"

#include "texture.h"

#include "humanoid.h"
Humanoid humanoid;

#include "init.h"
#include "world.h"

#include "powers.h"
#include "obstacles.h"

World world(no_lane_x,no_lane_z,lane_width_x,lane_depth_z);
World temp_world[3];

#include "mouse.h"
#include "collision.h"
#include "camera.h"

Tile_Camera tile_camera;
Tower_Camera tower_camera;
World_Camera world_camera;
First_Person_Camera first_person_camera;
Third_Person_Camera third_person_camera;
Helicoptor_Camera helicoptor_camera;
Center_Tower_Camera center_tower_camera;

Magnet magnet;
Invisible invisible;
Speed speed;
Gem gem;
Hurdle hurdle;

float lta = 0.0;
float rta = 0.0;
float lta_x = 0.0;
float rta_x = 0.0;
float lsa = 0.0;
float rsa = 0.0;
float lea = 0.0;
float rea = 0.0;
float lka = 0.0;
float rka = 0.0;
float ba = 0.0;
float px,pz,py;


void print_collected_coins(float x, float y, void *font, const char* string)
{
    glNormal3f(0,0,1);
    glRasterPos2f(x, y);
    int len = strlen(string);
    for(int i=0; i<len; i++)
        glutBitmapCharacter(font, string[i]);
    char coin_string[10];
    coin_string[0] = '0';
    int distance_travelled = coins_collected%500;
    if(distance_travelled == 0 && coins_collected !=0)
        coin_multiplier += 1;
    coins_collected += coin_multiplier;
    int k = 0,num = coins_collected;
    while(num)
    {
        coin_string[k++] = num%10 + '0';
        num /= 10;
    }
    if(k)
        while(k-->0)
            glutBitmapCharacter(font, coin_string[k]);
    else
        glutBitmapCharacter(font, '0');
}

void make_humanoid()
{
    glPushMatrix();

    glScalef(0.5,0.5,0.5);

    prev_block = get_humanoid_block(humanoid,world);

    humanoid.loc_x = r_x + jump_translate_x;
    humanoid.loc_y = world.height + r_y + jump_translate_y;
    if(robot_slide)
        humanoid.loc_y -= world.height;

    humanoid.loc_z = r_z + jump_translate_z;


    //detect_boundary_collision(humanoid,world);
    if( !(power_taken == 1 && ( power_choosen == SPEED || power_choosen == INVISIBLE) ) )
        detect_missing_blocks_collision(humanoid,world);
    //if(detect_is_on_moving_block(humanoid,world))
    //{
    //    vector2d block_num = get_humanoid_block(humanoid,world);
    //    humanoid.loc_y += world.block_motion_value[block_num.x][block_num.z]*2.0;
    //}
    //collect_coins(humanoid,world);
    /*if(prev_r.x!=humanoid.loc_x || prev_r.y!=humanoid.loc_y || prev_r.z!=humanoid.loc_z)
    printf("H == %f %f %f\n",humanoid.loc_x,humanoid.loc_y,humanoid.loc_z);
    prev_r.x = humanoid.loc_x;
    prev_r.y = humanoid.loc_y;
    prev_r.z = humanoid.loc_z;*/
    coin_detection();
    power_detection();
    obstacle_detection();

    if(!robot_jump)
        px = r_x,pz = r_z,py=r_y;
    humanoid.body(humanoid.loc_x,humanoid.loc_y + 22.5 +(robot_slide?world.height:0),humanoid.loc_z,ba,lsa,lea,rsa,rea,lta,lka,rta,rka,lta_x,rta_x);

    glPopMatrix();
}

void select_camera()
{
    if(view_mode == THIRD_PERSON)
    {
        third_person_camera.init_camera(ba);
    }
    else if(view_mode == FIRST_PERSON)
    {
        glTranslatef(0,0,85);
        first_person_camera.init_camera(ba);
        glTranslatef(0,0,-85);
    }
    else if(view_mode == WORLD_VIEW)
    {
        glTranslatef(0,0,85);
        world_camera.init_camera();
        glTranslatef(0,0,-85);
    }
    else if(view_mode == TOWER_VIEW)
    {
        tower_camera.init_camera(world);
    }
    else if(view_mode == CENTER_TOWER_VIEW)
    {
        center_tower_camera.init_camera(world);
    }
    else if(view_mode == TILE_VIEW)
    {
        glTranslatef(0,0,85);
        tile_camera.init_camera(tile_num_width,tile_num_depth,world);
        glTranslatef(0,0,-85);
    }
    else if(view_mode == HELICOPTOR_VIEW)
    {
        glTranslatef(0,0,-zoom_camera);
        helicoptor_camera.init_camera();
    }
}

void background()
{
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
    glBindTexture( GL_TEXTURE_2D, texture_background[world_choosen]);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,1,1,0,-1,1);

    float factorZ = 1.0;
    float factorX = 1.0;

    glBegin(GL_QUADS);
    glTexCoord2f(0,0);
    glVertex2f(0, 0);
    glTexCoord2f(0,factorZ);
    glVertex2f(0,factorZ);
    glTexCoord2f(factorX,factorZ);
    glVertex2f(factorX, factorZ);
    glTexCoord2f(factorX,0);
    glVertex2f(factorX, 0);
    glEnd();

    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);
    glDisable(GL_TEXTURE_2D);

}

void turn_robot(int value);
void turn_robot_lane(int value);

void make_coins()
{
    if(coin_apply_pattern)
    {
        if(coin_selected_pattern == 1)
            world.gen_coins_pattern(1,8,15,120);
        else if(coin_selected_pattern == 0)
            world.gen_coins_pattern(0,coinX*15 + 7.5,15,coinZ*100 + 300);
        else
            world.gen_coins_pattern(2,coinX*15 + 7.5,15,coinZ*150 + 300);
    }
}

void make_power()
{
    if(power_available == 0 || power_taken)
        return;
    glPushMatrix();

    if(power_choosen == MAGNET)
    {
        magnet.design(8,power_position.x,power_position.y,power_position.z);
    }

    else if(power_choosen == SPEED)
    {
        speed.design(5,power_position.x,power_position.y,power_position.z);
    }

    else if(power_choosen == INVISIBLE)
    {
        invisible.design(5,power_position.x,power_position.y,power_position.z);
    }

    glPopMatrix();
}

void make_obstacle()
{
    for(int i=0;i<obstacle_wood_num;i++)
    {
        glPushMatrix();
        hurdle.draw_fire_obstacle(lane_width_x/16.0,lane_width_x/16.0,20,obstacle_wood_position[i].x,obstacle_wood_position[i].y,obstacle_wood_position[i].z);
        glPopMatrix();
    }
    for(int i=0;i<obstacle_laser_num;i++)
    {
        glPushMatrix();
        hurdle.draw_laser_obstacle(lane_width_x/16.0,lane_width_x/16.0,20,obstacle_laser_position[i].x,obstacle_laser_position[i].y,obstacle_laser_position[i].z);
        glPopMatrix();
    }
}

void make_world()
{
    glPushMatrix();
    if(!first_world_load)
    {
        world.gen_missing();
        //world.gen_coins();
        //world.gen_moving();

        r_z = 0.0;
        r_x = lane_width_x;
        first_world_load = 1;

        coin_apply_pattern = !(rand()%1);
        coin_selected_pattern = rand()%3;
        if(coin_selected_pattern == 0 || coin_selected_pattern == 2)
        {
            coinX = rand()%3;
            coinZ = rand()%6;
        }
        if(coin_apply_pattern)
        {
            for(int i=0; i<coins_num; i++)
                coin_available[i] = 1;
            if(coin_selected_pattern == 0)
            {
                float X = coinX*15.0 + 7.5;
                float Z = coinZ*100.0 + 300.0;
                for(int i=0; i<coins_num; i++)
                {
                    coin_positions[i].x = X + coin_pattern[0][i].x;
                    coin_positions[i].y = 15.0 + coin_pattern[0][i].y;
                    coin_positions[i].z = Z + coin_pattern[0][i].z;
                }
            }
            else if(coin_selected_pattern == 1)
            {
                for(int i=0; i<coins_num; i++)
                {
                    coin_positions[i].x = 8.0 + coin_pattern[1][i].x;
                    coin_positions[i].y = 15.0 + coin_pattern[1][i].y;
                    coin_positions[i].z = 120.0 + coin_pattern[1][i].z;
                }
            }
            else if(coin_selected_pattern == 2)
            {
                float X = coinX*15.0 + 7.5;
                float Z = coinZ*150.0 + 300.0;
                for(int i=0; i<coins_num; i++)
                {
                    coin_positions[i].x = X + coin_pattern[2][i].x;
                    coin_positions[i].y = 15.0 + coin_pattern[2][i].y;
                    coin_positions[i].z = Z + coin_pattern[2][i].z;
                }
            }
        }

        //Obstacles
        obstacle_wood_num = 0;
        obstacle_laser_num = 0;
        int x = rand()%4;
        for(int i=0;i<x;i++)
        {
            int y = rand()%2;
            if(y == FIRE)
            {
                obstacle_wood_position[obstacle_wood_num].x = 0.0;
                obstacle_wood_position[obstacle_wood_num].y = 0.0;
                obstacle_wood_position[obstacle_wood_num].z = (rand()%10) * 100.0 + 400.0;
                obstacle_wood_num++;
            }
            else if(y == LASER)
            {
                obstacle_laser_position[obstacle_laser_num].x = 0.0;
                obstacle_laser_position[obstacle_laser_num].y = 0.0;
                obstacle_laser_position[obstacle_laser_num].z = (rand()%10) * 100.0 + 400.0;
                obstacle_laser_num++;
            }
        }


        if(world_crossed%7 == 0 && world_crossed)
        {
            power_available = 1;
            power_choosen = rand()%3;

            power_position.x = 22.5;
            power_position.y = 30.0;
            power_position.z = rand()%14 * 100 + 300;
        }
        else
            power_available = 0;


        if(world_crossed%4 == 0 && world_crossed)
            world_choosen = new_world_choosen;
        world_crossed++;

    }
    world.design(current_origin.x,current_origin.y,current_origin.z);
    make_coins();
    make_power();
    make_obstacle();
    glPopMatrix();

    vector2d block_num = get_humanoid_block(humanoid,world);

    //Generate Temp Lanes
    if(block_num.z >= 2)
    {

        //Generate Random Lanes
        if(block_num.z <= no_lane_z - 2)
        {
            int generate_random[3];
            if(!generate_lane)
            {
                for(int i=0; i<3; i++)
                {
                    generate_random[i] = rand() % 2;
                    temp_world_choosen[i] = rand()%5;
                }
                if(!generate_random[0] && !generate_random[1] && !generate_random[2])
                    generate_random[rand()%3] = 1;
                for(int i=0; i<3; i++)
                    available_lane[i] = generate_random[i];
                generate_lane = 1;
            }
        }
        //Up
        if(available_lane[0])
        {
            glPushMatrix();
            int x = world_choosen;
            if(world_crossed%4 == 0)
                world_choosen = temp_world_choosen[0];
            temp_world[0].design(current_origin.x,current_origin.y,current_origin.z + no_lane_z * lane_depth_z);
            glPopMatrix();
            world_choosen = x;
        }

        //Left
        if(available_lane[1])
        {
            glPushMatrix();
            int x = world_choosen;
            if(world_crossed%4 == 0)
                world_choosen = temp_world_choosen[1];
            glRotatef(90,0,1,0);
            temp_world[1].design(-current_origin.z - (no_lane_z * lane_depth_z),current_origin.y,current_origin.x + (no_lane_x * lane_width_x));
            glPopMatrix();
            world_choosen = x;
        }

        //Right
        if(available_lane[2])
        {
            glPushMatrix();
            int x = world_choosen;
            if(world_crossed%4 == 0)
                world_choosen = temp_world_choosen[1];
            glRotatef(-90,0,1,0);
            temp_world[2].design(current_origin.z + (no_lane_z * lane_depth_z - no_lane_x * lane_width_x),current_origin.y,current_origin.x);
            glPopMatrix();
            world_choosen = x;
        }
        lane_changed = 0;
        check_selected_lane = 0;
    }

    else if(block_num.z == 0 || block_num.z == 1)
    {
        int lanes[3];
        lanes[0] = available_lane[0];
        lanes[1] = available_lane[1];
        lanes[2] = available_lane[2];
        int draw_prev = 0;
        int draw_direction;
        if(!lanes[0] && lanes[1] && !lanes[2])
        {
            draw_prev = 1;
            draw_direction = LEFT;
        }
        if(!lanes[0] && !lanes[1] && lanes[2])
        {
            draw_prev = 1;
            draw_direction = RIGHT;
        }
        glPushMatrix();
        if(prev_selected == RIGHT)
        {
            lanes[0] = available_lane[2];
            lanes[1] = available_lane[0];
            lanes[2] = available_lane[1];
        }
        else if(prev_selected == LEFT)
        {
            lanes[0] = available_lane[1];
            lanes[1] = available_lane[2];
            lanes[2] = available_lane[0];
        }

        //Up
        if(lanes[0])
        {
            glPushMatrix();
            glTranslatef(-current_origin.x,-current_origin.y,-current_origin.z - 2 * (no_lane_z * lane_depth_z) );
            temp_world[0].design(current_origin.x,current_origin.y,current_origin.z + no_lane_z * lane_depth_z);
            glPopMatrix();
        }

        //Left
        if(lanes[1])
        {
            glPushMatrix();
            glRotatef(90,0,1,0);
            glTranslatef(current_origin.z + (no_lane_z * lane_depth_z),-current_origin.y,-current_origin.x);
            temp_world[1].design(-current_origin.z - (no_lane_z * lane_depth_z),current_origin.y,current_origin.x + (no_lane_x * lane_width_x));
            glPopMatrix();
        }

        //Right
        if(lanes[2])
        {
            glPushMatrix();
            glRotatef(-90,0,1,0);
            glTranslatef(-current_origin.z - (no_lane_z * lane_depth_z),-current_origin.y,-current_origin.x);
            temp_world[2].design(current_origin.z + (no_lane_z * lane_depth_z - no_lane_x * lane_width_x),current_origin.y,current_origin.x);
            glPopMatrix();
        }

        if(draw_prev)
        {
            glPushMatrix();
            if(draw_direction == LEFT)
            {
                glRotatef(90,0,1,0);
                glTranslatef(current_origin.z + (no_lane_z * lane_depth_z),-current_origin.y,-current_origin.x);
                temp_world[1].design(-current_origin.z - (no_lane_z * lane_depth_z),current_origin.y,current_origin.x + (no_lane_x * lane_width_x));
            }
            else if(draw_direction == RIGHT)
            {
                glRotatef(-90,0,1,0);
                glTranslatef(-current_origin.z - (no_lane_z * lane_depth_z),-current_origin.y,-current_origin.x);
                temp_world[2].design(current_origin.z + (no_lane_z * lane_depth_z - no_lane_x * lane_width_x),current_origin.y,current_origin.x);
            }
            glPopMatrix();
        }

        glPopMatrix();
    }

    //Check Last Block
    if(block_num.z >= no_lane_z - 1 && !lane_changed)
    {
        check_selected_lane = 1;
        if(lane_selection_done)
        {
            if(selected_lane == RIGHT)
            {
                if(available_lane[2])
                {
                    change_lane = 1;
                    if(world_crossed%4 == 0)
                        new_world_choosen = temp_world_choosen[2];
                    rotation_angle = 90.0;
                    turn_robot_lane(1);
                }
                else
                {
                    falling = 1;
                    fall_game_over(0);
                }
            }
            else if(selected_lane == LEFT)
            {
                if(available_lane[1])
                {
                    change_lane = 1;
                    if(world_crossed%4 == 0)
                        new_world_choosen = temp_world_choosen[1];
                    rotation_angle = 90.0;
                    turn_robot_lane(-1);
                }
                else
                {
                    falling = 1;
                    fall_game_over(0);
                }
            }
            lane_selection_done = 0;
            check_selected_lane = 0;
            selected_lane = UP;
            generate_lane = 0;
            lane_changed = 1;
        }
        if(power_taken && power_choosen == SPEED )
        {
            if(available_lane[0])
            {
                r_z = 0;
                prev_selected = UP;
                if(world_crossed%4 == 0)
                    new_world_choosen = temp_world_choosen[0];
                first_world_load = 0;
            }
            else if(available_lane[2])
            {
                change_lane = 1;
                if(world_crossed%4 == 0)
                    new_world_choosen = temp_world_choosen[2];
                rotation_angle = 90.0;
                turn_robot_lane(1);
            }
            else if(available_lane[1])
            {
                change_lane = 1;
                if(world_crossed%4 == 0)
                    new_world_choosen = temp_world_choosen[1];
                rotation_angle = 90.0;
                turn_robot_lane(-1);
            }

            lane_selection_done = 0;
            check_selected_lane = 0;
            selected_lane = UP;
            generate_lane = 0;
            lane_changed = 1;
        }
    }
    if(block_num.z == no_lane_z && !lane_changed && !falling)
    {
        if(!lane_selection_done)
        {
            if(available_lane[0])
            {
                r_z = 0;
                prev_selected = UP;
                if(world_crossed%4 == 0)
                    new_world_choosen = temp_world_choosen[0];
                first_world_load = 0;
            }
            else
            {
                falling = 1;
                fall_game_over(0);
            }
        }
        lane_selection_done = 0;
        check_selected_lane = 0;
        selected_lane = UP;
        generate_lane = 0;
        lane_changed = 1;
    }
    return;
}

void make_spotlight()
{

    float spot_light_direction[] = {0.0,-1.0,0.0};
    float spot_light_position[] = {humanoid.loc_x/2.0,humanoid.loc_y+30.0,humanoid.loc_z/2.0};

    glLightfv(GL_LIGHT0,GL_POSITION,spot_light_position);
    glLightf(GL_LIGHT0,GL_SPOT_CUTOFF,40.0);
    glLightf(GL_LIGHT0,GL_SPOT_EXPONENT,30.0);
    glLightfv(GL_LIGHT0,GL_SPOT_DIRECTION,spot_light_direction);

    glEnable(GL_LIGHT0);
}

int spot(float a, float b, float c, float d, float e, float f)
{
    GLfloat mat_specular[] = { 0.3, 1.0, 0.3, 1.0 };
    GLfloat mat_shininess[] = { 50.0 };
    GLfloat light_position[] = { a,b,c, 1.0 };
    GLfloat spotDir[] = { d,e,f };
    glClearColor (0, 0, 0, 1);
    glShadeModel (GL_SMOOTH);
    glLightfv(GL_LIGHT0,GL_SPECULAR,mat_specular);
    glLightfv(GL_LIGHT0,GL_POSITION,light_position);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glLightf(GL_LIGHT0,GL_SPOT_CUTOFF,95.0);
    glLightf(GL_LIGHT0,GL_SPOT_EXPONENT,2.0);
    glLightfv(GL_LIGHT0,GL_SPOT_DIRECTION,spotDir);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_DEPTH_TEST);
    return 0;
}

float tran = 0.0;
void test(float radius1,float radius2,float height)
{
    GLUquadricObj *x = gluNewQuadric();
    gluQuadricDrawStyle(x,GLU_FILL);
    gluQuadricNormals(x,GLU_SMOOTH);
    //gluQuadricTexture(x,1);
    glEnable(GL_COLOR_MATERIAL);
    tran += 0.1;
    if(tran > 1.0)
        tran = 0.1;
    glColor4f(1,0,0,tran);
    gluCylinder(x,radius1,radius2,height,50,10);
    glRotatef(180, 1,0,0);
    gluDisk(x,0.0,radius1,50,1);
    glRotatef(180,1,0,0);
    glTranslatef(0.0,0.0,height);
    gluDisk(x,0.0,radius2,50,1);
    glTranslatef(0.0,0.0,-height);
    glColor4f(0,0,0,1);
    glDisable(GL_COLOR_MATERIAL);
}

void draw_scene(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);
    background();
    glEnable(GL_DEPTH_TEST);
    glClear(GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    gluPerspective(45.0f, (GLfloat)window_width / (GLfloat)window_height, 1.0f, 15500.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    /*glLightfv(GL_LIGHT0, GL_SPECULAR, whiteSpecularLight);
    glLightfv(GL_LIGHT0, GL_AMBIENT, blackAmbientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteDiffuseLight);*/



    glPushMatrix();
    glTranslatef(0,0,-5);
    print_collected_coins(3.0,1.9,GLUT_BITMAP_HELVETICA_18,"Score:");
    glPopMatrix();

    glPushMatrix();
    glRotatef(rot_x,1,0,0);
    glRotatef(rot_y,0,1,0);
    glRotatef(rot_z,0,0,1);

    glTranslatef(0,0,-85);
    select_camera();

    glPushMatrix();

    make_world();

    //display_powers();
    //display_obstacles();

    glPushMatrix();
    if(!falling && !change_lane)
    {
        r_z += robot_velocity;
        robot_motion = robot_slide?0:1;
    }

    glPushMatrix();
    make_humanoid();
    glPopMatrix();

    /*glPushMatrix();
    glTranslatef(humanoid.loc_x/2.0,20,humanoid.loc_z/2.0 + 20);
    test(1,1,10);
    glPopMatrix();*/

    //spot(humanoid.loc_x/2.0,30,humanoid.loc_z/2.0,0,-1,0);

    //make_spotlight();

    glPopMatrix();

    glPopMatrix();

    glPopMatrix();
    glFlush();
    glutSwapBuffers();
}

void update_world(int value)
{
    int x,z;
    /* for(x=0; x<world.get_num_blocks_width(); x++)
     {
         for(z=0; z<world.get_num_blocks_depth(); z++)
         {
             if(world.moving[x][z])
             {
                 if( (world.block_motion_value[x][z]>=world.max_block_motion_value[x][z] && world.block_motion_direction[x][z]==0) ||
                         (world.block_motion_value[x][z]<=-world.max_block_motion_value[x][z] && world.block_motion_direction[x][z]==1) )
                     world.block_motion_direction[x][z] = !world.block_motion_direction[x][z];
                 world.block_motion_value[x][z] += world.block_motion_direction[x][z]?-1.0:1.0;
             }
         }
     }*/
    coin_rotate += 15.0;
    if(coin_rotate >= 360.0)
        coin_rotate = 0.0;
    gem_rotate +=10.0;
    if(gem_rotate >=360.0 )
        gem_rotate = 0.0;
    glutPostRedisplay();
    glutTimerFunc(60,update_world,0);
}

#include "robot_movement.h"
#include "keyboard.h"

int main(int argc ,char **argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
    screen_width = glutGet(GLUT_SCREEN_WIDTH);
    screen_height = glutGet(GLUT_SCREEN_HEIGHT);

    glutInitWindowPosition(0,0);
    glutInitWindowSize(screen_width,screen_height);
    glutCreateWindow("Graphics.... :)");

    initRendering();
    //world.gen_missing();
    //world.gen_moving();
    //world.gen_coins();

    temp_world[0] = World(no_lane_x,no_lane_z,lane_width_x,lane_depth_z);
    temp_world[1] = World(no_lane_x,no_lane_z,lane_width_x,lane_depth_z);
    temp_world[2] = World(no_lane_x,no_lane_z,lane_width_x,lane_depth_z);
    current_origin.x = 0.0;
    current_origin.y = 0.0;
    current_origin.z = 0.0;
    load_textures();

    glutDisplayFunc(draw_scene);
    glutReshapeFunc(reshape_window);
    glutKeyboardFunc(handle_keyboard_keys);
    glutSpecialFunc(handle_special_keyboard_keys);
    glutSpecialUpFunc(release_keyboard_keys);
    glutMouseFunc(click_action);
    glutMotionFunc(click_hold_action);
    //glutPassiveMotionFunc(mouse_action);
    glutTimerFunc(60,update_world,0);
    glutTimerFunc(10,robot_move_forward,0);
    glutMainLoop();
    return 0;
}


