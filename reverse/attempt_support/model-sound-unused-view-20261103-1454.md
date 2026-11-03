# Model-condition selector: remove unused comparator scaffolding

The old donor record view included a set of BfmeStringRecord002CF550 with an
inline comparator returning false. The native find loop never inspects that
set or calls the comparator: it reads the19-word flags and the indexed8B
assignment record before offset20C, and advances by220. The selector's other
record view independently puts its actual map at20C. Do not assert that the
donor's unused set/comparator was a recovered retail implementation.

Remove that unused comparator/type and represent its unread12B storage by
offset20C padding, retaining the8B tail and a compile-time220-byte extent
check. Keep all headers, flags and actual field accesses. Remove the now
orphaned donor-view comment/forward declaration after native composition.
No actual native function body, identity, row, alias, pin, register or header
changes. Six existing rows/301B, all22 external code bodies/relocations and
every non-debug section remain identical under normal/frozen/EH/strict gates.
The comparator was never emitted: there is no additional native-code removal
or runtime, memory or crash gain claimed by this source-only cleanup.
