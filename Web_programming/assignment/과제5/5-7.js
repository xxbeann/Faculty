let tds;
let prevIndex=0, index=0;
let colors = ["red", "lightblue", "lightgreen", "lightcoral", "lightgoldenrodyellow", "lightgray"];

window.onload = function () { // 웹 페이지의 로딩 완료시 실행
    tds = document.getElementsByTagName("td");	
    tds[index].style.backgroundColor = "red";
}

window.onkeydown = function (e) {
    switch(e.key) {
        case "ArrowDown" : 
            if(index/6 >= 5) return; // 맨 아래 셀의 경우
            index += 6;
            break;
        case "ArrowUp" : 
            if(index/6 < 1) return; // 맨 위 셀의 경우
            index -= 6;
            break;
        case "ArrowLeft" : 
            if(index%6 == 0) return; // 맨 왼쪽 셀의 경우
            index--; 
            break;
        case "ArrowRight" : 
            if(index%6 == 5) return; // 맨 오른쪽 셀의 경우
            index++; 
            break;
    }
    tds[index].style.backgroundColor = colors[Math.floor(index / 6)];
    tds[prevIndex].style.backgroundColor = "white";
    prevIndex = index;
}