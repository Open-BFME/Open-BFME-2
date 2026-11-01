// Target facts (BFME2 1.06; function addresses are RVAs):
//  - Constructors 0x0004CBF7 (34 bytes) and 0x0004CC19 (36 bytes) store the
//    pointee at +0, call attach at 0x0004CB9A when non-null, and otherwise
//    clear the dwords at +4 and +8. Neither constructor stores a vftable.
//  - attach (0x0004CB9A, 38 bytes) appends this to the pointee's chain at
//    +0x9C/+0xA0, storing the previous handle at +4 and a null next at +8.
//    Unlink (0x0004CBC0, 55 bytes) patches those links and clears +4/+8.
//  - The nonvirtual destructor (0x002115C5, 11 bytes) tests +0 and tail-jumps
//    to 0x0004CBC0 when non-null. These leaf bodies perform no throwing calls.
//  - Assignment (0x0004CC3D, 44 bytes) checks self-assignment, conditionally
//    unlinks, copies +0, and conditionally attaches. It returns this.
//    Both constructors and assignment call only the two leaf chain helpers;
//    their complete call graphs cannot throw.
//  - Copy range 0x0004CCCD divides by 12 and advances by 12 while calling
//    assignment; uninitialized copy 0x0004CC82 also advances by 12: sizeof 12.
//  - DefaultModuleHeadBase constructor 0x003A57C5 stores table VA 0x00C1B590
//    at its own +0, then calls the handle copy constructor on its +4 member.
//    Particle constructor 0x001F4B63 zeroes handles at +0x3C/+0x78 and calls
//    handle assignment; it consumes the pointee as a particle system.
//  - At 0x003FDAFE and 0x003FDB2E, caller 0x003FDAEB tests the handle's first
//    word as a boolean. At 0x003FDB03..0x003FDB0A it uses that word or calls
//    the rowed null-system factory 0x001FCBD7, as does accessor 0x001FD016.
//    These sites prove the inline boolean and pointer operations below.
//  - This is a plain intrusive particle-system handle with no virtual functions
//    or evidenced parent. The field spellings and original class name are unknown.

#pragma once

#ifndef __BFME2_RVASMARTPTR12_H_
#define __BFME2_RVASMARTPTR12_H_

class ParticleSystem;
ParticleSystem *Make001FCBD7();

class RvaSmartPtr12
{
public:
    RvaSmartPtr12(void *ptr) throw();
    RvaSmartPtr12(const RvaSmartPtr12 &other) throw();
    ~RvaSmartPtr12() throw();
    RvaSmartPtr12 &operator=(const RvaSmartPtr12 &other) throw();

    void attach() throw();
    void rva0004CBC0() throw();

    operator bool() const { return field00 != 0; }
    ParticleSystem *operator->() const
    {
        return field00 ? static_cast<ParticleSystem *>(field00) : Make001FCBD7();
    }

    void *field00;
    RvaSmartPtr12 *field04;
    RvaSmartPtr12 *field08;
};

typedef char RvaSmartPtr12SizeCheck[sizeof(RvaSmartPtr12) == 12 ? 1 : -1];

#endif
