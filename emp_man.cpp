#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <sys/types.h>
#include <cstdlib>
#include <string.h>
#include <filesystem>
#include <sstream>
#include <cstdio>

#define LOGIN_SIZE 25
#define PASS_SIZE 15
#define num_of_employee 12
#define TOTAL_WORKING_DAYS 300
#define MAX_NUM_LEAVE 5

int count[2][4] = {0}, i=0; 
std::string dep[] = {"CSE", "ECE"} ;
std::string year[] = {"2018", "2019", "2020"} ;

using namespace std ;


void emp_menu(std::string empid) ;

inline bool exists_test(const std::string& name) 
{
  struct stat buffer;   
  return (stat (name.c_str(), &buffer) == 0); 
}

class company
{
    protected:
    //std::string compid ;

    public:
    company()
    {
        //compid = "//" ;
    }
    virtual void read(std::string)= 0 ;
};


//employee class contains id, name, gender, DOB, Joining Date ,salary - personal and professional data
class employee: public company
{
    protected: 
    std::string emp_ID, emp_Name, aadhar, date_of_leave;
    float salary;
    char gender;
    int  DOB_dd,DOB_mm,DOB_year, DOJ_dd,DOJ_mm,DOJ_year, active, num_of_present_days, num_of_leave, perks, Medical, PPF ;

    public:
    employee() 
    {
        emp_ID = "/" ;
        emp_ID.resize(25) ;
        salary = 0 ;
        emp_Name = "/" ;
        gender = '/' ;
        DOB_dd = 0;
        DOB_mm = 0;
        DOB_year = 0 ;
        DOJ_dd = 0;
        DOJ_mm = 0;
        DOJ_year = 0 ;
        active = 0 ;
        num_of_present_days = 0;
        num_of_leave = 0;
        date_of_leave = "/" ;
    }

    //friend void emp_menu(std::string, executive*, manager*, president*, worker*); 
    void read(std::string) ;
    void work_position(std::string) ;
    friend void add_member() ;
    friend void delete_emp() ;
    void set();
    void data_show(std::string);
    void emp_menu(std::string) ;
    void display() ; //to display all employee's details
    void display(int)   ;   //display 1 employee details
    void dump(int, std::string) ;    //takes line no.and string
    int dump() ;   //direct dump

};

// department class conatins id, name, and no. of people in a particular department
class department: public company
{
    int dep_num_people, active;
    std::string dep_Name, dep_ID;

    public:
    department()
    {
        dep_ID = "/" ;
        dep_Name = "/" ;
        dep_num_people = 0 ;
        active = 0 ;
    }

    void set()
    {
        cout<<"Enter Department ID:"<<endl;
        cin >> dep_ID ;
        //cin.ignore() ;
        cout<<"Enter Department Name:"<<endl;
        cin >> dep_Name ;
        //cin.ignore() ;
        cout<<"Enter No. of Members in Department:" << endl;
        cin >> dep_num_people ;
        active = 1 ;
        cout<<"Since a new Department is being added to company, it's active status is set to 1:" << endl;
    }
    friend void add_dep() ;
    void read(std::string) ;
    int dep_dump(int , std::string ,std::string) ;
    int dep_dump(std::string, int) ;
    int dep_file(std::string) ; //takes path
    void display_dep() ;     //all
    void display_dep(std::string) ;    // display department details
    void dep_del(std::string) ;

};



//function to write department details to file
int department::dep_dump(std::string ddp, int a=1)
{
    ddp = ddp + ".txt" ;
    cout << "dump file path:" << ddp << endl ;
    
    display_dep(ddp) ;
    // dump in file and close the file

            fstream fd ;
            fd.open(ddp, ios::out) ;
            //int count =0 , flag=0;
            //std::string epath = emp_ID + ".txt" ;


            if(!fd)
            {
                cout << "\n\t\t\t Error opening department file!" << endl ;
                return -1 ;
            }
            else
            {
                active = a ;
                cout << "\n length of string: "<< ddp.length() <<endl ;
                cout << "\n length of dep_ID: "<< dep_ID.length() << ", " << dep_ID <<endl ;
                cout << "\n length of dep_Name: "<< dep_Name.length()  << ","<< dep_Name << endl ;
                cout << "\n dep_num_people: "<< dep_num_people <<endl ;
                cout << "\n active: "<< active <<endl ;
                //cout << "\n"<< "~~~~~~~~~~~~~~~~~~~~~~".length()  << ","<<dep_Name << endl ;

                fd << dep_ID << "\n" ;
                fd << dep_Name << "\n" ;
                fd << dep_num_people << "\n" ;
                fd << active << "\n" ;
                fd << "~~~~~~~~~~~~~~~~~~~~~~" ;
                
                fd.close() ;
                return 1 ;
            }
                    
}


//using namespace std ;
//int count[2][4] = {0}, i=0; 
//std::string dep[] = {"CSE", "ECE"} ;
//std::string year[] = {"2018", "2019", "2020"} ;

//function to plot graphs, is overloaded, recruit.txt
void recruit_stats()
{
    int i=0; 
    std::string path = "LOGIN/emp_login.txt", line ;
    ifstream rf(path, ios::in) ;

    if(!rf)   //error in opening file
    {
        cout << "\n\t\t\t No such file exists!!\n\t\t\t Type the employee ID correctly! \n\t\t\t Don't try to hack our systems\n" << endl ;
        cout<<"\n Exiting..." << endl ;
    }

    else        //if employee file found
    {
        //cin.flush() ;
        while(std::getline(rf, line , '\n'))
            {
                i+=1 ;
                cout << "\n----i:" << i <<endl ;
                cout << line <<endl ;      
                if(line.substr(4, 3) == dep[0])
                {
                    count[0][3] +=1 ;
                    cout<< "\n CSE count: " <<count[0][3] << endl ;
                    cout << "\n CSE" << endl ;
                    if(line.substr(8, 4) == year[0])  //2018
                    {
                        count[0][0] +=1 ;
                    }
                    else
                    {
                        if(line.substr(8, 4) == year[1])  //2019
                        {
                            count[0][1] +=1 ;
                        }
                        else
                        {
                            if(line.substr(8, 4) == year[2])  //2020
                            {
                                count[0][2] +=1 ;
                            }
                        }
                    }
                    
                }
                else
                {
                    if(line.substr(4, 3) == dep[1])
                    {
                        count[1][3] += 1 ;
                        cout<< "\n ECE count: " <<count[1][3] << endl ;
                        cout << "\n ECE" << endl ;
                        if(line.substr(8, 4) == year[0])  //2018
                        {
                            count[1][0] +=1 ;
                        }
                        else
                        {
                            if(line.substr(8, 4) == year[1])  //2019
                            {
                                count[1][1] +=1 ;
                            }
                            else
                            {
                                if(line.substr(8, 4) == year[2])  //2020
                                {
                                    count[1][2] +=1 ;
                                }
                            }
                        }
                    }
                    else
                    {
                        cout<< "\n No match!" << endl ;
                    }
                    
                }
                
            }

        cout << "\n--------------------------DONE--------------------------\n" << endl ;
        cout << "\n CSE:" << count[0][3] << endl ;
        cout << "\n ECE:" << count[1][3] << endl ;
        cout << "\n CSE:" << count[0][0] << ", "<<count[0][1]<< ", " << count[0][2] << endl ;
        cout << "\n ECE:" << count[1][0]<< ", " << count[1][1] << ", " << count[1][2] << endl ;

        ofstream tof("STATS/recruit.txt", ios::out) ; 
        tof << dep[0] << "\n" ;
        tof << year[0] << " "<< count[0][0] << "\n" ;
        tof << year[1] << " "<< count[0][1]<< "\n" ;
        tof << year[2] << " "<< count[0][2] << "\n\n\n";

        tof << dep[1] << "\n" ;
        tof << year[0] << " "<< count[1][0]<< "\n" ;
        tof << year[1] << " "<< count[1][1] << "\n" ;
        tof << year[2] << " "<< count[1][2] ;

        tof.close() ;
        rf.close() ;   
    }
    
}


