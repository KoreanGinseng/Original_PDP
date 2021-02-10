#include	"GameApp.h"
#include    "resource.h"
#include    "ScreenUtilites.h"

int WINAPI _tWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow )
{
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

	Mof::LPFramework pFrame = new Mof::CDX11GameFramework(); 
	Mof::WINDOWSGAMEFRAMEWORKINITIALIZEINFO Info;
	Info.pApplication = new CGameApp();

    int monitor_x = /**GetSystemMetrics(SM_CXSCREEN)/*/320 * 1.5f/**/;
    int monitor_y = /**GetSystemMetrics(SM_CYSCREEN)/*/568 * 1.5f/**/;
    //512 X 683

    g_ScreenUtilities.SetMonitorSize(monitor_x, monitor_y);
    Info.WindowCreateInfo.Width  = monitor_x;
    Info.WindowCreateInfo.Height = monitor_y;

	Info.WindowCreateInfo.Title = "ƒpƒlƒ‹‚Åƒ|ƒ“";
	Info.WindowCreateInfo.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));

	if ( pFrame->Initialize(&Info) )
	{
		pFrame->Run();
	}
	MOF_SAFE_DELETE(pFrame);
	return 0;
}