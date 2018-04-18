//
// Author: Emin Ilker Cetinbas (niw3_at_yahoo_d0t_com)
// Copyright (C) 2005 Emin Ilker Cetinbas
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>.
//

#include "inet/mobility/single/LinearMobility.h"
#include "inet/common/INETMath.h"

namespace inet {

Define_Module(LinearMobility);

LinearMobility::LinearMobility()
{
    speed = 0;
    angle = deg(0);
    acceleration = 0;
}

void LinearMobility::initialize(int stage)
{
    MovingMobilityBase::initialize(stage);

    EV_TRACE << "initializing LinearMobility stage " << stage << endl;
    if (stage == INITSTAGE_LOCAL) {
        speed = par("speed");
        angle = deg(fmod((double)par("angle"), 360));
        acceleration = par("acceleration");
        stationary = (speed == 0) && (acceleration == 0.0);
    }
//    updateDisplayString();
}

void LinearMobility::move()
{
    Coord direction(cos(rad(angle).get()), sin(rad(angle).get()));
    lastVelocity = direction * speed;
    double elapsedTime = (simTime() - lastUpdate).dbl();
    lastPosition += lastVelocity * elapsedTime;

    // do something if we reach the wall
    Coord dummy;
    handleIfOutside(REFLECT, dummy, dummy, angle);

    // accelerate
    speed += acceleration * elapsedTime;
    if (speed <= 0) {
        speed = 0;
        stationary = true;
    }
}

void LinearMobility::updateDisplayString()
{
    cDisplayString& dispStr = this->getDisplayString();
    std::string str;
    str.append(this->getComponentType()->getName());
    str.append("\npos");
    str.append(this->lastPosition.str());
//    EV_DETAIL << "XXX" << str << endl;
    dispStr.setTagArg("t", 0, str.c_str());
//    DirectiveResolver directiveResolver(this);
//    dispStr.setTagArg("t", 0, format.formatString(&directiveResolver));
}

} // namespace inet

