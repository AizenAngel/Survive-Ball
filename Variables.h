#include "Classes.h"
#include <vector>
#include <string>

// parametar koji podešsava poziciju kamere
double CAMERA_Y = 0;

//animacioni parametri
float animation_parameter = 0;
float animation_ongoing = 0;

// parametri koji određuju pomeranje
int ATTEMPT_LEFT = 0;
int ATTEMPT_RIGHT = 0;
int ATTEMPT_JUMP = 0;
double jump_counter = 0;

Coordinates ball_coordinates(0, 0, 5); // koordinate lopte
Coordinates plane1_coordinates(10, 1, 50); // koordinate prve ravni
Coordinates plane2_coordinates(10, 1, 150); // koordinate druge ravni


//int FIRST_PLANE = 0; 
//int SECOND_PLANE = 0;
int REWARD_COUNTER = 0; // generisanje nagrade
double SCORE = 0; // score
std::string SCORE_TEXT = "SCORE: "; // tekst koji se ispisuje za taj score.

int SPEED_BOOSTER_ACTIVE = 0; // da li imamo aktiviran speed boost
double SPEED_BOOST_VAR = 0; // parametar koji u neku ruku određuje visinu skoka
double SPEED_INCREASE = 0; // parametar koji određuje koliko ubrzavamo loptu prilikom kontakta sa specijalnom preprekom

std::vector<Coordinates> obstacles_plane1; // prepreke na prvoj ravni
std::vector<Coordinates> obstacles_plane2; // prepreke na drugoj ravni

double BALL_SPEED = 0.5; // inicjalna brzina lopte
int NUMBER_OF_POINTS = 5; // inicijalni maksimalni broj tačaka
//int LOOP_COUNT = 10;


std::string tutorial_text = "READY?"; // poruka na početku igre
std::string SCORE_DISPLAY = ""; // SCORE na početku igre

double SPEED_BOOST = 0.002; // parametar koji određuje bonus težinu igre