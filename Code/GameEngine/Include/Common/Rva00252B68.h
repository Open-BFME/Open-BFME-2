// Target facts (RVAs unless marked VA): this class's ctor 0x00252B68 calls DrawableModule's and installs
// VA 0x00BEFE48, which has 19 slots: DrawableModule's eleven, then slot 11 0x000D1407 `ret 0xC`, slots 12-16
// 0x000D43D0 (return zero) and slots 17-18 0x000B3FD0 `ret`. Its name and those slots' names are not recovered.
// The sound selectors (VA 0x00BF3220, 0x00BEFEB0) replace slots 13 and 14 with 0x000CA841, which returns their
// +0x0C interface, null-guarded.
#pragma once

#ifndef __BFME2_RVA00252B68_H_
#define __BFME2_RVA00252B68_H_

#include "DrawableModule.h"

class Rva00252B68 : public DrawableModule
{
public:
	Rva00252B68(Thing *thing, const ModuleData *moduleData);
	virtual ~Rva00252B68();
	virtual void vslot11(int, int, int) { }
	virtual void *vslot12() { return 0; }
	virtual void *vslot13() { return 0; }
	virtual void *vslot14() { return 0; }
	virtual void *vslot15() { return 0; }
	virtual void *vslot16() { return 0; }
	virtual void vslot17() { }
	virtual void vslot18() { }
};

#endif
