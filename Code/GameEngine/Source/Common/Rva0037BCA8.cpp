// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /EHsc /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_STLP_NO_EXCEPTIONS
//
// ?rva0037BCA8@Rva0037BBED@@QAE?AVUnicodeString@@XZ, retail 0x0037BCA8, 28 bytes.
// Evidence: this+0x10 is FILE* (prev Rva0037BBED dtor closes m_10 via fclose); forwards hidden+file to rowed readUnicodeString 0x0037B648 returning by value (hidden at [ebp+8], ret 4, mov eax hidden); callers in 0x0037CBB6/0x0037D55E.
#include "unicode_string.h"

struct _iobuf
{
};

UnicodeString readUnicodeString(_iobuf *file);

class Rva0037BB53
{
public:
	virtual ~Rva0037BB53();
	char m_pad[0xE3C - 4];
};

class GameEngineDeletingBase
{
public:
	virtual ~GameEngineDeletingBase();
	int m_pad04;
	int m_pad08;
};

class Rva0037BBED : public GameEngineDeletingBase
{
public:
	virtual ~Rva0037BBED();
	UnicodeString rva0037BCA8(void);
private:
	int m_0c;
	void *m_10;
	UnicodeString m_14;
	int m_18;
	int m_1c;
	UnicodeString m_20;
	Rva0037BB53 m_24;
};

UnicodeString Rva0037BBED::rva0037BCA8(void)
{
	return readUnicodeString((_iobuf *)m_10);
}
