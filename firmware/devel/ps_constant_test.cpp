#include "ps_constant_test.h"
#include "ps_time_utils.h"
#include "ps_constants.h"

namespace ps
{

    const String ConstantTest::DurationKey = String("duration");
    const String ConstantTest::ValueKey = String("value");


    ConstantTest::ConstantTest() 
    { 
        setName("constant");
    } 


    void ConstantTest::setDuration(uint64_t duration)
    {
        duration_ = duration;
    }


    uint64_t ConstantTest::getDuration() const
    {
        return duration_;
    }


    void ConstantTest::setValue(float value)
    {
        value_ = value;
    }


    float ConstantTest::getValue(uint64_t t) const 
    {
        if (t < quietTime_)
        {
            return quietValue_;
        }
        else
        {
            return value_;
        }
    }


    bool ConstantTest::isDone(uint64_t t) const 
    {
        return (t >= duration_ );
    }


    float ConstantTest::getMaxValue() const 
    {
        return max(value_,quietValue_);
    }


    float ConstantTest::getMinValue() const 
    {
        return min(value_,quietValue_);
    }


    void ConstantTest::getParam(JsonObject &json)
    {
        BaseTest::getParam(json);
        json.set(ValueKey, value_, JsonFloatDecimals);
        json.set(DurationKey, convertUsToMs(duration_));
    }

    ReturnStatus ConstantTest::setParam(JsonObject &jsonMsg, JsonObject &jsonDat)
    {
        ReturnStatus status;
        status = BaseTest::setParam(jsonMsg,jsonDat);

        // Extract JsonObject containing parameters
        JsonObject &jsonPrm = getParamJsonObject(jsonMsg,status);
        if (!status.success)
        {
            return status;
        }

        // Get value
        if (jsonPrm.containsKey(ValueKey))
        {
            if (jsonPrm[ValueKey].is<float>())
            {
                value_  = jsonPrm.get<float>(ValueKey);
                jsonDat.set(ValueKey,value_,JsonFloatDecimals);
            }
            else
            {
                status.success = false;
                String errorMsg = ValueKey + String(" not a float");
                status.appendToMessage(errorMsg);
            }
        }
       
        // Get duration
        if (jsonPrm.containsKey(DurationKey))
        {
            if (jsonPrm[DurationKey].is<unsigned long>())
            {
                duration_ = convertMsToUs(jsonPrm.get<unsigned long>(DurationKey));
                jsonDat.set(DurationKey,convertUsToMs(duration_));
            }
            else
            {
                status.success = false;
                String errorMsg = DurationKey + String(" not uint32");
                status.appendToMessage(errorMsg);
            }
        }

        return status;
    }

    //uint64_t duration_ = 5000000;
    //float value_ = 1.0;

} // namespace ps
