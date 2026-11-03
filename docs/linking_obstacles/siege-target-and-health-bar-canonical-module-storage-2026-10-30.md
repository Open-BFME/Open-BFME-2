### Siege target and health-bar canonical Module storage (2026-10-30)

Cleared only for InGameUISiegeDeployTarget and DrawableHealthBarGate: use
canonical Module8 with partial derived storage preserving the native dock
receiver at +0x20 and UpgradeMux receiver at +0x24. Native callers and the
existing raw-return lookup owners independently establish both offsets. Keep
the interface and lookup prototypes. All six source rows, the siege EH graph,
21 external code definitions and every non-debug section/reference are
unchanged in fresh private and strict-current final objects. The owning tool
retires two Module keys; ordinary previews retain LINKS/451 and 472 bytes
against ccafe54d1d. Complete derived hierarchy and other class/header debts
remain separate; no census or runtime gain is claimed.
[Siege evidence](../../reverse/attempt_support/module-ui-siege-dock-20261030/README.md),
[health-bar evidence](../../reverse/attempt_support/module-ui-health-interface-20261030/README.md).
