#include <fstream>
#include <iostream>
using namespace std;

enum position { MANAGER, ENGINER, SALESPERSON, UNKNOWN_POS };

enum department { IT, HR, FINANCE, UNKNOWN_DEP };

enum salaryType { MONTHLY, HOURLY };

struct employee {
  string ID;
  string Name;
  position position;
  department department;
  double salary;
  salaryType salaryType;
};

int displayOptions();
void addEmployee(employee[], int &);
void displayEmployeeByID(employee[], int);
void updateEmploye(employee[], int);
void deleteEmploye(employee[], int &);
void getTotalSalary(employee[], int);
void listEmployeesInDepartment(employee[], int);
void listEmployeesWithPosition(employee[], int);
void display(employee);
position getPositionFromString(string);
department getDepartmentFromString(string);
string getDepartmentName(department);
string getPositionName(position);
string getSalaryTypeName(salaryType);

int main() {
  employee employees[100];
  int counter = 0;
  int input;
  while (input != 8) {
    input = displayOptions();
    switch (input) {
      case 1:
        addEmployee(employees, counter);
        break;
      case 2:
        displayEmployeeByID(employees, counter);
        break;
      case 3:
        updateEmploye(employees, counter);
        break;
      case 4:
        deleteEmploye(employees, counter);
        break;
      case 5:
        getTotalSalary(employees, counter);
        break;
      case 6:
        listEmployeesInDepartment(employees, counter);
        break;
      case 7:
        listEmployeesWithPosition(employees, counter);
        break;
      case 8:
        return 0;
      default:
        cerr << "Please enter only numbers between 1 and 8." << endl;
        break;
    }
  }
}

int displayOptions() {
  int userOption;
  cout << "enter 1 to Add a new employee " << endl;
  cout << "enter 2 to Display the details of a specific employee with ID."
       << endl;
  cout << "enter 3 to update an employees database." << endl;
  cout << "enter 4 to delete an employees database." << endl;
  cout << "enter 5 to Calculate the total salary expense of the company"
       << endl;
  cout << "enter 6 to Display the list of employees in a specific department."
       << endl;
  cout << "enter 7 to Display the list of employees with a specific position."
       << endl;
  cout << "enter 8 to exit" << endl;
  cin >> userOption;
  return userOption;
}

void addEmployee(employee employees[], int &counter) {
  cout << "enter the employee ID" << endl;
  cin >> employees[counter].ID;
  cout << "enter the employee name" << endl;
  cin >> employees[counter].Name;
  string inputDepartment;
  cout << "choose the employee department: [IT, HR, FINANCE]" << endl;
  cin >> inputDepartment;
  employees[counter].department = getDepartmentFromString(inputDepartment);
  string inputPosition;
  cout << "choose the employee position: [MANAGER, ENGINER, SALESPERSON] "
       << endl;
  cin >> inputPosition;
  employees[counter].position = getPositionFromString(inputPosition);

  int salaryType = 0;
  cout << "choose the employe salary" << endl;
  cout << "enter 1 for monthly " << endl;
  cout << "enter 2 for hourly " << endl;
  cin >> salaryType;
  switch (salaryType) {
    case 1:
      cout << "Enter monthly salary: " << endl;
      cin >> employees[counter].salary;
      employees[counter].salaryType = salaryType::MONTHLY;
      break;
    case 2:
      cout << "Enter hourly salary" << endl;
      cin >> employees[counter].salary;
      employees[counter].salaryType = salaryType::HOURLY;
      break;
    default:
      cerr << "Please select 1 or 2 for salary type" << endl;
      break;
  }
  counter++;
}

void displayEmployeeByID(employee employees[], int counter) {
  string ID;
  cout << "enter the employee ID" << endl;
  cin >> ID;
  bool isEmployeeFound = false;
  for (int i = 0; i < counter; i++) {
    if (ID == employees[i].ID) {
      display(employees[i]);
      isEmployeeFound = true;
      break;
    }
  }
  if (!isEmployeeFound) {
    cerr << "Employee with ID: " << ID << " is not found!" << endl;
    return;
  }
}

void display(employee employee) {
  cout << "employe Name           : " << employee.Name << endl;
  cout << "employe ID             : " << employee.ID << endl;
  cout << "employe department     : " << getDepartmentName(employee.department)
       << endl;
  cout << "employe position       : " << getPositionName(employee.position)
       << endl;
  cout << "employe salary         : " << employee.salary << endl;
  cout << "employe salary type    : " << getSalaryTypeName(employee.salaryType)
       << endl;
  cout << "-----------------------------------------" << endl;
}

