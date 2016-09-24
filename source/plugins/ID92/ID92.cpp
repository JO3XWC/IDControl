// ID92.cpp : DLL �̏��������[�`���ł��B
//

#include "stdafx.h"
#include "ID92.h"
#include "CID92SerialPort.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//
//TODO: ���� DLL �� MFC DLL �ɑ΂��ē��I�Ƀ����N�����ꍇ�A
//		MFC ���ŌĂяo����邱�� DLL ����G�N�X�|�[�g���ꂽ�ǂ̊֐���
//		�֐��̍ŏ��ɒǉ������ AFX_MANAGE_STATE �}�N����
//		�����Ȃ���΂Ȃ�܂���B
//
//		��:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// �ʏ�֐��̖{�̂͂��̈ʒu�ɂ���܂�
//		}
//
//		���̃}�N�����e�֐��Ɋ܂܂�Ă��邱�ƁAMFC ����
//		�ǂ̌Ăяo�����D�悷�邱�Ƃ͔��ɏd�v�ł��B
//		����͊֐����̍ŏ��̃X�e�[�g�����g�łȂ���΂� 
//		��Ȃ����Ƃ��Ӗ����܂��A�R���X�g���N�^�[�� MFC
//		DLL ���ւ̌Ăяo�����s���\��������̂ŁA�I�u
//		�W�F�N�g�ϐ��̐錾�����O�łȂ���΂Ȃ�܂���B
//
//		�ڍׂɂ��Ă� MFC �e�N�j�J�� �m�[�g 33 �����
//		58 ���Q�Ƃ��Ă��������B
//

// CID92App

BEGIN_MESSAGE_MAP(CID92App, CWinApp)
END_MESSAGE_MAP()


// CID92App �R���X�g���N�V����

CID92App::CID92App()
{
	// TODO: ���̈ʒu�ɍ\�z�p�R�[�h��ǉ����Ă��������B
	// ������ InitInstance ���̏d�v�ȏ��������������ׂċL�q���Ă��������B
}


// �B��� CID92App �I�u�W�F�N�g�ł��B

CID92App theApp;


// CID92App ������

BOOL CID92App::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}










CID92SerialPort g_Serial;

ULONG WINAPI Serial_Open (PLUGIN_PARAM* pPluginParam, DATA_CALLBACK_FUNC pfnCallback, PVOID pParam)
{
	g_Serial.SetCallback (pfnCallback, pParam);
	return g_Serial.Open (pPluginParam->ComNo);
}

ULONG WINAPI Serial_Close()
{
	g_Serial.SetCallback (NULL, NULL);
	return g_Serial.Close ();
}

ULONG WINAPI Serial_Command(ULONG Type, PVOID pBuffer, ULONG Length)
{
	return g_Serial.AddCommand (Type, pBuffer, Length);
}

PLUGIN g_Plugin = 
{
	sizeof (PLUGIN),
	FLAGS_SERIAL,
	NULL,
	L"ID-92",
	L"ID-92 Control",
	L"(C) 2012-2016 JO3XWC (k.yamada)",	
	Serial_Open,
	Serial_Close,
	Serial_Command
};

// �G�N�X�|�[�g�֐�
ULONG WINAPI IDCtrlInfo (PLUGIN* pPlugin)
{
	ULONG	Result		= ERROR_SUCCESS;

	do
	{
		if (pPlugin == NULL)
		{	
			Result = ERROR_INVALID_PARAMETER;
			break;
		}

		if (pPlugin->Size != sizeof (PLUGIN))
		{
			Result = ERROR_INVALID_PARAMETER;
			break;
		}

		g_Plugin.hModule = theApp.m_hInstance;

		memcpy (pPlugin, &g_Plugin, sizeof (PLUGIN));
	}
	while (0);

	return Result;
}

