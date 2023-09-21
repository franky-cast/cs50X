// DOM
const answerStatusEl = document.querySelector('.answer-status-el');
const buttons = document.querySelectorAll('.button-el');

const openStatusEl = document.querySelector('.open-question-status-el');
const openInputEl = document.querySelector('#open-question-input-el');
const checkButtonEl = document.querySelector('#check-button-el');

// Functions
function clickHandler (event) {
    event.preventDefault();

    // check answer
    const button = event.currentTarget;
    const buttonValue = button.querySelector('.input-el');
    const isCorrect = checkAnswer('Jupiter', buttonValue.value);

    // change background color
    if (isCorrect) {
        button.style.backgroundColor = '#4CAF50';
        buttonValue.style.backgroundColor = '#4CAF50';
        answerStatusEl.innerHTML = 'Correct!';
        buttons.forEach((button) => {
            button.removeEventListener('click', clickHandler);
        })
    }
    else {    
       button.style.backgroundColor = '#FF5733';
       buttonValue.style.backgroundColor = '#FF5733';
       answerStatusEl.innerHTML = 'Incorrect';
    }
}

function checkAnswer (correctAnswer, answerGuessed) {
    return correctAnswer == answerGuessed ? true: false;
}


// Event Listeners
buttons.forEach((button) => {
    button.addEventListener('click', clickHandler);
})

openInputEl.addEventListener('keyup', () => {
    openInputEl.style.backgroundColor = "#fff";
    openStatusEl.innerHTML = "";
})

checkButtonEl.addEventListener('click', (event) => {
    // preventing default form submission
    event.preventDefault();

    // check answer
    if (openInputEl.value == "") {
        alert("Please enter answer");
        return
    }
    const isCorrect = checkAnswer ('Sherlock Holmes', openInputEl.value);
    openInputEl.value == "";

    // change color
    if (isCorrect) {
        openInputEl.style.backgroundColor = '#4CAF50';
        openStatusEl.innerHTML = "Correct!";
    } else {
        openInputEl.style.backgroundColor = '#FF5733';
        openStatusEl.innerHTML = "Incorrect";
    }
})