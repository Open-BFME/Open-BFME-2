# HotKey bounded copy-contract / implicit helper review

Read-only review of the supplied candidate/proof, exact existing Code declarations and narrow ledger/registry matches. No builds, claims, network, source edits, object-cache sweep or independent native/COFF selection audit. All tracked reads stopped before this report.

## Exact candidate API and operation

Existing `Pair358C60` is `_STL::pair<const AsciiString,TreeHintRef00217D4C>`. Its existing key/value constructor specialization and inline-only destructor contract are retained. The candidate adds only this declaration-level copy contract:

```
namespace _STL { template <> Pair358C60::pair(const Pair358C60 &); }
struct Rva00359032Value : public Pair358C60 {};
```

There is no handwritten Value copy constructor/body or new application name. The derived form is an operation view that requests the existing pair's genuine string/reference copy semantics; it does not recover original application inheritance. Its base's first field is const AsciiString and second is the counted reference. Consequently this changes implicit special-member behavior compared with the former unsigned/void* POD view; equal8-byte storage alone is not the evidence for the change.

The base copy is already matched under its exact decoration at **00358B43/34B**, owned by `Code/Libraries/Source/WWVegas/WWLib/stlport_rb_tree_hint_00218022.cpp` (functions11709). Its notes identify AsciiString-key and proven refcounted-pointer copying, with application identity opaque. This is stronger than a size-only or guessed AudioEvent interpretation, while remaining a bounded type/operation contract.

## Extra implicit helper

The only added definition is `??0Rva00359032Value@@QAE@ABU0@@Z`:18B SELECT_ANY COMDAT, bytes `56ff7424088bf1e8000000008bc65ec20400`, one REL32 at+8 to that exact pair copy. No independent native RVA, exact row/pin, canonical/header/identity/hatch entry, or literal decorated-name Code use for this helper was found in the narrow search.

The changed `_STL::_Construct<Rva00359032Value,Rva00359032Value>` goes from23-byte POD copying to45-byte EH-bearing real-pair construction. Its provided after-fact calls the pair copy **directly at+29**, not the new18-byte Value helper. Thus this particular corrected provider does not establish a runtime incoming edge to the extra helper. Other incoming references/selection are the parent's current COFF/index task; no absence claim is inferred from that one caller.

The provided proof reports45 retained rows, eight EXACT EH graphs, one changed _Construct, this one added copy constructor, no removals or binding_changes, and routes_identical=false. These are existing private proof facts, not checks rerun here. The18-byte helper itself has no newly certified native placement in this review.

## Existing outside source contract

`HotKeyAddHotKey.cpp:74-106` already has a related nominal view: HotKeyPair is the same pair specialization, Rva00358B65 derives it, and Rva00359032Value derives Rva00358B65 with a converting constructor from that base. Its implicit copy can potentially use the same Value copy-constructor decoration despite a different immediate base/declaration context. No literal decorated-name hit is needed for an implicit compiler function to be produced.

This concrete second source view is why a source grep and this single-TU byte proof do not close provider selection. The parent must account for actual other emitted copies/uses. This review does not request a broad cohort rewrite or establish original inheritance from these existing wrapper views.

## Frozen/inline ownership boundary

The new constructor is compiler-generated from a class declaration; no new out-of-class source body exists for find_declared_unmatched to inventory. Its mere emission does not require a new present-unmatched/absent-from-retail marker or a separate HotKey ledger claim. Parser silence does not certify native identity or make the extra helper a recovered row.

Do not add a marker, pin, alias or row to manufacture ownership of this18-byte copy. If explicit native ownership is sought later, it requires the normal evidence/admission route and approved placement; no RVA or original application type is supplied here. Keep existing base-copy ownership unchanged. Any actual live selected helper must still satisfy the ordinary provider and consumer checks; neither matching surrounding45 rows nor equal code size waives those checks.

Conclusion: the extra implicit copy is a legitimate compiler consequence of the bounded real-pair copy contract, conditional on the parent's provider checks. It introduces no automatic frozen-file marker obligation and establishes no original inheritance/name/native-RVA claim. No full-image or outside-cohort closure is certified.
