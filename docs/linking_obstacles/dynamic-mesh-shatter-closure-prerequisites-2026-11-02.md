### Dynamic-mesh / shatter closure prerequisites (2026-11-02)

Unchanged scope, banked boundary: original normal checks pass dynamesh's
four rows (113 B) and shatter's Scale row (133 B). Two unrowed dynamesh
providers have actual current Process_Clip_Pools callers, so they cannot
be dropped alone. Shatter's primary providers have no outside indexed
consumers. Connected reduction needs a Scale(float) declaration in the
canonical storage header, whose class is held; no shared header was edited.
Dynamesh's native +0xA4 indexed read also differs from canonical Material
at +0xA8: donor API/index identity remains unproven, with no guessed fix.
Evidence and concrete next checks:
reverse/attempt_support/dynamesh-shatter-closure-boundary-20261102/.
