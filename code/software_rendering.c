
static void clear_screen(u32 color)
{
    u32* pixel = (u32*)render_buffer.pixels;
    
    for(int x = 0;x<render_buffer.height;x++)
    {
        for(int y = 0;y<render_buffer.width;y++)
        {
            *pixel = color;
            pixel++;
        }
    }
}

static void draw_rectangle_in_pixels(int x0,int y0,int x1,int y1,u32 color)
{
    x0 = clamp(x0,0,render_buffer.width);
    x1 = clamp(x1,0,render_buffer.width);
    y0 = clamp(y0,0,render_buffer.height);
    y1 = clamp(y1,0,render_buffer.height);
    
    u32* row = (((u32*)render_buffer.pixels) + x0 + render_buffer.width *y0);
    u32* pixel = row;
    int stride = render_buffer.width;
    
    for(int y=y0;y<y1;y++)
    {
        for(int x = x0;x<x1;x++)
        {
            *pixel = color;
            pixel++;
        }
        row = row + stride;
        pixel = row;
    }
}