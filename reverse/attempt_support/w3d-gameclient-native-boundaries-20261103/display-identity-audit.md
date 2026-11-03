# Native identity audit: factory at 8FCAE

Bounded read-only review, 2026-11-03. No builds, gates, network, claims or tracked
edits. `display-identity-audit.json` archives the native bytes/tables, exact row
and pin witnesses, current five-row/337B normal object hash and compiled symbol.

**Conclusion: the W3DGameClient::createGameDisplay owner/name at 8FCAE is false,
independently of the constructor pin's spelling.** The code is existing covered
native text, not a lost row. Its correct lexical method/type names and approved
retail TU path are not established by this audit.

## Independent receiver-table evidence

- The GameClient-derived device constructor **4C43E** calls GameClient's
  constructor and installs primary **7C4738** plus secondary **7C4724**.
  data_ledger.csv:1282 bounds the primary at **208B / 52 slots**.
- **7C4790 is slot 22**, not this table's start. It contains **4C7A8**, the
  existing rowed W3DGameClient::addScorch (functions.csv:39397).
- The device table's **slot 37**, at **7C47CC**, contains **4C45D**, not 8FCAE.
  Canonical GameClientClass.h places createGameDisplay at that slot.
- A scan of mapped retail sections finds **one aligned .rdata pointer to
  8FCAE**, at **7C7CC8**, **slot 14 of separate table 7C7C90**. The data ledger
  independently bounds it at **312B / 78 slots** under Rva008FCA3 (line 1564).
  Existing rowed constructor **8FC51/18B** and destructor **8FCA3/11B** both
  install that table; actual immediate sites are **8FC5B** and **8FCA5**.
  Existing gadget and winDestroyAll rows corroborate this separate table group.

Thus the false owner follows from table membership and lifetimes, without
assuming an English replacement name from the product or donor.

## Native body and product contrast

| Fact | Factory 8FCAE / 53B | Device slot-37 factory 4C45D / 53B |
|---|---|---|
| EH helper | 629188 | 629188 |
| Allocation | 2FDA0, size **D8** | 2FDA0, size **2B0** |
| Constructor | **104EBF / 87B** | **49DEA / 293B** |
| Product table | **7CF800**, six slots | **7C3C80**, real W3DDisplay table |
| Existing owner | false W3DGameClient name being audited | matched address-owned rva0004C45D in W3DGameClientFactories.cpp |

Both allocation/constructor calls are direct native instruction facts. In
8FCAE incoming ECX is never dereferenced or used for receiver-dependent
computation. PUSH ECX reserves a stack word; after allocation ECX is overwritten
with EAX before construction. The returned constructor pointer is not adjusted.
That absence of receiver use alone proves no class identity; the tables do.

The D8 product constructor stores 7CF800, builds Render2DSentenceClass at +4
through 157E80 and initializes C8/CC/D0/D4/D5. Its existing matched destructor
104DB0 destroys the sentence at +4 through 157C70. The six native slots are:

0=105AF3, 1=10500F, 2=104E68, 3=105CC7, 4=104DE6, 5=104F16.

These have existing address-owned/window-rendering/deleting-destructor rows;
none supplies permission to invent the product's original class name. The
constructor's current Rva00104DB0 identity and data_ledger.csv:2041 already
describe this six-slot object independently of the false factory label.

By contrast canonical Display.h bounds the **base Display at 144B** with a
**100-slot primary table**; rowed real W3DDisplay ctor 49DEA begins its own
storage at +144. The real device factory's 2B0 allocation and 49DEA call agree
with the existing factory owner. A D8 complete product with the six-slot table
cannot be this canonical Display object. This is more than an unresolved
constructor classname.

## Why the old byte match did not establish identity

The old attempt at re_attempts.log:83658 established a unique compiled-byte
placement, then attributed the donor inline W3DGameClient.h method name to it.
The current normal object's dependency list confirms it uses external ZH
W3DGameClient/W3DDisplay declarations and the older sweep Display header, not
the canonical BFME2 Display declaration. The donor inline is literally
`return NEW W3DDisplay` (ZH W3DGameClient.h:101); that is a donor fact only.

symbols.csv:1692 pins the W3DDisplay constructor name to 104EBF based on this
factory's native REL32. That proves the native destination, not its lexical
name. The exact same constructor name already has a matched 49DEA/293B owner
(functions.csv:68043), while 104EBF has the matched Rva00104DB0/87B owner
(functions.csv:41836). They are not complete byte twins. The real 4C45D factory
is also already matched (functions.csv:33837), so no new text is needed to
explain the genuine device create-display slot.

Naming correction, pin retirement and any source move must follow their owning
tools/claims/current TU approval separately. No inferred replacement English
name, new pin/alias or original retail source-path assertion is proposed here.
