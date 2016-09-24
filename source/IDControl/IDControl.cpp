
// IDControl.cpp : �A�v���P�[�V�����̃N���X������`���܂��B
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "IDControl.h"
#include "MainFrm.h"

#include "IDControlDoc.h"
#include "IDControlView.h"
#include <strsafe.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


// CIDControlApp

BEGIN_MESSAGE_MAP(CIDControlApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CIDControlApp::OnAppAbout)
	// �W���̃t�@�C����{�h�L�������g �R�}���h
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
END_MESSAGE_MAP()


// CIDControlApp �R���X�g���N�V����

CIDControlApp::CIDControlApp()
{
	m_bHiColorIcons = TRUE;

	// �ċN���}�l�[�W���[���T�|�[�g���܂�
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// �A�v���P�[�V���������ʌ��ꃉ���^�C�� �T�|�[�g (/clr) ���g�p���č쐬����Ă���ꍇ:
	//     1) ���̒ǉ��ݒ�́A�ċN���}�l�[�W���[ �T�|�[�g������ɋ@�\���邽�߂ɕK�v�ł��B
	//     2) �쐬����ɂ́A�v���W�F�N�g�� System.Windows.Forms �ւ̎Q�Ƃ�ǉ�����K�v������܂��B
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: ���̃A�v���P�[�V���� ID ���������ӂ� ID ������Œu�����܂��B���������
	// ������̌`���� CompanyName.ProductName.SubProduct.VersionInformation �ł�
	CString strAppID;
	
	strAppID.Format (_T("JO3XWC.IDControl.%s.NoVersion"), GetMyDir ().GetString ());
	SetAppID(strAppID);

	// TODO: ���̈ʒu�ɍ\�z�p�R�[�h��ǉ����Ă��������B
	// ������ InitInstance ���̏d�v�ȏ��������������ׂċL�q���Ă��������B
}

// �B��� CIDControlApp �I�u�W�F�N�g�ł��B

CIDControlApp theApp;


// CIDControlApp ������

BOOL CIDControlApp::InitInstance()
{
	// �A�v���P�[�V���� �}�j�t�F�X�g�� visual �X�^�C����L���ɂ��邽�߂ɁA
	// ComCtl32.dll Version 6 �ȍ~�̎g�p���w�肷��ꍇ�́A
	// Windows XP �� InitCommonControlsEx() ���K�v�ł��B�����Ȃ���΁A�E�B���h�E�쐬�͂��ׂĎ��s���܂��B
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// �A�v���P�[�V�����Ŏg�p���邷�ׂẴR���� �R���g���[�� �N���X���܂߂�ɂ́A
	// �����ݒ肵�܂��B
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	// OLE ���C�u���������������܂��B
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// RichEdit �R���g���[�����g�p����ɂ� AfxInitRichEdit2() ���K�v�ł�	
	// AfxInitRichEdit2();

	// �W��������
	// �����̋@�\���g�킸�ɍŏI�I�Ȏ��s�\�t�@�C����
	// �T�C�Y���k���������ꍇ�́A�ȉ�����s�v�ȏ�����
	// ���[�`�����폜���Ă��������B
	// �ݒ肪�i�[����Ă��郌�W�X�g�� �L�[��ύX���܂��B
	// TODO: ��Ж��܂��͑g�D���Ȃǂ̓K�؂ȕ������
	// ���̕������ύX���Ă��������B
	CString strRegKey;
	
	strRegKey.Format (_T("JO3XWC\\IDCtrl\\%s"), GetMyDir ().GetString ());
	SetRegistryKey(strRegKey);
	LoadStdProfileSettings(4);  // �W���� INI �t�@�C���̃I�v�V���������[�h���܂� (MRU ���܂�)


	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// �A�v���P�[�V�����p�̃h�L�������g �e���v���[�g��o�^���܂��B�h�L�������g �e���v���[�g
	//  �̓h�L�������g�A�t���[�� �E�B���h�E�ƃr���[���������邽�߂ɋ@�\���܂��B
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CIDControlDoc),
		RUNTIME_CLASS(CMainFrame),       // ���C�� SDI �t���[�� �E�B���h�E
		RUNTIME_CLASS(CIDControlView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// DDE�Afile open �ȂǕW���̃V�F�� �R�}���h�̃R�}���h ���C������͂��܂��B
	CCommandLineInfo cmdInfo;
	//ParseCommandLine(cmdInfo);

	// DDE Execute open ���g�p�\�ɂ��܂��B
	//EnableShellOpen();
	//RegisterShellFileTypes(TRUE);

	LoadSetting ();
	GetRepeaterList ()->Load (GetMyDir () + _T("RptList.csv"));

	// �R�}���h ���C���Ŏw�肳�ꂽ�f�B�X�p�b�` �R�}���h�ł��B�A�v���P�[�V������
	// /RegServer�A/Register�A/Unregserver �܂��� /Unregister �ŋN�����ꂽ�ꍇ�AFalse ��Ԃ��܂��B
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// ���C�� �E�B���h�E�����������ꂽ�̂ŁA�\���ƍX�V���s���܂��B
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	// �ڔ��������݂���ꍇ�ɂ̂� DragAcceptFiles ���Ăяo���܂�
	//  SDI �A�v���P�[�V�����ł́AProcessShellCommand �̒���ɂ��̌Ăяo�����������Ȃ���΂Ȃ�܂���B
	// �h���b�O/�h���b�v �I�[�v���������܂��B
	//m_pMainWnd->DragAcceptFiles();
	return TRUE;
}

int CIDControlApp::ExitInstance()
{
	SaveSetting ();

	//TODO: �ǉ��������\�[�X������ꍇ�ɂ͂������������Ă�������
	AfxOleTerm(FALSE);

	return CWinAppEx::ExitInstance();
}


#define SECTION_PLUGIN			_T("Plugin")
#define PLUGIN_PATH				_T("Path")
#define PLUGIN_FLAGS			_T("Flags")
#define PLUGIN_COM				_T("ComNo")


#define SECTION_NETWORK			_T("Network")
#define NETWORK_SERVER_PORT		_T("ServerPort")
#define NETWORK_SERVER_ENABLE	_T("ServerEnable")
#define NETWORK_REMOTE_ADDR		_T("RemoteAddr")
#define NETWORK_REMOTE_PORT		_T("RemotePort")
#define NETWORK_USER_NAME		_T("UserName")
#define NETWORK_USER_PASS		_T("UserPass")

#define SECTION_MIC				_T("Mic")
#define MIC_ENABLE				_T("Enable")
#define MIC_PATH				_T("Path")
#define MIC_DEVICE				_T("Device")

#define SECTION_SPEAKER			_T("Speaker")
#define SPEAKER_ENABLE			_T("Enable")
#define SPEAKER_PATH			_T("Path")
#define SPEAKER_DEVICE			_T("Device")

#define SECTION_CONFIG			_T("Config")
#define CONFIG_SPEECH_LEVEL		_T("SPEECH_LEVEL")

VOID CIDControlApp::SaveSetting ()
{
	WriteProfileString (SECTION_PLUGIN, PLUGIN_PATH				, m_Setting.m_Trx.m_strPluginPath);
	WriteProfileInt    (SECTION_PLUGIN, PLUGIN_COM				, m_Setting.m_Trx.m_ComNo);

	WriteProfileInt    (SECTION_NETWORK, NETWORK_SERVER_ENABLE	, m_Setting.m_Network.m_ServerEnable);
	WriteProfileString (SECTION_NETWORK, NETWORK_USER_NAME		, m_Setting.m_Network.m_strUserName);
	WriteProfileString (SECTION_NETWORK, NETWORK_USER_PASS		, m_Setting.m_Network.m_strUserPass);
	WriteProfileInt    (SECTION_NETWORK, NETWORK_SERVER_PORT	, m_Setting.m_Network.m_ServerPort);
	WriteProfileString (SECTION_NETWORK, NETWORK_REMOTE_ADDR	, m_Setting.m_Network.m_strRemoteAddr);
	WriteProfileInt    (SECTION_NETWORK, NETWORK_REMOTE_PORT	, m_Setting.m_Network.m_RemotePort);

	WriteProfileInt    (SECTION_MIC, MIC_ENABLE					, m_Setting.m_Mic.m_Enable);
	WriteProfileString (SECTION_MIC, MIC_DEVICE					, m_Setting.m_Mic.m_strID);

	WriteProfileInt    (SECTION_SPEAKER, SPEAKER_ENABLE			, m_Setting.m_Speaker.m_Enable);
	WriteProfileString (SECTION_SPEAKER, SPEAKER_DEVICE			, m_Setting.m_Speaker.m_strID);

	WriteProfileInt    (SECTION_CONFIG, CONFIG_SPEECH_LEVEL		, m_Setting.m_SpeechLevel);
}

VOID CIDControlApp::LoadSetting ()
{
	CString strText;

	m_Setting.m_Trx.m_ComNo				= GetProfileInt    (SECTION_PLUGIN, PLUGIN_COM				, 1); 
	m_Setting.m_Trx.m_strPluginPath		= GetProfileString (SECTION_PLUGIN, PLUGIN_PATH				, _T(""));

	m_Setting.m_Network.m_ServerEnable	= GetProfileInt    (SECTION_NETWORK, NETWORK_SERVER_ENABLE	, 0);
	m_Setting.m_Network.m_strUserName	= GetProfileString (SECTION_NETWORK, NETWORK_USER_NAME		, _T(""));
	m_Setting.m_Network.m_strUserPass	= GetProfileString (SECTION_NETWORK, NETWORK_USER_PASS		, _T(""));
	m_Setting.m_Network.m_ServerPort	= GetProfileInt    (SECTION_NETWORK, NETWORK_SERVER_PORT	, 20000);
	m_Setting.m_Network.m_strRemoteAddr	= GetProfileString (SECTION_NETWORK, NETWORK_REMOTE_ADDR	, _T(""));
	m_Setting.m_Network.m_RemotePort	= GetProfileInt    (SECTION_NETWORK, NETWORK_REMOTE_PORT	, 20000);
	
	m_Setting.m_Mic.m_Enable			= GetProfileInt    (SECTION_MIC, MIC_ENABLE					, 0);
	m_Setting.m_Mic.m_strID				= GetProfileString (SECTION_MIC, MIC_DEVICE					, _T(""));
	
	m_Setting.m_Speaker.m_Enable		= GetProfileInt    (SECTION_SPEAKER, SPEAKER_ENABLE			, 0);
	m_Setting.m_Speaker.m_strID			= GetProfileString (SECTION_SPEAKER, SPEAKER_DEVICE			, _T(""));

	m_Setting.m_SpeechLevel				= GetProfileInt    (SECTION_CONFIG, CONFIG_SPEECH_LEVEL		, 20);

}



// CIDControlApp ���b�Z�[�W �n���h���[


// �A�v���P�[�V�����̃o�[�W�������Ɏg���� CAboutDlg �_�C�A���O

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �_�C�A���O �f�[�^
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

// ����
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// �_�C�A���O�����s���邽�߂̃A�v���P�[�V���� �R�}���h
void CIDControlApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CIDControlApp �̃J�X�^�}�C�Y���ꂽ�ǂݍ��݃��\�b�h�ƕۑ����\�b�h

void CIDControlApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_REPEATER);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_REPEATER);
}

void CIDControlApp::LoadCustomState()
{
}

void CIDControlApp::SaveCustomState()
{
}

// CIDControlApp ���b�Z�[�W �n���h���[



