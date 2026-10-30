# PartitionManager disguise provider selection

Target facts: the existing isDisguised owner in StealthUpdate.cpp is the
complete nine-byte retail body at 0x0004D65B, reading +0x3C. PartitionManager
instead emitted an eleven-byte +0x38 copy, first in link order. Its only raw
incoming relocation is in .debug$F. WeaponSet's later copy also differs, but
the native StealthUpdate provider precedes it. No recovered name, new native
body or donor-layout claim is needed for this emission repair.

Select the existing owned stealth-level link header before the transitive
include. A Partition-only dllimport/forceinline annotation retains the inline
body while suppressing its unwanted outlined copy. The shared header's default
behavior is unchanged. There is no getStealthLevel definition or reference in
the control object; switching that member to the existing declaration-only
view causes no additional provider removal.

Fresh private control/trial and final normal builds retain all four Partition
rows and the native owner's two rows. All 564 retained external code bodies
and relocations are identical. All other loadable definitions, non-debug
section contents/relocations (as a multiset) and undefined names are unchanged;
COFF section ordering changes. SafeSEH indices are resolved to handler names.
No new import, vtable, thunk, pin, alias or source move.

The ordinary four-source preview removes this selected-provider blocker from
PartitionManager, StealthUpdate and WeaponSet. Every other blocker is identical;
StealthUpdateLogic retains LINKS/5,722 authored bytes against ccafe54d1d.
Partition, StealthUpdate and WeaponSet remain blocked on the recorded unrelated
names, tables and updateCellsTouched/clear providers. No full-unit LINK or
census gain is claimed. The shared-header hook also checks its conservatively
computed dependent scope before the commit can land.

This supersedes LINK-088's failed layout/include-only hypothesis. It preserves
the old inline field interpretation rather than claiming to fix every inlined
unrowed function in this donor unit. Full class recovery and scheduled census
confirmation remain separate. proof.json records native bytes, the removed
copy's debug references, retained-object invariants and bounded blocker deltas.
