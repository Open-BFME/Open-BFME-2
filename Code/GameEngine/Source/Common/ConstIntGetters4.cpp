// Cold-slice B8-imm32 const-int returners (twin-free TU).
//
// Same shape as ConstIntGetters2.cpp/ConstIntGetters3.cpp (mov eax,<IMM32> /
// ret, 6B) but kept in a separate TU so this lane does not contend with the
// hot ConstIntGetters appends on origin/master. Rows are opaque
// address-derived names: each body follows a ret-imm (C2-04-00 / C2-08-00)
// and is carried by .rdata vtable slots with no direct callers and no branch
// sources, so no class identity is witnessed. No // cl: line (defaults match
// the frameless 6-byte shape).

// The three Apt screen factories these getters return are matched rows.
void *__stdcall createAptScreenInGameChat(void *);
void *__stdcall createAptScreenObjectives(void *);
void *__stdcall createAptScreenQuickMatchMenu(void *);

// ?Rva0033F4ABGet@@YAHXZ @ 0x0033f4ab (6B): returns 0x00C1123C.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva0033F4ABGet(void)
{
	return (int)"AIAttackFireWeaponState";
}

// ?Rva0033F4D9Get@@YAHXZ @ 0x000033f4d9 (6B): returns 0x00C1129C.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva0033F4D9Get(void)
{
	return (int)"AIAttackPositionFireWeaponState";
}

// ?Rva0033F53AGet@@YAHXZ @ 0x000033f53a (6B): returns 0x00C1135C.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva0033F53AGet(void)
{
	return (int)"AIDeadState";
}

// ?Rva0033F565Get@@YAHXZ @ 0x000033f565 (6B): returns 0x00C113AC.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva0033F565Get(void)
{
	return (int)"AIDockState";
}

// ?Rva0033F590Get@@YAHXZ @ 0x0033f590 (6B): returns 0x00C113FC.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva0033F590Get(void)
{
	return (int)"AIHarvestState";
}

// ?Rva0033F5B3Get@@YAHXZ @ 0x0033f5b3 (6B): returns 0x00C11454.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva0033F5B3Get(void)
{
	return (int)"AIHordeEnterState";
}

// ?Rva0033F5DDGet@@YAHXZ @ 0x0033f5dd (6B): returns 0x00C114AC.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva0033F5DDGet(void)
{
	return (int)"AIHordeExitState";
}

// ?Rva0033F5FFGet@@YAHXZ @ 0x0033f5ff (6B): returns 0x00C11504.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva0033F5FFGet(void)
{
	return (int)"AIHordeExitAndMoveToState";
}

// ?Rva0033F621Get@@YAHXZ @ 0x0033f621 (6B): returns 0x00C11564.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva0033F621Get(void)
{
	return (int)"AIHordeExitAndFollowPathState";
}

// ?Rva0033F648Get@@YAHXZ @ 0x0033f648 (6B): returns 0x00C115CC.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva0033F648Get(void)
{
	return (int)"AIMeleeReAcquireState";
}

// ?Rva0033F676Get@@YAHXZ @ 0x0033f676 (6B): returns 0x00C1162C.
// Follows a ret-8 (prev C2-08-00), carried by 2 .rdata vtable slots,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva0033F676Get(void)
{
	return (int)"AIExitState";
}

// ?Rva0033F698Get@@YAHXZ @ 0x0033f698 (6B): returns 0x00C1167C.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva0033F698Get(void)
{
	return (int)"AIExitAndMoveToState";
}

// ?Rva0033F6BAGet@@YAHXZ @ 0x0033f6ba (6B): returns 0x00C116DC.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva0033F6BAGet(void)
{
	return (int)"AIExitAndFollowPathState";
}

// ?Rva0033F6FBGet@@YAHXZ @ 0x0033f6fb (6B): returns 0x00C11784.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva0033F6FBGet(void)
{
	return (int)"AIGuardState";
}

// ?Rva0033F71EGet@@YAHXZ @ 0x0033f71e (6B): returns 0x00C117DC.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva0033F71EGet(void)
{
	return (int)"AIGoingIdleState";
}

// ?Rva0033F745Get@@YAHXZ @ 0x0033f745 (6B): returns 0x00C11834.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva0033F745Get(void)
{
	return (int)"AIGuardRetaliateState";
}

// ?Rva0033F76CGet@@YAHXZ @ 0x0033f76c (6B): returns 0x00C11894.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva0033F76CGet(void)
{
	return (int)"AITunnelNetworkGuardState";
}

// ?Rva0033F797Get@@YAHXZ @ 0x0033f797 (6B): returns 0x00C118F4.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva0033F797Get(void)
{
	return (int)"AIHuntState";
}

// ?Rva0033F7C2Get@@YAHXZ @ 0x0033f7c2 (6B): returns 0x00C11944.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva0033F7C2Get(void)
{
	return (int)"AIAttackAreaState";
}

// ?Rva0033F7E5Get@@YAHXZ @ 0x0033f7e5 (6B): returns 0x00C119A0.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva0033F7E5Get(void)
{
	return (int)"AICowerState";
}

// ?Rva0033F808Get@@YAHXZ @ 0x0033f808 (6B): returns 0x00C119F4.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva0033F808Get(void)
{
	return (int)"AIQuarrelState";
}

// ?Rva0033F837Get@@YAHXZ @ 0x0033f837 (6B): returns 0x00C11A4C.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva0033F837Get(void)
{
	return (int)"AIRampageState";
}

// ?Rva0033FC3CGet@@YAHXZ @ 0x0033fc3c (6B): returns 0x00C11DF4.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva0033FC3CGet(void)
{
	return (int)"AIMoveOntoWallState";
}

// ?Rva0033FE9DGet@@YAHXZ @ 0x0033fe9d (6B): returns 0x00C11E4C.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva0033FE9DGet(void)
{
	return (int)"AIIdleState";
}

// ?Rva003400F3Get@@YAHXZ @ 0x003400f3 (6B): returns 0x00C11F48.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva003400F3Get(void)
{
	return (int)"AIMoveToStateSA";
}

// ?Rva003403ADGet@@YAHXZ @ 0x003403ad (6B): returns 0x00C12090.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva003403ADGet(void)
{
	return (int)"AIUncontrollableCower";
}

// ?Rva00367839Get@@YAHXZ @ 0x00367839 (6B): returns 0x00C1758C.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva00367839Get(void)
{
	return (int)"GiantBirdAttackMoveToState";
}

// ?Rva00346CF5Get@@YAHXZ @ 0x00346cf5 (6B): returns 0x00C136E8.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva00346CF5Get(void)
{
	return (int)"AIMoveToPositionAndEnterState";
}

// ?Rva00362E16Get@@YAHXZ @ 0x00362e16 (6B): returns 0x00C17098.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva00362E16Get(void)
{
	return (int)"BuffManager";
}

// ?Rva00362F5EGet@@YAHXZ @ 0x00362f5e (6B): returns 0x00BCB950.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva00362F5EGet(void)
{
	return (int)"LaserUpdate";
}

// ?Rva00136825Get@@YAHXZ @ 0x00136825 (6B): returns 0x6D6F6472.
// Follows a ret-28 (prev C2-1C-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva00136825Get(void)
{
	return 0x6D6F6472;
}

