// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// ?rva0061FFA0@Rva0061FFA0@@QAEXIH@Z
// 0x0061FFA0 42B: small thiscall setter with clamp to 1 0. Stores args at +0x28 +0x2C then keeps them only when second arg positive or first arg nonzero with second zero. Evidence: callers unclaimed 26B. Callees none. Neighbours BfmeThingXS and Rva0061FFD0 in assetmanager.
class Rva0061FFA0
{
public:
	__declspec(noinline) void rva0061FFA0(unsigned int a, int b);
	unsigned char m_pad[0x28];
	unsigned int m_a28;
	int m_b2C;
};

void Rva0061FFA0::rva0061FFA0(unsigned int a, int b)
{
	m_a28 = a;
	m_b2C = b;
	if (b > 0)
		return;
	if (b < 0)
		goto set;
	if (a >= 1)
		return;
set:
	m_a28 = 1;
	m_b2C = 0;
}

// Target [61F1A0,61F1BA),26B: cdecl two-word forwarding operation.
// The shared registry is the same native E09C0C pointer used by the
// separately rowed26B Invoke and21B Begin wrappers. Its original class
// name remains unproved; consume only the rowed42B setter ABI above.
class Gen_009EBA60Target;
extern Gen_009EBA60Target*TheInvokeRegistry;
void forwardRegistrySettingRva0061F1A0(unsigned value,int second) {
 if(TheInvokeRegistry)
  ((Rva0061FFA0*)TheInvokeRegistry)->rva0061FFA0(value,second);
}
