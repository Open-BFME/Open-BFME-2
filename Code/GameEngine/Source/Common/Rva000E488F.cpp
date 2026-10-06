// cl: /MD
//
// ?rva000E488F@Rva000E488F@@QAE_NPAX@Z, retail 0x000E488F, 45 bytes.
// Array-all predicate: iterates pointers from [this] to [this+4], calling
// virtual slot 129 (offset 0x204) on each element with the single pointer
// arg, returning false on the first false and true if all pass.
// Evidence: retail push esi/edi plus mov edi ecx plus mov esi [edi] plus
// initial jmp to cmp [edi+4] loop; call [eax+0x204] with ecx=[esi] element
// and stack arg [esp+0x0c]; test al al plus je fail plus add esi 4; callers
// at 0x000E4998 plus 0x000E76DB plus 0x000EB247 plus 0x000EE15B each invert
// the result; landing unblocks 0x000E76B8 plus 0x000EE15B plus 0x000EB21D.
// Container layout begin at +0 and end at +4 proven by retail loads; element
// class unproven so honest Rva names with slot padding only.

template <int N>
class Rva000E488FSlots : public Rva000E488FSlots<N - 1>
{
public:
	virtual void unused(char (*)[N]) = 0;
};

template <>
class Rva000E488FSlots<0>
{
};

class Rva000E488FElement : public Rva000E488FSlots<129>
{
public:
	virtual bool check(void *arg);
};

class Rva000E488F
{
public:
	bool rva000E488F(void *arg);
	Rva000E488FElement **m_begin;
	Rva000E488FElement **m_end;
};

bool Rva000E488F::rva000E488F(void *arg)
{
	for (Rva000E488FElement **it = m_begin; it != m_end; ++it) {
		if (!(*it)->check(arg))
			return false;
	}
	return true;
}
