
// LogoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Logo.h"
#include "LogoDlg.h"
//#include "GdiPlusBitmap.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma message( "Compiling " __FILE__ )

// CLogoDlg dialog

//extern int frame; 
int frame = 0;
int iAnimashka = 0;

const int iRepeate = 200; //колличество показов середины картинки 200
int iRepeateCount = 0;

int iInterval = 300; //промежуток между показами 300
int iIntervalCount = 0;

const int iRedrawSpeed = 100; //скорость перерисовки картинки в миллисекундах
const int frameCount = 44; //число кадров

const WCHAR* ImageMove1 = L"C:\\Program Files\\USTLogo\\LogoMove1.png";
const WCHAR* ImageMove2 = L"C:\\Program Files\\USTLogo\\LogoMove2.png";
const WCHAR* ImageMove3 = L"C:\\Program Files\\USTLogo\\LogoMove3.png";

const int iTimerID = 1;

//смещение от нижнего и прового кра€ рабочего стола
int Border = 20;

CRect winRect;
RectF winRectF;

bool bBackGround = true;
bool bRunTimer = false;
bool bAction = true;

//#ifdef _DEBUG
//полезна€ функци€ при отладке
void ErrorExit(LPSTR lpszFunction) 
{ 
	char szBuf[200]; 
	LPVOID lpMsgBuf;
	DWORD dw = GetLastError(); 

	FormatMessageA(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | 
		FORMAT_MESSAGE_FROM_SYSTEM,
		NULL,
		dw,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPSTR) &lpMsgBuf,
		0, NULL );

	wsprintfA(szBuf, "%s failed with error %d: %s", lpszFunction, dw, lpMsgBuf); 

	MessageBoxA(NULL, szBuf, "Error", MB_ICONERROR); 
	TRACE(szBuf);

	LocalFree(lpMsgBuf);
	//ExitProcess(dw); 
}
//#endif

