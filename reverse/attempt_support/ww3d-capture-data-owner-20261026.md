# WW3D capture flag: verify the existing owner and reconcile five consumers

Base `d41006c64d`, 2026-10-26. Claimed ww3d.cpp and all five consumer files.
The existing private `bool WW3D::IsCapturing = false` is defined by ww3d.cpp
through `reference/shims/bfme2_ww3d/ww3d.h`. Its COFF name is
`?IsCapturing@WW3D@@0_NA`; no source or header edit to that owner is needed.

Upstream `397acb4f2e` changed five consumers to public access to match the
heuristic data catalogue's public spelling. That removed shadow data warnings
but left them referring to `?IsCapturing@WW3D@@2_NA`, with no definition.
The initial six-current-object preview confirms that exact unresolved name
in all five consumers. Reverting the declarations alone would restore the
catalogue mismatch, so the repair first records the proven existing data owner.

## Target facts and ownership proof

Seven DIR32 operands from independently matched consumer bodies establish
VA `0x00DEC3D6` (RVA `0x009EC3D6`), all with zero in-object addends:

| Body RVA / size | Operand offsets | Purpose |
|---|---|---|
| `0x00118530` / 213 | `+0x1A`, `+0x36` | Start: byte test and store 1 |
| `0x00117A10` / 74 | `+0x02`, `+0x13` | Stop: byte test and store 0 |
| `0x00118170` / 294 | `+0x64` | Begin render: byte test |
| `0x001180E0` / 134 | `+0x18` | Shutdown: byte test |
| `0x00118610` / 48 | `+0x02` | Toggle: byte test |

The address is in the loader-zero tail of retail `.data`, not backed by a
byte at a raw file offset. The existing owner object defines the private
symbol in `.bss`. Its one-byte extent is verified by the normal data-row
compiler `sizeof` probe using the shim's existing DataRowPrivateProbe friend;
the next symbol's offset alone is not the size proof. The initializer matches
retail zero. No matched owner-body operand is claimed: address evidence comes
from the consumers; source/COFF and the normal data gate establish the owner.

One verified data row is added, without a second global, pin, alias or manual
edit of the generated data catalogue. The existing `data_ledger.load()`
reconciliation gives that owner priority over its heuristic entry. The five
local views then use private access consistently, preserving their existing
friends and public methods. The donor's access spelling is not claimed as a
newly recovered retail source declaration.

## Verification and limits

The six whole sources pass **30/30 functions**, **five data rows** (four
existing plus the one-byte owner), three string literals, seven float literals
and four named imports. All **three EH graphs are EXACT**; frozen-file checks
pass for every source. Code identity reports 54 references (46 owner, five
alias, three EH), zero wrong bindings.

Before/after COFF comparison confirms all seven consumer rows have identical
body bytes and relocation lists except for the intended capture-name change;
the entire ww3d.cpp object is identical. The effective data index selects the
private one-byte owner. The shadow data check remains at its same ten unrelated
findings, including two unregistered DefaultStaticSortLists findings; no
IsCapturing finding is introduced and no debt-key retirement is counted.

Against the unchanged `763dc8759f` index, the six-current-object ordinary
preview goes from **0/6, 818 -> 0 bytes**, to **5/6, 818 -> 818**. All five
consumer units link in that bounded preview; this restores 818 authored bytes
in the current-object comparison, not a gain over the published census.
ww3d.cpp itself still has its unrelated missing callees and divergent
Flush/Set_Render_Device definitions, so the combined command still exits 1.
No complete-image, census or runtime clearance is claimed.

Reproduction: normal build, `eh_verify.py`, `allowed_symbols.py --source`,
`data_check.py`, `find_declared_unmatched.py` and `link_check.py` on ww3d.cpp,
GapBodiesGE41_Rva00118610.cpp, WW3DBeginRenderBFME2.cpp,
WW3DShutdownRenderDevice.cpp, WW3DStartMovieCapture.cpp and
WW3DStopMovieCapture.cpp. Detailed local receipts are under
`build/codex-cleanup-20261025/iteration23-capture-*.log`.
