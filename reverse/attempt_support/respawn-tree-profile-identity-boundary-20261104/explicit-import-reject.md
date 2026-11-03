# Explicit native `_strcmpi` import follow-up

The authorized post-header redeclaration is rejected by the compiler in both requested contexts. It does not produce a usable prerequisite or merged object.

Exactly two sanctioned Verifier trials ran, reusing the measured frozen `9a47cdf7b0` controls:

1. The 24-row seed alone, with the exact existing tree profile and seed-first include union.
2. The 32-row supported `union-first` composition under that same profile.

The only source addition in each case, immediately following its existing `#include <string.h>`, was:

```cpp
extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *, const char *);
```

Both compile attempts stop at that line with:

```
error C2375: '_strcmpi' : redefinition; different linkage
```

The remaining errors are consequent C3861 `_strcmpi` lookup failures in the parser bodies. Neither trial emits an object. Therefore no row match, provider/property/route identity, EH proof or LinkGuard judgment is asserted for this follow-up. No alternative declaration placement, header configuration, calling convention, pragma, import suppression or check change was attempted.

The earlier measured profile boundary remains the last successful evidence: seed flags match 28/32 and tree flags match 30/32. Native direct tree `_free` and native imported parser `_strcmpi` require compatible declaration contexts; this particular ordinary post-header redeclaration cannot supply them. Root's later canonical INI/filter/parser changes were not included in these frozen inputs and require fresh owning verification if investigated.

Full input snapshots, source hashes, effective profile and errors are in `explicit-import/proof.json`, beside both candidate `.cpp` files and the harness. No tracked edit, normal build/cache mutation, claim, network or publication occurred. All tracked/native reads are stopped; no additional trials are planned.
