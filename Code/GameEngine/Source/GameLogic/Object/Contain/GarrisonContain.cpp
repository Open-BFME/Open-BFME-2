// cl: /DNDEBUG /MD /EHsc
// TU Code/GameEngine/Source/GameLogic/Object/Contain/GarrisonContain.cpp.
#include "../../../Common/Thing/thing.h"

typedef float Real;
enum ObjectID { INVALID_ID = 0 };
enum NameKeyType { NK_UNKNOWN = 0 };

// Native trackTargets reads ObjectID at +0x74 and Thing's position at +0x38.
// Only the accessed Object prefix is represented; its full extent is unknown.
class Object : public Thing
{
public:
    ObjectID getID() const { return m_id; }
private:
    unsigned char m_pad60[0x74 - 0x60];
    ObjectID m_id;
};

class AIUpdateInterface
{
public:
    Object *getCurrentVictim() const;
};

// A partial primary-vtable view. Retail table 0x00C461F8 places the pool key
// at slot 4 (0x0047801C); trackTargets itself needs no base or member layout.
// This declares neither the full inheritance graph nor a complete-object size.
class GarrisonContain
{
public:
    virtual void slot00() = 0;
    virtual void slot04() = 0;
    virtual void slot08() = 0;
    virtual void slot0C() = 0;
    virtual NameKeyType getModuleNameKey() const;
protected:
    enum { GARRISON_INDEX_INVALID = -1 };
    void trackTargets();
    int findConditionIndex();
    int findClosestFreeGarrisonPointIndex(int conditionIndex, const Coord3D *pos);
    void removeObjectFromGarrisonPoint(Object *obj, int index);
    void putObjectAtGarrisonPoint(Object *obj, ObjectID targetID, int conditionIndex, int index);
};

template <typename NUM>
inline NUM sqr(NUM x) { return x * x; }

