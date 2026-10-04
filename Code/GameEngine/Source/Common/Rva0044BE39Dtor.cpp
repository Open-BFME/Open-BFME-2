// cl: /O1 /MD /EHsc
// ??1Rva0044BE39@@UAE@XZ @0x0044BE39 48B
// Dtor with member at +8 via rowed 0x0044BA4E then base vtable 0x007C6F20.
// Caller 0x0044BE1D is deleting dtor; base Rva00517397Base pattern.
// Evidence: unlock lane; vtable store; rowed callee; EH_prolog.
class Rva0044BA4E
{
public:
	~Rva0044BA4E();
};

class Rva0044BE39Base
{
public:
	__forceinline ~Rva0044BE39Base() {}
	virtual void keep() {}
};

class __declspec(novtable) Rva0044BE39 : public Rva0044BE39Base
{
public:
	virtual ~Rva0044BE39();
private:
	int m_pad04;
	Rva0044BA4E m_08; // +0x08
};

Rva0044BE39::~Rva0044BE39()
{
}
