# Projected-shadow pair header adoption

Inspected revision: `72e402b4e1`, 2026-11-04.

Target facts: `W3DProjectedShadowManagerRva0010C145.cpp` defines the
namespace-scope `Rva000B3F84Pair` with an empty constructor, pointer at +0 and
integer at +4, like `Code/GameEngine/Include/Common/Rva000B3F84Pair.h`.
The private definition's closing brace and semicolon occupy separate lines.
The frozen-file check passes; its seven matched rows remain unchanged.

`header_adopt_lane.py adopt --class Rva000B3F84Pair --header
Code/GameEngine/Include/Common/Rva000B3F84Pair.h
Code/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DProjectedShadowManagerRva0010C145.cpp
--apply` refuses with `no private view found` before compilation or mutation.
`class_layouts.class_body_spans` finds `(Rva000B3F84Pair, 4430, 4522, class)`;
`header_adopt_lane.body_span` returns `None` because its tail pattern permits
only horizontal whitespace before the terminating semicolon. This is a parser
false reject, not layout or byte evidence against adoption.

Next check: teach the adoption span parser to accept C++ whitespace before
the semicolon, preserving refusal of declarators and incomplete definitions.
Then retry ordinary adoption, byte/EH verification and queue acceptance.
No header debt is retired by this report.

Consolidation context: the scoped evidence planner surveyed 57 shadow files,
with 14 files and 56 static blockers in this destination's investigation group.
The committed TU map is stale; the merger rebuilds it in memory. The broad
merge dry run was interrupted after about twenty minutes during compiler-flag
screening, without a final verdict or tracked changes. No merge or file-count
gain is claimed. Temporary trial sources were removed after stopping the trial.

## Parser repair

The span tail accepts ASCII C++ whitespace before the terminating semicolon.
Regression tests reproduce the original refusal for LF, CRLF, blank lines,
vertical-tab/form-feed and a comment between the brace and semicolon; all five
failed before the fix. Four negative cases still refuse declarators or a
preprocessor directive between the brace and semicolon. The actual donor span
is now `(4430, 4525, class)`.

`python3 -m pytest -q tools/tests/test_header_adopt_lane.py
tools/tests/test_gate_exploits.py`: 213 passed, 1 skipped. No game source or
header-queue row changes accompany the parser fix.

## Downstream false reject

After the span repair, the same adoption command refuses with `field renames:
Rva000B3F84Pair: unterminated definition`. `tu_views.class_span` independently
requires horizontal whitespace between the closing brace and semicolon. The
source and header queue remain unchanged. Repair this second parser with the
same valid-whitespace and invalid-declarator boundaries before retrying adoption.

The downstream parser regression tests reproduce all five whitespace failures
before the repair and retain four negative declarator/directive cases. After
the repair, `test_tu_views.py`, `test_header_adopt_lane.py` and
`test_gate_exploits.py` pass together: 251 passed, 1 existing skip and 9
subtests passed. No layout, byte or link check is bypassed.

## Adoption and acceptance

Ordinary `adopt --apply` passes and replaces only the private Pair body with
the canonical header include. `header_adopt_lane.py accept --class
Rva000B3F84Pair --header Code/GameEngine/Include/Common/Rva000B3F84Pair.h`
on this unit passes its byte and link-prediction checks and retires exactly one
row from `reverse/header_queue.tsv` through the queue's supported path.

`./build.sh` on the unit passes 7/7 matched functions, four funclet pins,
one string literal, six empty-string references and one compiler float literal.
`eh_verify.py` reports one EH row EXACT, zero baseline entries and no missing
objects. `find_declared_unmatched.py` reports all defined functions matched.
No source path, function row, pin or alias changes; no census gain claimed.
