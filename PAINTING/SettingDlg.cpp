// SettingDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PAINTING.h"
#include "SettingDlg.h"
#include "afxdialogex.h"
#include "afxwin.h"



// CSettingDlg 对话框

IMPLEMENT_DYNAMIC(CSettingDlg, CDialog)

CSettingDlg::CSettingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSettingDlg::IDD, pParent)
	, m_nLineWidth(0)
	//, m_nLineType(0)
{
	m_clr=RGB(255,0,0);
	memset(&logBrush, 0, sizeof(logBrush));
	logBrush.lbStyle = BS_SOLID;
	logBrush.lbColor = m_clr;	
	m_nLineType=0;
	//m_nLineType=PS_SOLID;
	//DWORD dwF[4] = {5, 10, 15, 20};
}

CSettingDlg::~CSettingDlg()
{
}

void CSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_LINE_WIDTH, m_nLineWidth);
	//  DDX_Radio(pDX, IDC_RADIO2, m_nLineType);
	DDX_Radio(pDX, IDC_RADIO1, m_nLineType);
	//DDX_Radio(pDX, IDC_RADIO2, m_nLineType);
	//DDX_Radio(pDX, IDC_RADIO3, m_nLineType);
}


BEGIN_MESSAGE_MAP(CSettingDlg, CDialog)
	ON_WM_PAINT()
	ON_EN_CHANGE(IDC_LINE_WIDTH, &CSettingDlg::OnEnChangeLineWidth)
	ON_BN_CLICKED(IDC_RADIO1, &CSettingDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CSettingDlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &CSettingDlg::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_SAMPLE, &CSettingDlg::OnBnClickedSample)
//	ON_EN_CHANGE(IDC_RICHEDIT21, &CSettingDlg::OnEnChangeRichedit21)
//	ON_BN_CLICKED(IDC_CHECK1, &CSettingDlg::OnBnClickedCheck1)
END_MESSAGE_MAP()


// CSettingDlg 消息处理程序


void CSettingDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	
		// TODO: 在此处添加消息处理程序代码

		// 不为绘图消息调用 CDialog::OnPaint()
	CPen pen(m_nLineType,m_nLineWidth,m_clr);
	UpdateData();//使控件值的变化能及时反映到相应变量上
	dc.SelectObject(&pen);
	CRect rect;
	GetDlgItem(IDC_SAMPLE)->GetWindowRect(&rect);
	ScreenToClient(rect);//屏幕坐标转换成用户坐标
	dc.MoveTo(rect.left+20,rect.top+rect.Height()/2);
	dc.LineTo(rect.right-20,rect.top+rect.Height()/2);
}


void CSettingDlg::OnEnChangeLineWidth()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

//#1015

	// TODO:  在此添加控件通知处理程序代码
	UpdateData();
    Invalidate();
}


void CSettingDlg::OnBnClickedRadio1()
{
	// TODO: 在此添加控件通知处理程序代码
	//UpdateData();
	//Invalidate();
	//MessageBox(_T("现在可以绘制实线！"));
	//logBrush.lbStyle = BS_SOLID;
	//m_nLineType=logBrush.lbStyle;
	m_nLineType=PS_SOLID;
	//m_nLineType=0;
	UpdateData();
	Invalidate();
	//DWORD dwF[] = {5, 0, 5, 0};
    
}


void CSettingDlg::OnBnClickedRadio2()
{
	// TODO: 在此添加控件通知处理程序代码
	//UpdateData();
	//Invalidate();
	//MessageBox(_T("现在可以绘制虚线！"));
	//LOGBRUSH logBrush;
	//logBrush.lbStyle = PS_DASHDOT;
	m_nLineType=PS_DASH;
	//m_nLineType=1;
	//DWORD dwF[4] = {5, 10, 15, 20};
    UpdateData();
	Invalidate();
}


void CSettingDlg::OnBnClickedRadio3()
{
	// TODO: 在此添加控件通知处理程序代码
	//UpdateData();
	//Invalidate();
	//MessageBox(_T("现在可以绘制点线！"));
	//LOGBRUSH logBrush;
	//logBrush.lbStyle = PS_DOT;
	m_nLineType=PS_DOT;
	//m_nLineType=2;
	//DWORD dwF[4] = {5, 5, 5, 5};
    UpdateData();
	Invalidate();
}


void CSettingDlg::OnBnClickedSample()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
    Invalidate();
}


//void CSettingDlg::OnEnChangeRichedit21()
//{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

//#1015

	// TODO:  在此添加控件通知处理程序代码
//}


//void CSettingDlg::OnBnClickedCheck1()
//{
	// TODO: 在此添加控件通知处理程序代码
//}
