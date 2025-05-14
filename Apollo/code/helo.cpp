#include <iostream>
#include <string>
#include <termios.h>
#include <unistd.h>

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

void avance(){
    cout<< "Avance\n"<<endl;
}
void recule(){
    cout<< "Recule\n"<<endl;
}
void droite(){
    cout<< "Droite\n"<<endl;
}
void gauche(){
    cout<< "Gauche\n"<<endl;
}


int main() {
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
        if (c == 'z') avance();
        if (c == 's') recule();
        if (c == 'd') droite();
        if (c == 'q') gauche();
    }

    // Restaurer les paramètres d'origine
    resetTerminalMode(original);
    std::cout << "Mode canonique restauré.\n";

    return 0;
}

  