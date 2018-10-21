#pragma once


// CSettingDlg 对话框

class CSettingDlg : public CDialog
{
	DECLARE_DYNAMIC(CSettingDlg)

public:
	CSettingDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSettingDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	
public:
	afx_msg void OnPaint();
	unsigned int m_nLineWidth;
//	int m_nLineType;
	COLORREF m_clr;
	LOGBRUSH logBrush;
	int m_nLineType;
	afx_msg void OnEnChangeLineWidth();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedSample();
	//DWORD dwF[4];
};
