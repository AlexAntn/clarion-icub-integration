/*
 * Copyright (C) 2022 iCub Facility - Istituto Italiano di Tecnologia
 * Author: Alexandre Antunes
 * email:  alexandre.gomespereira@iit.it
 * Permission is granted to copy, distribute, and/or modify this program
 * under the terms of the GNU General Public License, version 2 or any
 * later version published by the Free Software Foundation.
 *
 * A copy of the license can be found at
 * http://www.robotcub.org/icub/license/gpl.txt
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
 * Public License for more details
 */

 #include <clarionInterfaceThread.h>

 clarionIntThread::clarionIntThread(const std::string &_moduleName,
                                                const double _period)
                                                : moduleName(_moduleName),
                                                  RateThread(int(_period*1000.0))
{
}

bool clarionIntThread::openPorts()
{
    bool ok;


    // ports to obtain currents
    // left arm
    std::string portName = "/" + moduleName + "/left_arm_state:i";
    ok = leftArmStatePort.open(portName);
    // right arm
    portName = "/" + moduleName + "/right_arm_state:i";
    ok = ok && rightArmStatePort.open(portName);
    // ARE rpc
    portName = "/" + moduleName + "/are_cmd:i";
    ok = ok && ARErpc.open(portName);

    return ok;
}

void clarionIntThread::threadRelease()
{
    std::cout << "thread terminated" << std::endl;
}

void clarionIntThread::close()
{
    yInfo() << "closing module";
    leftArmStatePort.close();
    rightArmStatePort.close();
    ARErpc.close();

    closing = true;

    // ports to close


    yarp::os::Time::delay(0.1); // small delay to allow for module to close properly
}

void clarionIntThread::interrupt()
{
    yInfo() << "interrupting ports";
    leftArmStatePort.interrupt();
    rightArmStatePort.interrupt();
    ARErpc.interrupt();

    // ports to interrupt
}

bool clarionIntThread::threadInit()
{
    closing = false;
    actionRunning = false;

    if (!openPorts())
    {
        yError() << "problem opening ports";
        return false;
    }
    return true;
}

bool clarionIntThread::point(double x_pos, double y_pos, double z_pos)
{
    // should interact with ARE to point at something
    actionRunning = true;
    //yarp::os::Time::delay(2);
    // instead of the delay, we send command to ARE
    yarp::os::Bottle cmd, reply;
    cmd.addString("point");
    yarp::os::Bottle &coordBottle = cmd.addList();
    coordBottle.addFloat32(x_pos);
    coordBottle.addFloat32(y_pos);
    coordBottle.addFloat32(z_pos);
    yInfo() << "bottle is: " << cmd.toString();
    ARErpc.write(cmd, reply);

    actionRunning = false;
    return true;
}

void clarionIntThread::run()
{
    // in this thread we will collect data during action execution
    // e.g.: motor currents
    if(actionRunning)
    {
        leftStateBottle = leftArmStatePort.read(false);
        if(leftStateBottle != NULL)
        {
            yInfo() << "we got a left state";
        }
        rightStateBottle = rightArmStatePort.read(false);
        if(rightStateBottle != NULL)
        {
            yInfo() << "we got a right state";
        }
    }

    //yInfo() << "Hello! I'm running!";
    return;
}
