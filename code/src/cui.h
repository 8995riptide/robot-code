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
    }

    // Displays a menu with options and allows the user to select one
    // Returns an integer representing the selected option.
    // 1 = Option 1, 2 = Option 2, etc.
    // 0 = No selection/back. It's the left arrow.
    class Menu {
        User(char* option1, char* option2, char* option3) {
            // Display the menu options on the controller's screen
            void updateMenu() {
                controller.clear();
                controller.print(0, 0, option1);
                controller.print(1, 0, option2);
                controller.print(2, 0, option3);
            }

            // Check for user input and return the selected option
            int getSelection() {
                while (true) {
                    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP)) {
                        return 1; // Option 1 selected
                    } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
                        return 2; // Option 2 selected
                    } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) {
                        return 3; // Option 3 selected
                    } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT)) {
                        return 0; // No selection/back
                    } else {
                        return -1; // No selection made/None pressed
                    }
                }
            }

            // Displaying and checking the menu is up to the user.
            // This is just a helper class to make it easier to display a menu and check for user input.
            // The user can call updateMenu() to display the menu and getSelection() to check for user input.
        }
    }

    /*
    Example Usage:
    CUI cui;
    // Create a menu with three options: "Tank drive", "Arcade drive", and "Autonomous".
    auto mainmenu = cui.Menu("Tank drive", "Arcade drive", "Autonomous");
    updateMenu(); // Display the menu
    while (true) {
        <OTHER ROBOT CODE>

        int selection = getSelection(); // Check for user input
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