void check(std::string line)
{
    cout << line <<endl ;      
            if(line.substr(4, 3) == dep[0])
                {
                    count[0][3] +=1 ;
                    cout<< "\n CSE count: " <<count[0][3] << endl ;
                    cout << "\n CSE" << endl ;
                    if(line.substr(8, 4) == year[0])  //2018
                    {
                        count[0][0] +=1 ;
                    }
                    else
                    {
                        if(line.substr(8, 4) == year[1])  //2019
                        {
                            count[0][1] +=1 ;
                        }
                        else
                        {
                            if(line.substr(8, 4) == year[2])  //2020
                            {
                                count[0][2] +=1 ;
                            }
                        }
                    }
                    
                }
                else
                {
                    if(line.substr(4, 3) == dep[1])
                    {
                        count[1][3] += 1 ;
                        cout<< "\n ECE count: " <<count[1][3] << endl ;
                        cout << "\n ECE" << endl ;
                        if(line.substr(8, 4) == year[0])  //2018
                        {
                            count[1][0] +=1 ;
                        }
                        else
                        {
                            if(line.substr(8, 4) == year[1])  //2019
                            {
                                count[1][1] +=1 ;
                            }
                            else
                            {
                                if(line.substr(8, 4) == year[2])  //2020
                                {
                                    count[1][2] +=1 ;
                                }
                            }
                        }
                    }
                    else
                    {
                        cout<< "\n No match!" << endl ;
                    }
                    
                }
}

//function to plot graphs, is overloaded, position_count.txt
void recruit_stats(int i)
{
    int count_pos[4][3][2] = {0}; 
    //std::string dep[] = {"CSE", "ECE"} ;
    //std::string year[] = {"2018", "2019", "2020"} ;
    std::string path = "LOGIN/emp_login.txt", line ;
    ifstream rf(path, ios::in) ;
    std::string pos[] = {"EXE", "MAN", "PRE", "WOR"} ;

    if(!rf)   //error in opening file
    {
        cout << "\n\t\t\t No such file exists!!\n\t\t\t Type the employee ID correctly! \n\t\t\t Don't try to hack our systems\n" << endl ;
        cout<<"\n Exiting..." << endl ;
    }

    else        //if employee file found
    {
        //cin.flush() ;
        while(std::getline(rf, line , '\n'))
            {
                i+=1 ;
                cout << "\n----i:" << i <<endl ;
                cout << line <<endl ;      
                if(line.substr(13, 3) == pos[0])  //exe
                {
                    //count[0][3][0] +=1 ;
                    cout<< "\n EXE count: " <<count[0][3] << endl ;
                    cout << "\n EXECUTIVE" << endl ;
                    check(line) ;
                    count_pos[0][0][0] += count[0][0] ;   //2018
                    count_pos[0][0][1] += count[1][0] ;
                    count_pos[0][1][0] += count[0][1] ;    //2019
                    count_pos[0][1][1] += count[1][1] ;
                    count_pos[0][2][0] += count[0][2] ;    //2020
                    count_pos[0][2][1] += count[1][2] ;
                    count[0][0] = 0 ;
                    count[0][1] = 0 ;
                    count[0][2] = 0 ;
                    count[1][0] = 0 ;
                    count[1][1] = 0 ;
                    count[1][2] = 0 ;
                }
                else
                {
                    if(line.substr(13, 3) == pos[1])      //man
                    {
                        //count[1][3][1] += 1 ;
                        cout<< "\n MAN count: " <<count[1][3] << endl ;
                        cout << "\n MANAGER" << endl ;
                        check(line) ;
                        count_pos[1][0][0] += count[0][0] ;   //2018
                        count_pos[1][0][1] += count[1][0] ;
                        count_pos[1][1][0] += count[0][1] ;    //2019
                        count_pos[1][1][1] += count[1][1] ;
                        count_pos[1][2][0] += count[0][2] ;    //2020
                        count_pos[1][2][1] += count[1][2] ;
                        count[0][0] = 0 ;
                        count[0][1] = 0 ;
                        count[0][2] = 0 ;
                        count[1][0] = 0 ;
                        count[1][1] = 0 ;
                        count[1][2] = 0 ;
                    }
                    else
                    {
                        if(line.substr(13, 3) == pos[2])   //pre
                        {
                            //count[1][3][1] += 1 ;
                            cout<< "\n PRE count: " <<count[1][3] << endl ;
                            cout << "\n PRESIDENT" << endl ;
                            check(line) ;
                            count_pos[2][0][0] += count[0][0] ;   //2018
                            count_pos[2][0][1] += count[1][0] ;
                            count_pos[2][1][0] += count[0][1] ;    //2019
                            count_pos[2][1][1] += count[1][1] ;
                            count_pos[2][2][0] += count[0][2] ;    //2020
                            count_pos[2][2][1] += count[1][2] ;
                            count[0][0] = 0 ;
                            count[0][1] = 0 ;
                            count[0][2] = 0 ;
                            count[1][0] = 0 ;
                            count[1][1] = 0 ;
                            count[1][2] = 0 ;
                        }
                        else
                        {
                            if(line.substr(13, 3) == pos[3])     //wor
                            {
                                //count[1][3][1] += 1 ;
                                cout<< "\n WOR count: " <<count[1][3] << endl ;
                                cout << "\n WORKER" << endl ;
                                check(line) ;
                                count_pos[3][0][0] += count[0][0] ;   //2018
                                count_pos[3][0][1] += count[1][0] ;
                                count_pos[3][1][0] += count[0][1] ;    //2019
                                count_pos[3][1][1] += count[1][1] ;
                                count_pos[3][2][0] += count[0][2] ;    //2020
                                count_pos[3][2][1] += count[1][2] ;
                                count[0][0] = 0 ;
                                count[0][1] = 0 ;
                                count[0][2] = 0 ;
                                count[1][0] = 0 ;
                                count[1][1] = 0 ;
                                count[1][2] = 0 ;
                            }
                            else
                            {
                                cout<< "\n No match!" << endl ;
                            }
                            
                        }
                        
                    }
                    
                }
                
            }

        cout << "\n--------------------------DONE--------------------------\n" << endl ;
        cout << "\n EXE:" << count[0][3] << endl ;
        cout << "\n MAN:" << count[1][3] << endl ;
        cout << "\n PRE:" << count[0][0] << ", "<<count[0][1]<< ", " << count[0][2] << endl ;
        cout << "\n WOR:" << count[1][0]<< ", " << count[1][1] << ", " << count[1][2] << endl ;

        ofstream tof("STATS/position_count.txt", ios::out) ; 
        tof << pos[0] << "\n" ;
        tof << year[0] << " "<< count_pos[0][0][0] << " "<< count_pos[0][0][1] << "\n" ;
        tof << year[1] << " "<< count_pos[0][1][0] << " "<< count_pos[0][1][1] << "\n" ;
        tof << year[2] << " "<< count_pos[0][2][0] << " "<< count_pos[0][2][1] << "\n\n\n";

        tof << pos[1] << "\n" ;
        tof << year[0] << " "<< count_pos[1][0][0] << " "<< count_pos[1][0][1] << "\n" ;
        tof << year[1] << " "<< count_pos[1][1][0] << " "<< count_pos[1][1][1] << "\n" ;
        tof << year[2] << " "<< count_pos[1][2][0] << " "<< count_pos[1][2][1] << "\n\n\n";

        tof << pos[2] << "\n" ;
        tof << year[0] << " "<< count_pos[2][0][0] << " "<< count_pos[2][0][1] << "\n" ;
        tof << year[1] << " "<< count_pos[2][1][0] << " "<< count_pos[2][1][1] << "\n" ;
        tof << year[2] << " "<< count_pos[2][2][0] << " "<< count_pos[2][2][1] << "\n\n\n";

        tof << pos[3] << "\n" ;
        tof << year[0] << " "<< count_pos[3][0][0] << " "<< count_pos[3][0][1] << "\n" ;
        tof << year[1] << " "<< count_pos[3][1][0] << " "<< count_pos[3][1][1] << "\n" ;
        tof << year[2] << " "<< count_pos[3][2][0] << " "<< count_pos[3][2][1] ;

        tof.close() ;
        rf.close() ;   
    }
    //return ;
    
}

