
// stdafx.cpp : �W���C���N���[�h IDControl.pch �݂̂�
// �܂ރ\�[�X �t�@�C���́A�v���R���p�C���ς݃w�b�_�[�ɂȂ�܂��B
// stdafx.obj �ɂ̓v���R���p�C���ς݌^��񂪊܂܂�܂��B

#include "stdafx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


UINT WM_SET_CALLSIGN = ::RegisterWindowMessage (_T("WM_SET_CALLSIGN"));
UINT WM_COMMON_VIEW = ::RegisterWindowMessage (_T("WM_COMMON_VIEW"));
UINT WM_ANALOG_FREQ_VIEW = ::RegisterWindowMessage (_T("WM_ANALOG_FREQ_VIEW"));
UINT WM_DIGITAL_FREQ_VIEW = ::RegisterWindowMessage (_T("WM_DIGITAL_FREQ_VIEW"));
