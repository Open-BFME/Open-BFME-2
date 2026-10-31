# OrCondition compatible native destructor and one-slot table

Target facts: the existing constructor at0x003B238A installs table0x0081F3F4; its one scalar-delete entry is28B at0x003B331E, calling the68B destructor at0x003B262E. The allocation in the existing duplicate body is12B. These facts do not prove the original class name. The existing OrCondition interface is retained without a canonical-name claim.

Stage1 adds a complete C++ implementation of the existing protected OrCondition destructor in OrConditionCtor.cpp, preserving the17B constructor. Its68B body and independently emitted28B scalar delete match retail. Official add_match --icf-owner admits the destructor against the retained Rva003B262E owner and the scalar delete in Scripts.cpp against the retained Rva scalar-delete owner. No pin or alias is added. The old public-destructor alternatename is removed and hatch_counters --update retires exactly one hatch.

Remaining before link closure: change only OrCondition in the TU-scoped Scripts.h view to the observed12B/single-slot ABI; bind the old68B destructor to the existing OrCondition table; retire the superseded28B Rva scalar-delete row after its native replacement is live. The current in-memory TU map approves Scripts.cpp for0x003B331E and0x003B262E; no generated map is committed. No source file is moved in this package.

Private proof retains all11 original Scripts code rows, one EH graph and23 external code definitions byte-and-symbolic-relocation identically. It removes only five unsupported pool/base helpers. Independent initialized-data/provider review follows. Final normal checks and cohort preview are recorded when complete.

The preceding ArmySummary push audit was INCONCLUSIVE against indexd249ce458a/outgoing baseeca62de411:14 affected source objects lacked current receipts, first Common/AwardSystemManager.cpp. Carry that consumer scope into the next census; no global census increase or complete audit clearance is claimed here.