// ?Rva0015162CGet@@YAHXZ @ 0x0015162c (6B): returns 0x46585348.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva0015162CGet(void)
{
	return 0x46585348;
}

// ?Rva0017FB8EGet@@YAHXZ @ 0x0017fb8e (6B): returns 0x48494552.
// Follows a ret-12 (prev C2-0C-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva0017FB8EGet(void)
{
	return 0x48494552;
}

// ?Rva0017FFC4Get@@YAHXZ @ 0x0017ffc4 (6B): returns 0x484C4F44.
// Follows a ret-12 (prev C2-0C-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva0017FFC4Get(void)
{
	return 0x484C4F44;
}

// ?Rva001826B0Get@@YAHXZ @ 0x001826b0 (6B): returns 0x0000000A.
// Follows a ret-16 (prev C2-10-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva001826B0Get(void)
{
	return 0x0000000A;
}

// ?Rva0028C933Get@@YAHXZ @ 0x0028c933 (6B): returns 0x00BFBD24.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva0028C933Get(void)
{
	return (int)"ObjectHelper";
}

// ?Rva00299C6EGet@@YAHXZ @ 0x00299c6e (6B): returns 0x00BE07C4.
// Follows a ret-20 (prev C2-14-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva00299C6EGet(void)
{
	return (int)"Object";
}

// ?Rva002B117CGet@@YAHXZ @ 0x002b117c (6B): returns 0x00BFDF5C.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva002B117CGet(void)
{
	return (int)"Player";
}

// ?Rva002C74FBGet@@YAHXZ @ 0x002c74fb (6B): returns 0x00C008AC.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva002C74FBGet(void)
{
	return (int)"WeaponSet";
}

// ?Rva002CC2F6Get@@YAHXZ @ 0x002cc2f6 (6B): returns 0x00BE1058.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva002CC2F6Get(void)
{
	return (int)"Weapon";
}

// ?Rva002D6E02Get@@YAHXZ @ 0x002d6e02 (6B): returns 0x00C03368.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva002D6E02Get(void)
{
	return (int)"Anim2D";
}

// ?Rva002E07C6Get@@YAHXZ @ 0x002e07c6 (6B): returns 0x00C04920.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva002E07C6Get(void)
{
	return (int)"LivingWorldPlayer";
}

// ?Rva003A59ADGet@@YAHXZ @ 0x003a59ad (6B): returns 0x00C1B5B8.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva003A59ADGet(void)
{
	return (int)"DefaultModule<CAT_WIND>";
}

// ?Rva003A5A42Get@@YAHXZ @ 0x003a5a42 (6B): returns 0x00C1B5F0.
// Follows a ret-8 (prev C2-08-00), carried by 2 .rdata vtable slots,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva003A5A42Get(void)
{
	return (int)"DefaultParticleModule<CAT_WIND>";
}

// ?Rva003ABAADGet@@YAHXZ @ 0x003abaad (6B): returns 0x00C1C360.
// Follows a ret-8 (prev C2-08-00), carried by 2 .rdata vtable slots,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva003ABAADGet(void)
{
	return (int)"DefaultDraw<CAT_DRAW>";
}

// ?Rva003ABAEDGet@@YAHXZ @ 0x003abaed (6B): returns 0x00C1C3B4.
// Follows a ret-8 (prev C2-08-00), carried by 2 .rdata vtable slots,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva003ABAEDGet(void)
{
	return (int)"StreakDrawModule";
}

// ?Rva003ABB1DGet@@YAHXZ @ 0x003abb1d (6B): returns 0x00C1C3F4.
// Follows a ret-8 (prev C2-08-00), carried by 2 .rdata vtable slots,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva003ABB1DGet(void)
{
	return (int)"QuadDrawModule";
}

// ?Rva003ABB4DGet@@YAHXZ @ 0x003abb4d (6B): returns 0x00C1C430.
// Follows a ret-8 (prev C2-08-00), carried by 2 .rdata vtable slots,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva003ABB4DGet(void)
{
	return (int)"ButterflyDrawModule";
}

// ?Rva003ABB7DGet@@YAHXZ @ 0x003abb7d (6B): returns 0x00C1C470.
// Follows a ret-8 (prev C2-08-00), carried by 2 .rdata vtable slots,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva003ABB7DGet(void)
{
	return (int)"RenderObjectDrawModule";
}

// ?Rva003ABBBDGet@@YAHXZ @ 0x003abbbd (6B): returns 0x00C1C4B4.
// Follows a ret-8 (prev C2-08-00), carried by 2 .rdata vtable slots,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva003ABBBDGet(void)
{
	return (int)"LightningDrawModule";
}

// ?Rva003ABBF5Get@@YAHXZ @ 0x003abbf5 (6B): returns 0x00C1C4F4.
// Follows a ret-8 (prev C2-08-00), carried by 2 .rdata vtable slots,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva003ABBF5Get(void)
{
	return (int)"GpuDrawModule";
}

// ?Rva003ABC9FGet@@YAHXZ @ 0x003abc9f (6B): returns 0x00C1C51C.
// Follows a ret-8 (prev C2-08-00), carried by 2 .rdata vtable slots,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva003ABC9FGet(void)
{
	return (int)"DefaultModule<CAT_ALPHA>";
}

// ?Rva003ABDB2Get@@YAHXZ @ 0x003abdb2 (6B): returns 0x00C1C5EC.
// Follows a ret-8 (prev C2-08-00), carried by 2 .rdata vtable slots,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva003ABDB2Get(void)
{
	return (int)"DefaultModule<CAT_UPDATE>";
}

// ?Rva003ABE2AGet@@YAHXZ @ 0x003abe2a (6B): returns 0x00C1C630.
// Follows a ret-8 (prev C2-08-00), carried by 2 .rdata vtable slots,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva003ABE2AGet(void)
{
	return (int)"LifeEventModule";
}

// ?Rva003ABEBEGet@@YAHXZ @ 0x003abebe (6B): returns 0x00C1C6B4.
// Follows a ret-8 (prev C2-08-00), carried by 2 .rdata vtable slots,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva003ABEBEGet(void)
{
	return (int)"TerrainCollisionModule";
}

// ?Rva003AC930Get@@YAHXZ @ 0x003ac930 (6B): returns 0x00C1C91C.
// Follows a ret-4 (prev C2-04-00), carried by 2 .rdata vtable slots,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva003AC930Get(void)
{
	return (int)"DefaultParticleModule<CAT_ALPHA>";
}

// ?Rva003ACA16Get@@YAHXZ @ 0x003aca16 (6B): returns 0x00C1C9CC.
// Follows a ret-4 (prev C2-04-00), carried by 2 .rdata vtable slots,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva003ACA16Get(void)
{
	return (int)"DefaultParticleModule<CAT_UPDATE>";
}

// ?Rva003ACA7DGet@@YAHXZ @ 0x003aca7d (6B): returns 0x00C1CA14.
// Follows a ret-4 (prev C2-04-00), carried by 2 .rdata vtable slots,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva003ACA7DGet(void)
{
	return (int)"ParticleLifeEventModule";
}

// ?Rva003ACAFAGet@@YAHXZ @ 0x003acafa (6B): returns 0x00C1CA6C.
// Follows a ret-4 (prev C2-04-00), carried by 2 .rdata vtable slots,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva003ACAFAGet(void)
{
	return (int)"RenderObjectParticleUpdateModule";
}

