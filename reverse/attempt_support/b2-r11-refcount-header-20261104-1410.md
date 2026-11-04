# Adopt canonical RefCountClass in W3DBridgeBufferDrawBridges

Adopt existing `Code/Libraries/Source/WWVegas/WWLib/RefCountData.h` in one provider/consumer unit. The native
CodeView before view is class/8B, no bases, vptr and int NumRefs at+4;
Delete_This is slot0. The after view retains that projection and uses the
header's target-evidenced protected destructor slot1. The canonical header
cites ctor72882, dtor72892, bounded BC650C table and Release_Ref5D1A7D.
This is not a claim that an old one-slot private projection was a full class.
Preserve the existing empty destructor as an out-of-class inline definition
where present (False); retain its original optimization context.
No shared header, alias, pin, compiler setting or function ledger changes.

Normal native/frozen/header acceptance pass for 7 existing rows.
All 29 external definitions and relocations, named local code
and every non-debug section are identical. Resolved dependency receipts differ
only by adding the canonical header. This removes one divergent class body;
no authored-byte, full-image, gameplay, RAM/leak/crash or performance gain.
Private before/after objects, layouts, dependency hashes and native logs are
preserved under build/up-to-twenty-each-20261104-1410/b2-r11-*. The full-image result remains
separate from this source-local proof.

Coupled adoption: existing `Code/Libraries/Source/WWVegas/WW3D2/RenderingMethod.h` replaces the complete
FXShader namespace-local interface. Its ten-slot header documents retail
Begin/Begin_Pass/End_Pass/End and the inherited deleting slot. The former
dummy slot1 is replaced by that inherited slot, preserving actual dispatch
offsets2/3/4/5/6. Native layout and complete source checks confirm this.
