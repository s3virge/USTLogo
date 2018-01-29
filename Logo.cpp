
// Logo.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Logo.h"
#include "LogoDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLogoApp

BEGIN_MESSAGE_MAP(CLogoApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CLogoApp construction

CLogoApp::CLogoApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CLogoApp object

CLogoApp theApp;


// CLogoApp initialization

BOOL CLogoApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	//----- запускае GDI+ -----
	GDIPlus::Initialize();

	//GetCommand();

	CLogoDlg dlg;
	m_pMainWnd = &dlg;

	INT_PTR nResponse = dlg.DoModal();
	//if (nResponse == IDOK)
	//{
	//	// TODO: Place code here to handle when the dialog is
	//	//  dismissed with OK
	//}
	//else if (nResponse == IDCANCEL)
	//{
	//	// TODO: Place code here to handle when the dialog is
	//	//  dismissed with Cancel
	//}

	//// Since the dialog has been closed, return FALSE so that we exit the
	////  application, rather than start the application's message pump.
	return FALSE;
}

int CLogoApp::ExitInstance()
{
	//------ завершаем использование GDI+ -----
	GDIPlus::Uninitialize();

	return CWinApp::ExitInstance();
}

//bool CLogoApp::GetCommand()
//{	
//	LPWSTR *szArglist;
//	int nArgs;
//	int i;
//	char buffer[MAX_PATH];
//	
//	szArglist = CommandLineToArgvW(GetCommandLineW(), &nArgs);
//
//	if( NULL == szArglist )
//	{
//		AfxMessageBox("CommandLineToArgvW failed");
//	}
//	else
//	{
//		for( i = 1; i < nArgs; i++)
//		{
//			sprintf(buffer, "%ws", szArglist[i]);
//
//			//добавить себя в автозагрузку
//			if(strcmp("/w", buffer) == 0)
//			{
//				//если Wait, то сделать паузу 
//				int iPauseMin = 5; //сколько минут
//				iPauseMin *= 60000; //преобразовываем в миллисекунды
//				
//				Sleep(iPauseMin);
//			}
//		}
//	}
//
//	// Free memory allocated for CommandLineToArgvW arguments.
//	LocalFree(szArglist);
//
//	return false;
//}
