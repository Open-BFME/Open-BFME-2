// cl: /DNDEBUG /MD /EHsc
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


// CaveContain::xfer, ported from Zero Hour's GameEngine/Source/GameLogic/
// Object/Contain/CaveContain.cpp (GeneralsMD tree vendored under
// reference/open-bfme-1/inputs/reference). It is slot 3 of the vftable whose
// name getter returns "CaveContain".
//
// BFME 2 order: the OpenContain base (0x00465EF1) first, then the light-CRC
// gate and Version1, then ZH's fields (+0x100 flag, +0x104 cave index, +0x108
// original team, saved by its id at Team+0x34). On load the team comes back
// through the team factory lookup 0x0039F761, held in the ledger as
// TeamFactory::findTeamByID. ZH's throw SC_INVALID_DATA becomes BFME 2's
// XferException with tag 5 and no text (constructor 0x0060C36E).

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

#include "../../../../Include/Common/BfmeXfer.h"

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
typedef int Int;
typedef unsigned int UnsignedInt;

class XferException
{
public:
	XferException(int tag, const char *format, ...);
	XferException(const XferException &that);
	~XferException(void);

	char *text;
	int tagValue;
};

#include "../../../../Include/Common/TeamBFME2.h"

class TeamFactory
{
public:
	Team *findTeamByID(unsigned int id);
};

class TeamFactory;
extern TeamFactory *TheTeamFactory;

class Object;
class Team;
class Player;
class Thing;
class ModuleData;
class DamageInfo;
class BfmeTab1026;
class Rva0036AE51ListView;
enum NameKeyType;
#include "../../../../Include/Common/ObjectModule.h"

class OpenContainPrimaryBase : public ObjectModule
{
public:
	virtual void primarySlot0A() = 0;
	virtual void primarySlot0B() = 0;
	virtual void primarySlot0C() = 0;
	virtual void primarySlot0D() = 0;
	virtual void primarySlot0E() = 0;
	virtual void primarySlot0F() = 0;
	virtual void primarySlot10() = 0;
	virtual void primarySlot11() = 0;
	virtual void primarySlot12() = 0;
	virtual void primarySlot13() = 0;
	virtual void primarySlot14() = 0;
	virtual void primarySlot15() = 0;
	virtual void doUnloadSound() = 0;
};
class OpenContainBehaviorInterface
{
public:
	virtual void behaviorAnchor() = 0;
};
class OpenContainUpdateInterface
{
public:
	virtual void updateAnchor() = 0;

private:
	UnsignedInt m_nextCallFrameAndPhase;
	Int m_indexInLogic;
	UnsignedInt m_unreconstructed1C;
};
class ContainModuleInterface
{
public:
	virtual void pad00() = 0;
	virtual void pad04() = 0;
	virtual void pad08() = 0;
	virtual void pad0C() = 0;
	virtual void pad10() = 0;
	virtual void pad14() = 0;
	virtual void pad18() = 0;
	virtual void pad1C() = 0;
	virtual void pad20() = 0;
	virtual void pad24() = 0;
	virtual void pad28() = 0;
	virtual void pad2C() = 0;
	virtual void pad30() = 0;
	virtual void pad34() = 0;
	virtual void pad38() = 0;
	virtual void targetPad3C() = 0;
	virtual void targetPad40() = 0;
	virtual void targetPad44() = 0;
	virtual void targetPad48() = 0;
	virtual const Player *getApparentControllingPlayer(const Player *) const = 0;
	virtual void recalcApparentControllingPlayer() = 0;
	virtual void targetPad54() = 0;
	virtual void onContaining(Object *, Bool) = 0;
	virtual void onRemoving(Object *) = 0;
	virtual void pad50() = 0;
	virtual void pad54() = 0;
	virtual void pad58() = 0;
	virtual void pad5C() = 0;
	virtual int getContainMax() const = 0;
	virtual void pad64() = 0;
	virtual void pad68() = 0;
	virtual void pad6C() = 0;
	virtual void pad70() = 0;
	virtual void pad74() = 0;
	virtual void pad78() = 0;
	virtual void pad7C() = 0;
	virtual void pad80() = 0;
	virtual void pad84() = 0;
	virtual Bool isValidContainerFor(Object *, Bool, Bool) = 0;
	virtual void pad8C() = 0;
	virtual void addToContainList(Object *) = 0;
	virtual void removeFromContain(Object *, Bool) = 0;
	virtual void removeAllContained(Bool) = 0;
	virtual void pad9C() = 0;
	virtual void padA0() = 0;
	virtual void padA4() = 0;
	virtual void padA8() = 0;
	virtual void padAC() = 0;
	virtual void padB0() = 0;
	virtual void padB4() = 0;
	virtual void padB8() = 0;
	virtual void padBC() = 0;
	virtual void padC0() = 0;
	virtual void padC4() = 0;
	virtual void padC8() = 0;
	virtual void padCC() = 0;
	virtual void padD0() = 0;
	virtual void padD4() = 0;
	virtual void padD8() = 0;
	virtual void padDC() = 0;
	virtual void padE0() = 0;
	virtual void padE4() = 0;
	virtual void padE8() = 0;
	virtual void padEC() = 0;
	virtual void padF0() = 0;
	virtual void padF4() = 0;
	virtual void padF8() = 0;
	virtual void padFC() = 0;
	virtual void iterateContained(void (*)(Object *, void *), void *, unsigned int) = 0;
	virtual int rva00466504(BfmeTab1026 *) = 0;
	virtual Rva0036AE51ListView rva00466534() = 0;
};
template <int Offset>
class OpenContainAuxiliaryInterface
{
public:
	virtual void auxiliaryAnchor() = 0;
};

