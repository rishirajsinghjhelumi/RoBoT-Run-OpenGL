void handle_keyboard_keys(unsigned char key ,int x ,int y)
{
    switch(key)
    {
    case ' ':
        robot_jump = 1;
        robot_jump_motion(1);
        break;

    case 'i':
        tile_num_depth = (tile_num_depth + 1);
        if(tile_num_depth > world.get_num_blocks_depth())
            tile_num_depth = world.get_num_blocks_depth();
        break;
    case 'k':
        tile_num_depth = (tile_num_depth - 1);
        if(tile_num_depth < 1)
            tile_num_depth = 1;
        break;
    case 'j':
        tile_num_width = (tile_num_width + 1);
        if(tile_num_width > world.get_num_blocks_width())
            tile_num_width = world.get_num_blocks_width();
        break;
    case 'l':
        tile_num_width = (tile_num_width - 1);
        if(tile_num_width < 1)
            tile_num_width = 1;
        break;

    case 'r':
        if(view_mode == TOWER_VIEW)
        {
            tower_view_angle += 5.0;
            if(tower_view_angle > 360.0)
                tower_view_angle -= 360.0;
        }
        else if(view_mode == TILE_VIEW)
            tile_view_angle += 5.0;
        else if(view_mode == CENTER_TOWER_VIEW)
        {
            center_tower_view_angle += 5.0;
            if(center_tower_view_angle > 360.0)
                center_tower_view_angle -= 360.0;
        }
        break;
    case 't':
        if(view_mode == TOWER_VIEW)
        {
            tower_view_angle -= 5.0;
            if(tower_view_angle < 0.0)
                tower_view_angle += 360.0;
        }
        else if(view_mode == TILE_VIEW)
            tile_view_angle -= 5.0;
        else if(view_mode == CENTER_TOWER_VIEW)
        {
            center_tower_view_angle -= 5.0;
            if(center_tower_view_angle < 0.0)
                center_tower_view_angle += 360.0;
        }
        break;


    case 'w':
        turn_robot_direction(robot_direction,direction[0][robot_direction-1]);
        robot_direction = direction[0][robot_direction-1];
        break;
    case 's':
        turn_robot_direction(robot_direction,direction[1][robot_direction-1]);
        robot_direction = direction[1][robot_direction-1];
        break;
    case 'a':
        turn_robot_direction(robot_direction,direction[2][robot_direction-1]);
        robot_direction = direction[2][robot_direction-1];
        break;
    case 'd':
        turn_robot_direction(robot_direction,direction[3][robot_direction-1]);
        robot_direction = direction[3][robot_direction-1];
        break;
    case 'n':
        if(check_selected_lane)
        {
            selected_lane = LEFT;
            prev_selected = LEFT;
            lane_selection_done = 1;
        }
        break;
    case 'm':
        if(check_selected_lane)
        {
            selected_lane = RIGHT;
            prev_selected = RIGHT;
            lane_selection_done = 1;
        }
        break;
    case 'b':
        if(!robot_jump)
        {
            robot_slide = 1;
            robot_slide_motion(0);
        }
        break;
    default:
        break;

    }
    glutPostRedisplay();
}

void first_third_camera_keys(int key)
{
    if(key == GLUT_KEY_UP)
    {
        robot_motion = 1;
        if(robot_direction == UP)
            r_z += robot_velocity;
        else if(robot_direction == DOWN)
            r_z -= robot_velocity;
        else if(robot_direction == LEFT)
            r_x += robot_velocity;
        else if(robot_direction == RIGHT)
            r_x -= robot_velocity;
        robot_movement_direction = UP;
    }
    else if(key == GLUT_KEY_DOWN)
    {
        robot_motion = 1;
        if(robot_direction == UP)
            r_z -= robot_velocity;
        else if(robot_direction == DOWN)
            r_z += robot_velocity;
        else if(robot_direction == LEFT)
            r_x -= robot_velocity;
        else if(robot_direction == RIGHT)
            r_x += robot_velocity;
        robot_movement_direction = DOWN;
    }
    else if(key == GLUT_KEY_LEFT)
    {
        robot_motion = 1;
        if(robot_direction == UP)
            r_x += robot_velocity;
        else if(robot_direction == DOWN)
            r_x -= robot_velocity;
        else if(robot_direction == LEFT)
            r_z -= robot_velocity;
        else if(robot_direction == RIGHT)
            r_z += robot_velocity;
        robot_movement_direction = LEFT;
    }

    else if(key == GLUT_KEY_RIGHT)
    {
        robot_motion = 1;
        if(robot_direction == UP)
            r_x -= robot_velocity;
        else if(robot_direction == DOWN)
            r_x += robot_velocity;
        else if(robot_direction == LEFT)
            r_z += robot_velocity;
        else if(robot_direction == RIGHT)
            r_z -= robot_velocity;
        robot_movement_direction = RIGHT;
    }
    detect_moving_blocks_collision(humanoid,world);
}