// ?Rva003ACB61Get@@YAHXZ @ 0x003acb61 (6B): returns 0x00C1CAB4.
// Follows a ret-4 (prev C2-04-00), carried by 2 .rdata vtable slots,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva003ACB61Get(void)
{
	return (int)"ParticleTerrainCollisionModule";
}

// ?Rva003ACFC1Get@@YAHXZ @ 0x003acfc1 (6B): returns 0x00C1CE30.
// Follows a ret-4 (prev C2-04-00), carried by 2 .rdata vtable slots,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva003ACFC1Get(void)
{
	return (int)"DefaultParticleModule<CAT_PHYSICS>";
}

// ?Rva003ADCE5Get@@YAHXZ @ 0x003adce5 (6B): returns 0x00C1D144.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva003ADCE5Get(void)
{
	return (int)"DefaultParticleAlphaModuleInfo";
}

// ?Rva003ADDC7Get@@YAHXZ @ 0x003addc7 (6B): returns 0x00C1D1B4.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva003ADDC7Get(void)
{
	return (int)"DefaultParticleColorModuleInfo";
}

// ?Rva003ADEB9Get@@YAHXZ @ 0x003adeb9 (6B): returns 0x00C1D204.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva003ADEB9Get(void)
{
	return (int)"DefaultParticlePhysicsModuleInfo";
}

// ?Rva003ADFACGet@@YAHXZ @ 0x003adfac (6B): returns 0x00C1D274.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva003ADFACGet(void)
{
	return (int)"DefaultParticleUpdateModuleInfo";
}

// ?Rva003AE136Get@@YAHXZ @ 0x003ae136 (6B): returns 0x00C1D300.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva003AE136Get(void)
{
	return (int)"ParticleLifeEventModuleInfo";
}

// ?Rva003AE26AGet@@YAHXZ @ 0x003ae26a (6B): returns 0x00C1D368.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva003AE26AGet(void)
{
	return (int)"RenderObjectParticleUpdateModuleInfo";
}

// ?Rva003AE336Get@@YAHXZ @ 0x003ae336 (6B): returns 0x00C1D3C0.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva003AE336Get(void)
{
	return (int)"ParticleTerrainCollisionModuleInfo";
}

// ?Rva003B00D0Get@@YAHXZ @ 0x003b00d0 (6B): returns 0x00C1D930.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva003B00D0Get(void)
{
	return (int)"ParticleSystemStorageModule";
}

// ?Rva003B014CGet@@YAHXZ @ 0x003b014c (6B): returns 0x00C1D990.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva003B014CGet(void)
{
	return (int)"CPUParticleSystemStorageModule";
}

// ?Rva00367E8CGet@@YAHXZ @ 0x00367e8c (6B): returns 0x00C1768C.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva00367E8CGet(void)
{
	return (int)"GiantBirdGuardIdleState";
}

// ?Rva00367EDBGet@@YAHXZ @ 0x00367edb (6B): returns 0x00C176EC.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva00367EDBGet(void)
{
	return (int)"GiantBirdGuardOuterState";
}

// ?Rva00367F13Get@@YAHXZ @ 0x00367f13 (6B): returns 0x00C1774C.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva00367F13Get(void)
{
	return (int)"GiantBirdGuardReturnState";
}

// ?Rva003680E3Get@@YAHXZ @ 0x003680e3 (6B): returns 0x00C17804.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva003680E3Get(void)
{
	return (int)"GiantBirdGuardAttackAggressorState";
}

// ?Rva00368A0DGet@@YAHXZ @ 0x00368a0d (6B): returns 0x00C179BC.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva00368A0DGet(void)
{
	return (int)"GiantBirdGuardInnerState";
}

// ?Rva003730F6Get@@YAHXZ @ 0x003730f6 (6B): returns 0x00BF5A74.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva003730F6Get(void)
{
	return (int)"MineshaftPortalBehaviour";
}

// ?Rva0038374DGet@@YAHXZ @ 0x0038374d (6B): returns 0x00C194A0.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva0038374DGet(void)
{
	return (int)"GameSpyStagingRoom";
}

// ?Rva003A2875Get@@YAHXZ @ 0x003a2875 (6B): returns 0x00C1AE80.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva003A2875Get(void)
{
	return (int)"TeamTemplateInfo";
}

// ?Rva003A33A1Get@@YAHXZ @ 0x003a33a1 (6B): returns 0x00C1AEA4.
// Follows a ret-28 (prev C2-1C-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva003A33A1Get(void)
{
	return (int)"TeamPrototype";
}

// ?Rva003A3709Get@@YAHXZ @ 0x003a3709 (6B): returns 0x00BEE898.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva003A3709Get(void)
{
	return (int)"Team";
}

// ?Rva003ECCD0Get@@YAHXZ @ 0x003eccd0 (6B): returns 0x00BF4E94.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva003ECCD0Get(void)
{
	return (int)"ThreatFinderUpdate";
}

// ?Rva003EFD37Get@@YAHXZ @ 0x003efd37 (6B): returns 0x00C36BA8.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva003EFD37Get(void)
{
	return (int)"RegionBonusInfo";
}

// ?Rva003F24D0Get@@YAHXZ @ 0x003f24d0 (6B): returns 0x00C36E58.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva003F24D0Get(void)
{
	return (int)"LivingWorldRegionConnection";
}

// ?Rva003FAB8DGet@@YAHXZ @ 0x003fab8d (6B): returns 0x00C379F4.
// Follows a ret-4 (prev C2-04-00), carried by 2 .rdata vtable slots,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva003FAB8DGet(void)
{
	return (int)"LivingWorldSound";
}

// ?Rva003FD783Get@@YAHXZ @ 0x003fd783 (6B): returns 0x00C37D88.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva003FD783Get(void)
{
	return (int)"LivingWorldAnimObject";
}

// ?Rva0040C586Get@@YAHXZ @ 0x0040c586 (6B): returns 0x00C39460.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva0040C586Get(void)
{
	return (int)"ArmySummaryEntry";
}

// ?Rva0041431FGet@@YAHXZ @ 0x0041431f (6B): returns 0x00C3A068.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva0041431FGet(void)
{
	return (int)"ScoredKillEvaAnnouncerController";
}

// ?Rva00436846Get@@YAHXZ @ 0x00436846 (6B): returns 0x006D20D3.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva00436846Get(void)
{
	return (int)&createAptScreenQuickMatchMenu;
}

// ?Rva004543A3Get@@YAHXZ @ 0x004543a3 (6B): returns 0x00BF5CF4.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004543A3Get(void)
{
	return (int)"GettingBuiltBehavior";
}

// ?Rva4583A9Get@@YAHXZ @ 0x4583a9 (6B): returns 0x00bf5c90.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva4583A9Get(void)
{
	return (int)"BridgeScaffoldBehavior";
}

// ?Rva458759Get@@YAHXZ @ 0x458759 (6B): returns 0x00bf5c7c.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva458759Get(void)
{
	return (int)"BridgeTowerBehavior";
}

// ?Rva458FFCGet@@YAHXZ @ 0x458ffc (6B): returns 0x00bf5c5c.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva458FFCGet(void)
{
	return (int)"EnragedBehavior";
}

