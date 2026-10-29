# ATL cache initializer data identity, 2026-10-29

The picker selected `Rva00C6E31EInitializers.cpp` for its data-identity
baseline entry at 0x00A09E50. The checked-in initializer already refers to
`ATL::CImage::s_cache`; the baseline still names an older placeholder. The
current-object retirement check refuses because it finds the `s_cache` name
instead of the data-row owner, `g_Va00E09E50`.

The data ledger names `?s_cache@CImage@ATL@@0VCDCCache@12@A` as the
provisional 16-byte global, and `Code/Libraries/Source/ATL/atlimage.cpp`
defines that member. The matched data row instead assigns a 4-byte
address-named global to `Rva007B6A00AtexitThunks.cpp`. A trial referenced
that existing data-row owner and cleared 16 bytes: the function matched 1/1,
the retirement check passed, and the unit retained LINKS 25 -> 25 bytes
against index `85f6b7f40c`. The commit hook refused the trial because its two
new address-named global occurrences grow the enforced hatch count. The trial
and baseline retirement were reverted; no debt was retired.

Next investigate the data ownership and all consumers together, including the
ATL definition and atexit thunk, and use the supported data/name tools to
establish the real owner before retrying retirement. The link preview is not
a consumer-wide check or census confirmation.
