// cl: /O1 /EHsc /MD
// ?rva0042C936@Rva0042C936@@QAEPAV1@UHolder0042C936@@@Z, retail 0x0042C936, 65 bytes.
// Setter with ownership-transfer holder: takes old at +0, stores released holder ptr,
// calls old virtual slot0 with 0, deletes returned pointer via rowed operator delete,
// returns this. Evidence: single caller 0x0042CA4B, __thiscall via ecx plus ret 4,
// chain sibling of 0x0042C1F9 with identical 65B shape and same // cl.
void __cdecl operator delete(void *p);

struct Rva0042C936Helper
{
	virtual void *virt0(int x);
};

namespace _STL
{
	template <class _Tp>
	struct auto_ptr
	{
		~auto_ptr() { delete _M_p; }
		_Tp *release() { _Tp *p = _M_p; _M_p = 0; return p; }
		_Tp *_M_p;
	};
}

class Rva0042C993Pointee
{
public:
	virtual ~Rva0042C993Pointee();
};

struct Holder0042C936
{
	Holder0042C936(_STL::auto_ptr<Rva0042C993Pointee> &a) : p(reinterpret_cast<Rva0042C936Helper *>(a.release())) {}
	Rva0042C936Helper *p;
	~Holder0042C936();
	Rva0042C936Helper *release();
};

class Rva0042C936
{
public:
	Rva0042C936Helper *m_ptr;
	Rva0042C936 *rva0042C936(Holder0042C936 h);
};

// ??1Holder0042C936@@QAE@XZ present-unmatched
inline Holder0042C936::~Holder0042C936()
{
	if (p)
		::operator delete(p);
}

// ?release@Holder0042C936@@QAEPAURva0042C936Helper@@XZ present-unmatched
inline Rva0042C936Helper *Holder0042C936::release()
{
	Rva0042C936Helper *t = p;
	p = 0;
	return t;
}

Rva0042C936 *Rva0042C936::rva0042C936(Holder0042C936 h)
{
	Rva0042C936Helper *old = m_ptr;
	m_ptr = h.release();
	void *q = old ? old->virt0(0) : 0;
	::operator delete(q);
	return this;
}

// ?rva0042CA4B@Rva0042CA4B@@QAEXXZ, retail 0x0042CA4B, 146 bytes (EH), reached
// through the pinned 7B thunk 0x0042CADD (mov ecx [ecx]; jmp). Once the
// living world exists and its pinned 0x0004253A check passes, clears the
// byte at +0x94 of the +0x08 object; when the logic's +0xF4 value differs
// from the one cached at +0x10, clears the +0x14 holder (rowed 0x000AD6F4),
// hands it the object the banked factory 0x0042C9BA (pinned) builds for that
// value and the +0x08 object -- the holder's constructor releases the
// factory's auto_ptr straight into the setter's by-value argument, as an
// auto_ptr conversion does -- and caches the value. The emptied auto_ptr's
// destructor (a virtual delete) runs after the call.
namespace StrategicInGameUI
{
	_STL::auto_ptr<Rva0042C993Pointee> Rva0042C9BAFactory(int kind, int argument);
}

class LivingWorldLogic
{
public:
	bool rva0004253A() const;
	unsigned char m_pad00[0xf4];
	int m_f4;	// +0xF4
};
extern LivingWorldLogic *TheLivingWorldLogic;

class Rva000AD6F4
{
public:
	void clear();
};

struct Rva0042CA4BTarget
{
	unsigned char m_pad00[0x94];
	bool m_94;	// +0x94
};

class Rva0042CA4B
{
public:
	void rva0042CA4B();
private:
	unsigned char m_pad00[0x08];
	Rva0042CA4BTarget *m_08;	// +0x08
	unsigned char m_pad0C[0x04];
	int m_10;					// +0x10
	Rva0042C936 m_14;			// +0x14
};

void Rva0042CA4B::rva0042CA4B()
{
	if (TheLivingWorldLogic && TheLivingWorldLogic->rva0004253A())
	{
		m_08->m_94 = false;
		int value = TheLivingWorldLogic->m_f4;
		if (value != m_10)
		{
			reinterpret_cast<Rva000AD6F4 *>(&m_14)->clear();
			m_14.rva0042C936(StrategicInGameUI::Rva0042C9BAFactory(value, (int)m_08));
			m_10 = value;
		}
	}
}
