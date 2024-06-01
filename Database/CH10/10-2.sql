USE cookDB;
SELECT * FROM userTBL;

SHOW INDEX FROM userTBL;

CREATE INDEX idx_userTBL_addr
ON userTBL (addr);

SHOW INDEX FROM userTBL;

CREATE UNIQUE INDEX idx_userTBL_birtyYear
ON userTBL (birthYear);

CREATE UNIQUE INDEX idx_userTBL_userName
ON userTBL (userName);
SHOW INDEX FROM userTBL;

INSERT INTO userTBL VALUES ('GHD', '강호동', 1988, '미국', NULL, NULL, 172, NULL);

CREATE INDEX idx_userTBL_userName_birthYear
ON userTBL (userName, birthYear);
DROP INDEX idx_userTBL_userName ON userTBL;
SHOW INDEX FROM userTBL;

SELECT * from userTBL;

SELECT * FROM userTBL WHERE userName = '신동엽' and birthYear = '1971';

CREATE INDEX idx_userTBL_mobile1
ON userTBL (mobile1);
SELECT * FROM userTBL WHERE mobile1 = '011';

SHOW INDEX FROM userTBL;

DROP INDEX idx_userTBL_addr ON userTBL;
DROP INDEX idx_userTBL_userName_birthYear ON userTBL;
DROP INDEX idx_userTBL_mobile1 ON userTBL;

ALTER TABLE userTBL DROP PRIMARY KEY;