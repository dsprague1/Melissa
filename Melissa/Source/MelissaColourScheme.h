#pragma once

#include <cstdint>
#include <tuple>

class MelissaColourScheme
{
public:
    static std::pair<uint32_t, uint32_t> BackGroundGradationColour()
    {
        return { 0xFF252F41, 0xFF1F2024 };
    }
    
    static uint32_t MainColour()
    {
        return 0xffddeaff;
    }
    
    static uint32_t DialogBackgoundColour()
    {
        return 0xFF1B1F25;
    }
};