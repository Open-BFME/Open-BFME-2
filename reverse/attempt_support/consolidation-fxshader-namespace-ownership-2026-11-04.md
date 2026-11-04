# Ownership follow-up for FXShaderParameterSourceNamespaceWW3D merge (2026-11-04)

After commit `5f70027397` was handed to the fleet publisher, its pre-commit shadow check reported:

`tu_ownership [shadow] A2 0x001F45C3 ??_GSourceNamespace_Fog@FXShaderParameterSourceNamespaceWW3D@@UAEPAXI@Z: moved to Code/Libraries/Source/WWVegas/WW3D2/FXShaderParameterSourceNamespaceWW3D.cpp; approved TU is Code/GameEngine/Source/GameClient/System/ParticleSys.cpp (C)`.

Current `reverse/tu_map.csv` assigns `0x001F45C3` to `ParticleSys.cpp`; before the merge the same matched identity row was in `Code/GameEngine/Source/Common/Rva0018BEC7Ctor.cpp`, alongside the constructor donor rows. The accepted mechanical merge carried it to the new namespace TU, which is not the approved owner. The ownership check is currently shadow mode, but the upstream rule still requires the approved TU. This seat must not hand-move it or alter the TU map. A contributor authorized for ownership repair should reconcile it through the approved TU workflow. The merge commit is already handed to the fleet publisher and must not be amended, rewritten or dropped. Its claims remain held pending landing: file claims on `Rva0018BEC7Ctor.cpp`, `FXShaderParameterSourceNamespaceWW3D.cpp`, and the rejected Common donor, plus row claims from the merge scope.
