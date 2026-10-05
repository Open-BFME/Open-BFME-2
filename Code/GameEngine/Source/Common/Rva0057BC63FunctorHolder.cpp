// cl: /O1 /MD
// ??0Rva0057BC63FunctorHolder@@QAE@ABUFunctorBinding@@@Z @0x0057BC63 59B
// Holder FROM_REFERENCE: m_ptr = new Wrapper(binding); if (m_ptr) m_refCount++.
// Donor: reference/open-bfme-1/Code/GameEngine/Source/Common/FunctorBindWrapperCtors.cpp
// (BFME_FUNCTOR_HOLDER_FROM_REFERENCE, 24B wrapper, 16B FunctorBinding).
// Vtable 0x00C6FAA0 (RVA 0x0086FAA0, between FileTransferPopUpClose and
// FileTransfer::Status%d; slots 0x009FAA31 deleting dtor + 0x00914EA0 invoker
// mov eax,ecx/mov ecx,[eax+0x14]/add ecx,[eax+0x8]/jmp [eax+0x10]).
// Inner wrapper ctor same movsd x4 at 0x005185BA (30B). Callers 0x002D558D
// 0x002D595A 0x000E2083 build 16B payload on stack and construct holder via
// push placeholder + mov ecx,esp.
void *__cdecl operator new(unsigned int size);

class __multiple_inheritance FunctorTarget;
typedef void (FunctorTarget::*FunctorMethod)(void);

struct FunctorBinding
{
	FunctorTarget *m_target;
	unsigned int m_pad;
	FunctorMethod m_method;
};

class FunctorWrapperHead
{
public:
	FunctorWrapperHead() : m_refCount(0) {}
	virtual void anchor();
	unsigned int m_refCount;
};

// ?anchor@FunctorWrapperHead@@UAEXXZ absent-from-retail
void FunctorWrapperHead::anchor() {}

class Rva0057BC63FunctorWrapper : public FunctorWrapperHead
{
public:
	Rva0057BC63FunctorWrapper(const FunctorBinding &binding) : m_binding(binding) {}
	FunctorBinding m_binding;
};

class Rva0057BC63FunctorHolder
{
public:
	Rva0057BC63FunctorHolder(const FunctorBinding &binding);
	Rva0057BC63FunctorWrapper *m_ptr;
};

Rva0057BC63FunctorHolder::Rva0057BC63FunctorHolder(const FunctorBinding &binding)
{
	m_ptr = new Rva0057BC63FunctorWrapper(binding);
	if (m_ptr != 0)
		m_ptr->m_refCount++;
}
