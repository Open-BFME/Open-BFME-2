# Thing.cpp consolidation: compiler and declaration prerequisites

Reviewed at 136ee37e6f6e0742135060bab7d9d2d8a5f9d331, VC7.1 build 3077.
Served item: `tu-merge:Code/GameEngine/Source/Common/Thing/Thing.cpp`.
No source, header, row, compiler override or protected register was changed.

The ordinary build verifies all 31 rows across the 14 claimed source files.
`tu_skeleton.py --merge Code/GameEngine/Source/Common/Thing/Thing.cpp --dry-run`
accepts no donor, so this item has not passed. A private native-Verifier matrix
confirms the reason without changing normal build caches:

| Standalone compile profile | Matching rows |
| --- | ---: |
| Each file's current native profile | 31/31 |
| Seed's carried empty managed override (base /O2) | 16/31 |
| Region /O1 /Ob1 /G7 /arch:SSE | 28/31 |

These are standalone context controls, not a verified composed TU or link result.
All six constructor rows pass under the region profile; two overloads share
0x000D43D0, explaining a misleading count of five unique RVAs.

The region profile changes exactly three seed rows: `_Base_bitset<4>::_S_maskbit`
at 0x00030C40 uses XOR/INC instead of retail MOV EAX,1 (13 versus 15 bytes);
`Matrix3D::Set_Y_Translation` at 0x00665600 uses MOVSS instead of retail EAX
copying; its existing alias at 0x00318B09 fails identically. Simply changing
the override loses verified bodies. Reconcile these actual provider expressions
and their canonical header consumers first, then use the native flag-defaults
tool only if all seed rows pass. Do not move helpers to an unapproved TU.

Independent declaration blockers remain: ThingIsAnyKindOf's target-backed
seven-DWORD `BitFlags<int N>` view (including ABI spellings 69 and 116) conflicts
with the seed's Zero Hour `BitFlags<unsigned N>` and KINDOFMASK_NONE definition.
A matching name does not establish matching storage. The native plan also asks
for canonical Rva0030A3E4 reconciliation. Preserve the existing class checks.

Before retrying, refresh the native link index: the inspected census predates
the source changes. Current linked bytes are unknown. `--merge` remains the
sole merge writer; preserve every row and pass ordinary build, declared-function
and provider/link checks. No aliases, optimization pragmas, baseline growth or
handwritten row moves are justified by this evidence.

Private reproducible matrix and disassembly are retained under
`W:/OpenBFME/diagnostics/continue-20261120-body-recovery-1656/agents/thing/`:
all_profiles.py, all-profiles.json, inspect_context.py, context.json and the
handoff. Failed experiments count as zero completed served tasks.
