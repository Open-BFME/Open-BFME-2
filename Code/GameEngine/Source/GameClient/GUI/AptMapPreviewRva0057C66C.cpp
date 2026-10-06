// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
// ?rva0057C66C@Rva0057C66C@@QAEPAXI@Z @0x0057C66C 28B
// Gap body between AptMapPreview rows: calls rowed setter 0x0057C51E then flag-guarded operator delete 0x0002FD60 and returns this.
// Evidence: packet disasm with all callees rowed; callee 0x0057C51E sets Mem04 vtable 0x00C363B8; no callers; ret 4 with one flag arg.
class Rva00057C51EDwordImmSetter
{
public:
	void apply();
};

class Rva0057C66C
{
public:
	void *rva0057C66C(unsigned int flag);
private:
	Rva00057C51EDwordImmSetter m_setter;
};

void *Rva0057C66C::rva0057C66C(unsigned int flag)
{
	m_setter.apply();
	if (flag & 1)
		::operator delete(this);
	return this;
}