//void DrawAlphaBlend (HWND hWnd, HDC hdcwnd)
//{
//	HDC hdc;               // handle of the DC we will create 
//	BLENDFUNCTION bf;      // structure for alpha blending
//	HBITMAP hbitmap;       // bitmap handle
//	BITMAPINFO bmi;        // bitmap header
//	VOID *pvBits;          // pointer to DIB section
//	ULONG   ulWindowWidth, ulWindowHeight;      // window width/height
//	ULONG   ulBitmapWidth, ulBitmapHeight;      // bitmap width/height
//	RECT    rt;            // used for getting window dimensions
//	UINT32   x,y;          // stepping variables
//	UCHAR ubAlpha;         // used for doing transparent gradient
//	UCHAR ubRed;        
//	UCHAR ubGreen;
//	UCHAR ubBlue;
//	float fAlphaFactor;    // used to do premultiply
//
//	// get window dimensions
//	GetClientRect(hWnd, &rt);
//
//	// calculate window width/height
//	ulWindowWidth = rt.right - rt.left;  
//	ulWindowHeight = rt.bottom - rt.top;  
//
//	// make sure we have at least some window size
//	if ((!ulWindowWidth) || (!ulWindowHeight))
//		return;
//
//	// divide the window into 3 horizontal areas
//	ulWindowHeight = ulWindowHeight / 3;
//
//	// create a DC for our bitmap -- the source DC for AlphaBlend 
//	hdc = CreateCompatibleDC(hdcwnd);
//
//	// zero the memory for the bitmap info
//	ZeroMemory(&bmi, sizeof(BITMAPINFO));
//
//	// setup bitmap info 
//	// set the bitmap width and height to 60% of the width and height of each of the three horizontal areas. Later on, the blending will occur in the center of each of the three areas.
//	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
//	bmi.bmiHeader.biWidth = ulBitmapWidth = ulWindowWidth - (ulWindowWidth/5)*2;
//	bmi.bmiHeader.biHeight = ulBitmapHeight = ulWindowHeight - (ulWindowHeight/5)*2;
//	bmi.bmiHeader.biPlanes = 1;
//	bmi.bmiHeader.biBitCount = 32;         // four 8-bit components
//	bmi.bmiHeader.biCompression = BI_RGB;
//	bmi.bmiHeader.biSizeImage = ulBitmapWidth * ulBitmapHeight * 4;
//
//	// create our DIB section and select the bitmap into the dc
//	hbitmap = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, &pvBits, NULL, 0x0);
//	SelectObject(hdc, hbitmap);
//
//	// in top window area, constant alpha = 50%, but no source alpha
//	// the color format for each pixel is 0xaarrggbb 
//	// set all pixels to blue and set source alpha to zero
//	for (y = 0; y < ulBitmapHeight; y++)
//		for (x = 0; x < ulBitmapWidth; x++)
//			((UINT32 *)pvBits)[x + y * ulBitmapWidth] = 0x000000ff; 
//
//	bf.BlendOp = AC_SRC_OVER;
//	bf.BlendFlags = 0;
//	bf.SourceConstantAlpha = 0x7f;  // half of 0xff = 50% transparency
//	bf.AlphaFormat = 0;             // ignore source alpha channel
//
//	if (!AlphaBlend(hdcwnd, ulWindowWidth/5, ulWindowHeight/5, 
//		ulBitmapWidth, ulBitmapHeight, 
//		hdc, 0, 0, ulBitmapWidth, ulBitmapHeight, bf))
//		return;                     // alpha blend failed
//
//	//-------------------------------------------------------------------------------------
//
//	// in middle window area, constant alpha = 100% (disabled), source 
//	// alpha is 0 in middle of bitmap and opaque in rest of bitmap 
//	for (y = 0; y < ulBitmapHeight; y++)
//		for (x = 0; x < ulBitmapWidth; x++)
//			if ((x > (int)(ulBitmapWidth/5)) && (x < (ulBitmapWidth-ulBitmapWidth/5)) &&
//				(y > (int)(ulBitmapHeight/5)) && (y < (ulBitmapHeight-ulBitmapHeight/5)))
//				//in middle of bitmap: source alpha = 0 (transparent).
//				// This means multiply each color component by 0x00.
//				// Thus, after AlphaBlend, we have a, 0x00 * r, 
//				// 0x00 * g,and 0x00 * b (which is 0x00000000)
//				// for now, set all pixels to red
//				((UINT32 *)pvBits)[x + y * ulBitmapWidth] = 0x00ff0000; 
//			else
//				// in the rest of bitmap, source alpha = 0xff (opaque) 
//				// and set all pixels to blue 
//				((UINT32 *)pvBits)[x + y * ulBitmapWidth] = 0xff0000ff; 
//	//endif;
//
//	bf.BlendOp = AC_SRC_OVER;
//	bf.BlendFlags = 0;
//	bf.AlphaFormat = AC_SRC_ALPHA;  // use source alpha 
//	bf.SourceConstantAlpha = 0xff;  // opaque (disable constant alpha)
//
//	if (!AlphaBlend(hdcwnd, ulWindowWidth/5, ulWindowHeight/5+ulWindowHeight, ulBitmapWidth, ulBitmapHeight, hdc, 0, 0, ulBitmapWidth, ulBitmapHeight, bf))
//		return;
//
//	//-------------------------------------------------------------------------------------
//
//	// bottom window area, use constant alpha = 75% and a changing
//	// source alpha. Create a gradient effect using source alpha, and 
//	// then fade it even more with constant alpha
//	ubRed = 0x00;
//	ubGreen = 0x00;
//	ubBlue = 0xff;
//
//	for (y = 0; y < ulBitmapHeight; y++)
//		for (x = 0; x < ulBitmapWidth; x++)
//		{
//			// for a simple gradient, base the alpha value on the x 
//			// value of the pixel 
//			ubAlpha = (UCHAR)((float)x / (float)ulBitmapWidth * 255);
//			//calculate the factor by which we multiply each component
//			fAlphaFactor = (float)ubAlpha / (float)0xff; 
//			// multiply each pixel by fAlphaFactor, so each component 
//			// is less than or equal to the alpha value.
//			((UINT32 *)pvBits)[x + y * ulBitmapWidth] 
//			= (ubAlpha << 24) |                       //0xaa000000
//				((UCHAR)(ubRed * fAlphaFactor) << 16) |  //0x00rr0000
//				((UCHAR)(ubGreen * fAlphaFactor) << 8) | //0x0000gg00
//				((UCHAR)(ubBlue   * fAlphaFactor));      //0x000000bb
//		}
//
//		bf.BlendOp = AC_SRC_OVER;
//		bf.BlendFlags = 0;
//		bf.AlphaFormat = AC_SRC_ALPHA;   // use source alpha 
//		bf.SourceConstantAlpha = 0xbf;   // use constant alpha, with 
//		// 75% opaqueness
//
//		AlphaBlend(hdcwnd, ulWindowWidth/5, 
//			ulWindowHeight/5+2*ulWindowHeight, ulBitmapWidth, 
//			ulBitmapHeight, hdc, 0, 0, ulBitmapWidth, 
//			ulBitmapHeight, bf);
//
//		// do cleanup
//		DeleteObject(hbitmap);
//		DeleteDC(hdc);
//
//}
//
//void DrawFish(Graphics& g)
//{
//	//The Clear method clears a Graphics object to a specified color.
//	Color bgrColor(255, 200, 200, 200);
//	g.Clear(bgrColor);
//
//	// Create an Image object.
//	Image image(ImageMove1);
//
//	int frameWidth = image.GetWidth() / frameCount; //ширина одного изображени€
//	int frameHeight = image.GetHeight();    //высота
//	//------------------------------------------------------------
//
//	//image [in] Pointer to an Image object that specifies the source image. 
//	REAL x; //	[in] Real number that specifies the x-coordinate of the upper-left corner of the destination position at which to draw the image. 
//	REAL y; //	[in] Real number that specifies the y-coordinate of the upper-left corner of the destination position at which to draw the image. 
//	REAL srcx; //	[in] Real number that specifies the x-coordinate of the upper-left corner of the portion of the source image to be drawn. 
//	REAL srcy; //	[in] Real number that specifies the y-coordinate of the upper-left corner of the portion of the source image to be drawn. 
//	REAL srcwidth; //[in] Real number that specifies the width of the portion of the source image to be drawn. 
//	REAL srcheight;//[in] Real number that specifies the height of the portion of the source image to be drawn. 
//	//srcUnit	[in] Element of the Unit enumeration that specifies the unit of measure for the image. The default value is UnitPixel. 
//
//	x = 0;
//	y = 0;
//	srcx = frameWidth;
//	srcy = 0;
//
//	srcwidth = frameWidth;
//	srcheight = frameHeight;	
//
//	g.DrawImage(&image, x, y, srcx, srcy, srcwidth, srcheight, UnitPixel);
//}
//

