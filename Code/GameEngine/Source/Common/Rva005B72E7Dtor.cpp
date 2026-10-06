// cl: /DNDEBUG /MD /EHsc
// ??1Rva005B72E7@@QAE@XZ @0x005B72E7 107B.
// Dtor frees DisplayString ptrs +0x10 +0x14 via manager 0x00DFEAD8 slot 0x3C then wide Strings +4 +8 via 0x36E70.
// Evidence: deleting-dtor caller 0x005B7352 28B; list-dtor caller 0x005B77F1 151B; and-zero plus EH frame.
class DisplayString;

class DisplayStringManager
{
public:
	virtual ~DisplayStringManager() {}
	virtual void managerSlot04() = 0;
	virtual void managerSlot08() = 0;
	virtual void managerSlot0C() = 0;
	virtual void managerSlot10() = 0;
	virtual void managerSlot14() = 0;
	virtual void managerSlot18() = 0;
	virtual void managerSlot1C() = 0;
	virtual void managerSlot20() = 0;
	virtual void managerSlot24() = 0;
	virtual void managerSlot28() = 0;
	virtual void managerSlot2C() = 0;
	virtual void managerSlot30() = 0;
	virtual void managerSlot34() = 0;
	virtual DisplayString *newDisplayString();
	virtual void freeDisplayString(DisplayString *s);
};

extern DisplayStringManager *TheDisplayStringManager;

template <typename T> class StringBase {
public: ~StringBase() { releaseBuffer(); }
private: void releaseBuffer();
	T *m_data; };

class Rva005B72E7 {
public:
	~Rva005B72E7();
private:
	int m_0;
	StringBase<unsigned short> m_4;
	StringBase<unsigned short> m_8;
	int m_C;
	DisplayString *m_10;
	DisplayString *m_14;
};

Rva005B72E7::~Rva005B72E7()
{
	if (m_10 != 0)
		TheDisplayStringManager->freeDisplayString(m_10);
	if (m_14 != 0)
		TheDisplayStringManager->freeDisplayString(m_14);
	m_10 = 0;
	m_14 = 0;
}
