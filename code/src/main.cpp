#include "main.h"
#include "titanselect/titanselect.h"
#include "lemlib/api.hpp"
#include "pros/apix.h"
#include "cui.h"

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void nothing() {
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
void red_auton() {
	pros::MotorGroup left_mg({1, 3}, pros::MotorGearset::green);    // Creates a motor group with forwards ports 1 & 3 and reversed port 2
	pros::MotorGroup right_mg({-4, -6}, pros::MotorGearset::green);  // Creates a motor group with forwards port 5 and reversed ports 4 & 6
	pros::Motor claw(-7);
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
                                              3, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              500, // large error range timeout, in milliseconds
                                              20 // maximum acceleration (slew)
);
	lemlib::ControllerSettings angular_controller(2, // proportional gain (kP)
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

	chassis.calibrate();  // Calibrates the IMU and tracking wheels. This should be called in the initialize function
	chassis.setPose(0, 0, 0);
	claw.move(100);
	chassis.turnToHeading(-270, 2000);
	pros::delay(3000);
	claw.move(0);
}
void blue_auton() {
	pros::MotorGroup left_mg({1, 3}, pros::MotorGearset::green);    // Creates a motor group with forwards ports 1 & 3 and reversed port 2
	pros::MotorGroup right_mg({-4, -6}, pros::MotorGearset::green);  // Creates a motor group with forwards port 5 and reversed ports 4 & 6
	pros::Motor claw(-7);
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
                                              3, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              500, // large error range timeout, in milliseconds
                                              20 // maximum acceleration (slew)
);
	lemlib::ControllerSettings angular_controller(2, // proportional gain (kP)
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

	chassis.calibrate();  // Calibrates the IMU and tracking wheels. This should be called in the initialize function
	chassis.setPose(0, 0, 0);
	claw.move(100);
	chassis.turnToHeading(270, 4000);
	pros::delay(3000);
	claw.move(0);
	
}
void competition_initialize() {
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
       pros::Controller master(pros::E_CONTROLLER_MASTER);
       	pros::MotorGroup right_mg({1, 3});    // Creates a motor group with forwards ports 1 & 3 and reversed port 2
	pros::MotorGroup left_mg({-4, -6});  // Creates a motor group with forwards port 5 and reversed ports 4 & 6
	pros::Motor claw(-7);
    pros::Motor lift(8);
    master.clear();
    pros::delay(50);
    master.print(0, 0, "R: Auton L: Opcontrol");
    while (!master.get_digital(DIGITAL_RIGHT) && !master.get_digital(DIGITAL_LEFT)) {
        pros::delay(10);
    }
    if (master.get_digital(DIGITAL_RIGHT)) {
        master.clear();
        pros::delay(50);
    }
    if (master.get_digital(DIGITAL_LEFT)) {
        master.clear();
        pros::delay(1000);
        master.print(0, 0, "R: Tank L: Arcade");
        while (!master.get_digital(DIGITAL_RIGHT) && !master.get_digital(DIGITAL_LEFT)) {
            pros::delay(10);
        }
        if (master.get_digital(DIGITAL_RIGHT)) {
            master.clear();
            pros::delay(50);
            master.print(0, 0, "Tank drive selected");
            pros::delay(50);
            master.clear();
        while (true) {
        int dir = master.get_analog(ANALOG_LEFT_Y);    // Gets amount forward/backward from left joystick
		int turn = master.get_analog(ANALOG_RIGHT_Y);  // Gets the turn left/right from right joystick
		int l1 = master.get_digital(DIGITAL_L1);
        int l2 = master.get_digital(DIGITAL_L2);
        int x = master.get_digital(DIGITAL_X);
        int y = master.get_digital(DIGITAL_Y);
		left_mg.move(dir);                      // Sets left motor voltage
		right_mg.move(turn);                     // Sets right motor voltage
        lift.move(l1 * 127 - l2 * 127); // Sets lift motor voltage
        if (x) {
            claw.move(127);
        } else if (y) {
            claw.move(0);
        }
		pros::delay(20);                               // Run for 20 ms then update  
        }      
    }
        if (master.get_digital(DIGITAL_LEFT)) {
            master.clear();
            pros::delay(50);
            master.print(0, 0, "Arcade drive selected");
            pros::delay(50);
            master.clear();
            while (true) {
            int throttle = master.get_analog(ANALOG_LEFT_Y);    // Gets amount forward/backward from left joystick
		int turn = master.get_analog(ANALOG_RIGHT_X);  // Gets the turn left/right from right joystick
        		int l1 = master.get_digital(DIGITAL_L1);
        int l2 = master.get_digital(DIGITAL_L2);
        int x = master.get_digital(DIGITAL_X);
        int y = master.get_digital(DIGITAL_Y);
		left_mg.move(throttle + turn);                      // Sets left motor voltage
		right_mg.move(throttle - turn);                     // Sets right motor voltage
                lift.move(l1 * 127 - l2 * 127); // Sets lift motor voltage
        if (x) {
            claw.move(127);
        } else if (y) {
            claw.move(0);
        }
		pros::delay(20);                               // Run for 20 ms then update
            }
}
        }
}