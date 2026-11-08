# Particle-info construction uses the existing C++ table provider

Rva005646BC.cpp stops defining g_00C1D3B0 as a single char containing the
first byte of a native vtable. Its subobject constructor now directly
references the existing ??_7Rva003AE315@@6B@ compiler table. The matched
33-byte copy constructor at 0x003AE315, in V3PolyDeferredCopyCtors.cpp,
installs that symbol at native RVA 0x0081D3B0. The data ledger already records
both spellings at that address; no alias, pin or address binding is added.

Target facts: the native table is 16 bytes, with four code slots. Its getter
at 0x003AE336 returns "ParticleTerrainCollisionModuleInfo". This literal does
not prove an original C++ namespace or donor source path; placeholder class
names are retained. The old char name is touched only by this source in the
index, and has no data_rows or data_converged owner. Removing its definition
therefore retires no matched data row or converged address. Historical ledger
spellings and the generated bridge queue are retained.

All three code rows and the two unrelated data rows remain byte-exact. The
parent EH graph is EXACT; the source remains unfrozen. Private LinkGuard is
clean, ordinary preview conserves LINKS/169 authored bytes, and strict
preparation creates a reusable receipt for this one owned source.

The attached bounded cached-object bridge replay includes this source, the
existing class-table provider and the four native slot owners. Before and
after both require one four-slot bridge, while strong-definition refusals
drop from one to zero. This is scoped provider evidence, not a replay of the
complete current image or proof that the game runs. No bridge is generated
or checked into Code by this pass. The real-link queue must confirm removal
of the old char-provider refusal.

Remaining: the existing class provider still exposes only one of the four
native slots. Full Snapshot/interface and member-type recovery must reconcile
the getter/xfer/destructor owners, then retire the temporary bridge. The two
separate one-byte data owners at native 0x0081D390/0x0081D3A0 remain in this
file; their registered rows require full containing-class/table recovery.
They are not removed or relabeled to hide that work.

Published as d171e84869, first attempt 34.2 seconds. Required gates pass
all three code rows, both data rows, the exact parent EH graph, scoped DIR32
for five symbols and converged data. Code-identity shadow reports no new
finding. Broader audit is INCONCLUSIVE: index eba83a23be versus base
7dca11f4660bec78fb099d6b37cceb0c3a03d484, affected
Common/ArmySummaryEntry.cpp lacks a current receipt. Current consumer
selection and the new real-link queue remain unverified.
