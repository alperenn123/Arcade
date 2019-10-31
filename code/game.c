int player_x = 30;
int player_y = 30;

static void simulate_game(Input* input)
{
    clear_screen(0xffffff00);
    if(pressed(BUTTON_LEFT))player_x -= 20;
    if(pressed(BUTTON_RIGHT))player_x += 20;
    if(pressed(BUTTON_DOWN))player_y -= 20;
    if(pressed(BUTTON_UP))player_y += 20;
    draw_rectangle_in_pixels(player_x,player_y,player_x+30,player_y+30,0xffff4400);
}
