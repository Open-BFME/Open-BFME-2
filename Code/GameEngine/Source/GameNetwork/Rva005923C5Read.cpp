// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ?Rva005923C5Read@@YAPAVRva004D62A9@@HPAI@Z @ 0x005923C5 (209B).
// NetCommandMsg Rva004D62A9 deserializer: auto_ptr-held new plus
// null-terminated string via byte loop plus AsciiString temp through the
// 0x00590F13 setter twin plus word and byte reads through the 0x006291A8
// import plus Disp8 setters 0x004D5978 0x004D5984. Evidence: new 0x24 plus
// ctor 0x004D62A9 plus StringBase char ctor 0x00037BA0; callers 0x00592882
// 0x00594164; byte loop and temp shape follow sibling Rva005922FBRead at
// 0x005922FB. Free function despite the packet hint: ecx is never read
// before it is written.
void *__cdecl operator new(unsigned int size);
void __cdecl ji_006291a8();

#include "ascii_string.h"

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
	NetCommandMsg();
protected:
	virtual ~NetCommandMsg() {}
protected:
	UnsignedInt m_timestamp;
	UnsignedInt m_executionFrame;
	UnsignedInt m_playerID;
	UnsignedShort m_id;
	NetCommandType m_commandType;
	Int m_referenceCount;
};
class Rva004D62A9 : public NetCommandMsg
{
public:
	Rva004D62A9();
	void rva00590F13(AsciiString s);
private:
	AsciiString m_str1c;
	UnsignedShort m_20;
	bool m_22;
};
class Rva004D5978WordSlot
{
public:
	void set(unsigned short value);
};
class Rva004D5984ByteSlot
{
public:
	void set(unsigned char value);
};

Rva004D62A9 *__cdecl Rva005923C5Read(int base, unsigned int *cursor)
{
	Rva004D62A9 *obj = new Rva004D62A9;
	char buf[260];
	char *dst = buf;
	while (((const char *)base)[*cursor] != 0) {
		*dst = ((const char *)base)[*cursor];
		++dst;
		++*cursor;
	}
	++*cursor;
	*dst = 0;
	obj->rva00590F13(AsciiString(buf));
	int tmpWord;
	tmpWord = 0;
	((void (__cdecl *)(int *, const void *, int))ji_006291a8)(&tmpWord, (const void *)(base + *cursor), 2);
	*cursor += 2;
	((Rva004D5978WordSlot *)obj)->set((unsigned short)tmpWord);
	unsigned char tmpByte;
	tmpByte = 0;
	((void (__cdecl *)(unsigned char *, const void *, int))ji_006291a8)(&tmpByte, (const void *)(base + *cursor), 1);
	*cursor += 1;
	((Rva004D5984ByteSlot *)obj)->set(tmpByte);
	return obj;
}