// function to determine work position
void employee::work_position(std::string epath)
{
    std::string work_pos = epath.substr(13,3) ;
    cout << "\n\t\t\tYour Work position:"<< work_pos << endl ;
    

    if(work_pos == "EXE")
    {
        cout <<"\t\t\t You are an Executive" <<endl ;
        perks = 0;
        Medical = 1 ;
        PPF = 1 ;
        data_show(epath) ;
        emp_menu(epath) ;
    }
    else 
    {   if(work_pos == "MAN")
        {
            cout <<"\t\t\t You are a Manager" <<endl ;
            perks = 1;
            Medical = 1 ;
            PPF = 1 ;
            data_show(epath) ;
            emp_menu(epath) ;
        }
        else 
        {   if(work_pos == "PRE")
            {
                cout <<"\t\t\t You are a President" <<endl ;
                perks = 1;
                Medical = 1 ;
                PPF = 0 ;
                data_show(epath) ;
                emp_menu(epath) ;
            }
            else
            {
                cout <<"\t\t\t You are a Worker" <<endl ;
                perks = 0;
                Medical = 1 ;
                PPF = 1 ;
                data_show(epath) ;
                emp_menu(epath) ;
            }
        }
    }
            
}


// function to read the employee details and store it in employee class object
void employee::data_show(std::string path)
{
    fstream emp;
    
    std::string data ; 
    //path.resize(25) ;
    //id.resize(25) ;
    
    int flag=0,count=0, diff=0;   //to choose admin/employee

    //cin.ignore(); 
    
    //cout << "\n Length of string:"<< id.length() << "\t path length:"<< path.length() <<endl ;
    cout << "\n path length:"<< path.length() << ", " <<path <<endl ;
    //path = path + ".txt" ;
    //int f = exists_test(path) ;
    
    emp.open(path, ios::in) ;

    if(!emp)   //error in opening file
    {
        cout << "\n\t\t\t No such employee exists!!\n\t\t\t Type the employe ID correctly! \n\t\t\t Don't try to hack our systems\n" << endl ;
        cout<<"\n Exiting..." << endl ;
        //emp.close() ;
        //exit(0) ;
    }

    else        //if employee file found
    {
        emp_ID = path.substr(0,20) ;

        //cin.flush() ;
            while(std::getline(emp, data , '\n'))
            {
                count+=1 ;
                cout<< "\ncount: " <<count << endl ;
                //read from employee file and store all values in objects
                if(count==1)
                {
                    emp_ID = data ;
                    cout << emp_ID <<endl ; 
                }
                else if(count==2)
                {
                    emp_Name = data ;
                    cout << emp_Name <<endl ; 
                }
                else if(count==3)
                {
                    gender = data[0];
                    cout << gender <<endl ; 
                }
                else if(count==4)
                {
                    aadhar = data ;
                    cout << aadhar <<endl ; 
                }
                else if(count == 5)
                {
                    DOB_dd = stoi(data) ; 
                    cout << DOB_dd <<endl ; 
                }
                 else if(count == 6)
                {
                    DOB_mm = stoi(data) ; 
                    cout << DOB_mm <<endl ; 
                }
                else if(count == 7)
                {
                    DOB_year = stoi(data) ; 
                    cout << DOB_year <<endl ; 
                }
                else if(count == 8)
                {
                    DOJ_dd = stoi(data) ; 
                    cout << DOJ_dd <<endl ; 
                }    
                else if(count == 9)
                {
                    DOJ_mm = stoi(data) ; 
                    cout << DOJ_mm <<endl ; 
                }   
                else if(count == 10)
                {
                    DOJ_year = stoi(data) ; 
                    cout << DOJ_year <<endl ; 
                }   
                else if(count == 11)
                {
                    active = stoi(data) ; 
                    cout << active <<endl ; 
                }  
                else if(count == 12)
                {
                    num_of_present_days = stoi(data) ; 
                    cout << num_of_present_days <<endl ; 
                }  
                else if(count == 13)
                {
                    num_of_leave = stoi(data) ; 
                    cout << num_of_leave <<endl ; 
                }  
                else if(count == 14)
                {
                    date_of_leave = data ; 
                    cout << date_of_leave <<endl ; 
                }
                else if(count == 15)
                {
                    perks = stoi(data) ; 
                    cout << perks <<endl ; 
                }  
                else if(count == 16)
                {
                    Medical = stoi(data) ; 
                    cout << Medical <<endl ; 
                }  
                else if(count == 17)
                {
                    PPF = stoi(data) ; 
                    cout << PPF <<endl ; 
                } 
                else if(count == 18)
                {
                    salary = stof(data) ; 
                    cout << salary <<endl ; 
                } 
            }

        cout << "\n--------------------------DONE--------------------------\n" << endl ;
        //cin.ignore() ;
        emp.close() ;   
    }
    //return ;
}


//set the values of employee class object
void employee::set() 
{
    cin.ignore();
    cout<<"Enter Employee ID:"<<endl;
    std::getline(cin,emp_ID) ;
    cout<<"Enter Employee Name:"<<endl;
    std::getline(cin,emp_Name) ;
    cout<<"Enter Gender:"<<endl;
    cin>> gender;
    cout<<"Enter aadhar number (eg. 1234-1234-1234-1234):"<<endl;
    cin >> aadhar ;

    cin.ignore();
    cout<<"\nEnter DOB"<<endl;
    cout<<"Enter day(01-30/01-31/01-28/01-29), eg. 08 or 26:"<<endl;
    cin>>DOB_dd;
    cout<<"Enter month(1-12), eg. 08 or 12:"<<endl;
    cin>>DOB_mm;
    cout<<"Enter year, eg. 2000 or 2018:"<<endl;
    cin>>DOB_year;

    cin.ignore();
    cout<<"\nEnter Date of Joining"<<endl;
    cout<<"Enter day(01-30/01-31/01-28/01-29), eg. 08 or 26:"<<endl;
    cin>>DOJ_dd;
    cout<<"Enter month(01-12), eg. 08 or 26:"<<endl;
    cin>>DOJ_mm;
    cout<<"Enter year, eg. 08 or 26:"<<endl;
    cin>>DOJ_year;

    cin.ignore();
    cout<<"\nEnter salary:"<<endl;
    cin>>salary;
    cout << "\nSince a new employee is being added, active status is set to 1" <<endl ;
    active =1 ;
    num_of_present_days =0;
    num_of_leave = 0 ;
    date_of_leave = "0" ;

    std::string work_pos = emp_ID.substr(13,3) ;

    if(work_pos == "EXE")
    {
        cout <<"\t\t\t An Executive is being added" <<endl ;
        perks = 0;
        Medical = 1 ;
        PPF = 1 ;
    }
    else 
    {   if(work_pos == "MAN")
        {
            cout <<"\t\t\t A Manager is being added" <<endl ;
            perks = 1;
            Medical = 1 ;
            PPF = 1 ;
        }
        else 
        {   if(work_pos == "PRE")
            {
                cout <<"\t\t\t A President is being addded" <<endl ;
                perks = 1;
                Medical = 1 ;
                PPF = 0 ;
            }
            else
            {
                cout <<"\t\t\t A Worker is being added" <<endl ;
                perks = 0;
                Medical = 1 ;
                PPF = 1 ;
            }
        }
    }

}

//to display 1 employee, is overloaded
void employee::display(int n)             
{
    std::string id ;
    cin.ignore(); 
    cout<<"\n Type your employee ID: " <<endl ; 
    getline(cin,id) ;
    cout << "typed ID:" <<id <<endl ;
    id = id + ".txt" ;
    cout << "path:" <<id <<endl ;
    read(id) ;
}

