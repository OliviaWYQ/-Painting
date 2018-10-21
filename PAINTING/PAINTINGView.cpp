
// PAINTINGView.cpp : CPAINTINGView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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
	// 标准打印命令
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

// CPAINTINGView 构造/析构

CPAINTINGView::CPAINTINGView()
	: m_nLineWidth(0)
	//, m_nLineType(0)
{
	// TODO: 在此处添加构造代码
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
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CPAINTINGView 绘制

void CPAINTINGView::OnDraw(CDC*pDC)
{
	CPAINTINGDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	CFont *pOldFont=pDC->SelectObject(&m_font);
	pDC->TextOut(0,0,m_strFontName);
	pDC->SelectObject(pOldFont);

	if (m_font.m_hObject)
		m_font.DeleteObject();

	CRect rect;
	GetClientRect(&rect);
	CDC dcMem;//以下是输出位图的标准操作
	CBitmap *pOldBitmap = NULL;
	dcMem.CreateCompatibleDC(NULL);
	pOldBitmap = dcMem.SelectObject(&pDoc->m_bmpBuf);
 
	pDC->BitBlt(0,0,rect.Width(),rect.Height(),&dcMem,0,0,SRCCOPY);
	dcMem.SelectObject(pOldBitmap); //将dcMeM中的bitmap拷贝到当前客户区
	dcMem.DeleteDC();
}


// CPAINTINGView 打印


void CPAINTINGView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CPAINTINGView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CPAINTINGView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CPAINTINGView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
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


// CPAINTINGView 诊断

#ifdef _DEBUG
void CPAINTINGView::AssertValid() const
{
	CView::AssertValid();
}

void CPAINTINGView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPAINTINGDoc* CPAINTINGView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPAINTINGDoc)));
	return (CPAINTINGDoc*)m_pDocument;
}
#endif //_DEBUG


// CPAINTINGView 消息处理程序


void CPAINTINGView::OnLine()
{
	// TODO: 在此添加命令处理程序代码
	dType=SLine;
	//MessageBox(_T("现在可以绘制直线！"));
}


void CPAINTINGView::OnCLine()
{
	// TODO: 在此添加命令处理程序代码
	//MessageBox(_T("现在可以绘制连续曲线！"));
	 dType=CLine;
}


void CPAINTINGView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	
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
	// TODO: 在此添加消息处理程序代码和/或调用默认值
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
	GetClientRect(&rect); //获取客户区域
	pDoc->m_bmpBuf.DeleteObject();
	pDoc->m_bmpBuf.CreateCompatibleBitmap(pDC,rect.Width(),rect.Height());
	CBitmap *pOldBitmap = dcMem.SelectObject(&pDoc->m_bmpBuf);//将创建好的m_bmpBuf添加到临时的CDC的Object中，类似于在墙上先糊上墙纸^_^，先在墙纸上作画，最后将最终形成的画拷贝到墙上。
	
	m_ptEnd = point;
	dcMem.BitBlt(0,0,rect.Width(),rect.Height(),pDC,0,0,SRCCOPY);
	dcMem.SelectObject(pOldBitmap); //将pDC即当前客户区里面的内容拷贝到临时的MEM中，MEM虽然过后会被delete掉，但是它更新了CDocument类中的m_bmpBuf
	m_bDraw = false;
	dcMem.DeleteDC();

	CView::OnLButtonUp(nFlags, point);
}


void CPAINTINGView::OnRec()
{
	// TODO: 在此添加命令处理程序代码
	dType=Recta;
	//MessageBox(_T("现在可以绘制矩形！"));
}


void CPAINTINGView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	
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
	// TODO: 在此添加命令处理程序代码
	//MessageBox(_T("现在可以绘制有边界扇形！"));
	dType=Sector;
}


void CPAINTINGView::OnNoSector()
{
	// TODO: 在此添加命令处理程序代码
	//MessageBox(_T("现在可以绘制无边界扇形！"));
	dType=NoSector;
}


void CPAINTINGView::OnEcllipse()
{
	// TODO: 在此添加命令处理程序代码
	//MessageBox(_T("现在可以绘制椭圆！"));
	dType=Ecllipse;
}


void CPAINTINGView::OnColor()
{
	// TODO: 在此添加命令处理程序代码
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
	// TODO: 在此添加命令处理程序代码
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
	// TODO: 在此添加命令处理程序代码

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
	// TODO: 在此添加命令处理程序代码
	dType=Recta2;
}
