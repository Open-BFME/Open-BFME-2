// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
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

class Object;

class TurretStateMachine
{
public:
	Object *getGoalObject();
};

class AIUpdateInterface
{
public:
	unsigned char m_pad00[0x30];
	TurretStateMachine *m_stateMachine;
};

class ThingTemplate
{
public:
	unsigned char m_pad00[0x115];
	unsigned char m_kindOf115;
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

class ContainModuleInterface
{
public:
	virtual void c00();
	virtual void c01();
	virtual void c02();
	virtual void c03();
	virtual void c04();
	virtual void c05();
	virtual void c06();
	virtual void c07();
	virtual void c08();
	virtual void c09();
	virtual void c10();
	virtual void c11();
	virtual void c12();
	virtual void c13();
	virtual void c14();
	virtual void c15();
	virtual void c16();
	virtual void c17();
	virtual void c18();
	virtual void c19();
	virtual void c20();
	virtual void c21();
	virtual void c22();
	virtual void c23();
	virtual void c24();
	virtual void c25();
	virtual void c26();
	virtual void c27();
	virtual void c28();
	virtual void c29();
	virtual void c30();
	virtual Rva0047DE6CRiderInterface *c31();
	virtual void c32();
	virtual void c33();
	virtual void c34();
	virtual void c35();
	virtual void c36();
	virtual void c37();
	virtual void c38();
	virtual void c39();
	virtual void c40();
	virtual void removeFromContain( Object *obj, int exposeStealthUnits ) = 0;
};

class Object
{
public:
	ContainModuleInterface *getContain() const { return m_contain; }
	AIUpdateInterface *getAI() const { return m_ai; }
	void *m_vtable;
	const ThingTemplate *m_template;
	unsigned char m_pad08[0x250 - 0x08];
	ContainModuleInterface *m_contain;
	unsigned char m_pad254[0x258 - 0x254];
	AIUpdateInterface *m_ai;
};

class TunnelContainPrimary
{
public:
	virtual void primarySlot00();
	const void *m_moduleData;
	Object *m_object;
	unsigned char m_pad0C[0x20 - 0x0C];
};

class TunnelContain : public TunnelContainPrimary, public ContainModuleInterface
{
public:
	virtual void removeFromContain( Object *obj, int exposeStealthUnits );
};

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

	if( ( obj->m_template->m_kindOf115 & 0x20 ) == 0 )
		return;

	ContainModuleInterface *contain = obj->getContain();
	if( contain == 0 )
		return;

	Rva0047DE6CRiderInterface *rider = contain->c31();
	if( rider == 0 )
		return;

	if( rider->x61() )
		return;

	TunnelContain *tunnelContain = static_cast<TunnelContain *>( tunnel->getContain() );
	tunnelContain->removeFromContain( obj, 1 );
}
