#ifndef GET_TELEMETERY
#define GET_TELEMETERY

#include <dji_linux_helpers.hpp>
#include <dji_vehicle.hpp>

using namespace DJI::OSDK;
using namespace DJI::OSDK::Telemetry;

class get_Telemetry
{
private:
    int TopicID;
    Vehicle *vehicle;
    bool Sub_state = false;
public:
    get_Telemetry(Vehicle *vehicle);
    ~get_Telemetry();
    bool Subscription(int timeout);
    bool setUpSubscription(int pkgIndex, int freq,TopicName topicList[], uint8_t topicSize,int timeout = 1);
    bool getvelocity_data(int timeout);
};












#endif // 