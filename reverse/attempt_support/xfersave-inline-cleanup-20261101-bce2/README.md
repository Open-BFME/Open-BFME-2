# Restore the visible string cleanup needed by XferSave composition

Base `beb5b0e494a`. Remove only the seed's declaration-only specialization of
`basic_string<char>::~basic_string`, restoring STLport's existing primary
body. No replacement instruction body, compiler flag, pin or alias is added.

The supported merge had compiled Rva0060D269 as 121 instead of 128 bytes:
its cleanup called an outlined string destructor where retail null-checks
and frees the string inline. With the primary body visible, the supported dry
run accepts the seed plus Rva0060D269.cpp, all 22 combined rows exact, and
its link guard passes. Seven other clean donor candidates remain rejected;
the mixed/refused files remain out of scope. Application is a later commit.

The standalone seed passes all 19 rows, strict preparation, two EXACT EH
graphs and frozen checks, retaining ordinary LINKS/1,156 bytes at 0d24c60eef.
All 157 retained external section bodies/relocation shapes are unchanged
after qualifying three existing list-helper references from the string
destructor to its base destructor. Their existing 14-byte native bodies at
7FAB3 and 142D70 are byte/relocation twins targeting engine free at 30830;
the latter's existing pin carries registry.cpp fold proof. No new fold is
admitted by this change.

Two generated inline copies appear in the standalone seed: a five-byte string
destructor forwarding to the base, and a one-byte no-op character destroy.
The latter has no incoming code edge. The former has local incoming calls;
do not describe both as locally unreferenced or as new native-exact bodies.
The bounded index/current-order preview retains the previous outside string
provider (stlport_locale_global.cpp) and the standalone seed still LINKS.
This does not establish complete current-object consumer closure. Adjacent
proof lists all incoming edges and qualifies the index-derived observation.

The change is a separately verified composition prerequisite. It makes no
source-file, census, new-C++ or registered-debt claim on its own. The final
merge must reverify the combined object and its provider selection under the
ordinary source-move guard and outgoing batch audit.

## Resume verification, 2026-11-02

Replayed the single declaration cleanup on base `0b27baa36db`, preserving
upstream's canonical XferException header adoption. Current seed passes
19/19 rows, strict preparation and two EXACT EH graphs. The ordinary preview
retains LINKS/1,156 bytes against the 2026-11-02 08:35 census at 984a4cdc4d.
The current supported composition again accepts the seed plus Rva0060D269,
22 rows, with its link guard; all seven other donor prerequisites remain.
The original object comparison below is historical evidence from November 1;
it is not a current full consumer audit. Actual guarded application follows
in a separate commit. Current raw receipts are alongside this note with the
`resume-` prefix. No new recovered bytes are claimed.
