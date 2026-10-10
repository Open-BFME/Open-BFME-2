// cl: /O1 /MD
// The holder/wrapper/invoker rows (0x0057BC63 59B, 0x005185BA 30B,
// 0x00514EA0 11B) live in AptOptionsConstructor.cpp; this TU keeps the shared
// class views and the absent-from-retail anchor definition.
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
	void invoke();
	FunctorBinding m_binding;
};

// Fresh BF1 f98983a7 whole FunctorBindInvokers.cpp supplies the ordinary
// multiple-inheritance member-pointer invocation. The donor has 41 names
// for this shape; none is asserted as the target's original class name.
// Target514EA0..514EAB is the complete tail jump, immediately afterRET4.
// Independently, this wrapper's existing native ctor5185BA installsC6FAA0,
// whose second slot names514EA0; its four copied binding words establish
// object+8 and the actual {code,delta} member-pointer words+10/+14.
// The holder constructor row lives in AptOptionsConstructor.cpp (identical
// select-any copy); its exclusive definition here is removed so the link
// keeps the one retail copy. This TU keeps the sole invoker definition.
void Rva0057BC63FunctorWrapper::invoke() {
    (m_binding.m_target->*m_binding.m_method)();
}

class Rva0057BC63FunctorHolder
{
public:
	Rva0057BC63FunctorHolder(const FunctorBinding &binding);
	Rva0057BC63FunctorWrapper *m_ptr;
};
