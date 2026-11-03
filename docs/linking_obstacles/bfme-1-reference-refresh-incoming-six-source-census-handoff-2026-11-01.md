### BFME 1 reference refresh: incoming six-source census handoff (2026-11-01, Cortys)

Reference `131fb8ff0a515c504313ac10ec87c929d71cf214` landed in
`42ba5fba3d67de6fd90e938e491169eea70fd6d2`. The normal full gate at
`fe53e204509d6fc566ea392ef3e4f66fcc7df5eb` passed all 99,276 function rows,
2,253 data rows, reference checks and the no-op patch. Its enforced converged
data audit judged 18,612 sources with zero second names or unjudged rows.
After master advanced, the automatic carried retry passed 22 rows across six
incoming sources, carried 99,254 rows and passed DIR32/data/EH checks.

The retry's link batch audit remains **UNVERIFIED**: census index `86db074988`
predates outgoing base `f77a97d726a12e401e0b20d32cd041f904812f76`, and these
six incoming source objects lack census-current receipts:

- `Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/DeliverPayloadAIUpdate.cpp`
- `Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/JetAIUpdate.cpp`
- `Code/GameEngine/Source/GameLogic/Object/Update/PhysicsUpdate.cpp`
- `Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DModelDraw.cpp`
- `Code/Libraries/Source/WWVegas/WW3D2/collect.cpp`
- `Code/Libraries/Source/WWVegas/WW3D2/ringobj.cpp`

Carry their current provider/consumer selection after the incoming donor-body
trims into the next scheduled census. Byte verification does not establish
complete link preservation; headline census figures remain unchanged.
[Reference-check evidence](../../reverse/attempt_support/reference-131fb8ff-20261101.md).
The local publication log and its six-path handoff are retained under
`build/bfme1-freshness-20261101/build/reference-131fb8ff-20261101/`.
