// ?rva004EABC7@Rva004EABC7@@QAE_NXZ
// partial score=0.96 date=2026-10-06
// cl: /O1 /arch:SSE /G7 /MD /EHs
// ?rva004EABC7@Rva004EABC7@@QAE_NXZ @0x004EABC7 35B. Address-derived
// identity: caller is anonymous and gives no class identity; packet shows
// two state checks and a rowed predicate call through the +0x14 object.
class Rva004E9378
{
public:
	bool rva004E9378();
};

class Rva004EABC7
{
public:
	bool rva004EABC7();
private:
	char m_pad[0x14];
	Rva004E9378 *m_14;
	char m_pad18[0x1C];
	int m_34;
	char m_pad38[4];
	int m_3C;
};

bool Rva004EABC7::rva004EABC7()
{
	if (m_34 != 4 || m_3C != 4 || m_14 == 0)
		return false;
	unsigned char result = m_14->rva004E9378();
	return result ? false : true;
}
