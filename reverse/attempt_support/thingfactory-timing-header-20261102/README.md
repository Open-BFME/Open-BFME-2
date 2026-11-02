# Timing-log ThingFactory header adoption

Rva0023C641Write.cpp's native setup reads the first-template pointer at
factory+0x0C. Replace its private factory view with the existing canonical
header and use that header's public firstTemplate() accessor. The cached
opaque pointer is const void*, preserving the accessor's const contract and
its unchanged four-byte storage. No shared header is edited.

All three native rows (542 B), four literal references, one float and six
imports pass normal and strict checks. All five prior complete external code
definitions and five external data definitions remain byte-and-symbolic-
relocation identical. Only the already-existing header's six-byte inline
accessor is additionally emitted; no factory/base table appears and no old
provider is removed. This incidental body is not a new matched-byte claim.
The scoped preview retains LINKS542B, with no new census linking claim.

The owning header accept tool retires exactly this ThingFactory queue entry.
The earlier owning whole-cohort swap correctly rejected private-field access;
using the real public interface fixes the caller instead of changing access
control or weakening a gate. Forty-three other factory header entries remain
for their own base/include, method, lifetime and member-pointer prerequisites.
The global outgoing consumer audit and scheduled census remain authoritative.
