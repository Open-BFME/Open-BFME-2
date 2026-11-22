# Explicit correction: Vector3 const-subscript identity

This correction supersedes the original study's identity wording, without changing
its byte observations. Original private artifacts remain unchanged. No production,
interface, header, row, pin, claim, tool, gate, Git or shared-cache change is proposed.

**Certain:** Original ZH vector3.h:108 returns `const float &`.
Current B2 Vector3Data.h:75 declares `float`; that is the current reconstructed API.
Retail1.06 RVA004047D9/10B is `8b442404d90481c20400`:
`mov eax,[esp+4]; fld dword ptr[ecx+eax*4]; ret4`.
This leaf returns a scalar through x87 after reading a32-bit float, rather than
returning an element address. Its complete original C++ declaration does not
follow from those instructions alone.

**Identity limit:** The existing row's notes record only a unique masked10B
whole-.text placement. The stored name and the reconstruction's inline emission
are not independent proof that this leaf originally belonged to Vector3, was
const-qualified, or had a particular vector dimension. The fresh targeted read
found0 E8/E9 sites to004047D9,0 to7173D0,260 to sanity control69B1, and0 literal
occurrences of VA008047D9. No independent caller currently binds this exact leaf
to the named class. This absence does not prove dynamic unreachability.

My earlier wording "real const subscript" and "wrong-ABI" overstated the original
class/signature identity. The correct distinction is the original ZH reference
API versus the current B2 value API, with a certain scalar native return for the
placed leaf and a bounded class-identity inference. No original EA type-debug
record establishes the missing binding. This does not prove the global canonical
model wrong, and does not justify switching the shared header to a reference return.

**Unchanged measured blocker:** On the original reported base bce1ceaf11/source
SHA44e2fd56...69e01744, fresh control43/43 and best canonical candidate42/43;
Sun005B0A95 remains971B with24 raw nonrelocation differences and19 identical
named relocations. Its changed SSE addition grouping can round differently.
The source bank is diagnostic only and must not be landed. Native code/data
footprint observations remain as recorded, while their identity labels need
the qualifications above. No new exact/linked/runtime byte or completed task.

Read README.md for sourcebank/diff/compiler scope, REVIEW-ORIGINAL-HDF.md for
tracked-copy edits, and the two separately named evidence JSONs. Root alone
performs ordinary no-change recording/publication; no gate/interface fix belongs
to this correction. No new compilation was run while assembling this package.
