class Magnet
{

public:

    void design(float radius,float x,float y,float z)
    {
        glTranslatef(x,y,z);
        GLUquadricObj *X = gluNewQuadric();
        gluQuadricDrawStyle(X,GLU_FILL);
        gluQuadricNormals(X,GLU_SMOOTH);
        glEnable(GL_TEXTURE_2D);
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
        glBindTexture(GL_TEXTURE_2D,magnet_texture);
        gluQuadricTexture(X,1);
        glRotatef(coin_rotate,0,1,0);
        glRotatef(90,0,1,0);
        glScalef(0.2,1,1);
        gluSphere(X,radius,50,10);
        glDisable(GL_TEXTURE_2D);
    }

};

class Invisible
{
public:

    void design(float radius,float x,float y,float z)
    {
        glTranslatef(x,y,z);
        GLUquadricObj *X = gluNewQuadric();
        gluQuadricDrawStyle(X,GLU_FILL);
        gluQuadricNormals(X,GLU_SMOOTH);
        glEnable(GL_TEXTURE_2D);
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
        glBindTexture(GL_TEXTURE_2D,invisible_texture);
        gluQuadricTexture(X,1);
        glRotatef(coin_rotate,0,1,0);
        glRotatef(90,0,1,0);
        glScalef(0.2,1,1);
        gluSphere(X,radius,50,10);
        glDisable(GL_TEXTURE_2D);
    }

};

class Speed
{
public:

    void design(float radius,float x,float y,float z)
    {
        glTranslatef(x,y,z);
        GLUquadricObj *X = gluNewQuadric();
        gluQuadricDrawStyle(X,GLU_FILL);
        gluQuadricNormals(X,GLU_SMOOTH);
        glEnable(GL_TEXTURE_2D);
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
        glBindTexture(GL_TEXTURE_2D,speed_texture);
        gluQuadricTexture(X,1);
        glRotatef(coin_rotate,0,1,0);
        glRotatef(90,0,1,0);
        glScalef(0.2,1,1);
        gluSphere(X,radius,50,10);
        glDisable(GL_TEXTURE_2D);
    }

};

class Gem
{
public:

    void draw_triangle(float x1,float y1,float z1,float x2,float y2,float z2,float x3,float y3,float z3)
    {
        glBegin(GL_TRIANGLES);
        glVertex3f(x1,y1,z1);
        glVertex3f(x2,y2,z2);
        glVertex3f(x3,y3,z3);
        glEnd();
    }

    void draw_pyramid()
    {
        glBegin(GL_TRIANGLES);

        glNormal3f(1,0,1);
        glTexCoord2f(0,0);
        glVertex3f(1,0,1);
        glNormal3f(0,2,0);
        glTexCoord2f(1,0);
        glVertex3f(0,2,0);
        glNormal3f(-1,0,1);
        glTexCoord2f(0,1);
        glVertex3f(-1,0,1);
        glNormal3f(-1,0,1);

        glTexCoord2f(0,0);
        glVertex3f(-1,0,1);
        glNormal3f(0,2,0);
        glTexCoord2f(1,0);
        glVertex3f(0,2,0);
        glNormal3f(-1,0,-1);
        glTexCoord2f(0,1);
        glVertex3f(-1,0,-1);
        glNormal3f(-1,0,-1);

        glTexCoord2f(0,0);
        glVertex3f(-1,0,-1);
        glNormal3f(0,2,0);
        glTexCoord2f(1,0);
        glVertex3f(0,2,0);
        glNormal3f(1,0,-1);
        glTexCoord2f(0,1);
        glVertex3f(1,0,-1);
        glNormal3f(1,0,-1);

        glTexCoord2f(0,0);
        glVertex3f(1,0,-1);
        glNormal3f(0,2,0);
        glTexCoord2f(1,0);
        glVertex3f(0,2,0);
        glNormal3f(1,0,1);
        glTexCoord2f(0,1);
        glVertex3f(1,0,1);
        glEnd();
    }

    void design(float length,float x,float y,float z)
    {
        glTranslatef(x,y,z);
        glPushMatrix();
        glRotatef(gem_rotate,0,1,0);
        glEnable(GL_TEXTURE_2D);
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
        glBindTexture(GL_TEXTURE_2D,gem_texture);
        glScalef(4,3,4);
        draw_pyramid();
        glRotatef(180,1,0,0);
        draw_pyramid();
        glDisable(GL_TEXTURE_2D);
        glPopMatrix();
    }
};