//to display all employees
void employee::display()        
{
    std::string p = "EMP/" ;
    std::string dep[] = {"CSE/", "ECE/"} ;
    std::string yr[] = {"2018", "2019", "2020", "2021"} ;
    std::string pos[] = {"EXE/", "MAN/","PRE/", "WOR/"} ;
    std::string dep1 = "CSE/" ;
    std::string dep2 = "ECE/" ;
    std::string pos1 = "EXE/" ;
    std::string pos2 = "MAN/" ;
    std::string pos3 = "PRE/" ;
    std::string pos4 = "WOR/" ;
   
   cout << dep[0] << ", " <<dep[1] <<endl ;
    for(int d=0; d<1; ++d )
    {
        for(int y=0; y<1; ++y)
        {
            for(int po=0; po<1; ++po)
            {
                for(int num=1; num<= 2; ++num)
                {
                    cout << "num:"<< num << endl ;
                    p = "EMP/" ;
                    p = p + dep[d] ;
                    p = p + yr[y] + "/" ;
                    p = p + pos[po] ;
                    p = p + "00" + to_string(num) ;          //to_string(num_of_employee_in_a_department)
                    p = p + ".txt" ;
                    cout << p << endl ;
                    cin.ignore() ;
                    read(p) ;
                }
            }
        }
    }
}

//read from a file and print all details, both for department and employee->> admin
void employee::read(std::string path)
{
    fstream emp;    
    std::string data ; 
    //path.resize(25) ;
    //id.resize(25) ;
    
    int flag=0,count=0;   //to choose admin/employee

    //cin.ignore(); 
    
    //cout << "\n Length of string:"<< id.length() << "\t path length:"<< path.length() <<endl ;
    cout << "\n path length:"<< path.length() <<endl ;
    //path = path + ".txt" ;
    //int f = exists_test(path) ;
    
    emp.open(path, ios::in|ios::out) ;

    if(!emp)   //error in opening file
    {
        cout << "\n\t\t\t No such file exists!!\n\t\t\t Type the employee ID correctly! \n\t\t\t Don't try to hack our systems\n" << endl ;
        cout<<"\n Exiting..." << endl ;
        //exit(0) ;
    }

    else        //if employee file found
    {
        //cin.flush() ;
        while(std::getline(emp, data , '\n'))
            {
                count+=1 ;
                cout<< "\ncount: " <<count << endl ;
                cout << data <<endl ;      
            }

        cout << "\n--------------------------DONE--------------------------\n" << endl ;
        emp.close() ;   
    }
    //return ;
}


// add a new employee
void add_member()
{
    //int c =0 ;
    cout << "\n\t\t\tADD A NEW EMPLOYEE\n" << endl ;
    cout << "\nTo add a new employee, enter all the details one by one. If no data exists, leave it blank there" << endl ;
    employee e ;
    e.set() ;    //values of object are taken input and set
    std::string empnum = e.emp_ID ;
    std::string emppath = e.emp_ID + ".txt" ;
    ofstream fi(emppath) ;
    // if file doesn't opens , error message
    if(!fi)
    {
        cout << "Error!! " << endl ;
    }
    else
    {
        //c+= 1;
        fi << e.emp_ID <<"\n";
        fi << e.emp_Name << "\n" ;
        fi << e.gender << "\n" ;
        fi << e.aadhar << "\n" ;
        fi << e.DOB_dd << "\n" ;
        fi << e.DOB_mm << "\n" ;
        fi << e.DOB_year << "\n" ;
        fi << e.DOJ_dd << "\n" ;
        fi << e.DOJ_mm << "\n" ;
        fi << e.DOJ_year << "\n" ;
        fi << e.active << "\n" ;
        fi << e.num_of_present_days << "\n" ;
        fi << e.num_of_leave << "\n" ;
        fi << e.date_of_leave << "\n" ;
        fi << e.perks << "\n" ;
        fi << e.Medical << "\n" ;
        fi << e.PPF << "\n";
        fi << e.salary << "\n" ;
        fi << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" ;

        cout << "\t\t\tEmployee added!  File created." << endl ;
        fi.close() ;
    }
    
}

int employee::dump()   //pth= employee id
{
    std::string pth = emp_ID + ".txt" ;
    cout << "dump file path:" << pth << endl ;
    fstream outf ;
            outf.open(pth, ios::out) ;
            //int count =0 , flag=0;
            //std::string epath = emp_ID + ".txt" ;


            if(!outf)
            {
                cout << "\n\t\t\t Error opening department file!" << endl ;
                return -1 ;
            }
            else
            {
                cout << "\n length of string: "<< pth.length() <<endl ;
                cout << "\n length of emp_ID: "<< emp_ID.length() << ", " << emp_ID <<endl ;
                cout << "\n length of emp_Name: "<< emp_Name.length()  << ","<< emp_Name << endl ;
                cout << "\n aadharr: "<< aadhar <<endl ;
                cout << "\n DOB_dd: " << DOB_dd << "\n" ;
                cout << "\n DOB_mm : "<< DOB_mm << "\n" ;
                cout << "\n DOB_year: "<< DOB_year << "\n" ;
                cout << "\n DOJ_dd: "<< DOJ_dd << "\n" ;
                cout << "\n DOJ_mm: "<< DOJ_mm << "\n" ;
                cout << "\n DOJ_year: "<< DOJ_year << "\n" ;
                cout << "\n active: "<< active << "\n" ;
                cout << "\n num_of_present_days: "<< num_of_present_days << "\n" ;
                cout << "\n num_of_leave: "<< num_of_leave << "\n" ;
                cout << "\n date_of_leave: "<< date_of_leave << "\n" ;
                cout << "\n perks: "<< perks << "\n" ;
                cout << "\n Medical: "<< Medical << "\n" ;
                cout << "\n PPF: "<< PPF << "\n" ;
                cout << "\n salary: "<< salary << "\n" ;  
                
                outf << emp_ID <<"\n";
                    outf << emp_Name << "\n" ;
                    outf << gender << "\n" ;
                    outf << aadhar << "\n" ;
                    outf << DOB_dd << "\n" ;
                    outf << DOB_mm << "\n" ;
                    outf << DOB_year << "\n" ;
                    outf << DOJ_dd << "\n" ;
                    outf << DOJ_mm << "\n" ;
                    outf << DOJ_year << "\n" ;
                    outf << active << "\n" ;
                    outf << num_of_present_days << "\n" ;
                    outf << num_of_leave << "\n" ;
                    outf << date_of_leave << "\n" ;
                    outf << perks << "\n" ;
                    outf << Medical << "\n" ;
                    outf << PPF << "\n" ;
                    outf << salary << "\n" ;  
                    outf << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" ;

                outf.close() ;
                return 1 ;
            }
                    
}

// function to write details to file
void employee::dump(int ln, string towrite="!")  //here l is line no. from the file eg. 3 for gender, 11 for active
{
    int count =0 , flag=0;
    std::string epath = emp_ID + ".txt" ;

    if(towrite != "!")
    {
        fstream del ;
        del.open(epath, ios::in|ios::out|ios::ate) ;
    
        if(!del)
        {
            cout << "\n\t\t\tERROR! opening file!\n\t\t\tContact IT department for help" << endl ;
        }
        else
        {
            cout << "\n length of string: "<< emp_ID.length() <<endl ;
            std::string rewrite ;
            del.seekg(0, ios::beg) ;

            count =0;
            while( std::getline(del, rewrite , '\n') && flag==0)
            {               
                count+=1 ;
                cout<< "\ncount: " <<count << endl ;
                cout << rewrite << endl ;
                
                if( count == ln)        //ID exists in the file
                {
                    flag =1 ;
                    cout << "\ntowrite:" << towrite << endl; 
                    std::string line  ;
                    
                    cout << "tellp:" << del.tellg() << endl ;
                    cout << "tellg:" << del.tellp() << endl ;
                    cout << "cur:" << ios::cur << endl ;
                    del.seekp(-(rewrite.length() + 2) , ios::cur) ;
                    //del.seekp(rewrite.length() + 2 , ios::cur) ;
                    cout << del.tellp() <<endl ;
                    cout << "eof:" << del.eof() << endl ;
                    del.seekp(ios::cur) ;
                    
                    //del.seekp(((count-1) * 43), ios::beg) ;
                    del << towrite ;
                    //del.seekg(((count-1) * 43)+27, ios::beg) ;
                    std::getline(del, line, '\n') ;
                    cout << "\nDumped at position:"<< count << ", line:" <<line << endl ;
                }
                else
                {
                    cout << "\nNot matched " <<endl ;
                }

                /*
                if(del.eof() && flag==0)
                {
                        //no such emp Id exists
                        cout << "\n\t\t\tError!!! No such employee exists.\n\t\t\tType the employe ID correctly! \n\t\t\tDon't try to hack our systems\n" <<endl ;
                        cout<<"\n Exiting..." << endl ;
                        //exit(0) ;
                        //or break ; 
                        del.close() ;
                }
                */   
            }
            del.close() ;
        }
        
    }

    else
    {
        cout << "\n\t\t\tError!!! can't dump this in file.\n\t\t\tYou're trying to coorrupt our files!" << endl ;
    }
    

}

