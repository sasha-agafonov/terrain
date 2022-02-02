#include <GL/glu.h>

#include <QTimer>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>


#include "world.h"
#include "noise.h"


#define PGM_8_BIT 255
#define PGM_16_BIT 65535
#define PI_EXTERN 3.141592653589793238462643383279502884197169399375105820974944592307816406286


world :: world(QGLFormat format, QWidget* parent) : QGLWidget(parent) {
    setFormat(format);
    tick = 0;
    zoom = 0;
    setCursor(Qt::BlankCursor);
    this->setFocusPolicy(Qt::StrongFocus);


    //painter = new QPainter(this);
    setMouseTracking(true);
//    grabMouse();

    direction_x = 0;
    direction_y = 0;
    direction_z = 0;

    forward = false;
    back = false;
    left = false;
    right = false;
    up = false;
    down = false;
    menu = false;

    cx = 0;
    cy = 0;
    cz = 0;

    noisy = new noise();

    cursor_x = 270;
    cursor_y = 90;
    camera = new fpp_camera(cursor_x, cursor_y);

    terrarray = new int[10000];

    noisy -> black_noise();
    //this -> black_noise();

    mouse_prev_pos_x = 0;
    mouse_prev_pos_y = 0;


    camera_position_x = 0;
    camera_position_y = 0;
    camera_position_z = 0;


    QPoint n;
    mouse_position = n;

    shake = 0;
    shake_right = true;
    jump = false;

    this -> terra = new terrain();


//    terrain_mx(10, std :: vector <int>, (10));
    //terrain_mx.resize(10, std :: vector <int> (10));

    reload();
    load_terrain();
    terra -> load_terrain();

//    view_x = 0.;
//    view_y = 0.;
//    view_z = 0.;
}

void world :: cameraUpdate(double x, double y, double z) {
    zoom += 1;
    //this -> repaint();
}


// mouse
void world :: mouseMoveEvent(QMouseEvent* event) {

    QPoint mouse_position_change = (event -> globalPos() - mapToGlobal(rect().center()));

    if (mouse_position_change.x() != 0 && mouse_position_change.y() != 0) {

        cursor_x -= ((double) mouse_position_change.x() * 0.005);
        cursor_y += ((double) mouse_position_change.y() * 0.005);

        camera -> set_angles(cursor_x, cursor_y);

        cursor().setPos(mapToGlobal(rect().center()));
    }
}


void world :: mousePressEvent(QMouseEvent* event) {

}

// keyboard
void world :: keyPressEvent(QKeyEvent* event) {

    if (event -> isAutoRepeat()) return;
    switch (event -> key()) {
        case Qt :: Key_W:
            forward = true;
            break;
        case Qt :: Key_S:
            back = true;
            break;
        case Qt :: Key_A:
            left = true;
            break;
        case Qt :: Key_D:
            right = true;
            break;
        case Qt :: Key_Space:
            up = true;
            break;
        case Qt :: Key_Shift:
            down = true;
            break;
//        case Qt :: Key_Escape:
//            if (menu) menu = false;
//            else menu = true;
//            break;
    }
    repaint();
}

void world :: keyReleaseEvent(QKeyEvent* event) {

    if (event -> isAutoRepeat()) return;
    switch (event -> key()) {
        case Qt :: Key_W:
            forward = false;
            break;
        case Qt :: Key_S:
            back = false;
            break;
        case Qt :: Key_A:
            left = false;
            break;
        case Qt :: Key_D:
            right = false;
            break;
        case Qt :: Key_Space:
            up = false;
            break;
        case Qt :: Key_Shift:
            down = false;
            break;
    }
    repaint();
}

void world :: update_scene() {
    tick++;
    this -> repaint();
}

void world :: reload() {

    if (terrain_mx.size() > 0) for (int i = 0; i < terrain_mx.size(); i++) terrain_mx[i].clear();
    terrain_mx.clear();
//    terrain_mx = terra -> load_terrain();

}


