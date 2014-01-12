void gen_coin_patterns()
{
    for(int i=0;i<15;i++)
    {
        coin_pattern[0][i].x = 0;
        coin_pattern[0][i].y = 0;
        coin_pattern[0][i].z = i*60.0;
    }
    for(int i=0;i<15;i++)
    {
        if((i%4)%2==1)
            coin_pattern[1][i].x = (i%4*15)%30;
        else
            coin_pattern[1][i].x = (i%4*15);
        coin_pattern[1][i].y = 0;
        coin_pattern[1][i].z = i*105.0;
    }
    int k = 1;
    for(int i=0;i<15;i++)
    {
        coin_pattern[2][i].x = 0;
        if(i<8)
            coin_pattern[2][i].y = sqrt(i*35.0);
        else
        {
            coin_pattern[2][i].y=coin_pattern[2][i-2*k].y;
            k++;
        }
        coin_pattern[2][i].z = 20*i;
    }
}

void reshape_window(int w, int h)
{
    glViewport(0, 0, w, h);
    window_width = w;
    window_height = h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (float)w / (float)h, 1.0, 500.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void initRendering()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);

    glEnable(GL_POINT_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);

    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);

    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glEnable(GL_BLEND_COLOR);

    glEnable(GL_SHADE_MODEL);
    glShadeModel(GL_SMOOTH);

    //Lights

    //glLightfv(GL_LIGHT0, GL_DIFFUSE, WHITE);
    //glLightfv(GL_LIGHT0, GL_SPECULAR, WHITE);
    //glMaterialfv(GL_FRONT, GL_SPECULAR, WHITE);
    //glMaterialf(GL_FRONT, GL_SHININ-ESS, 30);

    float ambient_light[] = {1.0,1.0,1.0,1.0};

    glLightfv(GL_LIGHT0,GL_AMBIENT,ambient_light);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);



    glEnable(GL_NORMALIZE);

    glEnable(GL_CULL_FACE);
    glCullFace ( GL_BACK );

    glPointSize(8);
    glLineWidth(2);
    //glClearColor(119.0/255,136.0/255,153.0/255,1);

    gen_coin_patterns();

    glClearColor(0,0,0,1);
    srand (time(NULL));
}
