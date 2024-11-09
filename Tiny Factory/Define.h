#include "string"	

#define PORT_PREFIX "\\\\.\\"
#define CONVAYORBELT_ON_DATA "ON"
#define CONVAYORBELT_OFF_DATA "OFF"
#define MAXIMUM_COMMUNICATION_COUNT 20
#define DATA_LENGTH 255
#define SYNC_TIME 1000

#define DATASTORE_PATH "./log.txt"

#define OBJECT_DETECTION "OBJECTDETECTION"


//커스텀 메시지
#define ON_CONNECT_COMPLETE_MESSAGE WM_USER + 150


//카메라
#define CAMERA_WIDTH 320
#define CAMERA_HEIGHT 260
#define CAMERA_EVENT 1000


const std::string yoloCfg = "C:/Users/biotite/Desktop/TinyFactoryData/test.cfg";
const std::string yoloWeight = "C:/Users/biotite/Desktop/TinyFactoryData/test_last.weights";
const std::string yoloClassFile = "C:/Users/biotite/Desktop/TinyFactoryData/tiny.names";
#define THRESHOLD 0.5

//데이터 통신
#define DATAPROCESS_ON_DATA "ON"
#define DATAPROCESS_OFF_DATA "OFF"
