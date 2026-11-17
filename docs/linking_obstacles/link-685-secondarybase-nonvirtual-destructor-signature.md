### LINK-685: SecondaryBase nonvirtual destructor signature blocks six-slot table recovery
Status: Blocked. Updated: 2026-11-17; inspected revision: 13afb2e8202fbcd6ebcf632631b0689b7694501a.
Evidence / affected units: Rva005C48E5Dtor.cpp, Rva005C4986Ctor.cpp, SecondaryBase.cpp and Rva004FB130Dtor.cpp; [native table and lifetime evidence](../../reverse/attempt_support/secondarybase-nonvirtual-destructor-20261117-root20.md), [structured facts](../../reverse/attempt_support/secondarybase-nonvirtual-destructor-20261117-root20.json).
Completed: baseline 7/7 rows; base table 0x00840818 proved six pure slots, and derived secondary 0x00874764 has six ordinary methods. Native teardown and EH directly call 0x004FAC80 at secondary +0x0C. Coherent nonvirtual destructor respell dry-run refused special-member naming; all production files unchanged.
Remaining / next check: owning-tool support to remove the erroneous virtual destructor signature across provider/consumers, then recover six secondary and eleven primary slots without duplicate listener storage.
Clearance: pending; no source repair or bridge retirement.
Census confirmation: pending published real-link result.
