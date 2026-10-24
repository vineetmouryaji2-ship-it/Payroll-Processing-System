
#include <stdio.h>
#include <string.h>

#define MAX_EMPLOYEES 100

struct Employee
{
    int id;
    char name[50];
    float basicSalary;
    float allowance;
    float pf;
    float otherDeduction;
};

struct Employee employees[MAX_EMPLOYEES];
int count = 0;

void addEmployee()
{
    if (count >= MAX_EMPLOYEES)
    {
        printf("\nEmployee limit reached!\n");
        return;
    }

    struct Employee e;

    printf("\n===== Add Employee =====\n");

    printf("Enter Employee ID: ");
    if (scanf("%d", &e.id) != 1)
    {
        printf("Invalid ID!\n");
        while (getchar() != '\n')
            ;
        return;
    }

    // Check for duplicate employee ID
    for (int i = 0; i < count; i++)
    {
        if (employees[i].id == e.id)
        {
            printf("This Employee ID already exists!\n");
            return;
        }
    }

    printf("Enter Employee Name: ");
    scanf(" %49[^\n]", e.name);

    printf("Enter Basic Salary: ");
    if (scanf("%f", &e.basicSalary) != 1 ||
        e.basicSalary < 0)
    {
        printf("Invalid salary!\n");
        while (getchar() != '\n')
            ;
        return;
    }

    printf("Enter Allowances: ");
    if (scanf("%f", &e.allowance) != 1 ||
        e.allowance < 0)
    {
        printf("Invalid allowance!\n");
        while (getchar() != '\n')
            ;
        return;
    }

    printf("Enter PF Deduction: ");
    if (scanf("%f", &e.pf) != 1 || e.pf < 0)
    {
        printf("Invalid PF amount!\n");
        while (getchar() != '\n')
            ;
        return;
    }

    printf("Enter Other Deductions: ");
    if (scanf("%f", &e.otherDeduction) != 1 ||
        e.otherDeduction < 0)
    {
        printf("Invalid deduction!\n");
        while (getchar() != '\n')
            ;
        return;
    }

    if (e.pf + e.otherDeduction >
        e.basicSalary + e.allowance)
    {
        printf("Error: Deductions cannot exceed gross salary.\n");
        return;
    }

    employees[count] = e;
    count++;

    printf("\nEmployee added successfully!\n");
}

void viewPayroll()
{
    if (count == 0)
    {
        printf("\nNo employee records found!\n");
        return;
    }

    printf("\n================ PAYROLL REPORT ================\n");

    printf("%-6s %-20s %12s %12s %12s\n",
           "ID", "Name", "Basic", "Allowance", "Net Salary");

    printf("---------------------------------------------------------------\n");

    float totalSalary = 0;

    for (int i = 0; i < count; i++)
    {
        float grossSalary =
            employees[i].basicSalary +
            employees[i].allowance;

        float deductions =
            employees[i].pf +
            employees[i].otherDeduction;

        float netSalary = grossSalary - deductions;

        printf("%-6d %-20.20s %12.2f %12.2f %12.2f\n",
               employees[i].id,
               employees[i].name,
               employees[i].basicSalary,
               employees[i].allowance,
               netSalary);

        totalSalary += netSalary;
    }

    printf("---------------------------------------------------------------\n");
    printf("Total Employees: %d\n", count);
    printf("Total Net Payroll: Rs. %.2f\n", totalSalary);
}

void searchEmployee()
{
    int id;
    printf("\nEnter Employee ID to search: ");

    if (scanf("%d", &id) != 1)
    {
        printf("Invalid ID!\n");
        while (getchar() != '\n')
            ;
        return;
    }

    for (int i = 0; i < count; i++)
    {
        if (employees[i].id == id)
        {
            float gross = employees[i].basicSalary +
                          employees[i].allowance;

            float deductions = employees[i].pf +
                               employees[i].otherDeduction;

            printf("\n===== Employee Details =====\n");
            printf("Employee ID: %d\n", employees[i].id);
            printf("Name: %s\n", employees[i].name);
            printf("Basic Salary: Rs. %.2f\n",
                   employees[i].basicSalary);
            printf("Allowances: Rs. %.2f\n",
                   employees[i].allowance);
            printf("Gross Salary: Rs. %.2f\n", gross);
            printf("PF Deduction: Rs. %.2f\n",
                   employees[i].pf);
            printf("Other Deductions: Rs. %.2f\n",
                   employees[i].otherDeduction);
            printf("Total Deductions: Rs. %.2f\n",
                   deductions);
            printf("Net Salary: Rs. %.2f\n",
                   gross - deductions);
            return;
        }
    }

    printf("Employee not found!\n");
}

int main()
{
    int choice;

    printf("====================================\n");
    printf("     PAYROLL PROCESSING SYSTEM\n");
    printf("====================================\n");

    do
    {
        printf("\n1. Add Employee\n");
        printf("2. View All Payroll Records\n");
        printf("3. Search Employee by ID\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("Please enter a valid menu number!\n");
            while (getchar() != '\n')
                ;
            continue;
        }

        switch (choice)
        {
        case 1:
            addEmployee();
            break;

        case 2:
            viewPayroll();
            break;

        case 3:
            searchEmployee();
            break;

        case 4:
            printf("\nThank you for using Payroll System!\n");
            break;

        default:
            printf("\nInvalid choice! Please try again.\n");
        }

    } while (choice != 4);

    return 0;
}
