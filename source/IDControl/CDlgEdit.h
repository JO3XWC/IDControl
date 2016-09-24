#pragma once
#include "afxwin.h"
#include "CCustomDC.h"
#include "CCustomButton.h"
#include "CCustomEdit.h"


// CDlgEdit �_�C�A���O

class CDlgEdit : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgEdit)

public:
	CDlgEdit(CWnd* pParent = NULL);   // �W���R���X�g���N�^�[
	virtual ~CDlgEdit();

	VOID SetText (LPCTSTR pszText, INT MaxLen);
	LPCTSTR GetText ();

// �_�C�A���O �f�[�^
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EDIT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

	DECLARE_MESSAGE_MAP()
public:
	CCustomEdit m_EditBox;
	CCustomButton m_OkButton;
	CCustomButton m_CancelButton;
	CCustomDC m_DC;

private:
	CString		m_strText;
	INT			m_MaxLen;
	virtual void OnOK();
public:
	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnNcHitTest(CPoint point);
};
