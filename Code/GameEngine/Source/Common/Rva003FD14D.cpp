// cl: /O1 /MD
//
// ?rva003FD14D@Rva003FD14D@@QAE@H@Z @0x003FD14D 31B.
// Derived constructor: run the base init at 0x003FC58C with (arg), then
// the compiler sets this TU's vtable (patched to the shared 0x00C37C68
// also used by 0x003FDC41, same class family), clears the +0xAC byte,
// and returns this for placement new.
// Evidence: retail push esi / push [esp+8] / mov esi,ecx /
// call 0x003FC58C / mov [esi],0xC37C68 / mov byte [esi+0xac],0 /
// mov eax,esi / pop esi / ret 4.
class Rva003FD14DBase
{
public:
	Rva003FD14DBase(int arg);
	virtual void vbfunc();
};

class Rva003FD14D : public Rva003FD14DBase
{
public:
	Rva003FD14D(int arg);
	virtual void vfunc();
private:
	char m_pad04[0xA8];
	char m_ac;
};

Rva003FD14D::Rva003FD14D(int arg) : Rva003FD14DBase(arg)
{
	m_ac = 0;
}
