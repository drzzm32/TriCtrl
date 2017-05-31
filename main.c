#include "util.h"

void main() {
	pwmInit();
	
	LED = 0;
	delay(10);
	LED = 1;
	
	while (1) {
		P3 = 0xFF;
		posA = (CTL_A ? CTL_V : 0);
		posB = (CTL_B ? CTL_V : 0);
		posC = (CTL_C ? CTL_V : 0);
	}
}