// cl: /O1 /DNDEBUG /MD
//
// Straw::Get, retail 0x00615560, 19 bytes.
// Kept out of straw.cpp so the landed dtor/Get_From keep their flags.
// Retail compares ChainTo in place (cmp [ecx+4],0) then tail-jumps
// the virtual Get at vtable+8.

class Straw
{
public:
	virtual ~Straw();
	virtual void Get_From(Straw *pipe);
	virtual int Get(void *buffer, int slen);
	Straw *ChainTo;
	Straw *ChainFrom;
};

int Straw::Get(void *buffer, int slen)
{
	if (ChainTo != 0)
		return ChainTo->Get(buffer, slen);
	return 0;
}
