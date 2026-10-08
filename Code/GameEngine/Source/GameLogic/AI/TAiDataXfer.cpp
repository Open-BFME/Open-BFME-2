// cl: /DNDEBUG /MD
// cl: /O1 /DNDEBUG /MD /GX
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


// TAiData::xfer, ported from Zero Hour's GameEngine/Source/GameLogic/AI/AI.cpp
// (GeneralsMD tree vendored under reference/open-bfme-1/inputs/reference). It
// is slot 3 of the vftable whose name getter returns "TAiData".
//
// ZH's xfer is only a version, and the fields go through crc(). BFME 2 folds
// the two together: under IsCRC (Xfer +0x0C) it transfers ZH's crc() field
// list; otherwise it runs Version1. The field layout skips +0x48 and +0x58.
// ZH's last three distances map onto two Reals here (+0x5C, +0x60), so those
// two keep neutral names. BFME 2 appends four Ints (+0x104..+0x110).

class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
class Coord3DBase;
class ICoord3D;
class Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;

class Xfer
{
public:
	class Version;

	Xfer();
	virtual ~Xfer();

	void Version1();

	virtual bool IsLoading() const;
	virtual bool IsStoring() const;
	virtual bool IsCRC() const;
	virtual bool IsLightCRC() const;

	virtual void v5() = 0;
	virtual void v6() = 0;
	virtual void v7() = 0;

	virtual void SkipBadBlock(Snapshot &snapshot, unsigned int size);
	virtual Xfer &XferRawBytes(void *data, unsigned int size);
	virtual Xfer &operator==(bool &value);
	virtual Xfer &operator==(char &value);
	virtual Xfer &operator==(unsigned char &value);
	virtual Xfer &operator==(short &value);
	virtual Xfer &operator==(unsigned short &value);
	virtual Xfer &operator==(int &value);
	virtual Xfer &operator==(unsigned int &value);
	virtual Xfer &operator==(__int64 &value);
	virtual Xfer &operator==(float &value);
	virtual Xfer &operator==(AsciiString &value);
	virtual Xfer &operator==(UnicodeString &value);
	virtual Xfer &operator==(PooledString &value);
	virtual Xfer &operator==(Coord3DBase &value);
	virtual Xfer &operator==(ICoord3D &value);
	virtual Xfer &operator==(Region3D &value);
	virtual Xfer &operator==(IRegion3D &value);
	virtual Xfer &operator==(Coord2D &value);
	virtual Xfer &operator==(ICoord2D &value);
	virtual Xfer &operator==(Region2D &value);
	virtual Xfer &operator==(IRegion2D &value);
	virtual Xfer &operator==(RealRange &value);
	virtual Xfer &operator==(RGBColor &value);
	virtual Xfer &operator==(RGBAColorReal &value);
	virtual Xfer &operator==(RGBAColorInt &value);
	virtual Xfer &operator==(Snapshot &value);
	virtual Xfer &operator==(XferUnknown11 &value) = 0;
	virtual Xfer &operator==(Version &value);

	virtual Xfer &XferEnum(const char *name, void *data, unsigned int size);

protected:
	virtual void XferData(unsigned int type, void *data, unsigned int size) = 0;
};

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

class Coord3DBase
{
public:
	float x;
	float y;
	float z;
};

typedef bool Bool;
typedef float Real;

class TAiData
{
protected:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void xfer( Xfer *xfer );
private:
	Real m_structureSeconds;																									///< 0x04
	Real m_teamSeconds;																												///< 0x08
	Int m_resourcesWealthy;																										///< 0x0C
	Int m_resourcesPoor;																											///< 0x10
	UnsignedInt m_forceIdleFramesCount;																				///< 0x14
	Real m_structuresWealthyMod;																							///< 0x18
	Real m_teamWealthyMod;																										///< 0x1C
	Real m_structuresPoorMod;																									///< 0x20
	Real m_teamPoorMod;																												///< 0x24
	Real m_teamResourcesToBuild;																							///< 0x28
	Real m_guardInnerModifierAI;																							///< 0x2C
	Real m_guardOuterModifierAI;																							///< 0x30
	Real m_guardInnerModifierHuman;																						///< 0x34
	Real m_guardOuterModifierHuman;																						///< 0x38
	UnsignedInt m_guardChaseUnitFrames;																				///< 0x3C
	UnsignedInt m_guardEnemyScanRate;																					///< 0x40
	UnsignedInt m_guardEnemyReturnScanRate;																		///< 0x44
	char m_unrecovered48[ 0x4C - 0x48 ];
	Real m_alertRangeModifier;																								///< 0x4C
	Real m_aggressiveRangeModifier;																						///< 0x50
	Real m_attackPriorityDistanceModifier;																		///< 0x54
	char m_unrecovered58[ 0x5C - 0x58 ];
	Real m_bfmeReal5C;																												///< 0x5C
	Real m_bfmeReal60;																												///< 0x60
	Bool m_enableRepulsors;																										///< 0x64
	char m_unrecovered65[ 0x104 - 0x65 ];
	Int m_bfmeInt104;																													///< 0x104
	Int m_bfmeInt108;																													///< 0x108
	Int m_bfmeInt10C;																													///< 0x10C
	Int m_bfmeInt110;																													///< 0x110
};

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
void TAiData::xfer( Xfer *xfer )
{
	if( xfer->IsCRC() )
	{
		*xfer == m_structureSeconds;
		*xfer == m_teamSeconds;
		*xfer == m_resourcesWealthy;
		*xfer == m_resourcesPoor;
		*xfer == m_forceIdleFramesCount;
		*xfer == m_structuresWealthyMod;
		*xfer == m_teamWealthyMod;
		*xfer == m_structuresPoorMod;
		*xfer == m_teamPoorMod;
		*xfer == m_teamResourcesToBuild;
		*xfer == m_guardInnerModifierAI;
		*xfer == m_guardOuterModifierAI;
		*xfer == m_guardInnerModifierHuman;
		*xfer == m_guardOuterModifierHuman;
		*xfer == m_guardChaseUnitFrames;
		*xfer == m_guardEnemyScanRate;
		*xfer == m_guardEnemyReturnScanRate;
		*xfer == m_alertRangeModifier;
		*xfer == m_aggressiveRangeModifier;
		*xfer == m_attackPriorityDistanceModifier;
		*xfer == m_bfmeReal5C;
		*xfer == m_bfmeReal60;
		*xfer == m_enableRepulsors;
		*xfer == m_bfmeInt104;
		*xfer == m_bfmeInt108;
		*xfer == m_bfmeInt10C;
		*xfer == m_bfmeInt110;
	}
	else
	{
		// version
		xfer->Version1();
	}

}  // end xfer

// BF1 9cbfb551fe Common/Rva14AAD0RangeCount.cpp is the clean semantic guide.
// Complete native 002FDF11..002FDF1C RET leaf proves: receiver0 range pointer; end4 minus begin0 divided by element stride8.
// Original owner and complete bounds unresolved; independent address-owned view.
struct Rva002FDF11Element { unsigned char bytes[8]; };
struct Rva002FDF11Range { Rva002FDF11Element *begin; Rva002FDF11Element *end; };
class Rva002FDF11Fields {
public: int count();
private: Rva002FDF11Range *range;
};
int Rva002FDF11Fields::count() { return range->end - range->begin; }
