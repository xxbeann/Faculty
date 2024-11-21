import cv2

# 두 이미지를 불러옵니다.
image1 = cv2.imread('Images/Jerry.jpg')
image2 = cv2.imread('images/Tom.jpg')

# 두 이미지의 높이가 같다고 가정.
# 두 이미지를 가로로 붙입니다.
merged_image = cv2.hconcat([image1, image2])

# 붙인 이미지를 저장.
cv2.imwrite('TomAndJerry.jpg', merged_image)
