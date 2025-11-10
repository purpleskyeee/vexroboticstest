#include "definitions.hpp"
#include "odom.hpp"
#include "pid.hpp"

void pidForward(double target)
{
    double startleft=Odom.encoder_to_inches(leftmotors[0].position(deg));
    double startright=Odom.encoder_to_inches(rightmotors[0].position(deg));

    pid_forward.reset();
    pid_forward.SetTarget(target);

    double currentleft=0;
    double currentright=0;
    while(!pid_forward.Arrived())
    {
      currentleft=Odom.encoder_to_inches(leftmotors[0].position(deg));
      currentright=Odom.encoder_to_inches(rightmotors[0].position(deg));

      double currtrav=((currentleft-startleft)+(currentright-startright))/2.0;
      double power=pid_forward.calculatepower(currtrav);
      Right_Power=power;
      Left_Power=power;
      
      bot.movecntrl(leftmotors,Left_Power);
      bot.movecntrl(rightmotors,Right_Power);
      wait(20,msec);
    }

    bot.movecntrl(leftmotors,0);
    bot.movecntrl(rightmotors,0);
}

void turnconstrainangle(double& angle)
{
    while (angle > M_PI) angle -= 2*M_PI;
    while (angle < -M_PI) angle += 2*M_PI;
}

void pidTurn(double target)
{
    double startheading=Odom.GetAngle();
    target*=M_PI/180;
    turnconstrainangle(target);
    turnconstrainangle(startheading);
    double currentheading=0;

    pid_turn.reset();
    pid_turn.SetTarget(target);

    while(!pid_turn.Arrived())
    {
      currentheading=Odom.GetAngle();
      double currturn=currentheading-startheading;
      turnconstrainangle(currturn);

      double power=pid_turn.calculatepower(currturn);
      Right_Power=-power; //opposite power so it turns
      Left_Power=power;

      bot.movecntrl(leftmotors,Left_Power);
      bot.movecntrl(rightmotors,Right_Power);
      wait(20,msec);
    }

    bot.movecntrl(leftmotors,0);
    bot.movecntrl(rightmotors,0);
}

void awpautonrightred()
{
  tonguemech.close(); //put down tonguemech
  pidForward(24); //forward 1 tile
  pidTurn(-90); //face loader
  pidForward(2); //go into loader
  intakeMotor.spinFor(1,vex::timeUnits::sec); //intake for certain amount of time (just use movemotor group on this)
  pidForward(1); //go into loader
  intakeMotor.spinFor(1,vex::timeUnits::sec); //intake for certain amount of time (just use movemotor group on this)

  pidForward(-24); //back 1 tile so aligner hits long goal
  tonguemech.open();//put up tonguemech
  intakeMotor.spinFor(2,vex::timeUnits::sec); //outtake on top for certain amount of time
  hoodMotor.spinFor(2,vex::timeUnits::sec); //outtake on top for certain amount of time

  pidTurn(-90); //turn to the dihhs
  intakeMotor.spin(vex::directionType::fwd,128,vex::voltageUnits::mV); //start intake
  pidForward(72); //collect all
  intakeMotor.spin(vex::directionType::fwd,0,vex::voltageUnits::mV); //start intake

  pidTurn(45); //butt face mid goal
  rubberband.open(); //open middle scoring
  intakeMotor.spinFor(2,vex::timeUnits::sec); //outtake mid for 3 ball time
  rubberband.close(); //close mid scoring

  tonguemech.close();//tonguemech down
  pidForward(72); //go to 2nd loader
  pidForward(2); //go into loader
  intakeMotor.spinFor(1,vex::timeUnits::sec); //intake for certain amount of time (just use movemotor group on this)
  pidForward(1); //go into loader
  intakeMotor.spinFor(1,vex::timeUnits::sec); //intake for certain amount of time (just use movemotor group on this)

  pidForward(-24); //to 2nd long goal
  tonguemech.open();//put up tonguemech
  intakeMotor.spinFor(2,vex::timeUnits::sec); //outtake on top for certain amount of time
  hoodMotor.spinFor(2,vex::timeUnits::sec); //outtake on top for certain amount of time
}

void awpautonleftred()
{
  tonguemech.close(); //put down tonguemech
  pidForward(24); //forward 1 tile
  pidTurn(90); //face loader
  pidForward(2); //go into loader
  intakeMotor.spinFor(1,vex::timeUnits::sec); //intake for certain amount of time (just use movemotor group on this)
  pidForward(1); //go into loader
  intakeMotor.spinFor(1,vex::timeUnits::sec); //intake for certain amount of time (just use movemotor group on this)

  pidForward(-24); //back 1 tile so aligner hits long goal
  tonguemech.open();//put up tonguemech
  intakeMotor.spinFor(2,vex::timeUnits::sec); //outtake on top for certain amount of time
  hoodMotor.spinFor(2,vex::timeUnits::sec); //outtake on top for certain amount of time

  pidTurn(-90); //turn to the dihhs
  intakeMotor.spin(vex::directionType::fwd,128,vex::voltageUnits::mV); //start intake
  pidForward(72); //collect all
  intakeMotor.spin(vex::directionType::fwd,0,vex::voltageUnits::mV); //start intake

  pidTurn(-45); //butt face mid goal
  rubberband.open(); //open middle scoring
  intakeMotor.spinFor(2,vex::timeUnits::sec); //outtake mid for 3 ball time
  rubberband.close(); //close mid scoring

  tonguemech.close();//tonguemech down
  pidForward(72); //go to 2nd loader
  pidForward(2); //go into loader
  intakeMotor.spinFor(1,vex::timeUnits::sec); //intake for certain amount of time (just use movemotor group on this)
  pidForward(1); //go into loader
  intakeMotor.spinFor(1,vex::timeUnits::sec); //intake for certain amount of time (just use movemotor group on this)

  pidForward(-24); //to 2nd long goal
  tonguemech.open();//put up tonguemech
  intakeMotor.spinFor(2,vex::timeUnits::sec); //outtake on top for certain amount of time
  hoodMotor.spinFor(2,vex::timeUnits::sec); //outtake on top for certain amount of time
}

