//////////////////////////////////////////////////////////////////////
// PlaySound.h: interface for the PlaySound class.
//

#if !defined(AFX_PLAYSOUND_H__263DF620_0B5C_11D6_90D8_00B04C390A3E__INCLUDED_)
#define AFX_PLAYSOUND_H__263DF620_0B5C_11D6_90D8_00B04C390A3E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxmt.h>

#include "mmsystem.h"
#include "soundpar.h"

#define PS_MAGIC 0x34242

// Bit defines for user buffer

#define PS_AUTOADD	0x40
#define PS_AUTOFREE	0x10
#define	PS_BUSY		0x20

//////////////////////////////////////////////////////////////////////////

class CPlaySound

{

private:

	static void CALLBACK CPlaySound::waveOutProc(HWAVEOUT hwo, UINT uMsg, DWORD dwInstance,  
					 DWORD dwParam1,  DWORD dwParam2);

	static	void	CPlaySound::PlayThread(void *lpParam);

public:		

	void	Reset();
	int		WaitForEnd();
	void	StopPlay();
	int		WaveClose();
	void	Play(char*buff, int len, int autofree = false);
	int		SaveWave(const char *fname, void *buff, int len);
	int		PlayMonoWave(char *buff, int len, int autofree = false);
	int		PlayWave(char *buff, int len, int autofree = false);
	//int		LoadWave(const char *fname, void **buff, int *len);
	int		LoadWave(const char *fname, char **buff, int *len);

	int		GetCurrPos();
	int		IsPlaying();
	
	HWAVEOUT WaveOpen();
	
	// Public Data

	// So it can be seen what happened
	WAVEFORMATEX devicewfx; 
	WAVEFORMATEX openwfx; 

	CPlaySound();
	virtual ~CPlaySound();

private:

	WAVEHDR	whead[10];

	void	DisplayError(int mmReturn, char errmsg[]);
	int		SubmitWavHead(WAVEHDR *whdr);
	int		WriteField(HMMIO hFile, const char *four, const char *str);

	int		magic, opened, lastpos, currhead;

	// Thread related
	HANDLE  event;
	int thhandle, endthread;

	CPtrArray	queue;
	CCriticalSection lock;

	volatile int stop_play;

	HWAVEOUT	m_hPlay;
};

#endif // !defined(AFX_PLAYSOUND_H__263DF620_0B5C_11D6_90D8_00B04C390A3E__INCLUDED_)
