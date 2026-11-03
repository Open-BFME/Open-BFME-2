# Devastate canonical AsciiString inline ownership

Bounded read-only review. Reread AGENTS.md, candidate.cpp.txt, the canonical ascii_string.h, relevant frozen-file docs/tool, exact ledger rows and the candidate's selected proof facts. No compilation, claims, network, tracked edits or gate runs. All tracked reads stopped before this report.

## No new row or marker for these copies

The candidate selects `/Ireference/shims/bfme2_ascii` and includes `ascii_string.h`; canonical_classes.csv:4 registers that exact shim. It includes the frozen sibling string_base.h. The candidate sets neither BFME_ASCII_IMPLICIT_DTOR nor BFME_ASCII_DTOR_DECL, so the default one-pointer wrapper's in-class constructor and destructor apply:

- `AsciiString(const char*)` calls the existing StringBase<char> const-char constructor on the same one-pointer receiver.
- `~AsciiString()` calls releaseBuffer directly.

Both exact decorated operations already have matched ownership in `Code/Libraries/Source/WWVegas/WWLib/ascii_string.cpp`: `??0AsciiString@@QAE@PBD@Z` at0000654A/18B (functions.csv:324) and `??1AsciiString@@QAE@XZ` at0048BA39/5B (functions.csv:4891).

The private proof records new SELECT_ANY COMDAT copies (selection2), not newly invented operations: ctor18B `56ff7424088bf1e8000000008bc65ec20400` with REL32 at+8 to the StringBase constructor; dtor5B `e900000000` with REL32 at+1 to releaseBuffer. Their emission in this TU does **not** require separate Devastate ledger rows or markers, nor move the existing owners. Do not add a second claim simply because a canonical inline operation emitted another physical copy.

This is a policy/ownership conclusion, not new native byte verification. The owner must still verify complete bytes, resolved callee identity and actual kept-provider effects. The proof's7 matched rows/no errors/no changed retained definitions are existing private results; this reviewer did not rerun them. `routes_identical=false` should not be paraphrased as whole-object route identity; binding_changes is empty, and added providers have their own route facts.

## What the frozen checker actually does

`docs/matching.md:777-806` requires checking the file before/after work. Reported real bodies need rows; an absent-from-retail annotation is honest only for retail-dead-stripped code. No hand-added present-unmatched or whitelist growth is allowed.

`find_declared_unmatched.py:157-165` inventories out-of-class qualified definitions in the supplied .cpp text; it does not preprocess includes and inventory canonical in-class header bodies. An `inline` keyword alone does not exempt an out-of-class definition. Its declared/matched lookup is global, with own-source ownership separately used for stale marker checks. Parser silence is not byte/layout/provider proof, and should never be manufactured by changing declaration placement.

Here both exact canonical string operations are already rowed elsewhere, so neither a new row nor a dead-strip/unmatched marker is justified. In particular, absent-from-retail would contradict their existing native rows.

## Existing Devastate destructor debt stays separate

Candidate retains:

```
// ??1DevastateSpecialPower@@MAE@XZ present-unmatched
DevastateSpecialPower::~DevastateSpecialPower() {}
```

The matching hatch baseline entry is12611, one existing present_unmatched key in this source. The private before/after facts retain identical25B code: three derived/subobject vptr stores followed by a base-destructor jump; COMDAT selection1 also remains. No exact MAE/UAE Devastate destructor row was found in the narrow ledger lookup. A nearby placeholder destructor under a different class spelling does not by itself establish its identity or excuse retiring this marker.

Keep this as unchanged existing debt during this bounded AsciiString adoption. Do not add another marker, relabel it absent-from-retail, invent a name/cast, or claim its body now rowed because the string helpers are. If a later proper destructor identity/row is established, remove the stale marker and retire its counted hatch through the owning workflow, then recheck the file.

The NameKeyGenerator header queue entry for this source describes the prior StringBase redefinition and remains subject to the owning header_adopt_lane acceptance. Canonical header inclusion and unchanged existing destructor debt are distinct findings; no header debt is retired by this report.
