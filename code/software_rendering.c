
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

static void draw_rectangle_in_pixels(int x0,int y0,int x1,int y1)
{
    
}