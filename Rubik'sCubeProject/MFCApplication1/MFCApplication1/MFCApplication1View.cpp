
// MFCApplication1View.cpp : CMFCApplication1View 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MFCApplication1.h"
#endif

#include "MFCApplication1Doc.h"
#include "MFCApplication1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApplication1View

IMPLEMENT_DYNCREATE(CMFCApplication1View, CView)

	BEGIN_MESSAGE_MAP(CMFCApplication1View, CView)
		// 표준 인쇄 명령입니다.
		ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
		ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
		ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
		ON_WM_LBUTTONDOWN()
		ON_WM_LBUTTONUP()
		//		ON_WM_LBUTTONDBLCLK()
		ON_WM_KEYDOWN()
		ON_COMMAND(ID_32771, &CMFCApplication1View::PopNumber)
		ON_COMMAND(ID_32772, &CMFCApplication1View::OnlyColor)
		ON_COMMAND(ID_32773, &CMFCApplication1View::KeyboarLog)
		ON_COMMAND(ID_32774, &CMFCApplication1View::MouseLog)
	END_MESSAGE_MAP()

	// CMFCApplication1View 생성/소멸

	CMFCApplication1View::CMFCApplication1View()
	{
		// TODO: 여기에 생성 코드를 추가합니다.
		ptChild.x = 300;
		ptChild.y = 300;
		m_bDragFlag = FALSE;
		ID_Menu_Flag = FALSE;
		str.Format(_T("%c"),' ');
	}

	CMFCApplication1View::~CMFCApplication1View()
	{
	}

	BOOL CMFCApplication1View::PreCreateWindow(CREATESTRUCT& cs)
	{
		// TODO: CREATESTRUCT cs를 수정하여 여기에서
		//  Window 클래스 또는 스타일을 수정합니다.

		return CView::PreCreateWindow(cs);
	}
	// CMFCApplication1View 그리기
	void CMFCApplication1View::OnDraw(CDC* pDC)
	{
		CMFCApplication1Doc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		if (!pDoc)
			return;
		pDoc->set_face(list.get_head());
		// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
		int brush[3];
		for(int i=0;i<3;i++) {
			for(int j=0;j<3;j++) {
				color_mapping(pDoc->m_face[0][2-i][j], brush);
				CBrush rectangle_color0(RGB(brush[0],brush[1],brush[2]));
				pDC->SelectObject(&rectangle_color0);
				pDC->Rectangle(ptChild.x+64*j,ptChild.y-64*i,ptChild.x+64*(j+1),ptChild.y-64*(i+1));
				pDC->SetBkMode(TRANSPARENT);
				if(ID_Menu_Flag==TRUE) str.Format(_T("%d"),pDoc->m_face[0][2-i][j]);
				else if(ID_Menu_Flag==FALSE) str.Format(_T("%c"),' ');
		        pDC->TextOut(324+64*(j),324-64*(i+1),str);
			}
		}

		CPoint pts[3][3][4];
		for(int i=0;i<3;i++) {
			for(int j=0;j<3;j++) {
				pts[j][i][0].x = ptChild.x+64*j+30*i;
				pts[j][i][0].y = ptChild.y-64*3-30*i;
				pts[j][i][1].x = ptChild.x+64*j+30*(i+1);
				pts[j][i][1].y = ptChild.y-64*3-30*(i+1);
				pts[j][i][2].x = ptChild.x+64*(j+1)+30*(i+1);
				pts[j][i][2].y = ptChild.y-64*3-30*(i+1);
				pts[j][i][3].x = ptChild.x+64*(j+1)+30*i;
				pts[j][i][3].y = ptChild.y-64*3-30*i;
				color_mapping(pDoc->m_face[1][2-i][j],brush);
				CBrush polygon_color0(RGB(brush[0],brush[1],brush[2]));
				pDC->SelectObject(&polygon_color0);
				pDC->Polygon(pts[j][i],4);
				pDC->SetBkMode(TRANSPARENT);
		        if(ID_Menu_Flag==TRUE) str.Format(_T("%d"),pDoc->m_face[1][2-i][j]);
				else if(ID_Menu_Flag==FALSE) str.Format(_T("%c"),' ');
		        pDC->TextOut(324+25*(i+1)+64*j,108-(25+i*2)*(i+1),str);
			}
		}

		CPoint p[3][3][4];
		for(int i=0;i<3;i++) {
			for(int j=0;j<3;j++) {
				p[j][i][0].x = ptChild.x+64*3+30*j;
				p[j][i][0].y = ptChild.y-64*i-30*j;
				p[j][i][1].x = ptChild.x+64*3+30*j;
				p[j][i][1].y = ptChild.y-64*(i+1)-30*j;
				p[j][i][2].x = ptChild.x+64*3+30*(j+1);
				p[j][i][2].y = ptChild.y-64*(i+1)-30*(j+1);
				p[j][i][3].x = ptChild.x+64*3+30*(j+1);
				p[j][i][3].y = ptChild.y-64*i-30*(j+1);
				color_mapping(pDoc->m_face[2][2-i][j],brush);
				CBrush side_color0(RGB(brush[0],brush[1],brush[2]));
				pDC->SelectObject(&side_color0);	
				pDC->Polygon(p[j][i],4);
				pDC->SetBkMode(TRANSPARENT);
		        if(ID_Menu_Flag==TRUE) str.Format(_T("%d"),pDoc->m_face[2][2-i][j]);
				else if(ID_Menu_Flag==FALSE) str.Format(_T("%c"),' ');
		        pDC->TextOut(492+(10+j*6)*(j+1),300-(39)*(j+1)-64*i,str);
			}
		}
	} //화면에 보여지는 큐브의 모양 내가 만듦
	void CMFCApplication1View::color_mapping(int value,int * brush) {
		if(value>=1 && value<=9) { //red
			brush[0] = 255;
			brush[1] = 0;
			brush[2] = 0; 
			//CBrush color(RGB(255,0,0)); 
		}
		else if(value>=10 && value<=18) { //green
			brush[0] = 0;
			brush[1] = 255;
			brush[2] = 0;
			//CBrush color(RGB(0,255,0));
		}
		else if(value>=19 && value<=27) { //orange
			brush[0] = 255;
			brush[1] = 127;
			brush[2] = 0;
			//CBrush color(RGB(255,127,0));
		}
		else if(value>=28 && value<=36) { //blue
			brush[0] = 0;
			brush[1] = 0;
			brush[2] = 255;
			//CBrush color(RGB(0,0,255));
		}
		else if(value>=37 && value<=45) { //yellow
			brush[0] = 255;
			brush[1] = 255;
			brush[2] = 0;
			//CBrush color(RGB(255,255,0));
		}
		else if(value>=46 && value<=54) { //white
			brush[0] = 255;
			brush[1] = 255;
			brush[2] = 255;
			//CBrush color(RGB(255,255,255));
		}
	} //화면에 보여지는 큐브의 색깔 내가 만듦

	// CMFCApplication1View 인쇄

	BOOL CMFCApplication1View::OnPreparePrinting(CPrintInfo* pInfo)
	{
		// 기본적인 준비
		return DoPreparePrinting(pInfo);
	}

	void CMFCApplication1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
	{
		// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
	}

	void CMFCApplication1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
	{
		// TODO: 인쇄 후 정리 작업을 추가합니다.
	}


	// CMFCApplication1View 진단

