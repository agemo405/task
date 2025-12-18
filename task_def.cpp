#include <ncurses.h>
#include "task.hpp"


int Account::m_count_acc_nm = 0;
bool IsFirstConnexion = true;

Task::Task(void) : m_title("tache sans nom . "), m_description("aucune description . ") {}

Task::Task(std::string_view TITLE, std::string_view DESC) : m_title(TITLE), m_description(DESC) {

    if(m_title == "") m_title = "tache sans nom ";
    if(m_description =="") m_description = "aucune description .";

}

Task::Task(const Task&) = default;

void Task::setTitle(std::string_view title) { m_title = title; }
void Task::setDescription(std::string_view desc) { m_description = desc; }

std::string Task::getTitle(void) const { return m_title; }

std::string Task::getDescription(void) const { return m_description; }

bool Task::isDone(void) const { return m_done; }

void Task::hasDone(bool statut) { m_done = statut; }

void Task::save(std::ofstream& file) {
    size_t title_size = m_title.size();
    size_t desc_size = m_description.size();

    file.write(reinterpret_cast<const char*>(&m_done), sizeof(m_done));
    file.write(reinterpret_cast<const char*>(&title_size), sizeof(title_size));
    file.write(reinterpret_cast<const char*>(&desc_size), sizeof(desc_size));

    file.write(m_title.c_str(), title_size);
    file.write(m_description.c_str(), desc_size);
}

void Task::load(std::ifstream& file) {
    size_t title_size;
    size_t desc_size;

    file.read(reinterpret_cast<char*>(&m_done), sizeof(m_done));
    file.read(reinterpret_cast<char*>(&title_size), sizeof(title_size));
    file.read(reinterpret_cast<char*>(&desc_size), sizeof(desc_size));

    m_title.resize(title_size);
    m_description.resize(desc_size);

    file.read(const_cast<char*>(m_title.data()), title_size);
    file.read(const_cast<char*>(m_description.data()), desc_size);

}

Task::~Task(void) = default;


Account::Account(std::string_view name, std::string_view password) : m_name(name), m_password(password) {
    if(m_name == "") {
        m_count_acc_nm++;
        auto a = std::to_string(m_count_acc_nm);
        m_name = "compte" + a;
    }
}

Account::Account(void) = default;

Account::Account(const Account&) = default;

void Account::setPassword(std::string_view pw) {
    m_password = pw;
}
void Account::setName(std::string_view nm) {
    m_name = nm;
    if(m_name == "") {
        m_count_acc_nm++;
        auto a = std::to_string(m_count_acc_nm);
        m_name = "compte" + a;
    }
}
std::string Account::getName(void) const  {
    return m_name;
}
std::vector<Task>& Account::getTask(void)  {
    return m_task;
}
bool Account::isPassword(std::string_view pw) {
    if(m_password == pw) return true;
    else return false;
}

int Account::save(std::ofstream& ofs) {

    if(!ofs.is_open()) return -1;
    size_t size = m_task.size();

    ofs.write(reinterpret_cast<const char*>(&size), sizeof(size));
    for(auto& e : m_task) e.save(ofs);
    return 0;

}

int Account::load(std::ifstream& ifs) {

    if(!ifs.is_open()) return -1;
    if(ifs.peek() == std::ifstream::traits_type::eof()) return 0;
   size_t size;
    ifs.read(reinterpret_cast<char*>(&size), sizeof(size));

    for(int i = 0; i < size; i++) {
        Task task;
        task.load(ifs);
        m_task.emplace_back(std::move(task));
    }

    return 0;
}



void Input(std::string& str) {
    nocbreak();
    echo();

    char buffer[BUFFER_SIZE];
    getnstr(buffer, INPUT_SIZE);
    str = buffer;

    cbreak();
    noecho();
}


void GetIndexFromChar(int& d) {
    char input = getch();
    d = input - 48;
}


int InputError(void) {
    DRAW(RED);
    DRAW(BOLD);
    printw("entrée invalide ! .");
    CLEAR(BOLD);
    CLEAR(RED);
    ENDL();
}



void InitColor(void) {
    init_pair(RED_ID, COLOR_RED, COLOR_BLACK);
    init_pair(GREEN_ID, COLOR_GREEN, COLOR_BLACK);
    init_pair(YELLOW_ID, COLOR_YELLOW, COLOR_BLACK);
    init_pair(PURPLE_ID, COLOR_MAGENTA, COLOR_BLACK);
}


