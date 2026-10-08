// cl: /O1 /arch:SSE /G7
// Retail 0x0007B6F3, 14 bytes: a thiscall member of the manager at 0x00DE1FF8
// that ignores its this; AptCreateAHero::DrawMapComponent (0x00514070) calls it
// with that manager in ecx after drawing the map view. WorldBuilder's body
// (0x007EEFD0) keeps the same shape. It clears the shadow-map info of the
// object at 0x00DF36B4 through its rowed method.
class FXShaderParameterSourceNamespaceSAS { public: void rva0014F7F2(int value); };
extern FXShaderParameterSourceNamespaceSAS *g_00DF36B4;

class Rva0007DA23ResourceManager
{
public:
	void rva0007B6F3();
};

void Rva0007DA23ResourceManager::rva0007B6F3() { g_00DF36B4->rva0014F7F2(0); }
