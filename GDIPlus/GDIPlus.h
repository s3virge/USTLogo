#pragma once

#include <GdiPlus.h>
#pragma comment( lib, "gdiplus.lib" )
using namespace Gdiplus;

namespace GDIPlus
{
	void Initialize(void);
	void Uninitialize(void);
}
