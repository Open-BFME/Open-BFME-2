# GarrisonContainModuleData header adoption

The initial-roster parser adopted the shared header in ec8d3eb66e. Its five rows matched and the header queue accepted the unit.

In GarrisonContain.cpp, replacing the local module-data declarations and filter with the registered declarations gives the constructor the correct fields at +0x40 and +0xA8. The scoped build failed one of 42 rows. At RVA 0x0078B513 the compiled unwind action jumps to the generated InitialRoster destructor. The original jumps straight to RVA 0x0048BA39. The existing blocked constructor record at 0x0047978F identified the same funclet.

In GarrisonContainModuleDataDtor.cpp, replacing both the local StringBase template and the novtable class with the registered header removes the template redefinition. The build then failed one of three rows. At offset 17 of the 56-byte destructor (RVA 0x00257507), the compiler inserted a six-byte store to the vtable pointer before the cleanup state update. Retail proceeds directly to the state update. Restoring the existing unit matched all three rows. Applying novtable to the shared class would also affect the constructor, where retail installs the derived table.

The deleting destructor at 0x0047981E is emitted by a tag constructor in ContainModuleDeletingDtors.cpp. The TU map assigns that row to GarrisonContain.cpp, which already defines the real constructor. Check the real constructor's emitted deleting destructor and the approved TU merge before extending the shared header with a compilation-only constructor.
