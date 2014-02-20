#include "Util.h"

float Util::lerp(float out1, float out2, float value) {
	return lerp(0.0f, 1.0f, out1, out2, value);
}

float Util::lerp(float v1, float v2, float a1, float a2, float cv) {
	return (a2 - a1) / (v2 - v1) * (cv - v1) + a1;
}
