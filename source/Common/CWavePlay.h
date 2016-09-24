#pragma once

#define PCM 0x0001
#pragma pack (push, 1)
typedef struct _WAVE_HEADER
{
	ULONG	Riff;				// 4 byte R' 'I' 'F' 'F' RIFF�w�b�_
	ULONG	Length;				// 4 byte ����ȍ~�̃t�@�C���T�C�Y (�t�@�C���T�C�Y - 8) �@ �@
	ULONG	Wave;				// 4 byte W' 'A' 'V' 'E' WAVE�w�b�_ RIFF�̎�ނ�WAVE�ł��邱�Ƃ�����킷 
	ULONG	chunkID;			// 4 byte f' 'm' 't' ' ' (���X�y�[�X���܂�) fmt �`�����N �t�H�[�}�b�g�̒�`
	ULONG	chunkSize;			// 4 byte �o�C�g�� fmt �`�����N�̃o�C�g�� ���j�APCM �Ȃ�� 16(10 00 00 00)
	SHORT	wFromatID;			// 2 byte �t�H�[�}�b�gID �Q�� ���j�APCM �Ȃ�� 1(01 00) 
	SHORT	wChannels;			// 2 byte �`�����l���� �@ ���m���� �Ȃ�� 1(01 00) �X�e���I �Ȃ�� 2(02 00) 
	ULONG	dwSamplesPerSec;	// 4 byte �T���v�����O���[�g Hz 44.1kHz �Ȃ�� 44100(44 AC 00 00) 
	ULONG	dwDataRate;			// 4 byte �f�[�^���x (Byte/sec) �@ 44.1kHz 16bit �X�e���I �Ȃ��44100�~2�~2 = 176400(10 B1 02 00) 
	SHORT	wBlockAlign;		// 2 byte �u���b�N�T�C�Y (Byte/sample�~�`�����l����) �@ 16bit �X�e���I �Ȃ��2�~2 = 4(04 00) 
	SHORT	wBitsPerSample;		// 2 byte �T���v��������̃r�b�g�� (bit/sample) WAV �t�H�[�}�b�g�ł� 8bit �� 16bit 16bit �Ȃ�� 16(10 00) 
	ULONG	DataChunk;			// 4 byte d' 'a' 't' 'a' data �`�����N �Q�� �@ 
	ULONG	DataChunkLength;	// 4 byte �o�C�g��n �g�`�f�[�^�̃o�C�g�� �@ 
}WAVE_HEADER, *PWAVE_HEADER;
#pragma pack(pop)


class CWavePlay
{
public:
	CWavePlay(void);
	~CWavePlay(void);

	VOID Load (HINSTANCE hInstance, ULONG Index, ULONG ResID, ULONG Count);
	VOID Play (LPCSTR pszString);
	VOID Stop ();
	VOID SetVolume (ULONG Level);
	ULONG GetVolume ();

private:
	PWAVE_HEADER LoadWave (HINSTANCE hInstance, UINT Id);
	PWAVE_HEADER Init (ULONG Index);
	PWAVE_HEADER Append (ULONG Index);
	PWAVE_HEADER VolumeApply ();

private:
	CMap<ULONG, ULONG, PWAVE_HEADER, PWAVE_HEADER> m_Map;
	PWAVE_HEADER	m_pWaveBuffer;
	ULONG			m_Level;

	enum
	{
		WAVE_BUFFER_SIZE = 8 * 1024 * 1024,
	};
};
