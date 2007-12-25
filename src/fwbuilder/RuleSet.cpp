/* 

                          Firewall Builder

                 Copyright (C) 2000 NetCitadel, LLC

  Author:  Vadim Kurland     vadim@vk.crocodile.org

  $Id: RuleSet.cpp 1045 2007-08-30 04:47:19Z vk $


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

#include <fwbuilder/FWObjectDatabase.h>
#include <fwbuilder/RuleSet.h>
#include <fwbuilder/FWOptions.h>
#include <fwbuilder/XMLTools.h>

using namespace std;
using namespace libfwbuilder;
 
const char *RuleSet::TYPENAME={"Ruleset"};

RuleSet::RuleSet()
{
    setName("RuleSet");
}

RuleSet::RuleSet(const FWObject*,bool)
{
    setName("RuleSet");
}

RuleSet::~RuleSet() {}

Rule* RuleSet::insertRuleAtTop() 
{
    Rule *r=createRule();
    r->setPosition( 0 );
    insert(begin(), r);
    _adopt(r);
    renumberRules();
    return(r);
}

Rule* RuleSet::insertRuleBefore(int rule_n) 
{
    Rule *old_rule=getRuleByNum(rule_n);
    Rule *r=createRule();
    if (old_rule==NULL) add(r);
    else                insert_before(old_rule,r);
    renumberRules();
    return(r);
}

Rule* RuleSet::appendRuleAtBottom() 
{
    Rule *r=createRule();
    add( r );            // FWObject::add adds to the end of the list
    renumberRules();
    return(r);
}

Rule* RuleSet::appendRuleAfter(int rule_n) 
{
    Rule *old_rule=getRuleByNum(rule_n);
    Rule *r=createRule();
    if (old_rule==NULL) add(r);
    else                insert_after(old_rule,r);
    renumberRules();
    return(r);
}

bool RuleSet::deleteRule(int rule_n) 
{
    return deleteRule( getRuleByNum(rule_n) );
}

bool RuleSet::deleteRule(Rule *r) 
{
    if (r!=NULL) {
	remove(r,false);   // do not put in "Deleted objects"
	renumberRules();
	return(true);
    }
    return(false);
}

bool RuleSet::moveRuleUp(int rule_n) 
{
    if (rule_n==0) return(false);

    FWObject* o   =getRuleByNum( rule_n );
    FWObject* prev=getRuleByNum( rule_n-1 );

    swapObjects(prev,o);
    renumberRules();
    return(true);
}

bool RuleSet::moveRuleDown(int rule_n) 
{
    if (rule_n > (getRuleSetSize()-2) ) return(false);

    FWObject* o   =getRuleByNum( rule_n );
    FWObject* next=getRuleByNum( rule_n+1 );

    swapObjects(o,next);
    renumberRules();
    return(true);
}

bool RuleSet::disableRule(int rule_n)
{
    FWObject* o   =getRuleByNum( rule_n );

    if (o) {
  	(Rule::cast(o))->disable();
  	return true;
    }
    return false;
}

bool RuleSet::enableRule(int rule_n)
{
    FWObject* o   =getRuleByNum( rule_n );

    if (o) {
  	(Rule::cast(o))->enable();
  	return true;
    }
    return false;
}

bool  RuleSet::isRuleDisabled(int rule_n)
{
    FWObject* o   =getRuleByNum( rule_n );

    if (o)
  	return((Rule::cast(o))->isDisabled());
    return false;
}


/*
 * Rule number src_rule_n moves right above rule number dst_rule_n
 */
bool RuleSet::moveRule(int src_rule_n, int dst_rule_n) 
{
      FWObject* src =getRuleByNum( src_rule_n );
      FWObject* dst =getRuleByNum( dst_rule_n );

      if (src!=NULL &&  dst!=NULL && src!=dst ) {

  	FWObject *o;
  	list<FWObject*>::iterator m, m1, m2;
  	for (m=begin(); m!=end(); ++m) {
  	    if ( (o=(*m))!=NULL ) {
  		if ( o==src ) m1=m;
  		if ( o==dst ) m2=m;
  	    }
  	}
  	if ( (*m1)!=NULL && (*m2)!=NULL ) {
  	    erase(m1);
  	    insert(m2,src);
  	}
  	renumberRules();
  	return(true);
      }
    return(false);
}

void RuleSet::renumberRules()
{
    FWObject *o;
    list<FWObject*>::iterator m;
    int rn;

    for (rn=0,m=begin(); m!=end(); ++rn,++m) {
	if ( (o=(*m))!=NULL && Rule::cast(o)!=NULL )   
	    (Rule::cast(o))->setPosition( rn );
    }
}

Rule* RuleSet::getRuleByNum(int n)
{
    for(list<FWObject*>::iterator m=begin(); m!=end(); ++m) 
    {
        FWObject *o;
	if ( (o=(*m))!=NULL ) 
        {
	    Rule *r = Rule::cast(o);
	    if (r && r->getPosition()==n) 
                return r;
	}
    }
    return NULL;
}

int RuleSet::getRuleSetSize()
{
    return getChildrenCount();
}


