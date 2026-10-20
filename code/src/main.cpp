#include "main.h"
#include "titanselect/titanselect.h"
#include "lemlib/api.hpp"
#include "pros/apix.h"

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
void initialize() {
    pros::Controller master(pros::E_CONTROLLER_MASTER);
   while (true) {
    master.print(0, 0, "For auton click right");
    master.print(1, 0, "For opcontrol click left");
    int right = master.get_digital_new_press(DIGITAL_RIGHT);
    int left = master.get_digital_new_press(DIGITAL_LEFT); 
    if (right == 1) {
        master.print(0, 0, "Auton selected");
        
    }
    }
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
	ts_create_auton("Red", red_auton);
    ts_create_auton("Blue", blue_auton);
	ts_display_selector();
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
	ts_run_selected_auton();
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
void opcontrol() {
	pros::Controller master(pros::E_CONTROLLER_MASTER);
	pros::MotorGroup left_mg({1, -2, 3});    // Creates a motor group with forwards ports 1 & 3 and reversed port 2
	pros::MotorGroup right_mg({-4, 5, -6});  // Creates a motor group with forwards port 5 and reversed ports 4 & 6
	pros::Motor claw(7);

	while (true) {
		pros::lcd::print(0, "%d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
		                 (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
		                 (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);  // Prints status of the emulated screen LCDs

		// Tank control scheme
		int dir = master.get_analog(ANALOG_LEFT_Y);    // Gets amount forward/backward from left joystick
		int turn = master.get_analog(ANALOG_RIGHT_X);  // Gets the turn left/right from right joystick
		int apress = master.get_digital(DIGITAL_A);
		left_mg.move(dir);                      // Sets left motor voltage
		right_mg.move(turn);                     // Sets right motor voltage
		pros::delay(20);                               // Run for 20 ms then update
	}
}
void test() {
   pros::Controller master(pros::E_CONTROLLER_MASTER);
   while (true) {
    master.print(0, 0, "For auton click right");
    master.print(1, 0, "For opcontrol click left");
    int right = master.get_digital_new_press(DIGITAL_RIGHT);
    int left = master.get_digital_new_press(DIGITAL_LEFT); }
}