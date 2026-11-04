# Win32BIGFileSystem canonical file declarations, 2026-11-04

Inspected revision: `e472447e0bb7d0106f2440f108fe8289fda1283b`.
Scope: `Code/GameEngineDevice/Source/Win32Device/Common/Win32BIGFileSystem.cpp`.

## Repair and verification

Replaced the private File and RAMFile bodies with their registered headers.
The private File used padding around delete-on-close and nonabstract declarations;
RAMFile declared only its constructor and trailing virtual slots. Including File.h
from the archive-parser donor made StreamingArchiveFile abstract during composition.
The canonical RAMFile supplies the concrete overrides and the target's existing
0x20-byte layout. No function body, pin, alias or ledger identity changed.

- `./build.sh` for the destination: 33/33 matched; five renumbered funclet labels
  verified through parent EH data; seven literals and two empty-string references
  verified; one named import verified.
- `find_declared_unmatched.py` before and after: all defined functions matched.
- `header_adopt_lane.py accept --class File SOURCE`: PASS, one queue row retired.
- `header_adopt_lane.py accept --class RAMFile SOURCE`: PASS, one queue row retired.
- `link_check.py SOURCE`: LINKS, census-linked 2,011 -> 2,011 bytes against index
  2026-11-04 07:28 at a62ac1c10b. This is a preview, not a census gain.
- `check_csv.py`: OK (99,440 function rows, 9,336 symbols, 2,269 data rows).
- `git diff --check`: clean.

## Selection and provenance

The default picker claimed the archive-parser donor and 0x00603C52 for the real-link
error `?g_Va00E06E60@@3IA`. Its 9 rows byte-verified. Current
Rva007B6880Thunks.cpp defines that name as 40-byte storage. Checking both current
objects together makes the parser donor LINKS, 606 -> 606 bytes. The provider itself
still reports an unrelated census-index unresolved `?g_Va00DF2984@@3PAIA`; no
provider-wide clearance or new real-link result is claimed.

The supported consolidation planner was run under Code/GameEngine. Its packet
reported mixed/incomplete routing, private types, compiler settings and path-keyed
register prerequisites. These are investigation hints, not movement approval.
`tu_skeleton.py --plan` rebuilt current routing and listed 61 approved rows, five
donor files and nine mixed files. No source path changed in this repair.

## Remaining consolidation prerequisites

After adoption the parser donor no longer fails because StreamingArchiveFile is
abstract. It reaches the Win32BIGFileSystem view disagreement instead: the
seed lacks rva006045A2 and the donor's nested member-map field/type declarations.
The other pure donors still fail on BfmeCStringLess declaration ordering,
Rva00604465's destructor declaration, and duplicate _STL::less definitions.
Reconcile each view in a separately verified change before merging; mixed donors
require separate split/ownership work. No source-file reduction is claimed.

The post-repair dry-run result follows (exit 2, no files changed):

```text
tu: Code/GameEngineDevice/Source/Win32Device/Common/Win32BIGFileSystem.cpp
approved: 61
mixed: {'Code/GameEngine/Source/Common/DestroyInstances.cpp': 34, 'Code/GameEngine/Source/Common/FamilyDeletingDtors12.cpp': 5, 'Code/GameEngine/Source/Common/OpaqueScalarDeletingDtorsB18.cpp': 14, 'Code/GameEngine/Source/Common/RvaAdjustorDtorFamily.cpp': 4, 'Code/GameEngine/Source/Common/Thing/ThingTemplate.cpp': 13, 'Code/GameEngine/Source/GameLogic/Map/SidesListCtor.cpp': 32, 'Code/Libraries/Source/WWVegas/WWLib/StlportMapForwardersSeat8.cpp': 24, 'Code/Libraries/Source/WWVegas/WWLib/stlport_cstring_tree_lookup_00603C0F.cpp': 1, 'Code/Libraries/Source/WWVegas/WWLib/stlport_map_int_ptr_lower.cpp': 1}
refused: {}
accepted: []
rejected: {'Code/GameEngine/Source/GameClient/Win32BIGFileSystemRva006046B0.cpp': "compile: Code\\GameEngineDevice\\Source\\Win32Device\\Common\\.Win32BIGFileSystem.97241fa5d74481a5.tu_skeleton.cpp(974) : error C2039: 'rva006045A2' : is not a member of 'Win32BIGFileSystem' | Code\\GameEngineDevice\\Source\\Win32Device\\Common\\.Win32BIGFileSystem.97241fa5d74481a5.tu_skeleton.cpp(979) : error C2065: ", 'Code/GameEngine/Source/Common/System/Win32BIGFileSystemGetFileListInDirectory.cpp': "compile: Code\\GameEngineDevice\\Source\\Win32Device\\Common\\.Win32BIGFileSystem.74d5cfab0cf210d9.tu_skeleton.cpp(346) : error C2065: 'BfmeCStringLess' : undeclared identifier | Code\\GameEngineDevice\\Source\\Win32Device\\Common\\.Win32BIGFileSystem.74d5cfab0cf210d9.tu_skeleton.cpp(346) : error C2955: '_STL::set' : ", 'Code/GameEngine/Source/Common/Rva00604465Dtor.cpp': "compile: Code\\GameEngineDevice\\Source\\Win32Device\\Common\\.Win32BIGFileSystem.54b947627d7278a4.tu_skeleton.cpp(911) : error C2600: 'Rva00604465::~Rva00604465' : cannot define a compiler-generated special member function (must be declared in the class first)", 'Code/GameEngine/Source/Common/Win32BIGFileSystem.cpp': "compile: Code\\GameEngineDevice\\Source\\Win32Device\\Common\\.Win32BIGFileSystem.45c9160c114f80c1.tu_skeleton.cpp(505) : error C2953: '_STL::less' : template class has already been defined | Code\\GameEngineDevice\\Source\\Win32Device\\Common\\.Win32BIGFileSystem.45c9160c114f80c1.tu_skeleton.cpp(508) : error C2953: '"}
link_guard: census-linked: Code/GameEngine/Source/Common/Rva00604465Dtor.cpp, Code/GameEngine/Source/Common/System/Win32BIGFileSystemGetFileListInDirectory.cpp, Code/GameEngine/Source/Common/Win32BIGFileSystem.cpp, Code/GameEngine/Source/GameClient/Win32BIGFileSystemRva006046B0.cpp, Code/GameEngineDevice/Source/Win32Device/Common/Win32BIGFileSystem.cpp
blocked: no verified merge of two or more donors
reconcile_classes: ['ArchiveFileSystem', 'BfmeCStringLess', 'BfmeStringNoCaseLess', 'BigArchiveMemberInfo', 'Rva006038D4Less', 'Rva00604465', 'Win32BIGFileSystem']
reconcile: python3 tools/tu_views.py Code/GameEngineDevice/Source/Win32Device/Common/Win32BIGFileSystem.cpp --dry-run, then without --dry-run: the donors declare their own views of ArchiveFileSystem, BfmeCStringLess, BfmeStringNoCaseLess, BigArchiveMemberInfo, ... (docs/consolidation.md, "Workflow per TU", step 4)
```
