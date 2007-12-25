/* 

                          Firewall Builder

                 Copyright (C) 2000 NetCitadel, LLC

  Author:  Vadim Kurland     vadim@vk.crocodile.org

  $Id: Library.cpp 975 2006-09-10 22:40:37Z vkurland $


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

#include <fwbuilder/FWObject.h>
#include <fwbuilder/Library.h>
#include <fwbuilder/XMLTools.h>

using namespace libfwbuilder;

const char *Library::TYPENAME={"Library"};

Library::Library()  {}
Library::Library(const FWObject *root,bool prepopulate) :
    FWObject(root,prepopulate) {}

Library::~Library() 
{
}

bool  Library::validateChild(FWObject *o)
{ 
    return true;   // anything goes
}

void Library::fromXML(xmlNodePtr root) throw(FWException)
{
    const char *n=FROMXMLCAST(xmlGetProp(root,TOXMLCAST("color")));
    if(n!=NULL)  // color is not a mandatory attribute
    {
        setStr("color", n);
        FREEXMLBUFF(n);
    }
    FWObject::fromXML(root);
}




