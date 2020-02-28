#ifndef LAPTOP
#include "CANHandler.h"

CANHandler::CANHandler (std::vector<struct arduino> in)
: a_cans (),
a_fields ()
{
    for (int i = 0; i < in.size (); i ++)
    {
        if (i != 0 || in[i].can_id != in[i - 1].can_id)
        {
            a_cans.push_back (frc::CAN (in[i].can_id));
            a_fields.push_back (std::vector<struct field> ());
            int bitsum = 0;
            for (int j = 0; j < in[i].data.size (); j ++)
            {
                int temp = in[i].data[j].bits;
                bitsum += temp;
                if (bitsum > 64 || temp > 32)
                {
                    break;
                }
                int temp2 = 0;
                for (int k = 0; k < temp; k ++)
                {
                    temp2 |= 1 << k;
                }
                struct field temp_d
                {
                    in[i].data[j].id,
                    temp,
                    temp2,
                    in[i].data[j].multiplier,
                    0
                };
                a_fields[i].push_back (temp_d);
            }
        }
    }
}

float CANHandler::getData (const int which) const
{
    for (int i = 0; i < a_fields.size (); i ++)
    {
        for (int j = 0; j < a_fields[i].size (); j ++)
        {
            if (a_fields[i][j].id == which)
            {
                return a_fields[i][j].data / a_fields[i][j].multiplier;
            }
        }
    }
}

void CANHandler::update ()
{
    frc::CANData data;
    for (int i = 0; i < a_cans.size (); i ++)
    {
        if (a_cans[i].ReadPacketNew (0, &data))
        {   
            uint64_t in = *((uint64_t *) data.data);
            for (int j = 0; j < a_fields[i].size (); j ++)
            {
                struct field datas = a_fields[i][j];
                datas.data = in & datas.bitnum;
                in >>= datas.bits;
            }
        }
    }
}

inline void set_vals (std::vector<struct dataField> *in, int id, unsigned char bits, float multiplier)
{
    struct dataField dfield
    {
        id,
        bits,
        multiplier
    };
    in->push_back (dfield);
}

std::vector<struct arduino> canMakeIn2020 ()
{
    std::vector<struct arduino> can_in;
    struct arduino ard;
    struct dataField dfield;

    ard.can_id = ARDUINO_L_CAN;
    ard.data = std::vector<struct dataField> ();
    set_vals(&ard.data, FL_SWERVE_D, 16, 10.0f);
    set_vals(&ard.data, BL_SWERVE_D, 16, 10.0f);
    set_vals(&ard.data, ARM_D, 16, 10.0f);
    can_in.push_back (ard);

    ard.can_id = ARDUINO_R_CAN;
    ard.data = std::vector<struct dataField> ();
    set_vals(&ard.data, BR_SWERVE_D, 16, 10.0f);
    set_vals(&ard.data, FR_SWERVE_D, 16, 10.0f);
    set_vals(&ard.data, B_TOF_D, 16, 1.0f);
    set_vals(&ard.data, F_TOF_D, 16, 1.0f);
    can_in.push_back (ard);
    return can_in;
}
#endif