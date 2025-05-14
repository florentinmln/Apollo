#include <rpos/robot_platforms/slamware_core_platform.h>
#include <iostream>
#include <string>
#include <termios.h>
#include <unistd.h>

using namespace rpos::robot_platforms;
using namespace std;

void setNonCanonicalMode() {
    struct termios tty;
    
    // Obtenir les paramètres actuels du terminal
    tcgetattr(STDIN_FILENO, &tty);

    // Désactiver le mode canonique et l'écho des caractères
    tty.c_lflag &= ~(ICANON | ECHO);

    // Appliquer les paramètres
    tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}

void resetTerminalMode(struct termios &original) {
    tcsetattr(STDIN_FILENO, TCSANOW, &original);
}

void forward(SlamwareCorePlatform platform){
    rpos::core::ACTION_DIRECTION actionDirection = rpos::core::ACTION_DIRECTION::FORWARD;
    rpos::core::Direction direction(actionDirection);
    rpos::actions::MoveAction moveBy = platform.moveBy(direction);
}
void backward(SlamwareCorePlatform platform){
    rpos::core::ACTION_DIRECTION actionDirection = rpos::core::ACTION_DIRECTION::BACKWARD;
    rpos::core::Direction direction(actionDirection);
    rpos::actions::MoveAction moveBy = platform.moveBy(direction);
}
void right(SlamwareCorePlatform platform){
    rpos::core::ACTION_DIRECTION actionDirection = rpos::core::ACTION_DIRECTION::TURNRIGHT;
    rpos::core::Direction direction(actionDirection);
    rpos::actions::MoveAction moveBy = platform.moveBy(direction);
}
void left(SlamwareCorePlatform platform){
    rpos::core::ACTION_DIRECTION actionDirection = rpos::core::ACTION_DIRECTION::TURNLEFT;
    rpos::core::Direction direction(actionDirection);
    rpos::actions::MoveAction moveBy = platform.moveBy(direction);
}

int connection(SlamwareCorePlatform &platform){
    try {
        platform = SlamwareCorePlatform::connect("192.168.11.1", 1445);
        std::cout <<"SDK Version: " << platform.getSDKVersion() << std::endl;
        std::cout <<"SDP Version: " << platform.getSDPVersion() << std::endl;
        std::cout <<"Barttery Percetage: " << platform.getBatteryPercentage() << std::endl;

    } catch(ConnectionTimeOutException& e) {
        std::cout <<e.what() << std::endl;
        return 1;
    } catch(ConnectionFailException& e) {
        std::cout <<e.what() << std::endl;
        return 1;
    }
    return 0;
}

int main(int argc, char* argv[]){
    SlamwareCorePlatform platform;
    cout<<"Coucou toi !!!!!!!!!\n";
    if(connection(platform)){
        cout<<"c PETER"<<endl;
        return 1;
    }
    std::cout <<"Connection Successfully" << std::endl;
    struct termios original;
    // Sauvegarder les paramètres actuels
    tcgetattr(STDIN_FILENO, &original);
    // Activer le mode non canonique
    setNonCanonicalMode();
    std::cout << "Mode non canonique activé. Appuie sur 'x' pour quitter.\n";
    char c;
    while (true) {
        cin >> c;
        std::cout << "Caractère lu: " << c << std::endl;
        if (c == 'x') break;
        if (c == 'z') forward(platform);
        if (c == 's') backward(platform);
        if (c == 'd') right(platform);
        if (c == 'q') left(platform);
    }

    // Restaurer les paramètres d'origine
    resetTerminalMode(original);
    std::cout << "Mode canonique restauré.\n";

    return 0;
}