void UseUpdateLayeredWindow(CWnd* wnd)
{
	// «агружаем 32-битный PNG с альфа каналом и получаем его HBITMAP
	Bitmap* img = NULL;
	
	HINSTANCE hInst = AfxGetInstanceHandle();

	if (!hInst)
		return;

	switch( iAnimashka )
	{
	case 0:
		//img = Bitmap::FromResource(hInst, MAKEINTRESOURCEW(IDB_PNGMOVE1));
		
		img = Bitmap::FromFile(ImageMove1);
		break;

	case 1:
		img = Bitmap::FromFile(ImageMove2);		
		break;

	case 2:
		img = Bitmap::FromFile(ImageMove3);
		break;
	}

	//img = Bitmap::FromResource(hInst, ImageMove3);
	
	HBITMAP hBmp = 0; // ѕрозрачна€ картинка   
	if ( img->GetHBITMAP(0, &hBmp) != Status::Ok) //hbmp = [out] Pointer to an HBITMAP that receives a handle to the GDI bitmap.
		ErrorExit("GetHBITMAP()");

	//------------------------------------------------------------------

	// ѕолучаем контекст экрана  
	HDC screendc = ::GetDC(wnd->m_hWnd); 

	if (!screendc)
		ErrorExit("GetDC()");

	// —оздаем контекст, совместимый с экраном 
	HDC backdc = ::CreateCompatibleDC(screendc);

	if (!backdc)
		ErrorExit("CreateCompatibleDC()");

	// «агружаем в него картинку 
	HGDIOBJ OldBmp = ::SelectObject(backdc, hBmp); 

	//-------------------------------------------------------------------

	// если дошли до последнего кадра, то задержимс€ на нем
	if (frame == frameCount - 1)
	{
		iIntervalCount++;

		if (iInterval >= iIntervalCount)
		{
			TRACE("goto proceed: iIntervalCount = %d, iInterval = %d \n", iIntervalCount, iInterval);
			goto proceed; //перепрыгиваем через сдвиг на следующий кадр
		}

		/* initialize random seed: */
		//srand ( time(NULL) );
		iInterval = ((rand()%600) + 600)* 10;
		iIntervalCount = 0;
		TRACE("iIntervalCount = %d сек ", iInterval);
	}

	if (frame < (frameCount-1))
	{
		//если добарлись до середины
		if (frame == frameCount / 2)
		{
			iRepeateCount++;

			if (iRepeate >= iRepeateCount)
			{
				//TRACE("goto proceed: iRepeateCount = %d, iRepeate = %d \n", iRepeateCount, iRepeate);
				goto proceed; //прыгаем на продолжение
			}
		}
		//то покажем ее N раз
		frame++;		
	}	
	else
	{
		frame = 0;
		iRepeateCount = 0;
		iAnimashka = rand()%3; //мен€ем анимашки
		TRACE(" после rand iAnimashka = %d\n", iAnimashka);
	}

proceed:	

	//TRACE("frame = %d\n", frame);

	//-------------------------------------------------------------------

	CRect rect(0, 0, 0, 0);
	//::GetWindowRect(GetDesktopWindow(), &rect); //получить разрешение экрана
	SystemParametersInfo(SPI_GETWORKAREA, 0, &rect, 0); //получить размер рабочего стола

	POINT pptDst, pptSrc; 

	int ImgWidth =  img->GetWidth();
	int ImgHeight = img->GetHeight();

	//	[in] Pointer to a POINT structure that specifies the new screen position of the layered window. 
	//	If the current position is not changing, pptDst can be NULL. 
	//pptDst.x = rect.Width()/2;


	//разместим изображение в правом нижнем углу рабочего стола
	pptDst.x = rect.Width()-(ImgWidth/frameCount) - Border;
	pptDst.y = rect.Height()-ImgHeight - Border;

	//pptSrc
	//	[in] Pointer to a POINT structure that specifies the location of the layer in the device context. 
	//If hdcSrc is NULL, pptSrc should be NULL.
	//вычислить какой кадр изображени€ показывать
	pptSrc.x = ImgWidth/frameCount * frame; 
	pptSrc.y = 0;

	//Pointer to a SIZE structure that specifies the new size of the layered window
	SIZE sz;
	sz.cx = ImgWidth/frameCount; 
	sz.cy = ImgHeight;

	BLENDFUNCTION bf = {AC_SRC_OVER, 0, 255, AC_SRC_ALPHA};      // structure for alpha blending

	//Updates the position, size, shape, content, and translucency of a layered window.
	if (!::UpdateLayeredWindow(wnd->m_hWnd, screendc, /*NULL*/&pptDst, &sz, backdc, &pptSrc, 0, &bf, ULW_ALPHA))
	{
		ErrorExit("UpdateLayeredWindow()");
		::PostQuitMessage(0);
	}

	::SelectObject(backdc, OldBmp);
	DeleteDC(backdc);
	DeleteObject(hBmp);
	::ReleaseDC(wnd->m_hWnd, screendc);
	delete img;
}


