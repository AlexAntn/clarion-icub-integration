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

    // open ports
    if (!openPorts())
    {
        yError() << "ports failed to open.";
        return false;
    }

    return true;
}

bool clarionInterface::attach(yarp::os::RpcServer &source)
{
    return this->yarp().attachAsServer(source);
}

bool clarionInterface::openPorts()
{
    bool ok;

    std::string portName;
    portName = "/" + moduleName + "/blobs:i";
    ok = blobPort.open(portName);

    portName = "/" + moduleName + "/segmented:i";
    ok = ok && segmentedPort.open(portName);

    return ok;
}

bool clarionInterface::interruptModule()
{
    handlerPort.interrupt();
    blobPort.interrupt();
    segmentedPort.interrupt();
    thread->askToStop();

    return true;
}

bool clarionInterface::close()
{
    yInfo() << "starting shutdown procedure";
    blobPort.close();
    segmentedPort.close();

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
    // Get visual data from lbpExtract/segmented
    segmentedImg = segmentedPort.read(false);
    if(segmentedImg != NULL)
    {
        yInfo() << "we got an image";
    }

    // get bottle data from lbpExtract/blobs
    blobBottle = blobPort.read(false);
    if(blobBottle != NULL)
    {
        yInfo() << "we got something: " << blobBottle->toString();
    }

    // Recognize shapes/colors

    // if we have OPC, update it? If not, and for now, internal memory


    return !closing;
}

bool clarionInterface::point(double x_pos, double y_pos, double z_pos)
{
    // should interact with ARE to point at something
    yInfo() << "asking to go to coordinates: " << x_pos << y_pos << z_pos;
    thread->point(x_pos, y_pos, z_pos);
    return true;
}