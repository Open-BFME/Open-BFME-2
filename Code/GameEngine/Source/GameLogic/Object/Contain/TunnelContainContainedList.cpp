// cl: /O1 /DNDEBUG /MD
// stlport
// ?rva0047DD0F@TunnelContain@@UAE?AVRva0036AE51ListView@@XZ retail
// 0x0047DD0F, 30 bytes: slot 33 of TunnelContain's primary vtable
// (0x00847740; its object pointer is the +0x08 member, as in
// TunnelContain.cpp). Zero Hour's TunnelContain answers its contained-items
// list from the owning player's tunnel system; BFME 2 returns the tunnel
// tracker's (+0x2E8) two-pointer list view by value through the rowed
// Rva00466398::rva00466398 0x00466398, with no null checks.
#include <list>
#include "../../../../Include/GameLogic/ContainmentListView.h"

class Rva00466398
{
public:
	Rva0036AE51ListView rva00466398();
};

class Player
{
public:
	unsigned char m_pad000[0x2E8];
	Rva00466398 *m_2E8;
};

class Object
{
public:
	Player *getControllingPlayer() const;
};

class TunnelContain
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void s06();
	virtual void s07();
	virtual void s08();
	virtual void s09();
	virtual void s10();
	virtual void s11();
	virtual void s12();
	virtual void s13();
	virtual void s14();
	virtual void s15();
	virtual void s16();
	virtual void s17();
	virtual void s18();
	virtual void s19();
	virtual void s20();
	virtual void s21();
	virtual void s22();
	virtual void s23();
	virtual void s24();
	virtual void s25();
	virtual void s26();
	virtual void s27();
	virtual void s28();
	virtual void s29();
	virtual void s30();
	virtual void s31();
	virtual void s32();
	virtual Rva0036AE51ListView rva0047DD0F();
private:
	const void *m_moduleData;
	Object *m_object;
};

Rva0036AE51ListView TunnelContain::rva0047DD0F()
{
	Player *owningPlayer = m_object->getControllingPlayer();
	return owningPlayer->m_2E8->rva00466398();
}
