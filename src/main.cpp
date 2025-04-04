#include <stdio.h>
#include <libdragon.h>
#include "gameobject.hpp"
#include "scenes/scenes.hpp"

int main(void)
{
    display_init(RESOLUTION_320x240, DEPTH_16_BPP, 2, GAMMA_NONE, FILTERS_RESAMPLE);

    dfs_init(DFS_DEFAULT_LOCATION);
    debug_init_isviewer();
    rdpq_init();
    controller_init();
    
    debug_init_usblog();
    console_set_debug(true);
    GameObjects::GameManager* gm = new GameObjects::GameManager();
    init_main_scene(gm);
    while(1) {
        surface_t* disp = display_get();
        gm->display = disp;
       
        /*Fill the screen */
        graphics_fill_screen( disp, 0xFFFFFFFF );

        gm->update(); 

        /* Force backbuffer flip */
        display_show(disp);
    }
}