// cl: /O1 /DNDEBUG /MD /EHsc
//
// ??0Rva00540845@@QAE@XZ @ 0x00540BAD 55B: derived default constructor,
// sibling of the rowed copy ctor 0x00540845 in Rva00540845Copy.cpp.
// Evidence: base-defaults through 0x0053FAB7 (39B base ctor, member+4
// via rowed 0x00330757, vtable 0x00C694DC), installs vtable 0x00C694F8,
// then default-constructs the +0x24 channel member through the rowed
// Rva00540B03 default ctor at 0x00540B03 via the explicit C::C() call
// form (no null check, no EH frame of its own). Member plus vector
// value-inits earn the __EH_prolog frame with this-spill and state 0.
// Separate TU from the copy ctor because the init-list member there
// has no default ctor; raw storage keeps this default ctor compiling.
// Identities are address-derived.
class Rva0053FADE
{
public:
	virtual void v0();
	virtual ~Rva0053FADE();
	Rva0053FADE();
private:
	char m_pad04[0x20];
};

class Rva00540B03
{
public:
	Rva00540B03();
private:
	char m_pad[0x20];
};

class Rva00540845 : public Rva0053FADE
{
public:
	virtual void v0();
	Rva00540845();
private:
	char m_sub24[0x20];
};

Rva00540845::Rva00540845()
	: Rva0053FADE()
{
	((Rva00540B03 *)m_sub24)->Rva00540B03::Rva00540B03();
}
