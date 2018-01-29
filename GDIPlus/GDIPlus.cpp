#include "StdAfx.h"
#include "GDIPlus.h"

namespace GDIPlus
{
	ULONG_PTR g_ulGdiPlusToken;
	
	void Initialize(void)
	{
		GdiplusStartupInput stGdiPlusStartupInput;
		::GdiplusStartup( &g_ulGdiPlusToken, &stGdiPlusStartupInput, NULL);
	}

	void Uninitialize(void)
	{
		::GdiplusShutdown(g_ulGdiPlusToken);
	}
}