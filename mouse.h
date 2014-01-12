#if !defined(GLUT_WHEEL_UP)
#define GLUT_WHEEL_UP   3
#define GLUT_WHEEL_DOWN 4
#endif

void get_mouse_coordinates(int x,int y)
{
    int viewport[4];
    double modelview[16];
    double projection[16];
    float winX, winY, winZ;
    double posX, posY, posZ;
    glEnable(GL_DEPTH);
    glEnable(GL_DEPTH_COMPONENT);
    glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
    glGetDoublev(GL_PROJECTION_MATRIX, projection);
    glGetIntegerv(GL_VIEWPORT, viewport);
    winX = (float)x;
    winY = (float)viewport[3] - (float)y;
    glReadPixels( int(winX), int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );
    gluUnProject( winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);
    mouse_posX = posX;
    mouse_posY = posY;
    mouse_posZ = posZ;
}

void click_hold_action(int x,int y)
{
    //get_mouse_coordinates(x,y);
    static int prevX, prevY;
    int movX = x - prevX;
    int movY = y - prevY;
    if(view_mode == HELICOPTOR_VIEW)
    {
        if(helicoptor_moveX)
        {
            if(movX < 0.0)
                helicoptor_view_angle += 1.0;
            else
                helicoptor_view_angle -= 1.0;
            if(helicoptor_view_angle > 360.0)
                helicoptor_view_angle -= 360.0;
            if(helicoptor_view_angle < 0.0)
                helicoptor_view_angle += 360.0;
        }
        else if(helicoptor_moveY)
        {
            if(movY < 0.0)
                helicoptor_angle -= 1.0;
            else
                helicoptor_angle += 1.0;
            if(helicoptor_angle < 0.0)
                helicoptor_angle = 0.0;
            if(helicoptor_angle > 180.0)
                helicoptor_angle = 180;
        }
    }
    prevX = x;
    prevY = y;
}

void click_action(int button,int state ,int x,int y)
{
    if(button == GLUT_WHEEL_UP)
    {
        if(view_mode == HELICOPTOR_VIEW)
            zoom_camera -= 0.6;
    }
    else if(button == GLUT_WHEEL_DOWN)
    {
        if(view_mode == HELICOPTOR_VIEW)
            zoom_camera += 0.6;
    }
    else if(button == GLUT_LEFT_BUTTON)
        helicoptor_moveX = (state == GLUT_DOWN);
    else if(button == GLUT_RIGHT_BUTTON)
        helicoptor_moveY = (state == GLUT_DOWN);
}

