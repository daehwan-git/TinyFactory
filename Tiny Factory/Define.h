#include "string"	

#define PORT_PREFIX "\\\\.\\"
#define CONVAYORBELT_ON_DATA "ON"
#define CONVAYORBELT_OFF_DATA "OFF"
#define MAXIMUM_COMMUNICATION_COUNT 20
#define DATA_LENGTH 255
#define SYNC_TIME 1000

#define DATASTORE_PATH "./log.txt"

#define OBJECT_DETECTION "OBJECTDETECTION"


//Ŀ���� �޽���
#define ON_CONNECT_COMPLETE_MESSAGE WM_USER + 150


//ī�޶�
#define CAMERA_WIDTH 320
#define CAMERA_HEIGHT 260
#define CAMERA_EVENT 1000


//������ ��
const std::string yoloCfg = "C:/Users/82108/Desktop/file/tiny.cfg";
const std::string yoloWeight = "C:/Users/82108/Desktop/file/tiny.weights";
const std::string yoloClassFile = "C:/Users/82108/Desktop/file/tinytiny.names";
#define THRESHOLD 0.1

#define NORMALOBJECT "NormalObject"
#define DIFFRENTSHAPEOBJECT "DIFFERENTSHAPEOBJECT"


//������ ���
#define DATAPROCESS_ON_DATA "ON"
#define DATAPROCESS_OFF_DATA "OFF"
