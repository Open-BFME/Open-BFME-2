// Target facts (code addresses are RVAs): AptCommandTarget is never constructed in retail. No ledger row names it, and retail_layout finds no constructor, destructor, vftable store or allocation for it, so it has no virtual functions and retail fixes no base or sizeof. It is the type-erased object and method class of the eight-byte DelegateDesc that the Apt callback binder 0x00579E47 copies as two dwords (object +0, method +4, at 0x00579E64..0x00579E6C).
// The method word is a bare code address: EndTurnButtonImpl's constructor 0x00579575 stores this at 0x00579618 and OnClicked 0x005794DD at 0x00579608 before calling the binder, and the bound invoke 0x005B4C73 calls it as `mov ecx,[eax+8]; jmp [eax+0xC]` without adjusting this. A four-byte member pointer called without adjustment is MSVC's single-inheritance form, which a complete class without bases has and an incomplete one lacks.
// The class is therefore complete, empty and without bases. Every private copy spells the class-key `class`, and no ledger name mangles this class.
#ifndef BFME2_APT_APTCOMMANDTARGET_H
#define BFME2_APT_APTCOMMANDTARGET_H

class AptCommandTarget
{
};

#endif
