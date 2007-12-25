/* 

                          Firewall Builder

                 Copyright (C) 2000 NetCitadel, LLC

  Author:  Vadim Kurland     vadim@vk.crocodile.org

  $Id: FWIntervalReference.cpp 975 2006-09-10 22:40:37Z vkurland $


  This program is free software which we release under the GNU General Public
  License. You may redistribute and/or modify this program under the terms
  of that license as published by the Free Software Foundation; either
  version 2 of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
 
  To get a copy of the GNU General Public License, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

*/

#include <fwbuilder/libfwbuilder-config.h>

#include <fwbuilder/FWIntervalReference.h>
#include <fwbuilder/FWObjectDatabase.h>
#include <fwbuilder/XMLTools.h>

using namespace libfwbuilder;

const char *FWIntervalReference::TYPENAME={"IntervalRef"};


//FWIntervalReference::FWIntervalReference(Interval *p):FWReference(p){}
//FWIntervalReference::FWIntervalReference(IntervalGroup *p):FWReference(p){}

FWIntervalReference::FWIntervalReference():FWReference(){}
FWIntervalReference::FWIntervalReference(const FWObject *root,bool prepopulate) :
    FWReference(root,prepopulate) {} 

void FWIntervalReference::setPointer(Interval *p)
{
    //TODO: add check if it is right type.
    FWReference::setPointer(p);
}

void FWIntervalReference::setPointer(IntervalGroup *p)
{
    //TODO: add check if it is right type.
    FWReference::setPointer(p);
}







