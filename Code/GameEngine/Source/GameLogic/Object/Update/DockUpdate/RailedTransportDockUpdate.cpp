// cl: /Ob0 /MD /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB
// stlport
// BFME 2 has no RailedTransportDockUpdate: game.dat holds no such module name and no row is
// one of its methods but the first below. Three rows rest in this file until their addresses
// are settled: the null-checked +0x0C to +0x88 cast at 0x004B01D9 (slot 3 of retail's table
// 0x00C562D8), DockUpdate's setDockOpen at 0x004A0DFC, and 0x004B01E6.

class RailedTransportDockUpdateInterface
{
public:
	virtual void slot0();
};

class RailedDockPrimary
{
public:
	virtual void slot0();

private:
	char m_pad04[8];
};

class RailedDockBehavior
{
public:
	virtual RailedTransportDockUpdateInterface *getRailedTransportDockUpdateInterface() = 0;

private:
	char m_pad04[0x78];
};

class RailedTransportDockUpdate : public RailedDockPrimary, public RailedDockBehavior, public RailedTransportDockUpdateInterface
{
public:
	virtual RailedTransportDockUpdateInterface *getRailedTransportDockUpdateInterface() { return this; }
};

class DockUpdate
{
public:
	virtual void setDockOpen(bool open) { m_dockOpen = open; }

private:
	char m_pad04[0x62];
	bool m_dockOpen; // +0x66
};

// A virtual's address is a call thunk, so only a direct call makes this unit emit the two
// bodies, and /Ob0 keeps those calls out of line. Nothing here is ever run.
static void callDockRows(RailedTransportDockUpdate *dock, DockUpdate *update)
{
	dock->RailedTransportDockUpdate::getRailedTransportDockUpdateInterface();
	update->DockUpdate::setDockOpen(true);
}

extern const void *const g_dockRowsAnchor = (const void *)&callDockRows;

// The callee at 0x0044FC52 is the rowed virtual
// SpecialAbilityUpdate::continuePreparation, called directly.
#include "../../../../../Include/GameLogic/Module/SpecialAbilityUpdate.h"

class Rva004B01E6Owner
{
public:
	bool rva004B01E6();

private:
	char m_pad00[0x24];
	int m_24;
};

// ?rva004B01E6@Rva004B01E6Owner@@QAE_NXZ
bool Rva004B01E6Owner::rva004B01E6()
{
	if (m_24 == 2)
		return false;
	return ((SpecialAbilityUpdate *)this)->SpecialAbilityUpdate::continuePreparation();
}
