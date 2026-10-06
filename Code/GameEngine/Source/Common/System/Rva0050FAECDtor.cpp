// cl: /Ireference/shims/bfme2_ascii /EHsc
// ??1Rva0050FAEC@@UAE@XZ retail 0x0050FAEC 11B
// Trivial dtor: stores vtable 0x00865518 then tail-jmps to pinned base dtor
// 0x005248D0. Evidence: 11B mov-plus-jmp shape, no EH prolog, caller 0x0050E7C8,
// unwind funclets at 0x007948B2/0x00794921/0x00794956 reference it.
class Rva005248D0
{
public:
	virtual ~Rva005248D0();
};

extern "C" char *__cdecl strcpy(char *destination, const char *source);
extern "C" __declspec(dllimport) int __cdecl _snprintf(char *buffer, unsigned int count, const char *format, ...);

// The list row built by 0x0050F85D, whose constructor binds
// "_level<n>.<name>_color" to color as a member pointer.
class Rva0050FAEC : public Rva005248D0
{
public:
	virtual ~Rva0050FAEC();

	void color(int query, char *result, bool skip);

private:
	unsigned char m_pad04[0x58 - 0x04];
	int m_color; // +0x58
};

Rva0050FAEC::~Rva0050FAEC()
{
}

// Retail 0x0050E7EB, 54 bytes: "_level<n>.<name>_color", an Apt query
// answering the row's color ("0" when skipped).
void Rva0050FAEC::color(int query, char *result, bool skip)
{
	strcpy(result, "0");
	if (!skip)
		_snprintf(result, 0xFF, "%d", m_color);
}

// Retail's strcpy call lands on the import thunk rowed as ji_00629176.
#pragma comment(linker, "/alternatename:_strcpy=?ji_00629176@@YAXXZ")
