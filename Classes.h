#include <cmath>
#include <iostream>

class Coordinates {
public:
	Coordinates(){
		x = 0;
		y = 0;
		z = 0;
		type_obstacle = 0;
		type_speed = 0;
	}
	Coordinates(double x, double y, double z) : x(x), y(y), z(z) {}

	friend Coordinates operator-(Coordinates cord1, Coordinates cord2) {
		cord1.x -= cord2.x;
		cord1.y -= cord2.y;
		cord1.z -= cord2.z;
	
		return cord1;
	}

	double distance() {
		return sqrt(x*x + y*y + z*z);
	}

	friend std::ostream& operator<<(std::ostream& os, Coordinates s) {
		os << s.x << " " << s.y << " " << s.z << " type_obstacle: "<<s.type_obstacle<<" "<<" type_speed: "<<s.type_speed<<"\n";
		return os;
	}

	double x;
	double y;
	double z;
	int type_obstacle = 0;
	int type_speed = 0;
};
