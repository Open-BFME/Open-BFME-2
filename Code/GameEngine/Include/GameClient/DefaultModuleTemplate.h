/* Target facts (RVAs): DefaultModuleTemplate<1>'s constructors 0x003A9732 and 0x003A622A install VA 0x00C1BA70 at
+0, the folded CategoryModuleInfo table VA 0x00C1C780 at +4 and VA 0x00C1BA80 at +8.
Table 0x0081BA70: the 0x8C-stride vector deleting destructor 0x003A628B, two pure calls and
writeINI 0x0055B735. Table 0x0081BA80: the -8 thunk 0x003A963D, then DefaultAlphaModuleInfo's
LoadPostProcess, GetSnapshotName and DoXfer.
DefaultModuleTemplate<2> (constructors 0x003A98A9 and 0x003A79A5): table 0x0081BCF0 holds the 0x70-stride
deleting destructor 0x003A7A06, two pure calls and writeINI 0x0055FB37; table 0x0081BD00 the -8 thunk
0x003A96B5 and DefaultUpdateModuleInfo's three Snapshot slots.
DefaultModuleTemplate<0> (constructors 0x003A9789 and 0x003A638D): table 0x0081BAA0 holds the 0x98-stride
deleting destructor 0x003A63EE, two pure calls and writeINI 0x0055C263; table 0x0081BAB0 the -8 thunk
0x003A969D and DefaultColorModuleInfo's three Snapshot slots.
DefaultModuleTemplate<3> (constructors 0x003A9852 and 0x003A77F2): table 0x0081BCC0 holds the 0x2C-stride
deleting destructor 0x003A7853, two pure calls and writeINI 0x0055F368; table 0x0081BCD0 the -8 thunk
0x003A965D and DefaultPhysicsModuleInfo's three Snapshot slots.
Each DefaultModuleTemplate<N> pairs its category with a different info class (alpha for 1), so the
categories are spelled as explicit specializations. */
#pragma once

#ifndef __BFME2_DEFAULTMODULETEMPLATE_H_
#define __BFME2_DEFAULTMODULETEMPLATE_H_

#include "DefaultAlphaModuleInfo.h"
#include "DefaultUpdateModuleInfo.h"
#include "DefaultColorModuleInfo.h"
#include "DefaultPhysicsModuleInfo.h"
#include "FXModuleTemplateBase.h"

namespace FXParticleSystem
{

template <int Category>
class DefaultModuleTemplate;

template <>
class DefaultModuleTemplate<1> : public CategoryModuleTemplate<1>,
    public DefaultAlphaModuleInfo
{
public:
    DefaultModuleTemplate();
    DefaultModuleTemplate(const DefaultModuleTemplate &that);
    virtual ~DefaultModuleTemplate();

    virtual void writeINI(File &file, unsigned int indent) const;
};

template <>
class DefaultModuleTemplate<2> : public CategoryModuleTemplate<2>,
    public DefaultUpdateModuleInfo
{
public:
    DefaultModuleTemplate();
    DefaultModuleTemplate(const DefaultModuleTemplate &that);
    virtual ~DefaultModuleTemplate();

    virtual void writeINI(File &file, unsigned int indent) const;
};

template <>
class DefaultModuleTemplate<0> : public CategoryModuleTemplate<0>,
    public DefaultColorModuleInfo
{
public:
    DefaultModuleTemplate();
    DefaultModuleTemplate(const DefaultModuleTemplate &that);
    virtual ~DefaultModuleTemplate();

    virtual void writeINI(File &file, unsigned int indent) const;
};

template <>
class DefaultModuleTemplate<3> : public CategoryModuleTemplate<3>,
    public DefaultPhysicsModuleInfo
{
public:
    DefaultModuleTemplate();
    DefaultModuleTemplate(const DefaultModuleTemplate &that);
    virtual ~DefaultModuleTemplate();

    virtual void writeINI(File &file, unsigned int indent) const;
};

}

#endif
