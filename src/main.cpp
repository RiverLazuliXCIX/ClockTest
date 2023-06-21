#include "bn_core.h"
#include "bn_log.h"

#include "agbabi.h"
#include "aeabi.h"

int main()
{
    bn::core::init();
    auto x = __agbabi_sqrt(9);  // this doesn't work
    auto y = __aeabi_idiv(32, 16);  // this works
    BN_LOG(x);
    BN_LOG(y);

    while(true)
    {
        bn::core::update();
    }
}