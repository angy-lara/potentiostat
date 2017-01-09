#ifndef PS_ANALOG_SUBSYSTEM_H
#define PS_ANALOG_SUBSYSTEM_H
#include "ps_pin_map.h"
#include "ps_gains.h"

namespace ps
{

    class AnalogSubsystem
    {
        public:

            static const VoltGain DefaultVoltGain = VoltGain1X;
            static const CurrGain DefaultCurrGain = CurrGainPathIn1;

            static const uint16_t DefaultAnalogWriteResolution = 12;
            static const uint16_t DefaultAnalogReadResolution = 16;
            static const uint16_t DefaultAnalogReadAveraging = 16;
            static const uint8_t  DefaultAnalogReference = INTERNAL;

            static const uint16_t MaxValueDAC = (1 << DefaultAnalogWriteResolution)-1;
            static const uint16_t MidValueDAC = MaxValueDAC/2;

            AnalogSubsystem();
            void initialize();

            void setVoltGain(VoltGain value);
            void setCurrGain(CurrGain value);

            VoltGain getVoltGain() const;
            CurrGain getCurrGain() const;

            String getVoltGainString() const;
            String getCurrGainString() const;

            void setValueDAC(uint16_t value);   // Set voltage output DAC value 16-bit
            uint16_t getValueDAC() const;       // Get the DAC voltage output setting  

            uint16_t getTransAmpAin() const;   // Read analog input associated with the transimpedance amplifier 
            uint16_t getRefElectAin() const;   // Read analog input associated with the refernce electrode

        protected:

            uint16_t valueDAC_ = 0;

    };
}


#endif
