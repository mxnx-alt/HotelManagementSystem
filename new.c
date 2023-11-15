#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Define data structures
typedef struct Guest {
    char name[50];
    int age;
    char phone[15];
    int food;
    int wifi;
    int roomType;
    int roomNumber;
    struct Guest* next;
} GUEST;

typedef struct hotel {
    GUEST* head;
} HOTEL;

// Function declarations
void menu(HOTEL* hotel);
void initializeRooms(HOTEL* hotel);
int login();
int displayAvailableRooms(HOTEL* hotel, int rt);
void guestFunc(HOTEL* hotel);
void amenities(HOTEL* hotel, int ro);
void removeGuest(HOTEL* hotel, int r, int rot);
void searchGuest(HOTEL* hotel, char nn[50]);
void generateInvoice(HOTEL* hotel, int room);
void checkRoom(HOTEL* hotel, int rm);
void makeReservation(HOTEL* hotel);
void addGuest(HOTEL* hotel);

// Function to initialize rooms with user-defined room type
void initializeRooms(HOTEL* hotel) {
    hotel->head = NULL;
    for (int i = 0; i < 50; i++) {
        GUEST* newGuest = (GUEST*)malloc(sizeof(GUEST));
        newGuest->roomNumber = i + 1;
        newGuest->age = -1;
        newGuest->wifi = 0;
        newGuest->food = 0;

        if (i < 20)
            newGuest->roomType = 1;
        else if (i >= 20 && i < 40)
            newGuest->roomType = 2;
        else
            newGuest->roomType = 3;

        newGuest->next = hotel->head;
        hotel->head = newGuest;
    }
}

int login() {
    char password[50];
    printf("Enter Admin password: ");
    scanf(" %[^\n]", password);
    if (strcmp(password, "admin") == 0) {
        printf("\nAdmin Logged in Successfully.\n");
        return 1;
    } else {
        printf("Login failed. Invalid username or password.\n");
        return 0;
    }
}

int displayAvailableRooms(HOTEL* hotel, int rt) {
    printf("Available Rooms for Room Type %d):\n", rt);

    bool isAvailable = false;

    GUEST* currentGuest = hotel->head;
    while (currentGuest != NULL) {
        if (currentGuest->roomType == rt && currentGuest->age == -1) {
            printf("Room no %d.\n", currentGuest->roomNumber);
            isAvailable = true;
        }
        currentGuest = currentGuest->next;
    }

    if (!isAvailable) {
        printf("No available rooms of type %d.\n", rt);
        return -1;
    }

    return 0;
}

void makeReservation(HOTEL* hotel) {
    int rn, rt, agee;
    char namee[50], phno[10];

    printf("Enter your name: ");
    scanf(" %[^\n]", namee);

    // Ask the guest to select the room type
    printf("Select a room type:\n");
    printf("1. Single\n");
    printf("2. Double\n");
    printf("3. Suite\n");
    printf("Enter your choice: ");
    scanf("%d", &rt);

    if (rt < 1 || rt > 3) {
        printf("Invalid room type selection.\n");
        return;
    }

    if (displayAvailableRooms(hotel, rt) != -1) {
        // Pass the selected room type to the function
        printf("Enter the room number you want to reserve: ");
        scanf("%d", &rn);

        GUEST* currentGuest = hotel->head;
        while (currentGuest != NULL) {
            if (currentGuest->roomNumber == rn) {
                if (currentGuest->age != -1) {
                    printf("Room is already reserved by another guest.\n");
                    guestFunc(hotel);
                    return;
                }

                if (((rt == 1) && ((rn >= 1) && (rn <= 20))) ||
                    ((rt == 2) && ((rn > 20) && (rn <= 40))) ||
                    ((rt == 3) && ((rn > 40) && (rn <= 50)))) {
                    printf("Please Enter your age: ");
                    scanf("%d", &agee);
                    printf("Please Enter your Phone NO: ");
                    scanf("%s", phno);

                    // Update guest information
                    strcpy(currentGuest->name, namee);
                    strcpy(currentGuest->phone, phno);
                    currentGuest->roomType = rt;
                    currentGuest->age = agee;

                    printf("Reservation successful!\n");
                } else {
                    printf("Invalid room number.\n");
                    guestFunc(hotel);
                    return;
                }
            }
            currentGuest = currentGuest->next;
        }
    } else {
        printf("Rooms are not available at the moment.\n\n");
        menu(hotel);
        return;
    }
}

