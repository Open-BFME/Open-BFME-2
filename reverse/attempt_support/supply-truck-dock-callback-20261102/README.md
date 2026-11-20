# SupplyTruck keyed dock delay, 2026-11-02

Target facts: secondary slot19 at852F38+4C points to the181B body4A6F0A. It initializes two literal module keys, calls Object::findModule for each dock, and selects the actual module-data dwords6C/68 or zero. The native guard/EH relocations and both exact strings are part of the proof, not just the instruction skeleton.

Donor facts: Zero Hour SupplyTruckAIUpdate.cpp224-240 and BFME1's recovered SupplyTruck implementation use public Object::findUpdateModule. Zero Hour Object.h308 defines that public inline wrapper over protected findModule (its protected declaration is at655). The BFME2 draft header omitted this API. It now has the same wrapper and a forward declaration; findModule stays protected. This is donor-backed API recovery in a draft BFME2 header, not a claim that the external donor path is retail BFME2 source.

Ordinary C++ through that wrapper matches all181B and all28 current ctor rows. Both literals pass; three complete parent EH graphs are EXACT. The full external-definition comparison preserves all82 prior code/seven data definitions and relocations, adding the wrapper, callback and two string definitions. Local static guards and EH objects are covered by normal/strict body and EH verification rather than that external-only comparison. The attached before/after object hashes identify the private proof.

The old Rva004A6F0A representative and its local-static identity work remain; no pin, alias, register retirement or shared-check change is added. The public header change must pass its normal dependent-source hook gate before publication. Primary overrides/base providers still block the unit; no unit/census, unique-byte or runtime gain is claimed.

The shadow data check reports three local-static identity findings in the new callback (shared guard and two keys at A03C5C/A03C54/A03C58), still owned by the old placeholder's identities. This migration does not retire or claim those keys. The first ordinary header gate also exposed ThreatFinder's unrelated stale Snapshot include; its separate verified repair is317e5fbef9, after which the full dependent-source gate resumes.

## 2026-11-20 Data retirement recheck

At `898a8cb5d7a`, `SupplyTruckAIUpdate.cpp` passes 38/38 rows and all three EH graphs. The current pool-key guard at `0x00A03C50` already has its emitted `getModuleNameKey` identity in the ledger. The Drawable initializer identity at `0x00A03C60` is also current. The owning retirement tool still refuses two findings and leaves the existing baseline entry intact.

- The named callback in `SupplyTruckAIUpdateCtor.cpp` and the old `Rva004A6F0A` callback in `SupplyTruckAIUpdate.cpp` emit separate mutable guards for `0x00A03C5C` and separate key cells for `0x00A03C54` and `0x00A03C58`. The named callback remains outside the approved home for `0x004A6F0A` and its three EH rows. The current split dry run omits the callback from its carve and fails compilation on undeclared `m_3F0` in the composed view.
- `busyConditions` and `regroupingConditions` each occupy a full 48-byte read-only `SELECT_ANY` COMDAT in the current object. Their bytes and all three relocations match, and the retail constructor passes `0x00C53330` at both sites. Direct source reuse previously changed register allocation. The real link runs with `/OPT:NOICF`, so the two current sections remain an ownership problem.

The next ownership repair needs the constructor and main class views to agree, plus one set of callback guard and key cells. The two condition sites also need one proven runtime table without changing the matched constructor or its EH graph.
