// FILE: ProductionUpdateInterface.h //////////////////////////////////////////////////////////////
// Desc:   Canonical BFME2 ProductionUpdateInterface, the production queue interface of ProductionUpdate.
//
// Target facts:
//  - ??0ProductionUpdate (0x0049E03A) calls ??0UpdateModule, stores this class's own
//    table 0x00C513F0 at +0x20 (0x0049E058) and DieModuleInterface's 0x00C1C780 at +0x24,
//    then its own tables 0x00C51478 at +0x20 (0x0049E08F) and 0x00C51470 at +0x24: the
//    class is its vptr alone, sizeof 4.
//  - 0x0049CC0C (9 B, rowed as ??0Rva0049E03AIface20@@QAE@XZ) is the out-of-line default
//    constructor: it stores 0x00C513F0 at +0 and returns this. No call reaches it; 0x0049E03A
//    inlines the same store, so it is declared here and defined by the unit that owns the row.
//  - 0x00C513F0 holds exactly 31 __purecall slots; the table 0x00C5146C that ??0Rva0049D1B1
//    (0x0049D162) stores follows. ProductionUpdate's table for this base, 0x00C51478, also
//    ends after 31 slots, at its +0x10 table 0x00C514F4 (stored at 0x0049E088). No slot is a
//    destructor and ~ProductionUpdate (0x0049E1BF) never stores 0x00C513F0: no virtual dtor.
//  - Only 0x0049E03A and 0x0049CC0C store 0x00C513F0, and only ProductionUpdate's constructor
//    and destructor store 0x00C51478: ProductionUpdate is the one implementer.
//  - Implementer bodies, offsets from ProductionUpdate (their `this` is +0x20): slot 0
//    (0x0049CFCD) takes no argument and returns 3 when the byte +0x13C is set, else 4 when
//    the count +0x34 reaches the module data's +0x28, else 0; slots 24 and 25 set and read
//    that byte. requestUniqueUnitID (0x0049E142) increments +0x30, which the constructor sets
//    to 1; slot 17 (0x0057E556) returns +0x34 and slot 21 (0x0030F45F) the queue head +0x28.
//    Slot 15 (0x0049CE6E) calls +0x28 or +0x10 until the queue head is empty; slot 16
//    (0x0049DEC8) calls +0x3C, then exits the object whose id is at +0x120. Slot 23
//    (0x0049D617) sets door [0..3]'s hold flag in the 0x10-byte records at +0x3C and, when
//    the door is idle, its open frame, its opening bit in +0xC8 and the dirty flag +0x114.
//  - Retail calls: AIPlayer::startTraining (0x004F2063) calls +0x44 and tests it against 0,
//    then +0x20 with seven arguments, the third the result of +0x08 called with none
//    (0x004F212F, 0x004F213B); 0x0049CC61 calls +0x28 with an entry's id. Object::defect
//    (0x00298CE7) and the DieModuleInterface thunk 0x0049CE63 call +0x40, not +0x3C.
//  - Types are the implementer rows' mangled types. Slots 10, 12 and 23-30 are rowed on
//    placeholder or shared classes; 10 and 23 take Zero Hour's types, 24 and 25 bool.
// Donor (Zero Hour ProductionUpdate.h) facts: the names. BFME2 keeps Zero Hour's slots 1-4,
// inserts slot 5 and others, and keeps Zero Hour's order for the named slots. A Zero Hour name
// is given where the implementer's row carries it or a body or call above pins it; slot 0
// does Zero Hour's canQueueCreateUnit test without its argument. Slots whose only name is the
// one implementer's placeholder row keep that rvaNNNNNNNN name; the rest are slotNN.
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef __BFME2_PRODUCTIONUPDATEINTERFACE_H_
#define __BFME2_PRODUCTIONUPDATEINTERFACE_H_

class AsciiString;
class ThingTemplate;
class UpgradeTemplate;
class Rva0049D1B1;
struct Rva0049D0DEMask;
enum CanMakeType;
enum ProductionID;
enum ExitDoorType;

//-------------------------------------------------------------------------------------------------
class ProductionUpdateInterface
{
public:
	ProductionUpdateInterface();

	virtual CanMakeType rva0049CFCD() const = 0;									// +0x00, 0x0049CFCD
	virtual CanMakeType canQueueUpgrade( const UpgradeTemplate *upgrade ) const = 0;	// +0x04
	virtual ProductionID requestUniqueUnitID() = 0;								// +0x08
	virtual bool queueUpgrade( const UpgradeTemplate *upgrade ) = 0;				// +0x0C
	virtual void cancelUpgrade( const UpgradeTemplate *upgrade ) = 0;				// +0x10
	virtual void rva0049CC9D( const ThingTemplate *, bool ) = 0;						// +0x14, 0x0049CC9D
	virtual bool isUpgradeInQueue( const UpgradeTemplate *upgrade ) const = 0;		// +0x18
	virtual unsigned int countUnitTypeInQueue( const ThingTemplate *unitType ) const = 0;	// +0x1C
	virtual bool queueCreateUnit( const ThingTemplate *unitType, int, ProductionID productionID,
		int, bool, const AsciiString &, bool ) = 0;									// +0x20
	virtual bool rva0049CC36( ProductionID ) const = 0;								// +0x24, 0x0049CC36
	virtual void cancelUnitCreate( ProductionID productionID ) = 0;				// +0x28, 0x0049DC50
	virtual void rva0049CC61( const ThingTemplate * ) = 0;								// +0x2C, 0x0049CC61
	virtual void slot12( int ) = 0;												// +0x30, 0x0049CCF0
	virtual void rva0049F8A9( const ThingTemplate *, bool ) = 0;						// +0x34, 0x0049F8A9
	virtual void rva0049CC15( ProductionID, int ) = 0;									// +0x38, 0x0049CC15
	virtual void cancelAndRefundAllProduction() = 0;								// +0x3C
	virtual void rva0049DEC8() = 0;													// +0x40, 0x0049DEC8
	virtual unsigned int getProductionCount() const = 0;							// +0x44
	virtual unsigned int rva0049CEAE( const ThingTemplate * ) const = 0;				// +0x48, 0x0049CEAE
	virtual unsigned int rva0049CEE1( int ) const = 0;									// +0x4C, 0x0049CEE1
	virtual unsigned int rva0049D0DE( const Rva0049D0DEMask * ) const = 0;				// +0x50, 0x0049D0DE
	virtual const Rva0049D1B1 *firstProduction() const = 0;						// +0x54
	virtual const Rva0049D1B1 *nextProduction( const Rva0049D1B1 *p ) const = 0;	// +0x58
	virtual void setHoldDoorOpen( ExitDoorType exitDoor, bool holdIt ) = 0;		// +0x5C
	virtual void slot24( bool ) = 0;												// +0x60, 0x003BA5D0
	virtual bool slot25() const = 0;												// +0x64, 0x002C8E83
	virtual float slot26( const ThingTemplate * ) = 0;							// +0x68, 0x0049D1CA
	virtual float slot27( const ThingTemplate * ) = 0;							// +0x6C, 0x0049D244
	virtual float slot28( unsigned char ) = 0;									// +0x70, 0x0049D2BE
	virtual float slot29( unsigned char ) = 0;									// +0x74, 0x0049D33D
	virtual bool slot30() const = 0;												// +0x78, 0x0049CF9E
};

#endif // __BFME2_PRODUCTIONUPDATEINTERFACE_H_
