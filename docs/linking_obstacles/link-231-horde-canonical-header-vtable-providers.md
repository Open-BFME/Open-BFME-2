### LINK-231: Horde canonical-header adoption exposes unresolved vtable providers (2026-11-04, codexb)

**Status: blocked for `HordeWorkerAIUpdateDtor.cpp`.** Adopting `HordeAIUpdate.h`
can preserve both destructor rows, but the resulting vtables reference four
unresolved HordeAIUpdate members and AIUpdateInterface's `vslot094`/`vslot095`.
Restore the existing providers' identities before retrying; the worker trial
was reverted. The private-command unit's adoption passes and preserves LINKS.

Evidence and exact names: [header-adoption checks](../../reverse/attempt_support/horde-header-adoption-20261104-codexb.md).
