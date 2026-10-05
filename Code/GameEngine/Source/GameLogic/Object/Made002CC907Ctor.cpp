// cl: /O1 /DNDEBUG /MD /arch:SSE
//
// ??0Made002CC907@@QAE@XZ retail 0x0050AA97 83B Grab ctor.
// Evidence: pin; base Rva00507823 0x0050775B; vtable 0x00864AC0; float 1.0 via 0x007BB8D8;
// caller parseGrabNugget 0x002CC92C news 0x140.
class Rva00507823
{
public:
	Rva00507823();
	virtual ~Rva00507823();
private:
	char m_pad[0x128 - 4];
};

class Made002CC907 : public Rva00507823
{
public:
	Made002CC907();
private:
	bool m_128;
	bool m_129;
	char m_pad12A[2];
	float m_12C;
	float m_130;
	float m_134;
	float m_138;
	float m_13C;
};

Made002CC907::Made002CC907()
{
	m_128 = true;
	m_129 = false;
	m_12C = 0.0f;
	m_130 = 0.0f;
	m_134 = 0.0f;
	m_138 = 0.0f;
	m_13C = 1.0f;
}
