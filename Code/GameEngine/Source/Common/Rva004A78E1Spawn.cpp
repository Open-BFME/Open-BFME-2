// cl: /O1 /DNDEBUG /MD
//
// ?rva004A78E1@MissileUpdate@@QAEXXZ @0x004A78E1 137B.
// Play the holder FX, and when the name at +0x11C is set, spawn the
// particle system onto +0xC8. Then store the frame at +0x98 and set state 3.

// class-gate: allow AsciiString address-only view for isEmpty and findTemplate.
class AsciiString
{
public:
	bool isEmpty() const;
};

class Object;

class FXList
{
public:
	static void doFXObj(const FXList *fx, const Object *primary, const Object *secondary);
};

class ParticleSystemTemplate;

class ParticleSystemManager
{
public:
	ParticleSystemTemplate *findTemplate(const AsciiString &name) const;
	int rva001F5AA4(const ParticleSystemTemplate *tmpl, const Object *obj, bool flag);
};

class GameLogic
{
public:
	char m_pad[0x40];
	int m_frame;
};

extern ParticleSystemManager *TheParticleSystemManager;
extern GameLogic *TheGameLogic;

class Holder
{
public:
	char m_pad[0xc4];
	int m_time;
	char m_gap[0xd4 - 0xc8];
	const FXList *m_fx;
	char m_gap2[0x11c - 0xd8];
	AsciiString m_name;
};

class MissileUpdate
{
public:
	void rva004A78E1();
	void Rva004A7530Set(int val);

private:
	char m_pad[4];
	Holder *m_holder;
	const Object *m_obj;
	char m_gap[0x98 - 0xc];
	int m_frame;
	char m_gap2[0xc8 - 0x9c];
	int m_slot;
	char m_gap3[1];
	unsigned char m_flag;
};

void MissileUpdate::rva004A78E1()
{
	Holder *holder = m_holder;
	FXList::doFXObj(holder->m_fx, m_obj, 0);
	AsciiString &name = holder->m_name;
	if (name.isEmpty() == 0) {
		ParticleSystemTemplate *tmpl = TheParticleSystemManager->findTemplate(name);
		if (tmpl != 0) {
			const Object *obj = m_obj;
			m_slot = TheParticleSystemManager->rva001F5AA4(tmpl, obj, 1);
		}
	}
	m_flag = 1;
	int t = holder->m_time;
	int frame;
	if (t != 0)
		frame = TheGameLogic->m_frame + t;
	else
		frame = 0x7fffffff;
	m_frame = frame;
	Rva004A7530Set(3);
}
