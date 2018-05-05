#include <iostream>
#include <cmath>
using namespace std;

const double EARTH_G = 9.807;

bool loop = true;
int choice;

double xVel;
double height;
double initialVel;
double angleToGround;

void pageBreak(){
    for (int x = 0; x < 200; x++){
        cout << "\n";
    }
}

double horizontalAirTime (double height){
    //calculate time in air using formula t = sqrt(2h/g)
    double time = sqrt(2.0 * height/EARTH_G);
    return time;
}

double horizontalDistance (double xVel, double time){
    //calculate distance travelled using formula d = vt
    double distance = xVel * time;
    return distance;
}

double findXVel(double initialVel, double angleToGround){
    //adjacent side of triangle is horizontal (CAH --> cos(x) = A/H)
    //converting degrees to radians by multiplying by PI/180
    double xVel = cos(angleToGround*PI/180) * initialVel;
    return xVel;
}

double findYVel(double initialVel, double angleToGround){
    //opposite side of triangle is vertical (SOH --> sin(x) = O/H)
    //converting degrees to radians by multiplying by PI/180
    double yVel = sin(angleToGround*PI/180) * initialVel;
    return yVel;
}

double angledAirTime(double yVel){
    //calculate time in the air using formula t = (vf - vi)/g (multiplied by two to account for the trip back down)
    double time = yVel/EARTH_G * 2
    return time;
}

int main(){
    pageBreak();
    cout << "How is your projectile being launched?\n";
    cout << "(1) Horizontally\n";
    cout << "(2) At an angle\n";
    cin >> choice;
    pageBreak();
    if (choice == 1){
        cout << "Initial Horizontal Velocity (m/s): ";
        cin >> xVel;
        cout << "Initial Height (m): ";
        cin >> height;
            
        cout << "The projectile was in the air for ";
        cout << horizontalAirTime(height);
        cout << " seconds.\n";
            
        cout << "The projectile travelled a distance of ";
        cout << horizontalDistance(xVel, horizontalAirTime(height));
        cout << " meters.\n";
    }
    else if (choice == 2) {
        cout << "Initial Velocity (m/s): ";
        cin >> initialVel;
        cout << "Angle to Ground (degrees): ";
        cin >> angleToGround;
        
        cout << "The projectile was in the air for ";
        cout << angledAirTime(findYVel(initialVel, angleToGround));
        cout << " seconds.\n";
    }
    else {
        cout << "Sorry, that's not an option.\n";
    }
}
