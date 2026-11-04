# Adopt canonical RefCountClass in sharebuf_shader_copy_ctor

Adopt existing `Code/Libraries/Source/WWVegas/WWLib/RefCountData.h` in one provider/consumer unit. The native
CodeView before view is class/8B, no bases, vptr and int NumRefs at+4;
Delete_This is slot0. The after view retains that projection and uses the
header's target-evidenced protected destructor slot1. The canonical header
cites ctor72882, dtor72892, bounded BC650C table and Release_Ref5D1A7D.
This is not a claim that an old one-slot private projection was a full class.
Preserve the existing empty destructor as an out-of-class inline definition
where present (True); retain its original optimization context.
No shared header, alias, pin, compiler setting or function ledger changes.

Normal native/frozen/header acceptance pass for 4 existing rows.
All 9 external definitions and relocations, named local code
and every non-debug section graph are equivalent. Section order may change;
the comparison proves a bijection preserving raw section bytes, symbol anchors,
COMDAT selection/association, relocation edges, and SafeSEH symbol identities.
Resolved dependency receipts differ only by adding the adopted header(s).
This removes one divergent class body;
no authored-byte, full-image, gameplay, RAM/leak/crash or performance gain.
Private before/after objects, layouts, dependency hashes and native logs are
preserved under build/up-to-twenty-each-20261104-1410/b2-r08-*. The full-image result remains
separate from this source-local proof.
