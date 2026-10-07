// cl: /O1 /MD
//
// ?rva004079D5@Rva004079D5@@QAEDHPAH@Z @0x004079D5 31B.
// Out-param helper: run the +0x74 subobject member with the address of the
// (otherwise unused) first-arg slot as scratch — frameless, no sub —
// store the int result through the second arg, and return whether it
// differs from the subobject head.
// Evidence: retail push esi / lea esi,[ecx+0x74] / lea eax,[esp+8] /
// push eax / mov ecx,esi / call 0x388E63 / mov ecx,[esp+0xc] /
// mov [ecx],eax / cmp eax,[esi] / pop esi / setne al / ret 8.
class Rva004079D5Sub74
{
public:
	int rva00388E63(int *out);
	int m_0;
};

class Rva004079D5
{
public:
	char rva004079D5(int tmp, int *out);
private:
	char m_pad00[0x74];
	Rva004079D5Sub74 m_74;
};

char Rva004079D5::rva004079D5(int tmp, int *out)
{
	int v = m_74.rva00388E63(&tmp);
	*out = v;
	return v != m_74.m_0;
}
