// cl: /EHsc /MD
// ??0Rva002E0906@@QAE@XZ @0x002E0906 100B, called from 0x002E2417.
// Retail's unwind map destroys narrow StringBase members at +0x00, +0x04
// and +0x20, in that order of construction. The first two and the third are
// default-constructed (null data pointer), the integers between them are
// zeroed in the same initializer sequence, and +0x24 is built from the
// literal "DefaultGoodArmyIcon" through the rowed StringBase(const char *)
// 0x00037BA0 once state 2 is armed. The banked 0.90 attempt put an empty
// base in front and zeroed +0x00..+0x20 as plain ints.
template <typename T> class StringBase
{
	friend class Rva002E0906;
	StringBase() : m_data(0) {}
	StringBase(const char *str);
	~StringBase();
	void *m_data;
};
class Rva002E0906
{
public:
	Rva002E0906();
private:
	StringBase<char> m_00;
	StringBase<char> m_04;
	int m_08;
	int m_0c;
	int m_10;
	int m_14;
	int m_18;
	int m_1c;
	StringBase<char> m_20;
	StringBase<char> m_24;
	int m_28;
	int m_2c;
	int m_30;
	int m_34;
	int m_38;
	int m_3c;
};
Rva002E0906::Rva002E0906() : m_08(0), m_0c(0), m_10(0), m_14(0), m_18(0), m_1c(0),
	m_24("DefaultGoodArmyIcon"), m_28(0), m_2c(0), m_30(0), m_34(0), m_38(0), m_3c(0)
{
}
