
// IDControlView.cpp : CIDControlView �N���X�̎���
//

#include "stdafx.h"
// SHARED_HANDLERS �́A�v���r���[�A�k���ŁA����ь����t�B���^�[ �n���h���[���������Ă��� ATL �v���W�F�N�g�Œ�`�ł��A
// ���̃v���W�F�N�g�Ƃ̃h�L�������g �R�[�h�̋��L���\�ɂ��܂��B
#ifndef SHARED_HANDLERS
#include "IDControl.h"
#endif

#include "IDControlDoc.h"
#include "IDControlView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


// CIDControlView

IMPLEMENT_DYNCREATE(CIDControlView, CView)

BEGIN_MESSAGE_MAP(CIDControlView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CIDControlView �R���X�g���N�V����/�f�X�g���N�V����

CIDControlView::CIDControlView()
{
	// TODO: �\�z�R�[�h�������ɒǉ����܂��B

}

CIDControlView::~CIDControlView()
{
}

BOOL CIDControlView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: ���̈ʒu�� CREATESTRUCT cs ���C������ Window �N���X�܂��̓X�^�C����
	//  �C�����Ă��������B

	return CView::PreCreateWindow(cs);
}

// CIDControlView �`��

void CIDControlView::OnDraw(CDC* pDC)
{
	CIDControlDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CRect Rect;

	GetClientRect (&Rect);

	pDC->FillSolidRect (&Rect, RGB (40, 40, 40));
}

void CIDControlView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CIDControlView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
}


// CIDControlView �f�f

#ifdef _DEBUG
void CIDControlView::AssertValid() const
{
	CView::AssertValid();
}

void CIDControlView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CIDControlDoc* CIDControlView::GetDocument() const // �f�o�b�O�ȊO�̃o�[�W�����̓C�����C���ł��B
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CIDControlDoc)));
	return (CIDControlDoc*)m_pDocument;
}
#endif //_DEBUG


// CIDControlView ���b�Z�[�W �n���h���[
