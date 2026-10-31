# GarrisonObjectGroupOrder decisions, qc-12
Basea997dfe5ef; queue5419; no source edit or adoption.
All seven queued attributes resolved by bounded native evidence:
- base-slots: complete GroupOrder tableC6A520 has14 entries, not0/1/4/13.
Native derived tableC6A3C4 likewise has14 entries, then the Garrison string.
Snapshot occupies slots0..3; command4, progress5, defaults6/7, position8,
defaults9/10, report11, classkey12 and clone13 follow. Exact target RVAs attached.
- field@1C: three-float position spanning1C/20/24, not an int or opaque12-byte
member. Ctor546C57 zeroes all three via MOVSS; refresh546D7C copies target
position with float loads/stores; xfer546D15 transfers the whole coordinate.
- name@20 and nested@20: y within that position, not standalone storage.
- name@24 and nested@24: z within that position, not standalone storage.
Existing m_pos spelling can represent the complete coordinate; the scalar
m_1c of the command-only view is incomplete. No original field name recovered.
- slot1: inherited empty post-load nativeB3FD0, not command546DD4 (slot4)
or clone546CB8 (slot13). Name getter546D56 is slot2, xfer546D15 is slot3.
Base extent18 is independently proved by ctor5488C5's vector4 and integers10/14,
and derived owned ID18 plus position1C..27. Complete derived extent28.

Real blocker: class:GroupOrder. It has no canonical header. Current full lifetime
owner uses Snapshot and exposes only its destructor/xfer, so its exact body
match does not establish the remaining14-slot ABI or inherited providers.
Native base slots7/9/10 have real callbacks47A69C/5CB9FF/36CC7A, not purecall;
changing those to abstract defaults would alter native dispatch. Other base
slots are purecall and require caller-backed signatures before declarations.
The derived callbacks at6/7/9/10 must preserve their native default bodies,
not gain guessed names or new unresolved provider bindings. Full base virtual
provider/signature closure must precede this header. No placeholder virtual
surface or pointer-padded class is promoted merely to pass the two bodies.

Both served files unchanged and frozen-checked. No module-root adoption,
hatches, tool changes or new names/byte/link credit. Native raw proof attached;
source/donor type spellings are not used as original target layout evidence.
Shared obstacle register held elsewhere; this is the proposed entry.
