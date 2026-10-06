// cl: /MD
// ?rva004F60AA@Rva004F60AA@@QAEXXZ @0x004F60AA 66B: malloc retry loop halving capacity on failure with 0x1fffffff clamp.
// Evidence: and [esi+8] 0 plus cmp 0x1fffffff plus shl 2 malloc IAT plus cdq-sub-sar halve plus caller 0x004F77BE; neighbours 0x004F6093 0x004F612A.
extern "C" __declspec(dllimport) void *__cdecl malloc(unsigned int size);

class Rva004F60AA
{
public:
	void rva004F60AA();
private:
	int m_00;
	int m_04;
	void *m_08;
};

void Rva004F60AA::rva004F60AA()
{
	int n = m_04;
	m_08 = 0;
	m_00 = n;
	if (n > 0x1fffffff)
		m_04 = 0x1fffffff;
	while (m_04 > 0) {
		void *p = malloc((unsigned int)m_04 * 4);
		m_08 = p;
		if (p)
			break;
		m_04 /= 2;
	}
}
