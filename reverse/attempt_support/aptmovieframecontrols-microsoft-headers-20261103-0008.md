# Use real Microsoft declarations in AptMovieFrameControls

Source: Code/Libraries/Source/Apt/AptMovieFrameControls.cpp.

Replace reviewed local declarations with the real toolchain header. Review the exact local prototypes and current native audit; preserve compiler flags, existing configuration macros, all callee bindings, complete native/EH rows and runtime sections. The direct header trial changed the existing _strstr binding into a DLL import. The established project CRT header configuration retains direct linked CRT calls; verify all native/EH rows and non-debug sections.

Normal/frozen/EH and strict provider checks pass. All 20 existing native/EH rows, 15 retained external code bodies/relocations and all non-debug sections remain exact. The owning scoped Microsoft-header scan retires 1 queue record(s), preserving unrelated records. No shared header, native pin, alias, baseline, optimization or ABI switch changes. Declaration cleanup or queue maintenance is not new native coverage or runtime improvement.

Bounded dated preview:

Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Code/Libraries/Source/Apt/AptMovieFrameControls.cpp: LINKS  LINKED 3,546 -> 3,546 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 3,546)
link_check: 1 of 1 link cleanly; LINKED 3,546 -> 3,546 bytes (2.7s)
