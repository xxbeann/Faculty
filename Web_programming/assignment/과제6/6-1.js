// 타이머 만들기------------------------------------------------
let counter;
let count;

function start_timer(){
    count = 10;
    document.getElementById('countdown').innerHTML=`남은 시간: ${count}`;
    counter = setInterval(timer,1000); 
    function timer(){
        count--;
        document.getElementById('countdown').innerHTML=`남은 시간: ${count}`;
        if(count<0){
            document.getElementById('countdown').innerHTML="남은 시간: 시간 초과!";
            result_handler_auto();
        }
    }
}

//문제 만들기-----------------------------------------------------
let answer;

function problem() {
    let operand = ['+','-','*'];
    let num1 = Math.floor(Math.random()*100) + 1;
    let num2 = Math.floor(Math.random()*100) + 1;
    let num3 = Math.floor(Math.random()*100) + 1;
    let i = Math.floor(Math.random()*3);
    let j = Math.floor(Math.random()*3);
    let problem = num1 + operand[i] + num2 + operand[j] + num3;
    answer = eval(problem);
    document.getElementById('problem').innerHTML = problem;
    console.log(problem);
    console.log(answer);
}

// 다시 버튼에 이벤트 추가-------------------------------------------------------
let re = document.getElementById('reset');
re.addEventListener("click", function(){
    problem();
    empty();
    start_timer();
});

// 출력된 form 요소 지우기
function empty() {
    r.innerHTML = '';
    r.style.backgroundColor = 'white';
    e.innerHTML = '';
    e.style.backgroundColor = 'white';
    let userAnswer = document.getElementById('input').value = '';
}

// 채점 버튼에 이벤트 추가 + result_handler------------------------------------------------- 
let r = document.getElementById('result');
let c = document.getElementById('calculate');
let e = document.getElementById('extra');
c.addEventListener('click', result_handler_click)

// 클릭했을 때 result 출력 함수
function result_handler_click() {
    let userAnswer = document.getElementById('input').value;
    console.log(userAnswer);
    clearInterval(counter);
    if(answer == userAnswer){ // 정답일때
        r.innerHTML = '정답입니다.';
        r.style.backgroundColor = 'lightblue';
        e.innerHTML = '와우! 대단해요! ' + (count+1) + '초 남았습니다.'
    }
    else if(userAnswer == ""){ // 빈칸일때
        r.innerHTML = '정답을 입력하세요';
        r.style.backgroundColor = 'lightyellow';
    }
    else { // 오답일 때
        r.innerHTML = '오답입니다.';
        r.style.backgroundColor = 'coral';
    }
}
// 10초 지났을 때 자동 채점 함수
function result_handler_auto() {
    let userAnswer = document.getElementById('input').value;
    console.log(userAnswer);
    clearInterval(counter);
    if(answer == userAnswer){ // 정답일때
        r.innerHTML = '정답입니다.';
        r.style.backgroundColor = 'lightblue';
    }
    else if(userAnswer == ""){ // 빈칸일때
        r.innerHTML = '정답을 입력하세요';
        r.style.backgroundColor = 'lightyellow';
    }
    else { // 오답일 때
        r.innerHTML = '오답입니다.';
        r.style.backgroundColor = 'coral';
    }
}

//-------------------------------------------------------------------------
window.onload = function () {
    problem();
    start_timer();
}