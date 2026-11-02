# Ring donor closure

The same dependency cause as sphere remains in ringobj.cpp after its earlier
port trim: two unverified bodies plus loader/prototype/global-array emission
leave ten unresolved names and one losing TextureBase string accessor.
The current preview against index 984a4cdc4d (2026-11-02 08:35) starts at
zero linked bytes. This unit's eight native rows cover 64 bytes.

Retain the six accessors as clean out-of-line C++ and instantiate the two
existing animation-template members explicitly, without the donor bodies
that happened to emit them. All eight complete native bodies and symbolic
relocations remain unchanged. The partial Ring view distinguishes native
offsets (14C,164,17C,194,1CC,200) from the intervening donor field meanings;
it does not claim the remaining class or its vtable slots. Vector3 and
Vector2 use their established canonical headers. PrimitiveAnimationChannel
members come from pinned BFME 1 prim_anim.h, not a new private copy.

Normal and strict verification pass all eight rows, new-variants checking
passes, the normal private LinkGuard has no finding, and the bounded current
preview now LINKS 0 -> 64 B. A scheduled census must confirm headline linking.
The eight native plus two incidental retained definitions are byte/relocation
identical. Of 136 old external code definitions, 125 disappear and 11 remain.

The one changed incidental definition is explicit in complete-code-diff.json:
removing the old optimization anchor changes its uncalled compiler-generated
vector-constructor iterator from 34 to 48 bytes. It has no runtime/data incoming
relocation in this unit. The index selects ATL's earlier native 34-byte owner
at 1423; that current object independently matches retail with receipt hashes
checked. The ordinary link guard and preview retain selection. This is not
a claim that all retained incidental code is unchanged or newly recovered.

All 18,640 index touch records are present. No outside object touches the
21 Ring-class providers. Ten apparently sole shared providers have only the
old sphere object as an outside consumer; current sphere after 06685c8a62
has neither those definitions nor relocations. The audit records that stale
index distinction, rather than treating the former donor closure as required.
No selected shared provider has a non-sphere outside touch.

The owning hatch tool retires exactly two present-unmatched occurrences and
the anchor's two optimization pragmas. The owning DX rescan removes this
unit's obsolete queue row: it opens no DirectX stand-in. No new native row,
pin, hatch, source path, identity/data key or flag override is introduced.

The preceding water adoption dd5c6cdd6c passed its 23 native rows and five EH
graphs through publication. Its wider audit remains INCONCLUSIVE against
index 984a4cdc4d versus outgoing base 3fc40cd989, first missing the current
0CreateAHeroManager21FE49.cpp consumer receipt. That is carried to the next
scheduled census, not reported as global clearance.
