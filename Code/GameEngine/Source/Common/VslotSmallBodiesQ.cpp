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
const char *g_rva00665450Key = "errorCode";
const char *g_rva00665560Key = "decodedSize";
// Native DD8310 already belongs to BfmeConv482.cpp.
extern void *g_bfmeWhatBKG;
class Rva00665450
{
public:
	Int getErrorCode(Rva007E8810Message *msg);
	Int getDecodedSize(Rva007E8810Message *msg);
	Int rva00668090(Rva007E8810Message *msg);
};
Int Rva00665450::getErrorCode(Rva007E8810Message *msg)
{
	return msg->getInt(g_rva00665450Key, 0);
}
Int Rva00665450::getDecodedSize(Rva007E8810Message *msg)
{
	return msg->getInt(g_rva00665560Key, 0);
}
Int Rva00665450::rva00668090(Rva007E8810Message *msg)
{
	return msg->getInt((const char *)g_bfmeWhatBKG, 0);
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
// Native DD8320: all35 complete protocol slots already have definitions in
// StaticTagInitializers.cpp; preserve those names and the native pointer order.
class Rva007F0210;
extern Rva007F0210 bfmeRva0130A9C8TagSlot;
extern Rva007F0210 bfmeRva0130AA1CTagSlot;
extern Rva007F0210 bfmeRva0130AAF4TagSlot;
extern Rva007F0210 bfmeRva0130A9D4TagSlot;
extern Rva007F0210 bfmeRva0130A9BCTagSlot;
extern Rva007F0210 bfmeRva0130A9F8TagSlot;
extern Rva007F0210 bfmeRva0130AB48TagSlot;
extern Rva007F0210 bfmeRva0130AAACTagSlot;
extern Rva007F0210 bfmeRva0130AAA0TagSlot;
extern Rva007F0210 bfmeRva0130AA58TagSlot;
extern Rva007F0210 bfmeRva0130AADCTagSlot;
extern Rva007F0210 bfmeRva0130AA28TagSlot;
extern Rva007F0210 bfmeRva0130AAB8TagSlot;
extern Rva007F0210 bfmeRva0130AA10TagSlot;
extern Rva007F0210 bfmeRva0130AB3CTagSlot;
extern Rva007F0210 bfmeRva0130AA4CTagSlot;
extern Rva007F0210 bfmeRva0130AB30TagSlot;
extern Rva007F0210 bfmeRva0130AA34TagSlot;
extern Rva007F0210 bfmeRva0130AB18TagSlot;
extern Rva007F0210 bfmeRva0130AA64TagSlot;
extern Rva007F0210 bfmeRva0130AB00TagSlot;
extern Rva007F0210 bfmeRva0130AAC4TagSlot;
extern Rva007F0210 bfmeRva0130AA94TagSlot;
extern Rva007F0210 bfmeRva0130AA04TagSlot;
extern Rva007F0210 bfmeRva0130AA88TagSlot;
extern Rva007F0210 bfmeRva0130AB0CTagSlot;
extern Rva007F0210 bfmeRva0130AAE8TagSlot;
extern Rva007F0210 bfmeRva0130AB24TagSlot;
extern Rva007F0210 bfmeRva0130AA7CTagSlot;
extern Rva007F0210 bfmeRva0130A9ECTagSlot;
extern Rva007F0210 bfmeRva0130AA40TagSlot;
extern Rva007F0210 bfmeRva0130AA70TagSlot;
extern Rva007F0210 bfmeRva0130AAD0TagSlot;
extern Rva007F0210 bfmeRva0130A9B0TagSlot;
extern Rva007F0210 bfmeRva0130A9E0TagSlot;
Rva00669410Entry *g_rva00669410Table[] = {
    (Rva00669410Entry *)&bfmeRva0130A9C8TagSlot,
    (Rva00669410Entry *)&bfmeRva0130AA1CTagSlot,
    (Rva00669410Entry *)&bfmeRva0130AAF4TagSlot,
    (Rva00669410Entry *)&bfmeRva0130A9D4TagSlot,
    (Rva00669410Entry *)&bfmeRva0130A9BCTagSlot,
    (Rva00669410Entry *)&bfmeRva0130A9F8TagSlot,
    (Rva00669410Entry *)&bfmeRva0130AB48TagSlot,
    (Rva00669410Entry *)&bfmeRva0130AAACTagSlot,
    (Rva00669410Entry *)&bfmeRva0130AAA0TagSlot,
    (Rva00669410Entry *)&bfmeRva0130AA58TagSlot,
    (Rva00669410Entry *)&bfmeRva0130AADCTagSlot,
    (Rva00669410Entry *)&bfmeRva0130AA28TagSlot,
    (Rva00669410Entry *)&bfmeRva0130AAB8TagSlot,
    (Rva00669410Entry *)&bfmeRva0130AA10TagSlot,
    (Rva00669410Entry *)&bfmeRva0130AB3CTagSlot,
    (Rva00669410Entry *)&bfmeRva0130AA4CTagSlot,
    (Rva00669410Entry *)&bfmeRva0130AB30TagSlot,
    (Rva00669410Entry *)&bfmeRva0130AA34TagSlot,
    (Rva00669410Entry *)&bfmeRva0130AB18TagSlot,
    (Rva00669410Entry *)&bfmeRva0130AA64TagSlot,
    (Rva00669410Entry *)&bfmeRva0130AB00TagSlot,
    (Rva00669410Entry *)&bfmeRva0130AAC4TagSlot,
    (Rva00669410Entry *)&bfmeRva0130AA94TagSlot,
    (Rva00669410Entry *)&bfmeRva0130AA04TagSlot,
    (Rva00669410Entry *)&bfmeRva0130AA88TagSlot,
    (Rva00669410Entry *)&bfmeRva0130AB0CTagSlot,
    (Rva00669410Entry *)&bfmeRva0130AAE8TagSlot,
    (Rva00669410Entry *)&bfmeRva0130AB24TagSlot,
    (Rva00669410Entry *)&bfmeRva0130AA7CTagSlot,
    (Rva00669410Entry *)&bfmeRva0130A9ECTagSlot,
    (Rva00669410Entry *)&bfmeRva0130AA40TagSlot,
    (Rva00669410Entry *)&bfmeRva0130AA70TagSlot,
    (Rva00669410Entry *)&bfmeRva0130AAD0TagSlot,
    (Rva00669410Entry *)&bfmeRva0130A9B0TagSlot,
    (Rva00669410Entry *)&bfmeRva0130A9E0TagSlot,
    0
};
class Rva00669410
{
public:
	Rva00669410Entry *rva00669410(const Rva00669410Arg *message);
};
Rva00669410Entry *Rva00669410::rva00669410(const Rva00669410Arg *message)
{
	Int id = message->m_1C;
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
#include "../../../Libraries/Source/Apt/AptObject/AptScriptFunction.h"
class Rva8D0D80Result : public AptScriptFunctionBase
{
public:
	void rva006FBED0();
	void rva00709A00();
};
void Rva8D0D80Result::rva00709A00()
{
	if (!spFrameStack)
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
#include "../../../Libraries/Source/profile/profile.h"
class CollisionManagerImpl
{
public:
	void Update();
};
class Rva007581E0
{
public:
	void update();
private:
	char m_pad00[0x10];
	CollisionManagerImpl *m_10;
};
void Rva007581E0::update()
{
	Profile::StartRange("collision");
	m_10->Update();
	Profile::StopRange("collision");
}
