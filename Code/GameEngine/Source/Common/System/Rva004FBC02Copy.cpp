// cl: /Ireference/shims/bfme2_ascii
#include "unicode_string.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"
// ?rva004FBC02@Rva004FBC02@@QAEXPBURva004FBC02Src@@@Z 0x004FBC02 21: copies 12 bytes
// from arg to +0x18 and sets byte at +0x24 to 1. Evidence: callers 0x002BA331 and
// 0x002BA7E1 pass a pointer; no other callees.

struct Rva004FBC02Src
{
	int m_0;
	int m_4;
	int m_8;
};

class __single_inheritance Rva004FBC02;
typedef void (Rva004FBC02::*DelegateMethod)(int);
#include "../../../Include/Common/DelegateDesc.h"
// Builds the bound-method descriptor; retail stores the method first, through
// a register, as this helper's parameter copy does.
template <class T> inline DelegateDesc MakeDesc(T *object, void (T::*method)(int))
{
	DelegateDesc desc;
	desc.field00 = object;
	desc.field04 = *reinterpret_cast<void **>(&method);
	return desc;
}
class Rva00579E47 { public: Rva00579E47() {} Rva00579E47(const DelegateDesc &); void *ptr; };
struct TreeHintRef00217D4C : public Rva00579E47
{
	TreeHintRef00217D4C() { ptr = 0; }
	TreeHintRef00217D4C(const DelegateDesc &delegateDesc) : Rva00579E47(delegateDesc) {}
	TreeHintRef00217D4C(const TreeHintRef00217D4C &sourceRef) : Rva00579E47(sourceRef) { if (ptr) ++((int *)ptr)[1]; }
	~TreeHintRef00217D4C();
};
#include "../../../Include/Common/Rva0054D2DDTarget.h"
class AptStrategicMessageBox { private: static AptStrategicMessageBox *s_instance; public: static __forceinline AptStrategicMessageBox *get() { return s_instance; } };
enum EvaEventID { EVA_EVENT_STUB = 0 };
#include "../../../Include/GameClient/Eva.h"
extern Eva *TheEva;

class Rva004FBC02
{
private:
	char m_pad04[4];
	UnicodeString m_text;	// +0x08
	UnicodeString m_title;	// +0x0C
	int m_mode;		// +0x10
	int m_event;		// +0x14
	Rva004FBC02Src m_18;
	unsigned char m_24;
	bool m_25;
	bool m_26;
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	void rva004FBBEB(int response);
	void rva004FBC02(const Rva004FBC02Src *src);
	void rva004FBD3A();
	int getMode() const { return m_mode; }
};

// Native4FBBEB..4FBC02 RET4; 4FBD3A stores VA8FBBEB as its delegate.
// Response3 clears25 and sets26 before dispatching owner virtual slot2.
void Rva004FBC02::rva004FBBEB(int response)
{
    if (response == 3) {
        m_25 = false;
        m_26 = true;
        slot2();
    }
}

void Rva004FBC02::rva004FBC02(const Rva004FBC02Src *src)
{
	m_18 = *src;
	m_24 = 1;
}

// ?rva004FBD3A@Rva004FBC02@@QAEXXZ 0x004FBD3A 118: when the strategic
// message box exists, shows this message (mode, text, title) with no first
// callback and 0x004FBBEB bound to this as the second, marks it shown,
// reports its EVA event (at the +0x18 position when +0x24 is set) and runs
// slot 1. The mode goes through an inline accessor, which loads it before
// the string arguments as retail does.
void Rva004FBC02::rva004FBD3A()
{
	Rva0054D2DDTarget *box = (Rva0054D2DDTarget *)AptStrategicMessageBox::get();
	if (box) {
		box->method(getMode(), m_text, m_title, TreeHintRef00217D4C(),
			TreeHintRef00217D4C(MakeDesc(this, &Rva004FBC02::rva004FBBEB)));
		m_25 = true;
		TheEva->reportEvaEvent((EvaEventID)m_event, m_24 ? (const Coord3D *)&m_18 : 0, 0);
		slot1();
	}
}

// ?rva004FBDB0@RegionAwardDispute@@QAEX_N@Z 0x004FBDB0 28: forwards its flag to slot-12
// virtual on the object looked up by this+0x18 key in the global map at 0x009FE1C8
// via rowed Rva002120A4::rva002120A4; returns on miss. Evidence: callers 0x004FBFF4
// and 0x004FC0E2 (in 0x004FC0AD) pass 0/1; the latter pushes a sete result
// without widening it, so the argument is a bool; callees rowed.

enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

class Rva002120A4
{
public:
	int rva002120A4(NameKeyType key);
};

class Rva0021294A;
class LivingWorldManager; extern LivingWorldManager *TheLivingWorldManager;

// Slot-12 target is unidentified; dummies pad the vtable so slot12 lands at +0x30.
class Rva004FBDB0Target
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void slot12(bool arg);
};

class RegionAwardDispute
{
private:
	char m_pad[0x18];
	NameKeyType m_key;
public:
	void rva004FBDB0(bool arg);
};

void RegionAwardDispute::rva004FBDB0(bool arg)
{
	int found = ((Rva002120A4 *)TheLivingWorldManager)->rva002120A4(m_key);
	if (found == 0)
		return;
	((Rva004FBDB0Target *)found)->slot12(arg);
}

// ?rva004FBDCC@Rva004FBDCC@@QAEXXZ 0x004FBDCC 19: pushes this+0x18 then sets
// byte at +0x1c to 1 and forwards the int to Rva00DFE1C8Host::rva00212655
// through global TheLivingWorldManager. Evidence: pin 0x00212655 plus caller 0x002BAF01.
#include "../../../Include/Common/Rva00DFE1C8Host.h"

class Rva004FBDCC
{
private:
	char m_pad[0x18];
	int m_18;
	bool m_1c;
public:
	void rva004FBDCC();
};

void Rva004FBDCC::rva004FBDCC()
{
	m_1c = true;
	((Rva00DFE1C8Host *)TheLivingWorldManager)->rva00212655(m_18);
}
