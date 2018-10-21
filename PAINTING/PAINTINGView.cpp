
// PAINTINGView.cpp : CPAINTINGView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "PAINTING.h"
#endif

#include "PAINTINGDoc.h"
#include "PAINTINGView.h"
#include "SettingDlg.h"
#include "afxwin.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPAINTINGView

IMPLEMENT_DYNCREATE(CPAINTINGView, CView)

BEGIN_MESSAGE_MAP(CPAINTINGView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CPAINTINGView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_32772, &CPAINTINGView::OnLine)
	ON_COMMAND(ID_32773, &CPAINTINGView::OnCLine)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_32774, &CPAINTINGView::OnRec)
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_32775, &CPAINTINGView::OnSector)
	ON_COMMAND(ID_32776, &CPAINTINGView::OnNoSector)
	ON_COMMAND(ID_32777, &CPAINTINGView::OnEcllipse)
	ON_COMMAND(ID_32778, &CPAINTINGView::OnColor)
	ON_COMMAND(ID_32780, &CPAINTINGView::OnFont)
	ON_COMMAND(ID_32781, &CPAINTINGView::OnShowLstylewidth)
	ON_COMMAND(ID_32782, &CPAINTINGView::OnRec2)
END_MESSAGE_MAP()

// CPAINTINGView ����/����

CPAINTINGView::CPAINTINGView()
	: m_nLineWidth(0)
	//, m_nLineType(0)
{
	// TODO: �ڴ˴���ӹ������
	DrawType dType=NoDraw;
	m_clr=RGB(0,255,0);
	memset(&logBrush, 0, sizeof(logBrush));
	logBrush.lbStyle = BS_SOLID;
	logBrush.lbColor = m_clr;
	m_nLineType=PS_SOLID;
	//m_nLineType=0;
	
	DWORD dwF[4] = {5, 0, 5, 0};
}

CPAINTINGView::~CPAINTINGView()
{
}

BOOL CPAINTINGView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CPAINTINGView ����

void CPAINTINGView::OnDraw(CDC*pDC)
{
	CPAINTINGDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	CFont *pOldFont=pDC->SelectObject(&m_font);
	pDC->TextOut(0,0,m_strFontName);
	pDC->SelectObject(pOldFont);

	if (m_font.m_hObject)
		m_font.DeleteObject();

	CRect rect;
	GetClientRect(&rect);
	CDC dcMem;//���������λͼ�ı�׼����
	CBitmap *pOldBitmap = NULL;
	dcMem.CreateCompatibleDC(NULL);
	pOldBitmap = dcMem.SelectObject(&pDoc->m_bmpBuf);
 
	pDC->BitBlt(0,0,rect.Width(),rect.Height(),&dcMem,0,0,SRCCOPY);
	dcMem.SelectObject(pOldBitmap); //��dcMeM�е�bitmap��������ǰ�ͻ���
	dcMem.DeleteDC();
}


// CPAINTINGView ��ӡ


void CPAINTINGView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CPAINTINGView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CPAINTINGView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CPAINTINGView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void CPAINTINGView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CPAINTINGView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CPAINTINGView ���

#ifdef _DEBUG
void CPAINTINGView::AssertValid() const
{
	CView::AssertValid();
}

void CPAINTINGView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPAINTINGDoc* CPAINTINGView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPAINTINGDoc)));
	return (CPAINTINGDoc*)m_pDocument;
}
#endif //_DEBUG


// CPAINTINGView ��Ϣ�������


void CPAINTINGView::OnLine()
{
	// TODO: �ڴ���������������
	dType=SLine;
	//MessageBox(_T("���ڿ��Ի���ֱ�ߣ�"));
}


void CPAINTINGView::OnCLine()
{
	// TODO: �ڴ���������������
	//MessageBox(_T("���ڿ��Ի����������ߣ�"));
	 dType=CLine;
}


void CPAINTINGView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	
	switch (dType)
	{
		case SLine:
			m_bDraw=TRUE;
	        m_ptOrigin=point;
			break;
		case CLine:
	        m_bDraw=TRUE;
	        m_ptOrigin=point;
			break;
		case NoSector:
			m_bDraw=TRUE;
	        m_ptOrigin=point;
			break;
		case Sector:
            m_bDraw=TRUE;
	        m_ptOrigin=point;
			m_ptNext=point;
			break;
		case Recta:
            m_bDraw=TRUE;
	        m_ptOrigin=point;
			break;
		case Ecllipse:
            m_bDraw=TRUE;
	        m_ptOrigin=point;
			break;
		case Recta2:
			m_bDraw=TRUE;
	        m_ptOrigin=point;
			break;
		default:
	          break;
		}
	CView::OnLButtonDown(nFlags, point);
}


