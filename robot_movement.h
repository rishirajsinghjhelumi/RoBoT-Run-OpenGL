int m = 0;
int m1 = 1;
int m2 = 1;
int m3 = 0;
float robot_motion_factor = 15.0;
void robot_move_forward(int value)
{
    if(!robot_motion)
    {
        if(falling)
            return;
        glutTimerFunc(robot_motion_timer,robot_move_forward,0);
        m = m3 = 0;
        m1 = m2 = 1;
        lsa = 0.0,lea = 0.0,rsa = 0.0,rea = 0.0,lta = 0.0,lka = 0.0,rta = 0.0,rka = 0.0;
        lta_x = rta_x = 0.0;
        lea = rea = -60.0;
        lka = rka = 45.0;
        return;
    }
    lea = rea = -60.0;
    lka = rka = 45.0;
    if((rta >= 60 && m==1) || (rta <= -60 && m==0))
        m=!m;
    rta += m?robot_motion_factor:-robot_motion_factor;
    if(rta<-60)rta=-60;
    if(rta>60)rta=60;

    if((lta >= 60 && m1==1) || (lta <= -60 && m1==0))
        m1=!m1;
    lta += m1?robot_motion_factor:-robot_motion_factor;
    if(lta<-60)lta=-60;
    if(lta>60)lta=60;

    if((rsa >= 60 && m2==1) || (rsa <= -60 && m2==0))
        m2=!m2;
    rsa += m2?robot_motion_factor:-robot_motion_factor;
    if(rsa<-60)rsa=-60;
    if(rsa>60)rsa=60;

    if((lsa >= 60 && m3==1) || (lsa <= -60 && m3==0))
        m3=!m3;
    lsa += m3?robot_motion_factor:-robot_motion_factor;
    if(lsa<-60)lsa=-60;
    if(lsa>60)lsa=60;
    glutPostRedisplay();
    glutTimerFunc(robot_motion_timer,robot_move_forward,value);
}


float t=0.25;
void robot_jump_motion(int value)
{
    if(!robot_jump)
    {
        lsa = 0.0,lea = -60.0,rsa = 0.0,rea = -60.0,lta = 0.0,lka = 45.0,rta = 0.0,rka = 45.0;
        return;
    }
    robot_motion = 1;
    lsa = -75,lea = -120.0,rsa = 45.0,rea = 0.0,lta=45.0,lka = 0.0,rta = -45.0,rka = 105.0;

    jump_translate_z = jump_velocity*t/SQRT2*cos(DEG2RAD(ba));
    jump_translate_x = -jump_velocity*t/SQRT2*sin(DEG2RAD(ba));
    jump_translate_y = jump_velocity*t/SQRT2 - GRAVITY*t*t/2;
    t += jump_update_time;
    if(jump_translate_y<0.01)
    {
        robot_jump = 0;
        robot_motion = 0;
        r_y = py;
        //r_z = pz + jump_translate_z;
        r_x = px + jump_translate_x;
        jump_translate_x = jump_translate_y = jump_translate_z = 0.0;
        t = 0.25;
    }
    glutPostRedisplay();
    glutTimerFunc(30,robot_jump_motion,value);
}

void check_robot_body_angle(int robot_direction)
{
    if(robot_direction == UP)
        ba = 0.0;
    else if(robot_direction == DOWN)
        ba = 180.0;
    else if(robot_direction == RIGHT)
        ba = 90.0;
    else
        ba = -90.0;
}

void turn_robot(int value)
{
    if(!robot_rotation)
    {
        check_robot_body_angle(robot_direction);
        return;
    }
    if(rotation_angle > 0.0)
    {
        ba = ba + value*5.0;
        rotation_angle = rotation_angle -5.0;
    }
    else
        robot_rotation = 0;
    glutPostRedisplay();
    glutTimerFunc(30,turn_robot,value);
}

