# Weapon return forwarding: three additional rejected private trials

Base 1c6e7e5711; source Weapon_bfmeGetLOSVictimPos.cpp, native 002CB65B/30B.
Read the existing coord3d-weapon-return-profile-20261101-bce2 handoff first.
Its companion/named-result 63B form was not repeated. Original byte/frozen
gates pass before these experiments. No Code source was changed.

New hypothesis: directly return the existing provider call through a by-value
member-pointer ABI view instead of passing a named coordinate result. The
current WeaponTemplateTargetPositions.cpp confirms the provider's 12B output
and ret16 ABI, but does not prove compiler result forwarding in this wrapper.

Private, normal-profile compile results:
- Canonical POD Coord3D: 45B; a 12B local, provider call, then three movsd copies.
- Existing Coord3DCtorView companion: 52B; a 12B local and memberwise result copy.
- Same companion with its supported empty-destructor option: still nonmatching.
All retain the original provider relocation; preserving the callee alone does
not preserve the caller. No shared header, provider contract, pin, alias,
ledger row or queue key was changed. No adoption or progress is counted.

Next: a supported target-specific shared construction/return profile or a
different evidenced C++ expression is needed to forward the output slot
directly. Merely changing the call to a typed by-value return is insufficient.
Controls: ignored build/one-each-no-qwen-20261101-1231/b2-01-* and local report.
File claim released. No Qwen/local inference; shared build cap ten.
