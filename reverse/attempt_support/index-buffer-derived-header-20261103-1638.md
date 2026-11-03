# Canonical DX8IndexBufferClass adoption, 20261103-1638

After the separate verified IndexBufferClass prerequisite, replace the private
DX8IndexBufferClass with its existing registered DX8IndexBufferClass.h. Its
IndexBufferClass base stays at0 and its buffer pointer stays at+20; complete
24-byte extent is bounded by the canonical header's native constructor and
sorting allocation evidence. Both raw call sites reinterpret only the returned
opaque IDirect3DIndexBuffer8 pointer as the existing BfmeIndexBuffer9 call-table
view. This preserves the witnessed D3D9 Lock/Unlock slots11/12; it does not
define a fake SDK D3D8 interface or replace the raw call table.

Normal native verification preserves the entire218B constructor and120B
destructor, their references and both EXACT EH graphs. The frozen gate passes.
The owning header PASS retires exactly one DX8IndexBufferClass queue key.
Complete COFF code comparison finds no changed existing body. Only the getter
name changes with its pointer-return type; both getter bodies still load+20.
The prior base adoption and local release helper remain. There is no new native
coverage, alias, pin, compiler option, shared-header edit or source-path move.
These are two progressive header prerequisites, not a completed TU merge or
a measured game/crash/memory improvement. The mutex declaration conflict and
remaining private DynamicIBAccessClass view still need reconciliation.

Final linking diagnostics exposed an unreferenced5B RefCountClass::Add_Ref
COMDAT (the majority copy is4B) emitted by the base adoption. Increment the
canonical public NumRefs directly at the existing inline call site, as its
proven header permits. The compiler emits exactly the same complete caller
bodies/relocations; complete COFF comparison removes only that unreferenced
copy and changes/adds no other external code. No pragma, flag, alias, pin,
method declaration or fake call suppresses it. This is part of the two header
adoptions, not a separately credited task or native coverage gain.
