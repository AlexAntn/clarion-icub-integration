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
    return true;
}

void clarionIntThread::threadRelease()
{
    std::cout << "thread terminated" << std::endl;
}

void clarionIntThread::close()
{
    yInfo() << "closing module";
    closing = true;

    // ports to close


    yarp::os::Time::delay(0.1); // small delay to allow for module to close properly
}

void clarionIntThread::interrupt()
{
    yInfo() << "interrupting ports";

    // ports to interrupt
}

bool clarionIntThread::threadInit()
{
    closing = false;

    if (!openPorts())
    {
        yError() << "problem opening ports";
        return false;
    }
    return true;
}

void clarionIntThread::run()
{
    //yInfo() << "Hello! I'm running!";
    return;
}
