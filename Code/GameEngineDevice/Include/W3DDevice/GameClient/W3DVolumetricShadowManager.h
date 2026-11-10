// W3DVolumetricShadowManager: canonical declarations for the members 8 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_W3DVOLUMETRICSHADOWMANAGER_H
#define CANONICAL_W3DVOLUMETRICSHADOWMANAGER_H

class RenderInfoClass;

class W3DVolumetricShadowManager
{
public:
	~W3DVolumetricShadowManager();
	bool ReAcquireResources();
	void ReleaseResources();
	void invalidateCachedLightPositions();
	void renderShadows(RenderInfoClass &rinfo);
protected:
	void renderStencilShadows();
};

#endif // CANONICAL_W3DVOLUMETRICSHADOWMANAGER_H
