#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <iostream>
#include <time.h>
#include "Constansts.h"
#include "Variables.h"
#include "image.h"
#include <vector>

const char* FILENAME0 = "floor_is_lava.bmp";
const char* FILENAME1 = "mars.bmp";

static int timer_active;

static void on_keyboard(unsigned char, int, int);
static void on_release(unsigned char, int, int);
static void on_timer(int);
static void on_reshape(int, int);
static void on_display(void);
static void make_obstacles(const int);
static void draw_obstacles(const int);
static void colision_detection();

static void draw_plane();
static void draw_ball();

static GLuint names[1];

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    glutInitWindowSize(WINDOW_HEIGHT, WINDOW_WIDTH);
    glutInitWindowPosition(WINDOW_POSITION_X, WINDOW_POSITION_Y);
    glutCreateWindow("SurviveBall");

    Image * image;

    glEnable(GL_TEXTURE_2D);

    glTexEnvf(GL_TEXTURE_ENV,
              GL_TEXTURE_ENV_MODE,
              GL_REPLACE);

    image = image_init(0, 0);
    glGenTextures(2, names);

    image_read(image, FILENAME0);
    
    glBindTexture(GL_TEXTURE_2D, names[0]);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
    
    image_read(image, FILENAME1);
    
    glBindTexture(GL_TEXTURE_2D, names[1]);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

    
    glBindTexture(GL_TEXTURE_2D, 0);

    image_done(image);


    glutKeyboardFunc(on_keyboard);
    glutKeyboardUpFunc(on_release);
    glutReshapeFunc(on_reshape);
    glutDisplayFunc(on_display);

    timer_active = 0;

    glClearColor(0.596, 1, 0.596, 1);
    glEnable(GL_DEPTH_TEST);

    GLfloat light_position[] = { 2, 5, 20, 0 };

    GLfloat light_ambient[] = { 0, 0, 0, 1 };

    GLfloat light_diffuse[] = { 1, 1, 1, 1 };

    GLfloat light_specular[] = { 1, 1, 1, 1 };

    GLfloat model_ambient[] = { 0.4, 0.4, 0.4, 1 };

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, model_ambient);

    glEnable(GL_COLOR_MATERIAL);

    glutFullScreen();

    glutMainLoop();

    return 0;
}

static void on_keyboard(unsigned char key, int x, int y) {
    switch (key) {

        case KEY_ESC:
            exit(0);
            break;

        case ARROW_UP:
            CAMERA_Y += 0.2;
            break;

        case ARROW_DOWN:
            CAMERA_Y -= 0.2;
            break;

        case 's':
            animation_ongoing = 0;
            break;

        case KEY_START:
            
            //std::cout<<"Ah yes, the game should be starting now!"<<"\n";
            
            if (!animation_ongoing) {
                animation_ongoing = 1;
                glutTimerFunc(20, on_timer, 0);
            }
            break;

        case KEY_LEFT:
            ATTEMPT_LEFT = 1;
            break;

        case KEY_RIGHT:
            ATTEMPT_RIGHT = 1;
            break;

        case 'w':
        case 'W':
            ATTEMPT_JUMP = 1;
            break;

    }
}

static void on_release(unsigned char key, int x, int y) {
    switch (key) {
    case 'a':
    case 'A':
        ATTEMPT_LEFT = 0;
        break;
    
    case 'd':
    case 'D':
        ATTEMPT_RIGHT = 0;
        break;
    }
}

