// Network.h : Network.DLL �̃��C�� �w�b�_�[ �t�@�C��
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH �ɑ΂��Ă��̃t�@�C�����C���N���[�h����O�� 'stdafx.h' ���C���N���[�h���Ă�������"
#endif

#include "resource.h"		// ���C�� �V���{��


// CNetworkApp
// ���̃N���X�̎����Ɋւ��Ă� Network.cpp ���Q�Ƃ��Ă��������B
//

class CNetworkApp : public CWinApp
{
public:
	CNetworkApp();

// �I�[�o�[���C�h
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
