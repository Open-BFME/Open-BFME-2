// cl: /MD
//
// ?rva001F5496@Rva001F5496@@QAEXABVRvaSmartPtr12@@@Z, retail 0x001F5496, 47 bytes.
// Smart-ptr assign at +0x15C via rowed 0x4CC3D, then pointee+0xA8 to +0x168
// else zero. Callers at 0x001FBD17 and 0x001FC701.
// Sibling of 0x001F5467 (offsets +0x16C/+0x178).

class RvaSmartPtr12
{
public:
	RvaSmartPtr12 &operator=(const RvaSmartPtr12 &that);
	void *m_ptr;
	int m_pad04;
	int m_pad08;
};

struct Target001F5496
{
	char m_pad[0xA8];
	int m_val;
};

class Rva001F5496
{
public:
	void rva001F5496(const RvaSmartPtr12 &arg);
private:
	char m_pad00[0x15C];
	RvaSmartPtr12 m_smart;
	int m_val168;
};

void Rva001F5496::rva001F5496(const RvaSmartPtr12 &arg)
{
	m_smart = arg;
	void *p = arg.m_ptr;
	int v;
	if (p != 0)
		v = ((Target001F5496 *)p)->m_val;
	else
		v = 0;
	m_val168 = v;
}
