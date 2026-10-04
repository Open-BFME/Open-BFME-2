// cl: /O1 /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc /arch:SSE
// stlport
// ?rva0035A1D8@Rva0035A1D8@@QAEXXZ @0x0035A1D8 96B
// Unlock via 0x002442A4; neighbours Rva0035A18DVectorDeletingDtor and OpaqueScalarDeletingDtorsB06.
// Evidence: thiscall reads ecx first; list clear 0x0023DAA5 at +0x14; 8 float zeros; array delete 0x0035A18D x3 at +0x40; forEach 0x00359BE8 with vcall thunk plus owner; callers 0x002443AA and thunk 0x0035AA3E.
#include <string>
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)

namespace _STL
{
template <class T> class allocator;
template <class T, class Alloc> class _List_base
{
public:
	void clear();
};
}

class Rva0035A18D
{
public:
	~Rva0035A18D();
private:
	_STL::basic_string<char> m_str;
	int m_x;
};

class Rva00359E04Owner;
class Rva00359E04Listener
{
public:
	virtual void notify00(Rva00359E04Owner *owner);
	virtual void notify04(Rva00359E04Owner *owner);
	virtual void notify08(Rva00359E04Owner *owner);
	virtual void notify0C(Rva00359E04Owner *owner);
};
class Rva00359BE8List
{
public:
	void forEach(void (Rva00359E04Listener::*notify)(Rva00359E04Owner *), Rva00359E04Owner *owner);
};
class Rva00359E04Owner
{
public:
	char m_pad[4];
	Rva00359BE8List m_list;
};

class Rva0035A1D8
{
public:
	void rva0035A1D8();
private:
	char m_pad00[0x04];
	char m_list04[0x10];
	char m_opaque14[0x04];
	float m_f18;
	float m_f1C;
	float m_f20;
	float m_f24;
	float m_f28;
	float m_f2C;
	float m_f30;
	int m_34;
	int m_38;
	float m_f3C;
	Rva0035A18D *m_arr40;
};

void Rva0035A1D8::rva0035A1D8()
{
	((_STL::_List_base<int, _STL::allocator<int> > *)((char *)this + 0x14))->clear();
	m_f1C = 0.0f;
	m_f20 = 0.0f;
	m_f24 = 0.0f;
	m_f28 = 0.0f;
	m_f2C = 0.0f;
	m_f30 = 0.0f;
	_ReadWriteBarrier();
	Rva0035A18D *arr = m_arr40;
	m_34 = 0;
	m_38 = 0;
	m_f3C = 0.0f;
	m_f18 = 0.0f;
	if (arr)
		delete[] arr;
	m_arr40 = 0;
	((Rva00359BE8List *)((char *)this + 0x04))->forEach(&Rva00359E04Listener::notify0C, (Rva00359E04Owner *)this);
}
