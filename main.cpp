#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
using namespace std;

const double PI = 3.141592653589793;
const double EARTH_G = 9.807;

int choice;

int sigFig1;
int sigFig2;
int sigFigs;

double xVel;
double height;
double initialVel;
double angleToGround;

void pageBreak(){
    for (int x = 0; x < 200; x++){
        cout << "\n";
    }
}

int findSigFigs(int sigFig1, int sigFig2){
    //NOTE: this only works because these calculations involve no adding/subtracting
    if (sigFig1 > sigFig2) return sigFig2;
    else return sigFig1;
}

double horizontalAirTime(double height){
    //calculate time in air using formula t = sqrt(2h/g)
    double time = sqrt(2.0 * height/EARTH_G);
    return time;
}

double findDistance(double vel, double time){
    //calculate distance travelled using formula d = vt
    double distance = vel * time;
    return distance;
}

double findMaxHeight(double yVel){
    //calculate height reached using formula (vf^2 - vi^2)/2g
    double height = (yVel * yVel)/(EARTH_G * 2.0);
    return height;
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
    double time = yVel/EARTH_G * 2.0;
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
        cout << "Number of significant digits: ";
        cin >> sigFig1;
        cout << "Initial Height (m): ";
        cin >> height;
        cout << "Number of significant digits: ";
        cin >> sigFig2;
        
        //calculate sig figs
        sigFigs = findSigFigs(sigFig1, sigFig2);
        
        cout << "\nThe projectile was in the air for ";
        cout << setprecision(sigFigs - 1) << scientific << horizontalAirTime(height);
        cout << " seconds.\n";
        
        cout << "The projectile travelled a distance of ";
       cout << setprecision(sigFigs - 1) << scientific << findDistance(xVel, horizontalAirTime(height));
        cout << " meters.\n";
    }
    else if (choice == 2) {
        cout << "Initial Velocity (m/s): ";
        cin >> initialVel;
        cout << "Number of significant digits: ";
        cin >> sigFig1;
        cout << "Angle to Ground (degrees): ";
        cin >> angleToGround;
        cout << "Number of significant digits: ";
        cin >> sigFig2;
        
        //calculate sig figs
        sigFigs = findSigFigs(sigFig1, sigFig2);
        
        cout << "\nThe projectile was in the air for ";
        cout << setprecision(sigFigs - 1) << scientific << angledAirTime(findYVel(initialVel, angleToGround));
        cout << " seconds.\n";
        
        cout << "The projectile travelled a distance of ";
        cout << setprecision(sigFigs - 1) << scientific << findDistance(findXVel(initialVel, angleToGround), angledAirTime(findYVel(initialVel, angleToGround)));
        cout << " meters.\n";
        
        cout << "The projectile reached a maximum height of ";
        cout << setprecision(sigFigs - 1) << scientific << findMaxHeight(findYVel(initialVel, angleToGround));
        cout << " meters.\n";
        
    }
    else {
        cout << "Sorry, that's not an option.\n";
    }
}
