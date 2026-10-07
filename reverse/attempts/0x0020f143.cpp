// ?rva0020F143@Rva0020F143@@QAE_NPAVRva002E071E@@PAM@Z
// partial score=0.92 date=2026-10-07
// cl: /EHsc /O1 /arch:SSE /G7

// ?rva0020F143@Rva0020F143@@QAE_NPAVRva002E071E@@PAM@Z @0x0020F143 176B.
// Address-derived owner: the packet establishes the offsets and callees but
// does not identify the containing class. The +0x2c range and +0x14 key id
// are target layout evidence; their field meanings are structural inferences.
class Rva0020E89C
{
public:
	char m_pad[0x13c];
	int m_id;
};

class Rva0020EAF6View
{
public:
	Rva0020E89C *rva0020EAF6(int id);
};

class LivingWorldLogic
{
public:
	char m_pad[0xb0];
	Rva0020EAF6View *m_view;
};

extern LivingWorldLogic *TheLivingWorldLogic;

class Rva002E071E
{
public:
	int rva002E0BC0(int id);
	char m_pad[0x14];
	int m_id;
};

class Rva0020F143
{
public:
	bool rva0020F143(Rva002E071E *key, float *fraction);
	char m_pad[0x2c];
	int *m_begin;
	int *m_end;
};

bool Rva0020F143::rva0020F143(Rva002E071E *key, float *fraction)
{
	int *end = m_end;
	int *begin = m_begin;
	int bytes = (int)((char *)end - (char *)begin);
	if ((bytes & 0xfffffffc) == 0)
		return false;
	int matches = 0;
	for (unsigned int i = 0; i < (unsigned int)(m_end - m_begin); ++i)
	{
		int currentId = m_begin[i];
		Rva0020E89C *entry = TheLivingWorldLogic->m_view->rva0020EAF6(currentId);
		if (entry != 0 && (unsigned char)key->rva002E0BC0(entry->m_id) && key->m_id == entry->m_id)
			++matches;
	}
	if (matches == 0)
		return false;
	if (fraction != 0)
		*fraction = (float)matches / (unsigned int)(m_end - m_begin);
	return true;
}
