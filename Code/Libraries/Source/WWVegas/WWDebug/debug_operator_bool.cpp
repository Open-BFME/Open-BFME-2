// cl: /DNDEBUG /MD /Oy- /EHsc

// Open-BFME5: Debug::operator<<(bool). const char* stream at vtable +0x38.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug/debug_debug.h
class Debug
{
public:
    class RepeatChar;
    class MemDump;
    class HResult;

    // Native BBE810 slots0..15: MSVC reverses this overload group.
    virtual Debug &operator<<(const RepeatChar &);
    virtual Debug &operator<<(const char *);
    virtual Debug &operator<<(int);
    virtual Debug &operator<<(unsigned);
    virtual Debug &operator<<(long);
    virtual Debug &operator<<(unsigned long);
    virtual Debug &operator<<(bool);
    virtual Debug &operator<<(float);
    virtual Debug &operator<<(double);
    virtual Debug &operator<<(short);
    virtual Debug &operator<<(unsigned short);
    virtual Debug &operator<<(__int64);
    virtual Debug &operator<<(unsigned __int64);
    virtual Debug &operator<<(const void *);
    virtual Debug &operator<<(const MemDump &);
    virtual Debug &operator<<(HResult);
    virtual ~Debug(); // Native slot16.
};

// ??6Debug@@UAEAAV0@_N@Z
Debug &Debug::operator<<(bool value)
{
	const char *text;
	if (value)
		text = "true";
	else
		text = "false";
	return (*this) << text;
}
