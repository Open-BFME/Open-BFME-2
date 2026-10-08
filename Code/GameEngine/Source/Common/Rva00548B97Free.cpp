// cl: /MD
// ?Rva00548B97Free@@YAXH@Z @0x00548B97 83B. Free cdecl void(int): if index
// 8 and its overlay slot set calls rowed Rva003B3371Call(22), then frees
// global array 0x00A05F88[index] via virtuals slot3(int) slot8() slot1(int)
// returning pointer for operator delete plus null. Evidence: rowed free
// plus 3 virtuals plus delete; 4 callers.
class Rva00548B97Helper
{
public:
	virtual void v0();
	virtual void *v1(int a1);
	virtual void v2();
	virtual void v3(int a1);
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual void v7();
	virtual void v8();
};

// One nine-slot overlay table. The cleanup body at 0x00548B97 reads
// VA 0x00e05fa8, exactly slot eight of the indexed table at 0x00e05f88.
// All 36 bytes are zero in retail. The old separate G00A05FA8 definition
// represented this same slot rather than an independent integer flag.
Rva00548B97Helper *G00A05F88[9];

void __cdecl Rva003B3371Call(int index);
void operator delete(void *p);

void __cdecl Rva00548B97Free(int index)
{
	if (index == 8 && G00A05F88[8] != 0)
		Rva003B3371Call(22);
	Rva00548B97Helper **slot = &G00A05F88[index];
	if (*slot != 0) {
		(*slot)->v3(0);
		(*slot)->v8();
		void *q = *slot ? (*slot)->v1(0) : 0;
		::operator delete(q);
		*slot = 0;
	}
}

// The public enum and boolean signature come from GameSpyOverlay.h. The
// query, cleanup, toggle, update and raise bodies independently identify the
// same retail table. BFME 1 9cbfb551fe20's GameSpyOverlay_close.cpp also
// records nine slots and the options slot at base + 32.
enum GSOverlayType;
bool GameSpyIsOverlayOpen(GSOverlayType overlay)
{
	return G00A05F88[overlay] != 0;
}
