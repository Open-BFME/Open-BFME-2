// cl: /O1 /DNDEBUG /MD /arch:SSE
// Native 0039E76C..0039E7F2 /134B. Team member damage dispatch: live
// members without status94 bit0 are killed with damage-kind8 if f<0;
// otherwise the existing7C damage record is built and submitted. The
// original method name and field labels remain unresolved. The loop uses
// the existing24B Team cursor and owned Object advance provider263526.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
typedef unsigned int UnsignedInt;
class PolygonTrigger;
template<class OBJCLASS>
class DLINK_ITERATOR
{
private:
	OBJCLASS *m_cur;
	unsigned char m_targetAbiState[20];

public:
	void advance();
	bool done() const { return m_cur == 0; }
	OBJCLASS *cur() const { return m_cur; }
};

class AIUpdateInterface
{
public:
	unsigned char m_pad[0x1dc];
	UnsignedInt m_surfaces;
};

struct ThingTemplate
{
	unsigned char m_pad[0x113];
	unsigned char m_kindByte113;
	unsigned char m_pad2[0x118 - 0x114];
	unsigned char m_kindByte118;
};

enum DamageType { DamageType_Unknown };
enum DeathType { DeathType_Unknown };
class DamageInfo;

class Rva00263653
{
public:
	Rva00263653() throw();
	char m_data[0x68];
};

class Rva00263895Member
{
public:
	Rva00263895Member() throw();
	virtual void rva00263895_dummy();

private:
	Rva00263653 m_mem;
	const void *m_ptr;
	float m_f70;
	float m_f74;
	unsigned char m_b78;
};

class Object
{
public:
	bool didEnter(PolygonTrigger *pTrigger);
	bool didExit(PolygonTrigger *pTrigger);
	bool isInside(PolygonTrigger *pTrigger);
	void kill(DamageType damageType, DeathType deathType);
	void attemptDamage(DamageInfo *damageInfo);

public:
	unsigned char m_pad0[4];
	ThingTemplate *m_template;
	unsigned char m_pad1a[0x94 - 0x8];
	unsigned char m_byte94;
	unsigned char m_pad1b[0x258 - 0x94 - 1];
	AIUpdateInterface *m_ai;
	unsigned char m_pad2[0x438 - 0x25c];
	unsigned char m_dead;
};

class Team {
public:
 DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
 bool rva0039E76C(float);
};
bool Team::rva0039E76C(float f)
{
	for (DLINK_ITERATOR<Object> iter = iterate_TeamMemberList(); ; iter.advance()) {
		Object *cur = iter.cur();
		_ReadWriteBarrier();if (cur == 0)
			break;
		if ((cur->m_dead & 1) != 0)
			continue;
		if ((cur->m_byte94 & 1) != 0)
			continue;
		if (f < 0.0) {
			cur->kill((DamageType)8, (DeathType)0);
		} else {
			Rva00263895Member info;
			*(int *)((char *)&info + 0x1c) &= 0;
			*(int *)((char *)&info + 0x08) &= 0;
			*(int *)((char *)&info + 0x10) = 8;
			*(float *)((char *)&info + 0x20) = f;
			cur->attemptDamage((DamageInfo *)&info);
		}
	}
	return false;
}
