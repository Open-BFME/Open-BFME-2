# SupplyTruck keyed dock delay, 2026-11-02

Target facts: secondary slot19 at852F38+4C points to the181B body4A6F0A. It initializes two literal module keys, calls Object::findModule for each dock, and selects the actual module-data dwords6C/68 or zero. The native guard/EH relocations and both exact strings are part of the proof, not just the instruction skeleton.

Donor facts: Zero Hour SupplyTruckAIUpdate.cpp224-240 and BFME1's recovered SupplyTruck implementation use public Object::findUpdateModule. Zero Hour Object.h308 defines that public inline wrapper over protected findModule (its protected declaration is at655). The BFME2 draft header omitted this API. It now has the same wrapper and a forward declaration; findModule stays protected. This is donor-backed API recovery in a draft BFME2 header, not a claim that the external donor path is retail BFME2 source.

Ordinary C++ through that wrapper matches all181B and all28 current ctor rows. Both literals pass; three complete parent EH graphs are EXACT. The full external-definition comparison preserves all82 prior code/seven data definitions and relocations, adding the wrapper, callback and two string definitions. Local static guards and EH objects are covered by normal/strict body and EH verification rather than that external-only comparison. The attached before/after object hashes identify the private proof.

The old Rva004A6F0A representative and its local-static identity work remain; no pin, alias, register retirement or shared-check change is added. The public header change must pass its normal dependent-source hook gate before publication. Primary overrides/base providers still block the unit; no unit/census, unique-byte or runtime gain is claimed.

The shadow data check reports three local-static identity findings in the new callback (shared guard and two keys at A03C5C/A03C54/A03C58), still owned by the old placeholder's identities. This migration does not retire or claim those keys. The first ordinary header gate also exposed ThreatFinder's unrelated stale Snapshot include; its separate verified repair is317e5fbef9, after which the full dependent-source gate resumes.