void updateEmploye(employee employees[], int counter) {
  string ID;
  cout << "Enter employe ID to update" << endl;
  cin >> ID;

  bool isEmployeeFound = false;
  employee *empToupdate;
  for (int i = 0; i <= counter; i++) {
    if (ID == employees[i].ID) {
      display(employees[i]);
      isEmployeeFound = true;
      empToupdate = &employees[i];
      break;
    }
  }
  if (!isEmployeeFound) {
    cerr << "Employee with ID: " << ID << " is not found!" << endl;
    return;
  }

  int userInput;
  cout << "choose what you want to update" << endl;
  cout << "enter 1 for Department" << endl;
  cout << "enter 2 for Position " << endl;
  cout << "enter 3 for Salary " << endl;
  cin >> userInput;
  switch (userInput) {
    case 1: {
      string inputDep;
      cout << "Choose which department you are updating to [IT, HR, FINANCE] "
           << endl;
      cin >> inputDep;
      empToupdate->department = getDepartmentFromString(inputDep);
      break;
    }
    case 2: {
      string inputPosition;
      cout << "Choose the employee position you are updating to [MANAGER, "
              "ENGINER, SALESPERSON] "
           << endl;
      cin >> inputPosition;
      empToupdate->position = getPositionFromString(inputPosition);
      break;
    }
    case 3: {
      if (empToupdate->salaryType == salaryType::MONTHLY) {
        cout << "enter the monthly salary you want to update to" << endl;
        cin >> empToupdate->salary;
      } else if (empToupdate->salaryType == salaryType::HOURLY) {
        cout << "enter hourly salary you want to update to" << endl;
        cin >> empToupdate->salary;
      }
      break;
    }
    default:
      cerr << "You entered a wrong input. Please enter 1, 2, or 3 to choose "
              "update type."
           << endl;
      break;
  }
}

void deleteEmploye(employee employees[], int &counter) {
  string ID;
  char confirmation;
  cout << "enter the employe ID you want to delete" << endl;
  cin >> ID;
  bool isEmployeeFound = false;
  int employeeIndexToDelete;
  for (int i = 0; i <= counter; i++) {
    if (ID == employees[i].ID) {
      display(employees[i]);
      employeeIndexToDelete = i;
      isEmployeeFound = true;
      break;
    }
  }
  if (!isEmployeeFound) {
    cerr << "No Employee with ID: " << ID << " is found!" << endl;
    return;
  }

  cout << "Make sure you want to delete the employe enter Y for yes, any other "
          "character for no "
       << endl;
  cin >> confirmation;
  if (confirmation != 'Y' && confirmation != 'y') {
    return;
  }

  // if the employee is the last in the list.
  if (employeeIndexToDelete == counter - 1) {
    counter--;
  } else {
    // overwrite the index where employee should be deleted,
    // and adjust the other indexes.
    for (int j = employeeIndexToDelete; j <= counter; j++) {
      employees[j] = employees[j + 1];
    }
  }
}

void getTotalSalary(employee employees[], int counter) {
  int totalMonthlySalary = 0;
  int totalHourlySalary = 0;
  for (int i = 0; i <= counter; i++) {
    if (employees[i].salaryType == salaryType::MONTHLY) {
      totalMonthlySalary = totalMonthlySalary + employees[i].salary;
    } else if (employees[i].salaryType == salaryType::HOURLY) {
      totalHourlySalary = totalHourlySalary + employees[i].salary;
    }
  }
  cout << "The total salary paid for monthly workers is: " << totalMonthlySalary
       << endl;
  cout << "The total salary paid for hourly workers is: " << totalHourlySalary
       << endl;
}

void listEmployeesWithPosition(employee employees[], int counter) {
  string posInput;
  cout << "enter the position: MANAGER , ENGINER , SALESPERSON" << endl;
  cin >> posInput;
  position position = getPositionFromString(posInput);
  for (int i = 0; i < counter; i++) {
    if (position == employees[i].position) {
      display(employees[i]);
    }
  }
}

void listEmployeesInDepartment(employee employees[], int counter) {
  string depInput;
  cout << "enter the department: IT , HR , FINANCE" << endl;
  cin >> depInput;
  department department = getDepartmentFromString(depInput);

  for (int i = 0; i < counter; i++) {
    if (department == employees[i].department) {
      display(employees[i]);
    }
  }
}

position getPositionFromString(string position) {
  if (position == "MANAGER") {
    return position::MANAGER;
  } else if (position == "ENGINER") {
    return position::ENGINER;
  } else if (position == "SALESPERSON") {
    return position::SALESPERSON;
  } else {
    return position::UNKNOWN_POS;
  }
}
department getDepartmentFromString(string department) {
  if (department == "IT") {
    return department::IT;
  } else if (department == "HR") {
    return department::HR;
  } else if (department == "FINANCE") {
    return department::FINANCE;
  } else {
    return department::UNKNOWN_DEP;
  }
}
department getDepartmentName(int index) {
  if (index == 0) {
    return department::IT;
  } else if (index == 1) {
    return department::HR;
  } else if (index == 2) {
    return department::FINANCE;
  }
}

string getPositionName(position position) {
  switch (position) {
    case MANAGER:
      return "Manager";
    case ENGINER:
      return "Enginer";
    case SALESPERSON:
      return "Sales Person";
  }
  return "Unknown";
}

string getDepartmentName(department department) {
  switch (department) {
    case IT:
      return "IT";
    case HR:
      return "HR";
    case FINANCE:
      return "Finance";
  }
  return "Unknown";
}
string getSalaryTypeName(salaryType salaryType) {
  switch (salaryType) {
    case salaryType::MONTHLY:
      return "Monthly";
      break;
    case salaryType::HOURLY:
      return "Hourly";
      break;

    default:
      break;
  }
}