//function to delete an employee
void delete_emp()
{
    int flag =0, diff=0, count=0 ; 
    std::string eid ;
    cout << "\nEnter the employee ID that has to be deleted:" << endl ;
    getline(cin, eid) ;
    cin.ignore(INT_MAX, '\n') ;

    employee empdel ;
    empdel.data_show(eid+".txt") ;
    empdel.active = 0;
    int ret = empdel.dump() ;
    //empdel.dump(11,"0") ;
    // dump the details in employee file

    if(ret == -1)
    {
        cout << "\n ERROR!! can't delete employee. Contact IT department" << endl ;
    }
    else
    {
        if(ret == 1)
        {
            fstream del("LOGIN/emp_login.txt", ios::in|ios::out|ios::ate) ;
    
            if(!del)
            {
                cout << "\n\t\t\tERROR Can't make employee's login account unusable\n\t\t\tContact IT department for help!" << endl  ;
            }
            else
            {
                cout << "\n In delete_emp, length of string: "<< eid.length() <<endl ;
                diff = LOGIN_SIZE - eid.length() ;
                if(eid.length() != LOGIN_SIZE )
                    {
                        for(int i=0; i<diff ; ++i)
                        {
                            eid.push_back('+') ;
                            cout<< eid <<endl;
                        }
                    }
                //login << "\n"<<  nm ;    //write empid to file
                ///see if nm is in file login??, if yes then only prompt for password otherwise error message
                std::string id ;
                del.seekg(0, ios::beg) ;

                count =0;

                //making employee's account unsuable, :. removing password
                while( std::getline(del, id , '\n') && flag==0)
                    {               
                        count+=1 ;
                        std::string line = id ;
                        id.resize(25) ; 
                        cout<< "\ncount: " <<count << endl ;
                        cout << id << endl ;
                
                        if( id == eid)        //ID exists in the file
                        {
                            flag =1 ;
                            cout << del.tellg() ;
                            std::string pass_orig = line.substr(25, 14) ;
                            cout << "\npassword orig:"<< pass_orig <<endl ;
                            cout << "pass_orig size:" << pass_orig.length() <<endl ; 
                            del.seekp(((count-1) * 43)+27, ios::beg) ;
                            pass_orig = "--------------" ;
                            del << pass_orig  ;    //writes password to file
                            del.seekg(((count-1) * 43)+27, ios::beg) ;
                            std::getline(del, line, '\n') ;
                            cout << "\nRemoved this employee's login account and made his/her account unsuable\n" <<line << endl ;
                        }
                        else
                        {
                            cout << "\nNot matched " <<endl ;
                        }

                    
                        if(count == num_of_employee && flag==0)
                        {
                                //no such emp Id exists
                                cout << "\n\t\t\tError!!! No such employee exists.\n\t\t\tType the employee ID correctly! \n\t\t\tDon't try to hack our systems\n" <<endl ;
                                cout<<"\n Exiting..." << endl ;
                                //exit(0) ;
                                //or break ; 
                                del.close() ;
                        }
                    
                    
                    }
                del.close() ;
            }
        }
    }
    
    
}

//read from a file and print all details, both for department ->> admin
void department::read(std::string path)
{
    fstream emp;    
    std::string data ; 
    //path.resize(25) ;
    //id.resize(25) ;
    
    int flag=0,count=0;   //to choose admin/employee

    //cin.ignore(); 
    
    //cout << "\n Length of string:"<< id.length() << "\t path length:"<< path.length() <<endl ;
    cout << "\n path length:"<< path.length() <<endl ;
    //path = path + ".txt" ;
    //int f = exists_test(path) ;
    
    emp.open(path, ios::in|ios::out) ;

    if(!emp)   //error in opening file
    {
        cout << "\n\t\t\t No such file exists!!\n\t\t\t Type the employee ID correctly! \n\t\t\t Don't try to hack our systems\n" << endl ;
        cout<<"\n Exiting..." << endl ;
        //exit(0) ;
    }

    else        //if employee file found
    {
        //cin.flush() ;
        while(std::getline(emp, data , '\n'))
            {
                count+=1 ;
                cout<< "\ncount: " <<count << endl ;
                cout << data <<endl ;      
            }

        cout << "\n--------------------------DONE--------------------------\n" << endl ;
        emp.close() ;   
    
    }
}
   

void department::display_dep() 
{
    std::string p = "DEP/" ;
    std::string dep[] = {"CSE", "ECE"} ;
    //dep->length of dep??

    cout << dep[0] << ", " <<dep[1] <<endl ;
    for(int d=0; d<=1; ++d )
    {
        cout << "\n d:"<<  d << endl ;
        p = "DEP/" ;
        p = p + dep[d] ;
        p = p + ".txt" ;
        cout << p << endl ;
        //cin.ignore() ;
        display_dep(p) ;
    }
}

//function to display department in format
void department::display_dep(std::string deppath)
{
    int ret = dep_file(deppath) ;
    if(ret ==1)
    {
        cout<< "\n**********************************************\n" <<endl ;
        cout<<"\t\t\tDEPARTMENT DETAILS"<<endl;
        cout<<"\nDepartment ID:"<< dep_ID <<"\nDepartment Name:"<<dep_Name <<"\nNo. of Members in Department:"<< dep_num_people <<endl;
        if(active==1)
        {
            cout << "\nDepartment is active" << endl ;
        }
        else
        {
            if(active==0)
            {
                cout << "\nDepartment is currently not active" << endl ;
            }
        }
        cout<< "\n**********************************************\n" <<endl ;
    }
    else 
    {
        if(ret==-1)
        {
        cout << "Can't display the contents of department file! Contact IT department for help." <<endl;
        }
    }
    
}

int department::dep_file(std::string dpath) 
{
    ifstream dept(dpath, ios::in);
    
    std::string data ; 
    //path.resize(25) ;
    
    int count=0;   //to choose admin/employee

    //cin.ignore(); 
    
    //cout << "\n Length of string:"<< id.length() << "\t path length:"<< path.length() <<endl ;
    cout << "\n path length:"<< dpath.length() << ", " << dpath <<endl ;
    //path = path + ".txt" ;
    

    if(!dept)   //error in opening file
    {
        cout << "\n\t\t\t No such department exists!!\n\t\t\t Type the department ID correctly! \n\t\t\t Don't try to hack our systems\n" << endl ;
        cout<<"\n Exiting..." << endl ;
        return -1 ;
    }

    else        //if employee file found
    {
        dep_ID = dpath.substr(0,7) ;

        //cin.flush() ;
            while(std::getline(dept, data , '\n'))
            {
                count+=1 ;
                cout<< "\ncount: " <<count << endl ;
                //read from employee file and store all values in objects
                if(count==1)
                {
                    dep_ID = data ;
                    cout << dep_ID <<endl ; 
                }
                else if(count==2)
                {
                    dep_Name = data ;
                    cout << dep_Name <<endl ; 
                }
                else if(count==3)
                {
                    dep_num_people = stoi(data);
                    cout << dep_num_people <<endl ; 
                }
                else if(count==4)
                {
                    active = stoi(data);
                    cout << active <<endl ; 
                }
                
                
            }

        cout << "\n--------------------------DONE--------------------------\n" << endl ;
        //cin.ignore() ;
        dept.close() ;   
        return 1 ;
    }
    
}

