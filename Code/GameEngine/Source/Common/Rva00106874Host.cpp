// cl: /MD /EHsc
//
// ?rva00106874@Rva00106874Host@@QAE_NXZ, retail 0x00106874, 27 bytes.
// ??1Rva00106874Host@@QAE@XZ, retail 0x00106A2D, 47 bytes.
// Target evidence: frameless release-if-nonnull at +0x04 via virtual slot 2
// then null plus bool return; callers 0x00106A3F and 0x00106B68 unclaimed.
// Dtor calls release then AsciiString dtor 0x00036410; prev is Rva007E3430
// ctor 0x00106A19, next is Disp8 getter 0x00106CEC. True class name unproven
// so honest Rva address name stands in.

template <typename T>
class StringBase
{
public:
	~StringBase();
private:
	T *m_data;
};

struct Rva00106874Pointee
{
	virtual void v0();
	virtual void v1();
	virtual void v2();
};

class Rva00106874Host
{
public:
	bool rva00106874();
	~Rva00106874Host();
private:
	StringBase<char> m_00;
	Rva00106874Pointee *m_04;
};

bool Rva00106874Host::rva00106874()
{
	if (m_04)
	{
		m_04->v2();
		m_04 = 0;
		return true;
	}
	return false;
}

Rva00106874Host::~Rva00106874Host()
{
	rva00106874();
}