// ?Rva4599DFGet@@YAHXZ @ 0x4599df (6B): returns 0x00bf5bf4.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva4599DFGet(void)
{
	return (int)"SiegeDockingBehavior";
}

// ?Rva45CEEEGet@@YAHXZ @ 0x45ceee (6B): returns 0x00c41ea8.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva45CEEEGet(void)
{
	return (int)"DieModule";
}

// ?Rva45E9F4Get@@YAHXZ @ 0x45e9f4 (6B): returns 0x00bf5b4c.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva45E9F4Get(void)
{
	return (int)"ShipSlowDeathBehavior";
}

// ?Rva0045EFB6Get@@YAHXZ @ 0x0045efb6 (6B): returns 0x00bf5a4c.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva0045EFB6Get(void)
{
	return (int)"StancesBehavior";
}

// ?Rva00460827Get@@YAHXZ @ 0x00460827 (6B): returns 0x00bf5ac4.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva00460827Get(void)
{
	return (int)"WargBehavior";
}

// ?Rva00460B4AGet@@YAHXZ @ 0x00460b4a (6B): returns 0x00c42798.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva00460B4AGet(void)
{
	return (int)"UpgradeModule";
}

// ?Rva00460BCDGet@@YAHXZ @ 0x00460bcd (6B): returns 0x00bf5aac.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva00460BCDGet(void)
{
	return (int)"DynamicPortalBehaviour";
}

// ?Rva004619A7Get@@YAHXZ @ 0x004619a7 (6B): returns 0x00bf5a90.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004619A7Get(void)
{
	return (int)"FakePathfindPortalBehaviour";
}

// ?Rva004621ACGet@@YAHXZ @ 0x004621ac (6B): returns 0x00bf5824.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004621ACGet(void)
{
	return (int)"RunOffMapBehavior";
}

// ?Rva00466B3FGet@@YAHXZ @ 0x00466b3f (6B): returns 0x00bf5a40.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva00466B3FGet(void)
{
	return (int)"HealContain";
}

// ?Rva0046F7B3Get@@YAHXZ @ 0x0046f7b3 (6B): returns 0x00bf5a30.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva0046F7B3Get(void)
{
	return (int)"HordeContain";
}

// ?Rva0047664DGet@@YAHXZ @ 0x0047664d (6B): returns 0x00bf5a1c.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva0047664DGet(void)
{
	return (int)"HorseHordeContain";
}

// ?Rva00477098Get@@YAHXZ @ 0x00477098 (6B): returns 0x00bf5994.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva00477098Get(void)
{
	return (int)"HordeTransportContain";
}

// ?Rva0047A0E0Get@@YAHXZ @ 0x0047a0e0 (6B): returns 0x00bf597c.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva0047A0E0Get(void)
{
	return (int)"HordeGarrisonContain";
}

// ?Rva0047B518Get@@YAHXZ @ 0x0047b518 (6B): returns 0x00bf5a0c.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva0047B518Get(void)
{
	return (int)"AODHordeContain";
}

// ?Rva004803B0Get@@YAHXZ @ 0x004803b0 (6B): returns 0x00bf5950.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004803B0Get(void)
{
	return (int)"SlaughterHordeContain";
}

// ?Rva004805FAGet@@YAHXZ @ 0x004805fa (6B): returns 0x00bf5930.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004805FAGet(void)
{
	return (int)"CitadelSlaughterHordeContain";
}

// ?Rva00482E4BGet@@YAHXZ @ 0x00482e4b (6B): returns 0x00bf58a8.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva00482E4BGet(void)
{
	return (int)"FireWeaponWhenDeadBehavior";
}

// ?Rva00484628Get@@YAHXZ @ 0x00484628 (6B): returns 0x00bf57f4.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva00484628Get(void)
{
	return (int)"SlaveWatcherBehavior";
}

// ?Rva00484AD7Get@@YAHXZ @ 0x00484ad7 (6B): returns 0x00bf4bc0.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva00484AD7Get(void)
{
	return (int)"PassiveAreaEffectBehavior";
}

// ?Rva00484F3BGet@@YAHXZ @ 0x00484f3b (6B): returns 0x00bf4ad4.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva00484F3BGet(void)
{
	return (int)"PillageModule";
}

// ?Rva0048515DGet@@YAHXZ @ 0x0048515d (6B): returns 0x00bf57d4.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva0048515DGet(void)
{
	return (int)"AnnounceBirthAndDeathBehavior";
}

// ?Rva00488515Get@@YAHXZ @ 0x00488515 (6B): returns 0x00c4b424.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva00488515Get(void)
{
	return (int)"DozerActionPickActionPosState";
}

// ?Rva0048853FGet@@YAHXZ @ 0x0048853f (6B): returns 0x00c4b48c.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva0048853FGet(void)
{
	return (int)"DozerActionMoveToActionPosState";
}

// ?Rva0048856DGet@@YAHXZ @ 0x0048856d (6B): returns 0x00c4b4f4.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva0048856DGet(void)
{
	return (int)"DozerActionDoActionState";
}

// ?Rva004886C1Get@@YAHXZ @ 0x004886c1 (6B): returns 0x00c4b550.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004886C1Get(void)
{
	return (int)"DozerActionStateMachine";
}

// ?Rva004886EFGet@@YAHXZ @ 0x004886ef (6B): returns 0x00c4b5ac.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004886EFGet(void)
{
	return (int)"DozerPrimaryIdleState";
}

// ?Rva0048B164Get@@YAHXZ @ 0x0048b164 (6B): returns 0x00bf5614.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva0048B164Get(void)
{
	return (int)"DynamicShroudClearingRangeUpdate";
}

// ?Rva0048C258Get@@YAHXZ @ 0x0048c258 (6B): returns 0x00bf54cc.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva0048C258Get(void)
{
	return (int)"OilSpillUpdate";
}

// ?Rva0048C6D9Get@@YAHXZ @ 0x0048c6d9 (6B): returns 0x00bf5490.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva0048C6D9Get(void)
{
	return (int)"FlammableUpdate";
}

// ?Rva0048E0F4Get@@YAHXZ @ 0x0048e0f4 (6B): returns 0x00bf5484.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva0048E0F4Get(void)
{
	return (int)"FloodUpdate";
}

// ?Rva0049053EGet@@YAHXZ @ 0x0049053e (6B): returns 0x00bf5464.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva0049053EGet(void)
{
	return (int)"SiegeAIUpdate";
}

// ?Rva00490D70Get@@YAHXZ @ 0x00490d70 (6B): returns 0x00bf52f4.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva00490D70Get(void)
{
	return (int)"ModelConditionSpecialAbilityUpdate";
}

// ?Rva00491661Get@@YAHXZ @ 0x00491661 (6B): returns 0x00bf54a0.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva00491661Get(void)
{
	return (int)"MonitorConditionUpdate";
}

// ?Rva004921AAGet@@YAHXZ @ 0x004921aa (6B): returns 0x00bf5228.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004921AAGet(void)
{
	return (int)"HeroModeSpecialAbilityUpdate";
}

// ?Rva00492433Get@@YAHXZ @ 0x00492433 (6B): returns 0x00bf5208.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva00492433Get(void)
{
	return (int)"WeaponSetSpecialAbilityUpdate";
}

