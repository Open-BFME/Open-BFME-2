// cl: /DNDEBUG /MD /EHsc /DWIN32 /D_WINDOWS
// Target evidence: retail 0x0009A383 checks four global pointers in order and
// calls each manager only when its pointer is non-null. The 91-byte body is
// byte-verified.
// Donor evidence: Zero Hour W3DShadow.cpp gives the same aggregate purpose
// and names its first two checks as volumetric and projected shadow managers.
// Inference: the target function keeps that owner and appends two checks. The
// latter helpers retain address-derived names because their owners are unknown.

typedef bool Bool;

class W3DVolumetricShadowManager
{
public:
	Bool ReAcquireResources();
};

class W3DProjectedShadowManager
{
public:
	Bool ReAcquireResources();
};

class Rva00108660ResourceManager
{
public:
	Bool ReAcquireResources();
};

class Rva0007DA23ResourceManager
{
public:
	Bool ReAcquireResources();
};

extern W3DVolumetricShadowManager *TheW3DVolumetricShadowManager;
// TheW3DVolumetricShadowManager: matched references place it at VA 0xdebcd8 (zero-filled .bss).
W3DVolumetricShadowManager * TheW3DVolumetricShadowManager;
extern W3DProjectedShadowManager *TheW3DProjectedShadowManager;
// TheW3DProjectedShadowManager: matched references place it at VA 0xdec2cc (zero-filled .bss).
W3DProjectedShadowManager * TheW3DProjectedShadowManager;
extern Rva00108660ResourceManager *Rva00DEC2D8Manager;
extern Rva0007DA23ResourceManager *Rva00DE1FF8Manager;
// Rva00DE1FF8Manager: matched references place it at VA 0xde1ff8 (zero-filled .bss).
Rva0007DA23ResourceManager * Rva00DE1FF8Manager;

class W3DShadowManager
{
public:
	Bool ReAcquireResources();
};

Bool W3DShadowManager::ReAcquireResources()
{
	Bool result = true;
	if (TheW3DVolumetricShadowManager && !TheW3DVolumetricShadowManager->ReAcquireResources())
		result = false;
	if (TheW3DProjectedShadowManager && !TheW3DProjectedShadowManager->ReAcquireResources())
		result = false;
	if (Rva00DEC2D8Manager && !Rva00DEC2D8Manager->ReAcquireResources())
		result = false;
	if (Rva00DE1FF8Manager && !Rva00DE1FF8Manager->ReAcquireResources())
		result = false;
	return result;
}

// ?Rva00DEC2D8Manager@@3PAVRva00108660ResourceManager@@A: matched references place it at VA 0xdec2d8; also referenced as ?R2Ptr01306DF0@@3PAVR2GlobalReceiver@@A.
Rva00108660ResourceManager * Rva00DEC2D8Manager = 0;
