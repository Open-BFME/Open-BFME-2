// ?zoomOut@View@@UAEXXZ
// partial score=0.7 date=2026-10-08
// Stash: View::zoomIn (0x0025EA2E) and View::zoomOut (0x0025EA55), 39 B each.
// Retail: getHeightAboveGround() (vtable +0x12C) * 0.96f - 1.0f -> setHeightAboveGround (+0x130).
// zoomOut: * 1.05f + 1.0f. Compiled bodies call vtable +0xFC/+0x100 with the header's layout,
// so the slot numbers differ from retail's +0x12C/+0x130 and bytes do not match.
void View::zoomIn( void )
{
	setHeightAboveGround(getHeightAboveGround() * 0.96f - 1.0f);
}

void View::zoomOut( void )
{
	setHeightAboveGround(getHeightAboveGround() * 1.05f + 1.0f);
}
