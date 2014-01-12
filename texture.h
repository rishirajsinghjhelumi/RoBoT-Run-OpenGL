GLuint LoadTexture1( const char * filename, int width, int height )
{
    GLuint texture;
    unsigned char * data;
    FILE * file;
    file = fopen( filename, "rb" );
    if ( file == NULL ) return 0;
    data = (unsigned char *)malloc( width * height * 3 );
    fread( data, width * height * 3, 1, file );
    fclose( file );

    glGenTextures( 1, &texture );
    glBindTexture( GL_TEXTURE_2D, texture );
    glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );

    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

    free( data );
    return texture;
}

GLuint LoadTexture(const char *filename, int width, int height)
{
    GLuint texture;
    unsigned char *data;
    FILE *file;
    file = fopen(filename, "rb");
    if (file == NULL) return 0;
    data = (unsigned char*) malloc(width * height * 4);
    fread(data, width * height * 4, 1, file);
    fclose(file);
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPEAT);

    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_DECAL);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_DECAL);
    //glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    //glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    //glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    //glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);

    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR );

    /*if (strstr((char*)glGetString(GL_EXTENSIONS),"GL_EXT_texture_filter_anisotropic"))
    {
        float f;
        glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT,&f);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, f);
    }*/
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //glTexGenf(GL_S, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
    //glTexGenf(GL_T, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);

    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_BGR, GL_UNSIGNED_BYTE, data);
    free(data);

    return texture;
}

void load_textures()
{
    texture = LoadTexture("./textures/1.bmp",400,300);
    texture1 = LoadTexture("./textures/2.bmp",300,200);

    texture_background[0] = LoadTexture("./textures/World1/bg.bmp",1920,1080);
    texture_background[1] = LoadTexture("./textures/World2/bg.bmp",1920,1201);
    texture_background[2] = LoadTexture("./textures/World3/bg.bmp",1920,1200);
    texture_background[3] = LoadTexture("./textures/World4/bg.bmp",1280,1024);
    texture_background[4] = LoadTexture("./textures/World5/bg.bmp",1920,1200);

    texture_track[0] = LoadTexture("./textures/World1/track.bmp",1200,1200);
    texture_track[1] = LoadTexture("./textures/World2/track.bmp",480,310);
    texture_track[2] = LoadTexture("./textures/World3/track.bmp",480,360);
    texture_track[3] = LoadTexture("./textures/World4/track.bmp",640,480);
    texture_track[4] = LoadTexture("./textures/World5/track.bmp",1024,1024);

    texture_side[0] = LoadTexture("./textures/World1/side.bmp",400,400);
    texture_side[1] = LoadTexture("./textures/World2/side.bmp",280,280);
    texture_side[2] = LoadTexture("./textures/World3/side.bmp",512,320);
    texture_side[3] = LoadTexture("./textures/World4/side.bmp",240,256);
    texture_side[4] = LoadTexture("./textures/World5/side.bmp",512,512);

    texture_boundary[0] = LoadTexture("./textures/World1/bd.bmp",200,200);
    texture_boundary[1] = LoadTexture("./textures/World2/bd.bmp",520,389);
    texture_boundary[2] = LoadTexture("./textures/World3/bd.bmp",448,336);
    texture_boundary[3] = LoadTexture("./textures/World4/bd.bmp",640,480);
    texture_boundary[4] = LoadTexture("./textures/World5/bd.bmp",448,336);

    coin_texture = LoadTexture("./textures/Powers/gold.bmp",512,512);
    magnet_texture = LoadTexture("./textures/Powers/magnet.bmp",600,600);
    invisible_texture = LoadTexture("./textures/Powers/invisible.bmp",1920,1200);
    speed_texture = LoadTexture("./textures/Powers/speed.bmp",600,800);
    gem_texture = LoadTexture("./textures/Powers/ruby.bmp",512,512);

    wood_texture = LoadTexture("./textures/Obstacles/wood.bmp",100,100);
    laser_texture = LoadTexture("./textures/Obstacles/laser.bmp",400,600);
    metal_texture = LoadTexture("./textures/Obstacles/grid.bmp",200,200);

}
