# Refresh completed Microsoft-header key for PlayerInitFromDict

Source: Code/GameEngine/Source/Common/RTS/PlayerInitFromDict.cpp.

Source is already clean; refresh its stale queue key through the native scoped audit. Review the exact local prototypes and current native audit; preserve compiler flags, existing configuration macros, all callee bindings, complete native/EH rows and runtime sections.

Normal/frozen/EH and strict provider checks pass. All 31 existing native/EH rows, 46 retained external code bodies/relocations and all non-debug sections remain exact. The owning scoped Microsoft-header scan retires 1 queue record(s), preserving unrelated records. No shared header, native pin, alias, baseline, optimization or ABI switch changes. Declaration cleanup or queue maintenance is not new native coverage or runtime improvement.

Bounded dated preview:

Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Code/GameEngine/Source/Common/RTS/PlayerInitFromDict.cpp: LINKS  LINKED 4,707 -> 4,707 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 4,707)
link_check: 1 of 1 link cleanly; LINKED 4,707 -> 4,707 bytes (2.8s)