// add a new department
void add_dep()
{
    //int c =0 ;
    cout << "\n\t\t\tADD A NEW DEPARTMENT\n" << endl ;
    cout << "\nTo add a new Department, enter all the details one by one. If no data exists, leave it blank there" << endl ;
    department d ;
    d.set() ;    //values of object are taken input and set
    //std::string empnum = d.dep_ID ;
    std::string deppath = d.dep_ID + ".txt" ;
    ofstream fi(deppath) ;

    // if file doesn't opens , error message
    if(!fi)
    {
        cout << "\nERROR opening file!\nCan't create a new Department file!" << endl ;
    }
    else
    {
        //c+= 1;
        fi << d.dep_ID <<"\n";
        fi << d.dep_Name << "\n" ;
        fi << d.dep_num_people << "\n" ; 
        fi << d.active << "\n";
        fi << "~~~~~~~~~~~~~~~~~~~~~~" ;

        cout << "\t\t\t Department added! File created." << endl ;
        fi.close() ;
    }
    
}



//function to write department details to file
int department::dep_dump(int ln, std::string ddp, std::string towrite="!")   //id of dep
{
    ddp = ddp + ".txt" ;
    cout << "dump file path:" << ddp << endl ;
     //active = 0;
    //display_dep(ddp) ;
    
        
        if(towrite != "!")
        {
            fstream fd ;
            fd.open(ddp, ios::in|ios::ate|ios::out) ;
            int count =0 , flag=0;
            //std::string epath = emp_ID + ".txt" ;


            if(!fd)
            {
                cout << "\n\t\t\t Error opening department file!" << endl ;
                return -1 ;
            }
            else
            {
                cout << "\n length of string: "<< ddp.length() <<endl ;
                std::string rewrite ;
                fd.seekg(0, ios::beg) ;
                fd.seekp(0, ios::beg) ;

                count =0;
                while( std::getline(fd, rewrite , '\n') && flag==0)
                {               
                    count+=1 ;
                    cout<< "\ncount: " <<count << endl ;
                    cout << rewrite << endl ;
                    
                    if( count == ln)        //ID exists in the file
                    {
                        flag =1 ;
                        std::string line  ;
                        cout << fd.tellg()  <<endl ;
                        cout << fd.tellp() << endl ;
                        //fd.seekp(ios::cur) ;
                        fd.seekp(-(rewrite.length() + 2) , ios::cur) ;
                        cout << fd.tellp() <<endl ;
                        //del.seekp(((count-1) * 43), ios::beg) ;
                        fd << towrite ;
                        //del.seekg(((count-1) * 43)+27, ios::beg) ;
                        std::getline(fd, line, '\n') ;
                        cout << "\nDumped at position:"<< count << ", line:" <<line << endl ;
                    }
                    else
                    {
                        cout << "\nNot matched " <<endl ;
                    }

                        
                    if(fd.eof() && flag==0)
                        {
                            //no such emp Id exists
                            cout << "\n\t\t\tDumped!" <<endl ;
                            cout<<"\n\t\t\tExiting..." << endl ;
                            //exit(0) ;
                            //or break ; 
                            fd.close() ;
                        }
                        
                        
                }
                fd.close() ;
                return 1 ;
            }
            
            
        }

        else
        {
            cout << "\n\t\t\tError!!! can't dump this in file.\n\t\t\tYou're trying to corrupt our files!" << endl;
            return -1 ;
        }
    
}

//function to delete a department
void department::dep_del(std::string depid)
{
    active =0 ;
    cout << "file:" << depid << endl ;
    //int r= dep_dump(4, depid, "0") ;
    int r= dep_dump(depid, 0) ;
    if(r==1)
    {
        cout << "\n Changed the department active status to 0. Thus department is no longer active" << endl ;
    }
    else
    {
        if(r==-1)
        {
            cout << "\n ERROR" << endl;
        }
    }
    
}

////// admin menu
void admin_menu() 
{
    char yn = 'y' ;
    while(yn == 'y' || 'Y')
    {
        //all emp details, all dep details, add/delete, view 1 emp. 
    //graph
        int ch=0;
        cout<< "\n \t\t\tMain Admin Menu:\n " <<endl ;
        cout<< "1.) Show all employee details" <<endl ;
        cout<< "2.) View 1 employee details" <<endl ;
        cout<< "3.) Add an employee details" <<endl ;
        cout<< "4.) Delete employee details" <<endl ;
        cout<< "5.) View employee statistics" <<endl ;
        cout<< "6.) Show all department details" <<endl ;
        cout<< "7.) View 1  department details" <<endl ;
        cout<< "8.) Add a department details" <<endl ;
        cout<< "9.) Delete department details" <<endl ;
        cout<< "10.) View department statistics" <<endl ;
        cout<< "11.) Quit!! " <<endl ;

        cout<< "\n Enter your choice: "<< endl ;
        cin >>ch ;

        if(ch >= 1 && ch<= 11)
        {
          switch(ch) 
          {
            case 1:
                {
                    employee e;
                    e.display() ;
                    // employee file
                    break ;
                }
            
            case 2:
                {
                    //read values from file and store in data members using set()
                    employee e1 ;
                    e1.display(1);

                    // employee file
                    break ;
                }
            
            case 3:
                {
                    add_member() ;
                    // employee file
                    break ;
                }
            
            case 4:
                {
                    cout << "\n\t\t\tDelete an Employee\n\t\t\tSad He/SHE is leaving!" << endl ;
                    delete_emp() ;
                    // employee file
                break ;
                }

            case 5:
                {
                    recruit_stats() ;    
                    recruit_stats(0) ;
                    // employee file, gnuplot
                break ;
                }

            case 6:
                {
                    department dep ;
                    dep.display_dep() ;
                    // department file
                break ;
                }

            case 7:
                {
                    std::string did ;
                    department dep ;
                    cout << "\nEnter the department ID whose details you want to display:" ;
                    std::getline(cin, did) ;
                    dep.display_dep(did+".txt") ;
                    cin.ignore() ;
                    // department file
                break ;
                }

            case 8:
                {
                    add_dep();
                    // department file
                break ;
                }

            case 9:
                {
                    department d ;
                    std::string deptid ;
                    cin.ignore() ;
                    cout << "\nEnter the department ID that has to removed:" ;
                    std::getline(cin, deptid) ; 
                    cout << deptid << endl  ;
                    //cin.ignore() ;
                    d.dep_del(deptid) ;
                    // department file
                break ;
                }

            case 10:
                {
                    recruit_stats() ;    
                    recruit_stats(0) ;
                    // department file, gnuplot
                break ;
                }
            
            case 11:
                {
                    cout << "\n\t\t\t Quiting... " <<endl ;
                    exit(0) ;
                break ;
                }
          }
        }
        else 
        {
            cout<< "\n\t\t\tWrong choice !!!!\n\t\t\tExiting..." <<endl ;
        }
        
        cin.ignore() ;
        cout << "\n\t\t\t Want to continue? Press y or n" << endl ;
        cin >> yn ;

    }

    cout << "\n\n You choose 'n', Exiting..." <<endl ;
}


