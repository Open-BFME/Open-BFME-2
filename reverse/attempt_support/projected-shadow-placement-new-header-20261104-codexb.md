# Projected-shadow placement-new header trial

Scope: `Code/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DProjectedShadowManagerRva0010C2D5.cpp`, retail RVA `0x0010C2D5`, 675 bytes.

The Microsoft-header queue identifies the local placement `operator new(unsigned int, void *)` definition. Replacing that definition with `#include <new>` was tested with `./build.sh` and rejected by byte verification. The trial emitted an `__EH_prolog` call, exception-state stores around placement construction and a larger stack frame; retail uses an ordinary EBP frame without that cleanup. The VS2003 `<new>` header declares matching placement delete as well as placement new. This provides a structural explanation for the additional cleanup, rather than evidence that the local declaration can simply be removed. `<new.h>` also declares matching placement delete, so changing only that header spelling is not a supported fix.

The original source was restored, and `./build.sh` again passed 1/1 matched rows, string references, one float literal and import references. No header-queue row was retired and no reconstruction was left in `Code/`.

Next step: reconcile construction and exception specifications using retail evidence before retrying the Microsoft-header migration. Do not suppress the generated cleanup through compiler flags or private header guards merely to preserve bytes. This trial did not measure linking or census progress.
