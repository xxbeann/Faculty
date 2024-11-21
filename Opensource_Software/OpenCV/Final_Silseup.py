import cv2
import numpy as np

alpha = 0.5

# 이미지 읽기
img1 = cv2.imread('images/ramus.jpg')
img2 = cv2.imread('images/ramusKing.jpg')
img3 = cv2.imread('images/effect1.png')

# 이미지 크기 가져오기
height, width, _ = img1.shape

# 이미지 크기 출력
print(f"img1 크기: {img1.shape}")  # (height, width, channels)
print(f"img2 크기: {img2.shape}")
print(f"img3 크기: {img3.shape}")

# img1의 왼쪽 3/5 자르기
img1_cropped = img1[:, :int(width * 3 / 5)]

# img2의 오른쪽 2/5 자르기
img2_cropped = img2[:, int(width * 3 / 5):]

# 가로로 붙이기
combined = np.hstack((img1_cropped, img2_cropped))

# img3 크기 조정
img3_resized = cv2.resize(img3, (combined.shape[1], combined.shape[0]))

print(f"img3 크기: {img3_resized.shape}")

# 이미지 합성
blended = ( combined * alpha + img3_resized * (1-alpha) )
blended = blended.astype(np.uint8)
blended = cv2.add(combined, img3_resized)

# 결과 출력
cv2.imshow("Original img1", img1)
cv2.imshow("Original img2", img2)
cv2.imshow("Combined Image", combined)
cv2.imshow("blended image", blended)

cv2.waitKey(0)
cv2.destroyAllWindows()
