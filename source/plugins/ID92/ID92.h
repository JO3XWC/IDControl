// ID92.h : ID92.DLL �̃��C�� �w�b�_�[ �t�@�C��
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH �ɑ΂��Ă��̃t�@�C�����C���N���[�h����O�� 'stdafx.h' ���C���N���[�h���Ă�������"
#endif

#include "resource.h"		// ���C�� �V���{��


// CID92App
// ���̃N���X�̎����Ɋւ��Ă� ID92.cpp ���Q�Ƃ��Ă��������B
//

class CID92App : public CWinApp
{
public:
	CID92App();

// �I�[�o�[���C�h
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
