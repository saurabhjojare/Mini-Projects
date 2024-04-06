let userScore = 0;
let compScore = 0;

const choices = document.querySelectorAll(".choice");
const msg = document.querySelector("#msg");

const userScoreShow = document.querySelector("#user-score");
const compScoreShow = document.querySelector("#comp-score");

const genComputerChoice = () => {
    const options = ["rock", "paper", "scissors"];
    const randomId = Math.floor(Math.random() * 3);
    return options[randomId];
}

const drawGame = () => {
    console.log("Draw Game");
    msg.innerText = "Draw Game"
    msg.style.color = "grey";
}

const showWinner = (userWin, userChoice, compChoice) => {
    if (userWin) {
        userScore++;
        userScoreShow.innerText = userScore;
        console.log("You Win");
        msg.innerText = "You Win"
        msg.style.color = "green";
    } else {
        compScore++;
        compScoreShow.innerText = compScore;
        console.log("You Lose");
        msg.innerText = "You Lose"
        msg.style.color = "red";
    }
}

const playGame = (userChoice) => {
    console.log("User Choice = ", userChoice);
    const compChoice = genComputerChoice();
    console.log("Comp Choice = ", compChoice);
    if (userChoice === compChoice) {
        drawGame();
    } else {
        let userWin = true;
        if (userChoice == "rock") {
            userWin = compChoice === "paper" ? false : true;
        } else if (userChoice === "paper") {
            userWin = compChoice === "scissors" ? false : true;
        } else {
            userWin = compChoice === "rock" ? false : true;
        }
        showWinner(userWin);
    }
};

choices.forEach((choice) => {
    choice.addEventListener("click", () => {
        const userChoice = choice.getAttribute("id")
        playGame(userChoice);
    });
});