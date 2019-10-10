#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
using namespace std;

const double PI = 3.141592653589793;
const double EARTH_G = 9.80665;
const int EARTH_G_SIGFIGS = 6;

void pageBreak(){
    for (int x = 0; x < 200; x++){
        cout << "\n";
    }
}

int findSigFigs(int sigFigA, int sigFigB){
    //NOTE: this only works because these calculations involve no adding/subtracting
    if (sigFigA > sigFigB && EARTH_G_SIGFIGS > sigFigB) return sigFigB;
    else if (sigFigB > sigFigA && EARTH_G_SIGFIGS > sigFigA) return sigFigA;
    else return EARTH_G_SIGFIGS;
}

//parse through input and return sig figs
int parseInputForSigFigs(string input){
    int sigFigCounter = input.length();
    bool hasDecimal = false;
    for (int i = 0; i < input.length(); i++){
        //decimal encountered
        if (input[i] == '.') hasDecimal = true;
        //digit is zero and no decimal has been encountered yet
        else if (input[i] == '0' && hasDecimal == false) sigFigCounter--;
    };
    if (hasDecimal) sigFigCounter--;
    return sigFigCounter;
}

double horizontalAirTime(double height){
    //calculate time in air using formula t = sqrt(2h/g)
    return sqrt(2.0 * height/EARTH_G);
}

double findDistance(double vel, double time){
    //calculate distance travelled using formula d = vt
    return vel * time;
}

double findMaxHeight(double yVel){
    //calculate height reached using formula (vf^2 - vi^2)/2g
    return (yVel * yVel)/(EARTH_G * 2.0);
}

double findXVel(double initialVel, double angleToGround){
    //adjacent side of triangle is horizontal (CAH --> cos(x) = A/H)
    //converting degrees to radians by multiplying by PI/180
    return cos(angleToGround*PI/180) * initialVel;

}

double findYVel(double initialVel, double angleToGround){
    //opposite side of triangle is vertical (SOH --> sin(x) = O/H)
    //converting degrees to radians by multiplying by PI/180
    return sin(angleToGround*PI/180) * initialVel;
}

double angledAirTime(double yVel){
    //calculate time in the air using formula t = (vf - vi)/g (multiplied by two to account for the trip back down)
    return yVel/EARTH_G * 2.0;
}

int main(){
    int choice = 0;

    int sigFigA = 0;
    int sigFigB = 0;

    string xVelInput = "";
    double xVel = 0.0;
    string heightInput = "";
    double height = 0.0;
    string initialVelInput = "";
    double initialVel = 0.0;
    string angleToGroundInput = "";
    double angleToGround = 0.0;

    pageBreak();
    cout << "How is your projectile being launched?\n";
    cout << "(1) Horizontally from a height\n";
    cout << "(2) At an angle from the ground\n";
    cin >> choice;
    pageBreak();
    
    switch (choice) {
    case 1:
    {
        cout << "Initial Horizontal Velocity (m/s): ";
        //take input as string for sig fig calclation
        cin >> xVelInput;
        //convert to double for math
        xVel = stod(xVelInput);
        //get sig figs from string input
        sigFigA = parseInputForSigFigs(xVelInput);
        cout << "Initial Height (m): ";
        cin >> heightInput;
        height = stod(heightInput);
        sigFigB = parseInputForSigFigs(heightInput);
        
        //calculate sig figs
        int sigFigs = findSigFigs(sigFigA, sigFigB);
        
        cout << setprecision(sigFigs - 1) << scientific;    //expurgates the problem of dealing with sigfigs

        cout << "\nThe projectile was in the air for ";
        cout << horizontalAirTime(height);
        cout << " seconds.\n";
        
        cout << "The projectile travelled a distance of ";
        cout << findDistance(xVel, horizontalAirTime(height));
        cout << " meters.\n";
        break;
    }

    case 2:{
        cout << "Initial Velocity (m/s): ";
        cin >> initialVelInput;
        initialVel = stod(initialVelInput);
        sigFigA = parseInputForSigFigs(initialVelInput);
        cout << "Angle to Ground (degrees): ";
        cin >> angleToGroundInput;
        angleToGround = stod(angleToGroundInput);
        sigFigB = parseInputForSigFigs(angleToGroundInput);
        
        //calculate sig figs
        int sigFigs = findSigFigs(sigFigA, sigFigB);

        cout << setprecision(sigFigs - 1) << scientific;    //expurgates the problem of dealing with sigfigs
        
        cout << "\nThe projectile was in the air for ";
        cout << angledAirTime(findYVel(initialVel, angleToGround));
        cout << " seconds.\n";
        
        cout << "The projectile travelled a distance of ";
        cout << findDistance(findXVel(initialVel, angleToGround), angledAirTime(findYVel(initialVel, angleToGround)));
        cout << " meters.\n";
        
        cout << "The projectile reached a maximum height of ";
        cout << findMaxHeight(findYVel(initialVel, angleToGround));
        cout << " meters.\n";
        break;
        
    }
    default: {
        cout << "Sorry, that's not an option. Please rerun with correct inputs.\n";
        //main();
    }
    }
return 0;
}
