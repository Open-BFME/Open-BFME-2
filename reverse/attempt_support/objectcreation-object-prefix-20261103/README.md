# ObjectCreationUpgrade seed/check prefix reconciliation

The seed and its check donor already used non-inheriting partial Object views.
They now share the union of their existing direct-call declarations and the
check donor's existing mask storage at+0x284. The seed gains that mask type's
complete declaration. Existing names and native field offsets are retained.
This remains a partial view, without a complete-Object or original-layout claim.

All19 current rows pass private and normal verification. Every external code
and data definition of both objects is identical to its control. The native
mask-check functions, original seed functions, data and lifetime behavior remain.
No body or ledger row moves in this prerequisite commit.

The separate update donor already adopted canonical Thing. Its larger inherited
view and the ObjectCreationUpgrade/ModuleData class conflicts remain separate;
they are not coerced into this common prefix. The supported merge engine must
still approve, byte-check and link-judge any actual source absorption.
