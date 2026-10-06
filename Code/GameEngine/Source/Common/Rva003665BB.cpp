// cl: /MD
// ?rva003665BB@Rva003665BB@@QAEXPAX@Z 0x003665BB 16B via link old head at +0x38 into arg +0x3c
// Evidence: retail mov edx [ecx+38] mov eax [esp+4] mov [eax+3c] edx mov [ecx+38] eax ret 4; neighbours Rva0036658B/Rva0036666B (/O1 /MD); caller 0x0052F736
class Rva003665BB
{
public:
	void rva003665BB(void *a);
private:
	char m_pad[0x38];
	void *m_38;
};

void Rva003665BB::rva003665BB(void *a)
{
	*(void **)((char *)a + 0x3c) = m_38;
	m_38 = a;
}
