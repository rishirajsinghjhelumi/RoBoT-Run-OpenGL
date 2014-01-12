class World
{
    int num_blocks_width;
    int num_blocks_depth;

public:
    float width;
    float depth;
    float height;
    int list;
    int missing[MAX][MAX];
    int moving[MAX][MAX];
    int coins[MAX][MAX];
    float block_motion_value[MAX][MAX];
    int block_motion_direction[MAX][MAX];
    float max_block_motion_value[MAX][MAX];

    World(int num_blocks_width,int num_blocks_depth,float width,float depth):
        width(width),
        depth(depth),
        num_blocks_depth(num_blocks_depth),
        num_blocks_width(num_blocks_width),
        height(15.0)
    {}

    World():
        width(0.0),
        depth(0.0),
        num_blocks_depth(0),
        num_blocks_width(0),
        height(15.0)
    {}
    void gen_missing()
    {
        for(int i=0; i<MAX; i++)
            for(int j=0; j<MAX; j++)
                missing[i][j] = 0;
        int x = rand()%(num_blocks_depth - 5);
        if(rand()%3)
            missing[rand()%(num_blocks_width)][x] = 1;
        if(rand()%3)
            missing[rand()%(num_blocks_width)][rand()%(num_blocks_depth - 6) + 6] = 1;
        missing[0][0] = missing[num_blocks_width - 1][num_blocks_depth-1] = 0;
    }

    void gen_moving()
    {
        for(int i=0; i<MAX; i++)
            for(int j=0; j<MAX; j++)
                moving[i][j] = 0;
        int x = num_blocks_depth*num_blocks_width/3;
        for(int i=0; i<x; i++)
        {
            int xx = rand()%(num_blocks_width);
            int zz = rand()%(num_blocks_depth);
            moving[xx][zz] = 1;
            max_block_motion_value[xx][zz] = 15.0 + (rand() % 36);
            block_motion_value[xx][zz] = 0.0;
            block_motion_direction[xx][zz] = 1;
        }
    }

    void gen_coins()
    {
        for(int i=0; i<MAX; i++)
            for(int j=0; j<MAX; j++)
                coins[i][j] = 0;
        int x = num_blocks_depth*num_blocks_width/3;
        for(int i=0; i<x; i++)
            coins[rand()%(num_blocks_width)][rand()%(num_blocks_depth)] = 1;
    }

    void gen_coins_pattern(int pattern,float x,float y,float z)
    {
        glPushMatrix();
        glTranslatef(x,y,z);
        for(int i=0; i<coins_num; i++)
        {
            if(coin_available[i])
            {
                glPushMatrix();
                glTranslatef(coin_pattern[pattern][i].x,coin_pattern[pattern][i].y,coin_pattern[pattern][i].z);
                draw_coin(5);
                glPopMatrix();
            }
        }
        glPopMatrix();
    }

    void draw_coin(float radius)
    {
        GLUquadricObj *x = gluNewQuadric();
        gluQuadricDrawStyle(x,GLU_FILL);
        gluQuadricNormals(x,GLU_SMOOTH);
        glEnable(GL_TEXTURE_2D);
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
        glBindTexture(GL_TEXTURE_2D,coin_texture);
        gluQuadricTexture(x,1);
        glRotatef(coin_rotate,0,1,0);
        glScalef(0.2,1,1);
        gluSphere(x,radius,50,10);
        glDisable(GL_TEXTURE_2D);
    }

    void boundary_grass(float x,float y,float z)
    {
        glPushMatrix();
        glTranslatef(x,y,z);
        glScalef(0.7,0.7,2.8);

        glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_TEXTURE_GEN_S);
        glEnable(GL_TEXTURE_GEN_T);
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_CLAMP_TO_EDGE);
        glBindTexture(GL_TEXTURE_2D,texture_boundary[world_choosen]);
        glScalef(width/10.0,depth/num_blocks_depth,depth/num_blocks_depth);
        glutSolidCube(1);
        glDisable(GL_TEXTURE_GEN_S);
        glDisable(GL_TEXTURE_GEN_T);
        glDisable(GL_TEXTURE_2D);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0,depth/num_blocks_depth-y-1,0);
        glRotatef(45,1,0,0);
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_TEXTURE_GEN_S);
        glEnable(GL_TEXTURE_GEN_T);
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_CLAMP_TO_EDGE);
        glBindTexture(GL_TEXTURE_2D,texture_boundary[world_choosen]);
        glScalef(width/7.0,depth/num_blocks_depth,depth/num_blocks_depth);
        glutSolidCube(0.7);
        glDisable(GL_TEXTURE_GEN_S);
        glDisable(GL_TEXTURE_GEN_T);
        glDisable(GL_TEXTURE_2D);
        glPopMatrix();

        glPopMatrix();
    }

    void draw_cylinder(float radius1,float radius2,float height)
    {
        GLUquadricObj *x = gluNewQuadric();
        gluQuadricDrawStyle(x,GLU_FILL);
        gluQuadricNormals(x,GLU_SMOOTH);
        glEnable(GL_TEXTURE_2D);
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPEAT);

        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glEnable(GL_TEXTURE_GEN_S);
        glEnable(GL_TEXTURE_GEN_T);
        glBindTexture(GL_TEXTURE_2D,texture_boundary[world_choosen]);
        gluQuadricTexture(x,1);
        gluCylinder(x,radius1,radius2,height,10,10);
        glRotatef(180, 1,0,0);
        gluDisk(x,0.0,radius1,10,1);
        glRotatef(180,1,0,0);
        glTranslatef(0.0,0.0,height);
        gluDisk(x,0.0,radius2,10,1);
        glTranslatef(0.0,0.0,-height);

        glDisable(GL_TEXTURE_GEN_S);
        glDisable(GL_TEXTURE_GEN_T);
        glDisable(GL_TEXTURE_2D);
    }

    void boundary_road(float x,float y,float z,float radius_top,float radius_bottom,float height)
    {
        glPushMatrix();
        glTranslatef(x,y,z);

        for(int i=0; i<num_blocks_depth; i++)
        {
            glPushMatrix();
            glTranslatef(0,0,i*depth);
            glRotatef(-90,1,0,0);
            draw_cylinder(radius_bottom,radius_top,height);
            glPopMatrix();
        }

        glPushMatrix();
        glTranslatef(0,height,0);
        draw_cylinder(1.5*radius_bottom,1.5*radius_top,num_blocks_depth*depth-width);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0,height/3.0,0);
        draw_cylinder(1.5*radius_bottom,1.5*radius_top,num_blocks_depth*depth-width);
        glPopMatrix();

        glPopMatrix();
    }

    void make_boundary(int num)
    {
        if(num == 1)
        {
            float x = depth * 2.0 / num_blocks_depth + 50.0;
            for(int i=0; i<(num_blocks_depth<<1); i+=1)
            {
                boundary_grass(0,8,i*x);
                boundary_grass(width,8,i*x);
            }
        }
        else if(num == 2)
        {
            boundary_road(0,8,0,1,1,10);
            boundary_road(width,8,0,1,1,10);
        }
    }

    void apply_texture()
    {
        glPushMatrix();
        glScalef(0.5,0.5,0.5);
        glEnable(GL_TEXTURE_2D);

        float factorZ = 1.0;
        float factorX = 1.05;

        //glEnable(GL_TEXTURE_GEN_S);
        //glEnable(GL_TEXTURE_GEN_T);
        //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_ONE_MINUS_SRC_ALPHA);
        glBindTexture(GL_TEXTURE_2D,texture_track[world_choosen]);

        //TOP
        glBegin (GL_QUADS);
        glTexCoord2d(0.0, factorZ);
        glVertex3f(-1.0, 1.0, -1.0);
        glTexCoord2d(0.0, 0.0);
        glVertex3f(-1.0,1.0,1.0);
        glTexCoord2d(factorX, 0.0);
        glVertex3f(1.0,1.0,1.0);
        glTexCoord2d(factorX, factorZ);
        glVertex3f(1.0,1.0,-1.0);
        glEnd();

        //BOTTOM
        glBegin (GL_QUADS);
        glTexCoord2d(factorX, factorZ);
        glVertex3f(-1.0,-1.0,-1.0);
        glTexCoord2d(0.0, factorZ);
        glVertex3f(1.0,-1.0,-1.0);
        glTexCoord2d(0.0, 0.0);
        glVertex3f(1.0,-1.0,1.0);
        glTexCoord2d(factorX, 0.0);
        glVertex3f(-1.0,-1.0,1.0);
        glEnd();

        glBindTexture(GL_TEXTURE_2D,texture_side[world_choosen]);

        //FRONT
        //glColor4f(1,1,1,1);
        glBegin (GL_QUADS);
        glTexCoord2d(0.0, 0.0);
        glVertex3f(-1.0,-1.0,1.0);
        glTexCoord2d(factorX, 0.0);
        glVertex3f(1.0,-1.0,1.0);
        glTexCoord2d(factorX, factorZ);
        glVertex3f(1.0,1.0,1.0);
        glTexCoord2d(0.0, factorZ);
        glVertex3f(-1.0,1.0,1.0);
        glEnd();

        //BACK
        glBegin (GL_QUADS);
        glTexCoord2d(factorX, 0.0);
        glVertex3f(-1.0,-1.0,-1.0);
        glTexCoord2d(factorX, factorZ);
        glVertex3f(-1.0,1.0,-1.0);
        glTexCoord2d(0.0, factorZ);
        glVertex3f(1.0,1.0,-1.0);
        glTexCoord2d(0.0, 0.0);
        glVertex3f(1.0,-1.0,-1.0);
        glEnd();

        //RIGHT
        glBegin (GL_QUADS);
        glTexCoord2d(factorX, 0.0);
        glVertex3f(1.0,-1.0,-1.0);
        glTexCoord2d(factorX, factorZ);
        glVertex3f(1.0,1.0,-1.0);
        glTexCoord2d(0.0, factorZ);
        glVertex3f(1.0,1.0,1.0);
        glTexCoord2d(0.0, 0.0);
        glVertex3f(1.0,-1.0,1.0);
        glEnd();

        //LEFT
        glBegin (GL_QUADS);
        glTexCoord2d(0.0, 0.0);
        glVertex3f(-1.0,-1.0,-1.0);
        glTexCoord2d(factorX, 0.0);
        glVertex3f(-1.0,-1.0,1.0);
        glTexCoord2d(factorX, factorZ);
        glVertex3f(-1.0,1.0,1.0);
        glTexCoord2d(0.0, factorZ);
        glVertex3f(-1.0,1.0,-1.0);
        glEnd();

        glDisable(GL_TEXTURE_2D);
        //glDisable(GL_TEXTURE_GEN_S);
        //glDisable(GL_TEXTURE_GEN_T);
        glPopMatrix();
    }

    void design(float trans_x,float trans_y,float trans_z)
    {
        glPushMatrix();
        glTranslatef(trans_x,trans_y,trans_z);

        for(int x = 0; x < num_blocks_width; x+=1)
        {
            for (int z = 0; z < num_blocks_depth; z+=1)
            {
                if(coins[x][z])
                {
                    glPushMatrix();
                    glTranslatef((2*x+1)*1.0*(width)/2,height/2.0 + 5 +(moving[x][z]?block_motion_value[x][z]:0) ,(2*z+1)*1.0*(depth)/2);
                    draw_coin(5);
                    glPopMatrix();
                }
                if(missing[x][z])
                    continue;
                glPushMatrix();
                glTranslatef((2*x+1)*1.0*(width)/2,moving[x][z]?block_motion_value[x][z]:0,(2*z+1)*1.0*(depth)/2);
                glScalef(width,height,depth);
                apply_texture();
                glutSolidCube(1);
                glPopMatrix();
            }
        }
        glPushMatrix();
        make_boundary(2);
        //gen_coins_pattern(0,22,height,200);
        glPopMatrix();
        glPopMatrix();
    }

    float get_center_x()
    {
        return (num_blocks_width*1.0/2.0)*1.0*width;
    }

    float get_center_z()
    {
        return (num_blocks_depth*1.0/2.0)*1.0*depth;
    }

    float get_tile_center_x(int x)
    {
        x -= 1;
        return (2.0*x+1)*1.0*width/2.0;
    }

    float get_tile_center_z(int z)
    {
        z -= 1;
        return (2.0*z+1)*1.0*depth/2.0;
    }

    int get_num_blocks_width()
    {
        return num_blocks_width;
    }

    int get_num_blocks_depth()
    {
        return num_blocks_depth;
    }
};
