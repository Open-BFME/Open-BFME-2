# HordeContain position name: declaration ownership prerequisite

Reviewed at base `46da0a1d23b788d446417197cc533583bec71935`.
Scope: the existing 783-byte row at RVA `0x00474842` in
`Code/GameEngine/Source/GameLogic/Object/Contain/HordeContainRva00474842.cpp`.
No new body, matched bytes or linking credit.

WorldBuilder `0x010B8C80` names itself `HordeContain::updatePosition`, with
pairing score 7. Its two distance paths, position-update calls and model
condition bit clear agree structurally with the current retail body. This is
name evidence, not evidence that every private class view is correctly owned.

Normal `rename.py function --rva 0x00474842 --new updatePosition --basis
canonical:wb --dry-run` refuses before changing source:

> HordeContainIface11CSlots.cpp also declares rva00474842 as a method of
> UpdateModule; a word rewrite would rename it too

That file declares the method as pure virtual on its private `UpdateModule`
view and invokes it from the containing implementation. The actual row and
the direct call in `HordeContainRva0047A895.cpp` use `HordeContain`. Reconcile
the native declaration owner and slot contract before retrying; a global word
replacement does not establish that identity. Do not change the naming check
or add an alias to evade the refusal.

All three files pass `find_declared_unmatched.py --fail`. No production source
changed, no build was needed, and no claim remains from this investigation.
The blocked verdict was recorded once through `re_log.py`.

`t=6 model=gpt-6 lane=R budget=30m`
