### Foundation canonical Module data access (2026-10-30)

Cleared for the Module key in `FoundationAIUpdateConstruct.cpp`: expose the
canonical protected getter through an abstract access view, preserving the
native module+4/data+0x74 access and the existing item IDs at +0x14/+0x18.
Five rows/EH and all 26 code definitions/relocations are conserved after the
one getter access-spelling correction. Current other public/protected copies
retain that identical four-byte provider. The owning acceptance tool retires
one key; preview retains LINKS/1,182 bytes against `ccafe54d1d`. No census gain
is claimed. The separate Thing/Matrix3D keys below remain blocked.
[Native fields and provider scope](../../reverse/attempt_support/module-foundation-data-access-20261030/README.md).
