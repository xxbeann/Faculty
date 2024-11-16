import cv2
import mediapipe as mp

# Mediapipe Drawing and Hands modules
mp_drawing = mp.solutions.drawing_utils
mp_hands = mp.solutions.hands

# Open the webcam
cap = cv2.VideoCapture(0)

# Initialize Mediapipe Hands
with mp_hands.Hands(
    max_num_hands=2, 
    min_detection_confidence=0.5, 
    min_tracking_confidence=0.5
) as hands:

    while cap.isOpened():
        success, image = cap.read()
        if not success:
            continue

        # Flip the image horizontally and convert color format
        image = cv2.cvtColor(cv2.flip(image, 1), cv2.COLOR_BGR2RGB)
        result = hands.process(image)
        image = cv2.cvtColor(image, cv2.COLOR_RGB2BGR)

        gestures = []
        labels = []

        # Process multiple hands
        if result.multi_hand_landmarks:
            for hand_landmarks, handedness in zip(result.multi_hand_landmarks, result.multi_handedness):
                hand_label = handedness.classification[0].label
                labels.append(hand_label)

                # Check finger positions
                finger_1 = hand_landmarks.landmark[4].y < hand_landmarks.landmark[2].y
                finger_2 = hand_landmarks.landmark[8].y < hand_landmarks.landmark[6].y
                finger_3 = hand_landmarks.landmark[12].y < hand_landmarks.landmark[10].y
                finger_4 = hand_landmarks.landmark[16].y < hand_landmarks.landmark[14].y
                finger_5 = hand_landmarks.landmark[20].y < hand_landmarks.landmark[18].y

                # Determine gesture
                if finger_1 and finger_2 and finger_3 and finger_4 and finger_5:
                    gesture_text = 'Bo'
                elif finger_1 and finger_2:
                    gesture_text = 'Gawi'
                elif not finger_2 and not finger_3 and not finger_4 and not finger_5:
                    gesture_text = 'Bawi'
                else:
                    gesture_text = 'Unknown'
                
                gestures.append(gesture_text)

                # Draw hand landmarks
                mp_drawing.draw_landmarks(image, hand_landmarks, mp_hands.HAND_CONNECTIONS)

        # Determine game result if two hands are detected
        game_result = "Waiting for two hands..."
        if len(gestures) == 2:
            if gestures[0] == gestures[1]:
                game_result = "It's a Draw!"
            elif (gestures[0], gestures[1]) in [('Gawi', 'Bo'), ('Bo', 'Bawi'), ('Bawi', 'Gawi')]:
                game_result = f"{labels[0]} Wins!"
            else:
                game_result = f"{labels[1]} Wins!"

        # Display results
        cv2.putText(image, f'Gestures: {gestures}', (10, 50), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2)
        cv2.putText(image, f'Result: {game_result}', (10, 100), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 0, 255), 2)

        # Show image
        cv2.imshow('Rock-Paper-Scissors', image)

        # Quit when 'q' is pressed
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

cap.release()
cv2.destroyAllWindows()
