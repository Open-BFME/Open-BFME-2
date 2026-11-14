// The LANAPICallbacks TU's layout views of the LAN game chain, shared by the
// seed and its donors ahead of a merge so every unit spells one view of each
// class. LANAPI_OnAccept.cpp shares these verbatim; canonical GameInfo.h is
// the skirmish flavor (Snapshot-derived) and is a different retail class, not
// this chain's home. Names follow Zero Hour's GameInfo.h where established;
// the game-info chain keeps the ledger's names for getLANSlot (0x00447773)
// and the LANGameInfo destructor row (0x004482FB).
#ifndef CANONICAL_LANGAMEVIEWS_H
#define CANONICAL_LANGAMEVIEWS_H

typedef int Int;
typedef bool Bool;
typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;

#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"
#include "../../../../reference/shims/bfme2_ascii/unicode_string.h"
#include "BfmeNetAddress.h"

enum
{
	MAX_SLOTS = 8
};
class GameSlot
{
public:
	GameSlot( void );
	virtual ~GameSlot( void );
	UnsignedByte encodeHero( void ) const;
	void setMapAvailability( Bool hasMap );
	Bool isHuman( void ) const;
	Bool decodeHero( UnsignedByte hero );
	void setPlayerTemplate( Int playerTemplate );
	Int getColor( void ) const { return m_color; }
	void setColor( Int color ) { m_color = color; }
	Int getStartPos( void ) const { return m_startPos; }
	void setStartPos( Int startPos ) { m_startPos = startPos; }
	void setBfme14( Int startPos ) { m_bfme14 = startPos; }
	Int getPlayerTemplate( void ) const { return m_playerTemplate; }
	Int getTeamNumber( void ) const { return m_teamNumber; }
	__declspec(dllimport) __forceinline void setTeamNumber( Int teamNumber ) { m_teamNumber = teamNumber; }
	void setHandicap( Int handicap ) { m_handicap = handicap; }
	void setNATBehavior( Int behavior ) { m_NATBehavior = behavior; }
	void unAccept();
	const UnicodeString &getName( void ) const { return m_name; }

private:
	UnsignedByte m_pre08[0x08 - 0x04];

public:
	Bool m_isAccepted;				// +0x08

private:
	Int m_color;					// +0x0C
	Int m_startPos;					// +0x10
	Int m_bfme14;					// +0x14, set with the start position
	Int m_playerTemplate;				// +0x18
	Int m_teamNumber;				// +0x1C
	Int m_handicap;					// +0x20
	UnsignedByte m_pre30[0x30 - 0x24];
	UnicodeString m_name;				// +0x30
	UnsignedByte m_pre38[0x38 - 0x34];

public:
	BfmeNetAddress m_address;			// +0x38
	Int m_NATBehavior;				// +0x40
	UnsignedByte m_pre4C[0x4C - 0x44];
	Int m_bfme4C;					// +0x4C, the living-world battle's index
	Int m_hero[4];					// +0x50, what decodeHero sets
	UnsignedByte m_pre1A4[0x1A4 - 0x60];
	Bool m_bfme1A4;					// +0x1A4
	UnsignedByte m_pre1AC[0x1AC - 0x1A5];
};
// The LAN slot's login and host setters (0x0024955E, 0x00249595).
class LANGameSlot : public GameSlot
{
public:
	void setLogin( AsciiString login );
	void setHost( AsciiString host );
};
struct LANSlotAddress
{
	UnsignedByte m_pre38[0x38];
	BfmeNetAddress m_address;			// slot +0x38
	UnsignedByte m_rest[0x1D0 - 0x40];
};
class GameInfo
{
public:
	virtual ~GameInfo();
	virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
	virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8();
	virtual void v9(); virtual void v10();
	virtual void startGame( Int gameID );		// slot 11 (+0x2C)
	virtual void v12(); virtual void v13();
	virtual void resetAccepted( void );		// slot 14 (+0x38)

	GameSlot *getSlot( Int slotNum );
	AsciiString getMap( void ) const;
	void setMapForwarder( AsciiString mapName );

	__declspec(dllimport) __forceinline Bool isGameInProgress( void ) const { return m_inProgress; }
	UnsignedInt getSeed( void ) const { return m_seed; }

protected:
	UnsignedByte m_pre11[0x11 - 4];
	Bool m_inProgress;				// +0x11
	UnsignedByte m_pre38[0x38 - 0x12];

public:
	BfmeNetAddress m_localAddress;			// +0x38

protected:
	UnsignedByte m_pre50[0x50 - 0x40];
	UnsignedInt m_seed;				// +0x50
	UnsignedByte m_pre58[0x58 - 0x54];

public:
	Int m_bfme58;					// +0x58
	Int m_gameMode;					// +0x5C, the preferences' mode

protected:
	UnsignedByte m_pre8C[0x8C - 0x60];

public:
	Bool m_bfme8C;					// +0x8C, keeps the preferred side

protected:
	UnsignedByte m_preDC[0xDC - 0x8D];
	LANSlotAddress m_slots[MAX_SLOTS];		// +0xDC, addresses from +0x114
};
// LANGameInfo, under the ledger's names for the classes of its getLANSlot
// (0x00447773) and its destructor (0x004482FB).
class Rva00447773 : public GameInfo
{
public:
	void *getLANSlot( Int index );			// getLANSlot

	const BfmeNetAddress *getSlotAddress( Int index ) const { return &m_slots[index].m_address; }
};
class Rva004482FB : public Rva00447773
{
public:
	Int getSlotNum( UnicodeString name );		// getSlotNum

	const BfmeNetAddress *getHostAddress( void ) const { return &m_slots[0].m_address; }
};
class LANGameInfo : public Rva004482FB
{
public:
	Bool amIHost( void ) const;
	void setLastHeard( UnsignedInt lastHeard ) { m_lastHeard = lastHeard; }

private:
	UnsignedInt m_preF60;
	UnsignedInt m_lastHeard;			// +0xF60
};

#endif // CANONICAL_LANGAMEVIEWS_H
