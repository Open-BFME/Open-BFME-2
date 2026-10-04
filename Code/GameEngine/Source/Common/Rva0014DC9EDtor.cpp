// cl: /O1 /MD
// ??1Rva0014DC9E@@UAE@XZ @0x0014DC9E 14B.
// Triple store of g_00BC6F24 to +0/+4/+8 like Rva0014DC76Init sibling.
// Evidence: retail mov eax,0xBC6F24 mov [ecx+8],eax mov [ecx+4],eax mov [ecx],eax ret;
// pin ??1Rva0014DC9E@@UAE@XZ; vtable 0x00BD3898#0 deleting wrapper 0x0014DCAC;
// callers 0x0014DCAF 0x00766A2E.
extern int g_00BC6F24;

class __declspec(novtable) Rva0014DC9E
{
public:
	virtual ~Rva0014DC9E();
private:
	int m_4;
	int m_8;
};

Rva0014DC9E::~Rva0014DC9E()
{
	int v = (int)&g_00BC6F24;
	m_8 = v;
	m_4 = v;
	*(int *)this = v;
}
