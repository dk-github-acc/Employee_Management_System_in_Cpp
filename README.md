# OOP-semester-project
Employee Record Management System using C++ and GNUplot

OOP project
Employee Management System

Requirements -
    -- IDE such as Visual Studio Code or Dev C/C++ or CodeBlocks etc. (preferred is Visual Studio code)
    -- gcc complier

The folders are - 
DEP, EMP, LOGIN, STATS

The source code is in file emp_man.cpp. Executable file can be created by comand: g++ emp_man.cpp -o emp_man
The commands for gnuplot can be found in gnuplot_command.txt file.

#The OOP concepts that were used in the project are -
    1. Objects and encapsulation -data members and member functions.
    2. Data Hiding - Private, Protected and Public access specifiers. Friend function.
    3. Inheritance - Classes.
    4. Polymorphism -Function overloading
    5. Abstraction - Abstraction
    6. Exception Handling - Try-throw-catch
    7. Default parameters
    8. Virtual functions

#FEATURES : 
1. Login system-For both admin and employee. In both the above files, the login ID is taken as Employee Id, but password is different to login into admin and employee’s portal. An admin himself/herself is an employee of the company too, so an admin gets two different passwords to login into admin and employee portal.
2. Separate portals for both employee and admin-Facilities like to view and update personal details, to file leave and complaints are provided on the customised portal for employees. The admin portal, on the other hand, can access the details of all the employees and thedepartments, and can visualize data using the GNUplot plotting feature provided in the admin portal.
3. Menu based interface.
4. CRUD (Create, Read, Update and Delete) operations-Basic CRUD operations can be performed on the details of employees and department, by the admin on the admin portal.
5. Updatingfacility for employees-The employee can update his/her personal details(but not those that have been provided/set by the company) on a customised portal.
6. Leave filing feature for an employee.
7. Data visualisation feature-GNUplot has been used to draw graphs and plotting features are provided in the admin portal. This can help the company to take serious decisions that can affect the company’s performance.
