
 
 

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "SameGame.h"
#include "MainFrm.h"

#include "SameGameDoc.h"
#include "SameGameView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


 

BEGIN_MESSAGE_MAP(CSameGameApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CSameGameApp::OnAppAbout)
	 
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
END_MESSAGE_MAP()


 

CSameGameApp::CSameGameApp() noexcept
{
	 
	 
	SetAppID(_T("SameGame.AppID.NoVersion"));

	 
	 
}

 

CSameGameApp theApp;


 

BOOL CSameGameApp::InitInstance()
{
	 
	 
	 
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	 
	 
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	EnableTaskbarInteraction(FALSE);

	
	SetRegistryKey(_T("Локальные приложения, созданные с помощью мастера приложений"));
	LoadStdProfileSettings(4);  


	
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CSameGameDoc),
		RUNTIME_CLASS(CMainFrame),      
		RUNTIME_CLASS(CSameGameView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	
	CMFCToolBar::m_bExtCharTranslation = TRUE;


	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);




	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}






class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg() noexcept;


#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);  


protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() noexcept : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

 
void CSameGameApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

 



