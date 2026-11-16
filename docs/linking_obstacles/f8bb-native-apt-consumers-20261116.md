# f8bb APT consumer regression: native-provider repair

Commit f8bb682906e removed the sole compatibility binding from the synthetic
Rva00222A8BTarget::rva00222B19 spelling to the existing rowed stdcall provider
Rva00222B19AptCall (0x00222B19). The real link at f8bb, published by
9bde27ffb56, lists 22 affected consumers. The provider itself was unchanged.

The current bounded repair covers 20 claimed consumers. Each now addresses
Rva00222B19AptCall directly through a local one-word member-call view. On the
retail x86 ABI this preserves the original ECX setup plus the same nine stack
arguments and RET 0x24. The provider ignores ECX. A compile-time size check
refuses a wider member-pointer representation. This is an explicit MSVC ABI
view using the actual provider address, not a forwarding body, alternate
symbol, alias, pin or identity claim about the synthetic class.

Private Boat before/after at cfa9fc960aa: all 20 units build and match 373/373
function rows. Every consumer's own link_check verdict is LINKS (20,277
predicted bytes preserved); the once-fetched index is the 02:02 census at
1300d9f970, which predates the alias removal. Therefore those predictions
alone are not current real-image proof. Raw COFF independently shows the old
undefined name in all 20 before objects, absent from all 20 after objects,
and the real rowed provider name referenced by all 20 after objects.
vt_undefined reports zero newly undefined vtable references. The staged
hatch check passes; no baseline, alias, pin, ledger or provider is added or
changed. Both full objects and dependency receipts are retained.

Two real-image consumers remain outside this repair because of foreign
claims: Common/StrategicHUD.cpp (StarkillerHDX file-claim footprints) and
GameClient/GUI/InGame/Tactical/InGameHeroSelectInterface.cpp
(StarkillerHDX class:Drawable). Do not call the whole 22-unit group cleared.
The lexical scan also finds an old call in the unrowed helper retained in
StrategicHUDRegionDetailsStructuresMovieClip.cpp; that source has six other
ledger rows but is not one of the real-image blocker sources. It is not
changed in this bounded 22-source regression repair.

Evidence on srv1: ~/bfme2-ops/swarm/sweeps/slotnames/red-apt-verification/,
red-apt-native-symbol-proof.json, red-apt-owned-units.txt and
red-link-blockers-f8bb.tsv. Full-image and runtime validation remain pending.
