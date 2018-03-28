
// MFCApplication1Doc.h : CMFCApplication1Doc 클래스의 인터페이스
//


#pragma once
#include "Face.h"
#include "Face_list.h"

class CMFCApplication1Doc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CMFCApplication1Doc();
	DECLARE_DYNCREATE(CMFCApplication1Doc);

// 특성입니다.
public:
	int m_face[3][3][3]; ///////보여지는 큐브 생성
	int * temp;
// 작업입니다.
public:
	void set_face(Face * head);
// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CMFCApplication1Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	afx_msg void On32773();
	afx_msg void MouseLog();
	afx_msg void KeyboardLog();
};
