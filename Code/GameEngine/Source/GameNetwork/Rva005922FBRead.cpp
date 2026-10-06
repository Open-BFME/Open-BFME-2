// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// stlport
// ?Rva005922FBRead@@YAPAVRva004D6208@@HPAI@Z @ 0x005922FB (202B).
// NetFileCommandMsg Rva004D6208 deserializer: auto_ptr-held new plus
// null-terminated string via byte loop plus AsciiString temp through the
// 0x00590F13 setter twin plus size and blob reads through the 0x006291A8
// import plus setFileData 0x004D594C. Evidence: new 0x28 plus ctor 0x004D61BB
// plus StringBase char ctor 0x00037BA0; callers 0x0059286E 0x00594158; byte
// loop and temp shape follow sibling Rva00592496Read at 0x00592496. Free
// function despite the packet hint: ecx is never read before it is written.

void *__cdecl operator new(unsigned int size);
void *__cdecl operator new[](unsigned int size);
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
class NetFileCommandMsg : public NetCommandMsg
{
public:
	void setFileData(unsigned char *data, unsigned int len);
};
class Rva004D6208 : public NetFileCommandMsg
{
public:
	Rva004D6208();
	void rva00590F13(AsciiString s);
private:
	AsciiString m_str1c;
	unsigned char *m_data20;
	int m_24;
};

Rva004D6208 *__cdecl Rva005922FBRead(int base, unsigned int *cursor)
{
	Rva004D6208 *obj = new Rva004D6208;
	char buf[256];
	char *dst = buf;
	while (((const char *)base)[*cursor] != 0) {
		*dst = ((const char *)base)[*cursor];
		++dst;
		++*cursor;
	}
	++*cursor;
	*dst = 0;
	obj->rva00590F13(AsciiString(buf));
	int size[2];
	size[1] = 0;
	((void (__cdecl *)(int *, const void *, int))ji_006291a8)(&size[1], (const void *)(base + *cursor), 4);
	*cursor += 4;
	unsigned char *data = new unsigned char[size[1]];
	((void (__cdecl *)(unsigned char *, const void *, int))ji_006291a8)(data, (const void *)(base + *cursor), size[1]);
	*cursor += size[1];
	obj->setFileData(data, size[1]);
	return obj;
}