static void on_timer(int value){
    if (value != 0)
        return;


    if (plane1_coordinates.z + 50 <= 0) {
        obstacles_plane1.clear();
        plane1_coordinates.z = 150;
        make_obstacles(1);
        draw_obstacles(1);
    }

    if (plane2_coordinates.z + 50 <= 0) {
        obstacles_plane2.clear();
        plane2_coordinates.z = 150;
        make_obstacles(2);
        draw_obstacles(2);
    }

    plane1_coordinates.z -= (0.5 + SPEED_INCREASE);
    plane2_coordinates.z -= (0.5 + SPEED_INCREASE);
    colision_detection();

    SCORE += 0.2 + 0.2 * (int(SPEED_INCREASE));

    if (int(SCORE) % 200 == 0 && SCORE > 1) {
        BALL_SPEED += 0.002;
        //std::cout << "Ah yes, score that can be devided by 200 "<<int(SCORE) << "\n";
        //std::cout << "Ball speed" << BALL_SPEED << "\n\n";

        NUMBER_OF_POINTS++;
    }



    for (int i = 0; i < obstacles_plane1.size(); i++) {
        obstacles_plane1[i].z -= (0.5 + SPEED_INCREASE);
    }

    for (int i = 0; i < obstacles_plane2.size(); i++) {
        obstacles_plane2[i].z -= (0.5 + SPEED_INCREASE);
    }

    if (ATTEMPT_LEFT && ball_coordinates.x < 4) {
        ball_coordinates.x += 0.1;
    }

    if (ATTEMPT_RIGHT && ball_coordinates.x > -4) {
        ball_coordinates.x -= 0.1;
    }

    if (ATTEMPT_JUMP) {
        if (jump_counter < PI) {
            jump_counter += JUMP_SPEED;
            ball_coordinates.y = MAX_JUMP_HEIGHT * sin(jump_counter);
        }
        else {
            jump_counter = 0;
            ATTEMPT_JUMP = 0;
        }
    }
    
    // std::cout<<"Speed booster: "<<SPEED_BOOSTER_ACTIVE<<"\n";
    // std::cout<<"Speed var: "<<SPEED_BOOSTER_ACTIVE<<"\n";
    // std::cout<<"Speed increase: "<<SPEED_INCREASE<<"\n";

    if (SPEED_BOOSTER_ACTIVE) {
        if (SPEED_BOOST_VAR <= PI) {
            SPEED_BOOST_VAR += JUMP_SPEED;
            SPEED_INCREASE = 2 * sin(SPEED_BOOST_VAR);
        }
        else {

            SPEED_INCREASE = 0;
            SPEED_BOOST_VAR = 0;
            SPEED_BOOSTER_ACTIVE = 0;
        }
    }

    glutPostRedisplay();

    if (animation_ongoing)
        glutTimerFunc(20, on_timer, 0);
}

static void score() {

    glPushMatrix();
        
        glColor3f(1, 1, 1);
        glRasterPos3f(ball_coordinates.x + 4, 3, ball_coordinates.z);

        std::string SCORE_DISPLAY = SCORE_TEXT + std::to_string(int(SCORE));

        for (auto it: SCORE_DISPLAY){
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, it);
        }

    glPopMatrix();

}

static void display_controls(){
    if(int(SCORE) < 20){
        tutorial_text = "READY?";
    }
    else if(int(SCORE) < 30) {
        tutorial_text = "3";
    }
    else if(int(SCORE) < 40) {
        tutorial_text = "2";
    }
    else if(int(SCORE) < 50) {
        tutorial_text = "1";
    }
    else if(int(SCORE) < 55) {
        tutorial_text = "GO!";
    }
    else {
        tutorial_text = "";
    }

    glPushMatrix();
        
        glColor3f(1, 1, 1);
        glRasterPos3f(ball_coordinates.x + 0.5, 3, ball_coordinates.z);

        for (auto it: tutorial_text){
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, it);
        }

    glPopMatrix();
}

static void on_reshape(int width, int height) {

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60,
        (float)width / height,
        1, 1500);
}

