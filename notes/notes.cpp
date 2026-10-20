void notes() {
pros::Controller master(pros::E_CONTROLLER_MASTER);
	pros::MotorGroup left_mg({1, -2, 3});    // Creates a motor group with forwards ports 1 & 3 and reversed port 2
	pros::MotorGroup right_mg({-4, 5, -6});
	left_mg.move_relative(720, 100);
	left_mg.move_relative(720, 100);
	right_mg.move_relative(720, 100); // First number is degrees of rotation second number is the power you finna give it
	left_mg.move_absolute(721,100) // This is where you like make it go to one point plus your point
	left_mg.move(120)// It likes auto set the power you can give to you know - tells brain to send set amount of volts to motor, keeps running at that
	pros::delay(1000); // stops the motor for after blah blah second so that no overheat
	left_mg.move(0); //Breaks the autoset thingy
	if (TRUE) { // If/else statement
		pros::lcd::print(0, "TRUE"); // Prints TRUE to the screen at line 0
	} else if (FALSE) {
		pros::lcd::print(0, "FALSE"); // the 0 represents the line it is gonna print on whe give out output
	} else {
		pros::lcd::print(0, "NEITHER");
	}
}