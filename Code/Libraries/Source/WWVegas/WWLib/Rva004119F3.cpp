// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /EHsc /Ireference/open-bfme-1/inputs/reference/shims/stringinline /O1 /arch:SSE /G7
// ?Rva004119F3Get@@YAPAXPAXPBVAsciiString@@H@Z @0x004119F3 88B free helper via make plus virtual plus table plus releaseBuffer. Evidence: caller 0x0041215B via add esp 0xC plus callee pins makeRva0074104C plus rva004112A0 plus Release_Ref plus releaseBuffer plus globals none new.
typedef int Int;

class AsciiString;

class Rva0074104C
{
public:
	virtual void* slot00(const AsciiString* a, int b);
	virtual void* slot04(const AsciiString* a, int b);
	void* m_04;
};

Rva0074104C* makeRva0074104C();

class Rva000427195
{
public:
	void* rva004112A0(const AsciiString* key);
};
extern const void* const g_00E0300C[];

template<class T>
class StringBase
{
public:
	StringBase() { m_data = 0; }
	~StringBase() { releaseBuffer(); }
	friend void* Rva004119F3Get(void*, const AsciiString*, int);
private:
	void releaseBuffer();
	void* m_data;
};

void* Rva004119F3Get(void* a, const AsciiString* b, int c)
{
	StringBase<char> tmp;
	Rva0074104C* obj = makeRva0074104C();
	obj->slot04(b, c);
	obj->m_04 = a;
	void* ret = ((Rva000427195*)&g_00E0300C)->rva004112A0(b);
	*(void**)ret = obj;
	return obj;
}
