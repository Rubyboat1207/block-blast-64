/**
 * @file main.cpp
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 * 
 * Copyright (C) 2025 Rubyboat (owner of https://github.com/Rubyboat1207)
 */

#include <stdio.h>
#include <libdragon.h>
#include "engine/gameobject.hpp"
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
    init_title_scene(gm);
    // graphics_set_color(0x000000, 0xFFFFFFFF);
    assert(eeprom_present() == 1);
    rdpq_font_t *font = rdpq_font_load_builtin(FONT_BUILTIN_DEBUG_MONO);
    rdpq_text_register_font(
        1,		// Font ID to set it to
        font	// Font pointer
    );
    audio_init(44100, 4);
    mixer_init(4);
    timer_init();
    while(1) {
        surface_t* disp = display_get();
        gm->display = disp;
       
        /*Fill the screen */
        rdpq_attach( disp, NULL );
        rdpq_clear(RGBA32(77, 63, 144, 255));

        gm->update();

        if (audio_can_write()) {
            // Select an audio buffer that we can write to
            short *buf = audio_write_begin();
            // Write to the audio buffer from the mixer
            mixer_poll(buf, audio_get_buffer_length());
            // Tell the audio system that the buffer has
            // been filled and is ready for playback
            audio_write_end();
        }

        rdpq_detach_wait();

        /* Force backbuffer flip */
        display_show(disp);
    }
}