void CPAINTINGView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CPen pen(m_nLineType,m_nLineWidth,m_clr);
	//m_nLineType=0;
	/*if(m_nLineType=0)
		{
			m_nLineType=PS_SOLID;
			//CPen pen(PS_SOLID,m_nLineWidth,m_clr); 

		}
	else 
	{
		if(m_nLineType=1)
			{
				m_nLineType=PS_DASH;
				//CPen pen(PS_DASH,m_nLineWidth,m_clr); 

			}
		else
			m_nLineType=PS_DOT;
			//CPen pen(PS_DOT,m_nLineWidth,m_clr); 
		
	}*/

	/*CPen myPen1;
	myPen1.CreatePen(m_nLineType, m_nLineWidth, m_clr);
	CClientDC dc(this);
	dc.SelectObject(&myPen1);
	CPen *pOldPen=dc.SelectObject(&myPen1);*/

	/*
	CPen myPen2;
	
	//DWORD dwF[4] = {5, 10, 15, 20};
	
	if(m_nLineType=PS_SOLID)
		{
			DWORD dwF[4] = {5, 0, 5, 0};
		}
	if(m_nLineType=PS_DASH)
		{
			DWORD dwF[4] = {5, 10, 15, 20};
		}
	if(m_nLineType=PS_DOT)
		{
			DWORD dwF[4] = {5, 5, 5, 5};
		}

	//myPen2.CreatePen(PS_USERSTYLE|PS_GEOMETRIC|PS_ENDCAP_FLAT, m_nLineWidth, &logBrush,4,dwF);
	myPen2.CreatePen(PS_USERSTYLE, m_nLineWidth, &logBrush,4,dwF);
	CClientDC dc(this);
	dc.SelectObject(&myPen2);
	CPen *pOldPen=dc.SelectObject(&myPen2);*/

	//CPen pen(m_nLineType,m_nLineWidth,m_clr); 
	CClientDC dc(this);
	dc.SelectObject(&pen);
	//CPen pen(PS_SOLID,2,RGB(255,255,0));
	CPen *pOldPen=dc.SelectObject(&pen);

    CBitmap bitmap; 
	bitmap.LoadBitmap(IDB_BITMAP2);
	CBrush brush(&bitmap);
	CBrush *pBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
	CBrush *pOldBrush=dc.SelectObject(pBrush);

	switch (dType)
	{
        case SLine:
	         dc.MoveTo(m_ptOrigin);
	         dc.LineTo(point);
	         break;
		case Recta:
             dc.FillRect(CRect(m_ptOrigin,point),&brush);
			 break;
		case Ecllipse:
			 dc.Ellipse(CRect(m_ptOrigin,point));
			 break;
		case Recta2:
			 dc.Rectangle(CRect(m_ptOrigin,point));
			 break;
		default:
	         break;
	 }
    m_bDraw=FALSE;
	dc.SelectObject(pOldPen);
	dc.SelectObject(pOldBrush);

	CDC *pDC = GetDC();
	CPAINTINGDoc* pDoc = GetDocument();
	CDC dcMem;
	dcMem.CreateCompatibleDC(NULL);
	CRect rect;
	GetClientRect(&rect); //��ȡ�ͻ�����
	pDoc->m_bmpBuf.DeleteObject();
	pDoc->m_bmpBuf.CreateCompatibleBitmap(pDC,rect.Width(),rect.Height());
	CBitmap *pOldBitmap = dcMem.SelectObject(&pDoc->m_bmpBuf);//�������õ�m_bmpBuf��ӵ���ʱ��CDC��Object�У���������ǽ���Ⱥ���ǽֽ^_^������ǽֽ����������������γɵĻ�������ǽ�ϡ�
	
	m_ptEnd = point;
	dcMem.BitBlt(0,0,rect.Width(),rect.Height(),pDC,0,0,SRCCOPY);
	dcMem.SelectObject(pOldBitmap); //��pDC����ǰ�ͻ�����������ݿ�������ʱ��MEM�У�MEM��Ȼ����ᱻdelete����������������CDocument���е�m_bmpBuf
	m_bDraw = false;
	dcMem.DeleteDC();

	CView::OnLButtonUp(nFlags, point);
}


void CPAINTINGView::OnRec()
{
	// TODO: �ڴ���������������
	dType=Recta;
	//MessageBox(_T("���ڿ��Ի��ƾ��Σ�"));
}