// ?Rva00492C8AGet@@YAHXZ @ 0x00492c8a (6B): returns 0x00bf5248.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva00492C8AGet(void)
{
	return (int)"TeleportSpecialAbilityUpdate";
}

// ?Rva00493DA4Get@@YAHXZ @ 0x00493da4 (6B): returns 0x00bf47d4.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva00493DA4Get(void)
{
	return (int)"SpecialPowerModule";
}

// ?Rva00494AD9Get@@YAHXZ @ 0x00494ad9 (6B): returns 0x00bf5318.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva00494AD9Get(void)
{
	return (int)"WeaponModeSpecialPowerUpdate";
}

// ?Rva00494DFBGet@@YAHXZ @ 0x00494dfb (6B): returns 0x00bf51e8.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva00494DFBGet(void)
{
	return (int)"ScaleWallSpecialAbilityUpdate";
}

// ?Rva00494F15Get@@YAHXZ @ 0x00494f15 (6B): returns 0x00bf51c4.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva00494F15Get(void)
{
	return (int)"FlingPassengerSpecialAbilityUpdate";
}

// ?Rva0049533EGet@@YAHXZ @ 0x0049533e (6B): returns 0x00bf5400.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva0049533EGet(void)
{
	return (int)"CommandButtonHuntUpdate";
}

// ?Rva0049B5D6Get@@YAHXZ @ 0x0049b5d6 (6B): returns 0x00bf5100.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva0049B5D6Get(void)
{
	return (int)"AttributeModifierAuraUpdate";
}

// ?Rva0049C3F6Get@@YAHXZ @ 0x0049c3f6 (6B): returns 0x00bf51b0.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva0049C3F6Get(void)
{
	return (int)"GiveUpgradeUpdate";
}

// ?Rva0049E13CGet@@YAHXZ @ 0x0049e13c (6B): returns 0x00bf5018.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva0049E13CGet(void)
{
	return (int)"ProductionUpdate";
}

// ?Rva004A0E06Get@@YAHXZ @ 0x004a0e06 (6B): returns 0x00bf5098.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004A0E06Get(void)
{
	return (int)"SupplyCenterDockUpdate";
}

// ?Rva004A11CEGet@@YAHXZ @ 0x004a11ce (6B): returns 0x00bf534c.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004A11CEGet(void)
{
	return (int)"RepairDockUpdate";
}

// ?Rva004A13E0Get@@YAHXZ @ 0x004a13e0 (6B): returns 0x00bf5068.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004A13E0Get(void)
{
	return (int)"MonsterDockUpdate";
}

// ?Rva004A34C0Get@@YAHXZ @ 0x004a34c0 (6B): returns 0x00bf568c.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004A34C0Get(void)
{
	return (int)"BroadcastStealthUpdate";
}

// ?Rva004A3871Get@@YAHXZ @ 0x004a3871 (6B): returns 0x00bf5668.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004A3871Get(void)
{
	return (int)"InvisibilityUpdate";
}

// ?Rva004A6950Get@@YAHXZ @ 0x004a6950 (6B): returns 0x00c52db4.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004A6950Get(void)
{
	return (int)"SupplyTruckWantsToPickUpOrDeliverBoxesState";
}

// ?Rva004A6973Get@@YAHXZ @ 0x004a6973 (6B): returns 0x00c52e24.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004A6973Get(void)
{
	return (int)"RegroupingState";
}

// ?Rva004A6996Get@@YAHXZ @ 0x004a6996 (6B): returns 0x00c52e7c.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004A6996Get(void)
{
	return (int)"DockingState";
}

// ?Rva004A69B9Get@@YAHXZ @ 0x004a69b9 (6B): returns 0x00c52ed4.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004A69B9Get(void)
{
	return (int)"HarvestingState";
}

// ?Rva004A7684Get@@YAHXZ @ 0x004a7684 (6B): returns 0x00bf5b8c.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004A7684Get(void)
{
	return (int)"MissileUpdate";
}

// ?Rva004A907AGet@@YAHXZ @ 0x004a907a (6B): returns 0x00bf4f88.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004A907AGet(void)
{
	return (int)"TransportAIUpdate";
}

// ?Rva004A9357Get@@YAHXZ @ 0x004a9357 (6B): returns 0x00bf4f78.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004A9357Get(void)
{
	return (int)"WanderAIUpdate";
}

// ?Rva004AB889Get@@YAHXZ @ 0x004ab889 (6B): returns 0x00bf5198.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004AB889Get(void)
{
	return (int)"LargeGroupAudioUpdate";
}

// ?Rva004AC12FGet@@YAHXZ @ 0x004ac12f (6B): returns 0x00bf554c.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004AC12FGet(void)
{
	return (int)"RainOfFireUpdate";
}

// ?Rva004AC680Get@@YAHXZ @ 0x004ac680 (6B): returns 0x00bf5530.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004AC680Get(void)
{
	return (int)"DestroyEnvironmentUpdate";
}

// ?Rva004AE1A6Get@@YAHXZ @ 0x004ae1a6 (6B): returns 0x00bf52ac.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004AE1A6Get(void)
{
	return (int)"ToggleHiddenSpecialAbilityUpdate";
}

// ?Rva004AE4DCGet@@YAHXZ @ 0x004ae4dc (6B): returns 0x00bf5288.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004AE4DCGet(void)
{
	return (int)"ToggleDeploySpecialAbilityUpdate";
}

// ?Rva004B4A86Get@@YAHXZ @ 0x004b4a86 (6B): returns 0x00bf4dc0.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004B4A86Get(void)
{
	return (int)"StatusBitsUpgradeIfEldestKindof";
}

// ?Rva004B6AB9Get@@YAHXZ @ 0x004b6ab9 (6B): returns 0x00bf4c88.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004B6AB9Get(void)
{
	return (int)"GeometryUpgrade";
}

// ?Rva004B7084Get@@YAHXZ @ 0x004b7084 (6B): returns 0x00bf4c74.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004B7084Get(void)
{
	return (int)"ReplaceSelfUpgrade";
}

// ?Rva004B8C38Get@@YAHXZ @ 0x004b8c38 (6B): returns 0x00bf4aa4.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004B8C38Get(void)
{
	return (int)"LockWeaponCreate";
}

// ?Rva004B8D2CGet@@YAHXZ @ 0x004b8d2c (6B): returns 0x00c59398.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004B8D2CGet(void)
{
	return (int)"CreateModule";
}

// ?Rva004B8DABGet@@YAHXZ @ 0x004b8dab (6B): returns 0x00bf4a80.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004B8DABGet(void)
{
	return (int)"SupplyCenterCreate";
}

// ?Rva004B8EA2Get@@YAHXZ @ 0x004b8ea2 (6B): returns 0x00bf4a68.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004B8EA2Get(void)
{
	return (int)"SupplyWarehouseCreate";
}

// ?Rva004B8F8CGet@@YAHXZ @ 0x004b8f8c (6B): returns 0x00bf4a40.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004B8F8CGet(void)
{
	return (int)"GrantUpgradeCreate";
}

// ?Rva004B91A5Get@@YAHXZ @ 0x004b91a5 (6B): returns 0x00bf4a28.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004B91A5Get(void)
{
	return (int)"ExperienceLevelCreate";
}

