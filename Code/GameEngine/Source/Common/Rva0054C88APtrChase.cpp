// cl: /MD
// ?rva0054C88A@Rva0054C88A@@QAE_NXZ @0x0054C88A 14B
// Ptr-chase nonzero test through this+4 to int at +0x14. Evidence: retail
// mov eax [ecx+4] xor ecx cmp [eax+0x14] ecx setne; caller at 0x00437EDC
// tail-jmps with ecx from global g_Va00E032FC and returns al on null path.
class Rva0054C88AInner
{
public:
	char m_lead[0x14];
	int m_val;
};
class Rva0054C88A
{
public:
	bool rva0054C88A();
	char m_lead0[4];
	Rva0054C88AInner *m_ptr;
};
bool Rva0054C88A::rva0054C88A()
{
	return m_ptr->m_val != 0;
}