void CreateFile(std::string_view FILE) {
    std::ofstream of(FILE, std::ios::binary | std::ios::app);
    of.close();
}






void DisplayOption(std::array<std::string, 7> vec) {
   ENDL();
    for(const auto& e : vec) {
       printw("%s", e.c_str());
        ENDL();
    }
}






void DisplayTask(std::vector<Account>& vec, uint32_t f) {
   ENDL();
   int i = 1;

   auto& temp = vec.at(f);

   if(temp.getTask().empty()) printw("aucune tache disponible . \n");


   else {

        for(const auto& e : temp.getTask()) {
            std::string sub = std::string(e.getTitle());

            char symb;
            int str_end = sub.length() - 1;
            int max_size = MAX_TITLE_DISPLAY_SIZE;
            if(str_end > max_size) {
                sub = sub.substr(0, max_size) + "...";
            }

            if(e.isDone()) {
                #define COLOR GREEN
                symb = '0';
            }
            else {
                #define COLOR RED
                symb = 'X';
            }

            printw("%d - %-40s", i, sub.c_str());
            DRAW(COLOR);
            printw( "[%c]", symb);
            CLEAR(COLOR);
            ++i;
        }
   }
   VER_TAB();
   refresh();
}








void AddTask(std::vector<Account>& vec, uint32_t f) {
    std::string title, desc;

    printw("Quel est le ");
    DRAW(PURPLE);
    printw("titre");
    CLEAR(PURPLE);
    printw(" de la tache : %c", TAB);
    Input(title);

    printw("Quel est la ");
    DRAW(PURPLE);
    printw("description");
    CLEAR(PURPLE);
    printw( " de la tache : %c", TAB);
    Input(desc);

    auto& temp = vec.at(f);
    temp.getTask().emplace_back(Task(title, desc));
    DRAW(GREEN);
    DRAW(BOLD);
    printw("tache ajoute .");
    CLEAR(BOLD);
    CLEAR(GREEN);
    VER_TAB();
}


int RemoveTask(std::vector<Account>& vec, uint32_t f ) {

    int index = 0;
    printw("Quel tache voulez vous supprimer : ");
    GetIndexFromChar(index);

    auto& temp = vec.at(f);

    if(index <= 0 || index > temp.getTask().size()) {
        InputError();
        VER_TAB();
        return -1;
    }

    --index;

    temp.getTask().erase(temp.getTask().begin() +  index);
    DRAW(GREEN);
    DRAW(BOLD);
    printw("tache supprimer .");
    DRAW(BOLD);
    DRAW(GREEN);
    VER_TAB();
    return 0;
}








int ValidTask(std::vector<Account>& vec, uint32_t f) {

    int index;
    printw("quelle tache a ete accomplie : ");
    GetIndexFromChar(index);


    if(index <=0 || index > vec.at(f).getTask().size()) {
        InputError();
        return -1;
    }

    --index;

    auto& temp = vec.at(f);
    auto& temp2 = temp.getTask().at(index);

    if(temp2.isDone()) temp2.hasDone(false);
    else temp2.hasDone(true);

    return 0;
}








int TaskInfo(std::vector<Account>& vec, uint32_t f) {
    int index = 0;

    printw("Quelle tache voulez vous connaitre les details : ");
    GetIndexFromChar(index);

    auto& temp = vec.at(f);

    if(index > temp.getTask().size()) {
        InputError();
        return -1;
    }

    --index;

    auto temp2 = temp.getTask().at(index);
    VER_TAB();

    printw("%s :\n%s . ", temp2.getTitle().c_str(), temp2.getDescription().c_str());
    VER_TAB();

    return 0;
}




int SaveAccount (std::vector<Account>&vec, std::ofstream& ofs) {

    for(auto& e : vec) {

        size_t size_pw = e.m_password.length();
        ofs.write(reinterpret_cast<const char *>(&size_pw), sizeof(size_pw));  
        ofs.write(e.m_password.c_str(), size_pw);

        size_t size_nm = e.m_name.length();
        ofs.write(reinterpret_cast<const char *>(&size_nm), sizeof(size_nm));  
        ofs.write(e.m_name.c_str(), size_nm);
    }

}






