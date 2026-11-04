### StateMachine destructor CRT header changes tree teardown
Status: Blocked. Updated: 2026-11-04; inspected revision: `6fbd44876f`.
The plain CRT-header substitution passes all six rows but changes the emitted tree destructor; preview loses 171 linking bytes. Trial reverted; original retains 171/171 bytes. Next: preserve throwing game-allocation teardown before replacing the local free declaration. [Evidence](../../reverse/attempt_support/statemachine-dtor-crt-header-20261104-codexb5.md). Census confirmation: not claimed.
