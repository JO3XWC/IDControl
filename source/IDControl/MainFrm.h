
// MainFrm.h : CMainFrame �N���X�̃C���^�[�t�F�C�X
//

#pragma once

#include "CRepeaterView.h"
#include "CCallsignHistoryView.h"
#include "CMessageHistoryView.h"
#include "CGpsHistoryView.h"
#include "CCommonView.h"
#include "CAnalogFreqView.h"
#include "CDigitalFreqView.h"
#include "CDebugView.h"

#include "CTcpServerCmd.h"
#include "CCIVCache.h"
#include "CDirectSound.h"
#include "CWavePlay.h"

class CMainFrame : public CFrameWndEx
{
	
protected: // �V���A��������̂ݍ쐬���܂��B
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// ����
public:

// ����
public:

// �I�[�o�[���C�h
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ����
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // �R���g���[�� �o�[�p�����o�[
	CMFCMenuBar       m_wndMenuBar;
	CMFCStatusBar     m_wndStatusBar;

	CRepeaterView			m_wndRepeaterView;
#ifdef _DEBUG
	CDebugView				m_wndDebugView;
#endif
	CCallsignHistoryView	m_wndCallsignHistoryView;
	CMessageHistoryView		m_wndMessageHistoryView;
	CGpsHistoryView			m_wndGpsHistoryView;
	CCommonView				m_wndCommonView;
	CAnalogFreqView			m_wndAnalogFreqView;
	CDigitalFreqView		m_wndDigitalFreqView;

// �������ꂽ�A���b�Z�[�W���蓖�Ċ֐�
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewCustomize();

	afx_msg LRESULT OnToolbarCreateNew(WPARAM wp, LPARAM lp);

	afx_msg LRESULT OnSetCallsign (WPARAM wp, LPARAM lp);
	afx_msg LRESULT OnCommonView (WPARAM wp, LPARAM lp);
	afx_msg LRESULT OnAnalogFreqView (WPARAM wp, LPARAM lp);
	afx_msg LRESULT OnDigitalFreqView (WPARAM wp, LPARAM lp);

	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);
	DECLARE_MESSAGE_MAP()

	BOOL CreateDockingWindows();
	void SetDockingWindowIcons(BOOL bHiColorIcons);
public:
	afx_msg void OnUpdateCmdTrxSetting(CCmdUI *pCmdUI);
	afx_msg void OnCmdTrxSetting();
	afx_msg void OnDestroy();
	afx_msg void OnClose();

	VOID StartIDCtrl ();
	VOID StopIDCtrl ();

	static ULONG CALLBACK onDataCallback (ULONG Type, PVOID pBuffer, ULONG Length, PVOID pParam);
	ULONG OnDataCallback (ULONG Type, PVOID pBuffer, ULONG Length);
	VOID OnWork (ULONG Type, PVOID pBuffer, ULONG Length);
	VOID OnWorkSerial (PVOID pBuffer, ULONG Length);
	VOID OnWorkVoice (PVOID pBuffer, ULONG Length);
	VOID OnWorkCommand (PVOID pBuffer, ULONG Length);

	static UINT WorkerThread (PVOID pParam);
	UINT WorkerThread ();
	VOID AddWork (ULONG Type, PVOID pBuffer, ULONG Length);

	VOID OnCIV (ULONG Trx, ULONG Cmd, PVOID pBuffer, ULONG Length);
	VOID OnRecvData (ULONG Trx, PVOID pBuffer, ULONG Length);

private:
	CTcpServerCmd	m_TcpServer;
	PLUGIN			m_Plugin;
	CCIVCache		m_CivCache;
	
	CMemFileEx		m_DvData[2];
	CString			m_strPic;

	//VOICE Capture flag
	ULONG			m_VoiceEnable;
	enum
	{
		VOICE_SQL1		= 0x01,
		VOICE_SQL2		= 0x02,
		VOICE_MONITOR	= 0x04,
	};
	
	CStringArray	m_MyCallsignArray;
	CStringArray	m_MyMemoArray;
	INT				m_MyCallsignIndex;
	

	HANDLE			m_hWorkerThread;
	HANDLE			m_hWorkEvent;
	HANDLE			m_hStopEvent;
	CMemFileExList	m_WorkList;
	CMemFileExList	m_RecvList;
	

	CDirectSound	m_DirectSoundCapture;
	CDirectSound	m_DirectSoundRender;
	static VOID CALLBACK onWaveIn (PUCHAR pBuffer, ULONG Length, PVOID pParam);

	CWavePlay		m_WaveSpeech;
	CString			m_strLastCaller;
	CStringA		m_strLastGpsA;
public:
	afx_msg void OnCmdImportRepeaterList();
	afx_msg void OnUpdateCmdSoundSetting(CCmdUI *pCmdUI);
	afx_msg void OnCmdSoundSetting();

public:
	enum
	{	
		SET_UR_CALLSIGN,
		SET_R1_CALLSIGN,
		SET_R2_CALLSIGN,
		SET_TOFROM_CALLSIGN,
	};
};


