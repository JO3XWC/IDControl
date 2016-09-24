// Network.cpp : DLL �̏��������[�`���ł��B
//

#include "stdafx.h"
#include "Network.h"
#include "CTcpClientCmd.h"

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

// CNetworkApp

BEGIN_MESSAGE_MAP(CNetworkApp, CWinApp)
END_MESSAGE_MAP()


// CNetworkApp �R���X�g���N�V����

CNetworkApp::CNetworkApp()
{
	// TODO: ���̈ʒu�ɍ\�z�p�R�[�h��ǉ����Ă��������B
	// ������ InitInstance ���̏d�v�ȏ��������������ׂċL�q���Ă��������B
}


// �B��� CNetworkApp �I�u�W�F�N�g�ł��B

CNetworkApp theApp;


// CNetworkApp ������

BOOL CNetworkApp::InitInstance()
{
	CWinApp::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	return TRUE;
}



CTcpClientCmd g_Client;


ULONG WINAPI Serial_Open (PLUGIN_PARAM* pPluginParam, DATA_CALLBACK_FUNC pfnCallback, PVOID pParam)
{
	g_Client.SetAuthMd5 (pPluginParam->AuthMd5);
	g_Client.SetCallback (pfnCallback, pParam);
	return g_Client.Open (pPluginParam->szRemoteAddr, pPluginParam->RemotePort);
}

ULONG WINAPI Serial_Close()
{
	g_Client.SetCallback (NULL, NULL);
	return g_Client.Close ();
}

ULONG WINAPI Serial_Command(ULONG Type, PVOID pBuffer, ULONG Length)
{
	UCHAR Buff[4 * 1024] = {};
	PACKET_CMD_HEADER* pHeader = reinterpret_cast<PACKET_CMD_HEADER*>(Buff);

	pHeader->m_Length	= sizeof (PACKET_CMD_HEADER) + Length;
	pHeader->m_Type		= Type;

	memcpy (pHeader + 1, pBuffer, Length);

	g_Client.Send (pHeader, pHeader->m_Length);

	return ERROR_SUCCESS;
}

PLUGIN g_Plugin = 
{
	sizeof (PLUGIN),
	FLAGS_NETWORK,
	NULL,
	L"Network Control",
	L"Network Control",
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

