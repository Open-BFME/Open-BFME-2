# Use real Microsoft declarations in EAStringCConcat

Source: Code/Libraries/Source/EA/Apt/AptString/EAStringCConcat.cpp.

Replace reviewed local declarations with the real toolchain header. Review the exact local prototypes and current native audit; preserve compiler flags, existing configuration macros, all callee bindings, complete native/EH rows and runtime sections. The initial direct header trial changed the three native _strstr calls into DLL imports. Use the existing project CRT header configuration to retain statically linked calls, as already used by EAStringCase.cpp; verify complete sections and native rows.

Normal/frozen/EH and strict provider checks pass. All 16 existing native/EH rows, 13 retained external code bodies/relocations and all non-debug sections remain exact. The owning scoped Microsoft-header scan retires 1 queue record(s), preserving unrelated records. No shared header, native pin, alias, baseline, optimization or ABI switch changes. Declaration cleanup or queue maintenance is not new native coverage or runtime improvement.

Bounded dated preview:

Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Code/Libraries/Source/EA/Apt/AptString/EAStringCConcat.cpp: LINKS  LINKED 1,790 -> 1,790 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 1,790)
link_check: 1 of 1 link cleanly; LINKED 1,790 -> 1,790 bytes (8.5s)
