### LINK-592: AICommandParms dispatcher private parameter view
Status: Cleared for AICommandParms adoption in AIUpdateInterfaceAiDoCommand.cpp; updated 2026-11-05, inspected 69591b5f6e.
The dispatcher now uses the existing parameter header: one header-queue row retired, 1/1 byte match, link prediction unchanged at 2,306 bytes. Other AI interface and parameter-vector adoption prerequisites remain outside this scope. [Evidence and next checks](../../reverse/attempt_support/aicommandparms-dispatch-header-20261105-codexb2.md).
Census confirmation: awaiting; no new measurement claimed.

2026-11-08: cleared for AICommandParms adoption in AnimalAIUpdate.cpp too.
Its existing inline 15-byte destructor now uses the canonical coordinate
start, preserving native buffer cleanup and EH while removing the two
private parameter/vector structs. All 15 source rows and three EH graphs
remain exact; one header queue row is retired. The only omitted provider,
the 14-byte RvaCoords destructor, retains strictly current identical copies
in the next census provider and the default real-link path provider.
Paired checks pass and preview preserves LINKS/3,167 bytes against
c885072a48. AI interfaces, the full Animal class, TU consolidation and
current-image/runtime closure remain open.
[Body and provider evidence](../../reverse/attempt_support/animal-command-parms-adoption-20261108/README.md).

Published as 2058c08f50 on attempt3 (28.7 seconds for the successful
attempt). Required checks pass; the broader audit remains INCONCLUSIVE
against c885072a48 because Animal lacked a current strict receipt after
rebase. No current-image closure is claimed.

Later on 2026-11-08, Animal's AICommandInterface and AIUpdateInterface
header debts are also cleared with all 15 rows and three EH graphs exact.
The complete Animal class and TU merge prerequisites remain; LINK-181 and
the Animal AI interface packet record that narrower receiver repair.