#define BFME_DISP8_BYTECHASE_BEFORE_GETTER(NAME, BACK, INNER) \
	class Inner##NAME \
	{ \
	public: \
		char m_lead[INNER]; \
		unsigned char m_value; \
	}; \
	class Sub##NAME \
	{ \
	public: \
		Inner##NAME *m_holder; \
	}; \
	class NAME \
	{ \
	public: \
		unsigned char get() const; \
	}; \
	unsigned char NAME::get() const \
	{ \
		return ((const Sub##NAME *)((const char *)this - (BACK)))->m_holder->m_value; \
	}

// Measured target helpers used by retail trackTargets at 0x00478ADB.
struct Rva0046247DPair { void *first; void *second; };

class Rva0046247D { public: void rva0046247D(Rva0046247DPair &result); };

class Rva00264E93 { public: void *rva00264E93(); };

// Retail dispatches the object-ID lookup through primary-vtable slot +0x6C.
// The prefix records only that call slot; it does not name the implementation.
class GarrisonContainIndexSlotView
{
public:
    virtual void slot00() = 0; virtual void slot04() = 0; virtual void slot08() = 0;
    virtual void slot0C() = 0; virtual void slot10() = 0; virtual void slot14() = 0;
    virtual void slot18() = 0; virtual void slot1C() = 0; virtual void slot20() = 0;
    virtual void slot24() = 0; virtual void slot28() = 0; virtual void slot2C() = 0;
    virtual void slot30() = 0; virtual void slot34() = 0; virtual void slot38() = 0;
    virtual void slot3C() = 0; virtual void slot40() = 0; virtual void slot44() = 0;
    virtual void slot48() = 0; virtual void slot4C() = 0; virtual void slot50() = 0;
    virtual void slot54() = 0; virtual void slot58() = 0; virtual void slot5C() = 0;
    virtual void slot60() = 0; virtual void slot64() = 0; virtual void slot68() = 0;
    virtual int objectIndex(int objectID) = 0;
};

// 0x0039ADAF is ExperienceTracker::isTrainable (pinned under that name from
// VeterancyCrateCollide::isValidToExecute; ZH's isTrainable reads the
// template's trainable flag): the byte at +0x5E7 of the +0x04 template.
class ExperienceTracker
{
public:
	bool isTrainable() const;
	char m_lead[0x4];
	void *m_template;
};

BFME_DISP8_BYTECHASE_BEFORE_GETTER(Rva0047840CByteChase32Field, 0x1C, 0xA1)

// tu-skeleton: 0x00477DA1 175B ?putObjectAtGarrisonPoint@GarrisonContain@@IAEXPAVObject@@W4ObjectID@@HH@Z -- matched in Code/GameEngine/Source/GameLogic/Object/Contain/GarrisonContainPutObjectAtGarrisonPoint.cpp (not merged yet)

// tu-skeleton: 0x00477E50 50B ?findConditionIndex@GarrisonContain@@IAEHXZ -- matched in Code/GameEngine/Source/GameLogic/Object/Contain/GarrisonContainFindConditionIndex.cpp (not merged yet)

// tu-skeleton: 0x00477E82 132B ?removeObjectFromGarrisonPoint@GarrisonContain@@IAEXPAVObject@@H@Z -- matched in Code/GameEngine/Source/GameLogic/Object/Contain/GarrisonContainRemoveObject.cpp (not merged yet)

// tu-skeleton: 0x00477F06 278B ??0GarrisonContain@@QAE@PAVThing@@PBVModuleData@@@Z -- matched in Code/GameEngine/Source/GameLogic/Object/Contain/GarrisonContainCtor.cpp (not merged yet)

// tu-skeleton: 0x0047801C 69B ?getModuleNameKey@GarrisonContain@@UBE?AW4NameKeyType@@XZ -- matched in Code/GameEngine/Source/GameLogic/Module/GarrisonContainPoolKey.cpp (not merged yet)

// tu-skeleton: 0x00478061 6B ?name@GarrisonContain@@QBEPBDXZ -- matched in Code/GameEngine/Source/Common/ModuleNameGetters.cpp (not merged yet)

// tu-skeleton: 0x00478067 128B ??1GarrisonContain@@UAE@XZ -- matched in Code/GameEngine/Source/GameLogic/Object/Contain/GarrisonContainDtor.cpp (not merged yet)

// tu-skeleton: 0x00478141 240B ?validateRallyPoint@GarrisonContain@@IAEXXZ -- matched in Code/GameEngine/Source/GameLogic/Object/Contain/GarrisonContainValidateRallyPoint.cpp (not merged yet)

// tu-skeleton: 0x00478231 47B ?rva00478231@Rva00478231@@QAEX_N@Z -- matched in Code/GameEngine/Source/GameLogic/Object/Contain/Rva00478231Contain.cpp (not merged yet)

// tu-skeleton: 0x00478260 375B ?xfer@GarrisonContain@@MAEXPAVXfer@@@Z -- matched in Code/GameEngine/Source/GameLogic/Object/Contain/GarrisonContainXfer.cpp (not merged yet)

// tu-skeleton: 0x004783D7 5B ?rva004783D7@Rva004697E1Contain@@QAEXXZ -- matched in Code/GameEngine/Source/GameLogic/Object/Contain/Rva004697E1Gate.cpp (not merged yet)

// tu-skeleton: 0x004783DC 24B ?setOriginalTeam@Rva004783F4@@UAEXPAVTeam@@@Z -- matched in Code/GameEngine/Source/GameLogic/Object/Contain/Rva004783F4.cpp (not merged yet)

// tu-skeleton: 0x004783F4 24B ?rva004783F4@Rva004783F4@@QAEPAVTeam@@XZ -- matched in Code/GameEngine/Source/GameLogic/Object/Contain/Rva004783F4.cpp (not merged yet)

// ---- from Code/GameEngine/Source/Common/Disp8ByteChaseGetters.cpp

// Disp8 byte-chase getters: seven-byte __thiscall members with one shape:
//
//     mov eax,[ecx+<DISP1>] / mov al,[eax+<DISP2>] / ret
//
// A pointer is read at a fixed displacement from `this`, then a byte is read
// at a second displacement from that pointer and returned in `al` (only the
// low byte is defined; the caller uses `al`). MSVC 7.1 emits the disp8 loads
// `8B 41 XX` + `8A 40 XX`, plus `ret`, for seven bytes total.
// Identity is not recovered: every name is derived from its address.
// No // cl: line (defaults match the frameless seven-byte shape).

// Backward variant: the holder sits at a NEGATIVE displacement from `this`
// (a sub-object `this` pointing into a larger object). Spelled as an explicit
// backward cast, which MSVC folds to `mov eax,[ecx-BACK]`; same shape and
// reading as BFME1's ChainedFieldGetters.

// tu-skeleton: 0x00478416 47B ?calcDistSqr@@YAMABUCoord3D@@0@Z -- matched in Code/GameEngine/Source/GameLogic/Object/Contain/GarrisonContainFindClosestFreePoint.cpp (not merged yet)

// tu-skeleton: 0x00478445 258B ?findClosestFreeGarrisonPointIndex@GarrisonContain@@IAEHHPBUCoord3D@@@Z -- matched in Code/GameEngine/Source/GameLogic/Object/Contain/GarrisonContainFindClosestFreePoint.cpp (not merged yet)

// tu-skeleton: 0x00478547 91B ?calcBestGarrisonPosition@GarrisonContain@@UAE_NPAUCoord3D@@PBU2@@Z -- matched in Code/GameEngine/Source/GameLogic/Object/Contain/GarrisonContainCalcBestGarrisonPosition.cpp (not merged yet)

// tu-skeleton: 0x004785A2 107B ?putObjectAtBestGarrisonPoint@GarrisonContain@@IAEXPAVObject@@0PBUCoord3D@@@Z -- matched in Code/GameEngine/Source/GameLogic/Object/Contain/GarrisonContainFirePoints.cpp (not merged yet)

// tu-skeleton: 0x0047860D 28B ??_GGarrisonContain@@UAEPAXI@Z -- matched in Code/GameEngine/Source/GameLogic/Object/Contain/GarrisonContainDtor.cpp (not merged yet)

// tu-skeleton: 0x00478629 112B ?rva00478629@GarrisonContain@@QAE_NPAVObject@@_N1@Z -- matched in Code/GameEngine/Source/GameLogic/Object/Contain/HordeGarrisonContainIface20.cpp (not merged yet)

// tu-skeleton: 0x00478699 95B ?isValidContainerFor@GarrisonContain@@UAE_NPAVObject@@_N1@Z -- matched in Code/GameEngine/Source/GameLogic/Object/Contain/HordeGarrisonContainIface20.cpp (not merged yet)

// tu-skeleton: 0x004786F8 114B ?healSingleObject@GarrisonContain@@IAEXPAVObject@@M@Z -- matched in Code/GameEngine/Source/GameLogic/Object/Contain/GarrisonContainHealSingleObject.cpp (not merged yet)

// tu-skeleton: 0x0047876A 70B ?onBodyDamageStateChange@GarrisonContain@@UAEXPBVDamageInfo@@W4BodyDamageType@@1@Z -- matched in Code/GameEngine/Source/GameLogic/Object/Contain/GarrisonContainHealSingleObject.cpp (not merged yet)

// tu-skeleton: 0x004787B0 160B ?rva004787B0@GarrisonContain@@QAEXXZ -- matched in Code/GameEngine/Source/GameLogic/Object/Contain/GarrisonContainRva004787B0.cpp (not merged yet)

// tu-skeleton: 0x00478850 126B ?attemptBestFirePointPosition@GarrisonContain@@UAE_NPAVObject@@PAVWeapon@@0@Z -- matched in Code/GameEngine/Source/GameLogic/Object/Contain/GarrisonContainFirePoints.cpp (not merged yet)

// tu-skeleton: 0x004788CE 126B ?attemptBestFirePointPosition@GarrisonContain@@UAE_NPAVObject@@PAVWeapon@@PBUCoord3D@@@Z -- matched in Code/GameEngine/Source/GameLogic/Object/Contain/GarrisonContainFirePoints.cpp (not merged yet)

// tu-skeleton: 0x0047894C 399B ?addValidObjectsToGarrisonPoints@GarrisonContain@@IAEXXZ -- matched in Code/GameEngine/Source/GameLogic/Object/Contain/GarrisonContainAddValidObjects.cpp (not merged yet)

// ---- from Code/GameEngine/Source/GameLogic/Object/Contain/GarrisonContain.cpp

// trackTargets follows the Generals Zero Hour reference structure.
// BFME 2 call identities and accessed offsets are measured from the target;
// the reference path is not evidence of a recovered BFME 2 header.
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

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////

// FILE: GarrisonContain.cpp //////////////////////////////////////////////////////////////////////
// Author: Colin Day, February 2002
// Desc:   Contain module for structures that can be garrisoned
///////////////////////////////////////////////////////////////////////////////////////////////////

// USER INCLUDES //////////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ??0GarrisonContainModuleData@@QAE@XZ defined in GarrisonContainModuleDataCtor.cpp (its row's unit).

//-----------------------------------------------------------------------------
inline Real calcDistSqr(const Coord3D& a, const Coord3D& b)
{
	return sqr(a.x - b.x) + sqr(a.y - b.y) + sqr(a.z - b.z);
}

// Target evidence: matched calcBestGarrisonPosition 0x00478547 calls this with
// the condition index and target position. Retail checks the occupied count at
// +0x420, the 40 object slots at +0x100 (0x14 stride), per-condition point
// count at +0x9C4, and coordinates at +0x424. GeneralsMD supports the
// closest-free-point purpose; the target adds its equal-to-owner first-free
// path and BFME2 offsets.

// ------------------------------------------------------------------------------------------------
/** Given the object, return the garrison point index the object is placed at ... if any */
// ------------------------------------------------------------------------------------------------

  // end getObjectGarrisonPointIndex

// ------------------------------------------------------------------------------------------------
/** Put the object at the specified garrison point by index */
// ------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------
/** Given the current state of the structure, return the condition index we are to use
	* from the garrison point position arrays */
// ------------------------------------------------------------------------------------------------
// GarrisonContain::findConditionIndex: defined in GarrisonContainFindConditionIndex.cpp (its row's unit).

//-------------------------------------------------------------------------------------------------
//The weapon system would like to perform a range check assuming the object is placed in the
//best possible available garrison position. If found, we change sourcePos to that position.
//-------------------------------------------------------------------------------------------------
// GarrisonContain::calcBestGarrisonPosition: defined and byte-verified in
// GarrisonContainCalcBestGarrisonPosition.cpp.

//-------------------------------------------------------------------------------------------------
//The AI is entering the aim state and would like to move the unit to the best position, perform
//a range check, and if it succeeds, leave him there -- otherwise, remove him immediately.
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//The AI is entering the aim state and would like to move the unit to the best position, perform
//a range check, and if it succeeds, leave him there -- otherwise, remove him immediately.
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
/** Place the object at the "best" garrison point position so it's on the same "side" of
	* the structure that its target is */
//-------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------
/** Remove the object from the garrison point position and replace at the center of the building */
// ------------------------------------------------------------------------------------------------
// GarrisonContain::removeObjectFromGarrisonPoint: defined in GarrisonContainRemoveObject.cpp (its row's unit).
  // end removeObjectFromGarrisonPoint

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// GarrisonContain::~GarrisonContain: Zero Hour copy removed (it emitted the class vftables).

  // end ~GarrisonContain

//-------------------------------------------------------------------------------------------------
/** can this container contain this kind of object? 
	and, if checkCapacity is TRUE, does this container have enough space 
	left to hold the given unit? */
// ------------------------------------------------------------------------------------------------

void GarrisonContain::trackTargets( void )
{
    int conditionIndex = findConditionIndex();
    Rva0046247DPair listView;
    reinterpret_cast<Rva0046247D *>(this)->rva0046247D(listView);

    struct GarrisonContainTrackNode
    {
        GarrisonContainTrackNode *next;
        GarrisonContainTrackNode *prev;
        Object *object;
    };
    for (GarrisonContainTrackNode *node =
             (*reinterpret_cast<GarrisonContainTrackNode **>(listView.second))->next;
         node != *reinterpret_cast<GarrisonContainTrackNode **>(listView.second);
         node = node->next)
    {
        Object *obj = *reinterpret_cast<Object **>(
            reinterpret_cast<char *>(node) + 8);
        int ourIndex = reinterpret_cast<GarrisonContainIndexSlotView *>(this)->objectIndex(obj->getID());
        if (ourIndex == GARRISON_INDEX_INVALID)
            continue;

        AIUpdateInterface *ai = *reinterpret_cast<AIUpdateInterface **>(
            reinterpret_cast<char *>(obj) + 0x258);
        if (!ai)
            continue;

        Object *victim = ai->getCurrentVictim();
        const Coord3D *victimPos = reinterpret_cast<const Coord3D *>(
            reinterpret_cast<Rva00264E93 *>(ai)->rva00264E93());
        if (!victim && !victimPos)
            continue;
        if (victim)
            victimPos = victim->getPosition();

        const Coord3D *ourPos = obj->getPosition();
        int newIndex = findClosestFreeGarrisonPointIndex(conditionIndex, victimPos);
        if (newIndex == GARRISON_INDEX_INVALID)
            continue;

        const Coord3D *points = reinterpret_cast<const Coord3D *>(
            reinterpret_cast<const char *>(this) + 0x424);
        const Coord3D *newPos = points + conditionIndex * 40 + newIndex;
        Real newDistSq = calcDistSqr(*victimPos, *newPos);
        Real currentDistSq = calcDistSqr(*victimPos, *ourPos);
        if (newDistSq < currentDistSq)
        {
            removeObjectFromGarrisonPoint(obj, ourIndex);
            ObjectID targetID = victim ? victim->getID() : INVALID_ID;
            putObjectAtGarrisonPoint(obj, targetID, conditionIndex, newIndex);
        }
    }
}

// ------------------------------------------------------------------------------------------------
/** Remove all the objects at garrison points back to the center and redeploy them among the
	* garrison points.  NOTE that we are preserving the frame in which the object was put
	* at the garrison point originally as this method is used when the model condition changes
	* which could shuffle the garrison point positions but that shouldn't logically change
	* when an object was placed at the point */
// ------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------
/** Do any effects during an update cycle that we need to */
// ------------------------------------------------------------------------------------------------

  // end updateEffects

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// GarrisonContain::update is retail 0x00479643, recovered in
// GarrisonContainUpdate.cpp.




//-------------------------------------------------------------------------------------------------
/** Every frame, and whenever anyone enters or leaves */
// ------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
/** enforce that everybody stays at their pre-assigned space */
// ------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
/** When a new guy enters a non-enclosing garrison container */
// ------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
/** When I become damaged */
// ------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// GarrisonContain::healSingleObject is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Contain/GarrisonContainHealSingleObject.cpp (0x004786F8).

//-------------------------------------------------------------------------------------------------
/** return the player that *appears* to control this unit. if null, 
		use getObject()->getControllingPlayer() instead. */
// ------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

// Native loadGarrisonPoints is recovered in GarrisonContainLoadGarrisonPoints.cpp.

// ------------------------------------------------------------------------------------------------
/** Validate any exit rally point that has been chosen (if any).  If it's not valid,
	* try to find a new one */
// ------------------------------------------------------------------------------------------------
// GarrisonContain::validateRallyPoint is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Contain/GarrisonContainValidateRallyPoint.cpp (0x00478141).




//-------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------
/** Remove all contents of this container.  We will try to do so with intelligent garrison
	* logic, but if all else fails no matter, we need to get all things out after this
	* call is complete */
// ------------------------------------------------------------------------------------------------

  // end removeAllContained

// ------------------------------------------------------------------------------------------------
/** 'exitObj' is one of the things we contain, it needs to 'exit' us */
// ------------------------------------------------------------------------------------------------
// Native exitObjectViaDoor is recovered in GarrisonContainExit.cpp.

// Note: an earlier ZH-derived GarrisonContain::onContaining body stood here.
// The census proves our copy is not retail's (S: the kept definition differs
// from retail bytes) while 0x00478C2C is rowed 222B from
// GarrisonContainOnContaining.cpp, so this unit no longer defines it and the
// link keeps the rowed copy.

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------
/** A GarrisonContain always lets people shoot out */
// ------------------------------------------------------------------------------------------------

  // end isPassengerAllowedToFire

// ------------------------------------------------------------------------------------------------
/** A Mobile garrison keeps its occupants with it when it moves */
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------

  // end crc

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
// byte-exact reconstruction: Code/GameEngine/Source/GameLogic/Object/Contain/GarrisonContainXfer.cpp

// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------

  // end loadPostProcess





// ------------------------------------------------------------------------------------------------
/** Load the loadStationGarrisonPoints data and save for use later */
// ------------------------------------------------------------------------------------------------

  // end loadStationGarrisonPoints

// tu-skeleton: 0x00478BE0 76B ?rva00478BE0@GarrisonContain@@QAEXXZ -- matched in Code/GameEngine/Source/GameLogic/Object/Contain/GarrisonContainSiblingHelpers.cpp (not merged yet)

// tu-skeleton: 0x00478C2C 222B ?onContaining@GarrisonContain@@UAEXPAVObject@@_N@Z -- matched in Code/GameEngine/Source/GameLogic/Object/Contain/GarrisonContainOnContaining.cpp (not merged yet)

// tu-skeleton: 0x00478D0A 717B ?onRemoving@GarrisonContain@@UAEXPAVObject@@@Z -- matched in Code/GameEngine/Source/GameLogic/Object/Contain/GarrisonContainOnRemoving.cpp (not merged yet)

// tu-skeleton: 0x00478FD7 68B ?rva00478FD7@GarrisonContain@@QAEXXZ -- matched in Code/GameEngine/Source/GameLogic/Object/Contain/GarrisonContainSiblingHelpers.cpp (not merged yet)

// tu-skeleton: 0x0047901B 631B ?loadGarrisonPoints@GarrisonContain@@IAEXXZ -- matched in Code/GameEngine/Source/GameLogic/Object/Contain/GarrisonContainLoadGarrisonPoints.cpp (not merged yet)

// tu-skeleton: 0x00479292 170B ?getObjectGarrisonPointIndex@GarrisonContain@@UAEHW4ObjectID@@@Z -- matched in Code/GameEngine/Source/GameLogic/Object/Contain/GarrisonContainGetObjectGarrisonPointIndex.cpp (not merged yet)

// tu-skeleton: 0x0047933C 89B ?removeInvalidObjectsFromGarrisonPoints@GarrisonContain@@IAEXXZ -- matched in Code/GameEngine/Source/GameLogic/Object/Contain/GarrisonContainRemoveInvalidObjects.cpp (not merged yet)

// tu-skeleton: 0x00479395 157B ?redeployOccupants@GarrisonContain@@MAEXXZ -- matched in Code/GameEngine/Source/GameLogic/Object/Contain/GarrisonContainGetObjectGarrisonPointIndex.cpp (not merged yet)

// tu-skeleton: 0x00479432 529B ?recalcApparentControllingPlayer@GarrisonContain@@UAEXXZ -- matched in Code/GameEngine/Source/GameLogic/Object/Contain/GarrisonContainRecalcApparentControllingPlayer.cpp (not merged yet)

// tu-skeleton: 0x00479643 217B ?update@GarrisonContain@@UAE?AW4UpdateSleepTime@@XZ -- matched in Code/GameEngine/Source/GameLogic/Object/Contain/GarrisonContainUpdate.cpp (not merged yet)

// tu-skeleton: 0x0047978F 143B ??0GarrisonContainModuleData@@QAE@XZ -- matched in Code/GameEngine/Source/GameLogic/Object/Contain/GarrisonContainModuleDataCtor.cpp (not merged yet)

// tu-skeleton: 0x0047981E 28B ??_GGarrisonContainModuleData@@UAEPAXI@Z -- matched in Code/GameEngine/Source/GameLogic/Object/Contain/ContainModuleDeletingDtors.cpp (not merged yet)

// tu-skeleton: 0x0047983A 672B ?exitObjectViaDoor@GarrisonContain@@UAEXPAVObject@@W4ExitDoorType@@@Z -- matched in Code/GameEngine/Source/GameLogic/Object/Contain/GarrisonContainExit.cpp (not merged yet)
