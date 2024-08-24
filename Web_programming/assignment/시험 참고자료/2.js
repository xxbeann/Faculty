let started = false; //게임 상태 저장
let spinning = new Array(3); // 각 슬롯의 회전상태 저장
let speed = new Array(3); //각 슬롯의 회전 속도 저장
let spinner = new Array(3); //각 슬롯 setInterval id 저장
let numbers; //모든 슬롯 객체 저장
let msg; // 게임 메세지 표기

function init() { // 초기화 본문이 로딩 완료되었을 때 초기화
    msg = document.getElementById("msg");
    numbers = document.getElementsByClassName("number");
    for (let i = 0; i < numbers.length; i++) {
        spinning[i] = false;
        numbers[i].innerHTML = Math.floor(Math.random() * 10).toString();
    }

    msg.innerHTML = "Spin을 누르세요"
}


function start() {
    if (!started) {
        started = true;
        for (let i = 0; i < numbers.length; i++) {
            spinning[i] = true;
            spinner[i] = setInterval("spin(" + i + ")", 100);
            speed[i] = Math.random() * 5 + 4;
        }

        msg.innerHTML = "게임이 시작되었습니다"
    }else{
        msg.innerHTML = "게임 중입니다"
    }
    
}


function spin(index) {
    let currentNum = parseInt(numbers[index].innerHTML);
    let newNumber = parseInt(currentNum + speed[index]);
0
    if (newNumber > 9) {
        newNumber = 0;
        // 0과 9사이로 스피드 설정
    }

    if (speed[index] < 0 || newNumber == currentNum) {
        stop(index)
        // 스피드가 0보다 작아질 때는 멈춤
    }

    numbers[index].innerHTML = parseInt(newNumber);
    speed[index] -= 0.1;
    // 호출 될 때마다 스피드를 줄여줌
}

function stop(index) {
    // onclick 이벤트
    spinning[index] = false;
    checkFinished();
    clearInterval(spinner[index]);
}

function checkFinished() {
    for (let i = 0; i < 3; i++) {
        if (spinning[i])
            return;
    }
    started = false;
    gameOver();   
}

function gameOver()
{
    let win = false;
    if (numbers[0].innerHTML == numbers[1].innerHTML)
    {
        if (numbers[1].innerHTML == numbers[2].innerHTML)
        {
            win = true;
        }
    }

    if(win)
    {
        msg.innerHTML = "축하합니다"
    }else{
        msg.innerHTML = "다시 시도해보세요"
    } 
}