#ifdef _DEBUG
	void CMFCApplication1View::AssertValid() const
	{
		CView::AssertValid();
	}

	void CMFCApplication1View::Dump(CDumpContext& dc) const
	{
		CView::Dump(dc);
	}

	CMFCApplication1Doc* CMFCApplication1View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
	{
		ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCApplication1Doc)));
		return (CMFCApplication1Doc*)m_pDocument;
	}
#endif //_DEBUG


	// CMFCApplication1View 메시지 처리기

	///////////////////////////////////////////////////////마우스 클릭시 동작
	void CMFCApplication1View::OnLButtonDown(UINT nFlags, CPoint point)
	{
		// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

		start_point = point; //마우스 클릭지점 start_point로 설정
		SetCapture();//마우스를 캡쳐하여 마우스 추적
		m_bDragFlag = true; //드래그가 시작된 것을 알린다
		RedrawWindow(); //OnDraw함수 호출
		CView::OnLButtonDown(nFlags, point);
	}

	//////////////////////////////////////////////////////마우스 클릭을 떼면 동작
	void CMFCApplication1View::OnLButtonUp(UINT nFlags, CPoint point)
	{
		// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
		//마우스 클릭시 동작되도록 구현

		end_point = point; //마우스 클릭이 해제된 위치 end_point로 설정
		//입력받은 point에 해당하는 slice를 rotation하는 함수
		slice_rotation(start_point,end_point);
		RedrawWindow(); //OnDraw함수 호출
		ReleaseCapture(); //마우스 추적 중단
		CView::OnLButtonUp(nFlags, point);
	}
	void CMFCApplication1View::slice_rotation(CPoint start, CPoint end) {
		//////////////////////////////////////////////////////////////////////////////////////////////////////////face[0]에서의 rotation
		if(start.x>=ptChild.x && start.x<=ptChild.x+64 && start.y>=ptChild.y-64*3 && start.y<=ptChild.y-64*2) {
			if(end.x>=ptChild.x+64*2 && end.x<=ptChild.x+64*3 && end.y>=ptChild.y-64*3 && end.y<=ptChild.y-64*2) {
				list.slice_horizontal(0,0,0,2);//(0,0)->(0,2)
				list.mouse_log(list.get_head()->get_name(),0,'1',1);
			}
			else if(end.x>=ptChild.x && end.x<=ptChild.x+64 && end.y<=ptChild.y && end.y>=ptChild.y-64) {
				list.slice_vertical(0,0,0,2);//(0,0)->(2,0)
				list.mouse_log(list.get_head()->get_name(),1,'1',4);
			}
		} //시작점이 (0,0)일 경우
			
		else if(start.x>=ptChild.x+64 && start.x<=ptChild.x+64*2 && start.y>=ptChild.y-64*3 && start.y<=ptChild.y-64*2) {
			if(end.x>=ptChild.x+64 && end.x<=ptChild.x+64*2 && end.y>=ptChild.y-64 && end.y<=ptChild.y) {
				list.slice_vertical(0,1,0,2);//(0,1)->(2,1)
				list.mouse_log(list.get_head()->get_name(),1,'2',4);
			}
		} //시작점이 (0,1)일 경우

		else if(start.x>=ptChild.x+64*2 && start.x<=ptChild.x+64*3 && start.y>=ptChild.y-64*3 && start.y<=ptChild.y-64*2) {
			if(end.x>=ptChild.x && end.x<=ptChild.x+64 && end.y>=ptChild.y-64*3 && end.y<=ptChild.y-64*2) {
				list.slice_horizontal(0,0,2,0);//(0,2)->(0,0)
				list.mouse_log(list.get_head()->get_name(),0,'1',2);
			}
			else if(end.x>=ptChild.x+64*2 && end.x<=ptChild.x+64*3 && end.y>=ptChild.y-64 && end.y<=ptChild.y) {
				list.slice_vertical(0,2,0,2);//(0,2)->(2,2)
				list.mouse_log(list.get_head()->get_name(),1,'3',4);
			}
		}//시작점이 (0,2)일 경우

		else if(start.x>=ptChild.x && start.x<=ptChild.x+64 && start.y>=ptChild.y-64*2 && start.y<=ptChild.y-64) {
			if(end.x>=ptChild.x+64*2 && end.x<=ptChild.x+64*3 && end.y>=ptChild.y-64*2 && end.y<=ptChild.y-64) {
				list.slice_horizontal(0,1,0,2);//(1,0)->(1,2)
				list.mouse_log(list.get_head()->get_name(),0,'2',1);
			}
		}//시작점이 (1,0)일 경우

		else if(start.x>=ptChild.x+64*2 && start.x<=ptChild.x+64*3 && start.y>=ptChild.y-64*2 && start.y<=ptChild.y-64) {
			if(end.x>=ptChild.x && end.x<=ptChild.x+64 && end.y>=ptChild.y-64*2 && end.y<=ptChild.y-64) {
				list.slice_horizontal(0,1,2,0);//(1,2)->(1,0)
				list.mouse_log(list.get_head()->get_name(),0,'2',2);
			}
		}//시작점이 (1,2)일 경우

		else if(start.x>=ptChild.x && start.x<=ptChild.x+64 && start.y>=ptChild.y-64 && start.y<=ptChild.y) {
			if(end.x>=ptChild.x+64*2 && end.x<=ptChild.x+64*3 && end.y>=ptChild.y-64 && end.y<=ptChild.y) {
				list.slice_horizontal(0,2,0,2);//(2,0)->(2,2)
				list.mouse_log(list.get_head()->get_name(),0,'3',1);
			}
			else if(end.x>=ptChild.x && end.x<=ptChild.x+64 && end.y>=ptChild.y-64*3 && end.y<=ptChild.y-64*2) {
				list.slice_vertical(0,0,2,0);//(2,0)->(0,0)
				list.mouse_log(list.get_head()->get_name(),1,'1',3);
			}
		}//시작점이 (2,0)일 경우
		else if(start.x>=ptChild.x+64 && start.x<=ptChild.x+64*2 && start.y>=ptChild.y-64 && start.y<=ptChild.y) {
			if(end.x>=ptChild.x+64 && end.x<=ptChild.x+64*2 && end.y>=ptChild.y-64*3 && end.y<=ptChild.y-64*2) {
				list.slice_vertical(0,1,2,0);//(2,1)->(0,1)
				list.mouse_log(list.get_head()->get_name(),1,'2',3);
			}
		}//시작점이 (2,1)일 경우 
		else if(start.x>=ptChild.x+64*2 && start.x<=ptChild.x+64*3 && start.y>=ptChild.y-64 && start.y<=ptChild.y) {
			if(end.x>=ptChild.x && end.x<=ptChild.x+64 && end.y>=ptChild.y-64 && end.y<=ptChild.y) {
				list.slice_horizontal(0,2,2,0); //(2,2)->(2,0)
				list.mouse_log(list.get_head()->get_name(),0,'3',2);
			}
			else if(end.x>=ptChild.x+64*2 && end.x<=ptChild.x+64*3 && end.y>=ptChild.y-64*3 && end.y<=ptChild.y-64*2) {
				list.slice_vertical(0,2,2,0);//(2,2)->(0,2)
				list.mouse_log(list.get_head()->get_name(),1,'3',3);
			}
		}//시작점이 (2,2)일 경우
		//////////////////////////////////////////////////////////////////////////////////////////////////////////face[1]에서의 rotation
		if(start.x>=ptChild.x+30*3 && start.x<=ptChild.x+30*3+34 && start.y>=ptChild.y-64*3-30*3 && start.y<=ptChild.y-64*3-30*2) {
			if(end.x>=ptChild.x+64*2+30*3 && end.x<=ptChild.x+64*3+30*2 && end.y>=ptChild.y-64*3-30*3 && end.y<=ptChild.y-64*3-30*2) {
				list.slice_horizontal(1,0,0,2);//(0,0)->(0,2)
				list.mouse_log(list.get_head()->get_up()->get_name(),0,'1',1);
			}
			else if(end.x>=ptChild.x+30 && end.x<=ptChild.x+64 && end.y>=ptChild.y-64*3-30 && end.y<=ptChild.y-64*3) {
				list.slice_vertical(1,0,0,2);//(0,0)->(2,0)
				list.mouse_log(list.get_head()->get_up()->get_name(),1,'1',4);
			}
		} //시작점이 (0,0)일 경우

		else if(start.x>=ptChild.x+64+30*3 && start.x<=ptChild.x+64*2+30*2 && start.y>=ptChild.y-64*3-30*3 && start.y<=ptChild.y-64*3-30*2) {
			if(end.x>=ptChild.x+64+30 && end.x<=ptChild.x+64*2 && end.y>=ptChild.y-64*3-30 && end.y<=ptChild.y-64*3) {
				list.slice_vertical(1,1,0,2);//(0,1)->(2,1)
				list.mouse_log(list.get_head()->get_up()->get_name(),1,'2',4);
			}
		} //시작점이 (0,1)일 경우

		else if(start.x>=ptChild.x+64*2+30*3 && start.x<=ptChild.x+64*3+30*3 && start.y>=ptChild.y-64*3-30*3 && start.y<=ptChild.y-64*3-30*2) {
			if(end.x>=ptChild.x+30*3 && end.x<=ptChild.x+64+30*3 && end.y>=ptChild.y-64*3-30*3 && end.y<=ptChild.y-64*3-30*2) {
				list.slice_horizontal(1,0,2,0);//(0,2)->(0,0)
				list.mouse_log(list.get_head()->get_up()->get_name(),0,'1',2);
			}
			else if(end.x>=ptChild.x+64*2+30 && end.x<=ptChild.x+64*3 && end.y>=ptChild.y-64*3-30 && end.y<=ptChild.y-64*3) {
				list.slice_vertical(1,2,0,2);//(0,2)->(2,2)
				list.mouse_log(list.get_head()->get_up()->get_name(),1,'3',4);
			}
		}//시작점이 (0,2)일 경우

		else if(start.x>=ptChild.x+30*2 && start.x<=ptChild.x+64+30 && start.y>=ptChild.y-64*3-30*2 && start.y<=ptChild.y-64*3-30) {
			if(end.x>=ptChild.x+64*2+30*2 && end.x<=ptChild.x+64*3+30 && end.y>=ptChild.y-64*3-30*2 && end.y<=ptChild.y-64*3-30) {
				list.slice_horizontal(1,1,0,2);//(1,0)->(1,2)
				list.mouse_log(list.get_head()->get_up()->get_name(),0,'2',1);
			}
		}//시작점이 (1,0)일 경우

		else if(start.x>=ptChild.x+64*2+30*2 && start.x<=ptChild.x+64*3+30 && start.y>=ptChild.y-64*3-30*2 && start.y<=ptChild.y-64*3-30) {
			if(end.x>=ptChild.x+30*2 && end.x<=ptChild.x+64+30 && end.y>=ptChild.y-64*3-30*2 && end.y<=ptChild.y-64*3-30) {
				list.slice_horizontal(1,1,2,0);//(1,2)->(1,0)
				list.mouse_log(list.get_head()->get_up()->get_name(),0,'2',2);
			}
		}//시작점이 (1,2)일 경우

		else if(start.x>=ptChild.x+30 && start.x<=ptChild.x+64 && start.y>=ptChild.y-64*3-30 && start.y<=ptChild.y-64*3) {
			if(end.x>=ptChild.x+64*2+30 && end.x<=ptChild.x+64*3 && end.y>=ptChild.y-64*3-30 && end.y<=ptChild.y-64*3) {
				list.slice_horizontal(1,2,0,2);//(2,0)->(2,2)
				list.mouse_log(list.get_head()->get_up()->get_name(),0,'3',1);
			}
			else if(end.x>=ptChild.x+30*3 && end.x<=ptChild.x+64+30*3 && end.y>=ptChild.y-64*3-30*3 && end.y<=ptChild.y-64*3-30*2) {
				list.slice_vertical(1,0,2,0);//(2,0)->(0,0)
				list.mouse_log(list.get_head()->get_up()->get_name(),1,'1',3);
			}
		}//시작점이 (2,0)일 경우
		else if(start.x>=ptChild.x+64+30 && start.x<=ptChild.x+64*2 && start.y>=ptChild.y-64*3-30 && start.y<=ptChild.y-64*3) {
			if(end.x>=ptChild.x+64+30*3 && end.x<=ptChild.x+64*2+30*3 && end.y>=ptChild.y-64*3-30*3 && end.y<=ptChild.y-64*3-30*2) {
				list.slice_vertical(1,1,2,0);//(2,1)->(0,1)
				list.mouse_log(list.get_head()->get_up()->get_name(),1,'2',3);
			}
		}//시작점이 (2,1)일 경우 
		else if(start.x>=ptChild.x+64*2+30 && start.x<=ptChild.x+64*3 && start.y>=ptChild.y-64*3-30 && start.y<=ptChild.y-64*3) {
			if(end.x>=ptChild.x+30 && end.x<=ptChild.x+64 && end.y>=ptChild.y-64*3-30 && end.y<=ptChild.y-64*3) {
				list.slice_horizontal(1,2,2,0); //(2,2)->(2,0)
				list.mouse_log(list.get_head()->get_up()->get_name(),0,'3',2);
			}
			else if(end.x>=ptChild.x+64*2+30*3 && end.x<=ptChild.x+64*3+30*3 && end.y>=ptChild.y-64*3-30*3 && end.y<=ptChild.y-64*3-30*2) {
				list.slice_vertical(1,2,2,0);//(2,2)->(0,2)
				list.mouse_log(list.get_head()->get_up()->get_name(),1,'3',3);
			}
		}//시작점이 (2,2)일 경우
		//////////////////////////////////////////////////////////////////////////////////////////////////////////face[2]에서의 rotation
		if(start.x>=ptChild.x+64*3 && start.x<=ptChild.x+64*3+30 && start.y>=ptChild.y-64*3 && start.y<=ptChild.y-64*2-30) {
			if(end.x>=ptChild.x+64*3+30*2 && end.x<=ptChild.x+64*3+30*3 && end.y>=ptChild.y-64*3-30*2 && end.y<=ptChild.y-64*2-30*2) {
				list.slice_horizontal(2,0,0,2);//(0,0)->(0,2)
				list.mouse_log(list.get_head()->get_next()->get_name(),0,'1',1);
			}
			else if(end.x>=ptChild.x+64*3 && end.x<=ptChild.x+64*3+30 && end.y>=ptChild.y-64 && end.y<=ptChild.y-30) {
				list.slice_vertical(2,0,0,2);//(0,0)->(2,0)
				list.mouse_log(list.get_head()->get_next()->get_name(),1,'1',4);
			}
		} //시작점이 (0,0)일 경우

		else if(start.x>=ptChild.x+64*3+30 && start.x<=ptChild.x+64*3+30*2 && start.y>=ptChild.y-64*3-30 && start.y<=ptChild.y-64*2-30*2) {
			if(end.x>=ptChild.x+64*3+30 && end.x<=ptChild.x+64*3+30*2 && end.y>=ptChild.y-64-30 && end.y<=ptChild.y-30*2) {
				list.slice_vertical(2,1,0,2);//(0,1)->(2,1)
				list.mouse_log(list.get_head()->get_next()->get_name(),1,'2',4);
			}
		} //시작점이 (0,1)일 경우

		else if(start.x>=ptChild.x+64*3+30*2 && start.x<=ptChild.x+64*3+30*3 && start.y>=ptChild.y-64*3-30*2 && start.y<=ptChild.y-64*2-30*3) {
			if(end.x>=ptChild.x+64*3 && end.x<=ptChild.x+64*3+30 && end.y>=ptChild.y-64*3 && end.y<=ptChild.y-64*2-30) {
				list.slice_horizontal(2,0,2,0);//(0,2)->(0,0)
				list.mouse_log(list.get_head()->get_next()->get_name(),0,'1',2);
			}
			else if(end.x>=ptChild.x+64*3+30*2 && end.x<=ptChild.x+64*3+30*3 && end.y>=ptChild.y-64-30*2 && end.y<=ptChild.y-30*3) {
				list.slice_vertical(2,2,0,2);//(0,2)->(2,2)
				list.mouse_log(list.get_head()->get_next()->get_name(),1,'3',4);
			}
		}//시작점이 (0,2)일 경우

		else if(start.x>=ptChild.x+64*3 && start.x<=ptChild.x+64*3+30 && start.y>=ptChild.y-64*2 && start.y<=ptChild.y-64-30) {
			if(end.x>=ptChild.x+64*3+30*2 && end.x<=ptChild.x+64*3+30*3 && end.y>=ptChild.y-64*2-30*2 && end.y<=ptChild.y-64-30*3) {
				list.slice_horizontal(2,1,0,2);//(1,0)->(1,2)
				list.mouse_log(list.get_head()->get_next()->get_name(),0,'2',1);
			}
		}//시작점이 (1,0)일 경우

		else if(start.x>=ptChild.x+64*3+30*2 && start.x<=ptChild.x+64*3+30*3 && start.y>=ptChild.y-64*2-30*2 && start.y<=ptChild.y-64-30*3) {
			if(end.x>=ptChild.x+64*3 && end.x<=ptChild.x+64*3+30 && end.y>=ptChild.y-64*2 && end.y<=ptChild.y-64-30) {
				list.slice_horizontal(2,1,2,0);//(1,2)->(1,0)
				list.mouse_log(list.get_head()->get_next()->get_name(),0,'2',2);
			}
		}//시작점이 (1,2)일 경우

		else if(start.x>=ptChild.x+64*3 && start.x<=ptChild.x+64*3+30 && start.y>=ptChild.y-64 && start.y<=ptChild.y-30) {
			if(end.x>=ptChild.x+64*3+30*2 && end.x<=ptChild.x+64*3+30*3 && end.y>=ptChild.y-64-30*2 && end.y<=ptChild.y-30*3) {
				list.slice_horizontal(2,2,0,2);//(2,0)->(2,2)
				list.mouse_log(list.get_head()->get_next()->get_name(),0,'3',1);
			}
			else if(end.x>=ptChild.x+64*3 && end.x<=ptChild.x+64*3+30 && end.y>=ptChild.y-64*3 && end.y<=ptChild.y-64*2-30) {
				list.slice_vertical(2,0,2,0);//(2,0)->(0,0)
				list.mouse_log(list.get_head()->get_next()->get_name(),1,'1',3);
			}
		}//시작점이 (2,0)일 경우
		else if(start.x>=ptChild.x+64*3+30 && start.x<=ptChild.x+64*3+30*2 && start.y>=ptChild.y-64-30 && start.y<=ptChild.y-30*2) {
			if(end.x>=ptChild.x+64*3+30 && end.x<=ptChild.x+64*3+30*2 && end.y>=ptChild.y-64*3-30 && end.y<=ptChild.y-64*2-30*2) {
				list.slice_vertical(2,1,2,0);//(2,1)->(0,1)
				list.mouse_log(list.get_head()->get_next()->get_name(),1,'2',3);
			}
		}//시작점이 (2,1)일 경우 
		else if(start.x>=ptChild.x+64*3+30*2 && start.x<=ptChild.x+64*3+30*3 && start.y>=ptChild.y-64-30*2 && start.y<=ptChild.y-30*3) {
			if(end.x>=ptChild.x+64*3 && end.x<=ptChild.x+64*3+30 && end.y>=ptChild.y-64 && end.y<=ptChild.y-30) {
				list.slice_horizontal(2,2,2,0); //(2,2)->(2,0)
				list.mouse_log(list.get_head()->get_next()->get_name(),0,'3',2);
			}
			else if(end.x>=ptChild.x+64*3+30*2 && end.x<=ptChild.x+64*3+30*3 && end.y>=ptChild.y-64*3-30*2 && end.y<=ptChild.y-64*2-30*2) {
				list.slice_vertical(2,2,2,0);//(2,2)->(0,2)
				list.mouse_log(list.get_head()->get_next()->get_name(),1,'3',3);
			}
		}//시작점이 (2,2)일 경우
	}

	//	void CMFCApplication1View::OnLButtonDblClk(UINT nFlags, CPoint point)
	//	{
	//		// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	//
	//		CView::OnLButtonDblClk(nFlags, point);
	//	}


	void CMFCApplication1View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

		switch(nChar)
		{
		case VK_RIGHT:
			{
				keydownfunc(1);
				list.keyboard_log(1);
				break;
			}
		case VK_LEFT:
			{
				keydownfunc(2);
				list.keyboard_log(2);
				break;
			}
		case VK_UP:
			{
				keydownfunc(3);
				list.keyboard_log(3);
				break;
			}
		case VK_DOWN:
			{
				keydownfunc(4);
				list.keyboard_log(4);
				break;
			}
		}
		CView::OnKeyDown(nChar, nRepCnt, nFlags);
	}
	void CMFCApplication1View::keydownfunc(int key) {

		if(key==1) { //right
			Face * head;
			Face * f1, * f2, * f3;

			head = list.get_head(); //우선 header의 주소를 head에 저장시킴
			f1 = head->get_up();
			f2 = head->get_next();
			f3 = head->get_up()->get_up()->get_up();

			list.set_head(head->get_next()->get_next()->get_next()); //header 한칸 이동
			head = list.get_head(); //head에 header의 값 넣어줌

			head->set_up(f1);
			head->get_up()->set_up(f2);
			head->get_up()->get_up()->set_up(f3);
			head->get_up()->get_up()->get_up()->set_up(head);

			head->get_up()->turn_side(1);
			head->get_up()->get_up()->get_up()->turn_side(2);

			RedrawWindow();
		}
		else if(key==2) { //left
			Face * head;
			Face * f1, * f2, * f3;

			head = list.get_head(); //우선 header의 주소를 head에 저장시킴
			f1 = head->get_up();
			f2 = head->get_next()->get_next()->get_next();
			f3 = head->get_up()->get_up()->get_up();

			list.set_head(head->get_next()); //header 한칸 이동
			head = list.get_head(); //head에 header의 값 넣어줌

			head->set_up(f1);
			head->get_up()->set_up(f2);
			head->get_up()->get_up()->set_up(f3);
			head->get_up()->get_up()->get_up()->set_up(head);
			
			head->get_up()->turn_side(2);
			head->get_up()->get_up()->get_up()->turn_side(1);

			RedrawWindow();
		}
		else if(key==3) { //up
			Face * head;
			Face * f1, * f2, * f3;

			head = list.get_head(); //우선 header의 주소를 head에 저장시킴
			f1 = head->get_next();
			f2 = head->get_up();
			f3 = head->get_next()->get_next()->get_next();

			list.set_head(head->get_up()->get_up()->get_up()); //header 한칸 이동
			head = list.get_head(); //head에 header의 값 넣어줌

			head->set_next(f1);
			head->get_next()->set_next(f2);
			head->get_next()->get_next()->set_next(f3);
			head->get_next()->get_next()->get_next()->set_next(head);
			head->get_up()->get_up()->get_up()->change_back();
			head->get_up()->get_up()->change_back();

			head->get_next()->turn_side(2);
			head->get_next()->get_next()->get_next()->turn_side(1);
			RedrawWindow();
		}
		else if(key==4) { //down
			Face * head;
			Face * f1, * f2, * f3;

			head = list.get_head(); //우선 header의 주소를 head에 저장시킴
			f1 = head->get_next();
			f2 = head->get_up()->get_up()->get_up();
			f3 = head->get_next()->get_next()->get_next();

			list.set_head(head->get_up()); //header 한칸 이동
			head = list.get_head(); //head에 header의 값 넣어줌
			head->get_up()->change_back();
			head->get_up()->get_up()->change_back();

			head->set_next(f1);
			head->get_next()->set_next(f2);
			head->get_next()->get_next()->set_next(f3);
			head->get_next()->get_next()->get_next()->set_next(head);

			head->get_next()->turn_side(1);
			head->get_next()->get_next()->get_next()->turn_side(2);

			RedrawWindow();
		}
	}


	void CMFCApplication1View::PopNumber()
	{
		// TODO: 여기에 명령 처리기 코드를 추가합니다.
		ID_Menu_Flag = TRUE;
		RedrawWindow();
	}


	void CMFCApplication1View::OnlyColor()
	{
		// TODO: 여기에 명령 처리기 코드를 추가합니다.
		ID_Menu_Flag = FALSE;
		RedrawWindow();
	}


	void CMFCApplication1View::KeyboarLog()
	{
		// TODO: 여기에 명령 처리기 코드를 추가합니다.
		list.key_File_out();
	}


	void CMFCApplication1View::MouseLog()
	{
		// TODO: 여기에 명령 처리기 코드를 추가합니다.
		list.mouse_File_out();
	}
