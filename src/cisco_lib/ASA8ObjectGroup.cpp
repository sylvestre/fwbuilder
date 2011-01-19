/* 

                          Firewall Builder

                 Copyright (C) 2011 NetCitadel, LLC

  Author:  Vadim Kurland     vadim@fwbuilder.org

  $Id$

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

#include "config.h"

#include "ASA8ObjectGroup.h"
#include "NamedObjectsAndGroupsSupport.h"

#include "fwbuilder/Address.h"
#include "fwbuilder/Network.h"
#include "fwbuilder/IPService.h"
#include "fwbuilder/ICMPService.h"
#include "fwbuilder/TCPService.h"
#include "fwbuilder/UDPService.h"
#include "fwbuilder/CustomService.h"

#include <iostream>
#include <sstream>

using namespace libfwbuilder;
using namespace std;
using namespace fwcompiler;


const char *ASA8ObjectGroup::TYPENAME={"ASA8ObjectGroup"};


string ASA8ObjectGroup::groupMemberToString(
    FWObject *obj, NamedObjectManager *named_object_manager)
    throw(libfwbuilder::FWException)
{
    NamedObject *named_object =
        named_object_manager->named_objects[obj->getId()];

    if (named_object)
    {
        return named_object->getCommandWhenObjectGroupMember(
            named_object_manager->fw).toStdString();
    }
        
    return PIXObjectGroup::groupMemberToString(obj, named_object_manager);
}

string ASA8ObjectGroup::getObjectGroupClass()
{
    switch (this->getObjectGroupType()) 
    {
    case MIXED_SERVICE:  return "service";;
    default: return PIXObjectGroup::getObjectGroupClass();
    }
}

