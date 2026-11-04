# AptActionInterpreter Microsoft-header cleanup

Inspected revision: 404f9196898c6788e357f89a1a135c93a368bee1.
Scope: Code/Libraries/Source/Apt/AptActionInterpreter.cpp.

Removed five bodyless local declarations: fmod, strlen, strcmp, fabs and
strcpy. The unit already includes the real string.h and math.h; their
intrinsic pragmas remain. Supported ms_header_audit scan --write-queue
refresh reduces its reported occurrences from 11 to 6. No debt baseline,
ledger identity, compiler flags, pin or linker alias changes.

Verification:

- Unchanged baseline and final source: ./build.sh reports 101/101 matched;
  141 literals plus 3 empty strings, 2 compiler float literals and imports pass.
- Separately rebuilt baseline/final COFF objects: all 142 external COMDAT
  definitions retain identical byte-and-relocation digests, using
  link_census._comdat_sections; no added or removed external COMDATs.
- find_declared_unmatched reports all definitions already matched;
  ms_header_audit check passes.

Remaining occurrences were tested and retained deliberately:

1. Adding stdio.h and deleting only the two sprintf declarations, on top of
   the final cleanup, fails rva006FD4C0 (0x006FD4C0, 233 bytes) and rva006ff980
   (0x006FF980, 682 bytes). Calls become indirect IAT calls instead of retail
   direct thunk calls. The changed parent also makes uw_007aa420 ambiguous.
2. Adding ctype.h and deleting only isalnum fails rva006FD4C0. The header
   classification expansion changes the matched body.
3. Adding new.h and deleting only the inline placement new fails callFunction
   (0x00706660, 742 bytes); 100/101 rows still match. The real header adds a
   matching placement delete, so placement construction gains EH setup and
   cleanup absent in retail (SEH prologue replaces the simple prologue).
4. The initial full-header trial also removed both strncmp declarations.
   bfmeHasPrefix8C5680 (0x006FD790, 50 bytes), GetUrl and GetUrl2 then fail:
   direct E8 calls to the strncmp thunk become FF15 IAT calls. The prefix
   function has no sprintf, isalnum or placement construction, so its failure
   isolates that direct-call ABI requirement. string.h was already included;
   deleting its later local redeclarations changes the import attribute.

These failed replacements were reverted. Further cleanup needs an evidenced
header/call configuration preserving retail's direct calls and its lack of
placement-delete cleanup. Do not blindly repeat the drop-in substitutions.
No census or real-link gain is claimed.