int center_tower_camera_keys(int key)
{
    int robot_direction;
    if( (center_tower_view_angle > 0.0 && center_tower_view_angle <= 45.0) || (center_tower_view_angle <=360 && center_tower_view_angle >315.0))
        robot_direction = UP;
    else if(center_tower_view_angle > 45.0 && center_tower_view_angle <= 135.0)
        robot_direction = LEFT;
    else if(center_tower_view_angle > 135 && center_tower_view_angle <= 225.0)
        robot_direction = DOWN;
    else
        robot_direction = RIGHT;
    if(key == GLUT_KEY_UP)
    {
        robot_motion = 1;
        if(robot_direction == UP)
            r_z += robot_velocity;
        else if(robot_direction == DOWN)
            r_z -= robot_velocity;
        else if(robot_direction == LEFT)
            r_x += robot_velocity;
        else if(robot_direction == RIGHT)
            r_x -= robot_velocity;
        robot_movement_direction = UP;
    }
    else if(key == GLUT_KEY_DOWN)
    {
        robot_motion = 1;
        if(robot_direction == UP)
            r_z -= robot_velocity;
        else if(robot_direction == DOWN)
            r_z += robot_velocity;
        else if(robot_direction == LEFT)
            r_x -= robot_velocity;
        else if(robot_direction == RIGHT)
            r_x += robot_velocity;
        robot_movement_direction = DOWN;
    }
    else if(key == GLUT_KEY_LEFT)
    {
        robot_motion = 1;
        if(robot_direction == UP)
            r_x += robot_velocity;
        else if(robot_direction == DOWN)
            r_x -= robot_velocity;
        else if(robot_direction == LEFT)
            r_z -= robot_velocity;
        else if(robot_direction == RIGHT)
            r_z += robot_velocity;
        robot_movement_direction = LEFT;
    }

    else if(key == GLUT_KEY_RIGHT)
    {
        robot_motion = 1;
        if(robot_direction == UP)
            r_x -= robot_velocity;
        else if(robot_direction == DOWN)
            r_x += robot_velocity;
        else if(robot_direction == LEFT)
            r_z += robot_velocity;
        else if(robot_direction == RIGHT)
            r_z -= robot_velocity;
        robot_movement_direction = RIGHT;
    }
    detect_moving_blocks_collision(humanoid,world);
    return robot_direction;
}

int tower_camera_keys(float tower_view_angle,int key)
{
    //int robot_direction;
    if( (tower_view_angle >= 0.0 && tower_view_angle <= 45.0) || (tower_view_angle <=360 && tower_view_angle >315.0))
        robot_direction = DOWN;
    else if(tower_view_angle > 45.0 && tower_view_angle <= 135.0)
        robot_direction = RIGHT;
    else if(tower_view_angle > 135 && tower_view_angle <= 225.0)
        robot_direction = UP;
    else
        robot_direction = LEFT;
    if(key == GLUT_KEY_UP)
    {
        robot_motion = 1;
        if(robot_direction == UP)
            r_z += robot_velocity;
        else if(robot_direction == DOWN)
            r_z -= robot_velocity;
        else if(robot_direction == LEFT)
            r_x += robot_velocity;
        else if(robot_direction == RIGHT)
            r_x -= robot_velocity;
        robot_movement_direction = UP;
    }
    else if(key == GLUT_KEY_DOWN)
    {
        robot_motion = 1;
        if(robot_direction == UP)
            r_z -= robot_velocity;
        else if(robot_direction == DOWN)
            r_z += robot_velocity;
        else if(robot_direction == LEFT)
            r_x -= robot_velocity;
        else if(robot_direction == RIGHT)
            r_x += robot_velocity;
        robot_movement_direction = DOWN;
    }
    else if(key == GLUT_KEY_LEFT)
    {
        robot_motion = 1;
        if(robot_direction == UP)
            r_x += robot_velocity;
        else if(robot_direction == DOWN)
            r_x -= robot_velocity;
        else if(robot_direction == LEFT)
            r_z -= robot_velocity;
        else if(robot_direction == RIGHT)
            r_z += robot_velocity;
        robot_movement_direction = LEFT;
    }

    else if(key == GLUT_KEY_RIGHT)
    {
        robot_motion = 1;
        if(robot_direction == UP)
            r_x -= robot_velocity;
        else if(robot_direction == DOWN)
            r_x += robot_velocity;
        else if(robot_direction == LEFT)
            r_z += robot_velocity;
        else if(robot_direction == RIGHT)
            r_z -= robot_velocity;
        robot_movement_direction = RIGHT;
    }
    detect_moving_blocks_collision(humanoid,world);
    //return robot_direction;
}