void world :: load_terrain() {

    using namespace std;

    // open .pgm image
    ifstream terrain_data("heightmap.pgm");

    // or don't
    if (terrain_data.fail()) return;

    int terrain_size = 0;
    string happy_string, unhappy_string, str;
    istringstream happy_string_stream;

    // image file checks
    for (int i = 0; i < 3; i++) {
        getline(terrain_data, happy_string);

        // check P2 header
        if (i == 0 && happy_string.compare("P2") != 0) return;

        // get terrain dimensions
        else if (i == 1) terrain_size = stoi(happy_string.substr(0, happy_string.find(' ')));

        // accept 8-bit or 16-bit pgm only.
        else if (i == 2 && stoi(happy_string) != PGM_8_BIT && stoi(happy_string) != PGM_16_BIT) return;
    }

    for (int i = 0; i < terrain_mx.size(); i++) terrain_mx[i].clear();

    terrain_mx.clear();
    //terrain_mx.resize(terrain_size, vector <int> (terrain_size));

    for (int i = 0; i < terrain_size; i++) {

        getline(terrain_data, happy_string);

        istringstream unhappy_string_stream(happy_string);
        vector <int> pixel_row;

        while (getline(unhappy_string_stream, unhappy_string, ' ')) pixel_row.push_back(stoi(unhappy_string));

        terrain_mx.push_back(pixel_row);

    }
}


static const float PI = 3.1415926535;

void world :: initializeGL() {

    glClearColor(0.4, 0.5, 0.8, 0.0);
    glEnable(GL_MULTISAMPLE);
}

void world :: resizeGL(int w, int h) {

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-20 * ((double)w/h) * (1. / sqrt(3)), 20 * ((double)w/h)* (1. / sqrt(3)), -20* (1. / sqrt(3)), 20* (1. / sqrt(3)), 20, 1000.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_FOG);

    glFogi(GL_FOG_MODE, GL_LINEAR);
    glFogf(GL_FOG_START, 100.f);
    glFogf(GL_FOG_END, 700.f);

    float fcolour[3]={0.4, 0.5, 0.8};

    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glFogfv(GL_FOG_COLOR, fcolour);
    glHint(GL_FOG_HINT, GL_NICEST);
    glFogf(GL_FOG_DENSITY,1.f);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat light_pos[] = {0., 0., 1., 0.};

    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

}


void world :: paintGL() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_NORMALIZE);
    glShadeModel(GL_FLAT);

    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);

    glLoadIdentity();



//    if (shake < 0.2 ) {
//        shake += 0.05;
//        if (shake )
//    }

//    else if (shake > 1.8 && shake_right == true) {
//        shake_right = false;
//        shake -= 0.05;
//        }
    // camera

//    if (jump && camera_position_z < 8) {
//        camera_position_z += 0.3;
//    }
//    else if (jump && camera_position_z > 8) {
//        jump = false;
//    }
//    if (!jump && camera_position_z > 0) {
//        camera_position_z -= 0.2;
//    }

//    double view_vector_x = look_x - direction_x;
//    double view_vector_y = ;
//    double view_vector_z = ;

    //double view_vector_y = 100 - (140 - camera_position_x + look_x) - (12 + camera_position_z + look_y) - (140 - camera_position_y);
    camera -> move_camera(forward, back, left, right, up, down);
    camera -> look();


              // look from
    gluLookAt(camera -> position_x, camera -> position_y, camera -> position_z ,
              // look at
              camera -> look_at_x, camera -> look_at_y, camera -> look_at_z,
              // camera rotation
              0., 0., 1.);

    glEnable(GL_FOG);
    glPushMatrix();
    glScalef(15, 15, 15);
   // glScalef(5 + direction_x, 5 + direction_ydddddddddddddddd, 5 + direction_z);
          //glRotatef(180, 0., 0., 1);

    glPushMatrix();
    //gluDisk(gluNewQuadric(), 0, 12, 12, 12);

    //gluSphere(gluNewQuadric(), 1, 12 ,12);
    glPopMatrix();

    // pole
//    glPushMatrix();
//    glTranslatef(23, 23 ,1);
//    gluCylinder(gluNewQuadric(), 1, 1, 12 ,12,12);
//    glPopMatrix();


    // test terrain



   terra -> draw_terrain();


//   if (menu) {
//       QPainter p(this);
//         p.setPen(Qt::red);
//         p.drawLine(rect().topLeft(), rect().bottomRight());
//   }




    glLoadIdentity();

    glFlush();
}
