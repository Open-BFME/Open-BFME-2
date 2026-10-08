# AptSkirmish teardown, 315 bytes

The clean BFME1 donor is `game/GameEngine/Source/GameClient/GUI/SkirmishScreenDestructor.cpp` at `34f59164f6d1efd413c5fd37f4894ec834c3c0fe`. Its base/member teardown and two registration strings provide the semantic guide. BFME2 WorldBuilder's complete `AptSkirmish::~AptSkirmish` at VA `0x01465F20`, including its singleton assertion, independently supplies the target screen identity.

Retail RVA `0x00521977` ends at `0x00521AB2` with `ret`: 315 bytes. It restores three vptrs at offsets `0`, `0x218`, and `0x27C`, destroys members at `0x6D8`, `0x6C8`, `0x698`, `0x668`, and `0x288`, then calls the callback-region destructor at `0x27C` and the screen-base destructor at offset zero. All seven destructor providers are already rowed. The consumed-prefix storage includes gaps and makes no assertion of complete application class layouts.

Unlike BFME1, retail also deletes `TheSkirmishGameInfo` through its witnessed slot-zero operation, clears that pointer and `TheGameInfo`, and clears the singleton only when it equals the receiver. It removes `Skirmish/tooltipPlayerLevelIcon` through the rowed `AptPlayer::RemoveOverButtonHandler` and closes `AptSkirmish::InitGadgets` through the rowed helper. The canonical data owner `g_bfmeAptWindowManager` supplies the existing Apt player pointer. No new address pin, address global, or assembly is introduced.

The existing `Rva00521977` destructor spelling is retained to keep the deleting-destructor caller bound without adding a competing real name. `/O1 /MD /EHsc` with the canonical BFME2 string headers reproduces all 315 bytes and both string relocations. The normal byte gate passes, and `eh_verify.py` reports the complete EH data `EXACT`. Fresh linking and runtime execution remain unverified.
