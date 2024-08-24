let ball;
let ballSize;
let x;
let y;
let velocityX;
let velocityY;
let gravity;
let restitution;
let isMouseDown;
let offsetX;
let offsetY;

function init() {
  ball = document.getElementById('ball');
  ballSize = 40;
  x = 200;
  y = 100;
  velocityX = Math.random() * 10 - 5; // 랜덤 초기 속도 (-5 ~ 5)
  velocityY = Math.random() * 10 - 5; // 랜덤 초기 속도 (-5 ~ 5)
  gravity = 0.5;
  restitution = 0.8;
  isMouseDown = false;
  offsetX = 0;
  offsetY = 0;

  ball.addEventListener('mousedown', function(event) {
    isMouseDown = true;
    offsetX = event.clientX - x;
    offsetY = event.clientY - y;
    velocityX = 0;
    velocityY = 0;
  });

  document.addEventListener('mousemove', function(event) {
    if (isMouseDown) {
      x = event.clientX - offsetX;
      y = event.clientY - offsetY;
    }
  });

  document.addEventListener('mouseup', function() {
    isMouseDown = false;
  });

  setInterval(update, 1000 / 60); // 60 FPS
}

function update() {
  if (!isMouseDown) {
    velocityY += gravity;
    x += velocityX;
    y += velocityY;

    if (y + ballSize > window.innerHeight) {
      y = window.innerHeight - ballSize;
      velocityY *= -restitution;
    }

    if (x + ballSize > window.innerWidth) {
      x = window.innerWidth - ballSize;
      velocityX *= -restitution;
    } else if (x < 0) {
      x = 0;
      velocityX *= -restitution;
    }
  }

  ball.style.left = x + 'px';
  ball.style.top = y + 'px';
}

window.onload = init;