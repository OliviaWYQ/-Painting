
// PAINTINGView.h : CPAINTINGView 类的接口
//

#pragma once
enum DrawType {SLine,CLine,Ecllipse,SetPen,SetBrush,NoSector,Sector,Recta,ColorSet,NoDraw,Recta2};

//enum LineStyle {PS_SOLID, PS_DASHDOT ,PS_DOT};

/*typedef struct tagLOGBRUSH {
  UINT     lbStyle;             // 画刷的样式
  COLORREF lbColor;    // 画刷的颜色
  LONG     lbHatch;         // 画刷的hatch样式, hatch的意思..., 自己揣摩吧...
} LOGBRUSH, *PLOGBRUSH;*/

class CPAINTINGView : public CView
{
protected: // 仅从序列化创建
	CPAINTINGView();
	DECLARE_DYNCREATE(CPAINTINGView)

// 特性
public:
	CPAINTINGDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CPAINTINGView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLine();
	afx_msg void OnCLine();

private:
	DrawType dType;
	BOOL m_bDraw;
	CPoint m_ptOrigin;
	CPoint m_ptNext;
	CPoint m_ptEnd;
	CButton btn;
	COLORREF m_clr;
	CFont m_font;
	CString m_strFontName;
	
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRec();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnSector();
	afx_msg void OnNoSector();
	afx_msg void OnEcllipse();
	afx_msg void OnColor();
	afx_msg void OnFont();
	afx_msg void OnShowLstylewidth();

	unsigned int m_nLineWidth;
	LOGBRUSH logBrush;
	int m_nLineType;
	DWORD dwF[4];
	//CPen(int nPenStyle, int nWidth, const LOGBRUSH* pLogBrush, int nStyleCount = 0, const DWORD* lpStyle = NULL);
	//BOOL CreatePen(int nPenStyle, int nWidth, const LOGBRUSH* pLogBrush, int nStyleCount = 0, const DWORD* lpStyle = NULL);
private:

public:
	afx_msg void OnRec2();
};

#ifndef _DEBUG  // PAINTINGView.cpp 中的调试版本
inline CPAINTINGDoc* CPAINTINGView::GetDocument() const
   { return reinterpret_cast<CPAINTINGDoc*>(m_pDocument); }
#endif

