#pragma once
#include "afxwin.h"
#include "CCustomDC.h"
#include "CCustomButton.h"
#include "CCustomEdit.h"


// CDlgMyCallsign �_�C�A���O

class CDlgMyCallsign : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgMyCallsign)

public:
	CDlgMyCallsign(CWnd* pParent = NULL);   // �W���R���X�g���N�^�[
	virtual ~CDlgMyCallsign();
	
	VOID SetCallsign (LPCTSTR pszText, INT MaxLen);
	LPCTSTR GetCallsign ();
	
	VOID SetMemo (LPCTSTR pszText, INT MaxLen);
	LPCTSTR GetMemo ();

// �_�C�A���O �f�[�^
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EDIT_MY_CALLSIGN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

	DECLARE_MESSAGE_MAP()
public:
	CCustomEdit m_CallsignEditBox;
	CCustomEdit m_MemoEditBox;
	CCustomButton m_OkButton;
	CCustomButton m_CancelButton;
	CCustomDC m_DC;

private:
	CString		m_strCallsign;
	INT			m_CallsignLen;
	CString		m_strMemo;
	INT			m_MemoLen;

	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnNcHitTest(CPoint point);
};
