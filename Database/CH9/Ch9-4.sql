USE tableDB;
DROP TABLE IF EXISTS buyTBL, userTBL;
CREATE TABLE userTBL
( userID CHAR(8),
userName VARCHAR(10),
birthYear INT,
addr CHAR(2),
mobile1 CHAR(3),
mobile2 CHAR(8),
height SMALLINT,
mDate DATE
);
CREATE TABLE buyTBL
( num INT AUTO_INCREMENT PRIMARY KEY,
userID CHAR(8),
prodName CHAR(6),
groupName CHAR(4),
price INT,
amount SMALLINT
);

INSERT INTO userTBL VALUES ('YJS', '유재석', 1972, '서울', '010', '11111111', 178, '2008-8-8');
INSERT INTO userTBL VALUES ('KHD', '강호동', NULL, '경북', '011', '22222222', 182, '2007-7-7');
INSERT INTO userTBL VALUES ('KKJ', '김국진', 1865, '서울', '019', '33333333', 171, '2009-9-9');
INSERT INTO userTBL VALUES ('KYM', '김용만', 1967, '서울', '010', '44444444', 177, '2015-5-5');
INSERT INTO buyTBL VALUES (NULL, 'KHD', '운동화', NULL, 30, 2);
INSERT INTO buyTBL VALUES (NULL, 'KHD', '노트북', '전자', 1000, 1);
INSERT INTO buyTBL VALUES (NULL, 'KYM', '모니터', '전자', 200, 1);
INSERT INTO buyTBL VALUES (NULL, 'PSH', '모니터', '전자', 200, 5);

ALTER TABLE userTBL
ADD CONSTRAINT PK_userTBL_userID
PRIMARY KEY (userID);

ALTER TABLE buyTBL
ADD CONSTRAINT FK_userTBL_buyTBL
FOREIGN KEY (userID)
REFERENCES userTBL (userID);

DELETE FROM buyTBL WHERE userID = 'PSH';
ALTER TABLE buyTBL
ADD CONSTRAINT FK_userTBL_buyTBL
FOREIGN KEY (userID)
REFERENCES userTBL (userID);

INSERT INTO buyTBL VALUES (NULL, 'PSH', '모니터', '전자', 200, 5);

SET foreign_key_checks = 0;
INSERT INTO buyTBL VALUES (NULL, 'PSH', '모니터', '전자', 200, 5);
INSERT INTO buyTBL VALUES (NULL, 'KHD', '청바지', '의류', 50, 3);
INSERT INTO buyTBL VALUES (NULL, 'PSH', '메모리', '전자', 80, 10);
INSERT INTO buyTBL VALUES (NULL, 'KJD', '책', '서적', 15, 5);
INSERT INTO buyTBL VALUES (NULL, 'LHJ', '책', '서적', 15, 2);
INSERT INTO buyTBL VALUES (NULL, 'LHJ', '청바지', '의류', 50, 1);
INSERT INTO buyTBL VALUES (NULL, 'PSH', '운동화', NULL, 30, 2);
INSERT INTO buyTBL VALUES (NULL, 'LHJ', '책', '서적', 15, 1);
INSERT INTO buyTBL VALUES (NULL, 'PSH', '운동화', NULL, 30, 2);
SET foreign_key_checks = 1;

ALTER TABLE userTBL
ADD CONSTRAINT CK_birthYear
CHECK (birthYear >= 1900 AND birthYear <= YEAR(CURDATE()));

INSERT INTO userTBL VALUES ('KJD', '김제동', 1974, '경남', NULL, NULL, 173, '2013-3-3');
INSERT INTO userTBL VALUES ('NHS', '남희석', 1971, '충남', '016', '66666666', 180, '2017-4-4');
INSERT INTO userTBL VALUES ('SDY', '신동엽', 1971, '경기', NULL, NULL, 176, '2008-10-10');
INSERT INTO userTBL VALUES ('LHJ', '이휘재', 1972, '경기', '011', '88888888', 180, '2006-4-4');
INSERT INTO userTBL VALUES ('LKK', '이경규', 1960, '경남', '018', '99999999', 170, '2004-12-12');
INSERT INTO userTBL VALUES ('PSH', '박수홍', 1970, '서울', '010', '00000000', 183, '2012-5-5');

UPDATE userTBL SET userID = 'PARK' WHERE userID='PSH';

SET foreign_key_checks = 0;
UPDATE userTBL SET userID = 'PARK' WHERE userID='PSH';
SET foreign_key_checks = 1;

SELECT B.userID, U.userName, B.prodName, U.addr, CONCAT(U.mobile1, U.mobile2) AS '연락처'
FROM buyTBL B
INNER JOIN userTBL U
ON B.userID = U.userID;

SELECT COUNT( * ) FROM buyTBL;

SELECT B.userID, U.userName, B.prodName, U.addr, CONCAT(U.mobile1, U.mobile2) AS '연락처'
FROM buyTBL B
LEFT OUTER JOIN userTBL U
ON B.userID = U.userID
ORDER BY B.userID;

SET foreign_key_checks = 0;
UPDATE userTBL SET userID = 'PSH' WHERE userID='PARK';
SET foreign_key_checks = 1;

ALTER TABLE buyTBL
DROP FOREIGN KEY FK_userTBL_buyTBL;
ALTER TABLE buyTBL
ADD CONSTRAINT FK_userTBL_buyTBL
FOREIGN KEY (userID)
REFERENCES userTBL (userID)
ON UPDATE CASCADE;

UPDATE userTBL SET userID = 'PARK' WHERE userID='PSH';
SELECT B.userID, U.userName, B.prodName, U.addr, CONCAT(U.mobile1, U.mobile2) AS '연락처'
FROM buyTBL B
INNER JOIN userTBL U
ON B.userID = U.userID
ORDER BY B.userID;

DELETE FROM userTBL WHERE userID = 'PARK';

ALTER TABLE buyTBL
DROP FOREIGN KEY FK_userTBL_buyTBL;
ALTER TABLE buyTBL
ADD CONSTRAINT FK_userTBL_buyTBL
FOREIGN KEY (userID)
REFERENCES userTBL (userID)
ON UPDATE CASCADE
ON DELETE CASCADE;

DELETE FROM userTBL WHERE userID = 'PARK';
SELECT * FROM buyTBL;

ALTER TABLE userTBL
DROP COLUMN birthYear;