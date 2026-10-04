// cl: /Os -Ireference/open-bfme-1/game/GameEngine/Source/Common
long roundedProductStride(long first, long second)
{
    return ((first * second + 31) / 32) * 4;
}
