// cl: /MD
// ?Rva004DF8D8Test@@YA_NPBUVec2@@00MMMM@Z @0x004DF8D8 133B
// Evidence: EBP-frame SSE comiss/divss/mulss shape; 3 Vec2 ptrs + 4 floats; dot/cross/sum-squared test; caller at 0x0028F38A.
#include "../../Include/Common/Vec2.h"
bool __cdecl Rva004DF8D8Test(const Vec2 *vec2, const Vec2 *origin, const Vec2 *dir, float range, float lateralScale, float rearScale, float f4)
{
	float dx = vec2->x - origin->x;
	float dy = vec2->y - origin->y;
	float dot = dir->x * dx + dy * dir->y;
	float cross = dx * dir->y - dir->x * dy;
	cross /= lateralScale;
	if (dot < 0.0f)
		dot /= rearScale;
	float sum = range + f4;
	float tot = cross * cross + dot * dot;
	float ss = sum * sum;
	if (tot < ss)
		return true;
	return false;
}
