#ifndef LAPTOP
#pragma once

#include <stdint.h>
#include <string>
#include <vector>
#include <frc/CAN.h>
#include "Prefs.h"

struct arduino
{
    int can_id;
    std::vector<struct dataField> data;
};

struct dataField
{
    int id;
    uint8_t bits;
    float multiplier;
};

// only used internally
struct field
{
    int id;
    uint8_t bits;
    uint32_t bitnum;
    float multiplier;
    int32_t data;
};

class CANHandler
{
    public:
        CANHandler (std::vector<struct arduino> in);
        float getData (const int which) const;
        void update ();
    private:
        std::vector<frc::CAN> a_cans;
        std::vector<std::vector<struct field>> a_fields;
};

inline void set_vals (std::vector<struct dataField> *in, int id, unsigned char bits, float multiplier);

std::vector<struct arduino> canMakeIn2020 ();
#endif