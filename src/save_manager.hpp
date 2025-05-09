#include <stdint.h>
#include <libdragon.h>

struct SaveManager {
    uint8_t* save_buffer_1 = nullptr;
    uint8_t* save_buffer_2 = nullptr;
    
    uint32_t high_score;

    void load();
    void save();
};

extern SaveManager* save_manager;