void awpautonleftblue()
{
  tonguemech.close(); //put down tonguemech
  pidForward(24); //forward 1 tile
  pidTurn(-90); //face loader
  pidForward(2); //go into loader
  intakeMotor.spinFor(1,vex::timeUnits::sec); //intake for certain amount of time (just use movemotor group on this)
  pidForward(1); //go into loader
  intakeMotor.spinFor(1,vex::timeUnits::sec); //intake for certain amount of time (just use movemotor group on this)

  pidForward(-24); //back 1 tile so aligner hits long goal
  tonguemech.open();//put up tonguemech
  intakeMotor.spinFor(2,vex::timeUnits::sec); //outtake on top for certain amount of time
  hoodMotor.spinFor(2,vex::timeUnits::sec); //outtake on top for certain amount of time

  pidTurn(90); //turn to the dihhs
  intakeMotor.spin(vex::directionType::fwd,128,vex::voltageUnits::mV); //start intake
  pidForward(72); //collect all
  intakeMotor.spin(vex::directionType::fwd,0,vex::voltageUnits::mV); //start intake

  pidTurn(-45); //butt face mid goal
  rubberband.open(); //open middle scoring
  intakeMotor.spinFor(2,vex::timeUnits::sec); //outtake mid for 3 ball time 
  rubberband.close(); //close mid scoring

  tonguemech.close();//tonguemech down
  pidForward(72); //go to 2nd loader
  pidForward(2); //go into loader
  intakeMotor.spinFor(1,vex::timeUnits::sec); //intake for certain amount of time (just use movemotor group on this)
  pidForward(1); //go into loader
  intakeMotor.spinFor(1,vex::timeUnits::sec); //intake for certain amount of time (just use movemotor group on this)

  pidForward(-24); //to 2nd long goal
  tonguemech.open();//put up tonguemech
  intakeMotor.spinFor(2,vex::timeUnits::sec); //outtake on top for certain amount of time
  hoodMotor.spinFor(2,vex::timeUnits::sec); //outtake on top for certain amount of time
}

void awpautonrightblue()
{
  tonguemech.close(); //put down tonguemech
  pidForward(24); //forward 1 tile
  pidTurn(-90); //face loader
  pidForward(2); //go into loader
  intakeMotor.spinFor(1,vex::timeUnits::sec); //intake for certain amount of time (just use movemotor group on this)
  pidForward(1); //go into loader
  intakeMotor.spinFor(1,vex::timeUnits::sec); //intake for certain amount of time (just use movemotor group on this)

  pidForward(-24); //back 1 tile so aligner hits long goal
  tonguemech.open();//put up tonguemech
  intakeMotor.spinFor(2,vex::timeUnits::sec); //outtake on top for certain amount of time
  hoodMotor.spinFor(2,vex::timeUnits::sec); //outtake on top for certain amount of time

  pidTurn(-90); //turn to the dihhs
  intakeMotor.spin(vex::directionType::fwd,128,vex::voltageUnits::mV); //start intake
  pidForward(72); //collect all
  intakeMotor.spin(vex::directionType::fwd,0,vex::voltageUnits::mV); //start intake

  pidTurn(45); //butt face mid goal
  rubberband.open(); //open middle scoring
  intakeMotor.spinFor(2,vex::timeUnits::sec); //outtake mid for 3 ball time

  tonguemech.close();//tonguemech down
  pidForward(72); //go to 2nd loader
  pidForward(2); //go into loader
  intakeMotor.spinFor(1,vex::timeUnits::sec); //intake for certain amount of time (just use movemotor group on this)
  pidForward(1); //go into loader
  intakeMotor.spinFor(1,vex::timeUnits::sec); //intake for certain amount of time (just use movemotor group on this)

  pidForward(-24); //to 2nd long goal
  tonguemech.open();//put up tonguemech
  intakeMotor.spinFor(2,vex::timeUnits::sec); //outtake on top for certain amount of time
  hoodMotor.spinFor(2,vex::timeUnits::sec); //outtake on top for certain amount of time
}

void longgoalrushrightblue()
{
  tonguemech.close(); //put down tonguemech
  pidForward(24); //forward 1 tile
  pidTurn(-90); //face loader
  pidForward(2); //go into loader
  intakeMotor.spinFor(1,vex::timeUnits::sec); //intake for certain amount of time (just use movemotor group on this)
  pidForward(1); //go into loader
  intakeMotor.spinFor(1,vex::timeUnits::sec); //intake for certain amount of time (just use movemotor group on this)

  pidForward(-24); //back 1 tile so aligner hits long goal
  tonguemech.open();//put up tonguemech
  intakeMotor.spinFor(2,vex::timeUnits::sec); //outtake on top for certain amount of time
  hoodMotor.spinFor(2,vex::timeUnits::sec); //outtake on top for certain amount of time
}