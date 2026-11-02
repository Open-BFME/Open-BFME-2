# ThingFactory lookup owner: exact canonical storage-view repair

Ready private candidate: `candidate.raw.cpp`; complete proof: `proof.json`.
The raw file preserves the immutable original's BOM/line endings and matches
the privately compiled candidate text. No Code/header/ledger/shared object,
claim, Git or network mutation was made by this investigation.

The private one-byte m_table member was only a receiver-address view. The
candidate removes that private ThingFactory definition, includes the unchanged
canonical header, and in the two actual member definitions calls:

```
reinterpret_cast<Rva00056F61 *>(field14)->rva0041534B(&name)
```

The canonical20-byte field14 remains opaque representation at+14. The existing
Rva00056F61 declaration supplies a callable receiver view only; its complete
application type or lifetime is not asserted. Real ThingFactory member bodies
can access their private storage directly, so no new public accessor/header
extension is necessary.

Private original and candidate prove all three native rows:

- findTemplate2D06CA/38B;
- rva002D06AA2D06AA/32B;
- rva000CEB48CEB48/5B.

All three complete external code definitions and symbolic relocations are
identical. There are no data definitions, added/dropped code, vtables, new
provider names, aliases, pins or exception promises. The existing rowed table
lookup provider and all consumers retain their bindings.

Root can apply this verified real-C++ repair, run ordinary/strict/link checks,
and use the owning `header_adopt_lane.py accept --class ThingFactory SOURCE`
to retire the queue entry. A repeat of the unchanged original automatic field
rename cannot solve the old1B-versus20B mismatch; the actual body/view repair
is what removes that false member-layout assertion.