int LoadAccount (std::vector<Account>& vec, std::ifstream& ifs) {

    if(ifs.peek() == std::ifstream::traits_type::eof())
        return 0;
    for(auto& e : vec) {

        size_t size_pw;
        ifs.read(reinterpret_cast<char *>(&size_pw), sizeof(size_pw));  
        e.m_password.resize(size_pw);
        ifs.read(const_cast<char *>(e.m_password.data()), size_pw);

        size_t size_nm;
        ifs.read(reinterpret_cast<char *>(&size_nm), sizeof(size_nm));  
        e.m_name.resize(size_nm);
        ifs.read(const_cast<char *>(e.m_name.data()), size_nm);
    }
    return 0;

}









int LogAccount(std::vector<Account>& _acc, uint32_t& f, std::string_view FILE) {

    std::ifstream ifs(FILE, std::ios::binary);

    if(ifs.is_open()) LoadAccount(_acc, ifs);

    ifs.close();

    int input = 0;

    if(IsFirstConnexion) {
        printw("Bienvenu sur task : gestionnaire de tache .\nVeillez creer un compte pour commencer .");
        ENDL();
    }

    printw("que voulez vous faire :");
    VER_TAB();
    printw("1 - creer un compte .\n");
    printw("2 - se connecter a un compte existant .\n");
    GetIndexFromChar(input);


    if(input <= 0 || input > 2) {
        InputError();
        return -1;
    }

    if(input == 1) {

        std::string name;
        std::string password, tpassword;

        VER_TAB();
        printw("quel est le nom du compte : ");
        Input(name);

        do {
            VER_TAB();
            printw("veuillez saisir un mot de passe : ");
            Input(password);

            VER_TAB();
            printw("veuillez confirmer le mot de passe : ");
            Input(tpassword);

            if(password != tpassword) printw("mot de passe incorrecte .\n");

            else {
                Account acc(name, password);
                printw("compte cree avec succes");
                VER_TAB();

                _acc.emplace_back(std::move(acc));
                f = _acc.size() - 1;
                std::ofstream ofs(FILE, std::ios::binary);
                if(ofs.is_open())
                    SaveAccount(_acc, ofs);
                ofs.close();
                IsFirstConnexion = false;
            }
        } while(password != tpassword);
    }

    else if(input == 2) {
        int i = 1;
        int index = 0;
        std::string pw;

        printw("a quel compte voulez-vous vous connecter : \n\v");
        for(const auto& e : _acc) {
            printw("%d - %s",i ,e.getName().c_str());
            ENDL();
            i++;
        }
        GetIndexFromChar(index);
        --index;

        if(index >= _acc.size()) {
            InputError();
            return -1;
        }

        auto& temp = _acc.at(index);
        printw("veuillez saisir le mot de passe : ");
        Input(pw);

        if(temp.isPassword(pw)) {
            f = index;
            DRAW(GREEN);
    	    DRAW(BOLD);
            printw("compte connecte .");
	    CLEAR(BOLD);
            CLEAR(GREEN);
            VER_TAB();
        }
        else {
            DRAW(RED);
            DRAW(BOLD);
            printw("mot de passe incorrecte, l\'acces au compte a ete refuse .");
            CLEAR(BOLD);
	    CLEAR(RED);
            VER_TAB();
            return -1;
        }
    }
    refresh();
    return 0;
}









int save(std::vector<Account>& vec,uint32_t& focus,  std::string_view FILE) {
    std::ofstream ofs(FILE , std::ios::binary);
    if(!ofs.is_open()) return -1;
    size_t size = vec.size();

    ofs.write(reinterpret_cast<const char*>(&size), sizeof(size));
    ofs.write(reinterpret_cast<const char*>(&focus), sizeof(focus));
    ofs.write(reinterpret_cast<const char*>(&IsFirstConnexion), sizeof(bool));
    for(auto& e : vec) e.save(ofs);
    ofs.close();
    return 0;
}









int load(std::vector<Account>& vec, uint32_t& focus, std::string_view FILE) {
    std::ifstream ifs(FILE  , std::ios::binary);
    if(!ifs.is_open()) return -1;
    if(ifs.peek() == std::ifstream::traits_type::eof()) return 0;
    size_t size;
    ifs.read(reinterpret_cast<char*>(&size), sizeof(size));
    ifs.read(reinterpret_cast<char*>(&focus), sizeof(focus));
    ifs.read(reinterpret_cast<char*>(&IsFirstConnexion), sizeof(bool));
    for(int i = 0; i < size; i++) {
        Account acc;
        acc.load(ifs);
        vec.emplace_back(std::move(acc));
    }

    ifs.close();
    return 0;
}
