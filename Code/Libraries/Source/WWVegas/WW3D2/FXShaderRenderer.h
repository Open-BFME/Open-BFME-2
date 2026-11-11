// FXShaderRenderer: canonical declarations for the members 3 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_FXSHADERRENDERER_H
#define CANONICAL_FXSHADERRENDERER_H

class FXShaderRenderer
{
public:
	void FlushSoftwareSkinnedRenderingTasks();
	void PerformRendering(int a, int b);
};

#endif // CANONICAL_FXSHADERRENDERER_H
