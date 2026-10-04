// ?rva00589297@WeaponModeSpecialPowerUpdateBase@@QAE_NXZ
// partial score=0.96 date=2026-10-04
// cl: /O1 /DNDEBUG /MD /EHsc /arch:SSE
// ?rva00589297@WeaponModeSpecialPowerUpdateBase@@QAE_NXZ retail 0x00589297 95B vslot 1 of 0x00870108 via rowed BitFlags plus slot6 virtual plus TheGameLogic
template<int N>
class BitFlags
{
public:
	bool any() const;
};

class Overridable
{
public:
	virtual void overridableAnchor();
	const Overridable *friend_getFinalOverride() const;
	unsigned char m_pad04[0x55];
	unsigned char m_hasOverride;
};

class SpecialPowerTemplate;
class Player;

class Object
{
public:
	Player *getControllingPlayer() const;
};

class Rva002AC6B1PlayerTimers
{
public:
	unsigned int getOrStart(const SpecialPowerTemplate *tmpl);
};

class GameLogic
{
public:
	unsigned char m_pad00[0x40];
	int m_frame40;
};

extern GameLogic *TheGameLogic;

struct VirtPrimary
{
	virtual void f0();
	virtual void f1();
	virtual void f2();
	virtual void f3();
	virtual void f4();
	virtual void f5();
	virtual const Overridable *f6() const;
};

class WeaponModeSpecialPowerUpdateBase
{
public:
	bool rva00589297();
private:
	unsigned char m_pad00[4];
	int m_04;
	int m_08;
	int m_0C;
};

// ?rva00589297@WeaponModeSpecialPowerUpdateBase@@QAE_NXZ present-unmatched
bool WeaponModeSpecialPowerUpdateBase::rva00589297()
{
	Object *outer = *(Object **)((char *)this - 0x1c);
	void *p2 = *(void **)((char *)this - 0x20);
	if (outer != 0) {
		Player *player = outer->getControllingPlayer();
		if (player != 0) {
			const SpecialPowerTemplate *tmpl = *(const SpecialPowerTemplate **)((char *)p2 + 8);
			const Overridable *fin = ((const Overridable *)tmpl)->friend_getFinalOverride();
			if (fin->m_hasOverride != 0) {
				unsigned int frame = (unsigned int)TheGameLogic->m_frame40;
				unsigned int ready = ((Rva002AC6B1PlayerTimers *)player)->getOrStart(tmpl);
				return frame >= ready;
			}
		}
	}
	if (m_08 == 0) {
		unsigned int frame2 = (unsigned int)TheGameLogic->m_frame40;
		if (frame2 >= (unsigned int)m_04)
			return true;
	}
	return false;
}
