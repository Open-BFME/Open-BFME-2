// cl: /DNDEBUG /MD /EHsc
// ?rva0039B24F@Rva0039B24F@@QAEXPAURva0039B24FInput@@H_N@Z, retail 0x0039B24F, 64 bytes.
// Method of Rva0039B20C family: calls rowed rva0039B20C/rva0039B227 at +0xFC,
// float at +0x10 from input+0x18, virtual slot 4 with (input,arg2), flag decides second call.
// Evidence: adjacency to 0x39B246, callees share +0x24/+0x2C layout, input+0xFC pattern like Rva0039B2E6.

class Rva0039B20C
{
public:
	void rva0039B20C(void *src);
	void rva0039B227(int val);
};

struct Rva0039B24FInput
{
	char m_pad00[0x18];
	int m_18;
	char m_pad1C[0xFC - 0x1C];
	void *m_FC;
};

class Rva0039B24F
{
public:
	virtual void d0(void);
	virtual void d1(void);
	virtual void d2(void);
	virtual void d3(void);
	virtual void virt4(Rva0039B24FInput *input, int arg2);
	void rva0039B24F(Rva0039B24FInput *input, int arg2, bool flag);

private:
	char m_pad04[0x10 - 0x04];
	float m_10;
};

void Rva0039B24F::rva0039B24F(Rva0039B24FInput *input, int arg2, bool flag)
{
	virt4(input, arg2);
	m_10 = (float)input->m_18;
	((Rva0039B20C *)this)->rva0039B20C(input->m_FC);
	if (flag)
		((Rva0039B20C *)this)->rva0039B227((int)input->m_FC);
}
