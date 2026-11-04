# AptWindowLayout consolidation trial (2026-11-04)

Allocated destination: `Code/GameEngine/Source/GameClient/GUI/AptWindowLayout.cpp`; `consolidation_queue.py --check-tu` passed. The fresh GUI-scoped planner and its `--check` passed. The plan had 12 approved rows, two pull donors and one mixed file.

The fresh merge dry run accepted no donors. `AptWindowLayoutConstructor.cpp` failed because `BfmeQuickMatchScreenBase::rva00538ADC` is absent from its view; the tool recommends reconciling `AptWindowLayout` and `BfmeQuickMatchScreenBase`. The mixed `AsciiStringFoldDeleters.cpp` inspection found no approved row for this TU, so `--split ... --for AptWindowLayout.cpp --dry-run` refused it. No changes or claims were made. Retry only after the declaration prerequisite changes; no source reduction or identity/link progress is claimed.
