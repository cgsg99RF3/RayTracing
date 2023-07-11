/*************************************************************
 * Copyright (C) 2022
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

 /* FILE NAME   : win.h
  * PURPOSE     : Raytracing project.
  *               Windows declaration module.
  * PROGRAMMER  : CGSG-SummerCamp'2022.
  *               Rimma Filatova.
  * LAST UPDATE : 23.07.2022.
  * NOTE        : Module namespace 'rirt'.
  *
  * No part of this file may be changed without agreement of
  * Computer Graphics Support Group of 30 Phys-Math Lyceum
  */

#ifndef __win_h_
#define __win_h_

#include "rt/frame.h"
#include "rt/rt.h"

namespace rirt
{
  class win
  {
  protected:
    HWND hWnd;           // Win  dow handle
    INT W, H;            // Window size
    HINSTANCE hInstance; // Application handle
  
  private:
    /* Window message handle function (CALLBACK version).
     *   - window handle:
     *       HWND hWnd;
     *   - message identifier (see WM_***):
     *       UINT Msg;
     *   - message first parameter ('word' param):
     *       WPARAM wParam;
     *   - message second parameter ('long' param):
     *       LPARAM lParam;
     * RETURNS:
     *   (LRESULT) message return code (depended to Msg type).
     */
    static LRESULT CALLBACK WinFunc( HWND hWnd, UINT Msg,
      WPARAM wParam, LPARAM lParam );
  
    BOOL IsFullScreen;          // Fullsreen mode flag
    RECT FullScreenSaveRect;    // Fullsreen mode old window rectangle
    INT MouseWheel;             // Mouse wheel counter 
  
  public:
    BOOL IsActive;              // Active window flag
  
    /* Window constructor function
    * ARGUMENTS:
    *   - app example description
    *       HINSTANCE hInst;
    */
    win( HINSTANCE hInst = GetModuleHandle(nullptr) );

    /* Window destructor function */
    virtual ~win( VOID );
  
    /* Window app run function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    virtual VOID Run( VOID );

    /* Flipping full screen function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID FlipFullScreen( VOID );
  
  private:
    // message cracks
    VOID OnGetMinMaxInfo( MINMAXINFO *MinMax ); // ???
    /* WM_CREATE window message handle function.
     * ARGUMENTS:
     *   - structure with creation data:
     *       CREATESTRUCT *CS;
     * RETURNS:
     *   (BOOL) TRUE to continue creation window, FALSE to terminate.
     */
    virtual BOOL OnCreate( CREATESTRUCT *CS );

    /* WM_DESTROY window message handle function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    virtual VOID OnDestroy( VOID );

    /* WM_SIZE window message handle function.
     * ARGUMENTS:
     *   - sizing flag (see SIZE_***, like SIZE_MAXIMIZED)
     *       UINT State;
     *   - new width and height of client area:
     *       INT W, H;
     * RETURNS: None.
     */
    virtual VOID OnSize( UINT State, INT W, INT H );
    
    /* WM_ERASEBKGND window message handle function.
     * ARGUMENTS:
     *   - device context of client area:
     *       HDC hDC;
     * RETURNS:
     *   (BOOL) TRUE if background is erased, FALSE otherwise.
     */
    virtual BOOL OnEraseBkgnd( HDC hDC );

    /* WM_PAINT window message handle function.
     * ARGUMENTS:
     *   - window device context:
     *       HDC hDC;
     *   - paint message structure pointer:
     *       PAINTSTRUCT *PS;
     * RETURNS: None.
     */
    virtual VOID OnPaint( HDC hDC, PAINTSTRUCT *PS );

    /* WM_ACTIVATE window message handle function.
     * ARGUMENTS:
     *   - reason (WA_CLICKACTIVE, WA_ACTIVE or WA_INACTIVE):
     *       UINT Reason;
     *   - handle of active window:
     *       HWND hWndActDeact;
     *   - minimized flag:
     *       BOOL IsMinimized;
     * RETURNS: None.
     */
    virtual VOID OnActivate( UINT Reason, HWND hWndActDeact, BOOL IsMinimized );

    /* WM_TIMER window message handle function.
     * ARGUMENTS:
     *   - specified the timer identifier.
     *       INT Id;
     * RETURNS: None.
     */
    virtual VOID OnTimer( INT Id );

    /* WM_KEYDOWN window message handle function.
     * ARGUMENTS:
     *   - message first parameter ('word' param)
     *       WPARAM wParam;
     * RETURNS: None.
     */
    virtual VOID OnKeyDown( WPARAM wParam );

