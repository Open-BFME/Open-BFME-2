# GiantBird canonical Thing and Object prefix

Adopt the current Thing header in the already Module-adopted GiantBird unit.
Its old queue error is stale: the header now declares the existing native
Thing::getDrawable owner at 0x005508E2. No Object-scoped replacement or pin is
introduced.

The private Thing ended at +0x38; canonical Thing owns storage through +0x60,
including the existing position at +0x38. Remove Object's overlapping position
and padding, retain Object::getPosition using inherited m_cachedPos, and pad
from +0x60 to ID +0x74. Transform remains at +8; every later field keeps its
offset. The native onEnter instructions recorded in the proof independently
use position+0x38 and ID+0x74.

All six owned rows and EXACT EH survive the private and final strict-current
builds. All 30 existing external code definitions and their relocations are
identical. One debug-referenced compiler iterator is newly emitted by the
canonical value members: its complete 34 bytes exactly match the existing ATL
owner at 0x00001423, with no relocations. No new row or covered byte is claimed.

Normal verification retains both strings, the empty-string reference and both
floats. The owning Thing acceptance tool retires the remaining header key for
this file. Ordinary preview against ccafe54d1d retains LINKS/1,359 authored
bytes. The inherited getContain shadow definition remains separate identity
work; the prior wider audit still needs the current affected-consumer receipts
and scheduled census confirmation.
