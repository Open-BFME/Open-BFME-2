// cl: /MD
// ?Rva006CC7C0@@YAXPBD@Z @ 0x006CC7C0 (87B).
//
// Builds a temporary refcounted string from a C-string argument and hands it
// to the Apt worker at 0x006D0D70 on the object held by the global at
// VA 0x00E176CC, then lets the temporary's destructor release it. The
// constructor and destructor are the rowed EAStringC bodies at 0x006D4C80
// and 0x006D3010 (EAStringCRefCount.cpp); the class view below is the
// minimum needed to name them (private copy, EAStringC is not in
// canonical_classes.csv).
//
// The temporary is constructed inside the argument list rather than as a
// named local: that is what makes MSVC reuse the constructor's returned
// `this` (eax) as the argument, which retail's `push eax` shows. A named
// local compiles to an extra `lea ecx,[esp]` and shifts the whole tail.
//
// The SEH frame in retail (state 0 covers the live temporary, -1 after its
// destructor) is the normal unwind shape for the destructible local, so the
// body needs exception handling enabled even though the near file's line does
// not spell it; ./build.sh proved which flag set reproduces the frame.

class EAStringC
{
public:
	class StringDataC
	{
	public:
		unsigned short m_uRefCount;
		unsigned short m_uSize;
		unsigned short m_uMaxSize;
		unsigned short m_uHash;
	};

	StringDataC *m_pData;

	EAStringC(const char *text);
	~EAStringC();
};

// Rva006D1090 is the address-derived list worker (pin for 0x006D0D70); only
// the one member this body calls is declared. The global at VA 0xe176cc is
// owned by Rva00893030RefDispatch.cpp as g_rva00893030Manager
// (?g_rva00893030Manager@@3PAVRva00893030Manager@@A); cast at the call keeps
// the callee name (pin ?rva006D0D70@Rva006D1090@@QAEXPAX@Z) byte-identical.
class Rva006D1090
{
public:
	void rva006D0D70(void *value);
};

class Rva00893030Manager;
extern Rva00893030Manager *g_rva00893030Manager;
// g_rva00893030Manager: matched references place it at VA 0xe176cc (zero-filled .bss).

void Rva006CC7C0(const char *text)
{
	((Rva006D1090 *)g_rva00893030Manager)->rva006D0D70(&EAStringC(text));
}
