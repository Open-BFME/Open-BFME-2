// cl: /MD
// ?rva005505E3@Rva005505E3@@QAEXXZ @0x005505E3 29B.
// Scoped CriticalSection lock of member at +0xA0 via rowed 0x00613B60 plus 0x00613B80.
// Evidence: callees rowed 0x00613B60 0x00613B80; caller 0x0055105B in 0x00550FDD.
class CriticalSectionClass
{
	void *handle;
	unsigned locked;
	void Lock();
	void Unlock();
public:
	CriticalSectionClass();
	~CriticalSectionClass();
	class LockClass
	{
		CriticalSectionClass &cs;
	public:
		LockClass(CriticalSectionClass &c);
		~LockClass();
	private:
		LockClass &operator=(const LockClass &) { return *this; }
	};
	friend class LockClass;
};

class Rva005505E3
{
public:
	void rva005505E3();
private:
	char m_pad[0xA0];
	CriticalSectionClass m_A0;
};

void Rva005505E3::rva005505E3()
{
	CriticalSectionClass::LockClass lock(m_A0);
}
