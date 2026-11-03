## Investigation-specific validation limitation

The initial investigation preserved a pre-existing BFME 1 checkout at
`f5140c1cff6a58e16276fd6de6788186286953d4`, while BFME 2 pinned
`0bf534ea7ccde110c456edb9cd2dd5dae823c953`. Fetching the provider index succeeded,
but normal object import refused that mismatch. No check was bypassed and no
fresh local compile-based preview was claimed. This is a local input limitation,
not evidence that other agents or the whole repository are blocked. Use a
consistent verified checkout before taking new compile-based measurements.

The graphics follow-up above used a separate checkout with the pinned reference
and completed ordinary compile-based verification. The original checkout was
preserved; its mismatch did not block that isolated check. LINK-008 records the
separate strict receipt limitation encountered there.
