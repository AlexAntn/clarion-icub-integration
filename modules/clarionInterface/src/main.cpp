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


/* The plan for this module is to act as an interface between the world and clarion.
 * As such, it will have to communicate with 4 main modules:
 * - Clarion
 * - ActionsRenderingEngine
 * - lbpExtract (for the vision stuff)
 * - motors (for the current)
 * 
 * Communication with ARE will be done on the clarionInterfaceThread. We can also use this
 * thread to obtain the currents from the motors, this way we only interface with motors there.
 * The vision stuff we can do in the clarionInterface module, in the updateModule function.
 */


#include <clarionInterface.h>

/********************************************************/
int main(int argc, char *argv[])
{
    yarp::os::Network::init();

    yarp::os::Network yarp;
    if (!yarp.checkNetwork())
    {
        yError() << "YARP server not available!";
        return 1;
    }

    clarionInterface module;
    yarp::os::ResourceFinder rf;

    rf.setDefaultContext("clarionInterface");
    rf.setDefaultConfigFile("config.ini");
    rf.setDefault("name","clarionInterface");
    rf.configure(argc,argv);

    return module.runModule(rf);
}