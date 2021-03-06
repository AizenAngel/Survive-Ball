#include <vector>
#include <string>

#define PI 3.14 

const int WINDOW_HEIGHT = 600; //visina prozora
const int WINDOW_WIDTH = 600; // širina prozora
const int WINDOW_POSITION_X = 100; // X pozicija prozora
const int WINDOW_POSITION_Y = 100; // Z pozicija prozora

const unsigned char KEY_ESC = 27;
const unsigned char KEY_LEFT = 'a';
const unsigned char KEY_RIGHT = 'd';
const unsigned char KEY_JUMP = 32;
const unsigned char KEY_TURBO = 87;
const unsigned char KEY_START = 'g';
const unsigned char ARROW_UP = 'u';
const unsigned char ARROW_DOWN = 'j';

// moguće X kooridnate prepreka
const std::vector<double> possible_positions = { 
-0.924962185096, 1.45013815562, -1.05236246367, -4,  
-1.19527567674, -4, -2.8823261238, -3.5,
0.491351635718, -2.28683066461, 2.8650686878, -0.768378111609, 
-3.49922333235, -4, -2.76353099453, 2.13590076459, 
-4, -0.914219416626, 0.938121530777, 2.95927508438,
-2.27775406557, -0.236845292764, 0.264956597778, -4.49697054963, 
2.86821104856, -4, -4.81334166085, 1.33798918859,
3.0200052693, -4.06192941612, 2.06127473548, -2.80453996204, 
-3.8324370441, 2.14100052665, -3.91274083978, 0.568482298696, 
1.00889052673, -3.1568632784, -4.14001125345, 3.73450539438, 
1.23695940174, -1.2138995138, 3.63925053629, -1.81705519619,  
-3.90665280106, 0.389830520657, 0.670056763599, -2.91356502914,
1.40846530076, -3.865166336, 1.10170342174, 0.665486621982, 
0.121991299407, -3.94528295923, 0.437073955142, -2.68971234112, 
-3.46277119441, -4.31837355195, -2.08667479759, -2.15305404248, 
-0.460538918911, -1.36799959865, -3.99365819371, -3.44569911075, 
-3.42280842423, -3.99957872078, 3.6309414515, -1.30618690861,
-1.80508447969, 1.77553670815, 0.879818227707, 3.52820042997, 
0.768300690132, 1.24637363796, 2.79305581145, -1.17214636939, 
-0.100487541102, 1.39438010797, 3.2036757661, 3.42572353639, 
-2.50696519372, -1.05744781708, -0.519159148023, -3.76362127433, 
-3.93435005281, -3.4699044893, -2.43213348757, -3.6112397108, 
-0.421142294587, -3.28293018799, -0.831756682353, 2.45040783206, 
-3.51738518214, -3.42755399603, -2.65515831403, 3.48895264057, 
1.0049741439, -4.22870685386, 1.05341439662, -3.7};

//const int MOVEMENT = 2; 
const double JUMP_SPEED = 0.0628; // brzina skoka
const double MAX_JUMP_HEIGHT = 1.5; // MAX visina do koje možemo da skočimo
//const double DECISION_BOUNDARY = 3.5;

const double LENGTH = 100; // dužina racni
//const std::string GAME_OVER = "GAME OVER!";
const std::string PRESS_ESC = "PRESS ESC TO EXIT THE GAME!";

// "motivacione" poruke
std::vector<std::string> thrash_talk = {"Were you even trying?",
                                        "How about you try again..... NEVER?",
                                        "Ouch, that was fast.", 
                                        "Surely, you must be joking, right?"};