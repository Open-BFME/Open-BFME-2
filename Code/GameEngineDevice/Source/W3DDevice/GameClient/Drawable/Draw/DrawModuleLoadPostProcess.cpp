// Existing W3DLaserDraw post-load directly calls B3FD0. ZH base hook
// is empty; one-byte RET is a genuine relocation-free folded body.
// cl: /O1 /G7 /arch:SSE /MD
class Thing;class ModuleData;class Drawable;class Xfer;
class DrawableModule{public:DrawableModule(Thing*,const ModuleData*);virtual~DrawableModule();void xfer(Xfer*);protected:const ModuleData*m_moduleData;Drawable*m_drawable;};
class DrawModule:public DrawableModule{public:DrawModule(Thing*,const ModuleData*);protected:virtual void loadPostProcess();virtual void xfer(Xfer*);};
void DrawModule::loadPostProcess(){}
