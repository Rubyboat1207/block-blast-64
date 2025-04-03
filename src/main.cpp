#include <stdio.h>
#include <libdragon.h>

int main(void)
{
    display_init(RESOLUTION_320x240, DEPTH_16_BPP, 2, GAMMA_NONE, FILTERS_RESAMPLE);

    dfs_init(DFS_DEFAULT_LOCATION);
    rdpq_init();
    controller_init();
    
    sprite_t* rubyboat = sprite_load("rom:/rubyboat.sprite");

    debug_init_usblog();
    console_set_debug(true);
    while(1) {
        surface_t* disp = display_get();
       
        /*Fill the screen */
        graphics_fill_screen( disp, 0xFFFFFFFF );

        /* Set the text output color */
        graphics_set_color( 0x0, 0xFFFFFFFF );

        graphics_draw_sprite(disp, 50, 50, rubyboat);

        /* Force backbuffer flip */
        display_show(disp);
    }
}