static void draw_plane() {
    glPushMatrix();
     glBindTexture(GL_TEXTURE_2D, names[0]);
        glEnable(GL_TEXTURE_2D);

        glBegin(GL_POLYGON);
			glTexCoord2f(0, 0);
			glVertex3f(-5, -0.499, 0);
			
			glTexCoord2f(1, 0);
			glVertex3f(5, -0.499, 0);
			
			glTexCoord2f(1, 1);
			glVertex3f(5, -0.499, 20);
			
			glTexCoord2f(0, 1);
			glVertex3f(-5, -0.499, 20);
		glEnd();
        glBegin(GL_POLYGON);
			glTexCoord2f(0, 0);
			glVertex3f(-5, -0.499, 20);
			
			glTexCoord2f(1, 0);
			glVertex3f(5, -0.499, 20);
			
			glTexCoord2f(1, 1);
			glVertex3f(5, -0.499, 100);
			
			glTexCoord2f(0, 1);
			glVertex3f(-5, -0.499, 100);
		glEnd();
        glDisable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);

        //glColor3f(0.35, 0.50, 0.73);
        glTranslatef(0, -plane1_coordinates.y, plane1_coordinates.z);
        glScalef(plane1_coordinates.x, plane1_coordinates.y, LENGTH);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();

     glBindTexture(GL_TEXTURE_2D, names[0]);
        glEnable(GL_TEXTURE_2D);

        glBegin(GL_POLYGON);
			glTexCoord2f(0, 0);
			glVertex3f(-5, -0.499, 100);
			
			glTexCoord2f(1, 0);
			glVertex3f(5, -0.499, 100);
			
			glTexCoord2f(1, 1);
			glVertex3f(5, -0.499, 200);
			
			glTexCoord2f(0, 1);
			glVertex3f(-5, -0.499, 200);
		glEnd();
        glDisable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);

        glColor3f(0.29, 0.447, 0.584); 
        glTranslatef(0, -plane2_coordinates.y, plane2_coordinates.z);
        glScalef(plane2_coordinates.x, plane2_coordinates.y, LENGTH);
        glutSolidCube(1);
    glPopMatrix();
}

static void draw_ball() {
    glPushMatrix();
        glColor3f(1, 1, 1);
        glTranslatef(ball_coordinates.x, ball_coordinates.y, ball_coordinates.z);
        glutSolidSphere(0.5, 100, 100);
    glPopMatrix();
}

static void draw_background(){
    glPushMatrix();
        glRotatef(110,1,0,0);
        glTranslatef(2, 50, -20);
        glScalef(7,1,15);

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, names[1]);
	
		glBegin(GL_POLYGON);
			glTexCoord2f(0, 0);
			glVertex3f(-10, 0, -5);
			
			glTexCoord2f(1, 0);
			glVertex3f(10, 0, -5);
			
			glTexCoord2f(1, 1);
			glVertex3f(10, 0, 5);
			
			glTexCoord2f(0, 1);
			glVertex3f(-10, 0, 5);
		glEnd();
	
        glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();
}

static void on_display(void) {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    score();
    display_controls();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(ball_coordinates.x, 3 + CAMERA_Y, -1,
              ball_coordinates.x, 1.5 + CAMERA_Y, 2,
              0, 1, 0);
    
    glPushMatrix();
        draw_background();
    glPopMatrix();

    draw_plane();

    glPushMatrix();
        draw_ball();
    glPopMatrix();

    draw_obstacles(1);
    draw_obstacles(2);

    glutSwapBuffers();
}

static std::vector<double> get_obstacle_locations() {
    
    std::vector<double> positions;

    for (int i = 0; i < NUMBER_OF_POINTS; i++) {
        int index = (int)rand() % 100;
        positions.push_back(possible_positions[index]);
    }

    return positions;
}

static bool should_generate_reward() {
    int index = (int)rand() % 100;
    
    return (possible_positions[index] > 0 ? true : false);
}

