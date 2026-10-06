// cl: /O1 /MD
// ?rva005D772D@Rva00049D20@@QAEHH@Z, retail 0x005D772D, 24 bytes.
// Element count of the +0x1C vector of entry i of the +0x10 pointer vector (ret 4).
// Evidence: callers 0x00573918 0x005D77BB 0x005D77F7 0x005EEB1C; table layout from
// Rva00049D20Get 0x00049D20 and Rva005D7766; pin at 0x005D772D.
// Honest address name; owner unproven.
class Rva00049D20
{
public:
	char m_pad00[0x10];
	void **m_begin;
	void **m_end;
	int rva005D772D(int index);
};

struct Rva005D772DEntry
{
	char m_pad00[0x1c];
	int *m_begin;
	int *m_end;
};

int Rva00049D20::rva005D772D(int index)
{
	char *entry = (char *)m_begin[index];
	int *vec = (int *)(entry + 0x1c);
	return (vec[1] - vec[0]) >> 2;
}
