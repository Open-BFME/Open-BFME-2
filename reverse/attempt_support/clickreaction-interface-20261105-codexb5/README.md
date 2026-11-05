# ClickReactionBehavior interface reconciliation, 2026-11-05

Base: `85b46a09f3`. Claimed scope: the main TU, constructor donor and
ClickReactionBehaviorView.h. This is the declaration prerequisite to LINK-238;
no source path moves or debt retirement in this commit.

Target facts: constructor RVA 0x0045961D installs the secondary interface at
complete-object +0x20. Its retail table at VA 0x00C41188 has the entries
0x008543E3, 0x008596F9 and 0x00859864. The intermediate table at VA 0x00BE2B78
has three __purecall entries. The matched reaction body at RVA 0x004596F9
receives the secondary-interface pointer (loads object at this-0x18 and module
data at this-0x1C). The three old unresolved declarations were not additional
retail bodies: the leaf slot0 added a primary-table method, and the interface
reaction declaration required an unimplemented base definition.

Use the constructor donor's existing `slot` spelling/binding, remove the extra
leaf slot0, and declare the base reaction operation pure virtual, overridden
by the existing rowed leaf implementation. Include this same declaration from
the constructor donor. The interface remains partial: this does not recover
its full table, original names, third operation or the leaf update override.
No new alias/pin is introduced; all three existing link-wide aliases remain.
The BFME 1 donor's one-slot constructor view supplied the existing slot spelling,
not proof of BFME 2's complete interface.

Checks:

- Scoped builder: 11/11 function rows exact across the two units, including the
  initializer and both parent EH handlers/funclets. All three edited files pass
  find_declared_unmatched.py.
- eh_verify.py: EXACT 2/2 parent EH graphs.
- link_check.py: both units LINKS, preserving 616 + 112 census-linked bytes
  (index census 2026-11-05 05:17, c95fcfcfcd). This is a preview, not a census.
- [Object symbol delta](symbol-delta.json): no definitions removed or added;
  main-unit external references unchanged; constructor adds only the existing
  rowed reaction implementation. All alias mappings unchanged.
- data_check.py: identical three pre-existing shadow findings before/after,
  two for DRAWABLE_FRAMES_PER_FLASH and one compiler guard spelling. Original
  sources were restored and byte-verified for this comparison, then the
  reconciled sources restored and byte-verified again. No debt removed.
- No matching header/ms-header queue, identity-baseline or data-baseline keys
  for these units. Shared header has only the main TU as an existing consumer;
  constructor becomes the second consumer.
- Supported merge dry run accepts both units, 11 rows, no rejected donor,
  preserving both census-linked units through the merge link guard. Two mixed
  sources stay outside this merge. Next: apply the supported merge, rerun
  scoped checks and audit path consumers. No source-file gain claimed yet.
