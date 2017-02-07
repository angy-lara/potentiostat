#ifndef PS_MESSAGE_SENDER_H
#define PS_MESSAGE_SENDER_H
#include <Arduino.h>
#include "ArduinoJson.h"
#include "ps_constants.h"
#include "ps_sample.h"
#include "ps_return_status.h"

namespace ps
{

    class MessageSender
    {

        public:

            MessageSender();
            void sendSample(Sample sample);
            void sendCommandResponse(ReturnStatus status);

        protected:

            StaticJsonBuffer<JsonMessageBufferSize> jsonBuffer_;

    };


} // namespace ps


#endif
