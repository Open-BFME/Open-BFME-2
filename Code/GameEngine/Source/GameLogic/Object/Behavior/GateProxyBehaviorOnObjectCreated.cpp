// cl: /DNDEBUG /MD
//
// ?onObjectCreated@GateProxyBehavior@@UAEXXZ, retail 0x00499475, 5 bytes:
// slot 1 of GateProxyBehavior's ProxyBaseB vtable 0x00BEF304. It extends
// nothing: a tail jump to the rowed GateOpenAndCloseBehavior::onObjectCreated
// 0x0049936A with the same this, the introducing interface's sub-object (no
// adjustment). GateProxyBehavior overrides GateOpenAndCloseBehavior
// (GateProxyBehaviorFloatGetters.cpp); only the interface that introduces
// onObjectCreated is modelled here.

class GateProxyPrimaryView
{
public:
	virtual void p00();
};

class GateProxyCreateInterface
{
public:
	virtual void s00();
	virtual void onObjectCreated();
};

class GateOpenAndCloseBehavior : public GateProxyPrimaryView, public GateProxyCreateInterface
{
public:
	virtual void onObjectCreated();
};

class GateProxyBehavior : public GateOpenAndCloseBehavior
{
public:
	virtual void onObjectCreated();
};

void GateProxyBehavior::onObjectCreated()
{
	GateOpenAndCloseBehavior::onObjectCreated();
}
