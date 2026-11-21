# Constructor initializer field ownership

The original native Tracker adoption refused a field in its constructor
initializer as file scope. The separately reviewed tools now read only bounded
ordinary constructor lists, structural receiver separators and explicit pointer
member definitions. The declaration reader is unchanged. A token rename must
equal the complete scoped rewrite; real globals, shadows, unknown or foreign
receivers, malformed/nested/default expressions and incomplete macro/include
provenance stay refused.

The new constructor exception captures the actual ordinary command, flags and
complete current include input twice. Unproved macro/scope expansion, FF/VT and
bare CR are conservatively held; LF and CRLF remain supported. V1/V2 review
counterexamples are regressions. The 1166 required tests and 113 subtests pass;
six existing environment/fixture skips are retained. Root repaired one accidental
em-dash comment encoding change and proved the full Python AST unchanged from
the reviewed/tested V3. No game source, SDK, contract, queue key, baseline, pin,
emission rule or checker requirement was changed to force a game pass.

Actual Tracker syntax is proved, but its full macro-owner context remains
unproved. Root must run normal adoption, source/lifetime/layout/identity/byte
checks and provider/link closure separately. This tools-only commit earns zero
body or task credit; the original false-reject attempt record stays with its
later source/blocked-result change.
