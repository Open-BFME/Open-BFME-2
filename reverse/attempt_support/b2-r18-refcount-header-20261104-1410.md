# Adopt canonical RefCountClass in FlatHeightMap

Adopt existing `Code/Libraries/Source/WWVegas/WWLib/RefCountData.h` in one provider/consumer unit. The native
CodeView before view is class/8B, no bases, vptr and int NumRefs at+4;
Delete_This is slot0. The after view retains that projection and uses the
header's target-evidenced protected destructor slot1. The canonical header
cites ctor72882, dtor72892, bounded BC650C table and Release_Ref5D1A7D.
This is not a claim that an old one-slot private projection was a full class.
Preserve the existing empty destructor as an out-of-class inline definition
where present (False); retain its original optimization context.
No shared header, alias, pin, compiler setting or function ledger changes.

Normal native/frozen/header acceptance pass for 40 existing rows.
All 51 external definitions and relocations, named local code
and every non-debug section are identical. Resolved dependency receipts differ
only by adding the canonical header. This removes one divergent class body;
no authored-byte, full-image, gameplay, RAM/leak/crash or performance gain.
Private before/after objects, layouts, dependency hashes and native logs are
preserved under build/up-to-twenty-each-20261104-1410/b2-r18-*. The full-image result remains
separate from this source-local proof.

Coupled adoption: existing `Code/Libraries/Source/WWVegas/WW3D2/RenderingMethod.h` replaces the complete
FXShader namespace-local interface. Its ten-slot header documents retail
Begin/Begin_Pass/End_Pass/End and the inherited deleting slot. The former
dummy slot1 is replaced by that inherited slot, preserving actual dispatch
offsets2/3/4/5/6. Native layout and complete source checks confirm this.


Publication rebase validation against upstream parent `f96ed021fe404f33aa447573bfb758d38b420c26`:
The upstream RenderInfoClass header adoption, removal of its obsolete stack
alias/private Vector3 and Ambient/Diffuse Set calls are preserved exactly.
Only the two private base/rendering views are replaced. Native before/after
checks pass for40 current rows; all51 emitted external
code definitions, local code, runtime section graph/COMDAT/weak bindings and
SafeSEH identities remain equal at the same upstream inputs. Separate fresh
objects and source snapshots use build/up-to-twenty-each-20261104-1410/b2-r18-rebase-*.
This incoming RenderInfo/Vector3 cleanup is not credited to this batch.
