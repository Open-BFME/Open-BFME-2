### ShipSlowDeathBehavior constructor composition: destructor and interface providers

Status: Blocked on native destructor identities and complete virtual interfaces.
Updated 2026-10-29; inspected `5eb27ead8e`, index `85f6b7f40c` (15:08).
A real shared-view constructor preserves 9/9 paired rows after correcting
ModuleData's class key. Explicit destructor declarations remove a wrong
implicit UpdateModule destructor, but the constructor then references the
unprovided ShipSlowDeathBehavior destructor and BehaviorModuleInterface::slot0;
ordinary preview loses its 74 authored bytes. The 13-slot primary table and
secondary interfaces need reconciliation with the existing placeholder-owned
destructors at 0x0045EA3F/0x0045ED2F and base 0x0045D39E before composition.
All source trials are restored; 9/9 rows and paired LINKS 907 -> 907 bytes
are reverified. No source move, debt retirement or census gain is claimed.
[Exact trial, verification and next prerequisite](../../reverse/attempt_support/ship-slow-death-constructor-20261029/README.md).
