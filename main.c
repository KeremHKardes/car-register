#include <stdio.h>
#include <string.h>

// structure to represent a date
typedef struct {
    int day;
    int month;
    int year;
} date_t;

// structure to represent a car
typedef struct {
    char brand[50];
    char model[50];
    date_t manufacture_date;
    char serial_number[11];
    double gas_tank_capacity;
} auto_t;

// function to get user input for a string (with validation for brand/model)
int get_string(char *str, int max_len) {
    fgets(str, max_len, stdin);
    str[strcspn(str, "\n")] = '\0'; // Remove trailing newline

    // validate brand/model input (at least one non-space character)
    if (strlen(str) == 0 || strspn(str, " ") == strlen(str)) {
        printf("Invalid input (must contain at least one non-space character).\n");
        return 0; // indicates error
    }
    return 1; // indicates success
}

// function to get user input for date (with validation)
int get_date(date_t *date) {
    if (scanf("%d-%d-%d", &date->day, &date->month, &date->year) != 3) {
        printf("Invalid date format.\n");
        return 0; // indicates error
    }

    // validate date (month 1-12, day 1-31 based on month/year)
    if (date->month < 1 || date->month > 12 ||
        date->day < 1 || date->day > 31 ||
        (date->month == 4 || date->month == 6 || date->month == 9 || date->month == 11) && date->day > 30 ||
        (date->month == 2 && ((date->year % 4 == 0 && date->year % 100 != 0) || date->year % 400 == 0) && date->day > 29) ||
        (date->month == 2 && date->year % 4 != 0 && date->day > 28)) {
        printf("Invalid date (out of range).\n");
        return 0; // indicates error
    }
    return 1; // indicates success
}

// function to get user input for serial number (with validation)
int get_serial_number(char *serial_number) {
    if (scanf("%10s", serial_number) != 1 || strlen(serial_number) != 10) {
        printf("Invalid serial number format (must be 10 digits).\n");
        return 0; // indicates error
    }
    return 1; // indicates success
}

// function to get user input for gas tank capacity (with validation)
int get_gas_tank_capacity(double *capacity) {
    if (scanf("%lf", capacity) != 1) {
        printf("Invalid gas tank capacity format (must be a number).\n");
        return 0; // indicates error
    }
    return 1; // indicates success
}

int main() {
    auto_t cars[100]; // array to store car data (adjust size if needed)
    int num_cars = 0;
    char continue_prompt;

    do {
        printf("\nPlease enter the brand and model of the car (separated by a space):\n");
        printf("Enter: ");

        fflush(stdin); // clear any leftover characters in the input buffer

        if (!get_string(cars[num_cars].brand, sizeof(cars[num_cars].brand))) {
            continue; // skips to continue prompt if input is invalid
        }

        // separate brand and model using strtok
        char *model = strtok(cars[num_cars].brand, " ");
        if (model == NULL) {
            printf("Invalid input (must contain both brand and model separated by a space).\n");
            continue; // skips to continue prompt if input is invalid
        }

        // copy model to its designated field
        strcpy(cars[num_cars].model, model);

        printf("Please enter the manufacture date (day-month-year):\n");
        printf("Enter: ");
        if (!get_date(&cars[num_cars].manufacture_date)) {
            continue; // skips to continue prompt if input is invalid
        }

        printf("Please enter the serial number (10 digits):\n");
        printf("Enter: ");
        if (!get_serial_number(cars[num_cars].serial_number)) {
            continue; // skips to continue prompt if input is invalid
        }

        printf("Please enter the gas tank capacity:\n");
        printf("Enter: ");
        if (!get_gas_tank_capacity(&cars[num_cars].gas_tank_capacity)) {
            continue; // skips to continue prompt if input is invalid
        }

        // continue prompt and increment car count
        printf("Do you want to continue (Y/N)? ");
        scanf(" %c", &continue_prompt);
        num_cars++;
    } while (continue_prompt == 'Y' || continue_prompt == 'y');

    FILE *fp = fopen("Cars.txt", "w");
    if (fp == NULL) {
        printf("Error creating file.\n");
        return 1;
    }

    // write car data to the file line by line (as mentioned struction in the assignment)
    for (int i = 0; i < num_cars; i++) {
        fprintf(fp, "%s %s %d-%d-%d %s %.2lf\n",
                cars[i].brand, cars[i].model,
                cars[i].manufacture_date.day, cars[i].manufacture_date.month, cars[i].manufacture_date.year,
                cars[i].serial_number, cars[i].gas_tank_capacity);
    }

    fclose(fp); // close the file before end

    printf("Car data written to Cars.txt successfully.\n");

    return 0;
}
