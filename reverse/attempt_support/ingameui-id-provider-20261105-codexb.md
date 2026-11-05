# InGameUI Drawable ID provider binding, 2026-11-05

Inspected revision: `17b7ed563138d6aa11c19560d24a86ac1393869a`.
Scope: `InGameUISelectDrawable.cpp`, `InGameUIXfer.cpp` and
`InGameUICreateMouseoverHint.cpp` under `Code/GameEngine/Source/GameClient/`.

## Target facts and repair

The real-link blocker register lists `?getID@Drawable@@QBE?AW4DrawableID@@XZ`
in each unit. Current-object previews independently reproduce that sole
unresolved name in all three units. The existing pin maps it to `0x0055A88B`;
the ledger already owns the seven-byte body as
`?get@Rva0055A88BDwordField@@QBEHXZ` in `DispDwordFieldGetters.cpp`.
That provider reads a dword at `this + 0x100`, the canonical Drawable header's
ID offset. This is an existing placeholder provider, not lost code coverage.

Following the animation-sound repair at the inspected revision, the three
callers now use that compiled getter through its existing opaque view. The
selection and mouseover results retain explicit DrawableID conversions; the
save/load local retains its int type. No additional class identity or donor
fact is inferred. The provider and its other consumers are unchanged.

## Verification

- `./build.sh` passes all 39 code rows (7 selection, 32 across the other two
  units), with their string, float and import checks. No row, extent, pin,
  alias, source path or debt key changes.
- `find_declared_unmatched.py` passes on each source before and after edits.
- `link_check.py --prepare-current` byte-verifies the three explicit sources
  and writes strict reusable receipts without changing census/index/status.
- Against local index `112a456a2c`, dated 2026-11-05 15:52, original previews
  fail solely on the missing getter. Final combined preview reports all three
  units LINKS: selection 605 authored bytes, save/load 1,947, mouseover 1,913.
  The 4,465-byte total is preview scope, not a census headline increase.
- `link_check.py --fetch-index` retains that newer local index; the published
  index is dated 2026-11-05 05:17 at `c95fcfcfcd`.
- `eh_verify.py` reports four EH graphs EXACT (one selection and three across
  the other units), zero non-exact and zero missing objects.
- Read-only COFF inspection confirms each consumer references the rowed getter
  and no longer references Drawable::getID. The provider defines the rowed
  getter in section 385. Final object SHA-256 values:

  | Unit | SHA-256 |
  | --- | --- |
  | InGameUISelectDrawable.cpp | `d8904dd459659a09e108ec6ebad5d27cbc526a13bbf444bf3aa4195230e2fd27` |
  | InGameUIXfer.cpp | `19ee332990dd299759952ea2436a20a793c0ed6a46f07efe7127811ae5f60fdc` |
  | InGameUICreateMouseoverHint.cpp | `0ee7853fb321730f1f40d99387084be1a15937e1f2376ccfb452313f15dab02d` |
  | DispDwordFieldGetters.cpp | `ff5d55d3600580136d6cc75abf311ea7a30538fa2b8c98e8692640be7d9900ac` |

Next check: the next real link should stop listing these three missing-name
errors. Other consumers of the missing spelling remain separate work. Existing
header-queue debt remains registered. Full consumer selection, census and
runtime confirmation are not claimed.
