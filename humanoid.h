class Humanoid
{
    float body_angle;
    float left_shoulder_angle;
    float left_elbow_angle;
    float right_shoulder_angle;
    float right_elbow_angle;
    float left_thigh_angle;
    float left_knee_angle;
    float right_thigh_angle;
    float right_knee_angle;
    float left_thigh_angleX;
    float right_thigh_angleX;
public:
    float loc_x;
    float loc_y;
    float loc_z;
    void draw_sphere(float radius)
    {
        GLUquadricObj *x = gluNewQuadric();
        gluQuadricDrawStyle(x,GLU_FILL);
        gluQuadricNormals(x,GLU_SMOOTH);
        glEnable(GL_TEXTURE_2D);
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
        glBindTexture(GL_TEXTURE_2D,texture);
        gluQuadricTexture(x,1);
        gluSphere(x,radius,50,10);
        glDisable(GL_TEXTURE_2D);
    }

    void draw_cylinder(float radius1,float radius2,float height)
    {
        GLUquadricObj *x = gluNewQuadric();
        gluQuadricDrawStyle(x,GLU_FILL);
        gluQuadricNormals(x,GLU_SMOOTH);
        if(power_taken && power_choosen == SPEED )
        {
            glColor4f(0.5,0,0,glow_value);
            glow_value += 0.05;
            if(glow_value > 1.0)
                glow_value = 0.05;
        }
        else if(power_taken && (power_choosen == INVISIBLE ))
        {
            glColor4f(0,0,0.5,glow_value);
            glow_value += 0.05;
            if(glow_value > 1.0)
                glow_value = 0.05;
        }
        else if(!power_taken)
        {
            glEnable(GL_TEXTURE_2D);
            glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
            glBindTexture(GL_TEXTURE_2D,texture1);
            gluQuadricTexture(x,1);
        }

        gluCylinder(x,radius1,radius2,height,50,10);
        glRotatef(180, 1,0,0);
        gluDisk(x,0.0,radius1,50,1);
        glRotatef(180,1,0,0);
        glTranslatef(0.0,0.0,height);
        gluDisk(x,0.0,radius2,50,1);
        glTranslatef(0.0,0.0,-height);
        if(power_taken && (power_choosen == SPEED || power_choosen == INVISIBLE))
            glColor4f(1.0,1.0,1.0,1.0);
        else if(!power_taken)
            glDisable(GL_TEXTURE_2D);

    }

    void left_shoulder_joint(float trans_x,float trans_y,float trans_z)
    {
        glPushMatrix();
        glTranslatef(trans_x,trans_y,trans_z);
        draw_sphere(1.25);
        left_upper_arm(0,0,0);
        glPopMatrix();
    }

    void left_upper_arm(float trans_x,float trans_y,float trans_z)
    {
        glPushMatrix();
        glTranslatef(trans_x,trans_y,trans_z);
        glRotatef(-15,0,1,0);
        glRotatef(left_shoulder_angle,1,0,0);
        draw_cylinder(1,1,4);
        joint_left_arm(0,0,3.75);
        glPopMatrix();
    }

    void joint_left_arm(float trans_x,float trans_y,float trans_z)
    {
        glPushMatrix();
        glTranslatef(trans_x,trans_y,trans_z);
        draw_sphere(1.25);
        left_lower_arm(0,0,0.5);
        glPopMatrix();
    }

    void left_lower_arm(float trans_x,float trans_y,float trans_z)
    {
        glPushMatrix();
        glTranslatef(trans_x,trans_y,trans_z);
        glRotatef(left_elbow_angle,1,0,0);
        draw_cylinder(1,0.8,4);
        left_palm(0,0,3.5);
        glPopMatrix();
    }

    void left_palm(float trans_x,float trans_y,float trans_z)
    {
        glPushMatrix();
        glTranslatef(trans_x,trans_y,trans_z);
        draw_sphere(1.2);
        glPopMatrix();
    }

    void right_shoulder_joint(float trans_x,float trans_y,float trans_z)
    {
        glPushMatrix();
        glTranslatef(trans_x,trans_y,trans_z);
        draw_sphere(1.25);
        right_upper_arm(0,0,0);
        glPopMatrix();
    }

    void right_upper_arm(float trans_x,float trans_y,float trans_z)
    {
        glPushMatrix();
        glTranslatef(trans_x,trans_y,trans_z);
        glRotatef(15,0,1,0);
        glRotatef(right_shoulder_angle,1,0,0);
        draw_cylinder(1,1,4);
        joint_right_arm(0,0,3.75);
        glPopMatrix();
    }

    void joint_right_arm(float trans_x,float trans_y,float trans_z)
    {
        glPushMatrix();
        glTranslatef(trans_x,trans_y,trans_z);
        draw_sphere(1.25);
        right_lower_arm(0,0,0.5);
        glPopMatrix();
    }

    void right_lower_arm(float trans_x,float trans_y,float trans_z)
    {
        glPushMatrix();
        glTranslatef(trans_x,trans_y,trans_z);
        glRotatef(right_elbow_angle,1,0,0);
        draw_cylinder(1,0.8,4);
        right_palm(0,0,3.5);
        glPopMatrix();
    }

    void right_palm(float trans_x,float trans_y,float trans_z)
    {
        glPushMatrix();
        glTranslatef(trans_x,trans_y,trans_z);
        draw_sphere(1.2);
        glPopMatrix();
    }

    void left_upper_leg(float trans_x,float trans_y,float trans_z)
    {
        glPushMatrix();
        glTranslatef(trans_x,trans_y,trans_z);
        glRotatef(left_thigh_angle,1,0,0);
        glRotatef(left_thigh_angleX,0,1,0);
        draw_cylinder(1.2,1,6);
        joint_left_leg(0,0,6.25);
        glPopMatrix();
    }

    void joint_left_leg(float trans_x,float trans_y,float trans_z)
    {
        glPushMatrix();
        glTranslatef(trans_x,trans_y,trans_z);
        draw_sphere(1.25);
        left_lower_leg(0,0,0.5);
        glPopMatrix();
    }

    void left_lower_leg(float trans_x,float trans_y,float trans_z)
    {
        glPushMatrix();
        glTranslatef(trans_x,trans_y,trans_z);
        glRotatef(left_knee_angle,1,0,0);
        draw_cylinder(1,0.8,5);
        left_foot(0,0,5);
        glPopMatrix();
    }

    void left_foot(float trans_x,float trans_y,float trans_z)
    {
        glPushMatrix();
        glTranslatef(trans_x,trans_y,trans_z);
        glScalef(1.5,1,1);
        draw_sphere(1);
        glPopMatrix();
    }

    void right_upper_leg(float trans_x,float trans_y,float trans_z)
    {
        glPushMatrix();
        glTranslatef(trans_x,trans_y,trans_z);
        glRotatef(right_thigh_angle,1,0,0);
        glRotatef(right_thigh_angleX,0,1,0);
        draw_cylinder(1.2,1,6);
        joint_right_leg(0,0,6.25);
        glPopMatrix();
    }

    void joint_right_leg(float trans_x,float trans_y,float trans_z)
    {
        glPushMatrix();
        glTranslatef(trans_x,trans_y,trans_z);
        draw_sphere(1.25);
        right_lower_leg(0,0,0.5);
        glPopMatrix();
    }

    void right_lower_leg(float trans_x,float trans_y,float trans_z)
    {
        glPushMatrix();
        glTranslatef(trans_x,trans_y,trans_z);
        glRotatef(right_knee_angle,1,0,0);
        draw_cylinder(1,0.8,5);
        right_foot(0,0,5);
        glPopMatrix();
    }

    void right_foot(float trans_x,float trans_y,float trans_z)
    {
        glPushMatrix();
        glTranslatef(trans_x,trans_y,trans_z);
        glScalef(1.5,1,1);
        draw_sphere(1);
        glPopMatrix();
    }

    void head(float trans_x,float trans_y,float trans_z)
    {
        glPushMatrix();
        glTranslatef(trans_x,trans_y,trans_z);
        draw_cylinder(2,2,4.5);
        glPopMatrix();
    }

    void body(float trans_x,float trans_y,float trans_z,float ba,float lsa,float lea,float rsa,float rea,float lta,float lka,float rta,float rka,
              float lta_x,float rta_x)
    {
        body_angle = ba;
        left_shoulder_angle = lsa;
        left_elbow_angle = lea;
        right_shoulder_angle = rsa;
        right_elbow_angle = rea;
        left_thigh_angle = lta;
        left_knee_angle = lka;
        right_thigh_angle = rta;
        right_knee_angle = rka;
        left_thigh_angleX = lta_x;
        right_thigh_angleX = rta_x;

        glPushMatrix();
        if(!robot_slide)
            glTranslatef(trans_x,trans_y,trans_z);
        else
            glTranslatef(trans_x,trans_y-15,trans_z);
        if(!robot_slide)
            glRotatef(90.0,1,0,0);
        else
            glRotatef(0,1,0,0);
        glRotatef(body_angle,0,0,1);

        draw_cylinder(4,4,12.5);

        head(0,0,-4.5);
        left_shoulder_joint(-4.5,0,1);
        right_shoulder_joint(4.5,0,1);
        left_upper_leg(-2,0,12.5);
        right_upper_leg(2,0,12.5);

        glPopMatrix();
    }
};
