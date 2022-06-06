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

#ifndef __CLARION_INTERFACE_THREAD_H__
#define __CLARION_INTERFACE_THREAD_H__

#include <yarp/os/Vocab.h>
#include <yarp/os/BufferedPort.h>
#include <yarp/os/ResourceFinder.h>
#include <yarp/os/RFModule.h>
#include <yarp/os/Network.h>
#include <yarp/os/Log.h>
#include <yarp/os/RateThread.h>
#include <yarp/os/RpcClient.h>
#include <yarp/os/LogStream.h>

#include <vector>
#include <mutex>
#include <sstream>
#include <iostream>
#include <cstring>
#include <utility>


/* potentially useful libraries:

#include <yarp/sig/Image.h>
#include <yarp/cv/Cv.h>
#include <yarp/os/Stamp.h>

#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>

*/

class clarionIntThread: public yarp::os::RateThread 
{
private:
    std::string             moduleName;

    // ports
    yarp::os::RpcClient         ARErpc;


    yarp::os::BufferedPort<yarp::os::Bottle>    leftArmStatePort;
    yarp::os::BufferedPort<yarp::os::Bottle>    rightArmStatePort;

    yarp::os::Bottle        *leftStateBottle;
    yarp::os::Bottle        *rightStateBottle;

public:
    bool                    closing;
    bool                    actionRunning; // this indicates if an action is running or not, so we know to read currents
    

    clarionIntThread(const std::string &_moduleName, const double _period);

    bool openPorts();
    virtual void close();
    virtual void interrupt();
    virtual bool threadInit();
    virtual void threadRelease();
    virtual void run();

    // rpc methods
    bool point(double x_pos, double y_pos, double z_pos);

};

#endif