// Target facts (BFME2 1.06; addresses are RVAs): factory 0x001F50F9 constructs its BfmeParticleSystemHandle return buffer through 0x0004CBF7; lookup 0x001F5B6F copies it through 0x0004CC19. These constructors store the system at +0, attach through 0x0004CB9A when non-null, and otherwise clear +4/+8. Attach 0x0004CB9A and unlink 0x0004CBC0 prove previous/next pointers at +4/+8 and the system's chain at +0x9C/+0xA0. Copy loops 0x0004CC82 and 0x0004CCCD advance by 12; sizeof is 12. No virtual functions, vftable stores, or parent are evidenced for this handle.
// Destructor 0x002115C5 tests +0 and tail-jumps to unlink 0x0004CBC0; its existing BfmeParticleSystemHandle pin names that body. Assignment 0x0004CC3D checks self-assignment, unlinks, copies +0, and attaches. These complete leaf call graphs cannot throw. Default returns at 0x001F5A7B..0x001F5A80 and 0x001F5B1F..0x001F5B24 clear all three words. DefaultModuleHeadBase's constructor 0x003A57CF and destructor 0x003A57E7 store VA 0x00C1B590 at their own +0; their handle receiver is +4, so this table is not the handle's.
// Lookup 0x001F5B33 tests the system word as a boolean; 0x001F5B38..0x001F5B3F and accessor 0x001FD016 return that pointer or call null-system factory 0x001FCBD7. Emitter code 0x000CB5D0/0x000CB5D4 repeats the pointer read and 0x000CB5DA keeps the null fallback after an outer null test, as get() reads it. Ledger returns at 0x001F50BC/0x001F5A6A/0x001F5B0A use class-key V. Member names describe system and previous/next roles proved by lookup and attach/unlink, not recovered original spellings. The original class name and get() spelling are unproven; get() retains the existing consumer API. Lifetime operations called out of line remain declarations.

#pragma once

#ifndef BFME2_PARTICLESYSTEMHANDLE_H
#define BFME2_PARTICLESYSTEMHANDLE_H

class ParticleSystem;
ParticleSystem *Make001FCBD7();

class BfmeParticleSystemHandle
{
public:
    BfmeParticleSystemHandle() : m_system(0), m_previous(0), m_next(0) {}
    BfmeParticleSystemHandle(ParticleSystem *system) throw();
    BfmeParticleSystemHandle(const BfmeParticleSystemHandle &other) throw();
    ~BfmeParticleSystemHandle() throw();
    BfmeParticleSystemHandle &operator=(const BfmeParticleSystemHandle &other) throw();

    operator bool() const { return m_system != 0; }
    ParticleSystem *operator->() const
    {
        return m_system ? m_system : Make001FCBD7();
    }

    ParticleSystem *get() const
    {
        return m_system ? m_system : Make001FCBD7();
    }

    ParticleSystem *m_system;
    BfmeParticleSystemHandle *m_previous;
    BfmeParticleSystemHandle *m_next;
};

typedef char BfmeParticleSystemHandleSizeCheck[sizeof(BfmeParticleSystemHandle) == 12 ? 1 : -1];

#endif
