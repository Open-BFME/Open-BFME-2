// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// ?rva004E5344@Rva004E5344@@QAEXMM@Z @0x004E5344 46B
// Conditional timer insert at +0x38 via rowed 0x357DF8 when a<b, floats bitcast to timer words.
// Evidence: movss/comiss plus rowed rva00357DF8, callees rowed, callers 0x4E53EB/0x4E5446 in 0x4E5372,
// prev/next WWLib neighbours, honest Rva name.
struct BfmeSpecialPowerTimer8
{
	unsigned int m_templateID;
	unsigned int m_readyFrame;
};

class Rva00357DF8
{
public:
	void rva00357DF8(const BfmeSpecialPowerTimer8 &rec);
};

class Rva004E5344
{
public:
	void rva004E5344(float a, float b);
private:
	char m_pad[0x38];
	Rva00357DF8 m_38;
};

void Rva004E5344::rva004E5344(float a, float b)
{
	if (a >= b)
		return;
	BfmeSpecialPowerTimer8 timer;
	*(float *)&timer.m_templateID = a;
	*(float *)&timer.m_readyFrame = b;
	m_38.rva00357DF8(timer);
}
