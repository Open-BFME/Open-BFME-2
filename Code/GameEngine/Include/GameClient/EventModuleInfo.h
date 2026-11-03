/* Target facts (RVAs): exported FXParticleSystem::EventModuleInfo constructor 0x00001236 writes true to bytes +0 and +1; exported assignment 0x00001240 copies exactly that word and returns this. The complete nonvirtual destructor 0x000B3FD0 is a bare ret. These bodies contain no vptr stores, base calls or virtual dispatch: EventModuleInfo has no virtual functions, vtable or nonempty base.
CategoryModuleTemplate<8> constructor 0x00001EF9 places those flags at +8/+9; assignment 0x0000124F and copy constructor 0x00001F30 copy their word at +8. The tables written at +0/+4 belong to the surrounding polymorphic bases, not EventModuleInfo. LifeEventModuleTemplate constructor 0x003A999C places its next polymorphic base at +0x0C. The two byte members give sizeof 2 and alignment 1; their original names are unproven, so they use offset names.
The ledger declares the default constructor and assignment public and the nonvirtual destructor protected; all three bodies remain out of line. The registered global ModuleInfo (constructor 0x001F81BF, sizeof 0x0C) is a distinct type from the empty FXParticleSystem::ModuleInfo in private views and is not a base of this layout. */
#pragma once

#ifndef __BFME2_EVENTMODULEINFO_H_
#define __BFME2_EVENTMODULEINFO_H_

namespace FXParticleSystem
{

class EventModuleInfo
{
public:
    EventModuleInfo();
    EventModuleInfo &operator=(const EventModuleInfo &that);

    bool m_00;
    bool m_01;

protected:
    ~EventModuleInfo();
};

}

using FXParticleSystem::EventModuleInfo;

#endif
