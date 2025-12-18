#ifndef __TASK_
#define __TASK_


#include <iostream>
#include <vector>
#include <array>
#include <iomanip>
#include <fstream>


#define DISPLAY 1
#define ADD 2
#define REMOVE 3
#define VALID 4
#define INFO 5
#define ACCOUNT 6
#define EXIT 7

#define FILE_TASK_DATA ".task.save.tasks.data.bin"
#define FILE_ACCOUNT_DATA  ".task.save.account.data.bin"

#define BUFFER_SIZE 100
#define INPUT_SIZE 99
#define MAX_TITLE_DISPLAY_SIZE 35

#define RED_ID 1
#define GREEN_ID 2
#define YELLOW_ID 3
#define PURPLE_ID 4

#define RED COLOR_PAIR(RED_ID)
#define GREEN COLOR_PAIR(GREEN_ID)
#define YELLOW COLOR_PAIR(YELLOW_ID)
#define PURPLE COLOR_PAIR(PURPLE_ID)

#define TAB '\t'
#define ENDL() printw("\n");
#define VER_TAB() printw("\n\v");

#define BOLD A_BOLD
#define LIGHT A_DIM
#define UNDERLINE A_UNDERLINE
#define OVERLINE A_REVERSE

#define DRAW(ATT) attron(ATT)
#define CLEAR(ATT) attroff(ATT)


extern bool IsFirstConnexion;





class Task {

private :
    std::string m_title;
    std::string m_description;
    bool m_done = false;

public :
    Task(void);
    explicit Task(std::string_view, std::string_view);
    Task(const Task&);

public :
    inline void setTitle(std::string_view);
    inline void setDescription(std::string_view);

    inline std::string getTitle(void) const;
    inline std::string getDescription(void) const;

    inline bool isDone(void) const;
    inline void hasDone(bool);


public :
    void save(std::ofstream&);
    void load(std::ifstream&);

public :
    ~Task(void);
};










class Account {
private :
    std::vector<Task> m_task;
    std::string m_name;
    std::string m_password;
    static int m_count_acc_nm;

public :
    Account(std::string_view, std::string_view);
    Account(void);
    Account(const Account&);


public :
    void setPassword(std::string_view pw);
    void setName(std::string_view);

    std::string getName(void) const;
    std::vector<Task>& getTask(void);

    bool isPassword(std::string_view);

public :
    int save(std::ofstream&);
    int load(std::ifstream&);

public :
    friend int SaveAccount(std::vector<Account>&, std::ofstream&);
    friend int LoadAccount(std::vector<Account>&, std::ifstream&);
};


void Input(std::string&);
void GetIndexFromChar(int&);
int  InputError(void);
void InitColor(void);
void CreateFile(std::string_view);
void DisplayOption(std::array<std::string, 7>);
void DisplayTask(std::vector<Account>&, uint32_t);
void AddTask(std::vector<Account>&, uint32_t);
int RemoveTask(std::vector<Account>&, uint32_t);
int ValidTask(std::vector<Account>&, uint32_t);
int TaskInfo(std::vector<Account>&, uint32_t);
int SaveAccount (std::vector<Account>&, std::ofstream&);
int LoadAccount (std::vector<Account>&, std::ifstream&);
int LogAccount(std::vector<Account>&, uint32_t&, std::string_view);
int save(std::vector<Account>&, uint32_t&,  std::string_view);
int load(std::vector<Account>&, uint32_t&, std::string_view);





template<typename... Args>
void CreateFile(std::string_view FILE, Args... other) {
    CreateFile(FILE);
    CreateFile(other...);
}

#endif

