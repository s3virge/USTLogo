
// LogoDlg.h : header file
//

#pragma once


// CLogoDlg dialog
class CLogoDlg : public CDialog
{
	// Construction
public:
	CLogoDlg(CWnd* pParent = NULL);	// standard constructor

	// Dialog Data
	enum { IDD = IDD_Logo_DIALOG };

protected:
	DECLARE_MESSAGE_MAP()
	HICON m_hIcon;
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//меню
	afx_msg void OnGoToSite();
	afx_msg void OnExit();

	void GetSettings();	//получить настройки из файла
	void WriteRegAutorun(); //добавить себя в автозагрузку

private:
	CMenu menu, *m_PopupMenu;
};
