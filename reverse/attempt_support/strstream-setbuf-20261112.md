# strstreambuf setbuf and its real table

At inspected master 7d86ea94731, the picker serves table 0x0087A878 from
Rva00602A30Cluster.cpp: one bridge, no refusal, with only slot1 mismatching.
The table has 56 bytes and 14 virtual slots. The target constructor's store
at 0x00602A88 independently binds the class to that native table; slot1
points to 0x00013570, complete bytes 8b c1 c2 08 00 (return this, RET8).

Donor fact: the locally verified official STLport4.6 release defines
strstreambuf::setbuf(char*, streamsize) as return this in
vendor/stlport-4.6/src/strstream.cpp:199-203; its protected virtual declaration
is in stlport/stl/_strstream.h:57. The archive and payload hashes match the
local release manifest. The name is the actual library method, not a BFME2
application identity inferred from a same-byte donor hit. A bounded native
review independently checked source provenance, slot identity and providers.

Add the ordinary definition beside the existing constructor. Private
verification passes both rows, preserves all 12 previous COMDATs unchanged,
and adds only the five-byte setbuf body with no relocation. Ordinary
add_match --icf-owner verifies it against the existing char streambuf
default in Common/StdioStreambufBase.cpp. No pin, alias mask or new class
view is added. This ICF row contributes zero unique retail bytes.

Remove the old linker alternate from stlport_strstreambuf_dtor.cpp that
redirected the missing narrow override to the wide base default. The owning
hatch tool lowers exactly one register line: alternatename 2,320 -> 2,319.
No other register entry changes. Both frozen-file checks pass, and the
normal two-source build passes all six rows, including the destructor's EH
handler and cleanup; literal/import checks pass. Strict preparation passes.

The read-only vtable planner uses an explicit eight-object cohort containing
all three emitters and the required slot providers. Before the admission:
one generated table, fourteen bridged slots, no refusals. After: zero
generated tables, zero refused tables, one already-correct table. The three
56-byte source table copies have the same slot signatures; constructor and
other retained code are unchanged. The final live constructor object is
checked against the private candidate's complete COMDAT set.

Own link_check reads LINKS for both edited units: 105 -> 110 and 155 ->155
own-row bytes, respectively, against the supported19:19 index refresh at
aa7acf764d. The extra five bytes are an already-covered ICF fold. That index
refresh is not a new scheduled census. No image was built or run here.

No source path changes, active include or tooling consumer needs repointing.
The published bridge queue is deliberately retained: the picker's pass test
requires the next published real link to omit this bridge and any refusal.
That confirmation and the full consumer/census audit remain pending. The
prior push's broader audit was inconclusive on a current receipt for
Common/0CreateAHeroManager21FE49.cpp; this scoped check does not close it.
