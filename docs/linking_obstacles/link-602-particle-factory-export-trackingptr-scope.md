### LINK-602: particle factory export uses the wrong TrackingPtr scope
Status: Repair landed / awaiting real-link verification. Updated: 2026-11-05.
Scope: `Rva003AD6DFCreate.cpp`, retail export ordinal 1530 at `0x003AD6DF`, charged alongside `ModuleTemplateFactorySlots.cpp` by the real-link blocker queue.
Completed: corrected the global-template signature; 60/60 bytes still match and the current object defines the exact export. Old-name scan found no consumer in 26,379 objects.
Evidence: [source, symbol audit and checks](../../reverse/attempt_support/link_602_particle_factory_export_scope.md).
Remaining / next check: confirm this export disappears from the next real-link errors; the other particle factory placeholder exports remain outside this repair. Census confirmation: not claimed.
