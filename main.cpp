#include <iostream>
#include <cmath>
using namespace std;

bool loop = true;
int choice;

double xVel;
double height;
double combinedVel;
double angleToGround;

void pageBreak(){
    for (int x = 0; x < 200; x++){
        cout << "\n";
    }
}

double horizontalAirTime (double height){
    //calculate time in air using formula t = sqrt(2d/a)
    double time = sqrt(2.0 * height/9.807);
    return time;
}

double horizontalDistance (double xVel, double time){
    //calculate distance travelled using formula d = vt
    double distance = xVel * time;
    return distance;
}

int main(){
    while (loop){
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
        //do angle
        }
        else {
            cout << "Sorry, that's not an option.\n";
        }
        //keep running program?
        cout << "\n\nRun again?\n";
        cout << "(1) Yes\n";
        cout << "(2) No\n";
        cin >> choice;
        if (choice != 1){
            loop = false;
        }
    }
}
