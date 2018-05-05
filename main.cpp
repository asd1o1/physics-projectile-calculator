#include <iostream>
#include <string>
#include <cmath>
using namespace std;

const double PI = 3.141592653589793;
const double EARTH_G = 9.807;

bool loop = true;
int choice;

 /*
 To make it possible to count sig figs in initial values,
 they need to be strings (if they are doubles, then the value will always be 9).
 There don't seem to be any issues converting them
 to doubles when it's needed.
 */
string xVel_str;
string height_str;
string initialVel_str;
string angleToGround_str;

double xVel;
double height;
double initialVel;
double angleToGround;

int sigFigs;

void pageBreak(){
    for (int x = 0; x < 200; x++){
        cout << "\n";
    }
}

bool isDecimal(string num){
    //check for a decimal point in string
    if (num.find('.') != string::npos) return true;
}

int findSigFigs(string num1, string num2){
    //NOTE: this only works because these calculations involve no adding/subtracting
    int length1 = num1.length();
    int length2 = num2.length();
    if (isDecimal(num1)) length1 -= 1;
    if (isDecimal(num2)) length2 -= 1;
    if (length1 > length2) return length2;
    else return length1;
}

string roundToSigFigs(double num, int sigFigs){
    //convert double to string to make it easier to work with
    string str = to_string(num);
    string newStr = "";
    //counter to make for loop longer without affecting sigFigs
    int notSigFigs = 0;
    bool zeroesAreSignificant = false;
    for (int i = 0; i <= (sigFigs + notSigFigs); i++){
        //increase the counter (and essentially not count sig figs) for insignificant values
        if ((str[i] == '0' && !zeroesAreSignificant) || str[i] == '.') notSigFigs += 1;
        else {
            //zeroes that aren't leading are made significant and counted as sig figs
            zeroesAreSignificant = true;
        }
        //append character to new string
        newStr += str[i];
    }
    return newStr;
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
        cin >> xVel_str;
        cout << "Initial Height (m): ";
        cin >> height_str;
        
        //calculate sig figs
        sigFigs = findSigFigs(xVel_str, height_str);
        
        //convert strings to doubles
        xVel = stod(xVel_str);
        height = stod(height_str);
        
        cout << "\nThe projectile was in the air for " + roundToSigFigs(horizontalAirTime(height), sigFigs) + " seconds.\n"; 
        cout << "The projectile travelled a distance of " + roundToSigFigs(findDistance(xVel, horizontalAirTime(height)), sigFigs) + " meters.\n";
    }
    else if (choice == 2) {
        cout << "Initial Velocity (m/s): ";
        cin >> initialVel_str;
        cout << "Angle to Ground (degrees): ";
        cin >> angleToGround_str;
        
        //calculate sig figs
        sigFigs = findSigFigs(initialVel_str, angleToGround_str);
        
        //convert strings to doubles
        initialVel = stod(initialVel_str);
        angleToGround = stod(angleToGround_str);
        
        cout << "\nThe projectile was in the air for " + roundToSigFigs(angledAirTime(findYVel(initialVel, angleToGround)), sigFigs) + " seconds.\n";
        cout << "The projectile travelled a distance of " + roundToSigFigs(findDistance(findXVel(initialVel, angleToGround), angledAirTime(findYVel(initialVel, angleToGround))), sigFigs) + " meters.\n";
        cout << "The projectile reached a maximum height of " + roundToSigFigs(findMaxHeight(findYVel(initialVel, angleToGround)), sigFigs) + " meters.\n";
    }
    else {
        cout << "Sorry, that's not an option.\n";
    }
    cout << "\nNOTE: All digits are significant except the last one!\n";
}
