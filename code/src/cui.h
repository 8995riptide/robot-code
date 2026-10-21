#include "pros/apix.h"

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
    int menu(const char* option1 = 0, const char* option2 = 0, const char* option3 = 0) {
        int selection = 0;
        while (true) {
            clear();
            print(1, option1);
            print(2, option2);
            print(3, option3);

            if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT)) {
                return 0; // No selection/back
            } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP)) {
                selection = 1; // Option 1
                break;
            } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) {
                selection = 2; // Option 2
                break;
            } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
                selection = 3; // Option 3
                break;
            }
        }
        return selection;
    }
};