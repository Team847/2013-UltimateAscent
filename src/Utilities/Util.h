#ifndef UTIL_H
#define UTIL_H

class Util {
public:
	static float lerp(float out1, float out2, float value);
	static float lerp(float in1, float in2, float out1, float out2, float value);
};

#endif
