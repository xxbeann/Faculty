import cv2
import mediapipe as mp

# Mediapipe 초기 설정
mp_drawing = mp.solutions.drawing_utils
mp_hands = mp.solutions.hands

# 웹캠 열기
cap = cv2.VideoCapture(0)

# Mediapipe Hands 모듈 설정
with mp_hands.Hands(max_num_hands=1, min_detection_confidence=0.5,
                    min_tracking_confidence=0.5) as hands:
    while cap.isOpened():
        success, image = cap.read()
        if not success:
            continue

        # 이미지 좌우 반전 및 BGR -> RGB 변환
        image = cv2.cvtColor(cv2.flip(image, 1), cv2.COLOR_BGR2RGB)
        result = hands.process(image)
        image = cv2.cvtColor(image, cv2.COLOR_RGB2BGR)

        # 기본 텍스트 설정
        gesture_text = 'Cannot detect hand'

        # 손이 인식된 경우
        if result.multi_hand_landmarks:
            hand_landmarks = result.multi_hand_landmarks[0]

            # 손가락 인식 변수들 초기화
            thumb = False
            index_finger = False
            middle_finger = False
            ring_finger = False
            pinky_finger = False

            # 손가락 상태 판별
            # 엄지: 4번 마디가 2번 마디보다 x축 기준으로 오른쪽(작으면) 접힌 것으로 판단
            if hand_landmarks.landmark[4].x < hand_landmarks.landmark[2].x:
                thumb = True

            # 검지: 8번 마디가 6번 마디보다 y축 기준으로 위쪽(작으면) 펴진 것으로 판단
            if hand_landmarks.landmark[8].y < hand_landmarks.landmark[6].y:
                index_finger = True

            # 중지: 12번 마디가 10번 마디보다 y축 기준으로 아래쪽(크면) 접힌 것으로 판단
            if hand_landmarks.landmark[12].y < hand_landmarks.landmark[10].y:
                middle_finger = True

            # 약지: 16번 마디가 14번 마디보다 y축 기준으로 아래쪽(크면) 접힌 것으로 판단
            if hand_landmarks.landmark[16].y < hand_landmarks.landmark[14].y:
                ring_finger = True

            # 새끼: 20번 마디가 18번 마디보다 y축 기준으로 위쪽(작으면) 펴진 것으로 판단
            if hand_landmarks.landmark[20].y < hand_landmarks.landmark[18].y:
                pinky_finger = True

            # 제스처 인식
            # 1. Rock and Roll: 검지와 새끼손가락이 펴져 있고, 나머지는 접힌 상태
            if index_finger and not middle_finger and not ring_finger and pinky_finger:
                gesture_text = 'Rock and Roll'
            # 2. 가위: 검지와 중지가 펴져 있고, 나머지는 접힌 상태
            elif index_finger and middle_finger and not ring_finger and not pinky_finger:
                gesture_text = 'Scissors (Gawi)'
            # 3. 보: 모든 손가락이 펴져 있는 상태
            elif thumb and index_finger and middle_finger and ring_finger and pinky_finger:
                gesture_text = 'Paper (Bo)'
            # 4. 바위: 모든 손가락이 접혀 있는 상태
            elif not index_finger and not middle_finger and not ring_finger and not pinky_finger:
                gesture_text = 'Rock (Bawi)'
            else:
                gesture_text = 'Unknown Gesture'

            # 손가락 랜드마크 그리기
            mp_drawing.draw_landmarks(image, hand_landmarks, mp_hands.HAND_CONNECTIONS)

        # 텍스트 출력
        cv2.putText(image, f'Hand shape : {gesture_text}', (10, 30),
                    cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 0, 255), 2)

        # 결과 이미지 보여주기
        cv2.imshow('image', image)

        # 'q' 입력시 종료
        if cv2.waitKey(1) == ord('q'):
            break

# 웹캠 및 창 닫기
cap.release()
cv2.destroyAllWindows()
