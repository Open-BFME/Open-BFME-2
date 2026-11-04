# dx8fvf exception-mode reconciliation, 2026-11-04

Follow-up to `68cfd1b356` and
[the shared-view handoff](dx8fvf-shared-view-20261104-codexb5.md).

A scratch composition through `tu_skeleton.Verifier` isolated the declaration
builder at `0x001818C0` as the sole lost row: 1,681 compiled bytes versus
retail's 1,705, with memory-form flag tests replacing retail's load-and-test
forms. The other eleven code rows matched. Removing the seed's `/EHsc` token
from that same composition restored **12/12** code rows. Resetting WWLib's
inline depth to eight instead retained the failure. These are compiler trial
results, not evidence for the descriptor's original name.

Use `/EHs` in the seed, agreeing with the builder's existing exception mode.
Also carry the builder's `/Ob2 /Op`, `_STLP_NO_EXCEPTIONS`, `_STLP_USE_MALLOC`
and `_CRTIMP=` settings in the seed. Changing only exception mode still gives
no accepted donors: the merge tool tests donor flag sets individually, and neither
original set describes the passing combined configuration. The seed retains
its `BFME_WWSTRING_NATIVE_CSTR_ASSIGN` setting for its existing StringClass use.
`./build.sh dx8fvf.cpp` retains **6/6 code rows**, its one data row and fourteen
string literals. `find_declared_unmatched.py` passes with the existing admitted
old-layout constructor unchanged. The current-object `link_check.py` preview
retains **877 -> 877 bytes**, using the 2026-11-04 11:27 census at `3a8028f34e`.
No body, ledger identity, alias, pin or debt register changes in this repair.

With that common configuration, the full `tu_skeleton.py --merge ... --dry-run`
accepts the seed and `BfmeFVFDescriptorVertexDeclaration.cpp`: **12 code rows**
match, and the census link guard passes. The merge is still unapplied here;
the compiler configuration is a separately verified prerequisite. The AngleFXInfo
flag override, StructureTopple include/type conflicts and allocate-proxy binding
conflict in `Rva00181500Finish.cpp` remain rejected, so their sources stay intact.
