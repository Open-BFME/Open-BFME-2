### LINK-188: ArmyDetails static cleanup needs a distinct destructor lifetime

Status: Blocked. Updated: 2026-11-03; inspected revision: `bc8e2a3575`.
The two registered `Rva005F2FEFApt.cpp` atexit callbacks need the destructor
at 0x0048BA39, while seven ordinary cleanups need releaseBuffer at 0x36410.
Existing string-header modes cannot yet preserve both parent constructors
and those cleanup identities. Source trials were restored; all 43 rows match.
Next: recover the implicit-mode text constructor shape and establish current
provider closure before identity retirement. Census clearance is not claimed.
[Trial boundaries, relocation audit and verification](../../reverse/attempt_support/army-details-static-lifetime-20261103.md).
