
// PAINTINGView.h : CPAINTINGView ��Ľӿ�
//

#pragma once
enum DrawType {SLine,CLine,Ecllipse,SetPen,SetBrush,NoSector,Sector,Recta,ColorSet,NoDraw,Recta2};

//enum LineStyle {PS_SOLID, PS_DASHDOT ,PS_DOT};

/*typedef struct tagLOGBRUSH {
  UINT     lbStyle;             // ��ˢ����ʽ
  COLORREF lbColor;    // ��ˢ����ɫ
  LONG     lbHatch;         // ��ˢ��hatch��ʽ, hatch����˼..., �Լ���Ħ��...
} LOGBRUSH, *PLOGBRUSH;*/

class CPAINTINGView : public CView
{
protected: // �������л�����
	CPAINTINGView();
	DECLARE_DYNCREATE(CPAINTINGView)

// ����
public:
	CPAINTINGDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CPAINTINGView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
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

#ifndef _DEBUG  // PAINTINGView.cpp �еĵ��԰汾
inline CPAINTINGDoc* CPAINTINGView::GetDocument() const
   { return reinterpret_cast<CPAINTINGDoc*>(m_pDocument); }
#endif

