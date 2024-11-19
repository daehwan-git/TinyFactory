#include "string"	
#include"opencv2/opencv.hpp"

#define PORT_PREFIX "\\\\.\\"

#define KNOCKDOWN "KNOCKDOWN\n"
#define CONVAYORBELT_ON_DATA "ON\n"
#define CONVAYORBELT_OFF_DATA "OFF\n"
#define RESETDETECT "RESETDETECT\n"
#define RESETGOAL "RESETGOAL"
#define OBJECT_GOAL "OBJECTGOAL"

#define MAXIMUM_COMMUNICATION_COUNT 20
#define DATA_LENGTH 255
#define SYNC_TIME 30

#define BAUDRATE 115200

#define DATASTORE_FILE_NAME "log.txt"


//커스텀 메시지
#define ON_CONNECT_COMPLETE_MESSAGE WM_USER + 150
#define DETECTIONFINISH ON_CONNECT_COMPLETE_MESSAGE + 200
#define DETECTION_RESET ON_CONNECT_COMPLETE_MESSAGE + 250

//카메라
#define CAMERA_WIDTH 640
#define CAMERA_HEIGHT 480
#define CAMERA_EVENT 1000

#define DETECTIONWAITTIME 4000


//데이터 셋
const std::string yoloCfg = "C:/Users/biotite/Desktop/file/test.cfg";
const std::string yoloWeight = "C:/Users/biotite/Desktop/file/test_last.weights";
const std::string yoloClassFile = "C:/Users/biotite/Desktop/file/tiny.names";
#define THRESHOLD 0.5


const cv::String NORMALOBJECT = "NORMAL";
#define DIFFRENTSHAPEOBJECT "DIFFERENTSHAPE"
#define DIFFRENTCOLOROBJECT "DIFFERENTCOLOR"


//데이터 통신
#define DATAPROCESS_ON_DATA "ON\n"
#define DATAPROCESS_OFF_DATA "OFF\n"



//화물차
#define MAX_CARRIAGE_COUNT 5
#define CURRENT_CARRIAGE 2


//로봇 팔

#define AMOTOR_MAX_RANGE 180
#define AMOTOR_MIN_RANGE 0
#define BMOTOR_MAX_RANGE 160
#define BMOTOR_MIN_RANGE 60
#define CMOTOR_MAX_RANGE 180
#define CMOTOR_MIN_RANGE 20
#define ROBOT_ARM_MIN_RANGE 0

#define MOTOR_A "AMOTOR"
#define MOTOR_B "BMOTOR"
#define MOTOR_C "CMOTOR"
#define MOTOR_D "DMOTOR"

#define COMMANDFNINISH "COMMANDFINISH"
#define ROBOTTEST "TEST\n"
#define STORECOMMAND "STORE"
#define ROBOTRECORD "RECORD\n"
#define ROBOTSTOP "RESET\n"
#define PLAYROBOT "PLAY\n"

#define ROBOT_WAIT_TIME 5000
#define RIGHT_OBJECT "RIGHT_OBJECT"
#define WRONG_OBJECT "WRONG_OBJECT"


//데이터 매니저
#define NORMAL_OBJECT_INC ON_CONNECT_COMPLETE_MESSAGE + 300
#define WRONG_OBJECT_INC ON_CONNECT_COMPLETE_MESSAGE + 350


//색상
#define WHITE_COLOR RGB(255, 255, 255)