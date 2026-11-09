# Canonical RenderObjectUpdateModuleInfo in the runtime constructor

RenderObjectUpdateModuleConstructor.cpp owns native constructor 005624DE,
its ten-byte EH handler and eight-byte unwind funclet. It used a private
RenderObjectUpdateModuleInfo copy with twelve three-word range members and
a final rotation word. The registered header has the same positions, with
GameClientRandomVariable members m_var0..11 and m_mode.

The source now includes that canonical header, using its established
capitalized/reference Snapshot interface modes. Explicit twelve-byte copies
target the real members. The canonical value class declares its assignment
out of line, while native construction has twelve inline three-dword copies.
Field assignments and ordinary memcpy fail the native parent/unwind checks;
the standard MSVC memcpy intrinsic preserves the complete original object.
No assembly, new private class, shared-header edit, pin or alias is added.
Composition and the existing input ABI view remain; full inheritance recovery
is not claimed.

The native LEA getter targets land on these member-storage positions; this
does not prove their original result types or method names:

| Target RVA | Receiver offset | Canonical info member at +1C |
| --- | --- | --- |
| 003EE704 | +44 | m_var3 |
| 0030BBA5 | +68 | m_var6 |
| 00308156 | +8C | m_var9 |
| 003ABE71 | +98 | m_var10 |
| 003ABE78 | +A4 | m_var11 |

Fresh private baselines and the final candidate have identical retained
external code, data, relocations, flags, selection policies and bindings.
Normal build.sh verifies all three rows and no string/float/import obligations.
The compiler-local funclet label renumbers from $L374 to $L738; the existing
scoped parent-EH proof places it at 00799C50, with no new pin or row edit.
eh_verify reports one EXACT graph. Frozen checks pass and link_check's own
verdict remains LINKS 241B against index 717b70f4ab. The final proof records
strict-current normal objects separately.

header_adopt_lane.py accept --class RenderObjectUpdateModuleInfo retires
exactly this source's queue row. One registered private copy is removed;
two other queued users of the class remain. No function or source path moves.

The accompanying native map records sixteen words from the runtime table
ranges at 0081D728/0081D758 and four independently checked constructor
operands. The two strong one-byte owners and two final pure-table aliases
remain in DefaultModuleTemplateCopyCtors.cpp. No complete emitted table pair
currently replaces them. Primary slot1 needs a genuine empty override;
the transfer and name rows have different guessed prototypes, and repeated
getter words in primary slots9..11 do not prove overload identities or
allocation boundaries. The returned RenderObjectUpdateModule string does
not establish the runtime class's original C++ name. Full table recovery
must resolve these facts before transferring or enlarging either owner.

This pass is header-debt retirement and a precise handoff, not a real image
or boot-path result. Local trials, normal logs and verifier are under
build/render-info-constructor-adopt-20261109/.
