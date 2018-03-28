
// MFCApplication1View.h : CMFCApplication1View 클래스의 인터페이스
//

#pragma once
#include "Face.h"
#include "Face_list.h"

class CMFCApplication1View : public CView
{
protected: // serialization에서만 만들어집니다.
	CMFCApplication1View();
	DECLARE_DYNCREATE(CMFCApplication1View)

// 특성입니다.
public:
	CMFCApplication1Doc* GetDocument() const;
	Face_list list;
	CPoint ptChild;
	CPoint start_point;
	CPoint end_point;
	bool m_bDragFlag;
	bool ID_Menu_Flag;
	CString str;
// 작업입니다.
public:
	void color_mapping(int value,int * brush);
	void keydownfunc(int key);
	void slice_rotation(CPoint start, CPoint end);
// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CMFCApplication1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
//	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void PopNumber();
	afx_msg void OnlyColor();
	afx_msg void KeyboarLog();
	afx_msg void MouseLog();
};

#ifndef _DEBUG  // MFCApplication1View.cpp의 디버그 버전
inline CMFCApplication1Doc* CMFCApplication1View::GetDocument() const
   { return reinterpret_cast<CMFCApplication1Doc*>(m_pDocument); }
#endif

