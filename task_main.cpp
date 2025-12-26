#include <ncurses.h>
#include "task.hpp"


int main(void) {

    initscr();
    start_color();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    WINDOW *ConstWin = newwin(5, COLS, 0, 0);

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
    WDRAW(ConstWin, YELLOW);
    wprintw(ConstWin, "<TASK : GESTIONNAIRE DE TACHE>");
    wnoutrefresh(ConstWin);
    WCLEAR(ConstWin, YELLOW);
    WVER_TAB(ConstWin);
    while(IsFirstConnexion) if(LogAccount(stdscr, Tasks, FocusAcc, FILE_ACCOUNT_DATA) < 0) return (int)error::undefined_error;


    while(Input != EXIT) {
        printw("Que voulez vous faire :");
        VER_TAB();
        wnoutrefresh(stdscr);
        doupdate();

        DisplayOption(stdscr, aOption);
        GetIndexFromChar(Input);
        switch(Input) {
            clear();
            printw("colone : %d", COLS);
            printw("line : %d", LINES);
            case DISPLAY: DisplayTask(stdscr, Tasks,  FocusAcc); break;
            case ADD: AddTask(stdscr, Tasks, FocusAcc); break;
            case REMOVE: RemoveTask(stdscr, Tasks, FocusAcc); break;
            case VALID: ValidTask(stdscr, Tasks, FocusAcc); break;
            case INFO: TaskInfo(stdscr, Tasks, FocusAcc); break;
            case ACCOUNT: LogAccount(stdscr, Tasks, FocusAcc, FILE_ACCOUNT_DATA); break;
            case KEY_RESIZE: ResizeScreens(ConstWin, stdscr);
            default: InputError(stdscr); break;
        }

        save(Tasks, FocusAcc, FILE_TASK_DATA);
        doupdate();
    }

    delwin(ConstWin);
    endwin();
    return (int)error::none;
}
