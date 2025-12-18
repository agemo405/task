#include <ncurses.h>
#include "task.hpp"


int main(void) {

    initscr();
    start_color();
    cbreak();
    noecho();


    std::vector<Account> Tasks;
    uint32_t FocusAcc(0);
    int Input(0);

    std::array<std::string, 7> aOption;

    aOption.at(0) = "1 - afficher .";
    aOption.at(1) = "2 - ajouter .";
    aOption.at(2) = "3 - supprimer .";
    aOption.at(3) = "4 - valider .";
    aOption.at(4) = "5 - info .";
    aOption.at(5) = "6- compte .";
    aOption.at(6) = "7 - quitter .";

    CreateFile(FILE_TASK_DATA, FILE_ACCOUNT_DATA);
    InitColor();

    load(Tasks, FocusAcc, FILE_TASK_DATA);
    DRAW(YELLOW);
    printw("<TASK : GESTIONNAIRE DE TACHE>");
    CLEAR(YELLOW);
    VER_TAB();
    while(IsFirstConnexion) if(LogAccount(Tasks, FocusAcc, FILE_ACCOUNT_DATA) < 0) return -1;


    while(Input != EXIT) {
        printw("Que voulez vous faire :");
        VER_TAB();
        DisplayOption(aOption);
        GetIndexFromChar(Input);

        if(Input == DISPLAY) DisplayTask(Tasks, FocusAcc);
        else if(Input == ADD) AddTask(Tasks, FocusAcc);
        else if(Input == REMOVE) RemoveTask(Tasks, FocusAcc);
        else if(Input == VALID) ValidTask(Tasks, FocusAcc);
        else if(Input == INFO) TaskInfo(Tasks, FocusAcc);
        else if(Input == ACCOUNT) LogAccount(Tasks, FocusAcc, FILE_ACCOUNT_DATA);
        else InputError();
        save(Tasks, FocusAcc, FILE_TASK_DATA);
    }

    endwin();
}
