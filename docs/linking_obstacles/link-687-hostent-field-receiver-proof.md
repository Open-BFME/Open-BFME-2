### LINK-687: hostent adoption needs receiver-bound field proof
Status: Blocked. Updated: 2026-11-17; inspected revision: 77e8eb27d71.
Evidence / affected unit: Code/GameEngine/Source/GameNetwork/NATUpdateBfme.cpp, canonical Common/hostent.h; [exact refusal and boundary](../../reverse/attempt_support/hostent-field-rename-refusal-20261117-root20.md).
Completed: owning adoption reproduces the unused length/basic_string collision; no Code/header/ledger/queue changes. Defined functions already matched.
Remaining / next check: separate verifier correction must establish unused-field nonuse and safe receiver binding inside a call's comma-separated argument list without accepting ambiguous operator/shadow/macro cases; then retry normal whole-file gates and owning queue acceptance.
Clearance: none; no current real-link or game-runtime change.
