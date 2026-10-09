// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva004FB0C7@Rva004FB0C7Registry@@QAE_NHPAURva004FAFF2@@@Z, retail 0x004FB0C7 (97 bytes, ret 8). The owner
// is unproven (address token): the vector of 0x58-byte Rva004FAFF2 records at +0x08 (record layout from the
// rowed copy-assign 0x004FAFF2, key word at +0x4C). Finds the record with the key; when asked, copies it
// out through that copy-assign. WorldBuilder twin 0x01309890 is unnamed.
#include <vector>

struct Rva004FAFF2
{
	char m_pad00[0x4C];
	int m_4c;
	char m_pad50[0x58 - 0x50];
	Rva004FAFF2 &rva004FAFF2(const Rva004FAFF2 &other);
};

class Rva004FB0C7Registry
{
public:
	bool rva004FB0C7(int key, Rva004FAFF2 *out);

private:
	char m_pad00[8];
	_STL::vector<Rva004FAFF2> m_records;	// +0x08
};

bool Rva004FB0C7Registry::rva004FB0C7(int key, Rva004FAFF2 *out)
{
	for (unsigned int i = 0; i < m_records.size(); ++i) {
		if (m_records[i].m_4c == key) {
			if (out)
				out->rva004FAFF2(m_records[i]);
			return true;
		}
	}
	return false;
}