    /* WM_MOUSEWHEEL window message handle function.
     * ARGUMENTS:
     *   - mouse window position:
     *       INT X, Y;
     *   - mouse wheel relative delta value:
     *       INT Z;
     *   - mouse keys bits (see MK_*** bits constants):
     *       UINT Keys;
     * RETURNS: None.
     */
    virtual VOID OnMouseWheel( INT X, INT Y, INT Z, UINT Keys );

    /* WM_DROPFILES window message handle function.
     * ARGUMENTS:
     *   - handle to an internal structure describing the dropped files:
     *       HDROP hDrop;
     * RETURNS: None.
     */
    virtual VOID OnDropFiles( HDROP hDrop );

    /* WM_NOTIFY window message handle function.
     * ARGUMENTS:
     *   - control identifier:
     *       INT Id;
     *   - notification header depended to control type:
     *       NMHDR *NoteHead;
     * RETURNS:
     *   (LRESULT) return value depended to notification.
     */
    virtual LRESULT OnNotify( INT Id, NMHDR* NoteHead );

    /* WM_COMMAND window message handle function.
     * ARGUMENTS:
     *   - item (menu or accelerator) or control window identifier:
     *       INT Id;
     *   - control window handle:
     *       HWND hWndCtl;
     *   - notification: 0 - menu, 1 - accelerator, otherwise -
     *     depended to control (like BM_CLICKED):
     *       UINT CodeNotify;
     * RETURNS: None.
     */
    virtual VOID OnCommand( INT Id, HWND hWndCtl, UINT CodeNotify );

    /* WM_DRAWITEM window message handle function.
     * ARGUMENTS:
     *   - control identifier (for menu - 0):
     *       INT Id;
     *   - draw item information structure pointer:
     *       DRAWITEMSTRUCT *DrawItem;
     * RETURNS: None.
     */
    virtual VOID OnDrawItem( INT Id, DRAWITEMSTRUCT *DrawItem );

    /* WM_HSCROLL message handle function.
     * ARGUMENTS:
     *   - handle of scroll window or nullptr for window scroll bars:
     *       HWND hWndCtl;
     *   - scrool bar request code (see SB_***):
     *       UINT Code;
     *   - schroll position for 'Code' is SB_THUMBPOSITION or SB_THUMBTRACK:
     *       INT Pos;
     * RETURNS: None.
     */
    virtual VOID OnHScroll( HWND hWndCtl, UINT Code, INT Pos );

    /* WM_VSCROLL message handle function.
     * ARGUMENTS:
     *   - handle of scroll window or nullptr for window scroll bars:
     *       HWND hWndCtl;
     *   - scrool bar request code (see SB_***):
     *       UINT Code;
     *   - schroll position for 'Code' is SB_THUMBPOSITION or SB_THUMBTRACK:
     *       INT Pos;
     * RETURNS: None.
     */
    virtual VOID OnVScroll( HWND hWndCtl, UINT Code, INT Pos );

    /* WM_MENUSELECT window message handle function.
     * ARGUMENTS:
     *   - handle of menu:
     *       HMENU hMenu;
     *   - submenu item ID or submenu index
     *       INT Item;
     *   - handle of popup menu if selected popup submenu:
     *       HMENU hMenuPopup;
     *   - menu item flags (see MF_***):
     *       UINT Flags;
     * RETURNS: None.
     */
    virtual VOID OnMenuSelect( HMENU hMenu, INT Item, HMENU hMenuPopup, UINT Flags );

    /* WM_INITMENUPOPUP window message handle function.
     * ARGUMENTS:
     *   - handle of popup menu:
     *       HMENU hMenu;
     *   - submenu item position:
     *       UINT Item;
     *   - window system menu flag:
     *       BOOL IsSystemMenu;
     * RETURNS: None.
     */
    virtual VOID OnInitMenuPopup( HMENU hMenu, UINT Item, BOOL IsSystemMenu );

    /* WM_EXITSIZEMOVE window message handle function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    virtual VOID OnExitSizeMove( VOID );

    /* WM_ENTERSIZEMOVE window message handle function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    virtual VOID OnEnterSizeMove( VOID );

    /* Window message universal handle function.
     * Should be returned 'DefWindowProc' call result.
     * ARGUMENTS:
     *   - message type (see WM_***):
     *      UINT Msg;
     *   - message 'word' parameter:
     *      WPARAM wParam;
     *   - message 'long' parameter:
     *      LPARAM lParam;
     * RETURNS:
     *   (LRESULT) message depende return value.
     */
    virtual LRESULT OnMessage( UINT Msg, WPARAM wParam, LPARAM lParam );
  };
}

#endif /* __win_h_ */

/* END OF 'win.h' FILE */