// compilation: g++ test_glut.cpp -o test_glut.o -lalleggl -lGL -lglut &&  setfattr -n user.pax.flags -v "m" ./test_glut.o  && ./test_glut.o

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <allegro.h>
#include <alleggl.h>
#include <iostream>
#include <cmath>

float angle = 0.0;
float zoom = 1.0;
float step_z=-5.0;
float camera_x = 0.0;
float camera_y = 0.0;
float camera_z = -5.0;
float view_angle = 3.0;
 
void InitAllegro() {

	allegro_init();
	install_allegro_gl();
	install_keyboard();
	install_timer();
}
void InitGL() {
	allegro_gl_set(AGL_DOUBLEBUFFER, 1);
	allegro_gl_set(AGL_WINDOWED, TRUE);
	allegro_gl_set( AGL_COLOR_DEPTH, 32 );
	allegro_gl_set( AGL_Z_DEPTH, 8 );
	allegro_gl_set( AGL_SUGGEST, AGL_COLOR_DEPTH | AGL_Z_DEPTH );

    if ( set_gfx_mode( GFX_OPENGL, 1280, 720, 0, 0 ) ) {
        allegro_message( "Cannot create window" );
		exit( 1 );
	}
	glEnable(GL_DEPTH_TEST);
	glViewport( 0, 0, SCREEN_W, SCREEN_H );
    glClearColor( 0, 0, 0, 0 );
}

void DrawGround() {
    glPushMatrix();
    for(int i=0; i<50; i++) {
        for(int j=0; j<50; j++) {

            if( (i+j)%2 ) glColor3f(0,0,0);
            else glColor3f(1,1,1);

            glBegin(GL_QUADS);
            glVertex3f(-25+i, -1, -25+j);
            glVertex3f(-25+i+1, -1, -25+j);
            glVertex3f(-25+i+1, -1, -25+j+1);
            glVertex3f(-25+i, -1, -25+j+1);
            glEnd();
        }
    }
    glPopMatrix();
}