void CPAINTINGView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	
	CPen pen(m_nLineType,m_nLineWidth,m_clr);
	/*if(m_nLineType=0)
		{
			m_nLineType=PS_SOLID;
		}
	else 
	{
		if(m_nLineType=1)
			{
				m_nLineType=PS_DASH;
				//CPen pen(PS_DASH,m_nLineWidth,m_clr); 

			}
		else
			m_nLineType=PS_DOT;
			//CPen pen(PS_DOT,m_nLineWidth,m_clr); 
		
	}*/

	/*CPen myPen1;
	myPen1.CreatePen(m_nLineType, m_nLineWidth, m_clr);*/
	/*CClientDC dc(this);
	dc.SelectObject(&myPen1);
	CPen *pOldPen=dc.SelectObject(&myPen1);*/

	/*CPen myPen2;

	//DWORD dwF[4] = {5, 0, 5, 0};

	if(m_nLineType=0)
		{
			dwF[0]=5;
			dwF[1]=0;
			dwF[2]=5;
			dwF[3]=0;
		}
	else 
		{
			if(m_nLineType=1)
			{
				dwF[0]=5;
				dwF[1]=10;
				dwF[2]=15;
				dwF[3]=20;
			}
			else
			{
				dwF[0]=5;
				dwF[1]=5;
				dwF[2]=5;
				dwF[3]=5;
			}
		}
	
	//logBrush.lbStyle = BS_SOLID;
	//logBrush.lbColor=m_clr;
	myPen2.CreatePen(PS_USERSTYLE|PS_GEOMETRIC|PS_ENDCAP_FLAT, m_nLineWidth, &logBrush,4,dwF);
	//myPen2.CreatePen(PS_USERSTYLE, m_nLineWidth, &logBrush,4,dwF);
	CClientDC dc(this);
	dc.SelectObject(&myPen2);
	CPen *pOldPen=dc.SelectObject(&myPen2);*/


	//CPen pen(m_nLineType,m_nLineWidth,m_clr); 
	//CPen pen(PS_SOLID,2,RGB(255,255,0));
	CClientDC dc(this);
	dc.SelectObject(&pen);
	CPen *pOldPen=dc.SelectObject(&pen);
	
	if(m_bDraw)
	{
		switch (dType)  
		{
			case CLine:
				 dc.MoveTo(m_ptOrigin);
		         dc.LineTo(point);
				 m_ptOrigin=point;
		         break;
		    case NoSector:
		         dc.MoveTo(m_ptOrigin);
		         dc.LineTo(point);
		         break;
			case Sector:
				 dc.MoveTo(m_ptOrigin);
		         dc.LineTo(point);
				 dc.LineTo(m_ptNext);
				 m_ptNext=point;
				 break;
	    default:
		         break;
		}
	}
	dc.SelectObject(pOldPen);
	CView::OnMouseMove(nFlags, point);
}


void CPAINTINGView::OnSector()
{
	// TODO: �ڴ���������������
	//MessageBox(_T("���ڿ��Ի����б߽����Σ�"));
	dType=Sector;
}


void CPAINTINGView::OnNoSector()
{
	// TODO: �ڴ���������������
	//MessageBox(_T("���ڿ��Ի����ޱ߽����Σ�"));
	dType=NoSector;
}


void CPAINTINGView::OnEcllipse()
{
	// TODO: �ڴ���������������
	//MessageBox(_T("���ڿ��Ի�����Բ��"));
	dType=Ecllipse;
}


void CPAINTINGView::OnColor()
{
	// TODO: �ڴ���������������
	dType=ColorSet;
	CColorDialog dlg;
	if(IDOK==dlg.DoModal())
		{
			m_clr=dlg.m_cc.rgbResult;
			logBrush.lbColor=m_clr;
			
		}

}


void CPAINTINGView::OnFont()
{
	// TODO: �ڴ���������������
	CFontDialog dlg;
	//UpdateData();
	if(IDOK==dlg.DoModal())
	{
		if (m_font.m_hObject)     
			m_font.DeleteObject();
		m_font.CreateFontIndirect(dlg.m_cf.lpLogFont);
		m_strFontName=dlg.m_cf.lpLogFont->lfFaceName;
	}
	//Invalidate();
	CClientDC dc(this);
	CFont *pOldFont=dc.SelectObject(&m_font);
	dc.TextOut(0,0,m_strFontName);
	dc.SelectObject(pOldFont);

	CDC *pDC=GetDC();  
  
}


void CPAINTINGView::OnShowLstylewidth()
{
	// TODO: �ڴ���������������

	CSettingDlg dlg;
    dlg.m_nLineWidth=m_nLineWidth;
	dlg.m_nLineType=m_nLineType;
	dlg.m_clr=m_clr;

	//UpdateData();

	//dlg.logBrush.lbStyle=dlg.m_nLineType;
	//dlg.logBrush=logBrush;

	if(IDOK==dlg.DoModal())
	{m_nLineWidth=dlg.m_nLineWidth;
	 m_nLineType=dlg.m_nLineType;

	 //logBrush.lbStyle=m_nLineType;
	 //logBrush=dlg.logBrush;
	 //dwF[4]=dlg.dwF[4];
	 
	}

	//Invalidate();
}


void CPAINTINGView::OnRec2()
{
	// TODO: �ڴ���������������
	dType=Recta2;
}
