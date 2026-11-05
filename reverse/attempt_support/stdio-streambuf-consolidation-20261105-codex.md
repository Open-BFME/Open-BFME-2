# Narrow streambuf declaration reconciliation

Base: `01abde215a`; inspected sources are the approved
`Code/GameEngine/Source/Common/StdioStreambufBase.cpp` and the three WWLib
fragments `stlport_narrow_streambuf_defaults.cpp`,
`stlport_narrow_streambuf_uflow.cpp` and
`stlport_narrow_streambuf_xsputnc_vendor.cpp`.

The initial supported merge trial rejected all three fragments: private
char_traits/fpos declarations collided with iosfwd, and full vendor streambuf
headers collided with the destination's retail-compatible locale view.
The earlier 2026-11-04 queue handoff records the same class-header boundary.
This prerequisite makes the fragments include the destination's existing
FILE-backed view. Protected default declarations now carry their existing
ledger signatures, including the fpos<int> seek results. The FILE helpers
use the same pointer/count operations as the vendor definitions.

The write loops retain vendor min's `b < a ? b : a` expression in a shared
TU-local helper. Reusing the destination read loop's inverse comparison shape
changed stack allocation/comparison bytes; it was rejected and corrected.
No vtable is emitted by this view, and the destination's link-wide constructor
alternatename is retained unchanged.

Verification before consolidation:

- `./build.sh` over the four sources: 25/25 functions match, including the
  two EH funclet pins; string, float and import checks pass.
- `find_declared_unmatched.py` over all four: no unrowed definitions.
- `link_check.py`: four units link locally, 986 -> 986 bytes against the
  2026-11-05 05:17 census at `c95fcfcfcd`. This is a prediction, not a new census.
- Saved pre-edit objects and compared COFF definitions, references, weak names,
  directives and relocation-aware COMDAT fingerprints. The destination's
  complete object symbol/COMDAT inventories are unchanged. Every represented
  game body in the fragments keeps its fingerprint. Full vendor headers'
  redundant locale startup references disappear from uflow.
- Nine auxiliary external inline definitions disappear from these fragments.
  Actual objects outside this scope still provide equal symbol/COMDAT digests:
  min<unsigned> (3), FILE_I_avail (7), FILE_I_bump (7), FILE_I_next (12),
  FILE_I_postincr (6), FILE_O_avail (4), FILE_O_bump (3), FILE_O_next (6),
  char_traits<char>::eof (2). New FILE-view inline spellings have the same
  bodies as their vendor counterparts. These are helper bindings, not renamed
  retail identities.
- Narrow searches of the gate, code-identity, data, header, MS-header and
  duplicate registers find no donor debt. Only the retained destination
  alternatename is keyed in the hatch register. No debt is retired.

The supported planner was regenerated under WWLib after source edits. Its
original-path alternatives include rendobj.cpp/nullrobj.cpp, both explicitly
marked investigation-only, incomplete and stale-map-blocked. Those are not
merge approval. The merge engine instead rebuilds the current TU map in
memory: all three clean donors are approved for StdioStreambufBase.cpp, and
the final dry run accepts all three with no rejection and a census link guard.
The mixed narrow_istream, wide_streambuf and wide_string sources remain out
of scope. No regenerated TU map is committed.
