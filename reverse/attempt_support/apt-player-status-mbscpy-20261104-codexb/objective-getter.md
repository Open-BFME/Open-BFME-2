# Objective getter declaration and GameWindow trial

Base: `e065a7c5ef`. The post-CRT-repair sequential consolidation dry run now
rejects ObjectiveText only because the seed's Rva004266A1 view does not declare
`rva004267E9(int)`. Add the donor's existing `void*` member declaration to the
seed's public struct, retaining its class key and all layouts. No function
body, identity, name, pin, flags or source path changes. The three-address
objective donor stays in place until tu_skeleton verifies a later merge.

The seed's normal build retains 30/30 exact rows, its string/import checks,
and its exact EH graph. Frozen-source check passes. External object facts
before and after the declaration are identical. Ordinary link preview retains
LINKS, 2,632 -> 2,632 bytes, against index `f12552d0a7` (2026-11-04 20:47).

Separately, the header adoption tool reports PASS for replacing the seed's
private GameWindow with Bfme2GameWindow.h. The applied trial also byte-verifies
30/30 rows, but ordinary link preview refuses its changed
`??_7AptPlayerStatus@@6BGameWindow@@@` COMDAT against the first copy in link
order. It would lose the seed's 2,632 census-linked bytes. The trial was
restored and the restored source rebuilt before adding this declaration.
The shared header and its existing canonical registration remain unchanged.
That failure is recorded through re_log; no nonlinking trial is retained in Code.

Next: use tu_skeleton to absorb the objective-text donor. Callback consolidation
still needs compatible GameWindow/base vtables and a reconciled 12-byte color
vector view; the standalone check needs its /Oy- frame shape. No declaration
or vtable workaround is admitted here.
