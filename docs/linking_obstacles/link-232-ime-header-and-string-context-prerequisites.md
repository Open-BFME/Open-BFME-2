### LINK-232: IME canonical callers and remaining string contexts

Status: Partly repaired; seven native header keys retired in this batch.
Inspected source commit `f0c2f61662b68c1df44a6a38005f50a8eed00328` after rebasing onto `bdbd14858ab62aa1e387ca79bcffddbe448b983c`.

Completed: the owning IME implementation and six caller projections use the
same existing header. Its full0x3064-byte layout and32-slot order are proved
from the target allocation/constructors/tables. All214 old code/EH rows,254
external code instances and code/data/relocations remain. The owner preserves
the old inline interface destruction and14-slot base context. Two sources
only repeat already-active canonical ASCII alias directives; no effective
alias mapping or shared header changes.

Remaining at inspection: ['Code/GameEngine/Source/Common/AptOnlineLogin.cpp', 'Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptMessengerCallbacks.cpp', 'Code/GameEngine/Source/GameClient/GUI/Shell/Shell.cpp'].
The initially held AptOnlineLogin source was never edited. AptMessengerCallbacks
still needs its changed object-section ordering reconciled. Shell needs a
supported composition with its existing private string/CharSource views;
the native sweep include setup was reproduced and is not the remaining cause.
Original failed-source bytes and owning keys are preserved.

[Seven-source evidence](../../reverse/attempt_support/ime-class-batch-20261104-1242.md).
[Affected-consumer audit](../../reverse/attempt_support/ime-consumer-audit-20261104-1242.md).
No full-image link or runtime/allocator improvement is established.

Native affected-consumer result: INCONCLUSIVE; closure remains unverified.
