# Colour-module Snapshot name recovery

The served Rva005EA590 copy constructor stores primary table 0081D17C and
Snapshot table 0081D194. Native Snapshot slot 2 is the six-byte getter at
003AC9A1 returning the exact literal `DefaultParticleModule<CAT_COLOR>` at
0081C96C. The new GetSnapshotName override recovers that slot without changing
the constructor or introducing a private Snapshot copy.

Both Rva005E95C0 views now give the existing pure name slot its measured return
type and constness. Its own getter at 003ADDC7 is claimed by another contributor
and remains unrecovered here. The derived override occupies the existing
Snapshot slot directly; scratch COFF inspection shows no adjusting thunk and
no change to either primary or +8 interface table.

Private verification passes 3/3 rows in each producer. Normal build.sh over
both files passes 6/6 rows, including the exact name string. This is one
recovered virtual body, not a completed bridge cohort or a fresh real-link
result. Remaining destructor, transfer and primary slots still need recovery.

The native rate helper at 0055B9BD is also recovered as calculateRates (128 bytes). Typed RGB keyframes and current/rate colours retain every constructor byte; the helper's complete body and floating references match retail. Paired normal verification passes 7/7 rows.

Primary slot 1 update at 0055BA3D is recovered too (287 bytes): advance RGB weights; test the clock and next key; calculate rates; clamp each component. The same-TU helper preserves retail's xmm1 lifetime across the call. Normal paired verification passes 8/8 rows, with all three floating references exact.

The base keyframe transfer at 0055B96D is recovered as Rva005E95C0::xfer (80 bytes). It uses canonical Xfer to skip light CRC, transfer Version1, eight RGB/frame pairs and the trailing float. Both view declarations are synchronized; paired normal verification passes 9/9 rows.

The derived transfer at 0055BB5C is recovered (82 bytes), together with its compiler-emitted minus-Ch Snapshot adjustment thunk at 003AC9A7 (8 bytes; parent xfer). The measured parent primary table 0081D164 has pure slots 1-3, now declared so the derived transfer occupies both native tables. All 11/11 rows pass normal paired verification.

Primary slot 4 testColor at 0055BBAE now uses the actual keyframe and RGB members (139 bytes). Blend modes 1/2/6 compare the component sum with 0.03; mode 5 compares the product with 0.97. Complete bytes and floating references match; normal paired verification passes 12/12 rows.

Primary slot 5 getColor at 003AC99A is recovered (7 bytes), returning the typed current RGB member at +94h. The primary table now has all six measured slots, with slots 1-5 backed by exact bodies or the native purecall; its deleting-destructor owner still needs repair. Normal paired verification passes 13/13 rows.

## Final partial-cohort audit

Eight banked bodies total 737 bytes, in seven substantive commits (the
compiler-generated 8-byte adjustment thunk rides with its 82-byte parent).
Normal paired verification passes 13/13 rows, one string and five floating
references. The source's own rows grow from 109 to 846 bytes.

Current-object relocation audit confirms primary 0081D17C is now 24 bytes and
slots 1-5 resolve to the native targets. Snapshot 0081D194 remains 16 bytes
and slots 1-3 resolve correctly. The base info table 0081D1A4 retains 16 bytes;
its transfer slot now resolves correctly too. This diagnostic is not a data
ledger admission or a whole-image bridge clearance.

The remaining primary and secondary deleting-destructor slots need a real
Snapshot lifetime in the info base. Its legacy slot04 empty callback is
already rowed under that spelling. Canonical Snapshot adoption must reconcile
that callback with loadPostProcess through the normal rename/tombstone path;
reverse/deleted_rows.csv is currently held by another contributor. The shared
empty body 000B3FD0 and base info getter 003ADDC7 are also held. No alias,
private Snapshot copy or fabricated subclass is introduced to get around these
dependencies. Remaining destructor recovery and both served table repairs stay
open, with the exact native targets preserved in the queue.

Scoped link_check predicts LINKS for both files: 109 -> 846 and 73 -> 73
bytes. Its index is stale (8b06c04cd2, 2026-11-17 18:16), so this is a preview,
not an updated headline or a real-image result. No real link or game run is
claimed. Release all body and scope claims after publication.

## 2026-11-21 follow-up (Copilot, claude-opus-5.5)

Retail 0x003AE270 (`??_G`, 28 bytes) calls the out-of-line destructor 0x003ADFB2,
which restores only the base tables (00BBB554 at +0x0C, 00C1C780 at +8, 00C1B320
at +0). An implicit destructor of the colour module class compiles to exactly
that in the EH unit Rva0055BCF1ColorModuleCtor.cpp (its ICF-alias rows prove it).
In Rva005EA590CopyCtor.cpp (`/EHs-c-`, which the 108-byte copy ctor 0x003ADD31
needs), the same implicit destructor is inlined into `??_G` (47 bytes). An
explicit out-of-line destructor stores the class's own three tables before the
base ones, so neither form reproduces 0x003ADFB2/0x003AE270 from this unit.
Tried, built: base Snapshot lifetime in `Rva005E95C0` (slot 0 a destructor
ending in `Snapshot::~Snapshot`), inline `~Rva0055BCD2` as in the colour unit;
10/10 rows stayed matched, but `??_G` was 47 bytes (implicit) or the dtor
32 bytes with own-table stores (explicit). Reverted.

The two placeholders are one retail class (same tables 0081D17C/0081D194/
0081C780; `GetSnapshotName` literal DefaultParticleModule<CAT_COLOR>). The fix
is the fold, so the copy unit's tables name `??_GRva0055BCF1`, which the colour
unit already rows. `rename.py class --fold` refuses both directions:
"Rva0055BCF1's rows install different own vftables (0x00C1B320 by
??1Rva0055BCF1@@UAE@XZ at 0x003ADFB2; 0x00C1D17C by ??0Rva0055BCF1 at
0x0055BCF1)". The destructor's +0 store is the base's table after the derived
store was elided, not a second class. That is a false reject, recorded as such.
A tooling seat should let the fold ignore a destructor's base-table restores.
The slot04 to loadPostProcess rename is still needed for a Snapshot-derived base.
