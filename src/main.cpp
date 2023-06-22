#include "bn_core.h"
#include "bn_log.h"
#include "bn_regular_bg_ptr.h"
#include "bn_sprite_text_generator.h"
#include "bn_sprite_ptr.h"
#include "bn_vector.h"
#include "bn_string.h"
#include "bn_timer.h"
#include "agbabi.h"

#include "bn_regular_bg_items_background.h"
#include "common_variable_8x16_sprite_font.h"

int main()
{
    bn::core::init();
    bn::regular_bg_ptr background = bn::regular_bg_items::background.create_bg(0, 0);

    bn::sprite_text_generator text_generator(common::variable_8x16_sprite_font);
    text_generator.set_center_alignment();

    bn::vector<bn::sprite_ptr, 32> text_sprites;
    if (__agbabi_rtc_init() == 0)
    {
        __agbabi_datetime_t temp = {0x230622, 0x305113};
        __agbabi_rtc_setdatetime(temp);
    }

    auto ticks = 0;
    while (true)
    {
        ticks++;

        if (ticks > 600)
        {
            auto rtc_time = __agbabi_rtc_datetime();
            text_generator.generate(0, 0, bn::to_string<10>(rtc_time[1]), text_sprites);
            bn::core::update();
            while (true)
            {
            }
        }

        bn::core::update();
    }
}