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


#define _FILE_ "task_save_data.bin" 
#define _FILE_ACC_ "task_save_account_data.bin"

#define FLUSH()  std::cout << std::flush
#define ENDL() std::cout << std::endl

#define LINE_WIDTH 40

#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define PURPLE "\033[34m"

#define TAB "    "
#define BOLD "\033[1m"
#define LIGHT "\033[2m"
#define UNDERLINED "\033[4m"
#define RESET "\033[0m"



bool IsFirstConnexion = true;





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
    
    inline std::string_view getTitle(void) const;
    inline std::string_view getDescription(void) const;
    
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
    
    std::string_view getName(void) const;
    std::vector<Task>& getTask(void);
    
    bool isPassword(std::string_view);

public :
    int save(std::ofstream&);
    int load(std::ifstream&);
    
public :
    friend int SaveAccount(std::vector<Account>&, std::ofstream&);
    friend int LoadAccount(std::vector<Account>&, std::ifstream&);
};



void Clear(void);
int InputGuard(void);
void CreateFile(std::string_view);
void DisplayOption(std::array<std::string, 7>);
void DisplayTask(std::vector<Account>&, uint32_t, int&&);
void AddTask(std::vector<Account>&, uint32_t);
int RemoveTask(std::vector<Account>&, uint32_t);
int ValidTask(std::vector<Account>&, uint32_t);
int TaskInfo(std::vector<Account>&, uint32_t);
int SaveAccount (std::vector<Account>&, std::ofstream&);
int LoadAccount (std::vector<Account>&, std::ifstream&);
int LogAccount(std::vector<Account>&, uint32_t&, std::string_view);
int save(std::vector<Account>&, uint32_t&,  std::string_view);
int load(std::vector<Account>&, uint32_t&, std::string_view);






void Print(void) {}
template<typename T, typename... Args>
void Print(T arg, Args... args) {
    std::cout << arg;
    Print(args...);
}
template<typename... Args>
void CreateFile(std::string_view FILE, Args... other) {
    CreateFile(FILE);
    CreateFile(other...);
}

#endif