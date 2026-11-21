# ??_7BFMENetwork@@6B@ 0x0086B318: one retail table, two readable class names

Status: blocked (naming decision). Recorded in reverse/re_attempts.log.

## Target facts
- Retail table 0x0086B318 (16 slots, 64 B) is installed by ??0BFMENetwork 0x00558EC1.
- Slot targets 1..15: 0x5543D5, 0x553222, 0x550609, 0x559261, 0x557D98,
  0x5592AE, 0x557DFB, 0x5593AE, 0x559480, 0x55954E,
  0x55961C, 0x556674, 0x556730, 0x555BD5, 0x555C76
  (RVAs of the ledger rows each slot word lands on).

## Ledger facts
- Slots 4-7 are rowed as BFMENetwork::pushQueue0/popQueue0/pushQueue1/popQueue1
  (native_network_BFMENetwork_*.cpp).
- Slot 3 is ?isThreadRunning@GameSpyPeerMessageQueue / GameSpyBuddyMessageQueue (ICF).
- Slots 8-15 are rowed as GameSpyPSMessageQueue virtuals (trackPlayer*Stats,
  findPlayerStatsByID, rva00556730/00555BD5/00555C76) in
  GameSpy/Thread/PersistentStorageThread.cpp and PersistentStorageTrackPlayerStats.cpp.
- Slots 1-2 are placeholders Rva005543D5 / Rva00553222.

## Inference
The retail class at 0x86B318 is one class rowed under two readable names
(BFMENetwork from the BFME1 donor, GameSpyPSMessageQueue from the Generals donor).
`rename.py class --fold` refuses (both names readable), so choosing the spelling is a
naming decision. Until then both installer views (BFMENetwork.cpp, Rva00557CCCDtor.cpp)
keep Rva00552C0FBase's pure1..pure15 and slots 1-15 compile to __purecall.

## Next step
Approve one class name via name_lane (two seats), move the PS-queue rows and the two
placeholders onto it with `rename.py function --to-class`, then declare the overrides
in one shared header adopted by both installers.
