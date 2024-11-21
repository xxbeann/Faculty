import cv2

# 이미지를 불러옵니다.
image_path = 'Images/suji.jpg'  # 이미지 파일 경로를 지정.
original_image = cv2.imread(image_path)

# 이미지의 높이와 너비를 얻습니다.
height, width = original_image.shape[:2]

# 자를 영역의 시작 좌표와 종료 좌표를 설정합니다.
x_start, y_start = 150, 25  # 시작 좌표 (x, y)
x_end, y_end = 450, 450      # 종료 좌표 (x, y)

# 이미지를 자릅니다.
cropped_image = original_image[y_start:y_end, x_start:x_end]

# 자른 이미지를 저장합니다.
cv2.imwrite('cropped_Suji_image.jpg', cropped_image)

# 자른 이미지를 화면에 표시합니다.
cv2.imshow('Cropped Image', cropped_image)
cv2.waitKey(0)
cv2.destroyAllWindows()
