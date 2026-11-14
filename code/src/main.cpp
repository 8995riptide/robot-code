#include "main.h"
#include "lemlib/api.hpp"
#include "pros/apix.h"
#include <random>
#include <cstdio>
#define EXAMPLE_SIG 1
	pros::MotorGroup right_mg({1, 3}, pros::MotorGearset::green);    // Creates a motor group with forwards ports 1 & 3 and reversed port 2
	pros::MotorGroup left_mg({-4, -6}, pros::MotorGearset::green);  // Creates a motor group with forwards port 5 and reversed ports 4 & 6
	pros::Motor claw(-7);
    pros::MotorGroup lift({-8, -5}, pros::MotorGearset::red);
    pros::Motor roller(2);
    pros::Controller master(pros::E_CONTROLLER_MASTER);
	lemlib::Drivetrain drivetrain(&left_mg,
                              &right_mg,
                              15.5, // 10 inch track width
                              lemlib::Omniwheel::NEW_275, // using new 4" omnis
                              100, // drivetrain rpm is 360
                              2 // horizontal drift is 2 (for now)
);
	lemlib::OdomSensors sensors(
    nullptr, // Vertical tracking wheel 1 (Set to nullptr to use Motor IMEs)
    nullptr, // Vertical tracking wheel 2
    nullptr, // Horizontal tracking wheel 1 (Set to nullptr since we have no sensor)
    nullptr, // Horizontal tracking wheel 2
    nullptr
);
	lemlib::ControllerSettings lateral_controller(10, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              10, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              500, // large error range timeout, in milliseconds
                                              20 // maximum acceleration (slew)
);
	lemlib::ControllerSettings angular_controller(1, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              10, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              500, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);
lemlib::Chassis chassis(drivetrain, // drivetrain settings
                        lateral_controller, // lateral PID settings
                        angular_controller, // angular PID settings
                        sensors // odometry sensors
);

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */

void save_auton(int selection) {
    if (pros::usd::is_installed()) {
        FILE* file = fopen("/usd/auton_selection.txt", "w");
        if (file != nullptr) {
            fprintf(file, "%d", selection);
            fclose(file);
        }
    }
}
void save_drive(int selection) {
    if (pros::usd::is_installed()) {
        FILE* file = fopen("/usd/drive_selection.txt", "w");
        if (file != nullptr) {
            fprintf(file, "%d", selection);
            fclose(file);
        }
    }
}
int get_auton() {
    if (pros::usd::is_installed()) {
        FILE* file = fopen("/usd/auton_selection.txt", "r");
        if (file != nullptr) {
            int selection;
            fscanf(file, "%d", &selection);
            fclose(file);
            return selection;
        }
    }
    return 0;
}
int get_drive() {
    if (pros::usd::is_installed()) {
        FILE* file = fopen("/usd/drive_selection.txt", "r");
        if (file != nullptr) {
            int selection;
            fscanf(file, "%d", &selection);
            fclose(file);
            return selection;
        }
    }
    return 0;
}
/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */

