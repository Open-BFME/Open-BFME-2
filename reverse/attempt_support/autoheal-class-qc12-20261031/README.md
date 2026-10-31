# AutoHealBehavior native decisions, qc-12
Basee78b61f1b2; queue5330; served sources unchanged.
All seven queued attributes resolve from the attached bounded native proof:
- inherited@0: primary vfptrC3FCDC, not ordinary m_vtable data.
- inherited@C: behavior-interface vfptrC495A0.
- inherited@10: update-interface vfptrC3FCD0; slot0 is existing update45280B.
- inherited@20: UpgradeMux subobject, extent8, vfptrC3FC88 at20 plus byteflag24.
Native ctor452592 calls253390, calls4CE2A3 on this+20, then installs the final
mux table. Existing AutoHeal override4A33E0 adjusts this by-20 before waking
the complete object, corroborating the secondary receiver. Do not promote the
partial aggregate/member spelling as proven original C++ inheritance syntax.
- inherited@24: one-byte executed flag, not an integer. Native mux ctor4CE2A3
clears byte+4 and mux transfer4CE397 passes+4 to the native bool Xfer slot90.
- inherited@28: damage-interface vfptrC3FC78, not m_28 uint. Ctor first places
BE2B78 then replaces it; table slot0 is existing AutoHeal onDamage45266B.
- name@30: stopped flag. stopHealing4523B6 sets byte30, activation4523CC
clears it then calls giveSelfUpgrade on+20 and setWakeFrame(owner,1). Existing
m_stopped is a consistent structural name, not recovered original member text.
Own state2C/30/34 and complete38 factory extent are retained. All pointer roles
come from the target, not the ZH donor's differing own fields.

Primary native prefix is dtor45264F, postload4B7BAA, name4523A3, xfer452401,
key45235E. The automatic slot1 xfer vote is rejected. No primary or secondary
slot may become an inherited null default after adoption. Native key45235E is
currently rowed as a static address-name method; a canonical virtual getter
profile must reconcile that binding/name under docs/naming.md, not silently
create an alias or assert a new canonical method name from vtable position.

Real blocker: class:UpdateModule with canonical UpgradeMux and damage interface
profiles as further prerequisites. None is registered on this base. The two
served partial views (a static pool key class and a nonpolymorphic padded
UpdateModule plus mux-member activation view) are not honest canonical bases.
Coordinator's root getter/profile boundary is honored: no root adoption or
header manufactured from pointer stores. Both served donors frozen-checked;
no hatches, aliases, pins, tools, ledger or source changes; zero adoption/byte/
linking gain. Shared obstacle register held elsewhere; this is proposed entry.
ZH gives the official AutoHealBehavior header destination and semantic leads
only; it does not establish target offsets or the derived virtual providers.
