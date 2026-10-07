// cl: /DNDEBUG /MD /GX-
// ?rva003F1AFF@Rva003F1AFF@@QAEXH@Z 0x003F1AFF 125: int-keyed broadcast.
// Evidence: rowed find 0x002B51F8 plus pin 0x002E0BC0 plus rowed broadcast
// 0x003F1A03 plus row 0x001FF3A9 forwarder; callers 0x003F2A8C 0x003F3F27;
// global g_009FEF10 mangled ?g_009FEF10@@3PAVRva002BA8F1Logic@@A.
class Rva002E2903Player;

// The native provider normalizes its bool result with movzx eax,al at
// 0x002E0BE0. Keep each caller's byte-sized test while naming its int ABI.
class Rva002E071E
{
public:
	int rva002E0BC0(int val);
};

class Rva002BA8F1Logic
{
public:
	Rva002E2903Player *find(int id, unsigned int *index);
	char m_pad98[0x98];
	Rva002E2903Player *m_98;
	char m_pad9C[0xFC - 0x9C];
	int m_FC;
};

extern Rva002BA8F1Logic *g_009FEF10;

struct Rva003F1AFF198
{
	char m_pad[0x18];
	int m_18;
};

class Rva003F119CListener
{
public:
	virtual void notify(void *, int, int);
};

struct Rva003F1A03
{
	void rva003F1A03(void (Rva003F119CListener::*notify)(void *, int, int), void *arg, int value, int extra);
};

struct TreeHintRef00217D4C;

class Rva001FF3A9
{
public:
	void rva001FF3A9(const TreeHintRef00217D4C &);
};

class Rva003F1AFF
{
private:
	char m_pad0[0x134];
	int m_134;
	int m_138;
	int m_13C;
	int m_140;
	char m_pad144[0x198 - 0x144];
	Rva003F1AFF198 *m_198;
public:
	void rva003F1AFF(int arg);
};

void Rva003F1AFF::rva003F1AFF(int arg)
{
	if (m_13C == arg)
		return;
	int old = m_13C;
	m_138 = g_009FEF10->m_FC;
	Rva002E2903Player *found = g_009FEF10->find(old, 0);
	if (found != 0)
	{
		if ((unsigned char)((Rva002E071E *)found)->rva002E0BC0(arg))
			goto broadcast;
	}
	m_134 = g_009FEF10->m_FC;
broadcast:
	m_13C = arg;
	m_140 = arg;
	m_198->m_18 = arg;
	((Rva003F1A03 *)this)->rva003F1A03((void (Rva003F119CListener::*)(void *, int, int))&Rva001FF3A9::rva001FF3A9, this, old, arg);
}
