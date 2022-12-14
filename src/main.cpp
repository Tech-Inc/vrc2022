#include "main.h"
#include "pros/misc.h"
#include "pros/motors.h"

#define LEFT_WHEELS_PORT 1
#define RIGHT_WHEELS_PORT 10

//using namespace pros;

void opcontrol() {
  pros::Motor left1 (10);
  pros::Motor right1 (1, false); // This reverses the motor
  pros::Motor right2 (2, true);
  pros::Motor left2 (9,true);
  pros::Motor shooter (19, false);
  pros::Motor intake (12, true);
  pros::Motor str_launcher (20);
  pros::Controller master (CONTROLLER_MASTER);
  pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS\]=]\ User!2");
//define a pnumetics controller
  pros::ADIDigitalOut trigger (1);
  pros::ADIDigitalOut pusher (8);
  master.clear();
  while (true) {
    left1.move(master.get_analog(ANALOG_LEFT_Y));
    left2.move(master.get_analog(ANALOG_LEFT_Y));
    right1.move(master.get_analog(ANALOG_RIGHT_Y));
    right2.move(master.get_analog(ANALOG_RIGHT_Y));
    if (master.get_digital(DIGITAL_A)){
      intake.move_velocity(-100000);
      intake.move(127);
    }
    if (master.get_digital(DIGITAL_B)){
      intake.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
      intake.brake();
    }
    if (master.get_digital(DIGITAL_X)){
      str_launcher.move_relative(100,100);
    }
    if (master.get_digital(DIGITAL_UP)){
      trigger.set_value(1);
    }
    if (master.get_digital(DIGITAL_LEFT)){
      trigger.set_value(0);
    }
    if (master.get_digital(DIGITAL_L1)){
        shooter.move_velocity(100);
        shooter.move(-100); // Moves 100 units forward

    }else{
        shooter.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
        shooter.brake();
    }
    if (master.get_digital(DIGITAL_L2)){
        shooter.move_velocity(-100);
        shooter.move(100); // Moves 100 units forward
    }else{
        shooter.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
        shooter.brake(); 
    }
    master.print(0, 0, "velocity: %d", int(intake.get_actual_velocity()));
    // master.print(1, 0, "efficiency: %d", bottom_intake.get_efficiency());
    // master.print(2, 0, "temperature: %d", bottom_intake.get_temperature());
    // master.print(3, 0, "voltage: %d", bottom_intake.get_voltage());
    pros::delay(2);
    
  }
}
