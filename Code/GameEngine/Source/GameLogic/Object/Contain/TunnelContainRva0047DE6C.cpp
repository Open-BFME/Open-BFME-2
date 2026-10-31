// cl: /MD /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /I.
// stlport
// Retail 0x0047DE6C, 117B: a TunnelContain contained-object visitor
// (cdecl (Object *, void *userData), the tunnel Object as user data).
// Target evidence: an object whose AI state machine (AI at Object+0x258,
// machine at +0x30) has the tunnel as goal object (TurretStateMachine::
// getGoalObject 0x004D7726), whose template has kind-of bit 0x115:0x20 set,
// and whose contain module (Object+0x250, slot 0x7C) yields an interface
// whose slot 0xF4 test is false, is removed from the tunnel with
// exposeStealthUnits set: the tunnel's contain pointer is cast down to
// TunnelContain (null-checked) and removeFromContain (slot 0xA4 of the
// contain interface at +0x20) is called. The owner and purpose are not
// otherwise named; the function keeps an address-derived name.

#include "TunnelContainView.h"

class TurretStateMachine
{
public:
	Object *getGoalObject();
};

class Rva0047DE6CRiderInterface
{
public:
	virtual void x00();
	virtual void x01();
	virtual void x02();
	virtual void x03();
	virtual void x04();
	virtual void x05();
	virtual void x06();
	virtual void x07();
	virtual void x08();
	virtual void x09();
	virtual void x10();
	virtual void x11();
	virtual void x12();
	virtual void x13();
	virtual void x14();
	virtual void x15();
	virtual void x16();
	virtual void x17();
	virtual void x18();
	virtual void x19();
	virtual void x20();
	virtual void x21();
	virtual void x22();
	virtual void x23();
	virtual void x24();
	virtual void x25();
	virtual void x26();
	virtual void x27();
	virtual void x28();
	virtual void x29();
	virtual void x30();
	virtual void x31();
	virtual void x32();
	virtual void x33();
	virtual void x34();
	virtual void x35();
	virtual void x36();
	virtual void x37();
	virtual void x38();
	virtual void x39();
	virtual void x40();
	virtual void x41();
	virtual void x42();
	virtual void x43();
	virtual void x44();
	virtual void x45();
	virtual void x46();
	virtual void x47();
	virtual void x48();
	virtual void x49();
	virtual void x50();
	virtual void x51();
	virtual void x52();
	virtual void x53();
	virtual void x54();
	virtual void x55();
	virtual void x56();
	virtual void x57();
	virtual void x58();
	virtual void x59();
	virtual void x60();
	virtual bool x61();
};

// Keep the native +0x250 load inline; omit the competing legacy getter.
void Rva0047DE6CVisit( Object *obj, void *userData )
{
	if( obj == 0 )
		return;

	Object *tunnel = (Object *)userData;
	if( tunnel == 0 )
		return;

	AIUpdateInterface *ai = obj->getAI();
	if( ai == 0 )
		return;

	if( ai->m_stateMachine->getGoalObject() != tunnel )
		return;

	if( ( obj->getTemplate()->m_kindOf115 & 0x20 ) == 0 )
		return;

	ContainModuleInterface *contain = obj->getContain();
	if( contain == 0 )
		return;

	Rva0047DE6CRiderInterface *rider = contain->c31();
	if( rider == 0 )
		return;

	if( rider->x61() )
		return;

	TunnelContain *tunnelContain = static_cast<TunnelContain *>( reinterpret_cast<B20 *>(tunnel->getContain()) );
	tunnelContain->removeFromContain( obj, 1 );
}
