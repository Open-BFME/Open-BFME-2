// cl: /Oy- /DNDEBUG /MD /GX
//
// ?get@Rva0055DDB6SmartField@@QBE?AVRvaSmartPtr12@@XZ, retail 0x0055DDB6, 27 bytes.
// Value-returning smart-pointer getter same shape as siblings 0x003FDA90
// (member +0x15C, 30B) and 0x001F6C54 (member +0x68, 27B) via the rowed copy
// at 0x4CC19: returns the 12-byte member at +0x04 through the hidden return
// pointer (RVO). Callers at 0x0055DE57 0x0055F885 0x005623AA use a 12-byte
// temp plus the rowed handle dtor; landing unblocks 0x0055F840 0x0055DDD1
// 0x00562366.
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

class Rva0055DDB6SmartField
{
public:
	RvaSmartPtr12 get() const;

private:
	char m_pad[4];
	RvaSmartPtr12 m_value;
};

RvaSmartPtr12 Rva0055DDB6SmartField::get() const
{
	return m_value;
}