// ?Rva004B9281Get@@YAHXZ @ 0x004b9281 (6B): returns 0x00bf4a94.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004B9281Get(void)
{
	return (int)"PreorderCreate";
}

// ?Rva004B936FGet@@YAHXZ @ 0x004b936f (6B): returns 0x00bf4a54.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004B936FGet(void)
{
	return (int)"SpecialPowerCreate";
}

// ?Rva004B9452Get@@YAHXZ @ 0x004b9452 (6B): returns 0x00bf4a10.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004B9452Get(void)
{
	return (int)"InheritUpgradeCreate";
}

// ?Rva004B9735Get@@YAHXZ @ 0x004b9735 (6B): returns 0x00c59914.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004B9735Get(void)
{
	return (int)"DamageModule";
}

// ?Rva004BA431Get@@YAHXZ @ 0x004ba431 (6B): returns 0x00bf49ec.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004BA431Get(void)
{
	return (int)"TransitionDamageFX";
}

// ?Rva004BAE7DGet@@YAHXZ @ 0x004bae7d (6B): returns 0x00bf49cc.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004BAE7DGet(void)
{
	return (int)"EvacuateDamage";
}

// ?Rva004BB46AGet@@YAHXZ @ 0x004bb46a (6B): returns 0x00bf499c.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004BB46AGet(void)
{
	return (int)"CallHelpOnDamage";
}

// ?Rva004BB733Get@@YAHXZ @ 0x004bb733 (6B): returns 0x00c5a160.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004BB733Get(void)
{
	return (int)"CollideModule";
}

// ?Rva004BC839Get@@YAHXZ @ 0x004bc839 (6B): returns 0x00bf4940.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004BC839Get(void)
{
	return (int)"HealCrateCollide";
}

// ?Rva004BC969Get@@YAHXZ @ 0x004bc969 (6B): returns 0x00bf492c.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004BC969Get(void)
{
	return (int)"MoneyCrateCollide";
}

// ?Rva004BCB07Get@@YAHXZ @ 0x004bcb07 (6B): returns 0x00bf4918.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004BCB07Get(void)
{
	return (int)"ShroudCrateCollide";
}

// ?Rva004BCC3DGet@@YAHXZ @ 0x004bcc3d (6B): returns 0x00bf4904.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004BCC3DGet(void)
{
	return (int)"UnitCrateCollide";
}

// ?Rva004BCE5CGet@@YAHXZ @ 0x004bce5c (6B): returns 0x00bf48ec.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004BCE5CGet(void)
{
	return (int)"VeterancyCrateCollide";
}

// ?Rva004BD201Get@@YAHXZ @ 0x004bd201 (6B): returns 0x00bf48d8.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004BD201Get(void)
{
	return (int)"SalvageCrateCollide";
}

// ?Rva004BD83BGet@@YAHXZ @ 0x004bd83b (6B): returns 0x00c5ae9c.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004BD83BGet(void)
{
	return (int)"BodyModule";
}

// ?Rva004C0898Get@@YAHXZ @ 0x004c0898 (6B): returns 0x00bf4884.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004C0898Get(void)
{
	return (int)"ImmortalBody";
}

// ?Rva004C0982Get@@YAHXZ @ 0x004c0982 (6B): returns 0x00bf4874.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004C0982Get(void)
{
	return (int)"StructureBody";
}

// ?Rva004C1315Get@@YAHXZ @ 0x004c1315 (6B): returns 0x00bf47e8.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004C1315Get(void)
{
	return (int)"RespawnBody";
}

// ?Rva004C15F1Get@@YAHXZ @ 0x004c15f1 (6B): returns 0x00bf4848.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004C15F1Get(void)
{
	return (int)"DelayedDeathBody";
}

// ?Rva004C1EF1Get@@YAHXZ @ 0x004c1ef1 (6B): returns 0x00bf4814.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004C1EF1Get(void)
{
	return (int)"OathbreakerBody";
}

// ?Rva004C2010Get@@YAHXZ @ 0x004c2010 (6B): returns 0x00bf47f4.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004C2010Get(void)
{
	return (int)"PorcupineFormationBodyModule";
}

// ?Rva004C23CEGet@@YAHXZ @ 0x004c23ce (6B): returns 0x00bf47b8.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004C23CEGet(void)
{
	return (int)"InvisibilitySpecialPower";
}

// ?Rva004C2650Get@@YAHXZ @ 0x004c2650 (6B): returns 0x00bf47a0.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004C2650Get(void)
{
	return (int)"CashHackSpecialPower";
}

// ?Rva004C29B5Get@@YAHXZ @ 0x004c29b5 (6B): returns 0x00bf4788.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004C29B5Get(void)
{
	return (int)"DefectorSpecialPower";
}

// ?Rva004C2B3FGet@@YAHXZ @ 0x004c2b3f (6B): returns 0x00bf4770.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004C2B3FGet(void)
{
	return (int)"LevelGrantSpecialPower";
}

// ?Rva004C2F1FGet@@YAHXZ @ 0x004c2f1f (6B): returns 0x00bf4758.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004C2F1FGet(void)
{
	return (int)"ProductionSpeedBonus";
}

// ?Rva004C3102Get@@YAHXZ @ 0x004c3102 (6B): returns 0x00bf4748.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004C3102Get(void)
{
	return (int)"OCLSpecialPower";
}

// ?Rva004C38FFGet@@YAHXZ @ 0x004c38ff (6B): returns 0x00bf4730.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004C38FFGet(void)
{
	return (int)"ElvenWoodSpecialPower";
}

// ?Rva004C4022Get@@YAHXZ @ 0x004c4022 (6B): returns 0x00bf4710.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004C4022Get(void)
{
	return (int)"WeaponChangeSpecialPowerModule";
}

// ?Rva004C4381Get@@YAHXZ @ 0x004c4381 (6B): returns 0x00bf46f8.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004C4381Get(void)
{
	return (int)"ScavengerSpecialPower";
}

// ?Rva004C4502Get@@YAHXZ @ 0x004c4502 (6B): returns 0x00bf46e0.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004C4502Get(void)
{
	return (int)"CloudBreakSpecialPower";
}

// ?Rva004C48C0Get@@YAHXZ @ 0x004c48c0 (6B): returns 0x00bf46cc.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004C48C0Get(void)
{
	return (int)"TaintSpecialPower";
}

// ?Rva004C4BCBGet@@YAHXZ @ 0x004c4bcb (6B): returns 0x00bf46b0.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004C4BCBGet(void)
{
	return (int)"FreezingRainSpecialPower";
}

// ?Rva004C4DE3Get@@YAHXZ @ 0x004c4de3 (6B): returns 0x00bf4698.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004C4DE3Get(void)
{
	return (int)"DarknessSpecialPower";
}

// ?Rva004C54ABGet@@YAHXZ @ 0x004c54ab (6B): returns 0x00bf4668.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004C54ABGet(void)
{
	return (int)"DeflectSpecialPower";
}

// ?Rva004C5736Get@@YAHXZ @ 0x004c5736 (6B): returns 0x00bf4650.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004C5736Get(void)
{
	return (int)"SiegeDeploySpecialPower";
}

