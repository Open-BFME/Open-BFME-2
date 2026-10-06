// cl: /EHs /MD
// ??1Rva0054080A@@UAE@XZ @0x0054080A 59B outer dtor.
// Retail stores vtable 0x008694F8, destroys inner at +0x24 via rowed
// ??1Rva005407C9@@QAE@XZ, then base ??1Rva0053FB33@@UAE@XZ with
// __EH_prolog frame. Evidence: chain lane; caller 0x00540A6C; pattern
// copied from Rva0053FB33Dtor TU.
class Rva005407C9
{
public:
	~Rva005407C9();
private:
	unsigned char m_pad[0x14];
};

class Rva0053FB33
{
public:
	virtual ~Rva0053FB33();
private:
	unsigned char m_pad[0x24 - 4];
};

class Rva0054080A : public Rva0053FB33
{
public:
	virtual ~Rva0054080A();
private:
	Rva005407C9 m_24;
};

Rva0054080A::~Rva0054080A()
{
}
