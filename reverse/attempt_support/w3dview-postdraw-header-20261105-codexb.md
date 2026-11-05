# W3DView callback Drawable header adoption

Inspected revision: `c7cde06523`; owner: `yasinschroeder-codexb`.
Changed source: `Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DViewDrawablePostDraw.cpp`.

## Applied prerequisite

Replace the private Drawable prefix with the registered `GameClient/Drawable.h`.
The hidden predicate still calls the existing address-named 0x00270260 provider;
no method or class identity is inferred. Read the canonical public `m_object`
field directly, eliminating the TU-specific inline getter and its wrapper.
No shared header, function row, pin, alias or source path changes.

Include order matters: Player selects the lowercase Snapshot slot spelling,
and View must be parsed before Drawable can select the capitalized variant.
Putting Drawable first changes the View getFXPitch dispatch from +0x1B0 to
+0x1B8. The final order preserves +0x1B0, verified by the complete callback.
This is an existing conditional-header boundary, not a new retail class claim.

`header_adopt_lane.py accept --class Drawable` passes and removes exactly one
row from `reverse/header_queue.tsv`. Scoped searches find no data, identity,
hatch, gate-baseline or MS-header keys for this source. This is header debt
retirement only; the wider W3DView merge remains unverified.

## Checks

- Baseline and final `./build.sh` pass 2/2 rows (180B drawTerrainNormal and
  127B drawablePostDraw), two float literals, no skipped strings or imports.
- `find_declared_unmatched.py --fail` passes; `check_csv.py` passes.
- Strict reusable receipts accepted through `link_check.py --prepare-current`.
- Before/after COFF graphs retain exact bytes, relocation identities (including
  local section destinations), and COMDAT policy for both callbacks. The whole
  objects differ: two unused inline wrapper/getter definitions disappear;
  the canonical header adds its existing frame-rate initializer, CRT entry,
  four-byte storage and compiler array-constructor iterator. No weak aliases.
- The census index contains three identical hidden-wrapper copies, including
  two outside this unit. The removed unique getter has no retained reference
  or inbound edge in that index. This is index evidence, not an exhaustive
  current-object consumer proof.
- Census-only baseline and final ordinary link previews report LINKS,
  305 -> 305 census-credited bytes, against 2026-11-05 05:17 at `c95fcfcfcd`.
  These previews do not update LINKED, real-link or ownership headlines.
- The outgoing-style consumer audit uses the older index and is inconclusive:
  Common/AIBaseBuilder.cpp now has a strict receipt after its ordinary build
  passes 27/27 rows, one data row and seven literals. The next missing receipt
  is Common/AIBuildable.cpp. Consumer-wide closure still needs current receipts
  and the next scheduled census; no clean consumer-wide or real-link result
  is claimed.

## Selected TU-approval boundary

The supported consolidation planner surveyed the GameClient subtree, completed
without missing inputs, and retained its snapshot under build/consolidation.
The current-input map rebuilt in memory still has 50 proposed W3DView rows
across 39 files: 16 K-only and 34 C rows whose brackets are unapproved.
For example, 0x00085947 remains K=Rva00085947; the already real-named static
callbacks at 0x000859F5, 0x00085A03 and 0x00085AB7 depend on that bracket.
The reset-family body and neighbour vtable membership do not independently
prove the placeholder class/member name. No name, TU assignment or map
approval is fabricated. No generated map is committed and no merge attempted.

Next: establish independent F/Z/S evidence for the placeholder brackets, and
reconcile the remaining canonical-header/private-view compiler rejects before
another supported merge trial. The existing seed include environment and
COMDAT-selection boundaries remain as recorded in the previous handoffs.
