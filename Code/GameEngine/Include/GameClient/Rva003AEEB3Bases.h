// Target facts (RVAs; tables are VAs): the 4-byte secondary subobjects of Rva003AEEB3 at +0x14 and +0x18. Derived constructor 0x003AEDE9 stores
// 0x00C1C61C (sole slot: factory 0x003ACA24, unsigned argument, pointer result, ret 4) and 0x00C1CA00 (sole slot: const class getter 0x003AD0FB).
// Not registered yet; naming lead: FXParticleSystem's CategoryModuleInfo<C> family (getClass, createModule), see the hn-categorymoduletempla report.
#pragma once

#ifndef __BFME2_RVA003AEEB3BASES_H_
#define __BFME2_RVA003AEEB3BASES_H_

class Rva003AEEB3Slot14
{
public:
    virtual void *slot14(unsigned int value) = 0;
};

class Rva003AEEB3Slot18
{
public:
    virtual const void *slot18() const = 0;
};

#endif
