#include <windows.h>

/* Pencereye yapılan tüm girdiler burada bulunur */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
		
		/* Program hata verince durdurulur */
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		
		/* Varsayılan prosedürler ve diğer tüm mesajlar kullanılarak işlenir */
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

/* Win32 ile ara yüz programlamanın başlatıldığı yer */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc; /* Pencerenin özellik yapısı */
	HWND hwnd; /* Bir "HANDLE", yani H veya pencere için bir bayrak(işaretçi) */
	MSG msg; /* Mesajlar için geçici yer */

	/* Yapıyı sıfırlayıp değiştirmek istediğiniz şeyleri ayarlayabilirsiniz. (Pencerenin ikonu, ekranın genişliği-yüksekliği...) */
	memset(&wc,0,sizeof(wc));
	wc.cbSize		 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* Mesaj gönderdiğimiz yer */
	wc.hInstance	 = hInstance;
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);
	
	/* Beyaz, COLOR_WINDOW için bir tanımdır. winuser.h dosyasındaki 3101. satırda belirtilir.*/
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1); /*COLOR_WINDOW+1*/
	wc.lpszClassName = "WindowClass";
	wc.hIcon		 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm		 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","Cup",WS_VISIBLE|WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		640, /* width */
		480, /* height */
		NULL,NULL,hInstance,NULL);

	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	/*
		This is the heart of our program where all input is processed and 
		sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
		this loop will not produce unreasonably high CPU usage
	*/
	while(GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... */
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg); /* Send it to WndProc */
	}
	return msg.wParam;
}
