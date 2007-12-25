/* 

                          Firewall Builder

                 Copyright (C) 2000 NetCitadel, LLC

  Author:  Vadim Kurland     vadim@vk.crocodile.org

  $Id: Network.h 975 2006-09-10 22:40:37Z vkurland $


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

#ifndef __NETWORK_HH_FLAG__
#define __NETWORK_HH_FLAG__

#include <fwbuilder/Address.h>
#include <fwbuilder/IPAddress.h>

namespace libfwbuilder
{

class Network : public Address
{
    private:
    
    IPAddress address;
    Netmask   netmask;
    
    public:
    
    Network();
    Network(const FWObject *root,bool prepopulate);
    Network(Network &);
    Network(const std::string &);

    virtual IPAddress getAddress() const { return address; }
    virtual Netmask   getNetmask() const { return netmask; }
    virtual guint32   dimension()  const;

    virtual void setAddress(const IPAddress &a)    { address=a;  }
    virtual void setNetmask(const Netmask   &nm)   { netmask=nm; }
    virtual void setAddress(const std::string &a)  { address=IPAddress(a); }
    virtual void setNetmask(const std::string &nm) { netmask=Netmask(nm);  }

    bool isValidRoutingNet() const;


    void setData(IPNetwork &n) { address=n.getAddress(); netmask=n.getNetmask(); }
    
    virtual FWObject& shallowDuplicate(const FWObject *obj, bool preserve_id = true) throw(FWException);
    
    virtual void       fromXML (xmlNodePtr parent) throw(FWException);
    virtual xmlNodePtr toXML   (xmlNodePtr xml_parent_node) throw(FWException);
    Network& operator=(const std::string &s) throw(FWException);
    
    DECLARE_FWOBJECT_SUBTYPE(Network);
    
};

}

#endif // __NETWORK_HH_FLAG__