void checkRoom(HOTEL* hotel, int rm) {
    rm = rm - 1;

    GUEST* currentGuest = hotel->head;
    while (currentGuest != NULL) {
        if (currentGuest->roomNumber == rm + 1) {
            if (currentGuest->age != -1) {
                printf("Room is occupied.\n");
                return;
            } else {
                printf("Room is available.\n");
                return;
            }
        }
        currentGuest = currentGuest->next;
    }

    printf("Invalid room number.\n");
}

void addGuest(HOTEL* hotel) {
    int rn, rt, agee;
    char namee[50], phno[10];

    printf("Enter your name: ");
    scanf(" %[^\n]", namee);

    // Ask the guest to select the room type
    printf("Select a room type:\n");
    printf("1. Single\n");
    printf("2. Double\n");
    printf("3. Suite\n");
    printf("Enter your choice: ");
    scanf("%d", &rt);

    if (rt < 1 || rt > 3) {
        printf("Invalid room type selection.\n");
        return;
    }

    if (displayAvailableRooms(hotel, rt) != -1) {
        // Pass the selected room type to the function
        printf("Enter the room number you want to reserve: ");
        scanf("%d", &rn);

        GUEST* currentGuest = hotel->head;
        while (currentGuest != NULL) {
            if (currentGuest->roomNumber == rn) {
                if (currentGuest->age != -1) {
                    printf("Room is already reserved by another guest.\n");
                    guestFunc(hotel);
                    return;
                }

                if (((rt == 1) && ((rn >= 1) && (rn <= 20))) ||
                    ((rt == 2) && ((rn > 20) && (rn <= 40))) ||
                    ((rt == 3) && ((rn > 40) && (rn <= 50)))) {
                    printf("Please Enter your age: ");
                    scanf("%d", &agee);

                    printf("Please Enter your Phone NO: ");
                    scanf("%s", phno);

                    // Update guest information
                    strcpy(currentGuest->name, namee);
                    strcpy(currentGuest->phone, phno);
                    currentGuest->roomType = rt;
                    currentGuest->age = agee;

                    printf("Guest added successfully!\n");
                } else {
                    printf("Invalid room number.\n");
                    guestFunc(hotel);
                    return;
                }
            }
            currentGuest = currentGuest->next;
        }
    } else {
        printf("Rooms are not available at the moment.\n\n");
        menu(hotel);
        return;
    }
}

void removeGuest(HOTEL* hotel, int r, int rot) {
    char n[50] = "";
    GUEST* currentGuest = hotel->head;

    while (currentGuest != NULL) {
        if (currentGuest->roomNumber == r) {
            currentGuest->age = -1;
            currentGuest->wifi = 0;
            currentGuest->food = 0;
            currentGuest->roomType = rot;
            currentGuest->roomNumber = r;
            strcpy(currentGuest->name, n);
            strcpy(currentGuest->phone, n);
            printf("The guest has been removed successfully.\n");
            return;
        }
        currentGuest = currentGuest->next;
    }

    printf("Invalid room number.\n");
}

void searchGuest(HOTEL* hotel, char nn[50]) {
    int c = 0;
    GUEST* currentGuest = hotel->head;

    while (currentGuest != NULL) {
        if (strcmp(currentGuest->name, nn) == 0) {
            printf("The room number is: %d\n", currentGuest->roomNumber);
            printf("The phone number is: %s\n", currentGuest->phone);
            printf("The age of the person is: %d\n", currentGuest->age);
            c++;
        }
        currentGuest = currentGuest->next;
    }

    if (c == 0) {
        printf("Guest not found.\n");
    }
}

void amenities(HOTEL* hotel, int ro) {
    printf("Do you want a WiFi plan?\n");
    printf("Enter 1 for yes and 2 for no\n");
    int var;
    scanf("%d", &var);

    GUEST* currentGuest = hotel->head;
    while (currentGuest != NULL) {
        if (currentGuest->roomNumber == ro) {
            if (var == 1) {
                currentGuest->wifi = 1;
                printf("WiFi plan is now included!\n");
            } else {
                currentGuest->wifi = 0;
            }
            break;
        }
        currentGuest = currentGuest->next;
    }

    printf("Do you want breakfast?\n");
    printf("Enter 1 for yes and 2 for no\n");
    int var1;
    scanf("%d", &var1);

    currentGuest = hotel->head;
    while (currentGuest != NULL) {
        if (currentGuest->roomNumber == ro) {
            if (var1 == 1) {
                currentGuest->food = 1;
                printf("Breakfast plan is now included!\n");
            } else {
                currentGuest->food = 0;
            }
            break;
        }
        currentGuest = currentGuest->next;
    }
}

