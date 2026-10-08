// cl: /DNDEBUG /MD
//
// ?rva0047680E@HorseHordeContain@@UAEXPBUCoord3D@@H@Z, retail 0x0047680E, 17 bytes.
// Slot 42 of the vftable 0x00C45C38 whose slot-2 name getter returns
// "HorseHordeContain" (one of the four slots, 39 to 42, it adds over the
// 39-slot ??_7HordeContain 0x00C45050; AODHordeContain 0x00C46D28 inherits
// it). Forwards both arguments to the rowed AICommandInterface::aiMoveToPosition
// on the owning object's AI (Object+0x258, its AICommandInterface base at
// +0x20) as a tail jump. Address name: class and slot are proven, the
// method identity is not.

struct Coord3D
{
	float x;
	float y;
	float z;
};

// Zero Hour's AICommandInterface takes a CommandSourceType (row 0x0026C26D).
enum CommandSourceType { CMD_FROM_PLAYER = 0, CMD_FROM_SCRIPT, CMD_FROM_AI, CMD_FROM_DOZER, CMD_DEFAULT_SWITCH_WEAPON };
class AICommandInterface
{
public:
	void aiMoveToPosition(const Coord3D *pos, CommandSourceType cmdSource);
};

class AIUpdateInterfaceHead
{
	char m_unrecovered00[0x20];
};

class AIUpdateInterface : public AIUpdateInterfaceHead, public AICommandInterface
{
};

class Object
{
public:
	AIUpdateInterface *getAI() const { return m_ai; }
private:
	char m_unrecovered00[0x258];
	AIUpdateInterface *m_ai;
};

#define SLOT08(a,b,c,d,e,f,g,h) virtual void a(); virtual void b(); virtual void c(); virtual void d(); virtual void e(); virtual void f(); virtual void g(); virtual void h();

class HordeContain
{
public:
	SLOT08(s00,s01,s02,s03,s04,s05,s06,s07)
	SLOT08(s08,s09,s0A,s0B,s0C,s0D,s0E,s0F)
	SLOT08(s10,s11,s12,s13,s14,s15,s16,s17)
	SLOT08(s18,s19,s1A,s1B,s1C,s1D,s1E,s1F)
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26();
protected:
	Object *getObject() const { return m_object; }
private:
	void *m_moduleData;
	Object *m_object;
};

class HorseHordeContain : public HordeContain
{
public:
	virtual void s27();
	virtual void s28();
	virtual void s29();
	virtual void rva0047680E(const Coord3D *pos, int cmdSource);
};

// ?rva0047680E@HorseHordeContain@@UAEXPBUCoord3D@@H@Z @0x0047680E
void HorseHordeContain::rva0047680E(const Coord3D *pos, int cmdSource)
{
	getObject()->getAI()->aiMoveToPosition(pos, (CommandSourceType)cmdSource);
}
