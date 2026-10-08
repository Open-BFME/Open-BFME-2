// cl: /O1 /EHsc /G7 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// Native 0x0020F5B3..0x0020F685 proves the 210-byte body. Existing
// callers and the pinned Rva0020EE29Inner owner establish the receiver.
// Its +0x2C pointer collection, +0x4C destination, entry +0x198 pointer
// and +0x1A8/+0x1AC array of 24-byte records are native layout facts.
// The record's +8 integer is forwarded to the rowed lookup/collector.
// Broader entry and record identities remain unknown. Preserve the
// established address-derived method name; the named WB caller identifies
// the pathfinder role but does not independently name this retail body.
// Typed 24-byte indexing supplies the exact offset lifetime and SIB shape
// missing from the earlier bank's hand-maintained byte offset.
// stlport
#include <vector>
// Use the existing out-of-line void-pointer vector provider.
template <> void **_STL::vector<void *>::erase(void **first, void **last);
struct Rva0020F5B3Range { void **begin; void **end; };
struct Rva002BA8F1Listener;
class Rva005A0B4CList
{
public:
	void append(Rva002BA8F1Listener *p);
};
struct Rva003EF7DFDest;
class Rva003EF7DF
{
public:
	void rva003EF7DF(Rva003EF7DFDest *dest, int value);
};
struct Rva0020F5B3Record { char pad00[8]; int value; char pad0C[12]; };
struct Rva0020F5B3Elem
{
	char m_pad00[0x198];
	void *m_ptr198;
	char m_pad19C[0xC];
	Rva0020F5B3Record *m_arrBegin;
	Rva0020F5B3Record *m_arrEnd;
};
struct Rva0020EE29Inner
{
public:
	void rva0020F5B3();
	_STL::vector<Rva0020F5B3Elem *> &entries() { return m_2C; }
private:
	char m_pad00[0x2C];
	_STL::vector<Rva0020F5B3Elem *> m_2C;
	char m_pad38[0x14];
	void *m_4C;
};
void Rva0020EE29Inner::rva0020F5B3()
{
	Rva0020F5B3Range *range = (Rva0020F5B3Range *)m_4C;
	if (range == 0)
		return;
	_STL::vector<void *, _STL::allocator<void *> > *vec = (_STL::vector<void *, _STL::allocator<void *> > *)range;
	vec->erase(range->begin, range->end);
	for (unsigned int i = 0; i < m_2C.size(); ++i)
	{
		Rva0020F5B3Elem *e = m_2C[i];
		((Rva005A0B4CList *)m_4C)->append((Rva002BA8F1Listener *)e->m_ptr198);
	}
	for (unsigned int j = 0; j < m_2C.size(); ++j)
	{
		Rva0020F5B3Elem *e = m_2C[j];
		for (unsigned int k = 0; k < (unsigned int)(e->m_arrEnd - e->m_arrBegin); ++k)
		{
			((Rva003EF7DF *)m_4C)->rva003EF7DF((Rva003EF7DFDest *)e->m_ptr198, e->m_arrBegin[k].value);
		}
	}
}

// Native 0x0052C161..0x0052C1D6 and the pinned same-receiver call in
// Rva0052C036::rva0052C9F9 establish this owner and 117-byte extent.
// WB 0x0133C2F0 is unnamed, but corroborates the +0x1C campaign and
// region-manager reset / indexed activation / effects / pathfinder order.
// The singleton chains and the four-byte collection slots are native facts;
// the owner and slot meanings remain address-derived views.
class Rva0020EB41 {public: void rva0020EB41();};
class Rva002104C7 {public: bool rva002104C7(void*,void*);};
class Rva003EF008 {public: void rva003EF008();};
struct Rva0052C161RegionManager: Rva0020EB41 {
 char unknown00[8]; Rva0020EE29Inner *campaign;
};
struct Rva0052C161World {char unknown00[0xB0]; Rva0052C161RegionManager *regions;};
struct Rva0052C161Manager {char unknown00[0x268]; Rva003EF008 *effects;};
class LivingWorldLogic; extern LivingWorldLogic *TheLivingWorldLogic;
class LivingWorldManager; extern LivingWorldManager *TheLivingWorldManager;
class Rva0052C036 {
 char unknown00[0x1C]; Rva0020EE29Inner *campaign;
 public: void rva0052C161();
};
void Rva0052C036::rva0052C161() {
 reinterpret_cast<Rva0052C161World*>(TheLivingWorldLogic)->regions->rva0020EB41();
 if(campaign) {
  _STL::vector<Rva0020F5B3Elem *> &entries=campaign->entries();
  for(unsigned i=0;i<entries.size();++i)
   reinterpret_cast<Rva002104C7*>(reinterpret_cast<Rva0052C161World*>(TheLivingWorldLogic)->regions)->rva002104C7(&entries[i],0);
 }
 reinterpret_cast<Rva0052C161Manager*>(TheLivingWorldManager)->effects->rva003EF008();
 reinterpret_cast<Rva0052C161World*>(TheLivingWorldLogic)->regions->campaign->rva0020F5B3();
}
