#include "dji_vehicle.hpp"
#include "dji_linux_helpers.hpp"
#include "osdkosal_linux.h"
#include "dji_battery.hpp"
#include "get_Telemetry.hpp"
#include <cmath>

using namespace DJI::OSDK;
using namespace DJI::OSDK::Telemetry;

bool get_Telemetry::setUpSubscription(int pkgIndex, int freq,TopicName topicList[], uint8_t topicSize,int timeout)
{

    if (vehicle) {
    /*! Telemetry: Verify the subscription*/
    ACK::ErrorCode subscribeStatus;
    subscribeStatus = vehicle->subscribe->verify(timeout);
    if (ACK::getError(subscribeStatus) != ACK::SUCCESS) {
      ACK::getErrorCodeMessage(subscribeStatus, __func__);
      return false;
    }

    bool enableTimestamp = false;
    bool pkgStatus = vehicle->subscribe->initPackageFromTopicList(
        pkgIndex, topicSize, topicList, enableTimestamp, freq);
    if (!(pkgStatus)) {
      return pkgStatus;
    }

    /*! Start listening to the telemetry data */
    subscribeStatus = vehicle->subscribe->startPackage(pkgIndex, timeout);
    if (ACK::getError(subscribeStatus) != ACK::SUCCESS) {
      ACK::getErrorCodeMessage(subscribeStatus, __func__);
      /*! Cleanup*/
      ACK::ErrorCode ack = vehicle->subscribe->removePackage(pkgIndex, timeout);
      if (ACK::getError(ack)) {
        DERROR(
            "Error unsubscription; please restart the drone/FC to get "
            "back to a clean state");
      }
      return false;
    }
    return true;
  } else {
    DERROR("vehicle haven't been initialized", __func__);
    return false;
  }
    return true;
}

bool get_Telemetry::Subscription(int timeout)
{
  const int pkgIndex = 0;
  int freq = 10;
  TopicName topicList[] = {TOPIC_STATUS_FLIGHT, TOPIC_STATUS_DISPLAYMODE,
                           TOPIC_AVOID_DATA, TOPIC_VELOCITY};
  int topicSize = sizeof(topicList) / sizeof(topicList[0]);
  bool ret = setUpSubscription(pkgIndex, freq, topicList, topicSize, timeout);
  Sub_state = ret;
  return ret;
}

bool get_Telemetry::getvelocity_data(int timeout) {
  /*! Step 1: Verify and setup the subscription */
  
  if(Sub_state == false)
    return false;
  Telemetry::TypeMap<TOPIC_VELOCITY>::type VELOCITY_DATA ;

  VELOCITY_DATA = vehicle->subscribe->getValue<TOPIC_VELOCITY>();
  


  double true_velocity = VELOCITY_DATA.data.x* VELOCITY_DATA.data.x + VELOCITY_DATA.data.y*VELOCITY_DATA.data.y + VELOCITY_DATA.data.z*VELOCITY_DATA.data.z;

  true_velocity = sqrt(true_velocity);

  DSTATUS("now speed is %ll\n",true_velocity);
  // /*! Step 2: Start go home */
  // DSTATUS("Start go home action");
  // ErrorCode::ErrorCodeType goHomeAck =
  //     vehicle->flightController->startGoHomeSync(timeout);
  // if (goHomeAck != ErrorCode::SysCommonErr::Success) {
  //   DERROR("Fail to execute go home action!  Error code: %llx\n", goHomeAck);
  //   return false;
  // }


  // /*! Step 3: Start landing */
  // DSTATUS("Start landing action");
  // if (!checkActionStarted(VehicleStatus::DisplayMode::MODE_AUTO_LANDING)) {
  //   DERROR("Fail to execute Landing action!");
  //   return false;
  // } else {
  //   while (vehicle->subscribe->getValue<TOPIC_STATUS_DISPLAYMODE>() ==
  //              VehicleStatus::DisplayMode::MODE_AUTO_LANDING &&
  //          vehicle->subscribe->getValue<TOPIC_STATUS_FLIGHT>() ==
  //              VehicleStatus::FlightStatus::IN_AIR) {
  //     Telemetry::TypeMap<TOPIC_AVOID_DATA>::type avoidData =
  //         vehicle->subscribe->getValue<TOPIC_AVOID_DATA>();
  //     Platform::instance().taskSleepMs(1000);
  //     if ((0.65 < avoidData.down && avoidData.down < 0.75) &&
  //         (avoidData.downHealth == 1)) {
  //       break;
  //     }
  //   }
  // }
  // DSTATUS("Finished landing action");

  // /*! Step 4: Confirm Landing */
  // DSTATUS("Start confirm Landing and avoid ground action");
  // ErrorCode::ErrorCodeType forceLandingAvoidGroundAck =
  //     vehicle->flightController->startConfirmLandingSync(timeout);
  // if (forceLandingAvoidGroundAck != ErrorCode::SysCommonErr::Success) {
  //   DERROR(
  //       "Fail to execute confirm landing avoid ground action! Error code: "
  //       "%llx\n ",
  //       forceLandingAvoidGroundAck);
  //   return false;
  // }
  // if (!checkActionStarted(VehicleStatus::DisplayMode::MODE_AUTO_LANDING)) {
  //   return false;
  // } else {
  //   while (vehicle->subscribe->getValue<TOPIC_STATUS_DISPLAYMODE>() ==
  //              VehicleStatus::DisplayMode::MODE_AUTO_LANDING &&
  //          vehicle->subscribe->getValue<TOPIC_STATUS_FLIGHT>() ==
  //              VehicleStatus::FlightStatus::IN_AIR) {
  //     Platform::instance().taskSleepMs(1000);
  //   }
  // }
  // DSTATUS("Finished force Landing and avoid ground action");

  // /*! Step 5: Landing finished check*/
  // if (vehicle->subscribe->getValue<TOPIC_STATUS_DISPLAYMODE>() !=
  //         VehicleStatus::DisplayMode::MODE_P_GPS ||
  //     vehicle->subscribe->getValue<TOPIC_STATUS_DISPLAYMODE>() !=
  //         VehicleStatus::DisplayMode::MODE_ATTITUDE) {
  //   DSTATUS("Successful landing!");
  // } else {
  //   DERROR(
  //       "Landing finished, but the aircraft is in an unexpected mode. "
  //       "Please connect DJI Assistant.");
  //   teardownSubscription(pkgIndex, timeout);
  //   return false;
  // }
  // /*! Step 6: Cleanup */
  // teardownSubscription(pkgIndex, timeout);
  return true;
}





get_Telemetry::get_Telemetry(Vehicle *vehicle)
{
    this->vehicle = vehicle;
}

get_Telemetry::~get_Telemetry()
{
}