void world_camera_keys(int key)
{
    if(key == GLUT_KEY_UP)
    {
        r_z += robot_velocity;
        robot_motion = 1;
        if(robot_direction != UP)
            turn_robot_direction(robot_direction,UP);
        robot_direction = UP;
        robot_movement_direction = UP;
    }
    if(key == GLUT_KEY_DOWN)
    {
        r_z -= robot_velocity;
        robot_motion = 1;
        if(robot_direction != DOWN)
            turn_robot_direction(robot_direction,DOWN);
        robot_direction = DOWN;
        robot_movement_direction = DOWN;
    }
    if(key == GLUT_KEY_LEFT)
    {
        r_x += robot_velocity;
        robot_motion = 1;
        if(robot_direction != LEFT)
            turn_robot_direction(robot_direction,LEFT);
        robot_direction = LEFT;
        robot_movement_direction = LEFT;
    }
    if(key == GLUT_KEY_RIGHT)
    {
        r_x -= robot_velocity;
        robot_motion = 1;
        if(robot_direction != RIGHT)
            turn_robot_direction(robot_direction,RIGHT);
        robot_direction = RIGHT;
        robot_movement_direction = RIGHT;
    }
    detect_moving_blocks_collision(humanoid,world);
}

void handle_special_keyboard_keys(int key,int x,int y)
{
    prev_r.x = r_x;
    prev_r.y = r_y;
    prev_r.z = r_z;

    if(key == GLUT_KEY_F1)
        rot_x -= 5.0;
    if(key == GLUT_KEY_F2)
        rot_x += 5.0;
    if(key == GLUT_KEY_F3)
        rot_y -=5.0;
    if(key == GLUT_KEY_F4)
        rot_y += 5.0;
    if(key == GLUT_KEY_F5)
        rot_z -=5.0;
    if(key == GLUT_KEY_F6)
        rot_z +=5.0;

    if(view_mode == FIRST_PERSON || view_mode == THIRD_PERSON)
    {
        first_third_camera_keys(key);
    }
    else if(view_mode == CENTER_TOWER_VIEW)
    {
        robot_direction = center_tower_camera_keys(key);
        check_robot_body_angle(robot_direction);
    }
    else if(view_mode == TOWER_VIEW)
    {
        tower_camera_keys(tower_view_angle,key);
        check_robot_body_angle(robot_direction);
    }
    else if(view_mode == WORLD_VIEW)
        world_camera_keys(key);
    else if(view_mode == HELICOPTOR_VIEW)
    {
        tower_camera_keys(helicoptor_view_angle,key);
        check_robot_body_angle(robot_direction);
    }
    else
        world_camera_keys(key);
    detect_on_moving_block_collision();

    if(key == GLUT_KEY_PAGE_UP)
    {
        view_mode = (view_mode + 1);
        if(view_mode > 7)
            view_mode = 7;
    }
    if(key == GLUT_KEY_PAGE_DOWN)
    {
        view_mode = (view_mode - 1);
        if(view_mode < 1)
            view_mode = 1;
    }
    glutPostRedisplay();
}

void release_keyboard_keys(int key,int x,int y)
{
    switch(key)
    {
    case GLUT_KEY_UP:
    case GLUT_KEY_DOWN:
    case GLUT_KEY_LEFT:
    case GLUT_KEY_RIGHT:
        robot_motion = 0;
        break;
    default:
        break;
    }
}

