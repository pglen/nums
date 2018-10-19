
/* =====[ dsp.cpp ]========================================== 
                                                                             
   Description:     The daco project, implementation of the dsp.cpp                
                                                                             
                    Defines the behavior for the application.          
                                                                             
   Compiled:        MS-VC 6.00                                               
                                                                             
   Notes:           <Empty Notes>                                            
                                                                             
   Revisions:                                                                
                                                                             
      REV     DATE        BY            DESCRIPTION                       
      ----  --------  -----------  ----------------------------   
      0.00  8/24/2009  Peter Glen   Initial version.                         
                                                                             
   ======================================================================= */

#include "stdafx.h"
#include "dsp.h"

// The one and only instance

CDsp dsp;

CDsp::CDsp()
{

}

//////////////////////////////////////////////////////////////////////////

// --------------------------------------------------------------
//
/// \brief   Split Stereo Wave to two mono waves
/// 
/// \details DescHere 
/// \n  
/// Return type:      void 
/// \n  
/// \param *dorg Arg Type: short 
/// \param len Arg Type: int 
/// \param *lptr Arg Type: short 
/// \param *rptr Arg Type: short 
/// \param lim Arg Type: int 

void	CDsp::SplitWave(short *dorg, int len, short *lptr, short *rptr, int lim)

{
	int len2 = len / sizeof(short);

	for(int loop = 0; loop < len2; loop += 2)
		{
		*rptr++ = *dorg++, *lptr++ = *dorg++;
		}
}

//////////////////////////////////////////////////////////////////////////
// Get the left channel

void	CDsp::SplitWaveLeft(short *dorg, int len, short *lptr, int lim)

{
	int len2 = len / sizeof(short);

	for(int loop = 0; loop < len2; loop += 2)
		{
		*lptr++ = *dorg++;
		
		dorg++;				// Skip channel
		}
}


//////////////////////////////////////////////////////////////////////////
// Unite the two channels

void	CDsp::UnSplitWave(short *lptr, short *rptr, int len, short *dorg)

{
	int len2 = len / sizeof(short);

	for(int loop = 0; loop < len2; loop ++)
		{
		*dorg++ = *lptr++;	*dorg++ = *rptr++;
		}
}

