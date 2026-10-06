// cl: /DNDEBUG /MD /EHsc
// ?rva004D5925@Rva004D58DE@@QAEXPAEI@Z, retail 0x004D5925, 39 bytes.
// Rva004D58DE setter twin of NetFileCommandMsg::setFileData 0x004D594C: stores
// length at +0x28, new[]s the buffer at +0x24, memcpy via thunk 0x006291A8.
// Identity from prev dtor 0x004D5902 layout +0x24 ptr +0x28 len, same 39B shape
// as next setFileData, callees new[] 0x0002FDE0 and memcpy thunk 0x006291A8,
// callers 0x004D02AD 0x0058E20D.
void *__cdecl operator new[](unsigned int size);
void __cdecl ji_006291a8();

typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef int Int;
enum NetCommandType
{
	NETCOMMANDTYPE_UNKNOWN = -1
};
class NetCommandMsg
{
public:
	virtual ~NetCommandMsg() {}
protected:
	UnsignedInt m_timestamp;
	UnsignedInt m_executionFrame;
	UnsignedInt m_playerID;
	UnsignedShort m_id;
	NetCommandType m_commandType;
	Int m_referenceCount;
};
class Rva004D58DE : public NetCommandMsg
{
public:
	void rva004D5925(unsigned char *data, unsigned int len);
private:
	unsigned int m_1c;
	unsigned short m_20;
	unsigned char *m_24;
	unsigned int m_28;
};

void Rva004D58DE::rva004D5925(unsigned char *data, unsigned int len)
{
	m_28 = len;
	m_24 = new unsigned char[len];
	((void (__cdecl *)(unsigned char *, const void *, unsigned int))ji_006291a8)(m_24, data, len);
}
