#pragma once

// TUI Library for VEX V5 Controller using PROS

#include "pros/apix.h"

// CUI (Controller User Interface) class for handling controller input and output
// Built for Vex V5 Controller using PROS API
class CUI {
    pros::Controller controller{pros::E_CONTROLLER_MASTER};

    // Clears the controller's screen
    void clear() {
        controller.clear();
    }

    // Prints text to the controller's screen at a specified line
    void print(int line, const char* text) {
        controller.print(line, 0, text);
        pros::delay(50); // Small delay to ensure the text is displayed properly
    }

public:
    // Displays a menu with options and allows the user to select one
    // Returns an integer representing the selected option.
    // 1 = Option 1, 2 = Option 2, etc.
    // 0 = No selection/back. It's the left arrow.
    class Menu {
        CUI& cui;
        const char* option1;
        const char* option2;
        const char* option3;

    public:
        Menu(CUI& cui, const char* option1, const char* option2, const char* option3)
            : cui(cui), option1(option1), option2(option2), option3(option3) {}

        // Display the menu options on the controller's screen
        void updateMenu() {
            cui.clear();
            cui.print(0, option1);
            cui.print(1, option2);
            cui.print(2, option3);
        }
        bool menuActive = true; // Menu is active by default
        // Check for user input and return the selected option
        int getSelection() {
            if (cui.controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP)) {
                menuActive = false; // Menu is no longer active after a selection is made
                return 1; // Option 1 selected
            } else if (cui.controller.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
                menuActive = false; // Menu is no longer active after a selection is made
                return 2; // Option 2 selected
            } else if (cui.controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) {
                menuActive = false; // Menu is no longer active after a selection is made
                return 3; // Option 3 selected
            } else if (cui.controller.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT)) {
                menuActive = false; // Menu is no longer active after a selection is made
                return 0; // No selection/back
            } else {
                return -1; // No selection made/None pressed
            }
        }

        // Displaying and checking the menu is up to the user.
        // This is just a helper class to make it easier to display a menu and check for user input.
        // The user can call updateMenu() to display the menu and getSelection() to check for user input.
    };

    Menu menu(const char* option1, const char* option2, const char* option3) {
        return Menu(*this, option1, option2, option3);
    }

    /*
    Example Usage:
    CUI cui;
    // Create a menu with three options: "Tank drive", "Arcade drive", and "Autonomous".
    auto mainmenu = cui.menu("Tank drive", "Arcade drive", "Autonomous");
    mainmenu.updateMenu(); // Display the menu
    while (true) {
        <OTHER ROBOT CODE>

        int selection = mainmenu.getSelection(); // Check for user input
        if (selection == 1) {
            // User selected "Tank drive"
            break; // Exit the menu loop or do whatever you want to do when the user selects "Tank drive"
        } else if (selection == 2) {
            // User selected "Arcade drive"
            break; // Exit the menu loop or do whatever you want to do when the user selects "Arcade drive"
        } else if (selection == 3) {
            // User selected "Autonomous"
            break; // Exit the menu loop or do whatever you want to do when the user selects "Autonomous"
        } else if (selection == 0) {
            // User pressed the left arrow (back)
            break; // Exit the menu loop or do whatever you want to do when the user presses the left arrow
        }

        <OTHER ROBOT CODE>
    }
    */
};
