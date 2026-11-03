# Model-condition selector: reconcile the overlapping storage view

Native approved merge planning selects BfmeObject544Find.cpp and
ModelConditionSoundSelectorClientBehavior.cpp. The first dry-run cannot compose
the two existing Rva004CABE5Store views: donor references m_vec, while the seed
keeps m_begin/m_end. Native tu_views independently reports m_begin at08..0C
overlapping the donor vector08..14. Both old sources pass native match checks;
the original method's74B loop uses a544B record stride and existing tested
19-word condition flags plus indexed Rva002C99FB assignment.

Reconcile only the donor private storage view: retain its20B object extent,
name begin/end with the seed's existing field spellings and opaque record type,
preserve the unread third vector word as offset10 padding, and cast these two
pointers to the donor's unchanged record view for its existing accesses.
Headers, flags, method identity/ABI, record fields, predicate/assignment calls
and every loop operation remain. No new semantic member role is asserted for
the unread word. No shared header, alias, pin, row or baseline is changed.

The native74B row and its relocations remain identical. Exactly two unrowed
vector<BfmeObject544View>::begin/end compiler-emitted copies disappear because
the body now reads their same two pointers directly. No other census object
touches either symbol, and this record type occurs only in this current source.
Every retained non-debug object section including data and directives remains
identical after removing exactly those two named code sections. There is no
other removed/changed/added external code. Normal/frozen/EH and strict native
receipt checks pass. This is a separately verified prerequisite; the native
merge and provider guard must still admit the final composition. No runtime,
RAM/leak/crash or new native coverage claim.
