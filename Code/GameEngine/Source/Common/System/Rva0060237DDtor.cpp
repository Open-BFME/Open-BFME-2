// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ??1Rva0060237D@@UAE@XZ @0x0060237D 68B evidence: vtable VA 0x0087A7B8 at +0; delete[] at +0x14 via 0x0002FD80; StringBase char releaseBuffer at +0x24 via 0x00036410; base File dtor via 0x006025CE row; unblocks deleting dtor 0x006023F6

void __cdecl operator delete[](void *) throw();

typedef void *FileHandle;

template <typename T>
class StringBase
{
	friend class Rva0060237D;
private:
	void releaseBuffer();
	void *m_data;
};

class AsciiString
{
public:
	void set(const char *str);
	void clear();
private:
	StringBase<char> m_base;
};

class File
{
public:
	virtual ~File();
	virtual bool open(const char *filename, int access);
	virtual void close();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void lock();
	virtual void unlock();
private:
	AsciiString m_nameStr;
	int m_access;
	unsigned char m_isOpen;
	unsigned char m_deleteOnClose;
	unsigned char m_pad0E[2];
	FileHandle m_mutex;
};

class Rva0060237D : public File
{
public:
	virtual ~Rva0060237D();
private:
	char *m_14;
	char m_pad18[0x0C];
	StringBase<char> m_24;
};

Rva0060237D::~Rva0060237D()
{
	delete[] m_14;
	m_24.releaseBuffer();
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?slot03@File@@UAEXXZ=?write@RAMFile@@UAEHPBXH@Z")
#pragma comment(linker, "/alternatename:?slot05@File@@UAEXXZ=?seek@MemoryReadFile@@UAEHHW4seekMode@File@@@Z")
#pragma comment(linker, "/alternatename:?slot10@File@@UAEXXZ=?print@File@@UAA_NPBDZZ")
#pragma comment(linker, "/alternatename:?slot11@File@@UAEXXZ=?get@Rva002A79A1DwordField@@QBEHXZ")
#pragma comment(linker, "/alternatename:?slot12@File@@UAEXXZ=?getData@NetWrapperCommandMsg@@QAEPAEXZ")
#pragma comment(linker, "/alternatename:?slot13@File@@UAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")
