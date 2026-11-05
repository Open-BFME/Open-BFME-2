### LINK-390: Stale generated import thunks retain duplicate harness IAT slots

Status: Cleared for the three harness APIs only. Updated: 2026-11-05; inspected revision: e1babc273c585724de3309762e9c9e7ae700ac3a
(game sources unchanged through 5fbfe29b028d8aa2dd7852162237371e2a9c5d93).

Evidence / affected units: The real native VC7.1 link with all 1,964 requested retail
exports reports 393 unresolved names and zero duplicates, both with default REF and
with /OPT:NOREF /OPT:NOICF. These figures do not measure runtime correctness.
The REF diagnostic contains two named IAT slots for each of
kernel32.dll!GetVersion, kernel32.dll!GetVersionExA and
shell32.dll!SHGetSpecialFolderPathW; tools/real_image.py at a51fbd7f0f refuses
these duplicate slots. Retail has exactly one slot each, at VA 0x00BBA154,
0x00BBA20C and 0x00BBA79C respectively.

A scan of supplied .obj inputs found bare __imp__GetVersion,
__imp__GetVersionExA and __imp__SHGetSpecialFolderPathW requests only in the object
from Code/gen_small/imports_001.cpp. The source still defines
ji_00006dc6, ji_00006d4e and ji_00688236 (lines 503, 483 and 899).
The ledger now places the corresponding retail RVAs 0x00006DC6, 0x00006D4E and
0x00688236 in Kernel32ImportThunks.cpp and Shell32ImportThunks.cpp under
Code/Libraries/Source/Win32/, with typed stdcall IAT names. The older bodies
are stale providers, not newly uncovered retail functions.

Completed: The link tooling roots one canonical stdcall spelling per harness API,
preserves every requested import/provider, and binds __except_list as ABSOLUTE
zero. No game source was edited, import spelling was filtered, or replacement alias
was introduced in the Link lane. NOREF deliberately retains supplied COMDAT bodies.

Repair on master: 811358bb29 removes 424 stale bodies from imports_000.cpp and
imports_001.cpp, including these three. The Link lane rebased onto that repair.
The two affected objects passed 82/82 function and 82 named-import checks.
After restoring current objects from verified caches, a further 630-source scoped
build passed 5,340/5,340 functions, 45 data rows and all reference checks.

Verification: The NOREF/NOICF diagnostic at code commit
3bfe30efedb003155a49f486ba0aaa36e9f72ba8 has image SHA-256
fc2d10d59f07e7c476802d0fb631494d3c430cc6b5d09449ec6b695ffd786b08.
Its unstubbed pass reports 392 missing names and zero duplicates; its final pass
reports zero missing names and zero duplicates, with 392 distinct trap bodies.
Both static and address checks in real_image.py pass. Each required API has one
named slot. The two-spelling VC7.1 fixture also passes those import checks under
NOREF/NOICF; no import alias or removal of NOREF was needed.

Measured section virtual sizes, bytes (ours / retail): .text
10,079,540 / 8,096,994; .rdata 2,124,582 / 2,004,867. Trap text accounts for 6,272
bytes. These reconstruction options do not establish retail's link options.
15,983 ledger rows lack a unique mapped body: 11,438 have a name in the map but
unresolved identity, 4,542 do not define that name in the supplied object, and
three defined COMDAT names (26 bytes) are absent. Those three are local EH labels
at RVAs 0x00771147, 0x007782C3 and 0x007616BB; absence of those labels alone is
not proof their bodies were stripped. Another 729 rows belong to deliberately
omitted generated objects. The object-manifest bundle is 148,867,965 bytes
uncompressed and is retained in the image artifact.

Remaining limits: image_report.py exits 1 with 1,314 short vtables and 1,738 wrong
vtable slots, among other incomplete data/initializer findings. The diagnostic
also stubs ?ji_006291ae@@YAPAXPAXHI@Z: the memset path through
Rva00219B9EAccessor.cpp can trap there. The maintainer's subsequent restore is
not in this frozen image. No runtime or census pass is claimed; this diagnostic
cannot close a real-image gate.

Review hardening: export-origin missing functions are routed through export RVA
to their current ledger owners. In the earlier 393-name measurement, this
recovers 99 code-export errors; 283 data-export errors have no functions.csv
owner and remain visible in the (export unowned) bucket, which the picker safely
reports as rowless. Receipts now record authority and omission-proof status,
and only authoritative real images are staged. Diagnostic IAT stubs contain a
relocated pointer to their own trap at +4 under the original map name; a native
VC7.1 fixture and real_image.where identify both map_symbol and stubbed_name
correctly. stubbed.tsv records kind, section, symbol offset and trap offset.
The workflow diagnostic step has a separate 60-minute nonfatal timeout.
