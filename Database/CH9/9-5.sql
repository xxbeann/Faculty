USE cookDB;
CREATE VIEW v_userbuyTBL
AS
SELECT U.userID AS 'USER ID', U.userName AS 'USER NAME', B.prodName AS 'PRODUCT NAME',
U.addr, CONCAT(U.mobile1, U.mobile2) AS 'MOBILE PHONE'
FROM userTBL U
INNER JOIN buyTBL B
ON U.userID = B.userID;
SELECT `USER ID`, `USER NAME` FROM v_userbuyTBL; -- 주의! 백틱(키보드 1의 왼쪽 키) 사용

ALTER VIEW v_userbuyTBL
AS
SELECT U.userID AS '사용자 아이디', U.userName AS '이름', B.prodName AS '제품 이름',
U.addr, CONCAT(U.mobile1, U.mobile2) AS '전화 번호'
FROM userTBL U
INNER JOIN buyTBL B
ON U.userID = B.userID;
SELECT `이름`, `전화 번호` FROM v_userbuyTBL; -- 주의! 백틱 사용

DROP VIEW v_userbuyTBL;

USE cookDB;
CREATE OR REPLACE VIEW v_userTBL
AS
SELECT userID, userName, addr FROM userTBL;

DESCRIBE v_userTBL;

SHOW CREATE VIEW v_userTBL;

UPDATE v_userTBL SET addr = '부산' WHERE userID='LKK';

INSERT INTO v_userTBL (userID, userName, addr) VALUES ('KBM', '김병만', '충북');

CREATE OR REPLACE VIEW v_sum
AS
SELECT userID AS 'userID', SUM(price * amount) AS 'total'
FROM buyTBL GROUP BY userID;
SELECT * FROM v_sum;

SELECT * FROM INFORMATION_SCHEMA.VIEWS
WHERE TABLE_SCHEMA = 'cookDB' AND TABLE_NAME = 'v_sum';

CREATE OR REPLACE VIEW v_height180
AS
SELECT * FROM userTBL WHERE height >= 180;
SELECT * FROM v_height180;

DELETE FROM v_height180 WHERE height < 180;

INSERT INTO v_height180 VALUES ('SJH', '서장훈', 1974, '경기', '010', '5555555', 158, '2019-01-01');

SELECT * FROM v_height180;

ALTER VIEW v_height180
AS
SELECT * FROM userTBL WHERE height >= 180
WITH CHECK OPTION;
INSERT INTO v_height180 VALUES('KBM', '김병만', 1977, '서울', '010', '3333333', 155, '2019-3-3');

CREATE OR REPLACE VIEW v_userbuyTBL
AS
SELECT U.userID, U.userName, B.prodName, U.addr, CONCAT(U.mobile1, U.mobile2) AS mobile
FROM userTBL U
INNER JOIN buyTBL B
ON U.userID = B.userID;
INSERT INTO v_userbuyTBL VALUES ('PKL', '박경리', '운동화', '경기', '00000000000', '2020-2-2');

DROP TABLE IF EXISTS buyTBL, userTBL;

SELECT * FROM v_userbuyTBL;

CHECK TABLE v_userbuyTBL;