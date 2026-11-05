# Four MessageStream callers: canonical header adoption

Inspected revision: `cff2efc6c8` (2026-11-05); revalidated at `aa57ef0d7d`
after syncing with origin/master on 2026-11-05.

The private MessageStream declarations in four callers use virtual slot 18
(offset `0x48`) for message creation. The canonical header declares that slot
as `appendMessage(GameMessage::Type)` and provides its integer overload.
Replace the private `appendType` / `createMessage` spellings with that method
and include `Common/MessageStream.h`, removing the private GameMessage views
as well. Palantir's private `MSG_RVA469` enumerator becomes an explicit cast
of the same native message value, `0x469`; no semantic enum name is inferred.

Verified sources and link preview results:

| Source under Code/GameEngine/Source/Common/ | Matched rows | Census-linked bytes before / after |
| --- | ---: | ---: |
| Bfme/Rva005E7C19Vslot1.cpp | 1 | 53 / 53 |
| Palantir_SetPlanningModeEnabled.cpp | 1 | 96 / 96 |
| Rva005E9137Check.cpp | 2 | 90 / 90 |
| doSetRallyPointCommand.cpp | 1 | 164 / 164 |

`header_adopt_lane.py adopt --class MessageStream --apply` passed for all
four sources. `header_adopt_lane.py accept --class MessageStream` passed
their structural, byte and link-preservation verdicts and retired four queue
rows. A separate `accept --class GameMessage` passed for Palantir and retired
its GameMessage row. The unrelated Palantir PlayerList queue row remains.

Final `./build.sh` of all four sources: 5/5 matched; string, float and import
reference checks passed. `find_declared_unmatched.py` reports all defined
functions matched. `link_check.py` reports 4/4 units link cleanly, preserving
403/403 bytes against census `2026-11-05 05:17` at `c95fcfcfcd` with current
objects. This preview establishes preservation in this scope, not a new
census measurement. No header, ledger identity, pin or alias changed.
