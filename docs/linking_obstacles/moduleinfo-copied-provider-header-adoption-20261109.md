### ModuleInfo copied-flag provider needs canonical header adoption

Status: this provider/consumer adoption verified; wider class recovery open.
Updated:2026-11-09; inspected revision:a3623130cb.

ThingTemplateSetCopiedFromDefault.cpp adopts ModuleInfoClass.h while retaining
the real67B setter as an inline out-of-class definition with unsigned loop
semantics. Three rows, one exact EH graph and the LINKS306/306 preview pass
against index5b5011469d. The setter's selection policy and ten retained COMDAT
payloads are unchanged. Only the unused size getter becomes the identical
canonical getCount copy, matching all six indexed providers.

Owning acceptance retires one ModuleInfo header row, leaving28 locally and no
header queue key in this file. [Native facts and provider/consumer evidence](../../reverse/attempt_support/moduleinfo-copied-provider-header-adoption-20261109.md).
Other ModuleInfo views/lifetimes remain separate. The previous broader audit's
AICowerState_onEnter.cpp receipt gap is carried forward; census/image
confirmation is pending, with no new runtime result claimed.
