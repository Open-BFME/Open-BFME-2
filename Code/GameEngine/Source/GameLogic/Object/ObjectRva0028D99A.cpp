// cl: /DNDEBUG /MD
// ?rva0028D99A@Object@@QAEX_N@Z, RVA 0x0028D99A, 75B. Object power dispatch gated by
// disabled mask and template+0x548: callers 0x002A9D35 0x002AD4EC; callees rowed
// ?any@?$BitFlags@$0L@@@QBE_NXZ +0x1C8, ?getControllingPlayer@Object@@QBEPAVPlayer@@XZ,
// ?rva004DF207@Rva004DF207@@QAEXPAX@Z / ?rva004DF231@Rva004DF231@@QAEXPAX@Z via Player+0x1BC.
template<int N>
class BitFlags
{
public:
	bool any() const;
};

struct ThingTemplate
{
	char m_pad[0x548];
	int m_val548;
};

class Player;
class Rva004DF207
{
public:
	void rva004DF207(void *arg);
};
class Rva004DF231
{
public:
	void rva004DF231(void *arg);
};

class Object
{
public:
	Player *getControllingPlayer() const;
	void rva0028D99A(bool flag);
private:
	char m_pad0[4];
	ThingTemplate *m_template004;
	char m_pad008[0x1C8 - 0x8];
public:
	BitFlags<11> m_disabled1C8;
};

void Object::rva0028D99A(bool flag)
{
	if (m_disabled1C8.any() && m_template004->m_val548 > 0)
		return;
	Player *player = getControllingPlayer();
	if (!player)
		return;
	Rva004DF207 *power = (Rva004DF207 *)((char *)player + 0x1BC);
	if (!power)
		return;
	if (flag)
		power->rva004DF207(this);
	else
		((Rva004DF231 *)power)->rva004DF231(this);
}
