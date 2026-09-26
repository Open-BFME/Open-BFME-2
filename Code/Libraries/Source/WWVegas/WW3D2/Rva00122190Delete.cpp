// cl: /O2 /MD
// ??_GGen_uw_001212f0@@QAEPAXI@Z, retail 0x00122190, 30 bytes.
// Gap between VectorClass deleting dtor 0x00122130 and BfmeEnumerationDesc
// ctor 0x001221B0 in dx8wrapper.cpp; owner is Gen_uw_001212f0 whose scalar
// dtor ??1 is pinned at 0x001212F0 (dup row, gen-uw-pin). Deleting dtor
// calls ??1 then deletes this if flag&1 and returns this; callees via pin
// and rowed ??3 0x0002FD60. Emitted via delete helper (famgen precedent).
void __cdecl operator delete(void *place);

class Gen_uw_001212f0
{
public:
	~Gen_uw_001212f0();
};

void deleteGen(Gen_uw_001212f0 *p)
{
	delete p;
}
