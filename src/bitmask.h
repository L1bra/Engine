#pragma once

#include <stdint.h>

class Bitmask
{
private:
    uint32_t mask;
public:
    Bitmask();
    ~Bitmask() = default;

    void set_mask(const Bitmask& other);
    uint32_t get_mask() const;
    
    void set_bit(int pos, bool on);
    void set_bit(int pos);
    bool get_bit(int pos) const;

    void clear_bit(int pos);
    void clear_mask();
};