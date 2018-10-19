
/* =====[ dsp.h ]========================================== 
                                                                             
   Description:     The daco project, implementation of the dsp.h                
                                                                             
                    Defines the behavior for the application.          
                                                                             
   Compiled:        MS-VC 6.00                                               
                                                                             
   Notes:           <Empty Notes>                                            
                                                                             
   Revisions:                                                                
                                                                             
      REV     DATE        BY            DESCRIPTION                       
      ----  --------  -----------  ----------------------------   
      0.00  8/24/2009  Peter Glen   Initial version.                         
                                                                             
   ======================================================================= */

class CDsp

{

public:

	CDsp::CDsp();

	void	SplitWave(short *dorg, int len, short *lptr, short *rptr, int lim);
	void	SplitWaveLeft(short *dorg, int len, short *lptr, int lim);
	void	UnSplitWave(short *lptr, short *rptr, int len, short *dorg);

};


extern CDsp dsp;
