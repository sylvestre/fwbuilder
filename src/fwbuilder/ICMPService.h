/* 

                          Firewall Builder

                 Copyright (C) 2000 NetCitadel, LLC

  Author:  Vadim Kurland     vadim@vk.crocodile.org

  $Id: ICMPService.h 975 2006-09-10 22:40:37Z vkurland $


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


#ifndef __ICMPSERVICE_HH_FLAG__
#define __ICMPSERVICE_HH_FLAG__

#include <fwbuilder/Service.h>

namespace libfwbuilder
{

class ICMPService : public Service
{

private:

public:

    ICMPService();
    ICMPService(const FWObject *root,bool prepopulate);
    virtual ~ICMPService();

    virtual void fromXML(xmlNodePtr parent) throw(FWException);

    DECLARE_FWOBJECT_SUBTYPE(ICMPService);

    virtual std::string getProtocolName();
    virtual int    getProtocolNumber();
};

}

#endif




