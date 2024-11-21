import cv2

# 첫 번째 이미지를 불러옵니다.
img1 = cv2.imread('images/cat.jpg')

# 두 번째 이미지를 불러옵니다.
img2 = cv2.imread('images/lion.jpg')

img1 = cv2.resize(img1, (int(img1.shape[1] * 0.5), int(img1.shape[0] * 0.5)))


# 첫 번째 이미지의 크기에 맞게 두 번째 이미지를 조정합니다.
img2_resized = cv2.resize(img2, (img1.shape[1], img1.shape[0]))

# 이미지 합성을 위한 가중치를 설정합니다.
alpha = 1  #이미지에 적용되는 가중치


while True:
    # 첫 번째 이미지의 크기에 맞게 두 번째 이미지를 조정합니다.
    img2_resized = cv2.resize(img2, (img1.shape[1], img1.shape[0]))

    # 두 이미지를 합성합니다.
    blended = cv2.addWeighted(img1, alpha, img2_resized, 1 - alpha, 0)

    # 합성된 이미지를 화면에 표시합니다.
    cv2.imshow('Blended Image', blended)

    # 키보드 입력을 기다립니다 (100ms 동안).
    key = cv2.waitKey(100)

    # 'a' 키를 누르면 alpha 값을 증가시킵니다.
    if key == ord('a'):
        alpha = min(alpha + 0.1, 1.0)  # alpha 값을 0.1씩 증가시키며 최댓값을 1로 유지합니다.

    # 'd' 키를 누르면 alpha 값을 감소시킵니다.
    elif key == ord('d'):
        alpha = max(alpha - 0.1, 0.0)  # alpha 값을 0.1씩 감소시키며 최솟값을 0으로 유지합니다.

    # 'q' 키를 누르면 루프를 종료합니다.
    elif key == ord('q'):
        break

# 모든 창을 닫습니다.
cv2.destroyAllWindows()
