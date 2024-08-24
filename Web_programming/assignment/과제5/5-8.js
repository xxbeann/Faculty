// 숫자1 연산 숫자2
// 입력 배열, 입력 받은 후 순회하며 특정 문자열 기준으로 파싱
// 그리고 출력하고 연산 후 출력

/***********************변수 선언 ********************* */
let input = []; // 입력 전체를 받는 배열
let result; // 결과값

/**************입력 받아오면서 배열에 저장 ********************* */
// 숫자 0 ~ 9
let zero = document.getElementById('zero');
zero.addEventListener('click',function(){
    input.push(zero.innerHTML);
    console.log(input);
});

let one = document.getElementById('one');
one.addEventListener('click',function(){
    input.push(one.innerHTML);
    console.log(input);
});

let two = document.getElementById('two');
two.addEventListener('click',function(){
    input.push(two.innerHTML);
    console.log(input);
});

let three = document.getElementById('three');
three.addEventListener('click',function(){
    input.push(three.innerHTML);
    console.log(input);
});

let four= document.getElementById('four');
four.addEventListener('click',function(){
    input.push(four.innerHTML);
    console.log(input);
});

let five = document.getElementById('five');
five.addEventListener('click',function(){
    input.push(five.innerHTML);
    console.log(input);
});

let six = document.getElementById('six');
six.addEventListener('click',function(){
    input.push(six.innerHTML);
    console.log(input);
});

let seven = document.getElementById('seven');
seven.addEventListener('click',function(){
    input.push(seven.innerHTML);
    console.log(input);
});

let eight = document.getElementById('eight');
eight.addEventListener('click',function(){
    input.push(eight.innerHTML);
    console.log(input);
});

let nine = document.getElementById('nine');
nine.addEventListener('click',function(){
    input.push(nine.innerHTML);
    console.log(input);
});

// 연산 (%, /, *, -, +) 및 첫번째 입력 출력
let percent = document.getElementById('percent');
percent.addEventListener('click',function(){
    input.push(percent.innerHTML);
    console.log(input);
    let temp = input.join('');
    temp = temp.split("%");
    display.innerHTML=temp[0];
    console.log(input);
});

let slash = document.getElementById('slash');
slash.addEventListener('click',function(){
    input.push(slash.innerHTML);
    console.log(input);
    let temp = input.join('');
    temp = temp.split("/");
    display.innerHTML=temp[0];
    console.log(input);
});

let multiple = document.getElementById('multiple');
multiple.addEventListener('click',function(){
    input.push(multiple.innerHTML);
    console.log(input);
    let temp = input.join('');
    temp = temp.split("*");
    display.innerHTML=temp[0];
    console.log(input);
});

let minus = document.getElementById('minus');
minus.addEventListener('click',function(){
    input.push(minus.innerHTML);
    console.log(input);
    let temp = input.join('');
    temp = temp.split("-");
    display.innerHTML=temp[0];
    console.log(input);
});

let plus = document.getElementById('plus');
plus.addEventListener('click',function(){
    input.push(plus.innerHTML);
    console.log(input);
    let temp = input.join('');
    temp = temp.split("+");
    display.innerHTML=temp[0];
    console.log(input);
});

// C는 배열 비우기
let C = document.getElementById('C');
C.addEventListener('click',function(){
    input = [];
    console.log(input);
    display.innerHTML='';
})

// 소수점
let point = document.getElementById('point');
point.addEventListener('click',function(){
    input.push(point.innerHTML);
    console.log(input);
});

/******************계산 처리 및 출력 **********************/
let display = document.getElementById('display');
let equal = document.getElementById('equal');

equal.addEventListener('click',function(){
    input = input.join('');
    console.log(input);
    result = eval(input);
    display.innerHTML=result;
})