void turn_robot_direction(int pre_dir,int new_dir)
{
    if(pre_dir == new_dir)
        return;
    robot_rotation = 1;
    if(pre_dir == UP)
    {
        if(new_dir == DOWN)
            rotation_angle = 180,turn_robot(1);
        else if(new_dir == LEFT)
            rotation_angle = 90,turn_robot(-1);
        else
            rotation_angle = 90,turn_robot(1);
    }
    else if(pre_dir == DOWN)
    {
        if(new_dir == UP)
            rotation_angle = 180,turn_robot(1);
        else if(new_dir == LEFT)
            rotation_angle = 90,turn_robot(1);
        else
            rotation_angle = 90,turn_robot(-1);
    }
    else if(pre_dir == LEFT)
    {
        if(new_dir == RIGHT)
            rotation_angle = 180,turn_robot(1);
        else if(new_dir == UP)
            rotation_angle = 90,turn_robot(1);
        else
            rotation_angle = 90,turn_robot(-1);
    }
    else if(pre_dir == RIGHT)
    {
        if(new_dir == LEFT)
            rotation_angle = 180,turn_robot(1);
        else if(new_dir == UP)
            rotation_angle = 90,turn_robot(-1);
        else
            rotation_angle = 90,turn_robot(1);
    }
}

void turn_robot_lane(int value)
{
    if(!change_lane)
    {
        return;
    }
    if(rotation_angle > 0.0)
    {
        ba = ba + value*15;
        rotation_angle = rotation_angle - 15.0;
        //r_z += 2.0;
        //r_x -= 2.0;
    }
    else
    {
        change_lane = 0;
        //r_z = 0.0;
        first_world_load = 0;
        ba = 0.0;
    }
    glutPostRedisplay();
    glutTimerFunc(2,turn_robot_lane,value);
}

int num_slides = 0;
void robot_slide_motion(int value)
{
    if(!robot_slide)
    {
        num_slides = 0;
        return;
    }
    lsa = -75,lea = -120.0,rsa = 45.0,rea = 0.0,lta=-35.0,lka = 0.0,rta = -35.0,rka = 0.0;
    num_slides++;
    if(num_slides == 200 || robot_jump)
        robot_slide = 0;
    glutTimerFunc(2,robot_slide_motion,value);
}

int num_speed = 0;
void robot_speed_motion(int value)
{
    if(!power_taken)
    {
        power_available = 0;
        power_choosen = 0;
        num_speed = 0;
        robot_velocity = 30.0;
        return;
    }
    robot_velocity = 60.0;
    num_speed++;
    if(num_speed == 200)
    {
        power_taken = 0;
    }
    glutTimerFunc(2,robot_speed_motion,value);
}

int num_magnet = 0;
void robot_magnet_motion(int value)
{
    if(!power_taken)
    {
        power_available = 0;
        power_choosen = 0;
        num_magnet = 0;
        return;
    }
    num_magnet++;
    if(num_magnet == 500)
    {
        power_taken = 0;
    }
    glutTimerFunc(2,robot_magnet_motion,value);
}

int num_invisible = 0;
void robot_invisible_motion(int value)
{
    if(!power_taken)
    {
        power_available = 0;
        power_choosen = 0;
        num_invisible = 0;
        return;
    }
    num_invisible++;
    if(num_invisible == 500)
    {
        power_taken = 0;
    }
    glutTimerFunc(2,robot_invisible_motion,value);
}


float t1 = 0.0;
int m4 = 1;
int m5 = 0;
int first = 1;
int fall_calls = 0;
void fall_game_over(int value)
{
    if(fall_calls == 100)
        exit(0);
    if(first)
    {
        lsa = -60.0,lea = -60.0,rsa = -60.0,rea = -60.0,lta = 0.0,lka = 60.0,rta = 0.0,rka = 60.0;
        m = 0,m1=1;
        first = 0;
        view_mode = THIRD_PERSON;
    }
    robot_motion = 0;
    robot_jump = 0;
    fall_calls++;

    jump_translate_y = -1.0*GRAVITY*t1*t1/2.0;
    t1+=0.1;

    if((lsa <= -120 && m4==0) || (lsa >= 0 && m4==1))
        m4=!m4;
    lsa += m4?10:-10;
    if(lsa>0)lsa=0;
    if(lsa<-120)lsa=-120;

    if((rsa <= -120 && m5==0) || (rsa >=0 && m5==1))
        m5=!m5;
    rsa += m5?10:-10;
    if(rsa>0)rsa=0;
    if(rsa<-120)rsa=-120;

    if((rta >= 60 && m==1) || (rta <= -60 && m==0))
        m=!m;
    rta += m?5:-5;
    if(rta<-60)rta=-60;
    if(rta>60)rta=60;

    if((lta >= 60 && m1==1) || (lta <= -60 && m1==0))
        m1=!m1;
    lta += m1?5:-5;
    if(lta<-60)lta=-60;
    if(lta>60)lta=60;

    glutPostRedisplay();
    glutTimerFunc(5,fall_game_over,value);
}
