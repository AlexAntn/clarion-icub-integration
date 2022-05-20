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

#ifndef __CLARION_INTERFACE_MODULE_H__
#define __CLARION_INTERFACE_MODULE_H__

#include <yarp/os/Vocab.h>
#include <yarp/os/BufferedPort.h>
#include <yarp/os/ResourceFinder.h>
#include <yarp/os/RFModule.h>
#include <yarp/os/Network.h>
#include <yarp/os/Log.h>
#include <yarp/os/RpcClient.h>
#include <yarp/os/LogStream.h>

#include <vector>
#include <mutex>
#include <sstream>
#include <iostream>
#include <cstring>
#include <utility>

#include <clarionInterfaceThread.h>
#include "clarionInterface_IDLserver.h"

/* potentially useful libraries:

#include <yarp/sig/Image.h>
#include <yarp/cv/Cv.h>
#include <yarp/os/Stamp.h>

#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>

*/

class clarionInterface : public yarp::os::RFModule, public clarionInterface_IDLserver
{
    yarp::os::ResourceFinder    *rf;
    yarp::os::RpcServer         handlerPort;
    std::string                 handlerPortName;
    
    // ports


    // other variables
    bool                        closing;
    std::string                 moduleName;

    // thread
    clarionIntThread            *thread;
    double                      threadPeriod;

public:


    bool            attach(yarp::os::RpcServer &source) override;
    bool            configure(yarp::os::ResourceFinder &rf) override;

    bool            interruptModule() override;
    bool            close() override;
    bool            quit() override;
    
    double          getPeriod() override;
    bool            updateModule() override;

    // rpc calls
};

#endif