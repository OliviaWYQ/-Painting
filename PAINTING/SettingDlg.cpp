// SettingDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PAINTING.h"
#include "SettingDlg.h"
#include "afxdialogex.h"
#include "afxwin.h"



// CSettingDlg �Ի���

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


// CSettingDlg ��Ϣ�������


void CSettingDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	
		// TODO: �ڴ˴������Ϣ����������

		// ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()
	CPen pen(m_nLineType,m_nLineWidth,m_clr);
	UpdateData();//ʹ�ؼ�ֵ�ı仯�ܼ�ʱ��ӳ����Ӧ������
	dc.SelectObject(&pen);
	CRect rect;
	GetDlgItem(IDC_SAMPLE)->GetWindowRect(&rect);
	ScreenToClient(rect);//��Ļ����ת�����û�����
	dc.MoveTo(rect.left+20,rect.top+rect.Height()/2);
	dc.LineTo(rect.right-20,rect.top+rect.Height()/2);
}


void CSettingDlg::OnEnChangeLineWidth()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

//#1015

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
    Invalidate();
}


void CSettingDlg::OnBnClickedRadio1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//UpdateData();
	//Invalidate();
	//MessageBox(_T("���ڿ��Ի���ʵ�ߣ�"));
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//UpdateData();
	//Invalidate();
	//MessageBox(_T("���ڿ��Ի������ߣ�"));
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//UpdateData();
	//Invalidate();
	//MessageBox(_T("���ڿ��Ի��Ƶ��ߣ�"));
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
    Invalidate();
}


//void CSettingDlg::OnEnChangeRichedit21()
//{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

//#1015

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
//}


//void CSettingDlg::OnBnClickedCheck1()
//{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
//}
