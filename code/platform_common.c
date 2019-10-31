typedef struct
{
    b32 is_down;
    b32 is_changed;
}Button;

enum 
{
    BUTTON_LEFT,
    BUTTON_RIGHT,
    BUTTON_UP,
    BUTTON_DOWN,
    
    BUTTON_COUNT,
};

typedef struct
{
    int mouse_x;
    int mouse_y;
    Button buttons[BUTTON_COUNT];
}Input;

#define pressed(b)(input->buttons[b].is_changed && input->buttons[b].is_down) 
#define released(b)(input->buttons[b].is_changed && !input->buttons[b].is_down) 
#define is_down(b)(input->buttons[b].is_down) 
