#ifndef ZERGLINGCLAWS_H
#define ZERGLINGCLAWS_H
#include "WPILib.h"
#include "../OI.h"

class ZerglingClaws {
private:
	OI *oI;
public:
	ZerglingClaws();
	void clawsForward(void);
	void clawsBackward(void);
};

#endif
