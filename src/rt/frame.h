/*************************************************************
 * Copyright (C) 2022
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

 /* FILE NAME   : frame.h
  * PURPOSE     : Ray tracing project.
  *               Frame declaration module.
  * PROGRAMMER  : CGSG-SummerCamp'2022.
  *               Rimma Filatova.
  * LAST UPDATE : 24.07.2022.
  * NOTE        : Module namespace 'rirt'.
  *
  * No part of this file may be changed without agreement of
  * Computer Graphics Support Group of 30 Phys-Math Lyceum
  */

#ifndef __frame_h_
#define __frame_h_

//#include "win/win.h"

#ifndef WIN32
#define WIN32
#include "commondf.h"
#undef WIN32
#else 
#include "commondf.h"
#endif
namespace rirt
{
  // frame structure
  struct frame //: public win
  {
    DWORD *Image;
    INT W, H;
  public:
    /* Frame construction function.
     * ARGUMENTS: 
     *   - length and width
     *       INT W, H;
     */
    frame( INT W1, INT H1 ) : Image(new DWORD[H1 * W1]), W(W1), H(H1)
    {
      memset(Image, 0, sizeof(DWORD) * W * H);
    } /* End of 'frame' function */
    
    /* Resize frame function.
     * ARGUMENTS: 
     *   - length and width
     *       INT W, H;
     * RETURNS: None.
     */
    VOID Resize( INT W1, INT H1 )
    {
      delete[] Image;
      Image = new DWORD[H1 * W1];
      W = W1;
      H = H1;
      memset(Image, 0, sizeof(DWORD) * W * H);
    } /* End of 'Resize' function */
 
    /* One pixel setting function.
     * ARGUMENTS:
     *   - pixel coordinates
     *       INT X, Y;
     *   - color
     *       DWORD Color;
     * RETURNS: None.
     */
    VOID PutPixel( INT X, INT Y, DWORD Color )
    {
      if (X >= 0 && X < W && Y >= 0 && Y < H)
        Image[Y * W + X] = Color;
    } /* End 'PutPixel' function */

    /* Frame draw function.
     * ARGUMENTS:
     *   - device context
     *       HDC hDC;
     * RETURNS: None.
     */
    VOID Draw( HDC hDC )
    {
      BITMAPINFOHEADER bmih = { 0 };
      bmih.biSize = sizeof(BITMAPINFOHEADER);
      bmih.biWidth = W;
      bmih.biHeight = -H;
      bmih.biPlanes = 1;
      bmih.biBitCount = 32;
      SetDIBitsToDevice(hDC, 0, 0, W, H, 0, 0, 0, H, Image, (BITMAPINFO*)&bmih, DIB_RGB_COLORS);
    } /* End of 'Draw' function */

    ~frame( VOID )
    {
      delete[] Image;
    }
  };
}

#endif /* __frame_h_ */

/* END OF 'frame.h' FILE */
