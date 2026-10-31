# UnleashSpecialPower canonical prerequisite, qc-12
Base d4b06a467a; queue5299; no source change or adoption.
Native ctor4CE006,49bytes calls44EF5E with unchanged this and installs tables
C5FDC0@0, C4D640@C, C4DEE8@10, C5FD98@20. The factory-supported allocation
size is88hex (class_contract retail-new). No native own member is initialized.

Hand decisions on both queued attributes:
- bases: one complete base at0, constructed by native44EF5E. Existing
SpecialAbilityUpdate versus Rva0044EF5E are competing reconstructed names for
that same base, not distinct bases. The semantic SpecialAbilityUpdate name is
an existing donor/view lead, not recovered original target identity. Shared
header work must reconcile the single native base, not multiply inherit both.
- field@20: a secondary interface vfptr, not an independent data pointer.
Ctor installs C5FD98; slot8 points to native4CE0D9, whose ECX-18 load accesses
the complete object's owner+8, independently proving a this+20 entry context.
Likewise m_p0C/m_p10 in the constructor's partial view are vfptr stores, not
retail data fields to copy into a header.

The primary C5FDC0 slot17 is4CE18A, whose first direct base call is45108D.
Secondary tableC5FD98 has nine callable entries followed by zero; its final
entry4CE0D9 is the other served donor. Full29-entry observed primary/secondary
prefix is not a proof of all inherited tables or primary extent. The two other
native tables C4D640/C4DEE8 require full behavior/update provider closure.
No canonical SpecialAbilityUpdate header is registered on this base, nor an
UpdateModule header. Reusing dummy base profiles would conceal inherited
callback/getter changes (coordinator's behavior slot9/getter2533D3 warning).

Real blocker: class:SpecialAbilityUpdate, including the canonical native44EF5E
parent hierarchy and provider closure. Establish that separately before sharing
a derived header. No root adoption attempted, no header fabricated from dummy
pointers and no unresolved slot falls back to a new base default.
Both served donors remain unchanged. Raw bounded native bodies attached;
no external donor source supplied target offsets. No hatch, tools or ledger edit.
Shared obstacle register was already refused as held by another worker; this
README is the proposed entry. No new byte or LINKED coverage is claimed.
