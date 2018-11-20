#pragma once
#include "stdafx.h"

unsigned char* LoadPNGinPath(
	const char *filename, int *width, int *height, int *channels, int force_channels);
