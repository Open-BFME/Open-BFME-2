// ?rva0020F9F6@Rva0020EE29@@QAEPAXPAX00@Z
// cl: /O1 /G7 /arch:SSE /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>
// Target20F9F6..20FAB4,190B: if the inner pointer range and manager268
// exist, test the preferred item first, then the remaining items; without a
// preference test all items. Return the first accepted pointer or null.
// Native calls20F91D four times with receiver unchanged and start/direction
// pointer inputs. Its existing typed provider performs the asset ray test.
// Inner at this+8 and range2C/30 are native facts; item identity is unknown.
// The STLport vector accessor and two-word range view preserve the observed
// count/address loads. The third vector word is not accessed or asserted.
// A borrowed volatile view of the local receiver reproduces native stack
// spill/reloads in the loops; this does not claim an original volatile type.
// The two explicit branches share the final null return, matching native
// conditional EBX save and final epilogue. No new globals, pins or aliases.
class Vector3;
class Rva0020F91D {public:bool rva0020F91D(void*,const Vector3*,const Vector3*);};
struct Rva0020F9F6Span {void **begin;void **end;};
struct Rva0020EE29Inner {char prefix[0x2c];_STL::vector<void*> m_entries;};
class Rva0020EE29 {public:void*rva0020F9F6(void*,void*,void*);private:char prefix[8];Rva0020EE29Inner*m_inner;};
class LivingWorldManager;extern LivingWorldManager *TheLivingWorldManager;
struct Rva00DFE1C8Host {char prefix[0x268];int m_268;};
void *Rva0020EE29::rva0020F9F6(void *a1, void *a2, void *preferred)
{
	Rva0020EE29Inner *inner = m_inner;
	unsigned i = 0;
 Rva0020F91D * const receiver=(Rva0020F91D*)this;
	if (!inner)
		return 0;
	if (((Rva00DFE1C8Host *)TheLivingWorldManager)->m_268 == (int)i)
		return 0;
	if (preferred != 0) {
		if (((Rva0020F91D*)this)->rva0020F91D(preferred, (const Vector3*)a1, (const Vector3*)a2))
			return preferred;
		for (i = 0; i < (unsigned)(((const Rva0020F9F6Span*)&inner->m_entries)->end - ((const Rva0020F9F6Span*)&inner->m_entries)->begin); ++i) {
			if (inner->m_entries[i] == preferred)
				continue;
			if (((Rva0020F91D *const volatile &)receiver)->rva0020F91D(inner->m_entries[i], (const Vector3*)a1, (const Vector3*)a2))
				return inner->m_entries[i];
		}
	} else {
	for (i = 0; i < (unsigned)(((const Rva0020F9F6Span*)&inner->m_entries)->end - ((const Rva0020F9F6Span*)&inner->m_entries)->begin); ++i) {
		if (((Rva0020F91D *const volatile &)receiver)->rva0020F91D(inner->m_entries[i], (const Vector3*)a1, (const Vector3*)a2))
			return inner->m_entries[i];
	}
	}
	return 0;
}

