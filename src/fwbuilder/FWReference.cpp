/* 

                          Firewall Builder

                 Copyright (C) 2000 NetCitadel, LLC

  Author:  Vadim Kurland     vadim@vk.crocodile.org

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

#include <fwbuilder/libfwbuilder-config.h>

#include <fwbuilder/FWReference.h>
#include <fwbuilder/FWObjectDatabase.h>
#include <fwbuilder/XMLTools.h>

#include <assert.h>

using namespace libfwbuilder;
using namespace std;

const char *FWReference::TYPENAME={"Ref"};


/*
FWReference::FWReference(FWObject *p)
{
    setPointer(p);
}
*/


FWReference::FWReference()
{
    setPointer(NULL);
}

FWReference::FWReference(const FWObject *root,bool prepopulate) : FWObject(root,prepopulate)
{
    setPointer(NULL);
}

FWReference::~FWReference()  {}


void FWReference::fromXML(xmlNodePtr root)  throw(FWException)
{
    assert(root!=NULL);
    FWObject::fromXML(root);

    const char *n = FROMXMLCAST(xmlGetProp(root, TOXMLCAST("ref")));
    assert(n!=NULL);
    str_ref = n;
    //setInt("ref", n);
    // if object with id str_ref has not been loaded yet, 
    // FWObjectDatabase::getIntId returns -1.
    int_ref = FWObjectDatabase::getIntId(str_ref);
    FREEXMLBUFF(n);
}

// Note that XML elements represented by FWReference have only one
// attribute "ref" and no value
xmlNodePtr FWReference::toXML(xmlNodePtr parent) throw(FWException)
{
    xmlNodePtr me = xmlNewChild(parent, NULL, xml_name.empty()?STRTOXMLCAST(getTypeName()):STRTOXMLCAST(xml_name), NULL);

    if (int_ref == -1 && !str_ref.empty())
        int_ref = FWObjectDatabase::getIntId(str_ref);

    if (int_ref > -1 && str_ref.empty())
        str_ref = FWObjectDatabase::getStringId(int_ref);

    xmlAttrPtr pr = xmlNewProp(me, 
                               TOXMLCAST("ref"),
                               STRTOXMLCAST(str_ref));
    xmlAddRef(NULL, parent->doc, STRTOXMLCAST(str_ref), pr);

    return me;
}

FWObject& FWReference::shallowDuplicate(const FWObject *_other,
                                        bool) throw(FWException)
{
    const FWReference *other = FWReference::constcast(_other);
    int_ref = other->int_ref;
    str_ref = other->str_ref;
    return *this;
}

void FWReference::add(FWObject*)
{
    throw std::string("Can't add to a reference !");
}

void FWReference::setPointer(FWObject *p)
{
    if(p) setPointerId(p->getId());
    else
    {
        int_ref = -1;
        str_ref = "";
    }
}

void FWReference::setPointerId(int ref_id)
{
    //setInt("ref" , ref_id );
    int_ref = ref_id;
    // if object with id ref_id has not been loaded into database
    // yet, FWObjectDatabase::getStringId returns empty string.
    // This works as postponed initialization.
    // We really need string id only in toXML.
    str_ref = FWObjectDatabase::getStringId(int_ref);
}

FWObject *FWReference::getPointer()
{
    return getRoot()->findInIndex( getPointerId() );
}

int FWReference::getPointerId()
{
    // postponed initialization happens now
    if (int_ref==-1 && !str_ref.empty())
        int_ref = FWObjectDatabase::getIntId(str_ref);
        
    return int_ref;
    //return getInt("ref");
}


#ifdef _REF_DUMP_
void   FWReference::dump(int offset)
{
    FWObject::dump(offset);

    FWObject* ptr=getPointer();

    cout << string(offset,' ') << "Pointer: " << ptr << endl;
    if (ptr) {
	cout<< string(offset,' ') << "Ptr.name: " << ptr->getName() <<endl;
	cout<< string(offset,' ') << "Ptr.id: "   << ptr->getId() <<endl;
    }
}
#endif
