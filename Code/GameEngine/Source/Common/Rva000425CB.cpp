// cl: /MD

// ?rva000425CB@Rva000425CB@@QAEMXZ @0x000425CB 58B
// Unlock: virtual 0x18 gate, unsigned 0xC/0x14 division, 0.0 default.
// Prev disp trivial, next is Rva0004263F wrapper. No EH.

class Rva000425CB
{
	virtual void _M_slot_00();
	virtual void _M_slot_01();
	virtual void _M_slot_02();
	virtual void _M_slot_03();
	virtual void _M_slot_04();
	virtual void _M_slot_05();
	virtual bool _M_slot_06();
	char _pad04[0xc - 4];
	unsigned int m_0c;
	unsigned int m_10;
	unsigned int m_14;
	unsigned int m_18;
public:
	float rva000425CB();
	float rva00042605();
};

float Rva000425CB::rva000425CB()
{
	if (_M_slot_06())
		return (float)m_0c / (float)m_14;
	else
		return 0.0f;
}

float Rva000425CB::rva00042605()
{
	if (_M_slot_06())
		return (float)m_10 / (float)m_18;
	else
		return 0.0f;
}
