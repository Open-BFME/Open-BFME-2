### ScriptActions doNamedEnterNamed link repair (2026-11-02)

`ScriptActions_doNamedEnterNamed.cpp` (92B) unresolved symbol `?Rva0026C347Command@Rva0026C347Commands@@QAEXPAXH@Z` resolved by pointing the call to the real rowed provider `AICommandInterface::rva0026C347` (`?rva0026C347@AICommandInterface@@QAEXPAVObject@@W4CommandSourceType@@@Z` at 0x0026C347 in `AICommandInterfaceAttackCommands.cpp`), which was already matched and linked.
Verification: `tools/build.py` 1/1 matched; `tools/link_check.py` LINKS (LINKED 91 -> 91 bytes).
