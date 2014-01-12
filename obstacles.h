class Hurdle
{
public:
    void draw_cylinder(float radius1,float radius2,float height,int num)
    {
        GLUquadricObj *x = gluNewQuadric();
        gluQuadricDrawStyle(x,GLU_FILL);
        gluQuadricNormals(x,GLU_SMOOTH);
        glEnable(GL_TEXTURE_2D);
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
        if(num==0)
            glBindTexture(GL_TEXTURE_2D,wood_texture);
        else if(num==1)
            glBindTexture(GL_TEXTURE_2D,wood_texture);
        else if(num==2)
            glBindTexture(GL_TEXTURE_2D,laser_texture);
        else if(num==3)
            glBindTexture(GL_TEXTURE_2D,metal_texture);
        gluQuadricTexture(x,1);
        gluCylinder(x,radius1,radius2,height,50,10);
        glRotatef(180, 1,0,0);
        gluDisk(x,0.0,radius1,50,1);
        glRotatef(180,1,0,0);
        glTranslatef(0.0,0.0,height);
        gluDisk(x,0.0,radius2,50,1);
        glTranslatef(0.0,0.0,-height);
        glDisable(GL_TEXTURE_2D);
    }

    void draw_fire_obstacle(float radius_top,float radius_bottom,float height,float x,float y,float z)
    {
        glTranslatef(x,y,z);
        glRotatef(-90,1,0,0);
        draw_cylinder(radius_bottom,radius_top,height,0);
        glTranslatef(0,0,height);
        glRotatef(90,0,1,0);
        draw_cylinder(1.1*radius_bottom,1.1*radius_top,no_lane_x*lane_width_x,1);
        //draw_fire(no_lane_x*lane_width_x,3*radius_bottom,3*radius_bottom);
        glTranslatef(0,0,1*no_lane_x*lane_width_x);
        glRotatef(90,0,1,0);
        draw_cylinder(radius_top,radius_bottom,height,0);
    }

    void draw_laser_obstacle(float radius_top,float radius_bottom,float height,float x,float y,float z)
    {
        glTranslatef(x,y,z);
        glRotatef(-90,1,0,0);
        draw_cylinder(radius_bottom,radius_top,height,3);
        glTranslatef(0,0,height);
        glRotatef(90,0,1,0);
        draw_cylinder(0.15*radius_bottom,0.15*radius_top,no_lane_x*lane_width_x,2);
        glTranslatef(height/2.0,0,0);
        draw_cylinder(0.15*radius_bottom,0.15*radius_top,no_lane_x*lane_width_x,2);
        glTranslatef(-height/2.0,0,0);
        glTranslatef(height/4.0,0,0);
        draw_cylinder(0.15*radius_bottom,0.15*radius_top,no_lane_x*lane_width_x,2);
        glTranslatef(-height/4.0,0,0);
        glTranslatef(height/8.0,0,0);
        draw_cylinder(0.15*radius_bottom,0.15*radius_top,no_lane_x*lane_width_x,2);
        glTranslatef(-height/8.0,0,0);
        glTranslatef(3*height/8.0,0,0);
        draw_cylinder(0.15*radius_bottom,0.15*radius_top,no_lane_x*lane_width_x,2);
        glTranslatef(-3*height/8.0,0,0);
        glTranslatef(height/16.0,0,0);
        draw_cylinder(0.15*radius_bottom,0.15*radius_top,no_lane_x*lane_width_x,2);
        glTranslatef(-height/16.0,0,0);
        glTranslatef(3*height/16.0,0,0);
        draw_cylinder(0.15*radius_bottom,0.15*radius_top,no_lane_x*lane_width_x,2);
        glTranslatef(-3*height/16.0,0,0);
        glTranslatef(5*height/16.0,0,0);
        draw_cylinder(0.15*radius_bottom,0.15*radius_top,no_lane_x*lane_width_x,2);
        glTranslatef(-5*height/16.0,0,0);
        glTranslatef(7*height/16.0,0,0);
        draw_cylinder(0.15*radius_bottom,0.15*radius_top,no_lane_x*lane_width_x,2);
        glTranslatef(-7*height/16.0,0,0);
        //draw_electricity(no_lane_x*lane_width_x,3*radius_bottom,3*radius_bottom);
        glTranslatef(0,0,1*no_lane_x*lane_width_x);
        glRotatef(90,0,1,0);
        draw_cylinder(radius_top,radius_bottom,height,3);
    }

};
