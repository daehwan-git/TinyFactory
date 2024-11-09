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


const std::string yoloCfg = "C:/Users/82108/Desktop/file/test.cfg";
const std::string yoloWeight = "C:/Users/82108/Desktop/file/test.weights";
const std::string yoloClassFile = "C:/Users/82108/source/repos/QualityTest1/obj.names";

//데이터 통신
#define DATAPROCESS_ON_DATA "ON"
#define DATAPROCESS_OFF_DATA "OFF"
