### GiantBirdAIUpdate constructor: AICommandInterface slot signature (2026-10-29)

Cleared for `GiantBirdAIUpdateCtor_GiantBirdAIUpdate.cpp` (518 B). Its local
`AICommandInterface` view declared `virtual void aiDoCommand()`, so the
GiantBirdAIUpdate vtable named the nonexistent
`?aiDoCommand@AICommandInterface@@UAEXXZ`. Retail's secondary slot 0 is
`AIUpdateInterface::aiDoCommand(const AICommandParms *)` (0x002673F6, no adjustor
thunk), as in `gamelogic/ai.h` and `module/aiupdate.h`. The view now declares the
pure `AICommandInterface` slot and the `AIUpdateInterface` override. Evidence:
`./build.sh` 6/6 matched; `link_check.py` on the file: LINKS, 0 -> 518 B
(prediction against the 2026-10-28 20:44 census, 840db2d676). Three other
files keep the parameterless view (`GiantBirdAIUpdateOnCollide.cpp`,
`GiantBirdAIUpdateCtor.cpp`, `DozerAIUpdateConstruct.cpp`); they emit no vtable
and already link, so they were left alone.
