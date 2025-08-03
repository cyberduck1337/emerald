#pragma once

#define EMERALD_VERIFY_THROW(EXPR, EXCEPTION, ...) \
    if(!(EXPR)) [[unlikely]]                       \
    {                                              \
        throw EXCEPTION(__VA_ARGS__);              \
    }                                              \
