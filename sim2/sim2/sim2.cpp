#include "src/SimulatorCore.h"
#undef main

extern "C" {
	_declspec(dllexport) uint32_t NvOptimusEnablement = 0x00000001;
}

int main()
{
	SimulatorCore simcore(false);
	simcore.start();
	return 0;
}