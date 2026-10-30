#pragma once
// Rva002B0F3CIface: the 4-byte interface base Player places at +4 (original
// name unknown).
//
// Target facts (code addresses are RVAs, tables VAs): Player's ctor 0x002B0F3C
// stores this class's table 0x00BE2B78 at +4 inline (no ctor call), then
// Player's own 0x00BFDF30. 0x00BE2B78 is three __purecall (0x0003B810) slots,
// an ICF-folded table nine classes share, so it names no class. Player fills
// the slots with 0x002B118A (add ecx,-4; jmp hasScience: bool(ScienceType)
// const), 0x0030D377 (mov eax,[ecx+0x20]: int() const) and 0x002B1192 (calls
// rva002AB855 and stores the bool through its second argument:
// void(CreateAHeroData *, bool *)). The bodies' rows are spelled on other
// classes, so the slots keep islotNN placeholders with those signatures. The
// class name is the spelling PlayerCtorBFME2.cpp and PlayerDestructor.cpp
// already use.
#ifndef CANONICAL_RVA002B0F3CIFACE_H
#define CANONICAL_RVA002B0F3CIFACE_H

class CreateAHeroData;
enum ScienceType;

class Rva002B0F3CIface
{
public:
	virtual bool islot00(ScienceType) const = 0;	// slot 0
	virtual int islot01() const = 0;				// slot 1
	virtual void islot02(CreateAHeroData *, bool *) = 0;	// slot 2
};
typedef char CanonicalRva002B0F3CIfaceSizeCheck[sizeof(Rva002B0F3CIface) == 4 ? 1 : -1];

#endif // CANONICAL_RVA002B0F3CIFACE_H
