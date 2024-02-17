#include "bn_core.h"
#include "bn_log.h"
#include "bn_regular_bg_ptr.h"
#include "bn_affine_bg_ptr.h"
#include "bn_sprite_text_generator.h"
#include "bn_sprite_ptr.h"
#include "bn_vector.h"
#include "bn_string.h"
#include "bn_date.h"
#include "bn_time.h"

#include "bn_regular_bg_items_clock_sky_day.h"
#include "bn_regular_bg_items_clock_sky_trans.h"
#include "bn_regular_bg_items_clock_sky_night.h"
#include "bn_regular_bg_items_clock_foreground.h"
#include "bn_affine_bg_items_clock_sun_moon.h"
#include "common_variable_8x16_sprite_font.h"

const int total_day_seconds = 86400;

void time_logic(
    bn::sprite_text_generator& text_generator,
    bn::regular_bg_ptr& sky,
    bn::affine_bg_ptr& sun_moon)
{
    constexpr bn::string_view week_days[] = {
            "Sunday",
            "Monday",
            "Tuesday",
            "Wednesday",
            "Thursday",
            "Friday",
            "Saturday",
        };

    bn::vector<bn::sprite_ptr, 24> date_text_sprites;
    bn::vector<bn::sprite_ptr, 24> time_text_sprites;

    while(true)
    {
        bn::string<64> date_text;
        bn::string<64> time_text;
        date_text_sprites.clear();
        time_text_sprites.clear();

        if (bn::time::active())
        {
            if(bn::optional<bn::date> date = bn::date::current())
            {
                date_text += week_days[date->week_day()];
                date_text += ' ';
                date_text += bn::to_string<4>(date->month_day());
                date_text += '/';
                date_text += bn::to_string<4>(date->month());
                date_text += '/';                
                date_text += bn::to_string<4>(date->year());
                date_text += ' ';
            }
            else
            {
                date_text = "Invalid RTC date";
            }

            if(bn::optional<bn::time> time = bn::time::current())
            {
                auto time_hour = time->hour();
                auto time_minute = time->minute();
                auto time_second = time->second();

                bn::string<4> hour = bn::to_string<4>(time_hour);
                bn::string<4> minute = bn::to_string<4>(time_minute);
                bn::string<4> second = bn::to_string<4>(time_second);

                if(hour.size() == 1)
                {
                    hour = "0" + hour;
                }

                if(minute.size() == 1)
                {
                    minute = "0" + minute;
                }

                if(second.size() == 1)
                {
                    second = "0" + second;
                }

                time_text += hour;
                time_text += ':';
                time_text += minute;
                time_text += ':';
                time_text += second;

                // sun_moon rotation

                bn::fixed current_day_seconds = time_second + (time_minute * 60) + (time_hour * 60 * 60);
                bn::fixed current_day_percentage = current_day_seconds / total_day_seconds;
                bn::fixed degree_time = current_day_percentage * 360;
                sun_moon.set_rotation_angle(360 - degree_time);

                // sky type

                if(time_hour >= 19 || time_hour <= 5)
                {
                    sky = bn::regular_bg_items::clock_sky_night.create_bg(0, 0);
                }
                else if(time_hour >= 7 && time_hour <= 17)
                {
                    sky = bn::regular_bg_items::clock_sky_day.create_bg(0, 0);
                }
                else
                {
                    sky = bn::regular_bg_items::clock_sky_trans.create_bg(0, 0);
                }
            }
            else
            {
                time_text = "Invalid RTC time";
            }
        }
        else
        {
            date_text = "RTC not present - no date";
            time_text = "RTC not present - no time";
        }

        text_generator.generate(-96, 28, date_text, date_text_sprites);
        text_generator.generate(-96, 40, time_text, time_text_sprites);

        bn::core::update();
    }
}

int main()
{
    bn::core::init();

    bn::regular_bg_ptr sky = bn::regular_bg_items::clock_sky_day.create_bg(0, 0);
    sky.set_priority(3);
    bn::affine_bg_ptr sun_moon = bn::affine_bg_items::clock_sun_moon.create_bg(0, 0);
    sun_moon.set_priority(1);
    bn::regular_bg_ptr foreground = bn::regular_bg_items::clock_foreground.create_bg(0, 0);
    foreground.set_priority(0);

    bn::sprite_text_generator text_generator(common::variable_8x16_sprite_font);
    text_generator.set_bg_priority(0);

    while (true)
    {
        time_logic(text_generator, sky, sun_moon);
        bn::core::update();
    }
}