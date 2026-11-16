// cl: /Ireference/shims/bfmecamera /DNDEBUG /MD /EHs-c- /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2
// DynamicVectorClass::Add of an 8-byte record whose second word is a COM
// pointer (AddRef slot 1, Release slot 2).

#include "BfmeSurfaceResource.h"
#include "W3DSurfaceClass.h"

struct Gen_0093E730_Elem
{
	void *first;
	BfmeSurfaceResource *surface;
};

class Gen_0093E730
{
public:
	virtual bool Equal(const Gen_0093E730 &that) const;
	virtual bool Unused(void);
	virtual bool Resize(int count, const Gen_0093E730_Elem *array);
	bool Add(const Gen_0093E730_Elem &object);
	bool rva001558D0(int index);

private:
	Gen_0093E730_Elem *vector;
	int vector_max;
	bool is_valid;
	bool is_allocated;
	bool pad[2];
	int active_count;
	int growth_step;
};

bool Gen_0093E730::Add(const Gen_0093E730_Elem &object)
{
	if (active_count >= vector_max) {
		if ((is_allocated || !vector_max) && growth_step > 0) {
			if (!Resize(vector_max + growth_step, 0))
				return false;
		} else {
			return false;
		}
	}

	int index = active_count;
	active_count = index + 1;
	Gen_0093E730_Elem *slot = &vector[index];
	slot->first = object.first;
	BfmeSurfaceResource *incoming = object.surface;
	if (incoming)
		incoming->AddRef();
	BfmeSurfaceResource *outgoing = slot->surface;
	if (outgoing)
		outgoing->Release();
	slot->surface = object.surface;
	return true;
}

bool Gen_0093E730::rva001558D0(int index)
{
	if (index < active_count) {
		--active_count;
		if (index < active_count) {
			for (int i = index; i < active_count; ++i) {
				Gen_0093E730_Elem *slot = &vector[i];
				Gen_0093E730_Elem *next = slot + 1;
				slot->first = next->first;
				BfmeSurfaceResource *incoming = next->surface;
				if (incoming)
					incoming->AddRef();
				BfmeSurfaceResource *outgoing = slot->surface;
				if (outgoing)
					outgoing->Release();
				slot->surface = next->surface;
			}
		}
		return true;
	}
	return false;
}
