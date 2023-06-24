#include "bn_core.h"
#include "bn_log.h"
#include "bn_regular_bg_ptr.h"
#include "bn_sprite_text_generator.h"
#include "bn_sprite_ptr.h"
#include "bn_vector.h"
#include "bn_string.h"
#include "agbabi.h"

#include "bn_regular_bg_items_background.h"
#include "common_variable_8x16_sprite_font.h"

int main()
{
    bn::core::init();

    bn::regular_bg_ptr background = bn::regular_bg_items::background.create_bg(0, 0);
    bn::sprite_text_generator text_generator(common::variable_8x16_sprite_font);
    bn::vector<bn::sprite_ptr, 32> text_sprites;

    text_generator.set_center_alignment();

    if (__agbabi_rtc_init() == 0)
    {
        __agbabi_rtc_settime(0x000012);

        BN_LOG("rtc time: ", __agbabi_rtc_time());

        text_generator.generate(0, 0, bn::to_string<32>(__agbabi_rtc_time()), text_sprites);
    }

    while (true)
    {
        bn::core::update();
    }
}