void RenderScene() {
    // clear buffer
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    // set up camera, coords of eye point, coords of reference point
    gluPerspective(45.0f, SCREEN_W/SCREEN_H, 1.0, 150.0);
    gluLookAt (camera_x - 1*sin(angle),0,camera_z + 1*cos(angle),camera_x + 5*sin(angle),camera_y,camera_z - 5*cos(angle),0,1,0);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    glTranslatef(camera_x,0,camera_z);
    glRotatef(angle,0,1,0);

    // draw sphere in place of camera
    glPushMatrix();
    glTranslatef(0,-0.5,0);
    glColor3f(0,0,1);
    glutSolidSphere(0.1,30,30);
    glPopMatrix();

//    glEnable(GL_BLEND);
//    glDisable(GL_DEPTH_TEST);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glPushMatrix();
    glTranslatef( camera_x, 0.0f, camera_z );
    DrawGround();
    // draw quads
    glBegin( GL_QUADS );        //front
        //glColor4f( 1.0f, 0.0f, 0.0f, 1.0 );
        glColor3f( 1.0f, 0.0f, 0.0f );
        glVertex3f( -1.0f, -1.0f, 0.0f );
        glVertex3f(  1.0f, -1.0f, 0.0f );
        glVertex3f(  1.0f,  1.0f, 0.0f );
        glVertex3f( -1.0f,  1.0f, 0.0f );
    glEnd();

    glBegin( GL_QUADS );        //back
        //glColor4f( 0.0f, 1.0f, 0.0f, 1.0 );
        glColor3f( 0.0f, 1.0f, 0.0f );
        glVertex3f( -1.0f, -1.0f, -1.0f );
        glVertex3f(  1.0f, -1.0f, -1.0f );
        glVertex3f(  1.0f,  1.0f, -1.0f );
        glVertex3f( -1.0f,  1.0f, -1.0f );
    glEnd();

    glBegin( GL_QUADS );        //down
        //glColor4f( 0.3f, 0.8f, 0.3f, 1.0 );
        glColor3f( 0.3f, 0.8f, 0.3f );
        glVertex3f( -1.0f, -1.0f, 0.0f );
        glVertex3f(  1.0f, -1.0f, 0.0f );
        glVertex3f(  1.0f,  -1.0f, -1.0f );
        glVertex3f( -1.0f,  -1.0f, -1.0f );
    glEnd();

    glBegin( GL_QUADS );        //up
        //glColor4f( 0.0f, 0.5f, 0.2f, 0.7 );
        glColor3f( 0.0f, 0.5f, 0.2f );
        glVertex3f( -1.0f, 1.0f, 0.0f );
        glVertex3f(  1.0f, 1.0f, 0.0f );
        glVertex3f(  1.0f,  1.0f, -1.0f );
        glVertex3f( -1.0f,  1.0f, -1.0f );
    glEnd();

    glBegin( GL_QUADS );        //right
        //glColor4f( 0.5f, 0.2f, 0.1f, 1.0 );
        glColor3f( 0.5f, 0.2f, 0.1f );
        glVertex3f( 1.0f, -1.0f, 0.0f );
        glVertex3f(  1.0f, -1.0f, -1.0f );
        glVertex3f(  1.0f,  1.0f, -1.0f );
        glVertex3f( 1.0f,  1.0f, 0.0f );
    glEnd();

    glBegin( GL_QUADS );        //left
        //glColor4f( 0.5f, 0.2f, 0.1f, 1.0 );
        glColor3f( 0.3f, 0.3f, 0.3f );
        glVertex3f( -1.0f, -1.0f, 0.0f );
        glVertex3f(  -1.0f, -1.0f, -1.0f );
        glVertex3f(  -1.0f,  1.0f, -1.0f );
        glVertex3f( -1.0f,  1.0f, 0.0f );
    glEnd();
    glPopMatrix();


    glPushMatrix();
    glTranslatef( camera_x-3, 0.0f, camera_z+10 );
    glBegin( GL_TRIANGLES);
        //glColor4f(1,1,0,1);
        glColor3f(1,1,0);
        glVertex3f(-1,-1,0);
        glVertex3f(1,-1,0);
        glVertex3f(1,1,0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(camera_x+7,0.0f,camera_z+9);
    glBegin( GL_TRIANGLES);
        //glColor4f(0,1,1,1);
        glColor3f(0.0f,1.0f,1.0f);
        glVertex3f(-1,-1,0);
        glVertex3f(1,-1,0);
        glVertex3f(1,1,0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(camera_x-15,0.0f,camera_z-3);
    glBegin( GL_TRIANGLES);
       // glColor4f(0.5,0.5,0.5,1);
        glColor3f( 0.5,0.5,0.5 );
        glVertex3f(-1,-1,0);
        glVertex3f(1,-1,0);
        glVertex3f(1,1,0);
    glEnd();
    glPopMatrix();

//    glEnable(GL_DEPTH_TEST);
//    glDisable(GL_BLEND);

    glFlush();
    allegro_gl_flip();
}

int main(int argc, char* argv[]) {
	InitAllegro();
	InitGL();
    glutInit(&argc, argv);

	int i=0;
    while(i<10000) {
        if(key[KEY_UP]) {
            camera_z+=cos(angle)*0.1;
            camera_x-=sin(angle)*0.1;
        }
        if(key[KEY_DOWN]) {
            camera_z-=cos(angle)*0.1;
            camera_x+=sin(angle)*0.1;
        }
        if(key[KEY_RIGHT]) angle+=0.01;
        if(key[KEY_LEFT]) angle-=0.01;

        if(key[KEY_W]) camera_y+=0.1;
        if(key[KEY_S]) camera_y-=0.1;

		if(key[KEY_ESC]) exit(0);

        RenderScene();
		i++;
	}
	allegro_exit();
	remove_allegro_gl();
}
END_OF_MAIN();
