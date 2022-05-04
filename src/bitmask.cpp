#include "bitmask.h"

Bitmask::Bitmask()
    :
    mask(0)
{
}

void Bitmask::set_mask(const Bitmask& other)
{
    mask = other.get_mask();
}

uint32_t Bitmask::get_mask() const
{
    return mask;
}

void Bitmask::set_bit(int pos, bool on)
{
    if(on)
    {
        set_bit(pos);
    }   
    else
    {
        clear_bit(pos);
    }
}

void Bitmask::set_bit(int pos)
{
    mask = mask | (1 << pos);
}

bool Bitmask::get_bit(int pos) const
{
    return (mask & (1 << pos)) != 0;
}

void Bitmask::clear_bit(int pos)
{
    mask = mask & ~(1 << pos);
}

void Bitmask::clear_mask()
{
    mask = 0;
}