//void GraduallyShowHideWindow(HWND hWnd, bool bShowHide) 
//{
//	const int LayeredWindowShowHideSpeed = 100;
//	//если true то показываем окно
//	if (bShowHide)
//	{		
//		for(int c = 0; c <= 100; c += 5)
//		{
//			SetLayeredWindowAttributes(hWnd, 0, (255 * c) / 100, LWA_ALPHA);
//			::Sleep(LayeredWindowShowHideSpeed);
//			UpdateWindow(hWnd);
//		}	
//	}
//	//если false
//	else
//	{
//		for(int c = 100; c >= 0; c -= 5)
//		{
//			SetLayeredWindowAttributes(hWnd, 0, (255 * c) / 100, LWA_ALPHA);
//			::Sleep(LayeredWindowShowHideSpeed);
//			UpdateWindow(hWnd);	
//		}	
//	}
//}
CLogoDlg::CLogoDlg(CWnd* pParent /*=NULL*/)
: CDialog(CLogoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	frame = 0;
	// «агружаем меню из ресурсов
	menu.LoadMenu(IDR_CONTEXTMENU);
	m_PopupMenu = menu.GetSubMenu(0);
}

void CLogoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CLogoDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(IDM_GOTOSITE, &CLogoDlg::OnGoToSite)
	ON_COMMAND(IDM_EXIT, &CLogoDlg::OnExit)
