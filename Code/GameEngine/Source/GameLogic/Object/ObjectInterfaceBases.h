// FILE: ObjectInterfaceBases.h ///////////////////////////////////////////////////////////////////
// Object's interface bases past Thing and Snapshot: the +0x64 interface (vbptr at +0x68, one virtual
// base) and the bases at +0x6C and +0x70. Shared by the units that lay Object out with its bases
// (ObjectConstructor.cpp, ObjectDestructor.cpp, Object.cpp). Not a registered canonical header: the
// class names are placeholders (the +0x64 slots are spelled as the registered ObjectShroudClient
// spells them; ObjectShroudClient is an interface surface, not a proven original class).
//
// Target facts: Object::Object (0x00298EA9) installs the vbtable at +0x68 (entries -4 and 0x46C: the
// virtual base at +0x4D4), calls ??0BfmeCtor001B3A20 (0x0028AADF) with this+0x64, stores the bases'
// own tables 0x00BFBC9C (+0x6C, 8 slots) and 0x00BFBCBC (+0x70, 10 slots), then overwrites all of them
// with Object's tables 0x00BFC2D8, 0x00BFC2B8, 0x00BFC290 and 0x00BFC27C. Both base tables hold only
// __purecall, so every slot declared here is pure. Retail's slot counts are 6 (+0x64), 8 (+0x6C),
// 10 (+0x70) and 5 (virtual base); only the slots Object's units declare overrides for are listed.
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef BFME2_OBJECT_INTERFACE_BASES_H
#define BFME2_OBJECT_INTERFACE_BASES_H

class AsciiString;
class GeometryInfo;
struct Coord3D;

// Object+0x64, table 0x00BFC2D8.
class BfmeCtorFirstBase001B3A20
{
public:
	virtual AsciiString rva00290EE0() = 0;
protected:
	// Empty native slot (0x000B3FD0); return type and name unknown.
	virtual void opaqueSlot1() = 0;
public:
	virtual void *getGhostObject() = 0;
	virtual void rva002941EA(int *, float *, float *, float *) = 0;
	virtual float ShroudGetValueRangeAndMask(int, unsigned *, unsigned *) const = 0;
	virtual bool ShroudHideIfFogged(int) const = 0;
};

// The virtual base, at Object+0x4D4 (table 0x00BFC27C) through the vbptr at +0x68.
class BfmeCtorVirtualBase001B3A20
{
public:
	virtual void *slot() const = 0;
};

// Object+0x64: ??0BfmeCtor001B3A20@@QAE@XZ (0x0028AADF).
class BfmeCtor001B3A20 : public BfmeCtorFirstBase001B3A20, public virtual BfmeCtorVirtualBase001B3A20
{
public:
	BfmeCtor001B3A20() throw();
};

// Object+0x6C, base table 0x00BFBC9C, Object's table 0x00BFC2B8. Slots 3 and 4 hold one body in
// retail; which of the pair is const is not proven by retail's bytes.
struct Rva00BFC2B8Base
{
	virtual const GeometryInfo &getGeometryInfo() const = 0;
	virtual void *rva00299CBE() const = 0;
	virtual float rva00299CC2() const = 0;
	virtual void *rva00299C74() = 0;
	virtual void *rva00299C74() const = 0;
};

// Object+0x70, base table 0x00BFBCBC, Object's table 0x00BFC290. Slots 2 and 3 hold one body in
// retail; which of the pair is const is not proven by retail's bytes.
struct Rva00BFC290Base
{
	virtual Coord3D rva0028C037() = 0;
	virtual Coord3D rva0028C08D() = 0;
	virtual void *rva00299C78() = 0;
	virtual void *rva00299C78() const = 0;
};

#endif // BFME2_OBJECT_INTERFACE_BASES_H
