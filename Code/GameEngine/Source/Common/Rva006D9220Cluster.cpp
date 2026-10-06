// cl: /MD /EHsc
// AptArray::~AptArray at retail 0x006D9220 (188 bytes); rowed here under the
// existing opaque pin ??1Rva006DA560@@UAE@XZ because the class name itself is
// not in the binary. Identity evidence: the three assert strings live in
// AptArray.cpp -- "mpValues == NULL", "mnLength == 0" and "mnCapacity == 0",
// each with "DestroyGCPointers Was not called on this object before deletion!"
// -- at lines 0x47/0x48/0x49, and the scalar deleting dtor 0x006DA560 calls
// this complete dtor (pin). Class derives from the rowed base at 0x006D6470
// (Rva006D6470Owner) and stores its own vtable 0x00CEA778 (DIR32 auto-patch).
// The dtor only asserts the array was emptied, then calls the base around the
// standard SEH registration; it does not itself null the members.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)

class Rva006D6470Owner
{
public:
	virtual ~Rva006D6470Owner();
};

class Rva006DA560 : public Rva006D6470Owner
{
public:
	virtual ~Rva006DA560();

private:
	char m_pad04[0x20 - 4];
	void *mpValues;   // +0x20
	int mnCapacity;   // +0x24
	int mnLength;     // +0x28
};

#define BFME_APT_ASSERT(expr)                                                  \
	do {                                                                       \
		if (!(expr)) {                                                         \
			g_bfmeAptAssertAtE17734(#expr,                                     \
				"C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptArray.cpp", \
				0);                                                            \
			if (g_bfmeAptBreakOnAssertAtDDC01C)                                \
				__debugbreak();                                                \
		}                                                                      \
	} while (0)

Rva006DA560::~Rva006DA560()
{
	if (mpValues != 0) {
		g_bfmeAptAssertAtE17734("mpValues == NULL && \"DestroyGCPointers Was not called on this object before deletion!\"", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptArray.cpp", 0x47);
		if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
	}
	if (mnLength != 0) {
		g_bfmeAptAssertAtE17734("mnLength == 0 && \"DestroyGCPointers Was not called on this object before deletion!\"", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptArray.cpp", 0x48);
		if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
	}
	if (mnCapacity != 0) {
		g_bfmeAptAssertAtE17734("mnCapacity == 0 && \"DestroyGCPointers Was not called on this object before deletion!\"", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptArray.cpp", 0x49);
		if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
	}
}
