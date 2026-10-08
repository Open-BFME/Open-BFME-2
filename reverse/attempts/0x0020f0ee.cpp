// ?rva0020F0EE@Rva0020F0EE@@QAEPAVRva0020E9D0@@PAVRva0020F0EEArg@@@Z
// partial score=0.6 date=2026-10-08
// cl: /Od /MD /EHsc
// ?rva0020F0EE@Rva0020F0EE@@QAEPAVRva0020E9D0@@PAVRva0020F0EEArg@@@Z @0x0020F0EE 85B:
// thiscall ret 4 scan of the pointer vector at +0x5c..+0x60. Each element's
// predicate 0x0020E9D0 is tested against the CreateAHeroData pointer at arg +0x12c,
// and the first element that answers true is returned, else null. The owner
// class is address-derived; the predicate and vector layout are retail evidence.
class CreateAHeroData;

class Rva0020E9D0
{
public:
	bool rva0020E9D0(CreateAHeroData *);
};

class Rva0020F0EEArg
{
public:
	char m_pad[0x12c];
	CreateAHeroData *m_ptr12c;
};

class Rva0020F0EE
{
public:
	Rva0020E9D0 *rva0020F0EE(Rva0020F0EEArg *arg);

private:
	char m_pad[0x5c];
	Rva0020E9D0 **m_begin; // +0x5c
	Rva0020E9D0 **m_end;   // +0x60
};

Rva0020E9D0 *Rva0020F0EE::rva0020F0EE(Rva0020F0EEArg *arg)
{
	for (unsigned int i = 0; i < (unsigned int)(m_end - m_begin); ++i) {
		Rva0020E9D0 *element = m_begin[i];
		if (element->rva0020E9D0(arg->m_ptr12c))
			return element;
	}
	return 0;
}
