# INI lookup parser: native C++ exceptions

Base `2808663ede`, 2026-10-26. The claimed whole source is
`Code/GameEngine/Source/Common/System/INI_scanLookupList.cpp`.
Its sole matched body is `INI::scanLookupList`,
`0x0002BD85..0x0002BDF1`, 108 bytes.

The preceding consolidation rejected this donor because its artificial
default-constructed `INIException` did not agree with the seed's real exception
declaration. The source manually invoked the variadic constructor and
`_CxxThrowException`, passing a zero-filled throw-info anchor.

Retail has two error paths: a missing/empty lookup table and an unsuccessful
case-insensitive lookup. Both construct the exception in the same eight-byte
stack slot and join the throw tail at `0x0002BDE3`. The successful lookup returns
the adjacent integer without constructing an exception.

The reconstruction now expresses both failures as ordinary
`throw INIException(...)`. Its class declaration retains the native two-member
layout and the existing constructor/copy/destructor ABI used by INI.cpp and
INIExceptionCtor.cpp. The artificial default constructor, explicit throw-runtime
declaration, direct runtime calls and zero-filled anchor are removed. The name,
row boundary, lookup loop, error codes, format strings and compiler flags stay
unchanged. No new pin, alias or counted hatch is introduced.

Verification:

- Normal whole-file build before and after: 1/1, all 108 bytes exact.
- Both format literals and the `_strcmpi` import verify; frozen-file checks pass.
- Code identity: three references, all owner bindings, zero wrong bindings.
- Data check: zero findings. EH verification has no EH-frame rows for this
  function, as expected; this is not a claim about a new full-image run.
- Ordinary preview against `763dc8759f` remains clean, 108 -> 108 authored bytes.

Logs: `build/codex-cleanup-20261025/iteration19-lookup-{before,after,identity,link}.log`.
This replaces manual exception machinery with verified C++; matching coverage
is unchanged. A new composition trial must still prove the donor can be absorbed.

The preceding merge's normal full commit gate completed successfully:
98,252 function rows, 2,216 data rows, all reference checks, the no-op image and
converged-data enforcement over 23,033 sources. A follow-up flag proposal proves
the inherited SSE override is still needed for two INI rows. Its measurement
count will be refreshed once for the final consolidated TU; no override is
retired by this parser change.
