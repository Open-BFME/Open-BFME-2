# Object upgrade Module lookup view

Adopt canonical Module with a partial view for the existing ObjectID at +0x14.
The legacy field label m_castleID is retained; this does not prove its original
name or distinguish keep/castle semantics for the complete derived class.

The complete 81-byte helper at 0x00395708 returns Object::findModule's EAX
without adjustment. The complete 43-byte finder returns the raw module-list
entry. The native upgrade caller calls that helper at 0x00292F10 and pushes
[EAX+0x14] at 0x00292F1A. These bodies and accesses resolve the prior receiver
ambiguity for this storage adoption; no new method identity is inferred.

Private before/trial objects and the final strict-current object preserve all
four rows and all five external code definitions and relocation targets.
Normal byte, literal and import checks pass. The owning Module acceptance tool
retires one key; ordinary preview against ccafe54d1d retains LINKS/360 authored
bytes. No pin, row, source path, shared header or coverage changes. Independent
behavior/upgrade interfaces remain outside this bounded cleanup.
