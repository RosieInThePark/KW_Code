
// MFCApplication1Doc.h : CMFCApplication1Doc Ŭ������ �������̽�
//


#pragma once
#include "Face.h"
#include "Face_list.h"

class CMFCApplication1Doc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CMFCApplication1Doc();
	DECLARE_DYNCREATE(CMFCApplication1Doc);

// Ư���Դϴ�.
public:
	int m_face[3][3][3]; ///////�������� ť�� ����
	int * temp;
// �۾��Դϴ�.
public:
	void set_face(Face * head);
// �������Դϴ�.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// �����Դϴ�.
public:
	virtual ~CMFCApplication1Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// �˻� ó���⿡ ���� �˻� �������� �����ϴ� ����� �Լ�
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	afx_msg void On32773();
	afx_msg void MouseLog();
	afx_msg void KeyboardLog();
};
