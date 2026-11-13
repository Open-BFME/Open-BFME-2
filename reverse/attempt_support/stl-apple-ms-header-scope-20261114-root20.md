# Apple MPW header is not a Windows CRT migration (root20, 2026-11-14)

The default picker served vendor/stlport/config/stl_apple.h, identifying its
`typedef int wint_t` as a Microsoft ctype.h ABI conflict. The file explicitly
configures Apple MPW MrCpp/SCpp, includes ConditionalMacros.h/Types.h and uses
Apple compiler __option expressions. stlcomp.h selects this branch for __MRC__
or the corresponding __SC__ version, separately from the Microsoft compiler
configuration. Its int carrier is a platform contract, not evidence that an
active BFME Windows translation unit privately copied Microsoft's wchar type.

No vendor edit was made. find_declared_unmatched reports no unmatched bodies.
The supplied pass test ./build.sh vendor/stlport/config/stl_apple.h exits1:
"Source claims: OK (0 sources, scoped byte-verified)" and "no functions match".
This establishes that the served pass test has no function scope; it is not
an exhaustive include-reachability proof or a successful migration.

Do not replace the type with the Microsoft definition, insert Windows headers
into this Apple configuration or delete its queue row by hand. The audit/picker
needs supported target/consumer scope evidence before serving such a vendor
platform file. A safe correction must preserve existing active Windows findings
and unknown-configuration failures. No checker/baseline change or new analysis
exception was attempted here. This is a false-alert/scope handoff, not a byte,
link, game-runtime or cleanup result. Baseline log: build/root-stl-apple/baseline.log.
