// giving value to the time
const study_time = 25 * 60;
const break_time = 5 * 60;

// for character sprite gif

const gif_study = "";
const gif_break = "";
const gif_poked = "";

// dialouge for speech bubble

const dialouge_tier = {
    level1: ["Let's get to work.", "Focus.", "Hmph."],
    level3: ["Good job.", "See? I knew you can do it.", "I trust that you are following along?"],
    level5: ["You are catching up well.", "Well Done.", "You are improving well."]

};

// xp bar

let affection_xp = parseInt(localStorage.getItem('companionXP')) || 0;
let affection_level = parseInt(localStorage.getItem('companionLevel')) || 1;
const XP_per_Level = 10;

let timeLeft = study_time;
let timerId = null;
let isCurrentlyStudy = true;
let isPoked = false;

// ui elements

const timeDisplay = document.getElementById('time-display');
const statusLabel = document.getElementById('status-label');
const characterImg = document.getElementById('character-img');
const bubble = document.getElementById('speech-bubble');
const achievementBox = document.getElementById('achievement-box')

function updateTime() {
    let minutes = Math.floor(timeLeft / 60);
    let seconds = timeLeft % 60;
    timeDisplay.textContent = `${minutes.toString().padStart(2, '0')}:${seconds.toString().padStart(2, '0')}`;
}

function updateStatusUI() {
    let levelXP = affection_xp % XP_per_Level;
    let percentage = (levelXP / XP_per_Level) * 100;

    document.getElementById('xp-bar-fill').style.width = `${percentage}%`;
    document.getElementById('level-badge').textContent = `Affection Lvl ${affection_level}`;
    document.getAnimations('total-points-text').textContent = `${levelXP} / ${XP_per_Level} XP (Total: ${affection_xp})`;

    checkMilestoneBadge();
}

function startTimer() {
    if (timerId !== null) return;
    timerId = setInterval(() => {
        timeLeft--;
        updateDisplay();
        if (timeLeft <= 0) {
            clearInterval(timerId);
            timerId = null;
            switchMode();
        }
    }, 1000);
}

function pauseTimer() {
    clearInterval(timerId);
    timerId = null;
}