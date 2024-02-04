#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

void input();
void deleteInfo();
void search();
void print();

struct info {
    char name[50];
    char fname[50];
    char cnic[54];
    int bill;
};

int main() {
    int choice;
    while (choice != 5) {
        printf("\nHOSPITAL MANAGEMENT SYSTEM\n");
        printf("Enter 1 for input, 2 for DELETE info, 3 for print info, 4 for search, 5 for exit\n");
        choice = getch();  // Use getch() to get the choice directly without pressing Enter

        switch (choice) {
            case '1':
                system("cls");  // Use system("cls") instead of clrscr()
                input();
                system("cls");
                break;
            case '2':
                system("cls");
                deleteInfo();
                system("cls");
                break;
            case '3':
                system("cls");
                print();
                printf("\t\t\tPress any key to exit\n");
                getch();
                system("cls");
                break;
            case '4':
                system("cls");
                search();
                system("cls");
                break;
            case '5':
                exit(0);
            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}

void input() {
    char another;
    FILE *fp;
    struct info record;  // Change variable name from info to record
    do {
        system("cls");
        printf("\twelcome to sbk management system\t");
        fp = fopen("INFO.TXT", "a");

        printf("ENTER NAME: ");
        scanf("%s", record.name);
        printf("ENTER FNAME: ");
        scanf("%s", record.fname);
        printf("ENTER CNIC: ");
        scanf("%s", record.cnic);
        printf("ENTER BILL: ");
        scanf("%d", &record.bill);

        printf("\n\t\t\t________________________\n");

        if (fp == NULL) {
            fprintf(stderr, "\t\t\tCANT OPEN FILE");
        } else {
            printf("\t\t\tRecord stored successfully\n");
        }

        fwrite(&record, sizeof(struct info), 1, fp);
        fclose(fp);

        printf("\t\t\tDO YOU WANT TO ADD ANOTHER? (y/n): ");
        scanf(" %c", &another);  // Add a space before %c to consume the newline character

    } while (another == 'y' || another == 'Y');
}

void print() {
    FILE *fp;
    struct info record;
    fp = fopen("INFO.txt", "r");

    printf("\twelcome to sbk management system\t");

    if (fp == NULL) {
        fprintf(stderr, "\t\t\tCANT OPEN FILE");
    } else {
        printf("\t\t\tSBK Record\n");
    }

    while (fread(&record, sizeof(struct info), 1, fp)) {
        printf("\n\t\t\t\t NAME: %s", record.name);
        printf("\n\t\t\t\t FNAME: %s", record.fname);
        printf("\n\t\t\t\t CNIC: %s", record.cnic);
        printf("\n\t\t\t\t BILL: %d$", record.bill);
    }

    fclose(fp);
    getch();
}

void search() {
    FILE *fp;
    struct info record;
    char cnic[54];
    int found = 0;
    fp = fopen("INFO.txt", "r");

    printf("\t\t\t===Search===\n");
    printf("\t\t\tEnter CNIC: ");
    scanf("%s", cnic);

    while (fread(&record, sizeof(struct info), 1, fp)) {
        if (strcmp(record.cnic, cnic) == 0) {
            found = 1;
            printf("\n\t\t\t\t NAME: %s", record.name);
            printf("\n\t\t\t\t FNAME: %s", record.fname);
            printf("\n\t\t\t\t CNIC: %s", record.cnic);
            printf("\n\t\t\t\t BILL: %d$", record.bill);
        }
    }

    if (!found) {
        printf("\t\t\tNot found\n");
    }

    fclose(fp);
    getch();
}

void deleteInfo() {
    FILE *fp, *fp1;
    struct info record;
    char cnic[54];
    int found = 0;

    fp = fopen("INFO.txt", "r");
    fp1 = fopen("temp.txt", "w");

    if (fp == NULL || fp1 == NULL) {
        fprintf(stderr, "\t\t\tCan't open file");
    }

    printf("\t\t\t===Search===\n");
    printf("\t\t\tEnter CNIC: ");
    scanf("%s", cnic);

    while (fread(&record, sizeof(struct info), 1, fp)) {
        if (strcmp(record.cnic, cnic) == 0) {
            found = 1;
        } else {
            fwrite(&record, sizeof(struct info), 1, fp1);
        }
    }

    fclose(fp);
    fclose(fp1);

    if (found) {
        remove("INFO.txt");
        rename("temp.txt", "INFO.txt");
        printf("\t\t\tRecord deleted\n");
    } else {
        printf("\t\t\tRecord not found\n");
    }
}