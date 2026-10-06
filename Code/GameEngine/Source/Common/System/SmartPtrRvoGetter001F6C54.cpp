// cl: /Oy- /DNDEBUG /MD /GX
//
// ?get@Rva001F6C54SmartField@@QBE?AVRvaSmartPtr12@@XZ @ 0x001F6C54 27B
// RVO smart-pointer getter. Same shape as rowed 0x003FDA90 (30B) with member
// at +0x68 vs +0x15C. Callee 0x0004CC19 rowed. Unblocks 20 callers with 2 ready.

class RvaSmartPtr12
{
public:
	RvaSmartPtr12(const RvaSmartPtr12 &that);
	~RvaSmartPtr12();

private:
	void *m_ptr;
	int m_pad04;
	int m_pad08;
};

class Rva001F6C54SmartField
{
public:
	RvaSmartPtr12 get() const;

private:
	char m_pad[0x68];
	RvaSmartPtr12 m_value;
};

RvaSmartPtr12 Rva001F6C54SmartField::get() const
{
	return m_value;
}
