// cl: /MD
//
// ?rva00318D05@Rva00318D05@@QAE_NH@Z, retail 0x00318D05, 15 bytes.
// Compares int arg with dword at +0x54 and returns equality as bool.
// Caller is FUN_006B5A5F at 0x002B5AB5 passing [eax+0x14] with this in edi
// which also uses +0x58 byte and +0x18 string. Adjacent setter at 0x00318D14
// writes byte at +0x58. Identity beyond the compare is unproven so the name
// stays honest address-derived.

class Rva00318D05
{
public:
	bool rva00318D05(int value);
private:
	char m_pad[0x54];
	int m_54;
};

bool Rva00318D05::rva00318D05(int value)
{
	return value == m_54;
}
