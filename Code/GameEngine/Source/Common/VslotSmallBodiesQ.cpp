// cl: /DNDEBUG /MD
//
// Small vtable-slot bodies with no ledger owner and no Ghidra entry (sized
// from their bytes) in the /O2 library range, batch Q. As in
// VslotSmallBodiesA-P, each class and method is address-derived unless the
// ledger already names it, and models only what its body touches; the comment
// above each gives the .rdata slot address that references it. Meanings are
// not recovered.

typedef int Int;

// slots at VA 0x00CE3170, 0x00CE3188 and 0x00CE36A4: the message's integer
// for the key held at VA 0x00DD8280 (resp. 0x00DD8288 and 0x00DD8310),
// default 0, through the rowed Rva007E8810Message::getInt.
class Rva007E8810Message
{
public:
	Int getInt(const char *key, Int defaultValue);
};
extern const char *g_rva00665450Key;
extern const char *g_rva00665560Key;
extern const char *g_rva00668090Key;
class Rva00665450
{
public:
	Int rva00665450(Rva007E8810Message *msg);
	Int rva00665560(Rva007E8810Message *msg);
	Int rva00668090(Rva007E8810Message *msg);
};
Int Rva00665450::rva00665450(Rva007E8810Message *msg)
{
	return msg->getInt(g_rva00665450Key, 0);
}
Int Rva00665450::rva00665560(Rva007E8810Message *msg)
{
	return msg->getInt(g_rva00665560Key, 0);
}
Int Rva00665450::rva00668090(Rva007E8810Message *msg)
{
	return msg->getInt(g_rva00668090Key, 0);
}

// slot at VA 0x00CE3790: the entry of the NULL-terminated table at VA
// 0x00DD8320 whose +0x08 id equals the argument's +0x1C id, or NULL (also for
// id -1).
struct Rva00669410Entry
{
	char m_pad00[0x08];
	Int m_08;
};
struct Rva00669410Arg
{
	char m_pad00[0x1C];
	Int m_1C;
};
extern Rva00669410Entry *g_rva00669410Table[];
class Rva00669410
{
public:
	Rva00669410Entry *rva00669410(const Rva00669410Arg *arg);
};
Rva00669410Entry *Rva00669410::rva00669410(const Rva00669410Arg *arg)
{
	Int id = arg->m_1C;
	if (id == -1)
		return 0;
	for (Rva00669410Entry **it = g_rva00669410Table; *it; ++it)
	{
		if ((*it)->m_08 == id)
			return *it;
	}
	return 0;
}

// slots from VA 0x00CEE928 on: runs the rowed 0x006FBED0 on this object while
// the pointer at VA 0x00E1835C is NULL.
extern void *g_rva00709A00Pending;
class Rva8D0D80Result
{
public:
	void rva006FBED0();
	void rva00709A00();
};
void Rva8D0D80Result::rva00709A00()
{
	if (!g_rva00709A00Pending)
		rva006FBED0();
}

// slot at VA 0x00CEEB38: copies the +0x3C/+0x40 pair into the argument.
struct Rva0070A310Pair
{
	Int m_00;
	Int m_04;
};
class Rva0070A310
{
public:
	void rva0070A310(Rva0070A310Pair *out);
private:
	char m_pad00[0x3C];
	Int m_3C;
	Int m_40;
};
void Rva0070A310::rva0070A310(Rva0070A310Pair *out)
{
	out->m_00 = m_3C;
	out->m_04 = m_40;
}

// slots at VA 0x00CEEB40 and 0x00CEEB24 (beside the two above): Apt script
// function stubs that only assert false through the shared Apt assert triple
// (AptValuePtrStackTop.cpp), naming AptScriptFunction.h lines 0x1CA and 0x1D2.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)
class Rva0070A330
{
public:
	void rva0070A330(Int a, Int b);
	Int rva0070A360(Int a);
};
void Rva0070A330::rva0070A330(Int, Int)
{
	g_bfmeAptAssertAtE17734("false", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptObject/AptScriptFunction.h", 0x1CA);
	if (g_bfmeAptBreakOnAssertAtDDC01C)
		__debugbreak();
}
Int Rva0070A330::rva0070A360(Int)
{
	g_bfmeAptAssertAtE17734("false", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptObject/AptScriptFunction.h", 0x1D2);
	if (g_bfmeAptBreakOnAssertAtDDC01C)
		__debugbreak();
	return 0;
}

// slot at 0x007581E0: the rowed 0x0075A490 on the +0x10 object inside a "collision"
// profile range.
class Profile
{
public:
	static void StartRange(const char *range);
	static void StopRange(const char *range);
};
class BfmeThingCGD
{
public:
	void bfmeGoCGD();
};
class Rva007581E0
{
public:
	void rva007581E0();
private:
	char m_pad00[0x10];
	BfmeThingCGD *m_10;
};
void Rva007581E0::rva007581E0()
{
	Profile::StartRange("collision");
	m_10->bfmeGoCGD();
	Profile::StopRange("collision");
}

// Native E1835C is the script-function current frame root. Bind its shared provider.
#pragma comment(linker, "/alternatename:?g_rva00709A00Pending@@3PAXA=?spFrameStack@AptScriptFunctionBase@@1PAVAptFrameStack@@A")
