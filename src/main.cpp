#include <stdio.h>
#include <libdragon.h>
#include "gameobject.hpp"
#include "scenes/scenes.hpp"

int main(void)
{
    // this requires the preview branch of libdragon for now, as of (5/5/25)
    display_init(RESOLUTION_320x240, DEPTH_16_BPP, 2, GAMMA_NONE, FILTERS_DISABLED);

    dfs_init(DFS_DEFAULT_LOCATION);
    debug_init_isviewer();
    rdpq_init();
    controller_init();
    
    debug_init_usblog();
    console_set_debug(true);
    GameObjects::GameManager* gm = new GameObjects::GameManager();
    init_main_scene(gm);
    // graphics_set_color(0x000000, 0xFFFFFFFF);
    assert(eeprom_present() == 1);
    rdpq_font_t *font = rdpq_font_load_builtin(FONT_BUILTIN_DEBUG_MONO);
    rdpq_text_register_font(
        1,		// Font ID to set it to
        font	// Font pointer
    );
    while(1) {
        surface_t* disp = display_get();
        gm->display = disp;
       
        /*Fill the screen */
        rdpq_attach( disp, NULL );
        rdpq_clear(RGBA32(255, 255, 255, 255));

        gm->update();

        rdpq_detach_wait();

        /* Force backbuffer flip */
        display_show(disp);
    }
}