#include "save_manager.hpp"
#include "math.hpp"

void SaveManager::load()
{
    save_buffer_1 = new uint8_t[8];
    save_buffer_2 = new uint8_t[8];

    eeprom_read(0, save_buffer_1);
    eeprom_read(1, save_buffer_2);
    if(save_buffer_1[0] == 0x02) {
        high_score = 0;

        high_score |= save_buffer_1[1] << 24;
        high_score |= save_buffer_1[2] << 16;
        high_score |= save_buffer_1[3] << 8;
        high_score |= save_buffer_1[4];

        rng_state = 0;
        rng_state |= save_buffer_2[0] << 24;
        rng_state |= save_buffer_2[1] << 16;
        rng_state |= save_buffer_2[2] << 8;
        rng_state |= save_buffer_2[3];
        set_rng_state(rng_state);
    }else {
        high_score = 0;
        save_buffer_1[0] = 0x02;
        for(int i = 1; i < 8; i++) {
            save_buffer_1[i] = 0x00;
            save_buffer_2[i] = 0x00;
        }
        save();
    }
}

void SaveManager::save()
{
    save_buffer_1[1] = (high_score >> 24) & 0xFF;
    save_buffer_1[2] = (high_score >> 16) & 0xFF;
    save_buffer_1[3] = (high_score >> 8) & 0xFF;
    save_buffer_1[4] = high_score & 0xFF;

    save_buffer_2[0] = (rng_state >> 24) & 0xFF;
    save_buffer_2[1] = (rng_state >> 16) & 0xFF;
    save_buffer_2[2] = (rng_state >> 8) & 0xFF;
    save_buffer_2[3] = rng_state & 0xFF;

    eeprom_write(0, save_buffer_1);
    eeprom_write(1, save_buffer_2);
}

SaveManager* save_manager;