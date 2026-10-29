# AptTimeLine consolidation, 2026-10-29 (claudeb)

Destination: Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/
AptTimeLine.cpp, the approved TU in reverse/tu_map.csv (157 approved rows).
Supersedes the open questions in apttimeline-consolidation-20261028.md.

Landed before the merge, each in its own verified commit:

- 12 superset class views shared across the TU's files (tools/tu_views.py).
- One CRT import preamble for the seed and AptTimeLineCallbacks: `<stdlib.h>`
  and `<stdio.h>` are included first under a dllimport `_CRTIMP`, then
  `_CRTIMP` is emptied again. Under `/D_CRTIMP=` a later plain redeclaration
  silently drops an earlier explicit `__declspec(dllimport)` (atoi became a
  direct `e8` call); the reverse order is error C2375.
- Rva0051E437 as one public class with short fields, and the
  Rva0051E716Range<T> begin/end view used by the E96B and E9D2 getters.
- The seed lists `/Ireference/shims/bfme2_ascii` first, so UnicodeString
  resolves to BFME 2's view (RenderGraph's `concat`), and
  `enum ScienceType { SCIENCE_INVALID = -1 }` matches the donors. The composer
  keeps one copy of an identical declaration; differing copies drop one side.

The merge absorbed Rva0051E437Copy, Rva0051E939Copy, Rva0051E96BGetter,
Rva0051E9D2, AptTimeLine_Rva0051E511, AptTimeLineRenderGraph and
AptTimeLineRva0051E766 (66 rows).

Remaining whole-file donors, all rejected by `--merge --dry-run`:

- AptTimeLineCallbacks.cpp: its AptTimeLine, AptTimeLinePlayer and
  GameTextInterface views now equal the seed's (commit "AptTimeLine: share
  the ... views with the callbacks"). GameTextInterface declares
  `fetch(const char *)` before `fetch(const AsciiString &)`: MSVC places
  overloaded virtuals in reverse declaration order, giving +0x38 (AsciiString)
  and +0x3C (C string) as both files' callers need. Composed with the seed it
  now compiles under the "first" strategy and judges 80 of 81 rows; the miss is
  PlayerFaction 0x0051EC4E, which matches only under the donor's `/GF-`
  (re_attempts.log: five source shapes all keep one pooled "" in EDI under
  /GF). Adding `/GF-` to the seed loses RenderGraph 0x0051EED7,
  rva0051E766 0x0051E766 and their seven unwind funclets, so one TU flag set
  cannot hold both until one side's real source shape is found. Retail pushes
  0x00BBAC1C for both "" uses, which suggests pooling, so PlayerFaction's
  shape is the likelier one to be wrong.
  The dry run reports this as an empty `compile: ` because attempt() keeps the
  first strategy's verdict ("union-first" fails: it places
  `Rva005202C8 *Rva005202C8::s_instance;` before the class) while the error
  list comes from the last strategy, which compiled and missed bytes.
- STL-faking donors define their own `_STL::allocator`, vector,
  `__false_type` or `_STL::free`: Common/Rva0051ECC3Copy, Rva0051ED0ACopy,
  Rva0051ED51AllocateCopy, Rva0051F6DFFinish, WWLib/StlSweepR3Rva0051F7AD,
  WWLib/Rva00520211ElementDtor. They need rewriting against the real STLport
  headers; their invented class names (e.g. `??0Rva0039C151@@QAE@ABV0@@Z`)
  are vector instantiations, so the symbols change and the link audit must
  judge them.
- Rva0051F87B family (Common/Rva0051F87BAssign, F87BCopy, F87BCtor,
  Rva0051FFF5Feed, WWLib/StlportRecord80ResizeDefault): each donor's view of
  Rva0051F87B differs (fields m_04 vs storage under a vfptr, ctor presence).
  Needs one shared declaration first.
- WWLib/StlportVectorOverflowRva00520211.cpp: Rva00520211Element is declared
  only by the STL-faking Rva00520211ElementDtor donor.
- AptTimeLineRva0051FCA2.cpp: declares `class AptTimeLine :
  public _bfme_AptGameWindow` (the seed's view has no base), so tu_views
  cannot superset it and `rva0051FCA2` is missing from the composed class; it
  also needs Rva005248D0/m_commandMaps and its cl line carries `/O1 /G6
  /arch:SSE`.
- AptTimeLineRva00520CD1.cpp: `rva00520CD1` is missing from the composed
  AptTimeLine view; its cl line (`/O1 /G7 /arch:SSE /EHsc
  /D_STLP_NO_EXCEPTIONS`) differs from the seed's.
- AptTimeLineCollectPlayerData.cpp (`/G6`): AptTimeLinePlayer undeclared at
  its use point in the composed order; StlSweepW4Rva005205DA.cpp (`/Ob0`):
  bytes differ under the seed's flags. Flag differences are a likely cause of
  byte failures for both.

Debug aid: compose the seed with chosen donors through
tu_skeleton.compose (relocate_includes with repo-relative directories) under
each of tu_skeleton.STRATEGIES, then judge the rows with Verifier.matched and
build.compile_function to see every error and every missing row; the dry-run
log keeps only the first error and can mislabel a byte miss as a compile.

Rva0051F87B (copy 0x0051F87B, default ctor 0x0051FAFC, operator= 0x0051F972)
has AptTimeLinePlayer's 0x50-byte layout (UnicodeString +4, color +8, faction
+0xC, int +0x10, vectors from +0x14) with a vtable at +0; the two are likely
one record type. That is a structural inference from layout only, and the
Assign donor's `/O1 /G7 /arch:SSE` flags differ from the seed's.
