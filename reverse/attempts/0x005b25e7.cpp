// ??0Rva005B2575@@QAE@H@Z
// partial score=0.9 date=2026-10-07
// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// ??0Rva005B2575@@QAE@H@Z @ 0x005B25E7, 118 bytes. The dtor TU proves the
// class name and the caller plus retail offsets prove the integer at +4.
#include "ascii_string.h"

class __single_inheritance RenderObjClass;

struct DelegateDesc
{
	void *m_object;
	void *m_method;
};

class Rva00579E47
{
public:
	Rva00579E47(const DelegateDesc &desc);
private:
	void *m_impl;
};

class AptScreenInitGadgets;
template <class T> class AptRef
{
public:
	AptRef(DelegateDesc desc) : m_ref(desc) {}
private:
	Rva00579E47 m_ref;
};

void _bfme_setAptScreenRef(const AsciiString &name, AptRef<AptScreenInitGadgets> ref);

class RenderObjClass
{
public:
	void Set_Animation();
};

class __declspec(novtable) Rva005B2575Base
{
public:
	virtual ~Rva005B2575Base();
	Rva005B2575Base(int value) : m_value(value) {}
private:
	int m_value;
};

class Rva005B2575 : public Rva005B2575Base
{
public:
	Rva005B2575(int a0);
	virtual ~Rva005B2575();
};

Rva005B2575::Rva005B2575(int a0) : Rva005B2575Base(a0)
{
	AsciiString name("CahBonus::InitGadgets");
	union MethodAddress
	{
		void (RenderObjClass::*method)();
		void *address;
	} method;
	method.method = &RenderObjClass::Set_Animation;
	DelegateDesc desc = { this, method.address };
	_bfme_setAptScreenRef(name, AptRef<AptScreenInitGadgets>(desc));
}
