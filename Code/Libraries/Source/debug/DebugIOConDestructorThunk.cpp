// cl: /DNDEBUG /MD /EHa /Oy-
// readable body of ??1DebugIOCon@@UAE@XZ: Code/Libraries/Source/debug/debug_io_con.cpp
// Open-BFME5: clean C++ DebugIOCon dtor. Retail keeps
// an EBP frame (/Oy-): stores its own vtable at entry, FreeConsole() when the
// byte flag at this+4 is set, then runs the inlined base dtor (base vtable
// store) on the normal and unwind paths.

extern "C" __declspec(dllimport) void __stdcall FreeConsole(void);

class DebugIOConBase
{
public:
	virtual ~DebugIOConBase() {}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug/internal_io.h
class DebugIOCon : public DebugIOConBase
{
public:
	virtual ~DebugIOCon();

private:
	bool m_allocatedConsole;
};

// ??1DebugIOCon@@UAE@XZ
DebugIOCon::~DebugIOCon()
{
	if (m_allocatedConsole) {
		FreeConsole();
	}
}

// Whole BFME 1 R1MemberPredicates.cpp at9cbfb551fe emits this byte test under
// the clean named Common O2/x87/G6 min5 sweep. Native408C0..408C9 is
// INT3-bounded, reads ECX+4 and normalizes that byte to0/1 in AL. No calls,
// globals, literals or direct/address references establish an original owner
// or richer prototype. Adjacent DebugIOCon code also uses byte+4, which makes
// this prescribed debug home suitable but does not prove a method identity.
// This ordinary fastcall projection models only the witnessed ECX input and
// low-byte return, with no class view, stack argument or original ABI claim.
bool __fastcall Rva000408C0NonzeroByte4(const unsigned char *receiver)
{
    if (receiver[4])
        return true;
    return false;
}
