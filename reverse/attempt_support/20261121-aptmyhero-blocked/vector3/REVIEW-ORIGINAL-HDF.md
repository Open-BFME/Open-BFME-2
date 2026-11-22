# Review of the stored original HDF and receipt

Reviewed OLD=../aptmyhero-vector3/HANDOFF.md, NATIVE-RECEIPT-COMPACT.json,
MANIFEST.json and the complete strict diff. Original files stay immutable.

Root's tracked copy should open with CORRECTION.md or an explicit equivalent
notice, and reference both copied evidence JSONs by name.

- Original HDF85-87: replace "real const subscript returns float" by "the current
  canonical model returns float; the placed leaf has a scalar x87 value return;
  its original Vector3/const identity is not independently caller-bound".
- Original HDF109-111: replace "old wrong-ABI"/"real by-value" labels with
  "seed reference-returning signature"/"current canonical value-returning signature".
  Preserve the observed removed/added COMDAT names and all raw size comparisons.
- Original HDF99: qualify the broad no-mismatch sentence to the observed target's
  resolved/unmasked callees and the examined object context. It does not establish
  the independent original class identity of the tiny unrelated leaf.
- Keep original42/43,971B,24 differences,19 relocations, changed wrappers, actual
  data/undefined footprints and auxiliary12-unwind-metadata limitation unchanged.
- Keep FactCanonSort as a hypothesis about the compiler mechanism, not an observed
  compiler IR/pass fact. The raw SSE instruction and addition-group differences
  are directly observed.
- Original compact JSON's raw names/hashes/counts need no invented replacements;
  attach the correction to their interpretation. It stays labeled ORIGINAL.

ROOT-RECORD-600.txt is a reviewed plain-language draft under600 characters for
Root's normal no-change record, not a log mutation. Root supplies its own actual
CLI metadata. No interface/row/header/gate fix is recommended or present.