// ?Rva004C63D8Get@@YAHXZ @ 0x004c63d8 (6B): returns 0x00bf4630.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004C63D8Get(void)
{
	return (int)"SiegeDeployHordeSpecialPower";
}

// ?Rva004C679AGet@@YAHXZ @ 0x004c679a (6B): returns 0x00bf461c.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004C679AGet(void)
{
	return (int)"StopSpecialPower";
}

// ?Rva004C693DGet@@YAHXZ @ 0x004c693d (6B): returns 0x00bf4608.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004C693DGet(void)
{
	return (int)"WoundArrowUpdate";
}

// ?Rva004C6C56Get@@YAHXZ @ 0x004c6c56 (6B): returns 0x00bf45f4.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004C6C56Get(void)
{
	return (int)"FellBeastSwoopPower";
}

// ?Rva004C6F71Get@@YAHXZ @ 0x004c6f71 (6B): returns 0x00bf45dc.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004C6F71Get(void)
{
	return (int)"ManTheWallsSpecialPower";
}

// ?Rva004C7B30Get@@YAHXZ @ 0x004c7b30 (6B): returns 0x00bf45bc.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004C7B30Get(void)
{
	return (int)"UntamedAllegianceSpecialPower";
}

// ?Rva004C7C2DGet@@YAHXZ @ 0x004c7c2d (6B): returns 0x00bf45a0.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004C7C2DGet(void)
{
	return (int)"PlayerUpgradeSpecialPower";
}

// ?Rva004C7EA8Get@@YAHXZ @ 0x004c7ea8 (6B): returns 0x00bf4588.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004C7EA8Get(void)
{
	return (int)"PlayerHealSpecialPower";
}

// ?Rva004C820DGet@@YAHXZ @ 0x004c820d (6B): returns 0x00bf4570.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004C820DGet(void)
{
	return (int)"DevastateSpecialPower";
}

// ?Rva004C859EGet@@YAHXZ @ 0x004c859e (6B): returns 0x00bf4558.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004C859EGet(void)
{
	return (int)"SplitHordeSpecialPower";
}

// ?Rva004C86DEGet@@YAHXZ @ 0x004c86de (6B): returns 0x00bf4544.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004C86DEGet(void)
{
	return (int)"RepairSpecialPower";
}

// ?Rva004C87EEGet@@YAHXZ @ 0x004c87ee (6B): returns 0x00bf4528.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004C87EEGet(void)
{
	return (int)"CombineHordeSpecialPower";
}

// ?Rva004C8A10Get@@YAHXZ @ 0x004c8a10 (6B): returns 0x00bf450c.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004C8A10Get(void)
{
	return (int)"HordeDispatchSpecialPower";
}

// ?Rva004C9008Get@@YAHXZ @ 0x004c9008 (6B): returns 0x00bf44e8.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004C9008Get(void)
{
	return (int)"AnimatedParticleSysBoneClientUpdate";
}

// ?Rva004C90DAGet@@YAHXZ @ 0x004c90da (6B): returns 0x00bf44d4.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004C90DAGet(void)
{
	return (int)"SwayClientUpdate";
}

// ?Rva004C95C3Get@@YAHXZ @ 0x004c95c3 (6B): returns 0x00bf44c0.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004C95C3Get(void)
{
	return (int)"BeaconClientUpdate";
}

// ?Rva004C9A06Get@@YAHXZ @ 0x004c9a06 (6B): returns 0x00bf4424.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004C9A06Get(void)
{
	return (int)"EvaAnnounceClientCreate";
}

// ?Rva004C9BEDGet@@YAHXZ @ 0x004c9bed (6B): returns 0x00bf44a8.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004C9BEDGet(void)
{
	return (int)"RadarMarkerClientUpdate";
}

// ?Rva004CBCA7Get@@YAHXZ @ 0x004cbca7 (6B): returns 0x00bf4464.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004CBCA7Get(void)
{
	return (int)"RandomSoundSelectorClientBehavior";
}

// ?Rva004CBF0DGet@@YAHXZ @ 0x004cbf0d (6B): returns 0x00bf443c.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004CBF0DGet(void)
{
	return (int)"ModelConditionAudioLoopClientBehavior";
}

// ?Rva004CC9B9Get@@YAHXZ @ 0x004cc9b9 (6B): returns 0x00bf4ba4.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004CC9B9Get(void)
{
	return (int)"DominateEnemySpecialPower";
}

// ?Rva004CCDB0Get@@YAHXZ @ 0x004ccdb0 (6B): returns 0x00bf4b08.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004CCDB0Get(void)
{
	return (int)"CurseSpecialPower";
}

// ?Rva004CD11BGet@@YAHXZ @ 0x004cd11b (6B): returns 0x00bf4ae4.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004CD11BGet(void)
{
	return (int)"GiveOrRestoreUpgradeSpecialPower";
}

// ?Rva004CD3D5Get@@YAHXZ @ 0x004cd3d5 (6B): returns 0x00bf4b84.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004CD3D5Get(void)
{
	return (int)"TeleportToCasterSpecialPower";
}

// ?Rva004CD975Get@@YAHXZ @ 0x004cd975 (6B): returns 0x00bf4b50.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004CD975Get(void)
{
	return (int)"StoreObjectsSpecialPower";
}

// ?Rva004CDC2DGet@@YAHXZ @ 0x004cdc2d (6B): returns 0x00bf4b1c.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004CDC2DGet(void)
{
	return (int)"EvacuateGarrisonSpecialPower";
}

// ?Rva004CDD33Get@@YAHXZ @ 0x004cdd33 (6B): returns 0x00bf4ab8.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004CDD33Get(void)
{
	return (int)"ActivateModuleSpecialPower";
}

// ?Rva004CE037Get@@YAHXZ @ 0x004ce037 (6B): returns 0x00bf4b3c.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004CE037Get(void)
{
	return (int)"UnleashSpecialPower";
}

// ?Rva004D73E4Get@@YAHXZ @ 0x004d73e4 (6B): returns 0x00c60598.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004D73E4Get(void)
{
	return (int)"SuccessState";
}

// ?Rva004D7BB9Get@@YAHXZ @ 0x004d7bb9 (6B): returns 0x00c6081c.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004D7BB9Get(void)
{
	return (int)"TurretAIIdleState";
}

// ?Rva004D7BE4Get@@YAHXZ @ 0x004d7be4 (6B): returns 0x00c60874.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004D7BE4Get(void)
{
	return (int)"TurretAIIdleScanState";
}

// ?Rva004D7C07Get@@YAHXZ @ 0x004d7c07 (6B): returns 0x00c608d4.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004D7C07Get(void)
{
	return (int)"TurretAIAimTurretState";
}

// ?Rva004D7C2AGet@@YAHXZ @ 0x004d7c2a (6B): returns 0x00c60934.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004D7C2AGet(void)
{
	return (int)"TurretAIRecenterTurretState";
}

// ?Rva004D7C51Get@@YAHXZ @ 0x004d7c51 (6B): returns 0x00c60994.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004D7C51Get(void)
{
	return (int)"TurretAIHoldTurretState";
}

// ?Rva004D7E5BGet@@YAHXZ @ 0x004d7e5b (6B): returns 0x00c60a08.
// Follows a ret-12 (prev C2-0C-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004D7E5BGet(void)
{
	return (int)"TurretStateMachine";
}

