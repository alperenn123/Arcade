#include <windows.h>
#include "utils.c"
#include "math.c"
static u8 running = TRUE;

typedef struct {
    int width,height;
    void* pixels;
    BITMAPINFO win32_bitmap_info;
}Render_Buffer;

Render_Buffer render_buffer = {0};
#include "software_rendering.c"
LRESULT CALLBACK WindowCallback(HWND window, UINT message, WPARAM w_param, LPARAM l_param)
{
    LRESULT result = 0;
    switch (message)
    {
        case WM_CLOSE:
        case WM_DESTROY:
        {
            running = FALSE;
        }break;
        
        case WM_SIZE:{
            RECT rect;
            GetWindowRect(window,&rect);
            render_buffer.width = rect.right - rect.left;
            render_buffer.height = rect.bottom - rect.top;
            if(render_buffer.pixels){
                VirtualFree(render_buffer.pixels,0,MEM_RELEASE);
            }
            
            render_buffer.pixels = VirtualAlloc(0,sizeof(u32)*render_buffer.width*render_buffer.height,MEM_COMMIT|MEM_RESERVE,PAGE_READWRITE);
            render_buffer.win32_bitmap_info.bmiHeader.biSize = sizeof(render_buffer.win32_bitmap_info.bmiHeader);
            render_buffer.win32_bitmap_info.bmiHeader.biWidth = render_buffer.width;
            render_buffer.win32_bitmap_info.bmiHeader.biHeight = render_buffer.height;
            render_buffer.win32_bitmap_info.bmiHeader.biPlanes = 1;
            render_buffer.win32_bitmap_info.bmiHeader.biBitCount = 32;
            render_buffer.win32_bitmap_info.bmiHeader.biCompression = BI_RGB;
        }break;
        default:
        {
            result = DefWindowProc(window, message, w_param, l_param);
        }
        
    }
    return result;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   PSTR lpCmdLine, INT nCmdShow)
{
    
    
    WNDCLASSA window_class = {0};
    window_class.style = CS_HREDRAW|CS_VREDRAW;
    window_class.lpfnWndProc = WindowCallback;
    window_class.lpszClassName = "Game_Window_Class";
    
    RegisterClass(&window_class);
    
    // Create the window.
    
    HWND win32_window = CreateWindowExA(
        0,
        window_class.lpszClassName,
        "Arcade Game",
        WS_OVERLAPPEDWINDOW|WS_VISIBLE,
        0, 0, 1280, 720,
        0,
        0,
        0,
        0
        );
    HDC hdc = GetDC(win32_window);
    b32 character = FALSE;
    while(running)
    {
        MSG local_message = {0};
        while (PeekMessageA(&local_message,win32_window,0,0,PM_REMOVE))
        {
            switch(local_message.message)
            {
                
                case WM_SYSKEYUP:
                case WM_SYSKEYDOWN:
                case WM_KEYDOWN:
                case WM_KEYUP:
                {
                    u32 vk_code = (u32)local_message.wParam;
                    b32 was_down = ((local_message.lParam & (1 << 30)) != 0);
                    b32 is_down = ((local_message.lParam & (1 << 31)) == 0);
                    
                    if (vk_code == VK_LEFT)
                    {
                        character = TRUE;
                    }
                }break;
                default:
                {
                    TranslateMessage(&local_message);
                    DispatchMessage(&local_message);
                }
            }
        }
        
        clear_screen(0xffffff00);
        if(character)
        {
            draw_rectangle_in_pixels(20,20,50,50,0xffff4400);
        }
        //render
        StretchDIBits(hdc, 0, 0, render_buffer.width, render_buffer.height, 0, 0, render_buffer.width, render_buffer.height, render_buffer.pixels, &render_buffer.win32_bitmap_info, DIB_RGB_COLORS, SRCCOPY);
    }
    return 0;
}