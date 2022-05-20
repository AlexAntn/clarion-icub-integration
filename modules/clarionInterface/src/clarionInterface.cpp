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

#include <clarionInterface.h>

bool clarionInterface::configure(yarp::os::ResourceFinder &rf)
{
    //module parameters
    moduleName = rf.check("name", yarp::os::Value("clarionInterface")).asString();
    setName(moduleName.c_str());

    //rpc configuration
    handlerPortName = "/" + moduleName + "/rpc";
    handlerPort.open(handlerPortName.c_str());
    attach(handlerPort);

    // module variables
    closing = false;

    threadPeriod = 0.033;

    thread = new clarionIntThread(moduleName, threadPeriod);

    // check if thread started properly
    if (!thread->start())
    {
        delete thread;
        return false;
    }

    return true;
}

bool clarionInterface::attach(yarp::os::RpcServer &source)
{
    return this->yarp().attachAsServer(source);
}

bool clarionInterface::interruptModule()
{
    handlerPort.interrupt();
    thread->askToStop();

    return true;
}

bool clarionInterface::close()
{
    yInfo() << "starting shutdown procedure";
    thread->interrupt();
    thread->close();
    thread->stop();
    if (thread) delete thread;

    handlerPort.close();
    yInfo() << "module terminated";
    return true;
}

bool clarionInterface::quit()
{
    closing = true;
    return true;
}

double clarionInterface::getPeriod()
{
    return 0.0;
}

bool clarionInterface::updateModule()
{

    return !closing;
}