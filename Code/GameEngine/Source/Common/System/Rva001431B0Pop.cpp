// cl: /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ?rva00142DF0@Rva001431B0@@QAEXXZ, RVA 0x00142DF0, 44B.
// Guarded pop from the member vector<Rva00142DF0String> at +0x13c.
// Evidence: empty check mov eax [ecx+0x13c] cmp [ecx+0x140] matches vector
// empty; tail decrements finish and releases string via refcount at +4
// plus slot-0 virtual call; same class and vector as push 0x001431B0 and dtor 0x00142E30;
// lea getter 0x00142C40 proves +0x13c; callers at 0x0007DDEF 0x000D7CD4 0x00101161.
// Not the shared AsciiString: retail inlines a virtual slot-0 delete with refcount at +4,
// while the shared header calls releaseBuffer at 0x00036410, so this keeps its own
// refcounted type named Rva00142DF0String to avoid the AsciiString COMDAT clash.

#include <vector>

// class-gate: allowlist not needed - this type is not AsciiString (see header comment).
class Rva00142DF0String
{
	struct Rva00142DF0StringData
	{
		virtual void _M_slot_00();
		int m_refCount;
	};

	Rva00142DF0StringData *m_data;

public:
	Rva00142DF0String(const Rva00142DF0String &that)
	{
		m_data = that.m_data;
		if (m_data)
			m_data->m_refCount++;
	}
	~Rva00142DF0String()
	{
		Rva00142DF0StringData *data = m_data;
		if (data && --data->m_refCount == 0)
			data->_M_slot_00();
	}
};

class Rva001431B0
{
	char m_pad[0x13c];
	_STL::vector<Rva00142DF0String, _STL::allocator<Rva00142DF0String> > m_vec;

public:
	void rva00142DF0();
};

void Rva001431B0::rva00142DF0()
{
	if (!m_vec.empty())
		m_vec.pop_back();
}
