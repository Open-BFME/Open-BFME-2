# Actual prefix fields before native class adoption

Replace the local opaque[0,B0) byte prefix with its14independently established
canonical fields. This restores the actual Image/scalar/mask member model;
B0/C8/CC/D0/D4 and the existing54-byte provider remain unchanged. Global mask
and string defaults, native layout/storage guards and the shared header stay
unchanged. Private21-row/full37-node controls are equal; ordinary whole429-code/
3-data and16-source link checks pass. This is a source prerequisite, not an
adoption verdict or completed queue unit. The previous native storage refusal
is preserved. Its complete-primitive-storage guard intentionally cannot approve
the old aggregate-containing opaque representation. No guard exception, hand
header swap, manual queue retirement, field-name trick or checker edit is used.
The ordinary private objects have no.debug$T stream; the unrelated preexisting
layout cache is explicitly not a current receipt. Native class adoption must
still obtain its own complete current layout, structural, byte and link proof.
