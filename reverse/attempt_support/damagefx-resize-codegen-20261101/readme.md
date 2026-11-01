# DamageFX insertion resize prerequisite, 2026-11-01

Control `df3dabb76b`, index `0d24c60eef`. No Code or code-ledger change is kept.
This is a blocked linking attempt, not new coverage or a repaired provider.

The current insertion at `0x003609F7` matches all 73 bytes, including its calls
to resize `0x0053F1EC` and node creation `0x00360939`. The published current
preview still fails only on its own non-retail resize and its selection.
The recent 0x780-byte mapped-payload correction remains intact.

The private candidate restores the normal STLport destructor definitions,
marks the existing pointer-vector swap declaration non-throwing, and uses the
malloc configuration. This removes the artificial allocator-destruction EH
scaffolding: resize falls from 220 to 191 bytes, with no EH prologue. The 73-byte
insertion remains exact. Native resize is 184 bytes, so the candidate is NOT
an acceptable Code reconstruction. This handoff retains its measurements and
disassembly; the private source stays under untracked build scratch.

The remaining loop difference is concrete: native computes a destination bucket
address once with LEA and reuses it across the node-next store. The candidate
uses a shift and reloads the destination vector pointer, adding seven bytes;
ESI and EDI also exchange roles. See the side-by-side disassembly. Relocations
at shifted offsets in that nonmatching helper are not validated placements.

The following additional private trials do not remove that seven-byte gap:
reference-taking hash, enum key with either a reference hash or the pristine
donor's by-value unsigned-hash delegation, word-array payload, a declared
mapped-value constructor, G6, GX, STLport 4.6 with allocator adaptation,
visible count-vector constructor, both count constructors visible, and restored
count constructors/swap bodies together. The enum/private-hash variants also
change relocation names and are NOT claimed as exact insertion bindings.
Malloc alone leaves the original helper at 220 bytes.

Read-only comparison with the existing Armor provider confirms the same vendor
vector/hashtable/hash implementations and bfmealloc allocator header. The
constructor-visibility and simple hash/payload hypotheses above were tested
and refuted; do not retry them unchanged. The original key, mapped type and
shared helper identity still need coherent recovery. Existing real-named
providers are evidence to investigate, not permission to add another alias.

Reproduce from the control source by removing the declaration-only allocator,
allocator-proxy, vector-base and vector destructors, adding
`__declspec(nothrow)` to the vector swap declaration, and appending
`/D_STLP_USE_MALLOC` to the source's existing options. The four removed
declarations refer to `allocator<void *>`,
`_STLP_alloc_proxy<void **, void *, allocator<void *> >`,
`_Vector_base<void *, allocator<void *> >` and `vector<void *, allocator<void *> >`.
All experiments used compiler_command with private output objects under build;
none wrote the shared match cache. The tracked source was never changed.
No new pin, alias, row, optimization pragma, helper definition or TU assignment
was added. Remaining work is native codegen/identity recovery and whole-cohort
selection verification before publication can claim a repair.
