// cl: /Os -Ireference/open-bfme-1/game/GameEngine/Source/Common
struct RvaA0380ByteThresholdThunk
{
    unsigned char unused;
    unsigned char value;

    bool isAtLeast(int threshold) const;
};

bool RvaA0380ByteThresholdThunk::isAtLeast(int threshold) const
{
    return value >= threshold;
}
