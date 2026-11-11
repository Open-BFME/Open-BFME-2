// Rva00785FD0Renderer: canonical declarations for the members 3 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA00785FD0RENDERER_H
#define CANONICAL_RVA00785FD0RENDERER_H

class Rva00785FD0Renderer
{
public:
	~Rva00785FD0Renderer();
	void __fastcall setMode(int mode);
	void stencil();
};

#endif // CANONICAL_RVA00785FD0RENDERER_H