void generateInvoice(HOTEL* hotel, int room) {
    GUEST* currentGuest = hotel->head;

    while (currentGuest != NULL) {
        if (currentGuest->roomNumber == room && currentGuest->age != -1) {
            printf("Invoice for Room %d:\n", room);
            printf("Guest Name: %s\n", currentGuest->name);
            printf("Age: %d\n", currentGuest->age);
            printf("Phone: %s\n", currentGuest->phone);
            printf("Room Type: %d\n", currentGuest->roomType);
            float Bill = 0.0;

            // Add extra charges like WiFi and food if applicable
            if (currentGuest->wifi) {
                Bill += 100.0; // Example WiFi charge
            }
            if (currentGuest->food) {
                Bill += 400.0; // Example food charge
            }

            // Update the bill based on the room type
            switch (currentGuest->roomType) {
                case 1: // Single room
                    Bill += 1000.0; // Example single room charge
                    break;
                case 2: // Double room
                    Bill += 1500.0; // Example double room charge
                    break;
                case 3: // Suite
                    Bill += 2000.0; // Example suite charge
                    break;
            }

            printf("Total Bill: $%.2f\n", Bill);
            return;
        }
        currentGuest = currentGuest->next;
    }

    printf("Room is either empty or an invalid room number.\n");
}

void admin(HOTEL* hotel) {
    int choice, roomtype, rooo, rr, roomNum, rrt;
    char nam[50];

    do {
        printf("\nAdmin Menu\n");
        printf("1. Display Available Rooms\n");
        printf("2. Make a Reservation\n");
        printf("3. Add amenities\n");
        printf("4. Search guest by name\n");
        printf("5. Add guest\n");
        printf("6. Remove guest\n");
        printf("7. Generate invoice\n");
        printf("8. Go back to MENU\n");

        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            // Clear the input buffer
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }

        switch (choice) {
            case 1:
                printf("Enter the room type (1 for single, 2 for double, 3 for suite): ");
                scanf("%d", &roomtype);
                displayAvailableRooms(hotel, roomtype);
                break;
            case 2:
                makeReservation(hotel);
                break;
            case 3:
                printf("Enter the room number: ");
                scanf("%d", &rooo);
                amenities(hotel, rooo);
                break;
            case 4:
                printf("Enter the name of the person: ");
                scanf("%s", nam);
                searchGuest(hotel, nam);
                break;
            case 5:
                addGuest(hotel);
                break;
            case 6:
                printf("Enter the room type: ");
                scanf("%d", &rrt);
                printf("Enter the room number: ");
                scanf("%d", &rr);
                removeGuest(hotel, rr, rrt);
                break;
            case 7:
                printf("Enter room number to generate an invoice: ");
                scanf("%d", &roomNum);
                printf("Generating invoice....\n");
                generateInvoice(hotel, roomNum);
                break;
            case 8:
                printf("Going back to MENU!\n");
                menu(hotel);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (1);
}


void menu(HOTEL* hotel) {
    int choice = 0;

    do {
        printf("\nMain Menu:\n");
        printf("1. Admin\n");
        printf("2. Guest\n");
        printf("3. Quit\n");

        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            // Clear the input buffer
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }

        switch (choice) {
            case 1:
                if (login() == 1) {
                    admin(hotel);
                } else {
                    menu(hotel);
                }
                break;
            case 2:
                guestFunc(hotel);
                break;
            case 3:
                printf("\nExiting...\n");
                exit(0);
                break;
            default:
                printf("Invalid choice. Please select a valid option.\n");
        }
    } while (1);
}


void guestFunc(HOTEL* hotel) {
    int choice, roomtype, roo, rmm, roomNum;
    do {
        printf("\nGuest Menu\n");
        printf("1. Display Available Rooms\n");
        printf("2. Make a Reservation\n");
        printf("3. Add Amenities\n");
        printf("4. Check if a Room is Available\n");
        printf("5. Generate My Bill\n");
        printf("6. Go Back to MENU\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the room type (1 for single, 2 for double, 3 for suite): ");
                scanf("%d", &roomtype);
                displayAvailableRooms(hotel, roomtype);
                break;
            case 2:
                makeReservation(hotel);
                break;
            case 3:
                printf("Enter the room number: ");
                scanf("%d", &roo);
                amenities(hotel, roo);
                break;
            case 4:
                printf("Enter the room number: ");
                scanf("%d", &rmm);
                checkRoom(hotel, rmm);
                break;
            case 5:
                printf("Enter room number to generate an invoice: ");
                scanf("%d", &roomNum);
                printf("Generating invoice....\n");
                generateInvoice(hotel, roomNum);
                break;
            case 6:
                printf("Going back to MENU!\n");
                menu(hotel);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (1);
}

int main() {
    HOTEL hotel;
    initializeRooms(&hotel);
    menu(&hotel);

    return 0;
}

           