END_MESSAGE_MAP()


// CLogoDlg message handlers

BOOL CLogoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon	

	SetTimer(iTimerID, iRedrawSpeed, 0); //скорость перерисовки

	WriteRegAutorun();	

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CLogoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	CDialog::OnSysCommand(nID, lParam);
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CLogoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);		
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CLogoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CLogoDlg::OnTimer(UINT_PTR nIDEvent)
{
	UseUpdateLayeredWindow(this);

	CDialog::OnTimer(nIDEvent);
}

void CLogoDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	//Move the window while you drag it
	PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x,point.y));

	CDialog::OnLButtonDown(nFlags, point);
}

void CLogoDlg::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	KillTimer(iTimerID);
	OnCancel();

	CDialog::OnLButtonDblClk(nFlags, point);
}

void CLogoDlg::GetSettings()
{

}

void CLogoDlg::WriteRegAutorun()
{
	//получить путь к запускаемому процессу
	//получить путь к программе 
	char szPath[MAX_PATH] = "0"; 
	CString csCommand;

	GetModuleFileNameA( NULL, szPath, MAX_PATH );

	//к пути прибавл€ем комманду на задержку запуска
	//csCommand.Format("\"%s\" /w", szPath);
	//strcpy_s(szPath, MAX_PATH, csCommand.GetString());

	HKEY hKey;		
	LPCSTR lpSubKey = "Software\\Microsoft\\Windows\\CurrentVersion\\Run";

	if (RegCreateKeyExA(HKEY_LOCAL_MACHINE, lpSubKey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKey, NULL)== ERROR_SUCCESS)
	{	
		RegSetValueExA(hKey, "Logo", 0, REG_SZ, (BYTE*) szPath, strlen(szPath)+1);
	
		RegCloseKey(hKey);		
	}
	else
	{
		ErrorExit("RegCreateKeyExA()");
	}
}
void CLogoDlg::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{    
	// ќтображаем меню
	m_PopupMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this, NULL);	
}
void CLogoDlg::OnGoToSite()
{
	if((UINT)ShellExecute(
		NULL,
		"open",
		"http://ust.lg.ua/",
		NULL,
		NULL,
		SW_SHOWNORMAL) <= 32) 
	{
		// обработка ошибок
	}
}

void CLogoDlg::OnExit()
{
	KillTimer(iTimerID);
	OnCancel();
}