template <>
class OpenContainAuxiliaryInterface<0x28>
{
public:
	virtual void onDie(const DamageInfo *) = 0;
};

template <>
class OpenContainAuxiliaryInterface<0x34>
{
public:
	virtual void onCreate() = 0;
	virtual void onBuildComplete() = 0;
	virtual void rva004B3FD0() = 0;
	virtual Bool shouldDoOnBuildComplete() = 0;
};

class __declspec(novtable) OpenContain
	: public OpenContainPrimaryBase,
	  public OpenContainBehaviorInterface,
	  public OpenContainUpdateInterface,
	  public ContainModuleInterface,
	  public OpenContainAuxiliaryInterface<0x24>,
	  public OpenContainAuxiliaryInterface<0x28>,
	  public OpenContainAuxiliaryInterface<0x2C>,
	  public OpenContainAuxiliaryInterface<0x30>,
	  public OpenContainAuxiliaryInterface<0x34>
{
public:
	OpenContain(Thing *thing, const ModuleData *moduleData);
	virtual ~OpenContain();
	virtual const Player *getApparentControllingPlayer(const Player *) const;
	virtual void onRemoving(Object *obj);
	virtual void onContaining(Object *, Bool);

protected:
	virtual void doUnloadSound();
	virtual void xfer(Xfer *xfer);
	using OpenContainPrimaryBase::getObject;

private:
	unsigned char m_openContainData[0xC4];
};
class CaveInterface
{
public:
	virtual void tryToSetCaveIndex(Int newIndex) = 0;
	virtual void setOriginalTeam(Team *oldTeam) = 0;
};

class CaveContain : public OpenContain, public CaveInterface
{
public:
	CaveContain(Thing *thing, const ModuleData *moduleData);
	virtual void onRemoving(Object *obj);
	virtual void recalcApparentControllingPlayer();
	void rva00466848(Team *, Bool);
	virtual void onContaining(Object *, Bool);
	virtual void removeFromContain(Object *obj, Bool exposeStealthUnits);
	virtual void removeAllContained(Bool exposeStealthUnits);
	virtual void iterateContained(void (*callback)(Object*,void*), void *data, unsigned int flags);
	// Implemented for the CaveInterface subobject at complete-object +0xFC.
	virtual void tryToSetCaveIndex(int newIndex);
	// Implemented for the one-entry die interface at complete-object +0x28.
	virtual void onDie(const DamageInfo *damageInfo);
	virtual void addToContainList(Object *obj);
	virtual Bool isValidContainerFor(Object *obj, Bool checkCapacity, Bool testPath);
	virtual int rva00466504(BfmeTab1026 *tab);
	virtual int getContainMax() const;
	virtual Rva0036AE51ListView rva00466534();
	// Lifecycle interface at complete-object +0x34.
	virtual void onCreate();
	virtual void onBuildComplete();

protected:
	virtual ~CaveContain();
	virtual void xfer(Xfer *xfer);

private:
	Bool m_needToRunOnBuildComplete; // +0x100
	unsigned char m_fieldAlignment[3];
	Int m_caveIndex; // +0x104
	Team *m_originalTeam; // +0x108
public:
	virtual NameKeyType getModuleNameKey() const;
};


// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
void CaveContain::xfer( Xfer *xfer )
{

	// extend base class
	OpenContain::xfer( xfer );

	if( xfer->IsLightCRC() )
		return;

	// version
	xfer->Version1();

	// need to run on build complete
	*xfer == m_needToRunOnBuildComplete;

	// cave index
	*xfer == m_caveIndex;

	// original team
	UnsignedInt teamID = m_originalTeam ? m_originalTeam->getID() : 0;
	*xfer == teamID;
	if( xfer->IsLoading() )
	{

		if( teamID != 0 )
		{

			m_originalTeam = TheTeamFactory->findTeamByID( teamID );
			if( m_originalTeam == 0 )
				throw XferException( 5, 0 );

		}  // end if
		else
			m_originalTeam = 0;

	}  // end if

}  // end xfer