// ?Rva004E133CGet@@YAHXZ @ 0x004e133c (6B): returns 0x00c61860.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004E133CGet(void)
{
	return (int)"MoveArmy";
}

// ?Rva004E1392Get@@YAHXZ @ 0x004e1392 (6B): returns 0x00c618b4.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004E1392Get(void)
{
	return (int)"SetPlayerControlOfArmy";
}

// ?Rva004E30C6Get@@YAHXZ @ 0x004e30c6 (6B): returns 0x00c04bc0.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004E30C6Get(void)
{
	return (int)"SpawnArmy";
}

// ?Rva004EECFCGet@@YAHXZ @ 0x004eecfc (6B): returns 0x00c62ad4.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004EECFCGet(void)
{
	return (int)"LivingWorldScoreKeeper";
}

// ?Rva004EF417Get@@YAHXZ @ 0x004ef417 (6B): returns 0x00c62b64.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004EF417Get(void)
{
	return (int)"AISkirmishPlayer";
}

// ?Rva004F05BAGet@@YAHXZ @ 0x004f05ba (6B): returns 0x00c62e34.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva004F05BAGet(void)
{
	return (int)"AIPlayer";
}

// ?Rva00513813Get@@YAHXZ @ 0x00513813 (6B): returns 0x006d1ec9.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva00513813Get(void)
{
	return (int)&createAptScreenObjectives;
}

// ?Rva0052CFABGet@@YAHXZ @ 0x0052cfab (6B): returns 0x00c68790.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva0052CFABGet(void)
{
	return (int)"LivingWorldCampaign";
}

// ?Rva00542D58Get@@YAHXZ @ 0x00542d58 (6B): returns 0x00c69714.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva00542D58Get(void)
{
	return (int)"AIGuardIdleState";
}

// ?Rva00542E5CGet@@YAHXZ @ 0x00542e5c (6B): returns 0x00c697c4.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva00542E5CGet(void)
{
	return (int)"AIGuardInnerState";
}

// ?Rva00542EABGet@@YAHXZ @ 0x00542eab (6B): returns 0x00c6981c.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva00542EABGet(void)
{
	return (int)"AIGuardOuterState";
}

// ?Rva00542ED2Get@@YAHXZ @ 0x00542ed2 (6B): returns 0x00c69878.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva00542ED2Get(void)
{
	return (int)"AIGuardReturnState";
}

// ?Rva00542F3DGet@@YAHXZ @ 0x00542f3d (6B): returns 0x00c698d4.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva00542F3DGet(void)
{
	return (int)"AIGuardAttackAggressorState";
}

// ?Rva005440B6Get@@YAHXZ @ 0x005440b6 (6B): returns 0x00c69984.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva005440B6Get(void)
{
	return (int)"AIDockWaitForClearanceState";
}

// ?Rva005445F9Get@@YAHXZ @ 0x005445f9 (6B): returns 0x00c69a64.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva005445F9Get(void)
{
	return (int)"AIDockProcessDockState";
}

// ?Rva0054480AGet@@YAHXZ @ 0x0054480a (6B): returns 0x00c69af8.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva0054480AGet(void)
{
	return (int)"AIDockApproachState";
}

// ?Rva00544C24Get@@YAHXZ @ 0x00544c24 (6B): returns 0x00c69cdc.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva00544C24Get(void)
{
	return (int)"AIHarvestPrepareSiteState";
}

// ?Rva00544C4BGet@@YAHXZ @ 0x00544c4b (6B): returns 0x00c69d3c.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva00544C4BGet(void)
{
	return (int)"AIHarvestWorkSiteState";
}

// ?Rva00544ECEGet@@YAHXZ @ 0x00544ece (6B): returns 0x00c69e50.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva00544ECEGet(void)
{
	return (int)"AIHarvestApproachSiteState";
}

// ?Rva005453DCGet@@YAHXZ @ 0x005453dc (6B): returns 0x00c69f80.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva005453DCGet(void)
{
	return (int)"AIGuardRetaliateReturnState";
}

// ?Rva00545519Get@@YAHXZ @ 0x00545519 (6B): returns 0x00c69fe4.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva00545519Get(void)
{
	return (int)"AIGuardRetaliateAttackAggressorState";
}

// ?Rva00545B6CGet@@YAHXZ @ 0x00545b6c (6B): returns 0x00c6a07c.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva00545B6CGet(void)
{
	return (int)"AITNGuardIdleState";
}

// ?Rva00545D78Get@@YAHXZ @ 0x00545d78 (6B): returns 0x00c6a184.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva00545D78Get(void)
{
	return (int)"AITNGuardInnerState";
}

// ?Rva00545DAAGet@@YAHXZ @ 0x00545daa (6B): returns 0x00c6a1dc.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva00545DAAGet(void)
{
	return (int)"AITNGuardOuterState";
}

// ?Rva00545DCCGet@@YAHXZ @ 0x00545dcc (6B): returns 0x00c6a238.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva00545DCCGet(void)
{
	return (int)"AITNGuardReturnState";
}

// ?Rva00545EACGet@@YAHXZ @ 0x00545eac (6B): returns 0x00c6a2dc.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva00545EACGet(void)
{
	return (int)"AITNGuardAttackAggressorState";
}

// ?Rva0055A914Get@@YAHXZ @ 0x0055a914 (6B): returns 0x00c6b8e8.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva0055A914Get(void)
{
	return (int)"ScoredKillTracker";
}

// ?Rva0056DC46Get@@YAHXZ @ 0x0056dc46 (6B): returns 0x0081025d.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva0056DC46Get(void)
{
	return (int)&createAptScreenInGameChat;
}

// ?Rva0058902FGet@@YAHXZ @ 0x0058902f (6B): returns 0x00c700f4.
// Follows a ret-8 (prev C2-08-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva0058902FGet(void)
{
	return (int)"DamagerModule";
}

// ?Rva005BA234Get@@YAHXZ @ 0x005ba234 (6B): returns 0x00c66380.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva005BA234Get(void)
{
	return (int)"OnlineOpenPlay";
}

// ?Rva005BA2C5Get@@YAHXZ @ 0x005ba2c5 (6B): returns 0x00c66370.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva005BA2C5Get(void)
{
	return (int)"OnlineStrategic";
}

// ?Rva005C4598Get@@YAHXZ @ 0x005c4598 (6B): returns 0x00c74670.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva005C4598Get(void)
{
	return (int)"LivingWorldBuildingNuggetStrengthenArmy";
}

// ?Rva005C47EAGet@@YAHXZ @ 0x005c47ea (6B): returns 0x00c74734.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva005C47EAGet(void)
{
	return (int)"LivingWorldBuildingNuggetUpgradeTroops";
}

// ?Rva005DAFFEGet@@YAHXZ @ 0x005daffe (6B): returns 0x00c76684.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva005DAFFEGet(void)
{
	return (int)"ExperienceTrackerAutoResolve";
}

// ?Rva006C75F0Get@@YAHXZ @ 0x006c75f0 (6B): returns 0x00ce7d4c.
// Follows a ret-4 (prev C2-04-00), carried by 1 .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva006C75F0Get(void)
{
	return (int)"file_csv";
}
