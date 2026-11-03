# Living-world interface headers: four debt retirements

2026-11-03; continuation from c1325ac0b6. Scope claimed through the repository:
Rva00222A8BTarget and its frozen header, GameMessage/MessageStream and their
shared frozen header, and both source files. No shared header is edited.

LivingWorldLogic replaces its one-method private Apt receiver with the existing
canonical Rva00222A8BTarget. The actual bool method ABI and call remain unchanged.
All174 ledger rows and36 EH graphs verify, and all427 external provider names,
properties and bindings remain. The sole textual relocation difference is the
dispatcher3170B body's29 local label numbers: raw bytes are identical, and every
old/new target stays at the same offset inside its own function section.
The existing MessageStream include in this source already passes its owning
acceptance; that stale queued item is retired too. The11 shadow identity
findings from the prior packet are untouched and no identity debt is retired.

ArmyUnitSwapperSelection replaces both private GameMessage/MessageStream views
with their existing canonical header. Four old numeric enum placeholders map
to the established canonical IDs1705/1712/1713/1715. The unknown1727 remains an
explicit conversion to GameMessage::Type(0x6BF), without inventing a name or
changing its numeric value. All16 rows and all21 complete external providers,
properties and symbol routes remain identical. Owning acceptance retires both
GameMessage and MessageStream queue items. No row, pin, flag, lifetime provider,
release cast or source path changes. Two-source preview keeps LINKS21,372 bytes.

The first Swapper scratch attempt still contained the macro-generated private
MessageStream view after automatic swapping, so compilation refused C2011.
Its exact already-read declaration was then removed; the bounded final proof
passes. Neither failed text nor a gate workaround was applied to Code. The
first Apt snapshot raced the publisher's rebase and captured pre-adoption main;
its checksum guard prevented application. The final proof was rebuilt from idle
current main before applying. Publication and source capture are kept sequential.

Count correction: the previous retained-accessor README/obstacle entry said175
Logic rows based on the frozen-file inventory banner. The narrow actual ledger
and normal byte builder both count174; those are the verified rows. This batch
does not edit functions.csv or remove a row. All190 current rows are preserved.

Prior publication c1325ac0b6 landed on attempt2 after an immediate rebase retry.
Normal push checks pass423rows and61 EXACT EH graphs across15 source consumers.
Its batch audit is INCONCLUSIVE at index984a4cdc4d/outgoingbase33936a1dc4e1f4dc703ebede1b06bfd523153bea:
all15 sources lack current census receipts. prior-publication-scope.json names
every source; carry them and affected consumers into the next scheduled census.
No whole-current-image, runtime, new-coverage or official-census gain is claimed.
