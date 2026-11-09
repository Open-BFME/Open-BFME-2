### ThingTemplate equivalence needs canonical string and vector views

Status: this consumer adoption verified; wider class recovery open. Updated:
2026-11-09; inspected revision: c21963756a.

ThingTemplateIsEquivalentTo.cpp now adopts the canonical class and StringBase
declarations, retaining its existing comparison ABI and Rva001E35DFView getter.
Normal verification passes the complete 335-byte row; the current-input preview
against index5b5011469d preserves LINKS330/330 bytes. Owning acceptance retires
one header queue row; 74 ThingTemplate consumers remain locally.

All six retained COMDAT payloads are unchanged. The removed incidental
StringBase-returning getName has no known outside Code/ledger/index consumer;
the original override getter stays. Existing shared-header alias directives
are explicitly audited rather than described as unchanged object directives.

[Native facts, provider preservation and verification scope](../../reverse/attempt_support/thingtemplate-equivalence-header-adoption-20261109.md).
Other consumers and member/base identity recovery remain open. The preceding
AptFileTransferPopup.cpp receipt gap is carried forward. Census/image
confirmation is pending; no new global linking coverage or runtime outcome
is claimed.