static void make_obstacles(int type){
    for (int i = 0; i < 10; i++) {
        int num = (int)rand() % NUMBER_OF_POINTS;

        if (num == 0)
            num = 4;

        std::vector<bool> free_positions = { 1, 1, 1, 1, 1 };
        for (int j = 0; j < num; j++) {
            Coordinates p;

            std::vector <double> positions = get_obstacle_locations();

            if (!REWARD_COUNTER) {
                REWARD_COUNTER = 1;
                bool have_reward = should_generate_reward();
                if (have_reward) {
                    free_positions[j] = 1;

                    p.y = 0.25;
                    p.x = positions[j];
                    if (type == 1) {
                        p.z = plane1_coordinates.z + 50 - i * 10;
                    }
                    else {
                        p.z = plane2_coordinates.z + 50 - i * 10;
                    }
                    
                    p.type_speed = 1;
                    
                    if (type == 1) {
                        obstacles_plane1.push_back(p);
                    }
                    else {
                        obstacles_plane2.push_back(p);
                    }

                    continue;
                }
            }

            int pos = j;
            if (free_positions[pos] == 1) {
                free_positions[pos] = 0;

                p.y = 0.25;
                
                p.x = positions[pos];
                if (type == 1) {
                    p.z = plane1_coordinates.z + 50 - i * 10;
                    p.type_obstacle = 1;
                    obstacles_plane1.push_back(p);
                }
                else {
                    p.z = plane2_coordinates.z + 50 - i * 10;
                    p.type_obstacle = 1;
                    obstacles_plane2.push_back(p);
                }
            }
        }
    }

    REWARD_COUNTER = 0;
}

static float find_distance(Coordinates cord) {
    Coordinates dist;
    dist = ball_coordinates - cord;

    return dist.distance();
}

static void draw_obstacles(const int plane) {
    int len = 0;

    len = (plane == 1 ? obstacles_plane1.size() : obstacles_plane2.size());
    
    for (int i = 0; i < len; i++) {
        Coordinates coord;
        
        if (plane == 1)
            coord = obstacles_plane1[i];
        else
            coord = obstacles_plane2[i];

        if (coord.type_obstacle) {
            glPushMatrix();
                glColor3f(224 / 255.0, 114 / 255.0, 9 / 255.0);
                glTranslatef(coord.x, coord.y, coord.z);
                glScalef(1, 1, 1);
                glutSolidCube(0.75);
            glPopMatrix();
        }
        else if(coord.type_speed){
            glPushMatrix();
                glColor3f(0, 225, 0);
                glTranslatef(coord.x, coord.y, coord.z);
                glScalef(1, 1, 1);
                glutSolidCube(0.75);
            glPopMatrix();
        }
    }
}


static void colision_detection() {

    int plane = (plane1_coordinates.z < plane2_coordinates.z ? 1 : 2);

    if (plane == 1) {

        for (int i = 0; i < obstacles_plane1.size(); i++) {
            double dist = find_distance(obstacles_plane1[i]);

            if (dist <= 0.75) {
                
                if (obstacles_plane1[i].type_obstacle && !SPEED_BOOSTER_ACTIVE) {
                    animation_ongoing = 0;
                }

                if (obstacles_plane1[i].type_speed) {
                    SPEED_BOOSTER_ACTIVE = 1;
                }
            }
        }

    }else {

        for (int i = 0; i < obstacles_plane2.size(); i++) {
            double dist = find_distance(obstacles_plane2[i]);

            if (dist <= 0.75) {

                if (obstacles_plane2[i].type_obstacle && !SPEED_BOOSTER_ACTIVE) {
                    //std::cout<<"Speed booster: "<<SPEED_BOOSTER_ACTIVE<<"\n";
                    //std::cout<<"Speed var: "<<SPEED_BOOSTER_ACTIVE<<"\n";
                    animation_ongoing = 0;
                }

                if (obstacles_plane2[i].type_speed) {
                    //std::cout<<"Speed booster colision speed: "<<SPEED_BOOSTER_ACTIVE<<"\n";
                    //std::cout<<"Speed var colision speed: "<<SPEED_BOOSTER_ACTIVE<<"\n";
                    SPEED_BOOSTER_ACTIVE = 1;
                }

            }
        }
    }
}