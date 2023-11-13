'''
***********************************************
**** Date  :  24 / 10 / 2023                  *
**** Author:  Farouk Ehab Fouad               *
**** Tobic :  Driver_Drowsiness_Detection     *
**** Version: First_One                       *
***********************************************
'''

#importing the needed libraries and models 
import cv2 as cv
import imutils
from imutils import face_utils
from scipy.spatial import distance
import dlib
import serial
import RPi.GPIO as GPIO
import time


''' 
Set the pins of Raspberry pi configurations
set the port Broadcom SOC (BCM) 
using pin number 16 which is GPIO_23
'''
GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
GPIO.setup(23, GPIO.OUT)


ser = serial.Serial(
        port ='/dev/serial0',
        baudrate = 115200,
        timeout = 1
        )

drowsy = 'D'
active = 'A'
#creating a variable that contains our model path
model_path = "shape_predictor_68_face_landmarks.dat"


'''
@breif: this function is used to calculate the EAR [ Eye Aspect Ratio]
@ret  : ear
@eye  : this is the parameter to be passed to the function and calculate on this frame
'''
def eye_aspect_ratio(eye):
    A = distance.euclidean(eye[1], eye[5])
    B = distance.euclidean(eye[2], eye[4])
    C = distance.euclidean(eye[0], eye[3])
    
    ear = (A + B) / (C * 2.0)
    return ear

'''
    creating some variable used for configurations and can be in separated config. file
'''

thresh = 0.25    #we can config it as we want for the comparing value
frame_check = 10 #by default 20 and we can config it 

'''
    we need to detect the face using dlib
'''
detect = dlib.get_frontal_face_detector()

'''
    we need to get the 68 landmarks of the face through the previous model
'''
predict = dlib.shape_predictor(model_path)

'''
    dealing with the 2 eyes only to save cpu load and memory usage so getting the coordinates
    of each eye will be through:
    1 -> Left Eye start and end points
    2 -> Right Eye Start and End points 
'''
(L_Start, L_End) = face_utils.FACIAL_LANDMARKS_68_IDXS["left_eye"]
(R_Start, R_End) = face_utils.FACIAL_LANDMARKS_68_IDXS["right_eye"]

'''
    openning the live camera to capture our frames and deal with them as live
'''
cap = cv.VideoCapture(0)

#creating a variable flag
flag = 0
checker = 'd'

'''
    start reading the frames from the live video comes from the camera,
    using the opencv 
'''

while True:

    '''
        @breif : this function reads the frames
        @arg   : None
        @state : this is the retrun state of reading frames [boolean]
        @frame : this is the desired frame
    '''
    
    state, frame = cap.read()
    
    '''
        @breif : this function used to resize the frame
        @des.  : used this function to minimize the size of the frame coming
                 from the camera to save cpu load and processing time
        @param1: the frame
        @param2: width you want
        @param3: height you want
    '''    
    frame = imutils.resize(frame, width = 240, height = 180)
    
    '''
        @breif: this function convert frame from colored to black and white
        @des. : this function is used to deal with only one matrix in black and white
                to reduce the processing time and load on the processor
        @param1: the frame
        @param2: function from opencv with desired type
    '''
    gray_frame = cv.cvtColor(frame, cv.COLOR_BGR2GRAY)
    
    # start saving the detected faces in the subjects 
    subjects = detect(gray_frame, 0)
    
    #loop on those face that stored in subjects
    for subject in subjects:
        
        #get the 68 landmarks of the face 
        shape = predict(gray_frame, subject)
        shape = face_utils.shape_to_np(shape)
        
        #devide the eyes into 2 one left and one right 
        LeftEye = shape[L_Start : L_End]
        RightEye = shape[R_Start : R_End]
        
        #use the EAR function to get the aspect ration of each eye [right and left]
        leftEAR = eye_aspect_ratio(LeftEye)
        rightEAR = eye_aspect_ratio(RightEye)
        
        Final_EAR = (leftEAR + rightEAR) / 2.0
        
        #using convexhull to detect the 6 point of each eye 
        LeftEyeHull = cv.convexHull(LeftEye)
        RightEyeHull = cv.convexHull(RightEye)
        
        #using countours to draw a shape around the detected 6 points of the eyes
        cv.drawContours(frame,[LeftEyeHull], -1, (0,255,0), 1)
        cv.drawContours(frame,[RightEyeHull], -1, (0,255,0), 1)
        
        #start check on the final EAR and compare it with the threshold we have set upper [Note: it's Configurable]
        if Final_EAR < thresh:
            flag+=1
            if flag >= frame_check:
                GPIO.output(23, GPIO.HIGH)
                if checker == 'd':
                    if ser.is_open:
                        ser.flush()
                        ser.write(drowsy.encode())
                        print("Message sent:", drowsy)
                        checker = 'a'
                cv.putText(frame, "**** Drowsy! ****", (40,15), cv.FONT_HERSHEY_SIMPLEX,0.5, (0,0,255),1)
                  
        else:
            flag = 0
            GPIO.output(23, GPIO.LOW)
            if checker == 'a':
                if ser.is_open:
                    #ser.flush()
                    #ser.write(active.encode())
                    checker ='d'
                    print("Message sent:", active)
                
    video = cv.resize(frame, (420, 360))
    cv.imshow("live", video)
    key = cv.waitKey(1) & 0xff
    if key == ord("q"):
        break
cap.release()
cv.destroyAllWindows()
    
