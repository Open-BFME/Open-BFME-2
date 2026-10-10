// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX- /GS-
// ?Rva00075725Check@@YA_NHH@Z 0x00075725 33B: free function indexed via g_00DE1F2C, null check then virtual slot 4 call; callers 0x00085F6A/0x00085F50 test al
class Rva00075725Item
{
public:
	virtual void f0();
	virtual void f1();
	virtual void f2();
	virtual void f3();
	virtual bool Slot4(int arg);
};

// g_00DE1F2C is the W3DFilters array (data ledger, owned by
// W3DShaderManager.cpp); name it so nothing dangles. The Rva00075725Item
// view above is kept for the slot-4 call shape.
class W3DFilterInterface;
extern W3DFilterInterface *W3DFilters[];

bool __cdecl Rva00075725Check(int index, int arg)
{
	W3DFilterInterface * volatile *slot = (W3DFilterInterface * volatile *)&W3DFilters[index];
	if (*slot != 0)
		return ((Rva00075725Item *)(*slot))->Slot4(arg);
	return false;
}

// Other units call this body (pinned at its address) under the spelling(s)
// below, with the same calling convention and stack arguments; bind them.
#pragma comment(linker, "/alternatename:?filterSetup@W3DShaderManager@@SA_NW4FilterTypes@@W4FilterModes@@@Z=?Rva00075725Check@@YA_NHH@Z")