//customised employee menu function
void employee::emp_menu(std::string emppath) 
{
    //his/her personal det., attendance, no. of leaves, file a leave, salary, perks/benefits if any, PPF/medical insurance details 
    std::string empid = emppath.substr(0,20) ;
    cout<< "\n\t\t\t Welcome!! "<< empid <<endl ;    

    cout << "\t\t\t Your details are:" <<endl ;
    cout<< "\nName:"<< emp_Name  <<endl ;
    cout<< "Age:"<< 2021-DOB_year<<" years" << endl ;
    cout<< "Gender:"<< gender <<endl ;
    cout<< "Aadhar No.:"<< aadhar <<endl ;
    cout<< "DOB:"<< DOB_dd <<"-"<< DOB_mm <<"-"<< DOB_year << endl ;
    cout<< "DOJ:"<< DOJ_dd <<"-"<< DOJ_mm <<"-"<< DOJ_year << endl ;
    cout<< "Department:"<< empid.substr(4,3) <<endl ;
    cout<< "Salary:"<< salary <<endl ;
    cout<< "Position:"<< empid.substr(13,3) << endl ;
    cout<< "No. of leaves:"<< num_of_leave <<endl ;
    cout<< "Attendance per year:" << TOTAL_WORKING_DAYS-num_of_leave-num_of_present_days <<endl ;
    if(perks == 0)
    {
            cout<< "You don't get any Perks due to your position."<< endl ;
    }
    else
    {
        if(perks == 1)
        {
                cout<< "You get useful Perks based on your position."<< endl ;
        }
    }

    if(Medical == 0)
    {
            cout<< "You don't get any Medical due to your position."<< endl ;
    }
    else
    {
        if(Medical == 1)
        {
                cout<< "You get Medical benefits based on your position, like- LT or Health Insurance from company."<< endl ;
        }
    }

    if(PPF == 0)
    {
            cout<< "You don't have PPF or pension saved by company due to your position."<< endl ;
    }
    else
    {
        if(PPF == 1)
        {
                cout<< "You get PPF or pension saved by company, based on your position."<< endl ;
        }
    }    

    int choice =0;
    char yn = 'y' ;
    //ofstream outf(emppath, ios::out) ;

    while(yn == 'y' || yn == 'Y')
    {
        
        int ch=0;
        cout<< "\n \t\t\tMain EMPLOYEE Menu:\n " <<endl ;
        cout<< "1.) Update/Change some data ?" <<endl ;
        cout<< "2.) File a leave ?" <<endl ;
        cout<< "3.) File a complaint ?" <<endl ;
        cout<< "4.) Log Out" <<endl ;

        //cin.ignore() ;
        cout<< "\n Enter your choice: "<< endl ;
        cin >>ch ;
        cin.ignore(INT_MAX, '\n') ;

        if(ch >= 1 && ch<= 4)
      {
        switch(ch) 
        {
            case 1:
                {
                    cout << "\n What you want to update? Enter a valid choice" << endl;
                    cout << "1. Name" << "\n2. Gender" << "\n3. AADHAR No." << "\n4. DOB\nEnter your choice" << endl ; 
                    cin >> choice ;
                    switch (choice)
                    {
                    case 1:
                        {
                            cin.ignore() ;
                            cout << "\n Enter your new name:" << endl ;
                            std::getline(cin, emp_Name) ;
                            //dump(2, emp_Name) ;
                            dump() ;
                            cout << "Updated successfully!\nYour updated name:" << emp_Name << endl ;
                            break;
                        }
                    case 2:
                        {
                            cin.ignore() ;
                            cout << "\n Enter your correct gender:" << endl ;
                            cin >> gender ;
                            std::string g(1,gender) ;
                            //dump(3, g) ;
                            dump() ;
                            cout << "g:" << g << endl ;
                            cout << "Updated successfully!\nYour updated gender:" << gender << endl ;
                            break;
                        }
                    case 3:
                        {
                            cin.ignore() ;
                            cout << "\n Enter your correct Aadhar No. carefully:" << endl ;
                            std::getline(cin, aadhar) ;
                            //dump(4, aadhar) ;
                            dump() ;
                            cout << "Updated successfully!\nYour updated Aadhar No.:" << aadhar << endl ;
                            break;
                        }
                    case 4:
                        {
                            cin.ignore() ;
                            cout << "\n Enter your correct DOB" << endl ;
                            cout << "\n Enter your correct DOB day:" << endl ;
                            cin >> DOB_dd ;
                            cout << "\n Enter your correct DOB month:" << endl ;
                            cin >> DOB_mm ;
                            cout << "\n Enter your correct DOB year:" << endl ;
                            cin >> DOB_year ;
                            /*
                            std::ostringstream ss;
                            ss << DOB_dd ;
                            std::string s(ss.str());
                            cout << "s:" << s << endl ;
                            dump(5,s) ;

                            ss << DOB_mm ;
                            //s = ss.str();
                            cout << "s:" << s << endl ;
                            dump(6, s) ;

                            ss << DOB_year ;
                            //s = ss.str() ;
                            cout << "s:" << s << endl ;
                            dump(7, s) ;
                            */
                            dump() ;

                            cout << "Updated successfully!\nYour updated DOB:" << DOB_dd <<"-"<< DOB_mm <<"-"<< DOB_year << endl ;
                            break;
                        }
                    
                    default:
                        {
                            cout << "\n\t\t\tWrong choice!! Approach admin if you want to change other details." << endl ;
                            break;
                        }
                    }
                    
                    break ; //case 1 of main menu ends 
                }
            
            case 2:
                {
                    if(num_of_leave < 5)
                    {
                        std::string leave ;
                        cout << "\nEnter the leave date, number of days, and reason in format->> 01-01-2021(num_of_days/reason code), num_of_days has to be as 02 not only 2\n******** Num_of_days has to be < 5 **********" << endl ;
                        cout<<"Available reason codes are:" << "\n\t\t1-Sick\n\t\t2-personal\n\t\t3-attending an event" << endl ;
                        
                        cout << "Enter your leave request in given format:" <<endl ;
                        //cin.clear() ;
                        //cin.ignore(INT_MAX, '\n') ;
                        getline(cin, leave) ;
                        try            //if user by mistake types data as 112021 or any other character by istake, exceptn. caught
                        {       //int old_length = date_of_leave.length() ;
                            
                                int res= stoi(leave.substr(10,2)) ;
                                num_of_leave = num_of_leave + res ;
                                cout << "\n\t  Filed your leave! for "<< leave.substr(11,2) <<" days, starting from "<< leave.substr(0,10) << "\n\t  You gave reason:" << leave.substr(13,1)<<  endl ;
                                date_of_leave = date_of_leave + "|" + leave ;
                                dump() ;
                            
                            
                        }
                        catch(...)
                        {
                            cout << "\n You did not file the leave in the correct specified format!!!"<< '\n';
                        }
                        /*
                        try
                        {
                            throw(stoi(leave.substr(11,2))) ;
                        }
                        catch(const std::invalid_argument &)
                        {
                            cout << '\n';
                        }
                        */

                        
                    }
                    else {
                        if(num_of_leave > 5)
                        {
                            cout << "\nYou can only have maximum" << MAX_NUM_LEAVE <<" leaves in a year" << endl ;
                        }
                        else 
                        {
                            cout << "\nYou can only have maximum " << MAX_NUM_LEAVE << " leaves in a year. Your salary will be deducted if no valid reason is given!" << endl ;
                        }
                    }
                break ;
                }
            
            case 3:
                {
                    
                    // employee file a complaint
                break ;
                }
            
            case 4:
                {
                    // employee file
                    cout << "\n\t\t\t Logging out... " << endl ;
                    //outf.close();
                    exit(0) ;
                break ;
                }

        }

    }
    else 
    {
        cout<< "\n\t\t\tWrong choice !!!!\n\t\t\tExiting..." <<endl ;
    }

    cout << "\n\t\t\t Want to continue? Press y or n" << endl ;
    cin >> yn ;
    if(yn == 'n' || yn =='N')
    {
        cout << "\n\n You choose 'n', Exiting..." <<endl ;
        //outf.close();
        exit(0) ;
    }
    }

}



