#include <ncurses.h>
#include "task.hpp"
#include "task_def.cpp"


int main(void) {
    
    init_win();
    start_color();
    cbreak();
    noecho();

    refresh();
    
    
    std::vector<Account> Tasks;
    uint32_t FocusAcc(0);

    int _input(0);
    
    std::array<std::string, 7> aOption;
    
    aOption.at(0) = "1 - afficher .";
    aOption.at(1) = "2 - ajouter .";
    aOption.at(2) = "3 - supprimer .";
    aOption.at(3) = "4 - valider .";
    aOption.at(4) = "5 - info .";
    aOption.at(5) = "6- compte .";
    aOption.at(6) = "7 - quitter .";
    
    CreateFile(_FILE_, _FILE_ACC_);
    
    load(Tasks, FocusAcc, _FILE_);
    
    Print(YELLOW, std::setw(LINE_WIDTH), "<TASK : GESTIONNAIRE DE TACHE>", "\n\v", RESET);
    
     while(IsFirstConnexion) if(LogAccount(Tasks, FocusAcc, _FILE_ACC_) < 0) return -1;
     
     std::cout << std::left;
 

    while(_input != EXIT) {
        Print("Que voulez vous faire : \n\v");
        DisplayOption(aOption);
        std::cin >> _input;
        if(_input == DISPLAY) DisplayTask(Tasks, FocusAcc, LINE_WIDTH);
        else if(_input == ADD) AddTask(Tasks, FocusAcc);
        else if(_input == REMOVE) RemoveTask(Tasks, FocusAcc);
        else if(_input == VALID) ValidTask(Tasks, FocusAcc);
        else if(_input == INFO) TaskInfo(Tasks, FocusAcc);
        else if(_input == ACCOUNT) LogAccount(Tasks, FocusAcc, _FILE_ACC_);
        InputGuard();
        save(Tasks, FocusAcc, _FILE_);
    }

    erase();
    endwin();
}