void competition_initialize() {
    while (get_auton() == 0 || get_drive() == 0) {
        master.clear();
        pros::delay(50);
        master.print(0, 0, "Selections have not been configured!");
        pros::delay(50);
        master.print(1, 0, "Unplug the controller and");
        pros::delay(50);
        master.print(2, 0, "rerun the program to try again!");
        pros::delay(50);
        master.rumble("--------");
        pros::delay(50);
    }
    chassis.calibrate();  // Calibrates the IMU and tracking wheels. This should be called in the initialize function
	chassis.setPose(0, 0, 0);
    master.clear();
    pros::delay(50);
    master.print(0, 0, "Controller plugged in,");
    pros::delay(50);
    master.print(1, 0, "All systems calibrated,");
    pros::delay(50);
    master.print(2, 0, "ready to go!");
    pros::delay(50);

}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
    master.print(0, 0, "Autonomous running");
    pros::delay(50);
    master.rumble(".");
    claw.move(100);
    chassis.moveToPoint(0, -6, 1000);
    roller.move_relative(360, 100);
    lift.move(127);
    if (get_auton() == 1) {
        chassis.moveToPoint(6, 12, 4000);
    } else if (get_auton() == 2) {
        chassis.moveToPoint(-6, 12, 4000);
    }
    lift.move(-50);
    claw.move(-50);
    master.clear();
    pros::delay(50);
    master.print(0, 0, "Auton done!");
    pros::delay(50);
    master.print(1, 0, "Proceeding to opcontrol...");
    pros::delay(50);
    master.clear();
}
/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void initialize() {
        master.clear();
    pros::delay(50);
    chassis.calibrate();  // Calibrates the IMU and tracking wheels. This should be called in the initialize function
	chassis.setPose(0, 0, 0);
    master.print(0, 0, "Odometry calibrated. CUI Ready.");
    pros::delay(100);
    master.print(1, 0, "Checking port config...");
    pros::delay(100);
    int flags = 0;
    std::vector<uint32_t> left_flags = left_mg.get_flags_all();
    for (int i = 0; i < left_flags.size(); i++) {
        if (left_flags[i] & pros::E_MOTOR_FLAGS_BUSY) {
            master.clear();
            pros::delay(50);
            master.print(0, 0, "Port %d disconnected", left_mg.get_port(i));
            pros::delay(50);
            master.rumble("-");
            flags = 1;
        }
    }
    pros::delay(100);
    std::vector<uint32_t> right_flags = right_mg.get_flags_all();
    for (int i = 0; i < right_flags.size(); i++) {
        if (right_flags[i] & pros::E_MOTOR_FLAGS_BUSY) {
            pros::delay(50);
            master.print(1, 0, "Port %d disconnected", right_mg.get_port(i));
            pros::delay(50);
            master.rumble("-");
            flags = 1;
        }
    }
    std::vector<uint32_t> lift_flags = lift.get_flags_all();
    for (int i = 0; i < lift_flags.size(); i++) {
        if (lift_flags[i] & pros::E_MOTOR_FLAGS_BUSY) {
            pros::delay(50);
            master.print(0, 0, "Port %d disconnected", lift.get_port(i));
            pros::delay(50);
            master.rumble("-");
            flags = 1;
        }
    }
    if (claw.get_flags() & pros::E_MOTOR_FLAGS_BUSY) {
        pros::delay(50);
        master.print(2, 0, "Port %d disconnected", claw.get_port());
        pros::delay(50);
        master.rumble("-");
        flags = 1;
    }
    if (roller.get_flags() & pros::E_MOTOR_FLAGS_BUSY) {
        pros::delay(50);
        master.print(2, 0, "Port %d disconnected", roller.get_port());
        pros::delay(50);
        master.rumble("-");
        flags = 1;
    }
    pros::delay(100);
    while (flags == 1) {
        pros::delay(100);
    }
    master.print(2, 0, " Starting ROBOS...");
    pros::delay(500);
    master.clear();
    pros::delay(50);
    const std::string charset = "0123456789";
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<std::size_t> distribution(0, charset.size() - 1); 
    std::uniform_int_distribution<int> distrib(0, 3); 
    std::uniform_int_distribution<int> distrib2(0, 15); 
    for (int i = 0; i < 3; i++) {
        for (int n = 0; n < 15; n++) {
            std::size_t randomIndex = distribution(generator);
            char randomChar = charset[randomIndex];
            master.print(i, n, "%c", randomChar);
            pros::delay(50);
        }
    }
    std::vector<char> chars = {'R', 'O', 'B', 'O', 'S'};
    for (int i = 0; i <= 80; i++) {
        std::size_t randomIndex = distribution(generator);
        char randomChar = charset[randomIndex];
        int randomLineNum = distrib(generator);
        int randomColNum = distrib2(generator);
            if (randomColNum >= 5 && randomColNum <= 9 && randomLineNum == 1) {
                pros::delay(50);
        } else {
        master.print(randomLineNum, randomColNum, "%c", randomChar);
        }
        pros::delay(50);
        if (i % 16 == 0) {
            master.print(1, (i/16)+5, "%c", chars[(i/16)]);
        }
    }
    master.rumble(". . .");
    pros::delay(2000);
    master.clear();
    pros::delay(50);
    master.print(0, 0, "Configure Auton");
    pros::delay(50);
        master.print(1, 0, "R: Driver L: Judges");
        while (!master.get_digital(DIGITAL_RIGHT) && !master.get_digital(DIGITAL_LEFT)) {
            pros::delay(10);
        }
        if (master.get_digital(DIGITAL_RIGHT)) {
            save_auton(1);
            master.clear();
            pros::delay(50);
            master.rumble(".");
            pros::delay(50);
            master.print(0, 0, "Drive auton selected");
            pros::delay(50);
        } else if (master.get_digital(DIGITAL_LEFT)) {
            save_auton(2);
            master.clear();
            pros::delay(50);
            master.rumble(".");
            pros::delay(50);
            master.print(0, 0, "Judges auton selected");
            pros::delay(50);
        }
        master.clear();
        pros::delay(1000);
        master.print(0, 0, "Configure driving style");
        pros::delay(50);
        master.print(1, 0, "R: Tank L: Arcade");
        while (!master.get_digital(DIGITAL_RIGHT) && !master.get_digital(DIGITAL_LEFT)) {
            pros::delay(10);
        }
        if (master.get_digital(DIGITAL_RIGHT)) {
            master.clear();
            pros::delay(50);
            master.rumble(".");
            pros::delay(50);
            master.print(0, 0, "Tank drive selected");
            pros::delay(50);
            master.clear();
            save_drive(1);      
    } else if (master.get_digital(DIGITAL_LEFT)) {
            master.clear();
            pros::delay(50);
            master.rumble(".");
            pros::delay(50);
            master.print(0, 0, "Arcade drive selected");
            pros::delay(50);
            master.clear();
            save_drive(2);
}
    pros::delay(50);
    master.print(0, 0, "Configuration done");
    pros::delay(50);
    master.print(1, 0, "You are all set!");
    pros::delay(50);
    master.print(2, 0, "Plug in the controller now!");
    pros::delay(2000);
    master.clear();
    autonomous();
}
void opcontrol() {
    master.print(0, 0, "opcontrol begun!");
    pros::delay(50);
    master.rumble(".");
    pros::delay(50);
    master.print(1, 0, "R: Tank L: Arcade");
        while (true) {
            int throttle = master.get_analog(ANALOG_LEFT_Y);    // Gets amount forward/backward from left joystick
		int turn = master.get_analog(ANALOG_RIGHT_X);  // Gets the turn left/right from right joystick
        int throttle2 = master.get_analog(ANALOG_RIGHT_Y);
        		int l1 = master.get_digital(DIGITAL_L1);
        int l2 = master.get_digital(DIGITAL_L2);
        int x = master.get_digital(DIGITAL_X);
        int y = master.get_digital(DIGITAL_Y);
        int r1 = master.get_digital(DIGITAL_R1);
        int r2 = master.get_digital(DIGITAL_R2);
        lift.set_brake_mode_all(pros::E_MOTOR_BRAKE_HOLD);
        if (master.get_digital_new_press(DIGITAL_LEFT)) {
            save_drive(2);
            master.rumble(".");
        } else if (master.get_digital_new_press(DIGITAL_RIGHT)) {
            save_drive(1);
            master.rumble(".");
        }
        if (get_drive() == 1) {
            chassis.tank(throttle, throttle2);
        } else if (get_drive() == 2) {
            chassis.arcade(throttle, turn);
        }
        if (l1) {
            lift.move(l1 * 127);
        } else if (l2) {
            lift.move_velocity(0);
        }

        if (x) {
            claw.move(127);
        } else if (y) {
            claw.move(-50);
        }
        if (r1) {
            roller.move(127);
        } else if (r2) {
            roller.move(-127);
        } else {
            roller.move(0);
        }
		pros::delay(20);                               // Run for 20 ms then update
            }
}