//driver code with login first
int main()
{   
    fstream login;

    //char nm[LOGIN_SIZE]= " "; 
    char pass_orig[PASS_SIZE] = " "; 
    char pass_in[PASS_SIZE] = " ";
    //char id[LOGIN_SIZE] = " " ;
    std::string id, nm  ;
    int ae =0, v=0, flag=0,count=0, diff=0 ;   //to choose admin/employee

    char choice='y' ;
    cout << "\n\t\t\t Welcome to DKAM LTD. portal" <<endl ;
    
    //cout << "\n is_file: " << boolalpha <<  filesystem::is_empty("F:/learnin_resources/sem5/OOPS/OOP project/DK_AM_oops_proj") <<endl;

    while(choice == 'y' || choice == 'Y')
    {
        cout << "\n\t\t\t Welcome to DKAM LTD. portal" <<endl ;
        cout<<"\n Are you an:\n\t\t(1) employee\n\t\t(2) an admin\n Type 1 or 2" <<endl ;
        cin >> ae ;
        if(ae ==1)            //an employee
        {
            login.open("LOGIN/emp_login.txt", ios::in|ios::app) ;
            login.seekg(0, ios::beg) ;
            cout<<"\n Hello Employee!, Type in your password and employee ID when prompted"<<endl ;
            cin.ignore(); 
            cout<<"\n Type your employee ID: " <<endl ; 
            getline(cin,nm) ;
            cout << "\n length of string: "<< nm.length() <<endl ;
            diff = LOGIN_SIZE - nm.length() ;
            if(nm.length() != LOGIN_SIZE )
            {
                for(int i=0; i<diff ; ++i)
                {
                    nm.push_back('+') ;
                    cout<<nm <<endl;
                }
            }
            //login << "\n"<<  nm ;    //write empid to file
            ///see if nm is in file login??, if yes then only prompt for password otherwise error message

            cout << "\n id: "<<id <<endl ;
        
            while(std::getline(login,id , '\n') && flag==0)
                {               
                    count+=1 ;
                    id.resize(25) ; 
                    cout<< "\ncount: " <<count<< "tellg():"<< login.tellg() << ", tellp:" << login.tellp() << endl ;
                    cout << id << endl ;
                
                    if( id == nm)        //ID exists in the file
                    {
                        flag =1;
                        cout << "\n\n\t\t\t Welcome!! "<< nm <<endl ;
                        //cin.ignore();               //don't use this, like a bug 
                        cout<< "\n Enter the password:"<<endl  ;
                        cin.getline(pass_in, PASS_SIZE) ;
                        std::string pin = pass_in ;
                        //pin.resize(9) ; 
                        //login <<"  "<<  pass  ;    //writes password to file

                        cout << "pin size earlier:" << pin.length() <<endl ;
                        diff = PASS_SIZE - pin.length() ;
                        if(pin.length() != PASS_SIZE )
                        {
                            for(int i=1; i<diff ; ++i)
                            {
                                pin.push_back('+') ;
                                cout<< pin <<endl;
                            }
                        }

                        login.seekg(((count-1) * 43)+27, ios::beg) ;
                        cout << login.tellg() ;

                        login.getline(pass_orig, PASS_SIZE) ;
                        std::string porig = pass_orig ;
                        porig.resize(14) ; 
                        cout << "\n\npassword in:"<< pass_in<< ",/////"<< pin <<endl ;
                        cout << "\n\npassword orig:"<< pass_orig << ",/////"<< porig <<endl ;
                        cout << "pass_in size:" << strlen(pass_in)<<",/////"<< pin.length() <<endl ;
                        cout << "pass_orig size:" << strlen(pass_orig)<<",/////" << porig.length() <<endl ; 

                        if(pin == porig)
                        {
                            cout << "Correct password!!" <<endl; 
                            employee e ;
                            std::string pathid = nm.substr(0,20) ;
                            pathid = pathid + ".txt" ;
                            cout << "pathid:" <<pathid <<endl; 
                            e.work_position(pathid) ; 
                            //login.close() ; at the end
                        }
                        else
                        {
                            cout<< "\t\t\tWrong password!!\n\t\t\tEnter a correct password !\n " <<endl;
                            cout << "\t\t\tStarting again!\n" <<endl;
                            
                        }
                    
                    }
                    else
                    {
                        cout << "Not matched " <<endl ;
                    }

                    
                    if(count == num_of_employee && flag==0)
                    {
                        //no such emp Id exists
                        cout << "\n\t\t\tError!!! No such employee exists.\n\t\t\tType the employe ID correctly! \n\t\t\tDon't try to hack our systems\n" <<endl ;
                        cout<<"\n Exiting..." << endl ;
                        //exit(0) ;
                        //or break ; 
                        login.close() ;
                    }
                    
                    
                }
            login.close() ;
        }

    else       //an admin
        {
            if(ae==2)
            {
                login.open("LOGIN/admin.txt", ios::in|ios::app) ;
                cout<<"\n Hello Admin !!, Type in your password and employee ID when prompted"<<endl ;
                cin.ignore(INT_MAX, '\n'); 
                cout<<"\n Type employee ID: " <<endl ; 
                getline(cin,nm) ;
                //cin.ignore(INT_MAX, '\n'); 
                cout << "\n length of employee ID: "<< nm.length() <<endl ;
                diff = LOGIN_SIZE - nm.length() ;
                if(nm.length() != LOGIN_SIZE )
                {
                    for(int i=0; i<diff ; ++i)
                    {
                        nm.push_back('+') ;
                        cout<<nm <<endl;
                    }
                }
                //login << "\n"<<  nm ;    //write empid to file

                login.seekg(0, ios::beg) ;
                while(std::getline(login,id , '\n') && flag==0)
                    {
                        
                        //std::istringstream iss(id);
                        count+=1 ;
                        id.resize(25) ; 
                        cout<< "\ncount: " <<count << endl ;
                        cout << id << endl ;
                        //login.getline(id, LOGIN_SIZE) ;
                    
                        //v = strcmp(id, nm) ;
                        //v = id.compare(nm) ;
                        //cout << "\n v: " <<v <<endl ;
                        if( id == nm)        //ID exists in the file
                        {
                            flag =1;
                            cout << "\n\n\t\t\t Welcome!! "<< nm <<endl ;
                            //cin.ignore();               //don't use this, like a bug 
                            cout<< "\n Enter the admin acount password:"<<endl  ;
                            cin.getline(pass_in, PASS_SIZE) ;
                            std::string pin = pass_in ;
                            //pin.resize(9) ; 
                            //login <<"  "<<  pass  ;    //writes password to file

                            cout << "pin size earlier:" << pin.length() <<endl ;
                            diff = PASS_SIZE - pin.length() ;
                            if(pin.length() != PASS_SIZE )
                            {
                                for(int i=1; i<diff ; ++i)
                                {
                                    pin.push_back('+') ;
                                    cout<< pin <<endl;
                                }
                            }

                            login.seekg(((count-1) * 43)+27, ios::beg) ;
                            cout << login.tellg() ;

                            login.getline(pass_orig, PASS_SIZE) ;
                            std::string porig = pass_orig ;
                            porig.resize(14) ; 
                            cout << "\n\npassword in:"<< pass_in<< ",/////"<< pin <<endl ;
                            cout << "password orig:"<< pass_orig << ",/////"<< porig <<endl ;
                            cout << "\n\npass_in size:" << strlen(pass_in)<<",/////"<< pin.length() <<endl ;
                            cout << "pass_orig size:" << strlen(pass_orig)<<",/////" << porig.length() <<endl ; 

                            if(pin == porig)
                            {
                                cout << "Correct password!!" <<endl; 
                                admin_menu() ; 
                                //login.close() ; at the end
                            }
                            else
                            {
                                cout<< "\t\t\tWrong password!!\n\t\t\tEnter a correct password !\n " <<endl;
                                cout << "\t\t\tStarting again!\n" <<endl;
                                login.close() ;
                            }
                            

                            
                        
                        }
                        else
                        {
                            cout << "Not matched " <<endl ;
                            //login.close() ;                    
                        }

                    
                        if(count == num_of_employee && flag==0)
                        {
                            //no such emp Id exists
                            cout << "\n\t\t\tError!!! No such employee exists.\n\t\t\tType the employee ID correctly! \n\t\t\tDon't try to hack our systems\n" <<endl ;
                            cout<<"\n Exiting..." << endl ;
                            //exit(0) ;
                            //or break ; 
                            login.close() ;
                        }
                
                    }
            }

            else
            {
                cout << "\n\t\t\tWrong choice!!!\n\t\t\tPlease only choose the correct option.\n\t\t\tStart the program again" << endl ;
            }
        
        }


        cin.ignore(INT_MAX,'\n') ;
        cout << "\nWant to continue? Press y or n" << endl ;
        cin >> choice ;
        if(choice =='n' || choice =='N')
        {
            cout << "\n\n\t\t\tExiting..." << endl ;
        }
        else
        {
            if(choice=='y' || choice=='Y')
            {
                cout << "\nContinuing and starting again>>>>>" << "\n****************************************************" << endl ;
            }
            else
            {
                cout << "\n\n\t\t\tYou did not type y or n. Exiting..." << endl ;
                //exit(0) ;
            }
            
        }
    
    }
    

return 0;
    
}
