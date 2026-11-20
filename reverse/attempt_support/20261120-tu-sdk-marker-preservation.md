# Preserve selected SDK context when a declaration is discarded

During the texture consolidation, compose() could discard a private class
and the compiler-selector comment attached to it. Losing an existing
`// platformsdk` or `// dxsdk` changes the real native include roots; a valid
guiddef.h include can then fail before byte or provider comparison.

This is conditional on which declaration composition keeps. An include
preceding the comment or a prior canonical-header adoption can change which
chunk owns it. It is not a claim that all merges dropped their SDK context.

The repair extracts only existing bare SDK markers and emits their union
once in the generated compiler header. Their old chunk positions are removed.
It introduces no SDK selection for a source set that supplied neither marker.
STLport, optimization tokens, region/override selection, map/claim checks,
byte comparisons and provider/link guards retain their existing behavior.

The original code fails 17 regression subcases. New coverage exercises both
SDKs, seed and donor placement, every composition strategy and ordinary prose
that must not select an SDK. A real MSVC7.1 positive control compiles a
composed guiddef.h body; removing its marker produces C1083 and the expected
missing include directory in the ordinary compiler environment.

Root validation: `python3 -m unittest discover -s tools/tests -p
test_tu_skeleton.py` passes all 403 tests, including these native controls.
This tooling repair is committed separately from any game-source change.
It does not itself complete the texture merge or establish runtime progress.

Private reproductions and original-versus-proposed logs are retained under
diagnostics/continue-20261120-body-recovery-1656/agents/thing/ as
sdk-original-tests.log, sdk-patched-tests.log and sdk-marker-tool-handoff.md.
