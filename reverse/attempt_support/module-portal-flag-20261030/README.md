# Weapon portal-flag Module adoption, 2026-10-30

WeaponRva002CB2D1Range.cpp includes canonical eight-byte Module and casts the
existing finder result only for its observed bool at +3C. Native 2CB44C calls
the existing DynamicPortalBehaviour finder; 2CB45A tests result byte +3C.
The finder at 4608E0 returns the unadjusted module-list entry (load at 460948),
not an interior interface pointer. Its declaration/call remain unchanged.
The partial storage view does not establish an original complete derived type.

Private original/corrected probes verify both whole-file rows and preserve all
three external code definitions and symbolic relocations. The actual strict
object must reproduce this. Native instructions/finder bytes and receipt facts
are in proof.json. Retire this file's Module header key through acceptance;
its separate Weapon header key and private Weapon reconciliation remain open.
No shared header, ledger, pin, hatch, build flag or path changes. Preserve
link coverage and qualify the broader audit by the old index/current receipts.
The normal current-source prediction retains LINKS/707 bytes.
