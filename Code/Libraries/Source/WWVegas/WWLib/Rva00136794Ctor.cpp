// cl: /O1 /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /arch:SSE
// stlport
// ??0Rva00136794@@QAE@PBD0MPBVRva0013101E@@ABV?$vector@VAsciiString@@V?$allocator@VAsciiString@@@_STL@@@_STL@@22@Z @0x00136794 (145B): chain ctor calls GenBase 0x0061ED40 then vtable 0x007D2970; StringBase private ctors 0x00037BA0 at +0x14/+0x18 from s1/s2; vector copies 0x000BC07E at +0x1C/+0x28/+0x34 from v1/v2/v3; float f at +0x40 via movss; Rva copy 0x0013101E at +0x44 from r; int 0 at +0x54; ret 0x1C (7 args).
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class AsciiString;

namespace _STL {
template <typename T>
class allocator
{
};
template <typename T, typename A>
class vector
{
public:
	vector(const vector &other);
	~vector();
private:
	void *m_start;
	void *m_finish;
	void *m_end;
};
}

class __declspec(novtable) GenBase009EB7D0
{
public:
	__declspec(noinline) GenBase009EB7D0();
	virtual ~GenBase009EB7D0() { _ReadWriteBarrier(); }
	virtual void handle();
private:
	unsigned int m_flags;
	unsigned int m_zero08;
	unsigned int m_zero0c;
	unsigned int m_zero10;
};

template <typename T>
class StringBase
{
private:
	StringBase(const T *str);
	~StringBase();
	friend class Rva00136794;
public:
	void set(const T *str, int len);
private:
	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};
	Header *m_data;
};

class Rva0013101E
{
public:
	Rva0013101E &rva0013101E(Rva0013101E const *src) throw();
	unsigned m_a : 3;
	unsigned m_b : 27;
	unsigned m_c : 1;
	unsigned m_keep : 1;
	unsigned m_d1;
	unsigned m_d2;
	unsigned m_d3;
};

struct RefM54 {
    virtual void vf0();
    int m_ref;
};

class Rva00136794 : public GenBase009EB7D0
{
public:
	Rva00136794(const char *s1, const char *s2, float f, const Rva0013101E *r, const _STL::vector<AsciiString, _STL::allocator<AsciiString> > &v1, const _STL::vector<AsciiString, _STL::allocator<AsciiString> > &v2, const _STL::vector<AsciiString, _STL::allocator<AsciiString> > &v3);
	virtual ~Rva00136794();
	void rva00135E6D();
private:
	StringBase<char> m_s1;
	StringBase<char> m_s2;
	_STL::vector<AsciiString, _STL::allocator<AsciiString> > m_v1;
	_STL::vector<AsciiString, _STL::allocator<AsciiString> > m_v2;
	_STL::vector<AsciiString, _STL::allocator<AsciiString> > m_v3;
	float m_f40;
	Rva0013101E m_r44;
	struct RefM54 *m_54;
};

Rva00136794::Rva00136794(const char *s1, const char *s2, float f, const Rva0013101E *r, const _STL::vector<AsciiString, _STL::allocator<AsciiString> > &v1, const _STL::vector<AsciiString, _STL::allocator<AsciiString> > &v2, const _STL::vector<AsciiString, _STL::allocator<AsciiString> > &v3)
	: m_s1(s1)
	, m_s2(s2)
	, m_v1(v1)
	, m_v2(v2)
	, m_v3(v3)
{
	m_f40 = f;
	m_r44.rva0013101E(r);
	m_54 = 0;
}

// ?rva00135E6D@Rva00136794@@QAEXXZ @ 0x00135E6D (25B). Vslot 7 of vtable 0x007D2970 via release of refcounted m_54.
void Rva00136794::rva00135E6D()
{
    RefM54 *p = m_54;
    if (p) {
        if (--p->m_ref == 0)
            p->vf0();
        m_54 = 0;
    }
}
