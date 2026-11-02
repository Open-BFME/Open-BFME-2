# Carryover vector: the constructor references do not satisfy class-fold proof

Base `3799c53a99b`, model GPT-6. Scope is the existing 286-byte insertion
at RVA `0x001EBEAB` in `WWLib/StlSweepW4Rva001EBEAB.cpp`, plus its existing
EH rows. Source and RVA claims were confirmed before this investigation.
The frozen-file check passes. No production source or ledger identity changed.

LINK-040's native call mapping remains the useful lead: the insertion calls
the real `CarryoverUnit` copy constructor at `0x001EB79E` and destructor at
`0x0037DEE4`, while its template dependencies use several placeholder types.
The source declares an opaque 172-byte struct with a nonvirtual destructor;
the real CarryoverUnit declaration has a virtual destructor. Renaming text
alone would not reconcile that ABI or the const/non-const helper twins.

Supported `rename.py class --fold Rva001EBEABElement --into CarryoverUnit
--dry-run` returns 2 before writing anything:

> Rva001EBEABElement installs no vftable retail shows as its own (through 0
> constructor, destructor or deleting destructor row(s))

The old constructor/destructor spellings are pins, not constructor/destructor
rows of that placeholder class. Thus the tool's own-vftable-store proof does
not cover this call-only template element. The existing pins are not enough
to authorize that class-fold operation. No extra alias row, pin, artificial
constructor, checker edit or unsupported cast was added to bypass the refusal.

Next work needs coherent element/declaration reconciliation and evidence for
the ABI and helper identities across LINK-040's whole family. Do not repeat
the same class-fold command while those inputs and the supported proof mode
remain unchanged. No new byte, link-preview or census gain is claimed.

`t=5 model=gpt-6 lane=R budget=30m`
