// cl: /MD /EHsc
// ??1Rva0035FD0A@@UAE@XZ @0x0035FD0A (105B): virtual dtor storing vtable 0x008166BC.
// Zeroes +0xC, frees DisplayString at +0x34 via TheDisplayStringManager slot 0x3C,
// zeroes +0x34, destroys wide StringBase at +0x30/+0x2C via rowed releaseBuffer
// 0x00036E70, then base dtor via pinned 0x001DBAC3. Caller at 0x0035FF59 is
// deleting dtor. Prev tail dtors in FamilyTailDtors1DBAC3.cpp.
class DisplayString;

class DisplayStringManager
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2C() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual DisplayString *newDisplayString() = 0;
	virtual void freeDisplayString(DisplayString *s) = 0;
};

extern DisplayStringManager *TheDisplayStringManager;

template <typename T> class StringBase {
public: ~StringBase() { releaseBuffer(); }
private: void releaseBuffer();
	T *m_data; };

class Rva001DBAC3
{
public:
	virtual ~Rva001DBAC3();
};

class Rva0035FD0A : public Rva001DBAC3
{
public:
	virtual ~Rva0035FD0A();
private:
	char m_pad4[8];
	int m_C;
	char m_pad10[28];
	StringBase<unsigned short> m_2C;
	StringBase<unsigned short> m_30;
	DisplayString *m_34;
};

Rva0035FD0A::~Rva0035FD0A()
{
	m_C = 0;
	if (m_34 != 0)
		TheDisplayStringManager->freeDisplayString(m_34);
	m_34 = 0;
}
