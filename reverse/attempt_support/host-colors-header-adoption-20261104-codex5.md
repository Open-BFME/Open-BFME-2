# HostValidateColors canonical headers, 2026-11-04

Inspected revision: `28e11dc681`.
Source: `Code/GameEngine/Source/GameClient/GUI/HostValidateColorsRva004422DDFarm.cpp`.

The header picker selected ImageSubscriptMap's private twelve-byte map member.
The same source also had an AptMpGameSetup queue entry. Both private class
definitions now use their existing canonical headers; neither header changes.

ImageSubscriptMap's existing subscript implementation remains inline and
noinline, preserving the caller's compiler knowledge. It accesses the canonical
twelve-byte storage through the same ImageNameMap operations. The canonical
header records the target constructor/lifetime evidence for that storage and
the subscript's unsigned-key lookup and node accesses; this change establishes
no additional target type or member name.

AptMpGameSetup now uses canonical fields +0x58, +0x5C, +0x3C4 and +0x3DC.
Its canonical header records the target bit-vector construction at +0x3C4;
this TU accesses that opaque storage through its established STL bit-vector
view. The existing owner-slot view remains local to this TU. No new global,
alias, pin, source path or ledger row is introduced.

Verification on the final source:

- `./build.sh` for the source: 4/4 matched rows; compiler-renumbered funclet
  label resolved through its parent's EH data. String, float and import checks
  pass with no references requiring verification.
- `find_declared_unmatched.py`: all defined functions already matched, before
  and after the changes.
- `header_adopt_lane.py accept --class ImageSubscriptMap` and
  `--class AptMpGameSetup`: both PASS on the final source. The owning tool
  retires the two corresponding rows from `reverse/header_queue.tsv`.
- `link_check.py` for the source: LINKS, 589 -> 589 authored bytes against
  the census dated 2026-11-04 16:16 at `2f0cb97f52`.
- `git diff --check`: clean.

No census gain or runtime validation is claimed. The default pick's unrelated
BridgeBehavior standalone-free-head blocker was checked first: its already
landed repair predicts LINKS (4,673 -> 4,673 bytes), matching the existing
obstacle evidence. That source was not changed and its claims were released.
