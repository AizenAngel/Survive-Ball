#include "Classes.h"
#include <vector>
#include <string>

double CAMERA_Y = 0;

float animation_parameter = 0;
float animation_ongoing = 0;

int ATTEMPT_LEFT = 0;
int ATTEMPT_RIGHT = 0;
int ATTEMPT_JUMP = 0;
double jump_counter = 0;

Coordinates ball_coordinates(0, 0, 5);
Coordinates plane1_coordinates(10, 1, 50);
Coordinates plane2_coordinates(10, 1, 150);

int FIRST_PLANE = 0;
int SECOND_PLANE = 0;
int REWARD_COUNTER = 0;
double SCORE = 0;
std::string SCORE_TEXT = "SCORE: ";

int SPEED_BOOSTER_ACTIVE = 0;
double SPEED_BOOST_VAR = 0;
double SPEED_INCREASE = 0;

std::vector<Coordinates> obstacles_plane1;
std::vector<Coordinates> obstacles_plane2;

double BALL_SPEED = 0.5;
int NUMBER_OF_POINTS = 5;
int LOOP_COUNT = 10;


std::string tutorial_text = "READY?";
std::string SCORE_DISPLAY = "";

double SPEED_BOOST = 0.002;