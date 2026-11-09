### Statistics records and traversal need canonical ModuleInfo

Status: both consumer adoptions verified; wider class recovery open.
Updated: 2026-11-09; inspected revision: cf14f42c4a.

INIStatsRecord.cpp and Rva0050CBA2StatsDump.cpp adopt the unchanged canonical
header and remove their unused opaque Nugget stand-ins. All29 rows, four EH
graphs, thirteen string references, two floats and six imports pass. Current
previews against index5b5011469d retain1678/1678 linked bytes. All32 retained
COMDAT bodies/policies stay unchanged; the one additional canonical count copy
matches all six indexed copies. Owning acceptance retires two header rows;
20 ModuleInfo units remain locally, with no header key in either source.

[Scope, native verification and provider-copy evidence](../../reverse/attempt_support/moduleinfo-stats-header-adoption-20261109.md).
Other class lifetimes and map identities remain open. A future supported TU
merge must separately check the diagnostic fragments' remaining private/CRT
declarations. The preceding AIBuildable.cpp receipt gap is carried forward;
census/image confirmation is pending, with no new runtime result claimed.
