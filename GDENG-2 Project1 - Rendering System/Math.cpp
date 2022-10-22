#include "Math.h"

Math::Math()
{
}

float Math::getRandom(float min, float max)
{
	return (min + 1) + (((float)rand()) / (float)RAND_MAX) * (max - (min + 1));
}

Math::~Math()
{
}
